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
#include "SEGeometryProgramCatalog.h"
#include "SEGeometryProgram.h"

using namespace Swing;

const std::string SEGeometryProgramCatalog::ms_NullString("");
const std::string SEGeometryProgramCatalog::ms_DefaultString("Default.g_Default");
SEGeometryProgramCatalog* SEGeometryProgramCatalog::ms_pActive = 0;

//----------------------------------------------------------------------------
SEGeometryProgramCatalog::SEGeometryProgramCatalog(const std::string& rName)
    :
    m_Name(rName),
    m_Entry(PROGRAM_MAP_SIZE)
{
    m_pRenderer = 0;
    m_spDefaultGProgram = 0;
}
//----------------------------------------------------------------------------
SEGeometryProgramCatalog::~SEGeometryProgramCatalog()
{
}
//----------------------------------------------------------------------------
void SEGeometryProgramCatalog::SetRenderer(SERenderer* pRenderer)
{
    m_pRenderer = pRenderer;

    if( m_pRenderer )
    {
        m_spDefaultGProgram = SEGeometryProgram::Load(m_pRenderer, 
            ms_DefaultString, ms_DefaultString, 0);

        SE_ASSERT( m_spDefaultGProgram );
    }
    else
    {
        m_spDefaultGProgram = 0;
    }
}
//----------------------------------------------------------------------------
const std::string& SEGeometryProgramCatalog::GetName() const
{
    return m_Name;
}
//----------------------------------------------------------------------------
bool SEGeometryProgramCatalog::Insert(SEGeometryProgram* pProgram)
{
    if( !pProgram )
    {
        SE_ASSERT( false );

        return false;
    }

    std::string StrProgramName(pProgram->GetName());
    if( StrProgramName == ms_NullString
    ||  StrProgramName == ms_DefaultString
    ||  pProgram == m_spDefaultGProgram )
    {
        return false;
    }

    // 首先在资源目录中查找
    SEGeometryProgram** ppTempProgram = m_Entry.Find(StrProgramName);
    if( ppTempProgram )
    {
        // 该程序已经存在
        return true;
    }

    // 该程序不存在,则插入
    m_Entry.Insert(StrProgramName, pProgram);

    return true;
}
//----------------------------------------------------------------------------
bool SEGeometryProgramCatalog::Remove(SEGeometryProgram* pProgram)
{
    if( !pProgram )
    {
        SE_ASSERT( false );

        return false;
    }

    std::string StrProgramName(pProgram->GetName());
    if( StrProgramName == ms_NullString
    ||  StrProgramName == ms_DefaultString
    ||  pProgram == m_spDefaultGProgram )
    {
        return false;
    }

    // 首先在资源目录中查找
    SEGeometryProgram** ppTempProgram = m_Entry.Find(StrProgramName);
    if( !ppTempProgram )
    {
        // 该程序不存在
        return false;
    }

    // 程序存在,则移除
    m_Entry.Remove(StrProgramName);

    return true;
}
//----------------------------------------------------------------------------
SEGeometryProgram* SEGeometryProgramCatalog::Find(const std::string& rProgramName,
    SEInterfaceDescriptor* pDescriptor)
{
    if( rProgramName == ms_NullString
    ||  rProgramName == ms_DefaultString )
    {
        return StaticCast<SEGeometryProgram>(m_spDefaultGProgram);
    }

    // 首先在资源目录中查找
    std::string tempKey = rProgramName;
    if( pDescriptor )
    {
        std::string tempPostFix;
        pDescriptor->GetDescription(tempPostFix);
        tempKey += tempPostFix;
    }
    SEGeometryProgram** ppTempProgram = m_Entry.Find(tempKey);
    if( ppTempProgram )
    {
        // 找到则返回
        return *ppTempProgram;
    }

    // 在磁盘中查找
    SEGeometryProgram* pProgram = SEGeometryProgram::Load(m_pRenderer, 
        rProgramName, tempKey, pDescriptor);
    if( pProgram )
    {
        // 该资源存在,且已经在Load后被加入资源目录,不用再次调用Insert函数
        return pProgram;
    }

    // 程序不存在,则使用默认程序
    return StaticCast<SEGeometryProgram>(m_spDefaultGProgram);
}
//----------------------------------------------------------------------------
bool SEGeometryProgramCatalog::PrintContents(const std::string& rFileName) const
{
    const char* pDecorated = SESystem::SE_GetPath(rFileName.c_str(), 
        SESystem::SM_WRITE);

    if( pDecorated )
    {
        std::ofstream OStream(pDecorated);

        SE_ASSERT( OStream );

		std::string StrProgramName;
		SEGeometryProgram** ppTempProgram = m_Entry.GetFirst(&StrProgramName);
        while( ppTempProgram )
        {
            OStream << StrProgramName.c_str() << std::endl;
            OStream << std::endl;
            ppTempProgram = m_Entry.GetNext(&StrProgramName);
        }
        OStream.close();

        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
int SEGeometryProgramCatalog::GetProfile() const
{
    return m_pRenderer ? m_pRenderer->GetMaxGShaderProfile() : -1;
}
//----------------------------------------------------------------------------
void SEGeometryProgramCatalog::SetActive(SEGeometryProgramCatalog* pActive)
{
    ms_pActive = pActive;
}
//----------------------------------------------------------------------------
SEGeometryProgramCatalog* SEGeometryProgramCatalog::GetActive()
{
    return ms_pActive;
}
//----------------------------------------------------------------------------
