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

//----------------------------------------------------------------------------
void SEDX9Renderer::SetPolygonOffsetState(SEPolygonOffsetState* pState)
{
    // The LineEnabled and PointEnabled members are ignored by the DX9
    // renderer since DX9 does not support polygon offset for those
    // primitives.

    SERenderer::SetPolygonOffsetState(pState);

    if( pState->FillEnabled )
    {
        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS,
            *((DWORD*)&pState->Scale));
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        // TO DO.  The renderer currently always creates a 24-bit depth
        // buffer.  If the precision changes, the adjustment to depth bias
        // must depend on the bits of precision.  The divisor is 2^n for n
        // bits of precision.
        float fBias = pState->Bias/16777216.0f;
        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_DEPTHBIAS,
            *((DWORD*)&fBias));
        SE_ASSERT( SUCCEEDED(ms_hResult) );
    }
    else
    {
        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS, 0);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        ms_hResult = m_pDXDevice->SetRenderState(D3DRS_DEPTHBIAS, 0);
        SE_ASSERT( SUCCEEDED(ms_hResult) );
    }
}
//----------------------------------------------------------------------------
