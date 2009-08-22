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
// 单精度4维向量类
//----------------------------------------------------------------------------
inline int Vector4f::CompareData(const Vector4f& rVec) const
{
    return memcmp(m_fData, rVec.m_fData, 4*sizeof(float));
}
//----------------------------------------------------------------------------
inline float Vector4f::GetLength() const
{
    return Math<float>::Sqrt(
                               m_fData[0] * m_fData[0] +
                               m_fData[1] * m_fData[1] +
                               m_fData[2] * m_fData[2] +
                               m_fData[3] * m_fData[3]);
}
//----------------------------------------------------------------------------
inline float Vector4f::GetSquaredLength() const
{
    return
            m_fData[0] * m_fData[0] +
            m_fData[1] * m_fData[1] +
            m_fData[2] * m_fData[2] +
            m_fData[3] * m_fData[3];
}
//----------------------------------------------------------------------------
inline float Vector4f::Dot(const Vector4f& rRhsVec) const
{
    return
            m_fData[0] * rRhsVec.m_fData[0] +
            m_fData[1] * rRhsVec.m_fData[1] +
            m_fData[2] * rRhsVec.m_fData[2] +
            m_fData[3] * rRhsVec.m_fData[3];
}
//----------------------------------------------------------------------------
inline float Vector4f::Normalize()
{
    float fLength = GetLength();

    if( fLength > Math<float>::ZERO_TOLERANCE )
    {
        float fInvLength = 1.0f / fLength;
        m_fData[0] *= fInvLength;
        m_fData[1] *= fInvLength;
        m_fData[2] *= fInvLength;
        m_fData[3] *= fInvLength;
    }
    else
    {
        m_fData[0] = 0.0f;
        m_fData[1] = 0.0f;
        m_fData[2] = 0.0f;
        m_fData[3] = 0.0f;
    }

    return fLength;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 双精度4维向量类
//----------------------------------------------------------------------------
inline int Vector4d::CompareData(const Vector4d& rVec) const
{
    return memcmp(m_dData, rVec.m_dData, 4*sizeof(double));
}
//----------------------------------------------------------------------------
inline double Vector4d::GetLength() const
{
    return Math<double>::Sqrt(
                               m_dData[0] * m_dData[0] +
                               m_dData[1] * m_dData[1] +
                               m_dData[2] * m_dData[2] +
                               m_dData[3] * m_dData[3]);
}
//----------------------------------------------------------------------------
inline double Vector4d::GetSquaredLength() const
{
    return
            m_dData[0] * m_dData[0] +
            m_dData[1] * m_dData[1] +
            m_dData[2] * m_dData[2] +
            m_dData[3] * m_dData[3];
}
//----------------------------------------------------------------------------
inline double Vector4d::Dot(const Vector4d& rRhsVec) const
{
    return
            m_dData[0] * rRhsVec.m_dData[0] +
            m_dData[1] * rRhsVec.m_dData[1] +
            m_dData[2] * rRhsVec.m_dData[2] +
            m_dData[3] * rRhsVec.m_dData[3];
}
//----------------------------------------------------------------------------
inline double Vector4d::Normalize()
{
    double dLength = GetLength();

    if( dLength > Math<double>::ZERO_TOLERANCE )
    {
        double fInvLength = 1.0 / dLength;
        m_dData[0] *= fInvLength;
        m_dData[1] *= fInvLength;
        m_dData[2] *= fInvLength;
        m_dData[3] *= fInvLength;
    }
    else
    {
        m_dData[0] = 0.0;
        m_dData[1] = 0.0;
        m_dData[2] = 0.0;
        m_dData[3] = 0.0;
    }

    return dLength;
}
//----------------------------------------------------------------------------