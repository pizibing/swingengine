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
#include "SEDX10Resources.h"
#include "SEShaderEffect.h"

using namespace Swing;

DXGI_FORMAT DX10Renderer::ms_aeImageFormat[SEImage::IT_COUNT] =
{
    DXGI_FORMAT_R8G8B8A8_UNORM,      // SEImage::IT_RGB888
    DXGI_FORMAT_R8G8B8A8_UNORM,      // SEImage::IT_RGBA8888
    DXGI_FORMAT_D16_UNORM,           // SEImage::IT_DEPTH16
    DXGI_FORMAT_D24_UNORM_S8_UINT,   // SEImage::IT_DEPTH24
    DXGI_FORMAT_D32_FLOAT,           // SEImage::IT_DEPTH32
    DXGI_FORMAT_R8G8B8A8_UNORM,      // SEImage::IT_CUBE_RGB888
    DXGI_FORMAT_R8G8B8A8_UNORM,      // SEImage::IT_CUBE_RGBA8888
    DXGI_FORMAT_R32G32B32A32_FLOAT,  // SEImage::IT_RGB32
    DXGI_FORMAT_R32G32B32A32_FLOAT,  // SEImage::IT_RGBA32
    DXGI_FORMAT_R8_UNORM,            // SEImage::IT_L8
    DXGI_FORMAT_R16_UNORM,           // SEImage::IT_L16
    DXGI_FORMAT_R32_FLOAT,           // SEImage::IT_R32
    DXGI_FORMAT_R16G16B16A16_FLOAT,  // SEImage::IT_RGB16F
    DXGI_FORMAT_R16G16B16A16_FLOAT,  // SEImage::IT_RGBA16F
    DXGI_FORMAT_R8G8B8A8_UNORM,      // SEImage::IT_RGB565
    DXGI_FORMAT_R8G8B8A8_UNORM,      // SEImage::IT_RGBA5551
    DXGI_FORMAT_R8G8B8A8_UNORM       // SEImage::IT_RGBA4444
};

