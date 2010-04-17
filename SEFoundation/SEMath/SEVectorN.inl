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
inline void SEVectorNf::SetSize(int iSize)
{
    delete[] m_pData;
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
inline int SEVectorNf::GetSize() const
{
    return m_iSize;
}
//----------------------------------------------------------------------------
inline int SEVectorNf::CompareData(const SEVectorNf& rVec) const
{
    return memcmp(m_pData, rVec.m_pData, m_iSize*sizeof(float));
}
//----------------------------------------------------------------------------
inline float SEVectorNf::GetLength(void) const
{
    float fSqrLen = 0.0f;
    for( int i = 0; i < m_iSize; i++ )
    {
        fSqrLen += m_pData[i] * m_pData[i];
    }

    return SEMath<float>::Sqrt(fSqrLen);
}
//----------------------------------------------------------------------------
inline float SEVectorNf::GetSquaredLength() const
{
    float fSqrLen = 0.0f;
    for( int i = 0; i < m_iSize; i++ )
    {
        fSqrLen += m_pData[i] * m_pData[i];
    }

    return fSqrLen;
}
//----------------------------------------------------------------------------
inline float SEVectorNf::Dot(const SEVectorNf& rRhsVec) const
{
    float fDot = 0.0f;
    for( int i = 0; i < m_iSize; i++ )
    {
        fDot += m_pData[i] * rRhsVec.m_pData[i];
    }

    return fDot;
}
//----------------------------------------------------------------------------
inline float SEVectorNf::Normalize()
{
    float fLength = GetLength();
    int i;

    if( fLength > SEMath<float>::ZERO_TOLERANCE )
    {
        float fInvLength = 1.0f / fLength;
        for( i = 0; i < m_iSize; i++ )
        {
            m_pData[i] *= fInvLength;
        }
    }
    else
    {
        fLength = 0.0f;
        for( i = 0; i < m_iSize; i++ )
        {
            m_pData[i] = 0.0f;
        }
    }

    return fLength;
}
//----------------------------------------------------------------------------
