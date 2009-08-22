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
#include "SEMatrix3.h"

using namespace Swing;

//----------------------------------------------------------------------------
// 单精度3阶方阵类
//----------------------------------------------------------------------------

const Matrix3f Matrix3f::ZERO(0.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 0.0f);
const Matrix3f Matrix3f::IDENTITY(1.0f, 0.0f, 0.0f,
                                  0.0f, 1.0f, 0.0f,
                                  0.0f, 0.0f, 1.0f);

//----------------------------------------------------------------------------
Matrix3f::Matrix3f()
{
    Zero();
}
//----------------------------------------------------------------------------
Matrix3f::Matrix3f(const Matrix3f& rMat)
{
    memcpy(m_fData, rMat.m_fData, /*12*/9*sizeof(float));
}
//----------------------------------------------------------------------------
Matrix3f::Matrix3f(float fM11, float fM12, float fM13, 
                   float fM21, float fM22, float fM23, 
                   float fM31, float fM32, float fM33)
{
    m_fData[0][0] = fM11;
    m_fData[0][1] = fM12;
    m_fData[0][2] = fM13;
    //m_fData[0][3] = 0.0f;

    m_fData[1][0] = fM21;
    m_fData[1][1] = fM22;
    m_fData[1][2] = fM23;
    //m_fData[1][3] = 0.0f;

    m_fData[2][0] = fM31;
    m_fData[2][1] = fM32;
    m_fData[2][2] = fM33;
    //m_fData[2][3] = 0.0f;

    //m_fData[3][0] = 0.0f;
    //m_fData[3][1] = 0.0f;
    //m_fData[3][2] = 0.0f;
    //m_fData[3][3] = 0.0f;
}
//----------------------------------------------------------------------------
Matrix3f::Matrix3f(const Vector3f& rVecU, const Vector3f& rVecV, 
    const Vector3f& rVecW, bool bIsRow)
{
    Zero();

    if( bIsRow )
	{
        m_fData[0][0] = rVecU[0];
        m_fData[0][1] = rVecU[1];
        m_fData[0][2] = rVecU[2];
        m_fData[1][0] = rVecV[0];
        m_fData[1][1] = rVecV[1];
        m_fData[1][2] = rVecV[2];
        m_fData[2][0] = rVecW[0];
        m_fData[2][1] = rVecW[1];
        m_fData[2][2] = rVecW[2];
    }
	else
    {
        m_fData[0][0] = rVecU[0];
        m_fData[0][1] = rVecV[0];
        m_fData[0][2] = rVecW[0];
        m_fData[1][0] = rVecU[1];
        m_fData[1][1] = rVecV[1];
        m_fData[1][2] = rVecW[1];
        m_fData[2][0] = rVecU[2];
        m_fData[2][1] = rVecV[2];
        m_fData[2][2] = rVecW[2];
	}
}
//----------------------------------------------------------------------------
Matrix3f::Matrix3f(float fM11, float fM22, float fM33)
{
    Zero();

    Diagonal(fM11, fM22, fM33);
}
//----------------------------------------------------------------------------
Matrix3f::Matrix3f(const Vector3f& rAxisVec, float fAngle)
{
    Zero();

    FromAxisAngle(rAxisVec, fAngle);
}
//----------------------------------------------------------------------------
Matrix3f::Matrix3f(const Vector3f& rVecU, const Vector3f& rVecV)
{
    Zero();

    TensorProduct(rVecU, rVecV);
}
//----------------------------------------------------------------------------
Matrix3f::operator const float*() const
{
    return &m_fData[0][0];
}
//----------------------------------------------------------------------------
Matrix3f::operator float*()
{
    return &m_fData[0][0];
}
//----------------------------------------------------------------------------
const float* Matrix3f::operator[](int iCurRow) const
{
    return &m_fData[iCurRow][0];
}
//----------------------------------------------------------------------------
float* Matrix3f::operator[](int iCurRow)
{
    return &m_fData[iCurRow][0];
}
//----------------------------------------------------------------------------
float Matrix3f::operator()(int iCurRow, int iCurCol) const
{
    return m_fData[iCurRow][iCurCol];
}
//----------------------------------------------------------------------------
float& Matrix3f::operator()(int iCurRow, int iCurCol)
{
    return m_fData[iCurRow][iCurCol];
}
//----------------------------------------------------------------------------
Matrix3f& Matrix3f::operator=(const Matrix3f& rMat)
{
    memcpy(m_fData, rMat.m_fData, /*12*/9*sizeof(float));

    return *this;
}
//----------------------------------------------------------------------------
bool Matrix3f::operator==(const Matrix3f& rMat) const
{
    return CompareData(rMat) == 0;
}
//----------------------------------------------------------------------------
bool Matrix3f::operator!=(const Matrix3f& rMat) const
{
    return CompareData(rMat) != 0;
}
//----------------------------------------------------------------------------
bool Matrix3f::operator<(const Matrix3f& rMat) const
{
    return CompareData(rMat) < 0;
}
//----------------------------------------------------------------------------
bool Matrix3f::operator<=(const Matrix3f& rMat) const
{
    return CompareData(rMat) <= 0;
}
//----------------------------------------------------------------------------
bool Matrix3f::operator>(const Matrix3f& rMat) const
{
    return CompareData(rMat) > 0;
}
//----------------------------------------------------------------------------
bool Matrix3f::operator>=(const Matrix3f& rMat) const
{
    return CompareData(rMat) >= 0;
}
//----------------------------------------------------------------------------
Matrix3f Matrix3f::operator+(const Matrix3f& rRhsMat) const
{
    Matrix3f ResMat;

    ResMat.m_fData[0][0] = m_fData[0][0] + rRhsMat.m_fData[0][0];
    ResMat.m_fData[0][1] = m_fData[0][1] + rRhsMat.m_fData[0][1];
    ResMat.m_fData[0][2] = m_fData[0][2] + rRhsMat.m_fData[0][2];

    ResMat.m_fData[1][0] = m_fData[1][0] + rRhsMat.m_fData[1][0];
    ResMat.m_fData[1][1] = m_fData[1][1] + rRhsMat.m_fData[1][1];
    ResMat.m_fData[1][2] = m_fData[1][2] + rRhsMat.m_fData[1][2];

    ResMat.m_fData[2][0] = m_fData[2][0] + rRhsMat.m_fData[2][0];
    ResMat.m_fData[2][1] = m_fData[2][1] + rRhsMat.m_fData[2][1];
    ResMat.m_fData[2][2] = m_fData[2][2] + rRhsMat.m_fData[2][2];

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix3f Matrix3f::operator-(const Matrix3f& rRhsMat) const
{
    Matrix3f ResMat;

    ResMat.m_fData[0][0] = m_fData[0][0] - rRhsMat.m_fData[0][0];
    ResMat.m_fData[0][1] = m_fData[0][1] - rRhsMat.m_fData[0][1];
    ResMat.m_fData[0][2] = m_fData[0][2] - rRhsMat.m_fData[0][2];

    ResMat.m_fData[1][0] = m_fData[1][0] - rRhsMat.m_fData[1][0];
    ResMat.m_fData[1][1] = m_fData[1][1] - rRhsMat.m_fData[1][1];
    ResMat.m_fData[1][2] = m_fData[1][2] - rRhsMat.m_fData[1][2];

    ResMat.m_fData[2][0] = m_fData[2][0] - rRhsMat.m_fData[2][0];
    ResMat.m_fData[2][1] = m_fData[2][1] - rRhsMat.m_fData[2][1];
    ResMat.m_fData[2][2] = m_fData[2][2] - rRhsMat.m_fData[2][2];

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix3f Matrix3f::operator*(const Matrix3f& rRhsMat) const
{
    Matrix3f ResMat;

#ifdef _SIMD
    __asm
    {
        mov edi,rRhsMat         // 把右操作数矩阵的首地址指针保存到edi
        movups xmm4,[edi]       // 保存右操作数矩阵的第1行到xmm4
        movups xmm5,[edi+16]    // 保存右操作数矩阵的第2行到xmm5
        movups xmm6,[edi+32]    // 保存右操作数矩阵的第3行到xmm6

        mov esi,this			// 把左操作数矩阵的首地址指针保存到esi

        movss xmm0,[esi]
        // xmm0变为4个重复的左操作数矩阵第1行第1个元素,aaaa
        shufps xmm0,xmm0,0x00
        movss xmm1,[esi+4]
        // xmm1变为4个重复的左操作数矩阵第1行第2个元素,bbbb
        shufps xmm1,xmm1,0x00
        movss xmm2,[esi+8]
        // xmm2变为4个重复的左操作数矩阵第1行第3个元素,cccc
        shufps xmm2,xmm2,0x00

        mulps xmm0,xmm4
        mulps xmm1,xmm5
        mulps xmm2,xmm6

        addps xmm0,xmm1
        addps xmm0,xmm2

        movups ResMat[0],xmm0

        movss xmm0,[esi+16]
        shufps xmm0,xmm0,0x00
        movss xmm1,[esi+20]
        shufps xmm1,xmm1,0x00
        movss xmm2,[esi+24]
        shufps xmm2,xmm2,0x00

        mulps xmm0,xmm4
        mulps xmm1,xmm5
        mulps xmm2,xmm6

        addps xmm0,xmm1
        addps xmm0,xmm2

        movups ResMat[16],xmm0

        movss xmm0,[esi+32]
        shufps xmm0,xmm0,0x00
        movss xmm1,[esi+36]
        shufps xmm1,xmm1,0x00
        movss xmm2,[esi+40]
        shufps xmm2,xmm2,0x00

        mulps xmm0,xmm4
        mulps xmm1,xmm5
        mulps xmm2,xmm6

        addps xmm0,xmm1
        addps xmm0,xmm2

        movups ResMat[32],xmm0
    }
#else
    ResMat.m_fData[0][0] = m_fData[0][0]*rRhsMat.m_fData[0][0] + 
                           m_fData[0][1]*rRhsMat.m_fData[1][0] + 
                           m_fData[0][2]*rRhsMat.m_fData[2][0];
    ResMat.m_fData[0][1] = m_fData[0][0]*rRhsMat.m_fData[0][1] + 
                           m_fData[0][1]*rRhsMat.m_fData[1][1] + 
                           m_fData[0][2]*rRhsMat.m_fData[2][1];
    ResMat.m_fData[0][2] = m_fData[0][0]*rRhsMat.m_fData[0][2] + 
                           m_fData[0][1]*rRhsMat.m_fData[1][2] + 
                           m_fData[0][2]*rRhsMat.m_fData[2][2];

    ResMat.m_fData[1][0] = m_fData[1][0]*rRhsMat.m_fData[0][0] + 
                           m_fData[1][1]*rRhsMat.m_fData[1][0] + 
                           m_fData[1][2]*rRhsMat.m_fData[2][0];
    ResMat.m_fData[1][1] = m_fData[1][0]*rRhsMat.m_fData[0][1] + 
                           m_fData[1][1]*rRhsMat.m_fData[1][1] + 
                           m_fData[1][2]*rRhsMat.m_fData[2][1];
    ResMat.m_fData[1][2] = m_fData[1][0]*rRhsMat.m_fData[0][2] + 
                           m_fData[1][1]*rRhsMat.m_fData[1][2] + 
                           m_fData[1][2]*rRhsMat.m_fData[2][2];

    ResMat.m_fData[2][0] = m_fData[2][0]*rRhsMat.m_fData[0][0] + 
                           m_fData[2][1]*rRhsMat.m_fData[1][0] + 
                           m_fData[2][2]*rRhsMat.m_fData[2][0];
    ResMat.m_fData[2][1] = m_fData[2][0]*rRhsMat.m_fData[0][1] + 
                           m_fData[2][1]*rRhsMat.m_fData[1][1] + 
                           m_fData[2][2]*rRhsMat.m_fData[2][1];
    ResMat.m_fData[2][2] = m_fData[2][0]*rRhsMat.m_fData[0][2] + 
                           m_fData[2][1]*rRhsMat.m_fData[1][2] + 
                           m_fData[2][2]*rRhsMat.m_fData[2][2];
#endif

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix3f Matrix3f::operator*(float fScalar) const
{
    Matrix3f ResMat;

    ResMat.m_fData[0][0] = m_fData[0][0] * fScalar;
    ResMat.m_fData[0][1] = m_fData[0][1] * fScalar;
    ResMat.m_fData[0][2] = m_fData[0][2] * fScalar;

    ResMat.m_fData[1][0] = m_fData[1][0] * fScalar;
    ResMat.m_fData[1][1] = m_fData[1][1] * fScalar;
    ResMat.m_fData[1][2] = m_fData[1][2] * fScalar;

    ResMat.m_fData[2][0] = m_fData[2][0] * fScalar;
    ResMat.m_fData[2][1] = m_fData[2][1] * fScalar;
    ResMat.m_fData[2][2] = m_fData[2][2] * fScalar;

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix3f Matrix3f::operator/(float fScalar) const
{
    // 注意除数不能为0
    Matrix3f ResMat;
    float fInvScalar = 1.0f / fScalar;

    ResMat.m_fData[0][0] = m_fData[0][0] * fInvScalar;
    ResMat.m_fData[0][1] = m_fData[0][1] * fInvScalar;
    ResMat.m_fData[0][2] = m_fData[0][2] * fInvScalar;

    ResMat.m_fData[1][0] = m_fData[1][0] * fInvScalar;
    ResMat.m_fData[1][1] = m_fData[1][1] * fInvScalar;
    ResMat.m_fData[1][2] = m_fData[1][2] * fInvScalar;

    ResMat.m_fData[2][0] = m_fData[2][0] * fInvScalar;
    ResMat.m_fData[2][1] = m_fData[2][1] * fInvScalar;
    ResMat.m_fData[2][2] = m_fData[2][2] * fInvScalar;

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix3f Matrix3f::operator-() const
{
    Matrix3f ResMat;

    ResMat.m_fData[0][0] = -m_fData[0][0];
    ResMat.m_fData[0][1] = -m_fData[0][1];
    ResMat.m_fData[0][2] = -m_fData[0][2];

    ResMat.m_fData[1][0] = -m_fData[1][0];
    ResMat.m_fData[1][1] = -m_fData[1][1];
    ResMat.m_fData[1][2] = -m_fData[1][2];

    ResMat.m_fData[2][0] = -m_fData[2][0];
    ResMat.m_fData[2][1] = -m_fData[2][1];
    ResMat.m_fData[2][2] = -m_fData[2][2];

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix3f& Matrix3f::operator+=(const Matrix3f& rRhsMat)
{
	m_fData[0][0] += rRhsMat.m_fData[0][0];
    m_fData[0][1] += rRhsMat.m_fData[0][1];
    m_fData[0][2] += rRhsMat.m_fData[0][2];

    m_fData[1][0] += rRhsMat.m_fData[1][0];
    m_fData[1][1] += rRhsMat.m_fData[1][1];
    m_fData[1][2] += rRhsMat.m_fData[1][2];

    m_fData[2][0] += rRhsMat.m_fData[2][0];
    m_fData[2][1] += rRhsMat.m_fData[2][1];
    m_fData[2][2] += rRhsMat.m_fData[2][2];

    return *this;
}
//----------------------------------------------------------------------------
Matrix3f& Matrix3f::operator-=(const Matrix3f& rRhsMat)
{
	m_fData[0][0] -= rRhsMat.m_fData[0][0];
    m_fData[0][1] -= rRhsMat.m_fData[0][1];
    m_fData[0][2] -= rRhsMat.m_fData[0][2];

    m_fData[1][0] -= rRhsMat.m_fData[1][0];
    m_fData[1][1] -= rRhsMat.m_fData[1][1];
    m_fData[1][2] -= rRhsMat.m_fData[1][2];

    m_fData[2][0] -= rRhsMat.m_fData[2][0];
    m_fData[2][1] -= rRhsMat.m_fData[2][1];
    m_fData[2][2] -= rRhsMat.m_fData[2][2];

    return *this;
}
//----------------------------------------------------------------------------
Matrix3f& Matrix3f::operator*=(float fScalar)
{
	m_fData[0][0] *= fScalar;
    m_fData[0][1] *= fScalar;
    m_fData[0][2] *= fScalar;

    m_fData[1][0] *= fScalar;
    m_fData[1][1] *= fScalar;
    m_fData[1][2] *= fScalar;

    m_fData[2][0] *= fScalar;
    m_fData[2][1] *= fScalar;
    m_fData[2][2] *= fScalar;

    return *this;
}
//----------------------------------------------------------------------------
Matrix3f& Matrix3f::operator/=(float fScalar)
{
    // 注意除数不能为0
    float fInvScalar = 1.0f / fScalar;
	m_fData[0][0] *= fInvScalar;
    m_fData[0][1] *= fInvScalar;
    m_fData[0][2] *= fInvScalar;

    m_fData[1][0] *= fInvScalar;
    m_fData[1][1] *= fInvScalar;
    m_fData[1][2] *= fInvScalar;

    m_fData[2][0] *= fInvScalar;
    m_fData[2][1] *= fInvScalar;
    m_fData[2][2] *= fInvScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector3f Matrix3f::operator*(const Vector3f& rRhsVec) const
{
    Vector3f ResVec;
   
    ResVec[0] = m_fData[0][0]*rRhsVec[0] + m_fData[0][1]*rRhsVec[1] + 
        m_fData[0][2]*rRhsVec[2];
    ResVec[1] = m_fData[1][0]*rRhsVec[0] + m_fData[1][1]*rRhsVec[1] + 
        m_fData[1][2]*rRhsVec[2];
    ResVec[2] = m_fData[2][0]*rRhsVec[0] + m_fData[2][1]*rRhsVec[1] + 
        m_fData[2][2]*rRhsVec[2];

    return ResVec;
}
//----------------------------------------------------------------------------
void Matrix3f::Transpose()
{
    Matrix3f tempMat;
	GetTranspose(tempMat);
	*this = tempMat;
}
//----------------------------------------------------------------------------
void Matrix3f::Inverse()
{
    Matrix3f tempMat;
	GetInverse(tempMat);
	*this = tempMat;
}
//----------------------------------------------------------------------------
Matrix3f& Matrix3f::FromEulerAnglesXYZ(float fYAngle, float fPAngle, 
    float fRAngle)
{
    float fCos, fSin;

    fCos = Math<float>::Cos(fYAngle);
    fSin = Math<float>::Sin(fYAngle);
    Matrix3f RotXMat(
        1.0f,0.0f,0.0f,
        0.0f,fCos,fSin,
        0.0f,-fSin,fCos);

    fCos = Math<float>::Cos(fPAngle);
    fSin = Math<float>::Sin(fPAngle);
    Matrix3f RotYMat(
        fCos,0.0f,-fSin,
        0.0f,1.0f,0.0f,
        fSin,0.0f,fCos);

    fCos = Math<float>::Cos(fRAngle);
    fSin = Math<float>::Sin(fRAngle);
    Matrix3f RotZMat(
        fCos,fSin,0.0f,
        -fSin,fCos,0.0f,
        0.0f,0.0f,1.0f);

    *this = RotXMat*(RotYMat*RotZMat);
    return *this;
}
//----------------------------------------------------------------------------
Matrix3f& Matrix3f::FromEulerAnglesXZY(float fYAngle, float fPAngle, 
    float fRAngle)
{
    float fCos, fSin;

    fCos = Math<float>::Cos(fYAngle);
    fSin = Math<float>::Sin(fYAngle);
    Matrix3f RotXMat(
        1.0f,0.0f,0.0f,
        0.0f,fCos,fSin,
        0.0f,-fSin,fCos);

    fCos = Math<float>::Cos(fPAngle);
    fSin = Math<float>::Sin(fPAngle);
    Matrix3f RotZMat(
        fCos,fSin,0.0f,
        -fSin,fCos,0.0f,
        0.0f,0.0f,1.0f);

    fCos = Math<float>::Cos(fRAngle);
    fSin = Math<float>::Sin(fRAngle);
    Matrix3f RotYMat(
        fCos,0.0f,-fSin,
        0.0f,1.0f,0.0f,
        fSin,0.0f,fCos);

    *this = RotXMat*(RotZMat*RotYMat);
    return *this;
}
//----------------------------------------------------------------------------
Matrix3f& Matrix3f::FromEulerAnglesYXZ(float fYAngle, float fPAngle, 
    float fRAngle)
{
    float fCos, fSin;

    fCos = Math<float>::Cos(fYAngle);
    fSin = Math<float>::Sin(fYAngle);
    Matrix3f RotYMat(
        fCos,0.0f,-fSin,
        0.0f,1.0f,0.0f,
        fSin,0.0f,fCos);

    fCos = Math<float>::Cos(fPAngle);
    fSin = Math<float>::Sin(fPAngle);
    Matrix3f RotXMat(
        1.0f,0.0f,0.0f,
        0.0f,fCos,fSin,
        0.0f,-fSin,fCos);

    fCos = Math<float>::Cos(fRAngle);
    fSin = Math<float>::Sin(fRAngle);
    Matrix3f RotZMat(
        fCos,fSin,0.0f,
        -fSin,fCos,0.0f,
        0.0f,0.0f,1.0f);

    *this = RotYMat*(RotXMat*RotZMat);
    return *this;
}
//----------------------------------------------------------------------------
Matrix3f& Matrix3f::FromEulerAnglesYZX(float fYAngle, float fPAngle, 
    float fRAngle)
{
    float fCos, fSin;

    fCos = Math<float>::Cos(fYAngle);
    fSin = Math<float>::Sin(fYAngle);
    Matrix3f RotYMat(
        fCos,0.0f,-fSin,
        0.0f,1.0f,0.0f,
        fSin,0.0f,fCos);

    fCos = Math<float>::Cos(fPAngle);
    fSin = Math<float>::Sin(fPAngle);
    Matrix3f RotZMat(
        fCos,fSin,0.0f,
        -fSin,fCos,0.0f,
        0.0f,0.0f,1.0f);

    fCos = Math<float>::Cos(fRAngle);
    fSin = Math<float>::Sin(fRAngle);
    Matrix3f RotXMat(
        1.0f,0.0f,0.0f,
        0.0f,fCos,fSin,
        0.0f,-fSin,fCos);

    *this = RotYMat*(RotZMat*RotXMat);
    return *this;
}
//----------------------------------------------------------------------------
Matrix3f& Matrix3f::FromEulerAnglesZXY(float fYAngle, float fPAngle, 
    float fRAngle)
{
    float fCos, fSin;

    fCos = Math<float>::Cos(fYAngle);
    fSin = Math<float>::Sin(fYAngle);
    Matrix3f RotZMat(
        fCos,fSin,0.0f,
        -fSin,fCos,0.0f,
        0.0f,0.0f,1.0f);

    fCos = Math<float>::Cos(fPAngle);
    fSin = Math<float>::Sin(fPAngle);
    Matrix3f RotXMat(
        1.0f,0.0f,0.0f,
        0.0f,fCos,fSin,
        0.0f,-fSin,fCos);

    fCos = Math<float>::Cos(fRAngle);
    fSin = Math<float>::Sin(fRAngle);
    Matrix3f RotYMat(
        fCos,0.0f,-fSin,
        0.0f,1.0f,0.0f,
        fSin,0.0f,fCos);

    *this = RotZMat*(RotXMat*RotYMat);
    return *this;
}
//----------------------------------------------------------------------------
Matrix3f& Matrix3f::FromEulerAnglesZYX(float fYAngle, float fPAngle, 
    float fRAngle)
{
    float fCos, fSin;

    fCos = Math<float>::Cos(fYAngle);
    fSin = Math<float>::Sin(fYAngle);
    Matrix3f RotZMat(
        fCos,fSin,0.0f,
        -fSin,fCos,0.0f,
        0.0f,0.0f,1.0f);

    fCos = Math<float>::Cos(fPAngle);
    fSin = Math<float>::Sin(fPAngle);
    Matrix3f RotYMat(
        fCos,0.0f,-fSin,
        0.0f,1.0f,0.0f,
        fSin,0.0f,fCos);

    fCos = Math<float>::Cos(fRAngle);
    fSin = Math<float>::Sin(fRAngle);
    Matrix3f RotXMat(
        1.0f,0.0f,0.0f,
        0.0f,fCos,fSin,
        0.0f,-fSin,fCos);

    *this = RotZMat*(RotYMat*RotXMat);
    return *this;
}
//----------------------------------------------------------------------------
bool Matrix3f::ToEulerAnglesXYZ(float& rfXAngle, float& rfYAngle, 
    float& rfZAngle) const
{
    // R = Rx * Ry * Rz
    //   = cy*cz           cy*sz          -sy
    //     cz*sx*sy-cx*sz  cx*cz+sx*sy*sz  sx*cy
    //     cx*cz*sy+sx*sz  cx*sy*sz-cz*sx  cx*cy
    //
    // 如果y = pi/2,则sy = 1,cy = 0
    // R = 0            0           -1
    //     cz*sx-cx*sz  cx*cz+sx*sz  0
    //     cx*cz+sx*sz  cx*sz-cz*sx  0
    //   = 0            0           -1
    //     sin(x-z)     cos(x-z)     0
    //     cos(x-z)     -sin(x-z)    0
    //
    // 如果y = -pi/2,则sy = -1,cy = 0
    // R =  0            0            1
    //     -cz*sx-cx*sz  cx*cz-sx*sz  0
    //     -cx*cz+sx*sz -cx*sz-cz*sx  0
    //   =  0            0            1
    //     -sin(x+z)     cos(x+z)     0
    //     -cos(x+z)    -sin(x+z)     0

    if( m_fData[0][2] > -1.0f )
    {
        if( m_fData[0][2] < 1.0f )
        {
            rfXAngle = Math<float>::ATan2(m_fData[1][2], m_fData[2][2]);
            rfYAngle = (float)asin(-(double)m_fData[0][2]);
            rfZAngle = Math<float>::ATan2(m_fData[0][1], m_fData[0][0]);

            return true;
        }
        else
        {
            // y = -pi/2,
            // 结果不唯一,
            // x + z = atan2(r10,r11)
            rfXAngle = Math<float>::ATan2(-m_fData[1][0], m_fData[1][1]);
            rfYAngle = -Math<float>::HALF_PI;
            rfZAngle = 0.0f;

            return false;
        }
    }
    else
    {
        // y = pi/2,
        // 结果不唯一,
        // x - z = atan2(r10,r11)
        rfXAngle = Math<float>::ATan2(m_fData[1][0], m_fData[1][1]);
        rfYAngle = Math<float>::HALF_PI;
        rfZAngle = 0.0f;

        return false;
    }
}
//----------------------------------------------------------------------------
bool Matrix3f::ToEulerAnglesXZY(float& rfXAngle, float& rfZAngle, 
    float& rfYAngle) const
{
    // R = Rx * Rz * Ry
    //   =  cy*cz           sz             -cz*sy
    //     -cx*cy*sz+sx*sy  cx*cz           cx*sy*sz+cy*sx
    //      cy*sx*sz+cx*sy -cz*sx          -sx*sy*sz+cx*cy
    //
    // 如果z = pi/2,则sz = 1,cz = 0
    // R = 0            1            0
    //     sx*sy-cx*cy  0            cx*sy+cy*sx
    //     cy*sx+cx*sy  0            cx*cy-sx*sy
    //   =  0            1           0
    //     -cos(x+y)     0           sin(x+y)
    //      sin(x+y)     0           cos(x+y)
    //
    // 如果z = -pi/2,则sz = -1,cz = 0
    // R =  0           -1            0
    //      cx*cy+sx*sy  0           -cx*sy+cy*sx
    //     -cy*sx+cx*sy  0            sx*sz+cx*cy
    //   =  0           -1            0
    //      cos(x-y)     0            sin(x-y)
    //     -sin(x-y)     0            cos(x-y)

    if( m_fData[0][1] > -1.0f )
    {
        if( m_fData[0][1] < 1.0f )
        {
            rfXAngle = Math<float>::ATan2(-m_fData[2][1], m_fData[1][1]);
            rfZAngle = (float)asin((double)m_fData[0][1]);
            rfYAngle = Math<float>::ATan2(-m_fData[0][2], m_fData[0][0]);

            return true;
        }
        else
        {
            // z = pi/2,
            // 结果不唯一,
            // x + y = atan2(r20,r22)
            rfXAngle = Math<float>::ATan2(m_fData[2][0], m_fData[2][2]);
            rfZAngle = Math<float>::HALF_PI;
            rfYAngle = 0.0f;

            return false;
        }
    }
    else
    {
        // z = -pi/2,
        // 结果不唯一,
        // x - y = atan2(-r20,r22)
        rfXAngle = Math<float>::ATan2(-m_fData[2][0], m_fData[2][2]);
        rfZAngle = -Math<float>::HALF_PI;
        rfYAngle = 0.0f;

        return false;
    }
}
//----------------------------------------------------------------------------
bool Matrix3f::ToEulerAnglesYXZ(float& rfYAngle, float& rfXAngle, 
    float& rfZAngle) const
{
    // R = Ry * Rx * Rz
    //   =  cy*cz-sx*sy*sz  cy*sz+cz*sx*sy -cx*sy
    //     -cx*sz           cx*cz           sx
    //      cz*sy+cy*sx*sz  sy*sz-cy*cz*sx  cx*cy
    //
    // 如果x = pi/2,则sx = 1,cx = 0
    // R = cy*cz-sy*sz  cy*sz+cz*sy  0
    //     0            0            1
    //     cz*sy+cy*sz  sy*sz-cy*cz  0
    //   = cos(y+z)     sin(y+z)    0
    //     0            0           1
    //     sin(y+z)    -cos(y+z)    0
    //
    // 如果x = -pi/2,则sx = -1,cx = 0
    // R = cy*cz+sy*sz  cy*sz-cz*sy  0
    //     0            0           -1
    //     cz*sy-cy*sz  sy*sz+cy*cz  0
    //   =  cos(y-z)    -sin(y-z)     0
    //      0            0           -1
    //      sin(y-z)     cos(y-z)     0

    if( m_fData[1][2] > -1.0f )
    {
        if( m_fData[1][2] < 1.0f )
        {
            rfYAngle = Math<float>::ATan2(-m_fData[0][2], m_fData[2][2]);
            rfXAngle = (float)asin((double)m_fData[1][2]);
            rfZAngle = Math<float>::ATan2(-m_fData[1][0], m_fData[1][1]);

            return true;
        }
        else
        {
            // x = pi/2,
            // 结果不唯一,
            // y + z = atan2(r01,r00)
            rfYAngle = Math<float>::ATan2(m_fData[0][1], m_fData[0][0]);
            rfXAngle = Math<float>::HALF_PI;
            rfZAngle = 0.0f;

            return false;
        }
    }
    else
    {
        // x = -pi/2,
        // 结果不唯一,
        // y - z = atan2(-r01,r00)
        rfYAngle = Math<float>::ATan2(-m_fData[0][1], m_fData[0][0]);
        rfXAngle = -Math<float>::HALF_PI;
        rfZAngle = 0.0f;

        return false;
    }
}
//----------------------------------------------------------------------------
bool Matrix3f::ToEulerAnglesYZX(float& rfYAngle, float& rfZAngle, 
    float& rfXAngle) const
{
    // R = Ry * Rz * Rx
    //   =  cy*cz           cx*cy*sz+sx*sy  cy*sx*sz-cx*sy
    //     -sz              cx*cz           cz*sx
    //      cz*sy           cx*sy*sz-cy*sx  sx*sy*sz+cx*cy
    //
    // 如果z = pi/2,则sz = 1,cz = 0
    // R =  0            cx*cy+sx*sy  cy*sx-cx*sy
    //     -1            0            0
    //      0            cx*sy-cy*sx  sx*sy+cx*cy
    //   =  0            cos(x-y)    sin(x-y)
    //     -1            0           0
    //      0           -sin(x-y)    cos(x-y)
    //
    // 如果z = -pi/2,则sz = -1,cz = 0
    // R = 0           -cx*cy+sx*sy -cy*sx-cx*sy
    //     1            0            0
    //     0           -cx*sy-cy*sx -sx*sy+cx*cy
    //   =  0           -cos(x+y)    -sin(x+y)
    //      1            0            0
    //      0           -sin(x+y)     cos(x+y)

    if( m_fData[1][0] > -1.0f )
    {
        if( m_fData[1][0] < 1.0f )
        {
            rfYAngle = Math<float>::ATan2(m_fData[2][0], m_fData[0][0]);
            rfZAngle = (float)asin(-(double)m_fData[1][0]);
            rfXAngle = Math<float>::ATan2(m_fData[1][2], m_fData[1][1]);

            return true;
        }
        else
        {
            // z = -pi/2,
            // 结果不唯一,
            // x + y = atan2(-r21,r22)
            rfYAngle = Math<float>::ATan2(-m_fData[2][1], m_fData[2][2]);
            rfZAngle = -Math<float>::HALF_PI;
            rfXAngle = 0.0f;

            return false;
        }
    }
    else
    {
        // z = pi/2,
        // 结果不唯一,
        // x - y = atan2(-r21,r22)
        rfYAngle = -Math<float>::ATan2(-m_fData[2][1], m_fData[2][2]);
        rfZAngle = Math<float>::HALF_PI;
        rfXAngle = 0.0f;

        return false;
    }
}
//----------------------------------------------------------------------------
bool Matrix3f::ToEulerAnglesZXY(float& rfZAngle, float& rfXAngle, 
    float& rfYAngle) const
{
    // R = Rz * Rx * Ry
    //   =  cy*cz+sx*sy*sz  cx*sz          -cz*sy+cy*sx*sz
    //     -cy*sz+cz*sx*sy  cx*cz           sy*sz+cy*cz*sx
    //      cx*sy          -sx              cx*cy
    //
    // 如果x = pi/2,则sx = 1,cx = 0
    // R =  cy*cz+sy*sz  0           -cz*sy+cy*sz
    //     -cy*sz+cz*sy  0            sy*sz+cy*cz
    //      0           -1            0
    //   =  cos(y-z)     0          -sin(y-z)
    //      sin(y-z)     0           cos(y-z)
    //      0           -1           0
    //
    // 如果x = -pi/2,则sx = -1,cx = 0
    // R =  cy*cz-sy*sz  0           -cz*sy-cy*sz
    //     -cy*sz-cz*sy  0            sy*sz-cy*cz
    //      0            1            0
    //   =  cos(y+z)     0           -sin(y+z)
    //     -sin(y+z)     0           -cos(y+z)
    //      0            1            0

    if( m_fData[2][1] > -1.0f )
    {
        if( m_fData[2][1] < 1.0f )
        {
            rfZAngle = Math<float>::ATan2(m_fData[0][1], m_fData[1][1]);
            rfXAngle = (float)asin(-(double)m_fData[2][1]);
            rfYAngle = Math<float>::ATan2(m_fData[2][0], m_fData[2][2]);

            return true;
        }
        else
        {
            // x = -pi/2,
            // 结果不唯一,
            // y + z = atan(-r02,r00)
            rfZAngle = Math<float>::ATan2(-m_fData[0][2], m_fData[0][0]);
            rfXAngle = -Math<float>::HALF_PI;
            rfYAngle = 0.0f;

            return false;
        }
    }
    else
    {
        // x = pi/2,
        // 结果不唯一,
        // y - z = atan2(-r02,r00)
        rfZAngle = -Math<float>::ATan2(-m_fData[0][2], m_fData[0][0]);
        rfXAngle = Math<float>::HALF_PI;
        rfYAngle = 0.0f;

        return false;
    }
}
//----------------------------------------------------------------------------
bool Matrix3f::ToEulerAnglesZYX(float& rfZAngle, float& rfYAngle, 
    float& rfXAngle) const
{
    // R = Rz * Ry * Rx
    //   =  cy*cz           cx*sz+cz*sx*sy  sx*sz-cx*cz*sy
    //     -cy*sz           cx*cz-sx*sy*sz  cz*sx+cx*sy*sz
    //      sy             -cy*sx           cx*cy
    //
    // 如果y = pi/2,则sy = 1,cy = 0
    // R = 0            cx*sz+cz*sx  sx*sz-cx*cz
    //     0            cx*cz-sx*sz  cz*sx+cx*sz
    //     1            0            0
    //   = 0            sin(x+z)    -cos(x+z)
    //     0            cos(x+z)     sin(x+z)
    //     1            0            0
    //
    // 如果y = -pi/2,则sy = -1,cy = 0
    // R =  0            cx*sz-cz*sx  sx*sz+cx*cz
    //      0            cx*cz+sx*sz  cz*sx-cx*sz
    //     -1            0            0
    //   =  0            sin(z-x)     cos(z-x)
    //      0            cos(z-x)    -sin(z-x)
    //     -1            0            0

    if( m_fData[2][0] > -1.0f )
    {
        if( m_fData[2][0] < 1.0f )
        {
            rfZAngle = Math<float>::ATan2(-m_fData[1][0], m_fData[0][0]);
            rfYAngle = (float)asin((double)m_fData[2][0]);
            rfXAngle = Math<float>::ATan2(-m_fData[2][1], m_fData[2][2]);

            return true;
        }
        else
        {
            // y = pi/2,
            // 结果不唯一,
            // x + z = atan2(r01,-r02)
            rfZAngle = Math<float>::ATan2(m_fData[0][1], -m_fData[0][2]);
            rfYAngle = Math<float>::HALF_PI;
            rfXAngle = 0.0f;

            return false;
        }
    }
    else
    {
        // y = -pi/2,
        // 结果不唯一,
        // z - x = atan2(r01,r02)
        rfZAngle = Math<float>::ATan2(m_fData[0][1], m_fData[0][2]);
        rfYAngle = -Math<float>::HALF_PI;
        rfXAngle = 0.0f;

        return false;
    }
}
//----------------------------------------------------------------------------
Matrix3f Swing::operator*(float fLhsScalar, const Matrix3f& rRhsMat)
{
    return rRhsMat * fLhsScalar;
}
//----------------------------------------------------------------------------
Vector3f Swing::operator*(const Vector3f& rLhsVec, const Matrix3f& rRhsMat)
{
    return Vector3f(
        rLhsVec[0]*rRhsMat[0][0] + rLhsVec[1]*rRhsMat[1][0] + 
        rLhsVec[2]*rRhsMat[2][0],
        rLhsVec[0]*rRhsMat[0][1] + rLhsVec[1]*rRhsMat[1][1] + 
        rLhsVec[2]*rRhsMat[2][1],
        rLhsVec[0]*rRhsMat[0][2] + rLhsVec[1]*rRhsMat[1][2] + 
        rLhsVec[2]*rRhsMat[2][2]);
}
//----------------------------------------------------------------------------
void Matrix3f::Orthonormalize()
{
    // 待检查
    // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
    // M = [m0|m1|m2], then orthonormal output matrix is Q = [q0|q1|q2],
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.

    // compute q0
    float fInvLength = Math<float>::InvSqrt(m_fData[0][0]*m_fData[0][0] +
        m_fData[1][0]*m_fData[1][0] + m_fData[2][0]*m_fData[2][0]);

    m_fData[0][0] *= fInvLength;
    m_fData[1][0] *= fInvLength;
    m_fData[2][0] *= fInvLength;

    // compute q1
    float fDot0 = m_fData[0][0]*m_fData[0][1] + m_fData[1][0]*m_fData[1][1] +
        m_fData[2][0]*m_fData[2][1];

    m_fData[0][1] -= fDot0*m_fData[0][0];
    m_fData[1][1] -= fDot0*m_fData[1][0];
    m_fData[2][1] -= fDot0*m_fData[2][0];

    fInvLength = Math<float>::InvSqrt(m_fData[0][1]*m_fData[0][1] +
        m_fData[1][1]*m_fData[1][1] + m_fData[2][1]*m_fData[2][1]);

    m_fData[0][1] *= fInvLength;
    m_fData[1][1] *= fInvLength;
    m_fData[2][1] *= fInvLength;

    // compute q2
    float fDot1 = m_fData[0][1]*m_fData[0][2] + m_fData[1][1]*m_fData[1][2] +
        m_fData[2][1]*m_fData[2][2];

    fDot0 = m_fData[0][0]*m_fData[0][2] + m_fData[1][0]*m_fData[1][2] +
        m_fData[2][0]*m_fData[2][2];

    m_fData[0][2] -= fDot0*m_fData[0][0] + fDot1*m_fData[0][1];
    m_fData[1][2] -= fDot0*m_fData[1][0] + fDot1*m_fData[1][1];
    m_fData[2][2] -= fDot0*m_fData[2][0] + fDot1*m_fData[2][1];

    fInvLength = Math<float>::InvSqrt(m_fData[0][2]*m_fData[0][2] +
        m_fData[1][2]*m_fData[1][2] + m_fData[2][2]*m_fData[2][2]);

    m_fData[0][2] *= fInvLength;
    m_fData[1][2] *= fInvLength;
    m_fData[2][2] *= fInvLength;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 双精度3阶方阵类
//----------------------------------------------------------------------------

const Matrix3d Matrix3d::ZERO(0.0, 0.0, 0.0,
                              0.0, 0.0, 0.0,
                              0.0, 0.0, 0.0);
const Matrix3d Matrix3d::IDENTITY(1.0, 0.0, 0.0,
                                  0.0, 1.0, 0.0,
                                  0.0, 0.0, 1.0);

//----------------------------------------------------------------------------
Matrix3d::Matrix3d()
{
    Zero();
}
//----------------------------------------------------------------------------
Matrix3d::Matrix3d(const Matrix3d& rMat)
{
    memcpy(m_dData, rMat.m_dData, /*12*/9*sizeof(double));
}
//----------------------------------------------------------------------------
Matrix3d::Matrix3d(double dM11, double dM12, double dM13, 
                   double dM21, double dM22, double dM23, 
                   double dM31, double dM32, double dM33)
{
    m_dData[0][0] = dM11;
    m_dData[0][1] = dM12;
    m_dData[0][2] = dM13;
    //m_dData[0][3] = 0.0;

    m_dData[1][0] = dM21;
    m_dData[1][1] = dM22;
    m_dData[1][2] = dM23;
    //m_dData[1][3] = 0.0;

    m_dData[2][0] = dM31;
    m_dData[2][1] = dM32;
    m_dData[2][2] = dM33;
    //m_dData[2][3] = 0.0;

    //m_dData[3][0] = 0.0;
    //m_dData[3][1] = 0.0;
    //m_dData[3][2] = 0.0;
    //m_dData[3][3] = 0.0;
}
//----------------------------------------------------------------------------
Matrix3d::Matrix3d(const Vector3d& rVecU, const Vector3d& rVecV, 
    const Vector3d& rVecW, bool bIsRow)
{
    Zero();

    if( bIsRow )
	{
        m_dData[0][0] = rVecU[0];
        m_dData[0][1] = rVecU[1];
        m_dData[0][2] = rVecU[2];
        m_dData[1][0] = rVecV[0];
        m_dData[1][1] = rVecV[1];
        m_dData[1][2] = rVecV[2];
        m_dData[2][0] = rVecW[0];
        m_dData[2][1] = rVecW[1];
        m_dData[2][2] = rVecW[2];
    }
	else
    {
        m_dData[0][0] = rVecU[0];
        m_dData[0][1] = rVecV[0];
        m_dData[0][2] = rVecW[0];
        m_dData[1][0] = rVecU[1];
        m_dData[1][1] = rVecV[1];
        m_dData[1][2] = rVecW[1];
        m_dData[2][0] = rVecU[2];
        m_dData[2][1] = rVecV[2];
        m_dData[2][2] = rVecW[2];
	}
}
//----------------------------------------------------------------------------
Matrix3d::Matrix3d(double dM11, double dM22, double dM33)
{
    Zero();

    Diagonal(dM11, dM22, dM33);
}
//----------------------------------------------------------------------------
Matrix3d::Matrix3d(const Vector3d& rAxisVec, double dAngle)
{
    Zero();

    FromAxisAngle(rAxisVec, dAngle);
}
//----------------------------------------------------------------------------
Matrix3d::Matrix3d(const Vector3d& rVecU, const Vector3d& rVecV)
{
    Zero();

    TensorProduct(rVecU, rVecV);
}
//----------------------------------------------------------------------------
Matrix3d::operator const double*() const
{
    return &m_dData[0][0];
}
//----------------------------------------------------------------------------
Matrix3d::operator double*()
{
    return &m_dData[0][0];
}
//----------------------------------------------------------------------------
const double* Matrix3d::operator[](int iCurRow) const
{
    return &m_dData[iCurRow][0];
}
//----------------------------------------------------------------------------
double* Matrix3d::operator[](int iCurRow)
{
    return &m_dData[iCurRow][0];
}
//----------------------------------------------------------------------------
double Matrix3d::operator()(int iCurRow, int iCurCol) const
{
    return m_dData[iCurRow][iCurCol];
}
//----------------------------------------------------------------------------
double& Matrix3d::operator()(int iCurRow, int iCurCol)
{
    return m_dData[iCurRow][iCurCol];
}
//----------------------------------------------------------------------------
Matrix3d& Matrix3d::operator=(const Matrix3d& rMat)
{
    memcpy(m_dData, rMat.m_dData, /*12*/9*sizeof(double));

    return *this;
}
//----------------------------------------------------------------------------
bool Matrix3d::operator==(const Matrix3d& rMat) const
{
    return CompareData(rMat) == 0;
}
//----------------------------------------------------------------------------
bool Matrix3d::operator!=(const Matrix3d& rMat) const
{
    return CompareData(rMat) != 0;
}
//----------------------------------------------------------------------------
bool Matrix3d::operator<(const Matrix3d& rMat) const
{
    return CompareData(rMat) < 0;
}
//----------------------------------------------------------------------------
bool Matrix3d::operator<=(const Matrix3d& rMat) const
{
    return CompareData(rMat) <= 0;
}
//----------------------------------------------------------------------------
bool Matrix3d::operator>(const Matrix3d& rMat) const
{
    return CompareData(rMat) > 0;
}
//----------------------------------------------------------------------------
bool Matrix3d::operator>=(const Matrix3d& rMat) const
{
    return CompareData(rMat) >= 0;
}
//----------------------------------------------------------------------------
Matrix3d Matrix3d::operator+(const Matrix3d& rRhsMat) const
{
    Matrix3d ResMat;

    ResMat.m_dData[0][0] = m_dData[0][0] + rRhsMat.m_dData[0][0];
    ResMat.m_dData[0][1] = m_dData[0][1] + rRhsMat.m_dData[0][1];
    ResMat.m_dData[0][2] = m_dData[0][2] + rRhsMat.m_dData[0][2];

    ResMat.m_dData[1][0] = m_dData[1][0] + rRhsMat.m_dData[1][0];
    ResMat.m_dData[1][1] = m_dData[1][1] + rRhsMat.m_dData[1][1];
    ResMat.m_dData[1][2] = m_dData[1][2] + rRhsMat.m_dData[1][2];

    ResMat.m_dData[2][0] = m_dData[2][0] + rRhsMat.m_dData[2][0];
    ResMat.m_dData[2][1] = m_dData[2][1] + rRhsMat.m_dData[2][1];
    ResMat.m_dData[2][2] = m_dData[2][2] + rRhsMat.m_dData[2][2];

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix3d Matrix3d::operator-(const Matrix3d& rRhsMat) const
{
    Matrix3d ResMat;

    ResMat.m_dData[0][0] = m_dData[0][0] - rRhsMat.m_dData[0][0];
    ResMat.m_dData[0][1] = m_dData[0][1] - rRhsMat.m_dData[0][1];
    ResMat.m_dData[0][2] = m_dData[0][2] - rRhsMat.m_dData[0][2];

    ResMat.m_dData[1][0] = m_dData[1][0] - rRhsMat.m_dData[1][0];
    ResMat.m_dData[1][1] = m_dData[1][1] - rRhsMat.m_dData[1][1];
    ResMat.m_dData[1][2] = m_dData[1][2] - rRhsMat.m_dData[1][2];

    ResMat.m_dData[2][0] = m_dData[2][0] - rRhsMat.m_dData[2][0];
    ResMat.m_dData[2][1] = m_dData[2][1] - rRhsMat.m_dData[2][1];
    ResMat.m_dData[2][2] = m_dData[2][2] - rRhsMat.m_dData[2][2];

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix3d Matrix3d::operator*(const Matrix3d& rRhsMat) const
{
    Matrix3d ResMat;

#ifdef _SIMD
    // 待实现.
    // 尚未支持SIMD.
    SE_ASSERT( false );
#else
    ResMat.m_dData[0][0] = m_dData[0][0]*rRhsMat.m_dData[0][0] + 
                           m_dData[0][1]*rRhsMat.m_dData[1][0] + 
                           m_dData[0][2]*rRhsMat.m_dData[2][0];
    ResMat.m_dData[0][1] = m_dData[0][0]*rRhsMat.m_dData[0][1] + 
                           m_dData[0][1]*rRhsMat.m_dData[1][1] + 
                           m_dData[0][2]*rRhsMat.m_dData[2][1];
    ResMat.m_dData[0][2] = m_dData[0][0]*rRhsMat.m_dData[0][2] + 
                           m_dData[0][1]*rRhsMat.m_dData[1][2] + 
                           m_dData[0][2]*rRhsMat.m_dData[2][2];

    ResMat.m_dData[1][0] = m_dData[1][0]*rRhsMat.m_dData[0][0] + 
                           m_dData[1][1]*rRhsMat.m_dData[1][0] + 
                           m_dData[1][2]*rRhsMat.m_dData[2][0];
    ResMat.m_dData[1][1] = m_dData[1][0]*rRhsMat.m_dData[0][1] + 
                           m_dData[1][1]*rRhsMat.m_dData[1][1] + 
                           m_dData[1][2]*rRhsMat.m_dData[2][1];
    ResMat.m_dData[1][2] = m_dData[1][0]*rRhsMat.m_dData[0][2] + 
                           m_dData[1][1]*rRhsMat.m_dData[1][2] + 
                           m_dData[1][2]*rRhsMat.m_dData[2][2];

    ResMat.m_dData[2][0] = m_dData[2][0]*rRhsMat.m_dData[0][0] + 
                           m_dData[2][1]*rRhsMat.m_dData[1][0] + 
                           m_dData[2][2]*rRhsMat.m_dData[2][0];
    ResMat.m_dData[2][1] = m_dData[2][0]*rRhsMat.m_dData[0][1] + 
                           m_dData[2][1]*rRhsMat.m_dData[1][1] + 
                           m_dData[2][2]*rRhsMat.m_dData[2][1];
    ResMat.m_dData[2][2] = m_dData[2][0]*rRhsMat.m_dData[0][2] + 
                           m_dData[2][1]*rRhsMat.m_dData[1][2] + 
                           m_dData[2][2]*rRhsMat.m_dData[2][2];
#endif

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix3d Matrix3d::operator*(double dScalar) const
{
    Matrix3d ResMat;

    ResMat.m_dData[0][0] = m_dData[0][0] * dScalar;
    ResMat.m_dData[0][1] = m_dData[0][1] * dScalar;
    ResMat.m_dData[0][2] = m_dData[0][2] * dScalar;

    ResMat.m_dData[1][0] = m_dData[1][0] * dScalar;
    ResMat.m_dData[1][1] = m_dData[1][1] * dScalar;
    ResMat.m_dData[1][2] = m_dData[1][2] * dScalar;

    ResMat.m_dData[2][0] = m_dData[2][0] * dScalar;
    ResMat.m_dData[2][1] = m_dData[2][1] * dScalar;
    ResMat.m_dData[2][2] = m_dData[2][2] * dScalar;

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix3d Matrix3d::operator/(double dScalar) const
{
    // 注意除数不能为0
    Matrix3d ResMat;
    double dInvScalar = 1.0 / dScalar;

    ResMat.m_dData[0][0] = m_dData[0][0] * dInvScalar;
    ResMat.m_dData[0][1] = m_dData[0][1] * dInvScalar;
    ResMat.m_dData[0][2] = m_dData[0][2] * dInvScalar;

    ResMat.m_dData[1][0] = m_dData[1][0] * dInvScalar;
    ResMat.m_dData[1][1] = m_dData[1][1] * dInvScalar;
    ResMat.m_dData[1][2] = m_dData[1][2] * dInvScalar;

    ResMat.m_dData[2][0] = m_dData[2][0] * dInvScalar;
    ResMat.m_dData[2][1] = m_dData[2][1] * dInvScalar;
    ResMat.m_dData[2][2] = m_dData[2][2] * dInvScalar;

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix3d Matrix3d::operator-() const
{
    Matrix3d ResMat;

    ResMat.m_dData[0][0] = -m_dData[0][0];
    ResMat.m_dData[0][1] = -m_dData[0][1];
    ResMat.m_dData[0][2] = -m_dData[0][2];

    ResMat.m_dData[1][0] = -m_dData[1][0];
    ResMat.m_dData[1][1] = -m_dData[1][1];
    ResMat.m_dData[1][2] = -m_dData[1][2];

    ResMat.m_dData[2][0] = -m_dData[2][0];
    ResMat.m_dData[2][1] = -m_dData[2][1];
    ResMat.m_dData[2][2] = -m_dData[2][2];

    return ResMat;
}
//----------------------------------------------------------------------------
Matrix3d& Matrix3d::operator+=(const Matrix3d& rRhsMat)
{
	m_dData[0][0] += rRhsMat.m_dData[0][0];
    m_dData[0][1] += rRhsMat.m_dData[0][1];
    m_dData[0][2] += rRhsMat.m_dData[0][2];

    m_dData[1][0] += rRhsMat.m_dData[1][0];
    m_dData[1][1] += rRhsMat.m_dData[1][1];
    m_dData[1][2] += rRhsMat.m_dData[1][2];

    m_dData[2][0] += rRhsMat.m_dData[2][0];
    m_dData[2][1] += rRhsMat.m_dData[2][1];
    m_dData[2][2] += rRhsMat.m_dData[2][2];

    return *this;
}
//----------------------------------------------------------------------------
Matrix3d& Matrix3d::operator-=(const Matrix3d& rRhsMat)
{
	m_dData[0][0] -= rRhsMat.m_dData[0][0];
    m_dData[0][1] -= rRhsMat.m_dData[0][1];
    m_dData[0][2] -= rRhsMat.m_dData[0][2];

    m_dData[1][0] -= rRhsMat.m_dData[1][0];
    m_dData[1][1] -= rRhsMat.m_dData[1][1];
    m_dData[1][2] -= rRhsMat.m_dData[1][2];

    m_dData[2][0] -= rRhsMat.m_dData[2][0];
    m_dData[2][1] -= rRhsMat.m_dData[2][1];
    m_dData[2][2] -= rRhsMat.m_dData[2][2];

    return *this;
}
//----------------------------------------------------------------------------
Matrix3d& Matrix3d::operator*=(double dScalar)
{
	m_dData[0][0] *= dScalar;
    m_dData[0][1] *= dScalar;
    m_dData[0][2] *= dScalar;

    m_dData[1][0] *= dScalar;
    m_dData[1][1] *= dScalar;
    m_dData[1][2] *= dScalar;

    m_dData[2][0] *= dScalar;
    m_dData[2][1] *= dScalar;
    m_dData[2][2] *= dScalar;

    return *this;
}
//----------------------------------------------------------------------------
Matrix3d& Matrix3d::operator/=(double dScalar)
{
    // 注意除数不能为0
    double dInvScalar = 1.0 / dScalar;
	m_dData[0][0] *= dInvScalar;
    m_dData[0][1] *= dInvScalar;
    m_dData[0][2] *= dInvScalar;

    m_dData[1][0] *= dInvScalar;
    m_dData[1][1] *= dInvScalar;
    m_dData[1][2] *= dInvScalar;

    m_dData[2][0] *= dInvScalar;
    m_dData[2][1] *= dInvScalar;
    m_dData[2][2] *= dInvScalar;

    return *this;
}
//----------------------------------------------------------------------------
Vector3d Matrix3d::operator*(const Vector3d& rRhsVec) const
{
    Vector3d ResVec;
   
    ResVec[0] = m_dData[0][0]*rRhsVec[0] + m_dData[0][1]*rRhsVec[1] + 
        m_dData[0][2]*rRhsVec[2];
    ResVec[1] = m_dData[1][0]*rRhsVec[0] + m_dData[1][1]*rRhsVec[1] + 
        m_dData[1][2]*rRhsVec[2];
    ResVec[2] = m_dData[2][0]*rRhsVec[0] + m_dData[2][1]*rRhsVec[1] + 
        m_dData[2][2]*rRhsVec[2];

    return ResVec;
}
//----------------------------------------------------------------------------
void Matrix3d::Transpose()
{
    Matrix3d tempMat;
	GetTranspose(tempMat);
	*this = tempMat;
}
//----------------------------------------------------------------------------
void Matrix3d::Inverse()
{
    Matrix3d tempMat;
	GetInverse(tempMat);
	*this = tempMat;
}
//----------------------------------------------------------------------------
Matrix3d& Matrix3d::FromEulerAnglesXYZ(double dYAngle, double dPAngle, 
    double dRAngle)
{
    double dCos, dSin;

    dCos = Math<double>::Cos(dYAngle);
    dSin = Math<double>::Sin(dYAngle);
    Matrix3d RotXMat(
        1.0,0.0,0.0,
        0.0,dCos,dSin,
        0.0,-dSin,dCos);

    dCos = Math<double>::Cos(dPAngle);
    dSin = Math<double>::Sin(dPAngle);
    Matrix3d RotYMat(
        dCos,0.0,-dSin,
        0.0,1.0,0.0,
        dSin,0.0,dCos);

    dCos = Math<double>::Cos(dRAngle);
    dSin = Math<double>::Sin(dRAngle);
    Matrix3d RotZMat(
        dCos,dSin,0.0,
        -dSin,dCos,0.0,
        0.0,0.0,1.0);

    *this = RotXMat*(RotYMat*RotZMat);
    return *this;
}
//----------------------------------------------------------------------------
Matrix3d& Matrix3d::FromEulerAnglesXZY(double dYAngle, double dPAngle, 
    double dRAngle)
{
    double dCos, dSin;

    dCos = Math<double>::Cos(dYAngle);
    dSin = Math<double>::Sin(dYAngle);
    Matrix3d RotXMat(
        1.0,0.0,0.0,
        0.0,dCos,dSin,
        0.0,-dSin,dCos);

    dCos = Math<double>::Cos(dPAngle);
    dSin = Math<double>::Sin(dPAngle);
    Matrix3d RotZMat(
        dCos,dSin,0.0,
        -dSin,dCos,0.0,
        0.0,0.0,1.0);

    dCos = Math<double>::Cos(dRAngle);
    dSin = Math<double>::Sin(dRAngle);
    Matrix3d RotYMat(
        dCos,0.0,-dSin,
        0.0,1.0,0.0,
        dSin,0.0,dCos);

    *this = RotXMat*(RotZMat*RotYMat);
    return *this;
}
//----------------------------------------------------------------------------
Matrix3d& Matrix3d::FromEulerAnglesYXZ(double dYAngle, double dPAngle, 
    double dRAngle)
{
    double dCos, dSin;

    dCos = Math<double>::Cos(dYAngle);
    dSin = Math<double>::Sin(dYAngle);
    Matrix3d RotYMat(
        dCos,0.0,-dSin,
        0.0,1.0,0.0,
        dSin,0.0,dCos);

    dCos = Math<double>::Cos(dPAngle);
    dSin = Math<double>::Sin(dPAngle);
    Matrix3d RotXMat(
        1.0,0.0,0.0,
        0.0,dCos,dSin,
        0.0,-dSin,dCos);

    dCos = Math<double>::Cos(dRAngle);
    dSin = Math<double>::Sin(dRAngle);
    Matrix3d RotZMat(
        dCos,dSin,0.0,
        -dSin,dCos,0.0,
        0.0,0.0,1.0);

    *this = RotYMat*(RotXMat*RotZMat);
    return *this;
}
//----------------------------------------------------------------------------
Matrix3d& Matrix3d::FromEulerAnglesYZX(double dYAngle, double dPAngle, 
    double dRAngle)
{
    double dCos, dSin;

    dCos = Math<double>::Cos(dYAngle);
    dSin = Math<double>::Sin(dYAngle);
    Matrix3d RotYMat(
        dCos,0.0,-dSin,
        0.0,1.0,0.0,
        dSin,0.0,dCos);

    dCos = Math<double>::Cos(dPAngle);
    dSin = Math<double>::Sin(dPAngle);
    Matrix3d RotZMat(
        dCos,dSin,0.0,
        -dSin,dCos,0.0,
        0.0,0.0,1.0);

    dCos = Math<double>::Cos(dRAngle);
    dSin = Math<double>::Sin(dRAngle);
    Matrix3d RotXMat(
        1.0,0.0,0.0,
        0.0,dCos,dSin,
        0.0,-dSin,dCos);

    *this = RotYMat*(RotZMat*RotXMat);
    return *this;
}
//----------------------------------------------------------------------------
Matrix3d& Matrix3d::FromEulerAnglesZXY(double dYAngle, double dPAngle, 
    double dRAngle)
{
    double dCos, dSin;

    dCos = Math<double>::Cos(dYAngle);
    dSin = Math<double>::Sin(dYAngle);
    Matrix3d RotZMat(
        dCos,dSin,0.0,
        -dSin,dCos,0.0,
        0.0,0.0,1.0);

    dCos = Math<double>::Cos(dPAngle);
    dSin = Math<double>::Sin(dPAngle);
    Matrix3d RotXMat(
        1.0,0.0,0.0,
        0.0,dCos,dSin,
        0.0,-dSin,dCos);

    dCos = Math<double>::Cos(dRAngle);
    dSin = Math<double>::Sin(dRAngle);
    Matrix3d RotYMat(
        dCos,0.0,-dSin,
        0.0,1.0,0.0,
        dSin,0.0,dCos);

    *this = RotZMat*(RotXMat*RotYMat);
    return *this;
}
//----------------------------------------------------------------------------
Matrix3d& Matrix3d::FromEulerAnglesZYX(double dYAngle, double dPAngle, 
    double dRAngle)
{
    double dCos, dSin;

    dCos = Math<double>::Cos(dYAngle);
    dSin = Math<double>::Sin(dYAngle);
    Matrix3d RotZMat(
        dCos,dSin,0.0,
        -dSin,dCos,0.0,
        0.0,0.0,1.0);

    dCos = Math<double>::Cos(dPAngle);
    dSin = Math<double>::Sin(dPAngle);
    Matrix3d RotYMat(
        dCos,0.0,-dSin,
        0.0,1.0,0.0,
        dSin,0.0,dCos);

    dCos = Math<double>::Cos(dRAngle);
    dSin = Math<double>::Sin(dRAngle);
    Matrix3d RotXMat(
        1.0,0.0,0.0,
        0.0,dCos,dSin,
        0.0,-dSin,dCos);

    *this = RotZMat*(RotYMat*RotXMat);
    return *this;
}
//----------------------------------------------------------------------------
bool Matrix3d::ToEulerAnglesXYZ(double& rdXAngle, double& rdYAngle, 
    double& rdZAngle) const
{
    // R = Rx * Ry * Rz
    //   = cy*cz           cy*sz          -sy
    //     cz*sx*sy-cx*sz  cx*cz+sx*sy*sz  sx*cy
    //     cx*cz*sy+sx*sz  cx*sy*sz-cz*sx  cx*cy
    //
    // 如果y = pi/2,则sy = 1,cy = 0
    // R = 0            0           -1
    //     cz*sx-cx*sz  cx*cz+sx*sz  0
    //     cx*cz+sx*sz  cx*sz-cz*sx  0
    //   = 0            0           -1
    //     sin(x-z)     cos(x-z)     0
    //     cos(x-z)     -sin(x-z)    0
    //
    // 如果y = -pi/2,则sy = -1,cy = 0
    // R =  0            0            1
    //     -cz*sx-cx*sz  cx*cz-sx*sz  0
    //     -cx*cz+sx*sz -cx*sz-cz*sx  0
    //   =  0            0            1
    //     -sin(x+z)     cos(x+z)     0
    //     -cos(x+z)    -sin(x+z)     0

    if( m_dData[0][2] > -1.0 )
    {
        if( m_dData[0][2] < 1.0 )
        {
            rdXAngle = Math<double>::ATan2(m_dData[1][2], m_dData[2][2]);
            rdYAngle = asin(-m_dData[0][2]);
            rdZAngle = Math<double>::ATan2(m_dData[0][1], m_dData[0][0]);

            return true;
        }
        else
        {
            // y = -pi/2,
            // 结果不唯一,
            // x + z = atan2(r10,r11)
            rdXAngle = Math<double>::ATan2(-m_dData[1][0], m_dData[1][1]);
            rdYAngle = -Math<double>::HALF_PI;
            rdZAngle = 0.0;

            return false;
        }
    }
    else
    {
        // y = pi/2,
        // 结果不唯一,
        // x - z = atan2(r10,r11)
        rdXAngle = Math<double>::ATan2(m_dData[1][0], m_dData[1][1]);
        rdYAngle = Math<double>::HALF_PI;
        rdZAngle = 0.0;

        return false;
    }
}
//----------------------------------------------------------------------------
bool Matrix3d::ToEulerAnglesXZY(double& rdXAngle, double& rdZAngle, 
    double& rdYAngle) const
{
    // R = Rx * Rz * Ry
    //   =  cy*cz           sz             -cz*sy
    //     -cx*cy*sz+sx*sy  cx*cz           cx*sy*sz+cy*sx
    //      cy*sx*sz+cx*sy -cz*sx          -sx*sy*sz+cx*cy
    //
    // 如果z = pi/2,则sz = 1,cz = 0
    // R = 0            1            0
    //     sx*sy-cx*cy  0            cx*sy+cy*sx
    //     cy*sx+cx*sy  0            cx*cy-sx*sy
    //   =  0            1           0
    //     -cos(x+y)     0           sin(x+y)
    //      sin(x+y)     0           cos(x+y)
    //
    // 如果z = -pi/2,则sz = -1,cz = 0
    // R =  0           -1            0
    //      cx*cy+sx*sy  0           -cx*sy+cy*sx
    //     -cy*sx+cx*sy  0            sx*sz+cx*cy
    //   =  0           -1            0
    //      cos(x-y)     0            sin(x-y)
    //     -sin(x-y)     0            cos(x-y)

    if( m_dData[0][1] > -1.0 )
    {
        if( m_dData[0][1] < 1.0 )
        {
            rdXAngle = Math<double>::ATan2(-m_dData[2][1], m_dData[1][1]);
            rdZAngle = asin(m_dData[0][1]);
            rdYAngle = Math<double>::ATan2(-m_dData[0][2], m_dData[0][0]);

            return true;
        }
        else
        {
            // z = pi/2,
            // 结果不唯一,
            // x + y = atan2(r20,r22)
            rdXAngle = Math<double>::ATan2(m_dData[2][0], m_dData[2][2]);
            rdZAngle = Math<double>::HALF_PI;
            rdYAngle = 0.0;

            return false;
        }
    }
    else
    {
        // z = -pi/2,
        // 结果不唯一,
        // x - y = atan2(-r20,r22)
        rdXAngle = Math<double>::ATan2(-m_dData[2][0], m_dData[2][2]);
        rdZAngle = -Math<double>::HALF_PI;
        rdYAngle = 0.0;

        return false;
    }
}
//----------------------------------------------------------------------------
bool Matrix3d::ToEulerAnglesYXZ(double& rdYAngle, double& rdXAngle, 
    double& rdZAngle) const
{
    // R = Ry * Rx * Rz
    //   =  cy*cz-sx*sy*sz  cy*sz+cz*sx*sy -cx*sy
    //     -cx*sz           cx*cz           sx
    //      cz*sy+cy*sx*sz  sy*sz-cy*cz*sx  cx*cy
    //
    // 如果x = pi/2,则sx = 1,cx = 0
    // R = cy*cz-sy*sz  cy*sz+cz*sy  0
    //     0            0            1
    //     cz*sy+cy*sz  sy*sz-cy*cz  0
    //   = cos(y+z)     sin(y+z)    0
    //     0            0           1
    //     sin(y+z)    -cos(y+z)    0
    //
    // 如果x = -pi/2,则sx = -1,cx = 0
    // R = cy*cz+sy*sz  cy*sz-cz*sy  0
    //     0            0           -1
    //     cz*sy-cy*sz  sy*sz+cy*cz  0
    //   =  cos(y-z)    -sin(y-z)     0
    //      0            0           -1
    //      sin(y-z)     cos(y-z)     0

    if( m_dData[1][2] > -1.0 )
    {
        if( m_dData[1][2] < 1.0 )
        {
            rdYAngle = Math<double>::ATan2(-m_dData[0][2], m_dData[2][2]);
            rdXAngle = asin(m_dData[1][2]);
            rdZAngle = Math<double>::ATan2(-m_dData[1][0], m_dData[1][1]);

            return true;
        }
        else
        {
            // x = pi/2,
            // 结果不唯一,
            // y + z = atan2(r01,r00)
            rdYAngle = Math<double>::ATan2(m_dData[0][1], m_dData[0][0]);
            rdXAngle = Math<double>::HALF_PI;
            rdZAngle = 0.0;

            return false;
        }
    }
    else
    {
        // x = -pi/2,
        // 结果不唯一,
        // y - z = atan2(-r01,r00)
        rdYAngle = Math<double>::ATan2(-m_dData[0][1], m_dData[0][0]);
        rdXAngle = -Math<double>::HALF_PI;
        rdZAngle = 0.0;

        return false;
    }
}
//----------------------------------------------------------------------------
bool Matrix3d::ToEulerAnglesYZX(double& rdYAngle, double& rdZAngle, 
    double& rdXAngle) const
{
    // R = Ry * Rz * Rx
    //   =  cy*cz           cx*cy*sz+sx*sy  cy*sx*sz-cx*sy
    //     -sz              cx*cz           cz*sx
    //      cz*sy           cx*sy*sz-cy*sx  sx*sy*sz+cx*cy
    //
    // 如果z = pi/2,则sz = 1,cz = 0
    // R =  0            cx*cy+sx*sy  cy*sx-cx*sy
    //     -1            0            0
    //      0            cx*sy-cy*sx  sx*sy+cx*cy
    //   =  0            cos(x-y)    sin(x-y)
    //     -1            0           0
    //      0           -sin(x-y)    cos(x-y)
    //
    // 如果z = -pi/2,则sz = -1,cz = 0
    // R = 0           -cx*cy+sx*sy -cy*sx-cx*sy
    //     1            0            0
    //     0           -cx*sy-cy*sx -sx*sy+cx*cy
    //   =  0           -cos(x+y)    -sin(x+y)
    //      1            0            0
    //      0           -sin(x+y)     cos(x+y)

    if( m_dData[1][0] > -1.0 )
    {
        if( m_dData[1][0] < 1.0 )
        {
            rdYAngle = Math<double>::ATan2(m_dData[2][0], m_dData[0][0]);
            rdZAngle = asin(-m_dData[1][0]);
            rdXAngle = Math<double>::ATan2(m_dData[1][2], m_dData[1][1]);

            return true;
        }
        else
        {
            // z = -pi/2,
            // 结果不唯一,
            // x + y = atan2(-r21,r22)
            rdYAngle = Math<double>::ATan2(-m_dData[2][1], m_dData[2][2]);
            rdZAngle = -Math<double>::HALF_PI;
            rdXAngle = 0.0;

            return false;
        }
    }
    else
    {
        // z = pi/2,
        // 结果不唯一,
        // x - y = atan2(-r21,r22)
        rdYAngle = -Math<double>::ATan2(-m_dData[2][1], m_dData[2][2]);
        rdZAngle = Math<double>::HALF_PI;
        rdXAngle = 0.0;

        return false;
    }
}
//----------------------------------------------------------------------------
bool Matrix3d::ToEulerAnglesZXY(double& rdZAngle, double& rdXAngle, 
    double& rdYAngle) const
{
    // R = Rz * Rx * Ry
    //   =  cy*cz+sx*sy*sz  cx*sz          -cz*sy+cy*sx*sz
    //     -cy*sz+cz*sx*sy  cx*cz           sy*sz+cy*cz*sx
    //      cx*sy          -sx              cx*cy
    //
    // 如果x = pi/2,则sx = 1,cx = 0
    // R =  cy*cz+sy*sz  0           -cz*sy+cy*sz
    //     -cy*sz+cz*sy  0            sy*sz+cy*cz
    //      0           -1            0
    //   =  cos(y-z)     0          -sin(y-z)
    //      sin(y-z)     0           cos(y-z)
    //      0           -1           0
    //
    // 如果x = -pi/2,则sx = -1,cx = 0
    // R =  cy*cz-sy*sz  0           -cz*sy-cy*sz
    //     -cy*sz-cz*sy  0            sy*sz-cy*cz
    //      0            1            0
    //   =  cos(y+z)     0           -sin(y+z)
    //     -sin(y+z)     0           -cos(y+z)
    //      0            1            0

    if( m_dData[2][1] > -1.0 )
    {
        if( m_dData[2][1] < 1.0 )
        {
            rdZAngle = Math<double>::ATan2(m_dData[0][1], m_dData[1][1]);
            rdXAngle = asin(-m_dData[2][1]);
            rdYAngle = Math<double>::ATan2(m_dData[2][0], m_dData[2][2]);

            return true;
        }
        else
        {
            // x = -pi/2,
            // 结果不唯一,
            // y + z = atan(-r02,r00)
            rdZAngle = Math<double>::ATan2(-m_dData[0][2], m_dData[0][0]);
            rdXAngle = -Math<double>::HALF_PI;
            rdYAngle = 0.0;

            return false;
        }
    }
    else
    {
        // x = pi/2,
        // 结果不唯一,
        // y - z = atan2(-r02,r00)
        rdZAngle = -Math<double>::ATan2(-m_dData[0][2], m_dData[0][0]);
        rdXAngle = Math<double>::HALF_PI;
        rdYAngle = 0.0;

        return false;
    }
}
//----------------------------------------------------------------------------
bool Matrix3d::ToEulerAnglesZYX(double& rdZAngle, double& rdYAngle, 
    double& rdXAngle) const
{
    // R = Rz * Ry * Rx
    //   =  cy*cz           cx*sz+cz*sx*sy  sx*sz-cx*cz*sy
    //     -cy*sz           cx*cz-sx*sy*sz  cz*sx+cx*sy*sz
    //      sy             -cy*sx           cx*cy
    //
    // 如果y = pi/2,则sy = 1,cy = 0
    // R = 0            cx*sz+cz*sx  sx*sz-cx*cz
    //     0            cx*cz-sx*sz  cz*sx+cx*sz
    //     1            0            0
    //   = 0            sin(x+z)    -cos(x+z)
    //     0            cos(x+z)     sin(x+z)
    //     1            0            0
    //
    // 如果y = -pi/2,则sy = -1,cy = 0
    // R =  0            cx*sz-cz*sx  sx*sz+cx*cz
    //      0            cx*cz+sx*sz  cz*sx-cx*sz
    //     -1            0            0
    //   =  0            sin(z-x)     cos(z-x)
    //      0            cos(z-x)    -sin(z-x)
    //     -1            0            0

    if( m_dData[2][0] > -1.0 )
    {
        if( m_dData[2][0] < 1.0 )
        {
            rdZAngle = Math<double>::ATan2(-m_dData[1][0], m_dData[0][0]);
            rdYAngle = asin(m_dData[2][0]);
            rdXAngle = Math<double>::ATan2(-m_dData[2][1], m_dData[2][2]);

            return true;
        }
        else
        {
            // y = pi/2,
            // 结果不唯一,
            // x + z = atan2(r01,-r02)
            rdZAngle = Math<double>::ATan2(m_dData[0][1], -m_dData[0][2]);
            rdYAngle = Math<double>::HALF_PI;
            rdXAngle = 0.0;

            return false;
        }
    }
    else
    {
        // y = -pi/2,
        // 结果不唯一,
        // z - x = atan2(r01,r02)
        rdZAngle = Math<double>::ATan2(m_dData[0][1], m_dData[0][2]);
        rdYAngle = -Math<double>::HALF_PI;
        rdXAngle = 0.0;

        return false;
    }
}
//----------------------------------------------------------------------------
Matrix3d Swing::operator*(double dLhsScalar, const Matrix3d& rRhsMat)
{
    return rRhsMat * dLhsScalar;
}
//----------------------------------------------------------------------------
Vector3d Swing::operator*(const Vector3d& rLhsVec, const Matrix3d& rRhsMat)
{
    return Vector3d(
        rLhsVec[0]*rRhsMat[0][0] + rLhsVec[1]*rRhsMat[1][0] + 
        rLhsVec[2]*rRhsMat[2][0],
        rLhsVec[0]*rRhsMat[0][1] + rLhsVec[1]*rRhsMat[1][1] + 
        rLhsVec[2]*rRhsMat[2][1],
        rLhsVec[0]*rRhsMat[0][2] + rLhsVec[1]*rRhsMat[1][2] + 
        rLhsVec[2]*rRhsMat[2][2]);
}
//----------------------------------------------------------------------------
void Matrix3d::Orthonormalize()
{
    // 待检查
    // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
    // M = [m0|m1|m2], then orthonormal output matrix is Q = [q0|q1|q2],
    //
    //   q0 = m0/|m0|
    //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
    //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
    //
    // where |V| indicates length of vector V and A*B indicates dot
    // product of vectors A and B.

    // compute q0
    double dInvLength = Math<double>::InvSqrt(m_dData[0][0]*m_dData[0][0] +
        m_dData[1][0]*m_dData[1][0] + m_dData[2][0]*m_dData[2][0]);

    m_dData[0][0] *= dInvLength;
    m_dData[1][0] *= dInvLength;
    m_dData[2][0] *= dInvLength;

    // compute q1
    double dDot0 = m_dData[0][0]*m_dData[0][1] + m_dData[1][0]*m_dData[1][1] +
        m_dData[2][0]*m_dData[2][1];

    m_dData[0][1] -= dDot0*m_dData[0][0];
    m_dData[1][1] -= dDot0*m_dData[1][0];
    m_dData[2][1] -= dDot0*m_dData[2][0];

    dInvLength = Math<double>::InvSqrt(m_dData[0][1]*m_dData[0][1] +
        m_dData[1][1]*m_dData[1][1] + m_dData[2][1]*m_dData[2][1]);

    m_dData[0][1] *= dInvLength;
    m_dData[1][1] *= dInvLength;
    m_dData[2][1] *= dInvLength;

    // compute q2
    double dDot1 = m_dData[0][1]*m_dData[0][2] + m_dData[1][1]*m_dData[1][2] +
        m_dData[2][1]*m_dData[2][2];

    dDot0 = m_dData[0][0]*m_dData[0][2] + m_dData[1][0]*m_dData[1][2] +
        m_dData[2][0]*m_dData[2][2];

    m_dData[0][2] -= dDot0*m_dData[0][0] + dDot1*m_dData[0][1];
    m_dData[1][2] -= dDot0*m_dData[1][0] + dDot1*m_dData[1][1];
    m_dData[2][2] -= dDot0*m_dData[2][0] + dDot1*m_dData[2][1];

    dInvLength = Math<double>::InvSqrt(m_dData[0][2]*m_dData[0][2] +
        m_dData[1][2]*m_dData[1][2] + m_dData[2][2]*m_dData[2][2]);

    m_dData[0][2] *= dInvLength;
    m_dData[1][2] *= dInvLength;
    m_dData[2][2] *= dInvLength;
}
//----------------------------------------------------------------------------
