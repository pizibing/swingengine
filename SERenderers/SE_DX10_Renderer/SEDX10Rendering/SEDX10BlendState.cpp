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

using namespace Swing;

D3D10_BLEND DX10Renderer::ms_aeAlphaSrcBlend[AlphaState::SBF_COUNT] =
{
    D3D10_BLEND_ZERO,            // AlphaState::SBF_ZERO
    D3D10_BLEND_ONE,             // AlphaState::SBF_ONE
    D3D10_BLEND_DEST_COLOR,      // AlphaState::SBF_DST_COLOR
    D3D10_BLEND_INV_DEST_COLOR,  // AlphaState::SBF_ONE_MINUS_DST_COLOR
    D3D10_BLEND_SRC_ALPHA,       // AlphaState::SBF_SRC_ALPHA
    D3D10_BLEND_INV_SRC_ALPHA,   // AlphaState::SBF_ONE_MINUS_SRC_ALPHA
    D3D10_BLEND_DEST_ALPHA,      // AlphaState::SBF_DST_ALPHA
    D3D10_BLEND_INV_DEST_ALPHA,  // AlphaState::SBF_ONE_MINUS_DST_ALPHA
    D3D10_BLEND_SRC_ALPHA_SAT,   // AlphaState::SBF_SRC_ALPHA_SATURATE
    (D3D10_BLEND)0,              // AlphaState::SBF_CONSTANT_COLOR
    (D3D10_BLEND)0,              // AlphaState::SBF_ONE_MINUS_CONSTANT_COLOR
    (D3D10_BLEND)0,              // AlphaState::SBF_CONSTANT_ALPHA
    (D3D10_BLEND)0               // AlphaState::SBF_ONE_MINUS_CONSTANT_ALPHA
};

D3D10_BLEND DX10Renderer::ms_aeAlphaDstBlend[AlphaState::DBF_COUNT] =
{
    D3D10_BLEND_ZERO,            // AlphaState::DBF_ZERO
    D3D10_BLEND_ONE,             // AlphaState::DBF_ONE
    D3D10_BLEND_SRC_COLOR,       // AlphaState::DBF_SRC_COLOR
    D3D10_BLEND_INV_SRC_COLOR,   // AlphaState::DBF_ONE_MINUS_SRC_COLOR
    D3D10_BLEND_SRC_ALPHA,       // AlphaState::DBF_SRC_ALPHA
    D3D10_BLEND_INV_SRC_ALPHA,   // AlphaState::DBF_ONE_MINUS_SRC_ALPHA
    D3D10_BLEND_DEST_ALPHA,      // AlphaState::DBF_DST_ALPHA
    D3D10_BLEND_INV_DEST_ALPHA,  // AlphaState::DBF_ONE_MINUS_DST_ALPHA
    (D3D10_BLEND)0,              // AlphaState::DBF_CONSTANT_COLOR
    (D3D10_BLEND)0,              // AlphaState::DBF_ONE_MINUS_CONSTANT_COLOR
    (D3D10_BLEND)0,              // AlphaState::DBF_CONSTANT_ALPHA
    (D3D10_BLEND)0               // AlphaState::DBF_ONE_MINUS_CONSTANT_ALPHA
};

//----------------------------------------------------------------------------
void DX10Renderer::GenerateBlendState(const RenderStateBlock* pRStateBlock,
    ID3D10BlendState*& rpDX10BState)
{
    GlobalState* pState = pRStateBlock->States[GlobalState::ALPHA];

    // 检查是否需要创建一个blend state对象.
    if( !pState )
    {
        rpDX10BState = 0;
        return;
    }
    
    AlphaState* pAlphaState = (AlphaState*)pState;

    D3D10_BLEND_DESC tempBSDesc;
    memset(&tempBSDesc, 0, sizeof(D3D10_BLEND_DESC));

    tempBSDesc.AlphaToCoverageEnable = false;
    tempBSDesc.BlendOp = D3D10_BLEND_OP_ADD;
    tempBSDesc.BlendOpAlpha = D3D10_BLEND_OP_ADD;
    if( pAlphaState->BlendEnabled )
    {
        // 待实现.
        // 如何设置constant color的情况?
        tempBSDesc.BlendEnable[0] = true;
        tempBSDesc.SrcBlend = ms_aeAlphaSrcBlend[pAlphaState->SrcBlend];
        tempBSDesc.DestBlend = ms_aeAlphaDstBlend[pAlphaState->DstBlend];
        tempBSDesc.SrcBlendAlpha = ms_aeAlphaSrcBlend[pAlphaState->SrcBlend];
        tempBSDesc.DestBlendAlpha = ms_aeAlphaDstBlend[pAlphaState->DstBlend];
    }
    else
    {
        tempBSDesc.BlendEnable[0] = false;
    }
    tempBSDesc.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;

    ms_hResult = m_pDX10Device->CreateBlendState(&tempBSDesc, &rpDX10BState);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------