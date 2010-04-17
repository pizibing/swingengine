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

#ifndef Swing_BoundingVolumeTree_H
#define Swing_BoundingVolumeTree_H

#include "SEFoundationLIB.h"
#include "SEBoundingVolume.h"
#include "SELine3.h"
#include "SETriMesh.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:Bounding volume tree基类
// 说明:
// 作者:Sun Che
// 时间:20081223
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEBoundingVolumeTree
{
public:
    // 虚基类.
    virtual ~SEBoundingVolumeTree(void);

    // 树拓扑.
    inline SEBoundingVolumeTree* GetLChild(void);
    inline SEBoundingVolumeTree* GetRChild(void);
    inline bool IsInteriorNode(void) const;
    inline bool IsLeafNode(void) const;

    // 成员访问.
    inline const TriMesh* GetMesh(void) const;
    inline const BoundingVolume* GetWorldBound(void) const;
    inline int GetTriangleCount(void) const;
    inline int GetTriangle(int i) const;
    inline const int* GetTriangles(void) const;

    void UpdateWorldBound(void);

protected:
    SEBoundingVolumeTree(const TriMesh* pMesh);
    SEBoundingVolumeTree(int eBVType, const TriMesh* pMesh,
        int iMaxTrisPerLeaf = 1, bool bStoreInteriorTris = false);

    void BuildTree(int eBVType, int iMaxTrisPerLeaf, bool bStoreInteriorTris,
        const SEVector3f* aCentroid, int i0, int i1, int* aiISplit,
        int* aiOSplit);

    static void SplitTriangles(const SEVector3f* aCentroid, int i0, int i1,
        int* aiISplit, int& rj0, int& rj1, int* aiOSplit,
        const SELine3f& rLine);

    // 关于如何拆分一个三角网格:
    // 所有三角面的中心用于拆分网格.
    // 这些中心被投影到一个用于拆分网格的轴向量上并存储起来.
    // 拆分基于这些投影值的中间值.用对应中间值的三角面,对网格进行二分化.

    // 用于三角面中心在投影轴上的投影点的快速排序.
    class SE_FOUNDATION_API ProjectionInfo
    {
    public:
        int m_iTriangle;
        float m_fProjection;
    };
    static int Compare(const void* pvElement0, const void* pvElement1);

    // 模型空间BV的工厂函数表.
    typedef BoundingVolume* (*CreatorM)(const TriMesh*, int, int, int*, SELine3f&);
    static CreatorM ms_aoCreateModelBound[BoundingVolume::BV_COUNT];

    // 世界空间BV的工厂函数表.
    typedef BoundingVolume* (*CreatorW)(void);
    static CreatorW ms_aoCreateWorldBound[BoundingVolume::BV_COUNT];

    // 网格及其BV.
    const TriMesh* m_pMesh;
    BoundingVolumePtr m_spModelBound;
    BoundingVolumePtr m_spWorldBound;

    // 二叉树表示.
    SEBoundingVolumeTree* m_pLChild;
    SEBoundingVolumeTree* m_pRChild;

    // 构造函数中如果bStoreInteriorTris设置为false,
    // 则所有内部节点设置m_iTriangleCount为零,并且m_aiTriangle为空.
    // 所有叶子节点存储实际数量的该节点三角形数(iMaxTrianglesPerLeaf设置为1时,
    // 则实际数量也为1),并且分配与之对应大小的数组,用于存储相应三角面在顶层
    // 构造函数传入的初始网格中的索引值.
    //
    // 如果bStoreInteriorTris设置为true,
    // 则所有内部节点也都存储与其对应的相应数量的三角面索引值数组.
    int m_iTriangleCount;
    int* m_aiTriangle;

#ifdef _DEBUG_TEST
    // 检查每个节点所表示的子网格的全部顶点是否都在该节点的模型空间BV中.
    // 只有定义了_DEBUG_TEST且bStoreInteriorTris为true时才有效.
    bool ContainsLeafData(const VertexBuffer* pVBuffer, const int* aiIndex,
        float fEpsilon) const;
#endif
};

#include "SEBoundingVolumeTree.inl"

}

#endif
