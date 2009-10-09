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
#include "SEMatrix4.h"

using namespace Swing;

//----------------------------------------------------------------------------
// ������4�׷�����
//----------------------------------------------------------------------------

const Matrix4f Matrix4f::ZERO(0.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 0.0f);
const Matrix4f Matrix4f::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 1.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 1.0f, 0.0f,
                                  0.0f, 0.0f, 0.0f, 1.0f);

//----------------------------------------------------------------------------
Matrix4f::Matrix4f()
{
    Zero();
}
//----------------------------------------------------------------------------
Matrix4f::Matrix4f(const Matrix4f& rMat)
{
    memcpy(m_fData, rMat.m_fData, 16*sizeof(float));
}
//----------------------------------------------------------------------------
Matrix4f::Matrix4f(float fM11, float fM12, float fM13, float fM14,
                   float fM21, float fM22, float fM23, float fM24,
                   float fM31, float fM32, float fM33, float fM34,
                   float fM41, float fM42, float fM43, float fM44)
{
    M11 = fM11;
    M12 = fM12;
    M13 = fM13;
    M14 = fM14;

    M21 = fM21;
    M22 = fM22;
    M23 = fM23;
    M24 = fM24;

    M31 = fM31;
    M32 = fM32;
    M33 = fM33;
    M34 = fM34;

    M41 = fM41;
    M42 = fM42;
    M43 = fM43;
    M44 = fM44;
}
//----------------------------------------------------------------------------
Matrix4f::operator const float*() const
{
    return &m_fData[0][0];
}
//----------------------------------------------------------------------------
Matrix4f::operator float*()
{
    return &m_fData[0][0];
}
//----------------------------------------------------------------------------
const float* Matrix4f::operator[](int iCurRow) const
{
    return &m_fData[iCurRow][0];
}
//----------------------------------------------------------------------------
float* Matrix4f::operator[](int iCurRow)
{
     return &m_fData[iCurRow][0];
}
//----------------------------------------------------------------------------
float Matrix4f::operator()(int iCurRow, int iCurCol) const
{
    return m_fData[iCurRow][iCurCol];
}
//----------------------------------------------------------------------------
float& Matrix4f::operator()(int iCurRow, int iCurCol)
{
    return m_fData[iCurRow][iCurCol];
}
//----------------------------------------------------------------------------
Matrix4f& Matrix4f::operator=(const Matrix4f& rMat)
{
    memcpy(m_fData, rMat.m_fData, 16 * sizeof(float));
    return *this;
}
//----------------------------------------------------------------------------
bool Matrix4f::operator==(const Matrix4f& rMat) const
{
    return CompareData(rMat) == 0;
}
//----------------------------------------------------------------------------
bool Matrix4f::operator!= (const Matrix4f& rMat) const
{
    return CompareData(rMat) != 0;
}
//----------------------------------------------------------------------------
bool Matrix4f::operator<(const Matrix4f& rMat) const
{
    return CompareData(rMat) < 0;
}
//----------------------------------------------------------------------------
bool Matrix4f::operator<=(const Matrix4f& rMat) const
{
    return CompareData(rMat) <= 0;
}
//----------------------------------------------------------------------------
bool Matrix4f::operator>(const Matrix4f& rMat) const
{
    return CompareData(rMat) > 0;
}
//----------------------------------------------------------------------------
bool Matrix4f::operator>=(const Matrix4f& rMat) const
{
    return CompareData(rMat) >= 0;
}
//----------------------------------------------------------------------------
Matrix4f Matrix4f::operator+(const Matrix4f& rRhsMat) const
{
    Matrix4f ResMat;

    ResMat.M11 = M11 + rRhsMat.M11;
    ResMat.M12 = M12 + rRhsMat.M12;
    ResMat.M13 = M13 + rRhsMat.M13;
    ResMat.M14 = M14 + rRhsMat.M14;

    ResMat.M21 = M21 + rRhsMat.M21;
    ResMat.M22 = M22 + rRhsMat.M22;
    ResMat.M23 = M23 + rRhsMat.M23;
    ResMat.M24 = M24 + rRhsMat.M24;

    ResMat.M31 = M31 + rRhsMat.M31;
    ResMat.M32 = M32 + rRhsMat.M32;
    ResMat.M33 = M33 + rRhsMat.M33;
    ResMat.M34 = M34 + rRhsMat.M34;

    ResMat.M41 = M41 + rRhsMat.M41;
    ResMat.M42 = M42 + rRhsMat.M42;
    ResMat.M43 = M43 + rRhsMat.M43;
    ResMat.M44 = M44 + rRhsMat.M44;

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix4f Matrix4f::operator-(const Matrix4f& rRhsMat) const
{
    Matrix4f ResMat;

    ResMat.M11 = M11 - rRhsMat.M11;
    ResMat.M12 = M12 - rRhsMat.M12;
    ResMat.M13 = M13 - rRhsMat.M13;
    ResMat.M14 = M14 - rRhsMat.M14;

    ResMat.M21 = M21 - rRhsMat.M21;
    ResMat.M22 = M22 - rRhsMat.M22;
    ResMat.M23 = M23 - rRhsMat.M23;
    ResMat.M24 = M24 - rRhsMat.M24;

    ResMat.M31 = M31 - rRhsMat.M31;
    ResMat.M32 = M32 - rRhsMat.M32;
    ResMat.M33 = M33 - rRhsMat.M33;
    ResMat.M34 = M34 - rRhsMat.M34;

    ResMat.M41 = M41 - rRhsMat.M41;
    ResMat.M42 = M42 - rRhsMat.M42;
    ResMat.M43 = M43 - rRhsMat.M43;
    ResMat.M44 = M44 - rRhsMat.M44;

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix4f Matrix4f::operator*(const Matrix4f& rRhsMat) const
{
    SE_ALIGN16 Matrix4f ResMat;

#ifdef _SIMD
    __asm
    {
        mov edi,rRhsMat    // ���Ҳ�����������׵�ַָ�뱣�浽edi
        mov esi,this       // ���������������׵�ַָ�뱣�浽esi
        mov	eax,0          // eax����ѭ���ۼ�ָ��ƫ�Ʊ���

        LOOP_1:
        // ���������������ĵ�i�е�xmm0,xmm1,xmm2,xmm3
        movups xmm0,[esi+eax]
        movups xmm1,xmm0
        movups xmm2,xmm0
        movups xmm3,xmm0

        // xmm0��Ϊ4���ظ���������������i�е�1��Ԫ��,aaaa
        shufps xmm0,xmm2,0x00
        // xmm1��Ϊ4���ظ���������������i�е�2��Ԫ��,bbbb
        shufps xmm1,xmm2,0x55
        // xmm2��Ϊ4���ظ���������������i�е�3��Ԫ��,cccc
        shufps xmm2,xmm2,0xAA
        // xmm3��Ϊ4���ظ���������������i�е�4��Ԫ��,dddd
        shufps xmm3,xmm3,0xFF

        mulps xmm0,[edi]
        mulps xmm1,[edi+16]
        mulps xmm2,[edi+32]
        mulps xmm3,[edi+48]

        addps xmm0,xmm1
        addps xmm0,xmm2
        addps xmm0,xmm3

        movups ResMat[eax],xmm0

        add eax, 16
        cmp	eax, 48
        jle LOOP_1
    }
#else
    ResMat.M11 = M11*rRhsMat.M11 + M12*rRhsMat.M21 + M13*rRhsMat.M31 + 
        M14*rRhsMat.M41;
    ResMat.M12 = M11*rRhsMat.M12 + M12*rRhsMat.M22 + M13*rRhsMat.M32 + 
        M14*rRhsMat.M42;
    ResMat.M13 = M11*rRhsMat.M13 + M12*rRhsMat.M23 + M13*rRhsMat.M33 + 
        M14*rRhsMat.M43;
    ResMat.M14 = M11*rRhsMat.M14 + M12*rRhsMat.M24 + M13*rRhsMat.M34 + 
        M14*rRhsMat.M44;

    ResMat.M21 = M21*rRhsMat.M11 + M22*rRhsMat.M21 + M23*rRhsMat.M31 + 
        M24*rRhsMat.M41;
    ResMat.M22 = M21*rRhsMat.M12 + M22*rRhsMat.M22 + M23*rRhsMat.M32 + 
        M24*rRhsMat.M42;
    ResMat.M23 = M21*rRhsMat.M13 + M22*rRhsMat.M23 + M23*rRhsMat.M33 + 
        M24*rRhsMat.M43;
    ResMat.M24 = M21*rRhsMat.M14 + M22*rRhsMat.M24 + M23*rRhsMat.M34 + 
        M24*rRhsMat.M44;

    ResMat.M31 = M31*rRhsMat.M11 + M32*rRhsMat.M21 + M33*rRhsMat.M31 + 
        M34*rRhsMat.M41;
    ResMat.M32 = M31*rRhsMat.M12 + M32*rRhsMat.M22 + M33*rRhsMat.M32 + 
        M34*rRhsMat.M42;
    ResMat.M33 = M31*rRhsMat.M13 + M32*rRhsMat.M23 + M33*rRhsMat.M33 + 
        M34*rRhsMat.M43;
    ResMat.M34 = M31*rRhsMat.M14 + M32*rRhsMat.M24 + M33*rRhsMat.M34 + 
        M34*rRhsMat.M44;

    ResMat.M41 = M41*rRhsMat.M11 + M42*rRhsMat.M21 + M43*rRhsMat.M31 + 
        M44*rRhsMat.M41;
    ResMat.M42 = M41*rRhsMat.M12 + M42*rRhsMat.M22 + M43*rRhsMat.M32 + 
        M44*rRhsMat.M42;
    ResMat.M43 = M41*rRhsMat.M13 + M42*rRhsMat.M23 + M43*rRhsMat.M33 + 
        M44*rRhsMat.M43;
    ResMat.M44 = M41*rRhsMat.M14 + M42*rRhsMat.M24 + M43*rRhsMat.M34 + 
        M44*rRhsMat.M44;
#endif

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix4f Matrix4f::operator*(float fScalar) const
{
    Matrix4f ResMat;

    ResMat.M11 = M11 * fScalar;
    ResMat.M12 = M12 * fScalar;
    ResMat.M13 = M13 * fScalar;
    ResMat.M14 = M14 * fScalar;

    ResMat.M21 = M21 * fScalar;
    ResMat.M22 = M22 * fScalar;
    ResMat.M23 = M23 * fScalar;
    ResMat.M24 = M24 * fScalar;

    ResMat.M31 = M31 * fScalar;
    ResMat.M32 = M32 * fScalar;
    ResMat.M33 = M33 * fScalar;
    ResMat.M34 = M34 * fScalar;

    ResMat.M41 = M41 * fScalar;
    ResMat.M42 = M42 * fScalar;
    ResMat.M43 = M43 * fScalar;
    ResMat.M44 = M44 * fScalar;

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix4f Matrix4f::operator/(float fScalar) const
{
    // ע���������Ϊ0
    Matrix4f ResMat;
    float fInvScalar = 1.0f / fScalar;

    ResMat.M11 = M11 * fInvScalar;
    ResMat.M12 = M12 * fInvScalar;
    ResMat.M13 = M13 * fInvScalar;
    ResMat.M14 = M14 * fInvScalar;

    ResMat.M21 = M21 * fInvScalar;
    ResMat.M22 = M22 * fInvScalar;
    ResMat.M23 = M23 * fInvScalar;
    ResMat.M24 = M24 * fInvScalar;

    ResMat.M31 = M31 * fInvScalar;
    ResMat.M32 = M32 * fInvScalar;
    ResMat.M33 = M33 * fInvScalar;
    ResMat.M34 = M34 * fInvScalar;

    ResMat.M41 = M41 * fInvScalar;
    ResMat.M42 = M42 * fInvScalar;
    ResMat.M43 = M43 * fInvScalar;
    ResMat.M44 = M44 * fInvScalar;

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix4f Matrix4f::operator-() const
{
    Matrix4f ResMat;

    ResMat.M11 = -M11;
    ResMat.M12 = -M12;
    ResMat.M13 = -M13;
    ResMat.M14 = -M14;

    ResMat.M21 = -M21;
    ResMat.M22 = -M22;
    ResMat.M23 = -M23;
    ResMat.M24 = -M24;

    ResMat.M31 = -M31;
    ResMat.M32 = -M32;
    ResMat.M33 = -M33;
    ResMat.M34 = -M34;

    ResMat.M41 = -M41;
    ResMat.M42 = -M42;
    ResMat.M43 = -M43;
    ResMat.M44 = -M44;

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix4f& Matrix4f::operator+=(const Matrix4f& rRhsMat)
{
	M11 += rRhsMat.M11;
    M12 += rRhsMat.M12;
    M13 += rRhsMat.M13;
    M14 += rRhsMat.M14;

    M21 += rRhsMat.M21;
    M22 += rRhsMat.M22;
    M23 += rRhsMat.M23;
    M24 += rRhsMat.M24;

    M31 += rRhsMat.M31;
    M32 += rRhsMat.M32;
    M33 += rRhsMat.M33;
    M34 += rRhsMat.M34;

    M41 += rRhsMat.M41;
    M42 += rRhsMat.M42;
    M43 += rRhsMat.M43;
    M44 += rRhsMat.M44;

    return *this;
}
//----------------------------------------------------------------------------
Matrix4f& Matrix4f::operator-=(const Matrix4f& rRhsMat)
{
	M11 -= rRhsMat.M11;
    M12 -= rRhsMat.M12;
    M13 -= rRhsMat.M13;
    M14 -= rRhsMat.M14;

    M21 -= rRhsMat.M21;
    M22 -= rRhsMat.M22;
    M23 -= rRhsMat.M23;
    M24 -= rRhsMat.M24;

    M31 -= rRhsMat.M31;
    M32 -= rRhsMat.M32;
    M33 -= rRhsMat.M33;
    M34 -= rRhsMat.M34;

    M41 -= rRhsMat.M41;
    M42 -= rRhsMat.M42;
    M43 -= rRhsMat.M43;
    M44 -= rRhsMat.M44;

    return *this;
}
//----------------------------------------------------------------------------
Matrix4f& Matrix4f::operator*=(float fScalar)
{
	M11 *= fScalar;
    M12 *= fScalar;
    M13 *= fScalar;
    M14 *= fScalar;

    M21 *= fScalar;
    M22 *= fScalar;
    M23 *= fScalar;
    M24 *= fScalar;

    M31 *= fScalar;
    M32 *= fScalar;
    M33 *= fScalar;
    M34 *= fScalar;

    M41 *= fScalar;
    M42 *= fScalar;
    M43 *= fScalar;
    M44 *= fScalar;

    return *this;
}
//----------------------------------------------------------------------------
Matrix4f& Matrix4f::operator/=(float fScalar)
{
    // ע���������Ϊ0
    float fInvScalar = 1.0f / fScalar;
	M11 *= fInvScalar;
    M12 *= fInvScalar;
    M13 *= fInvScalar;
    M14 *= fInvScalar;

    M21 *= fInvScalar;
    M22 *= fInvScalar;
    M23 *= fInvScalar;
    M24 *= fInvScalar;

    M31 *= fInvScalar;
    M32 *= fInvScalar;
    M33 *= fInvScalar;
    M34 *= fInvScalar;

    M41 *= fInvScalar;
    M42 *= fInvScalar;
    M43 *= fInvScalar;
    M44 *= fInvScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector4f Matrix4f::operator*(const Vector4f& rRhsVec) const
{
    Vector4f ResVec;
    
    ResVec[0] = M11*rRhsVec[0] + M12*rRhsVec[1] + M13*rRhsVec[2] + 
        M14*rRhsVec[3];
    ResVec[1] = M21*rRhsVec[0] + M22*rRhsVec[1] + M23*rRhsVec[2] + 
        M24*rRhsVec[3];
    ResVec[2] = M31*rRhsVec[0] + M32*rRhsVec[1] + M33*rRhsVec[2] + 
        M34*rRhsVec[3];
    ResVec[3] = M41*rRhsVec[0] + M42*rRhsVec[1] + M43*rRhsVec[2] + 
        M44*rRhsVec[3];

    return ResVec;
}
//----------------------------------------------------------------------------
void Matrix4f::Transpose()
{
    Matrix4f tempMat;
	GetTranspose(tempMat);
	*this = tempMat;
}
//----------------------------------------------------------------------------
void Matrix4f::Inverse()
{
    Matrix4f tempMat;
	GetInverse(tempMat);
	*this = tempMat;
}
//----------------------------------------------------------------------------
Matrix4f Swing::operator*(float fLhsScalar, const Matrix4f& rRhsMat)
{
    return rRhsMat * fLhsScalar;
}
//----------------------------------------------------------------------------
Vector4f Swing::operator*(const Vector4f& rLhsVec, const Matrix4f& rRhsMat)
{
    return Vector4f(
        rLhsVec[0]*rRhsMat.M11 + rLhsVec[1]*rRhsMat.M21 + 
        rLhsVec[2]*rRhsMat.M31 + rLhsVec[3]*rRhsMat.M41,
        rLhsVec[0]*rRhsMat.M12 + rLhsVec[1]*rRhsMat.M22 + 
        rLhsVec[2]*rRhsMat.M32 + rLhsVec[3]*rRhsMat.M42,
        rLhsVec[0]*rRhsMat.M13 + rLhsVec[1]*rRhsMat.M23 + 
        rLhsVec[2]*rRhsMat.M33 + rLhsVec[3]*rRhsMat.M43,
        rLhsVec[0]*rRhsMat.M14 + rLhsVec[1]*rRhsMat.M24 + 
        rLhsVec[2]*rRhsMat.M34 + rLhsVec[3]*rRhsMat.M44);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// ˫����4�׷�����
//----------------------------------------------------------------------------

const Matrix4d Matrix4d::ZERO(0.0, 0.0, 0.0, 0.0,
                              0.0, 0.0, 0.0, 0.0,
                              0.0, 0.0, 0.0, 0.0,
                              0.0, 0.0, 0.0, 0.0);
const Matrix4d Matrix4d::IDENTITY(1.0, 0.0, 0.0, 0.0,
                                  0.0, 1.0, 0.0, 0.0,
                                  0.0, 0.0, 1.0, 0.0,
                                  0.0, 0.0, 0.0, 1.0);

//----------------------------------------------------------------------------
Matrix4d::Matrix4d()
{
    Zero();
}
//----------------------------------------------------------------------------
Matrix4d::Matrix4d(const Matrix4d& rMat)
{
    memcpy(m_dData, rMat.m_dData, 16*sizeof(double));
}
//----------------------------------------------------------------------------
Matrix4d::Matrix4d(double dM11, double dM12, double dM13, double dM14,
                   double dM21, double dM22, double dM23, double dM24,
                   double dM31, double dM32, double dM33, double dM34,
                   double dM41, double dM42, double dM43, double dM44)
{
    M11 = dM11;
    M12 = dM12;
    M13 = dM13;
    M14 = dM14;

    M21 = dM21;
    M22 = dM22;
    M23 = dM23;
    M24 = dM24;

    M31 = dM31;
    M32 = dM32;
    M33 = dM33;
    M34 = dM34;

    M41 = dM41;
    M42 = dM42;
    M43 = dM43;
    M44 = dM44;
}
//----------------------------------------------------------------------------
Matrix4d::operator const double*() const
{
    return &m_dData[0][0];
}
//----------------------------------------------------------------------------
Matrix4d::operator double*()
{
    return &m_dData[0][0];
}
//----------------------------------------------------------------------------
const double* Matrix4d::operator[](int iCurRow) const
{
    return &m_dData[iCurRow][0];
}
//----------------------------------------------------------------------------
double* Matrix4d::operator[](int iCurRow)
{
     return &m_dData[iCurRow][0];
}
//----------------------------------------------------------------------------
double Matrix4d::operator()(int iCurRow, int iCurCol) const
{
    return m_dData[iCurRow][iCurCol];
}
//----------------------------------------------------------------------------
double& Matrix4d::operator()(int iCurRow, int iCurCol)
{
    return m_dData[iCurRow][iCurCol];
}
//----------------------------------------------------------------------------
Matrix4d& Matrix4d::operator=(const Matrix4d& rMat)
{
    memcpy(m_dData, rMat.m_dData, 16*sizeof(double));
    return *this;
}
//----------------------------------------------------------------------------
bool Matrix4d::operator==(const Matrix4d& rMat) const
{
    return CompareData(rMat) == 0;
}
//----------------------------------------------------------------------------
bool Matrix4d::operator!= (const Matrix4d& rMat) const
{
    return CompareData(rMat) != 0;
}
//----------------------------------------------------------------------------
bool Matrix4d::operator<(const Matrix4d& rMat) const
{
    return CompareData(rMat) < 0;
}
//----------------------------------------------------------------------------
bool Matrix4d::operator<=(const Matrix4d& rMat) const
{
    return CompareData(rMat) <= 0;
}
//----------------------------------------------------------------------------
bool Matrix4d::operator>(const Matrix4d& rMat) const
{
    return CompareData(rMat) > 0;
}
//----------------------------------------------------------------------------
bool Matrix4d::operator>=(const Matrix4d& rMat) const
{
    return CompareData(rMat) >= 0;
}
//----------------------------------------------------------------------------
Matrix4d Matrix4d::operator+(const Matrix4d& rRhsMat) const
{
    Matrix4d ResMat;

    ResMat.M11 = M11 + rRhsMat.M11;
    ResMat.M12 = M12 + rRhsMat.M12;
    ResMat.M13 = M13 + rRhsMat.M13;
    ResMat.M14 = M14 + rRhsMat.M14;

    ResMat.M21 = M21 + rRhsMat.M21;
    ResMat.M22 = M22 + rRhsMat.M22;
    ResMat.M23 = M23 + rRhsMat.M23;
    ResMat.M24 = M24 + rRhsMat.M24;

    ResMat.M31 = M31 + rRhsMat.M31;
    ResMat.M32 = M32 + rRhsMat.M32;
    ResMat.M33 = M33 + rRhsMat.M33;
    ResMat.M34 = M34 + rRhsMat.M34;

    ResMat.M41 = M41 + rRhsMat.M41;
    ResMat.M42 = M42 + rRhsMat.M42;
    ResMat.M43 = M43 + rRhsMat.M43;
    ResMat.M44 = M44 + rRhsMat.M44;

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix4d Matrix4d::operator-(const Matrix4d& rRhsMat) const
{
    Matrix4d ResMat;

    ResMat.M11 = M11 - rRhsMat.M11;
    ResMat.M12 = M12 - rRhsMat.M12;
    ResMat.M13 = M13 - rRhsMat.M13;
    ResMat.M14 = M14 - rRhsMat.M14;

    ResMat.M21 = M21 - rRhsMat.M21;
    ResMat.M22 = M22 - rRhsMat.M22;
    ResMat.M23 = M23 - rRhsMat.M23;
    ResMat.M24 = M24 - rRhsMat.M24;

    ResMat.M31 = M31 - rRhsMat.M31;
    ResMat.M32 = M32 - rRhsMat.M32;
    ResMat.M33 = M33 - rRhsMat.M33;
    ResMat.M34 = M34 - rRhsMat.M34;

    ResMat.M41 = M41 - rRhsMat.M41;
    ResMat.M42 = M42 - rRhsMat.M42;
    ResMat.M43 = M43 - rRhsMat.M43;
    ResMat.M44 = M44 - rRhsMat.M44;

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix4d Matrix4d::operator*(const Matrix4d& rRhsMat) const
{
    SE_ALIGN16 Matrix4d ResMat;

#ifdef _SIMD
    // ��ʵ��.
    // ��δ֧��SIMD.
    SE_ASSERT( false );
#else
    ResMat.M11 = M11*rRhsMat.M11 + M12*rRhsMat.M21 + M13*rRhsMat.M31 + 
        M14*rRhsMat.M41;
    ResMat.M12 = M11*rRhsMat.M12 + M12*rRhsMat.M22 + M13*rRhsMat.M32 + 
        M14*rRhsMat.M42;
    ResMat.M13 = M11*rRhsMat.M13 + M12*rRhsMat.M23 + M13*rRhsMat.M33 + 
        M14*rRhsMat.M43;
    ResMat.M14 = M11*rRhsMat.M14 + M12*rRhsMat.M24 + M13*rRhsMat.M34 + 
        M14*rRhsMat.M44;

    ResMat.M21 = M21*rRhsMat.M11 + M22*rRhsMat.M21 + M23*rRhsMat.M31 + 
        M24*rRhsMat.M41;
    ResMat.M22 = M21*rRhsMat.M12 + M22*rRhsMat.M22 + M23*rRhsMat.M32 + 
        M24*rRhsMat.M42;
    ResMat.M23 = M21*rRhsMat.M13 + M22*rRhsMat.M23 + M23*rRhsMat.M33 + 
        M24*rRhsMat.M43;
    ResMat.M24 = M21*rRhsMat.M14 + M22*rRhsMat.M24 + M23*rRhsMat.M34 + 
        M24*rRhsMat.M44;

    ResMat.M31 = M31*rRhsMat.M11 + M32*rRhsMat.M21 + M33*rRhsMat.M31 + 
        M34*rRhsMat.M41;
    ResMat.M32 = M31*rRhsMat.M12 + M32*rRhsMat.M22 + M33*rRhsMat.M32 + 
        M34*rRhsMat.M42;
    ResMat.M33 = M31*rRhsMat.M13 + M32*rRhsMat.M23 + M33*rRhsMat.M33 + 
        M34*rRhsMat.M43;
    ResMat.M34 = M31*rRhsMat.M14 + M32*rRhsMat.M24 + M33*rRhsMat.M34 + 
        M34*rRhsMat.M44;

    ResMat.M41 = M41*rRhsMat.M11 + M42*rRhsMat.M21 + M43*rRhsMat.M31 + 
        M44*rRhsMat.M41;
    ResMat.M42 = M41*rRhsMat.M12 + M42*rRhsMat.M22 + M43*rRhsMat.M32 + 
        M44*rRhsMat.M42;
    ResMat.M43 = M41*rRhsMat.M13 + M42*rRhsMat.M23 + M43*rRhsMat.M33 + 
        M44*rRhsMat.M43;
    ResMat.M44 = M41*rRhsMat.M14 + M42*rRhsMat.M24 + M43*rRhsMat.M34 + 
        M44*rRhsMat.M44;
#endif

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix4d Matrix4d::operator*(double dScalar) const
{
    Matrix4d ResMat;

    ResMat.M11 = M11 * dScalar;
    ResMat.M12 = M12 * dScalar;
    ResMat.M13 = M13 * dScalar;
    ResMat.M14 = M14 * dScalar;

    ResMat.M21 = M21 * dScalar;
    ResMat.M22 = M22 * dScalar;
    ResMat.M23 = M23 * dScalar;
    ResMat.M24 = M24 * dScalar;

    ResMat.M31 = M31 * dScalar;
    ResMat.M32 = M32 * dScalar;
    ResMat.M33 = M33 * dScalar;
    ResMat.M34 = M34 * dScalar;

    ResMat.M41 = M41 * dScalar;
    ResMat.M42 = M42 * dScalar;
    ResMat.M43 = M43 * dScalar;
    ResMat.M44 = M44 * dScalar;

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix4d Matrix4d::operator/(double dScalar) const
{
    // ע���������Ϊ0
    Matrix4d ResMat;
    double dInvScalar = 1.0 / dScalar;

    ResMat.M11 = M11 * dInvScalar;
    ResMat.M12 = M12 * dInvScalar;
    ResMat.M13 = M13 * dInvScalar;
    ResMat.M14 = M14 * dInvScalar;

    ResMat.M21 = M21 * dInvScalar;
    ResMat.M22 = M22 * dInvScalar;
    ResMat.M23 = M23 * dInvScalar;
    ResMat.M24 = M24 * dInvScalar;

    ResMat.M31 = M31 * dInvScalar;
    ResMat.M32 = M32 * dInvScalar;
    ResMat.M33 = M33 * dInvScalar;
    ResMat.M34 = M34 * dInvScalar;

    ResMat.M41 = M41 * dInvScalar;
    ResMat.M42 = M42 * dInvScalar;
    ResMat.M43 = M43 * dInvScalar;
    ResMat.M44 = M44 * dInvScalar;

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix4d Matrix4d::operator-() const
{
    Matrix4d ResMat;

    ResMat.M11 = -M11;
    ResMat.M12 = -M12;
    ResMat.M13 = -M13;
    ResMat.M14 = -M14;

    ResMat.M21 = -M21;
    ResMat.M22 = -M22;
    ResMat.M23 = -M23;
    ResMat.M24 = -M24;

    ResMat.M31 = -M31;
    ResMat.M32 = -M32;
    ResMat.M33 = -M33;
    ResMat.M34 = -M34;

    ResMat.M41 = -M41;
    ResMat.M42 = -M42;
    ResMat.M43 = -M43;
    ResMat.M44 = -M44;

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix4d& Matrix4d::operator+=(const Matrix4d& rRhsMat)
{
	M11 += rRhsMat.M11;
    M12 += rRhsMat.M12;
    M13 += rRhsMat.M13;
    M14 += rRhsMat.M14;

    M21 += rRhsMat.M21;
    M22 += rRhsMat.M22;
    M23 += rRhsMat.M23;
    M24 += rRhsMat.M24;

    M31 += rRhsMat.M31;
    M32 += rRhsMat.M32;
    M33 += rRhsMat.M33;
    M34 += rRhsMat.M34;

    M41 += rRhsMat.M41;
    M42 += rRhsMat.M42;
    M43 += rRhsMat.M43;
    M44 += rRhsMat.M44;

    return *this;
}
//----------------------------------------------------------------------------
Matrix4d& Matrix4d::operator-=(const Matrix4d& rRhsMat)
{
	M11 -= rRhsMat.M11;
    M12 -= rRhsMat.M12;
    M13 -= rRhsMat.M13;
    M14 -= rRhsMat.M14;

    M21 -= rRhsMat.M21;
    M22 -= rRhsMat.M22;
    M23 -= rRhsMat.M23;
    M24 -= rRhsMat.M24;

    M31 -= rRhsMat.M31;
    M32 -= rRhsMat.M32;
    M33 -= rRhsMat.M33;
    M34 -= rRhsMat.M34;

    M41 -= rRhsMat.M41;
    M42 -= rRhsMat.M42;
    M43 -= rRhsMat.M43;
    M44 -= rRhsMat.M44;

    return *this;
}
//----------------------------------------------------------------------------
Matrix4d& Matrix4d::operator*=(double dScalar)
{
	M11 *= dScalar;
    M12 *= dScalar;
    M13 *= dScalar;
    M14 *= dScalar;

    M21 *= dScalar;
    M22 *= dScalar;
    M23 *= dScalar;
    M24 *= dScalar;

    M31 *= dScalar;
    M32 *= dScalar;
    M33 *= dScalar;
    M34 *= dScalar;

    M41 *= dScalar;
    M42 *= dScalar;
    M43 *= dScalar;
    M44 *= dScalar;

    return *this;
}
//----------------------------------------------------------------------------
Matrix4d& Matrix4d::operator/=(double dScalar)
{
    // ע���������Ϊ0
    double dInvScalar = 1.0 / dScalar;
	M11 *= dInvScalar;
    M12 *= dInvScalar;
    M13 *= dInvScalar;
    M14 *= dInvScalar;

    M21 *= dInvScalar;
    M22 *= dInvScalar;
    M23 *= dInvScalar;
    M24 *= dInvScalar;

    M31 *= dInvScalar;
    M32 *= dInvScalar;
    M33 *= dInvScalar;
    M34 *= dInvScalar;

    M41 *= dInvScalar;
    M42 *= dInvScalar;
    M43 *= dInvScalar;
    M44 *= dInvScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector4d Matrix4d::operator*(const Vector4d& rRhsVec) const
{
    Vector4d ResVec;
    
    ResVec[0] = M11*rRhsVec[0] + M12*rRhsVec[1] + M13*rRhsVec[2] + 
        M14*rRhsVec[3];
    ResVec[1] = M21*rRhsVec[0] + M22*rRhsVec[1] + M23*rRhsVec[2] + 
        M24*rRhsVec[3];
    ResVec[2] = M31*rRhsVec[0] + M32*rRhsVec[1] + M33*rRhsVec[2] + 
        M34*rRhsVec[3];
    ResVec[3] = M41*rRhsVec[0] + M42*rRhsVec[1] + M43*rRhsVec[2] + 
        M44*rRhsVec[3];

    return ResVec;
}
//----------------------------------------------------------------------------
void Matrix4d::Transpose()
{
    Matrix4d tempMat;
	GetTranspose(tempMat);
	*this = tempMat;
}
//----------------------------------------------------------------------------
void Matrix4d::Inverse()
{
    Matrix4d tempMat;
	GetInverse(tempMat);
	*this = tempMat;
}
//----------------------------------------------------------------------------
Matrix4d Swing::operator*(double dLhsScalar, const Matrix4d& rRhsMat)
{
    return rRhsMat * dLhsScalar;
}
//----------------------------------------------------------------------------
Vector4d Swing::operator*(const Vector4d& rLhsVec, const Matrix4d& rRhsMat)
{
    return Vector4d(
        rLhsVec[0]*rRhsMat.M11 + rLhsVec[1]*rRhsMat.M21 + 
        rLhsVec[2]*rRhsMat.M31 + rLhsVec[3]*rRhsMat.M41,
        rLhsVec[0]*rRhsMat.M12 + rLhsVec[1]*rRhsMat.M22 + 
        rLhsVec[2]*rRhsMat.M32 + rLhsVec[3]*rRhsMat.M42,
        rLhsVec[0]*rRhsMat.M13 + rLhsVec[1]*rRhsMat.M23 + 
        rLhsVec[2]*rRhsMat.M33 + rLhsVec[3]*rRhsMat.M43,
        rLhsVec[0]*rRhsMat.M14 + rLhsVec[1]*rRhsMat.M24 + 
        rLhsVec[2]*rRhsMat.M34 + rLhsVec[3]*rRhsMat.M44);
}
//----------------------------------------------------------------------------