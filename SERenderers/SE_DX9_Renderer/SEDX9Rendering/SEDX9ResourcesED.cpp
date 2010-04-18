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

#include "SEDX9RendererPCH.h"
#include "SEDX9Renderer.h"
#include "SEDX9Resources.h"
#include "SEShaderEffect.h"

using namespace Swing;

DWORD SEDX9Renderer::ms_adwTexMinFilter[SETexture::MAX_FILTER_TYPES] =
{
    D3DTEXF_POINT,  // SETexture::MM_NEAREST
    D3DTEXF_LINEAR, // SETexture::MM_LINEAR
    D3DTEXF_POINT,  // SETexture::MM_NEAREST_NEAREST
    D3DTEXF_POINT,  // SETexture::MM_NEAREST_LINEAR
    D3DTEXF_LINEAR, // SETexture::MM_LINEAR_NEAREST
    D3DTEXF_LINEAR, // SETexture::MM_LINEAR_LINEAR
};

DWORD SEDX9Renderer::ms_adwTexMipFilter[SETexture::MAX_FILTER_TYPES] =
{
    D3DTEXF_NONE,   // SETexture::MM_NEAREST
    D3DTEXF_NONE,   // SETexture::MM_LINEAR
    D3DTEXF_POINT,  // SETexture::MM_NEAREST_NEAREST
    D3DTEXF_LINEAR, // SETexture::MM_NEAREST_LINEAR
    D3DTEXF_POINT,  // SETexture::MM_LINEAR_NEAREST
    D3DTEXF_LINEAR, // SETexture::MM_LINEAR_LINEAR
};

DWORD SEDX9Renderer::ms_adwTexWrapMode[SETexture::MAX_WRAP_TYPES] =
{
    D3DTADDRESS_CLAMP,      // SETexture::CLAMP
    D3DTADDRESS_WRAP,       // SETexture::REPEAT
    D3DTADDRESS_MIRROR,     // SETexture::MIRRORED_REPEAT
    D3DTADDRESS_BORDER,     // SETexture::CLAMP_BORDER
    D3DTADDRESS_CLAMP,      // SETexture::CLAMP_EDGE
};

