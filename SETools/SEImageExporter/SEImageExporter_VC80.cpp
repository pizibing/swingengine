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
#include "Form1.h"
#include <windows.h>

// 静态链接DirectX9库.
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxerr9.lib")

using namespace SEImageExporter_VC80;

ImageExporterApp g_ImageExporterApp;

//----------------------------------------------------------------------------
// 主循环回调函数.
//----------------------------------------------------------------------------
void App_Idle(System::Object^, System::EventArgs^) 
{
    g_ImageExporterApp.OnIdle();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 应用程序入口函数.
//----------------------------------------------------------------------------
[STAThreadAttribute]
int main(array<System::String ^> ^)
{
    // 运行Register.
    Swing::SE_Foundation_Register();
    Swing::SE_DX9Renderer_Register();

    // Swing Engine initialize.
    Swing::System::SE_Initialize();
    assert( Swing::System::SE_PATH[0] );
    Swing::String tempSEPath(Swing::System::SE_PATH);
    Swing::Main::Initialize();

    // 添加application所需资源目录.
    Swing::System::SE_InsertDirectory(".");
    Swing::String tempDir;
    tempDir = tempSEPath + Swing::String("/Data/sesp/Cg");
    Swing::System::SE_InsertDirectory((const char*)tempDir);

    // 创建application主窗体.
    Form1^ pForm1 = gcnew Form1;
    g_ImageExporterApp.Handle = (int)pForm1->SceneWindow->Handle;

    // 创建renderer.
    Swing::DX9Renderer* pRenderer = SE_NEW Swing::DX9Renderer(
        (HWND)(g_ImageExporterApp.Handle), 
        Swing::FrameBuffer::FT_FORMAT_RGBA, 
        Swing::FrameBuffer::DT_DEPTH_24,
        Swing::FrameBuffer::ST_STENCIL_8, 
        Swing::FrameBuffer::BT_BUFFERED_DOUBLE, 
        Swing::FrameBuffer::MT_SAMPLING_NONE, 
        640, 480);
    g_ImageExporterApp.AppRenderer = pRenderer;
    pRenderer->SetClearColor(Swing::ColorRGBA(0.5f, 0.5f, 0.5f, 1.0f));

    // 创建shader program catalog.
    assert( Swing::VertexProgramCatalog::GetActive() );
    Swing::VertexProgramCatalog::GetActive()->SetRenderer(pRenderer);
    assert( Swing::PixelProgramCatalog::GetActive() );
    Swing::PixelProgramCatalog::GetActive()->SetRenderer(pRenderer);

    // 创建camera.
    Swing::Camera* pCamera = SE_NEW Swing::Camera;
    pRenderer->SetCamera(pCamera);
    float fDMin = 1.0f;
    float fDMax = 100.0f;
    float fRMax = 0.55f * fDMin;
    float fRMin = -fRMax;
    float fUMax = 0.4125f/*0.309375f*/ * fDMin;
    float fUMin = -fUMax;
    pCamera->SetFrustum(fRMin, fRMax, fUMin, fUMax, fDMin, fDMax);
    Swing::Vector3f tempCLoc(0.0f, 0.0f, -3.0f);
    Swing::Vector3f tempCDir(0.0f, 0.0f, 1.0f);
    Swing::Vector3f tempCUp(0.0f, 1.0f, 0.0f);
    Swing::Vector3f tempCRight = tempCUp.Cross(tempCDir);
    pCamera->SetFrame(tempCLoc, tempCRight, tempCUp, tempCDir);
    g_ImageExporterApp.m_spCamera = pCamera;

    // 创建scene graph.
    g_ImageExporterApp.CreateScene();

    // 开始主循环.
    Application::Idle += gcnew System::EventHandler(App_Idle);
    Application::Run(pForm1);

    // 释放scene graph.
    g_ImageExporterApp.DestroyScene();

    // 释放camera和shader program catalog.
    g_ImageExporterApp.AppRenderer->SetCamera(0);
    g_ImageExporterApp.m_spCamera = 0;
    assert( Swing::VertexProgramCatalog::GetActive() );
    Swing::VertexProgramCatalog::GetActive()->SetRenderer(0);
    assert( Swing::PixelProgramCatalog::GetActive() );
    Swing::PixelProgramCatalog::GetActive()->SetRenderer(0);

    // 释放renderer.
    SE_DELETE g_ImageExporterApp.AppRenderer;
    g_ImageExporterApp.AppRenderer = 0;

    // Swing Engine terminate.
    Swing::Main::Terminate();
    Swing::System::SE_Terminate();

    return 0;
}
//----------------------------------------------------------------------------