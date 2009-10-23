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
void ColladaScene::ProcessControllers()
{
    int iInstanceControllerCount = (int)m_InstanceControllers.size();
    for( int i = 0; i < iInstanceControllerCount; i++ )
    {
        ColladaInstanceController* pIController = m_InstanceControllers[i];
        ColladaInstanceController::ControllerType eControllerType = 
            pIController->GetControllerType();
        if( eControllerType == ColladaInstanceController::CT_SKIN )
        {
            ProcessSkin(pIController);
        }
        else if( eControllerType == ColladaInstanceController::CT_MORPH )
        {
            ProcessMorph(pIController);
        }
    }
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
    Node** apBones = 0;
    if( pDomNameArray )
    {
        iBoneCount = (int)pDomNameArray->getCount();
        apBones = SE_NEW Node*[iBoneCount];

        for( int iB = 0; iB < iBoneCount; iB++ )
        {
            xsNCName acBoneName = pDomNameArray->getValue()[iB];
            domNode* pDomJoint = GetDomNodeBySID(pDomSkeletonRoot, acBoneName);
            SE_ASSERT( pDomJoint );

            // Try to find this bone node in Swing Engine scene graph.
            Node* pBone = GetBoneNodeByDomNode(pDomJoint);
            SE_ASSERT( pBone );
            apBones[iB] = pBone;
        }
    }
    else if( pDomIDREFArray )
    {
        iBoneCount = (int)pDomIDREFArray->getCount();
        apBones = SE_NEW Node*[iBoneCount];

        for( int iB = 0; iB < iBoneCount; iB++ )
        {
            const char* acBoneName = 
                (const char*)pDomIDREFArray->getValue()[iB].getID();

            // Try to find this bone node in Swing Engine scene graph.
            Object* pBone = m_spSceneRoot->GetObjectByName(acBoneName);
            SE_ASSERT( pBone );
            apBones[iB] = StaticCast<Node>(pBone);
        }
    }
    else
    {
        // Should never go to here.
        SE_ASSERT( false );
    }

    // Get all inverse binding matrices applied to the mesh.
    Transformation* aOffsets = SE_NEW Transformation[iBoneCount];
    domListOfFloats* pDomIBMatrixData = &pDomIBMatrixSource->getFloat_array(
        )->getValue();
    for( int iB = 0; iB < iBoneCount; iB++ )
    {
        // Given a COLLADA homogeneous inverse binding matrix M:
        // m00  m01  m02  t1
        // m10  m11  m12  t2
        // m20  m21  m22  t3
        //   0    0    0   1
        // in column major order.
        //
        // Given a Swing Engine homogeneous vector V:
        // x
        // y 
        // z 
        // w
        // in column major order.
        //
        // We should construct a homogeneous matrix that could finish the 
        // following operations:
        // (1) Transform V back to the original DCC right-handed system,
        //     say, V0, by using a homogeneous matrix M0:
        // 1  0  0  0        
        // 0  1  0  0
        // 0  0 -1  0
        // 0  0  0  1
        // in column major order.
        //
        // (2) Transform V0 into the COLLADA binding joint's local right-
        //     handed system, say, V1, by using M.
        //
        // (3) Transform V1 back to the Swing Engine binding joint's local
        //     left-handed system, say, V2, by using a homogeneous matrix M1:
        // 1  0  0  0        
        // 0  1  0  0
        // 0  0 -1  0
        // 0  0  0  1
        // in column major order.
        //
        // The final combination of these three operations will be:
        // V2 = M1*M*M0*V.
        // So M1*M*M0 is the matrix we want:
        //  m00  m01 -m02  t1
        //  m10  m11 -m12  t2
        // -m20 -m21  m22 -t3
        //    0    0    0   1
        // in column major order.

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

        Vector3f vec3fRow0(fM00, fM01, -fM02);
        Vector3f vec3fRow1(fM10, fM11, -fM12);
        Vector3f vec3fRow2(-fM20, -fM21, fM22);
        Matrix3f mat3fM(vec3fRow0, vec3fRow1, vec3fRow2, false);

        float fT0, fT1, fT2;
        fT0 = (float)(*pDomIBMatrixData)[iBase +  3];
        fT1 = (float)(*pDomIBMatrixData)[iBase +  7];
        fT2 = (float)(*pDomIBMatrixData)[iBase + 11];
        Vector3f vec3fT(fT0, fT1, -fT2);

        // Maybe MT form is enough for our usage.
        aOffsets[iB].SetMatrix(mat3fM);
        aOffsets[iB].SetTranslate(vec3fT);
    }

    // Get vertex's bone weights table.
    // Each vertex could be influenced by any number of bones, say,
    // a number that is greater than four.
    // But Swing Engine's max vertex bone number is four, so we should
    // do some work here to get the most greatest weights of four bones,
    // and normalize these values to ensure the sum of them is 1.0.
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

        // Sort base on weight value in reversed order(big to small).
        // Then keep the greatest four weights.
        sort(aBWArray[i].rbegin(), aBWArray[i].rend());
        while( aBWArray[i].size() > 4 )
        {
            aBWArray[i].pop_back();
        }

        // Normalization.
        float fNorm = 0.0f;
        for( int j = 0; j < (int)aBWArray[i].size(); j++ )
        {
            fNorm += aBWArray[i][j].Weight;
        }
        float fInvNorm = 1.0f/fNorm;
        for( int j = 0; j < (int)aBWArray[i].size(); j++ )
        {
            aBWArray[i][j].Weight *= fInvNorm;
        }
    }

    // Create skin effect for each sub-mesh(if it is influenced by any bones).
    int* aiVerticesPerBone = SE_NEW int[iBoneCount];
    for( int iM = 0; iM < pMeshRoot->GetCount(); iM++ )
    {
        TriMesh* pSubMesh = StaticCast<TriMesh>(pMeshRoot->GetChild(iM));

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

                if( vec3fCurPos == 
                    (*(Vector3f*)pSubMesh->VBuffer->PositionTuple(iAV)) )
                {
                    tempVIArray.push_back(iV);
                    break;
                }
            }
        }

        // Get the number of vertex influenced by each bone.
        int iVertexIndexCount = (int)tempVIArray.size();
        SE_ASSERT( iVertexIndexCount == iActiveVertexCount );
        memset(aiVerticesPerBone, 0, sizeof(int)*iBoneCount);
        for( int i = 0; i < iVertexIndexCount; i++ )
        {
            int iVertexID = tempVIArray[i];
            for( int j = 0; j < (int)aBWArray[iVertexID].size(); j++ )
            {
                int iB = aBWArray[iVertexID][j].BoneID;
                aiVerticesPerBone[iB]++;
            }
        }

        // It is possible that the current sub-mesh just uses a subset of the 
        // original bone set, we count the number of bones in the subset here.
        int iActiveBoneCount = 0;
        for( int iB = 0; iB < iBoneCount; iB++ )
        {
            if( aiVerticesPerBone[iB] > 0 )
            {
                iActiveBoneCount++;
            }
        }
        SE_ASSERT( iActiveBoneCount > 0 );
        if( iActiveBoneCount == 0 )
        {
            // The current sub-mesh is not influenced by any bones, so we
            // skip to next one.
            continue;
        }

        // Create active bone nodes array and offsets array for skin effect.
        // These data will be released by skin effect.
        Node** apActiveBones = SE_NEW Node*[iActiveBoneCount];
        Transformation* aActiveOffsets = SE_NEW Transformation[iActiveBoneCount];

        // Get active bone nodes and their offsets.
        std::vector<int> tempBIArray(iBoneCount);
        int k = 0;
        for( int iB = 0; iB < iBoneCount; iB++ )
        {
            if( aiVerticesPerBone[iB] > 0 )
            {
                apActiveBones[k] = apBones[iB];
                aActiveOffsets[k] = aOffsets[iB];
                tempBIArray[iB] = k;
                k++;
            }
        }

        // Decide which kind of effect we should create.
        // TODO:
        // Impliment a flexible skin effect system.
        SkinEffect eSkinEffect = SE_DEFAULT;
        Effect* pSaveEffect = 0;
        for( int i = 0; i < pSubMesh->GetEffectCount(); i++ )
        {
            Effect* pTempEffect = pSubMesh->GetEffect(i);
            if( DynamicCast<MaterialEffect>(pTempEffect) )
            {
                eSkinEffect = SE_MATERIAL;
                pSaveEffect = pTempEffect;
                break;
            }
            else if( DynamicCast<MaterialTextureEffect>(pTempEffect) )
            {
                eSkinEffect = SE_MATERIALTEXTURE;
                pSaveEffect = pTempEffect;
                break;
            }
            else if( DynamicCast<DefaultShaderEffect>(pTempEffect ))
            {
                eSkinEffect = SE_DEFAULT;
                pSaveEffect = pTempEffect;
                break;
            }
        }

        // Create a new vertex buffer for the sub-mesh and replace the old
        // one with it.
        Attributes tempAttr;
        switch( eSkinEffect )
        {
        case SE_DEFAULT:
            tempAttr.SetPositionChannels(3);
            tempAttr.SetTCoordChannels(0, 4); // BlendWeight
            tempAttr.SetTCoordChannels(1, 4); // BlendIndices
            break;

        case SE_MATERIAL:
            tempAttr.SetPositionChannels(3);
            tempAttr.SetNormalChannels(3);
            tempAttr.SetTCoordChannels(0, 4); // BlendWeight
            tempAttr.SetTCoordChannels(1, 4); // BlendIndices
            break;

        case SE_MATERIALTEXTURE:
            tempAttr.SetPositionChannels(3);
            tempAttr.SetNormalChannels(3);
            tempAttr.SetTCoordChannels(0, 2); // BaseTexture
            tempAttr.SetTCoordChannels(1, 4); // BlendWeight
            tempAttr.SetTCoordChannels(2, 4); // BlendIndices
            break;

        default :
            SE_ASSERT( false );
            break;
        }
        VertexBuffer* pVBNew = SE_NEW VertexBuffer(tempAttr, 
            iActiveVertexCount);
        int iChannels;
        float* afData = pVBNew->GetData();
        pSubMesh->VBuffer->BuildCompatibleArray(tempAttr, false, iChannels, 
            afData);
        SE_ASSERT( iChannels == pVBNew->GetChannelCount() );
        pSubMesh->VBuffer = pVBNew;

        // Assign bone index and bone weight values for the vertex buffer.
        SE_ASSERT( iVertexIndexCount == pVBNew->GetVertexCount() );
        for( int i = 0; i < iVertexIndexCount; i++ )
        {
            // Point to destination address.
            float* pWeights = 0;
            float* pIndices = 0;
            switch( eSkinEffect )
            {
            case SE_DEFAULT:
                pWeights = pSubMesh->VBuffer->TCoordTuple(0, i);
                pIndices = pSubMesh->VBuffer->TCoordTuple(1, i);
                break;

            case SE_MATERIAL:
                pWeights = pSubMesh->VBuffer->TCoordTuple(0, i);
                pIndices = pSubMesh->VBuffer->TCoordTuple(1, i);
                break;

            case SE_MATERIALTEXTURE:
                pWeights = pSubMesh->VBuffer->TCoordTuple(1, i);
                pIndices = pSubMesh->VBuffer->TCoordTuple(2, i);
                break;

            default :
                SE_ASSERT( false );
                break;
            }

            // CAUTION:
            // We already make sure that iVertexBoneCount <= 4, otherwise 
            // the following operation is unsafe.
            int iVertexID = tempVIArray[i];
            int iVertexBoneCount = (int)aBWArray[iVertexID].size();
            for( int j = 0; j < iVertexBoneCount; j++ )
            {
                int iCurBoneID = aBWArray[iVertexID][j].BoneID;
                int iCurActiveBoneID = tempBIArray[iCurBoneID];
                float fCurBoneWeight = aBWArray[iVertexID][j].Weight;

                *pWeights++ = fCurBoneWeight;
                *pIndices++ = (float)iCurActiveBoneID;
            }
        }

        // Create the skin effect we want and attach it to the sub-mesh.
        Effect* pNewEffect = 0;
        String tempImageName;
        switch( eSkinEffect )
        {
        case SE_DEFAULT:
            pNewEffect = SE_NEW SkinDefaultEffect(iActiveBoneCount, 
                apActiveBones, aActiveOffsets);
            break;

        case SE_MATERIAL:
            pNewEffect = SE_NEW SkinMaterialEffect(iActiveBoneCount, 
                apActiveBones, aActiveOffsets);
            break;

        case SE_MATERIALTEXTURE:
            {
                MaterialTextureEffect* pMTEffect = 
                    DynamicCast<MaterialTextureEffect>(pSaveEffect);
                tempImageName = pMTEffect->GetPImageName(0, 0);

                pNewEffect = SE_NEW SkinMaterialTextureEffect(
                    tempImageName, iActiveBoneCount, apActiveBones, 
                    aActiveOffsets);
            }
            break;

        default :
            SE_ASSERT( false );
            break;
        }
        if( pSaveEffect )
        {
            pSubMesh->DetachEffect(pSaveEffect);
        }
        pSubMesh->AttachEffect(pNewEffect);
    }

    SE_DELETE[] apBones;
    SE_DELETE[] aOffsets;
    SE_DELETE[] aBWArray;
    SE_DELETE[] aiVerticesPerBone;
}
//----------------------------------------------------------------------------
void ColladaScene::ProcessMorph(ColladaInstanceController*)
{
}
//----------------------------------------------------------------------------