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
#include "SEVector4.h"

using namespace Swing;

//----------------------------------------------------------------------------
// 单精度4维向量类
//----------------------------------------------------------------------------

const Vector4f Vector4f::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4f Vector4f::UNIT_X(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4f Vector4f::UNIT_Y(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4f Vector4f::UNIT_Z(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4f Vector4f::UNIT_W(0.0f, 0.0f, 0.0f, 1.0f);

//----------------------------------------------------------------------------
Vector4f::Vector4f()
{
}
//----------------------------------------------------------------------------
Vector4f::Vector4f(float fX, float fY, float fZ, float fW)
{
    m_fData[0] = fX;
    m_fData[1] = fY;
    m_fData[2] = fZ;
    m_fData[3] = fW;
}
//----------------------------------------------------------------------------
Vector4f::Vector4f(const Vector4f& rVec)
{
    m_fData[0] = rVec.m_fData[0];
    m_fData[1] = rVec.m_fData[1];
    m_fData[2] = rVec.m_fData[2];
    m_fData[3] = rVec.m_fData[3];
}
//----------------------------------------------------------------------------
Vector4f::operator const float*() const
{
    return m_fData;
}
//----------------------------------------------------------------------------
Vector4f::operator float*()
{
    return m_fData;
}
//----------------------------------------------------------------------------
float Vector4f::operator[](int i) const
{
    SE_ASSERT( 0 <= i && i <= 3 );
    return m_fData[i];
}
//----------------------------------------------------------------------------
float& Vector4f::operator[](int i)
{
    SE_ASSERT( 0 <= i && i <= 3 );
    return m_fData[i];
}
//----------------------------------------------------------------------------
Vector4f& Vector4f::operator=(const Vector4f& rVec)
{
    m_fData[0] = rVec.m_fData[0];
    m_fData[1] = rVec.m_fData[1];
    m_fData[2] = rVec.m_fData[2];
    m_fData[3] = rVec.m_fData[3];
    return *this;
}
//----------------------------------------------------------------------------
bool Vector4f::operator==(const Vector4f& rVec) const
{
    return CompareData(rVec) == 0;
}
//----------------------------------------------------------------------------
bool Vector4f::operator!=(const Vector4f& rVec) const
{
    return CompareData(rVec) != 0;
}
//----------------------------------------------------------------------------
bool Vector4f::operator<(const Vector4f& rVec) const
{
    return CompareData(rVec) < 0;
}
//----------------------------------------------------------------------------
bool Vector4f::operator<=(const Vector4f& rVec) const
{
    return CompareData(rVec) <= 0;
}
//----------------------------------------------------------------------------
bool Vector4f::operator>(const Vector4f& rVec) const
{
    return CompareData(rVec) > 0;
}
//----------------------------------------------------------------------------
bool Vector4f::operator>=(const Vector4f& rVec) const
{
    return CompareData(rVec) >= 0;
}
//----------------------------------------------------------------------------
Vector4f Vector4f::operator+(const Vector4f& rRhsVec) const
{
    return Vector4f(
                   m_fData[0] + rRhsVec.m_fData[0],
                   m_fData[1] + rRhsVec.m_fData[1],
                   m_fData[2] + rRhsVec.m_fData[2],
                   m_fData[3] + rRhsVec.m_fData[3]);
}
//----------------------------------------------------------------------------
Vector4f Vector4f::operator-(const Vector4f& rRhsVec) const
{
    return Vector4f(
                   m_fData[0] - rRhsVec.m_fData[0],
                   m_fData[1] - rRhsVec.m_fData[1],
                   m_fData[2] - rRhsVec.m_fData[2],
                   m_fData[3] - rRhsVec.m_fData[3]);
}
//----------------------------------------------------------------------------
Vector4f Vector4f::operator*(float fScalar) const
{
    return Vector4f(
                   fScalar * m_fData[0],
                   fScalar * m_fData[1],
                   fScalar * m_fData[2],
                   fScalar * m_fData[3]);
}
//----------------------------------------------------------------------------
Vector4f Vector4f::operator/(float fScalar) const
{
    Vector4f Res;

    if( fScalar != 0.0f )
    {
        float fInvScalar = 1.0f / fScalar;
        Res.m_fData[0] = fInvScalar * m_fData[0];
        Res.m_fData[1] = fInvScalar * m_fData[1];
        Res.m_fData[2] = fInvScalar * m_fData[2];
        Res.m_fData[3] = fInvScalar * m_fData[3];
    }
    else
    {
        Res.m_fData[0] = Math<float>::MAX_REAL;
        Res.m_fData[1] = Math<float>::MAX_REAL;
        Res.m_fData[2] = Math<float>::MAX_REAL;
        Res.m_fData[3] = Math<float>::MAX_REAL;
    }

    return Res;
}
//----------------------------------------------------------------------------
Vector4f Vector4f::operator-() const
{
    return Vector4f(
                   -m_fData[0],
                   -m_fData[1],
                   -m_fData[2],
                   -m_fData[3]);
}
//----------------------------------------------------------------------------
Vector4f Swing::operator*(float fLhsScalar, const Vector4f& rRhsVec)
{
    return Vector4f(
                   fLhsScalar * rRhsVec[0],
                   fLhsScalar * rRhsVec[1],
                   fLhsScalar * rRhsVec[2],
                   fLhsScalar * rRhsVec[3]);
}
//----------------------------------------------------------------------------
Vector4f& Vector4f::operator+=(const Vector4f& rRhsVec)
{
    m_fData[0] += rRhsVec.m_fData[0];
    m_fData[1] += rRhsVec.m_fData[1];
    m_fData[2] += rRhsVec.m_fData[2];
    m_fData[3] += rRhsVec.m_fData[3];

    return *this;
}
//----------------------------------------------------------------------------
Vector4f& Vector4f::operator+=(float fScalar)
{
    m_fData[0] += fScalar;
    m_fData[1] += fScalar;
    m_fData[2] += fScalar;
    m_fData[3] += fScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector4f& Vector4f::operator-=(const Vector4f& rRhsVec)
{
    m_fData[0] -= rRhsVec.m_fData[0];
    m_fData[1] -= rRhsVec.m_fData[1];
    m_fData[2] -= rRhsVec.m_fData[2];
    m_fData[3] -= rRhsVec.m_fData[3];

    return *this;
}
//----------------------------------------------------------------------------
Vector4f& Vector4f::operator-=(float fScalar)
{
    m_fData[0] -= fScalar;
    m_fData[1] -= fScalar;
    m_fData[2] -= fScalar;
    m_fData[3] -= fScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector4f& Vector4f::operator*=(float fScalar)
{
    m_fData[0] *= fScalar;
    m_fData[1] *= fScalar;
    m_fData[2] *= fScalar;
    m_fData[3] *= fScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector4f& Vector4f::operator/=(float fScalar)
{
    if( fScalar != 0.0f )
    {
        float fInvScalar = 1.0f / fScalar;
        m_fData[0] *= fInvScalar;
        m_fData[1] *= fInvScalar;
        m_fData[2] *= fInvScalar;
        m_fData[3] *= fInvScalar;
    }
    else
    {
        m_fData[0] = Math<float>::MAX_REAL;
        m_fData[1] = Math<float>::MAX_REAL;
        m_fData[2] = Math<float>::MAX_REAL;
        m_fData[3] = Math<float>::MAX_REAL;
    }

    return *this;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 双精度4维向量类
//----------------------------------------------------------------------------

const Vector4d Vector4d::ZERO(0.0, 0.0, 0.0, 0.0);
const Vector4d Vector4d::UNIT_X(1.0, 0.0, 0.0, 0.0);
const Vector4d Vector4d::UNIT_Y(0.0, 1.0, 0.0, 0.0);
const Vector4d Vector4d::UNIT_Z(0.0, 0.0, 1.0, 0.0);
const Vector4d Vector4d::UNIT_W(0.0, 0.0, 0.0, 1.0);

//----------------------------------------------------------------------------
Vector4d::Vector4d()
{
}
//----------------------------------------------------------------------------
Vector4d::Vector4d(double dX, double dY, double dZ, double dW)
{
    m_dData[0] = dX;
    m_dData[1] = dY;
    m_dData[2] = dZ;
    m_dData[3] = dW;
}
//----------------------------------------------------------------------------
Vector4d::Vector4d(const Vector4d& rVec)
{
    m_dData[0] = rVec.m_dData[0];
    m_dData[1] = rVec.m_dData[1];
    m_dData[2] = rVec.m_dData[2];
    m_dData[3] = rVec.m_dData[3];
}
//----------------------------------------------------------------------------
Vector4d::operator const double*() const
{
    return m_dData;
}
//----------------------------------------------------------------------------
Vector4d::operator double*()
{
    return m_dData;
}
//----------------------------------------------------------------------------
double Vector4d::operator[](int i) const
{
    SE_ASSERT( 0 <= i && i <= 3 );
    return m_dData[i];
}
//----------------------------------------------------------------------------
double& Vector4d::operator[](int i)
{
    SE_ASSERT( 0 <= i && i <= 3 );
    return m_dData[i];
}
//----------------------------------------------------------------------------
Vector4d& Vector4d::operator=(const Vector4d& rVec)
{
    m_dData[0] = rVec.m_dData[0];
    m_dData[1] = rVec.m_dData[1];
    m_dData[2] = rVec.m_dData[2];
    m_dData[3] = rVec.m_dData[3];
    return *this;
}
//----------------------------------------------------------------------------
bool Vector4d::operator==(const Vector4d& rVec) const
{
    return CompareData(rVec) == 0;
}
//----------------------------------------------------------------------------
bool Vector4d::operator!=(const Vector4d& rVec) const
{
    return CompareData(rVec) != 0;
}
//----------------------------------------------------------------------------
bool Vector4d::operator<(const Vector4d& rVec) const
{
    return CompareData(rVec) < 0;
}
//----------------------------------------------------------------------------
bool Vector4d::operator<=(const Vector4d& rVec) const
{
    return CompareData(rVec) <= 0;
}
//----------------------------------------------------------------------------
bool Vector4d::operator>(const Vector4d& rVec) const
{
    return CompareData(rVec) > 0;
}
//----------------------------------------------------------------------------
bool Vector4d::operator>=(const Vector4d& rVec) const
{
    return CompareData(rVec) >= 0;
}
//----------------------------------------------------------------------------
Vector4d Vector4d::operator+(const Vector4d& rRhsVec) const
{
    return Vector4d(
                   m_dData[0] + rRhsVec.m_dData[0],
                   m_dData[1] + rRhsVec.m_dData[1],
                   m_dData[2] + rRhsVec.m_dData[2],
                   m_dData[3] + rRhsVec.m_dData[3]);
}
//----------------------------------------------------------------------------
Vector4d Vector4d::operator-(const Vector4d& rRhsVec) const
{
    return Vector4d(
                   m_dData[0] - rRhsVec.m_dData[0],
                   m_dData[1] - rRhsVec.m_dData[1],
                   m_dData[2] - rRhsVec.m_dData[2],
                   m_dData[3] - rRhsVec.m_dData[3]);
}
//----------------------------------------------------------------------------
Vector4d Vector4d::operator*(double dScalar) const
{
    return Vector4d(
                   dScalar * m_dData[0],
                   dScalar * m_dData[1],
                   dScalar * m_dData[2],
                   dScalar * m_dData[3]);
}
//----------------------------------------------------------------------------
Vector4d Vector4d::operator/(double dScalar) const
{
    Vector4d Res;

    if( dScalar != 0.0 )
    {
        double dInvScalar = 1.0 / dScalar;
        Res.m_dData[0] = dInvScalar * m_dData[0];
        Res.m_dData[1] = dInvScalar * m_dData[1];
        Res.m_dData[2] = dInvScalar * m_dData[2];
        Res.m_dData[3] = dInvScalar * m_dData[3];
    }
    else
    {
        Res.m_dData[0] = Math<double>::MAX_REAL;
        Res.m_dData[1] = Math<double>::MAX_REAL;
        Res.m_dData[2] = Math<double>::MAX_REAL;
        Res.m_dData[3] = Math<double>::MAX_REAL;
    }

    return Res;
}
//----------------------------------------------------------------------------
Vector4d Vector4d::operator-() const
{
    return Vector4d(
                   -m_dData[0],
                   -m_dData[1],
                   -m_dData[2],
                   -m_dData[3]);
}
//----------------------------------------------------------------------------
Vector4d Swing::operator*(double dLhsScalar, const Vector4d& rRhsVec)
{
    return Vector4d(
                   dLhsScalar * rRhsVec[0],
                   dLhsScalar * rRhsVec[1],
                   dLhsScalar * rRhsVec[2],
                   dLhsScalar * rRhsVec[3]);
}
//----------------------------------------------------------------------------
Vector4d& Vector4d::operator+=(const Vector4d& rRhsVec)
{
    m_dData[0] += rRhsVec.m_dData[0];
    m_dData[1] += rRhsVec.m_dData[1];
    m_dData[2] += rRhsVec.m_dData[2];
    m_dData[3] += rRhsVec.m_dData[3];

    return *this;
}
//----------------------------------------------------------------------------
Vector4d& Vector4d::operator+=(double dScalar)
{
    m_dData[0] += dScalar;
    m_dData[1] += dScalar;
    m_dData[2] += dScalar;
    m_dData[3] += dScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector4d& Vector4d::operator-=(const Vector4d& rRhsVec)
{
    m_dData[0] -= rRhsVec.m_dData[0];
    m_dData[1] -= rRhsVec.m_dData[1];
    m_dData[2] -= rRhsVec.m_dData[2];
    m_dData[3] -= rRhsVec.m_dData[3];

    return *this;
}
//----------------------------------------------------------------------------
Vector4d& Vector4d::operator-=(double dScalar)
{
    m_dData[0] -= dScalar;
    m_dData[1] -= dScalar;
    m_dData[2] -= dScalar;
    m_dData[3] -= dScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector4d& Vector4d::operator*=(double dScalar)
{
    m_dData[0] *= dScalar;
    m_dData[1] *= dScalar;
    m_dData[2] *= dScalar;
    m_dData[3] *= dScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector4d& Vector4d::operator/=(double dScalar)
{
    if( dScalar != 0.0 )
    {
        double dInvScalar = 1.0 / dScalar;
        m_dData[0] *= dInvScalar;
        m_dData[1] *= dInvScalar;
        m_dData[2] *= dInvScalar;
        m_dData[3] *= dInvScalar;
    }
    else
    {
        m_dData[0] = Math<double>::MAX_REAL;
        m_dData[1] = Math<double>::MAX_REAL;
        m_dData[2] = Math<double>::MAX_REAL;
        m_dData[3] = Math<double>::MAX_REAL;
    }

    return *this;
}
//----------------------------------------------------------------------------