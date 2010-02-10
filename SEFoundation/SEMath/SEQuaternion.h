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

#ifndef Swing_Quaternion_H
#define Swing_Quaternion_H

// Quaternion是形如q = w + x*i + y*j + z*k的超复数,
// 对于4D向量空间向量(w,x,y,z),其模不一定为1,
// 虚部:i^2 = j^2 = k^2 = -1,i*j = k,j*k = i,k*i = j,j*i = -k,k*j = -i,i*k = -j

#include "SEFoundationLIB.h"
#include "SEMatrix3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:单精度4元数类
// 说明:
// 作者:Sun Che
// 时间:20070627
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Quaternionf
{
public:
    union
    {
        struct
		{
            float W;
            float X;
            float Y;
            float Z;
		};
        float m_fData[4];
    };

public:
    Quaternionf(void);
    Quaternionf(float fW, float fX, float fY, float fZ);
    Quaternionf(const Quaternionf& rQ);

    // 由旋转矩阵构造quaternion.
    Quaternionf(const Matrix3f& rRotMat);

    // 由任意轴角度构造quaternion.
    Quaternionf(const Vector3f& rAxis, float fAngle);

    operator const float* (void) const;
    operator float* (void);
    float operator [] (int i) const;
    float& operator [] (int i);

    Quaternionf& operator = (const Quaternionf& rQ);

    bool operator == (const Quaternionf& rQ) const;
    bool operator != (const Quaternionf& rQ) const;
    bool operator <  (const Quaternionf& rQ) const;
    bool operator <= (const Quaternionf& rQ) const;
    bool operator >  (const Quaternionf& rQ) const;
    bool operator >= (const Quaternionf& rQ) const;

    Quaternionf operator + (const Quaternionf& rRhsQ) const;
    Quaternionf operator - (const Quaternionf& rRhsQ) const;
    Quaternionf operator * (const Quaternionf& rRhsQ) const;
    Quaternionf operator * (float fScalar) const;
    Quaternionf operator / (float fScalar) const;
    Quaternionf operator - (void) const;

    Quaternionf& operator += (const Quaternionf& rRhsQ);
    Quaternionf& operator -= (const Quaternionf& rRhsQ);
    Quaternionf& operator *= (float fScalar);
    Quaternionf& operator /= (float fScalar);

    SE_FOUNDATION_API friend Quaternionf operator * (float fLhsScalar, 
        const Quaternionf& rRhsQ);

    // 必须为旋转矩阵.
    inline Quaternionf& FromRotationMatrix(const Matrix3f& rRotMat);
    inline void ToRotationMatrix(Matrix3f& rRotMat) const;
    Quaternionf& FromRotationMatrix(const Vector3f aRot[3],
        bool bIsRow = true);
    void ToRotationMatrix(Vector3f aRot[3], bool bIsRow = true) const;

    // 旋转轴必须是单位向量.
    inline Quaternionf& FromAxisAngle(const Vector3f& rAxis, float fAngle);
    inline void ToAxisAngle(Vector3f& rAxis, float& rfAngle) const;

    // 获取长度.
    inline float GetLength(void) const;
    // 获取长度平方.
    inline float GetSquaredLength(void) const;
    // 获取点积.
    inline float Dot(const Quaternionf& rQ) const;
    // 规范化.
    inline float Normalize(void);

    // 应用于非0 quaternion.
    inline void GetInverse(Quaternionf& rDesQ) const;
    // 获取共轭quaternion.
    inline void GetConjugate(Quaternionf& rDesQ) const;

    // 旋转一个向量.
    Vector3f Rotate(const Vector3f& rSrcVec) const;

    // 球面线性插值.
    Quaternionf& Slerp(float fT, const Quaternionf& rP,
        const Quaternionf& rQ);
    // 线性插值.
    Quaternionf& Lerp(float fT, const Quaternionf& rP,
        const Quaternionf& rQ);

    static const Quaternionf IDENTITY;
    static const Quaternionf ZERO;

private:
    inline int CompareData(const Quaternionf& rQ) const;

    // 用于FromRotationMatrix.
    static int m_iNext[3];
};

