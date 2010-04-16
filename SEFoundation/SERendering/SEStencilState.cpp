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
#include "SEStencilState.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, StencilState, GlobalState);
SE_IMPLEMENT_STREAM(StencilState);
SE_IMPLEMENT_DEFAULT_NAME_ID(StencilState, GlobalState);
SE_IMPLEMENT_INITIALIZE(StencilState);
SE_IMPLEMENT_TERMINATE(StencilState);

//SE_REGISTER_STREAM(StencilState);
//SE_REGISTER_INITIALIZE(StencilState);
//SE_REGISTER_TERMINATE(StencilState);

const char* StencilState::ms_pCompare[StencilState::CF_COUNT] =
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

const char* StencilState::ms_pOperation[StencilState::OT_COUNT] =
{
    "OT_KEEP",
    "OT_ZERO",
    "OT_REPLACE",
    "OT_INCREMENT",
    "OT_DECREMENT",
    "OT_INVERT"
};

//----------------------------------------------------------------------------
void StencilState::Initialize()
{
    Default[STENCIL] = SE_NEW StencilState;
}
//----------------------------------------------------------------------------
void StencilState::Terminate()
{
    Default[STENCIL] = 0;
}
//----------------------------------------------------------------------------
StencilState::StencilState()
{
    Enabled = false;
    Compare = CF_NEVER;
    Reference = 0;
    Mask = (unsigned int)~0;
    WriteMask = (unsigned int)~0;
    OnFail = OT_KEEP;
    OnZFail = OT_KEEP;
    OnZPass = OT_KEEP;
}
//----------------------------------------------------------------------------
StencilState::~StencilState()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void StencilState::Load(SEStream& rStream, SEStream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    GlobalState::Load(rStream, pLink);

    // native data
    int iTemp;
    rStream.Read(Enabled);
    rStream.Read(iTemp);
    Compare = (CompareFunction)iTemp;
    rStream.Read(Reference);
    rStream.Read(Mask);
    rStream.Read(WriteMask);
    rStream.Read(iTemp);
    OnFail = (OperationType)iTemp;
    rStream.Read(iTemp);
    OnZFail = (OperationType)iTemp;
    rStream.Read(iTemp);
    OnZPass = (OperationType)iTemp;

    SE_END_DEBUG_STREAM_LOAD(StencilState);
}
//----------------------------------------------------------------------------
void StencilState::Link(SEStream& rStream, SEStream::Link* pLink)
{
    GlobalState::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool StencilState::Register(SEStream& rStream) const
{
    return GlobalState::Register(rStream);
}
//----------------------------------------------------------------------------
void StencilState::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    GlobalState::Save(rStream);

    // native data
    rStream.Write(Enabled);
    rStream.Write((int)Compare);
    rStream.Write(Reference);
    rStream.Write(Mask);
    rStream.Write(WriteMask);
    rStream.Write((int)OnFail);
    rStream.Write((int)OnZFail);
    rStream.Write((int)OnZPass);

    SE_END_DEBUG_STREAM_SAVE(StencilState);
}
//----------------------------------------------------------------------------
int StencilState::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return GlobalState::GetDiskUsed(rVersion) +
        sizeof(char) + // Enabled
        sizeof(int) +  // Compare
        sizeof(Reference) +
        sizeof(Mask) +
        sizeof(WriteMask) +
        sizeof(int) +  // OnFail
        sizeof(int) +  // OnZFail
        sizeof(int);   // OnZPass
}
//----------------------------------------------------------------------------
SEStringTree* StencilState::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("enabled =", Enabled));
    pTree->Append(Format("compare =", ms_pCompare[Compare]));
    pTree->Append(Format("reference =", Reference));
    pTree->Append(Format("mask =", Mask));
    pTree->Append(Format("write mask =", WriteMask));
    pTree->Append(Format("on fail =", ms_pOperation[OnFail]));
    pTree->Append(Format("on z-fail =", ms_pOperation[OnZFail]));
    pTree->Append(Format("on z-pass =", ms_pOperation[OnZPass]));

    // children
    pTree->Append(GlobalState::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
