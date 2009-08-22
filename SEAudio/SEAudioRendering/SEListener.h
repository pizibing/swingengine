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

#ifndef Swing_Listener_H
#define Swing_Listener_H

#include "SEAudioLIB.h"
#include "SEObject.h"

// 我们的世界坐标系为左手坐标系{Origin;X,Y,Z}:
// 默认Origin = (0,0,0)
// 默认X轴    = (1,0,0)
// 默认Y轴    = (0,1,0)
// 默认Z轴    = (0,0,1)

// 我们使用:
// (1) 左手坐标系
// (2) 绕任意轴旋转theta度,theta > 0时为顺时针旋转
// (3) 3维向量叉积方向使用左手原则

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:listener基类
// 说明:
// 作者:Sun Che
// 时间:20090618
//----------------------------------------------------------------------------
class SE_AUDIO_API Listener : public Object
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    Listener(void);
    virtual ~Listener(void);

    // listener{E;R,U,D}的世界坐标系下表示:
    // 默认location  E = (0,0,0)
    // 默认right     R = (1,0,0)
    // 默认up        U = (0,1,0)
    // 默认direction D = (0,0,1)

    void SetFrame(const Vector3f& rLocation, const Vector3f& rRVector,
        const Vector3f& rUVector, const Vector3f& rDVector);
    void SetLocation(const Vector3f& rLocation);
    void SetAxes(const Vector3f& rRVector, const Vector3f& rUVector, 
        const Vector3f& rDVector);

    inline Vector3f GetLocation(void) const;
    inline Vector3f GetRVector(void) const;
    inline Vector3f GetUVector(void) const;
    inline Vector3f GetDVector(void) const;

    void SetMasterGain(float fMasterGain);
    inline float GetMasterGain(void) const;

protected:
    // listener E;R,U,D的世界坐标系表示.
    Vector3f m_Location, m_RVector, m_UVector, m_DVector;

    // master gain.
    float m_fMasterGain;  // default: 1.0f

    // 当前listener所属的声音渲染器.
    // 非空时表示当前listener处于激活状态,
    // listener不能同时添加给多个声音渲染器,但可以在多个声音渲染器之间共享,
    // 前提是确保只有一个声音渲染器正在使用该listener,
    // 声音渲染器有责任设置这个成员变量.
    friend class AudioRenderer;
    AudioRenderer* m_pAudioRenderer;
};

typedef SmartPointer<Listener> ListenerPtr;

#include "SEListener.inl"

}

#endif
