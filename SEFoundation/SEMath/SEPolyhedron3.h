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

#ifndef Swing_Polyhedron3_H
#define Swing_Polyhedron3_H

#include "SEFoundationLIB.h"
#include "SEVector3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:Polyhedron类
// 说明:
// 作者:Sun Che
// 时间:20081124
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Polyhedron3f
{
public:
    // simple polyhedron:每个edge最多被两个三角形共享,三角面没有自相交的情况.

    // 调用者有责任确保传入的数据构成simple polyhedron.
    // 从外侧观看mesh时,三角面的索引顺序应为顺时针方向.
    // bOwner为true时,polyhedron拥有传入数组的所有权.
    // 否则为false时,由调用者负责删除传入数组.
    Polyhedron3f(int iVCount, Vector3f* aVertex, int iTCount,
        int* aiIndex, bool bOwner);

    // 如果传入的polyhedron拥有其数组数据,则为'this'对象复制其数组数据,
    // 从而使'this'对象也拥有其数组数据.
    // 如果传入的polyhedron不拥有其数组数据,则'this'对象也不拥有.只进行指针共享.
    Polyhedron3f(const Polyhedron3f& rPoly);

    virtual ~Polyhedron3f(void);

    // 如果传入的polyhedron拥有其数组数据,则为'this'对象复制其数组数据,
    // 从而使'this'对象也拥有其数组数据.
    // 如果传入的polyhedron不拥有其数组数据,则'this'对象也不拥有.只进行指针共享.
    Polyhedron3f& operator = (const Polyhedron3f& rPoly);

    int GetVCount(void) const;
    const Vector3f* GetVertices(void) const;
    const Vector3f& GetVertex(int i) const;
    int GetTCount(void) const;
    const int* GetIndices(void) const;
    const int* GetTriangle(int i) const;

    // 允许对顶点进行修改.
    // 但不进行任何几何拓扑校验,不保证仍是simple polyhedron.
    virtual void SetVertex(int i, const Vector3f& rV);
    Vector3f* GetVertices(void);

    // 计算polyhedron的各种相关信息.
    Vector3f ComputeVertexAverage(void) const; // 平均顶点中心
    float ComputeSurfaceArea(void) const; // 表面积
    float ComputeVolume(void) const; // 体积

protected:
    int m_iVCount;
    Vector3f* m_aVertex;
    int m_iTCount;
    int* m_aiIndex;
    bool m_bOwner;
};

}

#endif
