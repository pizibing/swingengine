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

#include "SESceneEditorPCH.h"
#include "SESceneEditorApplication.h"
#include "MainForm.h"

using namespace Swing;
using namespace Swing::Tools::SceneEditor;

//---------------------------------------------------------------------------
SESceneEditorApplication::SESceneEditorApplication(MainForm^ thForm)
{
    m_thAppMainForm = thForm;

    // Create main renderer.
    m_pMainRenderer = SE_NEW SEDX9Renderer(
        (HWND)(int)(thForm->MainRenderingWindow->Handle), 
        SEFrameBuffer::FT_FORMAT_RGBA, 
        SEFrameBuffer::DT_DEPTH_24,
        SEFrameBuffer::ST_STENCIL_8, 
        SEFrameBuffer::BT_BUFFERED_DOUBLE, 
        SEFrameBuffer::MT_SAMPLING_NONE, 
        thForm->MainRenderingWindow->Width, 
        thForm->MainRenderingWindow->Height);
    m_pMainRenderer->SetClearColor(SEColorRGBA(0.5f, 0.5f, 0.5f, 1.0f));

    // Initialize shader program catalog.
    if( !SEVertexProgramCatalog::GetActive() || 
        !SEPixelProgramCatalog::GetActive() || 
        !SEDX9ProgramInterfaceCatalog::GetActive() )
    {
        throw gcnew NullReferenceException(
            "Initializing shader program catalog");
    }
    SEVertexProgramCatalog::GetActive()->SetRenderer(m_pMainRenderer);
    SEPixelProgramCatalog::GetActive()->SetRenderer(m_pMainRenderer);
    SEDX9ProgramInterfaceCatalog::GetActive()->SetRenderer(
        (SEDX9Renderer*)m_pMainRenderer);

    // Create main camera.
    m_pMainCamera = SE_NEW SECamera;
    m_pMainRenderer->SetCamera(m_pMainCamera);
    float fDMin = 1.0f;
    float fDMax = 1000.0f;
    float fRMax = 0.55f * fDMin;
    float fRMin = -fRMax;
    float fUMax = 0.4125f * fDMin;
    float fUMin = -fUMax;
    m_pMainCamera->SetFrustum(fRMin, fRMax, fUMin, fUMax, fDMin, fDMax);
    SEVector3f tempCLoc(0.0f, 5.0f, -30.0f);
    SEVector3f tempCDir(0.0f, 0.0f, 1.0f);
    SEVector3f tempCUp(0.0f, 1.0f, 0.0f);
    SEVector3f tempCRight = tempCUp.Cross(tempCDir);
    m_pMainCamera->SetFrame(tempCLoc, tempCRight, tempCUp, tempCDir);

    // Create main culler.
    m_pMainCuller = SE_NEW SECuller;
    m_pMainCuller->SetCamera(m_pMainCamera);

    // Create scene root.
    m_pSceneRoot = SE_NEW SENode;
}
//---------------------------------------------------------------------------
SESceneEditorApplication::~SESceneEditorApplication()
{
    // Release scene root.
    SE_DELETE m_pSceneRoot;
    m_pSceneRoot = 0;

    // Release main culler.
    SE_DELETE m_pMainCuller;
    m_pMainCuller = 0;

    // Release main camera.
    m_pMainRenderer->SetCamera(0);
    SE_DELETE m_pMainCamera;
    m_pMainCamera = 0;

    // Terminate shader program catalog.
    if( !SEVertexProgramCatalog::GetActive() || 
        !SEPixelProgramCatalog::GetActive() || 
        !SEDX9ProgramInterfaceCatalog::GetActive() )
    {
        throw gcnew NullReferenceException(
            "Terminating shader program catalog");
    }
    SEVertexProgramCatalog::GetActive()->SetRenderer(0);
    SEPixelProgramCatalog::GetActive()->SetRenderer(0);
    SEDX9ProgramInterfaceCatalog::GetActive()->SetRenderer(0);

    // Release main renderer.
    SE_DELETE m_pMainRenderer;
    m_pMainRenderer = 0;
}
//---------------------------------------------------------------------------
MainForm^ SESceneEditorApplication::AppMainForm::get()
{
    return m_thAppMainForm;
}
//---------------------------------------------------------------------------
SERenderer* SESceneEditorApplication::MainRenderer::get()
{
    return m_pMainRenderer;
}
//---------------------------------------------------------------------------
SECamera* SESceneEditorApplication::MainCamera::get()
{
    return m_pMainCamera;
}
//---------------------------------------------------------------------------
SECuller* SESceneEditorApplication::MainCuller::get()
{
    return m_pMainCuller;
}
//---------------------------------------------------------------------------
void SESceneEditorApplication::OnIdle(Object^, EventArgs^)
{
    m_pMainCuller->ComputeUnculledSet(m_pSceneRoot);

    m_pMainRenderer->ClearBuffers();
    if( m_pMainRenderer->BeginScene() )
    {
        m_pMainRenderer->DrawScene(m_pMainCuller->GetVisibleSet());

        m_pMainRenderer->EndScene();
    }
    m_pMainRenderer->DisplayBackBuffer();
}
//---------------------------------------------------------------------------