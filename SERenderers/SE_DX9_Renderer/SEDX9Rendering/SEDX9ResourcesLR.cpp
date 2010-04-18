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
#include "SEDX9Resources.h"
#include "SEShaderEffect.h"

using namespace Swing;

D3DFORMAT SEDX9Renderer::ms_aeImageFormat[SEImage::IT_COUNT] =
{
    D3DFMT_A8R8G8B8,      // SEImage::IT_RGB888
    D3DFMT_A8R8G8B8,      // SEImage::IT_RGBA8888
    D3DFMT_D16,           // SEImage::IT_DEPTH16
    D3DFMT_D24X8,         // SEImage::IT_DEPTH24
    D3DFMT_D32,           // SEImage::IT_DEPTH32
    D3DFMT_A8R8G8B8,      // SEImage::IT_CUBE_RGB888
    D3DFMT_A8R8G8B8,      // SEImage::IT_CUBE_RGBA8888
    D3DFMT_A32B32G32R32F, // SEImage::IT_RGB32
    D3DFMT_A32B32G32R32F, // SEImage::IT_RGBA32
    D3DFMT_L8,            // SEImage::IT_L8
    D3DFMT_L16,           // SEImage::IT_L16
    D3DFMT_R32F,          // SEImage::IT_R32
    D3DFMT_A16B16G16R16F, // SEImage::IT_RGB16F
    D3DFMT_A16B16G16R16F, // SEImage::IT_RGBA16F
    D3DFMT_R5G6B5,        // SEImage::IT_RGB565
    D3DFMT_A1R5G5B5,      // SEImage::IT_RGBA5551
    D3DFMT_A4R4G4B4       // SEImage::IT_RGBA4444
};

