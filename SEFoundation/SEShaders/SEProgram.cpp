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
#include "SEProgram.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, Program, Object);
SE_IMPLEMENT_STREAM(Program);
SE_IMPLEMENT_DEFAULT_STREAM(Program, Object);
SE_IMPLEMENT_DEFAULT_NAME_ID(Program, Object);

//SE_REGISTER_STREAM(Program);

Program::LoadProgram Program::OnLoadProgram = 0;
Program::ReleaseUserData Program::OnReleaseUserData = 0;

const std::string Program::ms_PositionStr("POSITION");
const std::string Program::ms_Position0Str("POSITION0");
const std::string Program::ms_NormalStr("NORMAL");
const std::string Program::ms_Normal0Str("NORMAL0");
const std::string Program::ms_ColorStr("COLOR");
const std::string Program::ms_Color0Str("COLOR0");
const std::string Program::ms_Color1Str("COLOR1");
const std::string Program::ms_Color2Str("COLOR2");
const std::string Program::ms_Color3Str("COLOR3");
const std::string Program::ms_TexCoordStr("TEXCOORD");

//----------------------------------------------------------------------------
bool Program::Load(Renderer* pRenderer, const std::string& rProgramName, 
    Program* pProgram, ProgramType eType, InterfaceDescriptor* pInterfaceDesc)
{
    SE_ASSERT( OnLoadProgram );

    return OnLoadProgram(pRenderer, rProgramName, pProgram, eType, 
        pInterfaceDesc);
}
//----------------------------------------------------------------------------
Program::Program()
{
    UserData = 0;
}
//----------------------------------------------------------------------------
Program::~Program()
{
    Release();

    SE_ASSERT( OnReleaseUserData );

    if( OnReleaseUserData )
    {
        OnReleaseUserData(UserData);
    }
}
//----------------------------------------------------------------------------
RendererConstant* Program::GetRC(int i)
{
    if( 0 <= i && i < (int)m_RendererConstants.size() )
    {
        return &m_RendererConstants[i];
    }

    return 0;
}
//----------------------------------------------------------------------------
RendererConstant* Program::GetRC(RendererConstant::Type eType)
{
    for( int i = 0; i < (int)m_RendererConstants.size(); i++ )
    {
        if( eType == m_RendererConstants[i].GetType() )
        {
            return &m_RendererConstants[i];
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
UserConstant* Program::GetUC(int i)
{
    if( 0 <= i && i < (int)m_UserConstants.size() )
    {
        return &m_UserConstants[i];
    }

    return 0;
}
//----------------------------------------------------------------------------
UserConstant* Program::GetUC(const std::string& rName)
{
    for( int i = 0; i < (int)m_UserConstants.size(); i++ )
    {
        if( rName == m_UserConstants[i].GetName() )
        {
            return &m_UserConstants[i];
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
SamplerInformation* Program::GetSI(int i)
{
    if( 0 <= i && i < (int)m_SamplerInformation.size() )
    {
        return &m_SamplerInformation[i];
    }

    return 0;
}
//----------------------------------------------------------------------------
SamplerInformation* Program::GetSI(const std::string& rName)
{
    for( int i = 0; i < (int)m_SamplerInformation.size(); i++ )
    {
        if( rName == m_SamplerInformation[i].GetName() )
        {
            return &m_SamplerInformation[i];
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
