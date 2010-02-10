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
#include "SEQuaternion.h"

using namespace Swing;

//----------------------------------------------------------------------------
// 单精度4元数类
//----------------------------------------------------------------------------

const Quaternionf Quaternionf::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f);
const Quaternionf Quaternionf::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
int Quaternionf::m_iNext[3] = { 1, 2, 0 };

//----------------------------------------------------------------------------
Quaternionf::Quaternionf()
{
}
//----------------------------------------------------------------------------
Quaternionf::Quaternionf(float fW, float fX, float fY, float fZ)
{
    m_fData[0] = fW;
    m_fData[1] = fX;
    m_fData[2] = fY;
    m_fData[3] = fZ;
}
//----------------------------------------------------------------------------
Quaternionf::Quaternionf(const Quaternionf& rQ)
{
    m_fData[0] = rQ.m_fData[0];
    m_fData[1] = rQ.m_fData[1];
    m_fData[2] = rQ.m_fData[2];
    m_fData[3] = rQ.m_fData[3];
}
//----------------------------------------------------------------------------
Quaternionf::Quaternionf(const Matrix3f& rRotMat)
{
    FromRotationMatrix(rRotMat);
}
//----------------------------------------------------------------------------
Quaternionf::Quaternionf(const Vector3f& rAxis, float fAngle)
{
    FromAxisAngle(rAxis, fAngle);
}
//----------------------------------------------------------------------------
Quaternionf::operator const float*() const
{
    return &m_fData[0];
}
//----------------------------------------------------------------------------
Quaternionf::operator float*()
{
    return &m_fData[0];
}
//----------------------------------------------------------------------------
float Quaternionf::operator[](int i) const
{
    SE_ASSERT( 0 <= i && i <= 3 );

    if( i < 0 )
    {
        i = 0;
    }
    else if( i > 3 )
    {
        i = 3;
    }

    return m_fData[i];
}
//----------------------------------------------------------------------------
float& Quaternionf::operator[](int i)
{
    SE_ASSERT( 0 <= i && i <= 3 );
    
    if( i < 0 )
    {
        i = 0;
    }
    else if( i > 3 )
    {
        i = 3;
    }

    return m_fData[i];
}
//----------------------------------------------------------------------------
Quaternionf& Quaternionf::operator=(const Quaternionf& rQ)
{
    m_fData[0] = rQ.m_fData[0];
    m_fData[1] = rQ.m_fData[1];
    m_fData[2] = rQ.m_fData[2];
    m_fData[3] = rQ.m_fData[3];

    return *this;
}
//----------------------------------------------------------------------------
bool Quaternionf::operator==(const Quaternionf& rQ) const
{
    return CompareData(rQ) == 0;
}
//----------------------------------------------------------------------------
bool Quaternionf::operator!=(const Quaternionf& rQ) const
{
    return CompareData(rQ) != 0;
}
//----------------------------------------------------------------------------
bool Quaternionf::operator<(const Quaternionf& rQ) const
{
    return CompareData(rQ) < 0;
}
//----------------------------------------------------------------------------
bool Quaternionf::operator<=(const Quaternionf& rQ) const
{
    return CompareData(rQ) <= 0;
}
//----------------------------------------------------------------------------
bool Quaternionf::operator>(const Quaternionf& rQ) const
{
    return CompareData(rQ) > 0;
}
//----------------------------------------------------------------------------
bool Quaternionf::operator>=(const Quaternionf& rQ) const
{
    return CompareData(rQ) >= 0;
}
//----------------------------------------------------------------------------
Quaternionf Quaternionf::operator+(const Quaternionf& rRhsQ) const
{
    Quaternionf tempQ;

    tempQ.m_fData[0] = m_fData[0] + rRhsQ.m_fData[0];
    tempQ.m_fData[1] = m_fData[1] + rRhsQ.m_fData[1];
    tempQ.m_fData[2] = m_fData[2] + rRhsQ.m_fData[2];
    tempQ.m_fData[3] = m_fData[3] + rRhsQ.m_fData[3];

    return tempQ;
}
//----------------------------------------------------------------------------
Quaternionf Quaternionf::operator-(const Quaternionf& rRhsQ) const
{
    Quaternionf tempQ;

    tempQ.m_fData[0] = m_fData[0] - rRhsQ.m_fData[0];
    tempQ.m_fData[1] = m_fData[1] - rRhsQ.m_fData[1];
    tempQ.m_fData[2] = m_fData[2] - rRhsQ.m_fData[2];
    tempQ.m_fData[3] = m_fData[3] - rRhsQ.m_fData[3];

    return tempQ;
}
//----------------------------------------------------------------------------
Quaternionf Quaternionf::operator*(const Quaternionf& rRhsQ) const
{
    // 注意:quaternion乘法不满足交换律

    Quaternionf tempQ;

    tempQ.m_fData[0] =
        m_fData[0]*rRhsQ.m_fData[0] -
        m_fData[1]*rRhsQ.m_fData[1] -
        m_fData[2]*rRhsQ.m_fData[2] -
        m_fData[3]*rRhsQ.m_fData[3];

    tempQ.m_fData[1] =
        m_fData[0]*rRhsQ.m_fData[1] +
        m_fData[1]*rRhsQ.m_fData[0] +
        m_fData[2]*rRhsQ.m_fData[3] -
        m_fData[3]*rRhsQ.m_fData[2];

    tempQ.m_fData[2] =
        m_fData[0]*rRhsQ.m_fData[2] +
        m_fData[2]*rRhsQ.m_fData[0] +
        m_fData[3]*rRhsQ.m_fData[1] -
        m_fData[1]*rRhsQ.m_fData[3];

    tempQ.m_fData[3] =
        m_fData[0]*rRhsQ.m_fData[3] +
        m_fData[3]*rRhsQ.m_fData[0] +
        m_fData[1]*rRhsQ.m_fData[2] -
        m_fData[2]*rRhsQ.m_fData[1];

    return tempQ;
}
//----------------------------------------------------------------------------
Quaternionf Quaternionf::operator*(float fScalar) const
{
    Quaternionf tempQ;

    tempQ.m_fData[0] = fScalar * m_fData[0];
    tempQ.m_fData[1] = fScalar * m_fData[1];
    tempQ.m_fData[2] = fScalar * m_fData[2];
    tempQ.m_fData[3] = fScalar * m_fData[3];

    return tempQ;
}
//----------------------------------------------------------------------------
Quaternionf Quaternionf::operator/(float fScalar) const
{
    Quaternionf tempQ;

    if( fScalar != 0.0f )
    {
        float fInvScalar = 1.0f / fScalar;
        tempQ.m_fData[0] = fInvScalar * m_fData[0];
        tempQ.m_fData[1] = fInvScalar * m_fData[1];
        tempQ.m_fData[2] = fInvScalar * m_fData[2];
        tempQ.m_fData[3] = fInvScalar * m_fData[3];
    }
    else
    {
        tempQ.m_fData[0] = Math<float>::MAX_REAL;
        tempQ.m_fData[1] = Math<float>::MAX_REAL;
        tempQ.m_fData[2] = Math<float>::MAX_REAL;
        tempQ.m_fData[3] = Math<float>::MAX_REAL;
    }

    return tempQ;
}
//----------------------------------------------------------------------------
Quaternionf Quaternionf::operator-() const
{
    Quaternionf tempQ;

    tempQ.m_fData[0] = -m_fData[0];
    tempQ.m_fData[1] = -m_fData[1];
    tempQ.m_fData[2] = -m_fData[2];
    tempQ.m_fData[3] = -m_fData[3];

    return tempQ;
}
//----------------------------------------------------------------------------
Quaternionf& Quaternionf::operator+=(const Quaternionf& rRhsQ)
{
    m_fData[0] += rRhsQ.m_fData[0];
    m_fData[1] += rRhsQ.m_fData[1];
    m_fData[2] += rRhsQ.m_fData[2];
    m_fData[3] += rRhsQ.m_fData[3];

    return *this;
}
//----------------------------------------------------------------------------
Quaternionf& Quaternionf::operator-=(const Quaternionf& rRhsQ)
{
    m_fData[0] -= rRhsQ.m_fData[0];
    m_fData[1] -= rRhsQ.m_fData[1];
    m_fData[2] -= rRhsQ.m_fData[2];
    m_fData[3] -= rRhsQ.m_fData[3];

    return *this;
}
//----------------------------------------------------------------------------
Quaternionf& Quaternionf::operator*=(float fScalar)
{
    m_fData[0] *= fScalar;
    m_fData[1] *= fScalar;
    m_fData[2] *= fScalar;
    m_fData[3] *= fScalar;

    return *this;
}
//----------------------------------------------------------------------------
Quaternionf& Quaternionf::operator/=(float fScalar)
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
Vector3f Quaternionf::Rotate(const Vector3f& rSrcVec) const
{
    Matrix3f tempRot;
    ToRotationMatrix(tempRot);

    return rSrcVec * tempRot;
}
//----------------------------------------------------------------------------
Quaternionf& Quaternionf::Slerp(float fT, const Quaternionf& rP,
    const Quaternionf& rQ)
{
    float fCos = rP.Dot(rQ);
    float fAngle = Math<float>::ACos(fCos);

    if( Math<float>::FAbs(fAngle) >= Math<float>::ZERO_TOLERANCE )
    {
        float fSin = Math<float>::Sin(fAngle);
        float fInvSin = 1.0f / fSin;
        float fCoeff0 = Math<float>::Sin((1.0f - fT) * fAngle) * fInvSin;
        float fCoeff1 = Math<float>::Sin(fT * fAngle) * fInvSin;
        *this = fCoeff0*rP + fCoeff1*rQ;
    }
    else
    {
        *this = rP;
    }

    return *this;
}
//----------------------------------------------------------------------------
Quaternionf& Quaternionf::Lerp(float fT, const Quaternionf& rP, 
    const Quaternionf& rQ)
{
    *this = (1.0f - fT)*rP + fT*rQ;
    Normalize();

    return *this;
}
//----------------------------------------------------------------------------
Quaternionf& Quaternionf::FromRotationMatrix(const Vector3f aRot[3], 
    bool bIsRow)
{
    Matrix3f tempRot;
    if( bIsRow )
    {
        for( int iRow = 0; iRow < 3; iRow++ )
        {
            tempRot(iRow, 0) = aRot[iRow][0];
            tempRot(iRow, 1) = aRot[iRow][1];
            tempRot(iRow, 2) = aRot[iRow][2];
        }
    }
    else
    {
        for( int iCol = 0; iCol < 3; iCol++ )
        {
            tempRot(0, iCol) = aRot[iCol][0];
            tempRot(1, iCol) = aRot[iCol][1];
            tempRot(2, iCol) = aRot[iCol][2];
        }
    }

    return FromRotationMatrix(tempRot);
}
//----------------------------------------------------------------------------
void Quaternionf::ToRotationMatrix(Vector3f aRot[3], bool bIsRow) const
{
    Matrix3f tempRot;
    ToRotationMatrix(tempRot);
    if( bIsRow )
    {
        for( int iRow = 0; iRow < 3; iRow++ )
        {
            aRot[iRow][0] = tempRot(iRow, 0);
            aRot[iRow][1] = tempRot(iRow, 1);
            aRot[iRow][2] = tempRot(iRow, 2);
        }
    }
    else
    {
        for( int iCol = 0; iCol < 3; iCol++ )
        {
            aRot[iCol][0] = tempRot(0, iCol);
            aRot[iCol][1] = tempRot(1, iCol);
            aRot[iCol][2] = tempRot(2, iCol);
        }
    }
}
//----------------------------------------------------------------------------
Quaternionf Swing::operator*(float fLhsScalar, const Quaternionf& rRhsQ)
{
    Quaternionf tempQ;

    tempQ[0] = fLhsScalar * rRhsQ[0];
    tempQ[1] = fLhsScalar * rRhsQ[1];
    tempQ[2] = fLhsScalar * rRhsQ[2];
    tempQ[3] = fLhsScalar * rRhsQ[3];

    return tempQ;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 双精度4元数类
//----------------------------------------------------------------------------

const Quaterniond Quaterniond::IDENTITY(1.0, 0.0, 0.0, 0.0);
const Quaterniond Quaterniond::ZERO(0.0, 0.0, 0.0, 0.0);
int Quaterniond::m_iNext[3] = { 1, 2, 0 };

//----------------------------------------------------------------------------
Quaterniond::Quaterniond()
{
}
//----------------------------------------------------------------------------
Quaterniond::Quaterniond(double dW, double dX, double dY, double dZ)
{
    m_dData[0] = dW;
    m_dData[1] = dX;
    m_dData[2] = dY;
    m_dData[3] = dZ;
}
//----------------------------------------------------------------------------
Quaterniond::Quaterniond(const Quaterniond& rQ)
{
    m_dData[0] = rQ.m_dData[0];
    m_dData[1] = rQ.m_dData[1];
    m_dData[2] = rQ.m_dData[2];
    m_dData[3] = rQ.m_dData[3];
}
//----------------------------------------------------------------------------
Quaterniond::Quaterniond(const Matrix3d& rRotMat)
{
    FromRotationMatrix(rRotMat);
}
//----------------------------------------------------------------------------
Quaterniond::Quaterniond(const Vector3d& rAxis, double dAngle)
{
    FromAxisAngle(rAxis, dAngle);
}
//----------------------------------------------------------------------------
Quaterniond::operator const double*() const
{
    return &m_dData[0];
}
//----------------------------------------------------------------------------
Quaterniond::operator double*()
{
    return &m_dData[0];
}
//----------------------------------------------------------------------------
double Quaterniond::operator[](int i) const
{
    SE_ASSERT( 0 <= i && i <= 3 );

    if( i < 0 )
    {
        i = 0;
    }
    else if( i > 3 )
    {
        i = 3;
    }

    return m_dData[i];
}
//----------------------------------------------------------------------------
double& Quaterniond::operator[](int i)
{
    SE_ASSERT( 0 <= i && i <= 3 );
    
    if( i < 0 )
    {
        i = 0;
    }
    else if( i > 3 )
    {
        i = 3;
    }

    return m_dData[i];
}
//----------------------------------------------------------------------------
Quaterniond& Quaterniond::operator=(const Quaterniond& rQ)
{
    m_dData[0] = rQ.m_dData[0];
    m_dData[1] = rQ.m_dData[1];
    m_dData[2] = rQ.m_dData[2];
    m_dData[3] = rQ.m_dData[3];

    return *this;
}
//----------------------------------------------------------------------------
bool Quaterniond::operator==(const Quaterniond& rQ) const
{
    return CompareData(rQ) == 0;
}
//----------------------------------------------------------------------------
bool Quaterniond::operator!=(const Quaterniond& rQ) const
{
    return CompareData(rQ) != 0;
}
//----------------------------------------------------------------------------
bool Quaterniond::operator<(const Quaterniond& rQ) const
{
    return CompareData(rQ) < 0;
}
//----------------------------------------------------------------------------
bool Quaterniond::operator<=(const Quaterniond& rQ) const
{
    return CompareData(rQ) <= 0;
}
//----------------------------------------------------------------------------
bool Quaterniond::operator>(const Quaterniond& rQ) const
{
    return CompareData(rQ) > 0;
}
//----------------------------------------------------------------------------
bool Quaterniond::operator>=(const Quaterniond& rQ) const
{
    return CompareData(rQ) >= 0;
}
//----------------------------------------------------------------------------
Quaterniond Quaterniond::operator+(const Quaterniond& rRhsQ) const
{
    Quaterniond tempQ;

    tempQ.m_dData[0] = m_dData[0] + rRhsQ.m_dData[0];
    tempQ.m_dData[1] = m_dData[1] + rRhsQ.m_dData[1];
    tempQ.m_dData[2] = m_dData[2] + rRhsQ.m_dData[2];
    tempQ.m_dData[3] = m_dData[3] + rRhsQ.m_dData[3];

    return tempQ;
}
//----------------------------------------------------------------------------
Quaterniond Quaterniond::operator-(const Quaterniond& rRhsQ) const
{
    Quaterniond tempQ;

    tempQ.m_dData[0] = m_dData[0] - rRhsQ.m_dData[0];
    tempQ.m_dData[1] = m_dData[1] - rRhsQ.m_dData[1];
    tempQ.m_dData[2] = m_dData[2] - rRhsQ.m_dData[2];
    tempQ.m_dData[3] = m_dData[3] - rRhsQ.m_dData[3];

    return tempQ;
}
//----------------------------------------------------------------------------
Quaterniond Quaterniond::operator*(const Quaterniond& rRhsQ) const
{
    // 注意:quaternion乘法不满足交换律

    Quaterniond tempQ;

    tempQ.m_dData[0] =
        m_dData[0]*rRhsQ.m_dData[0] -
        m_dData[1]*rRhsQ.m_dData[1] -
        m_dData[2]*rRhsQ.m_dData[2] -
        m_dData[3]*rRhsQ.m_dData[3];

    tempQ.m_dData[1] =
        m_dData[0]*rRhsQ.m_dData[1] +
        m_dData[1]*rRhsQ.m_dData[0] +
        m_dData[2]*rRhsQ.m_dData[3] -
        m_dData[3]*rRhsQ.m_dData[2];

    tempQ.m_dData[2] =
        m_dData[0]*rRhsQ.m_dData[2] +
        m_dData[2]*rRhsQ.m_dData[0] +
        m_dData[3]*rRhsQ.m_dData[1] -
        m_dData[1]*rRhsQ.m_dData[3];

    tempQ.m_dData[3] =
        m_dData[0]*rRhsQ.m_dData[3] +
        m_dData[3]*rRhsQ.m_dData[0] +
        m_dData[1]*rRhsQ.m_dData[2] -
        m_dData[2]*rRhsQ.m_dData[1];

    return tempQ;
}
//----------------------------------------------------------------------------
Quaterniond Quaterniond::operator*(double dScalar) const
{
    Quaterniond tempQ;

    tempQ.m_dData[0] = dScalar * m_dData[0];
    tempQ.m_dData[1] = dScalar * m_dData[1];
    tempQ.m_dData[2] = dScalar * m_dData[2];
    tempQ.m_dData[3] = dScalar * m_dData[3];

    return tempQ;
}
//----------------------------------------------------------------------------
Quaterniond Quaterniond::operator/(double dScalar) const
{
    Quaterniond tempQ;

    if( dScalar != 0.0 )
    {
        double dInvScalar = 1.0 / dScalar;
        tempQ.m_dData[0] = dInvScalar * m_dData[0];
        tempQ.m_dData[1] = dInvScalar * m_dData[1];
        tempQ.m_dData[2] = dInvScalar * m_dData[2];
        tempQ.m_dData[3] = dInvScalar * m_dData[3];
    }
    else
    {
        tempQ.m_dData[0] = Math<double>::MAX_REAL;
        tempQ.m_dData[1] = Math<double>::MAX_REAL;
        tempQ.m_dData[2] = Math<double>::MAX_REAL;
        tempQ.m_dData[3] = Math<double>::MAX_REAL;
    }

    return tempQ;
}
//----------------------------------------------------------------------------
Quaterniond Quaterniond::operator-() const
{
    Quaterniond tempQ;

    tempQ.m_dData[0] = -m_dData[0];
    tempQ.m_dData[1] = -m_dData[1];
    tempQ.m_dData[2] = -m_dData[2];
    tempQ.m_dData[3] = -m_dData[3];

    return tempQ;
}
//----------------------------------------------------------------------------
Quaterniond& Quaterniond::operator+=(const Quaterniond& rRhsQ)
{
    m_dData[0] += rRhsQ.m_dData[0];
    m_dData[1] += rRhsQ.m_dData[1];
    m_dData[2] += rRhsQ.m_dData[2];
    m_dData[3] += rRhsQ.m_dData[3];

    return *this;
}
//----------------------------------------------------------------------------
Quaterniond& Quaterniond::operator-=(const Quaterniond& rRhsQ)
{
    m_dData[0] -= rRhsQ.m_dData[0];
    m_dData[1] -= rRhsQ.m_dData[1];
    m_dData[2] -= rRhsQ.m_dData[2];
    m_dData[3] -= rRhsQ.m_dData[3];

    return *this;
}
//----------------------------------------------------------------------------
Quaterniond& Quaterniond::operator*=(double dScalar)
{
    m_dData[0] *= dScalar;
    m_dData[1] *= dScalar;
    m_dData[2] *= dScalar;
    m_dData[3] *= dScalar;

    return *this;
}
//----------------------------------------------------------------------------
Quaterniond& Quaterniond::operator/=(double dScalar)
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
        m_dData[0] = Math<float>::MAX_REAL;
        m_dData[1] = Math<float>::MAX_REAL;
        m_dData[2] = Math<float>::MAX_REAL;
        m_dData[3] = Math<float>::MAX_REAL;
    }

    return *this;
}
//----------------------------------------------------------------------------
Vector3d Quaterniond::Rotate(const Vector3d& rSrcVec) const
{
    Matrix3d tempRot;
    ToRotationMatrix(tempRot);

    return rSrcVec * tempRot;
}
//----------------------------------------------------------------------------
Quaterniond& Quaterniond::Slerp(double dT, const Quaterniond& rP,
    const Quaterniond& rQ)
{
    double dCos = rP.Dot(rQ);
    double dAngle = Math<double>::ACos(dCos);

    if( Math<double>::FAbs(dAngle) >= Math<double>::ZERO_TOLERANCE )
    {
        double dSin = Math<double>::Sin(dAngle);
        double dInvSin = 1.0 / dSin;
        double dCoeff0 = Math<double>::Sin((1.0 - dT) * dAngle) * dInvSin;
        double dCoeff1 = Math<double>::Sin(dT * dAngle) * dInvSin;
        *this = dCoeff0*rP + dCoeff1*rQ;
    }
    else
    {
        *this = rP;
    }

    return *this;
}
//----------------------------------------------------------------------------
Quaterniond& Quaterniond::Lerp(double dT, const Quaterniond& rP, 
    const Quaterniond& rQ)
{
    *this = (1.0 - dT)*rP + dT*rQ;
    Normalize();

    return *this;
}
//----------------------------------------------------------------------------
Quaterniond& Quaterniond::FromRotationMatrix(const Vector3d aRot[3], 
    bool bIsRow)
{
    Matrix3d tempRot;
    if( bIsRow )
    {
        for( int iRow = 0; iRow < 3; iRow++ )
        {
            tempRot(iRow, 0) = aRot[iRow][0];
            tempRot(iRow, 1) = aRot[iRow][1];
            tempRot(iRow, 2) = aRot[iRow][2];
        }
    }
    else
    {
        for( int iCol = 0; iCol < 3; iCol++ )
        {
            tempRot(0, iCol) = aRot[iCol][0];
            tempRot(1, iCol) = aRot[iCol][1];
            tempRot(2, iCol) = aRot[iCol][2];
        }
    }

    return FromRotationMatrix(tempRot);
}
//----------------------------------------------------------------------------
void Quaterniond::ToRotationMatrix(Vector3d aRot[3], bool bIsRow) const
{
    Matrix3d tempRot;
    ToRotationMatrix(tempRot);
    if( bIsRow )
    {
        for( int iRow = 0; iRow < 3; iRow++ )
        {
            aRot[iRow][0] = tempRot(iRow, 0);
            aRot[iRow][1] = tempRot(iRow, 1);
            aRot[iRow][2] = tempRot(iRow, 2);
        }
    }
    else
    {
        for( int iCol = 0; iCol < 3; iCol++ )
        {
            aRot[iCol][0] = tempRot(0, iCol);
            aRot[iCol][1] = tempRot(1, iCol);
            aRot[iCol][2] = tempRot(2, iCol);
        }
    }
}
//----------------------------------------------------------------------------
Quaterniond Swing::operator*(double dLhsScalar, const Quaterniond& rRhsQ)
{
    Quaterniond tempQ;

    tempQ[0] = dLhsScalar * rRhsQ[0];
    tempQ[1] = dLhsScalar * rRhsQ[1];
    tempQ[2] = dLhsScalar * rRhsQ[2];
    tempQ[3] = dLhsScalar * rRhsQ[3];

    return tempQ;
}
//----------------------------------------------------------------------------