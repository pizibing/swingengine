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

DWORD DX9Renderer::ms_adwTexMinFilter[Texture::MAX_FILTER_TYPES] =
{
    D3DTEXF_POINT,  // Texture::MM_NEAREST
    D3DTEXF_LINEAR, // Texture::MM_LINEAR
    D3DTEXF_POINT,  // Texture::MM_NEAREST_NEAREST
    D3DTEXF_POINT,  // Texture::MM_NEAREST_LINEAR
    D3DTEXF_LINEAR, // Texture::MM_LINEAR_NEAREST
    D3DTEXF_LINEAR, // Texture::MM_LINEAR_LINEAR
};

DWORD DX9Renderer::ms_adwTexMipFilter[Texture::MAX_FILTER_TYPES] =
{
    D3DTEXF_NONE,   // Texture::MM_NEAREST
    D3DTEXF_NONE,   // Texture::MM_LINEAR
    D3DTEXF_POINT,  // Texture::MM_NEAREST_NEAREST
    D3DTEXF_LINEAR, // Texture::MM_NEAREST_LINEAR
    D3DTEXF_POINT,  // Texture::MM_LINEAR_NEAREST
    D3DTEXF_LINEAR, // Texture::MM_LINEAR_LINEAR
};

DWORD DX9Renderer::ms_adwTexWrapMode[Texture::MAX_WRAP_TYPES] =
{
    D3DTADDRESS_CLAMP,      // Texture::CLAMP
    D3DTADDRESS_WRAP,       // Texture::REPEAT
    D3DTADDRESS_MIRROR,     // Texture::MIRRORED_REPEAT
    D3DTADDRESS_BORDER,     // Texture::CLAMP_BORDER
    D3DTADDRESS_CLAMP,      // Texture::CLAMP_EDGE
};

//----------------------------------------------------------------------------
// 资源开启与关闭.
//----------------------------------------------------------------------------
void DX9Renderer::SetVProgramRC(RendererConstant* pRC)
{
    cgSetParameterValuefr((CGparameter)pRC->GetID(), pRC->GetDataCount(), 
        pRC->GetData());
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void DX9Renderer::SetVProgramUC(UserConstant* pUC)
{
    cgSetParameterValuefr((CGparameter)pUC->GetID(), pUC->GetDataCount(), 
        pUC->GetData());
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void DX9Renderer::SetGProgramRC(RendererConstant* pRC)
{
    cgSetParameterValuefr((CGparameter)pRC->GetID(), pRC->GetDataCount(), 
        pRC->GetData());
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void DX9Renderer::SetGProgramUC(UserConstant* pUC)
{
    cgSetParameterValuefr((CGparameter)pUC->GetID(), pUC->GetDataCount(), 
        pUC->GetData());
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void DX9Renderer::SetPProgramRC(RendererConstant* pRC)
{
    cgSetParameterValuefr((CGparameter)pRC->GetID(), pRC->GetDataCount(), 
        pRC->GetData());
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void DX9Renderer::SetPProgramUC(UserConstant* pUC)
{
    cgSetParameterValuefr((CGparameter)pUC->GetID(), pUC->GetDataCount(), 
        pUC->GetData());
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void DX9Renderer::UpdateVProgramConstants(VertexProgram* pVProgram)
{
    ProgramData* pData = (ProgramData*)pVProgram->UserData;
    cgUpdateProgramParameters(pData->ID);
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void DX9Renderer::UpdateGProgramConstants(GeometryProgram* pGProgram)
{
    ProgramData* pData = (ProgramData*)pGProgram->UserData;
    cgUpdateProgramParameters(pData->ID);
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void DX9Renderer::UpdatePProgramConstants(PixelProgram* pPProgram)
{
    ProgramData* pData = (ProgramData*)pPProgram->UserData;
    cgUpdateProgramParameters(pData->ID);
    SE_DX9_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void DX9Renderer::OnEnableVProgram(ResourceIdentifier* pID)
{
    VProgramID* pResource = (VProgramID*)pID;
    ms_hResult = cgD3D9BindProgram(pResource->ID);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX9Renderer::OnDisableVProgram(ResourceIdentifier*)
{
    ms_hResult = m_pDXDevice->SetVertexShader(0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX9Renderer::OnEnablePProgram(ResourceIdentifier* pID)
{
    PProgramID* pResource = (PProgramID*)pID;
    ms_hResult = cgD3D9BindProgram(pResource->ID);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX9Renderer::OnDisablePProgram(ResourceIdentifier*)
{
    ms_hResult = m_pDXDevice->SetPixelShader(0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX9Renderer::OnEnableTexture(ResourceIdentifier* pID)
{
    TextureID* pResource = (TextureID*)pID;
    Texture* pTexture = pResource->TextureObject;

    SamplerInformation* pSI = m_apActiveSamplers[m_iCurrentSampler];
    SamplerInformation::Type eSType = pSI->GetType();
    CGparameter hParam = (CGparameter)pSI->GetID();

    // Set the filter mode.
    Texture::FilterType eFType = pTexture->GetFilterType();
    if( eFType == Texture::NEAREST )
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
    case SamplerInformation::SAMPLER_1D:
    {
        ms_hResult = cgD3D9SetSamplerState(hParam, D3DSAMP_ADDRESSU, 
            ms_adwTexWrapMode[pTexture->GetWrapType(0)]);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        ms_hResult = cgD3D9SetSamplerState(hParam, D3DSAMP_ADDRESSV, 
            ms_adwTexWrapMode[pTexture->GetWrapType(0)]);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        break;
    }
    case SamplerInformation::SAMPLER_2D:
    case SamplerInformation::SAMPLER_PROJ:
    case SamplerInformation::SAMPLER_CUBE:
    {
        ms_hResult = cgD3D9SetSamplerState(hParam, D3DSAMP_ADDRESSU, 
            ms_adwTexWrapMode[pTexture->GetWrapType(0)]);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        ms_hResult = cgD3D9SetSamplerState(hParam, D3DSAMP_ADDRESSV, 
            ms_adwTexWrapMode[pTexture->GetWrapType(1)]);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        break;
    }
    case SamplerInformation::SAMPLER_3D:
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
void DX9Renderer::OnDisableTexture(ResourceIdentifier*)
{
    SamplerInformation* pSI = m_apActiveSamplers[m_iCurrentSampler];
    CGparameter hParam = (CGparameter)pSI->GetID();

    ms_hResult = cgD3D9SetTexture(hParam, 0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX9Renderer::OnEnableVBuffer(ResourceIdentifier* pID, VertexProgram*)
{
    VBufferID* pResource = (VBufferID*)pID;
    ms_hResult = m_pDXDevice->SetStreamSource(0, pResource->ID, 0, 
        pResource->VertexSize);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    ms_hResult = m_pDXDevice->SetFVF(pResource->Format);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX9Renderer::OnDisableVBuffer(ResourceIdentifier*, VertexProgram*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void DX9Renderer::OnEnableIBuffer(ResourceIdentifier* pID)
{
    IBufferID* pResource = (IBufferID*)pID;
    ms_hResult = m_pDXDevice->SetIndices(pResource->ID);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX9Renderer::OnDisableIBuffer(ResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------