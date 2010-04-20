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

#include "SEDX10RendererPCH.h"
#include "SEDX10ProgramInterface.h"
#include "SEProgram.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SEDX10ProgramInterface, SEObject);
SE_IMPLEMENT_STREAM(SEDX10ProgramInterface);
SE_IMPLEMENT_DEFAULT_STREAM(SEDX10ProgramInterface, SEObject);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEDX10ProgramInterface, SEObject);

//SE_REGISTER_STREAM(SEDX10ProgramInterface);

//----------------------------------------------------------------------------
SEDX10ProgramInterface::SEDX10ProgramInterface()
{
    m_eCgType = CG_UNKNOWN_TYPE;
    m_hCgParam = 0;
    m_hCgProgram = 0;
}
//----------------------------------------------------------------------------
SEDX10ProgramInterface::~SEDX10ProgramInterface()
{
    if( m_hCgParam )
    {
        cgDestroyParameter(m_hCgParam);
        SE_DX10_DEBUG_CG_PROGRAM;
    }

    SEDX10ProgramInterfaceCatalog::GetActive()->Remove(this);
}
//----------------------------------------------------------------------------
SEDX10ProgramInterface* SEDX10ProgramInterface::Load(CGprogram hCgProgram, 
    CGcontext hCgContext, const std::string& rPInterfaceName)
{
    CGtype eCgType = cgGetNamedUserType(hCgProgram, rPInterfaceName.c_str());
    SE_ASSERT( eCgType != CG_UNKNOWN_TYPE );

    if( eCgType != CG_UNKNOWN_TYPE )
    {
        SEDX10ProgramInterface* pProgramInterface = 
            SE_NEW SEDX10ProgramInterface;

        pProgramInterface->SetName(rPInterfaceName);
        pProgramInterface->m_eCgType = eCgType;
        pProgramInterface->m_hCgParam = cgCreateParameter(hCgContext, 
            eCgType);
        SE_DX10_DEBUG_CG_PROGRAM;
        pProgramInterface->m_hCgProgram = hCgProgram;

        SEDX10ProgramInterfaceCatalog::GetActive()->Insert(pProgramInterface);

        return pProgramInterface;
    }

    return 0;
}
//----------------------------------------------------------------------------