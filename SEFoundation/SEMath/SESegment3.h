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

#ifndef Swing_Segment3_H
#define Swing_Segment3_H

#include "SEFoundationLIB.h"
#include "SEVector3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:3维线段类
// 说明:
// 作者:Sun Che
// 时间:20090113
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Segment3f
{
public:
    // 线段表示为参数方程形式:P + t*D,其中P是线段原点,D是单位长度方向向量,
    // |t| <= e,其中e是线段延展长度.
    // 用户必须确保D为单位向量.
    // 线段端点是P - e*D和P + e*D.
    // 线段的表示方法类似于OBB.P是中点,D是单位轴向量,e是轴向延展长度.

    Segment3f(void);
    Segment3f(const Vector3f& rOrigin, const Vector3f& rDirection,
        float fExtent);

    // 端点访问.
    Vector3f GetPosEnd(void) const;  // P + e*D
    Vector3f GetNegEnd(void) const;  // P - e*D

    Vector3f Origin, Direction;
    float Extent;
};

}

#endif
