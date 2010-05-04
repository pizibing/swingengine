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
    m_thAppMainForm->App = this;

    m_bFirstEntering = true;
    m_bAllowCameraTrn = true;
    m_bAllowCameraRot = false;
    m_bAllowCameraVHTrn = false;
    m_bAllowCameraTrackBall = false;
    m_fOrthogonalFactor = 2.0f;
    m_fCameraRotSpeed = 0.01f;
    m_fCameraTrnSpeed = 0.2f;
    m_fCameraVHTrnSpeed = 0.01f;

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
        // TODO:
        // Handle this exception.
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
    float fDMin = 0.001f;
    float fDMax = 1000.0f;
    float fRMax = 0.55f * fDMin;
    float fRMin = -fRMax;
    float fUMax = 0.4125f * fDMin;
    float fUMin = -fUMax;
    m_pMainCamera->SetFrustum(fRMin, fRMax, fUMin, fUMax, fDMin, fDMax);
    SEVector3f tempCLoc(0.0f, 1.5f, 0.0f);
    SEVector3f tempCDir(0.0f, 0.0f, 1.0f);
    SEVector3f tempCUp(0.0f, 1.0f, 0.0f);
    SEVector3f tempCRight = tempCUp.Cross(tempCDir);
    m_pMainCamera->SetFrame(tempCLoc, tempCRight, tempCUp, tempCDir);

    // Create main culler.
    m_pMainCuller = SE_NEW SECuller;
    m_pMainCuller->SetCamera(m_pMainCamera);

    // Create scene root.
    m_pSceneRoot = SE_NEW SENode;
    m_pWireframe = SE_NEW SEWireframeState;
    m_pSceneRoot->AttachGlobalState(m_pWireframe);

    // Create COLLADA importer.
    m_pColladaScene = SE_NEW SEColladaScene(
        ((SEDX9Renderer*)m_pMainRenderer)->GetDevice());
}
//---------------------------------------------------------------------------
SESceneEditorApplication::~SESceneEditorApplication()
{
    // Release COLLADA importer.
    SE_DELETE m_pColladaScene;
    m_pColladaScene = 0;

    // Release scene root.
    SE_DELETE m_pSceneRoot;
    m_pWireframe = 0;
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
        // TODO:
        // Handle this exception.
        throw gcnew NullReferenceException(
            "Terminating shader program catalog");
    }
    SEVertexProgramCatalog::GetActive()->SetRenderer(0);
    SEPixelProgramCatalog::GetActive()->SetRenderer(0);
    SEDX9ProgramInterfaceCatalog::GetActive()->SetRenderer(0);

    // Release main renderer.
    SE_DELETE m_pMainRenderer;
    m_pMainRenderer = 0;

    m_thAppMainForm->App = nullptr;
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
void SESceneEditorApplication::LoadFile(String^ thFileName)
{
    if( thFileName == nullptr || thFileName == "" )
    {
        return;
    }

    const char* acFileName = SESceneEditorUtility::StringToNativeCharBuffer(
        thFileName);

    SEStream tempStream;
    SENode* pSceneLoaded = 0;
    bool bLoaded = false;

    bLoaded = tempStream.Load(acFileName);
    if( bLoaded )
    {
        pSceneLoaded = DynamicCast<SENode>(tempStream.GetObjectAt(0));
        if( pSceneLoaded )
        {
            m_pSceneRoot->AttachChild(pSceneLoaded);
            m_pSceneRoot->UpdateGS();
            m_pSceneRoot->UpdateRS();
        }
    }

    SESceneEditorUtility::FreeNativeCharBuffer(acFileName);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// WinForm Event Callbacks
//---------------------------------------------------------------------------
void SESceneEditorApplication::OnOpenToolStripMenuItemClick(Object^, 
    EventArgs^)
{
    OpenFileDialog^ thDialog = gcnew OpenFileDialog;
    thDialog->Filter = "seof|*.seof";
    thDialog->FilterIndex = 1;
    thDialog->RestoreDirectory = true;
    thDialog->ShowDialog();

    LoadFile(thDialog->FileName);
}
//---------------------------------------------------------------------------
void SESceneEditorApplication::OnWindowRenderingMouseDown(Object^, 
    MouseEventArgs^ thEvent)
{
    if( thEvent->Button == MouseButtons::Middle )
    {
        m_bAllowCameraVHTrn = true;
    }
    else if( thEvent->Button == MouseButtons::Left )
    {
    }
    else if( thEvent->Button == MouseButtons::Right )
    {
        m_bAllowCameraRot = true;
    }
}
//---------------------------------------------------------------------------
void SESceneEditorApplication::OnWindowRenderingMouseEnter(Object^, 
    EventArgs^)
{
}
//---------------------------------------------------------------------------
void SESceneEditorApplication::OnWindowRenderingMouseLeave(Object^, 
    EventArgs^)
{
    m_bFirstEntering = true;
}
//---------------------------------------------------------------------------
void SESceneEditorApplication::OnWindowRenderingMouseMove(Object^, 
    MouseEventArgs^ thEvent)
{
    if( m_bFirstEntering )
    {
        m_LastMousePos.X = thEvent->Location.X;
        m_LastMousePos.Y = thEvent->Location.Y;
        m_bFirstEntering = false;
    }
    else
    {
        int iDiffX = thEvent->Location.X - m_LastMousePos.X;
        int iDiffY = thEvent->Location.Y - m_LastMousePos.Y;
        m_LastMousePos = thEvent->Location;

        if( m_bAllowCameraRot && !m_thAppMainForm->UsingPlanform )
        {
            // Camera rotation.

            // Get current orientation of camera.
            SEVector3f tempR = m_pMainCamera->GetRVector();
            SEVector3f tempU = m_pMainCamera->GetUVector();
            SEVector3f tempD = m_pMainCamera->GetDVector();

            // 纵向更新当前摄像机RUD轴姿态.
            SEMatrix3f tempM(tempR, iDiffY * m_fCameraRotSpeed);
            tempR = tempR * tempM;
            tempU = tempU * tempM;
            tempD = tempD * tempM;

            //// 横向更新当前摄像机RUD轴姿态.
            tempM.FromAxisAngle(SEVector3f::UNIT_Y, iDiffX * m_fCameraRotSpeed);
            tempR = tempR * tempM;
            tempU = tempU * tempM;
            tempD = tempD * tempM;
            m_pMainCamera->SetAxes(tempR, tempU, tempD);
        }
        else if( m_bAllowCameraVHTrn )
        {
            // Camera translation.

            if( !m_thAppMainForm->UsingPlanform )
            {
                // 3D视图摄像机.
                SEVector3f tempLoc = m_pMainCamera->GetLocation();
                SEVector3f tempR = m_pMainCamera->GetRVector();
                tempR *= m_fCameraVHTrnSpeed * iDiffX;
                tempLoc += tempR;

                SEVector3f tempU = m_pMainCamera->GetUVector();
                tempU *= -m_fCameraVHTrnSpeed * iDiffY;
                tempLoc += tempU;
                m_pMainCamera->SetLocation(tempLoc);
            }
            else
            {
            }
        }
        else if( m_bAllowCameraTrackBall )
        {
        }
    }
}
//---------------------------------------------------------------------------
void SESceneEditorApplication::OnWindowRenderingMouseUp(Object^, 
    MouseEventArgs^ thEvent)
{
    if( thEvent->Button == MouseButtons::Middle )
    {
        m_bAllowCameraVHTrn = false;
        m_bAllowCameraTrackBall = false;
    }
    else if( thEvent->Button == MouseButtons::Left )
    {
    }
    else if( thEvent->Button == MouseButtons::Right )
    {
        m_bAllowCameraRot = false;
    }
}
//---------------------------------------------------------------------------
void SESceneEditorApplication::OnWindowRenderingMouseClick(Object^, 
    MouseEventArgs^)
{
}
//---------------------------------------------------------------------------
void SESceneEditorApplication::OnWindowRenderingMouseWheel(Object^, 
    MouseEventArgs^ thEvent)
{
    // Moving forward or backward of camera.
    if( m_bAllowCameraTrn )
    {
        if( m_thAppMainForm->UsingPlanform )
        {
        }
        else
        {
            SEVector3f tempLoc = m_pMainCamera->GetLocation();
            SEVector3f tempD = m_pMainCamera->GetDVector();
            tempD *= m_fCameraTrnSpeed * (thEvent->Delta / 120);
            tempLoc += tempD;
            m_pMainCamera->SetLocation(tempLoc);
        }
    }
}
//---------------------------------------------------------------------------