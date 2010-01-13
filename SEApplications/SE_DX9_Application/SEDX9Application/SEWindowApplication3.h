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

#ifndef Swing_WindowAppliCation3_H
#define Swing_WindowAppliCation3_H

#include "SEWindowApplication.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:3D窗口应用程序基类
// 说明:
// 作者:Sun Che
// 时间:20080809
//----------------------------------------------------------------------------
class WindowApplication3 : public WindowApplication
{
public:
    WindowApplication3(const char* acWindowTitle, int iXPosition,
        int iYPosition, int iWidth, int iHeight,
        const ColorRGBA& rBackgroundColor);

    virtual ~WindowApplication3(void);

    // 事件回调函数
    virtual bool OnInitialize(void);
    virtual void OnTerminate(void);
    virtual void OnDisplay(void);
    virtual bool OnKeyDown(unsigned char ucKey, int iX, int iY);
    virtual bool OnSpecialKeyDown(int iKey, int iX, int iY);
    virtual bool OnSpecialKeyUp(int iKey, int iX, int iY);
    virtual bool OnMouseClick(int iButton, int iState, int iX, int iY,
        unsigned int uiModifiers);
    virtual bool OnMotion(int iButton, int iX, int iY,
        unsigned int uiModifiers);

protected:
    // 摄像机运动
    void InitializeCameraMotion(float fTrnSpeed, float fRotSpeed,
        float fTrnSpeedFactor = 2.0f, float fRotSpeedFactor = 2.0f);
    virtual bool MoveCamera(void);
    virtual void MoveForward(void);
    virtual void MoveBackward(void);
    virtual void MoveUp(void);
    virtual void MoveDown(void);
    virtual void TurnLeft(void);
    virtual void TurnRight(void);
    virtual void LookUp(void);
    virtual void LookDown(void);
    CameraPtr m_spCamera;
    Vector3f m_aWorldAxis[3];
    float m_fTrnSpeed, m_fTrnSpeedFactor;
    float m_fRotSpeed, m_fRotSpeedFactor;
    bool m_bUArrowPressed;
    bool m_bDArrowPressed;
    bool m_bLArrowPressed;
    bool m_bRArrowPressed;
    bool m_bPgUpPressed;
    bool m_bPgDnPressed;
    bool m_bHomePressed;
    bool m_bEndPressed;
    bool m_bCameraMoveable;

    // listener运动
    ListenerPtr m_spListener;

    // 对象运动
    void InitializeObjectMotion(Spatial* pMotionObject);
    bool MoveObject(void);
    void RotateTrackBall(float fX0, float fY0, float fX1, float fY1);
    SpatialPtr m_spMotionObject;
    int m_iDoRoll, m_iDoYaw, m_iDoPitch;
    float m_fXTrack0, m_fYTrack0, m_fXTrack1, m_fYTrack1;
    Matrix3f m_SaveRotate;
    bool m_bUseTrackBall, m_bTrackBallDown;

    // 性能测试
    void ResetTime(void);
    void MeasureTime(void);
    void UpdateFrameCount(void);
    void DrawFrameRate(int iX, int iY, const ColorRGBA& rColor);
    double m_dLastTime, m_dAccumulatedTime, m_dFrameRate;
    int m_iFrameCount, m_iAccumulatedFrameCount, m_iTimer, m_iMaxTimer;

    // 辅助显示世界体系坐标轴
    void DrawWorldAxis(void);
    NodePtr m_spWorldAxis;
    float m_fLengthOfAxis;
};

}

#endif
