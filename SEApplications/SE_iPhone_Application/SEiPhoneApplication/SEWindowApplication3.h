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
// 说明:for iPhone application
// 作者:jazzboysc
// 时间:20090604
//----------------------------------------------------------------------------
class SEWindowApplication3 : public SEWindowApplication
{
public:
    SEWindowApplication3(const char* acWindowTitle, int iXPosition,
        int iYPosition, int iWidth, int iHeight,
        const SEColorRGBA& rBackgroundColor);

    virtual ~SEWindowApplication3(void);

    // Event callback functions.
    virtual bool OnInitialize(void);
    virtual void OnTerminate(void);
    virtual void OnDisplay(void);
    virtual void OnTouchBegan(int iX, int iY);
    virtual void OnTouchMoved(int iX, int iY);
    virtual void OnTouchEnded(int iX, int iY);

protected:
    // Camera motion.
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
    SECameraPtr m_spCamera;
    SEVector3f m_aWorldAxis[3];
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

    // Listener motion.
    SEListenerPtr m_spListener;

    // Object motion.
    void InitializeObjectMotion(SESpatial* pMotionObject);
    bool MoveObject(void);
    void RotateTrackBall(float fX0, float fY0, float fX1, float fY1);
    SESpatialPtr m_spMotionObject;
    int m_iDoRoll, m_iDoYaw, m_iDoPitch;
    float m_fXTrack0, m_fYTrack0, m_fXTrack1, m_fYTrack1;
    SEMatrix3f m_SaveRotate;
    bool m_bUseTrackBall, m_bTrackBallDown;

    // Performance test.
    void ResetTime(void);
    void MeasureTime(void);
    void UpdateFrameCount(void);
    void DrawFrameRate(int iX, int iY, const SEColorRGBA& rColor);
    double m_dLastTime, m_dAccumulatedTime, m_dFrameRate;
    int m_iFrameCount, m_iAccumulatedFrameCount, m_iTimer, m_iMaxTimer;

    // World axis showing stuff.
    void DrawWorldAxis(void);
    void SetOriginScreenPos(int iX, int iY, float fT);
    int m_iOrignScreenX, m_iOrignScreenY;
    int m_iXEndScreenX, m_iXEndScreenY;
    int m_iYEndScreenX, m_iYEndScreenY;
    int m_iZEndScreenX, m_iZEndScreenY;
    float m_fT;
    SEVector3f m_Origin, m_XEnd, m_YEnd, m_ZEnd;
    SEPolylinePtr m_spWorldAxis;
};

}

#endif
