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
#include "SEVector3.h"

using namespace Swing;

//----------------------------------------------------------------------------
// 单精度3维向量类
//----------------------------------------------------------------------------

const Vector3f Vector3f::ZERO(0.0f, 0.0f, 0.0f);
const Vector3f Vector3f::UNIT_X(1.0f, 0.0f, 0.0f);
const Vector3f Vector3f::UNIT_Y(0.0f, 1.0f, 0.0f);
const Vector3f Vector3f::UNIT_Z(0.0f, 0.0f, 1.0f);

//----------------------------------------------------------------------------
Vector3f::Vector3f()
{
}
//----------------------------------------------------------------------------
Vector3f::Vector3f(float fX, float fY, float fZ)
{
    m_fData[0] = fX;
    m_fData[1] = fY;
    m_fData[2] = fZ;
}
//----------------------------------------------------------------------------
Vector3f::Vector3f(const Vector3f& rVecV)
{
    m_fData[0] = rVecV.m_fData[0];
    m_fData[1] = rVecV.m_fData[1];
    m_fData[2] = rVecV.m_fData[2];
}
//----------------------------------------------------------------------------
Vector3f::operator const float*() const
{
    return m_fData;
}
//----------------------------------------------------------------------------
Vector3f::operator float*()
{
    return m_fData;
}
//----------------------------------------------------------------------------
float Vector3f::operator[](int i) const
{
    SE_ASSERT( 0 <= i && i <= 2 );

    return m_fData[i];
}
//----------------------------------------------------------------------------
float& Vector3f::operator[](int i)
{
    SE_ASSERT( 0 <= i && i <= 2 );

    return m_fData[i];
}
//----------------------------------------------------------------------------
Vector3f& Vector3f::operator=(const Vector3f& rVecV)
{
    m_fData[0] = rVecV.m_fData[0];
    m_fData[1] = rVecV.m_fData[1];
    m_fData[2] = rVecV.m_fData[2];

    return *this;
}
//----------------------------------------------------------------------------
bool Vector3f::operator==(const Vector3f& rVecV) const
{
    return CompareData(rVecV) == 0;
}
//----------------------------------------------------------------------------
bool Vector3f::operator!=(const Vector3f& rVecV) const
{
    return CompareData(rVecV) != 0;
}
//----------------------------------------------------------------------------
bool Vector3f::operator<(const Vector3f& rVecV) const
{
    return CompareData(rVecV) < 0;
}
//----------------------------------------------------------------------------
bool Vector3f::operator<=(const Vector3f& rVecV) const
{
    return CompareData(rVecV) <= 0;
}
//----------------------------------------------------------------------------
bool Vector3f::operator>(const Vector3f& rVecV) const
{
    return CompareData(rVecV) > 0;
}
//----------------------------------------------------------------------------
bool Vector3f::operator>=(const Vector3f& rVecV) const
{
    return CompareData(rVecV) >= 0;
}
//----------------------------------------------------------------------------
Vector3f Vector3f::operator+(const Vector3f& rRhsVec) const
{
    return Vector3f(
                   m_fData[0] + rRhsVec.m_fData[0],
                   m_fData[1] + rRhsVec.m_fData[1],
                   m_fData[2] + rRhsVec.m_fData[2]);
}
//----------------------------------------------------------------------------
Vector3f Vector3f::operator-(const Vector3f& rRhsVec) const
{
    return Vector3f(
                   m_fData[0] - rRhsVec.m_fData[0],
                   m_fData[1] - rRhsVec.m_fData[1],
                   m_fData[2] - rRhsVec.m_fData[2]);
}
//----------------------------------------------------------------------------
Vector3f Vector3f::operator*(float fScalar) const
{
    return Vector3f(
                   fScalar * m_fData[0],
                   fScalar * m_fData[1],
                   fScalar * m_fData[2]);
}
//----------------------------------------------------------------------------
Vector3f Vector3f::operator/(float fScalar) const
{
    Vector3f Res;

    if( fScalar != 0.0f )
    {
        float fInvScalar = 1.0f/fScalar;
        Res.m_fData[0] = fInvScalar * m_fData[0];
        Res.m_fData[1] = fInvScalar * m_fData[1];
        Res.m_fData[2] = fInvScalar * m_fData[2];
    }
    else
    {
        Res.m_fData[0] = Math<float>::MAX_REAL;
        Res.m_fData[1] = Math<float>::MAX_REAL;
        Res.m_fData[2] = Math<float>::MAX_REAL;
    }

    return Res;
}
//----------------------------------------------------------------------------
Vector3f Vector3f::operator-() const
{
    return Vector3f(
                   -m_fData[0],
                   -m_fData[1],
                   -m_fData[2]);
}
//----------------------------------------------------------------------------
Vector3f& Vector3f::operator+=(const Vector3f& rRhsVec)
{
    m_fData[0] += rRhsVec.m_fData[0];
    m_fData[1] += rRhsVec.m_fData[1];
    m_fData[2] += rRhsVec.m_fData[2];

    return *this;
}
//----------------------------------------------------------------------------
Vector3f& Vector3f::operator+=(float fScalar)
{
    m_fData[0] += fScalar;
    m_fData[1] += fScalar;
    m_fData[2] += fScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector3f& Vector3f::operator-=(const Vector3f& rRhsVec)
{
    m_fData[0] -= rRhsVec.m_fData[0];
    m_fData[1] -= rRhsVec.m_fData[1];
    m_fData[2] -= rRhsVec.m_fData[2];

    return *this;
}
//----------------------------------------------------------------------------
Vector3f& Vector3f::operator-=(float fScalar)
{
    m_fData[0] -= fScalar;
    m_fData[1] -= fScalar;
    m_fData[2] -= fScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector3f& Vector3f::operator*=(float fScalar)
{
    m_fData[0] *= fScalar;
    m_fData[1] *= fScalar;
    m_fData[2] *= fScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector3f& Vector3f::operator/=(float fScalar)
{
    if( fScalar != 0.0f )
    {
        float fInvScalar = 1.0f / fScalar;
        m_fData[0] *= fInvScalar;
        m_fData[1] *= fInvScalar;
        m_fData[2] *= fInvScalar;
    }
    else
    {
        m_fData[0] = Math<float>::MAX_REAL;
        m_fData[1] = Math<float>::MAX_REAL;
        m_fData[2] = Math<float>::MAX_REAL;
    }

    return *this;
}
//----------------------------------------------------------------------------
void Vector3f::Orthonormalize(Vector3f& rVecU, Vector3f& rVecV, 
    Vector3f& rVecW)
{
    rVecU.Normalize();
    // V在U上的投影长度
    float fDot0 = rVecU.Dot(rVecV);
    // V = V减去V在U上的投影向量
    rVecV -= fDot0 * rVecU;
    rVecV.Normalize();
    // W在V上的投影长度
    float fDot1 = rVecV.Dot(rVecW);
	// W在U上的投影长度
    fDot0 = rVecU.Dot(rVecW);
	// W = W减去W在U上的投影向量再减去W在V上的投影向量
    rVecW -= fDot0*rVecU + fDot1*rVecV;
    rVecW.Normalize();
}
//----------------------------------------------------------------------------
void Vector3f::Orthonormalize(Vector3f* pVec)
{
	SE_ASSERT( pVec );

    Orthonormalize(pVec[0], pVec[1], pVec[2]);
}
//----------------------------------------------------------------------------
void Vector3f::GetOrthonormalBasis(Vector3f& rVecU, Vector3f& rVecV, 
    Vector3f& rVecW, bool bUnitLengthW)
{
    if( !bUnitLengthW )
        rVecW.Normalize();

    float fInvLength;

    if( Math<float>::FAbs(rVecW.m_fData[0]) >= 
        Math<float>::FAbs(rVecW.m_fData[1]) )
    {
        // W.X或W.Z是最大分量
        fInvLength = Math<float>::InvSqrt(rVecW.m_fData[0]*rVecW.m_fData[0] + 
            rVecW.m_fData[2]*rVecW.m_fData[2]);

        // 在左手坐标系中,
        // 对于向量(a,b,c),我们想获得与其垂直的顺时针一侧向量为(c,0,-a),
        // 与其垂直的逆时针一侧向量为(-c,0,a)
        rVecU.m_fData[0] = rVecW.m_fData[2] * fInvLength;
        rVecU.m_fData[1] = 0.0f;
        rVecU.m_fData[2] = -rVecW.m_fData[0] * fInvLength;

        // 叉积生成V
        rVecV.m_fData[0] = rVecW.m_fData[1] * rVecU.m_fData[2];
        rVecV.m_fData[1] = rVecW.m_fData[2]*rVecU.m_fData[0] - 
            rVecW.m_fData[0]*rVecU.m_fData[2];
        rVecV.m_fData[2] = -rVecW.m_fData[1] * rVecU.m_fData[0];
    }
    else
    {
        // W.Y或W.Z是最大分量
        fInvLength = Math<float>::InvSqrt(rVecW.m_fData[1]*rVecW.m_fData[1] + 
            rVecW.m_fData[2]*rVecW.m_fData[2]);

        rVecU.m_fData[0] = 0.0f;
        rVecU.m_fData[1] = +rVecW.m_fData[2] * fInvLength;
        rVecU.m_fData[2] = -rVecW.m_fData[1] * fInvLength;
        
        // 叉积生成V
		rVecV.m_fData[0] = rVecW.m_fData[1]*rVecU.m_fData[2] - 
            rVecW.m_fData[2]*rVecU.m_fData[1];
        rVecV.m_fData[1] = -rVecW.m_fData[0] * rVecU.m_fData[2];
        rVecV.m_fData[2] = rVecW.m_fData[0] * rVecU.m_fData[1];
    }
}
//----------------------------------------------------------------------------
void Vector3f::ComputeExtremes(int iCount, const Vector3f* pPoints, 
    Vector3f& rMin, Vector3f& rMax)
{
    SE_ASSERT( iCount > 0 && pPoints );

    rMin = pPoints[0];
    rMax = rMin;
    for( int i = 1; i < iCount; i++ )
    {
        const Vector3f& rPoint = pPoints[i];
        for( int j = 0; j < 3; j++ )
        {
            if( rPoint[j] < rMin[j] )
            {
                rMin[j] = rPoint[j];
            }
            else if( rPoint[j] > rMax[j] )
            {
                rMax[j] = rPoint[j];
            }
        }
    }
}
//----------------------------------------------------------------------------
Vector3f Swing::operator*(float fLhsScalar, const Vector3f& rRhsVec)
{
    return Vector3f(
                   fLhsScalar * rRhsVec[0],
                   fLhsScalar * rRhsVec[1],
                   fLhsScalar * rRhsVec[2]);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 双精度3维向量类
//----------------------------------------------------------------------------

const Vector3d Vector3d::ZERO(0.0, 0.0, 0.0);
const Vector3d Vector3d::UNIT_X(1.0, 0.0, 0.0);
const Vector3d Vector3d::UNIT_Y(0.0, 1.0, 0.0);
const Vector3d Vector3d::UNIT_Z(0.0, 0.0, 1.0);

//----------------------------------------------------------------------------
Vector3d::Vector3d()
{
}
//----------------------------------------------------------------------------
Vector3d::Vector3d(double dX, double dY, double dZ)
{
    m_dData[0] = dX;
    m_dData[1] = dY;
    m_dData[2] = dZ;
}
//----------------------------------------------------------------------------
Vector3d::Vector3d(const Vector3d& rVecV)
{
    m_dData[0] = rVecV.m_dData[0];
    m_dData[1] = rVecV.m_dData[1];
    m_dData[2] = rVecV.m_dData[2];
}
//----------------------------------------------------------------------------
Vector3d::operator const double*() const
{
    return m_dData;
}
//----------------------------------------------------------------------------
Vector3d::operator double*()
{
    return m_dData;
}
//----------------------------------------------------------------------------
double Vector3d::operator[](int i) const
{
    SE_ASSERT( 0 <= i && i <= 2 );

    return m_dData[i];
}
//----------------------------------------------------------------------------
double& Vector3d::operator[](int i)
{
    SE_ASSERT( 0 <= i && i <= 2 );

    return m_dData[i];
}
//----------------------------------------------------------------------------
Vector3d& Vector3d::operator=(const Vector3d& rVecV)
{
    m_dData[0] = rVecV.m_dData[0];
    m_dData[1] = rVecV.m_dData[1];
    m_dData[2] = rVecV.m_dData[2];

    return *this;
}
//----------------------------------------------------------------------------
bool Vector3d::operator==(const Vector3d& rVecV) const
{
    return CompareData(rVecV) == 0;
}
//----------------------------------------------------------------------------
bool Vector3d::operator!=(const Vector3d& rVecV) const
{
    return CompareData(rVecV) != 0;
}
//----------------------------------------------------------------------------
bool Vector3d::operator<(const Vector3d& rVecV) const
{
    return CompareData(rVecV) < 0;
}
//----------------------------------------------------------------------------
bool Vector3d::operator<=(const Vector3d& rVecV) const
{
    return CompareData(rVecV) <= 0;
}
//----------------------------------------------------------------------------
bool Vector3d::operator>(const Vector3d& rVecV) const
{
    return CompareData(rVecV) > 0;
}
//----------------------------------------------------------------------------
bool Vector3d::operator>=(const Vector3d& rVecV) const
{
    return CompareData(rVecV) >= 0;
}
//----------------------------------------------------------------------------
Vector3d Vector3d::operator+(const Vector3d& rRhsVec) const
{
    return Vector3d(
                   m_dData[0] + rRhsVec.m_dData[0],
                   m_dData[1] + rRhsVec.m_dData[1],
                   m_dData[2] + rRhsVec.m_dData[2]);
}
//----------------------------------------------------------------------------
Vector3d Vector3d::operator-(const Vector3d& rRhsVec) const
{
    return Vector3d(
                   m_dData[0] - rRhsVec.m_dData[0],
                   m_dData[1] - rRhsVec.m_dData[1],
                   m_dData[2] - rRhsVec.m_dData[2]);
}
//----------------------------------------------------------------------------
Vector3d Vector3d::operator*(double dScalar) const
{
    return Vector3d(
                   dScalar * m_dData[0],
                   dScalar * m_dData[1],
                   dScalar * m_dData[2]);
}
//----------------------------------------------------------------------------
Vector3d Vector3d::operator/(double dScalar) const
{
    Vector3d Res;

    if( dScalar != 0.0 )
    {
        double fInvScalar = 1.0/dScalar;
        Res.m_dData[0] = fInvScalar * m_dData[0];
        Res.m_dData[1] = fInvScalar * m_dData[1];
        Res.m_dData[2] = fInvScalar * m_dData[2];
    }
    else
    {
        Res.m_dData[0] = Math<double>::MAX_REAL;
        Res.m_dData[1] = Math<double>::MAX_REAL;
        Res.m_dData[2] = Math<double>::MAX_REAL;
    }

    return Res;
}
//----------------------------------------------------------------------------
Vector3d Vector3d::operator-() const
{
    return Vector3d(
                   -m_dData[0],
                   -m_dData[1],
                   -m_dData[2]);
}
//----------------------------------------------------------------------------
Vector3d& Vector3d::operator+=(const Vector3d& rRhsVec)
{
    m_dData[0] += rRhsVec.m_dData[0];
    m_dData[1] += rRhsVec.m_dData[1];
    m_dData[2] += rRhsVec.m_dData[2];

    return *this;
}
//----------------------------------------------------------------------------
Vector3d& Vector3d::operator+=(double dScalar)
{
    m_dData[0] += dScalar;
    m_dData[1] += dScalar;
    m_dData[2] += dScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector3d& Vector3d::operator-=(const Vector3d& rRhsVec)
{
    m_dData[0] -= rRhsVec.m_dData[0];
    m_dData[1] -= rRhsVec.m_dData[1];
    m_dData[2] -= rRhsVec.m_dData[2];

    return *this;
}
//----------------------------------------------------------------------------
Vector3d& Vector3d::operator-=(double dScalar)
{
    m_dData[0] -= dScalar;
    m_dData[1] -= dScalar;
    m_dData[2] -= dScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector3d& Vector3d::operator*=(double dScalar)
{
    m_dData[0] *= dScalar;
    m_dData[1] *= dScalar;
    m_dData[2] *= dScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector3d& Vector3d::operator/=(double dScalar)
{
    if( dScalar != 0.0 )
    {
        double dInvScalar = 1.0 / dScalar;
        m_dData[0] *= dInvScalar;
        m_dData[1] *= dInvScalar;
        m_dData[2] *= dInvScalar;
    }
    else
    {
        m_dData[0] = Math<double>::MAX_REAL;
        m_dData[1] = Math<double>::MAX_REAL;
        m_dData[2] = Math<double>::MAX_REAL;
    }

    return *this;
}
//----------------------------------------------------------------------------
void Vector3d::Orthonormalize(Vector3d& rVecU, Vector3d& rVecV, 
    Vector3d& rVecW)
{
    rVecU.Normalize();
    // V在U上的投影长度
    double dDot0 = rVecU.Dot(rVecV);
    // V = V减去V在U上的投影向量
    rVecV -= dDot0 * rVecU;
    rVecV.Normalize();
    // W在V上的投影长度
    double dDot1 = rVecV.Dot(rVecW);
	// W在U上的投影长度
    dDot0 = rVecU.Dot(rVecW);
	// W = W减去W在U上的投影向量再减去W在V上的投影向量
    rVecW -= dDot0*rVecU + dDot1*rVecV;
    rVecW.Normalize();
}
//----------------------------------------------------------------------------
void Vector3d::Orthonormalize(Vector3d* pVec)
{
	SE_ASSERT( pVec );

    Orthonormalize(pVec[0], pVec[1], pVec[2]);
}
//----------------------------------------------------------------------------
void Vector3d::GetOrthonormalBasis(Vector3d& rVecU, Vector3d& rVecV, 
    Vector3d& rVecW, bool bUnitLengthW)
{
    if( !bUnitLengthW )
        rVecW.Normalize();

    double dInvLength;

    if( Math<double>::FAbs(rVecW.m_dData[0]) >= 
        Math<double>::FAbs(rVecW.m_dData[1]) )
    {
        // W.X或W.Z是最大分量
        dInvLength = Math<double>::InvSqrt(rVecW.m_dData[0]*rVecW.m_dData[0] + 
            rVecW.m_dData[2]*rVecW.m_dData[2]);

        // 在左手坐标系中,
        // 对于向量(a,b,c),我们想获得与其垂直的顺时针一侧向量为(c,0,-a),
        // 与其垂直的逆时针一侧向量为(-c,0,a)
        rVecU.m_dData[0] = rVecW.m_dData[2] * dInvLength;
        rVecU.m_dData[1] = 0.0;
        rVecU.m_dData[2] = -rVecW.m_dData[0] * dInvLength;

        // 叉积生成V
        rVecV.m_dData[0] = rVecW.m_dData[1] * rVecU.m_dData[2];
        rVecV.m_dData[1] = rVecW.m_dData[2]*rVecU.m_dData[0] - 
            rVecW.m_dData[0]*rVecU.m_dData[2];
        rVecV.m_dData[2] = -rVecW.m_dData[1] * rVecU.m_dData[0];
    }
    else
    {
        // W.Y或W.Z是最大分量
        dInvLength = Math<double>::InvSqrt(rVecW.m_dData[1]*rVecW.m_dData[1] + 
            rVecW.m_dData[2]*rVecW.m_dData[2]);

        rVecU.m_dData[0] = 0.0;
        rVecU.m_dData[1] = +rVecW.m_dData[2] * dInvLength;
        rVecU.m_dData[2] = -rVecW.m_dData[1] * dInvLength;
        
        // 叉积生成V
		rVecV.m_dData[0] = rVecW.m_dData[1]*rVecU.m_dData[2] - 
            rVecW.m_dData[2]*rVecU.m_dData[1];
        rVecV.m_dData[1] = -rVecW.m_dData[0] * rVecU.m_dData[2];
        rVecV.m_dData[2] = rVecW.m_dData[0] * rVecU.m_dData[1];
    }
}
//----------------------------------------------------------------------------
void Vector3d::ComputeExtremes(int iCount, const Vector3d* pPoints, 
    Vector3d& rMin, Vector3d& rMax)
{
    SE_ASSERT( iCount > 0 && pPoints );

    rMin = pPoints[0];
    rMax = rMin;
    for( int i = 1; i < iCount; i++ )
    {
        const Vector3d& rPoint = pPoints[i];
        for( int j = 0; j < 3; j++ )
        {
            if( rPoint[j] < rMin[j] )
            {
                rMin[j] = rPoint[j];
            }
            else if( rPoint[j] > rMax[j] )
            {
                rMax[j] = rPoint[j];
            }
        }
    }
}
//----------------------------------------------------------------------------
Vector3d Swing::operator*(double dLhsScalar, const Vector3d& rRhsVec)
{
    return Vector3d(
                   dLhsScalar * rRhsVec[0],
                   dLhsScalar * rRhsVec[1],
                   dLhsScalar * rRhsVec[2]);
}
//----------------------------------------------------------------------------