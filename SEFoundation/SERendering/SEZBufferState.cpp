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
#include "SEZBufferState.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, ZBufferState, GlobalState);
SE_IMPLEMENT_STREAM(ZBufferState);
SE_IMPLEMENT_DEFAULT_NAME_ID(ZBufferState, GlobalState);
SE_IMPLEMENT_INITIALIZE(ZBufferState);
SE_IMPLEMENT_TERMINATE(ZBufferState);

//SE_REGISTER_STREAM(ZBufferState);
//SE_REGISTER_INITIALIZE(ZBufferState);
//SE_REGISTER_TERMINATE(ZBufferState);

const char* ZBufferState::ms_pCompareMode[CF_COUNT] =
{
    "CF_NEVER",
    "CF_LESS",
    "CF_EQUAL",
    "CF_LEQUAL",
    "CF_GREATER",
    "CF_NOTEQUAL",
    "CF_GEQUAL",
    "CF_ALWAYS"
};

//----------------------------------------------------------------------------
void ZBufferState::Initialize()
{
    Default[ZBUFFER] = SE_NEW ZBufferState;
}
//----------------------------------------------------------------------------
void ZBufferState::Terminate()
{
    Default[ZBUFFER] = 0;
}
//----------------------------------------------------------------------------
ZBufferState::ZBufferState()
{
    Enabled = true;
    Writable = true;
    Compare = CF_LEQUAL;
}
//----------------------------------------------------------------------------
ZBufferState::~ZBufferState()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void ZBufferState::Load(SEStream& rStream, SEStream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    GlobalState::Load(rStream, pLink);

    // native data
    int iTemp;
    rStream.Read(Enabled);
    rStream.Read(Writable);
    rStream.Read(iTemp);
    Compare = (CompareMode)iTemp;

    SE_END_DEBUG_STREAM_LOAD(ZBufferState);
}
//----------------------------------------------------------------------------
void ZBufferState::Link(SEStream& rStream, SEStream::Link* pLink)
{
    GlobalState::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool ZBufferState::Register(SEStream& rStream) const
{
    return GlobalState::Register(rStream);
}
//----------------------------------------------------------------------------
void ZBufferState::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    GlobalState::Save(rStream);

    // native data
    rStream.Write(Enabled);
    rStream.Write(Writable);
    rStream.Write((int)Compare);

    SE_END_DEBUG_STREAM_SAVE(ZBufferState);
}
//----------------------------------------------------------------------------
int ZBufferState::GetDiskUsed (const SEStreamVersion& rVersion) const
{
    return GlobalState::GetDiskUsed(rVersion) +
        sizeof(char) + // Enabled
        sizeof(char) + // Writable
        sizeof(int);   // Compare
}
//----------------------------------------------------------------------------
SEStringTree* ZBufferState::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("enabled =", Enabled));
    pTree->Append(Format("writable = ", Writable));
    pTree->Append(Format("compare = ", ms_pCompareMode[Compare]));

    // children
    pTree->Append(GlobalState::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
