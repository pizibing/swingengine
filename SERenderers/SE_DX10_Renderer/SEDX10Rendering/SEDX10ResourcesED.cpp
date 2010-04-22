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

DWORD SEDX10Renderer::ms_adwTexMinFilter[SETexture::MAX_FILTER_TYPES] =
{
    0,  // SETexture::MM_NEAREST
    0, // SETexture::MM_LINEAR
    0,  // SETexture::MM_NEAREST_NEAREST
    0,  // SETexture::MM_NEAREST_LINEAR
    0, // SETexture::MM_LINEAR_NEAREST
    0, // SETexture::MM_LINEAR_LINEAR
};

DWORD SEDX10Renderer::ms_adwTexMipFilter[SETexture::MAX_FILTER_TYPES] =
{
    0,   // SETexture::MM_NEAREST
    0,   // SETexture::MM_LINEAR
    0,  // SETexture::MM_NEAREST_NEAREST
    0, // SETexture::MM_NEAREST_LINEAR
    0,  // SETexture::MM_LINEAR_NEAREST
    0, // SETexture::MM_LINEAR_LINEAR
};

DWORD SEDX10Renderer::ms_adwTexWrapMode[SETexture::MAX_WRAP_TYPES] =
{
    0,      // SETexture::CLAMP
    0,       // SETexture::REPEAT
    0,     // SETexture::MIRRORED_REPEAT
    0,     // SETexture::CLAMP_BORDER
    0,      // SETexture::CLAMP_EDGE
};

