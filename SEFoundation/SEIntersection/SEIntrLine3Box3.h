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

#ifndef Swing_IntrLine3Box3_H
#define Swing_IntrLine3Box3_H

#include "SEFoundationLIB.h"
#include "SEIntersector.h"
#include "SELine3.h"
#include "SEBox3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:IntrLine3Box3f类
// 说明:
// 作者:Sun Che
// 时间:20081230
//----------------------------------------------------------------------------
class SE_FOUNDATION_API IntrLine3Box3f
    : public Intersector<float, SEVector3f>
{
public:
    IntrLine3Box3f(const SELine3f& rLine, const SEBox3f& rBox);

    // 对象访问.
    const SELine3f& GetLine(void) const;
    const SEBox3f& GetBox(void) const;

    // static intersection查询.
    virtual bool Test(void); // 使用潜在分离轴和Minkowski difference算法
    virtual bool Find(void);

    // 相交集合.
    int GetCount(void) const;
    const SEVector3f& GetPoint(int i) const;

private:
    static bool Clip(float fDenom, float fNumer, float& rfT0, float& rfT1);

    // 待检查是否相交的对象.
    const SELine3f* m_pLine;
    const SEBox3f* m_pBox;

    // 相交集相关信息.
    int m_iCount;
    SEVector3f m_aPoint[2];

// 内部使用(共享给IntrRay3Box3f和IntrSegment3Box3f)
public:
    // 使用梁友栋-Barsky裁减算法,计算linear component与box的交点.
    static bool DoClipping(float fT0, float fT1, const SEVector3f& rOrigin,
        const SEVector3f& rDirection, const SEBox3f& rBox, bool bSolid, 
        int& riCount, SEVector3f aPoint[2], int& riIntrType);
};

}

#endif
