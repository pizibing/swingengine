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

#include "SEDX10RendererPCH.h"
#include "SEDX10Renderer.h"
#include "SEDX10Resources.h"
#include "SEShaderEffect.h"

using namespace Swing;

DWORD DX10Renderer::ms_adwTexMinFilter[Texture::MAX_FILTER_TYPES] =
{
    0,  // Texture::MM_NEAREST
    0, // Texture::MM_LINEAR
    0,  // Texture::MM_NEAREST_NEAREST
    0,  // Texture::MM_NEAREST_LINEAR
    0, // Texture::MM_LINEAR_NEAREST
    0, // Texture::MM_LINEAR_LINEAR
};

DWORD DX10Renderer::ms_adwTexMipFilter[Texture::MAX_FILTER_TYPES] =
{
    0,   // Texture::MM_NEAREST
    0,   // Texture::MM_LINEAR
    0,  // Texture::MM_NEAREST_NEAREST
    0, // Texture::MM_NEAREST_LINEAR
    0,  // Texture::MM_LINEAR_NEAREST
    0, // Texture::MM_LINEAR_LINEAR
};

DWORD DX10Renderer::ms_adwTexWrapMode[Texture::MAX_WRAP_TYPES] =
{
    0,      // Texture::CLAMP
    0,       // Texture::REPEAT
    0,     // Texture::MIRRORED_REPEAT
    0,     // Texture::CLAMP_BORDER
    0,      // Texture::CLAMP_EDGE
};

//----------------------------------------------------------------------------
// 资源开启与关闭.
//----------------------------------------------------------------------------
void DX10Renderer::OnEnableVProgram(ResourceIdentifier* pID)
{
    VProgramID* pResource = (VProgramID*)pID;
    ms_hResult = cgD3D10BindProgram(pResource->ID);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX10Renderer::OnDisableVProgram(ResourceIdentifier*)
{
    m_pDX10Device->VSSetShader(0);
}
//----------------------------------------------------------------------------
void DX10Renderer::OnEnableGProgram(ResourceIdentifier* pID)
{
    GProgramID* pResource = (GProgramID*)pID;
    ms_hResult = cgD3D10BindProgram(pResource->ID);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX10Renderer::OnDisableGProgram(ResourceIdentifier*)
{
    m_pDX10Device->GSSetShader(0);
}
//----------------------------------------------------------------------------
void DX10Renderer::OnEnablePProgram(ResourceIdentifier* pID)
{
    PProgramID* pResource = (PProgramID*)pID;
    ms_hResult = cgD3D10BindProgram(pResource->ID);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX10Renderer::OnDisablePProgram(ResourceIdentifier*)
{
    m_pDX10Device->PSSetShader(0);
}
//----------------------------------------------------------------------------
void DX10Renderer::OnEnableTexture(ResourceIdentifier* pID)
{
    TextureID* pResource = (TextureID*)pID;
    Texture* pTexture = pResource->TextureObject;

    SamplerInformation* pSI = m_apActiveSamplers[m_iCurrentSampler];
    SamplerInformation::Type eSType = pSI->GetType();
    CGparameter hParam = (CGparameter)pSI->GetID();

    cgD3D10SetSamplerStateParameter(hParam, 0);
    cgD3D10SetTextureParameter(hParam, pResource->ID);
}
//----------------------------------------------------------------------------
void DX10Renderer::OnDisableTexture(ResourceIdentifier* pID)
{
    TextureID* pResource = (TextureID*)pID;
    Texture* pTexture = pResource->TextureObject;

    SamplerInformation* pSI = m_apActiveSamplers[m_iCurrentSampler];
    CGparameter hParam = (CGparameter)pSI->GetID();

    cgD3D10SetTextureParameter(hParam, 0);
}
//----------------------------------------------------------------------------
void DX10Renderer::OnEnableVBuffer(ResourceIdentifier* pID)
{
    VBufferID* pResource = (VBufferID*)pID;
    m_pDX10Device->IASetVertexBuffers(0, 1, &pResource->ID, 
        &pResource->VertexSize, &pResource->Offset);

    m_pDX10Device->IASetInputLayout(pResource->Layout);
}
//----------------------------------------------------------------------------
void DX10Renderer::OnDisableVBuffer(ResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void DX10Renderer::OnEnableIBuffer(ResourceIdentifier* pID)
{
    IBufferID* pResource = (IBufferID*)pID;
    m_pDX10Device->IASetIndexBuffer(pResource->ID, DXGI_FORMAT_R32_UINT, 0);
}
//----------------------------------------------------------------------------
void DX10Renderer::OnDisableIBuffer(ResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void DX10Renderer::OnEnableRenderStateBlock(ResourceIdentifier* pID)
{
    RStateBlockID* pResource = (RStateBlockID*)pID;

    if( pResource->BlendState )
    {
        float afBlendFactor[] = {0.0f, 0.0f, 0.0f, 0.0f};
        m_pDX10Device->OMSetBlendState(pResource->BlendState, afBlendFactor,
            0xffffffff);
    }

    if( pResource->DepthStencilState )
    {
        GlobalState* pState = 
            pResource->RStateBlock->States[GlobalState::STENCIL];
        StencilState* pStencilState = (StencilState*)pState;
        SE_ASSERT( pStencilState );

        m_pDX10Device->OMSetDepthStencilState(pResource->DepthStencilState,
            pStencilState->Reference);
    }

    if( pResource->RasterizerState )
    {
        m_pDX10Device->RSSetState(pResource->RasterizerState);
    }

}
//----------------------------------------------------------------------------
void DX10Renderer::OnDisableRenderStateBlock(ResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------