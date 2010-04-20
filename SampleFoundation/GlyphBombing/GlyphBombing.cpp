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

#include "GlyphBombing.h"
#include "GlyphBombingL1Effect.h"

SE_WINDOW_APPLICATION(GlyphBombing);

SE_REGISTER_INITIALIZE(GlyphBombing);

//----------------------------------------------------------------------------
GlyphBombing::GlyphBombing()
    :
    SEWindowApplication3("GlyphBombing", 0, 0, 640, 480, 
        SEColorRGBA(0.5f, 0.5f, 0.5f, 1.0f))
{
}
//----------------------------------------------------------------------------
bool GlyphBombing::OnInitialize()
{
    if( !SEWindowApplication3::OnInitialize() )
    {
        return false;
    }

    m_spCamera->SetFrustum(-0.55f, 0.55f, -0.4125f, 0.4125f, 1.0f, 100.0f);
    SEVector3f tempCLoc(0.0f, 0.0f, -10.0f);
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

    InitializeCameraMotion(0.01f, 0.001f);
    InitializeObjectMotion(m_spScene);
    return true;
}
//----------------------------------------------------------------------------
void GlyphBombing::OnTerminate()
{
    m_spScene = 0;
    m_spMesh = 0;
    m_spRandomImage = 0;
    m_spWireframe = 0;

    m_aspLight[0] = 0;
    m_aspLight[1] = 0;
    m_aspLight[2] = 0;
    m_aspLight[3] = 0;

    SEWindowApplication3::OnTerminate();
}
//----------------------------------------------------------------------------
void GlyphBombing::OnIdle()
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
bool GlyphBombing::OnKeyDown(unsigned char ucKey, int iX, int iY)
{
    if( SEWindowApplication3::OnKeyDown(ucKey, iX, iY) )
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
        TestStreaming(m_spScene, 128, 128, 640, 480, "GlyphBombing.seof");
        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
void GlyphBombing::CreateScene()
{
    m_spScene = SE_NEW SENode;
    m_spWireframe = SE_NEW SEWireframeState;
    m_spScene->AttachGlobalState(m_spWireframe);

    SEAttributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetNormalChannels(3);
    tempAttr.SetTCoordChannels(0, 2);

    SEStandardMesh tempSM(tempAttr);
    m_spMesh = tempSM.Rectangle(2, 2, 2.0f, 2.0f);
    m_spScene->AttachChild(m_spMesh);

    // ´´½¨randomÎÆÀí.
    m_spRandomImage = SEImage::GenerateRandomImage(SEImage::IT_RGBA8888, 
        32, 32, 100, "Random");

    GlyphBombingL1Effect* pEffect = SE_NEW GlyphBombingL1Effect("glyphs",
        "Random");
    SETexture* pRandomTexture = pEffect->GetPTexture(0, 1);
    pRandomTexture->SetFilterType(SETexture::NEAREST);
    pRandomTexture->SetWrapType(0, SETexture::REPEAT);
    pRandomTexture->SetWrapType(1, SETexture::REPEAT);
    m_spMesh->LightingMode = SEGeometry::GLM_USER;
    m_spMesh->AttachEffect(pEffect);

    CreateLights();
}
//----------------------------------------------------------------------------
void GlyphBombing::CreateLights()
{
    m_aspLight[0] = SE_NEW SELight(SELight::LT_AMBIENT);
    m_aspLight[1] = SE_NEW SELight(SELight::LT_DIRECTIONAL);
    m_aspLight[2] = SE_NEW SELight(SELight::LT_POINT);
    m_aspLight[3] = SE_NEW SELight(SELight::LT_SPOT);

    float fValue = 0.75f;
    m_aspLight[0]->Ambient = SEColorRGB(fValue, fValue, fValue);

    fValue = SEMathf::Sqrt(1.0f/3.0f);
    m_aspLight[1]->DVector = SEVector3f(-fValue, -fValue, +fValue);
    m_aspLight[1]->Diffuse = SEColorRGB::SE_RGB_WHITE;
    m_aspLight[1]->Specular = SEColorRGB::SE_RGB_WHITE;

    fValue = 4.0f;
    m_aspLight[2]->Position = SEVector3f(0.0f, 0.0f, -2.0f);
    m_aspLight[2]->Ambient = SEColorRGB::SE_RGB_WHITE*0.5f;
    m_aspLight[2]->Diffuse = SEColorRGB::SE_RGB_WHITE;
    m_aspLight[2]->Specular = SEColorRGB::SE_RGB_WHITE*0.6f;
    m_aspLight[2]->Linear = 0.02f;
    m_aspLight[2]->Quadratic = 0.005f;

    fValue = 4.0f;
    m_aspLight[3]->Position = SEVector3f(+fValue, +fValue, +fValue);
    fValue = -SEMathf::Sqrt(1.0f/3.0f);
    m_aspLight[3]->DVector = SEVector3f(+fValue, +fValue, +fValue);
    m_aspLight[3]->Diffuse = SEColorRGB::SE_RGB_WHITE;
    m_aspLight[3]->Specular = SEColorRGB::SE_RGB_WHITE;
    m_aspLight[3]->Exponent = 1.0f;
    m_aspLight[3]->SetAngle(0.125f*SEMathf::PI);

    m_spScene->AttachLight(m_aspLight[2]);
    //m_spScene->AttachLight(m_aspLight[0]);
    //m_spScene->AttachLight(m_aspLight[1]);
    //m_spScene->AttachLight(m_aspLight[3]);
}
//----------------------------------------------------------------------------