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

#ifndef Swing_WindowApplication_H
#define Swing_WindowApplication_H

#include "SEApplication.h"
#include "SwingAudio.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 说明:for iPhone application
// 作者:jazzboysc
// 时间:20090604
//----------------------------------------------------------------------------
class SEWindowApplication : public SEApplication
{
public:
    // Virtual base class.
    SEWindowApplication(const char* acWindowTitle, int iXPosition,
        int iYPosition, int iWidth, int iHeight,
        const SEColorRGBA& rBackgroundColor);
    virtual ~SEWindowApplication(void);

    // Application entry point.
    virtual int Main(int iCount, char** apcArgument);

    // Member access.
    inline const char* GetWindowTitle(void) const;
    inline int GetXPosition(void) const;
    inline int GetYPosition(void) const;
    inline int GetWidth(void) const;
    inline int GetHeight(void) const;
    inline void SetRenderer(SERenderer* pRenderer);
    inline SERenderer* GetRenderer(void);
    inline void SetAudioRenderer(SEAudioRenderer* pAudioRenderer);
    inline SEAudioRenderer* GetAudioRenderer(void);
    inline void SetWindowID(int iWindowID);
    inline int GetWindowID(void) const;

    // Event callback functions.
    virtual bool OnPrecreate(void);
    virtual bool OnInitialize(void);
    virtual void OnTerminate(void);
    virtual void OnMove(int iX, int iY);
    virtual void OnResize(int iWidth, int iHeight);
    virtual void OnDisplay(void);
    virtual void OnIdle(void);
    virtual void OnTouchBegan(int iX, int iY);
    virtual void OnTouchMoved(int iX, int iY);
    virtual void OnTouchEnded(int iX, int iY);
    virtual void OnTouchCancelled(int iX, int iY);

    // These functions are used by Cocoa delegate class when the renderer is
    // created.
    inline SEFrameBuffer::FormatType GetFormat(void);
    inline SEFrameBuffer::DepthType GetDepth(void);
    inline SEFrameBuffer::StencilType GetStencil(void);
    inline SEFrameBuffer::BufferingType GetBuffering(void);
    inline SEFrameBuffer::MultisamplingType GetMultisampling(void);

protected:
    // Hook our application entry point function.
    static int Run(int iArgCount, char** apcArgument);

    // 构造函数输入变量
    const char* m_acWindowTitle;
    int m_iXPosition, m_iYPosition, m_iWidth, m_iHeight;
    SEColorRGBA m_BackgroundColor;

    // Window ID(platform specific).
    int m_iWindowID;

    // 创建渲染器所需的frame buffer参数.
    // 你可以在你的应用程序构造函数中设置为所需的值.
    SEFrameBuffer::FormatType m_eFormat;
    SEFrameBuffer::DepthType m_eDepth;
    SEFrameBuffer::StencilType m_eStencil;
    SEFrameBuffer::BufferingType m_eBuffering;
    SEFrameBuffer::MultisamplingType m_eMultisampling;

    // SERenderer(for 2D and 3D applications).
    SERenderer* m_pRenderer;

    // Audio renderer(for 2D and 3D applications).
    SEAudioRenderer* m_pAudioRenderer;
};

#include "SEWindowApplication.inl"

}

#endif
