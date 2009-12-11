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

#include "SEOpenGLRendererPCH.h"
#include "SEProgram.h"
#include "SEOpenGLProgramInterface.h"
#include "SEOpenGLProgramInterfaceCatalog.h"


using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, OpenGLProgramInterface, Object);
SE_IMPLEMENT_STREAM(OpenGLProgramInterface);
SE_IMPLEMENT_DEFAULT_STREAM(OpenGLProgramInterface, Object);
SE_IMPLEMENT_DEFAULT_NAME_ID(OpenGLProgramInterface, Object);

//SE_REGISTER_STREAM(OpenGLProgramInterface);

//----------------------------------------------------------------------------
OpenGLProgramInterface::OpenGLProgramInterface()
{
    m_eCgType = CG_UNKNOWN_TYPE;
    m_hCgParam = 0;
    m_hCgProgram = 0;
}
//----------------------------------------------------------------------------
OpenGLProgramInterface::~OpenGLProgramInterface()
{
    if( m_hCgParam )
    {
        cgDestroyParameter(m_hCgParam);
        SE_GL_DEBUG_CG_PROGRAM;
    }

    OpenGLProgramInterfaceCatalog::GetActive()->Remove(this);
}
//----------------------------------------------------------------------------
OpenGLProgramInterface* OpenGLProgramInterface::Load(CGprogram hCgProgram, 
    CGcontext hCgContext, const std::string& rPInterfaceName)
{
    CGtype eCgType = cgGetNamedUserType(hCgProgram, rPInterfaceName.c_str());
    SE_ASSERT( eCgType != CG_UNKNOWN_TYPE );

    if( eCgType != CG_UNKNOWN_TYPE )
    {
        OpenGLProgramInterface* pProgramInterface = 
            SE_NEW OpenGLProgramInterface;

        pProgramInterface->SetName(rPInterfaceName);
        pProgramInterface->m_eCgType = eCgType;
        pProgramInterface->m_hCgParam = cgCreateParameter(hCgContext, 
            eCgType);
        SE_GL_DEBUG_CG_PROGRAM;
        pProgramInterface->m_hCgProgram = hCgProgram;

        OpenGLProgramInterfaceCatalog::GetActive()->Insert(pProgramInterface);

        return pProgramInterface;
    }

    return 0;
}
//----------------------------------------------------------------------------