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
#include "SEPolypoint.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SEPolypoint, SEGeometry);
SE_IMPLEMENT_STREAM(SEPolypoint);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEPolypoint, SEGeometry);

//SE_REGISTER_STREAM(SEPolypoint);

//----------------------------------------------------------------------------
SEPolypoint::SEPolypoint(SEVertexBuffer* pVBuffer)
    :
    SEGeometry(pVBuffer, 0)
{
    Type = GT_POLYPOINT;

    int iVCount = VBuffer->GetVertexCount();
    m_iActiveCount = iVCount;

    IBuffer = SE_NEW SEIndexBuffer(iVCount);
    int* aiIndex = IBuffer->GetData();
    for( int i = 0; i < iVCount; i++ )
    {
        aiIndex[i] = i;
    }
    LightingMode = GLM_DISABLE;
}
//----------------------------------------------------------------------------
SEPolypoint::SEPolypoint()
{
    Type = GT_POLYPOINT;
    m_iActiveCount = 0;
    LightingMode = GLM_DISABLE;
}
//----------------------------------------------------------------------------
SEPolypoint::~SEPolypoint()
{
}
//----------------------------------------------------------------------------
void SEPolypoint::SetActiveCount(int iActiveCount)
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

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SEPolypoint::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEGeometry::Load(rStream, pLink);

    // native data
    rStream.Read(m_iActiveCount);

    SE_END_DEBUG_STREAM_LOAD(SEPolypoint);
}
//----------------------------------------------------------------------------
void SEPolypoint::SELink(SEStream& rStream, SEStream::SELink* pLink)
{
    SEGeometry::SELink(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SEPolypoint::Register(SEStream& rStream) const
{
    return SEGeometry::Register(rStream);
}
//----------------------------------------------------------------------------
void SEPolypoint::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEGeometry::Save(rStream);

    // native data
    rStream.Write(m_iActiveCount);

    SE_END_DEBUG_STREAM_SAVE(SEPolypoint);
}
//----------------------------------------------------------------------------
int SEPolypoint::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SEGeometry::GetDiskUsed(rVersion) +
        sizeof(m_iActiveCount);
}
//----------------------------------------------------------------------------
SEStringTree* SEPolypoint::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("active quantity =", m_iActiveCount));

    // children
    pTree->Append(SEGeometry::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
