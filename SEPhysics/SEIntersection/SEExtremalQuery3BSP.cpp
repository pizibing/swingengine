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

#include "SEPhysicsPCH.h"
#include "SEExtremalQuery3BSP.h"
#include "SEBasicMesh.h"

using namespace Swing;

//----------------------------------------------------------------------------
ExtremalQuery3BSPf::ExtremalQuery3BSPf(const ConvexPolyhedron3f& rPolytope)
    :
    ExtremalQuery3f(rPolytope)
{
    // 为多面体创建邻接信息.
    int iVCount = m_pPolytope->GetVCount();
    const Vector3f* aVertex = m_pPolytope->GetVertices();
    int iTCount = m_pPolytope->GetTCount();
    const int* aiIndex = m_pPolytope->GetIndices();
    BasicMesh tempMesh(iVCount, aVertex, iTCount, aiIndex);

    // 创建spherical arc集合,用于创建BSP树.
    std::multiset<SphericalArc> tempArcs;
    CreateSphericalArcs(tempMesh, tempArcs);

    // 创建BSP树,用于极值查询.
    std::vector<SphericalArc> tempNodes;
    CreateBSPTree(tempArcs, tempNodes);

    // 把BSP树复制到固定大小的简单数组中.
    m_iNodeCount = (int)tempNodes.size();
    m_aNode = SE_NEW SphericalArc[m_iNodeCount];
    size_t uiSize = m_iNodeCount * sizeof(SphericalArc);
    SESystem::SE_Memcpy(m_aNode, uiSize, &tempNodes.front(), uiSize);
}
//----------------------------------------------------------------------------
ExtremalQuery3BSPf::~ExtremalQuery3BSPf()
{
    SE_DELETE[] m_aNode;
}
//----------------------------------------------------------------------------
void ExtremalQuery3BSPf::GetExtremeVertices(const Vector3f& rDirection, 
    int& riPositiveDirection, int& riNegativeDirection)
{
    // 非递归深度优先查找BSP树,判断包含指定方向向量D的球面多边形.
    int iCurrent = 0;  // BSP树根
    while( iCurrent >= 0 )
    {
        SphericalArc& rCurrent = m_aNode[iCurrent];
        int iSign = (int)Mathf::Sign(rDirection.Dot(rCurrent.Normal));
        if( iSign >= 0 )
        {
            iCurrent = rCurrent.PosChild;
            if( iCurrent == -1 )
            {
                // 到达叶子节点.
                riPositiveDirection = rCurrent.PosVertex;
            }
        }
        else
        {
            iCurrent = rCurrent.NegChild;
            if( iCurrent == -1 )
            {
                // 到达叶子节点.
                riPositiveDirection = rCurrent.NegVertex;
            }
        }
    }

    // 非递归深度优先查找BSP树,判断包含指定方向向量D的反向向量-D的球面多边形.
    iCurrent = 0;  // BSP树根
    while( iCurrent >= 0 )
    {
        SphericalArc& rCurrent = m_aNode[iCurrent];
        int iSign = (int)-Mathf::Sign(rDirection.Dot(rCurrent.Normal));
        if( iSign >= 0 )
        {
            iCurrent = rCurrent.PosChild;
            if( iCurrent == -1 )
            {
                // 到达叶子节点.
                riNegativeDirection = rCurrent.PosVertex;
            }
        }
        else
        {
            iCurrent = rCurrent.NegChild;
            if( iCurrent == -1 )
            {
                // 到达叶子节点.
                riNegativeDirection = rCurrent.NegVertex;
            }
        }
    }
}
//----------------------------------------------------------------------------
int ExtremalQuery3BSPf::GetNodeCount() const
{
    return m_iNodeCount;
}
//----------------------------------------------------------------------------
int ExtremalQuery3BSPf::GetTreeDepth() const
{
    return m_iTreeDepth;
}
//----------------------------------------------------------------------------
void ExtremalQuery3BSPf::SortVertexAdjacents(BasicMesh& rMesh)
{
    // 指针的typecast将允许对顶点数组进行修改.
    // 只要排序算法正确,修改顶点数组就是安全的.
    int iVCount = rMesh.GetVCount();
    BasicMesh::Vertex* aVertex = (BasicMesh::Vertex*)rMesh.GetVertices();

    const BasicMesh::Triangle* aTriangle = rMesh.GetTriangles();
    for( int i = 0; i < iVCount; i++ )
    {
        // This copy circumvents the constness of the mesh vertices, which
        // allows the sorting of the mesh triangles shared by a mesh vertex.
        BasicMesh::Vertex& rVertex = aVertex[i];

        // 网格构成多面体时必满足条件:该顶点的邻接顶点数等于邻接三角面数.
        SE_ASSERT( rVertex.VCount == rVertex.TCount );

        // 一旦我们有了第一个要进行邻接信息排序的顶点和其初始邻接三角面,
        // 我们就可以从该邻接三角面出发,围着该顶点"走一圈",
        // 有序的访问到该顶点的所有邻接三角面.
        // 如果三角面的顶点索引采用顺时针,则邻接三角面依次访问也将是顺时针顺序.
        // 也就是说整个遍历过程的时针性,取决于我们的数学系统的手向性.
        // 整个过程中,对顶点邻接信息的覆盖是安全的,
        // 因为我们的数据来源取自于其邻接三角面.
        int iTIndex = rVertex.T[0];
        const BasicMesh::Triangle* pTri = &aTriangle[iTIndex];

        for( int iAdj = 0; iAdj < rVertex.VCount; iAdj++ )
        {
            int iPrev, iCurr;
            for( iPrev = 2, iCurr = 0; iCurr < 3; iPrev = iCurr++ )
            {
                if( pTri->V[iCurr] == i )
                {
                    rVertex.V[iAdj] = pTri->V[iPrev];
                    rVertex.E[iAdj] = pTri->E[iPrev];
                    rVertex.T[iAdj] = iTIndex;

                    // 指向即将访问的下一个邻接三角面.
                    iTIndex = pTri->T[iPrev];
                    pTri = &aTriangle[iTIndex];

                    break;
                }
            }

            SE_ASSERT( iCurr < 3 );
        }
    }
}
//----------------------------------------------------------------------------
void ExtremalQuery3BSPf::CreateSphericalArcs(BasicMesh& rMesh,
    std::multiset<SphericalArc>& rArcs)
{
    int iECount = rMesh.GetECount();
    const BasicMesh::Edge* aEdge = rMesh.GetEdges();
    const BasicMesh::Triangle* aTriangle = rMesh.GetTriangles();

    const int aiPrev[3] = { 2, 0, 1 };
    const int aiNext[3] = { 1, 2, 0 };

    for( int i = 0; i < iECount; i++ )
    {
        const BasicMesh::Edge& rEdge = aEdge[i];

        SphericalArc tempArc;
        tempArc.N[0] = rEdge.T[0];
        tempArc.N[1] = rEdge.T[1];
        tempArc.Separation = 1;

        tempArc.Normal = m_aFaceNormal[tempArc.N[0]].Cross(
            m_aFaceNormal[tempArc.N[1]]);

        const BasicMesh::Triangle& rAdj = aTriangle[rEdge.T[0]];
        int j;
        for( j = 0; j < 3; j++ )
        {
            if( rAdj.V[j] != rEdge.V[0] && rAdj.V[j] != rEdge.V[1] )
            {
                tempArc.PosVertex = rAdj.V[aiPrev[j]];
                tempArc.NegVertex = rAdj.V[aiNext[j]];

                break;
            }
        }

        SE_ASSERT( j < 3 );

        rArcs.insert(tempArc);
    }

    CreateSphericalBisectors(rMesh, rArcs);
}
//----------------------------------------------------------------------------
void ExtremalQuery3BSPf::CreateSphericalBisectors(BasicMesh& rMesh,
    std::multiset<SphericalArc>& rArcs)
{
    // 针对每个顶点,对其邻接信息(最后用于邻接三角面法线)进行排序,
    // 使排序后的邻接信息得到的邻接三角面法线,
    // 在spherical dual上构成顺时针顺序的球面多边形(从球外观看).
    SortVertexAdjacents(rMesh);

    int iVCount = rMesh.GetVCount();
    const BasicMesh::Vertex* aVertex = rMesh.GetVertices();
    std::queue<std::pair<int, int> > tempQueue;
    for( int i = 0; i < iVCount; i++ )
    {
        const BasicMesh::Vertex& rVertex = aVertex[i];

        tempQueue.push(std::make_pair(0, rVertex.TCount));
        while( !tempQueue.empty() )
        {
            std::pair<int, int> tempArc = tempQueue.front();
            tempQueue.pop();
            int i0 = tempArc.first, i1 = tempArc.second;
            int iSeparation = i1 - i0;
            if( iSeparation > 1 && iSeparation != rVertex.TCount-1 )
            {
                if( i1 < rVertex.TCount )
                {
                    SphericalArc tempArc;
                    tempArc.N[0] = rVertex.T[i0]; // 待检查
                    tempArc.N[1] = rVertex.T[i1]; // 待检查
                    tempArc.Separation = iSeparation;

                    tempArc.Normal = m_aFaceNormal[tempArc.N[0]].Cross(
                        m_aFaceNormal[tempArc.N[1]]);

                    tempArc.PosVertex = i;
                    tempArc.NegVertex = i;
                    rArcs.insert(tempArc);
                }
                int iMid = (i0 + i1 + 1)/2;
                if( iMid != i1 )
                {
                    tempQueue.push(std::make_pair(i0, iMid));
                    tempQueue.push(std::make_pair(iMid, i1));
                }
            }
        }
    }
}
//----------------------------------------------------------------------------
void ExtremalQuery3BSPf::CreateBSPTree(std::multiset<SphericalArc>& rArcs, 
    std::vector<SphericalArc>& rNodes)
{
    // 至少有一个树根节点.
    m_iTreeDepth = 1;

    std::multiset<SphericalArc>::reverse_iterator tempIter;
    for( tempIter = rArcs.rbegin(); tempIter != rArcs.rend(); tempIter++ )
    {
        InsertArc(*tempIter, rNodes);
    }

    // 在遍历multiset调用InsertArc函数时,叶子节点没有参与深度计数.
    // 因此遍历结束后,增加一次深度计数.
    m_iTreeDepth++;
}
//----------------------------------------------------------------------------
void ExtremalQuery3BSPf::InsertArc(const SphericalArc& rArc,
    std::vector<SphericalArc>& rNodes)
{
    // 传入的arc被存储在节点数组最后.
    if( rNodes.size() > 0 )
    {
        // 为了放置传入arc,对当前BSP树做非递归深度优先查找.
        std::stack<int> tempCandidates;
        tempCandidates.push(0);  // 从BSP树根开始
        while( !tempCandidates.empty() )
        {
            int iCurrent = tempCandidates.top();
            tempCandidates.pop();
            SphericalArc* pCurrent = &rNodes[iCurrent];

            int iSign0;
            if( rArc.N[0] == pCurrent->N[0]
            ||  rArc.N[0] == pCurrent->N[1] )
            {
                iSign0 = 0;
            }
            else
            {
                iSign0 = (int)Mathf::Sign(
                    m_aFaceNormal[rArc.N[0]].Dot(pCurrent->Normal));
            }

            int iSign1;
            if( rArc.N[1] == pCurrent->N[0]
            ||  rArc.N[1] == pCurrent->N[1] )
            {
                iSign1 = 0;
            }
            else
            {
                iSign1 = (int)Mathf::Sign(
                    m_aFaceNormal[rArc.N[1]].Dot(pCurrent->Normal));
            }

            int iDoTest = 0;
            if( iSign0*iSign1 < 0 )
            {
                // 传入arc与当前arc相交,因此把传入arc同时传递给左右子节点.
                iDoTest = 3;
            }
            else if( iSign0 > 0 || iSign1 > 0 )
            {
                // 传入arc在当前arc正半球面空间.
                iDoTest = 1;
            }
            else if( iSign0 < 0 || iSign1 < 0 )
            {
                // 传入arc在当前arc负半球面空间.
                iDoTest = 2;
            }
            // 否则 iSign0 = iSign1 = 0,表明待插入arc与当前arc共面.
            // 则没有必要插入该arc了.

            int iDepth;

            if( iDoTest & 1 )
            {
                if( pCurrent->PosChild != -1 )
                {
                    tempCandidates.push(pCurrent->PosChild);
                    iDepth = (int)tempCandidates.size();
                    if( iDepth > m_iTreeDepth )
                    {
                        m_iTreeDepth = iDepth;
                    }
                }
                else
                {
                    pCurrent->PosChild = (int)rNodes.size();
                    rNodes.push_back(rArc);

                    // push_back可能造成vector重新分配内存,因此刷新current指针.
                    pCurrent = &rNodes[iCurrent];
                }
            }

            if( iDoTest & 2 )
            {
                if( pCurrent->NegChild != -1 )
                {
                    tempCandidates.push(pCurrent->NegChild);
                    iDepth = (int)tempCandidates.size();
                    if( iDepth > m_iTreeDepth )
                    {
                        m_iTreeDepth = iDepth;
                    }
                }
                else
                {
                    pCurrent->NegChild = (int)rNodes.size();
                    rNodes.push_back(rArc);
                }
            }
        }
    }
    else
    {
        // 根节点.
        rNodes.push_back(rArc);
    }
}
//----------------------------------------------------------------------------
