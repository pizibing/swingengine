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
ColladaScene::TransformType ColladaScene::GetTransformType(char* acType)
{
    // Return a enum for the type of transform, things that are not transforms 
    // like <instance_xxx> are returned as TT_UNKNOWN and will be handled by 
    // other code.

    if( strcmp(acType, "scale") == 0 )
    {
        return TT_SCALE;
    }
    else if( strcmp(acType, "rotate") == 0 )
    {
        return TT_ROTATE;
    }
    else if( strcmp(acType, "translate") == 0 )
    {
        return TT_TRANSLATE;
    }
    else if( strcmp(acType, "matrix") == 0 )
    {
        return TT_MATRIX;
    }
    else if( strcmp(acType, "lookat") == 0 )
    {
        return TT_LOOKAT;
    }
    else if( strcmp(acType, "skew") == 0 )
    {
        return TT_SKEW;
    }
    else
    {
        return TT_UNKNOWN;
    }
}
//----------------------------------------------------------------------------
void ColladaScene::GetLocalTransformation(Node* pNode, domNodeRef spDomNode)
{
    // Load the node transformations as they are to be able to 
    // handle any matrix stack configurations independant of the tools.
    std::vector<Transformation*> tempTransSequence;
    int iNodeContentCount = (int)spDomNode->getContents().getCount();
    for( int i = 0; i < iNodeContentCount; i++ )
    {
        // Get the component type string.
        char* acSID = 0;
        Transformation* pTransform = 0;
        char* acTypeName = (char*)spDomNode->getContents()[i]->getTypeName();
        TransformType eTType = GetTransformType(acTypeName);

        switch( eTType )
        {
        case TT_SCALE:
            {
                pTransform = SE_NEW Transformation;

                domScale* pDomScale = 
                    (domScale*)(domElement*)spDomNode->getContents()[i];
                domFloat3& rDomFloat3 = pDomScale->getValue();
                SE_ASSERT( rDomFloat3.getCount() == 3 );
                
                // Get the scale data.
                Vector3f vec3fScale;
                vec3fScale.X = (float)rDomFloat3[0];
                vec3fScale.Y = (float)rDomFloat3[1];
                vec3fScale.Z = (float)rDomFloat3[2];

                pTransform->SetScale(vec3fScale);

                acSID = (char*)pDomScale->getSid();
                if( acSID )
                {
                    // TODO:
                    // This will be used to bind to an animation later.
                }

                tempTransSequence.push_back(pTransform);
            }
            break;

        case TT_ROTATE:
            {
                pTransform = SE_NEW Transformation;

                domRotate* pDomRotate = 
                    (domRotate*)(domElement*)spDomNode->getContents()[i];
                domFloat4& rDomFloat4 = pDomRotate->getValue();
                SE_ASSERT( rDomFloat4.getCount() == 4 );

                // Get the rotation data.
                Vector3f vec3fRotAxis;
                vec3fRotAxis.X = (float)rDomFloat4[0];
                vec3fRotAxis.Y = (float)rDomFloat4[1];
                vec3fRotAxis.Z = (float)rDomFloat4[2];
                float fRotAngle = (float)rDomFloat4[3];

                Matrix3f mat3fR(vec3fRotAxis, fRotAngle);
                pTransform->SetRotate(mat3fR);

                acSID = (char*)pDomRotate->getSid();
                if( acSID )
                {
                    // TODO:
                    // This will be used to bind to an animation later.
                }
                
                tempTransSequence.push_back(pTransform);
            }
            break;

        case TT_TRANSLATE:
            {
                pTransform = SE_NEW Transformation;

                domTranslate* pDomTranslate = 
                    (domTranslate*)(domElement*)spDomNode->getContents()[i];
                domFloat3& rDomFloat3 = pDomTranslate->getValue();
                SE_ASSERT( rDomFloat3.getCount() == 3 );

                // Get the transation data.
                Vector3f vec3fTrans;
                vec3fTrans.X = (float)rDomFloat3[0];
                vec3fTrans.Y = (float)rDomFloat3[1];
                vec3fTrans.Z = (float)rDomFloat3[2];

                pTransform->SetTranslate(vec3fTrans);

                acSID = (char*)pDomTranslate->getSid();
                if( acSID )
                {
                    // TODO:
                    // This will be used to bind to an animation later.
                }
                
                tempTransSequence.push_back(pTransform);
            }
            break;

        case TT_MATRIX:
            {
                // TODO:
                // Support this transform.
            }
            break;

        case TT_LOOKAT:
            {
                // TODO:
                // Support this transform.
            }
            break;

        case TT_SKEW:
            // TODO:
            // Support this transform.
            ToolSystem::SE_DebugOutput("Skew transforms not supported yet");
            continue;

        case TT_UNKNOWN:
            // If it's not a transform, it's an instance or something else 
            // that will be handled later.
            continue; 
        }
    }

    int iTransCount = (int)tempTransSequence.size();
    for( int i = iTransCount - 1; i >= 0 ; i-- )
    {
        Transformation* pTransformation = tempTransSequence[i];
        pNode->Local.Product(pNode->Local, *pTransformation);

        SE_DELETE pTransformation;
    }
}
//----------------------------------------------------------------------------
Node* ColladaScene::LoadNode(domNodeRef spDomNode, Node* pParentNode)
{
    if( !spDomNode )
    {
        return 0;
    }

    xsID strNodeName = spDomNode->getId();
    const char* acNodeName = (const char*)strNodeName;
    Node* pNode = GetNode(acNodeName);
    // This node is already in our node catalog.
    if( pNode )
    {
        return pNode;
    }

    ToolSystem::SE_DebugOutput("ColladaScene::Loading Scene Node %s", 
        acNodeName);

    pNode = SE_NEW Node;
    pNode->SetName(acNodeName);

    GetLocalTransformation(pNode, spDomNode);

    // Process Instance Geometries.
    domInstance_geometry_Array& rInstanceGeometryArray = 
        spDomNode->getInstance_geometry_array();
    int iInstanceGeometryCount = (int)rInstanceGeometryArray.getCount();
    for( int i = 0; i < iInstanceGeometryCount; i++ )
    {
        TriMesh* pMesh = LoadInstanceGeometry(rInstanceGeometryArray[i]);
        if ( !pMesh )
        {
            continue;
        }

        pNode->AttachChild(pMesh);
        m_Geometries.push_back(pMesh);
    }

    //// Process Instance Controllers 
    //size_t uiInstanceControllerCount = node->getInstance_controller_array().getCount();
    //for (CrtUInt i = 0; i < uiInstanceControllerCount; i++)
    //{
    //	domInstance_controller *icontroller  = node->getInstance_controller_array()[i];
    //	CrtInstanceController * instanceController = ReadInstanceController(icontroller);
    //	if (instanceController==NULL) //if instance Controller can not be created, skip to the next one
    //		continue;

    //	instanceController->Parent = crtNode;
    //	crtNode->InstanceControllers.push_back(instanceController);
    //	ControllerInstances.push_back(instanceController);
    //}

    //// Process Instance Lights 
    //size_t uiInstanceLightCount = node->getInstance_light_array().getCount();
    //for (CrtUInt i = 0; i < uiInstanceLightCount; i++)
    //{
    //	CrtInstanceLight * instanceLight = ReadInstanceLight(node->getInstance_light_array()[i]);
    //	if (instanceLight) 
    //	{
    //		instanceLight->Parent = crtNode;
    //		crtNode->InstanceLights.push_back(instanceLight);
    //		LightInstances.push_back(instanceLight);
    //	}
    //}

    //// Process Instance Cameras 
    //size_t uiInstanceCameraCount = node->getInstance_camera_array().getCount();
    //for (CrtUInt i = 0; i < uiInstanceCameraCount; i++)
    //{	
    //	CrtInstanceCamera *instanceCamera = ReadInstanceCamera(node->getInstance_camera_array()[i]);
    //	if (instanceCamera) 
    //	{
    //		instanceCamera->Parent = crtNode;
    //		CameraInstances.push_back(instanceCamera);
    //	}
    //}

    //// add to parent 
    //parentNode->AddChild( crtNode ); 

    //// read children 
    //size_t uiChildNodeCount = node->getNode_array().getCount();
    //for (CrtUInt i = 0; i < uiChildNodeCount; i++)
    //{
    //	// read in each child an recursively it's children 
    //	CrtNode * readnode  = ReadNode( node->getNode_array()[i], crtNode );
    //	if (readnode) 
    //		Nodes[readnode->GetId()] = readnode;
    //}

    //// read children <instance_nodes>, can be 0 or more 
    //size_t uiChildInstanceNodeCount = node->getInstance_node_array().getCount();
    //for (CrtUInt i = 0; i < uiChildInstanceNodeCount; i++)
    //{
    //	// read in each child an recursively it's children 
    //	domInstance_node * instance_node = node->getInstance_node_array()[i];
    //	domNode * urlnode = (domNode*) (domElement*) instance_node->getUrl().getElement();
    //	if (urlnode) 
    //	{
    //		CrtNode * readnode = ReadNode( urlnode, crtNode );
    //		if (readnode) 
    //			Nodes[readnode->GetId()] = readnode;
    //	}
    //}

    return pNode;
}
//----------------------------------------------------------------------------