//----------------------------------------------------------------------------
// 资源装载与移除(主要针对显存).
//----------------------------------------------------------------------------
void DX10Renderer::OnLoadVProgram(SEResourceIdentifier*& rpID, 
    SEVertexProgram* pVProgram)
{
    SEVProgramID* pResource = SE_NEW SEVProgramID;
    SEProgramData* pData = (SEProgramData*)pVProgram->UserData;
    pResource->ID = pData->ID;
    rpID = pResource;

    ms_hResult = cgD3D10LoadProgram(pResource->ID, 0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX10Renderer::OnReleaseVProgram(SEResourceIdentifier* pID)
{
    SEVProgramID* pResource = (SEVProgramID*)pID;
    cgD3D10UnloadProgram(pResource->ID);
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
void DX10Renderer::OnLoadGProgram(SEResourceIdentifier*& rpID,
    SEGeometryProgram* pGProgram)
{
    SEGProgramID* pResource = SE_NEW SEGProgramID;
    SEProgramData* pData = (SEProgramData*)pGProgram->UserData;
    pResource->ID = pData->ID;
    rpID = pResource;

    ms_hResult = cgD3D10LoadProgram(pResource->ID, 0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX10Renderer::OnReleaseGProgram(SEResourceIdentifier* pID)
{
    SEGProgramID* pResource = (SEGProgramID*)pID;
    cgD3D10UnloadProgram(pResource->ID);
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
void DX10Renderer::OnLoadPProgram(SEResourceIdentifier*& rpID, 
    SEPixelProgram* pPProgram)
{
    SEPProgramID* pResource = SE_NEW SEPProgramID;
    SEProgramData* pData = (SEProgramData*)pPProgram->UserData;
    pResource->ID = pData->ID;
    rpID = pResource;

    ms_hResult = cgD3D10LoadProgram(pResource->ID, 0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX10Renderer::OnReleasePProgram(SEResourceIdentifier* pID)
{
    SEPProgramID* pResource = (SEPProgramID*)pID;
    cgD3D10UnloadProgram(pResource->ID);
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
void DX10Renderer::OnLoadTexture(SEResourceIdentifier*& rpID, SETexture* pTexture)
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

    // DXGI_FORMAT_R8G8B8A8_UNORM按照ABGR(最低字节到最高字节)顺序储存颜色,
    // 我们按照RGBA顺序.因此必须翻转字节存储顺序.
    int iCount, iByteCount = 0;
    unsigned char* aucSrc = pImage->GetData();
    unsigned char* aucRSrc = 0;
    bool bOwnRSrc = true;
    int i, iSrcBase = 0, iRSrcBase = 0;
    SEImage::FormatMode eFormat = pImage->GetFormat();
    DXGI_FORMAT eDXGIFMT = ms_aeImageFormat[eFormat];

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

    D3D10_BIND_FLAG eBindFlag;
    D3D10_USAGE eUsage;
    if( bOffscreen )
    {
        eBindFlag = (D3D10_BIND_FLAG)(D3D10_BIND_SHADER_RESOURCE | 
            D3D10_BIND_RENDER_TARGET);
        eUsage = D3D10_USAGE_DEFAULT;
    }
    else
    {
        eBindFlag = D3D10_BIND_SHADER_RESOURCE;
        eUsage = D3D10_USAGE_DEFAULT;
    }

    switch( iDimension )
    {
    case 1:
    {
        // TODO.
        SE_ASSERT( false );
        break;
    }
    case 2:
    {
        if( bIsRegularImage )
        {
   //         D3D10_TEXTURE2D_DESC tempTextureDesc;
   //         tempTextureDesc.Width = pImage->GetBound(0);
   //         tempTextureDesc.Height = pImage->GetBound(1);
   //         tempTextureDesc.MipLevels = 1;
   //         tempTextureDesc.ArraySize = 1;
   //         tempTextureDesc.Format = eDXGIFMT;
   //         tempTextureDesc.SampleDesc.Count = 1;
   //         tempTextureDesc.SampleDesc.Quality = 0;
   //         tempTextureDesc.Usage = eUsage;
   //         tempTextureDesc.BindFlags = eBindFlag;
   //         if( bOffscreen )
   //         {
   //             tempTextureDesc.CPUAccessFlags = 0;
   //         }
   //         else
   //         {
   //             tempTextureDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
   //         }
   //         tempTextureDesc.MiscFlags = 0;

   //         ID3D10Texture2D* pDX10Texture;
   //         ms_hResult = m_pDX10Device->CreateTexture2D(&tempTextureDesc, 
   //             0, &pDX10Texture);
   //         SE_ASSERT( SUCCEEDED(ms_hResult) );

   //         D3D10_MAPPED_TEXTURE2D tempMappedTex;
   //         UINT uiSubResource = D3D10CalcSubresource(0, 0, 1);
   //         pDX10Texture->Map(uiSubResource, D3D10_MAP_WRITE_DISCARD, 0, 
   //             &tempMappedTex);
   //         memcpy(tempMappedTex.pData, aucSrc, iByteCount);
   //         pDX10Texture->Unmap(uiSubResource);

            //D3D10_SHADER_RESOURCE_VIEW_DESC tempView;
            //tempView.Format = eDXGIFMT;
            //ID3D10ShaderResourceView* pView = 0;
            //ms_hResult = m_pDX10Device->CreateShaderResourceView(pDX10Texture, 0, &pView);
            //SE_ASSERT( SUCCEEDED(ms_hResult) );

            D3D10_TEXTURE2D_DESC tempTextureDesc;
            tempTextureDesc.Width = pImage->GetBound(0);
            tempTextureDesc.Height = pImage->GetBound(1);
            tempTextureDesc.MipLevels = 1;
            tempTextureDesc.ArraySize = 1;
            tempTextureDesc.Format = eDXGIFMT;
            tempTextureDesc.SampleDesc.Count = 1;
            tempTextureDesc.SampleDesc.Quality = 0;
            tempTextureDesc.Usage = eUsage;
            tempTextureDesc.BindFlags = eBindFlag;
            tempTextureDesc.CPUAccessFlags = 0;
            tempTextureDesc.MiscFlags = 0;

            D3D10_SUBRESOURCE_DATA tempSubResourceData;
            tempSubResourceData.pSysMem = aucSrc;
            tempSubResourceData.SysMemPitch = iByteCount / tempTextureDesc.Height;
            tempSubResourceData.SysMemSlicePitch = 0;

            ID3D10Texture2D* pDX10Texture;
            ms_hResult = m_pDX10Device->CreateTexture2D(&tempTextureDesc, 
                &tempSubResourceData, &pDX10Texture);
            SE_ASSERT( SUCCEEDED(ms_hResult) );

            D3D10_SHADER_RESOURCE_VIEW_DESC tempViewDesc;
            tempViewDesc.Format = tempTextureDesc.Format;
            tempViewDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
            tempViewDesc.Texture2D.MipLevels = tempTextureDesc.MipLevels;
            tempViewDesc.Texture2D.MostDetailedMip = 0;
            ID3D10ShaderResourceView* pView = 0;
            ms_hResult = m_pDX10Device->CreateShaderResourceView(pDX10Texture, &tempViewDesc, &pView);
            SE_ASSERT( SUCCEEDED(ms_hResult) );

            pResource->ID = (ID3D10Resource*)pDX10Texture;
        }
        else
        {
            // TODO.
            SE_ASSERT( false );
        }

        break;
    }
    case 3:
    {
        // 待实现.
        SE_ASSERT( false );

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
void DX10Renderer::OnReleaseTexture(SEResourceIdentifier* pID)
{
    SETextureID* pResource = (SETextureID*)pID;
    pResource->ID->Release();
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
void DX10Renderer::OnLoadVBuffer(SEResourceIdentifier*& rpID,
    const SEAttributes& rIAttr, const SEAttributes& rOAttr,
    SEVertexBuffer* pVBuffer, SEVertexProgram* pVProgram)
{
    SEVBufferID* pResource = SE_NEW SEVBufferID;
    rpID = pResource;
    pResource->IAttr = rIAttr;
    pResource->OAttr = rOAttr;

    // 用于创建ID3D10InputLayout接口.
    std::vector<D3D10_INPUT_ELEMENT_DESC*> tempDescs;

    // vertex buffer必须具备vertex position.
    D3D10_INPUT_ELEMENT_DESC* pTempDesc = SE_NEW D3D10_INPUT_ELEMENT_DESC;
    pTempDesc->SemanticName = "POSITION";
    pTempDesc->SemanticIndex = 0;
    pTempDesc->Format = DXGI_FORMAT_R32G32B32_FLOAT;
    pTempDesc->InputSlot = 0;
    pTempDesc->AlignedByteOffset = 0;
    pTempDesc->InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
    pTempDesc->InstanceDataStepRate = 0;
    tempDescs.push_back(pTempDesc);
    int iVertexSize = 3*sizeof(float);

    if( rIAttr.HasNormal() )
    {
        pTempDesc = SE_NEW D3D10_INPUT_ELEMENT_DESC;
        pTempDesc->SemanticName = "NORMAL";
        pTempDesc->SemanticIndex = 0;
        pTempDesc->Format = DXGI_FORMAT_R32G32B32_FLOAT;
        pTempDesc->InputSlot = 0;
        pTempDesc->AlignedByteOffset = iVertexSize;
        pTempDesc->InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
        pTempDesc->InstanceDataStepRate = 0;
        tempDescs.push_back(pTempDesc);
        iVertexSize += 3*sizeof(float);
    }

    if( rIAttr.HasColor(0) )
    {
        pTempDesc = SE_NEW D3D10_INPUT_ELEMENT_DESC;
        pTempDesc->SemanticName = "COLOR";
        pTempDesc->SemanticIndex = 0;
        pTempDesc->InputSlot = 0;
        pTempDesc->AlignedByteOffset = iVertexSize;
        pTempDesc->InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
        pTempDesc->InstanceDataStepRate = 0;

        switch( rIAttr.GetColorChannels(0) )
        {
        case 1:
            pTempDesc->Format = DXGI_FORMAT_R32_FLOAT;
            iVertexSize += sizeof(float);
            break;
        case 2:
            pTempDesc->Format = DXGI_FORMAT_R32G32_FLOAT;
            iVertexSize += 2*sizeof(float);
            break;
        case 3:
            pTempDesc->Format = DXGI_FORMAT_R32G32B32_FLOAT;
            iVertexSize += 3*sizeof(float);
            break;
        case 4:
            pTempDesc->Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
            iVertexSize += 4*sizeof(float);
            break;
        }

        tempDescs.push_back(pTempDesc);
    }

    if( rIAttr.HasColor(1) )
    {
        pTempDesc = SE_NEW D3D10_INPUT_ELEMENT_DESC;
        pTempDesc->SemanticName = "COLOR";
        pTempDesc->SemanticIndex = 1;
        pTempDesc->InputSlot = 0;
        pTempDesc->AlignedByteOffset = iVertexSize;
        pTempDesc->InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
        pTempDesc->InstanceDataStepRate = 0;

        switch( rIAttr.GetColorChannels(1) )
        {
        case 1:
            pTempDesc->Format = DXGI_FORMAT_R32_FLOAT;
            iVertexSize += sizeof(float);
            break;
        case 2:
            pTempDesc->Format = DXGI_FORMAT_R32G32_FLOAT;
            iVertexSize += 2*sizeof(float);
            break;
        case 3:
            pTempDesc->Format = DXGI_FORMAT_R32G32B32_FLOAT;
            iVertexSize += 3*sizeof(float);
            break;
        case 4:
            pTempDesc->Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
            iVertexSize += 4*sizeof(float);
            break;
        }

        tempDescs.push_back(pTempDesc);
    }

    int iUnit;
    for( iUnit = 0; iUnit < rIAttr.GetMaxTCoords(); iUnit++ )
    {
        if( rIAttr.HasTCoord(iUnit) )
        {
            pTempDesc = SE_NEW D3D10_INPUT_ELEMENT_DESC;
            pTempDesc->SemanticName = "TEXCOORD";
            pTempDesc->SemanticIndex = iUnit;
            pTempDesc->InputSlot = 0;
            pTempDesc->AlignedByteOffset = iVertexSize;
            pTempDesc->InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
            pTempDesc->InstanceDataStepRate = 0;

            switch( rIAttr.GetTCoordChannels(iUnit) )
            {
            case 1:
                pTempDesc->Format = DXGI_FORMAT_R32_FLOAT;
                iVertexSize += sizeof(float);
                break;
            case 2:
                pTempDesc->Format = DXGI_FORMAT_R32G32_FLOAT;
                iVertexSize += 2*sizeof(float);
                break;
            case 3:
                pTempDesc->Format = DXGI_FORMAT_R32G32B32_FLOAT;
                iVertexSize += 3*sizeof(float);
                break;
            case 4:
                pTempDesc->Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
                iVertexSize += 4*sizeof(float);
                break;
            }

            tempDescs.push_back(pTempDesc);
        }
    }

    // 创建input layout.
    int iElementCount = (int)tempDescs.size();
    D3D10_INPUT_ELEMENT_DESC* pIEDescs = 
        SE_NEW D3D10_INPUT_ELEMENT_DESC[iElementCount];
    for( int i = 0; i < iElementCount; i++ )
    {
        pIEDescs[i] = *tempDescs[i];
    }

    CGprogram hProgram = ((SEProgramData*)pVProgram->UserData)->ID;
    ID3D10Blob* pVShaderBuffer = cgD3D10GetCompiledProgram(hProgram);
    SE_ASSERT( pVShaderBuffer );

    ID3D10InputLayout* pDX10Layout;
    ms_hResult = m_pDX10Device->CreateInputLayout(pIEDescs, iElementCount, 
        pVShaderBuffer->GetBufferPointer(), pVShaderBuffer->GetBufferSize(),
        &pDX10Layout);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    SE_DELETE[] pIEDescs;
    for( int i = 0; i < iElementCount; i++ )
    {
        SE_DELETE tempDescs[i];
    }

    int iChannels;
    float* afCompatible = 0;  // 由BuildCompatibleArray函数分配数据
    pVBuffer->BuildCompatibleArray(rIAttr, false, iChannels, afCompatible);

    // 创建vertex buffer.
    unsigned int uiVBSize = (unsigned int)(iChannels*sizeof(float));
    D3D10_BUFFER_DESC tempVBDesc;
    tempVBDesc.Usage = D3D10_USAGE_DEFAULT;
    tempVBDesc.ByteWidth = uiVBSize;
    tempVBDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    tempVBDesc.CPUAccessFlags = 0;
    tempVBDesc.MiscFlags = 0;
    D3D10_SUBRESOURCE_DATA tempInitData;
    tempInitData.pSysMem = afCompatible;

    ID3D10Buffer* pDX10VBuffer;
    ms_hResult = m_pDX10Device->CreateBuffer(&tempVBDesc, &tempInitData, 
        &pDX10VBuffer);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    SE_DELETE[] afCompatible;

    // 创建绑定信息并保存.
    pResource->ID = pDX10VBuffer;
    pResource->VertexSize = iVertexSize;
    pResource->Offset = 0;
    pResource->Layout = pDX10Layout;
}
//----------------------------------------------------------------------------
void DX10Renderer::OnReleaseVBuffer(SEResourceIdentifier* pID)
{
    SEVBufferID* pResource = (SEVBufferID*)pID;
    pResource->ID->Release();
    pResource->Layout->Release();
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
void DX10Renderer::OnLoadIBuffer(SEResourceIdentifier*& rpID, SEIndexBuffer* pIBuffer)
{
    SEIBufferID* pResource = SE_NEW SEIBufferID;
    rpID = pResource;

    int iICount = pIBuffer->GetIndexCount();
    int* aiIndex = pIBuffer->GetData();
    unsigned int uiIBSize = (unsigned int)(iICount*sizeof(int));

    // 创建index buffer.
    D3D10_BUFFER_DESC tempIBDesc;
    tempIBDesc.Usage = D3D10_USAGE_DEFAULT;
    tempIBDesc.ByteWidth = uiIBSize;
    tempIBDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
    tempIBDesc.CPUAccessFlags = 0;
    tempIBDesc.MiscFlags = 0;
    D3D10_SUBRESOURCE_DATA tempInitData;
    tempInitData.pSysMem = aiIndex;

    ID3D10Buffer* pDX10IBuffer;
    ms_hResult = m_pDX10Device->CreateBuffer(&tempIBDesc, &tempInitData,
        &pDX10IBuffer);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    // 创建绑定信息并保存.
    pResource->ID = pDX10IBuffer;
}
//----------------------------------------------------------------------------
void DX10Renderer::OnReleaseIBuffer(SEResourceIdentifier* pID)
{
    SEIBufferID* pResource = (SEIBufferID*)pID;
    pResource->ID->Release();
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
void DX10Renderer::OnLoadRenderStateBlock(SEResourceIdentifier*& rpID,
    SERenderStateBlock* pRStateBlock)
{
    SERStateBlockID* pResource = SE_NEW SERStateBlockID;
    pResource->RStateBlock = pRStateBlock;
    rpID = pResource;

    // 创建ID3D10BlendState对象.
    ID3D10BlendState* pDX10BState = 0;
    GenerateBlendState(pRStateBlock, pDX10BState);

    // 创建ID3D10DepthStencilState对象.
    ID3D10DepthStencilState* pDX10DSState = 0;
    GenerateDepthStencilState(pRStateBlock, pDX10DSState);

    // 创建ID3D10RasterizerState对象.
    ID3D10RasterizerState* pDX10RState = 0;
    GenerateRasterizerState(pRStateBlock, pDX10RState);

    // 创建绑定信息并保存.
    pResource->BlendState = pDX10BState;
    pResource->DepthStencilState = pDX10DSState;
    pResource->RasterizerState = pDX10RState;
}
//----------------------------------------------------------------------------
void DX10Renderer::OnReleaseRenderStateBlock(SEResourceIdentifier* pID)
{
    SERStateBlockID* pResource = (SERStateBlockID*)pID;
    SE_DX10_SAFE_RELEASE(pResource->BlendState);
    SE_DX10_SAFE_RELEASE(pResource->DepthStencilState);
    SE_DX10_SAFE_RELEASE(pResource->RasterizerState);
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------