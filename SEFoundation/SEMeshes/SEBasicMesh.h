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

#ifndef Swing_BasicMesh_H
#define Swing_BasicMesh_H

#include "SEFoundationLIB.h"
#include "SEVector3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:Basic mesh类
// 说明:
// 作者:Sun Che
// 时间:20081123
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEBasicMesh
{
public:
    // 输入的顶点数是iVCount.
    // 顶点数组由aPoint传递,但传递的内容可以是任意数据类型(比如points+attributes).
    // 三角形数是iTCount.三角形由三个int索引表示,由aiIndex传递.
    // 调用者有责任删除传入的数组.

    SEBasicMesh(int iVCount, const void* aPoint, int iTCount,
        const int* aiIndex);

    virtual ~SEBasicMesh(void);

    // 传入数据必须为合法mesh数据.
    // 也就是说其所有edge只能被两个和两个以下的三角型所共享.
    // 在构建过程中,如果一个edge被两个以上的三角形共享,则IsValid返回false.
    // 否则返回true.
    inline bool IsValid(void) const;

    class SE_FOUNDATION_API SEBMVertex
    {
    public:
        SEBMVertex(void);
        ~SEBMVertex(void);

        enum { MV_CHUNK = 8 };

        void InsertEdge(int iV, int iE);
        void InsertTriangle(int iT);

        // 邻接顶点/边,必然相等.
        int VCount;
        int* V;
        int* E;
        // 邻接三角面.
        int TCount;
        int* T;
    };

    class SE_FOUNDATION_API SEBMEdge
    {
    public:
        SEBMEdge(void);

        int V[2];
        int T[2];
    };

    class SE_FOUNDATION_API SEBMTriangle
    {
    public:
        SEBMTriangle(void);

        int V[3];
        int E[3];
        int T[3];
    };

    inline int GetVCount(void) const;
    inline int GetECount(void) const;
    inline int GetTCount(void) const;
    inline const void* GetPoints(void) const;
    inline const int* GetIndices(void) const;
    inline const SEBMVertex* GetVertices(void) const;
    inline const SEBMEdge* GetEdges(void) const;
    inline const SEBMTriangle* GetTriangles(void) const;

protected:
    int m_iVCount, m_iECount, m_iTCount;
    const void* m_aPoint;
    const int* m_aiIndex;
    SEBMVertex* m_aVertex;
    SEBMEdge* m_aEdge;
    SEBMTriangle* m_aTriangle;
    bool m_bIsValid;
};

#include "SEBasicMesh.inl"

}

#endif
