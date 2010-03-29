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
    WindowApplication3("WaveSource3D", 0, 0, 320, 480, 
        ColorRGBA(0.5f, 0.5f, 0.5f, 1.0f))
{
    for( int i = 0; i < SOUND_COUNT; i++ )
    {
        m_bSoundSwitch[i] = false;
    }

    TriMesh::InitializePickRecordPool();
}
//----------------------------------------------------------------------------
bool WaveSource3D::OnInitialize()
{
    if( !WindowApplication3::OnInitialize() )
    {
        return false;
    }

    float fR = 0.55f;
    float fU = fR*1.5f;
    m_spCamera->SetFrustum(-fR, fR, -fU, fU, 1.0f, 100.0f);
    Vector3f tempCLoc(0.0f, 0.0f, 0.0f);
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

    TriMesh::TerminatePickRecordPool();

    WindowApplication3::OnTerminate();
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
        DrawFrameRate(8, 20, ColorRGBA::SE_RGBA_WHITE);
        m_pRenderer->EndScene();
    }
    m_pRenderer->DisplayBackBuffer();

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
void WaveSource3D::CreateScene()
{
    // create root.
    m_spScene = SE_NEW Node;
    Matrix3f mat3fR;
    mat3fR.FromAxisAngle(Vector3f::UNIT_Z, -Mathf::HALF_PI);
    m_spScene->Local.SetRotate(mat3fR);
	

    // create sound buffer "gunfire".
    Wave* pWave = WaveCatalog::GetActive()->Find("gunfire");
    SE_ASSERT( pWave );
    m_spSBufferGunfire = SE_NEW SoundBuffer(1, &pWave);
    m_spSBufferGunfire->SetName("gunfire");

    // create sound buffer "affliction alert".
    pWave = WaveCatalog::GetActive()->Find("AfflictionAlert");
    SE_ASSERT( pWave );
    m_spSBufferAfflictionAlert = SE_NEW SoundBuffer(1, &pWave);
    m_spSBufferAfflictionAlert->SetName("AfflictionAlert");

    // create sound buffer "gunhit".
    pWave = WaveCatalog::GetActive()->Find("gunhit");
    SE_ASSERT( pWave );
    m_spSBufferGunhit = SE_NEW SoundBuffer(1, &pWave);
    m_spSBufferGunhit->SetName("gunhit");

    // create sound buffer "blip".
    pWave = WaveCatalog::GetActive()->Find("Blip");
    SE_ASSERT( pWave );
    m_spSBufferBlip = SE_NEW SoundBuffer(1, &pWave);
    m_spSBufferBlip->SetName("Blip");

    // create a point light.
    m_spLight = SE_NEW Light(Light::LT_POINT);
    m_spLight->Position = Vector3f(0.0f, 20.0f, 0.0f);
    m_spLight->Diffuse = ColorRGB::SE_RGB_WHITE;
    m_spLight->Specular = ColorRGB::SE_RGB_WHITE;
    m_spScene->AttachLight(m_spLight);

    // create polished red material.
    MaterialState* pRedMaterial = SE_NEW MaterialState;
    pRedMaterial->Ambient = ColorRGB(0.2f, 0.0f, 0.0f);
    pRedMaterial->Diffuse = ColorRGB(0.8f, 0.0f, 0.0f);
    pRedMaterial->Specular = ColorRGB(1.0f, 1.0f, 1.0f);
    pRedMaterial->Shininess = 50.0f;

    // create polished blue material.
    MaterialState* pBlueMaterial = SE_NEW MaterialState;
    pBlueMaterial->Ambient = ColorRGB(0.0f, 0.0f, 0.2f);
    pBlueMaterial->Diffuse = ColorRGB(0.0f, 0.0f, 0.8f);
    pBlueMaterial->Specular = ColorRGB(1.0f, 1.0f, 1.0f);
    pBlueMaterial->Shininess = 50.0f;

    // create polished green material.
    MaterialState* pGreenMaterial = SE_NEW MaterialState;
    pGreenMaterial->Ambient = ColorRGB(0.0f, 0.2f, 0.0f);
    pGreenMaterial->Diffuse = ColorRGB(0.0f, 0.8f, 0.0f);
    pGreenMaterial->Specular = ColorRGB(1.0f, 1.0f, 1.0f);
    pGreenMaterial->Shininess = 50.0f;

    // create polished yellow material.
    MaterialState* pYellowMaterial = SE_NEW MaterialState;
    pYellowMaterial->Ambient = ColorRGB(0.2f, 0.2f, 0.0f);
    pYellowMaterial->Diffuse = ColorRGB(0.8f, 0.8f, 0.0f);
    pYellowMaterial->Specular = ColorRGB(1.0f, 1.0f, 1.0f);
    pYellowMaterial->Shininess = 50.0f;

    Attributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetNormalChannels(3);
    StandardMesh tempSM(tempAttr);

    Geometry::GeometryLightingMode eLMode = Geometry::GLM_PIPELINE_VERTEX;

    // create sound object 0.
    m_aspSoundNode[0] = SE_NEW Node;
    m_aspSoundNode[0]->SetName("SoundSource0");
    m_aspSoundNode[0]->Local.SetTranslate(Vector3f(-20.0f, 2.0f, 40.0f));
    TriMesh* pSoundMesh = tempSM.Sphere(16, 16, 2.0f);
    pSoundMesh->LightingMode = eLMode;
    pSoundMesh->AttachGlobalState(pRedMaterial);
    m_aspSoundNode[0]->AttachChild(pSoundMesh);
    m_spScene->AttachChild(m_aspSoundNode[0]);
    m_aspSound[0] = SE_NEW Sound(m_spSBufferGunfire);
    m_aspSound[0]->Gain = 2.0f;
    m_aspSound[0]->Looping = true;
    m_aspSoundNode[0]->AttachChild(m_aspSound[0]);

    // create sound object 1.
    m_aspSoundNode[1] = SE_NEW Node;
    m_aspSoundNode[1]->SetName("SoundSource1");
    m_aspSoundNode[1]->Local.SetTranslate(Vector3f(20.0f, 2.0f, 40.0f));
    pSoundMesh = tempSM.Sphere(16, 16, 2.0f);
    pSoundMesh->LightingMode = eLMode;
    pSoundMesh->AttachGlobalState(pBlueMaterial);
    m_aspSoundNode[1]->AttachChild(pSoundMesh);
    m_spScene->AttachChild(m_aspSoundNode[1]);
    m_aspSound[1] = SE_NEW Sound(m_spSBufferAfflictionAlert);
    m_aspSound[1]->Gain = 2.0f;
    m_aspSound[1]->Looping = true;
    m_aspSoundNode[1]->AttachChild(m_aspSound[1]);

    // create sound object 2.
    m_aspSoundNode[2] = SE_NEW Node;
    m_aspSoundNode[2]->SetName("SoundSource2");
    m_aspSoundNode[2]->Local.SetTranslate(Vector3f(20.0f, 2.0f, -40.0f));
    pSoundMesh = tempSM.Sphere(16, 16, 2.0f);
    pSoundMesh->LightingMode = eLMode;
    pSoundMesh->AttachGlobalState(pGreenMaterial);
    m_aspSoundNode[2]->AttachChild(pSoundMesh);
    m_spScene->AttachChild(m_aspSoundNode[2]);
    m_aspSound[2] = SE_NEW Sound(m_spSBufferGunhit);
    m_aspSound[2]->Gain = 2.0f;
    m_aspSound[2]->Looping = true;
    m_aspSoundNode[2]->AttachChild(m_aspSound[2]);

    // create sound object 3.
    m_aspSoundNode[3] = SE_NEW Node;
    m_aspSoundNode[3]->SetName("SoundSource3");
    m_aspSoundNode[3]->Local.SetTranslate(Vector3f(-20.0f, 2.0f, -40.0f));
    pSoundMesh = tempSM.Sphere(16, 16, 2.0f);
    pSoundMesh->LightingMode = eLMode;
    pSoundMesh->AttachGlobalState(pYellowMaterial);
    m_aspSoundNode[3]->AttachChild(pSoundMesh);
    m_spScene->AttachChild(m_aspSoundNode[3]);
    m_aspSound[3] = SE_NEW Sound(m_spSBufferBlip);
    m_aspSound[3]->Gain = 2.0f;
    m_aspSound[3]->Looping = true;
    m_aspSoundNode[3]->AttachChild(m_aspSound[3]);

    // set master gain.
    m_spListener->SetMasterGain(4.0f);
}
//----------------------------------------------------------------------------