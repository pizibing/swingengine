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

SE_IMPLEMENT_RTTI(Swing, Polypoint, Geometry);
SE_IMPLEMENT_STREAM(Polypoint);
SE_IMPLEMENT_DEFAULT_NAME_ID(Polypoint, Geometry);

//SE_REGISTER_STREAM(Polypoint);

//----------------------------------------------------------------------------
Polypoint::Polypoint(VertexBuffer* pVBuffer)
    :
    Geometry(pVBuffer, 0)
{
    Type = GT_POLYPOINT;

    int iVCount = VBuffer->GetVertexCount();
    m_iActiveCount = iVCount;

    IBuffer = SE_NEW IndexBuffer(iVCount);
    int* aiIndex = IBuffer->GetData();
    for( int i = 0; i < iVCount; i++ )
    {
        aiIndex[i] = i;
    }
    LightingMode = GLM_DISABLE;
}
//----------------------------------------------------------------------------
Polypoint::Polypoint()
{
    Type = GT_POLYPOINT;
    m_iActiveCount = 0;
    LightingMode = GLM_DISABLE;
}
//----------------------------------------------------------------------------
Polypoint::~Polypoint()
{
}
//----------------------------------------------------------------------------
void Polypoint::SetActiveCount(int iActiveCount)
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
void Polypoint::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    Geometry::Load(rStream, pLink);

    // native data
    rStream.Read(m_iActiveCount);

    SE_END_DEBUG_STREAM_LOAD(Polypoint);
}
//----------------------------------------------------------------------------
void Polypoint::Link(Stream& rStream, Stream::Link* pLink)
{
    Geometry::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool Polypoint::Register(Stream& rStream) const
{
    return Geometry::Register(rStream);
}
//----------------------------------------------------------------------------
void Polypoint::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    Geometry::Save(rStream);

    // native data
    rStream.Write(m_iActiveCount);

    SE_END_DEBUG_STREAM_SAVE(Polypoint);
}
//----------------------------------------------------------------------------
int Polypoint::GetDiskUsed(const StreamVersion& rVersion) const
{
    return Geometry::GetDiskUsed(rVersion) +
        sizeof(m_iActiveCount);
}
//----------------------------------------------------------------------------
StringTree* Polypoint::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("active quantity =", m_iActiveCount));

    // children
    pTree->Append(Geometry::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
