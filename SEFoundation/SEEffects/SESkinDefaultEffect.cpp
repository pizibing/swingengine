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
#include "SESkinDefaultEffect.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SkinDefaultEffect, SkinEffect);
SE_IMPLEMENT_STREAM(SkinDefaultEffect);
SE_IMPLEMENT_DEFAULT_STREAM(SkinDefaultEffect, SkinEffect);
SE_IMPLEMENT_DEFAULT_NAME_ID(SkinDefaultEffect, SkinEffect);

//SE_REGISTER_STREAM(SkinDefaultEffect);

bool SkinDefaultEffect::ms_bUCInitialized = false;

//----------------------------------------------------------------------------
SkinDefaultEffect::SkinDefaultEffect(int iBoneCount, SENode** apBones, 
    SETransformation* aOffset)
    :
    SkinEffect(iBoneCount, apBones, aOffset)
{
    m_VShader[0] = SE_NEW SEVertexShader("SkinDefault.v_SkinDefault");
    m_PShader[0] = SE_NEW SEPixelShader("SkinDefault.p_SkinDefault");
}
//----------------------------------------------------------------------------
SkinDefaultEffect::SkinDefaultEffect()
{
}
//----------------------------------------------------------------------------
SkinDefaultEffect::~SkinDefaultEffect()
{
}
//----------------------------------------------------------------------------
void SkinDefaultEffect::OnLoadPrograms(int, SEProgram* pVProgram, SEProgram*,
    SEProgram*)
{
    if( !ms_bUCInitialized )
    {
        InitializeUserConstants(pVProgram);
        ms_bUCInitialized = true;
    }
}
//----------------------------------------------------------------------------