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
//
//----------------------------------------------------------------------------
// AngelCode Tool Box Library
// Copyright (c) 2007-2008 Andreas Jonsson
//
// This software is provided 'as-is', without any express or implied 
// warranty. In no event will the authors be held liable for any 
// damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any 
// purpose, including commercial applications, and to alter it and 
// redistribute it freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you 
//    must not claim that you wrote the original software. If you use
//    this software in a product, an acknowledgment in the product 
//    documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and 
//    must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source 
//    distribution.
//
// Andreas Jonsson
// andreas@angelcode.com
//----------------------------------------------------------------------------

#include "SEGuiPCH.h"
#include "SEBMFont.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SEBMFont, SEObject);
SE_IMPLEMENT_STREAM(SEBMFont);
SE_IMPLEMENT_DEFAULT_STREAM(SEBMFont, SEObject);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEBMFont, SEObject);

//SE_REGISTER_STREAM(SEBMFont);

//----------------------------------------------------------------------------
SEBMFont::SEBMFont(char* pRawData, int iDataSize)
{
    m_pInfoBlock = 0;
    m_pCommonBlock = 0;
    m_aCharInfo = 0;
    m_iCharInfoCount = 0;
    m_aKerningPair = 0;
    m_ikerningPairCount = 0;
    m_iTexturePageCount = 0;

    Initialize(pRawData, iDataSize);
}
//----------------------------------------------------------------------------
SEBMFont::SEBMFont()
{
    m_pInfoBlock = 0;
    m_pCommonBlock = 0;
    m_aCharInfo = 0;
    m_iCharInfoCount = 0;
    m_aKerningPair = 0;
    m_ikerningPairCount = 0;
    m_iTexturePageCount = 0;
}
//----------------------------------------------------------------------------
SEBMFont::~SEBMFont()
{
    SE_DELETE m_pInfoBlock;
    SE_DELETE m_pCommonBlock;
    SE_DELETE[] m_aCharInfo;
    SE_DELETE[] m_aKerningPair;
}
//----------------------------------------------------------------------------
SEBMFontInfoBlock* SEBMFont::GetInfoBlock()
{
    return m_pInfoBlock;
}
//----------------------------------------------------------------------------
SEBMFontCommonBlock* SEBMFont::GetCommonBlock()
{
    return m_pCommonBlock;
}
//----------------------------------------------------------------------------
int SEBMFont::GetCharInfoCount() const
{
    return m_iCharInfoCount;
}
//----------------------------------------------------------------------------
SEBMFontCharInfo* SEBMFont::GetCharInfo(int i)
{
    SE_ASSERT( 0 <= i && i < m_iCharInfoCount );
    SE_ASSERT( m_aCharInfo );

    return &m_aCharInfo[i];
}
//----------------------------------------------------------------------------
SEBMFontCharInfo* SEBMFont::GetCharInfo(wchar_t wcChar)
{
    SE_ASSERT( m_aCharInfo );

    for( int i = 0; i < m_iCharInfoCount; i++ )
    {
        SEBMFontCharInfo* pCharInfo = &m_aCharInfo[i];
        if( pCharInfo->ID == wcChar )
        {
            return pCharInfo;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
int SEBMFont::GetKerningPairCount() const
{
    return m_ikerningPairCount;
}
//----------------------------------------------------------------------------
SEBMFontKerningPair* SEBMFont::GetKerningPair(int i)
{
    SE_ASSERT( 0 <= i && i < m_ikerningPairCount );
    SE_ASSERT( m_aKerningPair );

    return &m_aKerningPair[i];
}
//----------------------------------------------------------------------------
SEBMFontKerningPair* SEBMFont::GetKerningPair(wchar_t wcFirst, wchar_t 
    wcSecond)
{
    SE_ASSERT( m_aKerningPair );

    for( int i = 0; i < m_ikerningPairCount; i++ )
    {
        SEBMFontKerningPair* pKerningPair = &m_aKerningPair[i];
        if( pKerningPair->First == wcFirst && 
            pKerningPair->Second == wcSecond )
        {
            return pKerningPair;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
int SEBMFont::GetTexturePageCount() const
{
    return m_iTexturePageCount;
}
//----------------------------------------------------------------------------
const std::string& SEBMFont::GetTexturePageName(int i) const
{
    SE_ASSERT( 0 <= i && i < m_iTexturePageCount );

    return m_aTextureNames[i];
}
//----------------------------------------------------------------------------
void SEBMFont::SetTexturePage(int i, SETexture* pTexture)
{
    SE_ASSERT( 0 <= i && i < m_iTexturePageCount );

    m_aspTextures[i] = pTexture;
}
//----------------------------------------------------------------------------
SETexture* SEBMFont::GetTexturePage(int i)
{
    SE_ASSERT( 0 <= i && i < m_iTexturePageCount );

    return m_aspTextures[i];
}
//----------------------------------------------------------------------------
SEBMFont* SEBMFont::Load(const char* acBMFontName)
{
    SE_ASSERT( acBMFontName );

    std::string strFileName = std::string(acBMFontName) + std::string(".fnt");
    const char* pDecorated = SESystem::SE_GetPath(strFileName.c_str(), 
        SESystem::SM_READ);
    if( !pDecorated )
    {
        return 0;
    }

    char* acBuffer;
    int iSize;
    bool bLoaded = SESystem::SE_Load(pDecorated, acBuffer, iSize);
    if( !bLoaded )
    {
        // ÎÄ¼þ¶ÁÈ¡Ê§°Ü.
        return 0;
    }

    SEBMFont* pBMFont = SE_NEW SEBMFont(acBuffer, iSize);
    return pBMFont;
}
//----------------------------------------------------------------------------
void SEBMFont::Initialize(char* pRawData, int iDataSize)
{
    SE_ASSERT( pRawData && iDataSize > 0 );

    char* pCurrent = pRawData;

    if( pCurrent[0] != 'B' || pCurrent[1] != 'M' || pCurrent[2] != 'F' || 
        pCurrent[3] != 3 )
    {
        SE_DELETE[] pRawData;

        return;
    }

    // Skip "BMF3", which is the current newest verson of BMFont file.
    pCurrent += 4;

    char* pEnd = pRawData + iDataSize;
    while( pCurrent < pEnd )
    {
        // Get current block type.
        unsigned char ucBlockType;
        pCurrent += SESystem::SE_Read1(pCurrent, 1, &ucBlockType);

        // Get current block length.
        int iBlockLength;
        pCurrent += SESystem::SE_Read4le(pCurrent, 1, &iBlockLength);

        // Process current block.
        switch( ucBlockType )
        {
        case 1:
            SE_ASSERT( !m_pInfoBlock );
            m_pInfoBlock = SE_NEW SEBMFontInfoBlock;

            pCurrent += SESystem::SE_Read2le(pCurrent, 1, 
                &m_pInfoBlock->FontSize);

            pCurrent += SESystem::SE_Read1(pCurrent, 1, 
                &m_pInfoBlock->BitField);

            pCurrent += SESystem::SE_Read1(pCurrent, 1, 
                &m_pInfoBlock->CharSet);

            pCurrent += SESystem::SE_Read2le(pCurrent, 1, 
                &m_pInfoBlock->StretchH);

            pCurrent += SESystem::SE_Read1(pCurrent, 1, 
                &m_pInfoBlock->AA);

            pCurrent += SESystem::SE_Read1(pCurrent, 1, 
                &m_pInfoBlock->PaddingUp);

            pCurrent += SESystem::SE_Read1(pCurrent, 1, 
                &m_pInfoBlock->PaddingRight);

            pCurrent += SESystem::SE_Read1(pCurrent, 1, 
                &m_pInfoBlock->PaddingDown);

            pCurrent += SESystem::SE_Read1(pCurrent, 1, 
                &m_pInfoBlock->PaddingLeft);

            pCurrent += SESystem::SE_Read1(pCurrent, 1, 
                &m_pInfoBlock->SpacingHoriz);

            pCurrent += SESystem::SE_Read1(pCurrent, 1, 
                &m_pInfoBlock->SpacingVert);

            pCurrent += SESystem::SE_Read1(pCurrent, 1, 
                &m_pInfoBlock->Outline);

            m_pInfoBlock->FontName = pCurrent;
            pCurrent += m_pInfoBlock->FontName.length() + 1;

            break;

        case 2:
            SE_ASSERT( !m_pCommonBlock );
            m_pCommonBlock = SE_NEW SEBMFontCommonBlock;
            
            pCurrent += SESystem::SE_Read2le(pCurrent, 1, 
                &m_pCommonBlock->LineHeight);

            pCurrent += SESystem::SE_Read2le(pCurrent, 1, 
                &m_pCommonBlock->Base);

            pCurrent += SESystem::SE_Read2le(pCurrent, 1, 
                &m_pCommonBlock->ScaleW);

            pCurrent += SESystem::SE_Read2le(pCurrent, 1, 
                &m_pCommonBlock->ScaleH);

            pCurrent += SESystem::SE_Read2le(pCurrent, 1, 
                &m_pCommonBlock->Pages);

            pCurrent += SESystem::SE_Read1(pCurrent, 1, 
                &m_pCommonBlock->BitField);

            pCurrent += SESystem::SE_Read1(pCurrent, 1, 
                &m_pCommonBlock->AlphaChnl);

            pCurrent += SESystem::SE_Read1(pCurrent, 1, 
                &m_pCommonBlock->RedChnl);

            pCurrent += SESystem::SE_Read1(pCurrent, 1, 
                &m_pCommonBlock->GreenChnl);

            pCurrent += SESystem::SE_Read1(pCurrent, 1, 
                &m_pCommonBlock->BlueChnl);

            break;

        case 3:
            SE_ASSERT( m_pCommonBlock );

            if( m_pCommonBlock )
            {
                m_iTexturePageCount = m_pCommonBlock->Pages;
                SE_ASSERT( m_iTexturePageCount <= MAX_TEXTUREPAGES );

                char* acTextureName = (char*)pCurrent;
                for( int i = 0; i < m_pCommonBlock->Pages; i++ )
                {
                    m_aTextureNames[i] = acTextureName;
                    acTextureName += strlen(acTextureName) + 1;
                }
            }

            pCurrent += iBlockLength;
            break;

        case 4:
            m_iCharInfoCount = iBlockLength / 20;
            m_aCharInfo = SE_NEW SEBMFontCharInfo[m_iCharInfoCount];

            for( int i = 0; i < m_iCharInfoCount; i++ )
            {
                pCurrent += SESystem::SE_Read4le(pCurrent, 1, 
                    &m_aCharInfo[i].ID);

                pCurrent += SESystem::SE_Read2le(pCurrent, 1, 
                    &m_aCharInfo[i].X);

                pCurrent += SESystem::SE_Read2le(pCurrent, 1, 
                    &m_aCharInfo[i].Y);

                pCurrent += SESystem::SE_Read2le(pCurrent, 1, 
                    &m_aCharInfo[i].Width);

                pCurrent += SESystem::SE_Read2le(pCurrent, 1, 
                    &m_aCharInfo[i].Height);

                pCurrent += SESystem::SE_Read2le(pCurrent, 1, 
                    &m_aCharInfo[i].XOffset);

                pCurrent += SESystem::SE_Read2le(pCurrent, 1, 
                    &m_aCharInfo[i].YOffset);

                pCurrent += SESystem::SE_Read2le(pCurrent, 1, 
                    &m_aCharInfo[i].XAdvance);

                pCurrent += SESystem::SE_Read1(pCurrent, 1, 
                    &m_aCharInfo[i].Page);

                pCurrent += SESystem::SE_Read1(pCurrent, 1, 
                    &m_aCharInfo[i].Chnl);
            }

            break;

        case 5:
            m_ikerningPairCount = iBlockLength / 10;
            m_aKerningPair = SE_NEW SEBMFontKerningPair[m_ikerningPairCount];

            for( int i = 0; i < m_ikerningPairCount; i++ )
            {
                pCurrent += SESystem::SE_Read4le(pCurrent, 1, 
                    &m_aKerningPair[i].First);

                pCurrent += SESystem::SE_Read4le(pCurrent, 1, 
                    &m_aKerningPair[i].Second);

                pCurrent += SESystem::SE_Read2le(pCurrent, 1, 
                    &m_aKerningPair[i].Amount);
            }

            break;

        default:
            SE_ASSERT( false );
            break;
        }
    }

    SE_DELETE[] pRawData;
}
//----------------------------------------------------------------------------