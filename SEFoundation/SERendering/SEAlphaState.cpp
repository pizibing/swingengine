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
#include "SEAlphaState.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, AlphaState, GlobalState);
SE_IMPLEMENT_STREAM(AlphaState);
SE_IMPLEMENT_DEFAULT_NAME_ID(AlphaState, GlobalState);
SE_IMPLEMENT_INITIALIZE(AlphaState);
SE_IMPLEMENT_TERMINATE(AlphaState);

//SE_REGISTER_STREAM(AlphaState);
//SE_REGISTER_INITIALIZE(AlphaState);
//SE_REGISTER_TERMINATE(AlphaState);

const char* AlphaState::ms_pSrcBlend[SBF_COUNT] =
{
    "SBF_ZERO",
    "SBF_ONE",
    "SBF_DST_COLOR",
    "SBF_ONE_MINUS_DST_COLOR",
    "SBF_SRC_ALPHA",
    "SBF_ONE_MINUS_SRC_ALPHA",
    "SBF_DST_ALPHA",
    "SBF_ONE_MINUS_DST_ALPHA",
    "SBF_SRC_ALPHA_SATURATE",
    "SBF_CONSTANT_COLOR",
    "SBF_ONE_MINUS_CONSTANT_COLOR",
    "SBF_CONSTANT_ALPHA",
    "SBF_ONE_MINUS_CONSTANT_ALPHA"
};

const char* AlphaState::ms_pDstBlend[DBF_COUNT] =
{
    "DBF_ZERO",
    "DBF_ONE",
    "DBF_SRC_COLOR",
    "DBF_ONE_MINUS_SRC_COLOR",
    "DBF_SRC_ALPHA",
    "DBF_ONE_MINUS_SRC_ALPHA",
    "DBF_DST_ALPHA",
    "DBF_ONE_MINUS_DST_ALPHA",
    "DBF_CONSTANT_COLOR",
    "DBF_ONE_MINUS_CONSTANT_COLOR",
    "DBF_CONSTANT_ALPHA",
    "DBF_ONE_MINUS_CONSTANT_ALPHA"
};

const char* AlphaState::ms_pTestMode[TF_COUNT] =
{
    "TF_NEVER",
    "TF_LESS",
    "TF_EQUAL",
    "TF_LEQUAL",
    "TF_GREATER",
    "TF_NOTEQUAL",
    "TF_GEQUAL",
    "TF_ALWAYS"
};

//----------------------------------------------------------------------------
void AlphaState::Initialize()
{
    Default[ALPHA] = SE_NEW AlphaState;
}
//----------------------------------------------------------------------------
void AlphaState::Terminate()
{
    Default[ALPHA] = 0;
}
//----------------------------------------------------------------------------
AlphaState::AlphaState()
    :
    ConstantColor(0.0f,0.0f,0.0f,0.0f)
{
    BlendEnabled = false;
    SrcBlend = SBF_SRC_ALPHA;
    DstBlend = DBF_ONE_MINUS_SRC_ALPHA;
    TestEnabled = false;
    Test = TF_ALWAYS;
    Reference = 0.0f;
}
//----------------------------------------------------------------------------
AlphaState::~AlphaState()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void AlphaState::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    GlobalState::Load(rStream, pLink);

    // native data
    int iTemp;
    rStream.Read(BlendEnabled);
    rStream.Read(iTemp);
    SrcBlend = (SrcBlendMode)iTemp;
    rStream.Read(iTemp);
    DstBlend = (DstBlendMode)iTemp;
    rStream.Read(TestEnabled);
    rStream.Read(iTemp);
    Test = (TestMode)iTemp;
    rStream.Read(Reference);

    SE_END_DEBUG_STREAM_LOAD(AlphaState);
}
//----------------------------------------------------------------------------
void AlphaState::Link(Stream& rStream, Stream::Link* pLink)
{
    GlobalState::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool AlphaState::Register(Stream& rStream) const
{
    return GlobalState::Register(rStream);
}
//----------------------------------------------------------------------------
void AlphaState::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    GlobalState::Save(rStream);

    // native data
    rStream.Write(BlendEnabled);
    rStream.Write((int)SrcBlend);
    rStream.Write((int)DstBlend);
    rStream.Write(TestEnabled);
    rStream.Write((int)Test);
    rStream.Write(Reference);

    SE_END_DEBUG_STREAM_SAVE(AlphaState);
}
//----------------------------------------------------------------------------
int AlphaState::GetDiskUsed(const StreamVersion& rVersion) const
{
    return GlobalState::GetDiskUsed(rVersion) +
        sizeof(char) + // BlendEnabled
        sizeof(int) + // SrcBlend
        sizeof(int) +  // DstBlend
        sizeof(char) + // TestEnabled
        sizeof(int) + // Test
        sizeof(Reference);
}
//----------------------------------------------------------------------------
StringTree* AlphaState::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("blend =", BlendEnabled));
    pTree->Append(Format("src = ", ms_pSrcBlend[SrcBlend]));
    pTree->Append(Format("dst = ", ms_pDstBlend[DstBlend]));
    pTree->Append(Format("test =", TestEnabled));
    pTree->Append(Format("test func = ", ms_pTestMode[Test]));
    pTree->Append(Format("test ref =", Reference));

    // children
    pTree->Append(GlobalState::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
