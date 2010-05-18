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
SENode* SEColladaScene::LoadInstanceController(domInstance_controllerRef 
    spLib)
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
                SEColladaInstanceMaterial* pInstanceMaterial = 
                    LoadInstanceMaterial(rDomInstanceMaterialArray[i]);

                if( pInstanceMaterial )
                {
                    m_InstanceMaterials.push_back(pInstanceMaterial);
                }
            }
        }
    }

    // Create an instance controller to hold the relationship between the 
    // geometry and the controller.
    SEColladaInstanceController* pIController = 0;
    SEColladaInstanceController::ControllerType eControllerType = 
        SEColladaInstanceController::CT_UNKNOWN;

    // Find the controller that encapsulates the geometry object.
    // Then load the geometry object.
    xsAnyURI& rUrlType = spLib->getUrl();
    domElement* pDomElement = rUrlType.getElement();
    domController* pDomController = (domController*)pDomElement;
    SENode* pMeshRoot = 0;
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

            eControllerType = SEColladaInstanceController::CT_SKIN;
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

            eControllerType = SEColladaInstanceController::CT_MORPH;
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
        ToolSystem::DebugOutput("There are more than one skeleton");
    }
    if( rDomSkeletonArray.getCount() > 0 )
    {
        pDomSkeletonRoot = 
            (domNode*)(domElement*)rDomSkeletonArray[0]->getValue(
            ).getElement();
    }

    pIController = SE_NEW SEColladaInstanceController(eControllerType,
        pDomController, pDomSkeletonRoot, pMeshRoot);
    m_InstanceControllers.push_back(pIController);

    return pMeshRoot;
}
//----------------------------------------------------------------------------
void SEColladaScene::ProcessControllers()
{
    int iInstanceControllerCount = (int)m_InstanceControllers.size();
    for( int i = 0; i < iInstanceControllerCount; i++ )
    {
        SEColladaInstanceController* pIController = m_InstanceControllers[i];
        SEColladaInstanceController::ControllerType eControllerType = 
            pIController->GetControllerType();
        if( eControllerType == SEColladaInstanceController::CT_SKIN )
        {
            ProcessSkin(pIController);
        }
        else if( eControllerType == SEColladaInstanceController::CT_MORPH )
        {
            ProcessMorph(pIController);
        }
    }
}
//----------------------------------------------------------------------------
void SEColladaScene::ProcessSkin(SEColladaInstanceController* pIController)
{
    SE_ASSERT( pIController );

    SENode* pMeshRoot = pIController->GetMeshRoot();
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
    SENode** apBones = 0;
    if( pDomNameArray )
    {
        iBoneCount = (int)pDomNameArray->getCount();
        apBones = SE_NEW SENode*[iBoneCount];

        for( int iB = 0; iB < iBoneCount; iB++ )
        {
            xsNCName acBoneName = pDomNameArray->getValue()[iB];
            domNode* pDomJoint = GetDomNodeBySID(pDomSkeletonRoot, acBoneName);
            SE_ASSERT( pDomJoint );

            // Try to find this bone node in Swing Engine scene graph.
            SENode* pBone = GetBoneNodeByDomNode(pDomJoint);
            SE_ASSERT( pBone );
            apBones[iB] = pBone;
        }
    }
    else if( pDomIDREFArray )
    {
        iBoneCount = (int)pDomIDREFArray->getCount();
        apBones = SE_NEW SENode*[iBoneCount];

        for( int iB = 0; iB < iBoneCount; iB++ )
        {
            const char* acBoneName = 
                (const char*)pDomIDREFArray->getValue()[iB].getID();

            // Try to find this bone node in Swing Engine scene graph.
            SEObject* pBone = m_spSceneRoot->GetObjectByName(acBoneName);
            SE_ASSERT( pBone );
            apBones[iB] = StaticCast<SENode>(pBone);
        }
    }
    else
    {
        // Should never go to here.
        SE_ASSERT( false );
    }

    // Get all inverse binding matrices applied to the mesh.
    SETransformation* aOffsets = SE_NEW SETransformation[iBoneCount];
    domListOfFloats* pDomIBMatrixData = &pDomIBMatrixSource->getFloat_array(
        )->getValue();
    for( int iB = 0; iB < iBoneCount; iB++ )
    {
        int iBase = 16*iB;
        GetInverseBindingTransformation(aOffsets[iB], pDomIBMatrixData, 
            iBase);
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
        SETriMesh* pSubMesh = StaticCast<SETriMesh>(pMeshRoot->GetChild(iM));

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
                SEVector3f vec3fCurPos = GetTransformedVector(fX, fY, fZ);

                if( vec3fCurPos == 
                    (*(SEVector3f*)pSubMesh->VBuffer->PositionTuple(iAV)) )
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
        SENode** apActiveBones = SE_NEW SENode*[iActiveBoneCount];
        SETransformation* aActiveOffsets = SE_NEW SETransformation[
            iActiveBoneCount];

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
        SEEffect* pSaveEffect = 0;
        for( int i = 0; i < pSubMesh->GetEffectCount(); i++ )
        {
            SEEffect* pTempEffect = pSubMesh->GetEffect(i);
            if( DynamicCast<SEMaterialEffect>(pTempEffect) )
            {
                eSkinEffect = SE_MATERIAL;
                pSaveEffect = pTempEffect;
                break;
            }
            else if( DynamicCast<SEMaterialTextureEffect>(pTempEffect) )
            {
                eSkinEffect = SE_MATERIALTEXTURE;
                pSaveEffect = pTempEffect;
                break;
            }
            else if( DynamicCast<SEDefaultShaderEffect>(pTempEffect ))
            {
                eSkinEffect = SE_DEFAULT;
                pSaveEffect = pTempEffect;
                break;
            }
        }

        // Create a new vertex buffer for the sub-mesh and replace the old
        // one with it.
        SEAttributes tempAttr;
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
        SEVertexBuffer* pVBNew = SE_NEW SEVertexBuffer(tempAttr, 
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
        SEEffect* pNewEffect = 0;
        std::string tempImageName;
        switch( eSkinEffect )
        {
        case SE_DEFAULT:
            pNewEffect = SE_NEW SESkinDefaultEffect(iActiveBoneCount, 
                apActiveBones, aActiveOffsets);
            break;

        case SE_MATERIAL:
            pNewEffect = SE_NEW SESkinMaterialEffect(iActiveBoneCount, 
                apActiveBones, aActiveOffsets);
            break;

        case SE_MATERIALTEXTURE:
            {
                SEMaterialTextureEffect* pMTEffect = 
                    DynamicCast<SEMaterialTextureEffect>(pSaveEffect);
                tempImageName = pMTEffect->GetPImageName(0, 0);

                pNewEffect = SE_NEW SESkinMaterialTextureEffect(
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
void SEColladaScene::ProcessMorph(SEColladaInstanceController*)
{
    // TODO:
}
//----------------------------------------------------------------------------