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

#ifndef Swing_RoamTerrainPage_H
#define Swing_RoamTerrainPage_H

#include "SEFoundationLIB.h"
#include "SETriMesh.h"
#include "SERoamTerrainPatch.h"
#include "SERoamTriTreeNode.h"

namespace Swing
{

class RoamTerrain;

//   Y 
//   |
//   |----------------
//   | \     | \     |
//   |   \   |   \   |
//   |     \ |     \ |
//   |----------------
//   | \  R  | \     |
//   |   \   |   \   |
//   | L   \ |     \ |
//   |--------------------X
//
// 我们采用左手坐标系,
// 地形mesh存储在model space中,
// 地形的Y轴经过世界变换,应对齐世界坐标系的Z轴,地形的X轴经过世界变换,
// 对齐世界坐标系的X轴,地形Z轴为采样高度轴,经过世界变换,对齐世界坐标系的Y轴,
// 高度图为(2^N+1)*(2^N+1)的采样点数组,
// 一个Terrain page对应一个高度图,
// 一个Terrain page由N*N个Terrain patch组成,
// 一个Terrain patch由Left base triangle与Right base triangle组成,如上图.
//
// ROAM(Real-time Optimally Adapting Meshes) Terrain LOD:
// http://www.cognigraph.com/ROAM_homepage/
// 此实现采用ROAM的一个变种算法,此算法每frame都split而没有merge,
// 没有frame-coherence,采用二叉三角树递归算法,
// 替代了priority queue的维护,注意如果采用priority queue则会提升CPU开销,
// heap-based queue的维护代价过高,此时应采用bucket-based queue.
//
// 由于GPU三角形吞吐能力大为提高,现阶段ROAM LOD的CPU瓶颈问题已经突现,
// 在某些设备上,使用GPU直接处理大量顶点数据效率可能会更高.

//----------------------------------------------------------------------------
// 名称:ROAM地形页面类
// 说明:
// 作者:jazzboysc
// 时间:20070601
//----------------------------------------------------------------------------
class SE_FOUNDATION_API RoamTerrainPage : public TriMesh
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    RoamTerrainPage(const Attributes& rAttr, int iSize,
        unsigned short* ausHeight, const Vector2f& rOrigin,
        float fMinElevation, float fMaxElevation, float fSpacing,
        float fUVBias, int iPoolSize, int iPatchSize, int iSplitLevel, 
        int iVarianceLevel);

    virtual ~RoamTerrainPage(void);

    // 高度图访问.
    inline int GetSize(void) const;
    inline const unsigned short* GetHeights(void) const;
    inline const Vector2f& GetOrigin(void) const;
    inline float GetMinElevation(void) const;
    inline float GetMaxElevation(void) const;
    inline float GetSpacing(void) const;

    // 获取高度.
    // 如果不在page中,则返回INFINITY.
    float GetHeight(float fX, float fZ) const;

    // page的顶点纹理坐标可以从VB中获取.
    // bias从该函数获取.
    inline float& UVBias(void);

    // 初始frame varience(应该设置为较高,程序将会自动调整该值)
    float FrameVariance;
    
    // 每frame所期望的二叉三角树tessellation的数值,
    // 并不是实际渲染的三角形数量,
    // 是实际渲染的三角形的2倍左右
    static int DesiredTris;
    // 当前frame已经渲染的三角形数量
    static int NumTrisRendered;
    std::vector<RoamTriTreeNode*> Triangles;

protected:
    // streaming support.
    RoamTerrainPage(void);
    void InitializeDerivedData(void);

    // simplification.
    friend class RoamTerrain;
    void ResetPatches(void);
    void SimplifyPatches(const Camera* pCamera, Culler& rCuller);
    void CollectPatches(void);

    // page管理信息.
    inline void SetPageGrid(int iRow, int iCol, RoamTerrain* pTerrain);
    int m_iRow, m_iCol;
    RoamTerrain* m_pTerrain;  // 避免智能指针互指,不需要streaming.

    // tessellation.
    inline float GetX(int iX) const;
    inline float GetZ(int iZ) const;
    inline float GetHeight(int iIndex) const;
    inline float GetTextureCoordinate(int iIndex) const;

    // 用于重建IB.
    virtual void GetUnculledSet(Culler& rCuller, bool bNoCull);
	
    inline int GetNextTriNode(void) const;
    inline void SetNextTriNode(int iNextNode);

    // 高度图数据.
    int m_iSize, m_iSizeM1, m_iPatchSizeM1;
    unsigned short* m_ausHeight;
    Vector2f m_Origin;
    float m_fMinElevation, m_fMaxElevation, m_fSpacing;
    float m_fInvSpacing, m_fTextureSpacing, m_fMultiplier;

    // ROAM相关page信息.
    int m_iPatchesPerSide;
    int m_iPoolSize;
    int m_iPatchSize;
    int m_iSplitLevel;
    int m_iVarianceLevel; // 最小为2
    int m_iMaxIndexCount;

    // 在Lod模式下Simplify后,需要设置为true,从而允许重建IB.
    bool m_bNeedsTessellation;

    // 切换到非Lod模式后,需要设置为true,从而允许重建IB.
    bool m_bNeedsResetIB;

    // patch数组,必须是n*n个patch.
    mutable std::vector<std::vector<RoamTerrainPatch> > m_Patches;

    friend class RoamTerrainPatch;
    RoamTriTreeNode* AllocateTri(void);
    int m_iNextTriNode;										
    std::vector<RoamTriTreeNode> m_TriPool;

    // texture参数.
    float m_fUVBias;
};

typedef SmartPointer<RoamTerrainPage> RoamTerrainPagePtr;
#include "SERoamTerrainPage.inl"

}

#endif