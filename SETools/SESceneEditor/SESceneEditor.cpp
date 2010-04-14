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
#include "MainForm.h"

using namespace SceneEditor;

[STAThreadAttribute]
int main(array<System::String^>^)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // 运行Register.
    Swing::SE_Foundation_Register();
    Swing::SE_DX9Renderer_Register();

    // Swing Engine initialize.
    Swing::System::SE_Initialize();
    std::string tempSEPath(Swing::System::SE_PATH);
    Swing::Main::Initialize();

    // 总是检查当前工作目录.
    Swing::System::SE_InsertDirectory(".");

    // scene graph文件的路径.
    std::string tempDir;
    tempDir = tempSEPath + std::string("/Data/seof");
    Swing::System::SE_InsertDirectory(tempDir.c_str());

    // texture image文件的路径.
    tempDir = tempSEPath + std::string("/Data/seif");
    Swing::System::SE_InsertDirectory(tempDir.c_str());

    // shader program文件的路径.
    tempDir = tempSEPath + std::string("/Data/sesp/Cg");
    Swing::System::SE_InsertDirectory(tempDir.c_str());

    Application::Run(gcnew MainForm());

    // Swing Engine terminate.
    Swing::Main::Terminate();
    Swing::System::SE_Terminate();

    return 0;
}
