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
// 单精度3维向量类
//----------------------------------------------------------------------------
inline int SEVector3f::CompareData(const SEVector3f& rVecV) const
{
    return memcmp(m_fData, rVecV.m_fData, 3*sizeof(float));
}
//----------------------------------------------------------------------------
inline float SEVector3f::GetLength() const
{
    return SEMath<float>::Sqrt(m_fData[0]*m_fData[0] +
        m_fData[1]*m_fData[1] + m_fData[2]*m_fData[2]);
}
//----------------------------------------------------------------------------
inline float SEVector3f::GetSquaredLength() const
{
    return m_fData[0]*m_fData[0] + m_fData[1]*m_fData[1] + 
        m_fData[2]*m_fData[2];
}
//----------------------------------------------------------------------------
inline float SEVector3f::Dot(const SEVector3f& rRhsVec) const
{
    return m_fData[0]*rRhsVec.m_fData[0] + m_fData[1]*rRhsVec.m_fData[1] +
        m_fData[2]*rRhsVec.m_fData[2];
}
//----------------------------------------------------------------------------
inline float SEVector3f::Normalize()
{
    float fLength = GetLength();

    if( fLength > SEMath<float>::ZERO_TOLERANCE )
    {
        float fInvLength = 1.0f / fLength;
        m_fData[0] *= fInvLength;
        m_fData[1] *= fInvLength;
        m_fData[2] *= fInvLength;
    }
    else
    {
        m_fData[0] = 0.0f;
        m_fData[1] = 0.0f;
        m_fData[2] = 0.0f;
    }

    return fLength;
}
//----------------------------------------------------------------------------
inline SEVector3f SEVector3f::Cross(const SEVector3f& rRhsVec) const
{
    return SEVector3f(
        m_fData[1]*rRhsVec.m_fData[2] - m_fData[2]*rRhsVec.m_fData[1],
        m_fData[2]*rRhsVec.m_fData[0] - m_fData[0]*rRhsVec.m_fData[2],
        m_fData[0]*rRhsVec.m_fData[1] - m_fData[1]*rRhsVec.m_fData[0]);
}
//----------------------------------------------------------------------------
inline SEVector3f SEVector3f::UnitCross(const SEVector3f& rRhsVec) const
{
    SEVector3f vec3fCross(
        m_fData[1]*rRhsVec.m_fData[2] - m_fData[2]*rRhsVec.m_fData[1],
        m_fData[2]*rRhsVec.m_fData[0] - m_fData[0]*rRhsVec.m_fData[2],
        m_fData[0]*rRhsVec.m_fData[1] - m_fData[1]*rRhsVec.m_fData[0]);
    vec3fCross.Normalize();

    return vec3fCross;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 双精度3维向量类
//----------------------------------------------------------------------------
inline int SEVector3d::CompareData(const SEVector3d& rVecV) const
{
    return memcmp(m_dData, rVecV.m_dData, 3*sizeof(double));
}
//----------------------------------------------------------------------------
inline double SEVector3d::GetLength() const
{
    return SEMath<double>::Sqrt(m_dData[0]*m_dData[0] +
        m_dData[1]*m_dData[1] + m_dData[2]*m_dData[2]);
}
//----------------------------------------------------------------------------
inline double SEVector3d::GetSquaredLength() const
{
    return m_dData[0]*m_dData[0] + m_dData[1]*m_dData[1] + 
        m_dData[2]*m_dData[2];
}
//----------------------------------------------------------------------------
inline double SEVector3d::Dot(const SEVector3d& rRhsVec) const
{
    return m_dData[0]*rRhsVec.m_dData[0] + m_dData[1]*rRhsVec.m_dData[1] +
        m_dData[2]*rRhsVec.m_dData[2];
}
//----------------------------------------------------------------------------
inline double SEVector3d::Normalize()
{
    double dLength = GetLength();

    if( dLength > SEMath<double>::ZERO_TOLERANCE )
    {
        double dInvLength = 1.0 / dLength;
        m_dData[0] *= dInvLength;
        m_dData[1] *= dInvLength;
        m_dData[2] *= dInvLength;
    }
    else
    {
        m_dData[0] = 0.0;
        m_dData[1] = 0.0;
        m_dData[2] = 0.0;
    }

    return dLength;
}
//----------------------------------------------------------------------------
inline SEVector3d SEVector3d::Cross(const SEVector3d& rRhsVec) const
{
    return SEVector3d(
        m_dData[1]*rRhsVec.m_dData[2] - m_dData[2]*rRhsVec.m_dData[1],
        m_dData[2]*rRhsVec.m_dData[0] - m_dData[0]*rRhsVec.m_dData[2],
        m_dData[0]*rRhsVec.m_dData[1] - m_dData[1]*rRhsVec.m_dData[0]);
}
//----------------------------------------------------------------------------
inline SEVector3d SEVector3d::UnitCross(const SEVector3d& rRhsVec) const
{
    SEVector3d vec3fCross(
        m_dData[1]*rRhsVec.m_dData[2] - m_dData[2]*rRhsVec.m_dData[1],
        m_dData[2]*rRhsVec.m_dData[0] - m_dData[0]*rRhsVec.m_dData[2],
        m_dData[0]*rRhsVec.m_dData[1] - m_dData[1]*rRhsVec.m_dData[0]);
    vec3fCross.Normalize();

    return vec3fCross;
}
//----------------------------------------------------------------------------