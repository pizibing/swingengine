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

#ifndef Swing_DistRay2Ray2_H
#define Swing_DistRay2Ray2_H

#include "SEFoundationLIB.h"
#include "SEDistance.h"
#include "SERay2.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:DistRay2Ray2f类
// 说明:
// 作者:Sun Che
// 时间:20090116
//----------------------------------------------------------------------------
class SE_FOUNDATION_API DistRay2Ray2f : public Distance<float, Vector2f>
{
public:
    DistRay2Ray2f(const Ray2f& rRay0, const Ray2f& rRay1);

    // 对象访问.
    const Ray2f& GetRay0(void) const;
    const Ray2f& GetRay1(void) const;

    // static distance查询.
    virtual float Get(void);
    virtual float GetSquared(void);

    // 用于dynamic distance查询的convex function计算.
    virtual float Get(float fT, const Vector2f& rVelocity0,
        const Vector2f& rVelocity1);
    virtual float GetSquared(float fT, const Vector2f& rVelocity0,
        const Vector2f& rVelocity1);

private:
    const Ray2f* m_pRay0;
    const Ray2f* m_pRay1;
};

}

#endif
