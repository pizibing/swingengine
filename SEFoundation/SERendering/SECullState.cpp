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

SE_IMPLEMENT_RTTI(Swing, SECullState, SEGlobalState);
SE_IMPLEMENT_STREAM(SECullState);
SE_IMPLEMENT_DEFAULT_NAME_ID(SECullState, SEGlobalState);
SE_IMPLEMENT_INITIALIZE(SECullState);
SE_IMPLEMENT_TERMINATE(SECullState);

//SE_REGISTER_STREAM(SECullState);
//SE_REGISTER_INITIALIZE(SECullState);
//SE_REGISTER_TERMINATE(SECullState);

const char* SECullState::ms_pFrontMode[FT_COUNT] =
{
    "FT_CCW",
    "FT_CW"
};

const char* SECullState::ms_pCullMode[CT_COUNT] =
{
    "CT_FRONT",
    "CT_BACK"
};

//----------------------------------------------------------------------------
void SECullState::Initialize()
{
    Default[CULL] = SE_NEW SECullState;
}
//----------------------------------------------------------------------------
void SECullState::Terminate()
{
    Default[CULL] = 0;
}
//----------------------------------------------------------------------------
SECullState::SECullState()
{
    Enabled = true;
    FrontFace = FT_CW;
    CullFace = CT_BACK;
}
//----------------------------------------------------------------------------
SECullState::~SECullState()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SECullState::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEGlobalState::Load(rStream, pLink);

    // native data
    int iTemp;
    rStream.Read(Enabled);
    rStream.Read(iTemp);
    FrontFace = (FrontMode)iTemp;
    rStream.Read(iTemp);
    CullFace = (CullMode)iTemp;

    SE_END_DEBUG_STREAM_LOAD(SECullState);
}
//----------------------------------------------------------------------------
void SECullState::Link(SEStream& rStream, SEStream::SELink* pLink)
{
    SEGlobalState::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SECullState::Register(SEStream& rStream) const
{
    return SEGlobalState::Register(rStream);
}
//----------------------------------------------------------------------------
void SECullState::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEGlobalState::Save(rStream);

    // native data
    rStream.Write(Enabled);
    rStream.Write((int)FrontFace);
    rStream.Write((int)CullFace);

    SE_END_DEBUG_STREAM_SAVE(SECullState);
}
//----------------------------------------------------------------------------
int SECullState::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SEGlobalState::GetDiskUsed(rVersion) +
        sizeof(char) + // Enabled
        sizeof(int) + // FrontFace
        sizeof(int); // CullFace
}
//----------------------------------------------------------------------------
SEStringTree* SECullState::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("enabled =", Enabled));
    pTree->Append(Format("front face = ", ms_pFrontMode[FrontFace]));
    pTree->Append(Format("cull face = ", ms_pCullMode[CullFace]));

    // children
    pTree->Append(SEGlobalState::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
