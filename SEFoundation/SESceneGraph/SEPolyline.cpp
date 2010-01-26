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
#include "SEPolyline.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, Polyline, Geometry);
SE_IMPLEMENT_STREAM(Polyline);
SE_IMPLEMENT_DEFAULT_NAME_ID(Polyline, Geometry);

//SE_REGISTER_STREAM(Polyline);

//----------------------------------------------------------------------------
Polyline::Polyline(VertexBuffer* pVBuffer, bool bClosed, bool bContiguous)
    :
    Geometry(pVBuffer, 0)
{
    int iVCount = VBuffer->GetVertexCount();
    SE_ASSERT( iVCount >= 2 );

    m_iActiveCount = iVCount;
    m_bClosed = bClosed;
    m_bContiguous = bContiguous;

    // 为闭合线段多分配一个slot,aiIndex[iVCount] = aiIndex[0].
    IBuffer = SE_NEW IndexBuffer(iVCount+1);
    int* aiIndex = IBuffer->GetData();
    for( int i = 0; i < iVCount; i++ )
    {
        aiIndex[i] = i;
    }
    aiIndex[iVCount] = 0;

    if( !m_bContiguous || !m_bClosed )
    {
        // 如果是非闭合非连续线段,则让渲染器忽略掉额外的索引.
        IBuffer->SetIndexCount(iVCount);
    }

    SetGeometryType();
}
//----------------------------------------------------------------------------
Polyline::Polyline()
{
    m_iActiveCount = 0;
    m_bClosed = false;
    m_bContiguous = false;
    SetGeometryType();
}
//----------------------------------------------------------------------------
Polyline::~Polyline()
{
}
//----------------------------------------------------------------------------
void Polyline::SetGeometryType()
{
    if( m_bContiguous )
    {
        if( m_bClosed )
        {
            if( Type != GT_POLYLINE_CLOSED )
            {
                // 为闭合线段增加一个索引.
                IBuffer->SetIndexCount(IBuffer->GetIndexCount()+1);
                IBuffer->Release();
            }
            Type = GT_POLYLINE_CLOSED;
        }
        else
        {
            if( Type == GT_POLYLINE_CLOSED )
            {
                // Decrease the index count to account for closing the
                // polyline.
                IBuffer->SetIndexCount(IBuffer->GetIndexCount()-1);
                IBuffer->Release();
            }
            Type = GT_POLYLINE_OPEN;
        }
    }
    else
    {
        if( Type == GT_POLYLINE_CLOSED )
        {
            // Decrease the index count to account for closing the
            // polyline.
            IBuffer->SetIndexCount(IBuffer->GetIndexCount()-1);
            IBuffer->Release();
        }
        Type = GT_POLYLINE_SEGMENTS;
    }
}
//----------------------------------------------------------------------------
void Polyline::SetActiveCount(int iActiveCount)
{
    int iVCount = VBuffer->GetVertexCount();
    if( 0 <= iActiveCount && iActiveCount <= iVCount )
    {
        m_iActiveCount = iActiveCount;
    }
    else
    {
        m_iActiveCount = iVCount;
    }

    IBuffer->SetIndexCount(m_iActiveCount);
}
//----------------------------------------------------------------------------
void Polyline::SetClosed(bool bClosed)
{
    m_bClosed = bClosed;
    SetGeometryType();
}
//----------------------------------------------------------------------------
void Polyline::SetContiguous(bool bContiguous)
{
    m_bContiguous = bContiguous;
    SetGeometryType();
}
//----------------------------------------------------------------------------
ObjectPtr Polyline::Clone()
{
    Polyline* pClonedObject = SE_NEW Polyline(VBuffer, m_bClosed, 
        m_bContiguous);
    pClonedObject->Local = Local;

    int iECount = GetEffectCount();
    for( int i = 0; i < iECount; i++ )
    {
        pClonedObject->AttachEffect(GetEffect(i));
    }

    return pClonedObject;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void Polyline::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    Geometry::Load(rStream,pLink);

    // native data
    rStream.Read(m_iActiveCount);
    rStream.Read(m_bClosed);
    rStream.Read(m_bContiguous);

    SetGeometryType();

    SE_END_DEBUG_STREAM_LOAD(Polyline);
}
//----------------------------------------------------------------------------
void Polyline::Link(Stream& rStream, Stream::Link* pLink)
{
    Geometry::Link(rStream,pLink);
}
//----------------------------------------------------------------------------
bool Polyline::Register(Stream& rStream) const
{
    return Geometry::Register(rStream);
}
//----------------------------------------------------------------------------
void Polyline::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    Geometry::Save(rStream);

    // native data
    rStream.Write(m_iActiveCount);
    rStream.Write(m_bClosed);
    rStream.Write(m_bContiguous);

    SE_END_DEBUG_STREAM_SAVE(Polyline);
}
//----------------------------------------------------------------------------
int Polyline::GetDiskUsed(const StreamVersion& rVersion) const
{
    return Geometry::GetDiskUsed(rVersion) +
        sizeof(m_iActiveCount) +
        sizeof(char) + // m_bClosed
        sizeof(char);  // m_bContiguous
}
//----------------------------------------------------------------------------
StringTree* Polyline::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("active quantity =", m_iActiveCount));
    pTree->Append(Format("closed =", m_bClosed));
    pTree->Append(Format("contiguous =", m_bContiguous));

    // children
    pTree->Append(Geometry::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
