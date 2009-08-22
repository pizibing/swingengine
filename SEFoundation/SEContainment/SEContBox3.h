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

#ifndef Swing_ContBox3_H
#define Swing_ContBox3_H

#include "SEFoundationLIB.h"
#include "SEBox3.h"

namespace Swing
{

// 根据输入的若干顶点,计算其最小AABB.
SE_FOUNDATION_API Box3f ContAABBf(int iCount, const Vector3f* aPoint);

// 根据输入的若干顶点,计算其OBB,OBB中心是顶点平均中心,
// OBB轴是顶点协方差矩阵的特征向量.
SE_FOUNDATION_API Box3f ContOBBf(int iCount, const Vector3f* aPoint);

// 测试指定顶点是否包含于盒子内.
SE_FOUNDATION_API bool IsInBoxf(const Vector3f& rPoint, const Box3f& rBox);

// 计算包含两个OBB的新OBB,该OBB不能保证最小.
SE_FOUNDATION_API Box3f MergeBoxesf(const Box3f& rBox0, const Box3f& rBox1);

}

#endif