//----------------------------------------------------------------------------
// 名称:双精度4元数类
// 说明:
// 作者:Sun Che
// 时间:20090725
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Quaterniond
{
public:
    union
    {
        struct
		{
            double W;
            double X;
            double Y;
            double Z;
		};
        double m_dData[4];
    };

public:
    Quaterniond(void);
    Quaterniond(double dW, double dX, double dY, double dZ);
    Quaterniond(const Quaterniond& rQ);

    // 由旋转矩阵构造quaternion.
    Quaterniond(const Matrix3d& rRotMat);

    // 由任意轴角度构造quaternion.
    Quaterniond(const Vector3d& rAxis, double dAngle);

    operator const double* (void) const;
    operator double* (void);
    double operator [] (int i) const;
    double& operator [] (int i);

    Quaterniond& operator = (const Quaterniond& rQ);

    bool operator == (const Quaterniond& rQ) const;
    bool operator != (const Quaterniond& rQ) const;
    bool operator <  (const Quaterniond& rQ) const;
    bool operator <= (const Quaterniond& rQ) const;
    bool operator >  (const Quaterniond& rQ) const;
    bool operator >= (const Quaterniond& rQ) const;

    Quaterniond operator + (const Quaterniond& rRhsQ) const;
    Quaterniond operator - (const Quaterniond& rRhsQ) const;
    Quaterniond operator * (const Quaterniond& rRhsQ) const;
    Quaterniond operator * (double dScalar) const;
    Quaterniond operator / (double dScalar) const;
    Quaterniond operator - (void) const;

    Quaterniond& operator += (const Quaterniond& rRhsQ);
    Quaterniond& operator -= (const Quaterniond& rRhsQ);
    Quaterniond& operator *= (double dScalar);
    Quaterniond& operator /= (double dScalar);

    SE_FOUNDATION_API friend Quaterniond operator * (double dLhsScalar, 
        const Quaterniond& rRhsQ);

    // 必须为旋转矩阵.
    inline Quaterniond& FromRotationMatrix(const Matrix3d& rRotMat);
    inline void ToRotationMatrix(Matrix3d& rRotMat) const;
    Quaterniond& FromRotationMatrix(const Vector3d aRot[3],
        bool bIsRow = true);
    void ToRotationMatrix(Vector3d aRot[3], bool bIsRow = true) const;

    // 旋转轴必须是单位向量.
    inline Quaterniond& FromAxisAngle(const Vector3d& rAxis, double dAngle);
    inline void ToAxisAngle(Vector3d& rAxis, double& rdAngle) const;

    // 获取长度.
    inline double GetLength(void) const;
    // 获取长度平方.
    inline double GetSquaredLength(void) const;
    // 获取点积.
    inline double Dot(const Quaterniond& rQ) const;
    // 规范化.
    inline double Normalize(void);

    // 应用于非0 quaternion.
    inline void GetInverse(Quaterniond& rDesQ) const;
    // 获取共轭quaternion.
    inline void GetConjugate(Quaterniond& rDesQ) const;

    // 旋转一个向量.
    Vector3d Rotate(const Vector3d& rSrcVec) const;

    // 球面线性插值.
    Quaterniond& Slerp(double dT, const Quaterniond& rP,
        const Quaterniond& rQ);
    // 线性插值.
    Quaterniond& Lerp(double dT, const Quaterniond& rP,
        const Quaterniond& rQ);

    static const Quaterniond IDENTITY;
    static const Quaterniond ZERO;

private:
    inline int CompareData(const Quaterniond& rQ) const;

    // 用于FromRotationMatrix.
    static int m_iNext[3];
};

#include "SEQuaternion.inl"

}

#endif
