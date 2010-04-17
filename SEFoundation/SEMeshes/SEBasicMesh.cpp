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

#include "SEFoundationPCH.h"
#include "SEBasicMesh.h"
#include "SEEdgeKey.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEBasicMesh::SEBasicMesh(int iVCount, const void* aPoint, int iTCount,
    const int* aiIndex)
{
    SE_ASSERT( iVCount > 0 && iTCount > 0 && aiIndex );

    if( iVCount <= 0 || iTCount <= 0 || !aiIndex )
    {
        m_iVCount = 0;
        m_iECount = 0;
        m_iTCount = 0;
        m_aVertex = 0;
        m_aEdge = 0;
        m_aTriangle = 0;
        m_aPoint = 0;
        m_aiIndex = 0;
        m_bIsValid = false;

        return;
    }

    m_iVCount = iVCount;
    m_iECount = 0;
    m_iTCount = iTCount;
    m_aPoint = aPoint;
    m_aiIndex = aiIndex;
    m_bIsValid = true;

    // 根据传入数据动态创建triangle mesh.
    m_aVertex = SE_NEW SEBMVertex[m_iVCount];
    m_aEdge = SE_NEW SEBMEdge[3*m_iTCount];
    m_aTriangle = SE_NEW SEBMTriangle[m_iTCount];
    std::map<SEEdgeKey, int> tempEMap;
    for( int iT = 0; iT < m_iTCount; iT++ )
    {
        // 更新triangle.
        SEBMTriangle& rTriangle = m_aTriangle[iT];
        rTriangle.V[0] = *aiIndex++;
        rTriangle.V[1] = *aiIndex++;
        rTriangle.V[2] = *aiIndex++;

        // 为mesh添加edges.
        for( int i0 = 2, i1 = 0; i1 < 3; i0 = i1++ )
        {
            // 更新vertices.
            m_aVertex[rTriangle.V[i1]].InsertTriangle(iT);

            SEEdgeKey tempKey(rTriangle.V[i0], rTriangle.V[i1]);
            std::map<SEEdgeKey, int>::iterator tempEIter = tempEMap.find(tempKey);
            if( tempEIter == tempEMap.end() )
            {
                // 第一次遇到该edge.
                tempEMap[tempKey] = m_iECount;

                // 更新edge.
                SEBMEdge& rEdge = m_aEdge[m_iECount];
                rEdge.V[0] = rTriangle.V[i0];
                rEdge.V[1] = rTriangle.V[i1];
                rEdge.T[0] = iT;

                // 更新vertices.
                m_aVertex[rEdge.V[0]].InsertEdge(rEdge.V[1], m_iECount);
                m_aVertex[rEdge.V[1]].InsertEdge(rEdge.V[0], m_iECount);

                // 更新triangle.
                rTriangle.E[i0] = m_iECount;

                m_iECount++;
            }
            else
            {
                // 第二次遇到该edge.
                int iE = tempEIter->second;
                SEBMEdge& rEdge = m_aEdge[iE];

                // 更新edge.
                SE_ASSERT( rEdge.T[1] == -1 );  // 只能被两个三角形共享
                if( rEdge.T[1] != -1 )
                {
                    SE_DELETE[] m_aVertex;
                    SE_DELETE[] m_aEdge;
                    SE_DELETE[] m_aTriangle;
                    m_iVCount = 0;
                    m_iECount = 0;
                    m_iTCount = 0;
                    m_aVertex = 0;
                    m_aEdge = 0;
                    m_aTriangle = 0;
                    m_aPoint = 0;
                    m_aiIndex = 0;
                    m_bIsValid = false;
                }
                rEdge.T[1] = iT;

                // 更新triangles.
                int iAdj = rEdge.T[0];
                SEBMTriangle& rAdj = m_aTriangle[iAdj];
                for( int j = 0; j < 3; j++ )
                {
                    if( rAdj.E[j] == iE )
                    {
                        rAdj.T[j] = iT;
                        break;
                    }
                }
                rTriangle.E[i0] = iE;
                rTriangle.T[i0] = iAdj;
            }
        }
    }
}
//----------------------------------------------------------------------------
SEBasicMesh::~SEBasicMesh()
{
    SE_DELETE[] m_aVertex;
    SE_DELETE[] m_aEdge;
    SE_DELETE[] m_aTriangle;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// SEBasicMesh::SEBMVertex
//----------------------------------------------------------------------------
SEBasicMesh::SEBMVertex::SEBMVertex()
{
    VCount = 0;
    V = 0;
    E = 0;
    TCount = 0;
    T = 0;
}
//----------------------------------------------------------------------------
SEBasicMesh::SEBMVertex::~SEBMVertex()
{
    SE_DELETE[] V;
    SE_DELETE[] E;
    SE_DELETE[] T;
}
//----------------------------------------------------------------------------
void SEBasicMesh::SEBMVertex::InsertEdge(int iV, int iE)
{
    // 添加新的相邻顶点/边.

    // 检查相邻顶点是否已经存在,
    // 从而判断是否已经加入过该edge.
    for( int i = 0; i < VCount; i++ )
    {
        if( iV == V[i] )
        {
            return;
        }
    }

    if( (VCount % MV_CHUNK) == 0 )
    {
        size_t uiDstSize = (VCount + MV_CHUNK)*sizeof(int);
        size_t uiSrcSize = VCount * sizeof(int);

        int* aiSave = V;
        V = SE_NEW int[VCount + MV_CHUNK];
        if( aiSave )
        {
            SESystem::SE_Memcpy(V, uiDstSize, aiSave, uiSrcSize);
            SE_DELETE[] aiSave;
        }

        aiSave = E;
        E = SE_NEW int[VCount + MV_CHUNK];
        if( aiSave )
        {
            SESystem::SE_Memcpy(E, uiDstSize, aiSave, uiSrcSize);
            SE_DELETE[] aiSave;
        }
    }

    V[VCount] = iV;
    E[VCount] = iE;
    VCount++;
}
//----------------------------------------------------------------------------
void SEBasicMesh::SEBMVertex::InsertTriangle(int iT)
{
    // 添加新的相邻三角形.

    // 检查相邻三角形是否已经存在.
    for( int i = 0; i < TCount; i++ )
    {
        if( iT == T[i] )
        {
            return;
        }
    }

    if( (TCount % MV_CHUNK) == 0 )
    {
        int* aiSave = T;
        T = SE_NEW int[TCount + MV_CHUNK];
        if( aiSave )
        {
            size_t uiDstSize = (TCount + MV_CHUNK)*sizeof(int);
            size_t uiSrcSize = TCount * sizeof(int);
            SESystem::SE_Memcpy(T, uiDstSize, aiSave, uiSrcSize);
            SE_DELETE[] aiSave;
        }
    }

    T[TCount] = iT;
    TCount++;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// SEBasicMesh::SEBMEdge
//----------------------------------------------------------------------------
SEBasicMesh::SEBMEdge::SEBMEdge()
{
    for( int i = 0; i < 2; i++ )
    {
        V[i] = -1;
        T[i] = -1;
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// SEBasicMesh::SEBMTriangle
//----------------------------------------------------------------------------
SEBasicMesh::SEBMTriangle::SEBMTriangle()
{
    for( int i = 0; i < 3; i++ )
    {
        V[i] = -1;
        E[i] = -1;
        T[i] = -1;
    }
}
//----------------------------------------------------------------------------
