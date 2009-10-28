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

#include "DefaultShader.h"

SE_WINDOW_APPLICATION(DefaultShader);

SE_REGISTER_INITIALIZE(DefaultShader);

//----------------------------------------------------------------------------
DefaultShader::DefaultShader()
    :
    WindowApplication3("DefaultShader", 0, 0, 640, 480, 
        ColorRGBA(0.5f, 0.5f, 0.5f, 1.0f))
{
}
//----------------------------------------------------------------------------
bool DefaultShader::OnInitialize()
{
    if( !WindowApplication3::OnInitialize() )
    {
        return false;
    }

    m_spCamera->SetFrustum(-0.55f, 0.55f, -0.4125f, 0.4125f, 1.0f, 100.0f);
    Vector3f tempCLoc(0.0f, 0.0f, -10.0f);
    Vector3f tempCDir(0.0f, 0.0f, 1.0f);
    Vector3f tempCUp(0.0f, 1.0f, 0.0f);
    Vector3f tempCRight = tempCUp.Cross(tempCDir);
    m_spCamera->SetFrame(tempCLoc, tempCRight, tempCUp, tempCDir);

    CreateScene();

    // initial update of objects
    m_spScene->UpdateGS();
    m_spScene->UpdateRS();

    // initial culling of scene
    m_Culler.SetCamera(m_spCamera);
    m_Culler.ComputeUnculledSet(m_spScene);

    InitializeCameraMotion(0.01f, 0.001f);
    InitializeObjectMotion(m_spScene);
    return true;
}
//----------------------------------------------------------------------------
void DefaultShader::OnTerminate()
{
    m_spScene = 0;
    m_spMesh = 0;
    m_spWireframe = 0;
    WindowApplication3::OnTerminate();
}
//----------------------------------------------------------------------------
void DefaultShader::OnIdle()
{
    MeasureTime();

    //// 旋转我们的box.
    //static double dCurTime = 0.0f;
    //static double dLastTime = 0.0f;
    //static float fAngel = 0.0f;
    //static float fR = 15.0f;
    //dCurTime = System::SE_GetTime();
    //if( dCurTime - dLastTime > 0.01f )
    //{
    //    dLastTime = dCurTime;

    //    Matrix3f mat3fRot(Vector3f::UNIT_Z, -0.01f);
    //    m_spMesh->Local.SetRotate(m_spMesh->Local.GetRotate()*mat3fRot);
    //    m_spMesh->UpdateGS();
    //}

    m_spScene->UpdateGS(System::SE_GetTime());
    m_Culler.ComputeUnculledSet(m_spScene);

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
        m_pRenderer->DrawScene(m_Culler.GetVisibleSet());
        DrawFrameRate(8, 20, ColorRGBA::SE_RGBA_WHITE);
        m_pRenderer->EndScene();
    }
    m_pRenderer->DisplayBackBuffer();

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool DefaultShader::OnKeyDown(unsigned char ucKey, int iX, int iY)
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
#if defined(SE_USING_DX10)
        // DX10 render state objects must be re-created based on our new states.
        m_spScene->UpdateRS();
#endif
        return true;
    case 's':
    case 'S':
        TestStreaming(m_spScene, 128, 128, 640, 480, "DefaultShader.seof");
        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
void DefaultShader::CreateScene()
{
    m_spScene = SE_NEW Node;
    m_spWireframe = SE_NEW WireframeState;
    m_spScene->AttachGlobalState(m_spWireframe);

    Attributes tempAttr;
    tempAttr.SetPositionChannels(3);
    StandardMesh tempSM(tempAttr);
    m_spMesh = tempSM.Box(4.0f, 1.0f, 2.0f);
    //m_spScene->AttachChild(m_spMesh);

    DefaultShaderEffect* pEffect = SE_NEW DefaultShaderEffect;
    m_spMesh->AttachEffect(pEffect);

    Stream tempStream;
    const char* acPath = System::SE_GetPath("boy.seof", System::SM_READ);
    SE_ASSERT( acPath );
    bool bLoaded = tempStream.Load(acPath);
    SE_ASSERT( bLoaded );
    (void)bLoaded;

    Node* pSceneLoaded = DynamicCast<Node>(tempStream.GetObjectAt(0));
    pSceneLoaded->AttachGlobalState(m_spWireframe);
    m_spScene->AttachChild(pSceneLoaded);

    // Test.
    Object* pBone = pSceneLoaded->GetObjectByName("l_hip");
    Node* pBoneNode = DynamicCast<Node>(pBone);
    SE_ASSERT( pBoneNode );
    Vector3f vec3fT = pBoneNode->Local.GetTranslate();
    //vec3fT.X += 1.0f;
    pBoneNode->Local.SetTranslate(vec3fT);
}
//----------------------------------------------------------------------------
