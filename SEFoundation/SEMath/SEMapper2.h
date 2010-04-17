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

#ifndef Swing_Mapper2_H
#define Swing_Mapper2_H

#include "SEFoundationLIB.h"
#include "SEVector2.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:SEMapper2f类
// 说明:
// 作者:Sun Che
// 时间:20081202
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEMapper2f
{
public:
    // 当计算传入顶点集合的维度时,epsilon值用作相对误差.
    SEMapper2f(int iVCount, const SEVector2f* aVertex, float fEpsilon);
    ~SEMapper2f(void);

    // 传入顶点集合的AABBox.
    const SEVector2f& GetMin(void) const;
    const SEVector2f& GetMax(void) const;
    float GetMaxRange(void) const;

    // 集合的维度(0, 1, 或2).
    int GetDimension(void) const;

    // 坐标系统.对于任何维度d,origin都有效.
    // 单位方向向量在0 <= i < d范围内有效.
    // extreme index与传入顶点数组有关,在0 <= i < d范围内有效.
    // 如果d = 0,则所有顶点都相同,由于使用了epsilon,则extreme index可能不是0.
    // 如果d = 1,则所有顶点都在一条线段上.extreme index表示传入线段的端点.
    // 如果d = 2,则前两个extreme index表示一条线段.
    // 之后的extreme index表示在垂直于这条线段的方向上,距离该线段最远的顶点.
    const SEVector2f& GetOrigin(void) const;
    const SEVector2f& GetDirection(int i) const;
    int GetExtremeIndex(int i) const;

    // 如果d = 2,则方向向量{U0,U1}构成右手坐标系.
    // 三个极值顶点构成一个三角形.函数表明该三角形是否为逆时针索引顺序.
    bool GetExtremeCCW(void) const;

private:
    // 传入顶点的AABBox.
    // maximum range是max[0]-min[0]和max[1]-min[1]中的较大者.
    SEVector2f m_Min, m_Max;
    float m_fMaxRange;

    // 传入顶点集合的固有维度.
    // 在判断维度时,传给构造函数的参数fEpsilon用来提供一个相对误差值.
    int m_iDimension;

    // 用来定义maximum dimensional extents的索引值.
    // m_aiExtreme[0]和m_aiExtreme[1]是两个顶点索引,
    // 这两个顶点定义了具备最大extent的坐标轴向.
    // 如果固有维度是2,则m_aiExtreme[2]是另一个有效的顶点索引,
    // 该顶点定义了垂直于m_aiExtreme[0]和m_aiExtreme[1]坐标轴向上的最大extent.
    // 三角形<V[extreme0],V[extreme1],V[extreme2]>可以是顺时针或者逆时针索引顺序,
    // 由m_bExtremeCCW表明.
    int m_aiExtreme[3];
    bool m_bExtremeCCW;

    SEVector2f m_Origin;
    SEVector2f m_aDirection[2];
};

}

#endif
