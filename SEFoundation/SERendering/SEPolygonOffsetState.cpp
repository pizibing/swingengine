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
#include "SEPolygonOffsetState.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SEPolygonOffsetState, SEGlobalState);
SE_IMPLEMENT_STREAM(SEPolygonOffsetState);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEPolygonOffsetState, SEGlobalState);
SE_IMPLEMENT_INITIALIZE(SEPolygonOffsetState);
SE_IMPLEMENT_TERMINATE(SEPolygonOffsetState);

//SE_REGISTER_STREAM(SEPolygonOffsetState);
//SE_REGISTER_INITIALIZE(SEPolygonOffsetState);
//SE_REGISTER_TERMINATE(SEPolygonOffsetState);

//----------------------------------------------------------------------------
void SEPolygonOffsetState::Initialize()
{
    Default[POLYGONOFFSET] = SE_NEW SEPolygonOffsetState;
}
//----------------------------------------------------------------------------
void SEPolygonOffsetState::Terminate()
{
    Default[POLYGONOFFSET] = 0;
}
//----------------------------------------------------------------------------
SEPolygonOffsetState::SEPolygonOffsetState()
{
    FillEnabled = false;
    LineEnabled = false;
    PointEnabled = false;
    Scale = 0.0f;
    Bias = 0.0f;
}
//----------------------------------------------------------------------------
SEPolygonOffsetState::~SEPolygonOffsetState()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SEPolygonOffsetState::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEGlobalState::Load(rStream, pLink);

    // native data
    rStream.Read(FillEnabled);
    rStream.Read(LineEnabled);
    rStream.Read(PointEnabled);
    rStream.Read(Scale);
    rStream.Read(Bias);

    SE_END_DEBUG_STREAM_LOAD(SEPolygonOffsetState);
}
//----------------------------------------------------------------------------
void SEPolygonOffsetState::Link(SEStream& rStream, SEStream::SELink* pLink)
{
    SEGlobalState::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SEPolygonOffsetState::Register(SEStream& rStream) const
{
    return SEGlobalState::Register(rStream);
}
//----------------------------------------------------------------------------
void SEPolygonOffsetState::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEGlobalState::Save(rStream);

    // native data
    rStream.Write(FillEnabled);
    rStream.Write(LineEnabled);
    rStream.Write(PointEnabled);
    rStream.Write(Scale);
    rStream.Write(Bias);

    SE_END_DEBUG_STREAM_SAVE(SEPolygonOffsetState);
}
//----------------------------------------------------------------------------
int SEPolygonOffsetState::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SEGlobalState::GetDiskUsed(rVersion) +
        sizeof(char) + // FillEnabled
        sizeof(char) + // LineEnabled
        sizeof(char) + // PointEnabled
        sizeof(Scale) +
        sizeof(Bias);
}
//----------------------------------------------------------------------------
SEStringTree* SEPolygonOffsetState::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("fill enabled =", FillEnabled));
    pTree->Append(Format("line enabled =", LineEnabled));
    pTree->Append(Format("point enabled =", PointEnabled));
    pTree->Append(Format("scale =", Scale));
    pTree->Append(Format("bias =", Bias));

    // children
    pTree->Append(SEGlobalState::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
