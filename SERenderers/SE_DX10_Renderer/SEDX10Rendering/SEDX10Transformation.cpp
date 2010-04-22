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
#include "SECamera.h"

using namespace Swing;

//----------------------------------------------------------------------------
void SEDX10Renderer::OnViewportChange()
{
    float fPortL, fPortR, fPortT, fPortB;
    if( m_pCamera )
    {
        // 3D应用程序使用camera.
        m_pCamera->GetViewport(fPortL, fPortR, fPortT, fPortB);
    }
    else
    {
        // 2D应用程序不用camera.
        fPortL = 0.0f;
        fPortR = 1.0f;
        fPortT = 1.0f;
        fPortB = 0.0f;
    }

    // DirectX将viewport坐标原点定义在屏幕左上角.
    // 我们使用OpenGL的viewport约定方式.从而,
    // fPortB指定viewport相对于屏幕下方的距离.
    // 而DirectX需要指定viewport相对于屏幕上方的距离,
    // 也就是1-fPortT.
    D3D10_VIEWPORT tempViewport;
    tempViewport.TopLeftX = (INT)(fPortL*m_iWidth);
    tempViewport.TopLeftY = (INT)((1.0f - fPortT)*m_iHeight);
    tempViewport.Width = (UINT)((fPortR - fPortL)*m_iWidth);
    tempViewport.Height = (UINT)((fPortT - fPortB)*m_iHeight);
    tempViewport.MinDepth = 0.0f;
    tempViewport.MaxDepth = 1.0f;

    m_pDX10Device->RSSetViewports(1, &tempViewport);
}
//----------------------------------------------------------------------------
void SEDX10Renderer::OnDepthRangeChange()
{
    UINT uiVPCount = 1;
    D3D10_VIEWPORT tempViewport;
    m_pDX10Device->RSGetViewports(&uiVPCount, &tempViewport);

    if( m_pCamera )
    {
        m_pCamera->GetDepthRange(tempViewport.MinDepth, tempViewport.MaxDepth);
    }
    else
    {
        tempViewport.MinDepth = 0.0f;
        tempViewport.MaxDepth = 1.0f;
    }

    m_pDX10Device->RSSetViewports(1, &tempViewport);
}
//----------------------------------------------------------------------------
