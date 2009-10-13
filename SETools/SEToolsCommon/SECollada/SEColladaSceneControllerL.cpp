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
	ColladaInstanceController* pIController = 
		SE_NEW ColladaInstanceController;
	m_InstanceControllers.push_back(pIController);

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

	// Try to find the controller that encapsulates the geometry object.
	xsAnyURI& rUrlType  = spLib->getUrl();
	domElement* pDomElement = rUrlType.getElement();
	domController* pDomController = (domController*)pDomElement;
	pIController->Controller = pDomController;

	// Try to find the skeleton root that will be used to control the 
	// geometry object. There could be more than one skeleton root, but 
	// for now we just support one.
	domInstance_controller::domSkeleton_Array& rDomSkeletonArray = 
		spLib->getSkeleton_array();
	if( rDomSkeletonArray.getCount() > 1 )
	{
		ToolSystem::SE_DebugOutput("There are more than one skeleton");
	}
	if( rDomSkeletonArray.getCount() > 0 )
	{
		domNode* pDomSkeletonRoot = 
			(domNode*)(domElement*)rDomSkeletonArray[0]->getValue(
			).getElement();

		pIController->SkeletonRoot = pDomSkeletonRoot;
	}

	return 0;
}
//----------------------------------------------------------------------------