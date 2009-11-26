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

#include "Lighting.h"

SE_WINDOW_APPLICATION(Lighting);

SE_REGISTER_INITIALIZE(Lighting);

//----------------------------------------------------------------------------
Lighting::Lighting()
    :
    WindowApplication3("Lighting", 0, 0, 640, 480, 
        ColorRGBA(0.5f, 0.5f, 0.5f, 1.0f))
{
    m_fLight0Height = 4.0f;
    m_fLight1Height = 4.0f;
    m_Light0Color = ColorRGB::SE_RGB_GREEN;
    m_Light1Color = ColorRGB::SE_RGB_RED;
}
//----------------------------------------------------------------------------
bool Lighting::OnInitialize()
{
    if( !WindowApplication3::OnInitialize() )
    {
        return false;
    }

    m_spCamera->SetFrustum(-0.55f, 0.55f, -0.4125f, 0.4125f, 1.0f, 100.0f);
    Vector3f tempCLoc(0.0f, 9.0f, -20.0f);
    Vector3f tempCDir(0.0f, -0.2f, 1.0f);
    tempCDir.Normalize();
    Vector3f tempCUp(0.0f, 1.0f, 0.0f);
    Vector3f tempCRight = tempCUp.Cross(tempCDir);
    tempCRight.Normalize();
    tempCUp = tempCDir.Cross(tempCRight);
    tempCUp.Normalize();
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

    return true;
}
//----------------------------------------------------------------------------
void Lighting::OnTerminate()
{
    m_spScene = 0;
    m_spModelRoot = 0;
    m_spWireframe = 0;
    m_spLight0 = 0;
    m_spLight0Node = 0;
    m_spLight1 = 0;
    m_spLight1Node = 0;

    WindowApplication3::OnTerminate();
}
//----------------------------------------------------------------------------
void Lighting::OnIdle()
{
    // Lights motion.
    static double dCurTime = 0.0;
    static double dLastTime = 0.0;
    static double dDiffTime = 0.0;
    static float fAngel0 = 0.0f;
    static float fAngel0Speed = 2.0f;
    static float fRadius0 = 4.0f;
    static float fAngel1 = Mathf::PI;
    static float fAngel1Speed = 2.0f;
    static float fRadius1 = 4.0f;
    dCurTime = System::SE_GetTime();
    dDiffTime = dCurTime - dLastTime;
    dLastTime = dCurTime;
    fAngel0 +=fAngel0Speed*(float)dDiffTime;
    fAngel1 -= fAngel1Speed*(float)dDiffTime;
    Matrix3f mat3fRot;
    mat3fRot.FromEulerAnglesXYZ(0.0f, -fAngel0Speed, 0.0f);
    m_spLight0Node->Local.SetRotate(m_spLight0Node->Local.GetRotate()
        *mat3fRot);
    float fX = fRadius0*Mathf::Cos(fAngel0);
    float fZ = fRadius0*Mathf::Sin(fAngel0);
    m_spLight0Node->Local.SetTranslate(Vector3f(fX, m_fLight0Height, fZ));
    m_spLight0Node->UpdateGS();
    mat3fRot.FromEulerAnglesXYZ(0.0f, fAngel1Speed, 0.0f);
    m_spLight1Node->Local.SetRotate(m_spLight1Node->Local.GetRotate()
        *mat3fRot);
    fX = fRadius1*Mathf::Cos(fAngel1);
    fZ = fRadius1*Mathf::Sin(fAngel1);
    m_spLight1Node->Local.SetTranslate(Vector3f(fX, m_fLight1Height, fZ));
    m_spLight1Node->UpdateGS();

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
        DrawFrameRate(8, GetHeight()-8, ColorRGBA::SE_RGBA_WHITE);
        m_pRenderer->EndScene();
    }
    m_pRenderer->DisplayBackBuffer();

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool Lighting::OnKeyDown(unsigned char ucKey, int iX, int iY)
{
    if( WindowApplication3::OnKeyDown(ucKey, iX, iY) )
    {
        return true;
    }

    if( ucKey == 'w' || ucKey == 'W' )
    {
        m_spWireframe->Enabled = !m_spWireframe->Enabled;
        return true;
    }

    switch( ucKey )
    {
    case 'v':
    case 'V':
        TestStreaming(m_spScene, 128, 128, 640, 480, "Lighting.seof");
        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
void Lighting::CreateScene()
{
    m_spScene = SE_NEW Node;
    m_spWireframe = SE_NEW WireframeState;
    m_spScene->AttachGlobalState(m_spWireframe);

    CreateLights();
    CreateModels();

    m_spModelRoot->AttachLight(m_spLight0);
    m_spModelRoot->AttachLight(m_spLight1);
    m_spScene->AttachChild(m_spLight0Node);
    m_spScene->AttachChild(m_spLight1Node);
    m_spScene->AttachChild(m_spModelRoot);

    m_spScene->UpdateGS();
    m_spScene->UpdateRS();
}
//----------------------------------------------------------------------------
void Lighting::CreateLights()
{
    // Create light0(point light).
    m_spLight0 = SE_NEW Light(Light::LT_POINT);
    m_spLight0->Ambient = m_Light0Color*0.5f;
    m_spLight0->Diffuse = m_Light0Color;
    m_spLight0->Specular = m_Light0Color*0.5f;
    m_spLight0->Linear = 0.02f;
    m_spLight0->Quadratic = 0.02f;

    // Create light0's node.
    m_spLight0Node = SE_NEW LightNode(m_spLight0);
    m_spLight0Node->Local.SetTranslate(Vector3f(0.0f, m_fLight0Height, 0.0f));

    // Create a sphere to represent the light0's source.
    Attributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetColorChannels(0, 3);
    float fRadius = 0.2f;
    TriMesh* pPLightSphere = StandardMesh(tempAttr).Sphere(8, 8, fRadius);
    m_spLight0Node->AttachChild(pPLightSphere);
    VertexBuffer* pVBuffer = pPLightSphere->VBuffer;
    int iVCount = pVBuffer->GetVertexCount();
    for( int i = 0; i < iVCount; i++ )
    {
        pVBuffer->Color3(0, i) = m_Light0Color;
    }
    VertexColor3Effect* pLightSphereEffect = SE_NEW VertexColor3Effect;
    pPLightSphere->AttachEffect(pLightSphereEffect);

    // Create light1(point light).
    m_spLight1 = SE_NEW Light(Light::LT_POINT);
    m_spLight1->Ambient = m_Light1Color*0.5f;
    m_spLight1->Diffuse = m_Light1Color;
    m_spLight1->Specular = m_Light1Color*0.5f;
    m_spLight1->Linear = 0.02f;
    m_spLight1->Quadratic = 0.02f;

    // Create light1's node.
    m_spLight1Node = SE_NEW LightNode(m_spLight1);
    m_spLight1Node->Local.SetTranslate(Vector3f(0.0f, m_fLight1Height, 0.0f));

    // Create a sphere to represent the light1's source.
    pPLightSphere = StandardMesh(tempAttr).Sphere(8, 8, fRadius);
    m_spLight1Node->AttachChild(pPLightSphere);
    pVBuffer = pPLightSphere->VBuffer;
    iVCount = pVBuffer->GetVertexCount();
    for( int i = 0; i < iVCount; i++ )
    {
        pVBuffer->Color3(0, i) = m_Light1Color;
    }
    pPLightSphere->AttachEffect(pLightSphereEffect);
}
//----------------------------------------------------------------------------
void Lighting::CreateModels()
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

    m_spModelRoot = pRoot;
}
//----------------------------------------------------------------------------