//----------------------------------------------------------------------------
// 资源开启与关闭.
//----------------------------------------------------------------------------
void SEDX9Renderer::SetVProgramRC(SERendererConstant* pRC)
{
    cgSetParameterValuefr((CGparameter)pRC->GetID(), pRC->GetDataCount(), 
        pRC->GetData());
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX9Renderer::SetVProgramUC(SEUserConstant* pUC)
{
    cgSetParameterValuefr((CGparameter)pUC->GetID(), pUC->GetDataCount(), 
        pUC->GetData());
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX9Renderer::SetGProgramRC(SERendererConstant* pRC)
{
    cgSetParameterValuefr((CGparameter)pRC->GetID(), pRC->GetDataCount(), 
        pRC->GetData());
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX9Renderer::SetGProgramUC(SEUserConstant* pUC)
{
    cgSetParameterValuefr((CGparameter)pUC->GetID(), pUC->GetDataCount(), 
        pUC->GetData());
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX9Renderer::SetPProgramRC(SERendererConstant* pRC)
{
    cgSetParameterValuefr((CGparameter)pRC->GetID(), pRC->GetDataCount(), 
        pRC->GetData());
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX9Renderer::SetPProgramUC(SEUserConstant* pUC)
{
    cgSetParameterValuefr((CGparameter)pUC->GetID(), pUC->GetDataCount(), 
        pUC->GetData());
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX9Renderer::UpdateVProgramConstants(SEVertexProgram* pVProgram)
{
    SEProgramData* pData = (SEProgramData*)pVProgram->UserData;
    cgUpdateProgramParameters(pData->ID);
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX9Renderer::UpdateGProgramConstants(SEGeometryProgram* pGProgram)
{
    SEProgramData* pData = (SEProgramData*)pGProgram->UserData;
    cgUpdateProgramParameters(pData->ID);
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX9Renderer::UpdatePProgramConstants(SEPixelProgram* pPProgram)
{
    SEProgramData* pData = (SEProgramData*)pPProgram->UserData;
    cgUpdateProgramParameters(pData->ID);
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnEnableVProgram(SEResourceIdentifier* pID)
{
    SEVProgramID* pResource = (SEVProgramID*)pID;
    ms_hResult = cgD3D9BindProgram(pResource->ID);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnDisableVProgram(SEResourceIdentifier*)
{
    ms_hResult = m_pDXDevice->SetVertexShader(0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnEnablePProgram(SEResourceIdentifier* pID)
{
    SEPProgramID* pResource = (SEPProgramID*)pID;
    ms_hResult = cgD3D9BindProgram(pResource->ID);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnDisablePProgram(SEResourceIdentifier*)
{
    ms_hResult = m_pDXDevice->SetPixelShader(0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnEnableTexture(SEResourceIdentifier* pID)
{
    SETextureID* pResource = (SETextureID*)pID;
    SETexture* pTexture = pResource->TextureObject;

    SESamplerInformation* pSI = m_apActiveSamplers[m_iCurrentSampler];
    SESamplerInformation::Type eSType = pSI->GetType();
    CGparameter hParam = (CGparameter)pSI->GetID();

    // Set the filter mode.
    SETexture::FilterType eFType = pTexture->GetFilterType();
    if( eFType == SETexture::NEAREST )
    {
        ms_hResult = cgD3D9SetSamplerState(hParam, D3DSAMP_MAGFILTER, 
            D3DTEXF_POINT);
        SE_ASSERT( SUCCEEDED(ms_hResult) );
    }
    else
    {
        ms_hResult = cgD3D9SetSamplerState(hParam, D3DSAMP_MAGFILTER, 
            D3DTEXF_LINEAR);
        SE_ASSERT( SUCCEEDED(ms_hResult) );
    }

    // Set the mipmap mode.
    ms_hResult = cgD3D9SetSamplerState(hParam, D3DSAMP_MINFILTER,
        ms_adwTexMinFilter[eFType]);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
    ms_hResult = cgD3D9SetSamplerState(hParam, D3DSAMP_MIPFILTER,
        ms_adwTexMipFilter[eFType]);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    // Set the border color (for clamp to border).
    const SEColorRGBA& rBorderColor = pTexture->GetBorderColor();
    ms_hResult = cgD3D9SetSamplerState(hParam, D3DSAMP_BORDERCOLOR, 
        D3DCOLOR_COLORVALUE(rBorderColor.R, rBorderColor.G, rBorderColor.B, 
        rBorderColor.A));
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    switch( eSType )
    {
    case SESamplerInformation::SAMPLER_1D:
    {
        ms_hResult = cgD3D9SetSamplerState(hParam, D3DSAMP_ADDRESSU, 
            ms_adwTexWrapMode[pTexture->GetWrapType(0)]);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        ms_hResult = cgD3D9SetSamplerState(hParam, D3DSAMP_ADDRESSV, 
            ms_adwTexWrapMode[pTexture->GetWrapType(0)]);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        break;
    }
    case SESamplerInformation::SAMPLER_2D:
    case SESamplerInformation::SAMPLER_PROJ:
    case SESamplerInformation::SAMPLER_CUBE:
    {
        ms_hResult = cgD3D9SetSamplerState(hParam, D3DSAMP_ADDRESSU, 
            ms_adwTexWrapMode[pTexture->GetWrapType(0)]);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        ms_hResult = cgD3D9SetSamplerState(hParam, D3DSAMP_ADDRESSV, 
            ms_adwTexWrapMode[pTexture->GetWrapType(1)]);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        break;
    }
    case SESamplerInformation::SAMPLER_3D:
    {
        ms_hResult = cgD3D9SetSamplerState(hParam, D3DSAMP_ADDRESSU, 
            ms_adwTexWrapMode[pTexture->GetWrapType(0)]);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        ms_hResult = cgD3D9SetSamplerState(hParam, D3DSAMP_ADDRESSV, 
            ms_adwTexWrapMode[pTexture->GetWrapType(1)]);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        ms_hResult = cgD3D9SetSamplerState(hParam, D3DSAMP_ADDRESSW, 
            ms_adwTexWrapMode[pTexture->GetWrapType(2)]);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        break;
    }
    default:
        SE_ASSERT( false );

        break;
    }

    ms_hResult = cgD3D9SetTexture(hParam, pResource->ID);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnDisableTexture(SEResourceIdentifier*)
{
    SESamplerInformation* pSI = m_apActiveSamplers[m_iCurrentSampler];
    CGparameter hParam = (CGparameter)pSI->GetID();

    ms_hResult = cgD3D9SetTexture(hParam, 0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnEnableVBuffer(SEResourceIdentifier* pID, 
    SEVertexProgram*)
{
    SEVBufferID* pResource = (SEVBufferID*)pID;
    ms_hResult = m_pDXDevice->SetStreamSource(0, pResource->ID, 0, 
        pResource->VertexSize);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    ms_hResult = m_pDXDevice->SetFVF(pResource->Format);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnDisableVBuffer(SEResourceIdentifier*, SEVertexProgram*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnEnableIBuffer(SEResourceIdentifier* pID)
{
    SEIBufferID* pResource = (SEIBufferID*)pID;
    ms_hResult = m_pDXDevice->SetIndices(pResource->ID);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnDisableIBuffer(SEResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------