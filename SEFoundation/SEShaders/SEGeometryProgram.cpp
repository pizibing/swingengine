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

#include "SEFoundationPCH.h"
#include "SEGeometryProgram.h"
#include "SEGeometryProgramCatalog.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, GeometryProgram, Program);
SE_IMPLEMENT_STREAM(GeometryProgram);
SE_IMPLEMENT_DEFAULT_STREAM(GeometryProgram, Program);
SE_IMPLEMENT_DEFAULT_NAME_ID(GeometryProgram, Program);

//SE_REGISTER_STREAM(GeometryProgram);

//----------------------------------------------------------------------------
GeometryProgram* GeometryProgram::Load(Renderer* pRenderer, 
    const std::string& rProgramName, const std::string& rKey, 
    InterfaceDescriptor* pInterfaceDesc)
{
    GeometryProgram* pProgram = SE_NEW GeometryProgram;
    bool bLoaded = Program::Load(pRenderer, rProgramName, pProgram,
        Program::PT_GEOMETRY, pInterfaceDesc);

    if( !bLoaded )
    {
        SE_DELETE pProgram;
        return 0;
    }

    pProgram->SetName(rKey);
    GeometryProgramCatalog::GetActive()->Insert(pProgram);

    return pProgram;
}
//----------------------------------------------------------------------------
GeometryProgram::GeometryProgram()
{
}
//----------------------------------------------------------------------------
GeometryProgram::~GeometryProgram()
{
    GeometryProgramCatalog::GetActive()->Remove(this);
}
//----------------------------------------------------------------------------
