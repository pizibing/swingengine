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
#include "SEPixelProgram.h"
#include "SEPixelProgramCatalog.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, PixelProgram, Program);
SE_IMPLEMENT_STREAM(PixelProgram);
SE_IMPLEMENT_DEFAULT_STREAM(PixelProgram, Program);
SE_IMPLEMENT_DEFAULT_NAME_ID(PixelProgram, Program);

//SE_REGISTER_STREAM(PixelProgram);

//----------------------------------------------------------------------------
PixelProgram* PixelProgram::Load(Renderer* pRenderer, 
    const String& rProgramName, const String& rKey, 
    InterfaceDescriptor* pInterfaceDesc)
{
    PixelProgram* pProgram = SE_NEW PixelProgram;
	bool bLoaded = Program::Load(pRenderer, rProgramName, pProgram, 
        Program::PT_PIXEL, pInterfaceDesc);

    if( !bLoaded )
    {
        SE_DELETE pProgram;
        return 0;
    }

    pProgram->SetName(rKey);
    PixelProgramCatalog::GetActive()->Insert(pProgram);

    return pProgram;
}
//----------------------------------------------------------------------------
PixelProgram::PixelProgram()
{
}
//----------------------------------------------------------------------------
PixelProgram::~PixelProgram()
{
    PixelProgramCatalog::GetActive()->Remove(this);
}
//----------------------------------------------------------------------------
