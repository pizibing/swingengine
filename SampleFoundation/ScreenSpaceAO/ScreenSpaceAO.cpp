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

#include "ScreenSpaceAO.h"

SE_WINDOW_APPLICATION(ScreenSpaceAO);

SE_REGISTER_INITIALIZE(ScreenSpaceAO);

//----------------------------------------------------------------------------
ScreenSpaceAO::ScreenSpaceAO()
    :
    WindowApplication3("ScreenSpaceAO", 0, 0, 800, 600, 
        ColorRGBA(0.5f, 0.5f, 0.5f, 1.0f))
{
    m_pFrameBufferSceneMRT = 0;

    m_bShowSSAO = false;
    m_bShowSSAOBlurred = false;
    m_bShowCombined = false;
    m_bShowUnCombined = true;
}
//----------------------------------------------------------------------------
bool ScreenSpaceAO::OnInitialize()
{
    if( !WindowApplication3::OnInitialize() )
    {
        return false;
    }

    m_spCamera->SetFrustum(-0.55f, 0.55f, -0.4125f, 0.4125f, 1.0f, 1000.0f);
    Vector3f tempCLoc(0.0f, 9.0f, -20.0f);
    Vector3f tempCDir(0.0f, -0.5f, 1.0f);
    tempCDir.Normalize();
    Vector3f tempCUp(0.0f, 1.0f, 0.0f);
    Vector3f tempCRight = tempCUp.Cross(tempCDir);
    tempCRight.Normalize();
    tempCUp = tempCDir.Cross(tempCRight);
    tempCUp.Normalize();
    m_spCamera->SetFrame(tempCLoc, tempCRight, tempCUp, tempCDir);

    CreateScene();

    m_spScene->UpdateGS();
    m_spScene->UpdateRS();

    m_Culler.SetCamera(m_spCamera);
    m_Culler.ComputeUnculledSet(m_spScene);

    InitializeCameraMotion(0.5f, 0.01f);
    InitializeObjectMotion(m_spScene);

    return true;
}
//----------------------------------------------------------------------------
void ScreenSpaceAO::OnTerminate()
{
    FrameBuffer::Destroy(m_pFrameBufferSceneMRT);
    FrameBuffer::Destroy(m_pFrameBufferSSAO);

    m_spScene = 0;
    m_spWireframe = 0;

    m_spScenePolygon1 = 0;
    m_spScenePolygon2 = 0;
    m_spScenePolygon3 = 0;
    m_spScenePolygon4 = 0;
    m_spScenePolygon5 = 0;
    m_spScenePolygon6 = 0;

    m_spSceneImageColor = 0;
    m_spSceneImageNormal = 0;
    m_spSceneImageDepth = 0;
    m_spSSAORandomImage = 0;

    m_spSceneTargetColor = 0;
    m_spSceneTargetNormal = 0;
    m_spSceneTargetDepth = 0;

    m_spSSAORandom = 0;
    m_spSceneImageSSAO = 0;
    m_spSceneTargetSSAO = 0;

    m_aspLight[0] = 0;
    m_aspLight[1] = 0;
    m_aspLight[2] = 0;
    m_aspLight[3] = 0;

    WindowApplication3::OnTerminate();
    // For safty reason.
    m_spScreenCamera = 0;
}
//----------------------------------------------------------------------------
void ScreenSpaceAO::OnIdle()
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
        if( m_bShowUnCombined )
        {
            // Render the scene to back buffer directly.
            m_pRenderer->SetClearColor(ColorRGBA(0.5f, 0.5f, 0.5f, 1.0f));
            m_pRenderer->ClearBuffers();
            m_pRenderer->DrawScene(m_Culler.GetVisibleSet());
        }
        else
        {
            // First, clear back buffer.
            m_pRenderer->ClearBuffers();

            // Render the scene to multiple render targets.
            m_pFrameBufferSceneMRT->Enable();
            m_pRenderer->SetClearColor(ColorRGBA(0.5f, 0.5f, 0.5f, 1.0f));
            m_pRenderer->ClearBuffers();  // Clear MRT.
            m_pRenderer->DrawScene(m_Culler.GetVisibleSet());
            m_pFrameBufferSceneMRT->Disable();

            // SSAO target.
            m_pRenderer->SetCamera(m_spScreenCamera);
            if( !m_bShowSSAO )
            {
                // Render the SSAO scene to SSAO render target.
                m_pFrameBufferSSAO->Enable();
                m_pRenderer->ClearBuffers();
                m_pRenderer->Draw(m_spScenePolygon4);
                m_pFrameBufferSSAO->Disable();
            }
            else
            {
                // Render the SSAO scene to back buffer.
                m_pRenderer->Draw(m_spScenePolygon4);
            }

            // SSAO target blurred.
            if( !m_bShowSSAOBlurred )
            {
                m_pFrameBufferSSAO->Enable();
                m_pRenderer->Draw(m_spScenePolygon5);
                m_pFrameBufferSSAO->Disable();
            }
            else
            {
                m_pRenderer->Draw(m_spScenePolygon5);
            }

            if( m_bShowCombined )
            {
                m_pRenderer->Draw(m_spScenePolygon6);
            }

            // Render three screen polygons to show the MRT(color/normal/
            // depth).
            m_pRenderer->SetCamera(m_spScreenCamera);
            m_pRenderer->Draw(m_spScenePolygon1);
            m_pRenderer->Draw(m_spScenePolygon2);
            m_pRenderer->Draw(m_spScenePolygon3);
        }

        m_pRenderer->SetCamera(m_spCamera);
        DrawFrameRate(8, 20, ColorRGBA::SE_RGBA_WHITE);

        m_pRenderer->EndScene();
    }
    m_pRenderer->DisplayBackBuffer();

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool ScreenSpaceAO::OnKeyDown(unsigned char ucKey, int iX, int iY)
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

