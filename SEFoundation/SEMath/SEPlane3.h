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

#ifndef Swing_Plane_H
#define Swing_Plane_H

#include "SEVector3.h"

// 设3维平面的法线向量为单位向量N,且已知平面上一点P0,平面上任意一点P,
// 则平面方程可表示为Dot(N,(P - P0)) = 0;进一步表示为Dot(N,P) = c.

// 平面采用左手坐标系与左手原则,设平面上3点为P0,P1,P2,则平面法线N的
// 方向为左手顺时针索引P0,P1,P2的叉积向量方向.
// 注意DirectX采用左手顺时针索引,而OpenGL采用右手逆时针索引,
// 设DirectX方式的三角面<P0,P1,P2>,则OpenGL中应为<P0,P2,P1>.

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:3维平面类
// 说明:
// 作者:Sun Che
// 时间:20070522
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Plane3f
{
public:
    Plane3f(void);
    Plane3f(const Plane3f& rPlane);
    // 用单位向量法线和常量构建
    Plane3f(const Vector3f& rNormal, float fConstant);
    // 用单位向量法线和平面上一点构建
    Plane3f(const Vector3f& rNormal, const Vector3f& rP0);
    // 用平面上3点构建
    Plane3f(const Vector3f& rP0, const Vector3f& rP1, const Vector3f& rP2);

    Plane3f& operator = (const Plane3f& rPlane);

    // 点P在平面正面返回1,在平面上返回0,在平面负面返回-1
    inline int OnWhichSide(const Vector3f& rP) const;
    // 计算点P到平面的距离
    inline float GetDistance(const Vector3f& rP) const;

public:
    Vector3f Normal;
    float Constant;
};

#include "SEPlane3.inl"

}

#endif