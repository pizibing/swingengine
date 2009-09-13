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

#include "stdafx.h"
#include "SEImageExporterApp.h"

HRESULT ImageExporterApp::ms_hResult = 0;

using namespace Swing;

//----------------------------------------------------------------------------
ImageExporterApp::ImageExporterApp()
{
    m_spImage = 0;
    m_bOpenFile = false;
}
//----------------------------------------------------------------------------
ImageExporterApp::~ImageExporterApp()
{
}
//----------------------------------------------------------------------------
void ImageExporterApp::OnIdle()
{
    m_Culler.ComputeUnculledSet(m_spScene);

    if( m_bOpenFile )
    {
        OpenFile(m_acFilename);
        m_bOpenFile = false;
    }

    AppRenderer->ClearBuffers();
    if( AppRenderer->BeginScene() )
    {
        m_spWireframe->Enabled = false;
        AppRenderer->DrawScene(m_Culler.GetVisibleSet());

        AppRenderer->EndScene();
    }
    AppRenderer->DisplayBackBuffer();
}
//----------------------------------------------------------------------------
void ImageExporterApp::CreateScene()
{
    m_spScene = SE_NEW Node;
    m_spWireframe = SE_NEW WireframeState;
    m_spWireframe->Enabled = false;
    m_spScene->AttachGlobalState(m_spWireframe);

	// 创建用于显示纹理图的矩形.
    Attributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetTCoordChannels(0, 2);
	VertexBuffer* pVB = SE_NEW VertexBuffer(tempAttr, 4);
	pVB->Position3(0) = Vector3f(-1, 1, 0);
	pVB->Position3(1) = Vector3f(1, 1, 0);
	pVB->Position3(2) = Vector3f(1, -1, 0);
	pVB->Position3(3) = Vector3f(-1, -1, 0);
	pVB->TCoord2(0, 0) = Vector2f(0, 0);
	pVB->TCoord2(0, 1) = Vector2f(1, 0);
	pVB->TCoord2(0, 2) = Vector2f(1, 1);
	pVB->TCoord2(0, 3) = Vector2f(0, 1);
	IndexBuffer* pIB = SE_NEW IndexBuffer(6);
	int* pIBData = pIB->GetData();
	*(pIBData    ) = 0;
	*(pIBData + 1) = 2;
	*(pIBData + 2) = 3;
	*(pIBData + 3) = 0;
	*(pIBData + 4) = 1;
	*(pIBData + 5) = 2;

	m_spMesh = SE_NEW TriMesh(pVB, pIB);
	m_spScene->AttachChild(m_spMesh);

    m_spScene->UpdateGS();
    m_spScene->UpdateRS();

    m_Culler.SetCamera(m_spCamera);
    m_Culler.ComputeUnculledSet(m_spScene);
}
//----------------------------------------------------------------------------
void ImageExporterApp::DestroyScene()
{
    m_spScene = 0;
    m_spMesh = 0;
    m_spWireframe = 0;
    m_spImage = 0;
}
//----------------------------------------------------------------------------
void ImageExporterApp::OnOpenFile(const char* acFilename)
{
    m_bOpenFile = true;
    Swing::System::SE_Strcpy(m_acFilename, 256, acFilename);
}
//----------------------------------------------------------------------------
void ImageExporterApp::OnSave(const char* acFilename)
{
    if( m_spImage )
    {
        m_spImage->Save(acFilename);
    }
}
//----------------------------------------------------------------------------
void ImageExporterApp::OpenFile(const char* acFilename)
{
    IDirect3DDevice9* pDXDevice = ((DX9Renderer*)AppRenderer)->GetDevice();
    ms_hResult = D3DXCreateTextureFromFile(pDXDevice, acFilename, &m_pDXTex);
    assert( SUCCEEDED(ms_hResult) );

    D3DSURFACE_DESC tempDesc;
    m_pDXTex->GetLevelDesc(0, &tempDesc);

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
    ms_hResult = m_pDXTex->LockRect(0, &tempLockRect, 0, 0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
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
    ms_hResult = m_pDXTex->UnlockRect(0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
    SE_DX9_SAFE_RELEASE(m_pDXTex);

    if( m_spImage )
    {
        ImageCatalog::GetActive()->Remove(m_spImage);
    }
    m_spImage = 0;
    m_spImage = SE_NEW Image((Image::FormatMode)eFormat, iWidth, iHeight, 
        aucDst, acFilename, true);
    m_spMesh->DetachAllEffects();
    m_spMesh->AttachEffect(SE_NEW TextureEffect(acFilename));
}
//----------------------------------------------------------------------------