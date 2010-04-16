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
#include "SEConvexHull1.h"

using namespace Swing;

//----------------------------------------------------------------------------
ConvexHull1f::ConvexHull1f(int iVertexCount, float* afVertex, 
    float fEpsilon, bool bOwner, Query::Type eQueryType)
    :
    ConvexHullf(iVertexCount, fEpsilon, bOwner, eQueryType)
{
    SE_ASSERT(afVertex);
    m_afVertex = afVertex;

    std::vector<SortedVertex> tempArray(m_iVertexCount);
    int i;
    for( i = 0; i < m_iVertexCount; i++ )
    {
        tempArray[i].Value = m_afVertex[i];
        tempArray[i].Index = i;
    }
    std::sort(tempArray.begin(), tempArray.end());

    float fRange = tempArray[m_iVertexCount-1].Value - tempArray[0].Value;
    if( fRange >= m_fEpsilon )
    {
        m_iDimension = 1;
        m_iSimplexCount = 2;
        m_aiIndex = SE_NEW int[2];
        m_aiIndex[0] = tempArray[0].Index;
        m_aiIndex[1] = tempArray[m_iVertexCount - 1].Index;
    }
}
//----------------------------------------------------------------------------
ConvexHull1f::~ConvexHull1f()
{
    if( m_bOwner )
    {
        SE_DELETE[] m_afVertex;
    }
}
//----------------------------------------------------------------------------
const float* ConvexHull1f::GetVertices() const
{
    return m_afVertex;
}
//----------------------------------------------------------------------------
ConvexHull1f::ConvexHull1f(const char* acFilename)
    :
    ConvexHullf(0, 0.0f, false, Query::QT_REAL)
{
    m_afVertex = 0;
    bool bLoaded = Load(acFilename);
    SE_ASSERT( bLoaded );
    (void)bLoaded;  // avoid warning in Release build
}
//----------------------------------------------------------------------------
bool ConvexHull1f::Load(const char* acFilename)
{
    FILE* pIFile = SESystem::SE_Fopen(acFilename, "rb");
    if( !pIFile )
    {
        return false;
    }

    ConvexHullf::Load(pIFile);

    if( m_bOwner )
    {
        SE_DELETE[] m_afVertex;
    }

    m_bOwner = true;
    m_afVertex = SE_NEW float[m_iVertexCount];

    size_t uiSize = sizeof(float);
    if( uiSize == 4 )
    {
        SESystem::SE_Read4le(pIFile, m_iVertexCount, m_afVertex);
    }
    else // uiSize == 8
    {
        SESystem::SE_Read8le(pIFile, m_iVertexCount, m_afVertex);
    }

    SESystem::SE_Fclose(pIFile);

    return true;
}
//----------------------------------------------------------------------------
bool ConvexHull1f::Save(const char* acFilename) const
{
    FILE* pOFile = SESystem::SE_Fopen(acFilename, "wb");
    if( !pOFile )
    {
        return false;
    }

    ConvexHullf::Save(pOFile);

    size_t uiSize = sizeof(float);
    if( uiSize == 4 )
    {
        SESystem::SE_Write4le(pOFile, m_iVertexCount, m_afVertex);
    }
    else // uiSize == 8
    {
        SESystem::SE_Write8le(pOFile, m_iVertexCount, m_afVertex);
    }

    SESystem::SE_Fclose(pOFile);

    return true;
}
//----------------------------------------------------------------------------