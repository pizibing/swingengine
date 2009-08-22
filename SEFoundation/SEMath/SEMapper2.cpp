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
#include "SEMapper2.h"

using namespace Swing;

//----------------------------------------------------------------------------
Mapper2f::Mapper2f(int iVCount, const Vector2f* aVertex, float fEpsilon)
{
    SE_ASSERT( iVCount > 0 && aVertex && fEpsilon >= 0.0f );

    m_bExtremeCCW = false;

    // 计算传入顶点的AABBox.
    m_Min = aVertex[0];
    m_Max = m_Min;

    int aiIMin[2], aiIMax[2], i, j;
    for( j = 0; j < 2; j++ )
    {
        aiIMin[j] = 0;
        aiIMax[j] = 0;
    }

    for( i = 1; i < iVCount; i++ )
    {
        for( j = 0; j < 2; j++ )
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

    // 判断bounding box的最大范围.
    Vector2f vec2fRange = m_Max - m_Min;
    m_fMaxRange = vec2fRange[0];
    m_aiExtreme[0] = aiIMin[0];
    m_aiExtreme[1] = aiIMax[0];
    if( vec2fRange[1] > m_fMaxRange )
    {
        m_fMaxRange = vec2fRange[1];
        m_aiExtreme[0] = aiIMin[1];
        m_aiExtreme[1] = aiIMax[1];
    }
    m_Origin = aVertex[m_aiExtreme[0]];

    // 测试传入顶点集合是否近似为一点.
    if( m_fMaxRange < fEpsilon )
    {
        m_iDimension = 0;
        m_aiExtreme[1] = m_aiExtreme[0];
        m_aiExtreme[2] = m_aiExtreme[0];
        m_aDirection[0] = Vector2f::ZERO;
        m_aDirection[1] = Vector2f::ZERO;

        return;
    }

    // 测试传入顶点集合是否近似为一条线段.
    m_aDirection[0] = aVertex[m_aiExtreme[1]] - m_Origin;
    m_aDirection[0].Normalize();
    m_aDirection[0].GetPerp(m_aDirection[1]);
    m_aDirection[1] = -m_aDirection[1];
    float fLMax = 0.0f, fMaxSign = 0.0f;
    m_aiExtreme[2] = m_aiExtreme[0];
    for( i = 0; i < iVCount; i++ )
    {
        Vector2f vec2fDiff = aVertex[i] - m_Origin;
        float fL = m_aDirection[1].Dot(vec2fDiff);
        float fSign = Mathf::Sign(fL);
        fL = Mathf::FAbs(fL);
        if( fL > fLMax )
        {
            fLMax = fL;
            fMaxSign = fSign;
            m_aiExtreme[2] = i;
        }
    }

    if( fLMax < fEpsilon*m_fMaxRange )
    {
        m_iDimension = 1;
        m_aiExtreme[2] = m_aiExtreme[1];

        return;
    }

    m_iDimension = 2;
    m_bExtremeCCW = (fMaxSign > 0.0f ? true : false);
}
//----------------------------------------------------------------------------
Mapper2f::~Mapper2f()
{
}
//----------------------------------------------------------------------------
const Vector2f& Mapper2f::GetMin() const
{
    return m_Min;
}
//----------------------------------------------------------------------------
const Vector2f& Mapper2f::GetMax() const
{
    return m_Max;
}
//----------------------------------------------------------------------------
float Mapper2f::GetMaxRange() const
{
    return m_fMaxRange;
}
//----------------------------------------------------------------------------
int Mapper2f::GetDimension() const
{
    return m_iDimension;
}
//----------------------------------------------------------------------------
const Vector2f& Mapper2f::GetOrigin() const
{
    return m_Origin;
}
//----------------------------------------------------------------------------
const Vector2f& Mapper2f::GetDirection(int i) const
{
    SE_ASSERT( 0 <= i && i < 2 );

    return m_aDirection[i];
}
//----------------------------------------------------------------------------
int Mapper2f::GetExtremeIndex(int i) const
{
    SE_ASSERT( 0 <= i && i < 3 );

    return m_aiExtreme[i];
}
//----------------------------------------------------------------------------
bool Mapper2f::GetExtremeCCW() const
{
    return m_bExtremeCCW;
}
//----------------------------------------------------------------------------
