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

#include "SEOpenGLRendererPCH.h"
#include "SEWglRenderer.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEWglRenderer::SEWglRenderer(HWND hWnd, SEFrameBuffer::FormatType eFormat,
    SEFrameBuffer::DepthType eDepth, SEFrameBuffer::StencilType eStencil,
    SEFrameBuffer::BufferingType eBuffering,
    SEFrameBuffer::MultisamplingType eMultisampling, int iWidth, int iHeight,
    int iPixelFormat)
    :
    SEOpenGLRenderer(eFormat, eDepth, eStencil, eBuffering, eMultisampling, 
        iWidth, iHeight)
{
    SE_ASSERT( m_iWidth > 0 && m_iHeight > 0 );
    m_iSaveWidth = m_iWidth;
    m_iSaveHeight = m_iHeight;

    m_hWnd = hWnd;
    m_hWindowDC = ::GetDC(m_hWnd);

    // 为drawing surface选择格式.
    PIXELFORMATDESCRIPTOR tempPFD;
    memset(&tempPFD, 0, sizeof(PIXELFORMATDESCRIPTOR));
    tempPFD.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    tempPFD.nVersion = 1;
    tempPFD.dwFlags =
        PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL |
        PFD_GENERIC_ACCELERATED;
    if( m_eBuffering == SEFrameBuffer::BT_BUFFERED_DOUBLE )
    {
        tempPFD.dwFlags |= PFD_DOUBLEBUFFER;
    }

    // m_eFormat参数被忽略,总是创建32-bit RGBA buffer
    tempPFD.iPixelType = PFD_TYPE_RGBA;
    tempPFD.cColorBits = 32;

    switch( m_eDepth )
    {
    case SEFrameBuffer::DT_DEPTH_NONE:  tempPFD.cDepthBits =  0;  break;
    case SEFrameBuffer::DT_DEPTH_16:    tempPFD.cDepthBits = 16;  break;
    case SEFrameBuffer::DT_DEPTH_24:    tempPFD.cDepthBits = 24;  break;
    case SEFrameBuffer::DT_DEPTH_32:    tempPFD.cDepthBits = 32;  break;
    default:                          tempPFD.cDepthBits = 16;  break;
    }

    if( m_eStencil == SEFrameBuffer::ST_STENCIL_8 )
    {
        tempPFD.cStencilBits = 8;
    }
    else
    {
        tempPFD.cStencilBits = 0;
    }

    // 为rendering context设置pixel format.
    bool bFirstTime = (iPixelFormat == 0 ? true : false);
    if( bFirstTime )
    {
        // 第一次创建.
        // 如果需要multisampling,则会产生第二次创建,
        // 再次传入的pixel format将直接用于SetPixelFormat函数.
        iPixelFormat = ChoosePixelFormat(m_hWindowDC, &tempPFD);
        if( iPixelFormat == 0 )
        {
            return;
        }
    }

    BOOL bSuccess = SetPixelFormat(m_hWindowDC, iPixelFormat, &tempPFD);
    if( !bSuccess )
    {
        SE_ASSERT( false );

        return;
    }

    // 创建一个OpenGL context.
    m_hWindowRC = wglCreateContext(m_hWindowDC);
    if( !m_hWindowRC )
    {
        SE_ASSERT( false );

        return;
    }

    bSuccess = wglMakeCurrent(m_hWindowDC, m_hWindowRC);
    if( !bSuccess )
    {
        SE_ASSERT( false );

        return;
    }

    if( bFirstTime )
    {
        // 为OpenGL exetensions装载库函数指针.只需要装载一次.
        // 如果你需要创建一个文件来储存并了解OpenGL driver信息,
        // 则在此输入一个文件名,例如"OpenGLDriverInfo.txt".
        const char* acInfoFile = "OpenGLDriverInfo.txt";
        SE_WGL_Initialize(acInfoFile);
    }

    // 关闭vertical sync等待
    wglSwapIntervalEXT(0);

    // 默认使用系统字体.
    DisplayListInfo tempInfo;
    int iFirstChar = int(' ');
    tempInfo.Count = 127 - iFirstChar;
    tempInfo.Start = glGenLists(tempInfo.Count) ;
    tempInfo.Base = tempInfo.Start - iFirstChar;
    m_DLInfo.push_back(tempInfo);
    m_hOldFont = SelectObject(m_hWindowDC, GetStockObject(SYSTEM_FONT)); 
    wglUseFontBitmaps(m_hWindowDC, iFirstChar, tempInfo.Count, tempInfo.Start);

    InitializeState();
}
//----------------------------------------------------------------------------
SEWglRenderer::~SEWglRenderer()
{
    for( int i = 0; i < (int)m_DLInfo.size(); i++ )
    {
        DisplayListInfo tempInfo = m_DLInfo[i];
        glDeleteLists(tempInfo.Start, tempInfo.Count);
    }

    if( m_hWindowRC )
    {
        wglDeleteContext(m_hWindowRC);
    }

    if( m_hWindowDC )
    {
        SelectObject(m_hWindowDC, m_hOldFont);
        ReleaseDC(m_hWnd, m_hWindowDC);
    }
}
//----------------------------------------------------------------------------
void SEWglRenderer::ToggleFullscreen()
{
    SEOpenGLRenderer::ToggleFullscreen();
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
void SEWglRenderer::DisplayBackBuffer()
{
    SwapBuffers(m_hWindowDC);
}
//----------------------------------------------------------------------------
int SEWglRenderer::LoadFont(const char* acFace, int iSize, bool bBold,
    bool bItalic)
{
    int iWeight = (bBold ? FW_BOLD : FW_REGULAR);
        
    HFONT hFont = CreateFont(iSize, 0, 0, 0, iWeight, (DWORD)bItalic, FALSE, 
        FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
        ANTIALIASED_QUALITY, VARIABLE_PITCH, acFace);
    
    if( !hFont )
    {
        SE_ASSERT( false );

        return -1;
    }

    DisplayListInfo tempInfo;
    int iFirstChar = int(' ');
    tempInfo.Count = 127 - iFirstChar;
    tempInfo.Start = glGenLists(tempInfo.Count) ;
    tempInfo.Base = tempInfo.Start - iFirstChar;
    m_DLInfo.push_back(tempInfo);
    SelectObject(m_hWindowDC, hFont); 
    wglUseFontBitmaps(m_hWindowDC, iFirstChar, tempInfo.Count, tempInfo.Start);
    DeleteObject(hFont);

    return (int)m_DLInfo.size() - 1;
}
//----------------------------------------------------------------------------
