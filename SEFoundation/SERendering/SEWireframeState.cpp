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
#include "SEWireframeState.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, WireframeState, GlobalState);
SE_IMPLEMENT_STREAM(WireframeState);
SE_IMPLEMENT_DEFAULT_NAME_ID(WireframeState, GlobalState);
SE_IMPLEMENT_INITIALIZE(WireframeState);
SE_IMPLEMENT_TERMINATE(WireframeState);

//SE_REGISTER_STREAM(WireframeState);
//SE_REGISTER_INITIALIZE(WireframeState);
//SE_REGISTER_TERMINATE(WireframeState);

//----------------------------------------------------------------------------
void WireframeState::Initialize()
{
    Default[WIREFRAME] = SE_NEW WireframeState;
}
//----------------------------------------------------------------------------
void WireframeState::Terminate()
{
    Default[WIREFRAME] = 0;
}
//----------------------------------------------------------------------------
WireframeState::WireframeState()
{
    Enabled = false;
}
//----------------------------------------------------------------------------
WireframeState::~WireframeState()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void WireframeState::Load(SEStream& rStream, SEStream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    GlobalState::Load(rStream, pLink);

    // native data
    rStream.Read(Enabled);

    SE_END_DEBUG_STREAM_LOAD(WireframeState);
}
//----------------------------------------------------------------------------
void WireframeState::Link(SEStream& rStream, SEStream::Link* pLink)
{
    GlobalState::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool WireframeState::Register(SEStream& rStream) const
{
    return GlobalState::Register(rStream);
}
//----------------------------------------------------------------------------
void WireframeState::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    GlobalState::Save(rStream);

    // native data
    rStream.Write(Enabled);

    SE_END_DEBUG_STREAM_SAVE(WireframeState);
}
//----------------------------------------------------------------------------
int WireframeState::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return GlobalState::GetDiskUsed(rVersion) +
        sizeof(char);  // Enabled
}
//----------------------------------------------------------------------------
SEStringTree* WireframeState::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("enabled =", Enabled));

    // children
    pTree->Append(GlobalState::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
