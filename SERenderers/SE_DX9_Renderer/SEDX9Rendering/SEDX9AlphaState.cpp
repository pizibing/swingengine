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

using namespace Swing;

DWORD DX9Renderer::ms_adwAlphaSrcBlend[AlphaState::SBF_COUNT] =
{
    D3DBLEND_ZERO,          // AlphaState::SBF_ZERO
    D3DBLEND_ONE,           // AlphaState::SBF_ONE
    D3DBLEND_DESTCOLOR,     // AlphaState::SBF_DST_COLOR
    D3DBLEND_INVDESTCOLOR,  // AlphaState::SBF_ONE_MINUS_DST_COLOR
    D3DBLEND_SRCALPHA,      // AlphaState::SBF_SRC_ALPHA
    D3DBLEND_INVSRCALPHA,   // AlphaState::SBF_ONE_MINUS_SRC_ALPHA
    D3DBLEND_DESTALPHA,     // AlphaState::SBF_DST_ALPHA
    D3DBLEND_INVDESTALPHA,  // AlphaState::SBF_ONE_MINUS_DST_ALPHA
    D3DBLEND_SRCALPHASAT,   // AlphaState::SBF_SRC_ALPHA_SATURATE
    0,                      // AlphaState::SBF_CONSTANT_COLOR
    0,                      // AlphaState::SBF_ONE_MINUS_CONSTANT_COLOR
    0,                      // AlphaState::SBF_CONSTANT_ALPHA
    0                       // AlphaState::SBF_ONE_MINUS_CONSTANT_ALPHA
};

DWORD DX9Renderer::ms_adwAlphaDstBlend[AlphaState::DBF_COUNT] =
{
    D3DBLEND_ZERO,          // AlphaState::DBF_ZERO
    D3DBLEND_ONE,           // AlphaState::DBF_ONE
    D3DBLEND_SRCCOLOR,      // AlphaState::DBF_SRC_COLOR
    D3DBLEND_INVSRCCOLOR,   // AlphaState::DBF_ONE_MINUS_SRC_COLOR
    D3DBLEND_SRCALPHA,      // AlphaState::DBF_SRC_ALPHA
    D3DBLEND_INVSRCALPHA,   // AlphaState::DBF_ONE_MINUS_SRC_ALPHA
    D3DBLEND_DESTALPHA,     // AlphaState::DBF_DST_ALPHA
    D3DBLEND_INVDESTALPHA,  // AlphaState::DBF_ONE_MINUS_DST_ALPHA
    0,                      // AlphaState::DBF_CONSTANT_COLOR
    0,                      // AlphaState::DBF_ONE_MINUS_CONSTANT_COLOR
    0,                      // AlphaState::DBF_CONSTANT_ALPHA
    0                       // AlphaState::DBF_ONE_MINUS_CONSTANT_ALPHA
};

DWORD DX9Renderer::ms_adwAlphaTest[AlphaState::TF_COUNT] =
{
    D3DCMP_NEVER,           // AlphaState::TF_NEVER
    D3DCMP_LESS,            // AlphaState::TF_LESS
    D3DCMP_EQUAL,           // AlphaState::TF_EQUAL
    D3DCMP_LESSEQUAL,       // AlphaState::TF_LEQUAL
    D3DCMP_GREATER,         // AlphaState::TF_GREATER
    D3DCMP_NOTEQUAL,        // AlphaState::TF_NOTEQUAL
    D3DCMP_GREATEREQUAL,    // AlphaState::TF_GEQUAL
    D3DCMP_ALWAYS           // AlphaState::TF_ALWAYS
};

