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
#include "SEIndexBuffer.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SEIndexBuffer, SEObject);
SE_IMPLEMENT_STREAM(SEIndexBuffer);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEIndexBuffer, SEObject);

//SE_REGISTER_STREAM(SEIndexBuffer);

//----------------------------------------------------------------------------
SEIndexBuffer::SEIndexBuffer(int iICount)
{
    SE_ASSERT( iICount > 0 );

    m_iICount = iICount;
    m_pIndex = SE_NEW int[m_iICount];
    memset(m_pIndex, 0, m_iICount * sizeof(int));
}
//----------------------------------------------------------------------------
SEIndexBuffer::SEIndexBuffer(const SEIndexBuffer* pIBuffer)
{
    SE_ASSERT(pIBuffer);

    m_iICount = pIBuffer->m_iICount;
    m_pIndex = SE_NEW int[m_iICount];
    size_t uiSize = m_iICount * sizeof(int);
    SESystem::SE_Memcpy(m_pIndex, uiSize, pIBuffer->m_pIndex, uiSize);
}
//----------------------------------------------------------------------------
SEIndexBuffer::SEIndexBuffer()
{
    m_iICount = 0;
    m_pIndex = 0;
}
//----------------------------------------------------------------------------
SEIndexBuffer::~SEIndexBuffer()
{
    // 通知所有使用此IB的renderer,资源即将被释放,
    // 从而允许renderer释放与此IB有关的资源(VRAM中)
    Release();

    SE_DELETE[] m_pIndex;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SEIndexBuffer::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEObject::Load(rStream, pLink);

    rStream.Read(m_iICount);
    m_pIndex = SE_NEW int[m_iICount];
    rStream.Read(m_iICount, m_pIndex);

    SE_END_DEBUG_STREAM_LOAD(SEIndexBuffer);
}
//----------------------------------------------------------------------------
void SEIndexBuffer::SELink(SEStream& rStream, SEStream::SELink* pLink)
{
    SEObject::SELink(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SEIndexBuffer::Register(SEStream& rStream) const
{
    return SEObject::Register(rStream);
}
//----------------------------------------------------------------------------
void SEIndexBuffer::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEObject::Save(rStream);
    rStream.Write(m_iICount);
    rStream.Write(m_iICount, m_pIndex);

    SE_END_DEBUG_STREAM_SAVE(SEIndexBuffer);
}
//----------------------------------------------------------------------------
int SEIndexBuffer::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SEObject::GetDiskUsed(rVersion) +
        sizeof(m_iICount) +
        m_iICount*sizeof(m_pIndex[0]);
}
//----------------------------------------------------------------------------
SEStringTree* SEIndexBuffer::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));

    // children
    pTree->Append(SEObject::SaveStrings());
    // this is very slow.
    //pTree->Append(Format(pTitle, m_iICount, m_pIndex));

    return pTree;
}
//----------------------------------------------------------------------------
