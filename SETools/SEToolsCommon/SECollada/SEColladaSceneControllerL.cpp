// Swing Engine Version 1 Source Code 
// Most of techniques in the engine are mainly based on David Eberly's
// Wild Magic 4 open-source code.The author of Swing Engine learned a lot
// from Eberly's experience of architecture and algorithm.
// Several sub-systems are totally new,and others are re-implimented or
// re-organized based on Wild Magic 4's sub-systems.
// Copyright (c) 2007-2010.  All Rights Reserved
//
// Eberly's permission:
// Geometric Tools, Inc.
// http://www.geometrictools.com
// Copyright (c) 1998-2006.  All Rights Reserved
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or (at
// your option) any later version.  The license is available for reading at
// the location:
// http://www.gnu.org/copyleft/lgpl.html

#include "SEToolsCommonPCH.h"
#include "SEColladaScene.h"

using namespace Swing;

//----------------------------------------------------------------------------
Node* ColladaScene::LoadInstanceController(domInstance_controllerRef spLib)
{
    // Get all instance materials used by this instance controller object.
    // Each instance material points to a material object in our material 
    // catalog.
    domBind_material* pDomBindMaterial =  spLib->getBind_material();
    if( pDomBindMaterial )
    {
        // Get the <technique_common> element.
        domBind_material::domTechnique_common* pDomTechniqueCommon = 
            pDomBindMaterial->getTechnique_common();
        if( pDomTechniqueCommon )
        {
            // Get all <instance_material> elements.
            domInstance_material_Array& rDomInstanceMaterialArray = 
                pDomTechniqueCommon->getInstance_material_array();

            int iIMaterialCount = (int)rDomInstanceMaterialArray.getCount();
            for( int i = 0; i < iIMaterialCount; i++ )
            {
                ColladaInstanceMaterial* pInstanceMaterial = 
                    LoadInstanceMaterial(rDomInstanceMaterialArray[i]);

                if( pInstanceMaterial )
                {
                    m_InstanceMaterials.push_back(pInstanceMaterial);
                }
            }
        }
    }

    // Create a instance controller to hold the relationship between the 
    // geometry and the controller.
    ColladaInstanceController* pIController = 0;
    ColladaInstanceController::ControllerType eControllerType = 
        ColladaInstanceController::CT_UNKNOWN;

    // Find the controller that encapsulates the geometry object.
    // Then load the geometry object.
    xsAnyURI& rUrlType = spLib->getUrl();
    domElement* pDomElement = rUrlType.getElement();
    domController* pDomController = (domController*)pDomElement;
    Node* pMeshRoot = 0;
    if( pDomController )
    {
        // There are two kinds of controller in COLLADA(<skin> and <morph>).
        // Each one of them has a source attribute that points to the 
        // geometry object. So the controller must be one of these two cases.

        domElement* pDomSource = 0;
        domSkin* pDomSkin = pDomController->getSkin();
        domMorph* pDomMorph = pDomController->getMorph();
        if( pDomSkin )
        {
            pDomSource = pDomSkin->getSource().getElement();
            if( !pDomSource )
            {
                // Skin source not found.
                SE_ASSERT( false );
                return 0;
            }

            if( pDomSource->getElementType() != COLLADA_TYPE::GEOMETRY )
            {   
                // Skin source is not geometry.
                SE_ASSERT( false );
                return 0;
            }

            // Load the geometry.
            pMeshRoot = LoadGeometry((domGeometry*)pDomSource);
            if( !pMeshRoot )	
            {		
                // Target geometry is not found.
                SE_ASSERT( false );
                return 0;
            }

            eControllerType = ColladaInstanceController::CT_SKIN;
        }
        else if( pDomMorph )
        {
            pDomSource = pDomMorph->getSource().getElement();
            if( !pDomSource )
            {
                // Morph source not found.
                SE_ASSERT( false );
                return 0;
            }

            // Load the geometry.
            pMeshRoot = LoadGeometry((domGeometry*)pDomSource);
            if( !pMeshRoot )	
            {		
                // Target geometry is not found.
                SE_ASSERT( false );
                return 0;
            }

            eControllerType = ColladaInstanceController::CT_MORPH;
        }
    }
    else
    {
        SE_ASSERT( false );
        return 0;
    }

    // Try to find the skeleton root that will be used to control the 
    // geometry object. There could be more than one skeleton root, but 
    // for now we just support one.
    domInstance_controller::domSkeleton_Array& rDomSkeletonArray = 
        spLib->getSkeleton_array();
    domNode* pDomSkeletonRoot = 0;
    if( rDomSkeletonArray.getCount() > 1 )
    {
        ToolSystem::SE_DebugOutput("There are more than one skeleton");
    }
    if( rDomSkeletonArray.getCount() > 0 )
    {
        pDomSkeletonRoot = 
            (domNode*)(domElement*)rDomSkeletonArray[0]->getValue(
            ).getElement();
    }

    pIController = SE_NEW ColladaInstanceController(eControllerType,
        pDomController, pDomSkeletonRoot, pMeshRoot);
    m_InstanceControllers.push_back(pIController);

    return pMeshRoot;
}
//----------------------------------------------------------------------------
void ColladaScene::ProcessSkin(ColladaInstanceController* pIController)
{
    SE_ASSERT( pIController );

    Node* pMeshRoot = pIController->GetMeshRoot();
    domController* pDomController = pIController->GetController();
    domNode* pDomSkeletonRoot = pIController->GetSkeletonRoot();
    SE_ASSERT( pMeshRoot && pDomController && pDomSkeletonRoot );

    // Get COLLADA skinned geometry.
    domSkin* pDomSkin = pDomController->getSkin();
    SE_ASSERT( pDomSkin );
    domGeometry* pDomGeometry = 
        (domGeometry*)(domElement*)pDomSkin->getSource().getElement();
    SE_ASSERT( pDomGeometry );

    // Get COLLADA skinned geometry's position data.
    domMesh* pDomMesh = pDomGeometry->getMesh();
    SE_ASSERT( pDomMesh );
    domVertices* pDomVertices = pDomMesh->getVertices();
    SE_ASSERT( pDomVertices );
    domListOfFloats* pDomPositionData = 0;
    domInputLocal_Array& rDomVerticesInputs = pDomVertices->getInput_array();
    for( int i = 0; i < (int)rDomVerticesInputs.getCount(); i++ )
    {
        domSource* pDomSource = 
            (domSource*)(domElement*)rDomVerticesInputs[i]->getSource(
            ).getElement();

        xsNMTOKEN strSemantic = rDomVerticesInputs[i]->getSemantic();
        if( strcmp("POSITION", strSemantic) == 0 )
        {
            pDomPositionData = &pDomSource->getFloat_array()->getValue();
            break;
        }
    }
    SE_ASSERT( pDomPositionData );

    // How many vertices are there in the COLLADA mesh's position source?
    int iVertexCount = (int)pDomPositionData->getCount()/3;

    // Get COLLADA JOINT source and INV_BIND_MATRIX source.
    domSkin::domJoints* pDomJoints = pDomSkin->getJoints();
    domInputLocal_Array& rDomJointsInputs = pDomJoints->getInput_array();
    domSource* pDomJointSource = 0;
    domSource* pDomIBMatrixSource = 0;
    for( int i = 0; i < (int)rDomJointsInputs.getCount(); i++ )
    {
        domSource* pDomSource = 
            (domSource*)(domElement*)rDomJointsInputs[i]->getSource(
            ).getElement();

        xsNMTOKEN strSemantic = rDomJointsInputs[i]->getSemantic();
        if( strcmp("JOINT", strSemantic) == 0 )
        {
            pDomJointSource = pDomSource;
        }
        else if( strcmp("INV_BIND_MATRIX", strSemantic) == 0 )
        {
            pDomIBMatrixSource = pDomSource;
        }
    }
    SE_ASSERT( pDomJointSource && pDomIBMatrixSource );

    // Get COLLADA WEIGHT source/data, JOINT offset, and WEIGHT offset.
    domSkin::domVertex_weights* pDomVertexWeights = 
        pDomSkin->getVertex_weights();
    domInputLocalOffset_Array& rDomVertexWeightsInputs = 
        pDomVertexWeights->getInput_array();
    domSource* pDomWeightsSource = 0;
    domListOfFloats* pDomWeightsData = 0;
    int iJointOffset = -1;
    int iWeightOffset = -1;
    for( int i = 0; i < (int)rDomVertexWeightsInputs.getCount(); i++ )
    {
        domSource* pDomSource = 
            (domSource*)(domElement*)rDomVertexWeightsInputs[i]->getSource(
            ).getElement();

        xsNMTOKEN strSemantic = rDomVertexWeightsInputs[i]->getSemantic();
        if( strcmp("JOINT", strSemantic) == 0 )
        {
            iJointOffset = (int)rDomVertexWeightsInputs[i]->getOffset();
        }
        else if( strcmp("WEIGHT", strSemantic) == 0 )
        {
            pDomWeightsSource = pDomSource;
            iWeightOffset = (int)rDomVertexWeightsInputs[i]->getOffset();
        }
    }
    SE_ASSERT( pDomWeightsSource && iJointOffset > -1 && iWeightOffset > -1 );
    pDomWeightsData = &pDomWeightsSource->getFloat_array()->getValue();

    // Get all bone nodes applied to the mesh from Swing Engine scene graph.
    // There are two cases:
    // (1) If we got a COLLADA <name_array>, then we should use SID as the key
    //     for searching.
    // (2) If we got a COLLADA <IDREF_array>, then we should use ID as the key
    //     for searching.
    domName_array* pDomNameArray = pDomJointSource->getName_array();
    domIDREF_array* pDomIDREFArray = pDomJointSource->getIDREF_array();
    int iBoneCount = 0;
    Node** apSEBones = 0;
    if( pDomNameArray )
    {
        // TODO:
        // Support SID case.
        iBoneCount = (int)pDomNameArray->getCount();
    }
    else if( pDomIDREFArray )
    {
        iBoneCount = (int)pDomIDREFArray->getCount();
        apSEBones = SE_NEW Node*[iBoneCount];

        for( int iB = 0; iB < iBoneCount; iB++ )
        {
            const char* acBoneName = 
                (const char*)pDomIDREFArray->getValue()[iB].getID();

            Object* pBone = m_spSceneRoot->GetObjectByName(acBoneName);
            SE_ASSERT( pBone );
            apSEBones[iB] = StaticCast<Node>(pBone);
        }
    }
    else
    {
        // Should never go to here.
        SE_ASSERT( false );
    }

    // Get all inverse binding matrices applied to the mesh.
    Transformation* aOffset = SE_NEW Transformation[iBoneCount];
    domListOfFloats* pDomIBMatrixData = &pDomIBMatrixSource->getFloat_array(
        )->getValue();
    for( int iB = 0; iB < iBoneCount; iB++ )
    {
        int iBase = 16*iB;

        float fM00, fM01, fM02, fM10, fM11, fM12, fM20, fM21, fM22;
        fM00 = (float)(*pDomIBMatrixData)[iBase     ];
        fM01 = (float)(*pDomIBMatrixData)[iBase +  1];
        fM02 = (float)(*pDomIBMatrixData)[iBase +  2];
        fM10 = (float)(*pDomIBMatrixData)[iBase +  4];
        fM11 = (float)(*pDomIBMatrixData)[iBase +  5];
        fM12 = (float)(*pDomIBMatrixData)[iBase +  6];
        fM20 = (float)(*pDomIBMatrixData)[iBase +  8];
        fM21 = (float)(*pDomIBMatrixData)[iBase +  9];
        fM22 = (float)(*pDomIBMatrixData)[iBase + 10];

        Vector3f vec3fRow0, vec3fRow1, vec3fRow2;
        vec3fRow0 = GetTransformedVector(fM00, fM01, fM02);
        vec3fRow1 = GetTransformedVector(fM10, fM11, fM12);
        vec3fRow2 = GetTransformedVector(fM20, fM21, fM22);

        Matrix3f mat3fM(vec3fRow0, vec3fRow1, vec3fRow2);

        float fT0, fT1, fT2;
        fT0 = (float)(*pDomIBMatrixData)[iBase +  3];
        fT1 = (float)(*pDomIBMatrixData)[iBase +  7];
        fT2 = (float)(*pDomIBMatrixData)[iBase + 11];

        Vector3f vec3fT = GetTransformedVector(fT0, fT1, fT2);

        aOffset[iB].SetMatrix(mat3fM);
        aOffset[iB].SetTranslate(vec3fT);
    }

    // Get vertex's bone weights table.
    int iVertexWeightsCount = (int)pDomVertexWeights->getCount();
    SE_ASSERT( iVertexWeightsCount == iVertexCount );
    domSkin::domVertex_weights::domVcount* pDomVCount = 
        pDomVertexWeights->getVcount();
    domSkin::domVertex_weights::domV* pDomV = pDomVertexWeights->getV();
    domListOfUInts& rDomVCountData = pDomVCount->getValue();
    domListOfInts& rDomVData = pDomV->getValue();
    std::vector<BoneWeight>* aBWArray = 
        SE_NEW std::vector<BoneWeight>[iVertexWeightsCount];
    int iCurVBase = 0;
    for( int i = 0; i < iVertexWeightsCount; i++ )
    {
        // For each vertex, get its bones index and bone weights.
        int iVertexBoneCount = (int)rDomVCountData[i];
        for( int j = 0; j < iVertexBoneCount; j++ )
        {
            BoneWeight tempBW;
            tempBW.BoneID = (int)rDomVData[iCurVBase + iJointOffset];
            int iWeightID = (int)rDomVData[iCurVBase + iWeightOffset];
            tempBW.Weight = (float)(*pDomWeightsData)[iWeightID];

            aBWArray[i].push_back(tempBW);
            iCurVBase += 2;
        }
    }

    // Create skin effect for each sub-mesh.
    for( int i = 0; i < pMeshRoot->GetCount(); i++ )
    {
        TriMesh* pSubMesh = StaticCast<TriMesh>(pMeshRoot->GetChild(i));

        // Get all vertex indices used by this sub-mesh.
        int iActiveVertexCount = pSubMesh->VBuffer->GetVertexCount();
        std::vector<int> tempVIArray;
        int iAV, iV;
        for( iAV = 0; iAV < iActiveVertexCount; iAV++ )
        {
            for( iV = 0; iV < iVertexCount; iV++ )
            {
                float fX, fY, fZ;
                int iBase = 3*iV;
                fX = (float)(*pDomPositionData)[iBase    ];
                fY = (float)(*pDomPositionData)[iBase + 1];
                fZ = (float)(*pDomPositionData)[iBase + 2];
                Vector3f vec3fCurPos = GetTransformedVector(fX, fY, fZ);

                if( vec3fCurPos.X == 
                    (*(Vector3f*)pSubMesh->VBuffer->PositionTuple(iAV)).X
                &&  vec3fCurPos.Y == 
                    (*(Vector3f*)pSubMesh->VBuffer->PositionTuple(iAV)).Z
                &&  vec3fCurPos.Z == 
                    (*(Vector3f*)pSubMesh->VBuffer->PositionTuple(iAV)).Y )
                {
                    tempVIArray.push_back(iV);
                    break;
                }
            }
        }
    }

    if( apSEBones )
    {
        SE_DELETE[] apSEBones;
    }
    SE_DELETE[] aBWArray;
}
//----------------------------------------------------------------------------
void ColladaScene::ProcessMorph(ColladaInstanceController*)
{
}
//----------------------------------------------------------------------------