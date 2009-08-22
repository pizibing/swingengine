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
#include "SEVector2.h"

using namespace Swing;

//----------------------------------------------------------------------------
// 单精度2维向量类
//----------------------------------------------------------------------------

const Vector2f Vector2f::ZERO(0.0f, 0.0f);
const Vector2f Vector2f::UNIT_X(1.0f, 0.0f);
const Vector2f Vector2f::UNIT_Y(0.0f, 1.0f);

//----------------------------------------------------------------------------
Vector2f::Vector2f()
{
}
//----------------------------------------------------------------------------
Vector2f::Vector2f(float fX, float fY)
{
    m_fData[0] = fX;
    m_fData[1] = fY;
}
//----------------------------------------------------------------------------
Vector2f::Vector2f(const Vector2f& rVec)
{
    m_fData[0] = rVec.m_fData[0];
    m_fData[1] = rVec.m_fData[1];
}
//----------------------------------------------------------------------------
Vector2f::operator const float*() const
{
    return m_fData;
}
//----------------------------------------------------------------------------
Vector2f::operator float*()
{
    return m_fData;
}
//----------------------------------------------------------------------------
float Vector2f::operator[](int i) const
{
    SE_ASSERT( 0 <= i && i <= 1 );

    return m_fData[i];
}
//----------------------------------------------------------------------------
float& Vector2f::operator[](int i)
{
    SE_ASSERT( 0 <= i && i <= 1 );

    return m_fData[i];
}
//----------------------------------------------------------------------------
Vector2f& Vector2f::operator=(const Vector2f& rVec)
{
    m_fData[0] = rVec.m_fData[0];
    m_fData[1] = rVec.m_fData[1];

    return *this;
}
//----------------------------------------------------------------------------
bool Vector2f::operator==(const Vector2f& rVec) const
{
    return CompareData(rVec) == 0;
}
//----------------------------------------------------------------------------
bool Vector2f::operator!=(const Vector2f& rVec) const
{
    return CompareData(rVec) != 0;
}
//----------------------------------------------------------------------------
bool Vector2f::operator<(const Vector2f& rVec) const
{
    return CompareData(rVec) < 0;
}
//----------------------------------------------------------------------------
bool Vector2f::operator<=(const Vector2f& rVec) const
{
    return CompareData(rVec) <= 0;
}
//----------------------------------------------------------------------------
bool Vector2f::operator>(const Vector2f& rVec) const
{
    return CompareData(rVec) > 0;
}
//----------------------------------------------------------------------------
bool Vector2f::operator>=(const Vector2f& rVec) const
{
    return CompareData(rVec) >= 0;
}
//----------------------------------------------------------------------------
Vector2f Vector2f::operator+(const Vector2f& rRhsVec) const
{
    return Vector2f(
                   m_fData[0] + rRhsVec.m_fData[0],
                   m_fData[1] + rRhsVec.m_fData[1]);
}
//----------------------------------------------------------------------------
Vector2f Vector2f::operator-(const Vector2f& rRhsVec) const
{
    return Vector2f(
                   m_fData[0] - rRhsVec.m_fData[0],
                   m_fData[1] - rRhsVec.m_fData[1]);
}
//----------------------------------------------------------------------------
Vector2f Vector2f::operator*(float fScalar) const
{
    return Vector2f(
                   fScalar * m_fData[0],
                   fScalar * m_fData[1]);
}
//----------------------------------------------------------------------------
Vector2f Vector2f::operator/(float fScalar) const
{
    Vector2f Res;

    if( fScalar != 0.0f )
    {
        float fInvScalar = (1.0f) / fScalar;
        Res.m_fData[0] = fInvScalar * m_fData[0];
        Res.m_fData[1] = fInvScalar * m_fData[1];
    }
    else
    {
        Res.m_fData[0] = Math<float>::MAX_REAL;
        Res.m_fData[1] = Math<float>::MAX_REAL;
    }

    return Res;
}
//----------------------------------------------------------------------------
Vector2f Vector2f::operator-() const
{
    return Vector2f(
                   -m_fData[0],
                   -m_fData[1]);
}
//----------------------------------------------------------------------------
Vector2f Swing::operator*(float fLhsScalar, const Vector2f& rRhsVec)
{
    return Vector2f(
                   fLhsScalar * rRhsVec[0],
                   fLhsScalar * rRhsVec[1]);
}
//----------------------------------------------------------------------------
Vector2f& Vector2f::operator+=(const Vector2f& rRhsVec)
{
    m_fData[0] += rRhsVec.m_fData[0];
    m_fData[1] += rRhsVec.m_fData[1];

    return *this;
}
//----------------------------------------------------------------------------
Vector2f& Vector2f::operator+=(float fScalar)
{
    m_fData[0] += fScalar;
    m_fData[1] += fScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector2f& Vector2f::operator-=(const Vector2f& rRhsVec)
{
    m_fData[0] -= rRhsVec.m_fData[0];
    m_fData[1] -= rRhsVec.m_fData[1];

    return *this;
}
//----------------------------------------------------------------------------
Vector2f& Vector2f::operator-=(float fScalar)
{
    m_fData[0] -= fScalar;
    m_fData[1] -= fScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector2f& Vector2f::operator*=(float fScalar)
{
    m_fData[0] *= fScalar;
    m_fData[1] *= fScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector2f& Vector2f::operator/=(float fScalar)
{
    if( fScalar != 0.0f )
    {
        float fInvScalar = (1.0f) / fScalar;
        m_fData[0] *= fInvScalar;
        m_fData[1] *= fInvScalar;
    }
    else
    {
        m_fData[0] = Math<float>::MAX_REAL;
        m_fData[1] = Math<float>::MAX_REAL;
    }

    return *this;
}
//----------------------------------------------------------------------------
void Vector2f::Orthonormalize(Vector2f& rVecU, Vector2f& rVecV)
{
    rVecU.Normalize();
    // V在U上的投影长度
    float fDot0 = rVecU.Dot(rVecV);
    // V = V减去V在U上的投影向量
    rVecV -= rVecU*fDot0;
    rVecV.Normalize();
}
//----------------------------------------------------------------------------
void Vector2f::GetOrthonormalBasis(Vector2f& rVecU, Vector2f& rVecV, 
    bool bUnitLengthV)
{
    if( !bUnitLengthV )
        rVecV.Normalize();

    rVecV.GetPerp(rVecU);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 双精度2维向量类
//----------------------------------------------------------------------------

const Vector2d Vector2d::ZERO(0.0, 0.0);
const Vector2d Vector2d::UNIT_X(1.0, 0.0);
const Vector2d Vector2d::UNIT_Y(0.0, 1.0);

//----------------------------------------------------------------------------
Vector2d::Vector2d()
{
}
//----------------------------------------------------------------------------
Vector2d::Vector2d(double dX, double dY)
{
    m_dData[0] = dX;
    m_dData[1] = dY;
}
//----------------------------------------------------------------------------
Vector2d::Vector2d(const Vector2d& rVec)
{
    m_dData[0] = rVec.m_dData[0];
    m_dData[1] = rVec.m_dData[1];
}
//----------------------------------------------------------------------------
Vector2d::operator const double*() const
{
    return m_dData;
}
//----------------------------------------------------------------------------
Vector2d::operator double*()
{
    return m_dData;
}
//----------------------------------------------------------------------------
double Vector2d::operator[](int i) const
{
    SE_ASSERT( 0 <= i && i <= 1 );

    return m_dData[i];
}
//----------------------------------------------------------------------------
double& Vector2d::operator[](int i)
{
    SE_ASSERT( 0 <= i && i <= 1 );

    return m_dData[i];
}
//----------------------------------------------------------------------------
Vector2d& Vector2d::operator=(const Vector2d& rVec)
{
    m_dData[0] = rVec.m_dData[0];
    m_dData[1] = rVec.m_dData[1];

    return *this;
}
//----------------------------------------------------------------------------
bool Vector2d::operator==(const Vector2d& rVec) const
{
    return CompareData(rVec) == 0;
}
//----------------------------------------------------------------------------
bool Vector2d::operator!=(const Vector2d& rVec) const
{
    return CompareData(rVec) != 0;
}
//----------------------------------------------------------------------------
bool Vector2d::operator<(const Vector2d& rVec) const
{
    return CompareData(rVec) < 0;
}
//----------------------------------------------------------------------------
bool Vector2d::operator<=(const Vector2d& rVec) const
{
    return CompareData(rVec) <= 0;
}
//----------------------------------------------------------------------------
bool Vector2d::operator>(const Vector2d& rVec) const
{
    return CompareData(rVec) > 0;
}
//----------------------------------------------------------------------------
bool Vector2d::operator>=(const Vector2d& rVec) const
{
    return CompareData(rVec) >= 0;
}
//----------------------------------------------------------------------------
Vector2d Vector2d::operator+(const Vector2d& rRhsVec) const
{
    return Vector2d(
                   m_dData[0] + rRhsVec.m_dData[0],
                   m_dData[1] + rRhsVec.m_dData[1]);
}
//----------------------------------------------------------------------------
Vector2d Vector2d::operator-(const Vector2d& rRhsVec) const
{
    return Vector2d(
                   m_dData[0] - rRhsVec.m_dData[0],
                   m_dData[1] - rRhsVec.m_dData[1]);
}
//----------------------------------------------------------------------------
Vector2d Vector2d::operator*(double dScalar) const
{
    return Vector2d(
                   dScalar * m_dData[0],
                   dScalar * m_dData[1]);
}
//----------------------------------------------------------------------------
Vector2d Vector2d::operator/(double dScalar) const
{
    Vector2d Res;

    if( dScalar != 0.0 )
    {
        double dInvScalar = 1.0 / dScalar;
        Res.m_dData[0] = dInvScalar * m_dData[0];
        Res.m_dData[1] = dInvScalar * m_dData[1];
    }
    else
    {
        Res.m_dData[0] = Math<double>::MAX_REAL;
        Res.m_dData[1] = Math<double>::MAX_REAL;
    }

    return Res;
}
//----------------------------------------------------------------------------
Vector2d Vector2d::operator-() const
{
    return Vector2d(
                   -m_dData[0],
                   -m_dData[1]);
}
//----------------------------------------------------------------------------
Vector2d Swing::operator*(double dLhsScalar, const Vector2d& rRhsVec)
{
    return Vector2d(
                   dLhsScalar * rRhsVec[0],
                   dLhsScalar * rRhsVec[1]);
}
//----------------------------------------------------------------------------
Vector2d& Vector2d::operator+=(const Vector2d& rRhsVec)
{
    m_dData[0] += rRhsVec.m_dData[0];
    m_dData[1] += rRhsVec.m_dData[1];

    return *this;
}
//----------------------------------------------------------------------------
Vector2d& Vector2d::operator+=(double dScalar)
{
    m_dData[0] += dScalar;
    m_dData[1] += dScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector2d& Vector2d::operator-=(const Vector2d& rRhsVec)
{
    m_dData[0] -= rRhsVec.m_dData[0];
    m_dData[1] -= rRhsVec.m_dData[1];

    return *this;
}
//----------------------------------------------------------------------------
Vector2d& Vector2d::operator-=(double dScalar)
{
    m_dData[0] -= dScalar;
    m_dData[1] -= dScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector2d& Vector2d::operator*=(double dScalar)
{
    m_dData[0] *= dScalar;
    m_dData[1] *= dScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector2d& Vector2d::operator/=(double dScalar)
{
    if( dScalar != 0.0 )
    {
        double dInvScalar = 1.0 / dScalar;
        m_dData[0] *= dInvScalar;
        m_dData[1] *= dInvScalar;
    }
    else
    {
        m_dData[0] = Math<double>::MAX_REAL;
        m_dData[1] = Math<double>::MAX_REAL;
    }

    return *this;
}
//----------------------------------------------------------------------------
void Vector2d::Orthonormalize(Vector2d& rVecU, Vector2d& rVecV)
{
    rVecU.Normalize();
    // V在U上的投影长度
    double dDot0 = rVecU.Dot(rVecV);
    // V = V减去V在U上的投影向量
    rVecV -= rVecU*dDot0;
    rVecV.Normalize();
}
//----------------------------------------------------------------------------
void Vector2d::GetOrthonormalBasis(Vector2d& rVecU, Vector2d& rVecV, 
    bool bUnitLengthV)
{
    if( !bUnitLengthV )
        rVecV.Normalize();

    rVecV.GetPerp(rVecU);
}
//----------------------------------------------------------------------------