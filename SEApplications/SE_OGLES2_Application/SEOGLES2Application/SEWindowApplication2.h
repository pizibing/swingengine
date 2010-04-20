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

#ifndef Swing_WindowApplication2_H
#define Swing_WindowApplication2_H

#include "SEWindowApplication.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 说明:
// 作者:jazzboysc
// 时间:20080809
//----------------------------------------------------------------------------
class SEWindowApplication2 : public SEWindowApplication
{
public:
    SEWindowApplication2(const char* acWindowTitle, int iXPosition,
        int iYPosition, int iWidth, int iHeight,
        const SEColorRGBA& rBackgroundColor);

    virtual ~SEWindowApplication2(void);

    // 事件回调函数
    virtual bool OnInitialize(void);
    virtual void OnTerminate(void);
    virtual void OnResize(int iWidth, int iHeight);
    virtual void OnDisplay(void);

    // 在屏幕多边形渲染完毕后,允许你做额外的渲染操作.
    virtual void ScreenOverlay(void);

    void ClearScreen(void);

    class Color
    {
    public:
        Color(unsigned char ucR=0, unsigned char ucG=0, unsigned char ucB=0)
        {
            r = ucR;
            g = ucG;
            b = ucB;
        }

        bool operator == (Color rhsColor) const
        {
            return b == rhsColor.b && g == rhsColor.g && r == rhsColor.r;
        }

        bool operator != (Color rhsColor) const
        {
            return b != rhsColor.b || g != rhsColor.g || r != rhsColor.r;
        }

        unsigned char b, g, r;
    };

    void SetPixel(int iX, int iY, Color srcColor);
    void SetThickPixel(int iX, int iY, int iThick, Color srcColor);
    Color GetPixel(int iX, int iY);
    void DrawLine(int iX0, int iY0, int iX1, int iY1, Color srcColor);
    void DrawRectangle(int iXMin, int iYMin, int iXMax, int iYMax,
        Color srcColor, bool bSolid = false);
    void DrawCircle(int iXCenter, int iYCenter, int iRadius, Color srcColor,
        bool bSolid = false);
    void Fill(int iX, int iY, Color srcFColor, Color srcBColor);

    bool& ClampToWindow(void);

    // For right-handed drawing.  You still draw to the left-handed screen,
    // but immediately before drawing the screen is copied into another buffer
    // with the rows reversed.  You need only call DoFlip(true) once for an
    // application.  The default is 'false'.
    void DoFlip(bool bDoFlip);


protected:
    int Index(int iX, int iY)
    {
        // left-handed screen coordinates
        return iX + m_iWidth*iY;
    }

    int m_iScrWidth, m_iScrHeight;
    Color* m_aScreen;
    bool m_bClampToWindow;

    // For right-handed drawing.  The array m_aScreen is copied to
    // m_aFlipScreen so that the rows are reversed.
    Color* m_aFlipScreen;
};

}

#endif