//----------------------------------------------------------------------------
// 资源开启与关闭.
//----------------------------------------------------------------------------
void SEDX10Renderer::SetVProgramRC(SERendererConstant* pRC)
{
    cgSetParameterValuefr((CGparameter)pRC->GetID(), pRC->GetDataCount(), 
        pRC->GetData());
    SE_DX10_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX10Renderer::SetVProgramUC(SEUserConstant* pUC)
{
    cgSetParameterValuefr((CGparameter)pUC->GetID(), pUC->GetDataCount(), 
        pUC->GetData());
    SE_DX10_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX10Renderer::SetGProgramRC(SERendererConstant* pRC)
{
    cgSetParameterValuefr((CGparameter)pRC->GetID(), pRC->GetDataCount(), 
        pRC->GetData());
    SE_DX10_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX10Renderer::SetGProgramUC(SEUserConstant* pUC)
{
    cgSetParameterValuefr((CGparameter)pUC->GetID(), pUC->GetDataCount(), 
        pUC->GetData());
    SE_DX10_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX10Renderer::SetPProgramRC(SERendererConstant* pRC)
{
    cgSetParameterValuefr((CGparameter)pRC->GetID(), pRC->GetDataCount(), 
        pRC->GetData());
    SE_DX10_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX10Renderer::SetPProgramUC(SEUserConstant* pUC)
{
    cgSetParameterValuefr((CGparameter)pUC->GetID(), pUC->GetDataCount(), 
        pUC->GetData());
    SE_DX10_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX10Renderer::UpdateVProgramConstants(SEVertexProgram* pVProgram)
{
    SEProgramData* pData = (SEProgramData*)pVProgram->UserData;
    cgUpdateProgramParameters(pData->ID);
    SE_DX10_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX10Renderer::UpdateGProgramConstants(SEGeometryProgram* pGProgram)
{
    SEProgramData* pData = (SEProgramData*)pGProgram->UserData;
    cgUpdateProgramParameters(pData->ID);
    SE_DX10_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX10Renderer::UpdatePProgramConstants(SEPixelProgram* pPProgram)
{
    SEProgramData* pData = (SEProgramData*)pPProgram->UserData;
    cgUpdateProgramParameters(pData->ID);
    SE_DX10_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX10Renderer::OnEnableVProgram(SEResourceIdentifier* pID)
{
    SEVProgramID* pResource = (SEVProgramID*)pID;
    ms_hResult = cgD3D10BindProgram(pResource->ID);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void SEDX10Renderer::OnDisableVProgram(SEResourceIdentifier*)
{
    m_pDX10Device->VSSetShader(0);
}
//----------------------------------------------------------------------------
void SEDX10Renderer::OnEnableGProgram(SEResourceIdentifier* pID)
{
    SEGProgramID* pResource = (SEGProgramID*)pID;
    ms_hResult = cgD3D10BindProgram(pResource->ID);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void SEDX10Renderer::OnDisableGProgram(SEResourceIdentifier*)
{
    m_pDX10Device->GSSetShader(0);
}
//----------------------------------------------------------------------------
void SEDX10Renderer::OnEnablePProgram(SEResourceIdentifier* pID)
{
    SEPProgramID* pResource = (SEPProgramID*)pID;
    ms_hResult = cgD3D10BindProgram(pResource->ID);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void SEDX10Renderer::OnDisablePProgram(SEResourceIdentifier*)
{
    m_pDX10Device->PSSetShader(0);
}
//----------------------------------------------------------------------------
void SEDX10Renderer::OnEnableTexture(SEResourceIdentifier* pID)
{
    SETextureID* pResource = (SETextureID*)pID;
    SETexture* pTexture = pResource->TextureObject;

    SESamplerInformation* pSI = m_apActiveSamplers[m_iCurrentSampler];
    SESamplerInformation::Type eSType = pSI->GetType();
    CGparameter hParam = (CGparameter)pSI->GetID();

    cgD3D10SetTextureParameter(hParam, pResource->ID);
    SE_DX10_DEBUG_CG_PROGRAM;

    cgD3D10SetSamplerStateParameter(hParam, 0);
    SE_DX10_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEDX10Renderer::OnDisableTexture(SEResourceIdentifier* pID)
{
    SETextureID* pResource = (SETextureID*)pID;
    SETexture* pTexture = pResource->TextureObject;

    SESamplerInformation* pSI = m_apActiveSamplers[m_iCurrentSampler];
    CGparameter hParam = (CGparameter)pSI->GetID();

    cgD3D10SetTextureParameter(hParam, 0);
}
//----------------------------------------------------------------------------
void SEDX10Renderer::OnEnableVBuffer(SEResourceIdentifier* pID, SEVertexProgram*)
{
    SEVBufferID* pResource = (SEVBufferID*)pID;
    m_pDX10Device->IASetVertexBuffers(0, 1, &pResource->ID, 
        &pResource->VertexSize, &pResource->Offset);

    m_pDX10Device->IASetInputLayout(pResource->Layout);
}
//----------------------------------------------------------------------------
void SEDX10Renderer::OnDisableVBuffer(SEResourceIdentifier*, SEVertexProgram*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void SEDX10Renderer::OnEnableIBuffer(SEResourceIdentifier* pID)
{
    SEIBufferID* pResource = (SEIBufferID*)pID;
    m_pDX10Device->IASetIndexBuffer(pResource->ID, DXGI_FORMAT_R32_UINT, 0);
}
//----------------------------------------------------------------------------
void SEDX10Renderer::OnDisableIBuffer(SEResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void SEDX10Renderer::OnEnableRenderStateBlock(SEResourceIdentifier* pID)
{
    SERStateBlockID* pResource = (SERStateBlockID*)pID;

    if( pResource->BlendState )
    {
        float afBlendFactor[] = {0.0f, 0.0f, 0.0f, 0.0f};
        m_pDX10Device->OMSetBlendState(pResource->BlendState, afBlendFactor,
            0xffffffff);
    }

    if( pResource->DepthStencilState )
    {
        SEGlobalState* pState = 
            pResource->RStateBlock->States[SEGlobalState::STENCIL];
        SEStencilState* pStencilState = (SEStencilState*)pState;
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
void SEDX10Renderer::OnDisableRenderStateBlock(SEResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------