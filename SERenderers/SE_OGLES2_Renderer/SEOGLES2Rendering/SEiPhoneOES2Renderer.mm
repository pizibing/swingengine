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

#include "SEiPhoneOES2Renderer.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEiPhoneOES2Renderer::SEiPhoneOES2Renderer(UIWindow* pWindow,
    SEFrameBuffer::FormatType eFormat, SEFrameBuffer::DepthType eDepth,
    SEFrameBuffer::StencilType eStencil, SEFrameBuffer::BufferingType 
    eBuffering, SEFrameBuffer::MultisamplingType eMultisampling, int iX, int 
    iY, int iWidth, int iHeight)
    :
    SEOGLES2Renderer(eFormat, eDepth, eStencil, eBuffering, eMultisampling, 
        iWidth, iHeight)
{
    SE_ASSERT( m_iWidth > 0 && m_iHeight > 0 );
    SE_ASSERT( pWindow );
    
    m_iSaveWidth = m_iWidth;
    m_iSaveHeight = m_iHeight;

    m_iX = iX;
    m_iY = iY;
    // 稍后创建SEEAGL2View.
    m_pEAGL2View = 0;
    m_pWindow = pWindow;
    m_bFullScreen = false;

    // Request a depth buffer.
    if( m_eDepth != SEFrameBuffer::DT_DEPTH_NONE )
    {
        // 待实现.
        // 目前只支持GL_DEPTH_COMPONENT16_OES.
    }

    // Request a stencil buffer.
    if( m_eStencil == SEFrameBuffer::ST_STENCIL_8 )
    {
        // 待实现.
    }

    // Request buffering.
    if( m_eBuffering == SEFrameBuffer::BT_BUFFERED_DOUBLE )
    {
        // 待实现.
    }

    // Request sampling.
    if( m_eMultisampling != SEFrameBuffer::MT_SAMPLING_NONE )
    {
        // 待实现.
    }

    // 创建SEEAGL2View及其EAGLContext.
    CGRect tempRect = [[UIScreen mainScreen] bounds];
    m_pEAGL2View = [[SEEAGL2View alloc] initWithFrame:tempRect 
        pixelFormat:GL_RGB565 depthFormat:GL_DEPTH_COMPONENT16 
        preserveBackbuffer:NO];

    // 把SEEAGL2View绑定给UIWindow.
    [m_pWindow addSubview:m_pEAGL2View];

    // 初始化OpenGL管线,获取设备能力.
    InitializeState();
}
//----------------------------------------------------------------------------
SEiPhoneOES2Renderer::~SEiPhoneOES2Renderer()
{
    [m_pEAGL2View release];
}
//----------------------------------------------------------------------------
void SEiPhoneOES2Renderer::Resize(int iWidth, int iHeight)
{
    // 待实现.
}
//----------------------------------------------------------------------------
void SEiPhoneOES2Renderer::ToggleFullscreen()
{
    // 待实现.
}
//----------------------------------------------------------------------------
void SEiPhoneOES2Renderer::DisplayBackBuffer()
{
    [m_pEAGL2View swapBuffers];
}
//----------------------------------------------------------------------------
int SEiPhoneOES2Renderer::LoadFont(const char*, int, bool, bool)
{
    // 待实现.
    return 0;
}
//----------------------------------------------------------------------------
SEEAGL2View* SEiPhoneOES2Renderer::GetView()
{
    return m_pEAGL2View;
}
//----------------------------------------------------------------------------
UIWindow* SEiPhoneOES2Renderer::GetWindow()
{
    return m_pWindow;
}
//----------------------------------------------------------------------------