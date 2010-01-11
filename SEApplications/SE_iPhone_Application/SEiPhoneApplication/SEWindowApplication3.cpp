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

#include "SEiPhoneApplicationPCH.h"
#include "SEWindowApplication3.h"

using namespace Swing;

//----------------------------------------------------------------------------
WindowApplication3::WindowApplication3(const char* acWindowTitle,
    int iXPosition, int iYPosition, int iWidth, int iHeight,
    const ColorRGBA& rBackgroundColor)
    :
    WindowApplication(acWindowTitle, iXPosition, iYPosition, iWidth, iHeight,
        rBackgroundColor)
{
    // Camera motion.
    m_aWorldAxis[0] = Vector3f::ZERO;
    m_aWorldAxis[1] = Vector3f::ZERO;
    m_aWorldAxis[2] = Vector3f::ZERO;
    m_fTrnSpeed = 0.0f;
    m_fRotSpeed = 0.0f;
    m_bUArrowPressed = false;
    m_bDArrowPressed = false;
    m_bLArrowPressed = false;
    m_bRArrowPressed = false;
    m_bPgUpPressed = false;
    m_bPgDnPressed = false;
    m_bHomePressed = false;
    m_bEndPressed = false;
    m_bCameraMoveable = false;

    // Object motion.
    m_iDoRoll = 0;
    m_iDoYaw = 0;
    m_iDoPitch = 0;
    m_spMotionObject = 0;
    m_fXTrack0 = 0.0f;
    m_fYTrack0 = 0.0f;
    m_fXTrack1 = 0.0f;
    m_fYTrack1 = 0.0f;
    m_bUseTrackBall = true;
    m_bTrackBallDown = false;

    // Performance test.
    m_dLastTime = -1.0;
    m_dAccumulatedTime = 0.0;
    m_dFrameRate = 0.0;
    m_iFrameCount = 0;
    m_iAccumulatedFrameCount = 0;
    m_iTimer = 30;
    m_iMaxTimer = 30;

    // World axis showing stuff.
    m_Origin = Vector3f::ZERO;
    m_XEnd = Vector3f::UNIT_X;
    m_YEnd = Vector3f::UNIT_Y;
    m_ZEnd = Vector3f::UNIT_Z;
    m_fT = 1.0f;
}
//----------------------------------------------------------------------------
WindowApplication3::~WindowApplication3()
{
}
//----------------------------------------------------------------------------
bool WindowApplication3::OnInitialize()
{
    if( !WindowApplication::OnInitialize() )
    {
        return false;
    }

    m_spCamera = SE_NEW Camera;
    m_pRenderer->SetCamera(m_spCamera);
    m_spMotionObject = 0;

    m_spListener = SE_NEW Listener;
    m_pAudioRenderer->SetListener(m_spListener);

    Attributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetColorChannels(0, 3);
    VertexBuffer* pVBuffer = SE_NEW VertexBuffer(tempAttr, 6);
    (*(Vector3f*)pVBuffer->PositionTuple(0)) = m_Origin;
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 0)) = ColorRGB::SE_RGB_RED;
    (*(Vector3f*)pVBuffer->PositionTuple(1)) = m_XEnd;
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 1)) = ColorRGB::SE_RGB_RED;
    (*(Vector3f*)pVBuffer->PositionTuple(2)) = m_Origin;
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 2)) = ColorRGB::SE_RGB_GREEN;  
    (*(Vector3f*)pVBuffer->PositionTuple(3)) = m_YEnd;
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 3)) = ColorRGB::SE_RGB_GREEN;
    (*(Vector3f*)pVBuffer->PositionTuple(4)) = m_Origin;
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 4)) = ColorRGB::SE_RGB_BLUE;
    (*(Vector3f*)pVBuffer->PositionTuple(5)) = m_ZEnd;
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 5)) = ColorRGB::SE_RGB_BLUE;
    m_spWorldAxis = SE_NEW Polyline(pVBuffer, false, false);

    VertexColor3Effect* pEffect = SE_NEW VertexColor3Effect;
    m_spWorldAxis->AttachEffect(pEffect);

    return true;
}
//----------------------------------------------------------------------------
void WindowApplication3::OnTerminate()
{
    m_pRenderer->SetCamera(0);
    m_spCamera = 0;
    m_spMotionObject = 0;
    m_spWorldAxis = 0;

    m_pAudioRenderer->SetListener(0);
    m_spListener = 0;

    WindowApplication::OnTerminate();
}
//----------------------------------------------------------------------------
void WindowApplication3::OnDisplay()
{
    if( m_pRenderer )
    {
        OnIdle();
    }
}
//----------------------------------------------------------------------------
void WindowApplication3::OnTouchBegan(int iX, int iY)
{
    if( !m_bUseTrackBall || !m_spMotionObject )
    {
        return;
    }

    float fMult = 1.0f / (m_iWidth >= m_iHeight ? m_iHeight : m_iWidth);

    // Get trackball drag's beginning point.
    m_bTrackBallDown = true;
    m_SaveRotate = m_spMotionObject->Local.GetRotate();
    m_fXTrack0 = (2*iX - m_iWidth)*fMult;
    m_fYTrack0 = (2*(m_iHeight - 1 - iY) - m_iHeight)*fMult;
}
//----------------------------------------------------------------------------
void WindowApplication3::OnTouchMoved(int iX, int iY)
{
    if( !m_bUseTrackBall || !m_bTrackBallDown || !m_spMotionObject )
    {
        return;
    }

    // Get trackball drag's ending point.
    float fMult = 1.0f / (m_iWidth >= m_iHeight ? m_iHeight : m_iWidth);
    m_fXTrack1 = (2*iX - m_iWidth)*fMult;
    m_fYTrack1 = (2*(m_iHeight - 1 - iY) - m_iHeight)*fMult;

    // Update object's local transformation.
    RotateTrackBall(m_fXTrack0, m_fYTrack0, m_fXTrack1, m_fYTrack1);
}
//----------------------------------------------------------------------------
void WindowApplication3::OnTouchEnded(int, int)
{
    m_bTrackBallDown = false;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Camera motion.
//----------------------------------------------------------------------------
void WindowApplication3::InitializeCameraMotion(float fTrnSpeed,
    float fRotSpeed, float fTrnSpeedFactor, float fRotSpeedFactor)
{
    m_bCameraMoveable = true;

    m_fTrnSpeed = fTrnSpeed;
    m_fRotSpeed = fRotSpeed;
    m_fTrnSpeedFactor = fTrnSpeedFactor;
    m_fRotSpeedFactor = fRotSpeedFactor;

    m_aWorldAxis[0] = m_spCamera->GetRVector();
    m_aWorldAxis[1] = m_spCamera->GetUVector();
    m_aWorldAxis[2] = m_spCamera->GetDVector();
}
//----------------------------------------------------------------------------
bool WindowApplication3::MoveCamera()
{
    if( !m_bCameraMoveable )
    {
        return false;
    }

    bool bMoved = false;

    if( m_bUArrowPressed )
    {
        MoveForward();
        bMoved = true;
    }

    if( m_bDArrowPressed )
    {
        MoveBackward();
        bMoved = true;
    }

    if( m_bHomePressed )
    {
        MoveUp();
        bMoved = true;
    }

    if( m_bEndPressed )
    {
        MoveDown();
        bMoved = true;
    }

    if( m_bLArrowPressed )
    {
        TurnLeft();
        bMoved = true;
    }

    if( m_bRArrowPressed )
    {
        TurnRight();
        bMoved = true;
    }

    if( m_bPgUpPressed )
    {
        LookUp();
        bMoved = true;
    }

    if( m_bPgDnPressed )
    {
        LookDown();
        bMoved = true;
    }

    return bMoved;
}
//----------------------------------------------------------------------------
void WindowApplication3::MoveForward()
{
    Vector3f vec3fLoc = m_spCamera->GetLocation();
    vec3fLoc += m_fTrnSpeed * m_aWorldAxis[2]; // 沿D轴方向前进
    m_spCamera->SetLocation(vec3fLoc);
    m_spListener->SetLocation(vec3fLoc);
}
//----------------------------------------------------------------------------
void WindowApplication3::MoveBackward()
{
    Vector3f vec3fLoc = m_spCamera->GetLocation();
    vec3fLoc -= m_fTrnSpeed * m_aWorldAxis[2]; // 沿D轴方向后退
    m_spCamera->SetLocation(vec3fLoc);
    m_spListener->SetLocation(vec3fLoc);
}
//----------------------------------------------------------------------------
void WindowApplication3::MoveUp()
{
    Vector3f vec3fLoc = m_spCamera->GetLocation();
    vec3fLoc += m_fTrnSpeed * m_aWorldAxis[1]; // 沿U轴方向上升
    m_spCamera->SetLocation(vec3fLoc);
    m_spListener->SetLocation(vec3fLoc);
}
//----------------------------------------------------------------------------
void WindowApplication3::MoveDown()
{
    Vector3f vec3fLoc = m_spCamera->GetLocation();
    vec3fLoc -= m_fTrnSpeed * m_aWorldAxis[1]; // 沿U轴方向下降
    m_spCamera->SetLocation(vec3fLoc);
    m_spListener->SetLocation(vec3fLoc);
}
//----------------------------------------------------------------------------
void WindowApplication3::TurnLeft()
{
    Matrix3f mat3fIncr(m_aWorldAxis[1], -m_fRotSpeed);
    m_aWorldAxis[0] = m_aWorldAxis[0] * mat3fIncr; // R轴绕U轴向左旋转
    m_aWorldAxis[2] = m_aWorldAxis[2] * mat3fIncr; // D轴绕U轴向左旋转

    // 更新摄像机RUD轴.
    Vector3f tempRVector = m_spCamera->GetRVector() * mat3fIncr;
    Vector3f tempUVector = m_spCamera->GetUVector() * mat3fIncr;
    Vector3f tempDVector = m_spCamera->GetDVector() * mat3fIncr;
    m_spCamera->SetAxes(tempRVector, tempUVector, tempDVector);

    // 更新listener RUD轴.
    m_spListener->SetAxes(tempRVector, tempUVector, tempDVector);
}
//----------------------------------------------------------------------------
void WindowApplication3::TurnRight()
{
    Matrix3f mat3fIncr(m_aWorldAxis[1], +m_fRotSpeed);
    m_aWorldAxis[0] = m_aWorldAxis[0] * mat3fIncr; // R轴绕U轴向右旋转
    m_aWorldAxis[2] = m_aWorldAxis[2] * mat3fIncr; // D轴绕U轴向右旋转

    // 更新摄像机RUD轴.
    Vector3f tempRVector = m_spCamera->GetRVector() * mat3fIncr;
    Vector3f tempUVector = m_spCamera->GetUVector() * mat3fIncr;
    Vector3f tempDVector = m_spCamera->GetDVector() * mat3fIncr;
    m_spCamera->SetAxes(tempRVector, tempUVector, tempDVector);

    // 更新listener RUD轴.
    m_spListener->SetAxes(tempRVector, tempUVector, tempDVector);
}
//----------------------------------------------------------------------------
void WindowApplication3::LookUp()
{
    Matrix3f mat3fIncr(m_aWorldAxis[0], -m_fRotSpeed);

    // 更新摄像机RUD轴.
    Vector3f tempRVector = m_spCamera->GetRVector() * mat3fIncr;
    Vector3f tempUVector = m_spCamera->GetUVector() * mat3fIncr;
    Vector3f tempDVector = m_spCamera->GetDVector() * mat3fIncr;
    m_spCamera->SetAxes(tempRVector, tempUVector, tempDVector);

    // 更新listener RUD轴.
    m_spListener->SetAxes(tempRVector, tempUVector, tempDVector);
}
//----------------------------------------------------------------------------
void WindowApplication3::LookDown()
{
    Matrix3f mat3fIncr(m_aWorldAxis[0], +m_fRotSpeed);

    // 更新摄像机RUD轴.
    Vector3f tempRVector = m_spCamera->GetRVector() * mat3fIncr;
    Vector3f tempUVector = m_spCamera->GetUVector() * mat3fIncr;
    Vector3f tempDVector = m_spCamera->GetDVector() * mat3fIncr;
    m_spCamera->SetAxes(tempRVector, tempUVector, tempDVector);

    // 更新listener RUD轴.
    m_spListener->SetAxes(tempRVector, tempUVector, tempDVector);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Object motion.
//----------------------------------------------------------------------------
void WindowApplication3::InitializeObjectMotion(Spatial* pMotionObject)
{
    m_spMotionObject = pMotionObject;
}
//----------------------------------------------------------------------------
bool WindowApplication3::MoveObject()
{
    // 旋转变换针对的是对象的父节点的坐标系,如果对象父节点非空的话.
    // 其世界旋转变换矩阵是R,R的3列构成了一组坐标轴.
    // 0列为"right",1列为"up",2列为"direction".
    // 如果对象没有父节点,则使用世界体系坐标轴,
    // 此时旋转矩阵是一个单位矩阵I,
    // 0列(1,0,0)为"right",1列(0,1,0)为"up",2列(0,0,1)为"direction".
    // 这个选择与Camera和Light类中的旋转变换的选择是一致的.
    //
    // Yaw针对"up"轴,Pitch针对"right"轴,Roll针对"direction"轴.

    if( !m_bCameraMoveable || !m_spMotionObject )
    {
        return false;
    }

    // 检查对象是否已经被virtual trackball移动过.
    if( m_bTrackBallDown )
    {
        return true;
    }

    // 检查对象是否已经被功能键移动过.
    Spatial* pParent = m_spMotionObject->GetParent();
    Vector3f vec3fAxis;
    float fAngle;
    Matrix3f mat3fRot, mat3fIncr;

    if( m_iDoPitch ) // 针对R轴
    {
        mat3fRot = m_spMotionObject->Local.GetRotate();

        fAngle = m_iDoPitch * m_fRotSpeed;
        if( pParent )
        {
            pParent->World.GetRotate().GetRow(0, vec3fAxis);
        }
        else
        {
            vec3fAxis = Vector3f::UNIT_X;
        }

        mat3fIncr.FromAxisAngle(vec3fAxis, fAngle);
        mat3fRot = mat3fRot * mat3fIncr;
        mat3fRot.Orthonormalize();
        m_spMotionObject->Local.SetRotate(mat3fRot);

        return true;
    }

    if( m_iDoYaw ) // 针对U轴
    {
        mat3fRot = m_spMotionObject->Local.GetRotate();

        fAngle = m_iDoYaw * m_fRotSpeed;
        if( pParent )
        {
            pParent->World.GetRotate().GetRow(1, vec3fAxis);
        }
        else
        {
            vec3fAxis = Vector3f::UNIT_Y;
        }

        mat3fIncr.FromAxisAngle(vec3fAxis, fAngle);
        mat3fRot = mat3fRot * mat3fIncr;
        mat3fRot.Orthonormalize();
        m_spMotionObject->Local.SetRotate(mat3fRot);

        return true;
    }

    if( m_iDoRoll ) // 针对D轴
    {
        mat3fRot = m_spMotionObject->Local.GetRotate();

        fAngle = m_iDoRoll * m_fRotSpeed;
        if( pParent )
        {
            pParent->World.GetRotate().GetRow(2, vec3fAxis);
        }
        else
        {
            vec3fAxis = Vector3f::UNIT_Z;
        }

        mat3fIncr.FromAxisAngle(vec3fAxis, fAngle);
        mat3fRot = mat3fRot * mat3fIncr;
        mat3fRot.Orthonormalize();
        m_spMotionObject->Local.SetRotate(mat3fRot);

        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
void WindowApplication3::RotateTrackBall(float fX0, float fY0, float fX1,
    float fY1)
{
    if( !m_spCamera )
    {
        return;
    }

    Matrix3f mat3fTrackRotate;
    if( !m_spCamera->GetTrackBallRotate(fX0, fY0, fX1, fY1, mat3fTrackRotate) )
    {
        return;
    }

    // 计算出新的对象local旋转变换.
    // 如果对象是scene的根节点,则新local旋转变换就是在旧有local旋转变换基础上,
    // 进一步施加刚刚算出的增量旋转变换,成为Rlocal' = Rlocal*Rincremental.
    // 如果对象不是scene的根节点,则必须通过一系列针对对象父节点的基变换,
    // 使新local旋转变换成为:Rlocal' = Rlocal*Rparent*Rincremental*(Rparent^T).
    const Spatial* pParent = m_spMotionObject->GetParent();
    Matrix3f mat3fLocalRot;
    if( pParent )
    {
        const Matrix3f& rPRotate = pParent->World.GetRotate();
        Matrix3f mat3fPRotateT;
        rPRotate.GetTranspose(mat3fPRotateT);
        mat3fLocalRot = m_SaveRotate * rPRotate * mat3fTrackRotate * mat3fPRotateT;
    }
    else
    {
        mat3fLocalRot = m_SaveRotate * mat3fTrackRotate;
    }
    mat3fLocalRot.Orthonormalize();
    m_spMotionObject->Local.SetRotate(mat3fLocalRot);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Performance test.
//----------------------------------------------------------------------------
void WindowApplication3::ResetTime()
{
    m_dLastTime = -1.0f;
}
//----------------------------------------------------------------------------
void WindowApplication3::MeasureTime()
{
    // 开始性能测试.
    if( m_dLastTime == -1.0 )
    {
        m_dLastTime = System::SE_GetTime();
        m_dAccumulatedTime = 0.0;
        m_dFrameRate = 0.0;
        m_iFrameCount = 0;
        m_iAccumulatedFrameCount = 0;
        m_iTimer = m_iMaxTimer;
    }

    // 定时积累m_dAccumulatedTime,m_iAccumulatedFrameCount.
    if( --m_iTimer == 0 )
    {
        double dCurrentTime = System::SE_GetTime();
        double dDelta = dCurrentTime - m_dLastTime;
        m_dLastTime = dCurrentTime;
        m_dAccumulatedTime += dDelta;
        m_iAccumulatedFrameCount += m_iFrameCount;
        m_iFrameCount = 0;
        m_iTimer = m_iMaxTimer;
    }
}
//----------------------------------------------------------------------------
void WindowApplication3::UpdateFrameCount()
{
    m_iFrameCount++;
}
//----------------------------------------------------------------------------
void WindowApplication3::DrawFrameRate(int iX, int iY, const ColorRGBA& rColor)
{
    if( m_dAccumulatedTime > 0.0 )
    {
        m_dFrameRate = m_iAccumulatedFrameCount / m_dAccumulatedTime;
    }
    else
    {
        m_dFrameRate = 0.0;
    }

    const size_t uiSize = 256;
    char acMessage[uiSize];
    System::SE_Sprintf(acMessage, uiSize, "fps: %.1lf", m_dFrameRate);
    m_pRenderer->Draw(iX, iY, rColor, acMessage);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// World axis showing stuff.
//----------------------------------------------------------------------------
void WindowApplication3::DrawWorldAxis(void)
{
    m_pRenderer->Draw(m_spWorldAxis);
    m_pRenderer->Draw(m_iXEndScreenX + 2, m_iXEndScreenY - 2, 
        ColorRGBA::SE_RGBA_RED, "x");
    m_pRenderer->Draw(m_iYEndScreenX + 2, m_iYEndScreenY - 2, 
        ColorRGBA::SE_RGBA_GREEN, "y");
    m_pRenderer->Draw(m_iZEndScreenX + 2, m_iZEndScreenY - 2, 
        ColorRGBA::SE_RGBA_BLUE, "z");
}
//----------------------------------------------------------------------------
void WindowApplication3::SetOriginScreenPos(int iX, int iY, float fT)
{
    SE_ASSERT( iX >= 0 && iX < m_iWidth );
    SE_ASSERT( iY >= 0 && iY < m_iHeight );

    float fX = ((float)iX / (float)m_iWidth)*2.0f - 1.0f;
    float fY = (1.0f - (float)iY / (float)m_iHeight)*2.0f - 1.0f;
    // 注意如果z分量不是0时,最终变换结果需要除以w分量.
    Vector4f vec4fOriginProj(fX, fY, 0.5f, 1.0f);

    Matrix4f mat4fProjInv, mat4fViewInv;
    m_pRenderer->GetProjectionMatrix().GetInverse(mat4fProjInv);
    m_pRenderer->GetViewMatrix().GetInverse(mat4fViewInv);
    Vector4f vec4fOriginView = vec4fOriginProj * mat4fProjInv;
    Vector4f vec4fOriginWorld = vec4fOriginView * mat4fViewInv;
    vec4fOriginWorld /= vec4fOriginWorld.W;

    m_fT = fT;
    m_Origin.X = vec4fOriginWorld.X;
    m_Origin.Y = vec4fOriginWorld.Y;
    m_Origin.Z = vec4fOriginWorld.Z;
    m_XEnd = m_Origin + fT*Vector3f::UNIT_X;
    m_YEnd = m_Origin + fT*Vector3f::UNIT_Y;
    m_ZEnd = m_Origin + fT*Vector3f::UNIT_Z;

    Vector4f vec4fXEnd, vec4fYEnd, vec4fZEnd,
        vec4fXEndProj, vec4fYEndProj, vec4fZEndProj;
    vec4fXEnd.X = m_XEnd.X;
    vec4fXEnd.Y = m_XEnd.Y;
    vec4fXEnd.Z = m_XEnd.Z;
    vec4fXEnd.W = 1.0f;
    vec4fYEnd.X = m_YEnd.X;
    vec4fYEnd.Y = m_YEnd.Y;
    vec4fYEnd.Z = m_YEnd.Z;
    vec4fYEnd.W = 1.0f;
    vec4fZEnd.X = m_ZEnd.X;
    vec4fZEnd.Y = m_ZEnd.Y;
    vec4fZEnd.Z = m_ZEnd.Z;
    vec4fZEnd.W = 1.0f;
    const Matrix4f& rView = m_pRenderer->GetViewMatrix();
    const Matrix4f& rProj = m_pRenderer->GetProjectionMatrix();
    vec4fXEndProj = vec4fXEnd * rView * rProj;
    vec4fYEndProj = vec4fYEnd * rView * rProj;
    vec4fZEndProj = vec4fZEnd * rView * rProj;
    vec4fXEndProj /= vec4fXEndProj.W;
    vec4fYEndProj /= vec4fYEndProj.W;
    vec4fZEndProj /= vec4fZEndProj.W;

    m_iXEndScreenX = (int)((vec4fXEndProj.X*0.5f + 0.5f) * m_iWidth);
    m_iXEndScreenY = (int)((0.5f - vec4fXEndProj.Y*0.5f) * m_iHeight);
    m_iYEndScreenX = (int)((vec4fYEndProj.X*0.5f + 0.5f) * m_iWidth);
    m_iYEndScreenY = (int)((0.5f - vec4fYEndProj.Y*0.5f) * m_iHeight);
    m_iZEndScreenX = (int)((vec4fZEndProj.X*0.5f + 0.5f) * m_iWidth);
    m_iZEndScreenY = (int)((0.5f - vec4fZEndProj.Y*0.5f) * m_iHeight);

    (*(Vector3f*)m_spWorldAxis->VBuffer->PositionTuple(0)) = m_Origin;
    (*(Vector3f*)m_spWorldAxis->VBuffer->PositionTuple(1)) = m_XEnd;
    (*(Vector3f*)m_spWorldAxis->VBuffer->PositionTuple(2)) = m_Origin;
    (*(Vector3f*)m_spWorldAxis->VBuffer->PositionTuple(3)) = m_YEnd;
    (*(Vector3f*)m_spWorldAxis->VBuffer->PositionTuple(4)) = m_Origin;
    (*(Vector3f*)m_spWorldAxis->VBuffer->PositionTuple(5)) = m_ZEnd;
    m_spWorldAxis->VBuffer->Release();
}
//----------------------------------------------------------------------------