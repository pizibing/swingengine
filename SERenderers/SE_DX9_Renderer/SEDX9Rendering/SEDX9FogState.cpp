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

// 固定管线这样做.
//DWORD SEDX9Renderer::ms_adwFogDensity[FogState::DF_COUNT] = 
//{
//    D3DFOG_LINEAR,  // FogState::DF_LINEAR
//    D3DFOG_EXP,     // FogState::DF_EXP
//    D3DFOG_EXP2,    // FogState::DF_EXPSQR
//};
//
////----------------------------------------------------------------------------
//void SEDX9Renderer::SetFogState(FogState* pState)
//{
//    SERenderer::SetFogState(pState);
//
//    if( pState->Enabled )
//    {
//        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
//        SE_ASSERT( SUCCEEDED(ms_hResult) );
//
//        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_FOGSTART,
//            *((DWORD*)(&pState->Start)));
//        SE_ASSERT( SUCCEEDED(ms_hResult) );
//
//        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_FOGEND,
//            *((DWORD*)(&pState->End)));
//        SE_ASSERT( SUCCEEDED(ms_hResult) );
//
//        D3DCOLOR dwFogColor = D3DCOLOR_COLORVALUE(pState->Color.R,
//            pState->Color.G, pState->Color.B, pState->Color.A);
//        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_FOGCOLOR, dwFogColor);
//        SE_ASSERT( SUCCEEDED(ms_hResult) );
//
//        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_FOGDENSITY,
//            *((DWORD*)(&pState->Density)));
//        SE_ASSERT( SUCCEEDED(ms_hResult) );
//
//        if( pState->ApplyFunction == FogState::AF_PER_PIXEL )
//        {
//            ms_hResult = m_pDXDevice->SetRenderState(D3DRS_FOGTABLEMODE,
//                ms_adwFogDensity[pState->DensityFunction]);
//            SE_ASSERT( SUCCEEDED(ms_hResult) );
//        }
//        else
//        {
//            ms_hResult = m_pDXDevice->SetRenderState(D3DRS_FOGVERTEXMODE,
//                ms_adwFogDensity[pState->DensityFunction]);    
//            SE_ASSERT( SUCCEEDED(ms_hResult) );
//        }
//    }
//    else
//    {
//        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
//        SE_ASSERT( SUCCEEDED(ms_hResult) );
//   }   
//}
////----------------------------------------------------------------------------

