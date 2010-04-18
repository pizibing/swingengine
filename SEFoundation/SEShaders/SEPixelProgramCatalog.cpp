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
#include "SEPixelProgramCatalog.h"
#include "SEPixelProgram.h"

using namespace Swing;

const std::string SEPixelProgramCatalog::ms_NullString("");
const std::string SEPixelProgramCatalog::ms_DefaultString("Default.p_Default");
SEPixelProgramCatalog* SEPixelProgramCatalog::ms_pActive = 0;

//----------------------------------------------------------------------------
SEPixelProgramCatalog::SEPixelProgramCatalog(const std::string& rName)
    :
    m_Name(rName),
    m_Entry(PROGRAM_MAP_SIZE)
{
    m_pRenderer = 0;
    m_spDefaultPProgram = 0;
}
//----------------------------------------------------------------------------
SEPixelProgramCatalog::~SEPixelProgramCatalog()
{
}
//----------------------------------------------------------------------------
void SEPixelProgramCatalog::SetRenderer(SERenderer* pRenderer)
{
    m_pRenderer = pRenderer;

    if( m_pRenderer )
    {
        m_spDefaultPProgram = SEPixelProgram::Load(m_pRenderer, 
            ms_DefaultString, ms_DefaultString, 0);

        SE_ASSERT( m_spDefaultPProgram );
    }
    else
    {
        m_spDefaultPProgram = 0;
    }
}
//----------------------------------------------------------------------------
const std::string& SEPixelProgramCatalog::GetName() const
{
    return m_Name;
}
//----------------------------------------------------------------------------
bool SEPixelProgramCatalog::Insert(SEPixelProgram* pProgram)
{
    if( !pProgram )
    {
        SE_ASSERT( false );

        return false;
    }

    std::string StrProgramName(pProgram->GetName());
    if( StrProgramName == ms_NullString
    ||  StrProgramName == ms_DefaultString
    ||  pProgram == m_spDefaultPProgram )
    {
        return false;
    }

    // 首先在资源目录中查找
    SEPixelProgram** ppTempProgram = m_Entry.Find(StrProgramName);
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
bool SEPixelProgramCatalog::Remove(SEPixelProgram* pProgram)
{
    if( !pProgram )
    {
        SE_ASSERT( false );

        return false;
    }

    std::string StrProgramName(pProgram->GetName());
    if( StrProgramName == ms_NullString
    ||  StrProgramName == ms_DefaultString
    ||  pProgram == m_spDefaultPProgram )
    {
        return false;
    }

    // 首先在资源目录中查找
    SEPixelProgram** ppTempProgram = m_Entry.Find(StrProgramName);
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
SEPixelProgram* SEPixelProgramCatalog::Find(const std::string& rProgramName,
    SEInterfaceDescriptor* pDescriptor)
{
    if( rProgramName == ms_NullString
    ||  rProgramName == ms_DefaultString)
    {
        return StaticCast<SEPixelProgram>(m_spDefaultPProgram);
    }

    // 首先在资源目录中查找
    std::string tempKey = rProgramName;
    if( pDescriptor )
    {
        std::string tempPostFix;
        pDescriptor->GetDescription(tempPostFix);
        tempKey += tempPostFix;
    }
    SEPixelProgram** ppTempProgram = m_Entry.Find(tempKey);
    if( ppTempProgram )
    {
        // 找到则返回
        return *ppTempProgram;
    }

    // 在磁盘中查找
    SEPixelProgram* pProgram = SEPixelProgram::Load(m_pRenderer, rProgramName, 
        tempKey, pDescriptor);
    if( pProgram )
    {
        // 该资源存在,且已经在Load后被加入资源目录,不用再次调用Insert函数
        return pProgram;
    }

    // 程序不存在,则使用默认程序
    return StaticCast<SEPixelProgram>(m_spDefaultPProgram);
}
//----------------------------------------------------------------------------
bool SEPixelProgramCatalog::PrintContents(const std::string& rFileName) const
{
    const char* pDecorated = SESystem::SE_GetPath(rFileName.c_str(), 
        SESystem::SM_WRITE);

    if( pDecorated )
    {
        std::ofstream OStream(pDecorated);

        SE_ASSERT( OStream );

        std::string StrProgramName;
		SEPixelProgram** ppTempProgram = m_Entry.GetFirst(&StrProgramName);
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
int SEPixelProgramCatalog::GetProfile() const
{
    return m_pRenderer ? m_pRenderer->GetMaxPShaderProfile() : -1;
}
//----------------------------------------------------------------------------
void SEPixelProgramCatalog::SetActive(SEPixelProgramCatalog* pActive)
{
    ms_pActive = pActive;
}
//----------------------------------------------------------------------------
SEPixelProgramCatalog* SEPixelProgramCatalog::GetActive()
{
    return ms_pActive;
}
//----------------------------------------------------------------------------
