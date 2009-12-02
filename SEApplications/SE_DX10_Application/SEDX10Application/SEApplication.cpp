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

#include "SEDX10ApplicationPCH.h"
#include "SEApplication.h"
#include "SEDX10RendererRegister.h"
#include "SEAudioRegister.h"
#include "SEOpenALRendererRegister.h"

using namespace Swing;

Application::EntryPoint Application::Run = 0;
Command* Application::TheCommand = 0;
Application* Application::TheApplication = 0;

//----------------------------------------------------------------------------
Application::Application()
{
    memset(m_acExtraData, 0, APP_EXTRA_DATA_COUNT*sizeof(char));
    m_bLaunchFileDialog = false;
}
//----------------------------------------------------------------------------
Application::~Application()
{
}
//----------------------------------------------------------------------------
void Application::SetExtraData(int iIndex, int iSize, const void* pvData)
{
    if( 0 <= iIndex && iIndex < APP_EXTRA_DATA_COUNT - iSize )
    {
        System::SE_Memcpy(m_acExtraData, APP_EXTRA_DATA_COUNT, pvData, iSize);
    }
}
//----------------------------------------------------------------------------
void Application::GetExtraData(int iIndex, int iSize, void* pvData) const
{
    if( 0 <= iIndex && iIndex < APP_EXTRA_DATA_COUNT - iSize )
    {
        System::SE_Memcpy(pvData, APP_EXTRA_DATA_COUNT, m_acExtraData, iSize);
    }
}
//----------------------------------------------------------------------------
bool Application::LaunchFileDialog() const
{
    return m_bLaunchFileDialog;
}
//----------------------------------------------------------------------------
void Application::TestStreaming(Spatial* pScene, int iXPos, int iYPos,
    int iXSize, int iYSize, const char* acFilename)
{
    Stream tempOStream;
    tempOStream.Insert(pScene);
    tempOStream.Save(acFilename);

    Stream tempIStream;
    tempIStream.Load(acFilename);
    SpatialPtr spScene = StaticCast<Spatial>(tempIStream.GetObjectAt(0));
    spScene->SetName(acFilename);

    LaunchTreeControl(spScene, iXPos, iYPos, iXSize, iYSize);
}
//----------------------------------------------------------------------------
int main(int iArgCount, char* apcArgument[])
{
    // 运行Register.
    SE_Foundation_Register();
    SE_Audio_Register();
    SE_DX10Renderer_Register();
    SE_OpenALRenderer_Register();

    // 先要手动创建SE_PATH这个环境变量,指定所需资源文件的所在位置.
    System::SE_Initialize();
    SE_ASSERT( System::SE_PATH[0] );
    String tempSEPath(System::SE_PATH);

    Main::Initialize();

    int iExitCode = 0;
    if( Application::Run )
    {
        // 总是检查当前工作目录.
        System::SE_InsertDirectory(".");

        // scene graph文件的路径.
        String tempDir;
        tempDir = tempSEPath + String("/Data/seof"); // swing engine object file
        System::SE_InsertDirectory((const char*)tempDir);

        // texture image文件的路径.
        tempDir = tempSEPath + String("/Data/seif");
        System::SE_InsertDirectory((const char*)tempDir);

        // shader program文件的路径.
        tempDir = tempSEPath + String("/Data/sesp/Cg");
        System::SE_InsertDirectory((const char*)tempDir);

        // wave文件的路径.
        tempDir = tempSEPath + String("/Data/sewf");
        System::SE_InsertDirectory((const char*)tempDir);

        // 其他image文件路径.
        tempDir = tempSEPath + String("/Data/Im");
        System::SE_InsertDirectory((const char*)tempDir);

        Application::TheCommand = SE_NEW Command(iArgCount, apcArgument);
        iExitCode = Application::Run(iArgCount, apcArgument);
        SE_DELETE Application::TheCommand;
        Application::TheCommand = 0;

        System::SE_RemoveAllDirectories();
    }
    else
    {
        iExitCode = INT_MAX;
    }

    Main::Terminate();

    SE_DELETE Application::TheApplication;
    Application::TheApplication = 0;

    System::SE_Terminate();

#ifdef SE_MEMORY_MANAGER
#ifdef _DEBUG
    Memory::GenerateReport("MemoryReportDebug.txt");
#else
    Memory::GenerateReport("MemoryReportRelease.txt");
#endif
#endif

    return iExitCode;
}
//----------------------------------------------------------------------------