#if defined(SE_USE_DX10)
        // DX10 render state objects must be re-created based on our new states.
        m_spScene->UpdateRS();
#endif
        return true;

    case '1':
        m_bShowSSAO = true;
        m_bShowSSAOBlurred = false;
        m_bShowCombined = false;
        m_bShowUnCombined = false;
        return true;

    case '2':
        m_bShowSSAO = false;
        m_bShowSSAOBlurred = true;
        m_bShowCombined = false;
        m_bShowUnCombined = false;
        return true;

    case '3':
        m_bShowSSAO = false;
        m_bShowSSAOBlurred = false;
        m_bShowCombined = true;
        m_bShowUnCombined = false;
        return true;

    case '4':
        m_bShowSSAO = false;
        m_bShowSSAOBlurred = false;
        m_bShowCombined = false;
        m_bShowUnCombined = true;
        return true;

    case 's':
    case 'S':
        TestStreaming(m_spScene, 128, 128, 640, 480, "ScreenSpaceAO.seof");
        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
void ScreenSpaceAO::CreateScene()
{
    int iWidth = m_iWidth;
    int iHeight = m_iHeight;

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
    pVBufferScenePoly->TCoord2(0, 0) = Vector2f(0.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0, 1) = Vector2f(1.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0, 2) = Vector2f(1.0f, 0.0f);
    pVBufferScenePoly->TCoord2(0, 3) = Vector2f(0.0f, 0.0f);

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
    pVBufferScenePoly->TCoord2(0, 0) = Vector2f(0.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0, 1) = Vector2f(1.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0, 2) = Vector2f(1.0f, 0.0f);
    pVBufferScenePoly->TCoord2(0, 3) = Vector2f(0.0f, 0.0f);
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
    pVBufferScenePoly->TCoord2(0, 0) = Vector2f(0.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0, 1) = Vector2f(1.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0, 2) = Vector2f(1.0f, 0.0f);
    pVBufferScenePoly->TCoord2(0, 3) = Vector2f(0.0f, 0.0f);
    m_spScenePolygon3 = SE_NEW TriMesh(pVBufferScenePoly, pIBufferScenePoly);

    float fExtend2 = 1.0f;
    pVBufferScenePoly = SE_NEW VertexBuffer(tempAttrScenePoly, 4);
    pVBufferScenePoly->Position3(0) = Vector3f(0.0f, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(1) = Vector3f(fExtend2, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(2) = Vector3f(fExtend2, fExtend2, 0.0f);
    pVBufferScenePoly->Position3(3) = Vector3f(0.0f, fExtend2, 0.0f);
    pVBufferScenePoly->TCoord2(0,0) = Vector2f(0.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0,1) = Vector2f(1.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0,2) = Vector2f(1.0f, 0.0f);
    pVBufferScenePoly->TCoord2(0,3) = Vector2f(0.0f, 0.0f);
    m_spScenePolygon4 = SE_NEW TriMesh(pVBufferScenePoly, pIBufferScenePoly);

    pVBufferScenePoly = SE_NEW VertexBuffer(tempAttrScenePoly, 4);
    pVBufferScenePoly->Position3(0) = Vector3f(0.0f, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(1) = Vector3f(fExtend2, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(2) = Vector3f(fExtend2, fExtend2, 0.0f);
    pVBufferScenePoly->Position3(3) = Vector3f(0.0f, fExtend2, 0.0f);
    pVBufferScenePoly->TCoord2(0, 0) = Vector2f(0.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0, 1) = Vector2f(1.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0, 2) = Vector2f(1.0f, 0.0f);
    pVBufferScenePoly->TCoord2(0, 3) = Vector2f(0.0f, 0.0f);
    m_spScenePolygon5 = SE_NEW TriMesh(pVBufferScenePoly, pIBufferScenePoly);

    tempAttrScenePoly.SetTCoordChannels(1, 2);
    pVBufferScenePoly = SE_NEW VertexBuffer(tempAttrScenePoly, 4);
    pVBufferScenePoly->Position3(0) = Vector3f(0.0f, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(1) = Vector3f(fExtend2, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(2) = Vector3f(fExtend2, fExtend2, 0.0f);
    pVBufferScenePoly->Position3(3) = Vector3f(0.0f, fExtend2, 0.0f);
    pVBufferScenePoly->TCoord2(0, 0) = Vector2f(0.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0, 1) = Vector2f(1.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0, 2) = Vector2f(1.0f, 0.0f);
    pVBufferScenePoly->TCoord2(0, 3) = Vector2f(0.0f, 0.0f);
    pVBufferScenePoly->TCoord2(1, 0) = Vector2f(0.0f, 1.0f);
    pVBufferScenePoly->TCoord2(1, 1) = Vector2f(1.0f, 1.0f);
    pVBufferScenePoly->TCoord2(1, 2) = Vector2f(1.0f, 0.0f);
    pVBufferScenePoly->TCoord2(1, 3) = Vector2f(0.0f, 0.0f);
    m_spScenePolygon6 = SE_NEW TriMesh(pVBufferScenePoly, pIBufferScenePoly);

    // Color target.
    m_spSceneImageColor = Image::GenerateColorImage(Image::IT_RGBA8888, 
        iWidth, iHeight, ColorRGBA::SE_RGBA_RED, "SceneImageColor");
    TextureEffect* pEffectScenePoly = SE_NEW TextureEffect("SceneImageColor");
    m_spSceneTargetColor = pEffectScenePoly->GetPTexture(0, 0);
    m_spSceneTargetColor->SetImage(m_spSceneImageColor);
    m_spSceneTargetColor->SetOffscreenTexture(true);
    m_spScenePolygon1->AttachEffect(pEffectScenePoly);
    m_spScenePolygon1->UpdateGS();
    m_spScenePolygon1->UpdateRS();

    // Normal target.
    m_spSceneImageNormal = Image::GenerateColorImage(Image::IT_RGBA8888, 
        iWidth, iHeight, ColorRGBA::SE_RGBA_RED, "SceneImageNormal");
    pEffectScenePoly = SE_NEW TextureEffect("SceneImageNormal");
    m_spSceneTargetNormal = pEffectScenePoly->GetPTexture(0, 0);
    m_spSceneTargetNormal->SetImage(m_spSceneImageNormal);
    m_spSceneTargetNormal->SetOffscreenTexture(true);
    m_spScenePolygon2->AttachEffect(pEffectScenePoly);
    m_spScenePolygon2->UpdateGS();
    m_spScenePolygon2->UpdateRS();

    // Depth target.
    m_spSceneImageDepth = Image::GenerateColorImage(Image::IT_R32, 
        iWidth, iHeight, ColorRGBA::SE_RGBA_RED, "SceneImageDepth");
    pEffectScenePoly = SE_NEW TextureEffect("SceneImageDepth");
    m_spSceneTargetDepth = pEffectScenePoly->GetPTexture(0, 0);
    m_spSceneTargetDepth->SetImage(m_spSceneImageDepth);
    m_spSceneTargetDepth->SetOffscreenTexture(true);
    m_spScenePolygon3->AttachEffect(pEffectScenePoly);
    m_spScenePolygon3->UpdateGS();
    m_spScenePolygon3->UpdateRS();

    // Create the MRT(color/normal/depth).
    Texture** apTargets = SE_NEW Texture*[3];
    apTargets[0] = m_spSceneTargetColor;
    apTargets[1] = m_spSceneTargetNormal;
    apTargets[2] = m_spSceneTargetDepth;
    m_pRenderer->LoadTexture(m_spSceneTargetColor);
    m_pRenderer->LoadTexture(m_spSceneTargetNormal);
    m_pRenderer->LoadTexture(m_spSceneTargetDepth);
    m_pFrameBufferSceneMRT = FrameBuffer::Create(m_eFormat, m_eDepth, m_eStencil,
        m_eBuffering, m_eMultisampling, m_pRenderer, 3, apTargets);
    SE_ASSERT( m_pFrameBufferSceneMRT );

    // Create SSAO's random texture.
    m_spSSAORandomImage = Image::GenerateRandomImage(Image::IT_RGBA8888, 
        4, 4, 100, "SSAORandom");
    m_spSSAORandom = SE_NEW Texture(m_spSSAORandomImage);
    m_spSSAORandom->SetFilterType(Texture::NEAREST);
    m_spSSAORandom->SetWrapType(0, Texture::REPEAT);
    m_spSSAORandom->SetWrapType(1, Texture::REPEAT);
    ScreenSpaceAOEffect* pSSAOEffect = SE_NEW ScreenSpaceAOEffect(
        "SSAORandom", "SceneImageDepth");
    pSSAOEffect->SetPTexture(0, 0, m_spSSAORandom);
    pSSAOEffect->SetPTexture(0, 1, m_spSceneTargetDepth);
    m_spScenePolygon4->AttachEffect(pSSAOEffect);
    m_spScenePolygon4->UpdateGS();
    m_spScenePolygon4->UpdateRS();

    m_pSSAOEffect = pSSAOEffect;
    m_pSSAOEffect->ScreenSize.X = (float)iWidth;
    m_pSSAOEffect->ScreenSize.Y = (float)iHeight;
    m_pSSAOEffect->FarClipDist = m_spCamera->GetDMax();

    // SSAO's image.
    m_spSceneImageSSAO = Image::GenerateColorImage(Image::IT_RGBA8888, 
        iWidth, iHeight, ColorRGBA::SE_RGBA_RED, "SceneImageSSAO");
    // SSAO's render target texture.
    m_spSceneTargetSSAO = SE_NEW Texture(m_spSceneImageSSAO);
    m_spSceneTargetSSAO->SetFilterType(Texture::LINEAR);
    m_spSceneTargetSSAO->SetOffscreenTexture(true);

    // This screen polygon will be used to blur the original SSAO target.
    ScreenSpaceAOBlurEffect* pEffectSSAOBlur = 
        SE_NEW ScreenSpaceAOBlurEffect("SceneImageSSAO");
    ScreenSpaceAOBlurEffect::GenerateTexelKernel(iWidth, iHeight);
    pEffectSSAOBlur->SetPTexture(0, 0, m_spSceneTargetSSAO);
    m_spScenePolygon5->AttachEffect(pEffectSSAOBlur);
    m_spScenePolygon5->UpdateGS();
    m_spScenePolygon5->UpdateRS();

    // Create SSAO's frame buffer.
    apTargets = SE_NEW Texture*[1];
    apTargets[0] = m_spSceneTargetSSAO;
    m_pRenderer->LoadTexture(m_spSceneTargetSSAO);
    m_pFrameBufferSSAO = FrameBuffer::Create(m_eFormat, m_eDepth, m_eStencil,
        m_eBuffering, m_eMultisampling, m_pRenderer, 1, apTargets);
    SE_ASSERT( m_pFrameBufferSSAO );

    CombineEffect* pEffectCombine = SE_NEW CombineEffect("SceneImageColor", 
        "SceneImageSSAO");
    pEffectCombine->SetPTexture(0, 0, m_spSceneTargetColor);
    pEffectCombine->SetPTexture(0, 1, m_spSceneTargetSSAO);
    m_spScenePolygon6->AttachEffect(pEffectCombine);
    m_spScenePolygon6->UpdateGS();
    m_spScenePolygon6->UpdateRS();

    m_spScene->AttachChild(CreateModel());
    CreateLights();

    m_spScene->UpdateGS();
    m_spScene->UpdateRS();
    m_spScene->GetChild(0)->Local.SetTranslate(
        -m_spScene->WorldBound->GetCenter());
}
//----------------------------------------------------------------------------
Node* ScreenSpaceAO::CreateModel()
{
    // polished gold.
    MaterialState* pGoldMaterial = SE_NEW MaterialState;
    pGoldMaterial->Ambient = ColorRGB(0.24725f, 0.2245f, 0.0645f);
    pGoldMaterial->Diffuse = ColorRGB(0.34615f, 0.3143f, 0.0903f);
    pGoldMaterial->Specular = ColorRGB(0.797357f, 0.723991f, 0.208006f);
    pGoldMaterial->Shininess = 83.2f;

    // polished red.
    MaterialState* pRedMaterial = SE_NEW MaterialState;
    pRedMaterial->Ambient = ColorRGB(0.2f, 0.0f, 0.0f);
    pRedMaterial->Diffuse = ColorRGB(0.2f, 0.0f, 0.0f);
    pRedMaterial->Specular = ColorRGB(1.0f, 1.0f, 1.0f);
    pRedMaterial->Shininess = 50.0f;

    // polished blue.
    MaterialState* pBlueMaterial = SE_NEW MaterialState;
    pBlueMaterial->Ambient = ColorRGB(0.0f, 0.0f, 0.2f);
    pBlueMaterial->Diffuse = ColorRGB(0.0f, 0.0f, 0.8f);
    pBlueMaterial->Specular = ColorRGB(1.0f, 1.0f, 1.0f);
    pBlueMaterial->Shininess = 83.2f;

    // polished white.
    MaterialState* pWhiteMaterial = SE_NEW MaterialState;
    pWhiteMaterial->Ambient = ColorRGB(0.2f, 0.2f, 0.2f);
    pWhiteMaterial->Diffuse = ColorRGB(0.8f, 0.8f, 0.8f);
    pWhiteMaterial->Specular = ColorRGB(1.0f, 1.0f, 1.0f);
    pWhiteMaterial->Shininess = 100.0f;

    // polished green.
    MaterialState* pGreenMaterial = SE_NEW MaterialState;
    pGreenMaterial->Ambient = ColorRGB(0.0f, 0.2f, 0.0f);
    pGreenMaterial->Diffuse = ColorRGB(0.0f, 0.1f, 0.0f);
    pGreenMaterial->Specular = ColorRGB(1.0f, 1.0f, 1.0f);
    pGreenMaterial->Shininess = 50.0f;

    // polished copper.
    MaterialState* pCopperMaterial = SE_NEW MaterialState;
    pCopperMaterial->Ambient = ColorRGB(0.2295f, 0.08825f, 0.0275f);
    pCopperMaterial->Diffuse = ColorRGB(0.5508f, 0.2118f, 0.066f);
    pCopperMaterial->Specular = ColorRGB(0.580594f, 0.223257f, 0.0695701f);
    pCopperMaterial->Shininess = 51.2f;

    // flat egg.
    MaterialState* pEggMaterial = SE_NEW MaterialState;
    pEggMaterial->Ambient = ColorRGB(0.0f, 0.0f, 0.0f);
    pEggMaterial->Diffuse = ColorRGB(1.0f, 0.92f, 0.804f);
    pEggMaterial->Specular = ColorRGB(0.0f, 0.0f, 0.0f);
    pEggMaterial->Shininess = 0.0f;

    // We apply this texture effect as a post-lighting effect,
    // so the src output fragments should be modulated with dst buffer pixels.
    TextureEffect* pTextureWoodEffect = SE_NEW TextureEffect("wood512");
    AlphaState* pAState = pTextureWoodEffect->GetBlending(0);
    pAState->SrcBlend = AlphaState::SBF_DST_COLOR;
    pAState->DstBlend = AlphaState::DBF_ZERO;

    // We apply this bump map effect as a lighting effect,
    // When UpdateRS is called, geometry object's default lighting effect will
    // be replaced by the bump map effect.
    BumpMapL1Effect* pBumpMapRockEffect = SE_NEW BumpMapL1Effect("rock",
        "rocknormal");

    Node* pRoot = SE_NEW Node;

    Attributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetNormalChannels(3);
    tempAttr.SetTCoordChannels(0, 2);

    float fExtend = 8.0f;
    StandardMesh tempSM(tempAttr);

    // floor.
    TriMesh* pMesh = tempSM.Rectangle(2, 2, fExtend, fExtend);
    pMesh->AttachGlobalState(pWhiteMaterial);
    pMesh->AttachEffect(pTextureWoodEffect);
    pMesh->GenerateNormals();
    pMesh->GenerateTangents(0, 1, 2);
    Matrix3f mat3fRot;
    mat3fRot.FromEulerAnglesXYZ(Mathf::PI/2.0f, 0.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pRoot->AttachChild(pMesh);

    // far wall.
    pMesh = SE_NEW TriMesh(pMesh->VBuffer, pMesh->IBuffer);
    pMesh->LightingMode = Geometry::GLM_USER;
    pMesh->AttachGlobalState(pWhiteMaterial);
    pMesh->AttachEffect(pBumpMapRockEffect);
    pMesh->Local.SetTranslate(Vector3f(0.0f, fExtend, fExtend));
    pRoot->AttachChild(pMesh);

    // left wall.
    pMesh = SE_NEW TriMesh(pMesh->VBuffer, pMesh->IBuffer);
    pMesh->LightingMode = Geometry::GLM_USER;
    pMesh->AttachGlobalState(pWhiteMaterial);
    pMesh->AttachEffect(pBumpMapRockEffect);
    mat3fRot.FromEulerAnglesXYZ(0.0f, -Mathf::PI/2.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(Vector3f(-fExtend, fExtend, 0.0f));
    pRoot->AttachChild(pMesh);

    // right wall.
    pMesh = SE_NEW TriMesh(pMesh->VBuffer, pMesh->IBuffer);
    pMesh->LightingMode = Geometry::GLM_USER;
    pMesh->AttachGlobalState(pWhiteMaterial);
    pMesh->AttachEffect(pBumpMapRockEffect);
    mat3fRot.FromEulerAnglesXYZ(0.0f, Mathf::PI/2.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(Vector3f(fExtend, fExtend, 0.0f));
    pRoot->AttachChild(pMesh);

    // sphere.
    pMesh = tempSM.Sphere(32, 32, 1.0f);
    pMesh->AttachGlobalState(pGoldMaterial);
    pMesh->GenerateNormals();
    pMesh->Local.SetTranslate(Vector3f(0.0f, 1.0f, 0.0f));
    pRoot->AttachChild(pMesh);

    // cylinder.
    pMesh = tempSM.Cylinder(8, 32, 1.0f, 2.0f, false);
    pMesh->AttachGlobalState(pRedMaterial);
    pMesh->GenerateNormals();
    mat3fRot.FromEulerAnglesXYZ(Mathf::PI/2.0f, 0.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(Vector3f(2.0f, 1.0f, 1.0f));
    pRoot->AttachChild(pMesh);

    // box.
    pMesh = tempSM.Box(0.6f, 0.6f, 0.6f);
    pMesh->AttachGlobalState(pBlueMaterial);
    pMesh->GenerateNormals();
    mat3fRot.FromEulerAnglesXYZ(0.0f, Mathf::PI/3.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(Vector3f(-1.6f, 0.6f, -1.0f));
    pRoot->AttachChild(pMesh);

    // torus.
    pMesh = tempSM.Torus(32, 32, 1.0f, 0.2f);
    pMesh->AttachGlobalState(pCopperMaterial);
    pMesh->GenerateNormals();
    mat3fRot.FromEulerAnglesXYZ(Mathf::PI/2.0f, 0.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(Vector3f(0.0f, 0.2f, 0.0f));
    pRoot->AttachChild(pMesh);

    // tetrahedron.
    pMesh = tempSM.Tetrahedron();
    pMesh->AttachGlobalState(pWhiteMaterial);
    pMesh->GenerateNormals();
    mat3fRot.FromEulerAnglesXYZ(-Mathf::PI/2.0f, 0.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(Vector3f(1.8f, 1.0f/3.0f, -0.8f));
    pRoot->AttachChild(pMesh);

    // dragon.
    Stream tempStream;
    const char* acPath = System::SE_GetPath("dragon.seof", System::SM_READ);
    SE_ASSERT( acPath );
    bool bLoaded = tempStream.Load(acPath);
    SE_ASSERT( bLoaded );
    (void)bLoaded;
    Node* pSceneLoaded = DynamicCast<Node>(tempStream.GetObjectAt(0));
    TriMeshPtr spMeshDragon = DynamicCast<TriMesh>(pSceneLoaded->GetChild(0));
    SE_ASSERT( spMeshDragon );
    spMeshDragon->GenerateNormals();
    mat3fRot.FromEulerAnglesXYZ(0.0f, Mathf::PI/3.0f, 0.0f);
    spMeshDragon->Local.SetRotate(mat3fRot);
    spMeshDragon->Local.SetTranslate(Vector3f(10.0f, -14.5f, 9.5f));
    spMeshDragon->AttachGlobalState(pGreenMaterial);
    spMeshDragon->DetachAllEffects();
    pSceneLoaded->DetachChild(spMeshDragon);
    pRoot->AttachChild(spMeshDragon);

    // teapot.
    acPath = System::SE_GetPath("teapot.seof", System::SM_READ);
    SE_ASSERT( acPath );
    bLoaded = tempStream.Load(acPath);
    SE_ASSERT( bLoaded );
    pSceneLoaded = DynamicCast<Node>(tempStream.GetObjectAt(0));
    TriMeshPtr spMeshTeapot = DynamicCast<TriMesh>(pSceneLoaded->GetChild(0));
    SE_ASSERT( spMeshTeapot );
    spMeshTeapot->GenerateNormals();
    spMeshTeapot->AttachGlobalState(pEggMaterial);
    spMeshTeapot->Local.SetUniformScale(0.2f);
    mat3fRot.FromEulerAnglesXYZ(0.0f, Mathf::PI/3.0f, 0.0f);
    spMeshTeapot->Local.SetRotate(mat3fRot);
    spMeshTeapot->Local.SetTranslate(Vector3f(4.0f, 0.0f, -1.5f));
    spMeshTeapot->DetachAllEffects();
    pRoot->AttachChild(pSceneLoaded);

    ColorNormalDepthEffect* pEffect = SE_NEW ColorNormalDepthEffect;
    pEffect->FarCilpDist = m_spCamera->GetDMax();
    pRoot->AttachEffect(pEffect);

    return (Node*)pRoot;
}
//----------------------------------------------------------------------------
void ScreenSpaceAO::CreateLights()
{
    m_aspLight[0] = SE_NEW Light(Light::LT_AMBIENT);
    m_aspLight[1] = SE_NEW Light(Light::LT_DIRECTIONAL);
    m_aspLight[2] = SE_NEW Light(Light::LT_POINT);
    m_aspLight[3] = SE_NEW Light(Light::LT_SPOT);

    float fValue = 0.75f;
    m_aspLight[0]->Ambient = ColorRGB(fValue, fValue, fValue);

    fValue = Mathf::Sqrt(1.0f/3.0f);
    m_aspLight[1]->DVector = Vector3f(-fValue, -fValue, +fValue);
    m_aspLight[1]->Diffuse = ColorRGB::SE_RGB_WHITE;
    m_aspLight[1]->Specular = ColorRGB::SE_RGB_WHITE;

    fValue = 4.0f;
    m_aspLight[2]->Position = Vector3f(0.0f, +fValue, 0.0f);
    m_aspLight[2]->Ambient = ColorRGB::SE_RGB_WHITE*0.5f;
    m_aspLight[2]->Diffuse = ColorRGB::SE_RGB_WHITE;
    m_aspLight[2]->Specular = ColorRGB::SE_RGB_WHITE*0.6f;
    m_aspLight[2]->Linear = 0.02f;
    m_aspLight[2]->Quadratic = 0.005f;

    fValue = 4.0f;
    m_aspLight[3]->Position = Vector3f(+fValue, +fValue, +fValue);
    fValue = -Mathf::Sqrt(1.0f/3.0f);
    m_aspLight[3]->DVector = Vector3f(+fValue, +fValue, +fValue);
    m_aspLight[3]->Diffuse = ColorRGB::SE_RGB_WHITE;
    m_aspLight[3]->Specular = ColorRGB::SE_RGB_WHITE;
    m_aspLight[3]->Exponent = 1.0f;
    m_aspLight[3]->SetAngle(0.125f*Mathf::PI);

    m_spScene->AttachLight(m_aspLight[2]);
    m_spScene->AttachLight(m_aspLight[0]);
    //m_spScene->AttachLight(m_aspLight[1]);
    //m_spScene->AttachLight(m_aspLight[3]);
}
//----------------------------------------------------------------------------