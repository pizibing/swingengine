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

DWORD DX9Renderer::ms_adwStencilCompare[StencilState::CF_COUNT] = 
{
    D3DCMP_NEVER,           // StencilState::CF_NEVER
    D3DCMP_LESS,            // StencilState::CF_LESS
    D3DCMP_EQUAL,           // StencilState::CF_EQUAL
    D3DCMP_LESSEQUAL,       // StencilState::CF_LEQUAL
    D3DCMP_GREATER,         // StencilState::CF_GREATER
    D3DCMP_NOTEQUAL,        // StencilState::CF_NOTEQUAL
    D3DCMP_GREATEREQUAL,    // StencilState::CF_GEQUAL
    D3DCMP_ALWAYS,          // StencilState::CF_ALWAYS
};

DWORD DX9Renderer::ms_adwStencilOperation[StencilState::OT_COUNT] =
{
    D3DSTENCILOP_KEEP,      // StencilState::OT_KEEP
    D3DSTENCILOP_ZERO,      // StencilState::OT_ZERO
    D3DSTENCILOP_REPLACE,   // StencilState::OT_REPLACE
    D3DSTENCILOP_INCR,      // StencilState::OT_INCREMENT
    D3DSTENCILOP_DECR,      // StencilState::OT_DECREMENT
    D3DSTENCILOP_INVERT     // StencilState::OT_INVERT
};

//----------------------------------------------------------------------------
void DX9Renderer::SetStencilState(StencilState* pState)
{
    Renderer::SetStencilState(pState);

    if( pState->Enabled )
    {
        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_STENCILFUNC,
            ms_adwStencilCompare[pState->Compare]);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_STENCILREF,
            (DWORD)pState->Reference);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_STENCILMASK,
            (DWORD)pState->Mask);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_STENCILWRITEMASK,
            (DWORD)pState->WriteMask);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_STENCILFAIL,
            ms_adwStencilOperation[pState->OnFail]);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_STENCILZFAIL,
            ms_adwStencilOperation[pState->OnZFail]);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_STENCILPASS,
            ms_adwStencilOperation[pState->OnZPass]);
        SE_ASSERT( SUCCEEDED(ms_hResult) );
    }
    else
    {
        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
        SE_ASSERT( SUCCEEDED(ms_hResult) );
    }
}
//----------------------------------------------------------------------------
