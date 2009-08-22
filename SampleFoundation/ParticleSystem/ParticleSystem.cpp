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

#include "ParticleSystem.h"
#include "BloodCellController.h"

SE_WINDOW_APPLICATION(ParticleSystem);

SE_REGISTER_INITIALIZE(ParticleSystem);

//----------------------------------------------------------------------------
ParticleSystem::ParticleSystem()
    :
    WindowApplication3("ParticleSystem", 0, 0, 800, 600, 
        ColorRGBA(0.5f, 0.5f, 0.5f, 1.0f))
{
}
//----------------------------------------------------------------------------
bool ParticleSystem::OnInitialize()
{
    if( !WindowApplication3::OnInitialize() )
    {
        return false;
    }

    m_spCamera->SetFrustum(-0.55f, 0.55f, -0.4125f, 0.4125f, 1.0f, 100.0f);
    Vector3f tempCLoc(0.0f, 0.0f, -5.0f);
    Vector3f tempCDir(0.0f, 0.0f, 1.0f);
    Vector3f tempCUp(0.0f, 1.0f, 0.0f);
    Vector3f tempCRight = tempCUp.Cross(tempCDir);
    m_spCamera->SetFrame(tempCLoc, tempCRight, tempCUp, tempCDir);

    m_spScene = SE_NEW Node;
    m_spWireframe = SE_NEW WireframeState;
    m_spScene->AttachGlobalState(m_spWireframe);
    m_spScene->AttachChild(CreateParticles());

    m_spScene->UpdateGS();
    m_spScene->UpdateRS();

    m_Culler.SetCamera(m_spCamera);
    m_Culler.ComputeUnculledSet(m_spScene);

    InitializeCameraMotion(0.01f, 0.001f);
    InitializeObjectMotion(m_spScene);
    return true;
}
//----------------------------------------------------------------------------
void ParticleSystem::OnTerminate()
{
    m_spScene = 0;
    m_spBloodCell = 0;
    m_spWireframe = 0;
    m_spController = 0;
    WindowApplication3::OnTerminate();
}
//----------------------------------------------------------------------------
void ParticleSystem::OnIdle()
{
    MeasureTime();

    MoveCamera();
    MoveObject();
    m_spScene->UpdateGS(System::SE_GetTime());
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
bool ParticleSystem::OnKeyDown(unsigned char ucKey, int iX, int iY)
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
    case 's':
    case 'S':
        TestStreaming(m_spScene, 128, 128, 640, 480, "ParticleSystem.seof");
        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
void ParticleSystem::CreateBloodCellImage()
{
    // create an image with transparency.
    int iWidth = 32, iHeight = 32;
    float fFactor = 1.0f/(iWidth*iWidth + iHeight*iHeight);
    unsigned char* aucData = SE_NEW unsigned char[4*iWidth*iHeight];
    int i = 0;
    for( int iY = 0; iY < iHeight; iY++ )
    {
        for( int iX = 0; iX < iWidth; iX++ )
        {
            aucData[i++] = 255;
            aucData[i++] = 0;
            aucData[i++] = 0;

            int iDX = 2*iX - iWidth;
            int iDY = 2*iY - iHeight;
            float fValue = fFactor*(iDX*iDX + iDY*iDY);
            SE_ASSERT( 0.0f <= fValue && fValue <= 1.0f );

            if( fValue < 0.125f )
            {
                fValue = Mathf::Cos(4.0f*Mathf::PI*fValue);
            }
            else
            {
                fValue = 0.0f;
            }
            aucData[i++] = (unsigned char)(255.0f*fValue);
        }
    }

    m_spBloodCell = SE_NEW Image(Image::IT_RGBA8888, iWidth, iHeight, aucData,
        "BloodCell");
}
//----------------------------------------------------------------------------
Particles* ParticleSystem::CreateParticles()
{
    const int iVCount = 256;
    Vector3f* aVertex = SE_NEW Vector3f[iVCount];
    float* afSize = SE_NEW float[iVCount];
    for( int i = 0; i < iVCount; i++ )
    {
        aVertex[i].X = Mathf::SymmetricRandom();
        aVertex[i].Y = Mathf::SymmetricRandom();
        aVertex[i].Z = Mathf::SymmetricRandom();
        afSize[i] = 0.25f*Mathf::UnitRandom();
    }
    Vector3fArray* pVertices = SE_NEW Vector3fArray(iVCount, aVertex);
    FloatArray* pSizes = SE_NEW FloatArray(iVCount, afSize);

    Attributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetTCoordChannels(0, 2);
    Particles* pParticles = SE_NEW Particles(tempAttr, pVertices, pSizes);

    CreateBloodCellImage();
    Effect* pEffect = SE_NEW TextureEffect("BloodCell");
    pParticles->AttachEffect(pEffect);

    AlphaState* pAS = SE_NEW AlphaState;
    pAS->BlendEnabled = true;
    pParticles->AttachGlobalState(pAS);

    ZBufferState* pZS = SE_NEW ZBufferState;
    pZS->Enabled = false;
    pParticles->AttachGlobalState(pZS);

    m_spController = SE_NEW BloodCellController;
    pParticles->AttachController(m_spController);
    m_spController->Frequency = 0.1;
    m_spController->MinTime = 0.0;
    m_spController->MaxTime = 1000.0;
    m_spController->Repeat = Controller::RT_CYCLE;
    m_spController->SystemAngularAxis = Vector3f::UNIT_Y;
    m_spController->SystemAngularSpeed = 10.0f;

    return pParticles;
}
//----------------------------------------------------------------------------