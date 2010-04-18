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

#include "SEGaussianBlurHEffect2.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, GaussianBlurHEffect2, SEShaderEffect);
SE_IMPLEMENT_STREAM(GaussianBlurHEffect2);
SE_IMPLEMENT_DEFAULT_STREAM(GaussianBlurHEffect2, SEShaderEffect);
SE_IMPLEMENT_DEFAULT_NAME_ID(GaussianBlurHEffect2, SEShaderEffect);

SE_REGISTER_STREAM(GaussianBlurHEffect2);

SEVector3f GaussianBlurHEffect2::ms_TexelKernelStep = SEVector3f::ZERO;
bool GaussianBlurHEffect2::ms_bUCInitialized = false;

//----------------------------------------------------------------------------
GaussianBlurHEffect2::GaussianBlurHEffect2(const std::string& rBaseName)
    :
    SEShaderEffect(1)
{
    m_VShader[0] = SE_NEW SEVertexShader("GaussianBlur.main");
    m_PShader[0] = SE_NEW SEPixelShader("GaussianBlur.main");

    m_PShader[0]->SetTextureCount(1);
    m_PShader[0]->SetImageName(0, rBaseName);
}
//----------------------------------------------------------------------------
GaussianBlurHEffect2::GaussianBlurHEffect2()
{
}
//----------------------------------------------------------------------------
GaussianBlurHEffect2::~GaussianBlurHEffect2()
{
}
//----------------------------------------------------------------------------
void GaussianBlurHEffect2::OnLoadPrograms(int, SEProgram* pVProgram, 
    SEProgram*, SEProgram*)
{
    if( !ms_bUCInitialized )
    {
        SEUserConstant* pUC = pVProgram->GetUC("TexelKernelStep");
        SE_ASSERT( pUC );

        if( pUC )
        {
            pUC->SetDataSource((float*)ms_TexelKernelStep);
        }

        ms_bUCInitialized = true;
    }
}
//----------------------------------------------------------------------------
void GaussianBlurHEffect2::GenerateTexelKernelStep(int iWidth, int iHeight)
{
    SE_ASSERT( iWidth > 0 && iHeight > 0 );

    ms_TexelKernelStep.X = 1.0f / (float)iWidth;
    ms_TexelKernelStep.Y = 1.0f / (float)iHeight;
    ms_TexelKernelStep.Z = 0.0f;
}
//----------------------------------------------------------------------------