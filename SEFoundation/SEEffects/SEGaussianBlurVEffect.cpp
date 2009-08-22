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
#include "SEGaussianBlurVEffect.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, GaussianBlurVEffect, ShaderEffect);
SE_IMPLEMENT_STREAM(GaussianBlurVEffect);
SE_IMPLEMENT_DEFAULT_STREAM(GaussianBlurVEffect, ShaderEffect);
SE_IMPLEMENT_DEFAULT_NAME_ID(GaussianBlurVEffect, ShaderEffect);

//SE_REGISTER_STREAM(GaussianBlurVEffect);

Vector2f GaussianBlurVEffect::ms_aTexelKernel[KERNEL_COUNT] = 
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
Vector2f GaussianBlurVEffect::ms_aPixelKernelV[KERNEL_COUNT] = 
{
    Vector2f(0.0f, -6.0f),
    Vector2f(0.0f, -5.0f),
    Vector2f(0.0f, -4.0f),
    Vector2f(0.0f, -3.0f),
    Vector2f(0.0f, -2.0f),
    Vector2f(0.0f, -1.0f),
    Vector2f(0.0f, 0.0f),
    Vector2f(0.0f, 1.0f),
    Vector2f(0.0f, 2.0f),
    Vector2f(0.0f, 3.0f),
    Vector2f(0.0f, 4.0f),
    Vector2f(0.0f, 5.0f),
    Vector2f(0.0f, 6.0f)
};
bool GaussianBlurVEffect::ms_bTexelKernelUCInitialized = false;

//----------------------------------------------------------------------------
GaussianBlurVEffect::GaussianBlurVEffect(const String& rBaseName)
    :
    ShaderEffect(1)
{
    m_VShader[0] = SE_NEW VertexShader("Texture.v_Texture");
    m_PShader[0] = SE_NEW PixelShader("GaussianBlur.p_GaussianBlur");

    m_PShader[0]->SetTextureCount(1);
    m_PShader[0]->SetImageName(0, rBaseName);
}
//----------------------------------------------------------------------------
GaussianBlurVEffect::GaussianBlurVEffect()
{
}
//----------------------------------------------------------------------------
GaussianBlurVEffect::~GaussianBlurVEffect()
{
}
//----------------------------------------------------------------------------
void GaussianBlurVEffect::OnLoadPrograms(int, Program*, 
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
void GaussianBlurVEffect::GenerateTexelKernel(int iWidth, int iHeight)
{
    SE_ASSERT( iWidth > 0 && iHeight > 0 );

    for( int i = 0; i < KERNEL_COUNT; i++ )
    {
        ms_aTexelKernel[i].X = ms_aPixelKernelV[i].X / (float)iWidth;
        ms_aTexelKernel[i].Y = ms_aPixelKernelV[i].Y / (float)iHeight;
    }
}
//----------------------------------------------------------------------------