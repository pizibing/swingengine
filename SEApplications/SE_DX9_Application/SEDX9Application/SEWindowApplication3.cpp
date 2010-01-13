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

#include "SEDX9ApplicationPCH.h"
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
    // 摄像机运动
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

    // 对象运动
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

    // 性能测试
    m_dLastTime = -1.0;
    m_dAccumulatedTime = 0.0;
    m_dFrameRate = 0.0;
    m_iFrameCount = 0;
    m_iAccumulatedFrameCount = 0;
    m_iTimer = 30;
    m_iMaxTimer = 30;
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

    // Create main camera.
    m_spCamera = SE_NEW Camera;
    m_pRenderer->SetCamera(m_spCamera);
    m_spMotionObject = 0;

    // Create main listener.
    m_spListener = SE_NEW Listener;
    m_pAudioRenderer->SetListener(m_spListener);

    // Create world coordinate frame's widget.
    m_fLengthOfAxis = 0.35f;
    m_spWorldAxis = Widget::CoordinateFrame(m_fLengthOfAxis);
    ZBufferState* pZS = SE_NEW ZBufferState;
    pZS->Enabled = false;
    m_spWorldAxis->AttachGlobalState(pZS);
    m_spWorldAxis->UpdateRS();

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
bool WindowApplication3::OnKeyDown(unsigned char ucKey, int iX, int iY)
{
    if( WindowApplication::OnKeyDown(ucKey, iX, iY) )
    {
        return true;
    }

    switch( ucKey )
    {
    case 't':  // 减慢摄像机平移变换速度
        if( m_bCameraMoveable )
        {
            m_fTrnSpeed /= m_fTrnSpeedFactor;
        }

        return true;
    case 'T':  // 加快摄像机平移变换速度
        if( m_bCameraMoveable )
        {
            m_fTrnSpeed *= m_fTrnSpeedFactor;
        }

        return true;
    case 'r':  // 减慢摄像机旋转变换速度
        if( m_bCameraMoveable )
        {
            m_fRotSpeed /= m_fRotSpeedFactor;
        }

        return true;
    case 'R':  // 加快摄像机旋转变换速度
        if( m_bCameraMoveable )
        {
            m_fRotSpeed *= m_fRotSpeedFactor;
        }

        return true;
    case '?':  // 重置定时器
        ResetTime();

        return true;
    };

    return false;
}
//----------------------------------------------------------------------------
bool WindowApplication3::OnSpecialKeyDown(int iKey, int, int)
{
    if( m_bCameraMoveable )
    {
        if( iKey == KEY_LEFT_ARROW )
        {
            m_bLArrowPressed = true;

            return true;
        }
        if( iKey == KEY_RIGHT_ARROW )
        {
            m_bRArrowPressed = true;

            return true;
        }
        if( iKey == KEY_UP_ARROW )
        {
            m_bUArrowPressed = true;

            return true;
        }
        if( iKey == KEY_DOWN_ARROW )
        {
            m_bDArrowPressed = true;

            return true;
        }
        if( iKey == KEY_PAGE_UP )
        {
            m_bPgUpPressed = true;

            return true;
        }
        if( iKey == KEY_PAGE_DOWN )
        {
            m_bPgDnPressed = true;

            return true;
        }
        if( iKey == KEY_HOME )
        {
            m_bHomePressed = true;

            return true;
        }
        if( iKey == KEY_END )
        {
            m_bEndPressed = true;

            return true;
        }
    }

    if( m_spMotionObject )
    {
        if( iKey == KEY_F1 )
        {
            m_iDoRoll = +1;

            return true;
        }
        if( iKey == KEY_F2 )
        {
            m_iDoRoll = -1;

            return true;
        }
        if( iKey == KEY_F3 )
        {
            m_iDoYaw = +1;

            return true;
        }
        if( iKey == KEY_F4 )
        {
            m_iDoYaw = -1;

            return true;
        }
        if( iKey == KEY_F5 )
        {
            m_iDoPitch = +1;

            return true;
        }
        if( iKey == KEY_F6 )
        {
            m_iDoPitch = -1;

            return true;
        }
    }

    return false;
}
//----------------------------------------------------------------------------
bool WindowApplication3::OnSpecialKeyUp(int iKey, int, int)
{
    if( m_bCameraMoveable )
    {
        if( iKey == KEY_LEFT_ARROW )
        {
            m_bLArrowPressed = false;

            return true;
        }
        if( iKey == KEY_RIGHT_ARROW )
        {
            m_bRArrowPressed = false;

            return true;
        }
        if( iKey == KEY_UP_ARROW )
        {
            m_bUArrowPressed = false;

            return true;
        }
        if( iKey == KEY_DOWN_ARROW )
        {
            m_bDArrowPressed = false;

            return true;
        }
        if( iKey == KEY_PAGE_UP )
        {
            m_bPgUpPressed = false;

            return true;
        }
        if( iKey == KEY_PAGE_DOWN )
        {
            m_bPgDnPressed = false;

            return true;
        }
        if( iKey == KEY_HOME )
        {
            m_bHomePressed = false;

            return true;
        }
        if( iKey == KEY_END )
        {
            m_bEndPressed = false;

            return true;
        }
    }

    if( m_spMotionObject )
    {
        if( iKey == KEY_F1 )
        {
            m_iDoRoll = 0;

            return true;
        }
        if( iKey == KEY_F2 )
        {
            m_iDoRoll = 0;

            return true;
        }
        if( iKey == KEY_F3 )
        {
            m_iDoYaw = 0;

            return true;
        }
        if( iKey == KEY_F4 )
        {
            m_iDoYaw = 0;

            return true;
        }
        if( iKey == KEY_F5 )
        {
            m_iDoPitch = 0;

            return true;
        }
        if( iKey == KEY_F6 )
        {
            m_iDoPitch = 0;

            return true;
        }
    }

    return false;
}
//----------------------------------------------------------------------------
bool WindowApplication3::OnMouseClick(int iButton, int iState, int iX,
    int iY, unsigned int)
{
    if( !m_bUseTrackBall
    ||  iButton != MOUSE_LEFT_BUTTON
    ||  !m_spMotionObject )
    {
        return false;
    }

    float fMult = 1.0f / (m_iWidth >= m_iHeight ? m_iHeight : m_iWidth);

    if( iState == MOUSE_DOWN )
    {
        // 获取trackball托拽起始点.
        m_bTrackBallDown = true;
        m_SaveRotate = m_spMotionObject->Local.GetRotate();
        m_fXTrack0 = (2*iX-m_iWidth)*fMult;
        m_fYTrack0 = (2*(m_iHeight-1-iY)-m_iHeight)*fMult;
    }
    else
    {
        m_bTrackBallDown = false;
    }

    return true;
}
//----------------------------------------------------------------------------
bool WindowApplication3::OnMotion(int iButton, int iX, int iY, unsigned int)
{
    if( !m_bUseTrackBall
    ||  iButton != MOUSE_LEFT_BUTTON
    ||  !m_bTrackBallDown
    ||  !m_spMotionObject )
    {
        return false;
    }

    // 获取trackball托拽终止点.
    float fMult = 1.0f / (m_iWidth >= m_iHeight ? m_iHeight : m_iWidth);
    m_fXTrack1 = (2*iX-m_iWidth)*fMult;
    m_fYTrack1 = (2*(m_iHeight-1-iY)-m_iHeight)*fMult;

    // 更新对象的local旋转变换.
    RotateTrackBall(m_fXTrack0, m_fYTrack0, m_fXTrack1, m_fYTrack1);

    return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 摄像机运动
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
// 对象运动
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
// 性能测试
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
// 辅助显示世界体系坐标轴
//----------------------------------------------------------------------------
void WindowApplication3::DrawWorldAxis(void)
{
    // Update the origin of world axis.
    float fRatio = m_spCamera->GetRMax() / m_spCamera->GetUMax();
    float fU = 3.4f;
    float fR = fRatio*fU + 0.2f; 
    Vector3f vec3fOrigin = m_spCamera->GetLocation() + 
        (m_spCamera->GetDMin() + 10.0f)*m_spCamera->GetDVector() - 
        fR*m_spCamera->GetRVector() - fU*m_spCamera->GetUVector();
    m_spWorldAxis->Local.SetTranslate(vec3fOrigin);
    m_spWorldAxis->UpdateGS();

    // Draw world axis's geometry.
    for( int i = 0; i < m_spWorldAxis->GetCount(); i++ )
    {
        m_pRenderer->Draw((Geometry*)(Spatial*)m_spWorldAxis->GetChild(i));
    }

    // Get axis's ending points.
    Matrix4f mat4fVP = m_pRenderer->GetViewMatrix()*
        m_pRenderer->GetProjectionMatrix();
    Vector3f vec3fXEnd, vec3fYEnd, vec3fZEnd;
    vec3fXEnd = vec3fOrigin + m_fLengthOfAxis*Vector3f::UNIT_X;
    vec3fYEnd = vec3fOrigin + m_fLengthOfAxis*Vector3f::UNIT_Y;
    vec3fZEnd = vec3fOrigin + m_fLengthOfAxis*Vector3f::UNIT_Z;

    // Draw character 'x' at the end of axis x.
    Vector4f vec4fXTopH = Vector4f(vec3fXEnd.X, vec3fXEnd.Y, vec3fXEnd.Z, 1)*
        mat4fVP;
    float fInvW = 1.0f / vec4fXTopH.W;
    float fX = (vec4fXTopH.X*fInvW + 1.0f)*0.5f;  // fX:[0,1]
    float fY = (vec4fXTopH.Y*fInvW + 1.0f)*0.5f;  // fY:[0,1]
    int iX = (int)(fX * (float)m_iWidth);         // iX:[0, width]
    int iY = (int)((1.0f - fY)*(float)m_iHeight); // iY:[0, height]
    m_pRenderer->Draw(iX + 2, iY - 2, ColorRGBA::SE_RGBA_RED, "x");

    // Draw character 'y' at the end of axis y.
    Vector4f vec4fYTopH = Vector4f(vec3fYEnd.X, vec3fYEnd.Y, vec3fYEnd.Z, 1)*
        mat4fVP;
    fInvW = 1.0f / vec4fYTopH.W;
    fX = (vec4fYTopH.X*fInvW + 1.0f)*0.5f;    // fX:[0,1]
    fY = (vec4fYTopH.Y*fInvW + 1.0f)*0.5f;    // fY:[0,1]
    iX = (int)(fX * (float)m_iWidth);         // iX:[0, width]
    iY = (int)((1.0f - fY)*(float)m_iHeight); // iY:[0, height]
    m_pRenderer->Draw(iX + 2, iY - 2, ColorRGBA::SE_RGBA_GREEN, "y");

    // Draw character 'z' at the end of axis z.
    Vector4f vec4fZTopH = Vector4f(vec3fZEnd.X, vec3fZEnd.Y, vec3fZEnd.Z, 1)*
        mat4fVP;
    fInvW = 1.0f / vec4fZTopH.W;
    fX = (vec4fZTopH.X*fInvW + 1.0f)*0.5f;    // fX:[0,1]
    fY = (vec4fZTopH.Y*fInvW + 1.0f)*0.5f;    // fY:[0,1]
    iX = (int)(fX * (float)m_iWidth);         // iX:[0, width]
    iY = (int)((1.0f - fY)*(float)m_iHeight); // iY:[0, height]
    m_pRenderer->Draw(iX + 2, iY - 2, ColorRGBA::SE_RGBA_BLUE, "z");
}
//----------------------------------------------------------------------------