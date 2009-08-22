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

#include "DynamicShader.h"

SE_WINDOW_APPLICATION(DynamicShader);

SE_REGISTER_INITIALIZE(DynamicShader);

//----------------------------------------------------------------------------
DynamicShader::DynamicShader()
    :
    WindowApplication3("DynamicShader", 0, 0, 640, 480, 
        ColorRGBA(0.5f, 0.5f, 0.5f, 1.0f))
{
    m_ImageNames[0] = "random1";
    m_ImageNames[1] = "kate";
    m_ImageNames[2] = "whitecircle";
}
//----------------------------------------------------------------------------
bool DynamicShader::OnInitialize()
{
    if( !WindowApplication3::OnInitialize() )
    {
        return false;
    }

    m_spCamera->SetFrustum(-0.55f, 0.55f, -0.4125f, 0.4125f, 1.0f, 100.0f);
    Vector3f tempCLoc(0.0f, 0.0f, -3.0f);
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
void DynamicShader::OnTerminate()
{
    m_spScene = 0;
    m_spMesh = 0;
    m_spWireframe = 0;
    m_spEffect = 0;
    m_spController = 0;

    WindowApplication3::OnTerminate();
}
//----------------------------------------------------------------------------
void DynamicShader::OnIdle()
{
    MeasureTime();

    if( MoveCamera() )
    {
        m_Culler.ComputeUnculledSet(m_spScene);
    }

    //m_spScene->UpdateGS(System::SE_GetTime());  // inefficient
    m_spController->Update(System::SE_GetTime());

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
bool DynamicShader::OnKeyDown(unsigned char ucKey, int iX, int iY)
{
    if( WindowApplication3::OnKeyDown(ucKey, iX, iY) )
    {
        return true;
    }

    switch( ucKey )
    {
        int iTextureCount;

    case 'w':
    case 'W':
        m_spWireframe->Enabled = !m_spWireframe->Enabled;
        return true;
    case 's':
    case 'S':
        TestStreaming(m_spScene, 128, 128, 640, 480, "DynamicShader.seof");
        return true;
    case '1':
        iTextureCount = 1;
        m_spEffect->SetTextureCount(iTextureCount);
        for( int i = 0; i < iTextureCount; i++ )
        {
            m_spEffect->SetImageName(i, m_ImageNames[i]);
            m_spEffect->SetTextureTypeName(i, "ImageTexture");
        }
        m_spEffect->Configure();
        return true;
    case '2':
        iTextureCount = 2;
        m_spEffect->SetTextureCount(iTextureCount);
        for( int i = 0; i < iTextureCount; i++ )
        {
            m_spEffect->SetImageName(i, m_ImageNames[i]);
            m_spEffect->SetTextureTypeName(i, "ImageTexture");
        }
        m_spEffect->Configure();
        return true;
    case '3':
        iTextureCount = 3;
        m_spEffect->SetTextureCount(iTextureCount);
        for( int i = 0; i < iTextureCount; i++ )
        {
            m_spEffect->SetImageName(i, m_ImageNames[i]);
            m_spEffect->SetTextureTypeName(i, "ImageTexture");
        }
        m_spEffect->Configure();
        return true;
    case '4':
        iTextureCount = 4;
        m_spEffect->SetTextureCount(iTextureCount);
        for( int i = 0; i < iTextureCount - 1; i++ )
        {
            m_spEffect->SetImageName(i, m_ImageNames[i]);
            m_spEffect->SetTextureTypeName(i, "ImageTexture");
        }
        m_spEffect->SetImageName(iTextureCount - 1, "");
        m_spEffect->SetTextureTypeName(iTextureCount - 1, "ConstantTexture");
        m_spEffect->Configure();
    case 'a':
        if( m_spEffect->ConstantColor.X < 1.5f )
        {
            m_spEffect->ConstantColor.X += 0.1f;
            m_spEffect->ConstantColor.Y += 0.1f;
            m_spEffect->ConstantColor.Z += 0.1f;
        }
        return true;
    case 'm':
        if( m_spEffect->ConstantColor.X > 0.0f )
        {
            m_spEffect->ConstantColor.X -= 0.1f;
            m_spEffect->ConstantColor.Y -= 0.1f;
            m_spEffect->ConstantColor.Z -= 0.1f;
        }
        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
void DynamicShader::CreateScene()
{
    m_spScene = SE_NEW Node;
    m_spWireframe = SE_NEW WireframeState;
    m_spScene->AttachGlobalState(m_spWireframe);

    // 创建一个场景中的矩形.
    Attributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetTCoordChannels(0, 2);

    VertexBuffer* pVBuffer = SE_NEW VertexBuffer(tempAttr, 4);
    (*(Vector3f*)pVBuffer->PositionTuple(0)).X = -1.0f;
    (*(Vector3f*)pVBuffer->PositionTuple(0)).Y = -1.0f;
    (*(Vector3f*)pVBuffer->PositionTuple(0)).Z = 0.0f;
    (*(Vector2f*)pVBuffer->TCoordTuple(0, 0)).X = 0.0f;
    (*(Vector2f*)pVBuffer->TCoordTuple(0, 0)).Y = 1.0f;
    (*(Vector3f*)pVBuffer->PositionTuple(1)).X = 1.0f;
    (*(Vector3f*)pVBuffer->PositionTuple(1)).Y = -1.0f;
    (*(Vector3f*)pVBuffer->PositionTuple(1)).Z = 0.0f;
    (*(Vector2f*)pVBuffer->TCoordTuple(0, 1)).X = 1.0f;
    (*(Vector2f*)pVBuffer->TCoordTuple(0, 1)).Y = 1.0f;
    (*(Vector3f*)pVBuffer->PositionTuple(2)).X = 1.0f;
    (*(Vector3f*)pVBuffer->PositionTuple(2)).Y = 1.0f;
    (*(Vector3f*)pVBuffer->PositionTuple(2)).Z = 0.0f;
    (*(Vector2f*)pVBuffer->TCoordTuple(0, 2)).X = 1.0f;
    (*(Vector2f*)pVBuffer->TCoordTuple(0, 2)).Y = 0.0f;
    (*(Vector3f*)pVBuffer->PositionTuple(3)).X = -1.0f;
    (*(Vector3f*)pVBuffer->PositionTuple(3)).Y = 1.0f;
    (*(Vector3f*)pVBuffer->PositionTuple(3)).Z = 0.0f;
    (*(Vector2f*)pVBuffer->TCoordTuple(0, 3)).X = 0.0f;
    (*(Vector2f*)pVBuffer->TCoordTuple(0, 3)).Y = 0.0f;
    IndexBuffer* pIBuffer = SE_NEW Swing::IndexBuffer(6);
    int* pIBufferData = pIBuffer->GetData();
    pIBufferData[0] = 0;
    pIBufferData[1] = 3;
    pIBufferData[2] = 1;
    pIBufferData[3] = 1;
    pIBufferData[4] = 3;
    pIBufferData[5] = 2;

    m_spMesh = SE_NEW TriMesh(pVBuffer, pIBuffer);
    m_spScene->AttachChild(m_spMesh);

    m_spEffect = SE_NEW DynamicMultiTextureEffect(1);
    m_spMesh->AttachEffect(m_spEffect);
    m_spEffect->SetImageName(0, m_ImageNames[0]);
    m_spEffect->SetTextureTypeName(0, "ImageTexture");
    m_spEffect->Configure();

    ConstantColorController* pController = SE_NEW ConstantColorController; 
    m_spEffect->AttachController(pController);
    m_spController = pController;
    pController->Frequency = 5.0;
    pController->MinTime = 0.0;
    pController->MaxTime = 4.0;
    pController->Repeat = Controller::RT_CYCLE;
}
//----------------------------------------------------------------------------
