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
#include "SEDescriptorItem.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SEDescriptorItem, SEObject);
SE_IMPLEMENT_STREAM(SEDescriptorItem);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEDescriptorItem, SEObject);

//SE_REGISTER_STREAM(SEDescriptorItem);

//----------------------------------------------------------------------------
SEDescriptorItem::SEDescriptorItem()
{
    IsArray = false;
}
//----------------------------------------------------------------------------
SEDescriptorItem::~SEDescriptorItem()
{
}
//----------------------------------------------------------------------------
void SEDescriptorItem::AttachTypeName(const std::string& rTypeName)
{
    m_TypeNames.push_back(rTypeName);
}
//----------------------------------------------------------------------------
void SEDescriptorItem::DetachTypeName(const std::string& rTypeName)
{
    std::vector<std::string>::iterator pIter;
    for( pIter = m_TypeNames.begin(); pIter != m_TypeNames.end(); pIter++ )
    {
        if( *pIter == rTypeName )
        {
            m_TypeNames.erase(pIter);

            return;
        }
    }
}
//----------------------------------------------------------------------------
void SEDescriptorItem::DetachTypeName(int i)
{
    SE_ASSERT( i >= 0 && i < (int)m_TypeNames.size() );

    int iCount = (int)m_TypeNames.size();
    m_TypeNames[i] = m_TypeNames[iCount - 1];
    m_TypeNames.pop_back();
}
//----------------------------------------------------------------------------
const std::string& SEDescriptorItem::GetTypeName(int i) const
{
    SE_ASSERT( i >= 0 && i < (int)m_TypeNames.size() );

    return m_TypeNames[i];
}
//----------------------------------------------------------------------------
void SEDescriptorItem::GetDescription(std::string& rDesc) const
{
    rDesc = m_InstanceName;
    rDesc += "[";
    for( int i = 0; i < (int)m_TypeNames.size(); i++ )
    {
        rDesc += m_TypeNames[i];
        rDesc += ",";
    }
    rDesc += "]";
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SEDescriptorItem::Load(SEStream& rStream, SEStream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEObject::Load(rStream, pLink);

    // native data
    rStream.Read(IsArray);
    rStream.Read(m_InstanceName);

    int iCount;
    rStream.Read(iCount);
    m_TypeNames.resize(iCount);
    for( int i = 0; i < iCount; i++ )
    {
        rStream.Read(m_TypeNames[i]);
    }

    SE_END_DEBUG_STREAM_LOAD(SEDescriptorItem);
}
//----------------------------------------------------------------------------
void SEDescriptorItem::Link(SEStream& rStream, SEStream::Link* pLink)
{
    SEObject::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SEDescriptorItem::Register(SEStream& rStream) const
{
    return SEObject::Register(rStream);
}
//----------------------------------------------------------------------------
void SEDescriptorItem::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEObject::Save(rStream);

    // native data
    rStream.Write(IsArray);
    rStream.Write(m_InstanceName);

    int iCount = (int)m_TypeNames.size();
    rStream.Write(iCount);
    for( int i = 0; i < iCount; i++ )
    {
        rStream.Write(m_TypeNames[i]);
    }

    SE_END_DEBUG_STREAM_SAVE(SEDescriptorItem);
}
//----------------------------------------------------------------------------
int SEDescriptorItem::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    int iSize = SEObject::GetDiskUsed(rVersion) + sizeof(char) +
        sizeof(int) + (int)m_InstanceName.length();

    int iCount = (int)m_TypeNames.size();
    iSize += sizeof(int);
    for( int i = 0; i < iCount; i++ )
    {
        iSize += sizeof(int) + (int)m_TypeNames[i].length();
    }

    return iSize;
}
//----------------------------------------------------------------------------
SEStringTree* SEDescriptorItem::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("instance is array =", IsArray));
    pTree->Append(Format("instance name =", m_InstanceName.c_str()));

    const size_t uiTitleSize = 16;
    char acTitle[uiTitleSize];
    for( int i = 0; i < (int)m_TypeNames.size(); i++ )
    {
        SESystem::SE_Sprintf(acTitle, uiTitleSize, "type name[%d] =", i);
        pTree->Append(Format(acTitle, m_TypeNames[i].c_str()));
    }

    // children
    pTree->Append(SEObject::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
