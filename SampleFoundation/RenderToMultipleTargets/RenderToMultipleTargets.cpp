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

#include "RenderToMultipleTargets.h"

SE_WINDOW_APPLICATION(RenderToMultipleTargets);

SE_REGISTER_INITIALIZE(RenderToMultipleTargets);

//----------------------------------------------------------------------------
RenderToMultipleTargets::RenderToMultipleTargets()
    :
    WindowApplication3("RenderToMultipleTargets", 0, 0, 1024, 768, 
        ColorRGBA(0.5f, 0.5f, 0.5f, 1.0f))
{
    m_pFrameBuffer = 0;
}
//----------------------------------------------------------------------------
bool RenderToMultipleTargets::OnInitialize()
{
    if( !WindowApplication3::OnInitialize() )
    {
        return false;
    }

    m_spCamera->SetFrustum(-0.55f, 0.55f, -0.4125f, 0.4125f, 1.0f, 1000.0f);
    Vector3f tempCLoc(0.0f, 0.0f, -3.0f);
    Vector3f tempCDir(0.0f, 0.0f, 1.0f);
    Vector3f tempCUp(0.0f, 1.0f, 0.0f);
    Vector3f tempCRight = tempCUp.Cross(tempCDir);
    m_spCamera->SetFrame(tempCLoc, tempCRight, tempCUp, tempCDir);

    CreateScene();

    m_spScene->UpdateGS();
    m_spScene->UpdateRS();

    m_Culler.SetCamera(m_spCamera);
    m_Culler.ComputeUnculledSet(m_spScene);

    InitializeCameraMotion(0.01f, 0.002f);
    InitializeObjectMotion(m_spScene);

    //m_pRenderer->ToggleFullscreen();

    return true;
}
//----------------------------------------------------------------------------
void RenderToMultipleTargets::OnTerminate()
{
    FrameBuffer::Destroy(m_pFrameBuffer);

    m_spScene = 0;
    m_spWireframe = 0;
    m_spScreenCamera = 0;
    m_spScenePolygon1 = 0;
    m_spScenePolygon2 = 0;
    m_spScenePolygon3 = 0;
    m_spSceneImage = 0;

    WindowApplication3::OnTerminate();
}
//----------------------------------------------------------------------------
void RenderToMultipleTargets::OnIdle()
{
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

    if( m_pRenderer->BeginScene() )
    {
        // 把场景并行渲染到多个render targets.
        m_pFrameBuffer->Enable();
        m_pRenderer->SetClearColor(ColorRGBA(0.5f, 0.5f, 0.5f, 1.0f));
        m_pRenderer->ClearBuffers();
        m_pRenderer->DrawScene(m_Culler.GetVisibleSet());
        //m_pFrameBuffer->CopyToTexture(0);
        //m_spSceneImage->Save("Target1.seif");
        //m_pFrameBuffer->CopyToTexture(1);
        //m_spSceneImage->Save("Target2.seif");
        //m_pFrameBuffer->CopyToTexture(2);
        //m_spSceneImage->Save("Target3.seif");
        m_pFrameBuffer->Disable();

        // 把场景渲染到backbuffer.
        m_pRenderer->SetClearColor(ColorRGBA(0.0f, 0.0f, 1.0f, 1.0f));
        m_pRenderer->ClearBuffers();
        m_pRenderer->DrawScene(m_Culler.GetVisibleSet());

        // 在窗口左下角渲染三个屏幕矩形,每个矩形用一个render target作纹理.
        m_pRenderer->SetCamera(m_spScreenCamera);
        m_pRenderer->Draw(m_spScenePolygon1);
        m_pRenderer->Draw(m_spScenePolygon2);
        m_pRenderer->Draw(m_spScenePolygon3);

        m_pRenderer->SetCamera(m_spCamera);
        m_pRenderer->Draw(8, GetHeight()-8, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 
            "Target1");
        m_pRenderer->Draw(212, GetHeight()-8, ColorRGBA(0.0f, 1.0f, 0.0f, 1.0f), 
            "Target2");
        m_pRenderer->Draw(418, GetHeight()-8, ColorRGBA(0.0f, 0.0f, 1.0f, 1.0f), 
            "Target3");
        DrawFrameRate(8, 20, ColorRGBA::SE_RGBA_WHITE);

        m_pRenderer->EndScene();
    }
    m_pRenderer->DisplayBackBuffer();

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool RenderToMultipleTargets::OnKeyDown(unsigned char ucKey, int iX, int iY)
{
    if( WindowApplication3::OnKeyDown(ucKey, iX, iY) )
    {
        return true;
    }

    switch( ucKey )
    {
    case 'w':
    case 'W':
        m_spWireframe->Enabled = !m_spWireframe->Enabled;
        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
void RenderToMultipleTargets::CreateScene()
{
    // screen camera把[0, 1]^3区间上的(x, y, z)映射到[-1, 1]^2 x [0, 1]区间上
    // 的(x', y, 'z').
    m_spScreenCamera = SE_NEW Camera;
    m_spScreenCamera->Perspective = false;
    m_spScreenCamera->SetFrustum(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    m_spScreenCamera->SetFrame(Vector3f::ZERO, Vector3f::UNIT_X, 
        Vector3f::UNIT_Y, Vector3f::UNIT_Z);

    // 创建场景根节点.
    m_spScene = SE_NEW Node;
    m_spWireframe = SE_NEW WireframeState;
    m_spScene->AttachGlobalState(m_spWireframe);

    // 创建三个使用RGBA渲染目标纹理的屏幕矩形..
    Attributes tempAttrScenePoly;
    tempAttrScenePoly.SetPositionChannels(3);
    tempAttrScenePoly.SetTCoordChannels(0, 2);

    float fExtend = 0.2f, fOffset = 0.002f;
    VertexBuffer* pVBufferScenePoly = SE_NEW VertexBuffer(tempAttrScenePoly, 4);
    pVBufferScenePoly->Position3(0) = Vector3f(0.0f, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(1) = Vector3f(fExtend, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(2) = Vector3f(fExtend, fExtend, 0.0f);
    pVBufferScenePoly->Position3(3) = Vector3f(0.0f, fExtend, 0.0f);
    pVBufferScenePoly->TCoord2(0,0) = Vector2f(0.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0,1) = Vector2f(1.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0,2) = Vector2f(1.0f, 0.0f);
    pVBufferScenePoly->TCoord2(0,3) = Vector2f(0.0f, 0.0f);
    // 创建三个矩形共享的index buffer.
    IndexBuffer* pIBufferScenePoly = SE_NEW IndexBuffer(6);
    int* pIBufferDataScenePoly = pIBufferScenePoly->GetData();
    pIBufferDataScenePoly[0] = 0;  
    pIBufferDataScenePoly[1] = 3;  
    pIBufferDataScenePoly[2] = 1;
    pIBufferDataScenePoly[3] = 1;  
    pIBufferDataScenePoly[4] = 3;  
    pIBufferDataScenePoly[5] = 2;
    m_spScenePolygon1 = SE_NEW TriMesh(pVBufferScenePoly, pIBufferScenePoly);

    pVBufferScenePoly = SE_NEW VertexBuffer(tempAttrScenePoly, 4);
    pVBufferScenePoly->Position3(0) = Vector3f(fExtend + 
        fOffset, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(1) = Vector3f(fExtend + fExtend + 
        fOffset, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(2) = Vector3f(fExtend + fExtend + 
        fOffset, fExtend, 0.0f);
    pVBufferScenePoly->Position3(3) = Vector3f(fExtend + fOffset, 
        fExtend, 0.0f);
    pVBufferScenePoly->TCoord2(0,0) = Vector2f(0.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0,1) = Vector2f(1.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0,2) = Vector2f(1.0f, 0.0f);
    pVBufferScenePoly->TCoord2(0,3) = Vector2f(0.0f, 0.0f);
    m_spScenePolygon2 = SE_NEW TriMesh(pVBufferScenePoly, pIBufferScenePoly);

    pVBufferScenePoly = SE_NEW VertexBuffer(tempAttrScenePoly, 4);
    pVBufferScenePoly->Position3(0) = Vector3f(fExtend + fExtend + 
        2.0f*fOffset, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(1) = Vector3f(fExtend + fExtend + 
        fExtend + 2.0f*fOffset, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(2) = Vector3f(fExtend + fExtend + 
        fExtend + 2.0f*fOffset, fExtend, 0.0f);
    pVBufferScenePoly->Position3(3) = Vector3f(fExtend + fExtend + 
        2.0f*fOffset, fExtend, 0.0f);
    pVBufferScenePoly->TCoord2(0,0) = Vector2f(0.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0,1) = Vector2f(1.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0,2) = Vector2f(1.0f, 0.0f);
    pVBufferScenePoly->TCoord2(0,3) = Vector2f(0.0f, 0.0f);
    m_spScenePolygon3 = SE_NEW TriMesh(pVBufferScenePoly, pIBufferScenePoly);

    // 三个矩形共享的image.
    int iWidth = 1024, iHeight = 768;
    unsigned char* aucData = SE_NEW unsigned char[4*iWidth*iHeight];
    unsigned char* pucData = aucData;
    int i;
    for( i = 0; i < iWidth*iHeight; i++ )
    {
        *pucData++ = 0xFF;
        *pucData++ = 0x00;
        *pucData++ = 0x00;
        *pucData++ = 0xFF;
    }
    m_spSceneImage = SE_NEW Image(Image::IT_RGBA8888, iWidth, iHeight, 
        aucData, "SceneImage");

    TextureEffect* pEffectScenePoly = SE_NEW TextureEffect("SceneImage");
    m_pSceneTarget1 = pEffectScenePoly->GetPTexture(0, 0);
    m_pSceneTarget1->SetOffscreenTexture(true);
    m_spScenePolygon1->AttachEffect(pEffectScenePoly);
    m_spScenePolygon1->UpdateGS();
    m_spScenePolygon1->UpdateRS();
    m_pRenderer->LoadResources(m_spScenePolygon1);

    pEffectScenePoly = SE_NEW TextureEffect("SceneImage");
    m_pSceneTarget2 = pEffectScenePoly->GetPTexture(0, 0);
    m_pSceneTarget2->SetOffscreenTexture(true);
    m_spScenePolygon2->AttachEffect(pEffectScenePoly);
    m_spScenePolygon2->UpdateGS();
    m_spScenePolygon2->UpdateRS();
    m_pRenderer->LoadResources(m_spScenePolygon2);

    pEffectScenePoly = SE_NEW TextureEffect("SceneImage");
    m_pSceneTarget3 = pEffectScenePoly->GetPTexture(0, 0);
    m_pSceneTarget3->SetOffscreenTexture(true);
    m_spScenePolygon3->AttachEffect(pEffectScenePoly);
    m_spScenePolygon3->UpdateGS();
    m_spScenePolygon3->UpdateRS();
    m_pRenderer->LoadResources(m_spScenePolygon3);

    // 创建绑定到纹理的RGBA frame buffer.
    Texture** apTargets = SE_NEW Texture*[3];
    apTargets[0] = m_pSceneTarget1;
    apTargets[1] = m_pSceneTarget2;
    apTargets[2] = m_pSceneTarget3;
    m_pFrameBuffer = FrameBuffer::Create(m_eFormat, m_eDepth, m_eStencil,
        m_eBuffering, m_eMultisampling, m_pRenderer, 3, apTargets);
    SE_ASSERT( m_pFrameBuffer );

    m_spScene->AttachChild(CreateModel());
    m_spScene->UpdateGS();
    m_spScene->GetChild(0)->Local.SetTranslate(
        -m_spScene->WorldBound->GetCenter());
}
//----------------------------------------------------------------------------
Node* RenderToMultipleTargets::CreateModel()
{
    // 创建一个场景中的矩形.
    Attributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetNormalChannels(3);
    tempAttr.SetColorChannels(0, 3);
    tempAttr.SetTCoordChannels(0, 2);

    VertexBuffer* pVBufferSM = SE_NEW VertexBuffer(tempAttr, 4);
    (*(Vector3f*)pVBufferSM->PositionTuple(0)).X = -1.0f;
    (*(Vector3f*)pVBufferSM->PositionTuple(0)).Y = -1.0f;
    (*(Vector3f*)pVBufferSM->PositionTuple(0)).Z = 0.0f;
    pVBufferSM->Color3(0, 0) = ColorRGB::SE_RGB_RED;
    (*(Vector2f*)pVBufferSM->TCoordTuple(0, 0)).X = 0.0f;
    (*(Vector2f*)pVBufferSM->TCoordTuple(0, 0)).Y = 1.0f;
    (*(Vector3f*)pVBufferSM->PositionTuple(1)).X = 1.0f;
    (*(Vector3f*)pVBufferSM->PositionTuple(1)).Y = -1.0f;
    (*(Vector3f*)pVBufferSM->PositionTuple(1)).Z = 0.0f;
    pVBufferSM->Color3(0, 1) = ColorRGB::SE_RGB_GREEN;
    (*(Vector2f*)pVBufferSM->TCoordTuple(0, 1)).X = 1.0f;
    (*(Vector2f*)pVBufferSM->TCoordTuple(0, 1)).Y = 1.0f;
    (*(Vector3f*)pVBufferSM->PositionTuple(2)).X = 1.0f;
    (*(Vector3f*)pVBufferSM->PositionTuple(2)).Y = 1.0f;
    (*(Vector3f*)pVBufferSM->PositionTuple(2)).Z = 0.0f;
    pVBufferSM->Color3(0, 2) = ColorRGB::SE_RGB_BLUE;
    (*(Vector2f*)pVBufferSM->TCoordTuple(0, 2)).X = 1.0f;
    (*(Vector2f*)pVBufferSM->TCoordTuple(0, 2)).Y = 0.0f;
    (*(Vector3f*)pVBufferSM->PositionTuple(3)).X = -1.0f;
    (*(Vector3f*)pVBufferSM->PositionTuple(3)).Y = 1.0f;
    (*(Vector3f*)pVBufferSM->PositionTuple(3)).Z = 0.0f;
    pVBufferSM->Color3(0, 3) = ColorRGB::SE_RGB_WHITE;
    (*(Vector2f*)pVBufferSM->TCoordTuple(0, 3)).X = 0.0f;
    (*(Vector2f*)pVBufferSM->TCoordTuple(0, 3)).Y = 0.0f;
    IndexBuffer* pIBufferSM = SE_NEW Swing::IndexBuffer(6);
    int* pIBufferDataSM = pIBufferSM->GetData();
    pIBufferDataSM[0] = 0;
    pIBufferDataSM[1] = 3;
    pIBufferDataSM[2] = 1;
    pIBufferDataSM[3] = 1;
    pIBufferDataSM[4] = 3;
    pIBufferDataSM[5] = 2;
    TriMesh* pMesh = SE_NEW TriMesh(pVBufferSM, pIBufferSM);
    pMesh->GenerateNormals();
    pMesh->GenerateTangents(0, 1, 2);

    DefaultMRT3Effect* pEffect = SE_NEW DefaultMRT3Effect("kate");
    pMesh->AttachEffect(pEffect);

    return (Node*)pMesh;
}
//----------------------------------------------------------------------------
