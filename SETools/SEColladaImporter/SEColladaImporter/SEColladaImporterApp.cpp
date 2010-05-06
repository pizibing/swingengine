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

#include "stdafx.h"
#include "SEColladaImporterApp.h"

using namespace Swing;

//----------------------------------------------------------------------------
ColladaImporterApp::ColladaImporterApp()
{
}
//----------------------------------------------------------------------------
ColladaImporterApp::~ColladaImporterApp()
{
}
//----------------------------------------------------------------------------
void ColladaImporterApp::OnIdle()
{
    AppCuller.ComputeUnculledSet(AppScene);

    AppRenderer->ClearBuffers();
    if( AppRenderer->BeginScene() )
    {
        AppRenderer->DrawScene(AppCuller.GetVisibleSet());

        AppRenderer->EndScene();
    }
    AppRenderer->DisplayBackBuffer();
}
//----------------------------------------------------------------------------
void ColladaImporterApp::CreateScene()
{
    AppScene = SE_NEW SENode;
    AppWireframe = SE_NEW SEWireframeState;
    AppWireframe->Enabled = false;
    AppScene->AttachGlobalState(AppWireframe);

    AppScene->UpdateGS();
    AppScene->UpdateRS();

    AppCuller.SetCamera(AppCamera);
    AppCuller.ComputeUnculledSet(AppScene);

    m_pImageConverter = SE_NEW SEImageConverter(
        ((SEDX9Renderer*)AppRenderer)->GetDevice());
    m_pColladaScene = SE_NEW SEColladaScene(m_pImageConverter);
}
//----------------------------------------------------------------------------
void ColladaImporterApp::DestroyScene()
{
    AppScene = 0;
    SceneLoaded = 0;
    AppWireframe = 0;

    SE_DELETE m_pColladaScene;
    SE_DELETE m_pImageConverter;
}
//----------------------------------------------------------------------------
void ColladaImporterApp::OnSave(const char* acFilename)
{
    SEStream tempOStream;
    tempOStream.Insert(SceneLoaded);
    tempOStream.Save(acFilename);

    int iImageCount = m_pColladaScene->GetImageCount();
    for( int i = 0; i < iImageCount; i++ )
    {
        SEImage* pImage = m_pColladaScene->GetImage(i);
        const char* acFilename = pImage->GetName().c_str();
        pImage->Save(acFilename);
    }
}
//----------------------------------------------------------------------------
void ColladaImporterApp::OnOpenFile(const char* acFilename)
{
    Swing::SESystem::SE_Strcpy(m_acFilename, 256, acFilename);

    m_pColladaScene->Load(acFilename);
    SceneLoaded = m_pColladaScene->GetScene();
    AppScene->AttachChild(SceneLoaded);
}
//----------------------------------------------------------------------------