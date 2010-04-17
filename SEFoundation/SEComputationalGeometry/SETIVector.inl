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

//----------------------------------------------------------------------------
template <int VSIZE>
SETIVector<VSIZE>::SETIVector()
{
    // For efficiency in construction of large arrays of vectors,  the
    // default constructor does not initialize the vector.
}
//----------------------------------------------------------------------------
template <int VSIZE>
SETIVector<VSIZE>::SETIVector(const SETIVector& rV)
{
    for( int i = 0; i < VSIZE; i++ )
    {
        m_aiTuple[i] = rV.m_aiTuple[i];
    }
}
//----------------------------------------------------------------------------
template <int VSIZE>
SETIVector<VSIZE>::operator const SE_Int64*() const
{
    return m_aiTuple;
}
//----------------------------------------------------------------------------
template <int VSIZE>
SETIVector<VSIZE>::operator SE_Int64*()
{
    return m_aiTuple;
}
//----------------------------------------------------------------------------
template <int VSIZE>
SE_Int64 SETIVector<VSIZE>::operator[](int i) const
{
    SE_ASSERT( 0 <= i && i < VSIZE );

    return m_aiTuple[i];
}
//----------------------------------------------------------------------------
template <int VSIZE>
SE_Int64& SETIVector<VSIZE>::operator[](int i)
{
    SE_ASSERT( 0 <= i && i < VSIZE );

    return m_aiTuple[i];
}
//----------------------------------------------------------------------------
template <int VSIZE>
SETIVector<VSIZE>& SETIVector<VSIZE>::operator=(const SETIVector& rV)
{
    for( int i = 0; i < VSIZE; i++ )
    {
        m_aiTuple[i] = rV.m_aiTuple[i];
    }

    return *this;
}
//----------------------------------------------------------------------------
template <int VSIZE>
bool SETIVector<VSIZE>::operator==(const SETIVector& rV) const
{
    for( int i = 0; i < VSIZE; i++ )
    {
        if( m_aiTuple[i] != rV.m_aiTuple[i] )
        {
            return false;
        }
    }

    return true;
}
//----------------------------------------------------------------------------
template <int VSIZE>
bool SETIVector<VSIZE>::operator!=(const SETIVector& rV) const
{
    return !operator==(rV);
}
//----------------------------------------------------------------------------
template <int VSIZE>
int SETIVector<VSIZE>::CompareArrays(const SETIVector& rV) const
{
    for( int i = 0; i < VSIZE; i++ )
    {
        if( m_aiTuple[i] < rV.m_aiTuple[i] )
        {
            return -1;
        }
        if( m_aiTuple[i] > rV.m_aiTuple[i] )
        {
            return +1;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
template <int VSIZE>
bool SETIVector<VSIZE>::operator<(const SETIVector& rV) const
{
    return CompareArrays(rV) < 0;
}
//----------------------------------------------------------------------------
template <int VSIZE>
bool SETIVector<VSIZE>::operator<=(const SETIVector& rV) const
{
    return CompareArrays(rV) <= 0;
}
//----------------------------------------------------------------------------
template <int VSIZE>
bool SETIVector<VSIZE>::operator>(const SETIVector& rV) const
{
    return CompareArrays(rV) > 0;
}
//----------------------------------------------------------------------------
template <int VSIZE>
bool SETIVector<VSIZE>::operator>=(const SETIVector& rV) const
{
    return CompareArrays(rV) >= 0;
}
//----------------------------------------------------------------------------
template <int VSIZE>
SETIVector<VSIZE> SETIVector<VSIZE>::operator+(const SETIVector& rV) const
{
    SETIVector<VSIZE> iSum;
    for( int i = 0; i < VSIZE; i++ )
    {
        iSum.m_aiTuple[i] = m_aiTuple[i] + rV.m_aiTuple[i];
    }

    return iSum;
}
//----------------------------------------------------------------------------
template <int VSIZE>
SETIVector<VSIZE> SETIVector<VSIZE>::operator-(const SETIVector& rV) const
{
    SETIVector<VSIZE> iDiff;
    for( int i = 0; i < VSIZE; i++ )
    {
        iDiff.m_aiTuple[i] = m_aiTuple[i] - rV.m_aiTuple[i];
    }

    return iDiff;
}
//----------------------------------------------------------------------------
template <int VSIZE>
SETIVector<VSIZE> SETIVector<VSIZE>::operator*(const SE_Int64& riI) const
{
    SETIVector<VSIZE> iProd;
    for( int i = 0; i < VSIZE; i++ )
    {
        iProd.m_aiTuple[i] = riI * m_aiTuple[i];
    }

    return iProd;
}
//----------------------------------------------------------------------------
template <int VSIZE>
SETIVector<VSIZE> SETIVector<VSIZE>::operator/(const SE_Int64& riI) const
{
    SE_ASSERT( riI != 0 );

    SETIVector<VSIZE> iProd;
    for( int i = 0; i < VSIZE; i++ )
    {
        iProd.m_aiTuple[i] = m_aiTuple[i] / riI;
    }

    return iProd;
}
//----------------------------------------------------------------------------
template <int VSIZE>
SETIVector<VSIZE> SETIVector<VSIZE>::operator-() const
{
    SETIVector<VSIZE> iNeg;
    for( int i = 0; i < VSIZE; i++ )
    {
        iNeg.m_aiTuple[i] = -m_aiTuple[i];
    }

    return iNeg;
}
//----------------------------------------------------------------------------
template <int VSIZE>
SETIVector<VSIZE> operator*(const SE_Int64& riI,  const SETIVector<VSIZE>& rV)
{
    SETIVector<VSIZE> iProd;
    for( int i = 0; i < VSIZE; i++ )
    {
        iProd[i] = riI * rV[i];
    }

    return iProd;
}
//----------------------------------------------------------------------------
template <int VSIZE>
SETIVector<VSIZE>& SETIVector<VSIZE>::operator+=(const SETIVector& rV)
{
    for( int i = 0; i < VSIZE; i++ )
    {
        m_aiTuple[i] += rV.m_aiTuple[i];
    }

    return *this;
}
//----------------------------------------------------------------------------
template <int VSIZE>
SETIVector<VSIZE>& SETIVector<VSIZE>::operator-=(const SETIVector& rV)
{
    for( int i = 0; i < VSIZE; i++ )
    {
        m_aiTuple[i] -= rV.m_aiTuple[i];
    }

    return *this;
}
//----------------------------------------------------------------------------
template <int VSIZE>
SETIVector<VSIZE>& SETIVector<VSIZE>::operator*=(const SE_Int64& riI)
{
    for( int i = 0; i < VSIZE; i++ )
    {
        m_aiTuple[i] *= riI;
    }

    return *this;
}
//----------------------------------------------------------------------------
template <int VSIZE>
SETIVector<VSIZE>& SETIVector<VSIZE>::operator/=(const SE_Int64& riI)
{
    SE_ASSERT( riI != 0 );

    for( int i = 0; i < VSIZE; i++ )
    {
        m_aiTuple[i] /= riI;
    }

    return *this;
}
//----------------------------------------------------------------------------
template <int VSIZE>
SE_Int64 SETIVector<VSIZE>::GetSquaredLength() const
{
    SE_Int64 iSqrLen = 0;
    for( int i = 0; i < VSIZE; i++ )
    {
        iSqrLen += m_aiTuple[i] * m_aiTuple[i];
    }

    return iSqrLen;
}
//----------------------------------------------------------------------------
template <int VSIZE>
SE_Int64 SETIVector<VSIZE>::Dot(const SETIVector& rV) const
{
    SE_Int64 iDot = 0;
    for( int i = 0; i < VSIZE; i++ )
    {
        iDot += m_aiTuple[i] * rV.m_aiTuple[i];
    }

    return iDot;
}
//----------------------------------------------------------------------------
