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

#ifndef Swing_Wgl_Renderer_H
#define Swing_Wgl_Renderer_H

#include "SEOpenGLRendererLIB.h"
#include "SEOpenGLRenderer.h"
#include "SEWglExtensions.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:Microsoft Windows OpenGL2.0 Renderer类
// 说明:
// 作者:Sun Che
// 时间:20080920
//----------------------------------------------------------------------------
class SE_RENDERER_API WglRenderer : public OpenGLRenderer
{
public:
    // 构造函数被应用程序层第一次调用时,传入的pixel format将被忽略掉.
    // 如果multisampling被开启,渲染器和窗体必须被释放掉,
    // 然后利用支持multisampling的pixel format来重新创建渲染器和窗体.
    // 从SEWglApplication.cpp可以查看这个程序流程.
    WglRenderer(HWND hWnd, FrameBuffer::FormatType eFormat,
        FrameBuffer::DepthType eDepth, FrameBuffer::StencilType eStencil,
        FrameBuffer::BufferingType eBuffering,
        FrameBuffer::MultisamplingType eMultisampling, int iWidth,
        int iHeight, int iPixelFormat = 0);

    virtual ~WglRenderer(void);

    virtual void ToggleFullscreen(void);
    virtual void DisplayBackBuffer(void);
    virtual int LoadFont(const char* acFace, int iSize, bool bBold,
        bool bItalic);

    // 窗体参数.
    HWND GetWindow(void){ return m_hWnd; }
    HDC GetDC(void){ return m_hWindowDC; }
    HGLRC GetRC(void){ return m_hWindowRC; }

protected:
    // 窗体参数.
    HWND m_hWnd;
    HDC m_hWindowDC;
    HGLRC m_hWindowRC;
    HGDIOBJ m_hOldFont;

    // 用于支持fullscreen/window
    int m_iSaveWidth, m_iSaveHeight;
};

}

#endif
