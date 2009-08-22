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

#include "SEGaussianBlurVEffect2.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, GaussianBlurVEffect2, ShaderEffect);
SE_IMPLEMENT_STREAM(GaussianBlurVEffect2);
SE_IMPLEMENT_DEFAULT_STREAM(GaussianBlurVEffect2, ShaderEffect);
SE_IMPLEMENT_DEFAULT_NAME_ID(GaussianBlurVEffect2, ShaderEffect);

SE_REGISTER_STREAM(GaussianBlurVEffect2);

Vector3f GaussianBlurVEffect2::ms_TexelKernelStep = Vector3f::ZERO;
bool GaussianBlurVEffect2::ms_bUCInitialized = false;

//----------------------------------------------------------------------------
GaussianBlurVEffect2::GaussianBlurVEffect2(const String& rBaseName)
    :
    ShaderEffect(1)
{
    m_VShader[0] = SE_NEW VertexShader("GaussianBlur.main");
    m_PShader[0] = SE_NEW PixelShader("GaussianBlur.main");

    m_PShader[0]->SetTextureCount(1);
    m_PShader[0]->SetImageName(0, rBaseName);
}
//----------------------------------------------------------------------------
GaussianBlurVEffect2::GaussianBlurVEffect2()
{
}
//----------------------------------------------------------------------------
GaussianBlurVEffect2::~GaussianBlurVEffect2()
{
}
//----------------------------------------------------------------------------
void GaussianBlurVEffect2::OnLoadPrograms(int, Program* pVProgram, 
    Program*, Program*)
{
    if( !ms_bUCInitialized )
    {
        UserConstant* pUC = pVProgram->GetUC("TexelKernelStep");
        SE_ASSERT( pUC );

        if( pUC )
        {
            pUC->SetDataSource((float*)ms_TexelKernelStep);
        }

        ms_bUCInitialized = true;
    }
}
//----------------------------------------------------------------------------
void GaussianBlurVEffect2::GenerateTexelKernelStep(int iWidth, int iHeight)
{
    SE_ASSERT( iWidth > 0 && iHeight > 0 );

    ms_TexelKernelStep.X = 1.0f / (float)iWidth;
    ms_TexelKernelStep.Y = 1.0f / (float)iHeight;
    ms_TexelKernelStep.Z = 1.0f;
}
//----------------------------------------------------------------------------