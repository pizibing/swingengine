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
#include "SEInterfaceDescriptor.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, InterfaceDescriptor, Object);
SE_IMPLEMENT_STREAM(InterfaceDescriptor);
SE_IMPLEMENT_DEFAULT_NAME_ID(InterfaceDescriptor, Object);

//SE_REGISTER_STREAM(InterfaceDescriptor);

//----------------------------------------------------------------------------
InterfaceDescriptor::InterfaceDescriptor()
{
}
//----------------------------------------------------------------------------
InterfaceDescriptor::~InterfaceDescriptor()
{
}
//----------------------------------------------------------------------------
void InterfaceDescriptor::AttachItem(DescriptorItem* pItem)
{
    SE_ASSERT( pItem );

    // 是否存在该item.
    for( int i = 0; i < (int)m_DescriptorItems.size(); i++ )
    {
        if( m_DescriptorItems[i] == pItem )
        {
            // 存在则返回.
            return;
        }
    }

    m_DescriptorItems.push_back(pItem);
}
//----------------------------------------------------------------------------
void InterfaceDescriptor::DetachItem(DescriptorItem* pItem)
{
    SE_ASSERT( pItem );

    // 是否存在该item.
    std::vector<DescriptorItemPtr>::iterator pIter = m_DescriptorItems.begin();
    for( /**/ ; pIter != m_DescriptorItems.end(); pIter++ )
    {
        if( *pIter == pItem )
        {
            // 存在则删除.
            m_DescriptorItems.erase(pIter);
            return;
        }
    }
}
//----------------------------------------------------------------------------
DescriptorItem* InterfaceDescriptor::GetItem(int i) const
{
    SE_ASSERT( i >= 0 && i < (int)m_DescriptorItems.size() );

    return m_DescriptorItems[i];
}
//----------------------------------------------------------------------------
void InterfaceDescriptor::GetDescription(std::string& rDesc) const
{
    for( int i = 0; i < (int)m_DescriptorItems.size(); i++ )
    {
        std::string tempItemDesc;
        m_DescriptorItems[i]->GetDescription(tempItemDesc);
        rDesc += tempItemDesc;
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void InterfaceDescriptor::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    Object::Load(rStream, pLink);

    // link data
    int iCount;
    rStream.Read(iCount);
    m_DescriptorItems.resize(iCount);
    for( int i = 0; i < iCount; i++ )
    {
        Object* pObject;
        rStream.Read(pObject);  // m_DescriptorItems[i]
        pLink->Add(pObject);
    }

    SE_END_DEBUG_STREAM_LOAD(InterfaceDescriptor);
}
//----------------------------------------------------------------------------
void InterfaceDescriptor::Link(Stream& rStream, Stream::Link* pLink)
{
    Object::Link(rStream, pLink);

    for( int i = 0; i < (int)m_DescriptorItems.size(); i++ )
    {
        Object* pLinkID;
        pLinkID = pLink->GetLinkID();
        m_DescriptorItems[i] = (DescriptorItem*)rStream.GetFromMap(pLinkID);
    }
}
//----------------------------------------------------------------------------
bool InterfaceDescriptor::Register(Stream& rStream) const
{
    if( !Object::Register(rStream) )
    {
        return false;
    }

    for( int i = 0; i < (int)m_DescriptorItems.size(); i++ )
    {
        if( m_DescriptorItems[i] )
        {
            m_DescriptorItems[i]->Register(rStream);
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void InterfaceDescriptor::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    Object::Save(rStream);

    // link data
    int iCount = (int)m_DescriptorItems.size();
    rStream.Write(iCount);
    for( int i = 0; i < iCount; i++ )
    {
        rStream.Write(m_DescriptorItems[i]);
    }

    SE_END_DEBUG_STREAM_SAVE(InterfaceDescriptor);
}
//----------------------------------------------------------------------------
int InterfaceDescriptor::GetDiskUsed(const StreamVersion& rVersion) const
{
    int iSize = Object::GetDiskUsed(rVersion);

    int iCount = (int)m_DescriptorItems.size();
    iSize += sizeof(int) + iCount*sizeof(m_DescriptorItems[0]);

    return iSize;
}
//----------------------------------------------------------------------------
StringTree* InterfaceDescriptor::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));

    // children
    pTree->Append(Object::SaveStrings());

    for( int i = 0; i < (int)m_DescriptorItems.size(); i++ )
    {
        pTree->Append(m_DescriptorItems[i]->SaveStrings());
    }

    return pTree;
}
//----------------------------------------------------------------------------