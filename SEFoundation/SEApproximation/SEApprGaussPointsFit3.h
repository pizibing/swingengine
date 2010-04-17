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

#ifndef Swing_ApprGaussPointsFit3_H
#define Swing_ApprGaussPointsFit3_H

#include "SEFoundationLIB.h"
#include "SEBox3.h"

namespace Swing
{

// 用Gaussian distribution创建box,
// 中心点是平均顶点中心,
// 轴是规范正交基,由顶点协方差矩阵的特征向量构成,
// 特征向量对应的特征值用作Box的半长,半宽,半高,
// 特征向量顺序与特征值顺序对应,特征值由小到大排列
SE_FOUNDATION_API SEBox3f GaussPointsFit3f(int iCount, const SEVector3f* aPoint);

}

#endif
