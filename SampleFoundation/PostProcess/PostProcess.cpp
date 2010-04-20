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

#include "PostProcess.h"
#include "SEGaussianBlurHEffect2.h"
#include "SEGaussianBlurVEffect2.h"

SE_WINDOW_APPLICATION(PostProcess);
SE_REGISTER_INITIALIZE(PostProcess);

//----------------------------------------------------------------------------
PostProcess::PostProcess()
    :
    SEWindowApplication3("PostProcess", 0, 0, 640, 480, 
        SEColorRGBA(0.0f, 0.25f, 0.75f, 1.0f))
{
    m_pFrameBuffer1 = 0;
    m_pFrameBuffer2 = 0;
    m_pFrameBuffer3= 0;
    m_bPostProcess = false;
}
//----------------------------------------------------------------------------
bool PostProcess::OnInitialize()
{
    if( !SEWindowApplication3::OnInitialize() )
    {
        return false;
    }

    // 创建camera.
    m_spCamera->SetFrustum(60.0f, 4.0f/3.0f, 1.0f, 100.0f);
    SEVector3f tempCLoc(0.0f, 0.0f, -10.0f);
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
void PostProcess::OnTerminate()
{
    SEFrameBuffer::Destroy(m_pFrameBuffer1);
    SEFrameBuffer::Destroy(m_pFrameBuffer2);
    SEFrameBuffer::Destroy(m_pFrameBuffer3);

    m_spScene = 0;
    m_spTeapot = 0;
    m_spWireframe = 0;
    m_spScreenCamera = 0;
    m_spScenePolygon1 = 0;
    m_spScenePolygon2 = 0;
    m_spScenePolygon3 = 0;
    m_spSceneImage = 0;

    m_aspLight[0] = 0;
    m_aspLight[1] = 0;

    SEWindowApplication3::OnTerminate();
}
//----------------------------------------------------------------------------
void PostProcess::OnIdle()
{
    // 旋转我们创建的teapot.
    static double dCurTime = 0.0f;
    static double dLastTime = 0.0f;
    static float fAngel = 0.0f;
    static float fR = 15.0f;
    dCurTime = SESystem::SE_GetTime();
    if( dCurTime - dLastTime > 0.01f )
    {
        dLastTime = dCurTime;

        SEMatrix3f mat3fRot;
        mat3fRot.FromEulerAnglesXYZ(0.0f, 0.01f, 0.0f);
        m_spTeapot->Local.SetRotate(m_spTeapot->Local.GetRotate()*mat3fRot);
        m_spTeapot->UpdateGS();
    }

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
        if( m_bPostProcess )
        {
            // 把场景渲染到target 1(original scene).
            m_pFrameBuffer1->Enable();
            m_pRenderer->SetClearColor(SEColorRGBA(0.5f, 0.5f, 0.5f, 1.0f));
            m_pRenderer->ClearBuffers();
            m_pRenderer->DrawScene(m_Culler.GetVisibleSet());
            m_pFrameBuffer1->Disable();

            // 把target 1渲染到target 2(post process 1).
            m_pRenderer->SetCamera(m_spScreenCamera);
            m_pFrameBuffer2->Enable();
            m_pRenderer->Draw(m_spScenePolygon1);
            m_pFrameBuffer2->Disable();

            // 把target 2渲染到target 3(post process 2).
            m_pFrameBuffer3->Enable();
            m_pRenderer->Draw(m_spScenePolygon2);
            m_pFrameBuffer3->Disable();

            // 把target1和target3进行combine,渲染到屏幕矩形3.
            m_pRenderer->Draw(m_spScenePolygon3);
        }
        else
        {
            // 把场景渲染到backbuffer.
            m_pRenderer->SetCamera(m_spCamera);
            m_pRenderer->SetClearColor(SEColorRGBA(0.5f, 0.5f, 0.5f, 1.0f));
            m_pRenderer->ClearBuffers();
            m_pRenderer->DrawScene(m_Culler.GetVisibleSet());
        }

        m_pRenderer->SetCamera(m_spCamera);
        DrawFrameRate(8, 20, SEColorRGBA::SE_RGBA_WHITE);

        m_pRenderer->EndScene();
    }
    m_pRenderer->DisplayBackBuffer();

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool PostProcess::OnKeyDown(unsigned char ucKey, int iX, int iY)
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
        TestStreaming(m_spScene, 128, 128, 640, 480, "PostProcess.seof");
        return true;

    case 'p':
    case 'P':
        m_bPostProcess = !m_bPostProcess;
        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
void PostProcess::CreateScene()
{
    // screen camera把[0, 1]^3区间上的(x, y, z)映射到[-1, 1]^2 x [0, 1]区间上
    // 的(x', y, 'z').
    m_spScreenCamera = SE_NEW SECamera;
    m_spScreenCamera->SetPerspective(false);
    m_spScreenCamera->SetFrustum(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    m_spScreenCamera->SetFrame(SEVector3f::ZERO, SEVector3f::UNIT_X, 
        SEVector3f::UNIT_Y, SEVector3f::UNIT_Z);

    m_spScene = SE_NEW SENode;
    m_spWireframe = SE_NEW SEWireframeState;
    m_spScene->AttachGlobalState(m_spWireframe);

    CreateLights();
    CreateTeapot();

    SEAttributes tempAttrScenePoly;
    tempAttrScenePoly.SetPositionChannels(3);
    tempAttrScenePoly.SetTCoordChannels(0, 2);

    float fExtend = 1.0f;
    SEVertexBuffer* pVBufferScenePoly = SE_NEW SEVertexBuffer(
        tempAttrScenePoly, 4);
    pVBufferScenePoly->Position3(0) = SEVector3f(0.0f, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(1) = SEVector3f(fExtend, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(2) = SEVector3f(fExtend, fExtend, 0.0f);
    pVBufferScenePoly->Position3(3) = SEVector3f(0.0f, fExtend, 0.0f);
    pVBufferScenePoly->TCoord2(0, 0) = SEVector2f(0.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0, 1) = SEVector2f(1.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0, 2) = SEVector2f(1.0f, 0.0f);
    pVBufferScenePoly->TCoord2(0, 3) = SEVector2f(0.0f, 0.0f);
    SEIndexBuffer* pIBufferScenePoly = SE_NEW SEIndexBuffer(6);
    int* pIBufferDataScenePoly = pIBufferScenePoly->GetData();
    pIBufferDataScenePoly[0] = 0;  
    pIBufferDataScenePoly[1] = 3;  
    pIBufferDataScenePoly[2] = 1;
    pIBufferDataScenePoly[3] = 1;  
    pIBufferDataScenePoly[4] = 3;  
    pIBufferDataScenePoly[5] = 2;
    m_spScenePolygon1 = SE_NEW SETriMesh(pVBufferScenePoly, 
        pIBufferScenePoly);

    fExtend = 1.0f;
    pVBufferScenePoly = SE_NEW SEVertexBuffer(tempAttrScenePoly, 4);
    pVBufferScenePoly->Position3(0) = SEVector3f(0.0f, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(1) = SEVector3f(fExtend, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(2) = SEVector3f(fExtend, fExtend, 0.0f);
    pVBufferScenePoly->Position3(3) = SEVector3f(0.0f, fExtend, 0.0f);
    pVBufferScenePoly->TCoord2(0,0) = SEVector2f(0.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0, 1) = SEVector2f(1.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0, 2) = SEVector2f(1.0f, 0.0f);
    pVBufferScenePoly->TCoord2(0, 3) = SEVector2f(0.0f, 0.0f);
    m_spScenePolygon2 = SE_NEW SETriMesh(pVBufferScenePoly, 
        pIBufferScenePoly);

    fExtend = 1.0f;
    tempAttrScenePoly.SetTCoordChannels(1, 2);
    pVBufferScenePoly = SE_NEW SEVertexBuffer(tempAttrScenePoly, 4);
    pVBufferScenePoly->Position3(0) = SEVector3f(0.0f, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(1) = SEVector3f(fExtend, 0.0f, 0.0f);
    pVBufferScenePoly->Position3(2) = SEVector3f(fExtend, fExtend, 0.0f);
    pVBufferScenePoly->Position3(3) = SEVector3f(0.0f, fExtend, 0.0f);
    pVBufferScenePoly->TCoord2(0, 0) = SEVector2f(0.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0, 1) = SEVector2f(1.0f, 1.0f);
    pVBufferScenePoly->TCoord2(0, 2) = SEVector2f(1.0f, 0.0f);
    pVBufferScenePoly->TCoord2(0, 3) = SEVector2f(0.0f, 0.0f);
    pVBufferScenePoly->TCoord2(1, 0) = SEVector2f(0.0f, 1.0f);
    pVBufferScenePoly->TCoord2(1, 1) = SEVector2f(1.0f, 1.0f);
    pVBufferScenePoly->TCoord2(1, 2) = SEVector2f(1.0f, 0.0f);
    pVBufferScenePoly->TCoord2(1, 3) = SEVector2f(0.0f, 0.0f);
    m_spScenePolygon3 = SE_NEW SETriMesh(pVBufferScenePoly, 
        pIBufferScenePoly);

    int iWidth = 640, iHeight = 480;
    unsigned char* aucData = 0;
    m_spSceneImage = SE_NEW SEImage(SEImage::IT_RGBA8888, iWidth, iHeight, 
        aucData, "SceneImage");

    SEZBufferState* pState = SE_NEW SEZBufferState();
    pState->Enabled = false;

#if defined(SE_USING_OES2)
    SEGaussianBlurHEffect2* pEffectScenePoly1 = 
        SE_NEW SEGaussianBlurHEffect2("SceneImage");
    SEGaussianBlurHEffect2::GenerateTexelKernelStep(iWidth, iHeight);
#else
    SEGaussianBlurHEffect* pEffectScenePoly1 = 
        SE_NEW SEGaussianBlurHEffect("SceneImage");
    SEGaussianBlurHEffect::GenerateTexelKernel(iWidth, iHeight);
#endif
    m_pSceneTarget1 = pEffectScenePoly1->GetPTexture(0, 0);
    m_pSceneTarget1->SetOffscreenTexture(true);
    m_spScenePolygon1->AttachEffect(pEffectScenePoly1);
    m_spScenePolygon1->AttachGlobalState(pState);
    m_spScenePolygon1->UpdateGS();
    m_spScenePolygon1->UpdateRS();
    m_pRenderer->LoadResources(m_spScenePolygon1);

    // 创建绑定到纹理的RGBA frame buffer 1.
    SETexture** apTargets = SE_NEW SETexture*[1];
    apTargets[0] = m_pSceneTarget1;
    m_pFrameBuffer1 = SEFrameBuffer::Create(m_eFormat, m_eDepth, m_eStencil,
        m_eBuffering, m_eMultisampling, m_pRenderer, 1, apTargets);
    SE_ASSERT( m_pFrameBuffer1 );

#if defined(SE_USING_OES2)
    SEGaussianBlurVEffect2* pEffectScenePoly2 = 
        SE_NEW SEGaussianBlurVEffect2("SceneImage");
    SEGaussianBlurVEffect2::GenerateTexelKernelStep(iWidth, iHeight);
#else
    SEGaussianBlurVEffect* pEffectScenePoly2 = 
        SE_NEW SEGaussianBlurVEffect("SceneImage");
    SEGaussianBlurVEffect::GenerateTexelKernel(iWidth, iHeight);
#endif
    m_pSceneTarget2 = pEffectScenePoly2->GetPTexture(0, 0);
    m_pSceneTarget2->SetOffscreenTexture(true);
    m_spScenePolygon2->AttachEffect(pEffectScenePoly2);
    m_spScenePolygon2->AttachGlobalState(pState);
    m_spScenePolygon2->UpdateGS();
    m_spScenePolygon2->UpdateRS();
    m_pRenderer->LoadResources(m_spScenePolygon2);

    // 创建绑定到纹理的RGBA frame buffer 2.
    apTargets = SE_NEW SETexture*[1];
    apTargets[0] = m_pSceneTarget2;
    m_pFrameBuffer2 = SEFrameBuffer::Create(m_eFormat, m_eDepth, m_eStencil,
        m_eBuffering, m_eMultisampling, m_pRenderer, 1, apTargets);
    SE_ASSERT( m_pFrameBuffer2 );

    SECombineEffect* pEffectScenePoly3 = 
        SE_NEW SECombineEffect("SceneImage", "SceneImage");
    pEffectScenePoly3->SetPTexture(0, 0, m_pSceneTarget1);
    m_pSceneTarget3 = pEffectScenePoly3->GetPTexture(0, 1);
    m_pSceneTarget3->SetOffscreenTexture(true);
    m_spScenePolygon3->AttachEffect(pEffectScenePoly3);
    m_spScenePolygon3->UpdateGS();
    m_spScenePolygon3->UpdateRS();
    m_pRenderer->LoadResources(m_spScenePolygon3);

    // 创建绑定到纹理的RGBA frame buffer 3.
    apTargets = SE_NEW SETexture*[1];
    apTargets[0] = m_pSceneTarget3;
    m_pFrameBuffer3 = SEFrameBuffer::Create(m_eFormat, m_eDepth, m_eStencil,
        m_eBuffering, m_eMultisampling, m_pRenderer, 1, apTargets);
    SE_ASSERT( m_pFrameBuffer3 );
}
//----------------------------------------------------------------------------
void PostProcess::CreateTeapot()
{
    // polished egg.
    SEMaterialState* pEggMaterial = SE_NEW SEMaterialState;
    pEggMaterial->Ambient = SEColorRGB(1.0f, 0.92f, 0.804f)*0.1f;
    pEggMaterial->Diffuse = SEColorRGB(1.0f, 0.92f, 0.804f)*0.9f;
    pEggMaterial->Specular = SEColorRGB(0.4f, 0.4f, 0.4f);
    pEggMaterial->Shininess = 50.0f;

    SEStream tempStream;
    const char* acPath = SESystem::SE_GetPath("teapot.seof", 
        SESystem::SM_READ);
    SE_ASSERT( acPath );
    bool bLoaded = tempStream.Load(acPath);
    SE_ASSERT( bLoaded );
    (void)bLoaded;

    SENode* pSceneLoaded = DynamicCast<SENode>(tempStream.GetObjectAt(0));
    m_spTeapot = DynamicCast<SETriMesh>(pSceneLoaded->GetChild(0));
    SE_ASSERT( m_spTeapot );

#if defined(SE_USING_OES2)
    m_spTeapot->LightingMode = SEGeometry::GLM_PIPELINE_VERTEX;
#else
    m_spTeapot->LightingMode = SEGeometry::GLM_PIPELINE_PIXEL;
#endif

    m_spTeapot->GenerateNormals();
    m_spTeapot->AttachGlobalState(pEggMaterial);
    m_spTeapot->Local.SetUniformScale(20.0f);
    m_spTeapot->Local.SetTranslate(SEVector3f(0.0f, -3.0f, 0.0f));
    m_spTeapot->DetachAllEffects();

    m_spScene->AttachChild(pSceneLoaded);
}
//----------------------------------------------------------------------------
void PostProcess::CreateLights()
{
    m_aspLight[0] = SE_NEW SELight(SELight::LT_AMBIENT);
    m_aspLight[1] = SE_NEW SELight(SELight::LT_DIRECTIONAL);

    float fValue = 0.75f;
    m_aspLight[0]->Ambient = SEColorRGB(fValue, fValue, fValue);

    fValue = SEMathf::Sqrt(1.0f/3.0f);
    m_aspLight[1]->DVector = SEVector3f(-fValue, -fValue, +fValue);
    m_aspLight[1]->Ambient = SEColorRGB::SE_RGB_WHITE;
    m_aspLight[1]->Diffuse = SEColorRGB::SE_RGB_WHITE;
    m_aspLight[1]->Specular = SEColorRGB::SE_RGB_WHITE;

    m_spScene->AttachLight(m_aspLight[0]);
    m_spScene->AttachLight(m_aspLight[1]);
}
//----------------------------------------------------------------------------