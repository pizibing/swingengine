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

#include "WaveSource3D.h"

SE_WINDOW_APPLICATION(WaveSource3D);

SE_REGISTER_INITIALIZE(WaveSource3D);

//----------------------------------------------------------------------------
WaveSource3D::WaveSource3D()
    :
    SEWindowApplication3("WaveSource3D", 0, 0, 320, 480, 
        SEColorRGBA(0.5f, 0.5f, 0.5f, 1.0f))
{
    for( int i = 0; i < SOUND_COUNT; i++ )
    {
        m_bSoundSwitch[i] = false;
    }

    SETriMesh::InitializePickRecordPool();
}
//----------------------------------------------------------------------------
bool WaveSource3D::OnInitialize()
{
    if( !SEWindowApplication3::OnInitialize() )
    {
        return false;
    }

    float fR = 0.55f;
    float fU = fR*1.5f;
    m_spCamera->SetFrustum(-fR, fR, -fU, fU, 1.0f, 100.0f);
    SEVector3f tempCLoc(0.0f, 0.0f, 0.0f);
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
	
	// initial playing of sounds.
	m_pAudioRenderer->Play(m_aspSound[0]);
	m_pAudioRenderer->Play(m_aspSound[1]);
	m_pAudioRenderer->Play(m_aspSound[2]);
	m_pAudioRenderer->Play(m_aspSound[3]);
	
    return true;
}
//----------------------------------------------------------------------------
void WaveSource3D::OnTerminate()
{
	m_pAudioRenderer->Stop(m_aspSound[0]);
	m_pAudioRenderer->Stop(m_aspSound[1]);
	m_pAudioRenderer->Stop(m_aspSound[2]);
	m_pAudioRenderer->Stop(m_aspSound[3]);
	
    m_spScene = 0;
    for( int i = 0; i < SOUND_COUNT; i++ )
    {
        m_aspSoundNode[i] = 0;
        m_aspSound[i] = 0;
    }
    m_spLight = 0;

    m_spSBufferGunfire = 0;
    m_spSBufferAfflictionAlert = 0;
    m_spSBufferGunhit = 0;
    m_spSBufferBlip = 0;

    SETriMesh::TerminatePickRecordPool();

    SEWindowApplication3::OnTerminate();
}
//----------------------------------------------------------------------------
void WaveSource3D::OnIdle()
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
void WaveSource3D::CreateScene()
{
    // create root.
    m_spScene = SE_NEW SENode;
    SEMatrix3f mat3fR;
    mat3fR.FromAxisAngle(SEVector3f::UNIT_Z, -SEMathf::HALF_PI);
    m_spScene->Local.SetRotate(mat3fR);
	

    // create sound buffer "gunfire".
    SEWave* pWave = SEWaveCatalog::GetActive()->Find("gunfire");
    SE_ASSERT( pWave );
    m_spSBufferGunfire = SE_NEW SESoundBuffer(1, &pWave);
    m_spSBufferGunfire->SetName("gunfire");

    // create sound buffer "affliction alert".
    pWave = SEWaveCatalog::GetActive()->Find("AfflictionAlert");
    SE_ASSERT( pWave );
    m_spSBufferAfflictionAlert = SE_NEW SESoundBuffer(1, &pWave);
    m_spSBufferAfflictionAlert->SetName("AfflictionAlert");

    // create sound buffer "gunhit".
    pWave = SEWaveCatalog::GetActive()->Find("gunhit");
    SE_ASSERT( pWave );
    m_spSBufferGunhit = SE_NEW SESoundBuffer(1, &pWave);
    m_spSBufferGunhit->SetName("gunhit");

    // create sound buffer "blip".
    pWave = SEWaveCatalog::GetActive()->Find("Blip");
    SE_ASSERT( pWave );
    m_spSBufferBlip = SE_NEW SESoundBuffer(1, &pWave);
    m_spSBufferBlip->SetName("Blip");

    // create a point light.
    m_spLight = SE_NEW SELight(SELight::LT_POINT);
    m_spLight->Position = SEVector3f(0.0f, 20.0f, 0.0f);
    m_spLight->Diffuse = SEColorRGB::SE_RGB_WHITE;
    m_spLight->Specular = SEColorRGB::SE_RGB_WHITE;
    m_spScene->AttachLight(m_spLight);

    // create polished red material.
    SEMaterialState* pRedMaterial = SE_NEW SEMaterialState;
    pRedMaterial->Ambient = SEColorRGB(0.2f, 0.0f, 0.0f);
    pRedMaterial->Diffuse = SEColorRGB(0.8f, 0.0f, 0.0f);
    pRedMaterial->Specular = SEColorRGB(1.0f, 1.0f, 1.0f);
    pRedMaterial->Shininess = 50.0f;

    // create polished blue material.
    SEMaterialState* pBlueMaterial = SE_NEW SEMaterialState;
    pBlueMaterial->Ambient = SEColorRGB(0.0f, 0.0f, 0.2f);
    pBlueMaterial->Diffuse = SEColorRGB(0.0f, 0.0f, 0.8f);
    pBlueMaterial->Specular = SEColorRGB(1.0f, 1.0f, 1.0f);
    pBlueMaterial->Shininess = 50.0f;

    // create polished green material.
    SEMaterialState* pGreenMaterial = SE_NEW SEMaterialState;
    pGreenMaterial->Ambient = SEColorRGB(0.0f, 0.2f, 0.0f);
    pGreenMaterial->Diffuse = SEColorRGB(0.0f, 0.8f, 0.0f);
    pGreenMaterial->Specular = SEColorRGB(1.0f, 1.0f, 1.0f);
    pGreenMaterial->Shininess = 50.0f;

    // create polished yellow material.
    SEMaterialState* pYellowMaterial = SE_NEW SEMaterialState;
    pYellowMaterial->Ambient = SEColorRGB(0.2f, 0.2f, 0.0f);
    pYellowMaterial->Diffuse = SEColorRGB(0.8f, 0.8f, 0.0f);
    pYellowMaterial->Specular = SEColorRGB(1.0f, 1.0f, 1.0f);
    pYellowMaterial->Shininess = 50.0f;

    SEAttributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetNormalChannels(3);
    SEStandardMesh tempSM(tempAttr);

    SEGeometry::GeometryLightingMode eLMode = SEGeometry::GLM_PIPELINE_VERTEX;

    // create sound object 0.
    m_aspSoundNode[0] = SE_NEW SENode;
    m_aspSoundNode[0]->SetName("SoundSource0");
    m_aspSoundNode[0]->Local.SetTranslate(SEVector3f(-20.0f, 2.0f, 40.0f));
    SETriMesh* pSoundMesh = tempSM.Sphere(16, 16, 2.0f);
    pSoundMesh->LightingMode = eLMode;
    pSoundMesh->AttachGlobalState(pRedMaterial);
    m_aspSoundNode[0]->AttachChild(pSoundMesh);
    m_spScene->AttachChild(m_aspSoundNode[0]);
    m_aspSound[0] = SE_NEW SESound(m_spSBufferGunfire);
    m_aspSound[0]->Gain = 2.0f;
    m_aspSound[0]->Looping = true;
    m_aspSoundNode[0]->AttachChild(m_aspSound[0]);

    // create sound object 1.
    m_aspSoundNode[1] = SE_NEW SENode;
    m_aspSoundNode[1]->SetName("SoundSource1");
    m_aspSoundNode[1]->Local.SetTranslate(SEVector3f(20.0f, 2.0f, 40.0f));
    pSoundMesh = tempSM.Sphere(16, 16, 2.0f);
    pSoundMesh->LightingMode = eLMode;
    pSoundMesh->AttachGlobalState(pBlueMaterial);
    m_aspSoundNode[1]->AttachChild(pSoundMesh);
    m_spScene->AttachChild(m_aspSoundNode[1]);
    m_aspSound[1] = SE_NEW SESound(m_spSBufferAfflictionAlert);
    m_aspSound[1]->Gain = 2.0f;
    m_aspSound[1]->Looping = true;
    m_aspSoundNode[1]->AttachChild(m_aspSound[1]);

    // create sound object 2.
    m_aspSoundNode[2] = SE_NEW SENode;
    m_aspSoundNode[2]->SetName("SoundSource2");
    m_aspSoundNode[2]->Local.SetTranslate(SEVector3f(20.0f, 2.0f, -40.0f));
    pSoundMesh = tempSM.Sphere(16, 16, 2.0f);
    pSoundMesh->LightingMode = eLMode;
    pSoundMesh->AttachGlobalState(pGreenMaterial);
    m_aspSoundNode[2]->AttachChild(pSoundMesh);
    m_spScene->AttachChild(m_aspSoundNode[2]);
    m_aspSound[2] = SE_NEW SESound(m_spSBufferGunhit);
    m_aspSound[2]->Gain = 2.0f;
    m_aspSound[2]->Looping = true;
    m_aspSoundNode[2]->AttachChild(m_aspSound[2]);

    // create sound object 3.
    m_aspSoundNode[3] = SE_NEW SENode;
    m_aspSoundNode[3]->SetName("SoundSource3");
    m_aspSoundNode[3]->Local.SetTranslate(SEVector3f(-20.0f, 2.0f, -40.0f));
    pSoundMesh = tempSM.Sphere(16, 16, 2.0f);
    pSoundMesh->LightingMode = eLMode;
    pSoundMesh->AttachGlobalState(pYellowMaterial);
    m_aspSoundNode[3]->AttachChild(pSoundMesh);
    m_spScene->AttachChild(m_aspSoundNode[3]);
    m_aspSound[3] = SE_NEW SESound(m_spSBufferBlip);
    m_aspSound[3]->Gain = 2.0f;
    m_aspSound[3]->Looping = true;
    m_aspSoundNode[3]->AttachChild(m_aspSound[3]);

    // set master gain.
    m_spListener->SetMasterGain(4.0f);
}
//----------------------------------------------------------------------------