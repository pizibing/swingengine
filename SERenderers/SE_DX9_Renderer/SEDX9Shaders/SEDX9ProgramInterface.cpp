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

#include "SEDX9RendererPCH.h"
#include "SEDX9ProgramInterface.h"
#include "SEProgram.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, DX9ProgramInterface, Object);
SE_IMPLEMENT_STREAM(DX9ProgramInterface);
SE_IMPLEMENT_DEFAULT_STREAM(DX9ProgramInterface, Object);
SE_IMPLEMENT_DEFAULT_NAME_ID(DX9ProgramInterface, Object);

//SE_REGISTER_STREAM(DX9ProgramInterface);

//----------------------------------------------------------------------------
DX9ProgramInterface::DX9ProgramInterface()
{
    m_eCgType = CG_UNKNOWN_TYPE;
    m_hCgParam = 0;
    m_hCgProgram = 0;
}
//----------------------------------------------------------------------------
DX9ProgramInterface::~DX9ProgramInterface()
{
    if( m_hCgParam )
    {
        cgDestroyParameter(m_hCgParam);
        SE_DX9_DEBUG_CG_PROGRAM;
    }

    DX9ProgramInterfaceCatalog::GetActive()->Remove(this);
}
//----------------------------------------------------------------------------
DX9ProgramInterface* DX9ProgramInterface::Load(CGprogram hCgProgram, 
    CGcontext hCgContext, const String& rPInterfaceName)
{
    CGtype eCgType = cgGetNamedUserType(hCgProgram, rPInterfaceName);
    SE_ASSERT( eCgType != CG_UNKNOWN_TYPE );

    if( eCgType != CG_UNKNOWN_TYPE )
    {
        DX9ProgramInterface* pProgramInterface = SE_NEW DX9ProgramInterface;

        pProgramInterface->SetName(rPInterfaceName);
        pProgramInterface->m_eCgType = eCgType;
        pProgramInterface->m_hCgParam = cgCreateParameter(hCgContext, 
            eCgType);
        SE_DX9_DEBUG_CG_PROGRAM;
        pProgramInterface->m_hCgProgram = hCgProgram;

        DX9ProgramInterfaceCatalog::GetActive()->Insert(pProgramInterface);

        return pProgramInterface;
    }

    return 0;
}
//----------------------------------------------------------------------------