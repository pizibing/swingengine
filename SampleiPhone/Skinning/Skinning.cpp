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

#include "Skinning.h"

SE_WINDOW_APPLICATION(Skinning);

SE_REGISTER_INITIALIZE(Skinning);

//----------------------------------------------------------------------------
Skinning::Skinning()
    :
    SEWindowApplication3("Skinning", 0, 0, 320, 480, 
        SEColorRGBA(0.5f, 0.5f, 0.5f, 1.0f))
{
}
//----------------------------------------------------------------------------
bool Skinning::OnInitialize()
{
    if( !SEWindowApplication3::OnInitialize() )
    {
        return false;
    }

    float fR = 0.55f;
    float fU = fR*1.5f;
    m_spCamera->SetFrustum(-fR, fR, -fU, fU, 1.0f, 100.0f);
    SEVector3f tempCLoc(0.0f, 0.0f, -20.0f);
    SEVector3f tempCDir(0.0f, 0.0f, 1.0f);
    SEVector3f tempCUp(0.0f, 1.0f, 0.0f);
    SEVector3f tempCRight = tempCUp.Cross(tempCDir);
    m_spCamera->SetFrame(tempCLoc, tempCRight, tempCUp, tempCDir);

    CreateScene();

    // initial update of objects
    m_spScene->UpdateGS();
    m_spScene->UpdateRS();

    // initial culling of scene
    m_Culler.SetCamera(m_spCamera);
    m_Culler.ComputeUnculledSet(m_spScene);

    InitializeCameraMotion(0.1f, 0.01f);
    InitializeObjectMotion(m_spScene);
    return true;
}
//----------------------------------------------------------------------------
void Skinning::OnTerminate()
{
    m_spScene = 0;
    m_spMesh = 0;
    m_spWireframe = 0;
    SEWindowApplication3::OnTerminate();
}
//----------------------------------------------------------------------------
void Skinning::OnIdle()
{
    MeasureTime();

    m_spScene->UpdateGS(SESystem::SE_GetTime());
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
        DrawFrameRate(8, 20, SEColorRGBA::SE_RGBA_WHITE);
        m_pRenderer->EndScene();
    }
    m_pRenderer->DisplayBackBuffer();

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
void Skinning::CreateScene()
{
    m_spScene = SE_NEW SENode;
    m_spWireframe = SE_NEW SEWireframeState;
    m_spScene->AttachGlobalState(m_spWireframe);

    SEMatrix3f mat3fR;
    mat3fR.FromAxisAngle(SEVector3f::UNIT_Z, -SEMathf::HALF_PI);
    m_spScene->Local.SetRotate(mat3fR);
    m_spScene->Local.SetTranslate(SEVector3f(-5.0f, 0.0f, 0.0f));

    SEStream tempStream;
    const char* acPath = SESystem::SE_GetPath("boy.seof", SESystem::SM_READ);
    SE_ASSERT( acPath );
    bool bLoaded = tempStream.Load(acPath);
    SE_ASSERT( bLoaded );
    (void)bLoaded;
    SENode* pRoot = DynamicCast<SENode>(tempStream.GetObjectAt(0));
    m_spScene->AttachChild(pRoot);
}
//----------------------------------------------------------------------------
