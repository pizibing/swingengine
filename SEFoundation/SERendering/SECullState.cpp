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
#include "SECullState.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, CullState, GlobalState);
SE_IMPLEMENT_STREAM(CullState);
SE_IMPLEMENT_DEFAULT_NAME_ID(CullState, GlobalState);
SE_IMPLEMENT_INITIALIZE(CullState);
SE_IMPLEMENT_TERMINATE(CullState);

//SE_REGISTER_STREAM(CullState);
//SE_REGISTER_INITIALIZE(CullState);
//SE_REGISTER_TERMINATE(CullState);

const char* CullState::ms_pFrontMode[FT_COUNT] =
{
    "FT_CCW",
    "FT_CW"
};

const char* CullState::ms_pCullMode[CT_COUNT] =
{
    "CT_FRONT",
    "CT_BACK"
};

//----------------------------------------------------------------------------
void CullState::Initialize()
{
    Default[CULL] = SE_NEW CullState;
}
//----------------------------------------------------------------------------
void CullState::Terminate()
{
    Default[CULL] = 0;
}
//----------------------------------------------------------------------------
CullState::CullState()
{
    Enabled = true;
    FrontFace = FT_CW;
    CullFace = CT_BACK;
}
//----------------------------------------------------------------------------
CullState::~CullState()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void CullState::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    GlobalState::Load(rStream, pLink);

    // native data
    int iTemp;
    rStream.Read(Enabled);
    rStream.Read(iTemp);
    FrontFace = (FrontMode)iTemp;
    rStream.Read(iTemp);
    CullFace = (CullMode)iTemp;

    SE_END_DEBUG_STREAM_LOAD(CullState);
}
//----------------------------------------------------------------------------
void CullState::Link(Stream& rStream, Stream::Link* pLink)
{
    GlobalState::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool CullState::Register(Stream& rStream) const
{
    return GlobalState::Register(rStream);
}
//----------------------------------------------------------------------------
void CullState::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    GlobalState::Save(rStream);

    // native data
    rStream.Write(Enabled);
    rStream.Write((int)FrontFace);
    rStream.Write((int)CullFace);

    SE_END_DEBUG_STREAM_SAVE(CullState);
}
//----------------------------------------------------------------------------
int CullState::GetDiskUsed(const StreamVersion& rVersion) const
{
    return GlobalState::GetDiskUsed(rVersion) +
        sizeof(char) + // Enabled
        sizeof(int) + // FrontFace
        sizeof(int); // CullFace
}
//----------------------------------------------------------------------------
StringTree* CullState::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, (const char*)GetName()));
    pTree->Append(Format("enabled =", Enabled));
    pTree->Append(Format("front face = ", ms_pFrontMode[FrontFace]));
    pTree->Append(Format("cull face = ", ms_pCullMode[CullFace]));

    // children
    pTree->Append(GlobalState::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
