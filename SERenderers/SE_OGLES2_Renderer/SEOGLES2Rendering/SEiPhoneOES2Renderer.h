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

#ifndef Swing_iPhoneOES2_Renderer_H
#define Swing_iPhoneOES2_Renderer_H

#include "SEOGLES2RendererLIB.h"
#include "SEOGLES2Renderer.h"
#include "SEEAGL2View.h"

// 注意:
// 这个文件包含了含有cocoa代码的头文件,因此只能被.mm文件所包含.

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:iPhone OpenGL ES2 Renderer类
// 说明:
// 作者:Sun Che
// 时间:20091104
//----------------------------------------------------------------------------
class SE_RENDERER_API iPhoneOES2Renderer : public OGLES2Renderer
{
public:
    iPhoneOES2Renderer(UIWindow* pWindow, FrameBuffer::FormatType eFormat,
        FrameBuffer::DepthType eDepth, FrameBuffer::StencilType eStencil,
        FrameBuffer::BufferingType eBuffering,
        FrameBuffer::MultisamplingType eMultisampling, int iX, int iY,
        int iWidth, int iHeight);

    virtual ~iPhoneOES2Renderer(void);

    virtual void Resize(int iWidth, int iHeight);
    virtual void ToggleFullscreen(void);

    virtual void DisplayBackBuffer(void);

    virtual int LoadFont(const char* acFace, int iSize, bool bBold,
        bool bItalic);

    // 窗体和view访问.
    EAGL2View* GetView(void);
    UIWindow* GetWindow(void);

private:
    // 窗体和view参数.
    EAGL2View* m_pEAGL2View;
    UIWindow* m_pWindow;
    Boolean m_bFullScreen;

    // 待实现.
    // 字体管理.

    // 用于支持fullscreen/window.
    int m_iX, m_iY;
    int m_iSaveWidth, m_iSaveHeight;
};

}

#endif

