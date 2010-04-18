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
#include "SESkinMaterialTextureEffect.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SkinMaterialTextureEffect, SkinEffect);
SE_IMPLEMENT_STREAM(SkinMaterialTextureEffect);
SE_IMPLEMENT_DEFAULT_STREAM(SkinMaterialTextureEffect, SkinEffect);
SE_IMPLEMENT_DEFAULT_NAME_ID(SkinMaterialTextureEffect, SkinEffect);

//SE_REGISTER_STREAM(SkinMaterialTextureEffect);

bool SkinMaterialTextureEffect::ms_bUCInitialized = false;

//----------------------------------------------------------------------------
SkinMaterialTextureEffect::SkinMaterialTextureEffect(const std::string& rBaseName,
    int iBoneCount, SENode** apBones, SETransformation* aOffset)
    :
    SkinEffect(iBoneCount, apBones, aOffset)
{
    m_VShader[0] = SE_NEW SEVertexShader(
        "SkinMaterialTexture.v_SkinMaterialTexture");
    m_PShader[0] = SE_NEW SEPixelShader(
        "SkinMaterialTexture.p_SkinMaterialTexture");

    m_PShader[0]->SetTextureCount(1);
    m_PShader[0]->SetImageName(0, rBaseName);
}
//----------------------------------------------------------------------------
SkinMaterialTextureEffect::SkinMaterialTextureEffect()
{
}
//----------------------------------------------------------------------------
SkinMaterialTextureEffect::~SkinMaterialTextureEffect()
{
}
//----------------------------------------------------------------------------
void SkinMaterialTextureEffect::OnLoadPrograms(int, SEProgram* pVProgram,
    SEProgram*, SEProgram*)
{
    if( !ms_bUCInitialized )
    {
        InitializeUserConstants(pVProgram);
        ms_bUCInitialized = true;
    }
}
//----------------------------------------------------------------------------