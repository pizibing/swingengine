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

// ע��:
// ����ļ������˺���cocoa�����ͷ�ļ�,���ֻ�ܱ�.mm�ļ�������.

namespace Swing
{

//----------------------------------------------------------------------------
// ˵��:
// ����:Sun Che
// ʱ��:20091104
//----------------------------------------------------------------------------
class SE_RENDERER_API SEiPhoneOES2Renderer : public SEOGLES2Renderer
{
public:
    SEiPhoneOES2Renderer(UIWindow* pWindow, SEFrameBuffer::FormatType eFormat,
        SEFrameBuffer::DepthType eDepth, SEFrameBuffer::StencilType eStencil,
        SEFrameBuffer::BufferingType eBuffering,
        SEFrameBuffer::MultisamplingType eMultisampling, int iX, int iY,
        int iWidth, int iHeight);

    virtual ~SEiPhoneOES2Renderer(void);

    virtual void Resize(int iWidth, int iHeight);
    virtual void ToggleFullscreen(void);

    virtual void DisplayBackBuffer(void);

    virtual int LoadFont(const char* acFace, int iSize, bool bBold,
        bool bItalic);

    // �����view����.
    SEEAGL2View* GetView(void);
    UIWindow* GetWindow(void);

private:
    // �����view����.
    SEEAGL2View* m_pEAGL2View;
    UIWindow* m_pWindow;
    Boolean m_bFullScreen;

    // ��ʵ��.
    // �������.

    // ����֧��fullscreen/window.
    int m_iX, m_iY;
    int m_iSaveWidth, m_iSaveHeight;
};

}

#endif
