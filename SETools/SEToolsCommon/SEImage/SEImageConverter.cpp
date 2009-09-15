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

#include "SEToolsCommonPCH.h"
#include "SEImageConverter.h"

using namespace Swing;

//----------------------------------------------------------------------------
ImageConverter::ImageConverter(IDirect3DDevice9* pDevice)
{
    SE_ASSERT( pDevice );
    m_pDXDevice = pDevice;
}
//----------------------------------------------------------------------------
ImageConverter::ImageConverter()
{
}
//----------------------------------------------------------------------------
ImageConverter::~ImageConverter()
{
}
//----------------------------------------------------------------------------
Image* ImageConverter::CreateImageFromFile(const char* acFilename)
{
    if( !acFilename )
    {
        return 0;
    }

    HRESULT hResult;
    LPDIRECT3DTEXTURE9 pDXTex;
    Image* pImage;

    hResult = D3DXCreateTextureFromFile(m_pDXDevice, acFilename, &pDXTex);
    if( !SUCCEEDED(hResult) )
    {
        return 0;
    }

    D3DSURFACE_DESC tempDesc;
    pDXTex->GetLevelDesc(0, &tempDesc);

    int iWidth = tempDesc.Width;
    int iHeight = tempDesc.Height;
    int eFormat = D3DFMT_UNKNOWN;
    int iBytesPerPixel = 0;
    switch( tempDesc.Format )
    {
        case D3DFMT_R8G8B8:
        {
            eFormat = Image::IT_RGB888;
            iBytesPerPixel = 3;

            break;
        }
        case D3DFMT_A8R8G8B8:
        case D3DFMT_X8R8G8B8:
        {
            eFormat = Image::IT_RGBA8888;
            iBytesPerPixel = 4;

            break;
        }
        case D3DFMT_L8:
        {
            eFormat = Image::IT_L8;
            iBytesPerPixel = 1;

            break;
        }
        case D3DFMT_L16:
        {
            eFormat = Image::IT_L16;
            iBytesPerPixel = 2;

            break;
        }
        default:
        {
            // 尚未支持的情况.
            SE_ASSERT( 0 );
            break;
        }
    }
    int iCount = iWidth * iHeight;
    int iByteCount = iCount * iBytesPerPixel;
    unsigned char* aucDst = SE_NEW unsigned char[iByteCount];
    unsigned char* pDst, * pSrc;

    D3DLOCKED_RECT tempLockRect;
    hResult = pDXTex->LockRect(0, &tempLockRect, 0, 0);
    SE_ASSERT( SUCCEEDED(hResult) );
    pSrc = (unsigned char*)tempLockRect.pBits;
    pDst = aucDst;
    int i, iBase = 0;
    switch( eFormat )
    {
        case Image::IT_RGB888:
        {
            for( i = 0; i < iCount; i++, iBase += 3 )
            {
                pDst[iBase    ] = pSrc[iBase + 2];
                pDst[iBase + 1] = pSrc[iBase + 1];
                pDst[iBase + 2] = pSrc[iBase    ];
            }

            break;
        }
        case Image::IT_RGBA8888:
        {
            for( i = 0; i < iCount; i++, iBase += 4 )
            {
                pDst[iBase    ] = pSrc[iBase + 2];
                pDst[iBase + 1] = pSrc[iBase + 1];
                pDst[iBase + 2] = pSrc[iBase    ];
                pDst[iBase + 3] = pSrc[iBase + 3];
            }

            break;
        }
        case Image::IT_L8:
        {
            for( i = 0; i < iCount; i++, iBase += 1 )
            {
                pDst[iBase] = pSrc[iBase];
            }

            break;
        }
        case Image::IT_L16:
        {
            for( i = 0; i < iCount; i++, iBase += 2 )
            {
                pDst[iBase    ] = pSrc[iBase    ];
                pDst[iBase + 1] = pSrc[iBase + 1];
            }

            break;
        }
        default:
        {
            // 尚未支持的情况.
            SE_ASSERT( 0 );
            break;
        }
    }
    hResult = pDXTex->UnlockRect(0);
    SE_ASSERT( SUCCEEDED(hResult) );
    pDXTex->Release();

    pImage = SE_NEW Image((Image::FormatMode)eFormat, iWidth, iHeight, 
        aucDst, acFilename, false);
    SE_ASSERT( pImage );

    return pImage;
}
//----------------------------------------------------------------------------