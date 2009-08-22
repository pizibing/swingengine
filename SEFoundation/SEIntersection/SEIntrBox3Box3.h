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

#ifndef Swing_IntrBox3Box3_H
#define Swing_IntrBox3Box3_H

#include "SEFoundationLIB.h"
#include "SEIntersector.h"
#include "SEBox3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:IntrBox3Box3f类
// 说明:
// 作者:Sun Che
// 时间:20081230
//----------------------------------------------------------------------------
class SE_FOUNDATION_API IntrBox3Box3f
    : public Intersector<float, Vector3f>
{
public:
    IntrBox3Box3f(const Box3f& rBox0, const Box3f& rBox1);

    // 对象访问.
    const Box3f& GetBox0(void) const;
    const Box3f& GetBox1(void) const;

    // static test-intersection查询.
    virtual bool Test(void);

    // dynamic test-intersection查询.计算first contact time(如果有的话),
    // 但没有任何关于contact set的信息.
    virtual bool Test(float fTMax, const Vector3f& rVelocity0,
        const Vector3f& rVelocity1);

private:
    // 用于支持dynamic查询.  
    // 输入参数包括: 两个box在一个潜在分离轴上的各自投影区间,
    // 两区间运动的相对速度值,以及查询所指定的最大时间值.
    // 输出参数包括: first/last contact time.
    // 当这个函数针对不同的潜在分离轴被频繁调用时,相应的输出参数也被不断更新.
    // 输出的first contact time只有在大于输入的first contact time时才更新.
    // 输出的last contact time只有在小于输入的last contact time时才更新.
    bool IsSeparated(float fMin0, float fMax0, float fMin1, float fMax1,
        float fSpeed, float fTMax, float& rfTFirst, float& rfTLast);

    // 待检查对象.
    const Box3f* m_pBox0;
    const Box3f* m_pBox1;
};

}

#endif
