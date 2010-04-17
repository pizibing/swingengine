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

#ifndef Swing_Distance_H
#define Swing_Distance_H

#include "SEFoundationLIB.h"
#include "SEVector2.h"
#include "SEVector3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:Distance虚基类
// 说明:
// 作者:Sun Che
// 时间:20090104
//----------------------------------------------------------------------------
template <class Real, class TVector>
class SE_FOUNDATION_API Distance
{
public:
    // 虚基类.
    virtual ~Distance(void);

    // static distance查询.
    virtual Real Get(void) = 0;     // distance
    virtual Real GetSquared(void) = 0;  // squared distance

    // 用于dynamic distance查询的convex function计算.
    virtual Real Get(Real fT, const TVector& rVelocity0,
        const TVector& rVelocity1) = 0;
    virtual Real GetSquared(Real fT, const TVector& rVelocity0,
        const TVector& rVelocity1) = 0;

    // 用于dynamic distance查询的导数计算.
    // 默认使用有限差分估算导数.
    // f'(t) = (f(t+h)-f(t-h))/(2*h).
    // 其中h = DifferenceStep.  派生类可以重载这些函数,
    // 从而实现一个不需要h的精确导数计算方法.
    virtual Real GetDerivative(Real fT, const TVector& rVelocity0,
        const TVector& rVelocity1);
    // g(t) = f(t)^2, g'(t) = 2*f(t)*f'(t).
    virtual Real GetDerivativeSquared(Real fT, const TVector& rVelocity0,
        const TVector& rVelocity1);

    // Dynamic distance查询.
    // 函数计算出在给定时间区间[tmin,tmax]上,两对象间的最小距离.
    virtual Real Get(Real fTMin, Real fTMax, const TVector& rVelocity0,
        const TVector& rVelocity1);
    virtual Real GetSquared(Real fTMin, Real fTMax,
        const TVector& rVelocity0, const TVector& rVelocity1);

    // 用于Newton's method和inverse parabolic interpolation.
    int MaximumIterations;  // default = 8
    Real ZeroThreshold;     // default = SEMath<Real>::ZERO_TOLERANCE

    // 用于导数估算.
    void SetDifferenceStep(Real fDifferenceStep);  // default = 1e-03
    Real GetDifferenceStep(void) const;

    // dynamic distance查询时,达到最小距离的时刻.
    Real GetContactTime(void) const;

    // 两对象上的最近点.对于static或dynmaic查询都有效.
    // 一个对象上的最近点可以是一个集合,此时,布尔成员函数返回为true.
    // 派生类可以实现支持完整最近点集合的查询.
    const TVector& GetClosestPoint0(void) const;
    const TVector& GetClosestPoint1(void) const;
    bool HasMultipleClosestPoints0(void) const;
    bool HasMultipleClosestPoints1(void) const;

protected:
    Distance(void);

    Real m_fContactTime;
    TVector m_ClosestPoint0;
    TVector m_ClosestPoint1;
    bool m_bHasMultipleClosestPoints0;
    bool m_bHasMultipleClosestPoints1;
    Real m_fDifferenceStep, m_fInvTwoDifferenceStep;
};

typedef Distance<float, SEVector2f> Distance2f;
typedef Distance<float, SEVector3f> Distance3f;
//typedef Distance<double, SEVector2d> Distance2d;
//typedef Distance<double, SEVector3d> Distance3d;

}

#endif
