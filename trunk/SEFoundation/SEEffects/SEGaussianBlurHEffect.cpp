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

SE_IMPLEMENT_RTTI(Swing, GaussianBlurHEffect, ShaderEffect);
SE_IMPLEMENT_STREAM(GaussianBlurHEffect);
SE_IMPLEMENT_DEFAULT_STREAM(GaussianBlurHEffect, ShaderEffect);
SE_IMPLEMENT_DEFAULT_NAME_ID(GaussianBlurHEffect, ShaderEffect);

//SE_REGISTER_STREAM(GaussianBlurHEffect);

Vector2f GaussianBlurHEffect::ms_aTexelKernel[KERNEL_COUNT] = 
{
    Vector2f::ZERO,
    Vector2f::ZERO,
    Vector2f::ZERO,
    Vector2f::ZERO,
    Vector2f::ZERO,
    Vector2f::ZERO,
    Vector2f::ZERO,
    Vector2f::ZERO,
    Vector2f::ZERO,
    Vector2f::ZERO,
    Vector2f::ZERO,
    Vector2f::ZERO,
    Vector2f::ZERO
};
Vector2f GaussianBlurHEffect::ms_aPixelKernelH[KERNEL_COUNT] = 
{
    Vector2f(-6.0f, 0.0f),
    Vector2f(-5.0f, 0.0f),
    Vector2f(-4.0f, 0.0f),
    Vector2f(-3.0f, 0.0f),
    Vector2f(-2.0f, 0.0f),
    Vector2f(-1.0f, 0.0f),
    Vector2f(0.0f, 0.0f),
    Vector2f(1.0f, 0.0f),
    Vector2f(2.0f, 0.0f),
    Vector2f(3.0f, 0.0f),
    Vector2f(4.0f, 0.0f),
    Vector2f(5.0f, 0.0f),
    Vector2f(6.0f, 0.0f)
};
bool GaussianBlurHEffect::ms_bTexelKernelUCInitialized = false;

//----------------------------------------------------------------------------
GaussianBlurHEffect::GaussianBlurHEffect(const String& rBaseName)
    :
    ShaderEffect(1)
{
    m_VShader[0] = SE_NEW VertexShader("Texture.v_Texture");
    m_PShader[0] = SE_NEW PixelShader("GaussianBlur.p_GaussianBlur");

    m_PShader[0]->SetTextureCount(1);
    m_PShader[0]->SetImageName(0, rBaseName);
}
//----------------------------------------------------------------------------
GaussianBlurHEffect::GaussianBlurHEffect()
{
}
//----------------------------------------------------------------------------
GaussianBlurHEffect::~GaussianBlurHEffect()
{
}
//----------------------------------------------------------------------------
void GaussianBlurHEffect::OnLoadPrograms(int, Program*, 
    Program* pPProgram, Program*)
{
    if( !ms_bTexelKernelUCInitialized )
    {
        char tempName[16]; // "TexelKernel[xx]"

        for( int i = 0; i < KERNEL_COUNT; i++ )
        {
            System::SE_Sprintf(tempName, 16, "TexelKernel[%d]", i);
            UserConstant* pUC = pPProgram->GetUC(tempName);
            SE_ASSERT( pUC );

            if( pUC )
                pUC->SetDataSource((float*)ms_aTexelKernel[i]);
        }

        ms_bTexelKernelUCInitialized = true;
    }
}
//----------------------------------------------------------------------------
void GaussianBlurHEffect::GenerateTexelKernel(int iWidth, int iHeight)
{
    SE_ASSERT( iWidth > 0 && iHeight > 0 );

    for( int i = 0; i < KERNEL_COUNT; i++ )
    {
        ms_aTexelKernel[i].X = ms_aPixelKernelH[i].X / (float)iWidth;
        ms_aTexelKernel[i].Y = ms_aPixelKernelH[i].Y / (float)iHeight;
    }
}
//----------------------------------------------------------------------------