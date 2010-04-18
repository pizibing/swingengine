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

#ifndef Swing_ExtremalQuery3BSP_H
#define Swing_ExtremalQuery3BSP_H

#include "SEPhysicsLIB.h"
#include "SEExtremalQuery3.h"

namespace Swing
{

class SEBasicMesh;

class SE_PHYSICS_API SEExtremalQuery3BSPf : public SEExtremalQuery3f
{
public:
    SEExtremalQuery3BSPf(const SEConvexPolyhedron3f& rPolytope);
    virtual ~SEExtremalQuery3BSPf(void);

    // 根据指定方向,计算多面体在该方向上的极值顶点,
    // 并返回那些顶点在顶点数组中的索引.
    virtual void GetExtremeVertices(const SEVector3f& rDirection,
        int& riPositiveDirection, int& riNegativeDirection);

    // tree statistics.
    int GetNodeCount(void) const;
    int GetTreeDepth(void) const;

private:
    class SE_PHYSICS_API SESphericalArc
    {
    public:
        SESphericalArc()
        {
            PosChild = -1;
            NegChild = -1;
        }

        // 对应arc两端点的三角面法线的索引.
        int N[2];

        // 从法线N[0]到达法线N[1]的路径所经过的arc数量.
        // 对于球面多边形的边arc,该值为1.
        // 对于球面多边形的bisector arc,该值大于等于2.
        int Separation;

        // 该法线为:Cross(FaceNormal[N[0]], FaceNormal[N[1]]).
        SEVector3f Normal;

        // 共享该arc的两个球面多边形代表针对该arc的两个潜在极值顶点.
        // 当从arc的N[0]端点向N[1]端点移动时,根据左手原则,
        // arc右手边的潜在极值顶点,由PosVertex索引.
        // arc左手边的潜在极值顶点,由NegVertex索引.
        int PosVertex, NegVertex;

        // BSP树子节点索引.
        int PosChild, NegChild;

        // 实现运算符<的重载,从而允许本类型被用于stl的multiset.
        // 全部arc根据separation值,被增序存储在multiset中.
        // 访问multiset进行BSP树创建时,逆序访问,separation值大的优先处理.
        // 这种启发式算法确保了BSP树的平衡性,
        // 从而在极值查询时,顶层节点尽可能多的剔除掉大量arc.
        bool operator < (const SESphericalArc& rArc) const
        {
            return Separation < rArc.Separation;
        }
    };

    void SortVertexAdjacents(SEBasicMesh& rMesh);
    void CreateSphericalArcs(SEBasicMesh& rMesh,
        std::multiset<SESphericalArc>& rArcs);
    void CreateSphericalBisectors(SEBasicMesh& rMesh,
        std::multiset<SESphericalArc>& rArcs);

    void CreateBSPTree(std::multiset<SESphericalArc>& rArcs,
        std::vector<SESphericalArc>& rNodes);
    void InsertArc(const SESphericalArc& rArc,
        std::vector<SESphericalArc>& rNodes);

    // BSP节点的固定大小存储空间.
    int m_iNodeCount;
    SESphericalArc* m_aNode;
    int m_iTreeDepth;
};

}

#endif
