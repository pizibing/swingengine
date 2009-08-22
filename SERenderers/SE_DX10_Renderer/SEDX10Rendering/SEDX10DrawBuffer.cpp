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

//----------------------------------------------------------------------------
void DX10Renderer::Draw(const unsigned char* aucBuffer)
{
    if( !aucBuffer )
    {
        return;
    }

    //IDirect3DSurface9* pBackBuffer = 0;
    //ms_hResult = m_pDXDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
    //SE_ASSERT( pBackBuffer );
    //SE_ASSERT( SUCCEEDED(ms_hResult) );

    //if( FAILED(ms_hResult) || !pBackBuffer )
    //{
    //    return;
    //}

    //RECT SrcRect = { 0, 0, m_iWidth-1, m_iHeight-1 };
    //ms_hResult = D3DXLoadSurfaceFromMemory(pBackBuffer, 0, 0, aucBuffer,
    //    D3DFMT_R8G8B8, 3*m_iWidth, 0, &SrcRect, D3DX_FILTER_NONE, 0);
    //SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
