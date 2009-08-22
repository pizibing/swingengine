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
    WindowApplication3("WaveSource3D", 0, 0, 640, 480, 
        ColorRGBA(0.5f, 0.5f, 0.5f, 1.0f))
{
    m_fVerticalDistance = 1.7f;

    for( int i = 0; i < SOUND_COUNT; i++ )
    {
        m_bSoundSwitch[i] = false;
    }

    // 创建一组从摄像机观察点的12点方向发散开的射线.
    m_iNumRays = 5;
    m_fHalfAngle = 0.25f*Mathf::PI;
    m_afCos = SE_NEW float[m_iNumRays];
    m_afSin = SE_NEW float[m_iNumRays];
    m_afTolerance = SE_NEW float[m_iNumRays];
    float fMult = 1.0f / (m_iNumRays/2);
    for( int i = 0; i < m_iNumRays; i++ )
    {
        float fUnit = i*fMult - 1.0f;  // in [-1,1]
        float fAngle = Mathf::HALF_PI + m_fHalfAngle*fUnit;
        m_afCos[i] = Mathf::Cos(fAngle);
        m_afSin[i] = Mathf::Sin(fAngle);
        m_afTolerance[i] = 2.0f - 1.5f*Mathf::FAbs(fUnit);  // in [1/2,1]
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

    m_spCamera->SetFrustum(-0.55f, 0.55f, -0.4125f, 0.4125f, 1.0f, 200.0f);
    Vector3f tempCLoc(0.0f, 5.0f, 0.0f);
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

#if defined(SE_USING_OES2)
    InitializeCameraMotion(0.2f, 0.02f);
#else
    InitializeCameraMotion(0.02f, 0.001f);
#endif
    InitializeObjectMotion(m_spScene);
    MoveForward();
    return true;
}
//----------------------------------------------------------------------------
void WaveSource3D::OnTerminate()
{
    m_spScene = 0;
    for( int i = 0; i < SOUND_COUNT; i++ )
    {
        m_aspSoundNode[i] = 0;
        m_aspSound[i] = 0;
    }
    m_spLight = 0;
    m_spGround = 0;
    m_spWireframe = 0;

    m_spSBufferGunfire = 0;
    m_spSBufferAfflictionAlert = 0;
    m_spSBufferFootsteps = 0;
    m_spSBufferGunhit = 0;
    m_spSBufferBlip = 0;
    m_spSBufferKillZone2 = 0;

    SE_DELETE[] m_afCos;
    SE_DELETE[] m_afSin;
    SE_DELETE[] m_afTolerance;
    TriMesh::TerminatePickRecordPool();

    WindowApplication3::OnTerminate();
}
//----------------------------------------------------------------------------
void WaveSource3D::OnIdle()
{
    // 绕y轴以半径R旋转sound source 2.
    static double dCurTime = 0.0f;
    static double dLastTime = 0.0f;
    static float fAngel = 0.0f;
    static float fR = 15.0f;
    dCurTime = System::SE_GetTime();
    if( dCurTime - dLastTime > 0.0001f )
    {
        dLastTime = dCurTime;
        fAngel += 0.002f;
        Matrix3f mat3fRot;
        mat3fRot.FromEulerAnglesXYZ(0.0f, -0.002f, 0.0f);
        m_aspSoundNode[2]->Local.SetRotate(
            m_aspSoundNode[2]->Local.GetRotate()*mat3fRot);
        float fX = fR*Mathf::Cos(fAngel);
        float fZ = fR*Mathf::Sin(fAngel);
        m_aspSoundNode[2]->Local.SetTranslate(Vector3f(fX, 2.0f, fZ));
        m_aspSoundNode[2]->UpdateGS();
    }

    MeasureTime();
    MoveCamera();
    m_Culler.ComputeUnculledSet(m_spScene);

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
bool WaveSource3D::OnKeyDown(unsigned char ucKey, int iX, int iY)
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

    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
        {
            int iIndex = ucKey - '1';
            m_bSoundSwitch[iIndex] = !m_bSoundSwitch[iIndex];
            if( m_bSoundSwitch[iIndex] )
            {
                m_pAudioRenderer->Play(m_aspSound[iIndex]);
            }
            else
            {
                m_pAudioRenderer->Stop(m_aspSound[iIndex]);
            }
        }
        return true;

    case 's':
    case 'S':
        TestStreaming(m_spScene, 128, 128, 640, 480, "WaveSource3D.seof");
        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
bool WaveSource3D::OnMouseClick(int, int iState, int, int, unsigned int)
{
    if( iState != MOUSE_DOWN )
    {
        return false;
    }

    return true;
}
//----------------------------------------------------------------------------
void WaveSource3D::CreateScene()
{
    // create root.
    m_spScene = SE_NEW Node;
    m_spWireframe = SE_NEW WireframeState;
    m_spScene->AttachGlobalState(m_spWireframe);

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

    // create sound buffer "footsteps".
    pWave = WaveCatalog::GetActive()->Find("KillZone2");
    SE_ASSERT( pWave );
    m_spSBufferFootsteps = SE_NEW SoundBuffer(1, &pWave);
    m_spSBufferFootsteps->SetName("Footsteps");

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

    // create sound buffer "killzone2".
    pWave = WaveCatalog::GetActive()->Find("killzone2");
    SE_ASSERT( pWave );
    m_spSBufferKillZone2 = SE_NEW SoundBuffer(1, &pWave);
    m_spSBufferKillZone2->SetName("KillZone2");

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

    // create flat gray material.
    MaterialState* pGrayMaterial = SE_NEW MaterialState;
    pGrayMaterial->Ambient = ColorRGB(0.1f, 0.1f, 0.1f);
    pGrayMaterial->Diffuse = ColorRGB(0.7f, 0.7f, 0.7f);
    pGrayMaterial->Specular = ColorRGB(0.2f, 0.2f, 0.2f);
    pGrayMaterial->Shininess = 50.0f;

    // create flat egg material.
    MaterialState* pEggMaterial = SE_NEW MaterialState;
    pEggMaterial->Ambient = ColorRGB(1.0f, 0.92f, 0.804f)*0.2f;
    pEggMaterial->Diffuse = ColorRGB(1.0f, 0.92f, 0.804f)*0.8f;
    pEggMaterial->Specular = ColorRGB(0.1f, 0.1f, 0.1f);
    pEggMaterial->Shininess = 50.0f;

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

#if defined(SE_USING_OES2)
    Geometry::GeometryLightingMode eLMode = Geometry::GLM_PIPELINE_VERTEX;
#else
    Geometry::GeometryLightingMode eLMode = Geometry::GLM_PIPELINE_PIXEL;
#endif

    // create ground.
    m_spGround = tempSM.Rectangle(2, 2, 100.0f, 100.0f);
    m_spGround->LightingMode = eLMode;
    Matrix3f mat3fRot;
    mat3fRot.FromAxisAngle(Vector3f::UNIT_X, Mathf::HALF_PI);
    m_spGround->Local.SetRotate(mat3fRot);
    m_spGround->AttachGlobalState(pGrayMaterial);
    m_spScene->AttachChild(m_spGround);

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
    mat3fRot.FromEulerAnglesXYZ(0.0f, Mathf::HALF_PI, 0.0f);
    m_aspSoundNode[2]->Local.SetRotate(mat3fRot);
    m_aspSoundNode[2]->Local.SetTranslate(Vector3f(20.0f, 2.0f, 0.0f));
    pSoundMesh = tempSM.Sphere(16, 16, 2.0f);
    pSoundMesh->LightingMode = eLMode;
    pSoundMesh->AttachGlobalState(pEggMaterial);
    m_aspSoundNode[2]->AttachChild(pSoundMesh);
    m_spScene->AttachChild(m_aspSoundNode[2]);
    m_aspSound[2] = SE_NEW Sound(m_spSBufferKillZone2);
    m_aspSound[2]->Gain = 2.0f;
    m_aspSound[2]->Looping = true;
    m_aspSoundNode[2]->AttachChild(m_aspSound[2]);

    // create sound object 3.
    m_aspSoundNode[3] = SE_NEW Node;
    m_aspSoundNode[3]->SetName("SoundSource3");
    m_aspSoundNode[3]->Local.SetTranslate(Vector3f(20.0f, 2.0f, -40.0f));
    pSoundMesh = tempSM.Sphere(16, 16, 2.0f);
    pSoundMesh->LightingMode = eLMode;
    pSoundMesh->AttachGlobalState(pGreenMaterial);
    m_aspSoundNode[3]->AttachChild(pSoundMesh);
    m_spScene->AttachChild(m_aspSoundNode[3]);
    m_aspSound[3] = SE_NEW Sound(m_spSBufferGunhit);
    m_aspSound[3]->Gain = 2.0f;
    m_aspSound[3]->Looping = true;
    m_aspSoundNode[3]->AttachChild(m_aspSound[3]);

    // create sound object 4.
    m_aspSoundNode[4] = SE_NEW Node;
    m_aspSoundNode[4]->SetName("SoundSource4");
    m_aspSoundNode[4]->Local.SetTranslate(Vector3f(-20.0f, 2.0f, -40.0f));
    pSoundMesh = tempSM.Sphere(16, 16, 2.0f);
    pSoundMesh->LightingMode = eLMode;
    pSoundMesh->AttachGlobalState(pYellowMaterial);
    m_aspSoundNode[4]->AttachChild(pSoundMesh);
    m_spScene->AttachChild(m_aspSoundNode[4]);
    m_aspSound[4] = SE_NEW Sound(m_spSBufferBlip);
    m_aspSound[4]->Gain = 2.0f;
    m_aspSound[4]->Looping = true;
    m_aspSoundNode[4]->AttachChild(m_aspSound[4]);

    // set master gain.
    m_spListener->SetMasterGain(4.0f);
}
//----------------------------------------------------------------------------
void WaveSource3D::AdjustVerticalDistance()
{
    // 保持在ground上的垂直高度.
    Spatial::PickArray tempPickResults;
    Ray3f tempRay(m_spCamera->GetLocation(), -Vector3f::UNIT_Y);
    TriMesh::ResetPickRecordPool();
    m_spScene->DoPick(tempRay, tempPickResults);

    if( tempPickResults.size() > 0 )
    {
        Spatial::PickRecord* pClosest = Spatial::GetClosest(tempPickResults);
        SE_ASSERT( pClosest );

        TriMesh* pMesh = DynamicCast<TriMesh>(pClosest->IObject);
        SE_ASSERT( pMesh );
        TriMesh::PickRecord* pTMRecord = (TriMesh::PickRecord*)pClosest;

        Triangle3f tempTri;
        pMesh->GetWorldTriangle(pTMRecord->Triangle, tempTri);
        Vector3f vec3fClosest =
            pTMRecord->Bary0*tempTri.V[0] +
            pTMRecord->Bary1*tempTri.V[1] +
            pTMRecord->Bary2*tempTri.V[2];

        vec3fClosest.Y += m_fVerticalDistance;
        m_spCamera->SetLocation(vec3fClosest);
    }
}
//----------------------------------------------------------------------------
bool WaveSource3D::AllowMotion(float fSign)
{
    // 根据fSign,向前或向后走一步.
    // 检查场景中对象是否足够远.如果是,则允许走,否则停在原地.
    Vector3f vec3fNextPos = m_spCamera->GetLocation()
        + fSign*m_fTrnSpeed*m_aWorldAxis[2]
        - 0.5f*m_fVerticalDistance*m_aWorldAxis[1];

    bool bFoundObstacle = false;
    int i;
    for( i = 0; i < m_iNumRays; i++ )
    {
        Vector3f vec3fDir = m_afCos[i]*m_aWorldAxis[0] +
            fSign*m_afSin[i]*m_aWorldAxis[2];

        Spatial::PickArray tempPickResults;
        TriMesh::ResetPickRecordPool();
        m_spScene->DoPick(Ray3f(vec3fNextPos, vec3fDir), tempPickResults);
        if( tempPickResults.size() > 0 )
        {
            Spatial::PickRecord* pClosest = Spatial::GetClosest(tempPickResults);
            SE_ASSERT( pClosest );

            if( pClosest->T <= m_afTolerance[i] )
            {
                bFoundObstacle = true;
            }

            if( bFoundObstacle )
            {
                return false;
            }
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void WaveSource3D::MoveForward()
{
    if( AllowMotion(1.0f) )
    {
        WindowApplication3::MoveForward();
        AdjustVerticalDistance();
    }
}
//----------------------------------------------------------------------------
void WaveSource3D::MoveBackward()
{
    if( AllowMotion(-1.0f) )
    {
        WindowApplication3::MoveBackward();
        AdjustVerticalDistance();
    }
}
//----------------------------------------------------------------------------