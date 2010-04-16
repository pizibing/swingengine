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

#ifndef Swing_ParticleController_H
#define Swing_ParticleController_H

#include "SEFoundationLIB.h"
#include "SEController.h"
#include "SEParticles.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:particle controller基类
// 说明:
// 作者:Sun Che
// 时间:20090602
//----------------------------------------------------------------------------
class SE_FOUNDATION_API ParticleController : public Controller
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    virtual ~ParticleController(void);

    // system motion,在local坐标系下.以下速度向量应为单位长度.
    float SystemLinearSpeed;
    float SystemAngularSpeed;
    Vector3f SystemLinearAxis;
    Vector3f SystemAngularAxis;

    // point motion,在system的模型空间下.以下速度向量应为单位长度.
    // 对于把这些粒子当作一个rigid body(刚体)来使用的用户,
    // 可以选择system的原点作为这些粒子的质量中心,选择system的坐标轴作为
    // inertia tensor(惯性张量)的principal directions(主方向).
    inline float* PointLinearSpeed(void);
    inline Vector3f* PointLinearAxis(void);

    // system size change访问.
    float SystemSizeChange;
    inline float* PointSizeChange(void);

    // 动画更新,派生类可重载,从而实现自定义控制行为.
    virtual bool Update(double dAppTime);

protected:
    ParticleController(void);

    // 用于延迟分配point motion arrays.
    void Reallocate(int iVertexCount);
    virtual void SetObject(SEObject* pObject);

    // 更新motion参数,派生类可重载.
    virtual void UpdateSystemMotion(float fCtrlTime);
    virtual void UpdatePointMotion(float fCtrlTime);

    // point motion(在system的模型空间下).
    int m_iLCount;
    float* m_afPointLinearSpeed;
    Vector3f* m_aPointLinearAxis;

    // point size change参数.
    float* m_afPointSizeChange;
};

typedef SESmartPointer<ParticleController> ParticleControllerPtr;

#include "SEParticleController.inl"

}

#endif
