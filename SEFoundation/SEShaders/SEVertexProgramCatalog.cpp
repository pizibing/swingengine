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
#include "SEVertexProgramCatalog.h"
#include "SEVertexProgram.h"

using namespace Swing;

const String VertexProgramCatalog::ms_NullString("");
const String VertexProgramCatalog::ms_DefaultString("Default.v_Default");
VertexProgramCatalog* VertexProgramCatalog::ms_pActive = 0;

//----------------------------------------------------------------------------
VertexProgramCatalog::VertexProgramCatalog(const String& rName)
    :
    m_Name(rName),
    m_Entry(PROGRAM_MAP_SIZE)
{
    m_pRenderer = 0;
    m_spDefaultVProgram = 0;
}
//----------------------------------------------------------------------------
VertexProgramCatalog::~VertexProgramCatalog()
{
}
//----------------------------------------------------------------------------
void VertexProgramCatalog::SetRenderer(Renderer* pRenderer)
{
    m_pRenderer = pRenderer;

    if( m_pRenderer )
    {
        m_spDefaultVProgram = VertexProgram::Load(m_pRenderer, 
            ms_DefaultString, ms_DefaultString, 0);

        SE_ASSERT( m_spDefaultVProgram );
    }
    else
    {
        m_spDefaultVProgram = 0;
    }
}
//----------------------------------------------------------------------------
const String& VertexProgramCatalog::GetName() const
{
    return m_Name;
}
//----------------------------------------------------------------------------
bool VertexProgramCatalog::Insert(VertexProgram* pProgram)
{
    if( !pProgram )
    {
        SE_ASSERT( false );

        return false;
    }

    String StrProgramName(pProgram->GetName());
    if( StrProgramName == ms_NullString
    ||  StrProgramName == ms_DefaultString
    ||  pProgram == m_spDefaultVProgram )
    {
        return false;
    }

    // 首先在资源目录中查找
    VertexProgram** ppTempProgram = m_Entry.Find(StrProgramName);
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
bool VertexProgramCatalog::Remove(VertexProgram* pProgram)
{
    if( !pProgram )
    {
        SE_ASSERT( false );

        return false;
    }

    String StrProgramName(pProgram->GetName());
    if( StrProgramName == ms_NullString
    ||  StrProgramName == ms_DefaultString
    ||  pProgram == m_spDefaultVProgram )
    {
        return false;
    }

    // 首先在资源目录中查找
    VertexProgram** ppTempProgram = m_Entry.Find(StrProgramName);
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
VertexProgram* VertexProgramCatalog::Find(const String& rProgramName,
    InterfaceDescriptor* pDescriptor)
{
    if( rProgramName == ms_NullString
    ||  rProgramName == ms_DefaultString )
    {
        return StaticCast<VertexProgram>(m_spDefaultVProgram);
    }

    // 首先在资源目录中查找
    String tempKey = rProgramName;
    if( pDescriptor )
    {
        String tempPostFix;
        pDescriptor->GetDescription(tempPostFix);
        tempKey += tempPostFix;
    }
    VertexProgram** ppTempProgram = m_Entry.Find(tempKey);
    if( ppTempProgram )
    {
        // 找到则返回
        return *ppTempProgram;
    }

    // 在磁盘中查找
    VertexProgram* pProgram = VertexProgram::Load(m_pRenderer, rProgramName, 
        tempKey, pDescriptor);
    if( pProgram )
    {
        // 该资源存在,且已经在Load后被加入资源目录,不用再次调用Insert函数
        return pProgram;
    }

    // 程序不存在,则使用默认程序
    return StaticCast<VertexProgram>(m_spDefaultVProgram);
}
//----------------------------------------------------------------------------
bool VertexProgramCatalog::PrintContents(const String& rFileName) const
{
    const char* pDecorated = System::SE_GetPath(rFileName, System::SM_WRITE);

    if( pDecorated )
    {
        std::ofstream OStream(pDecorated);

        SE_ASSERT( OStream );

		String StrProgramName;
		VertexProgram** ppTempProgram = m_Entry.GetFirst(&StrProgramName);
        while( ppTempProgram )
        {
            OStream << (const char*)StrProgramName << std::endl;
            OStream << std::endl;
            ppTempProgram = m_Entry.GetNext(&StrProgramName);
        }
        OStream.close();

        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
int VertexProgramCatalog::GetProfile() const
{
    return m_pRenderer ? m_pRenderer->GetMaxVShaderProfile() : -1;
}
//----------------------------------------------------------------------------
void VertexProgramCatalog::SetActive(VertexProgramCatalog* pActive)
{
    ms_pActive = pActive;
}
//----------------------------------------------------------------------------
VertexProgramCatalog* VertexProgramCatalog::GetActive()
{
    return ms_pActive;
}
//----------------------------------------------------------------------------
