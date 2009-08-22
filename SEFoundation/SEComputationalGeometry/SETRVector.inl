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
template <int VSIZE,  int ISIZE>
TRVector<VSIZE,  ISIZE>::TRVector()
{
    // For efficiency in construction of large arrays of vectors,  the
    // default constructor does not initialize the vector.
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRVector<VSIZE,  ISIZE>::TRVector(const TRVector& rV)
{
    for( int i = 0; i < VSIZE; i++ )
    {
        m_aTuple[i] = rV.m_aTuple[i];
    }
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRVector<VSIZE,  ISIZE>::operator const TRational<ISIZE>*() const
{
    return m_aTuple;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRVector<VSIZE,  ISIZE>::operator TRational<ISIZE>*()
{
    return m_aTuple;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRational<ISIZE> TRVector<VSIZE,  ISIZE>::operator[](int i) const
{
    SE_ASSERT( 0 <= i && i < VSIZE );

    return m_aTuple[i];
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRational<ISIZE>& TRVector<VSIZE,  ISIZE>::operator[](int i)
{
    SE_ASSERT( 0 <= i && i < VSIZE );

    return m_aTuple[i];
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRVector<VSIZE,  ISIZE>& TRVector<VSIZE,  ISIZE>::operator=(const TRVector& rV)
{
    for( int i = 0; i < VSIZE; i++ )
    {
        m_aTuple[i] = rV.m_aTuple[i];
    }

    return *this;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
bool TRVector<VSIZE,  ISIZE>::operator==(const TRVector& rV) const
{
    for( int i = 0; i < VSIZE; i++ )
    {
        if( m_aTuple[i] != rV.m_aTuple[i] )
        {
            return false;
        }
    }

    return true;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
bool TRVector<VSIZE,  ISIZE>::operator!=(const TRVector& rV) const
{
    return !operator==(rV);
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
int TRVector<VSIZE,  ISIZE>::CompareArrays(const TRVector& rV) const
{
    for( int i = 0; i < VSIZE; i++ )
    {
        if( m_aTuple[i] < rV.m_aTuple[i] )
        {
            return -1;
        }
        if( m_aTuple[i] > rV.m_aTuple[i] )
        {
            return +1;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
bool TRVector<VSIZE,  ISIZE>::operator<(const TRVector& rV) const
{
    return CompareArrays(rV) < 0;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
bool TRVector<VSIZE,  ISIZE>::operator<=(const TRVector& rV) const
{
    return CompareArrays(rV) <= 0;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
bool TRVector<VSIZE,  ISIZE>::operator>(const TRVector& rV) const
{
    return CompareArrays(rV) > 0;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
bool TRVector<VSIZE,  ISIZE>::operator>=(const TRVector& rV) const
{
    return CompareArrays(rV) >= 0;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRVector<VSIZE,  ISIZE> TRVector<VSIZE,  ISIZE>::operator+(const TRVector& rV)
    const
{
    TRVector<VSIZE,  ISIZE> tempSum;
    for( int i = 0; i < VSIZE; i++ )
    {
        tempSum.m_aTuple[i] = m_aTuple[i] + rV.m_aTuple[i];
    }

    return tempSum;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRVector<VSIZE,  ISIZE> TRVector<VSIZE,  ISIZE>::operator-(const TRVector& rV)
    const
{
    TRVector<VSIZE,  ISIZE> tempDiff;
    for( int i = 0; i < VSIZE; i++ )
    {
        tempDiff.m_aTuple[i] = m_aTuple[i] - rV.m_aTuple[i];
    }

    return tempDiff;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRVector<VSIZE,  ISIZE> TRVector<VSIZE,  ISIZE>::operator*
    (const TRational<ISIZE>& rR) const
{
    TRVector<VSIZE,  ISIZE> tempProd;
    for( int i = 0; i < VSIZE; i++ )
    {
        tempProd.m_aTuple[i] = rR * m_aTuple[i];
    }

    return tempProd;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRVector<VSIZE,  ISIZE> TRVector<VSIZE,  ISIZE>::operator/
    (const TRational<ISIZE>& rR) const
{
    SE_ASSERT( rR != 0 );

    TRVector<VSIZE,  ISIZE> tempProd;
    for( int i = 0; i < VSIZE; i++ )
    {
        tempProd.m_aTuple[i] = m_aTuple[i] / rR;
    }

    return tempProd;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRVector<VSIZE,  ISIZE> TRVector<VSIZE,  ISIZE>::operator-() const
{
    TRVector<VSIZE,  ISIZE> tempNeg;
    for( int i = 0; i < VSIZE; i++ )
    {
        tempNeg.m_aTuple[i] = -m_aTuple[i];
    }

    return tempNeg;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRVector<VSIZE,  ISIZE> operator*(const TRational<ISIZE>& rR, 
    const TRVector<VSIZE,  ISIZE>& rV)
{
    TRVector<VSIZE,  ISIZE> tempProd;
    for( int i = 0; i < VSIZE; i++ )
    {
        tempProd[i] = rR * rV[i];
    }

    return tempProd;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRVector<VSIZE,  ISIZE>& TRVector<VSIZE,  ISIZE>::operator+=(const TRVector& rV)
{
    for( int i = 0; i < VSIZE; i++ )
    {
        m_aTuple[i] += rV.m_aTuple[i];
    }

    return *this;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRVector<VSIZE,  ISIZE>& TRVector<VSIZE,  ISIZE>::operator-=(const TRVector& rV)
{
    for( int i = 0; i < VSIZE; i++ )
    {
        m_aTuple[i] -= rV.m_aTuple[i];
    }

    return *this;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRVector<VSIZE,  ISIZE>& TRVector<VSIZE,  ISIZE>::operator*=
    (const TRational<ISIZE>& rR)
{
    for( int i = 0; i < VSIZE; i++ )
    {
        m_aTuple[i] *= rR;
    }

    return *this;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRVector<VSIZE,  ISIZE>& TRVector<VSIZE,  ISIZE>::operator/=
    (const TRational<ISIZE>& rR)
{
    SE_ASSERT( rR != 0 );

    for( int i = 0; i < VSIZE; i++ )
    {
        m_aTuple[i] /= rR;
    }

    return *this;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRational<ISIZE> TRVector<VSIZE,  ISIZE>::GetSquaredLength() const
{
    TRational<ISIZE> tempSqrLen = 0;
    for( int i = 0; i < VSIZE; i++ )
    {
        tempSqrLen += m_aTuple[i] * m_aTuple[i];
    }

    return tempSqrLen;
}
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
TRational<ISIZE> TRVector<VSIZE,  ISIZE>::Dot(const TRVector& rV) const
{
    TRational<ISIZE> tempDot = 0;
    for( int i = 0; i < VSIZE; i++ )
    {
        tempDot += m_aTuple[i] * rV.m_aTuple[i];
    }

    return tempDot;
}
//----------------------------------------------------------------------------
