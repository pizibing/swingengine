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

D3D10_CULL_MODE SEDX10Renderer::ms_aeCullModel[SECullState::CT_COUNT] = 
{
    D3D10_CULL_FRONT,
    D3D10_CULL_BACK
};

//----------------------------------------------------------------------------
void SEDX10Renderer::GenerateRasterizerState(
    const SERenderStateBlock* pRStateBlock, 
    ID3D10RasterizerState*& rpDX10RState)
{
    SEGlobalState* pState = pRStateBlock->States[SEGlobalState::WIREFRAME];
    SEWireframeState* pWireframeState = (SEWireframeState*)pState;
    pState = pRStateBlock->States[SEGlobalState::CULL];
    SECullState* pCullState = (SECullState*)pState;
    pState = pRStateBlock->States[SEGlobalState::POLYGONOFFSET];
    SEPolygonOffsetState* pPolygonOffsetState = (SEPolygonOffsetState*)pState;

    // 检查是否需要创建一个rasterizer state对象.
    if( !pWireframeState && !pCullState && !pPolygonOffsetState )
    {
        rpDX10RState = 0;
        return;
    }

    D3D10_RASTERIZER_DESC tempRSDesc;
    memset(&tempRSDesc, 0, sizeof(D3D10_RASTERIZER_DESC));

    // 填充wireframe state相关参数.
    if( !pWireframeState )
    {
        pState = SEGlobalState::Default[SEGlobalState::WIREFRAME];
        pWireframeState = (SEWireframeState*)pState;
    }
    SE_ASSERT( pWireframeState );

    if( pWireframeState->Enabled )
    {
        tempRSDesc.FillMode = D3D10_FILL_WIREFRAME;
    }
    else
    {
        tempRSDesc.FillMode = D3D10_FILL_SOLID;
    }

    // 填充cull state相关参数.
    if( !pCullState )
    {
        pState = SEGlobalState::Default[SEGlobalState::CULL];
        pCullState = (SECullState*)pState;
    }
    SE_ASSERT( pCullState );

    if( pCullState->Enabled )
    {
        if( pCullState->FrontFace == SECullState::FT_CW )
        {
            tempRSDesc.FrontCounterClockwise = false;
        }
        else
        {
            tempRSDesc.FrontCounterClockwise = true;
        }

        if( !m_bReverseCullFace )
        {
            tempRSDesc.CullMode = ms_aeCullModel[pCullState->CullFace];
        }
        else
        {
            if( ms_aeCullModel[pCullState->CullFace] == D3D10_CULL_BACK )
            {
                tempRSDesc.CullMode = D3D10_CULL_FRONT;
            }
            else
            {
                tempRSDesc.CullMode = D3D10_CULL_BACK;
            }
        }
    }
    else
    {
        tempRSDesc.CullMode = D3D10_CULL_NONE;
    }

    // 填充polygon offset state相关参数.
    if( !pPolygonOffsetState )
    {
        pState = SEGlobalState::Default[SEGlobalState::POLYGONOFFSET];
        pPolygonOffsetState = (SEPolygonOffsetState*)pState;
    }
    SE_ASSERT( pPolygonOffsetState );

    tempRSDesc.DepthBias = 0;
    tempRSDesc.DepthBiasClamp = 0.0f;
    tempRSDesc.SlopeScaledDepthBias = pPolygonOffsetState->Scale;

    // 其他默认参数.
    tempRSDesc.ScissorEnable = false;
    tempRSDesc.MultisampleEnable = false;
    tempRSDesc.AntialiasedLineEnable = false;

    ms_hResult = m_pDX10Device->CreateRasterizerState(&tempRSDesc, 
        &rpDX10RState);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------