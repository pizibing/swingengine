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

#ifndef Swing_IntrRay3Sphere3_H
#define Swing_IntrRay3Sphere3_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEIntersector.h"
#include "SERay3.h"
#include "SESphere3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:IntrRay3Sphere3f类
// 说明:
// 作者:Sun Che
// 时间:20081219
//----------------------------------------------------------------------------
class SE_FOUNDATION_API IntrRay3Sphere3f
    : public Intersector<float, Vector3f>
{
public:
    IntrRay3Sphere3f(const Ray3f& rRay, const Sphere3f& rSphere);

    // 对象访问.
    const Ray3f& GetRay(void) const;
    const Sphere3f& GetSphere(void) const;

    // test-intersection查询.
    virtual bool Test(void);

    // find-intersection查询.
    virtual bool Find(void);
    int GetCount(void) const;
    const Vector3f& GetPoint(int i) const;
    float GetRayT(int i) const;

private:
    // 待检查是否相交的对象.
    const Ray3f* m_pRay;
    const Sphere3f* m_pSphere;

    // 相交集相关信息.
    int m_iCount;
    Vector3f m_aPoint[2];
    float m_afRayT[2];
};

}

#endif
