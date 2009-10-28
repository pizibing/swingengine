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
Node* ColladaScene::GetNode(const char* acName)
{
    if( !acName )
    {
        return 0;
    }

    if( m_Nodes.empty() )
    {
        return 0;
    }

    return m_Nodes[acName];
}
//----------------------------------------------------------------------------
void ColladaScene::GetLocalTransSequence(Node* pNode, domNodeRef spDomNode,
    std::vector<ColladaTransformation*>& rColladaTransSequence)
{
    // Get the node transformations as they are to be able to handle any 
    // matrix stack configurations independant of the tools.

    int iNodeContentCount = (int)spDomNode->getContents().getCount();
    for( int i = 0; i < iNodeContentCount; i++ )
    {
        char* acSID = 0;
        ColladaTransformation* pColladaTransform = 0;

        // Get the component type string.
        char* acTypeName = (char*)spDomNode->getContents()[i]->getTypeName();
        ColladaTransformation::TransformType eTType = 
            ColladaTransformation::GetTransformType(acTypeName);

        switch( eTType )
        {
        case ColladaTransformation::TT_SCALE:
            {
                domScale* pDomScale = 
                    (domScale*)(domElement*)spDomNode->getContents()[i];
                domFloat3& rDomFloat3 = pDomScale->getValue();
                SE_ASSERT( rDomFloat3.getCount() == 3 );

                // Create a COLLADA transformation object.
                pColladaTransform = SE_NEW ColladaTransformation;

                acSID = (char*)pDomScale->getSid();
                if( acSID )
                {
                    // This will be used to bind to an animation later.
                    pColladaTransform->SetName(acSID);
                }
                pColladaTransform->TransType = eTType;
                pColladaTransform->SRTData = Vector4f((float)rDomFloat3[0], 
                    (float)rDomFloat3[1], (float)rDomFloat3[2], 0.0f);
                rColladaTransSequence.push_back(pColladaTransform);
            }
            break;

        case ColladaTransformation::TT_ROTATE:
            {
                domRotate* pDomRotate = 
                    (domRotate*)(domElement*)spDomNode->getContents()[i];
                domFloat4& rDomFloat4 = pDomRotate->getValue();
                SE_ASSERT( rDomFloat4.getCount() == 4 );

                // Create a COLLADA transformation object.
                pColladaTransform = SE_NEW ColladaTransformation;

                acSID = (char*)pDomRotate->getSid();
                if( acSID )
                {
                    // This will be used to bind to an animation later.
                    pColladaTransform->SetName(acSID);
                }
                pColladaTransform->TransType = eTType;
                pColladaTransform->SRTData = Vector4f((float)rDomFloat4[0], 
                    (float)rDomFloat4[1], (float)rDomFloat4[2], 
                    (float)rDomFloat4[3]);
                rColladaTransSequence.push_back(pColladaTransform);
            }
            break;

        case ColladaTransformation::TT_TRANSLATE:
            {
                domTranslate* pDomTranslate = 
                    (domTranslate*)(domElement*)spDomNode->getContents()[i];
                domFloat3& rDomFloat3 = pDomTranslate->getValue();
                SE_ASSERT( rDomFloat3.getCount() == 3 );

                // Create a COLLADA transformation object.
                pColladaTransform = SE_NEW ColladaTransformation;
                acSID = (char*)pDomTranslate->getSid();
                if( acSID )
                {
                    // This will be used to bind to an animation later.
                    pColladaTransform->SetName(acSID);
                }
                pColladaTransform->TransType = eTType;
                pColladaTransform->SRTData = Vector4f((float)rDomFloat3[0], 
                    (float)rDomFloat3[1], (float)rDomFloat3[2], 0.0f);
                rColladaTransSequence.push_back(pColladaTransform);
            }
            break;

        case ColladaTransformation::TT_MATRIX:
            {
                // TODO:
                // Support this transformation.
                SE_ASSERT( false );
            }
            break;

        case ColladaTransformation::TT_LOOKAT:
            {
                // TODO:
                // Support this transformation.
                SE_ASSERT( false );
            }
            break;

        case ColladaTransformation::TT_SKEW:
            {
                // TODO:
                // Support this transformation.
                SE_ASSERT( false );
            }
            break;

        case ColladaTransformation::TT_UNKNOWN:
            // If it's not a transformation, it's an instance or something 
            // else that will be handled later.
            continue; 
        }

        // Now we want to find out whether or not this transformation is 
        // affected by a COLLADA animation object.
        for( int j = 0; j < (int)m_Animations.size(); j++ )
        {
            ColladaAnimation* pAnimation = m_Animations[j];
            if( pAnimation->FoundTarget )
            {
                continue;
            }

            bool bFoundTarget = false;
            for( int k = 0; k < (int)pAnimation->Channels.size(); k++ )
            {
                const char* acTargetID = pAnimation->Channels[k]->TargetID;
                const char* acTargetSID = pAnimation->Channels[k]->TargetSID;
                const char* acNodeID = pNode->GetName();
                if( acTargetID && acTargetSID && acNodeID && acSID )
                {
                    if( strcmp(acTargetID, acNodeID) == 0 &&
                        strcmp(acTargetSID, acSID) == 0 )
                    {
                        pAnimation->FoundTarget = true;
                        pColladaTransform->Animation = pAnimation;
                        pColladaTransform->AttachChannel(k);
                        bFoundTarget = true;

                        break;
                    }
                }
            }
            if (bFoundTarget)
            {
                break;
            }
        }
    }
}
//----------------------------------------------------------------------------
Transformation ColladaScene::GetLocalTransformation(
    std::vector<ColladaTransformation*>& rColladaTransSequence,
    float fTime)
{
    Transformation tempRes;

    // Update each animated COLLADA transformation.
    int iTransCount = (int)rColladaTransSequence.size();
    for( int i = 0; i < iTransCount; i++ )
    {
        ColladaAnimation* pAnimation = rColladaTransSequence[i]->Animation;
        if( pAnimation )
        {
            // A single transform may have serveral animated channels attached.
            int iChannelCount = rColladaTransSequence[i]->GetChannelCount();
            for( int j = 0; j < iChannelCount; j++ )
            {
                int iChannelID = rColladaTransSequence[i]->GetChannel(j);

                // Interpolate the value based on the element that is to be 
                // targeted and the key frame info attached at loading time.
                pAnimation->AnimateChannel(rColladaTransSequence[i], 
                    pAnimation->Channels[iChannelID]->TargetType, iChannelID,
                    fTime);
            }
        }
    }

    for( int i = iTransCount - 1; i >= 0 ; i-- )
    {
        Transformation tempTransform = 
            rColladaTransSequence[i]->ToTransformation();

        tempRes.Product(tempRes, tempTransform);
    }

    return tempRes;
}
//----------------------------------------------------------------------------
Node* ColladaScene::LoadNode(domNodeRef spDomNode, Node* pParentNode)
{
    if( !spDomNode )
    {
        return 0;
    }

    xsID strNodeID = spDomNode->getId();
    const char* acNodeID = (const char*)strNodeID;
    Node* pNode = GetNode(acNodeID);
    if( pNode )
    {
        // This node is already in our node catalog.
        return pNode;
    }

    ToolSystem::SE_DebugOutput("ColladaScene::Loading Scene Node %s", 
        acNodeID);

    // Create a Swing Engine node to handle the COLLADA node's information.
    pNode = SE_NEW Node;
    pNode->SetName(acNodeID);

    // Process local transformation sequence.
    std::vector<ColladaTransformation*> tempColladaTransSequence;
    GetLocalTransSequence(pNode, spDomNode, tempColladaTransSequence);

    // Get node's combined local transformation base on local transformation 
    // sequence at animation's start time(if there is any).
    pNode->Local = GetLocalTransformation(tempColladaTransSequence, 0.0f);

    // Process keyframe animation.
    // TODO:
    // Support keyframe animation option.
    BuildKeyFrameController(pNode, tempColladaTransSequence);

    // Release the local transformation sequence.
    for( int i = 0; i < (int)tempColladaTransSequence.size(); i++ )
    {
        SE_DELETE tempColladaTransSequence[i];
    }

    // Process joint.
    domNodeType eNodeType = spDomNode->getType();
    if( eNodeType == NODETYPE_JOINT )
    {
        TriMesh* pJointMesh = CreateJointMesh(acNodeID);
        pNode->AttachChild(pJointMesh);

        Bone tempBone;
        tempBone.BoneNode = pNode;
        tempBone.BoneDomNode = (domNode*)spDomNode;
        m_Bones.push_back(tempBone);
    }

    // Process instance geometries.
    domInstance_geometry_Array& rInstanceGeometryArray = 
        spDomNode->getInstance_geometry_array();
    int iInstanceGeometryCount = (int)rInstanceGeometryArray.getCount();
    for( int i = 0; i < iInstanceGeometryCount; i++ )
    {
        Node* pMeshRoot = LoadInstanceGeometry(rInstanceGeometryArray[i]);
        if( !pMeshRoot )
        {
            continue;
        }

        pNode->AttachChild(pMeshRoot);
        m_Geometries.push_back(pMeshRoot);
    }

    // Process instance controllers.
    // Instance controller is similar to instance geometry. A skin controller
    // is a skinned geometry controlled by a node hierarchy called skeleton.
    // We should set bone index, bone weight, and skeleton node reference for
    // skinned geometry. But now we haven't finished building of Swing Engine
    // scene graph, so the processing of assigning skinning data is deferred.
    // TODO:
    // Support morph controller.
    domInstance_controller_Array& rInstanceControllerArray = 
        spDomNode->getInstance_controller_array();
    int iInstanceControllerCount = (int)rInstanceControllerArray.getCount();
    for( int i = 0; i < iInstanceControllerCount; i++ )
    {
        Node* pMeshRoot = LoadInstanceController(rInstanceControllerArray[i]);
        if( !pMeshRoot )
        {
            continue;
        }

        pNode->AttachChild(pMeshRoot);
        m_Geometries.push_back(pMeshRoot);
    }


    // Process instance lights.
    // We should set orientation(position,direction) for spot light, and set 
    // position for point light base on their parent node's orientation. But 
    // now we haven't finished building of Swing Engine scene graph, so the 
    // processing of assigning orientation is deferred.
    domInstance_light_Array& rDomInstanceLightArray = 
        spDomNode->getInstance_light_array();
    int iInstanceLightCount = (int)rDomInstanceLightArray.getCount();
    for( int i = 0; i < iInstanceLightCount; i++ )
    {
        ColladaInstanceLight* pInstanceLight = 
            LoadInstanceLight(pNode, rDomInstanceLightArray[i]);
        if( pInstanceLight ) 
        {
            Light* pLight = pInstanceLight->GetLight();
            pNode->AttachLight(pLight);
            m_InstanceLights.push_back(pInstanceLight);
        }
    }

    // Process instance cameras.
    // We should set orientation(E,R,U,D) for camera base on its parent node's
    // orientation. But now we haven't finished building of Swing Engine scene
    // graph, so the processing of assigning orientation is deferred.
    domInstance_camera_Array& rDomInstanceCameraArray = 
        spDomNode->getInstance_camera_array();
    int iInstanceCameraCount = (int)rDomInstanceCameraArray.getCount();
    for( int i = 0; i < iInstanceCameraCount; i++ )
    {
        ColladaInstanceCamera* pInstanceCamera = 
            LoadInstanceCamera(pNode, rDomInstanceCameraArray[i]);
        if( pInstanceCamera )
        {
            m_InstanceCameras.push_back(pInstanceCamera);
        }
    }

    // Add current node to Swing Engine scene graph.
    pParentNode->AttachChild(pNode);

    // Load all children, can be zero or more.
    int iChildNodeCount = (int)spDomNode->getNode_array().getCount();
    for( int i = 0; i < iChildNodeCount; i++ )
    {
        // Load each child an recursively it's children.
        Node* pChildNode = LoadNode(spDomNode->getNode_array()[i], pNode);
        if( pChildNode )
        {
            String strChildName = pChildNode->GetName();
            m_Nodes[(const char*)strChildName] = pChildNode;
        }
    }

    // Load all children <instance_nodes>, can be zero or more.
    domInstance_node_Array& rInstanceNodeArray = 
        spDomNode->getInstance_node_array();
    int iChildInstanceNodeCount = (int)rInstanceNodeArray.getCount();
    for( int i = 0; i < iChildInstanceNodeCount; i++ )
    {
        // Load each child an recursively it's children.
        domInstance_node* pDomInstanceNode = rInstanceNodeArray[i];
        domNodeRef spDomChildNode = 
            (domNode*)(domElement*)pDomInstanceNode->getUrl().getElement();
        if( spDomChildNode ) 
        {
            Node* pChildNode = LoadNode(spDomChildNode, pNode);
            if( pChildNode )
            {
                String strChildName = pChildNode->GetName();
                m_Nodes[(const char*)strChildName] = pChildNode;
            }
        }
    }

    return pNode;
}
//----------------------------------------------------------------------------
TriMesh* ColladaScene::CreateJointMesh(const char* acJointName, float fSize)
{
    SE_ASSERT( fSize >= 0.0f );

    String strJointName("Joint_");
    if( acJointName )
    {
        strJointName += acJointName;
    }
    else
    {
        strJointName += "unnamed";
    }

    Attributes tempAttr;
    tempAttr.SetPositionChannels(3);
    StandardMesh tempSM(tempAttr);
    TriMesh* pJointMesh = tempSM.Box(fSize, fSize, fSize);
    pJointMesh->SetName(strJointName);
    pJointMesh->AttachEffect(SE_NEW DefaultShaderEffect);

    return pJointMesh;
}
//----------------------------------------------------------------------------
domNode* ColladaScene::GetDomNodeBySID(domNodeRef spDomNode, xsNCName strSID)
{
    if( !spDomNode || !strSID )
    {
        return 0;
    }

    xsNCName strCurSID = spDomNode->getSid();
    if( strCurSID )
    {
        if( strcmp((const char*)strSID, (const char*)strCurSID) == 0 )
        {
            return (domNode*)spDomNode;
        }
    }

    int iChildNodeCount = (int)spDomNode->getNode_array().getCount();
    for( int i = 0; i < iChildNodeCount; i++ )
    {
        domNode* pFound = GetDomNodeBySID(spDomNode->getNode_array()[i], 
            strSID);
        if( pFound )
        {
            return pFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
Node* ColladaScene::GetBoneNodeByDomNode(domNode* pDomNode)
{
    if( !pDomNode )
    {
        return 0;
    }

    for( int i = 0; i < (int)m_Bones.size(); i++ )
    {
        if( m_Bones[i].BoneDomNode == pDomNode )
        {
            return m_Bones[i].BoneNode;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------