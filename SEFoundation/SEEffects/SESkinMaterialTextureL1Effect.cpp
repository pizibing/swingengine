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
#include "SESkinMaterialTextureL1Effect.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SkinMaterialTextureL1Effect, SkinEffect);
SE_IMPLEMENT_STREAM(SkinMaterialTextureL1Effect);
SE_IMPLEMENT_DEFAULT_STREAM(SkinMaterialTextureL1Effect, SkinEffect);
SE_IMPLEMENT_DEFAULT_NAME_ID(SkinMaterialTextureL1Effect, SkinEffect);

//SE_REGISTER_STREAM(SkinMaterialTextureL1Effect);

bool SkinMaterialTextureL1Effect::ms_bUCInitialized = false;

//----------------------------------------------------------------------------
SkinMaterialTextureL1Effect::SkinMaterialTextureL1Effect(
    const std::string& rBaseName, int iBoneCount, Node** apBones, 
    Transformation* aOffset)
    :
    SkinEffect(iBoneCount, apBones, aOffset)
{
    m_VShader[0] = SE_NEW VertexShader(
        "SkinMaterialTextureL1.v_SkinMaterialTextureL1");
    m_PShader[0] = SE_NEW PixelShader(
        "SkinMaterialTextureL1.p_SkinMaterialTextureL1");

    m_PShader[0]->SetTextureCount(1);
    m_PShader[0]->SetImageName(0, rBaseName);
}
//----------------------------------------------------------------------------
SkinMaterialTextureL1Effect::SkinMaterialTextureL1Effect()
{
}
//----------------------------------------------------------------------------
SkinMaterialTextureL1Effect::~SkinMaterialTextureL1Effect()
{
}
//----------------------------------------------------------------------------
void SkinMaterialTextureL1Effect::OnLoadPrograms(int, Program* pVProgram,
    Program*, Program*)
{
    if( !ms_bUCInitialized )
    {
        InitializeUserConstants(pVProgram);
        ms_bUCInitialized = true;
    }
}
//----------------------------------------------------------------------------