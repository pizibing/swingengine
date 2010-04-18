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

SE_IMPLEMENT_RTTI(Swing, SEZBufferState, SEGlobalState);
SE_IMPLEMENT_STREAM(SEZBufferState);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEZBufferState, SEGlobalState);
SE_IMPLEMENT_INITIALIZE(SEZBufferState);
SE_IMPLEMENT_TERMINATE(SEZBufferState);

//SE_REGISTER_STREAM(SEZBufferState);
//SE_REGISTER_INITIALIZE(SEZBufferState);
//SE_REGISTER_TERMINATE(SEZBufferState);

const char* SEZBufferState::ms_pCompareMode[CF_COUNT] =
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
void SEZBufferState::Initialize()
{
    Default[ZBUFFER] = SE_NEW SEZBufferState;
}
//----------------------------------------------------------------------------
void SEZBufferState::Terminate()
{
    Default[ZBUFFER] = 0;
}
//----------------------------------------------------------------------------
SEZBufferState::SEZBufferState()
{
    Enabled = true;
    Writable = true;
    Compare = CF_LEQUAL;
}
//----------------------------------------------------------------------------
SEZBufferState::~SEZBufferState()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SEZBufferState::Load(SEStream& rStream, SEStream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEGlobalState::Load(rStream, pLink);

    // native data
    int iTemp;
    rStream.Read(Enabled);
    rStream.Read(Writable);
    rStream.Read(iTemp);
    Compare = (CompareMode)iTemp;

    SE_END_DEBUG_STREAM_LOAD(SEZBufferState);
}
//----------------------------------------------------------------------------
void SEZBufferState::Link(SEStream& rStream, SEStream::Link* pLink)
{
    SEGlobalState::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SEZBufferState::Register(SEStream& rStream) const
{
    return SEGlobalState::Register(rStream);
}
//----------------------------------------------------------------------------
void SEZBufferState::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEGlobalState::Save(rStream);

    // native data
    rStream.Write(Enabled);
    rStream.Write(Writable);
    rStream.Write((int)Compare);

    SE_END_DEBUG_STREAM_SAVE(SEZBufferState);
}
//----------------------------------------------------------------------------
int SEZBufferState::GetDiskUsed (const SEStreamVersion& rVersion) const
{
    return SEGlobalState::GetDiskUsed(rVersion) +
        sizeof(char) + // Enabled
        sizeof(char) + // Writable
        sizeof(int);   // Compare
}
//----------------------------------------------------------------------------
SEStringTree* SEZBufferState::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("enabled =", Enabled));
    pTree->Append(Format("writable = ", Writable));
    pTree->Append(Format("compare = ", ms_pCompareMode[Compare]));

    // children
    pTree->Append(SEGlobalState::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
