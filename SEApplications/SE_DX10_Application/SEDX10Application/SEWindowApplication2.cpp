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

#include "SEDX10ApplicationPCH.h"
#include "SEWindowApplication2.h"

using namespace Swing;

//----------------------------------------------------------------------------
WindowApplication2::WindowApplication2(const char* acWindowTitle,
    int iXPosition, int iYPosition, int iWidth, int iHeight,
    const ColorRGBA& rBackgroundColor)
    :
    // rows必须是4字节的倍数,因此iWidth需要被调整.
    WindowApplication(acWindowTitle, iXPosition, iYPosition,
        iWidth-(iWidth % 4), iHeight, rBackgroundColor)
{
    m_iScrWidth = 0;
    m_iScrHeight = 0;
    m_aScreen = 0;
    m_bClampToWindow = true;
    m_aFlipScreen = 0;
}
//----------------------------------------------------------------------------
WindowApplication2::~WindowApplication2()
{
}
//----------------------------------------------------------------------------
bool WindowApplication2::OnInitialize()
{
    if( !WindowApplication::OnInitialize() )
    {
        return false;
    }

    // RGB屏幕像素
    m_iScrWidth = GetWidth();
    m_iScrHeight = GetHeight();
    m_aScreen = SE_NEW Color[m_iScrWidth*m_iScrHeight];
    ClearScreen();

    return true;
}
//----------------------------------------------------------------------------
void WindowApplication2::OnTerminate ()
{
    SE_DELETE[] m_aScreen;
    SE_DELETE[] m_aFlipScreen;
    WindowApplication::OnTerminate();
}
//----------------------------------------------------------------------------
void WindowApplication2::OnDisplay()
{
    m_pRenderer->ClearBuffers();
    if( m_pRenderer->BeginScene() )
    {
        if( !m_aFlipScreen )
        {
            m_pRenderer->Draw((const unsigned char*)m_aScreen);
        }
        else
        {
            // flip the screen
            Color* aSPtr = m_aScreen;
            Color* aFPtr = m_aFlipScreen + m_iScrWidth*(m_iScrHeight - 1);
            size_t uiCount = m_iScrWidth * sizeof(Color);
            for( int i = 0; i < m_iScrHeight; i++ )
            {
                System::SE_Memcpy(aFPtr, uiCount, aSPtr, uiCount);
                aSPtr += m_iScrWidth;
                aFPtr -= m_iScrWidth;
            }

            m_pRenderer->Draw((const unsigned char*)m_aFlipScreen);
        }

        // Screen overlays should use m_pRenderer and not access the
        // m_aScreen array directly.
        ScreenOverlay();

        m_pRenderer->EndScene();
    }
    m_pRenderer->DisplayBackBuffer();
}
//----------------------------------------------------------------------------
void WindowApplication2::OnResize(int iWidth, int iHeight)
{
    iWidth = iWidth - (iWidth % 4);
    WindowApplication::OnResize(iWidth, iHeight);
    if( iWidth*iHeight <= 0 )
    {
        return;
    }

    if( iWidth != m_iScrWidth || iHeight != m_iScrHeight )
    {
        SE_DELETE[] m_aScreen;
        m_iScrWidth = iWidth;
        m_iScrHeight = iHeight;
        m_aScreen = SE_NEW Color[m_iScrWidth*m_iScrHeight];
        ClearScreen();

        if( m_aFlipScreen )
        {
            SE_DELETE[] m_aFlipScreen;
            m_aFlipScreen = SE_NEW Color[m_iScrWidth*m_iScrHeight];
        }
    }
}
//----------------------------------------------------------------------------
void WindowApplication2::ScreenOverlay()
{
    // 由派生类负责实现
}
//----------------------------------------------------------------------------
void WindowApplication2::ClearScreen()
{
    for( int i = 0; i < m_iWidth*m_iHeight; i++ )
    {
        // This can lead to slow float-to-int conversions.
        //m_aScreen[i].r = (unsigned char)(255.0f*ms_kBackgroundColor.r);
        //m_aScreen[i].b = (unsigned char)(255.0f*ms_kBackgroundColor.g);
        //m_aScreen[i].b = (unsigned char)(255.0f*ms_kBackgroundColor.b);

        // fast float-to-int conversions
        int iValue;
        SE_SCALED_FLOAT_TO_INT(m_BackgroundColor.R, 8, iValue);
        m_aScreen[i].r = (unsigned char)iValue;
        SE_SCALED_FLOAT_TO_INT(m_BackgroundColor.G, 8, iValue);
        m_aScreen[i].g = (unsigned char)iValue;
        SE_SCALED_FLOAT_TO_INT(m_BackgroundColor.B, 8, iValue);
        m_aScreen[i].b = (unsigned char)iValue;
    }
}
//----------------------------------------------------------------------------
bool& WindowApplication2::ClampToWindow()
{
    return m_bClampToWindow;
}
//----------------------------------------------------------------------------
void WindowApplication2::SetPixel(int iX, int iY, Color srcColor)
{
    if( m_bClampToWindow )
    {
        if( 0 <= iX && iX < m_iWidth && 0 <= iY && iY < m_iHeight )
        {
            m_aScreen[Index(iX, iY)] = srcColor;
        }
    }
    else
    {
        m_aScreen[Index(iX, iY)] = srcColor;
    }
}
//----------------------------------------------------------------------------
void WindowApplication2::SetThickPixel(int iX, int iY, int iThick, Color srcColor)
{
    for( int iDY = -iThick; iDY <= iThick; iDY++ )
    {
        for( int iDX = -iThick; iDX <= iThick; iDX++ )
        {
            SetPixel(iX+iDX, iY+iDY, srcColor);
        }
    }
}
//----------------------------------------------------------------------------
WindowApplication2::Color WindowApplication2::GetPixel(int iX, int iY)
{
    if( m_bClampToWindow )
    {
        if( 0 <= iX && iX < m_iWidth && 0 <= iY && iY < m_iHeight )
        {
            return m_aScreen[Index(iX, iY)];
        }
        else
        {
            return Color(0, 0, 0);
        }
    }
    else
    {
        return m_aScreen[Index(iX, iY)];
    }
}
//----------------------------------------------------------------------------
void WindowApplication2::DrawLine(int iX0, int iY0, int iX1, int iY1, Color srcColor)
{
    int iX = iX0, iY = iY0;

    // direction of line
    int iDx = iX1-iX0, iDy = iY1-iY0;

    // increment or decrement depending on direction of line
    int iSx = (iDx > 0 ? 1 : (iDx < 0 ? -1 : 0));
    int iSy = (iDy > 0 ? 1 : (iDy < 0 ? -1 : 0));

    // decision parameters for voxel selection
    if( iDx < 0 )
    {
        iDx = -iDx;
    }
    if( iDy < 0 )
    {
        iDy = -iDy;
    }
    int iAx = 2*iDx, iAy = 2*iDy;
    int iDecX, iDecY;

    // determine largest direction component, single-step related variable
    int iMax = iDx, iVar = 0;
    if( iDy > iMax )
    {
        iVar = 1;
    }

    // traverse Bresenham line
    switch( iVar )
    {
    case 0:  // single-step in x-direction
        iDecY = iAy - iDx;
        for( /**/; /**/; iX += iSx, iDecY += iAy )
        {
            // process pixel
            SetPixel(iX, iY, srcColor);

            // take Bresenham step
            if( iX == iX1 )
            {
                break;
            }
            if( iDecY >= 0 )
            {
                iDecY -= iAx;
                iY += iSy;
            }
        }

        break;
    case 1:  // single-step in y-direction
        iDecX = iAx - iDy;
        for (/**/; /**/; iY += iSy, iDecX += iAx)
        {
            // process pixel
            SetPixel(iX, iY, srcColor);

            // take Bresenham step
            if( iY == iY1 )
            {
                break;
            }
            if( iDecX >= 0 )
            {
                iDecX -= iAy;
                iX += iSx;
            }
        }

        break;
    }
}
//----------------------------------------------------------------------------
void WindowApplication2::DrawRectangle(int iXMin, int iYMin, int iXMax,
    int iYMax, Color srcColor, bool bSolid)
{
    if( iXMin >= m_iWidth || iXMax < 0 || iYMin >= m_iHeight || iYMax < 0 )
    {
        // rectangle not visible
        return;
    }

    int iX, iY;

    if( bSolid )
    {
        for( iY = iYMin; iY <= iYMax; iY++ )
        {
            for( iX = iXMin; iX <= iXMax; iX++ )
            {
                SetPixel(iX, iY, srcColor);
            }
        }
    }
    else
    {
        for( iX = iXMin; iX <= iXMax; iX++ )
        {
            SetPixel(iX, iYMin, srcColor);
            SetPixel(iX, iYMax, srcColor);
        }
        for( iY = iYMin+1; iY <= iYMax-1; iY++ )
        {
            SetPixel(iXMin, iY, srcColor);
            SetPixel(iXMax, iY, srcColor);
        }
    }
}
//----------------------------------------------------------------------------
void WindowApplication2::DrawCircle(int iXCenter, int iYCenter, int iRadius,
    Color srcColor, bool bSolid)
{
    int iX, iY, iDec;

    if( bSolid )
    {
        int iXValue, iYMin, iYMax, i;
        for( iX = 0, iY = iRadius, iDec = 3-2*iRadius; iX <= iY; iX++ )
        {
            iXValue = iXCenter + iX;
            iYMin = iYCenter - iY;
            iYMax = iYCenter + iY;
            for( i = iYMin; i <= iYMax; i++ )
            {
                SetPixel(iXValue, i, srcColor);
            }

            iXValue = iXCenter - iX;
            for( i = iYMin; i <= iYMax; i++ )
            {
                SetPixel(iXValue, i, srcColor);
            }

            iXValue = iXCenter + iY;
            iYMin = iYCenter - iX;
            iYMax = iYCenter + iX;
            for( i = iYMin; i <= iYMax; i++ )
            {
                SetPixel(iXValue, i, srcColor);
            }

            iXValue = iXCenter - iY;
            for( i = iYMin; i <= iYMax; i++ )
            {
                SetPixel(iXValue, i, srcColor);
            }

            if( iDec >= 0 )
            {
                iDec += -4*(iY--)+4;
            }
            iDec += 4*iX+6;
        }
    }
    else
    {
        for( iX = 0, iY = iRadius, iDec = 3-2*iRadius; iX <= iY; iX++ )
        {
            SetPixel(iXCenter+iX, iYCenter+iY, srcColor);
            SetPixel(iXCenter+iX, iYCenter-iY, srcColor);
            SetPixel(iXCenter-iX, iYCenter+iY, srcColor);
            SetPixel(iXCenter-iX, iYCenter-iY, srcColor);
            SetPixel(iXCenter+iY, iYCenter+iX, srcColor);
            SetPixel(iXCenter+iY, iYCenter-iX, srcColor);
            SetPixel(iXCenter-iY, iYCenter+iX, srcColor);
            SetPixel(iXCenter-iY, iYCenter-iX, srcColor);

            if( iDec >= 0 )
            {
                iDec += -4*(iY--)+4;
            }
            iDec += 4*iX+6;
        }
    }
}
//----------------------------------------------------------------------------
void WindowApplication2::Fill(int iX, int iY, Color srcFColor, Color srcBColor)
{
    // Allocate the maximum amount of space needed.  If you prefer less, you
    // need to modify this data structure to allow for dynamic reallocation
    // when it is needed.  An empty stack has iTop == -1.
    int iXMax = m_iWidth, iYMax = m_iHeight;
    int iCount = iXMax*iYMax;
    int* aiXStack = SE_NEW int[iCount];
    int* aiYStack = SE_NEW int[iCount];

    // Push seed point onto stack if it has the background color.  All points
    // pushed onto stack have background color iBColor.
    int iTop = 0;
    aiXStack[iTop] = iX;
    aiYStack[iTop] = iY;

    while( iTop >= 0 )  // stack is not empty
    {
        // Read top of stack.  Do not pop since we need to return to this
        // top value later to restart the fill in a different direction.
        iX = aiXStack[iTop];
        iY = aiYStack[iTop];

        // fill the pixel
        SetPixel(iX, iY, srcFColor);

        int iXp1 = iX+1;
        if( iXp1 < iXMax && GetPixel(iXp1, iY) == srcBColor )
        {
            // push pixel with background color
            iTop++;
            aiXStack[iTop] = iXp1;
            aiYStack[iTop] = iY;

            continue;
        }

        int iXm1 = iX-1;
        if( 0 <= iXm1 && GetPixel(iXm1, iY) == srcBColor )
        {
            // push pixel with background color
            iTop++;
            aiXStack[iTop] = iXm1;
            aiYStack[iTop] = iY;

            continue;
        }

        int iYp1 = iY+1;
        if( iYp1 < iYMax && GetPixel(iX, iYp1) == srcBColor )
        {
            // push pixel with background color
            iTop++;
            aiXStack[iTop] = iX;
            aiYStack[iTop] = iYp1;

            continue;
        }

        int iYm1 = iY-1;
        if( 0 <= iYm1 && GetPixel(iX, iYm1) == srcBColor )
        {
            // push pixel with background color
            iTop++;
            aiXStack[iTop] = iX;
            aiYStack[iTop] = iYm1;

            continue;
        }

        // done in all directions, pop and return to search other directions
        iTop--;
    }

    SE_DELETE[] aiXStack;
    SE_DELETE[] aiYStack;
}
//----------------------------------------------------------------------------
void WindowApplication2::DoFlip(bool bDoFlip)
{
    if( m_aFlipScreen )
    {
        if( !bDoFlip )
        {
            SE_DELETE[] m_aFlipScreen;
            m_aFlipScreen = 0;
        }
    }
    else
    {
        if( bDoFlip )
        {
            m_aFlipScreen = SE_NEW Color[m_iScrWidth*m_iScrHeight];
        }
    }
}
//----------------------------------------------------------------------------
