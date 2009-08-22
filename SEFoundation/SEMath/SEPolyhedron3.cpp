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
#include "SEPolyhedron3.h"

using namespace Swing;

//----------------------------------------------------------------------------
Polyhedron3f::Polyhedron3f(int iVCount, Vector3f* aVertex, int iTCount, 
    int* aiIndex, bool bOwner)
{
    // polyhedron必须至少是个四面体.
    SE_ASSERT( iVCount >= 4 && aVertex );
    SE_ASSERT( iTCount >= 4 && aiIndex );

    m_iVCount = iVCount;
    m_aVertex = aVertex;
    m_iTCount = iTCount;
    m_aiIndex = aiIndex;
    m_bOwner = bOwner;
}
//----------------------------------------------------------------------------
Polyhedron3f::Polyhedron3f(const Polyhedron3f& rPoly)
{
    m_aVertex = 0;
    m_aiIndex = 0;
    m_bOwner = false;
    *this = rPoly;
}
//----------------------------------------------------------------------------
Polyhedron3f::~Polyhedron3f()
{
    if( m_bOwner )
    {
        SE_DELETE[] m_aVertex;
        SE_DELETE[] m_aiIndex;
    }
}
//----------------------------------------------------------------------------
Polyhedron3f& Polyhedron3f::operator=(const Polyhedron3f& rPoly)
{
    if( m_bOwner )
    {
        SE_DELETE[] m_aVertex;
        SE_DELETE[] m_aiIndex;
    }

    m_iVCount = rPoly.m_iVCount;
    m_iTCount = rPoly.m_iTCount;
    m_bOwner = rPoly.m_bOwner;

    if( m_bOwner )
    {
        m_aVertex = SE_NEW Vector3f[m_iVCount];
        size_t uiSize = m_iVCount * sizeof(Vector3f);
        System::SE_Memcpy(m_aVertex, uiSize, rPoly.m_aVertex, uiSize);
        m_aiIndex = SE_NEW int[3 * m_iTCount];
        uiSize = 3 * m_iTCount * sizeof(int);
        System::SE_Memcpy(m_aiIndex, uiSize, rPoly.m_aiIndex, uiSize);
    }
    else
    {
        m_aVertex = rPoly.m_aVertex;
        m_aiIndex = rPoly.m_aiIndex;
    }

    return *this;
}
//----------------------------------------------------------------------------
int Polyhedron3f::GetVCount() const
{
    return m_iVCount;
}
//----------------------------------------------------------------------------
const Vector3f* Polyhedron3f::GetVertices() const
{
    return m_aVertex;
}
//----------------------------------------------------------------------------
const Vector3f& Polyhedron3f::GetVertex(int i) const
{
    SE_ASSERT( 0 <= i && i < m_iVCount );

    return m_aVertex[i];
}
//----------------------------------------------------------------------------
int Polyhedron3f::GetTCount() const
{
    return m_iTCount;
}
//----------------------------------------------------------------------------
const int* Polyhedron3f::GetIndices() const
{
    return m_aiIndex;
}
//----------------------------------------------------------------------------
const int* Polyhedron3f::GetTriangle(int i) const
{
    SE_ASSERT( 0 <= i && i < m_iTCount );

    return &m_aiIndex[3 * i];
}
//----------------------------------------------------------------------------
void Polyhedron3f::SetVertex(int i, const Vector3f& rV)
{
    SE_ASSERT( 0 <= i && i < m_iVCount );

    m_aVertex[i] = rV;
}
//----------------------------------------------------------------------------
Vector3f* Polyhedron3f::GetVertices()
{
    return m_aVertex;
}
//----------------------------------------------------------------------------
Vector3f Polyhedron3f::ComputeVertexAverage() const
{
    Vector3f vec3fAverage = m_aVertex[0];
    for( int i = 1; i < m_iVCount; i++ )
    {
        vec3fAverage += m_aVertex[i];
    }

    vec3fAverage /= (float)m_iVCount;

    return vec3fAverage;
}
//----------------------------------------------------------------------------
float Polyhedron3f::ComputeSurfaceArea() const
{
    float fSurfaceArea = 0.0f;

    const int* piIndex = m_aiIndex;
    for( int i = 0; i < m_iTCount; i++ )
    {
        int iV0 = *piIndex++;
        int iV1 = *piIndex++;
        int iV2 = *piIndex++;
        Vector3f vec3fEdge0 = m_aVertex[iV1] - m_aVertex[iV0];
        Vector3f vec3fEdge1 = m_aVertex[iV2] - m_aVertex[iV0];
        Vector3f vec3fCross = vec3fEdge0.Cross(vec3fEdge1);
        fSurfaceArea += vec3fCross.GetLength();
    }

    fSurfaceArea *= 0.5f;

    return fSurfaceArea;
}
//----------------------------------------------------------------------------
float Polyhedron3f::ComputeVolume() const
{
    float fVolume = 0.0f;

    const int* piIndex = m_aiIndex;
    for( int i = 0; i < m_iTCount; i++ )
    {
        int iV0 = *piIndex++;
        int iV1 = *piIndex++;
        int iV2 = *piIndex++;
        fVolume +=
            m_aVertex[iV0].Dot(m_aVertex[iV1].Cross(m_aVertex[iV2]));
    }

    fVolume /= 6.0f;

    return fVolume;
}
//----------------------------------------------------------------------------
