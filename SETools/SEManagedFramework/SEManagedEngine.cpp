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

#include "SEManagedFrameworkPCH.h"
#include "SEManagedEngine.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedEngine::ManagedEngine()
{
    // 运行Register.
    SE_Foundation_Register();
    SE_DX9Renderer_Register();

    // Swing Engine initialize.
    System::SE_Initialize();
    std::string tempSEPath(System::SE_PATH);
    Main::Initialize();

    // 总是检查当前工作目录.
    System::SE_InsertDirectory(".");

    // scene graph文件的路径.
    std::string tempDir;
    tempDir = tempSEPath + std::string("/Data/seof");
    System::SE_InsertDirectory(tempDir.c_str());

    // texture image文件的路径.
    tempDir = tempSEPath + std::string("/Data/seif");
    System::SE_InsertDirectory(tempDir.c_str());

    // shader program文件的路径.
    tempDir = tempSEPath + std::string("/Data/sesp/Cg");
    System::SE_InsertDirectory(tempDir.c_str());

    TriMesh::InitializePickRecordPool();
}
//---------------------------------------------------------------------------
ManagedEngine::~ManagedEngine()
{
    TriMesh::TerminatePickRecordPool();

    // Swing Engine terminate.
    Main::Terminate();
    System::SE_Terminate();
}
//---------------------------------------------------------------------------
void ManagedEngine::Initialize()
{
    if( !ms_thThis )
    {
        ms_thThis = gcnew ManagedEngine;
    }
}
//---------------------------------------------------------------------------
void ManagedEngine::Terminate()
{
    if( ms_thThis )
    {
        delete ms_thThis;
        ms_thThis = nullptr;
    }
}
//---------------------------------------------------------------------------
void ManagedEngine::InitializeShaderProgramCatalog(
    ManagedRenderer^ thRenderer)
{
    if( !ms_thThis )
    {
        return;
    }

    if( !thRenderer )
    {
        throw gcnew ArgumentNullException("thRenderer");
    }

    if( !VertexProgramCatalog::GetActive() || 
        !PixelProgramCatalog::GetActive() || 
        !DX9ProgramInterfaceCatalog::GetActive() )
    {
        throw gcnew NullReferenceException(
            "Initializing shader program catalog");
    }

    Renderer* pRenderer = thRenderer->GetNativeRenderer();
    VertexProgramCatalog::GetActive()->SetRenderer(pRenderer);
    PixelProgramCatalog::GetActive()->SetRenderer(pRenderer);
    DX9ProgramInterfaceCatalog::GetActive()->SetRenderer(
        (DX9Renderer*)pRenderer);
}
//---------------------------------------------------------------------------
void ManagedEngine::TerminateShaderProgramCatalog()
{
    if( !ms_thThis )
    {
        return;
    }

    if( !VertexProgramCatalog::GetActive() || 
        !PixelProgramCatalog::GetActive() || 
        !DX9ProgramInterfaceCatalog::GetActive() )
    {
        throw gcnew NullReferenceException(
            "Terminating shader program catalog");
    }

    VertexProgramCatalog::GetActive()->SetRenderer(0);
    PixelProgramCatalog::GetActive()->SetRenderer(0);
    DX9ProgramInterfaceCatalog::GetActive()->SetRenderer(0);
}
//---------------------------------------------------------------------------