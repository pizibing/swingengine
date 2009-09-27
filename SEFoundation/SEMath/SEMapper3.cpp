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
#include "SEMapper3.h"

using namespace Swing;

//----------------------------------------------------------------------------
Mapper3f::Mapper3f(int iVCount, const Vector3f* aVertex, float fEpsilon)
{
    SE_ASSERT( iVCount > 0 && aVertex && fEpsilon >= 0.0f );

    m_bExtremeCCW = false;

    // Compute the axis-aligned bounding box for the input points.
    m_Min = aVertex[0];
    m_Max = m_Min;

    int aiIMin[3], aiIMax[3], i, j;
    for( j = 0; j < 3; j++ )
    {
        aiIMin[j] = 0;
        aiIMax[j] = 0;
    }

    for( i = 1; i < iVCount; i++ )
    {
        for( j = 0; j < 3; j++ )
        {
            if( aVertex[i][j] < m_Min[j] )
            {
                m_Min[j] = aVertex[i][j];
                aiIMin[j] = i;
            }
            else if( aVertex[i][j] > m_Max[j] )
            {
                m_Max[j] = aVertex[i][j];
                aiIMax[j] = i;
            }
        }
    }

    // Determine the maximum range for the bounding box.
    Vector3f vec3fRange = m_Max - m_Min;
    m_fMaxRange = vec3fRange[0];
    m_aiExtreme[0] = aiIMin[0];
    m_aiExtreme[1] = aiIMax[0];
    if( vec3fRange[1] > m_fMaxRange )
    {
        m_fMaxRange = vec3fRange[1];
        m_aiExtreme[0] = aiIMin[1];
        m_aiExtreme[1] = aiIMax[1];
    }
    if( vec3fRange[2] > m_fMaxRange )
    {
        m_fMaxRange = vec3fRange[2];
        m_aiExtreme[0] = aiIMin[2];
        m_aiExtreme[1] = aiIMax[2];
    }
    m_Origin = aVertex[m_aiExtreme[0]];

    // Test if the point set is (nearly) a point.
    if( m_fMaxRange < fEpsilon )
    {
        m_iDimension = 0;
        m_aiExtreme[1] = m_aiExtreme[0];
        m_aiExtreme[2] = m_aiExtreme[0];
        m_aiExtreme[3] = m_aiExtreme[0];
        m_aDirection[0] = Vector3f::ZERO;
        m_aDirection[1] = Vector3f::ZERO;
        m_aDirection[2] = Vector3f::ZERO;

        return;
    }

    // Test if the point set is (nearly) a line segment.
    m_aDirection[0] = aVertex[m_aiExtreme[1]] - m_Origin;
    m_aDirection[0].Normalize();
    float fLMax = 0.0f, fL, fDot;
    m_aiExtreme[2] = m_aiExtreme[0];
    for( i = 0; i < iVCount; i++ )
    {
        Vector3f vec3fDiff = aVertex[i] - m_Origin;
        fDot = m_aDirection[0].Dot(vec3fDiff);
        Vector3f vec3fProj = vec3fDiff - fDot*m_aDirection[0];
        fL = vec3fProj.GetLength();
        if( fL > fLMax )
        {
            fLMax = fL;
            m_aiExtreme[2] = i;
        }
    }

    if( fLMax < fEpsilon*m_fMaxRange )
    {
        m_iDimension = 1;
        m_aiExtreme[2] = m_aiExtreme[1];
        m_aiExtreme[3] = m_aiExtreme[1];
        m_aDirection[1] = Vector3f::ZERO;
        m_aDirection[2] = Vector3f::ZERO;

        return;
    }

    // Test if the point set is (nearly) a planar polygon.
    m_aDirection[1] = aVertex[m_aiExtreme[2]] - m_Origin;
    fDot = m_aDirection[0].Dot(m_aDirection[1]);
    m_aDirection[1] -= fDot * m_aDirection[0];
    m_aDirection[1].Normalize();
    m_aDirection[2] = m_aDirection[0].Cross(m_aDirection[1]);
    fLMax = 0.0f;
    float fMaxSign = 0.0f, fSign;
    m_aiExtreme[3] = m_aiExtreme[0];
    for( i = 0; i < iVCount; i++ )
    {
        Vector3f vec3fDiff = aVertex[i] - m_Origin;
        fL = m_aDirection[2].Dot(vec3fDiff);
        fSign = Mathf::Sign(fL);
        fL = Mathf::FAbs(fL);
        if( fL > fLMax )
        {
            fLMax = fL;
            fMaxSign = fSign;
            m_aiExtreme[3] = i;
        }
    }

    if( fLMax < fEpsilon*m_fMaxRange )
    {
        m_iDimension = 2;
        m_aiExtreme[3] = m_aiExtreme[2];

        return;
    }

    m_iDimension = 3;
    m_bExtremeCCW = (fMaxSign > 0.0f ? true : false);
}
//----------------------------------------------------------------------------
Mapper3f::~Mapper3f()
{
}
//----------------------------------------------------------------------------
const Vector3f& Mapper3f::GetMin() const
{
    return m_Min;
}
//----------------------------------------------------------------------------
const Vector3f& Mapper3f::GetMax() const
{
    return m_Max;
}
//----------------------------------------------------------------------------
float Mapper3f::GetMaxRange() const
{
    return m_fMaxRange;
}
//----------------------------------------------------------------------------
int Mapper3f::GetDimension() const
{
    return m_iDimension;
}
//----------------------------------------------------------------------------
const Vector3f& Mapper3f::GetOrigin() const
{
    return m_Origin;
}
//----------------------------------------------------------------------------
const Vector3f& Mapper3f::GetDirection(int i) const
{
    SE_ASSERT( 0 <= i && i < 3 );

    return m_aDirection[i];
}
//----------------------------------------------------------------------------
int Mapper3f::GetExtremeIndex(int i) const
{
    SE_ASSERT( 0 <= i && i < 4 );

    return m_aiExtreme[i];
}
//----------------------------------------------------------------------------
bool Mapper3f::GetExtremeCCW() const
{
    return m_bExtremeCCW;
}
//----------------------------------------------------------------------------