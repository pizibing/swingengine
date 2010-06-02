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

SE_IMPLEMENT_RTTI(Swing, SEWireframeState, SEGlobalState);
SE_IMPLEMENT_STREAM(SEWireframeState);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEWireframeState, SEGlobalState);
SE_IMPLEMENT_INITIALIZE(SEWireframeState);
SE_IMPLEMENT_TERMINATE(SEWireframeState);

//SE_REGISTER_STREAM(SEWireframeState);
//SE_REGISTER_INITIALIZE(SEWireframeState);
//SE_REGISTER_TERMINATE(SEWireframeState);

//----------------------------------------------------------------------------
void SEWireframeState::Initialize()
{
    Default[WIREFRAME] = SE_NEW SEWireframeState;
}
//----------------------------------------------------------------------------
void SEWireframeState::Terminate()
{
    Default[WIREFRAME] = 0;
}
//----------------------------------------------------------------------------
SEWireframeState::SEWireframeState()
{
    Enabled = false;
}
//----------------------------------------------------------------------------
SEWireframeState::~SEWireframeState()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SEWireframeState::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEGlobalState::Load(rStream, pLink);

    // native data
    rStream.Read(Enabled);

    SE_END_DEBUG_STREAM_LOAD(SEWireframeState);
}
//----------------------------------------------------------------------------
void SEWireframeState::Link(SEStream& rStream, SEStream::SELink* pLink)
{
    SEGlobalState::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SEWireframeState::Register(SEStream& rStream) const
{
    return SEGlobalState::Register(rStream);
}
//----------------------------------------------------------------------------
void SEWireframeState::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEGlobalState::Save(rStream);

    // native data
    rStream.Write(Enabled);

    SE_END_DEBUG_STREAM_SAVE(SEWireframeState);
}
//----------------------------------------------------------------------------
int SEWireframeState::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SEGlobalState::GetDiskUsed(rVersion) +
        sizeof(char);  // Enabled
}
//----------------------------------------------------------------------------
SEStringTree* SEWireframeState::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("enabled =", Enabled));

    // children
    pTree->Append(SEGlobalState::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
