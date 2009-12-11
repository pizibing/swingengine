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

using namespace SEColladaImporter;

ColladaImporterApp g_ColladaImporterApp;

//----------------------------------------------------------------------------
// 主循环回调函数.
//----------------------------------------------------------------------------
void App_Idle(System::Object^, System::EventArgs^) 
{
    g_ColladaImporterApp.OnIdle();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 应用程序入口函数.
//----------------------------------------------------------------------------
[STAThreadAttribute]
int main(array<System::String ^> ^)
{
    // 在创建任何控件之前启用 Windows XP 可视化效果.
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false); 

    // 运行Register.
    Swing::SE_Foundation_Register();
    Swing::SE_DX9Renderer_Register();

    // Swing Engine initialize.
    Swing::ToolSystem::SE_DebugOutput("Swing Engine initialized");
    Swing::System::SE_Initialize();
    assert( Swing::System::SE_PATH[0] );
    std::string tempSEPath(Swing::System::SE_PATH);
    Swing::Main::Initialize();

    // 添加application所需资源目录.
    Swing::System::SE_InsertDirectory(".");
    std::string tempDir;
    tempDir = tempSEPath + std::string("/Data/sesp/Cg");
    Swing::System::SE_InsertDirectory(tempDir.c_str());

    // 创建application主窗体.
    Form1^ pForm1 = gcnew Form1;
    g_ColladaImporterApp.Handle = (int)pForm1->SceneWindow->Handle;

    // 创建renderer.
    Swing::DX9Renderer* pRenderer = SE_NEW Swing::DX9Renderer(
        (HWND)(g_ColladaImporterApp.Handle), 
        Swing::FrameBuffer::FT_FORMAT_RGBA, 
        Swing::FrameBuffer::DT_DEPTH_24,
        Swing::FrameBuffer::ST_STENCIL_8, 
        Swing::FrameBuffer::BT_BUFFERED_DOUBLE, 
        Swing::FrameBuffer::MT_SAMPLING_NONE, 
        640, 480);
    g_ColladaImporterApp.AppRenderer = pRenderer;
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
    float fDMax = 1000.0f;
    float fRMax = 0.55f * fDMin;
    float fRMin = -fRMax;
    float fUMax = 0.4125f/*0.309375f*/ * fDMin;
    float fUMin = -fUMax;
    pCamera->SetFrustum(fRMin, fRMax, fUMin, fUMax, fDMin, fDMax);
    Swing::Vector3f tempCLoc(0.0f, 5.0f, -30.0f);
    Swing::Vector3f tempCDir(0.0f, 0.0f, 1.0f);
    Swing::Vector3f tempCUp(0.0f, 1.0f, 0.0f);
    Swing::Vector3f tempCRight = tempCUp.Cross(tempCDir);
    pCamera->SetFrame(tempCLoc, tempCRight, tempCUp, tempCDir);
    g_ColladaImporterApp.AppCamera = pCamera;

    // 创建scene graph.
    g_ColladaImporterApp.CreateScene();

    // 开始主循环.
    Application::Idle += gcnew System::EventHandler(App_Idle);
    Application::Run(pForm1);

    // 释放scene graph.
    g_ColladaImporterApp.DestroyScene();

    // 释放camera和shader program catalog.
    g_ColladaImporterApp.AppRenderer->SetCamera(0);
    g_ColladaImporterApp.AppCamera = 0;
    assert( Swing::VertexProgramCatalog::GetActive() );
    Swing::VertexProgramCatalog::GetActive()->SetRenderer(0);
    assert( Swing::PixelProgramCatalog::GetActive() );
    Swing::PixelProgramCatalog::GetActive()->SetRenderer(0);

    // 释放renderer.
    SE_DELETE g_ColladaImporterApp.AppRenderer;
    g_ColladaImporterApp.AppRenderer = 0;

    // Swing Engine terminate.
    Swing::ToolSystem::SE_DebugOutput("Swing Engine terminated");
    Swing::Main::Terminate();
    Swing::System::SE_Terminate();

    return 0;
}
//----------------------------------------------------------------------------