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
#include "SEGaussianBlurHEffect.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SEGaussianBlurHEffect, SEShaderEffect);
SE_IMPLEMENT_STREAM(SEGaussianBlurHEffect);
SE_IMPLEMENT_DEFAULT_STREAM(SEGaussianBlurHEffect, SEShaderEffect);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEGaussianBlurHEffect, SEShaderEffect);

//SE_REGISTER_STREAM(SEGaussianBlurHEffect);

SEVector2f SEGaussianBlurHEffect::ms_aTexelKernel[KERNEL_COUNT] = 
{
    SEVector2f::ZERO,
    SEVector2f::ZERO,
    SEVector2f::ZERO,
    SEVector2f::ZERO,
    SEVector2f::ZERO,
    SEVector2f::ZERO,
    SEVector2f::ZERO,
    SEVector2f::ZERO,
    SEVector2f::ZERO,
    SEVector2f::ZERO,
    SEVector2f::ZERO,
    SEVector2f::ZERO,
    SEVector2f::ZERO
};
SEVector2f SEGaussianBlurHEffect::ms_aPixelKernelH[KERNEL_COUNT] = 
{
    SEVector2f(-6.0f, 0.0f),
    SEVector2f(-5.0f, 0.0f),
    SEVector2f(-4.0f, 0.0f),
    SEVector2f(-3.0f, 0.0f),
    SEVector2f(-2.0f, 0.0f),
    SEVector2f(-1.0f, 0.0f),
    SEVector2f(0.0f, 0.0f),
    SEVector2f(1.0f, 0.0f),
    SEVector2f(2.0f, 0.0f),
    SEVector2f(3.0f, 0.0f),
    SEVector2f(4.0f, 0.0f),
    SEVector2f(5.0f, 0.0f),
    SEVector2f(6.0f, 0.0f)
};
bool SEGaussianBlurHEffect::ms_bTexelKernelUCInitialized = false;

//----------------------------------------------------------------------------
SEGaussianBlurHEffect::SEGaussianBlurHEffect(const std::string& rBaseName)
    :
    SEShaderEffect(1)
{
    m_VShader[0] = SE_NEW SEVertexShader("SETexture.v_Texture");
    m_PShader[0] = SE_NEW SEPixelShader("GaussianBlur.p_GaussianBlur");

    m_PShader[0]->SetTextureCount(1);
    m_PShader[0]->SetImageName(0, rBaseName);
}
//----------------------------------------------------------------------------
SEGaussianBlurHEffect::SEGaussianBlurHEffect()
{
}
//----------------------------------------------------------------------------
SEGaussianBlurHEffect::~SEGaussianBlurHEffect()
{
}
//----------------------------------------------------------------------------
void SEGaussianBlurHEffect::OnLoadPrograms(int, SEProgram*, 
    SEProgram* pPProgram, SEProgram*)
{
    if( !ms_bTexelKernelUCInitialized )
    {
        char tempName[16]; // "TexelKernel[xx]"

        for( int i = 0; i < KERNEL_COUNT; i++ )
        {
            SESystem::SE_Sprintf(tempName, 16, "TexelKernel[%d]", i);
            SEUserConstant* pUC = pPProgram->GetUC(tempName);
            SE_ASSERT( pUC );

            if( pUC )
                pUC->SetDataSource((float*)ms_aTexelKernel[i]);
        }

        ms_bTexelKernelUCInitialized = true;
    }
}
//----------------------------------------------------------------------------
void SEGaussianBlurHEffect::GenerateTexelKernel(int iWidth, int iHeight)
{
    SE_ASSERT( iWidth > 0 && iHeight > 0 );

    for( int i = 0; i < KERNEL_COUNT; i++ )
    {
        ms_aTexelKernel[i].X = ms_aPixelKernelH[i].X / (float)iWidth;
        ms_aTexelKernel[i].Y = ms_aPixelKernelH[i].Y / (float)iHeight;
    }
}
//----------------------------------------------------------------------------