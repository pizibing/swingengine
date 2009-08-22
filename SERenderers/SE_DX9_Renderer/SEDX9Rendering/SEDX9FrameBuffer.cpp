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
#include "SEDX9FrameBuffer.h"
#include "SEDX9Resources.h"

using namespace Swing;

SE_IMPLEMENT_INITIALIZE(DX9FrameBuffer);

//SE_REGISTER_INITIALIZE(DX9FrameBuffer);

//----------------------------------------------------------------------------
void DX9FrameBuffer::Initialize()
{
    ms_aoCreator[Renderer::DIRECTX9] = &DX9FrameBuffer::Create;
    ms_aoDestroyer[Renderer::DIRECTX9] = &DX9FrameBuffer::Destroy;
}
//----------------------------------------------------------------------------
FrameBuffer* DX9FrameBuffer::Create(FormatType eFormat, DepthType eDepth,
    StencilType eStencil, BufferingType eBuffering,
    MultisamplingType eMultisampling, Renderer* pRenderer, int iTCount,
    Texture** apTargets)
{
    if( pRenderer && apTargets )
    {
        DX9FrameBuffer* pBuffer = SE_NEW DX9FrameBuffer(eFormat,
            eDepth, eStencil, eBuffering, eMultisampling, pRenderer, iTCount,
            apTargets);

        if( pBuffer->InitializeBuffer() )
        {
            return pBuffer;
        }

        SE_DELETE pBuffer;
    }

    return 0;
}
//----------------------------------------------------------------------------
void DX9FrameBuffer::Destroy(FrameBuffer* pBuffer)
{
    ((DX9FrameBuffer*)pBuffer)->TerminateBuffer();
    SE_DELETE pBuffer;
}
//----------------------------------------------------------------------------
DX9FrameBuffer::DX9FrameBuffer(FormatType eFormat, DepthType eDepth,
    StencilType eStencil, BufferingType eBuffering,
    MultisamplingType eMultisampling, Renderer* pRenderer, int iTCount, 
    Texture** apTargets)
    :
    FrameBuffer(eFormat, eDepth, eStencil, eBuffering, eMultisampling, 
        pRenderer, iTCount, apTargets)
{
    m_TargetItems.resize(iTCount);
    ((DX9Renderer*)pRenderer)->m_FrameBuffers.push_back(this);
}
//----------------------------------------------------------------------------
DX9FrameBuffer::~DX9FrameBuffer()
{
    DX9Renderer* pRenderer = (DX9Renderer*)m_pRenderer;
    std::vector<DX9FrameBuffer*>& rFrameBuffers = pRenderer->m_FrameBuffers;

    int iCount = (int)pRenderer->m_FrameBuffers.size();
    for( int i = 0; i < iCount; i++ )
    {
        if( rFrameBuffers[i] == this )
        {
            // 如果必要则用数组最后元素覆盖当前元素.
            if( i < --iCount )
            {
                rFrameBuffers[i] = rFrameBuffers[iCount];
            }

            // 删除最后元素.
            rFrameBuffers.pop_back();

            return;
        }
    }
}
//----------------------------------------------------------------------------
bool DX9FrameBuffer::InitializeBuffer()
{
    DX9Renderer* pRenderer = (DX9Renderer*)m_pRenderer;
    HRESULT hResult;

    for( int i = 0; i < m_iCount; i++ )
    {
        Image* pImage = m_apTargets[i]->GetImage();
        if( pImage->IsCubeImage() )
        {
            // 待实现.
            // 尚未支持cube map.
            TerminateBuffer();
            return false;
        }

        // 确保用作frame buffer的纹理已经装载入显存.
        ResourceIdentifier* pID = m_apTargets[i]->GetIdentifier(m_pRenderer);
        SE_ASSERT( pID );
        TextureID* pResource = (TextureID*)pID;
        m_TargetItems[i].TargetID = (IDirect3DTexture9*)pResource->ID;

        if( pImage->IsDepthImage() )
        {
            hResult = m_TargetItems[i].TargetID->GetSurfaceLevel(0, 
                &m_TargetItems[i].DepthStencilSurface);
            if( !SUCCEEDED(hResult) )
            {
                m_TargetItems[i].DepthStencilSurface = 0;

                TerminateBuffer();
                return false;
            }
        }
        else
        {
            hResult = m_TargetItems[i].TargetID->GetSurfaceLevel(0, 
                &m_TargetItems[i].TextureSurface);
            if( !SUCCEEDED(hResult) )
            {
                m_TargetItems[i].TextureSurface = 0;

                TerminateBuffer();
                return false;
            }
        }
    }

    // 创建旧式的ID3DXRenderToSurface接口,使用该接口时,
    // 只允许使用一个render target,因此我们取target0.
    D3DSURFACE_DESC tempDesc;
    hResult = m_TargetItems[0].TextureSurface->GetDesc(&tempDesc);
    if( !SUCCEEDED(hResult) )
    {
        SE_DX9_SAFE_RELEASE(m_TargetItems[0].TextureSurface);

        TerminateBuffer();
        return false;
    }
    hResult = D3DXCreateRenderToSurface(pRenderer->m_pDXDevice,
        tempDesc.Width, tempDesc.Height, tempDesc.Format, TRUE, 
        D3DFMT_D24S8, &m_pRenderToTexture);
    if( !SUCCEEDED(hResult) )
    {
        SE_DX9_SAFE_RELEASE(m_TargetItems[0].TextureSurface);
        m_pRenderToTexture = 0;

        TerminateBuffer();
        return false;
    }

    return true;
}
//----------------------------------------------------------------------------
void DX9FrameBuffer::TerminateBuffer()
{
    SE_DX9_SAFE_RELEASE(m_pRenderToTexture);

    for( int i = 0; i < m_iCount; i++ )
    {
        if( m_apTargets[i]->GetImage()->IsDepthImage() )
        {
            SE_DX9_SAFE_RELEASE(m_TargetItems[i].DepthStencilSurface);
        }
        else
        {
            SE_DX9_SAFE_RELEASE(m_TargetItems[i].TextureSurface);
        }

        SE_DX9_SAFE_RELEASE(m_TargetItems[i].CopySurface);
        SE_DX9_SAFE_RELEASE(m_TargetItems[i].CopyTexture);
    }
}
//----------------------------------------------------------------------------
void DX9FrameBuffer::Enable()
{
    DX9Renderer* pRenderer = (DX9Renderer*)m_pRenderer;
    HRESULT hResult;

    if( pRenderer->m_bBeginSceneActive )
    {
        for( int i = 0; i < m_iCount; i++ )
        {
            if( m_apTargets[i]->GetImage()->IsDepthImage() )
            {
                hResult = pRenderer->m_pDXDevice->GetDepthStencilSurface(
                    &m_TargetItems[i].SaveDepthStencilSurface);
                SE_ASSERT( SUCCEEDED(hResult) );

                hResult = pRenderer->m_pDXDevice->SetDepthStencilSurface(
                    m_TargetItems[i].DepthStencilSurface);
                SE_ASSERT( SUCCEEDED(hResult) );
            }
            else
            {
                hResult = pRenderer->m_pDXDevice->GetRenderTarget(i,
                    &m_TargetItems[i].SaveTextureSurface);
                if( !SUCCEEDED(hResult) )
                    m_TargetItems[i].SaveTextureSurface = 0;

                hResult = pRenderer->m_pDXDevice->SetRenderTarget(i,
                    m_TargetItems[i].TextureSurface);
                SE_ASSERT( SUCCEEDED(hResult) );
            }
        }
    }
    else
    {
        // ID3DXRenderToSurface::BeginScene不支持嵌套调用,也不支持MRT.
        SE_ASSERT( m_iCount == 1 );

        hResult = m_pRenderToTexture->BeginScene(
            m_TargetItems[0].TextureSurface, 0);
        SE_ASSERT( SUCCEEDED(hResult) );
    }

    pRenderer->OnFrustumChange();
    pRenderer->OnFrameChange();

    Image* pImage = m_apTargets[0]->GetImage();
    D3DVIEWPORT9 tempViewport;
    tempViewport.X = 0;
    tempViewport.Y = 0;
    tempViewport.Width = (DWORD)pImage->GetBound(0);
    tempViewport.Height = (DWORD)pImage->GetBound(1);
    tempViewport.MinZ = 0.0f;
    tempViewport.MaxZ = 1.0f;
    hResult = pRenderer->m_pDXDevice->SetViewport(&tempViewport);
    SE_ASSERT( SUCCEEDED(hResult) );
}
//----------------------------------------------------------------------------
void DX9FrameBuffer::Disable()
{
    DX9Renderer* pRenderer = (DX9Renderer*)m_pRenderer;
    HRESULT hResult;

    if( pRenderer->m_bBeginSceneActive )
    {
        for( int i = 0; i < m_iCount; i++ )
        {
            if( m_apTargets[i]->GetImage()->IsDepthImage() )
            {
                hResult = pRenderer->m_pDXDevice->SetDepthStencilSurface(
                    m_TargetItems[i].SaveDepthStencilSurface);
                SE_ASSERT( SUCCEEDED(hResult) );

                m_TargetItems[i].SaveDepthStencilSurface->Release();
            }
            else
            {
                hResult = pRenderer->m_pDXDevice->SetRenderTarget(i,
                    m_TargetItems[i].SaveTextureSurface);
                SE_ASSERT( SUCCEEDED(hResult) );

                if( m_TargetItems[i].SaveTextureSurface )
                    m_TargetItems[i].SaveTextureSurface->Release();
            }
        }
    }
    else
    {
        // ID3DXRenderToSurface::EndScene不支持嵌套调用,也不支持MRT.
        SE_ASSERT( m_iCount == 1 );

        hResult = m_pRenderToTexture->EndScene(0);
        SE_ASSERT( SUCCEEDED(hResult) );
    }

    pRenderer->OnViewportChange();
    pRenderer->OnFrustumChange();
    pRenderer->OnFrameChange();
}
//----------------------------------------------------------------------------
void DX9FrameBuffer::CopyToTexture(int i)
{
    SE_ASSERT( i >= 0 && i < m_iCount );
    i = i < 0 ? 0 : (i >= m_iCount ? m_iCount - 1 : i );

    // 待实现. 
    // DX9中,目前没有已知方法可以把深度图数据从VRAM复制到系统内存.
    if( !m_apTargets[i]->GetImage()->IsDepthImage() )
    {
        Image* pImage = m_apTargets[i]->GetImage();
        unsigned char* aucDst = pImage->GetData();
        int iCount = pImage->GetCount();
        int iByteCount = pImage->GetBytesPerPixel() * iCount;
        unsigned char* aucRDst = SE_NEW unsigned char[iByteCount];
        int j, iDstBase = 0, iRDstBase = 0;

        DX9Renderer* pRenderer = (DX9Renderer*)m_pRenderer;
        HRESULT hResult;

        // D3D API要求必须创建一个在系统内存中的D3D纹理,
        // 用来获取render target surface数据.
        if( !m_TargetItems[i].CopyTexture )
        {
            hResult = D3DXCreateTexture(pRenderer->m_pDXDevice,
                pImage->GetBound(0), pImage->GetBound(1), 0,
                0, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM,
                &m_TargetItems[i].CopyTexture);
            SE_ASSERT( SUCCEEDED(hResult) );

            hResult = m_TargetItems[i].CopyTexture->GetSurfaceLevel(0,
                &m_TargetItems[i].CopySurface);
            SE_ASSERT( SUCCEEDED(hResult) );

            hResult = pRenderer->m_pDXDevice->GetRenderTargetData(
                m_TargetItems[i].TextureSurface, m_TargetItems[i].CopySurface);
            SE_ASSERT( SUCCEEDED(hResult) );
        }

        // 待实现.
        // 目前测试表明在我的开发设备上可以这样复制纹理数据,
        // 在旧式设备上是否需要通过tempLockRect.Pitch来逐行读取源纹理数据?
        D3DLOCKED_RECT tempLockRect;
        hResult = m_TargetItems[i].CopySurface->LockRect(&tempLockRect, 0, 0);
        SE_ASSERT( SUCCEEDED(hResult) );
        memcpy(aucRDst, tempLockRect.pBits, iByteCount);
        hResult = m_TargetItems[i].CopySurface->UnlockRect();
        SE_ASSERT( SUCCEEDED(hResult) );

        switch( m_eFormat )
        {
        case FT_FORMAT_RGB:
            for( j = 0; j < iCount; j++, iDstBase += 3, iRDstBase += 4 )
            {
                aucDst[iDstBase    ] = aucRDst[iRDstBase + 2];
                aucDst[iDstBase + 1] = aucRDst[iRDstBase + 1];
                aucDst[iDstBase + 2] = aucRDst[iRDstBase    ];
            }
            break;

        case FT_FORMAT_RGBA:
            for( j = 0; j < iCount; j++, iDstBase += 4, iRDstBase += 4 )
            {
                aucDst[iDstBase    ] = aucRDst[iRDstBase + 2];
                aucDst[iDstBase + 1] = aucRDst[iRDstBase + 1];
                aucDst[iDstBase + 2] = aucRDst[iRDstBase    ];
                aucDst[iDstBase + 3] = aucRDst[iRDstBase + 3];
            }
            break;

        case FT_FORMAT_DEPTH:
            memcpy(aucDst, aucRDst, iByteCount);
            break;

        default:
            SE_ASSERT( false );
            break;
        }

        SE_DELETE[] aucRDst;
    }
}
//----------------------------------------------------------------------------
void DX9FrameBuffer::OnLostDevice()
{
    m_pRenderToTexture->OnLostDevice();

    TerminateBuffer();

    for( int i = 0; i < m_iCount; i++ )
    {
        m_pRenderer->ReleaseTexture(m_apTargets[i]);
    }
}
//----------------------------------------------------------------------------
void DX9FrameBuffer::OnResetDevice()
{
    for( int i = 0; i < m_iCount; i++ )
    {
        m_pRenderer->LoadTexture(m_apTargets[i]);
    }

    InitializeBuffer();
}
//----------------------------------------------------------------------------