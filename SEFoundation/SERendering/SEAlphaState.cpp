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

SE_IMPLEMENT_RTTI(Swing, SEAlphaState, SEGlobalState);
SE_IMPLEMENT_STREAM(SEAlphaState);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEAlphaState, SEGlobalState);
SE_IMPLEMENT_INITIALIZE(SEAlphaState);
SE_IMPLEMENT_TERMINATE(SEAlphaState);

//SE_REGISTER_STREAM(SEAlphaState);
//SE_REGISTER_INITIALIZE(SEAlphaState);
//SE_REGISTER_TERMINATE(SEAlphaState);

const char* SEAlphaState::ms_pSrcBlend[SBF_COUNT] =
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

const char* SEAlphaState::ms_pDstBlend[DBF_COUNT] =
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

const char* SEAlphaState::ms_pTestMode[TF_COUNT] =
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
void SEAlphaState::Initialize()
{
    Default[ALPHA] = SE_NEW SEAlphaState;
}
//----------------------------------------------------------------------------
void SEAlphaState::Terminate()
{
    Default[ALPHA] = 0;
}
//----------------------------------------------------------------------------
SEAlphaState::SEAlphaState()
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
SEAlphaState::~SEAlphaState()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SEAlphaState::Load(SEStream& rStream, SEStream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEGlobalState::Load(rStream, pLink);

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

    SE_END_DEBUG_STREAM_LOAD(SEAlphaState);
}
//----------------------------------------------------------------------------
void SEAlphaState::Link(SEStream& rStream, SEStream::Link* pLink)
{
    SEGlobalState::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SEAlphaState::Register(SEStream& rStream) const
{
    return SEGlobalState::Register(rStream);
}
//----------------------------------------------------------------------------
void SEAlphaState::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEGlobalState::Save(rStream);

    // native data
    rStream.Write(BlendEnabled);
    rStream.Write((int)SrcBlend);
    rStream.Write((int)DstBlend);
    rStream.Write(TestEnabled);
    rStream.Write((int)Test);
    rStream.Write(Reference);

    SE_END_DEBUG_STREAM_SAVE(SEAlphaState);
}
//----------------------------------------------------------------------------
int SEAlphaState::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SEGlobalState::GetDiskUsed(rVersion) +
        sizeof(char) + // BlendEnabled
        sizeof(int) + // SrcBlend
        sizeof(int) +  // DstBlend
        sizeof(char) + // TestEnabled
        sizeof(int) + // Test
        sizeof(Reference);
}
//----------------------------------------------------------------------------
SEStringTree* SEAlphaState::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("blend =", BlendEnabled));
    pTree->Append(Format("src = ", ms_pSrcBlend[SrcBlend]));
    pTree->Append(Format("dst = ", ms_pDstBlend[DstBlend]));
    pTree->Append(Format("test =", TestEnabled));
    pTree->Append(Format("test func = ", ms_pTestMode[Test]));
    pTree->Append(Format("test ref =", Reference));

    // children
    pTree->Append(SEGlobalState::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