//----------------------------------------------------------------------------
// 资源装载与移除(主要针对显存).
//----------------------------------------------------------------------------
void SEDX9Renderer::OnLoadVProgram(SEResourceIdentifier*& rpID, 
    SEVertexProgram* pVProgram)
{
    // When using multiple renderers, cgD3D9 runtime can not support a 
    // one-to-one relationship between a cg context and a DX device.
    // Every cg context shares the same active DX device, and manages DX
    // related resource(shader programs,parameter handles) by using this
    // active DX device. So it is important to re-set the current renderer's
    // device to the cgD3D9 runtime by using this function.
    // This is a disadvantage of cgD3D9 which reduces renderer's performance.
    cgD3D9SetDevice(m_pDXDevice);
    SE_DX9_DEBUG_CG_PROGRAM;

    SEVProgramID* pResource = SE_NEW SEVProgramID;
    SEProgramData* pData = (SEProgramData*)pVProgram->UserData;
    pResource->ID = pData->ID;
    rpID = pResource;

    ms_hResult = cgD3D9LoadProgram(pResource->ID, false, 0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnReleaseVProgram(SEResourceIdentifier* pID)
{
    SEVProgramID* pResource = (SEVProgramID*)pID;
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnLoadPProgram(SEResourceIdentifier*& rpID, 
    SEPixelProgram* pPProgram)
{
    // When using multiple renderers, cgD3D9 runtime can not support a 
    // one-to-one relationship between a cg context and a DX device.
    // Every cg context shares the same active DX device, and manages DX
    // related resource(shader programs,parameter handles) by using this
    // active DX device. So it is important to re-set the current renderer's
    // device to the cgD3D9 runtime by using this function.
    // This is a disadvantage of cgD3D9 which reduces renderer's performance.
    cgD3D9SetDevice(m_pDXDevice);
    SE_DX9_DEBUG_CG_PROGRAM;

    SEPProgramID* pResource = SE_NEW SEPProgramID;
    SEProgramData* pData = (SEProgramData*)pPProgram->UserData;
    pResource->ID = pData->ID;
    rpID = pResource;

    ms_hResult = cgD3D9LoadProgram(pResource->ID, false, 0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnReleasePProgram(SEResourceIdentifier* pID)
{
    SEPProgramID* pResource = (SEPProgramID*)pID;
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnLoadTexture(SEResourceIdentifier*& rpID, SETexture* 
    pTexture)
{
    // 第一次遇到该纹理资源.
    // 为使用该纹理的设备设置纹理单元.
    SETextureID* pResource = SE_NEW SETextureID;
    pResource->TextureObject = pTexture;
    rpID = pResource;

    bool bOffscreen = pTexture->IsOffscreenTexture();

    // 把image数据从系统内存装载入显存..
    const SEImage* pImage = pTexture->GetImage();
    SE_ASSERT( pImage );
    int iDimension = pImage->GetDimension();
    bool bIsRegularImage = !pImage->IsCubeImage();

    // windows按照BGRA(最低字节到最高字节)顺序储存颜色,
    // 我们按照RGBA顺序.因此必须翻转字节存储顺序.
    int iCount, iByteCount = 0;
    unsigned char* aucSrc = pImage->GetData();
    unsigned char* aucRSrc = 0;
    bool bOwnRSrc = true;
    int i, iSrcBase = 0, iRSrcBase = 0;
    SEImage::FormatMode eFormat = pImage->GetFormat();
    D3DFORMAT eD3DFormat = ms_aeImageFormat[eFormat];

    if( aucSrc )
    {
        switch( eFormat )
        {
        case SEImage::IT_RGB888:
            // Swap R and B and pad to an RGBA image.
            iCount = pImage->GetCount();
            iByteCount = 4*iCount;
            aucRSrc = SE_NEW unsigned char[iByteCount];
            for( i = 0; i < iCount; i++, iSrcBase += 3, iRSrcBase += 4 )
            {
                aucRSrc[iRSrcBase    ] = aucSrc[iSrcBase + 2];
                aucRSrc[iRSrcBase + 1] = aucSrc[iSrcBase + 1];
                aucRSrc[iRSrcBase + 2] = aucSrc[iSrcBase    ];
                aucRSrc[iRSrcBase + 3] = 255;
            }
            break;

        case SEImage::IT_RGBA8888:
            iCount = pImage->GetCount();
            iByteCount = 4*iCount;
            aucRSrc = SE_NEW unsigned char[iByteCount];
            for( i = 0; i < iCount; i++, iSrcBase += 4, iRSrcBase += 4 )
            {
                aucRSrc[iRSrcBase    ] = aucSrc[iSrcBase + 2];
                aucRSrc[iRSrcBase + 1] = aucSrc[iSrcBase + 1];
                aucRSrc[iRSrcBase + 2] = aucSrc[iSrcBase    ];
                aucRSrc[iRSrcBase + 3] = aucSrc[iSrcBase + 3];
            }
            break;

        case SEImage::IT_CUBE_RGB888:
            // Swap R and B and pad to an RGBA image.
            iCount = 6*pImage->GetCount();
            iByteCount = 4*iCount;
            aucRSrc = SE_NEW unsigned char[iByteCount];
            for( i = 0; i < iCount; i++, iSrcBase += 3, iRSrcBase += 4 )
            {
                aucRSrc[iRSrcBase    ] = aucSrc[iSrcBase + 2];
                aucRSrc[iRSrcBase + 1] = aucSrc[iSrcBase + 1];
                aucRSrc[iRSrcBase + 2] = aucSrc[iSrcBase    ];
                aucRSrc[iRSrcBase + 3] = 255;
            }
            iByteCount = 4*pImage->GetCount();
            break;

        case SEImage::IT_CUBE_RGBA8888:
            iCount = 6*pImage->GetCount();
            iByteCount = 4*iCount;
            aucRSrc = SE_NEW unsigned char[iByteCount];
            for( i = 0; i < iCount; i++, iSrcBase += 4, iRSrcBase += 4 )
            {
                aucRSrc[iRSrcBase    ] = aucSrc[iSrcBase + 2];
                aucRSrc[iRSrcBase + 1] = aucSrc[iSrcBase + 1];
                aucRSrc[iRSrcBase + 2] = aucSrc[iSrcBase    ];
                aucRSrc[iRSrcBase + 3] = aucSrc[iSrcBase + 3];
            }
            iByteCount = 4*pImage->GetCount();
            break;

        case SEImage::IT_RGB565:
        {
            // Swap R and B.
            iCount = pImage->GetCount();
            iByteCount = 2*iCount;
            aucRSrc = SE_NEW unsigned char[iByteCount];
            unsigned short* ausSrc = (unsigned short*)aucSrc;
            unsigned short* ausRSrc = (unsigned short*)aucRSrc;
            for( i = 0; i < iCount; i++ )
            {
                unsigned short value = *ausSrc++;
                unsigned short blue = value & 0x001Fu;
                unsigned short green = value & 0x07E0u;
                unsigned short red = value & 0xF800u;
                value = (red >> 11) | green | (blue << 11);
                *ausRSrc++ = value;
            }
            break;
        }

        case SEImage::IT_RGBA5551:
        {
            // Swap R and B.
            iCount = pImage->GetCount();
            iByteCount = 2*iCount;
            aucRSrc = SE_NEW unsigned char[iByteCount];
            unsigned short* ausSrc = (unsigned short*)aucSrc;
            unsigned short* ausRSrc = (unsigned short*)aucRSrc;
            for( i = 0; i < iCount; i++ )
            {
                unsigned short value = *ausSrc++;
                unsigned short blue = value & 0x001Fu;
                unsigned short green = value & 0x03E0u;
                unsigned short red = value & 0x7C00u;
                unsigned short alpha = value & 0x8000u;
                value = (red >> 10) | green | (blue << 10) | alpha;
                *ausRSrc++ = value;
            }
            break;
        }

        case SEImage::IT_RGBA4444:
        {
            // Swap R and B.
            iCount = pImage->GetCount();
            iByteCount = 2*iCount;
            aucRSrc = SE_NEW unsigned char[iByteCount];
            unsigned short* ausSrc = (unsigned short*)aucSrc;
            unsigned short* ausRSrc = (unsigned short*)aucRSrc;
            for( i = 0; i < iCount; i++ )
            {
                unsigned short value = *ausSrc++;
                unsigned short blue = value & 0x000Fu;
                unsigned short green = value & 0x00F0u;
                unsigned short red = value & 0x0F00u;
                unsigned short alpha = value & 0xF000u;
                value = (red >> 8) | green | (blue << 8) | alpha;
                *ausRSrc++ = value;
            }
            break;
        }

        default:
            // There is no need to preprocess depth or intensity images.  The
            // floating-point formats and the 16/32-bit integer formats are
            // already RGB/RGBA.
            aucRSrc = aucSrc;
            bOwnRSrc = false;
            iByteCount = pImage->GetBytesPerPixel()*pImage->GetCount();
            break;
        }
    }

    DWORD dwUsage;
    D3DPOOL tempPool;
    if( bOffscreen )
    {
        dwUsage = D3DUSAGE_RENDERTARGET | D3DUSAGE_AUTOGENMIPMAP;
        tempPool = D3DPOOL_DEFAULT; // 必须创建在显存中
    }
    else
    {
        if( pImage->GetDimension() < 3 )
        {
            dwUsage = D3DUSAGE_AUTOGENMIPMAP;
        }
        else
        {
            dwUsage = 0;
        }
        tempPool = D3DPOOL_MANAGED;
    }

    D3DLOCKED_RECT tempLockRect;

    switch( iDimension )
    {
    case 1:
    {
        // DirectX appears not to have support for 1D textures, but the
        // pImage data works anyway because it is equivalent to an n-by-1
        // 2D image.
        LPDIRECT3DTEXTURE9 pDXTexture;
        ms_hResult = D3DXCreateTexture(m_pDXDevice, pImage->GetBound(0), 1,
            0, dwUsage, eD3DFormat, tempPool, &pDXTexture);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        if( aucRSrc )
        {
            ms_hResult = pDXTexture->LockRect(0, &tempLockRect, 0, 0);
            SE_ASSERT( SUCCEEDED(ms_hResult) );
            memcpy(tempLockRect.pBits, aucRSrc, iByteCount);
            ms_hResult = pDXTexture->UnlockRect(0);
            SE_ASSERT( SUCCEEDED(ms_hResult) );
        }

        pResource->ID = pDXTexture;
        break;
    }
    case 2:
    {
        if( bIsRegularImage )
        {
            LPDIRECT3DTEXTURE9 pDXTexture;
            ms_hResult = D3DXCreateTexture(m_pDXDevice, pImage->GetBound(0),
                pImage->GetBound(1), 0, dwUsage, eD3DFormat, tempPool,
                &pDXTexture);
            SE_ASSERT( SUCCEEDED(ms_hResult) );

            if( !pTexture->IsOffscreenTexture() && aucRSrc )
            {
                ms_hResult = pDXTexture->LockRect(0, &tempLockRect, 0, 0);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                memcpy(tempLockRect.pBits, aucRSrc, iByteCount);
                ms_hResult = pDXTexture->UnlockRect(0);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
            }

            pResource->ID = pDXTexture;
        }
        else
        {
            LPDIRECT3DCUBETEXTURE9 pDXTexture;
            ms_hResult = D3DXCreateCubeTexture(m_pDXDevice, pImage->GetBound(0),
                0, dwUsage, eD3DFormat, tempPool, &pDXTexture);
            SE_ASSERT( SUCCEEDED(ms_hResult) );

            LPDIRECT3DSURFACE9 pFace;
            unsigned char* aucRFace;

            if( aucRSrc )
            {
                aucRFace = aucRSrc;
                ms_hResult = pDXTexture->GetCubeMapSurface(
                    D3DCUBEMAP_FACE_POSITIVE_X, 0, &pFace);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                ms_hResult = pFace->LockRect(&tempLockRect, 0, 0);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                memcpy(tempLockRect.pBits, aucRFace, iByteCount);
                ms_hResult =
                    pDXTexture->UnlockRect(D3DCUBEMAP_FACE_POSITIVE_X, 0);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                pFace->Release();

                aucRFace = aucRSrc + iByteCount;
                ms_hResult = pDXTexture->GetCubeMapSurface(
                    D3DCUBEMAP_FACE_NEGATIVE_X, 0, &pFace);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                ms_hResult = pFace->LockRect(&tempLockRect, 0, 0);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                memcpy(tempLockRect.pBits, aucRFace, iByteCount);
                ms_hResult =
                    pDXTexture->UnlockRect(D3DCUBEMAP_FACE_NEGATIVE_X, 0);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                pFace->Release();

                aucRFace = aucRSrc + 2*iByteCount;
                ms_hResult = pDXTexture->GetCubeMapSurface(
                    D3DCUBEMAP_FACE_POSITIVE_Y, 0, &pFace);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                ms_hResult = pFace->LockRect(&tempLockRect, 0, 0);
                SE_ASSERT(SUCCEEDED( ms_hResult) );
                memcpy(tempLockRect.pBits, aucRFace, iByteCount);
                ms_hResult =
                    pDXTexture->UnlockRect(D3DCUBEMAP_FACE_POSITIVE_Y, 0);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                pFace->Release();

                aucRFace = aucRSrc + 3*iByteCount;
                ms_hResult = pDXTexture->GetCubeMapSurface(
                    D3DCUBEMAP_FACE_NEGATIVE_Y, 0, &pFace);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                ms_hResult = pFace->LockRect(&tempLockRect, 0, 0);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                memcpy(tempLockRect.pBits, aucRFace, iByteCount);
                ms_hResult =
                    pDXTexture->UnlockRect(D3DCUBEMAP_FACE_NEGATIVE_Y, 0);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                pFace->Release();

                aucRFace = aucRSrc + 4*iByteCount;
                ms_hResult = pDXTexture->GetCubeMapSurface(
                    D3DCUBEMAP_FACE_POSITIVE_Z, 0, &pFace);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                ms_hResult = pFace->LockRect(&tempLockRect, 0, 0);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                memcpy(tempLockRect.pBits, aucRFace, iByteCount);
                ms_hResult =
                    pDXTexture->UnlockRect(D3DCUBEMAP_FACE_POSITIVE_Z, 0);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                pFace->Release();

                aucRFace = aucRSrc + 5*iByteCount;
                ms_hResult = pDXTexture->GetCubeMapSurface(
                    D3DCUBEMAP_FACE_NEGATIVE_Z, 0, &pFace);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                ms_hResult = pFace->LockRect(&tempLockRect, 0, 0);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                memcpy(tempLockRect.pBits, aucRFace, iByteCount);
                ms_hResult =
                    pDXTexture->UnlockRect(D3DCUBEMAP_FACE_NEGATIVE_Z, 0);
                SE_ASSERT( SUCCEEDED(ms_hResult) );
                pFace->Release();
            }

            pResource->ID = pDXTexture;
        }
        break;
    }
    case 3:
    {
        LPDIRECT3DVOLUMETEXTURE9 pDXTexture;
        ms_hResult = D3DXCreateVolumeTexture(m_pDXDevice, pImage->GetBound(0),
            pImage->GetBound(1), pImage->GetBound(2), 0, dwUsage, eD3DFormat,
            tempPool, &pDXTexture);
        SE_ASSERT( SUCCEEDED(ms_hResult) );

        if( aucRSrc )
        {
            D3DLOCKED_BOX tempLockBox;
            ms_hResult = pDXTexture->LockBox(0, &tempLockBox, 0, 0);
            SE_ASSERT( SUCCEEDED(ms_hResult) );
            memcpy(tempLockBox.pBits, aucRSrc, iByteCount);
            ms_hResult = pDXTexture->UnlockBox(0);
            SE_ASSERT( SUCCEEDED(ms_hResult) );
        }

        pResource->ID = pDXTexture;

        break;
    }
    default:
        SE_ASSERT( false );

        break;
    }

    if( bOwnRSrc )
    {
        SE_DELETE[] aucRSrc;
    }
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnReleaseTexture(SEResourceIdentifier* pID)
{
    SETextureID* pResource = (SETextureID*)pID;
    ms_hResult = pResource->ID->Release();
    SE_ASSERT( SUCCEEDED(ms_hResult) );
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnLoadVBuffer(SEResourceIdentifier*& rpID,
    const SEAttributes& rIAttr, const SEAttributes& rOAttr,
    SEVertexBuffer* pVBuffer, SEVertexProgram*)
{
    SEVBufferID* pResource = SE_NEW SEVBufferID;
    rpID = pResource;
    pResource->IAttr = rIAttr;
    pResource->OAttr = rOAttr;

    DWORD dwFormat = D3DFVF_XYZ;
    int iVertexSize = 3 * sizeof(float);

    if( rIAttr.HasNormal() )
    {
        dwFormat |= D3DFVF_NORMAL;
        iVertexSize += 3*sizeof(float);
    }

    if( rIAttr.HasColor(0) )
    {
        // DirectX always has RGBA color, stored as unsigned byte
        // channels.
        dwFormat |= D3DFVF_DIFFUSE;
        iVertexSize += sizeof(DWORD);
    }

    if( rIAttr.HasColor(1) )
    {
        // DirectX always has RGBA color, stored as unsigned byte
        // channels.
        dwFormat |= D3DFVF_SPECULAR;
        iVertexSize += sizeof(DWORD);
    }

    int iUnit;
    for( iUnit = 0; iUnit < rIAttr.GetMaxTCoords(); iUnit++ )
    {
        if( rIAttr.HasTCoord(iUnit) )
        {
            switch( rIAttr.GetTCoordChannels(iUnit) )
            {
            case 1:
                dwFormat |= D3DFVF_TEXCOORDSIZE1(iUnit);
                iVertexSize += sizeof(float);

                break;
            case 2:
                dwFormat |= D3DFVF_TEXCOORDSIZE2(iUnit);
                iVertexSize += 2*sizeof(float);

                break;
            case 3:
                dwFormat |= D3DFVF_TEXCOORDSIZE3(iUnit);
                iVertexSize += 3*sizeof(float);

                break;
            case 4:
                dwFormat |= D3DFVF_TEXCOORDSIZE4(iUnit);
                iVertexSize += 4*sizeof(float);

                break;
            }
        }
    }

    // The index of the maximum texture unit needed determines the
    // maximum number of texture coordinate sets defined.
    dwFormat |= (rIAttr.GetMaxTCoords() << D3DFVF_TEXCOUNT_SHIFT);

    // Copy the vertex buffer data to an array.  NOTE:  The output iChannels
    // will be smaller than vertexSize*vertexCount for pVBuffer whenever
    // the vertex buffer attributes have colors.  This is because a SEColorRGBA
    // value is 4 floats but is packed into 1 float.
    int iChannels;
    float* afCompatible = 0;  // 由BuildCompatibleArray函数分配数据
    pVBuffer->BuildCompatibleArray(rIAttr, true, iChannels, afCompatible);

    // 创建vertex buffer.
    unsigned int uiVBSize = (unsigned int)(iChannels*sizeof(float));
    LPDIRECT3DVERTEXBUFFER9 pDXVBuffer;
    ms_hResult = m_pDXDevice->CreateVertexBuffer(uiVBSize, D3DUSAGE_WRITEONLY,
        dwFormat, D3DPOOL_MANAGED, &pDXVBuffer, 0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    // 把vertex buffer数据从系统内存拷入显存.
    float* afVBData;
    ms_hResult = pDXVBuffer->Lock(0, uiVBSize, (void**)(&afVBData), 0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    SESystem::SE_Memcpy(afVBData, uiVBSize, afCompatible, uiVBSize);
    ms_hResult = pDXVBuffer->Unlock();
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    SE_DELETE[] afCompatible;

    // Generate the binding information and save it.
    pResource->ID = pDXVBuffer;
    pResource->VertexSize = iVertexSize;
    pResource->Format = dwFormat;
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnReleaseVBuffer(SEResourceIdentifier* pID)
{
    SEVBufferID* pResource = (SEVBufferID*)pID;
    pResource->ID->Release();
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnLoadIBuffer(SEResourceIdentifier*& rpID, SEIndexBuffer* 
    pIBuffer)
{
    // The index buffer is encountered the first time.
    SEIBufferID* pResource = SE_NEW SEIBufferID;
    rpID = pResource;

    int iICount = pIBuffer->GetIndexCount();
    int* aiIndex = pIBuffer->GetData();
    unsigned int uiIBSize = (unsigned int)(iICount*sizeof(int));

    // Create the index buffer.
    LPDIRECT3DINDEXBUFFER9 pDXIBuffer;
    ms_hResult = m_pDXDevice->CreateIndexBuffer(uiIBSize, D3DUSAGE_WRITEONLY,
        D3DFMT_INDEX32, D3DPOOL_MANAGED, &pDXIBuffer, 0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    // Copy the index buffer data from system memory to video memory.
    char* pcIndices;
    ms_hResult = pDXIBuffer->Lock(0, uiIBSize, (void**)(&pcIndices), 0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    SESystem::SE_Memcpy(pcIndices, uiIBSize, aiIndex, iICount*sizeof(int));

    ms_hResult = pDXIBuffer->Unlock();
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    // Generate the binding information and save it.
    pResource->ID = pDXIBuffer;
}
//----------------------------------------------------------------------------
void SEDX9Renderer::OnReleaseIBuffer(SEResourceIdentifier* pID)
{
    SEIBufferID* pResource = (SEIBufferID*)pID;
    pResource->ID->Release();
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
