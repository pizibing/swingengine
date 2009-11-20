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

#include "Lighting2.h"

SE_WINDOW_APPLICATION(Lighting2);

SE_REGISTER_INITIALIZE(Lighting2);

//----------------------------------------------------------------------------
Lighting2::Lighting2()
    :
    WindowApplication3("Lighting2", 0, 0, 320, 480, 
        ColorRGBA(0.5f, 0.5f, 0.5f, 1.0f))
{
    m_iACount = 0;
    m_iDCount = 0;
    m_iPCount = 0;
    m_iSCount = 0;
    m_iActiveLight = -1;
    m_iLightCount = 0;
    for (int i = 0; i < 8; i++)
    {
        m_acCaption[i] = '.';
    }
    m_acCaption[8] = 0;
}
//----------------------------------------------------------------------------
bool Lighting2::OnInitialize()
{
    if( !WindowApplication3::OnInitialize() )
    {
        return false;
    }

    float fR = 0.55f;
    float fU = fR*1.5f;
    m_spCamera->SetFrustum(-fR, fR, -fU, fU, 1.0f, 100.0f);
    Vector3f tempCLoc(0.0f, 0.0f, -15.0f);
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
    InitializeCameraMotion(0.1f, 0.01f);
#else
    InitializeCameraMotion(0.01f, 0.001f);
#endif
    InitializeObjectMotion(m_spScene);

    // Test.
    m_iPCount++;
    m_iLightCount++;
    UpdateEffects();

    return true;
}
//----------------------------------------------------------------------------
void Lighting2::OnTerminate()
{
    m_spScene = 0;
    m_spMesh = 0;
    m_spWireframe = 0;

    for( int i = 0; i < 8; i++ )
    {
        m_aspALight[i] = 0;
        m_aspDLight[i] = 0;
        m_aspPLight[i] = 0;
        m_aspSLight[i] = 0;
    }

    m_spDefaultEffect = 0;

    WindowApplication3::OnTerminate();
}
//----------------------------------------------------------------------------
void Lighting2::OnIdle()
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
        m_pRenderer->Draw(8, 16, ColorRGBA::SE_RGBA_WHITE, m_acCaption);
        DrawFrameRate(8, GetHeight()-8, ColorRGBA::SE_RGBA_WHITE);
        m_pRenderer->EndScene();
    }
    m_pRenderer->DisplayBackBuffer();

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
void Lighting2::CreateScene()
{
    m_spScene = SE_NEW Node;
    m_spWireframe = SE_NEW WireframeState;
    m_spScene->AttachGlobalState(m_spWireframe);

    Matrix3f mat3fR;
    mat3fR.FromAxisAngle(Vector3f::UNIT_Z, -Mathf::HALF_PI);
    m_spScene->Local.SetRotate(mat3fR);
    m_spScene->Local.SetTranslate(Vector3f(-5.0f, 0.0f, 0.0f));

    CreateLights();

    m_spScene->AttachChild(CreateModel());
    m_spScene->UpdateGS();
    m_spScene->UpdateRS();
    m_spScene->GetChild(0)->Local.SetTranslate(
        -m_spScene->WorldBound->GetCenter());
}
//----------------------------------------------------------------------------
void Lighting2::CreateLights()
{
    int i;
    for( i = 0; i < 8; i++ )
    {
        m_aspALight[i] = SE_NEW Light(Light::LT_AMBIENT);
        m_aspDLight[i] = SE_NEW Light(Light::LT_DIRECTIONAL);
        m_aspPLight[i] = SE_NEW Light(Light::LT_POINT);
        m_aspSLight[i] = SE_NEW Light(Light::LT_SPOT);
    }

    // ambient lights.
    float fValue = 0.75f;
    m_aspALight[0]->Ambient = ColorRGB(fValue, fValue, fValue);
    m_aspALight[1]->Ambient = ColorRGB(fValue, 0.0f,  0.0f);
    m_aspALight[2]->Ambient = ColorRGB(0.0f,  fValue, 0.0f);
    m_aspALight[3]->Ambient = ColorRGB(0.0f,  0.0f,  fValue);
    m_aspALight[4]->Ambient = ColorRGB(0.0f,  fValue, fValue);
    m_aspALight[5]->Ambient = ColorRGB(fValue, 0.0f,  fValue);
    m_aspALight[6]->Ambient = ColorRGB(fValue, fValue, 0.0f);
    m_aspALight[7]->Ambient = ColorRGB(fValue, fValue, fValue);

    // directional lights.
    fValue = Mathf::Sqrt(1.0f/3.0f);
    m_aspDLight[0]->DVector = Vector3f(-fValue, -fValue, +fValue);
    m_aspDLight[1]->DVector = Vector3f(-fValue, +fValue, +fValue);
    m_aspDLight[2]->DVector = Vector3f(+fValue, -fValue, +fValue);
    m_aspDLight[3]->DVector = Vector3f(+fValue, +fValue, +fValue);
    m_aspDLight[4]->DVector = Vector3f(-fValue, -fValue, -fValue);
    m_aspDLight[5]->DVector = Vector3f(-fValue, -fValue, +fValue);
    m_aspDLight[6]->DVector = Vector3f(-fValue, +fValue, -fValue);
    m_aspDLight[7]->DVector = Vector3f(-fValue, +fValue, +fValue);
    for( i = 0; i < 8; i++ )
    {
        m_aspDLight[i]->Ambient = ColorRGB::SE_RGB_WHITE*0.2f;
        m_aspDLight[i]->Diffuse = ColorRGB::SE_RGB_WHITE;
        m_aspDLight[i]->Specular = ColorRGB::SE_RGB_WHITE;
    }

    // point lights.
    fValue = 4.0f;
    m_aspPLight[0]->Position = Vector3f(4.0f, +2.0f, -5.0f);
    m_aspPLight[1]->Position = Vector3f(+fValue, +fValue, -fValue);
    m_aspPLight[2]->Position = Vector3f(+fValue, -fValue, +fValue);
    m_aspPLight[3]->Position = Vector3f(+fValue, -fValue, -fValue);
    m_aspPLight[4]->Position = Vector3f(-fValue, +fValue, +fValue);
    m_aspPLight[5]->Position = Vector3f(-fValue, +fValue, -fValue);
    m_aspPLight[6]->Position = Vector3f(-fValue, -fValue, +fValue);
    m_aspPLight[7]->Position = Vector3f(-fValue, -fValue, -fValue);
    for( i = 0; i < 8; i++ )
    {
        m_aspPLight[i]->Ambient = ColorRGB::SE_RGB_WHITE*0.2f;
        m_aspPLight[i]->Diffuse = ColorRGB::SE_RGB_WHITE;
        m_aspPLight[i]->Specular = ColorRGB::SE_RGB_WHITE;
        m_aspPLight[i]->Linear = 0.02f;
        m_aspPLight[i]->Quadratic = 0.005f;
    }

    // spot lights.
    fValue = 4.0f;
    m_aspSLight[0]->Position = Vector3f(+fValue, +fValue, +fValue);
    m_aspSLight[1]->Position = Vector3f(+fValue, +fValue, -fValue);
    m_aspSLight[2]->Position = Vector3f(+fValue, -fValue, +fValue);
    m_aspSLight[3]->Position = Vector3f(+fValue, -fValue, -fValue);
    m_aspSLight[4]->Position = Vector3f(-fValue, +fValue, +fValue);
    m_aspSLight[5]->Position = Vector3f(-fValue, +fValue, -fValue);
    m_aspSLight[6]->Position = Vector3f(-fValue, -fValue, +fValue);
    m_aspSLight[7]->Position = Vector3f(-fValue, -fValue, -fValue);
    fValue = -Mathf::Sqrt(1.0f/3.0f);
    m_aspSLight[0]->DVector = Vector3f(+fValue, +fValue, +fValue);
    m_aspSLight[1]->DVector = Vector3f(+fValue, +fValue, -fValue);
    m_aspSLight[2]->DVector = Vector3f(+fValue, -fValue, +fValue);
    m_aspSLight[3]->DVector = Vector3f(+fValue, -fValue, -fValue);
    m_aspSLight[4]->DVector = Vector3f(-fValue, +fValue, +fValue);
    m_aspSLight[5]->DVector = Vector3f(-fValue, +fValue, -fValue);
    m_aspSLight[6]->DVector = Vector3f(-fValue, -fValue, +fValue);
    m_aspSLight[7]->DVector = Vector3f(-fValue, -fValue, -fValue);
    for( i = 0; i < 8; i++ )
    {
        m_aspSLight[i]->Diffuse = ColorRGB::SE_RGB_WHITE;
        m_aspSLight[i]->Specular = ColorRGB::SE_RGB_WHITE;
        m_aspSLight[i]->Exponent = 1.0f;
        m_aspSLight[i]->SetAngle(0.125f*Mathf::PI);
    }
}
//----------------------------------------------------------------------------
Node* Lighting2::CreateModel()
{
    // polished gold.
    MaterialState* pGoldMaterial = SE_NEW MaterialState;
    pGoldMaterial->Ambient = ColorRGB(0.24725f, 0.2245f, 0.0645f);
    pGoldMaterial->Diffuse = ColorRGB(0.34615f, 0.3143f, 0.0903f);
    pGoldMaterial->Specular = ColorRGB(0.797357f, 0.723991f, 0.208006f);
    pGoldMaterial->Shininess = 83.2f;

    // polished red.
    MaterialState* pRedMaterial = SE_NEW MaterialState;
    pRedMaterial->Ambient = ColorRGB(0.8f, 0.0f, 0.0f);
    pRedMaterial->Diffuse = ColorRGB(0.8f, 0.0f, 0.0f);
    pRedMaterial->Specular = ColorRGB(1.0f, 1.0f, 1.0f);
    pRedMaterial->Shininess = 83.2f;

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
    pWhiteMaterial->Shininess = 50.0f;

    // polished copper.
    MaterialState* pCopperMaterial = SE_NEW MaterialState;
    pCopperMaterial->Ambient = ColorRGB(0.2295f, 0.08825f, 0.0275f);
    pCopperMaterial->Diffuse = ColorRGB(0.5508f, 0.2118f, 0.066f);
    pCopperMaterial->Specular = ColorRGB(0.580594f, 0.223257f, 0.0695701f);
    pCopperMaterial->Shininess = 51.2f;

    // We apply these texture effects as post-lighting effects,
    // so the src output fragments should be modulated with dst buffer pixels.
    TextureEffect* pTextureRockEffect = SE_NEW TextureEffect("rock");
    AlphaState* pAState = pTextureRockEffect->GetBlending(0);
    pAState->SrcBlend = AlphaState::SBF_DST_COLOR;
    pAState->DstBlend = AlphaState::DBF_ZERO;

    TextureEffect* pTextureWoodEffect = SE_NEW TextureEffect("wood512");
    pAState = pTextureWoodEffect->GetBlending(0);
    pAState->SrcBlend = AlphaState::SBF_DST_COLOR;
    pAState->DstBlend = AlphaState::DBF_ZERO;

    Node* pRoot = SE_NEW Node;

    Attributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetNormalChannels(3);
    tempAttr.SetTCoordChannels(0, 2);

#if defined(SE_USING_OES2)
    Geometry::GeometryLightingMode eLMode = Geometry::GLM_PIPELINE_VERTEX;
#else
    Geometry::GeometryLightingMode eLMode = Geometry::GLM_PIPELINE_PIXEL;
#endif

    float fExtend = 8.0f;
    StandardMesh tempSM(tempAttr);
    // floor.
    TriMesh* pMesh = tempSM.Rectangle(4, 4, fExtend, fExtend);
    pMesh->LightingMode = eLMode;
    pMesh->AttachGlobalState(pWhiteMaterial);
    pMesh->AttachEffect(pTextureWoodEffect);
    pMesh->GenerateNormals();
    Matrix3f mat3fRot;
	mat3fRot.FromEulerAnglesXYZ(Mathf::PI/2.0f, 0.0f, 0.0f);
	pMesh->Local.SetRotate(mat3fRot);
	pRoot->AttachChild(pMesh);

    // far wall.
    pMesh = SE_NEW TriMesh(pMesh->VBuffer, pMesh->IBuffer);
    pMesh->LightingMode = eLMode;
    pMesh->AttachGlobalState(pWhiteMaterial);
    pMesh->AttachEffect(pTextureRockEffect);
    pMesh->GenerateNormals();
    pMesh->Local.SetTranslate(Vector3f(0.0f, fExtend, fExtend));
    pRoot->AttachChild(pMesh);

    // left wall.
    pMesh = SE_NEW TriMesh(pMesh->VBuffer, pMesh->IBuffer);
    pMesh->LightingMode = eLMode;
    pMesh->AttachGlobalState(pWhiteMaterial);
    pMesh->AttachEffect(pTextureRockEffect);
    pMesh->GenerateNormals();
    mat3fRot.FromEulerAnglesXYZ(0.0f, -Mathf::PI/2.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(Vector3f(-fExtend, fExtend, 0.0f));
    pRoot->AttachChild(pMesh);

    // right wall.
    pMesh = SE_NEW TriMesh(pMesh->VBuffer, pMesh->IBuffer);
    pMesh->LightingMode = eLMode;
    pMesh->AttachGlobalState(pWhiteMaterial);
    pMesh->AttachEffect(pTextureRockEffect);
    pMesh->GenerateNormals();
    mat3fRot.FromEulerAnglesXYZ(0.0f, Mathf::PI/2.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(Vector3f(fExtend, fExtend, 0.0f));
    pRoot->AttachChild(pMesh);

    // sphere.
    pMesh = tempSM.Sphere(32, 32, 1.0f);
    pMesh->LightingMode = eLMode;
    pMesh->AttachGlobalState(pGoldMaterial);
    pMesh->GenerateNormals();
    pMesh->Local.SetTranslate(Vector3f(0.0f, 1.0f, 0.0f));
    pRoot->AttachChild(pMesh);

    // cylinder.
    pMesh = tempSM.Cylinder(8, 32, 1.0f, 2.0f, false);
    pMesh->LightingMode = eLMode;
    pMesh->AttachGlobalState(pRedMaterial);
    pMesh->GenerateNormals();
    mat3fRot.FromEulerAnglesXYZ(Mathf::PI/2.0f, 0.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(Vector3f(2.0f, 1.0f, 1.0f));
    pRoot->AttachChild(pMesh);

    // box.
    pMesh = tempSM.Box(0.6f, 0.6f, 0.6f);
    pMesh->LightingMode = eLMode;
    pMesh->AttachGlobalState(pBlueMaterial);
    pMesh->GenerateNormals();
    mat3fRot.FromEulerAnglesXYZ(0.0f, Mathf::PI/3.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(Vector3f(-1.6f, 0.6f, -1.0f));
    pRoot->AttachChild(pMesh);

    // torus.
    pMesh = tempSM.Torus(32, 32, 1.0f, 0.2f);
    pMesh->LightingMode = eLMode;
    pMesh->AttachGlobalState(pCopperMaterial);
    pMesh->GenerateNormals();
    mat3fRot.FromEulerAnglesXYZ(Mathf::PI/2.0f, 0.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(Vector3f(0.0f, 0.2f, 0.0f));
    pRoot->AttachChild(pMesh);

    // tetrahedron.
    pMesh = tempSM.Tetrahedron();
    pMesh->LightingMode = eLMode;
    pMesh->AttachGlobalState(pWhiteMaterial);
    pMesh->GenerateNormals();
    mat3fRot.FromEulerAnglesXYZ(-Mathf::PI/2.0f, 0.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(Vector3f(1.8f, 1.0f/3.0f, -0.8f));
    pRoot->AttachChild(pMesh);

    return (Node*)pRoot;
}
//----------------------------------------------------------------------------
void Lighting2::UpdateEffects()
{
    int i;
    for( i = 0; i < 8; i++ )
    {
        m_acCaption[i] = '.';
    }

    if( m_iLightCount > 0 )
    {
        m_spScene->DetachAllLights();
        char* pcCaption = m_acCaption;
        for( i = 0; i < m_iACount; i++ )
        {
            m_spScene->AttachLight(m_aspALight[i]);
            *pcCaption++ = 'a';
        }
        for( i = 0; i < m_iDCount; i++ )
        {
            m_spScene->AttachLight(m_aspDLight[i]);
            *pcCaption++ = 'd';
        }
        for( i = 0; i < m_iPCount; i++ )
        {
            m_spScene->AttachLight(m_aspPLight[i]);
            *pcCaption++ = 'p';
        }
        for( i = 0; i < m_iSCount; i++ )
        {
            m_spScene->AttachLight(m_aspSLight[i]);
            *pcCaption++ = 's';
        }
    }

    m_spScene->UpdateRS();
    m_iActiveLight = -1;
}
//----------------------------------------------------------------------------