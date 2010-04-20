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

#include "SEDX10RendererPCH.h"
#include "SEDX10Renderer.h"

using namespace Swing;

//----------------------------------------------------------------------------
int DX10Renderer::LoadFont(const char* acFace, int iSize, bool bBold, 
    bool bItalic)
{
    // 找一个未使用的位置.
    int iLoc;
    for( iLoc = 0; iLoc < (int)m_FontArray.size(); iLoc++ )
    {
        if( !m_FontArray[iLoc] )
        {
            break;
        }
    }

    ID3DX10Font* pDX10Font;
    UINT uiWeight = (bBold ? FW_BOLD : FW_REGULAR);

    D3DX10_FONT_DESC tempFontDesc;
    tempFontDesc.Height = iSize;
    tempFontDesc.Width = 0;
    tempFontDesc.Weight = uiWeight;
    tempFontDesc.MipLevels = 0;
    tempFontDesc.Italic = bItalic;
    tempFontDesc.CharSet = DEFAULT_CHARSET;
    tempFontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
    tempFontDesc.Quality = DEFAULT_QUALITY;
    tempFontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    SESystem::SE_Strcpy(tempFontDesc.FaceName, sizeof(tempFontDesc.FaceName), 
        acFace);

    ms_hResult = D3DX10CreateFontIndirect(m_pDX10Device, &tempFontDesc, 
        &pDX10Font);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    // 加入到font array.
    if( iLoc == (int)m_FontArray.size() )
    {
        m_FontArray.push_back(pDX10Font);
    }
    else
    {
        m_FontArray[iLoc] = pDX10Font;
    }

    return iLoc;
}
//----------------------------------------------------------------------------
void DX10Renderer::UnloadFont(int iFontID)
{
    // 不能unload默认字体(id = 0).
    if( 1 <= iFontID && iFontID < (int)m_FontArray.size() )
    {
        m_FontArray[iFontID]->Release();
    }
}
//----------------------------------------------------------------------------
bool DX10Renderer::SelectFont(int iFontID)
{
    if( 0 <= iFontID && iFontID < (int)m_FontArray.size() )
    {
        if( m_FontArray[iFontID] )
        {
            m_iFontID = iFontID;

            return true;
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void DX10Renderer::Draw(int iX, int iY, const SEColorRGBA& rColor, 
    const char* acText)
{
    SE_ASSERT( acText );

    if( !acText )
    {
        return;
    }

    RECT TextRect;
    TextRect.left = iX;
    TextRect.top = iY;
    TextRect.right = 0;
    TextRect.bottom = 0;

    D3DXCOLOR TextColor(rColor.R, rColor.G, rColor.B, rColor.A);

    m_pDX10Device->RSSetState(m_pDX10RasterizerState);
    ms_hResult = m_FontArray[m_iFontID]->DrawText(
        0,                                  // pSprite
        acText,                             // pString
        -1,                                 // Count
        &TextRect,                          // pRect
        DT_NOCLIP,                          // Format
        TextColor);                         // Color
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    // ID3DX10Font::DrawText会改变geometry stage state,因此恢复到默认值.
    m_pDX10Device->GSSetShader(0);
}
//----------------------------------------------------------------------------
