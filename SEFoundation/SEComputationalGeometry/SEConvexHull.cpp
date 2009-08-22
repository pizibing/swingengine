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
#include "SEConvexHull.h"

using namespace Swing;

//----------------------------------------------------------------------------
ConvexHullf::ConvexHullf(int iVertexCount, float fEpsilon, bool bOwner, 
    Query::Type eQueryType)
{
    SE_ASSERT( iVertexCount > 0 && fEpsilon >= 0.0f );

    m_eQueryType = eQueryType;
    m_iVertexCount = iVertexCount;
    m_iDimension = 0;
    m_iSimplexCount = 0;
    m_aiIndex = 0;
    m_fEpsilon = fEpsilon;
    m_bOwner = bOwner;
}
//----------------------------------------------------------------------------
ConvexHullf::~ConvexHullf()
{
    SE_DELETE[] m_aiIndex;
}
//----------------------------------------------------------------------------
int ConvexHullf::GetQueryType() const
{
    return m_eQueryType;
}
//----------------------------------------------------------------------------
int ConvexHullf::GetVertexCount() const
{
    return m_iVertexCount;
}
//----------------------------------------------------------------------------
float ConvexHullf::GetEpsilon() const
{
    return m_fEpsilon;
}
//----------------------------------------------------------------------------
bool ConvexHullf::GetOwner() const
{
    return m_bOwner;
}
//----------------------------------------------------------------------------
int ConvexHullf::GetDimension() const
{
    return m_iDimension;
}
//----------------------------------------------------------------------------
int ConvexHullf::GetSimplexCount() const
{
    return m_iSimplexCount;
}
//----------------------------------------------------------------------------
const int* ConvexHullf::GetIndices() const
{
    return m_aiIndex;
}
//----------------------------------------------------------------------------
bool ConvexHullf::Load(FILE* pIFile)
{
    SE_DELETE[] m_aiIndex;

    // fixed-size members
    int iQueryType;
    System::SE_Read4le(pIFile, 1, &iQueryType);
    m_eQueryType = (Query::Type)iQueryType;
    System::SE_Read4le(pIFile, 1, &m_iVertexCount);
    System::SE_Read4le(pIFile, 1, &m_iDimension);
    System::SE_Read4le(pIFile, 1, &m_iSimplexCount);
    System::SE_Read4le(pIFile, 1, &m_fEpsilon);

    // variable-size members
    int iICount;
    System::SE_Read4le(pIFile, 1, &iICount);
    if( 1 <= m_iDimension && m_iDimension <= 3 )
    {
        SE_ASSERT( iICount == (m_iDimension+1)*m_iSimplexCount );

        m_aiIndex = SE_NEW int[iICount];
        System::SE_Read4le(pIFile, iICount, m_aiIndex);

        return true;
    }

    m_aiIndex = 0;

    return m_iDimension == 0;
}
//----------------------------------------------------------------------------
bool ConvexHullf::Save(FILE* pOFile) const
{
    // fixed-size members
    int iQueryType = (int)m_eQueryType;
    System::SE_Write4le(pOFile, 1, &iQueryType);
    System::SE_Write4le(pOFile, 1, &m_iVertexCount);
    System::SE_Write4le(pOFile, 1, &m_iDimension);
    System::SE_Write4le(pOFile, 1, &m_iSimplexCount);
    System::SE_Write4le(pOFile, 1, &m_fEpsilon);

    // The member m_bOwner is not streamed because on a Load call, this
    // object will allocate the vertices and own this memory.

    // variable-size members
    int iICount;
    if( 1 <= m_iDimension && m_iDimension <= 3 )
    {
        iICount = (m_iDimension + 1)*m_iSimplexCount;
        System::SE_Write4le(pOFile, 1, &iICount);
        System::SE_Write4le(pOFile, iICount, m_aiIndex);

        return true;
    }

    iICount = 0;
    System::SE_Write4le(pOFile, 1, &iICount);

    return m_iDimension == 0;
}
//----------------------------------------------------------------------------
