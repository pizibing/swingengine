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

#ifndef Swing_Matrix4_H
#define Swing_Matrix4_H

// Matrices in Swing Engine are stored in row-major order.
// CAUTION: By default, DirectX uses row-major order, OpenGL uses column-major
// order. For example, given a matrix M in DirectX, the corresponding matrix
// in OpenGL is M^T.

// Matrix operation is concatenated from left to right. Say, given a matrix
// M and a vector V, V multiply M equals V*M, V is viewed as a row vector. 
// Some graphics APIs express the multiplication as M'*V', in which cases 
// V' equals V but is viewed as a column vector, and M' is the transpose of M.
// So a sequence of transformation should be expressed as V' = V*M0*M1...Mn,
// Others graphics APIs express the operation from right to left, in which 
// cases the sequence of transformation should be expressed as V' = Mn...M1*M0*V.
// CAUTION: DirectX uses the rule of from left to right, OpenGL uses the rule of
// from right to left.
// Say, in DirectX, given M1 and M2, the equivalent items in OpenGL are M1^T, 
// M2^T, ^T means transpose operation.
// M1*M2 is equivalent to (M1*M2)^T = M2^T*M1^T.

#include "SEFoundationLIB.h"
#include "SEVector4.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:单精度4阶方阵类
// 说明:
// 作者:Sun Che
// 时间:20070512
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Matrix4f
{
public:
    union
    {
        struct
        {
            float M11, M12, M13, M14;
            float M21, M22, M23, M24;
            float M31, M32, M33, M34;
            float M41, M42, M43, M44;
        };
        float m_fData[4][4];
    };

public:
    Matrix4f(void);
    Matrix4f(const Matrix4f& rMat);
    Matrix4f(float fM11, float fM12, float fM13, float fM14,
             float fM21, float fM22, float fM23, float fM24,
             float fM31, float fM32, float fM33, float fM34,
             float fM41, float fM42, float fM43, float fM44);

public:    
    operator const float* (void) const;
    operator float* (void);
    const float* operator [] (int iCurRow) const;
    float* operator [] (int iCurRow);
    float operator () (int iCurRow, int iCurCol) const;
    float& operator () (int iCurRow, int iCurCol);

    inline void SetRow(int iDesRow, const Vector4f& rSrcVec);
    inline void GetRow(int iSrcRow, Vector4f& rDesVec) const;
    inline void SetColumn(int iDesCol, const Vector4f& rSrcVec);
    inline void GetColumn(int iSrcCol, Vector4f& rDesVec) const;

    Matrix4f& operator = (const Matrix4f& rMat);

    bool operator == (const Matrix4f& rMat) const;
    bool operator != (const Matrix4f& rMat) const;
    bool operator <  (const Matrix4f& rMat) const;
    bool operator <= (const Matrix4f& rMat) const;
    bool operator >  (const Matrix4f& rMat) const;
    bool operator >= (const Matrix4f& rMat) const;

    Matrix4f operator + (const Matrix4f& rRhsMat) const;
    Matrix4f operator - (const Matrix4f& rRhsMat) const;
    Matrix4f operator * (const Matrix4f& rRhsMat) const;
    Matrix4f operator * (float fScalar) const;
    Matrix4f operator / (float fScalar) const;
    Matrix4f operator - (void) const;

    Matrix4f& operator += (const Matrix4f& rRhsMat);
    Matrix4f& operator -= (const Matrix4f& rRhsMat);
    Matrix4f& operator *= (float fScalar);
    Matrix4f& operator /= (float fScalar);

    // 乘以列向量
    Vector4f operator * (const Vector4f& rRhsVec) const;

    SE_FOUNDATION_API friend Matrix4f operator * (float fLhsScalar, 
        const Matrix4f& rRhsMat);
    SE_FOUNDATION_API friend Vector4f operator * (const Vector4f& rLhsVec, 
        const Matrix4f& rRhsMat);

    // 置为0矩阵
    inline void Zero(void);
    // 置为单位矩阵
    inline void Identity(void);
	// 将自己转置
    void Transpose(void); // 执行时间为D3DX的2倍左右
    // 将自己求逆
    void Inverse(void); // 执行时间为D3DX的4倍左右
    // 获取转置矩阵
    inline void GetTranspose(Matrix4f& rDesMat) const;
    // 获取逆矩阵
    inline void GetInverse(Matrix4f& rDesMat) const;
    // 获取伴随矩阵
    inline void GetAdjoint(Matrix4f& rDesMat) const;
    // 获取行列式
    inline float GetDeterminant(void) const;
    // this^T * M
    inline void GetTransposeTimes(const Matrix4f& rRhsMat, 
        Matrix4f& rDesMat) const;
    // this * M^T
    inline void GetTimesTranspose(const Matrix4f& rRhsMat, 
        Matrix4f& rDesMat) const;

    static const Matrix4f ZERO;
    static const Matrix4f IDENTITY;

private:
    inline int CompareData(const Matrix4f& rMat) const;

};

