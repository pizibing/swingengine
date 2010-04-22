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

#include "SEiPhoneOES1Renderer.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEiPhoneOES1Renderer::SEiPhoneOES1Renderer(UIWindow* pWindow,
    SEFrameBuffer::FormatType eFormat, SEFrameBuffer::DepthType eDepth,
    SEFrameBuffer::StencilType eStencil, SEFrameBuffer::BufferingType 
    eBuffering, SEFrameBuffer::MultisamplingType eMultisampling, int iX, int 
    iY, int iWidth, int iHeight)
    :
    SEOGLES1Renderer(eFormat, eDepth, eStencil, eBuffering, eMultisampling, 
        iWidth, iHeight)
{
    SE_ASSERT( m_iWidth > 0 && m_iHeight > 0 );
    SE_ASSERT( pWindow );
	
    m_iSaveWidth = m_iWidth;
    m_iSaveHeight = m_iHeight;

    m_iX = iX;
    m_iY = iY;
    // 稍后创建SEEAGLView.
    m_pEAGLView = 0;
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

    // 创建SEEAGLView及其EAGLContext.
    CGRect tempRect = [[UIScreen mainScreen] bounds];
    m_pEAGLView = [[SEEAGLView alloc] initWithFrame:tempRect 
        pixelFormat:GL_RGB565_OES depthFormat:GL_DEPTH_COMPONENT16_OES 
        preserveBackbuffer:NO];

    // 把SEEAGLView绑定给UIWindow.
    [m_pWindow addSubview:m_pEAGLView];

    // 初始化OpenGL管线,获取设备能力.
    InitializeState();
}
//----------------------------------------------------------------------------
SEiPhoneOES1Renderer::~SEiPhoneOES1Renderer()
{
    [m_pEAGLView release];
}
//----------------------------------------------------------------------------
void SEiPhoneOES1Renderer::Resize(int iWidth, int iHeight)
{
    // 待实现.
}
//----------------------------------------------------------------------------
void SEiPhoneOES1Renderer::ToggleFullscreen()
{
    // 待实现.
}
//----------------------------------------------------------------------------
void SEiPhoneOES1Renderer::DisplayBackBuffer()
{
    [m_pEAGLView swapBuffers];
}
//----------------------------------------------------------------------------
int SEiPhoneOES1Renderer::LoadFont(const char*, int, bool, bool)
{
    // 待实现.
    return 0;
}
//----------------------------------------------------------------------------
SEEAGLView* SEiPhoneOES1Renderer::GetView()
{
    return m_pEAGLView;
}
//----------------------------------------------------------------------------
UIWindow* SEiPhoneOES1Renderer::GetWindow()
{
    return m_pWindow;
}
//----------------------------------------------------------------------------