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

#ifndef Swing_DistLine3Box3_H
#define Swing_DistLine3Box3_H

#include "SEFoundationLIB.h"
#include "SEDistance.h"
#include "SELine3.h"
#include "SEBox3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:DistLine3Box3f类
// 说明:
// 作者:Sun Che
// 时间:20090113
//----------------------------------------------------------------------------
class SE_FOUNDATION_API DistLine3Box3f : public Distance<float, Vector3f>
{
public:
    DistLine3Box3f(const Line3f& rLine, const Box3f& rBox);

    // 对象访问.
    const Line3f& GetLine(void) const;
    const Box3f& GetBox(void) const;

    // static distance查询.
    virtual float Get(void);
    virtual float GetSquared(void);

    // 用于dynamic distance查询的convex function计算.
    virtual float Get(float fT, const Vector3f& rVelocity0,
        const Vector3f& rVelocity1);
    virtual float GetSquared(float fT, const Vector3f& rVelocity0,
        const Vector3f& rVelocity1);

    // 访问最近点处的直线参数.
    // ray-box和segment-box的distance计算也使用这个函数.
    float GetLineParameter(void) const;

private:
    void Face(int i0, int i1, int i2, Vector3f& rPnt,
        const Vector3f& rDir, const Vector3f& rPmE,
        float& rfSqrDistance);

    void CaseNoZeros(Vector3f& rPnt, const Vector3f& rDir,
        float& rfSqrDistance);

    void Case0(int i0, int i1, int i2, Vector3f& rPnt,
        const Vector3f& rDir, float& rfSqrDistance);

    void Case00(int i0, int i1, int i2, Vector3f& rPnt,
        const Vector3f& rDir, float& rfSqrDistance);

    void Case000(Vector3f& rPnt, float& rfSqrDistance);

    const Line3f* m_pLine;
    const Box3f* m_pBox;
    float m_fLParam;
};

}

#endif
