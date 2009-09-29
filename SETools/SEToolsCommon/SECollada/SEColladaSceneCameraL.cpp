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
Camera* ColladaScene::GetCamera(const char* acName)
{
    if( !acName )
    {
        return 0;
    }

    for( int i = 0; i < (int)m_Cameras.size(); i++ )
    {
        if( strcmp(m_Cameras[i]->GetName(), acName) == 0 )
        {
            return m_Cameras[i];
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
Camera* ColladaScene::LoadCamera(domCameraRef spDomCamera)
{
    xsID strCameraID = spDomCamera->getId();
    if( !strCameraID )
    {
        return 0;
    }

    Camera* pCamera = GetCamera((const char*)strCameraID);
    if( pCamera )
    {
        // This camera is already in our camera catalog.
        return pCamera;
    }

    ToolSystem::SE_DebugOutput("Add new camera %s", (const char*)strCameraID);

    domCamera* pDomCamera = (domCamera*)(domElement*)spDomCamera;
    if( pDomCamera )
    {	
        // Create a Swing Engine camera.
        pCamera = SE_NEW Camera;
        pCamera->SetName((const char*)strCameraID);

    //	// Get the optics
    //	domCamera::domOptics *cameraOptics = CameraElement->getOptics();
    //	
    //	// Get the optics common profile technique
    //	domCamera::domOptics::domTechnique_common *cameraCommonTechnique = cameraOptics->getTechnique_common();
    //	
    //	// Get the get the perspective and orthographic common profiles (if they exist)
    //	domCamera::domOptics::domTechnique_common::domPerspective *cameraPerspective = cameraCommonTechnique->getPerspective();
    //	domCamera::domOptics::domTechnique_common::domOrthographic *cameraOrthographic = cameraCommonTechnique->getOrthographic();
    //	
    //	// Setup camera parameters, note we have to check if a parameter is there before doing getValue
    //	// Parameters not in the COLLADA data will be left at the CrtCamera defaults
    //	if(cameraPerspective)
    //	{
    //		if(cameraPerspective->getXfov())
    //			newCam->SetXFov((float)(cameraPerspective->getXfov()->getValue()));
    //		if(cameraPerspective->getYfov())
    //			newCam->SetYFov((float)(cameraPerspective->getYfov()->getValue()));
    //		if(cameraPerspective->getAspect_ratio())
    //			newCam->SetAspect((float)(cameraPerspective->getAspect_ratio()->getValue()));
    //		if(cameraPerspective->getZnear())
    //			newCam->SetZNear((float)(cameraPerspective->getZnear()->getValue()));
    //		if(cameraPerspective->getZfar())
    //			newCam->SetZFar((float)(cameraPerspective->getZfar()->getValue()));
    //		// !!!GAC force Znear to be >= 1.0 to avoid rendering problems
    //		if( newCam->GetZNear() < 1.0f)
    //			newCam->SetZNear(1.0f);
    //	}
    //	if(cameraOrthographic)
    //	{
    //		// Setup orthographic camera
    //		CrtPrint("Support for orthograph cameras incomplete, this camera will probably look odd\n");
    //		if(cameraOrthographic->getXmag())
    //			newCam->SetXMag((float)(cameraOrthographic->getXmag()->getValue()));
    //		if(cameraOrthographic->getYmag())
    //			newCam->SetYMag((float)(cameraOrthographic->getYmag()->getValue()));
    //		if(cameraOrthographic->getAspect_ratio())
    //			newCam->SetAspect((float)(cameraOrthographic->getAspect_ratio()->getValue()));
    //		if(cameraOrthographic->getZnear())
    //			newCam->SetZNear((float)(cameraOrthographic->getZnear()->getValue()));
    //		if(cameraOrthographic->getZfar())
    //			newCam->SetZFar((float)(cameraOrthographic->getZfar()->getValue()));
    //		// !!!GAC force Znear to be >= 1.0 to avoid rendering problems
    //		if( newCam->GetZNear() < 1.0f)
    //			newCam->SetZNear(1.0f);
    //	}

        m_Cameras.push_back(pCamera);

        return pCamera;
    }

    return 0;
}
//----------------------------------------------------------------------------
Camera* ColladaScene::LoadInstanceCamera(
    domInstance_cameraRef spDomInstanceCamera)
{
    xsAnyURI& rUrlType  = spDomInstanceCamera->getUrl();
    domElement* pDomElement = (domElement*) rUrlType.getElement();
    if( !pDomElement )
    {
        // This instance light is not found, skip to the next one.
        ToolSystem::SE_DebugOutput("Can't find this camera:%s", 
            rUrlType.getURI());

        return 0;
    }

    Camera* pCamera = LoadCamera((domCamera*)pDomElement);

    return pCamera;
}
//----------------------------------------------------------------------------