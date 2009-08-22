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
VectorNf::VectorNf(int iSize)
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
VectorNf::VectorNf(int iSize, const float* pData)
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
VectorNf::VectorNf(const VectorNf& rVec)
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
VectorNf::~VectorNf()
{
    delete[] m_pData;
}
//----------------------------------------------------------------------------
VectorNf::operator float*()
{
    return m_pData;
}
//----------------------------------------------------------------------------
VectorNf::operator const float*() const
{
    return m_pData;
}
//----------------------------------------------------------------------------
float VectorNf::operator[](int i) const
{
    SE_ASSERT( 0 <= i && i < m_iSize );

    return m_pData[i];
}
//----------------------------------------------------------------------------
float& VectorNf::operator[](int i)
{
    SE_ASSERT( 0 <= i && i < m_iSize );

    return m_pData[i];
}
//----------------------------------------------------------------------------
VectorNf& VectorNf::operator=(const VectorNf& rVec)
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
bool VectorNf::operator==(const VectorNf& rVec) const
{
    return CompareData(rVec) == 0;
}
//----------------------------------------------------------------------------
bool VectorNf::operator!=(const VectorNf& rVec) const
{
    return CompareData(rVec) != 0;
}
//----------------------------------------------------------------------------
bool VectorNf::operator<(const VectorNf& rVec) const
{
    return CompareData(rVec) < 0;
}
//----------------------------------------------------------------------------
bool VectorNf::operator<=(const VectorNf& rVec) const
{
    return CompareData(rVec) <= 0;
}
//----------------------------------------------------------------------------
bool VectorNf::operator>(const VectorNf& rVec) const
{
    return CompareData(rVec) > 0;
}
//----------------------------------------------------------------------------
bool VectorNf::operator>=(const VectorNf& rVec) const
{
    return CompareData(rVec) >= 0;
}
//----------------------------------------------------------------------------
VectorNf VectorNf::operator+(const VectorNf& rRhsVec) const
{
    VectorNf ResVec(m_iSize);
    for( int i = 0; i < m_iSize; i++ )
    {
        ResVec.m_pData[i] = m_pData[i] + rRhsVec.m_pData[i];
    }

    return ResVec;
}
//----------------------------------------------------------------------------
VectorNf VectorNf::operator-(const VectorNf& rRhsVec) const
{
    VectorNf ResVec(m_iSize);
    for( int i = 0; i < m_iSize; i++ )
    {
        ResVec.m_pData[i] = m_pData[i] - rRhsVec.m_pData[i];
    }

    return ResVec;
}
//----------------------------------------------------------------------------
VectorNf VectorNf::operator*(float fScalar) const
{
    VectorNf ResVec(m_iSize);
    for( int i = 0; i < m_iSize; i++ )
    {
        ResVec.m_pData[i] = fScalar * m_pData[i];
    }

    return ResVec;
}
//----------------------------------------------------------------------------
VectorNf VectorNf::operator/(float fScalar) const
{
    VectorNf ResVec(m_iSize);
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
            ResVec.m_pData[i] = Math<float>::MAX_REAL;
        }
    }

    return ResVec;
}
//----------------------------------------------------------------------------
VectorNf VectorNf::operator-() const
{
    VectorNf ResVec(m_iSize);
    for( int i = 0; i < m_iSize; i++ )
    {
        ResVec.m_pData[i] = -m_pData[i];
    }

    return ResVec;
}
//----------------------------------------------------------------------------
VectorNf& VectorNf::operator+=(const VectorNf& rRhsVec)
{
    for( int i = 0; i < m_iSize; i++ )
    {
        m_pData[i] += rRhsVec.m_pData[i];
    }

    return *this;
}
//----------------------------------------------------------------------------
VectorNf& VectorNf::operator-=(const VectorNf& rRhsVec)
{
    for( int i = 0; i < m_iSize; i++ )
    {
        m_pData[i] -= rRhsVec.m_pData[i];
    }

    return *this;
}
//----------------------------------------------------------------------------
VectorNf& VectorNf::operator*=(float fScalar)
{
    for( int i = 0; i < m_iSize; i++ )
    {
        m_pData[i] *= fScalar;
    }

    return *this;
}
//----------------------------------------------------------------------------
VectorNf& VectorNf::operator/=(float fScalar)
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
            m_pData[i] = Math<float>::MAX_REAL;
        }
    }

    return *this;
}
//----------------------------------------------------------------------------
VectorNf Swing::operator*(float fLhsScalar, const VectorNf& rRhsVec)
{
    int iSize = rRhsVec.GetSize();
    VectorNf ResVec(iSize);
    for( int i = 0; i < iSize; i++ )
    {
        ResVec[i] = fLhsScalar * rRhsVec[i];
    }

    return ResVec;
}
//----------------------------------------------------------------------------