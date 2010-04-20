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

#include "ParallaxMaps.h"

SE_WINDOW_APPLICATION(ParallaxMaps);

SE_REGISTER_INITIALIZE(ParallaxMaps);

//----------------------------------------------------------------------------
ParallaxMaps::ParallaxMaps()
    :
    SEWindowApplication3("ParallaxMaps", 0, 0, 640, 480, 
        SEColorRGBA(0.5f, 0.5f, 0.5f, 1.0f))
{
    m_fLight0Height = 4.0f;
    m_Light0Color = SEColorRGB::SE_RGB_WHITE;
}
//----------------------------------------------------------------------------
bool ParallaxMaps::OnInitialize()
{
    if( !SEWindowApplication3::OnInitialize() )
    {
        return false;
    }

    m_spCamera->SetFrustum(-0.55f, 0.55f, -0.4125f, 0.4125f, 1.0f, 100.0f);
    SEVector3f tempCLoc(0.0f, 9.0f, -20.0f);
    SEVector3f tempCDir(0.0f, -0.2f, 1.0f);
    tempCDir.Normalize();
    SEVector3f tempCUp(0.0f, 1.0f, 0.0f);
    SEVector3f tempCRight = tempCUp.Cross(tempCDir);
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
void ParallaxMaps::OnTerminate()
{
    m_spScene = 0;
    m_spModelRoot = 0;
    m_spWireframe = 0;
    m_spLight0 = 0;
    m_spLight0Node = 0;

    SEWindowApplication3::OnTerminate();
}
//----------------------------------------------------------------------------
void ParallaxMaps::OnIdle()
{
    // Light0 motion.
    static double dCurTime = 0.0f;
    static double dLastTime = 0.0f;
    static float fAngel0 = 0.0f;
    static float fRadius0 = 4.0f;
    dCurTime = SESystem::SE_GetTime();
    if( dCurTime - dLastTime > 0.0001f )
    {
        dLastTime = dCurTime;
        fAngel0 += 0.002f;
        SEMatrix3f mat3fRot;

        mat3fRot.FromEulerAnglesXYZ(0.0f, -0.002f, 0.0f);
        m_spLight0Node->Local.SetRotate(m_spLight0Node->Local.GetRotate()
            *mat3fRot);
        float fX = fRadius0*SEMathf::Cos(fAngel0);
        float fZ = fRadius0*SEMathf::Sin(fAngel0);
        m_spLight0Node->Local.SetTranslate(SEVector3f(fX, m_fLight0Height, 
            fZ));
        m_spLight0Node->UpdateGS();
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
        m_pRenderer->DrawScene(m_Culler.GetVisibleSet());
        DrawFrameRate(8, GetHeight()-8, SEColorRGBA::SE_RGBA_WHITE);
        m_pRenderer->EndScene();
    }
    m_pRenderer->DisplayBackBuffer();

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool ParallaxMaps::OnKeyDown(unsigned char ucKey, int iX, int iY)
{
    if( SEWindowApplication3::OnKeyDown(ucKey, iX, iY) )
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
    case 's':
    case 'S':
        TestStreaming(m_spScene, 128, 128, 640, 480, "BumpMaps.seof");
        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
void ParallaxMaps::CreateScene()
{
    m_spScene = SE_NEW SENode;
    m_spWireframe = SE_NEW SEWireframeState;
    m_spScene->AttachGlobalState(m_spWireframe);

    CreateModels();
    CreateLights();

    m_spModelRoot->AttachLight(m_spLight0);
    m_spScene->AttachChild(m_spLight0Node);
    m_spScene->AttachChild(m_spModelRoot);

    m_spScene->UpdateGS();
    m_spScene->UpdateRS();
}
//----------------------------------------------------------------------------
void ParallaxMaps::CreateLights()
{
    // Create light0(point light).
    m_spLight0 = SE_NEW SELight(SELight::LT_POINT);
    m_spLight0->Ambient = m_Light0Color*0.5f;
    m_spLight0->Diffuse = m_Light0Color;
    m_spLight0->Specular = m_Light0Color*0.5f;
    m_spLight0->Linear = 0.02f;
    m_spLight0->Quadratic = 0.02f;

    // Create light0's node.
    m_spLight0Node = SE_NEW SELightNode(m_spLight0);
    m_spLight0Node->Local.SetTranslate(SEVector3f(0.0f, m_fLight0Height, 
        0.0f));

    // Create a sphere to represent the light0's source.
    SEAttributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetColorChannels(0, 3);
    float fRadius = 0.2f;
    SETriMesh* pPLightSphere = SEStandardMesh(tempAttr).Sphere(8, 8, fRadius);
    m_spLight0Node->AttachChild(pPLightSphere);
    SEVertexBuffer* pVBuffer = pPLightSphere->VBuffer;
    int iVCount = pVBuffer->GetVertexCount();
    for( int i = 0; i < iVCount; i++ )
    {
        pVBuffer->Color3(0, i) = m_Light0Color;
    }
    SEVertexColor3Effect* pLightSphereEffect = SE_NEW SEVertexColor3Effect;
    pPLightSphere->AttachEffect(pLightSphereEffect);
}
//----------------------------------------------------------------------------
void ParallaxMaps::CreateModels()
{
    // polished gold.
    SEMaterialState* pGoldMaterial = SE_NEW SEMaterialState;
    pGoldMaterial->Ambient = SEColorRGB(0.24725f, 0.2245f, 0.0645f);
    pGoldMaterial->Diffuse = SEColorRGB(0.34615f, 0.3143f, 0.0903f);
    pGoldMaterial->Specular = SEColorRGB(0.797357f, 0.723991f, 0.208006f);
    pGoldMaterial->Shininess = 83.2f;

    // polished red.
    SEMaterialState* pRedMaterial = SE_NEW SEMaterialState;
    pRedMaterial->Ambient = SEColorRGB(0.8f, 0.0f, 0.0f);
    pRedMaterial->Diffuse = SEColorRGB(0.8f, 0.0f, 0.0f);
    pRedMaterial->Specular = SEColorRGB(1.0f, 1.0f, 1.0f);
    pRedMaterial->Shininess = 83.2f;

    // polished blue.
    SEMaterialState* pBlueMaterial = SE_NEW SEMaterialState;
    pBlueMaterial->Ambient = SEColorRGB(0.0f, 0.0f, 0.8f);
    pBlueMaterial->Diffuse = SEColorRGB(0.0f, 0.0f, 0.8f);
    pBlueMaterial->Specular = SEColorRGB(1.0f, 1.0f, 1.0f);
    pBlueMaterial->Shininess = 83.2f;

    // polished white.
    SEMaterialState* pWhiteMaterial = SE_NEW SEMaterialState;
    pWhiteMaterial->Ambient = SEColorRGB(0.2f, 0.2f, 0.2f);
    pWhiteMaterial->Diffuse = SEColorRGB(0.8f, 0.8f, 0.8f);
    pWhiteMaterial->Specular = SEColorRGB(1.0f, 1.0f, 1.0f);
    pWhiteMaterial->Shininess = 100.0f;

    // polished copper.
    SEMaterialState* pCopperMaterial = SE_NEW SEMaterialState;
    pCopperMaterial->Ambient = SEColorRGB(0.2295f, 0.08825f, 0.0275f);
    pCopperMaterial->Diffuse = SEColorRGB(0.5508f, 0.2118f, 0.066f);
    pCopperMaterial->Specular = SEColorRGB(0.580594f, 0.223257f, 0.0695701f);
    pCopperMaterial->Shininess = 51.2f;

    // We apply this texture effect as a post-lighting effect,
    // so the src output fragments should be modulated with dst buffer pixels.
    SETextureEffect* pTextureWoodEffect = SE_NEW SETextureEffect("wood512");
    SEAlphaState* pAState = pTextureWoodEffect->GetBlending(0);
    pAState->SrcBlend = SEAlphaState::SBF_DST_COLOR;
    pAState->DstBlend = SEAlphaState::DBF_ZERO;

    // We apply this parallax map effect as a lighting effect,
    // When UpdateRS is called, geometry object's default lighting effect will
    // be replaced by the parallax map effect.
    SEParallaxMapL1Effect* pParallaxMapRockEffect = 
        SE_NEW SEParallaxMapL1Effect("rock", "rocknormal", "rockheight");

    SENode* pRoot = SE_NEW SENode;

    SEAttributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetNormalChannels(3);
    tempAttr.SetTCoordChannels(0, 2);

#if defined(SE_USING_OES2)
    SEGeometry::GeometryLightingMode eLMode = SEGeometry::GLM_PIPELINE_VERTEX;
#else
    SEGeometry::GeometryLightingMode eLMode = SEGeometry::GLM_PIPELINE_PIXEL;
#endif

    float fExtend = 8.0f;
    SEStandardMesh tempSM(tempAttr);
    // floor.
    SETriMesh* pMesh = tempSM.Rectangle(4, 4, fExtend, fExtend);
    pMesh->LightingMode = eLMode;
    pMesh->AttachGlobalState(pWhiteMaterial);
    pMesh->AttachEffect(pTextureWoodEffect);
    pMesh->GenerateNormals();
    pMesh->GenerateTangents(0, 1, 2);
    SEMatrix3f mat3fRot;
    mat3fRot.FromEulerAnglesXYZ(SEMathf::PI/2.0f, 0.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pRoot->AttachChild(pMesh);

    // far wall.
    pMesh = SE_NEW SETriMesh(pMesh->VBuffer, pMesh->IBuffer);
    pMesh->LightingMode = SEGeometry::GLM_USER;
    pMesh->AttachGlobalState(pWhiteMaterial);
    pMesh->AttachEffect(pParallaxMapRockEffect);
    pMesh->Local.SetTranslate(SEVector3f(0.0f, fExtend, fExtend));
    pRoot->AttachChild(pMesh);

    // left wall.
    pMesh = SE_NEW SETriMesh(pMesh->VBuffer, pMesh->IBuffer);
    pMesh->LightingMode = SEGeometry::GLM_USER;
    pMesh->AttachGlobalState(pWhiteMaterial);
    pMesh->AttachEffect(pParallaxMapRockEffect);
    mat3fRot.FromEulerAnglesXYZ(0.0f, -SEMathf::PI/2.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(SEVector3f(-fExtend, fExtend, 0.0f));
    pRoot->AttachChild(pMesh);

    // right wall.
    pMesh = SE_NEW SETriMesh(pMesh->VBuffer, pMesh->IBuffer);
    pMesh->LightingMode = SEGeometry::GLM_USER;
    pMesh->AttachGlobalState(pWhiteMaterial);
    pMesh->AttachEffect(pParallaxMapRockEffect);
    mat3fRot.FromEulerAnglesXYZ(0.0f, SEMathf::PI/2.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(SEVector3f(fExtend, fExtend, 0.0f));
    pRoot->AttachChild(pMesh);

    // sphere.
    pMesh = tempSM.Sphere(32, 32, 1.0f);
    pMesh->LightingMode = eLMode;
    pMesh->AttachGlobalState(pGoldMaterial);
    pMesh->GenerateNormals();
    pMesh->Local.SetTranslate(SEVector3f(0.0f, 1.0f, 0.0f));
    pRoot->AttachChild(pMesh);

    // cylinder.
    pMesh = tempSM.Cylinder(8, 32, 1.0f, 2.0f, false);
    pMesh->LightingMode = eLMode;
    pMesh->AttachGlobalState(pRedMaterial);
    pMesh->GenerateNormals();
    mat3fRot.FromEulerAnglesXYZ(SEMathf::PI/2.0f, 0.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(SEVector3f(2.0f, 1.0f, 1.0f));
    pRoot->AttachChild(pMesh);

    // box.
    pMesh = tempSM.Box(0.6f, 0.6f, 0.6f);
    pMesh->LightingMode = eLMode;
    pMesh->AttachGlobalState(pBlueMaterial);
    pMesh->GenerateNormals();
    mat3fRot.FromEulerAnglesXYZ(0.0f, SEMathf::PI/3.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(SEVector3f(-1.6f, 0.6f, -1.0f));
    pRoot->AttachChild(pMesh);

    // torus.
    pMesh = tempSM.Torus(32, 32, 1.0f, 0.2f);
    pMesh->LightingMode = eLMode;
    pMesh->AttachGlobalState(pCopperMaterial);
    pMesh->GenerateNormals();
    mat3fRot.FromEulerAnglesXYZ(SEMathf::PI/2.0f, 0.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(SEVector3f(0.0f, 0.2f, 0.0f));
    pRoot->AttachChild(pMesh);

    // tetrahedron.
    pMesh = tempSM.Tetrahedron();
    pMesh->LightingMode = eLMode;
    pMesh->AttachGlobalState(pWhiteMaterial);
    pMesh->GenerateNormals();
    mat3fRot.FromEulerAnglesXYZ(-SEMathf::PI/2.0f, 0.0f, 0.0f);
    pMesh->Local.SetRotate(mat3fRot);
    pMesh->Local.SetTranslate(SEVector3f(1.8f, 1.0f/3.0f, -0.8f));
    pRoot->AttachChild(pMesh);

    m_spModelRoot = pRoot;
}
//----------------------------------------------------------------------------