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

#include "Distortion.h"
#include "SEDistortionEffect.h"

SE_WINDOW_APPLICATION(Distortion);
SE_REGISTER_INITIALIZE(Distortion);

//----------------------------------------------------------------------------
Distortion::Distortion()
    :
    SEWindowApplication3("Distortion", 0, 0, 640, 640, 
        SEColorRGBA(0.0f, 0.25f, 0.75f, 1.0f))
{
	m_pFrameBuffer = 0;
}
//----------------------------------------------------------------------------
bool Distortion::OnInitialize()
{
    if( !SEWindowApplication3::OnInitialize() )
    {
        return false;
    }

    // 创建camera.
    m_spCamera->SetFrustum(60.0f, 1.0f, 1.0f, 100.0f);
    SEVector3f tempCLoc(0.0f, 0.0f, -2.0f);
    SEVector3f tempCDir(0.0f, 0.0f, 1.0f);
    SEVector3f tempCUp(0.0f, 1.0f, 0.0f);
    SEVector3f tempCRight = tempCUp.Cross(tempCDir);
    m_spCamera->SetFrame(tempCLoc, tempCRight, tempCUp, tempCDir);

    CreateScene();

    m_spScene->UpdateGS();
    m_spScene->UpdateRS();

    m_Culler.SetCamera(m_spCamera);
    m_Culler.ComputeUnculledSet(m_spScene);

    InitializeCameraMotion(0.01f, 0.002f);
    InitializeObjectMotion(m_spScene);

    return true;
}
//----------------------------------------------------------------------------
void Distortion::OnTerminate()
{
    SEFrameBuffer::Destroy(m_pFrameBuffer);

    m_spScene = 0;
	m_spSceneMesh = 0;
	m_spDistortionMesh = 0;
    m_spWireframe = 0;
	m_spSceneImage = 0;

    SEWindowApplication3::OnTerminate();
}
//----------------------------------------------------------------------------
void Distortion::OnIdle()
{
    static double dCurTime = 0.0f;
    dCurTime = SESystem::SE_GetTime();
	float fScale = SEMathf::Sin(dCurTime);
	fScale = (fScale + 1.0f)*0.15f + 0.3f;
	m_spDistortionMesh->Local.SetUniformScale(fScale);
	m_spDistortionMesh->UpdateGS();

    MeasureTime();

    if( MoveCamera() )
    {
        m_Culler.ComputeUnculledSet(m_spScene);
    }

    if( MoveObject() )
    {
        m_spScene->UpdateGS();
        m_Culler.ComputeUnculledSet(m_spScene);
    }

    m_pRenderer->ClearBuffers();
    if( m_pRenderer->BeginScene() )
    {
        m_pFrameBuffer->Enable();
        m_pRenderer->SetClearColor(SEColorRGBA(0.5f, 0.5f, 0.5f, 1.0f));
        m_pRenderer->ClearBuffers();
        m_pRenderer->Draw(m_spSceneMesh);
        m_pFrameBuffer->Disable();

        // 把场景渲染到backbuffer.
        m_pRenderer->SetClearColor(SEColorRGBA(0.5f, 0.5f, 0.5f, 1.0f));
        m_pRenderer->ClearBuffers();
        m_pRenderer->DrawScene(m_Culler.GetVisibleSet());

        DrawFrameRate(8, 20, SEColorRGBA::SE_RGBA_WHITE);

        m_pRenderer->EndScene();
    }
    m_pRenderer->DisplayBackBuffer();

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool Distortion::OnKeyDown(unsigned char ucKey, int iX, int iY)
{
    if( SEWindowApplication3::OnKeyDown(ucKey, iX, iY) )
    {
        return true;
    }

    SEVector3f vec3fTrn;

    switch( ucKey )
    {
    case 'w':
    case 'W':
        m_spWireframe->Enabled = !m_spWireframe->Enabled;
        return true;

    case 's':
    case 'S':
        TestStreaming(m_spScene, 128, 128, 640, 480, "Distortion.seof");
        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
void Distortion::CreateScene()
{
    m_spScene = SE_NEW SENode;
    m_spWireframe = SE_NEW SEWireframeState;
    m_spScene->AttachGlobalState(m_spWireframe);

	CreateModels();

    int iWidth = m_iWidth, iHeight = m_iHeight;
    unsigned char* aucData = SE_NEW unsigned char[4*iWidth*iHeight];
    unsigned char* pucData = aucData;
    int i;
    for( i = 0; i < iWidth*iHeight; i++ )
    {
        *pucData++ = 0xFF;
        *pucData++ = 0xFF;
        *pucData++ = 0x00;
        *pucData++ = 0xFF;
    }
    m_spSceneImage = SE_NEW SEImage(SEImage::IT_RGBA8888, iWidth, iHeight, 
        aucData, "SceneImage");

    SEDistortionEffect* pEffect = SE_NEW SEDistortionEffect("SceneImage", "rocknormal");
    m_pSceneTarget = pEffect->GetPTexture(0, 0);
    m_pSceneTarget->SetOffscreenTexture(true);
    m_spDistortionMesh->AttachEffect(pEffect);
    m_pRenderer->LoadResources(m_spDistortionMesh);

    // 创建绑定到纹理的RGBA frame buffer.
    SETexture** apTargets = SE_NEW SETexture*[1];
    apTargets[0] = m_pSceneTarget;

    m_pFrameBuffer = SEFrameBuffer::Create(m_eFormat, m_eDepth, m_eStencil,
        m_eBuffering, m_eMultisampling, m_pRenderer, 1, apTargets);
    SE_ASSERT( m_pFrameBuffer );

    m_spScene->GetChild(0)->Local.SetTranslate(
        -m_spScene->WorldBound->GetCenter());
}
//----------------------------------------------------------------------------
void Distortion::CreateModels()
{
    // 创建一个场景中的矩形.
    SEAttributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetNormalChannels(3);
    tempAttr.SetColorChannels(0, 3);
    tempAttr.SetTCoordChannels(0, 2);

    SEVertexBuffer* pVBufferSM = SE_NEW SEVertexBuffer(tempAttr, 4);
    (*(SEVector3f*)pVBufferSM->PositionTuple(0)).X = -1.0f;
    (*(SEVector3f*)pVBufferSM->PositionTuple(0)).Y = -1.0f;
    (*(SEVector3f*)pVBufferSM->PositionTuple(0)).Z = 0.0f;
    pVBufferSM->Color3(0, 0) = SEColorRGB::SE_RGB_RED;
    (*(SEVector2f*)pVBufferSM->TCoordTuple(0, 0)).X = 0.0f;
    (*(SEVector2f*)pVBufferSM->TCoordTuple(0, 0)).Y = 1.0f;
    (*(SEVector3f*)pVBufferSM->PositionTuple(1)).X = 1.0f;
    (*(SEVector3f*)pVBufferSM->PositionTuple(1)).Y = -1.0f;
    (*(SEVector3f*)pVBufferSM->PositionTuple(1)).Z = 0.0f;
    pVBufferSM->Color3(0, 1) = SEColorRGB::SE_RGB_GREEN;
    (*(SEVector2f*)pVBufferSM->TCoordTuple(0, 1)).X = 1.0f;
    (*(SEVector2f*)pVBufferSM->TCoordTuple(0, 1)).Y = 1.0f;
    (*(SEVector3f*)pVBufferSM->PositionTuple(2)).X = 1.0f;
    (*(SEVector3f*)pVBufferSM->PositionTuple(2)).Y = 1.0f;
    (*(SEVector3f*)pVBufferSM->PositionTuple(2)).Z = 0.0f;
    pVBufferSM->Color3(0, 2) = SEColorRGB::SE_RGB_BLUE;
    (*(SEVector2f*)pVBufferSM->TCoordTuple(0, 2)).X = 1.0f;
    (*(SEVector2f*)pVBufferSM->TCoordTuple(0, 2)).Y = 0.0f;
    (*(SEVector3f*)pVBufferSM->PositionTuple(3)).X = -1.0f;
    (*(SEVector3f*)pVBufferSM->PositionTuple(3)).Y = 1.0f;
    (*(SEVector3f*)pVBufferSM->PositionTuple(3)).Z = 0.0f;
    pVBufferSM->Color3(0, 3) = SEColorRGB::SE_RGB_WHITE;
    (*(SEVector2f*)pVBufferSM->TCoordTuple(0, 3)).X = 0.0f;
    (*(SEVector2f*)pVBufferSM->TCoordTuple(0, 3)).Y = 0.0f;
    SEIndexBuffer* pIBufferSM = SE_NEW Swing::SEIndexBuffer(6);
    int* pIBufferDataSM = pIBufferSM->GetData();
    pIBufferDataSM[0] = 0;
    pIBufferDataSM[1] = 3;
    pIBufferDataSM[2] = 1;
    pIBufferDataSM[3] = 1;
    pIBufferDataSM[4] = 3;
    pIBufferDataSM[5] = 2;
    SETriMesh* pMesh = SE_NEW SETriMesh(pVBufferSM, pIBufferSM);
    pMesh->GenerateNormals();
    pMesh->GenerateTangents(0, 1, 2);

    SETextureEffect* pEffect = SE_NEW SETextureEffect("rock");
    pMesh->AttachEffect(pEffect);
	m_spScene->AttachChild(pMesh);
	m_spSceneMesh = pMesh;


    SEVertexBuffer* pVBufferSM2 = SE_NEW SEVertexBuffer(tempAttr, 4);
    (*(SEVector3f*)pVBufferSM2->PositionTuple(0)).X = -1.0f;
    (*(SEVector3f*)pVBufferSM2->PositionTuple(0)).Y = -1.0f;
    (*(SEVector3f*)pVBufferSM2->PositionTuple(0)).Z = 0.0f;
    pVBufferSM2->Color3(0, 0) = SEColorRGB::SE_RGB_RED;
    (*(SEVector2f*)pVBufferSM2->TCoordTuple(0, 0)).X = 0.0f;
    (*(SEVector2f*)pVBufferSM2->TCoordTuple(0, 0)).Y = 1.0f;
    (*(SEVector3f*)pVBufferSM2->PositionTuple(1)).X = 1.0f;
    (*(SEVector3f*)pVBufferSM2->PositionTuple(1)).Y = -1.0f;
    (*(SEVector3f*)pVBufferSM2->PositionTuple(1)).Z = 0.0f;
    pVBufferSM2->Color3(0, 1) = SEColorRGB::SE_RGB_GREEN;
    (*(SEVector2f*)pVBufferSM2->TCoordTuple(0, 1)).X = 1.0f;
    (*(SEVector2f*)pVBufferSM2->TCoordTuple(0, 1)).Y = 1.0f;
    (*(SEVector3f*)pVBufferSM2->PositionTuple(2)).X = 1.0f;
    (*(SEVector3f*)pVBufferSM2->PositionTuple(2)).Y = 1.0f;
    (*(SEVector3f*)pVBufferSM2->PositionTuple(2)).Z = 0.0f;
    pVBufferSM2->Color3(0, 2) = SEColorRGB::SE_RGB_BLUE;
    (*(SEVector2f*)pVBufferSM2->TCoordTuple(0, 2)).X = 1.0f;
    (*(SEVector2f*)pVBufferSM2->TCoordTuple(0, 2)).Y = 0.0f;
    (*(SEVector3f*)pVBufferSM2->PositionTuple(3)).X = -1.0f;
    (*(SEVector3f*)pVBufferSM2->PositionTuple(3)).Y = 1.0f;
    (*(SEVector3f*)pVBufferSM2->PositionTuple(3)).Z = 0.0f;
    pVBufferSM2->Color3(0, 3) = SEColorRGB::SE_RGB_WHITE;
    (*(SEVector2f*)pVBufferSM2->TCoordTuple(0, 3)).X = 0.0f;
    (*(SEVector2f*)pVBufferSM2->TCoordTuple(0, 3)).Y = 0.0f;
    SEIndexBuffer* pIBufferSM2 = SE_NEW Swing::SEIndexBuffer(6);
    int* pIBufferDataSM2 = pIBufferSM2->GetData();
    pIBufferDataSM2[0] = 0;
    pIBufferDataSM2[1] = 3;
    pIBufferDataSM2[2] = 1;
    pIBufferDataSM2[3] = 1;
    pIBufferDataSM2[4] = 3;
    pIBufferDataSM2[5] = 2;
	m_spDistortionMesh = SE_NEW SETriMesh(pVBufferSM2, pIBufferSM2);
	m_spDistortionMesh->Local.SetUniformScale(0.3f);
	m_spDistortionMesh->Local.SetTranslate(SEVector3f(0.0f, 0.0f, -0.5f));
	m_spScene->AttachChild(m_spDistortionMesh);
}
//----------------------------------------------------------------------------