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

#include "SEOGLES2ApplicationPCH.h"
#include "SEWindowApplication3.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEWindowApplication3::SEWindowApplication3(const char* acWindowTitle,
    int iXPosition, int iYPosition, int iWidth, int iHeight,
    const SEColorRGBA& rBackgroundColor)
    :
    SEWindowApplication(acWindowTitle, iXPosition, iYPosition, iWidth, iHeight,
        rBackgroundColor)
{
    // ������˶�
    m_aWorldAxis[0] = SEVector3f::ZERO;
    m_aWorldAxis[1] = SEVector3f::ZERO;
    m_aWorldAxis[2] = SEVector3f::ZERO;
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

    // �����˶�
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

    // ���ܲ���
    m_dLastTime = -1.0;
    m_dAccumulatedTime = 0.0;
    m_dFrameRate = 0.0;
    m_iFrameCount = 0;
    m_iAccumulatedFrameCount = 0;
    m_iTimer = 30;
    m_iMaxTimer = 30;

    // ������ʾ������ϵ������
    m_Origin = SEVector3f::ZERO;
    m_XEnd = SEVector3f::UNIT_X;
    m_YEnd = SEVector3f::UNIT_Y;
    m_ZEnd = SEVector3f::UNIT_Z;
    m_fT = 1.0f;
}
//----------------------------------------------------------------------------
SEWindowApplication3::~SEWindowApplication3()
{
}
//----------------------------------------------------------------------------
bool SEWindowApplication3::OnInitialize()
{
    if( !SEWindowApplication::OnInitialize() )
    {
        return false;
    }

    m_spCamera = SE_NEW SECamera;
    m_pRenderer->SetCamera(m_spCamera);
    m_spMotionObject = 0;

    m_spListener = SE_NEW SEListener;
    m_pAudioRenderer->SetListener(m_spListener);

    SEAttributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetColorChannels(0, 3);
    SEVertexBuffer* pVBuffer = SE_NEW SEVertexBuffer(tempAttr, 6);
    (*(SEVector3f*)pVBuffer->PositionTuple(0)) = m_Origin;
    (*(SEColorRGB*)pVBuffer->ColorTuple(0, 0)) = SEColorRGB::SE_RGB_RED;
    (*(SEVector3f*)pVBuffer->PositionTuple(1)) = m_XEnd;
    (*(SEColorRGB*)pVBuffer->ColorTuple(0, 1)) = SEColorRGB::SE_RGB_RED;
    (*(SEVector3f*)pVBuffer->PositionTuple(2)) = m_Origin;
    (*(SEColorRGB*)pVBuffer->ColorTuple(0, 2)) = SEColorRGB::SE_RGB_GREEN;  
    (*(SEVector3f*)pVBuffer->PositionTuple(3)) = m_YEnd;
    (*(SEColorRGB*)pVBuffer->ColorTuple(0, 3)) = SEColorRGB::SE_RGB_GREEN;
    (*(SEVector3f*)pVBuffer->PositionTuple(4)) = m_Origin;
    (*(SEColorRGB*)pVBuffer->ColorTuple(0, 4)) = SEColorRGB::SE_RGB_BLUE;
    (*(SEVector3f*)pVBuffer->PositionTuple(5)) = m_ZEnd;
    (*(SEColorRGB*)pVBuffer->ColorTuple(0, 5)) = SEColorRGB::SE_RGB_BLUE;
    m_spWorldAxis = SE_NEW SEPolyline(pVBuffer, false, false);

    SEVertexColor3Effect* pEffect = SE_NEW SEVertexColor3Effect;
    m_spWorldAxis->AttachEffect(pEffect);

    return true;
}
//----------------------------------------------------------------------------
void SEWindowApplication3::OnTerminate()
{
    m_pRenderer->SetCamera(0);
    m_spCamera = 0;
    m_spMotionObject = 0;
    m_spWorldAxis = 0;

    m_pAudioRenderer->SetListener(0);
    m_spListener = 0;

    SEWindowApplication::OnTerminate();
}
//----------------------------------------------------------------------------
void SEWindowApplication3::OnDisplay()
{
    if( m_pRenderer )
    {
        OnIdle();
    }
}
//----------------------------------------------------------------------------
bool SEWindowApplication3::OnKeyDown(unsigned char ucKey, int iX, int iY)
{
    if( SEWindowApplication::OnKeyDown(ucKey, iX, iY) )
    {
        return true;
    }

    switch( ucKey )
    {
    case 't':  // ���������ƽ�Ʊ任�ٶ�
        if( m_bCameraMoveable )
        {
            m_fTrnSpeed /= m_fTrnSpeedFactor;
        }

        return true;
    case 'T':  // �ӿ������ƽ�Ʊ任�ٶ�
        if( m_bCameraMoveable )
        {
            m_fTrnSpeed *= m_fTrnSpeedFactor;
        }

        return true;
    case 'r':  // �����������ת�任�ٶ�
        if( m_bCameraMoveable )
        {
            m_fRotSpeed /= m_fRotSpeedFactor;
        }

        return true;
    case 'R':  // �ӿ��������ת�任�ٶ�
        if( m_bCameraMoveable )
        {
            m_fRotSpeed *= m_fRotSpeedFactor;
        }

        return true;
    case '?':  // ���ö�ʱ��
        ResetTime();

        return true;
    };

    return false;
}
//----------------------------------------------------------------------------
bool SEWindowApplication3::OnSpecialKeyDown(int iKey, int, int)
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
bool SEWindowApplication3::OnSpecialKeyUp(int iKey, int, int)
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
bool SEWindowApplication3::OnMouseClick(int iButton, int iState, int iX,
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
        // ��ȡtrackball��ק��ʼ��.
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
bool SEWindowApplication3::OnMotion(int iButton, int iX, int iY, unsigned int)
{
    if( !m_bUseTrackBall
    ||  iButton != MOUSE_LEFT_BUTTON
    ||  !m_bTrackBallDown
    ||  !m_spMotionObject )
    {
        return false;
    }

    // ��ȡtrackball��ק��ֹ��.
    float fMult = 1.0f / (m_iWidth >= m_iHeight ? m_iHeight : m_iWidth);
    m_fXTrack1 = (2*iX-m_iWidth)*fMult;
    m_fYTrack1 = (2*(m_iHeight-1-iY)-m_iHeight)*fMult;

    // ���¶����local��ת�任.
    RotateTrackBall(m_fXTrack0, m_fYTrack0, m_fXTrack1, m_fYTrack1);

    return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ������˶�
//----------------------------------------------------------------------------
void SEWindowApplication3::InitializeCameraMotion(float fTrnSpeed,
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
bool SEWindowApplication3::MoveCamera()
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
void SEWindowApplication3::MoveForward()
{
    SEVector3f vec3fLoc = m_spCamera->GetLocation();
    vec3fLoc += m_fTrnSpeed * m_aWorldAxis[2]; // ��D�᷽��ǰ��
    m_spCamera->SetLocation(vec3fLoc);
    m_spListener->SetLocation(vec3fLoc);
}
//----------------------------------------------------------------------------
void SEWindowApplication3::MoveBackward()
{
    SEVector3f vec3fLoc = m_spCamera->GetLocation();
    vec3fLoc -= m_fTrnSpeed * m_aWorldAxis[2]; // ��D�᷽�����
    m_spCamera->SetLocation(vec3fLoc);
    m_spListener->SetLocation(vec3fLoc);
}
//----------------------------------------------------------------------------
void SEWindowApplication3::MoveUp()
{
    SEVector3f vec3fLoc = m_spCamera->GetLocation();
    vec3fLoc += m_fTrnSpeed * m_aWorldAxis[1]; // ��U�᷽������
    m_spCamera->SetLocation(vec3fLoc);
    m_spListener->SetLocation(vec3fLoc);
}
//----------------------------------------------------------------------------
void SEWindowApplication3::MoveDown()
{
    SEVector3f vec3fLoc = m_spCamera->GetLocation();
    vec3fLoc -= m_fTrnSpeed * m_aWorldAxis[1]; // ��U�᷽���½�
    m_spCamera->SetLocation(vec3fLoc);
    m_spListener->SetLocation(vec3fLoc);
}
//----------------------------------------------------------------------------
void SEWindowApplication3::TurnLeft()
{
    SEMatrix3f mat3fIncr(m_aWorldAxis[1], -m_fRotSpeed);
    m_aWorldAxis[0] = m_aWorldAxis[0] * mat3fIncr; // R����U��������ת
    m_aWorldAxis[2] = m_aWorldAxis[2] * mat3fIncr; // D����U��������ת

    // ���������RUD��.
    SEVector3f tempRVector = m_spCamera->GetRVector() * mat3fIncr;
    SEVector3f tempUVector = m_spCamera->GetUVector() * mat3fIncr;
    SEVector3f tempDVector = m_spCamera->GetDVector() * mat3fIncr;
    m_spCamera->SetAxes(tempRVector, tempUVector, tempDVector);

    // ����listener RUD��.
    m_spListener->SetAxes(tempRVector, tempUVector, tempDVector);
}
//----------------------------------------------------------------------------
void SEWindowApplication3::TurnRight()
{
    SEMatrix3f mat3fIncr(m_aWorldAxis[1], +m_fRotSpeed);
    m_aWorldAxis[0] = m_aWorldAxis[0] * mat3fIncr; // R����U��������ת
    m_aWorldAxis[2] = m_aWorldAxis[2] * mat3fIncr; // D����U��������ת

    // ���������RUD��.
    SEVector3f tempRVector = m_spCamera->GetRVector() * mat3fIncr;
    SEVector3f tempUVector = m_spCamera->GetUVector() * mat3fIncr;
    SEVector3f tempDVector = m_spCamera->GetDVector() * mat3fIncr;
    m_spCamera->SetAxes(tempRVector, tempUVector, tempDVector);

    // ����listener RUD��.
    m_spListener->SetAxes(tempRVector, tempUVector, tempDVector);
}
//----------------------------------------------------------------------------
void SEWindowApplication3::LookUp()
{
    SEMatrix3f mat3fIncr(m_aWorldAxis[0], -m_fRotSpeed);

    // ���������RUD��.
    SEVector3f tempRVector = m_spCamera->GetRVector() * mat3fIncr;
    SEVector3f tempUVector = m_spCamera->GetUVector() * mat3fIncr;
    SEVector3f tempDVector = m_spCamera->GetDVector() * mat3fIncr;
    m_spCamera->SetAxes(tempRVector, tempUVector, tempDVector);

    // ����listener RUD��.
    m_spListener->SetAxes(tempRVector, tempUVector, tempDVector);
}
//----------------------------------------------------------------------------
void SEWindowApplication3::LookDown()
{
    SEMatrix3f mat3fIncr(m_aWorldAxis[0], +m_fRotSpeed);

    // ���������RUD��.
    SEVector3f tempRVector = m_spCamera->GetRVector() * mat3fIncr;
    SEVector3f tempUVector = m_spCamera->GetUVector() * mat3fIncr;
    SEVector3f tempDVector = m_spCamera->GetDVector() * mat3fIncr;
    m_spCamera->SetAxes(tempRVector, tempUVector, tempDVector);

    // ����listener RUD��.
    m_spListener->SetAxes(tempRVector, tempUVector, tempDVector);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// �����˶�
//----------------------------------------------------------------------------
void SEWindowApplication3::InitializeObjectMotion(SESpatial* pMotionObject)
{
    m_spMotionObject = pMotionObject;
}
//----------------------------------------------------------------------------
bool SEWindowApplication3::MoveObject()
{
    // ��ת�任��Ե��Ƕ���ĸ��ڵ������ϵ,������󸸽ڵ�ǿյĻ�.
    // ��������ת�任������R,R��3�й�����һ��������.
    // 0��Ϊ"right",1��Ϊ"up",2��Ϊ"direction".
    // �������û�и��ڵ�,��ʹ��������ϵ������,
    // ��ʱ��ת������һ����λ����I,
    // 0��(1,0,0)Ϊ"right",1��(0,1,0)Ϊ"up",2��(0,0,1)Ϊ"direction".
    // ���ѡ����SECamera��Light���е���ת�任��ѡ����һ�µ�.
    //
    // Yaw���"up"��,Pitch���"right"��,Roll���"direction"��.

    if( !m_bCameraMoveable || !m_spMotionObject )
    {
        return false;
    }

    // �������Ƿ��Ѿ���virtual trackball�ƶ���.
    if( m_bTrackBallDown )
    {
        return true;
    }

    // �������Ƿ��Ѿ������ܼ��ƶ���.
    SESpatial* pParent = m_spMotionObject->GetParent();
    SEVector3f vec3fAxis;
    float fAngle;
    SEMatrix3f mat3fRot, mat3fIncr;

    if( m_iDoPitch ) // ���R��
    {
        mat3fRot = m_spMotionObject->Local.GetRotate();

        fAngle = m_iDoPitch * m_fRotSpeed;
        if( pParent )
        {
            pParent->World.GetRotate().GetRow(0, vec3fAxis);
        }
        else
        {
            vec3fAxis = SEVector3f::UNIT_X;
        }

        mat3fIncr.FromAxisAngle(vec3fAxis, fAngle);
        mat3fRot = mat3fRot * mat3fIncr;
        mat3fRot.Orthonormalize();
        m_spMotionObject->Local.SetRotate(mat3fRot);

        return true;
    }

    if( m_iDoYaw ) // ���U��
    {
        mat3fRot = m_spMotionObject->Local.GetRotate();

        fAngle = m_iDoYaw * m_fRotSpeed;
        if( pParent )
        {
            pParent->World.GetRotate().GetRow(1, vec3fAxis);
        }
        else
        {
            vec3fAxis = SEVector3f::UNIT_Y;
        }

        mat3fIncr.FromAxisAngle(vec3fAxis, fAngle);
        mat3fRot = mat3fRot * mat3fIncr;
        mat3fRot.Orthonormalize();
        m_spMotionObject->Local.SetRotate(mat3fRot);

        return true;
    }

    if( m_iDoRoll ) // ���D��
    {
        mat3fRot = m_spMotionObject->Local.GetRotate();

        fAngle = m_iDoRoll * m_fRotSpeed;
        if( pParent )
        {
            pParent->World.GetRotate().GetRow(2, vec3fAxis);
        }
        else
        {
            vec3fAxis = SEVector3f::UNIT_Z;
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
void SEWindowApplication3::RotateTrackBall(float fX0, float fY0, float fX1,
    float fY1)
{
    if( !m_spCamera )
    {
        return;
    }

    SEMatrix3f mat3fTrackRotate;
    if( !m_spCamera->GetTrackBallRotate(fX0, fY0, fX1, fY1, mat3fTrackRotate) )
    {
        return;
    }

    // ������µĶ���local��ת�任.
    // ���������scene�ĸ��ڵ�,����local��ת�任�����ھ���local��ת�任������,
    // ��һ��ʩ�Ӹո������������ת�任,��ΪRlocal' = Rlocal*Rincremental.
    // ���������scene�ĸ��ڵ�,�����ͨ��һϵ����Զ��󸸽ڵ�Ļ��任,
    // ʹ��local��ת�任��Ϊ:Rlocal' = Rlocal*Rparent*Rincremental*(Rparent^T).
    const SESpatial* pParent = m_spMotionObject->GetParent();
    SEMatrix3f mat3fLocalRot;
    if( pParent )
    {
        const SEMatrix3f& rPRotate = pParent->World.GetRotate();
        SEMatrix3f mat3fPRotateT;
        rPRotate.GetTranspose(mat3fPRotateT);
        mat3fLocalRot = m_SaveRotate * rPRotate * mat3fTrackRotate * 
            mat3fPRotateT;
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
// ���ܲ���
//----------------------------------------------------------------------------
void SEWindowApplication3::ResetTime()
{
    m_dLastTime = -1.0f;
}
//----------------------------------------------------------------------------
void SEWindowApplication3::MeasureTime()
{
    // ��ʼ���ܲ���.
    if( m_dLastTime == -1.0 )
    {
        m_dLastTime = SESystem::SE_GetTime();
        m_dAccumulatedTime = 0.0;
        m_dFrameRate = 0.0;
        m_iFrameCount = 0;
        m_iAccumulatedFrameCount = 0;
        m_iTimer = m_iMaxTimer;
    }

    // ��ʱ����m_dAccumulatedTime,m_iAccumulatedFrameCount.
    if( --m_iTimer == 0 )
    {
        double dCurrentTime = SESystem::SE_GetTime();
        double dDelta = dCurrentTime - m_dLastTime;
        m_dLastTime = dCurrentTime;
        m_dAccumulatedTime += dDelta;
        m_iAccumulatedFrameCount += m_iFrameCount;
        m_iFrameCount = 0;
        m_iTimer = m_iMaxTimer;
    }
}
//----------------------------------------------------------------------------
void SEWindowApplication3::UpdateFrameCount()
{
    m_iFrameCount++;
}
//----------------------------------------------------------------------------
void SEWindowApplication3::DrawFrameRate(int iX, int iY, const SEColorRGBA& 
    rColor)
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
    SESystem::SE_Sprintf(acMessage, uiSize, "fps: %.1lf", m_dFrameRate);
    m_pRenderer->Draw(iX, iY, rColor, acMessage);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ������ʾ������ϵ������
//----------------------------------------------------------------------------
void SEWindowApplication3::DrawWorldAxis(void)
{
    m_pRenderer->Draw(m_spWorldAxis);
    m_pRenderer->Draw(m_iXEndScreenX + 2, m_iXEndScreenY - 2, 
        SEColorRGBA::SE_RGBA_RED, "x");
    m_pRenderer->Draw(m_iYEndScreenX + 2, m_iYEndScreenY - 2, 
        SEColorRGBA::SE_RGBA_GREEN, "y");
    m_pRenderer->Draw(m_iZEndScreenX + 2, m_iZEndScreenY - 2, 
        SEColorRGBA::SE_RGBA_BLUE, "z");
}
//----------------------------------------------------------------------------
void SEWindowApplication3::SetOriginScreenPos(int iX, int iY, float fT)
{
    SE_ASSERT( iX >= 0 && iX < m_iWidth );
    SE_ASSERT( iY >= 0 && iY < m_iHeight );

    float fX = ((float)iX / (float)m_iWidth)*2.0f - 1.0f;
    float fY = (1.0f - (float)iY / (float)m_iHeight)*2.0f - 1.0f;
    // ע�����z��������0ʱ,���ձ任�����Ҫ����w����.
    SEVector4f vec4fOriginProj(fX, fY, 0.5f, 1.0f);

    SEMatrix4f mat4fProjInv, mat4fViewInv;
    m_pRenderer->GetProjectionMatrix().GetInverse(mat4fProjInv);
    m_pRenderer->GetViewMatrix().GetInverse(mat4fViewInv);
    SEVector4f vec4fOriginView = vec4fOriginProj * mat4fProjInv;
    SEVector4f vec4fOriginWorld = vec4fOriginView * mat4fViewInv;
    vec4fOriginWorld /= vec4fOriginWorld.W;

    m_fT = fT;
    m_Origin.X = vec4fOriginWorld.X;
    m_Origin.Y = vec4fOriginWorld.Y;
    m_Origin.Z = vec4fOriginWorld.Z;
    m_XEnd = m_Origin + fT*SEVector3f::UNIT_X;
    m_YEnd = m_Origin + fT*SEVector3f::UNIT_Y;
    m_ZEnd = m_Origin + fT*SEVector3f::UNIT_Z;

    SEVector4f vec4fXEnd, vec4fYEnd, vec4fZEnd,
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
    const SEMatrix4f& rView = m_pRenderer->GetViewMatrix();
    const SEMatrix4f& rProj = m_pRenderer->GetProjectionMatrix();
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

    (*(SEVector3f*)m_spWorldAxis->VBuffer->PositionTuple(0)) = m_Origin;
    (*(SEVector3f*)m_spWorldAxis->VBuffer->PositionTuple(1)) = m_XEnd;
    (*(SEVector3f*)m_spWorldAxis->VBuffer->PositionTuple(2)) = m_Origin;
    (*(SEVector3f*)m_spWorldAxis->VBuffer->PositionTuple(3)) = m_YEnd;
    (*(SEVector3f*)m_spWorldAxis->VBuffer->PositionTuple(4)) = m_Origin;
    (*(SEVector3f*)m_spWorldAxis->VBuffer->PositionTuple(5)) = m_ZEnd;
    m_spWorldAxis->VBuffer->Release();
}
//----------------------------------------------------------------------------