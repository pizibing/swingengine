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

#ifndef Swing_Vector4_H
#define Swing_Vector4_H

#include "SEFoundationLIB.h"
#include "SEMath.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:单精度4维向量类
// 说明:
// 作者:Sun Che
// 时间:20070512
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Vector4f
{
public:
    union
    {
        struct
        {
            float X;
            float Y;
            float Z;
            float W;
        };
        float m_fData[4];
    };

public:
    Vector4f(void);
    Vector4f(float fX, float fY, float fZ, float fW);
    Vector4f(const Vector4f& rVec);

	// 转换为连续指针空间
    operator const float* (void) const;
    operator float* (void);
	// 取第i元素形式
    float operator [] (int i) const;
    float& operator [] (int i);

    Vector4f& operator = (const Vector4f& rVec);

    bool operator == (const Vector4f& rVec) const;
    bool operator != (const Vector4f& rVec) const;
    bool operator <  (const Vector4f& rVec) const;
    bool operator <= (const Vector4f& rVec) const;
    bool operator >  (const Vector4f& rVec) const;
    bool operator >= (const Vector4f& rVec) const;

    Vector4f operator + (const Vector4f& rRhsVec) const;
    Vector4f operator - (const Vector4f& rRhsVec) const;
    Vector4f operator * (float fScalar) const;
    Vector4f operator / (float fScalar) const;
    Vector4f operator - (void) const;

    Vector4f& operator += (const Vector4f& rRhsVec);
    Vector4f& operator += (float fScalar);
    Vector4f& operator -= (const Vector4f& rRhsVec);
    Vector4f& operator -= (float fScalar);
    Vector4f& operator *= (float fScalar);
    Vector4f& operator /= (float fScalar);

    SE_FOUNDATION_API friend Vector4f operator * (float fLhsScalar, 
        const Vector4f& rRhsVec);
	
    // 求向量长度
    inline float GetLength(void) const;
    // 求向量长度平方
    inline float GetSquaredLength(void) const;
    // 求点积
    inline float Dot(const Vector4f& rRhsVec) const;
	// 规范化
	inline float Normalize(void);

    static const Vector4f ZERO;
    static const Vector4f UNIT_X;
    static const Vector4f UNIT_Y;
    static const Vector4f UNIT_Z;
    static const Vector4f UNIT_W;

private:
    inline int CompareData(const Vector4f& rVec) const;
};

//----------------------------------------------------------------------------
// 名称:双精度4维向量类
// 说明:
// 作者:Sun Che
// 时间:20090515
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Vector4d
{
public:
    union
    {
        struct
        {
            double X;
            double Y;
            double Z;
            double W;
        };
        double m_dData[4];
    };

public:
    Vector4d(void);
    Vector4d(double dX, double dY, double dZ, double dW);
    Vector4d(const Vector4d& rVec);

	// 转换为连续指针空间
    operator const double* (void) const;
    operator double* (void);
	// 取第i元素形式
    double operator [] (int i) const;
    double& operator [] (int i);

    Vector4d& operator = (const Vector4d& rVec);

    bool operator == (const Vector4d& rVec) const;
    bool operator != (const Vector4d& rVec) const;
    bool operator <  (const Vector4d& rVec) const;
    bool operator <= (const Vector4d& rVec) const;
    bool operator >  (const Vector4d& rVec) const;
    bool operator >= (const Vector4d& rVec) const;

    Vector4d operator + (const Vector4d& rRhsVec) const;
    Vector4d operator - (const Vector4d& rRhsVec) const;
    Vector4d operator * (double dScalar) const;
    Vector4d operator / (double dScalar) const;
    Vector4d operator - (void) const;

    Vector4d& operator += (const Vector4d& rRhsVec);
    Vector4d& operator += (double dScalar);
    Vector4d& operator -= (const Vector4d& rRhsVec);
    Vector4d& operator -= (double dScalar);
    Vector4d& operator *= (double dScalar);
    Vector4d& operator /= (double dScalar);

    SE_FOUNDATION_API friend Vector4d operator * (double dLhsScalar, 
        const Vector4d& rRhsVec);
	
    // 求向量长度
    inline double GetLength(void) const;
    // 求向量长度平方
    inline double GetSquaredLength(void) const;
    // 求点积
    inline double Dot(const Vector4d& rRhsVec) const;
	// 规范化
	inline double Normalize(void);

    static const Vector4d ZERO;
    static const Vector4d UNIT_X;
    static const Vector4d UNIT_Y;
    static const Vector4d UNIT_Z;
    static const Vector4d UNIT_W;

private:
    inline int CompareData(const Vector4d& rVec) const;
};

typedef SE_ALIGN16 Vector4f Vector4fA16;
typedef SE_ALIGN16 Vector4d Vector4dA16;

#include "SEVector4.inl"

}

#endif