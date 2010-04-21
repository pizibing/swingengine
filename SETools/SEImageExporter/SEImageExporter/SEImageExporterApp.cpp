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
#include "SEImageConverter.h"

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
    m_spScene = SE_NEW SENode;
    m_spWireframe = SE_NEW SEWireframeState;
    m_spWireframe->Enabled = false;
    m_spScene->AttachGlobalState(m_spWireframe);

	// 创建用于显示纹理图的矩形.
    SEAttributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetTCoordChannels(0, 2);
	SEVertexBuffer* pVB = SE_NEW SEVertexBuffer(tempAttr, 4);
	pVB->Position3(0) = SEVector3f(-1, 1, 0);
	pVB->Position3(1) = SEVector3f(1, 1, 0);
	pVB->Position3(2) = SEVector3f(1, -1, 0);
	pVB->Position3(3) = SEVector3f(-1, -1, 0);
	pVB->TCoord2(0, 0) = SEVector2f(0, 0);
	pVB->TCoord2(0, 1) = SEVector2f(1, 0);
	pVB->TCoord2(0, 2) = SEVector2f(1, 1);
	pVB->TCoord2(0, 3) = SEVector2f(0, 1);
	SEIndexBuffer* pIB = SE_NEW SEIndexBuffer(6);
	int* pIBData = pIB->GetData();
	*(pIBData    ) = 0;
	*(pIBData + 1) = 2;
	*(pIBData + 2) = 3;
	*(pIBData + 3) = 0;
	*(pIBData + 4) = 1;
	*(pIBData + 5) = 2;

	m_spMesh = SE_NEW SETriMesh(pVB, pIB);
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
    Swing::SESystem::SE_Strcpy(m_acFilename, 256, acFilename);
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
    IDirect3DDevice9* pDXDevice = ((SEDX9Renderer*)AppRenderer)->GetDevice();
    SEImageConverter* pConverter = SE_NEW SEImageConverter(pDXDevice);

    if( m_spImage )
    {
        SEImageCatalog::GetActive()->Remove(m_spImage);
    }
    m_spImage = 0;

    m_spImage = pConverter->CreateImageFromFile(acFilename);
    if( m_spImage )
    {
        SEImageCatalog::GetActive()->Insert(m_spImage);
    }

    SE_DELETE pConverter;

    m_spMesh->DetachAllEffects();
    m_spMesh->AttachEffect(SE_NEW SETextureEffect(acFilename));
}
//----------------------------------------------------------------------------