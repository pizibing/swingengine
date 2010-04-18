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

DWORD SEDX9Renderer::ms_adwCullType[SECullState::FT_COUNT] = 
{
    // SECullState::FT_CCW (front faces are CCW,so cull backface CW in DX)
    D3DCULL_CW,
    // SECullState::FT_CW  (front faces are CW, so cull backface CCW in DX)
    D3DCULL_CCW,
};

//----------------------------------------------------------------------------
void SEDX9Renderer::SetCullState(SECullState* pState)
{
    SERenderer::SetCullState(pState);

    if( pState->Enabled )
    {
        if( m_bReverseCullFace )
        {
            if( ms_adwCullType[pState->CullFace] == D3DCULL_CW )
            {
                ms_hResult = m_pDXDevice->SetRenderState(D3DRS_CULLMODE, 
                    D3DCULL_CCW);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
            }
            else
            {
                ms_hResult = m_pDXDevice->SetRenderState(D3DRS_CULLMODE, 
                    D3DCULL_CW);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
            }
        } 
        else
        {
            ms_hResult = m_pDXDevice->SetRenderState(D3DRS_CULLMODE,
                ms_adwCullType[pState->CullFace]);
            SE_ASSERT( SUCCEEDED(ms_hResult) );
        }
    }
    else
    {
        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_CULLMODE, 
            D3DCULL_NONE);
        SE_ASSERT( SUCCEEDED(ms_hResult) );
    }
}
//----------------------------------------------------------------------------
