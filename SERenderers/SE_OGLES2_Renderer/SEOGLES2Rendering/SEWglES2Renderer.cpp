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

#include "SEOGLES2RendererPCH.h"
#include "SEWglES2Renderer.h"

using namespace Swing;

//----------------------------------------------------------------------------
WglES2Renderer::WglES2Renderer(EGLNativeWindowType hWnd,
    FrameBuffer::FormatType eFormat, FrameBuffer::DepthType eDepth,
    FrameBuffer::StencilType eStencil, FrameBuffer::BufferingType eBuffering,
    FrameBuffer::MultisamplingType eMultisampling, int iWidth, int iHeight)
    :
    OGLES2Renderer(eFormat, eDepth, eStencil, eBuffering, eMultisampling,
        iWidth, iHeight)
{
    SE_ASSERT( m_iWidth > 0 && m_iHeight > 0 );
    m_iSaveWidth = m_iWidth;
    m_iSaveHeight = m_iHeight;

    m_hWnd = hWnd;

    // m_eFormat参数被忽略.
    EGLint iR = 5;
    EGLint iG = 6;
    EGLint iB = 5;
    EGLint iA = 0;

    // depth buffer bits,目前只支持8-bit和16-bit.
    EGLint iDepth;
    switch( m_eDepth )
    {
    case FrameBuffer::DT_DEPTH_NONE:  iDepth =  0;  break;
    case FrameBuffer::DT_DEPTH_8:     iDepth =  8;  break;
    case FrameBuffer::DT_DEPTH_16:    iDepth = 16;  break;
    case FrameBuffer::DT_DEPTH_24:    iDepth = 24;  break;
    default:                          iDepth =  0;  break;
    }

    // stencil buffer bits.
    EGLint iStencil;
    if( m_eStencil == FrameBuffer::ST_STENCIL_8 )
    {
        iStencil = 8;
    }
    else
    {
        iStencil = 0;
    }

    // 待实现.
    // eBuffering被忽略.

    // multisample.
    EGLint iMultisampling;
    switch( eMultisampling )
    {
    case FrameBuffer::MT_SAMPLING_NONE: iMultisampling = 0; break;
    case FrameBuffer::MT_SAMPLING_2:    iMultisampling = 2; break;
    case FrameBuffer::MT_SAMPLING_4:    iMultisampling = 4; break;
    case FrameBuffer::MT_SAMPLING_8:    iMultisampling = 8; break;
    default:                            iMultisampling = 0; break;
    }

    // setup attrib list.
    EGLint aiAttribList[] =
    {
        EGL_RED_SIZE,       iR,
        EGL_GREEN_SIZE,     iG,
        EGL_BLUE_SIZE,      iB,
        EGL_ALPHA_SIZE,     iA,
        EGL_DEPTH_SIZE,     iDepth,
        EGL_STENCIL_SIZE,   iStencil,
        EGL_SAMPLE_BUFFERS, (eMultisampling != FrameBuffer::MT_SAMPLING_NONE)
            ? 1 : 0,
        EGL_SAMPLES,        iMultisampling,
        EGL_NONE
    };

    EGLint iConfigCount;
    EGLint iMajorVersion;
    EGLint iMinorVersion;
    EGLConfig tempConfig = 0;
    EGLint aiContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE,
        EGL_NONE };

    // get a display.
    m_eglDisplay = eglGetDisplay(GetDC(hWnd));
    if( m_eglDisplay == EGL_NO_DISPLAY )
    {
        SE_ASSERT( false );
        return;
    }

    // initialize EGL.
    if( !eglInitialize(m_eglDisplay, &iMajorVersion, &iMinorVersion) )
    {
        SE_ASSERT( false );
        return;
    }

    // get configs.
    if( !eglGetConfigs(m_eglDisplay, 0, 0, &iConfigCount) )
    {
        SE_ASSERT( false );
        return;
    }

    // choose a config.
    if( !eglChooseConfig(m_eglDisplay, aiAttribList, &tempConfig, 1,
        &iConfigCount) )
    {
        SE_ASSERT( false );
        return;
    }

    // create a surface.
    m_eglSurface = eglCreateWindowSurface(m_eglDisplay, tempConfig, 
        (EGLNativeWindowType)hWnd, 0);
    if( m_eglSurface == EGL_NO_SURFACE )
    {
        SE_ASSERT( false );
        return;
    }

    // create a GL context.
    m_eglContext = eglCreateContext(m_eglDisplay, tempConfig, EGL_NO_CONTEXT,
        aiContextAttribs);
    if ( m_eglContext == EGL_NO_CONTEXT )
    {
        SE_ASSERT( false );
        return;
    }   
   
    // make the context current.
    if( !eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface,
        m_eglContext) )
    {
        SE_ASSERT( false );
        return;
    }

    InitializeState();
}
//----------------------------------------------------------------------------
WglES2Renderer::~WglES2Renderer()
{
    eglMakeCurrent(m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE,
        EGL_NO_CONTEXT);

    if( m_eglContext )
    {
        eglDestroyContext(m_eglDisplay, m_eglContext);
    }

    if( m_eglSurface )
    {
        eglDestroySurface(m_eglDisplay, m_eglSurface);
    }

    if( m_eglDisplay )
    {
        eglTerminate(m_eglDisplay);
    }
}
//----------------------------------------------------------------------------
void WglES2Renderer::ToggleFullscreen()
{
    OGLES2Renderer::ToggleFullscreen();
    glFinish();

    DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

    UINT uiFlags = SWP_NOACTIVATE | SWP_NOOWNERZORDER |
        SWP_NOSENDCHANGING | SWP_NOZORDER;

    RECT tempRect;

    if( m_bFullscreen )
    {
        m_iSaveWidth = m_iWidth;
        m_iSaveHeight = m_iHeight;
        GetWindowRect(GetDesktopWindow(), &tempRect);
        AdjustWindowRect(&tempRect, dwStyle, FALSE);
    }
    else
    {
        m_iWidth = m_iSaveWidth;
        m_iHeight = m_iSaveHeight;

        tempRect.left = 0;
        tempRect.top = 0;
        tempRect.right = m_iWidth - 1;
        tempRect.bottom = m_iHeight - 1;
        AdjustWindowRect(&tempRect, dwStyle, FALSE);

        tempRect.right -= tempRect.left;
        tempRect.left = 0;
        tempRect.bottom -= tempRect.top;
        tempRect.top = 0;
    }

    SetWindowPos(m_hWnd, HWND_TOP, tempRect.left, tempRect.top,
        tempRect.right-tempRect.left, tempRect.bottom-tempRect.top, uiFlags);
}
//----------------------------------------------------------------------------
void WglES2Renderer::DisplayBackBuffer()
{
    eglSwapBuffers(m_eglDisplay, m_eglSurface);
}
//----------------------------------------------------------------------------
int WglES2Renderer::LoadFont(const char*, int, bool, bool)
{
    // 待实现.
    return -1;
}
//----------------------------------------------------------------------------
