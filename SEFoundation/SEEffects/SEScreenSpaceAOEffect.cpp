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

SE_IMPLEMENT_RTTI(Swing, SEScreenSpaceAOEffect, SEShaderEffect);
SE_IMPLEMENT_STREAM(SEScreenSpaceAOEffect);
SE_IMPLEMENT_DEFAULT_STREAM(SEScreenSpaceAOEffect, SEShaderEffect);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEScreenSpaceAOEffect, SEShaderEffect);

//SE_REGISTER_STREAM(SEScreenSpaceAOEffect);

SEVector2f SEScreenSpaceAOEffect::ScreenSize = SEVector2f::ZERO; 
float SEScreenSpaceAOEffect::FarClipDist = 0.0f;
bool SEScreenSpaceAOEffect::ms_bUCInitialized = false;

//----------------------------------------------------------------------------
SEScreenSpaceAOEffect::SEScreenSpaceAOEffect(const std::string& rRandom, 
    const std::string& rDepth)
    :
    SEShaderEffect(1)
{
    m_VShader[0] = SE_NEW SEVertexShader("ScreenSpaceAO.v_ScreenSpaceAO");
    m_PShader[0] = SE_NEW SEPixelShader("ScreenSpaceAO.p_ScreenSpaceAO");

    m_PShader[0]->SetTextureCount(2);
    m_PShader[0]->SetImageName(0, rRandom);
    m_PShader[0]->SetImageName(1, rDepth);
}
//----------------------------------------------------------------------------
SEScreenSpaceAOEffect::SEScreenSpaceAOEffect()
{
}
//----------------------------------------------------------------------------
SEScreenSpaceAOEffect::~SEScreenSpaceAOEffect()
{
}
//----------------------------------------------------------------------------
void SEScreenSpaceAOEffect::OnLoadPrograms(int, SEProgram*, 
    SEProgram* pPProgram, SEProgram*)
{
    if( !ms_bUCInitialized )
    {
        SEUserConstant* pUC = pPProgram->GetUC("kScreenSize");
        if( pUC )
            pUC->SetDataSource((float*)ScreenSize);

        pUC = pPProgram->GetUC("fFarClipDist");
        if( pUC )
            pUC->SetDataSource(&FarClipDist);

        ms_bUCInitialized = true;
    }
}
//----------------------------------------------------------------------------