//----------------------------------------------------------------------------
// 名称:双精度4阶方阵类
// 说明:
// 作者:Sun Che
// 时间:20090518
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Matrix4d
{
public:
    union
    {
        struct
        {
            double M11, M12, M13, M14;
            double M21, M22, M23, M24;
            double M31, M32, M33, M34;
            double M41, M42, M43, M44;
        };
        double m_dData[4][4];
    };

public:
    Matrix4d(void);
    Matrix4d(const Matrix4d& rMat);
    Matrix4d(double dM11, double dM12, double dM13, double dM14,
             double dM21, double dM22, double dM23, double dM24,
             double dM31, double dM32, double dM33, double dM34,
             double dM41, double dM42, double dM43, double dM44);

public:    
    operator const double* (void) const;
    operator double* (void);
    const double* operator [] (int iCurRow) const;
    double* operator [] (int iCurRow);
    double operator () (int iCurRow, int iCurCol) const;
    double& operator () (int iCurRow, int iCurCol);

    inline void SetRow(int iDesRow, const Vector4d& rSrcVec);
    inline void GetRow(int iSrcRow, Vector4d& rDesVec) const;
    inline void SetColumn(int iDesCol, const Vector4d& rSrcVec);
    inline void GetColumn(int iSrcCol, Vector4d& rDesVec) const;

    Matrix4d& operator = (const Matrix4d& rMat);

    bool operator == (const Matrix4d& rMat) const;
    bool operator != (const Matrix4d& rMat) const;
    bool operator <  (const Matrix4d& rMat) const;
    bool operator <= (const Matrix4d& rMat) const;
    bool operator >  (const Matrix4d& rMat) const;
    bool operator >= (const Matrix4d& rMat) const;

    Matrix4d operator + (const Matrix4d& rRhsMat) const;
    Matrix4d operator - (const Matrix4d& rRhsMat) const;
    Matrix4d operator * (const Matrix4d& rRhsMat) const;
    Matrix4d operator * (double dScalar) const;
    Matrix4d operator / (double dScalar) const;
    Matrix4d operator - (void) const;

    Matrix4d& operator += (const Matrix4d& rRhsMat);
    Matrix4d& operator -= (const Matrix4d& rRhsMat);
    Matrix4d& operator *= (double dScalar);
    Matrix4d& operator /= (double dScalar);

    // 乘以列向量
    Vector4d operator * (const Vector4d& rRhsVec) const;

    SE_FOUNDATION_API friend Matrix4d operator * (double dLhsScalar, 
        const Matrix4d& rRhsMat);
    SE_FOUNDATION_API friend Vector4d operator * (const Vector4d& rLhsVec, 
        const Matrix4d& rRhsMat);

    // 置为0矩阵
    inline void Zero(void);
    // 置为单位矩阵
    inline void Identity(void);
	// 将自己转置
    void Transpose(void);
    // 将自己求逆
    void Inverse(void);
    // 获取转置矩阵
    inline void GetTranspose(Matrix4d& rDesMat) const;
    // 获取逆矩阵
    inline void GetInverse(Matrix4d& rDesMat) const;
    // 获取伴随矩阵
    inline void GetAdjoint(Matrix4d& rDesMat) const;
    // 获取行列式
    inline double GetDeterminant(void) const;
    // this^T * M
    inline void GetTransposeTimes(const Matrix4d& rRhsMat, 
        Matrix4d& rDesMat) const;
    // this * M^T
    inline void GetTimesTranspose(const Matrix4d& rRhsMat, 
        Matrix4d& rDesMat) const;

    static const Matrix4d ZERO;
    static const Matrix4d IDENTITY;

private:
    inline int CompareData(const Matrix4d& rMat) const;

};

typedef SE_ALIGN16 Matrix4f Matrix4fA16;
typedef SE_ALIGN16 Matrix4d Matrix4dA16;

#include "SEMatrix4.inl"

}

#endif