//----------------------------------------------------------------------------
void DX9Renderer::SetAlphaState(AlphaState* pState)
{
    Renderer::SetAlphaState(pState);

    if( pState->BlendEnabled )
    {
        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        DWORD dwSrcBlend = ms_adwAlphaSrcBlend[pState->SrcBlend];
        DWORD dwSrcConstantColor = 0;
        if( dwSrcBlend > 0 )
        {
            dwSrcConstantColor = 0;
        }
        else  // CONSTANT format
        {
            switch( pState->SrcBlend )
            {
            case AlphaState::SBF_CONSTANT_COLOR:
                dwSrcBlend = D3DBLEND_BLENDFACTOR;
                dwSrcConstantColor = D3DCOLOR_COLORVALUE(
                    pState->ConstantColor.R, pState->ConstantColor.G,
                    pState->ConstantColor.B, pState->ConstantColor.A);
                break;
            case AlphaState::SBF_ONE_MINUS_CONSTANT_COLOR:
                dwSrcBlend = D3DBLEND_INVBLENDFACTOR;
                dwSrcConstantColor = D3DCOLOR_COLORVALUE(
                    pState->ConstantColor.R, pState->ConstantColor.G,
                    pState->ConstantColor.B, pState->ConstantColor.A);
                break;
            case AlphaState::SBF_CONSTANT_ALPHA:
                dwSrcBlend = D3DBLEND_BLENDFACTOR;
                dwSrcConstantColor = D3DCOLOR_COLORVALUE(
                    pState->ConstantColor.A, pState->ConstantColor.A,
                    pState->ConstantColor.A, pState->ConstantColor.A);
                break;
            case AlphaState::SBF_ONE_MINUS_CONSTANT_ALPHA:
                dwSrcBlend = D3DBLEND_INVBLENDFACTOR;
                dwSrcConstantColor = D3DCOLOR_COLORVALUE(
                    pState->ConstantColor.A, pState->ConstantColor.A,
                    pState->ConstantColor.A, pState->ConstantColor.A);
                break;
            }
        }

        DWORD dwDstBlend = ms_adwAlphaDstBlend[pState->DstBlend];
        DWORD dwDstConstantColor = 0;
        if( dwDstBlend > 0 )
        {
            dwDstConstantColor = 0;
        }
        else  // CONSTANT format
        {
            switch( pState->DstBlend )
            {
            case AlphaState::DBF_CONSTANT_COLOR:
                dwDstBlend = D3DBLEND_BLENDFACTOR;
                dwDstConstantColor = D3DCOLOR_COLORVALUE(
                    pState->ConstantColor.R, pState->ConstantColor.G,
                    pState->ConstantColor.B, pState->ConstantColor.A);
                break;
            case AlphaState::DBF_ONE_MINUS_CONSTANT_COLOR:
                dwDstBlend = D3DBLEND_INVBLENDFACTOR;
                dwDstConstantColor = D3DCOLOR_COLORVALUE(
                    pState->ConstantColor.R, pState->ConstantColor.G,
                    pState->ConstantColor.B, pState->ConstantColor.A);
                break;
            case AlphaState::DBF_CONSTANT_ALPHA:
                dwDstBlend = D3DBLEND_BLENDFACTOR;
                dwDstConstantColor = D3DCOLOR_COLORVALUE(
                    pState->ConstantColor.A, pState->ConstantColor.A,
                    pState->ConstantColor.A, pState->ConstantColor.A);
                break;
            case AlphaState::DBF_ONE_MINUS_CONSTANT_ALPHA:
                dwDstBlend = D3DBLEND_INVBLENDFACTOR;
                dwDstConstantColor = D3DCOLOR_COLORVALUE(
                    pState->ConstantColor.A, pState->ConstantColor.A,
                    pState->ConstantColor.A, pState->ConstantColor.A);
                break;
            }

        }

        // DirectX appears not to support the OpenGL modes GL_CONSTANT_ALPHA
        // and GL_ONE_MINUS_CONSTANT_ALPHA.  In these cases, the constant
        // color is being set explicitly to the alpha values.  If the source
        // uses constant color (constant alpha) and the destination uses
        // constant alpha (constant color), then the blending results will be
        // incorrect.
#ifdef _DEBUG
        if( dwSrcBlend == D3DBLEND_BLENDFACTOR
        ||  dwSrcBlend == D3DBLEND_INVBLENDFACTOR )
        {
            if( dwDstBlend == D3DBLEND_BLENDFACTOR
            ||  dwDstBlend == D3DBLEND_INVBLENDFACTOR )
            {
                SE_ASSERT( dwSrcConstantColor == dwDstConstantColor );
            }
        }
#endif

        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_SRCBLEND, dwSrcBlend);
        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_DESTBLEND, dwDstBlend);
        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_BLENDFACTOR, dwSrcConstantColor);
    }
    else
    {
        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        SE_ASSERT( SUCCEEDED(ms_hResult) );
    }

    if( pState->TestEnabled )
    {
        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_ALPHAFUNC, ms_adwAlphaTest[pState->Test]);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)(255.0f*pState->Reference));
        SE_ASSERT( SUCCEEDED(ms_hResult) );
    }
    else
    {
        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
        SE_ASSERT( SUCCEEDED(ms_hResult) );
    }
}
//----------------------------------------------------------------------------
