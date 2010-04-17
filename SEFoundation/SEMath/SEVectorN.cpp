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
#include "SEVectorN.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEVectorNf::SEVectorNf(int iSize)
{
    if( iSize > 0 )
    {
        m_iSize = iSize;
        m_pData = new float[m_iSize];
        memset(m_pData, 0, m_iSize*sizeof(float));
    }
    else
    {
        m_iSize = 0;
        m_pData = 0;
    }
}
//----------------------------------------------------------------------------
SEVectorNf::SEVectorNf(int iSize, const float* pData)
{
    if( iSize > 0 )
    {
        m_iSize = iSize;
        m_pData = new float[m_iSize];
        size_t uiSize = m_iSize * sizeof(float);
        memcpy(m_pData, pData, uiSize);
    }
    else
    {
        m_iSize = 0;
        m_pData = 0;
    }
}
//----------------------------------------------------------------------------
SEVectorNf::SEVectorNf(const SEVectorNf& rVec)
{
    m_iSize = rVec.m_iSize;
    if( m_iSize > 0 )
    {
        m_pData = new float[m_iSize];
        size_t uiSize = m_iSize * sizeof(float);
        memcpy(m_pData, rVec.m_pData, uiSize);
    }
    else
    {
        m_pData = 0;
    }
}
//----------------------------------------------------------------------------
SEVectorNf::~SEVectorNf()
{
    delete[] m_pData;
}
//----------------------------------------------------------------------------
SEVectorNf::operator float*()
{
    return m_pData;
}
//----------------------------------------------------------------------------
SEVectorNf::operator const float*() const
{
    return m_pData;
}
//----------------------------------------------------------------------------
float SEVectorNf::operator[](int i) const
{
    SE_ASSERT( 0 <= i && i < m_iSize );

    return m_pData[i];
}
//----------------------------------------------------------------------------
float& SEVectorNf::operator[](int i)
{
    SE_ASSERT( 0 <= i && i < m_iSize );

    return m_pData[i];
}
//----------------------------------------------------------------------------
SEVectorNf& SEVectorNf::operator=(const SEVectorNf& rVec)
{
    if( rVec.m_iSize > 0 )
    {
        if( m_iSize != rVec.m_iSize )
        {
            delete[] m_pData;
            m_iSize = rVec.m_iSize;
            m_pData = new float[m_iSize];
        }

        size_t uiSize = m_iSize * sizeof(float);
        memcpy(m_pData, rVec.m_pData, uiSize);
    }
    else
    {
        delete[] m_pData;
        m_iSize = 0;
        m_pData = 0;
    }

    return *this;
}
//----------------------------------------------------------------------------
bool SEVectorNf::operator==(const SEVectorNf& rVec) const
{
    return CompareData(rVec) == 0;
}
//----------------------------------------------------------------------------
bool SEVectorNf::operator!=(const SEVectorNf& rVec) const
{
    return CompareData(rVec) != 0;
}
//----------------------------------------------------------------------------
bool SEVectorNf::operator<(const SEVectorNf& rVec) const
{
    return CompareData(rVec) < 0;
}
//----------------------------------------------------------------------------
bool SEVectorNf::operator<=(const SEVectorNf& rVec) const
{
    return CompareData(rVec) <= 0;
}
//----------------------------------------------------------------------------
bool SEVectorNf::operator>(const SEVectorNf& rVec) const
{
    return CompareData(rVec) > 0;
}
//----------------------------------------------------------------------------
bool SEVectorNf::operator>=(const SEVectorNf& rVec) const
{
    return CompareData(rVec) >= 0;
}
//----------------------------------------------------------------------------
SEVectorNf SEVectorNf::operator+(const SEVectorNf& rRhsVec) const
{
    SEVectorNf ResVec(m_iSize);
    for( int i = 0; i < m_iSize; i++ )
    {
        ResVec.m_pData[i] = m_pData[i] + rRhsVec.m_pData[i];
    }

    return ResVec;
}
//----------------------------------------------------------------------------
SEVectorNf SEVectorNf::operator-(const SEVectorNf& rRhsVec) const
{
    SEVectorNf ResVec(m_iSize);
    for( int i = 0; i < m_iSize; i++ )
    {
        ResVec.m_pData[i] = m_pData[i] - rRhsVec.m_pData[i];
    }

    return ResVec;
}
//----------------------------------------------------------------------------
SEVectorNf SEVectorNf::operator*(float fScalar) const
{
    SEVectorNf ResVec(m_iSize);
    for( int i = 0; i < m_iSize; i++ )
    {
        ResVec.m_pData[i] = fScalar * m_pData[i];
    }

    return ResVec;
}
//----------------------------------------------------------------------------
SEVectorNf SEVectorNf::operator/(float fScalar) const
{
    SEVectorNf ResVec(m_iSize);
    int i;

    if( fScalar != 0.0f )
    {
        float fInvScalar = 1.0f / fScalar;
        for( i = 0; i < m_iSize; i++ )
        {
            ResVec.m_pData[i] = fInvScalar * m_pData[i];
        }
    }
    else
    {
        for( i = 0; i < m_iSize; i++ )
        {
            ResVec.m_pData[i] = SEMath<float>::MAX_REAL;
        }
    }

    return ResVec;
}
//----------------------------------------------------------------------------
SEVectorNf SEVectorNf::operator-() const
{
    SEVectorNf ResVec(m_iSize);
    for( int i = 0; i < m_iSize; i++ )
    {
        ResVec.m_pData[i] = -m_pData[i];
    }

    return ResVec;
}
//----------------------------------------------------------------------------
SEVectorNf& SEVectorNf::operator+=(const SEVectorNf& rRhsVec)
{
    for( int i = 0; i < m_iSize; i++ )
    {
        m_pData[i] += rRhsVec.m_pData[i];
    }

    return *this;
}
//----------------------------------------------------------------------------
SEVectorNf& SEVectorNf::operator-=(const SEVectorNf& rRhsVec)
{
    for( int i = 0; i < m_iSize; i++ )
    {
        m_pData[i] -= rRhsVec.m_pData[i];
    }

    return *this;
}
//----------------------------------------------------------------------------
SEVectorNf& SEVectorNf::operator*=(float fScalar)
{
    for( int i = 0; i < m_iSize; i++ )
    {
        m_pData[i] *= fScalar;
    }

    return *this;
}
//----------------------------------------------------------------------------
SEVectorNf& SEVectorNf::operator/=(float fScalar)
{
    int i;

    if( fScalar != 0.0f )
    {
        float fInvScalar = 1.0f / fScalar;
        for( i = 0; i < m_iSize; i++ )
        {
            m_pData[i] *= fInvScalar;
        }
    }
    else
    {
        for( i = 0; i < m_iSize; i++ )
        {
            m_pData[i] = SEMath<float>::MAX_REAL;
        }
    }

    return *this;
}
//----------------------------------------------------------------------------
SEVectorNf Swing::operator*(float fLhsScalar, const SEVectorNf& rRhsVec)
{
    int iSize = rRhsVec.GetSize();
    SEVectorNf ResVec(iSize);
    for( int i = 0; i < iSize; i++ )
    {
        ResVec[i] = fLhsScalar * rRhsVec[i];
    }

    return ResVec;
}
//----------------------------------------------------------------------------