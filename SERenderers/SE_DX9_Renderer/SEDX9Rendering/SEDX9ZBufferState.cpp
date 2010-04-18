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

DWORD SEDX9Renderer::ms_adwZBufferCompare[SEZBufferState::CF_COUNT] = 
{
    D3DCMP_NEVER,           // SEZBufferState::CF_NEVER
    D3DCMP_LESS,            // SEZBufferState::CF_LESS
    D3DCMP_EQUAL,           // SEZBufferState::CF_EQUAL
    D3DCMP_LESSEQUAL,       // SEZBufferState::CF_LEQUAL
    D3DCMP_GREATER,         // SEZBufferState::CF_GREATER
    D3DCMP_NOTEQUAL,        // SEZBufferState::CF_NOTEQUAL
    D3DCMP_GREATEREQUAL,    // SEZBufferState::CF_GEQUAL
    D3DCMP_ALWAYS,          // SEZBufferState::CF_ALWAYS
};

//----------------------------------------------------------------------------
void SEDX9Renderer::SetZBufferState(SEZBufferState* pState)
{
    SERenderer::SetZBufferState(pState);

    if( pState->Enabled )
    {
        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_ZFUNC,
            ms_adwZBufferCompare[pState->Compare]);
        SE_ASSERT( SUCCEEDED(ms_hResult) );
    }
    else
    {
        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
        SE_ASSERT( SUCCEEDED(ms_hResult) );
    }

    if( pState->Writable )
    {
        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
        SE_ASSERT( SUCCEEDED(ms_hResult) );
    }
    else
    {
        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        SE_ASSERT( SUCCEEDED(ms_hResult) );
    }
}
//----------------------------------------------------------------------------
