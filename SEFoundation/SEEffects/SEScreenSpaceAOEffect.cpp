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
#include "SEScreenSpaceAOEffect.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, ScreenSpaceAOEffect, ShaderEffect);
SE_IMPLEMENT_STREAM(ScreenSpaceAOEffect);
SE_IMPLEMENT_DEFAULT_STREAM(ScreenSpaceAOEffect, ShaderEffect);
SE_IMPLEMENT_DEFAULT_NAME_ID(ScreenSpaceAOEffect, ShaderEffect);

//SE_REGISTER_STREAM(ScreenSpaceAOEffect);

SEVector2f ScreenSpaceAOEffect::ScreenSize = SEVector2f::ZERO; 
float ScreenSpaceAOEffect::FarClipDist = 0.0f;
bool ScreenSpaceAOEffect::ms_bUCInitialized = false;

//----------------------------------------------------------------------------
ScreenSpaceAOEffect::ScreenSpaceAOEffect(const std::string& rRandom, 
    const std::string& rDepth)
    :
    ShaderEffect(1)
{
    m_VShader[0] = SE_NEW VertexShader("ScreenSpaceAO.v_ScreenSpaceAO");
    m_PShader[0] = SE_NEW PixelShader("ScreenSpaceAO.p_ScreenSpaceAO");

    m_PShader[0]->SetTextureCount(2);
    m_PShader[0]->SetImageName(0, rRandom);
    m_PShader[0]->SetImageName(1, rDepth);
}
//----------------------------------------------------------------------------
ScreenSpaceAOEffect::ScreenSpaceAOEffect()
{
}
//----------------------------------------------------------------------------
ScreenSpaceAOEffect::~ScreenSpaceAOEffect()
{
}
//----------------------------------------------------------------------------
void ScreenSpaceAOEffect::OnLoadPrograms(int, Program*, 
    Program* pPProgram, Program*)
{
    if( !ms_bUCInitialized )
    {
        UserConstant* pUC = pPProgram->GetUC("kScreenSize");
        if( pUC )
            pUC->SetDataSource((float*)ScreenSize);

        pUC = pPProgram->GetUC("fFarClipDist");
        if( pUC )
            pUC->SetDataSource(&FarClipDist);

        ms_bUCInitialized = true;
    }
}
//----------------------------------------------------------------------------