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
#include "SEConvexHull3.h"
#include "SEMapper3.h"
#include "SEQuery3Filtered.h"
#include "SEQuery3Int64.h"
#include "SEQuery3TInteger.h"
#include "SEQuery3TRational.h"

using namespace Swing;

//----------------------------------------------------------------------------
ConvexHull3f::ConvexHull3f(int iVertexCount,  Vector3f* aVertex, 
    float fEpsilon,  bool bOwner,  Query::Type eQueryType)
    :
    ConvexHullf(iVertexCount,  fEpsilon,  bOwner,  eQueryType), 
    m_LineOrigin(Vector3f::ZERO), 
    m_LineDirection(Vector3f::ZERO), 
    m_PlaneOrigin(Vector3f::ZERO)
{
    SE_ASSERT( aVertex );

    m_aVertex = aVertex;
    m_aPlaneDirection[0] = Vector3f::ZERO;
    m_aPlaneDirection[1] = Vector3f::ZERO;
    m_aSVertex = 0;
    m_pQuery = 0;

    Mapper3f tempMapper(m_iVertexCount,  m_aVertex,  m_fEpsilon);
    if( tempMapper.GetDimension() == 0 )
    {
        // The values of m_iDimension,  m_aiIndex,  and m_aiAdjacent were
        // already initialized by the ConvexHullf base class.
        return;
    }

    if( tempMapper.GetDimension() == 1 )
    {
        // The set is (nearly) collinear.  The caller is responsible for
        // creating a ConvexHull1f object.
        m_iDimension = 1;
        m_LineOrigin = tempMapper.GetOrigin();
        m_LineDirection = tempMapper.GetDirection(0);

        return;
    }

    if( tempMapper.GetDimension() == 2 )
    {
        // The set is (nearly) coplanar.  The caller is responsible for
        // creating a Delaunay2 object.
        m_iDimension = 2;
        m_PlaneOrigin = tempMapper.GetOrigin();
        m_aPlaneDirection[0] = tempMapper.GetDirection(0);
        m_aPlaneDirection[1] = tempMapper.GetDirection(1);

        return;
    }

    m_iDimension = 3;

    int i0 = tempMapper.GetExtremeIndex(0);
    int i1 = tempMapper.GetExtremeIndex(1);
    int i2 = tempMapper.GetExtremeIndex(2);
    int i3 = tempMapper.GetExtremeIndex(3);

    m_aSVertex = SE_NEW Vector3f[m_iVertexCount];
    int i;

    if( eQueryType != Query::QT_RATIONAL && eQueryType != Query::QT_FILTERED )
    {
        // Transform the vertices to the cube [0, 1]^3.
        Vector3f vec3fMin = tempMapper.GetMin();
        float fScale = 1.0f / tempMapper.GetMaxRange();
        for( i = 0; i < m_iVertexCount; i++ )
        {
            m_aSVertex[i] = (m_aVertex[i] - vec3fMin)*fScale;
        }

        float fExpand;
        if( eQueryType == Query::QT_INT64 )
        {
            // Scale the vertices to the square [0, 2^{20}]^2 to allow use of
            // 64-bit integers.
            fExpand = (float)(1 << 20);
            m_pQuery = SE_NEW Query3Int64f(m_iVertexCount,  m_aSVertex);
        }
        else if( eQueryType == Query::QT_INTEGER )
        {
            // Scale the vertices to the square [0, 2^{24}]^2 to allow use of
            // TInteger.
            fExpand = (float)(1 << 24);
            m_pQuery = SE_NEW Query3TIntegerf(m_iVertexCount,  m_aSVertex);
        }
        else  // eQueryType == Query::QT_REAL
        {
            // No scaling for floating point.
            fExpand = 1.0f;
            m_pQuery = SE_NEW Query3f(m_iVertexCount,  m_aSVertex);
        }

        for( i = 0; i < m_iVertexCount; i++ )
        {
            m_aSVertex[i] *= fExpand;
        }
    }
    else
    {
        // No transformation needed for exact rational arithmetic or filtered
        // predicates.
        size_t uiSize = m_iVertexCount * sizeof(Vector3f);
        SESystem::SE_Memcpy(m_aSVertex,  uiSize,  m_aVertex,  uiSize);

        if( eQueryType == Query::QT_RATIONAL )
        {
            m_pQuery = SE_NEW Query3TRationalf(m_iVertexCount,  m_aSVertex);
        }
        else // eQueryType == Query::QT_FILTERED
        {
            m_pQuery = SE_NEW Query3Filteredf(m_iVertexCount,  m_aSVertex,  
                m_fEpsilon);
        }
    }

    HullTriangle3f* pT0;
    HullTriangle3f* pT1;
    HullTriangle3f* pT2;
    HullTriangle3f* pT3;

    if( tempMapper.GetExtremeCCW() )
    {
        pT0 = SE_NEW HullTriangle3f(i0,  i1,  i3);
        pT1 = SE_NEW HullTriangle3f(i0,  i2,  i1);
        pT2 = SE_NEW HullTriangle3f(i0,  i3,  i2);
        pT3 = SE_NEW HullTriangle3f(i1,  i2,  i3);
        pT0->AttachTo(pT1,  pT3,  pT2);
        pT1->AttachTo(pT2,  pT3,  pT0);
        pT2->AttachTo(pT0,  pT3,  pT1);
        pT3->AttachTo(pT1,  pT2,  pT0);
    }
    else
    {
        pT0 = SE_NEW HullTriangle3f(i0,  i3,  i1);
        pT1 = SE_NEW HullTriangle3f(i0,  i1,  i2);
        pT2 = SE_NEW HullTriangle3f(i0,  i2,  i3);
        pT3 = SE_NEW HullTriangle3f(i1,  i3,  i2);
        pT0->AttachTo(pT2,  pT3,  pT1);
        pT1->AttachTo(pT0,  pT3,  pT2);
        pT2->AttachTo(pT1,  pT3,  pT0);
        pT3->AttachTo(pT0,  pT2,  pT1);
    }

    m_Hull.clear();
    m_Hull.insert(pT0);
    m_Hull.insert(pT1);
    m_Hull.insert(pT2);
    m_Hull.insert(pT3);

    for( i = 0; i < m_iVertexCount; i++ )
    {
        if( !Update(i) )
        {
            DeleteHull();
            return;
        }
    }

    ExtractIndices();
}
//----------------------------------------------------------------------------
ConvexHull3f::~ConvexHull3f()
{
    if( m_bOwner )
    {
        SE_DELETE[] m_aVertex;
    }
    SE_DELETE[] m_aSVertex;
    SE_DELETE m_pQuery;
}
//----------------------------------------------------------------------------
const Vector3f& ConvexHull3f::GetLineOrigin() const
{
    return m_LineOrigin;
}
//----------------------------------------------------------------------------
const Vector3f& ConvexHull3f::GetLineDirection() const
{
    return m_LineDirection;
}
//----------------------------------------------------------------------------
const Vector3f& ConvexHull3f::GetPlaneOrigin() const
{
    return m_PlaneOrigin;
}
//----------------------------------------------------------------------------
const Vector3f& ConvexHull3f::GetPlaneDirection(int i) const
{
    SE_ASSERT( 0 <= i && i < 2 );

    return m_aPlaneDirection[i];
}
//----------------------------------------------------------------------------
ConvexHull1f* ConvexHull3f::GetConvexHull1() const
{
    SE_ASSERT( m_iDimension == 1 );

    if( m_iDimension != 1 )
    {
        return 0;
    }

    float* afProjection = SE_NEW float[m_iVertexCount];
    for( int i = 0; i < m_iVertexCount; i++ )
    {
        Vector3f vec3fDiff = m_aVertex[i] - m_LineOrigin;
        afProjection[i] = m_LineDirection.Dot(vec3fDiff);
    }

    return SE_NEW ConvexHull1f(m_iVertexCount,  afProjection, 
        m_fEpsilon,  true,  m_eQueryType);
}
//----------------------------------------------------------------------------
ConvexHull2f* ConvexHull3f::GetConvexHull2() const
{
    SE_ASSERT( m_iDimension == 2 );

    if( m_iDimension != 2 )
    {
        return 0;
    }

    SEVector2f* aProjection = SE_NEW SEVector2f[m_iVertexCount];
    for( int i = 0; i < m_iVertexCount; i++ )
    {
        Vector3f vec3fDiff = m_aVertex[i] - m_PlaneOrigin;
        aProjection[i][0] = m_aPlaneDirection[0].Dot(vec3fDiff);
        aProjection[i][1] = m_aPlaneDirection[1].Dot(vec3fDiff);
    }

    return SE_NEW ConvexHull2f(m_iVertexCount,  aProjection, 
        m_fEpsilon,  true,  m_eQueryType);
}
//----------------------------------------------------------------------------
bool ConvexHull3f::Update(int i)
{
    // Locate a triangle visible to the input point (if possible).
    HullTriangle3f* pVisible = 0;
    HullTriangle3f* pTri;
    std::set<HullTriangle3f*>::iterator tempIter;
    for( tempIter = m_Hull.begin(); tempIter != m_Hull.end(); tempIter++ )
    {
        pTri = *tempIter;
        if( pTri->GetSign(i,  m_pQuery) > 0 )
        {
            pVisible = pTri;
            break;
        }
    }

    if( !pVisible )
    {
        // The point is inside the current hull; nothing to do.
        return true;
    }

    // Locate and remove the visible triangles.
    std::stack<HullTriangle3f*> tempVisible;
    std::map<int,  TerminatorData> tempTerminator;
    tempVisible.push(pVisible);
    pVisible->OnStack = true;
    int j,  iV0,  iV1;
    while( !tempVisible.empty() )
    {
        pTri = tempVisible.top();
        tempVisible.pop();
        pTri->OnStack = false;
        for( j = 0; j < 3; j++ )
        {
            HullTriangle3f* pAdj = pTri->A[j];
            if( pAdj )
            {
                // Detach triangle and adjacent triangle from each other.
                int iNullIndex = pTri->DetachFrom(j,  pAdj);

                if( pAdj->GetSign(i,  m_pQuery) > 0 )
                {
                    if( !pAdj->OnStack )
                    {
                        // Adjacent triangle is visible.
                        tempVisible.push(pAdj);
                        pAdj->OnStack = true;
                    }
                }
                else
                {
                    // Adjacent triangle is invisible.
                    iV0 = pTri->V[j];
                    iV1 = pTri->V[(j + 1) % 3];
                    tempTerminator[iV0] = TerminatorData(iV0,  iV1,  iNullIndex, 
                        pAdj);
                }
            }
        }
        m_Hull.erase(pTri);
        SE_DELETE pTri;
    }

    // Insert the new edges formed by the input point and the terminator
    // between visible and invisible triangles.
    int iSize = (int)tempTerminator.size();
    SE_ASSERT( iSize >= 3 );

    std::map<int,  TerminatorData>::iterator pEdge =
        tempTerminator.begin();
    iV0 = pEdge->second.V[0];
    iV1 = pEdge->second.V[1];
    pTri = SE_NEW HullTriangle3f(i,  iV0,  iV1);
    m_Hull.insert(pTri);

    // save information for linking first/last inserted new triangles
    int iSaveV0 = pEdge->second.V[0];
    HullTriangle3f* pSaveTri = pTri;

    // establish adjacency links across terminator edge
    pTri->A[1] = pEdge->second.Tri;
    pEdge->second.Tri->A[pEdge->second.NullIndex] = pTri;
    for( j = 1; j < iSize; j++ )
    {
        pEdge = tempTerminator.find(iV1);
        SE_ASSERT( pEdge != tempTerminator.end() );

        iV0 = iV1;
        iV1 = pEdge->second.V[1];
        HullTriangle3f* pNext = SE_NEW HullTriangle3f(i,  iV0,  iV1);
        m_Hull.insert(pNext);

        // establish adjacency links across terminator edge
        pNext->A[1] = pEdge->second.Tri;
        pEdge->second.Tri->A[pEdge->second.NullIndex] = pNext;

        // establish adjacency links with previously inserted triangle
        pNext->A[0] = pTri;
        pTri->A[2] = pNext;

        pTri = pNext;
    }
    SE_ASSERT( iV1 == iSaveV0 );
    (void)iSaveV0;  // avoid warning in Release build

    // establish adjacency links between first/last triangles
    pSaveTri->A[0] = pTri;
    pTri->A[2] = pSaveTri;

    return true;
}
//----------------------------------------------------------------------------
void ConvexHull3f::ExtractIndices()
{
    int iTCount = (int)m_Hull.size();
    m_iSimplexCount = iTCount;
    m_aiIndex = SE_NEW int[3 * m_iSimplexCount];

    std::set<HullTriangle3f*>::iterator tempIter;
    int i = 0;
    for( tempIter = m_Hull.begin(); tempIter != m_Hull.end(); tempIter++ )
    {
        HullTriangle3f* pTri = *tempIter;
        for( int j = 0; j < 3; j++ )
        {
            m_aiIndex[i++] = pTri->V[j];
        }
        SE_DELETE pTri;
    }
    m_Hull.clear();
}
//----------------------------------------------------------------------------
void ConvexHull3f::DeleteHull()
{
    std::set<HullTriangle3f*>::iterator tempIter;
    for( tempIter = m_Hull.begin(); tempIter != m_Hull.end(); tempIter++ )
    {
        HullTriangle3f* pTri = *tempIter;
        SE_DELETE pTri;
    }
    m_Hull.clear();
}
//----------------------------------------------------------------------------
ConvexHull3f::ConvexHull3f(const char* acFilename)
    :
    ConvexHullf(0,  0.0f,  false,  Query::QT_REAL)
{
    m_aVertex = 0;
    m_aSVertex = 0;
    m_pQuery = 0;
    bool bLoaded = Load(acFilename);
    SE_ASSERT( bLoaded );
    (void)bLoaded;  // avoid warning in Release build
}
//----------------------------------------------------------------------------
bool ConvexHull3f::Load(const char* acFilename)
{
    FILE* pIFile = SESystem::SE_Fopen(acFilename,  "rb");
    if( !pIFile )
    {
        return false;
    }

    ConvexHullf::Load(pIFile);

    SE_DELETE m_pQuery;
    SE_DELETE[] m_aSVertex;
    if( m_bOwner )
    {
        SE_DELETE[] m_aVertex;
    }

    m_bOwner = true;
    m_aVertex = SE_NEW Vector3f[m_iVertexCount];
    m_aSVertex = SE_NEW Vector3f[m_iVertexCount + 4];

    size_t uiSize = sizeof(float);
    int iVC = 3 * m_iVertexCount;
    if( uiSize == 4 )
    {
        SESystem::SE_Read4le(pIFile,  iVC,  m_aVertex);
        SESystem::SE_Read4le(pIFile,  iVC,  m_aSVertex);
        SESystem::SE_Read4le(pIFile,  3,  (float*)m_LineOrigin);
        SESystem::SE_Read4le(pIFile,  3,  (float*)m_LineDirection);
        SESystem::SE_Read4le(pIFile,  3,  (float*)m_PlaneOrigin);
        SESystem::SE_Read4le(pIFile,  3,  (float*)m_aPlaneDirection[0]);
        SESystem::SE_Read4le(pIFile,  3,  (float*)m_aPlaneDirection[1]);
    }
    else // iSize == 8
    {
        SESystem::SE_Read8le(pIFile,  iVC,  m_aVertex);
        SESystem::SE_Read8le(pIFile,  iVC,  m_aSVertex);
        SESystem::SE_Read8le(pIFile,  3,  (float*)m_LineOrigin);
        SESystem::SE_Read8le(pIFile,  3,  (float*)m_LineDirection);
        SESystem::SE_Read8le(pIFile,  3,  (float*)m_PlaneOrigin);
        SESystem::SE_Read8le(pIFile,  3,  (float*)m_aPlaneDirection[0]);
        SESystem::SE_Read8le(pIFile,  3,  (float*)m_aPlaneDirection[1]);
    }

    SESystem::SE_Fclose(pIFile);

    switch( m_eQueryType )
    {
    case Query::QT_INT64:
        m_pQuery = SE_NEW Query3Int64f(m_iVertexCount,  m_aSVertex);

        break;
    case Query::QT_INTEGER:
        m_pQuery = SE_NEW Query3TIntegerf(m_iVertexCount,  m_aSVertex);

        break;
    case Query::QT_RATIONAL:
        m_pQuery = SE_NEW Query3TRationalf(m_iVertexCount,  m_aSVertex);

        break;
    case Query::QT_REAL:
        m_pQuery = SE_NEW Query3f(m_iVertexCount,  m_aSVertex);

        break;
    case Query::QT_FILTERED:
        m_pQuery = SE_NEW Query3Filteredf(m_iVertexCount,  m_aSVertex,  
            m_fEpsilon);

        break;
    }

    return true;
}
//----------------------------------------------------------------------------
bool ConvexHull3f::Save(const char* acFilename) const
{
    FILE* pOFile = SESystem::SE_Fopen(acFilename,  "wb");
    if( !pOFile )
    {
        return false;
    }

    ConvexHullf::Save(pOFile);

    size_t uiSize = sizeof(float);
    int iVC = 3 * m_iVertexCount;
    if( uiSize == 4 )
    {
        SESystem::SE_Write4le(pOFile,  iVC,  m_aVertex);
        SESystem::SE_Write4le(pOFile,  iVC,  m_aSVertex);
        SESystem::SE_Write4le(pOFile,  3,  (const float*)m_LineOrigin);
        SESystem::SE_Write4le(pOFile,  3,  (const float*)m_LineDirection);
        SESystem::SE_Write4le(pOFile,  3,  (const float*)m_PlaneOrigin);
        SESystem::SE_Write4le(pOFile,  3,  (const float*)m_aPlaneDirection[0]);
        SESystem::SE_Write4le(pOFile,  3,  (const float*)m_aPlaneDirection[1]);
    }
    else // iSize == 8
    {
        SESystem::SE_Write8le(pOFile,  iVC,  m_aVertex);
        SESystem::SE_Write8le(pOFile,  iVC,  m_aSVertex);
        SESystem::SE_Write8le(pOFile,  3,  (const float*)m_LineOrigin);
        SESystem::SE_Write8le(pOFile,  3,  (const float*)m_LineDirection);
        SESystem::SE_Write8le(pOFile,  3,  (const float*)m_PlaneOrigin);
        SESystem::SE_Write8le(pOFile,  3,  (const float*)m_aPlaneDirection[0]);
        SESystem::SE_Write8le(pOFile,  3,  (const float*)m_aPlaneDirection[1]);
    }

    SESystem::SE_Fclose(pOFile);

    return true;
}
//----------------------------------------------------------------------------