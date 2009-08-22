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

#include "SEDX9RendererPCH.h"
#include "SEDX9Renderer.h"

using namespace Swing;

//----------------------------------------------------------------------------
int DX9Renderer::LoadFont(const char* acFace, int iSize, bool bBold, 
    bool bItalic)
{
    // Find the first unused font location
    int iLoc;
    for( iLoc = 0; iLoc < (int)m_FontArray.size(); iLoc++ )
    {
        if( !m_FontArray[iLoc] )
        {
            break;
        }
    }

    LPD3DXFONT pqFont;
    DWORD dwWeight = (bBold ? FW_BOLD : FW_REGULAR);

    ms_hResult = D3DXCreateFont(
        m_pDXDevice,                     // pDevice
        iSize,                          // Height
        0,                              // Width
        dwWeight,                       // Weight
        0,                              // MipLevels
        (DWORD)bItalic,                 // Italic
        DEFAULT_CHARSET,                // CharSet
        OUT_DEFAULT_PRECIS,             // OutputPrecision
        ANTIALIASED_QUALITY,            // Quality
        VARIABLE_PITCH,                 // PitchAndFamily
        acFace,                         // pFaceName
        &pqFont);                       // ppFont

    SE_ASSERT( SUCCEEDED(ms_hResult) );

    // Put into the font array.
    if( iLoc == (int)m_FontArray.size() )
    {
        m_FontArray.push_back(pqFont);
    }
    else
    {
        m_FontArray[iLoc] = pqFont;
    }

    return iLoc;
}
//----------------------------------------------------------------------------
void DX9Renderer::UnloadFont(int iFontID)
{
    // You may not unload the default font (id = 0).
    if( 1 <= iFontID && iFontID < (int)m_FontArray.size() )
    {
        m_FontArray[iFontID]->Release();
    }
}
//----------------------------------------------------------------------------
bool DX9Renderer::SelectFont(int iFontID)
{
    if( 0 <= iFontID && iFontID < (int)m_FontArray.size() )
    {
        if( m_FontArray[iFontID] )
        {
            m_iFontID = iFontID;

            return true;
        }
    }

    return false;
}
//----------------------------------------------------------------------------
void DX9Renderer::Draw(int iX, int iY, const ColorRGBA& rColor, const char* acText)
{
    SE_ASSERT( acText );

    if( !acText )
    {
        return;
    }

    RECT TextRect;
    TextRect.bottom = iY;
    TextRect.top = iY;
    TextRect.left = iX;
    TextRect.right = iX;

    D3DCOLOR TextColor = D3DCOLOR_COLORVALUE(rColor.R, rColor.G, rColor.B, rColor.A);

    ms_hResult = m_FontArray[m_iFontID]->DrawText(
        0,                                  // pSprite
        acText,                             // pString
        -1,                                 // Count
        &TextRect,                          // pRect
        DT_LEFT | DT_BOTTOM | DT_CALCRECT,  // Format
        TextColor);                         // Color
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    ms_hResult = m_FontArray[m_iFontID]->DrawText(
        0,
        acText,
        -1,
        &TextRect,
        DT_LEFT | DT_BOTTOM,
        TextColor);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
