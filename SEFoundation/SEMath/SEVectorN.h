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

#ifndef Swing_VectorN_H
#define Swing_VectorN_H

#include "SEFoundationLIB.h"
#include "SEMath.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:N维向量类
// 说明:
// 作者:Sun Che
// 时间:20070706
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEVectorNf
{
public:
    SEVectorNf(int iSize = 0);
    SEVectorNf(int iSize, const float* pData);
    SEVectorNf(const SEVectorNf& rVec);
    ~SEVectorNf(void);

public:
    inline void SetSize(int iSize);
    inline int GetSize(void) const;

    operator float* (void);
    operator const float* (void) const;
    float operator [] (int i) const;
    float& operator [] (int i);

    SEVectorNf& operator = (const SEVectorNf& rVec);

    bool operator == (const SEVectorNf& rVec) const;
    bool operator != (const SEVectorNf& rVec) const;
    bool operator <  (const SEVectorNf& rVec) const;
    bool operator <= (const SEVectorNf& rVec) const;
    bool operator >  (const SEVectorNf& rVec) const;
    bool operator >= (const SEVectorNf& rVec) const;

    SEVectorNf operator + (const SEVectorNf& rRhsVec) const;
    SEVectorNf operator - (const SEVectorNf& rRhsVec) const;
    SEVectorNf operator * (float fScalar) const;
    SEVectorNf operator / (float fScalar) const;
    SEVectorNf operator - (void) const;

    SEVectorNf& operator += (const SEVectorNf& rRhsVec);
    SEVectorNf& operator -= (const SEVectorNf& rRhsVec);
    SEVectorNf& operator *= (float fScalar);
    SEVectorNf& operator /= (float fScalar);

    SE_FOUNDATION_API friend SEVectorNf operator * (float fLhsScalar,
        const SEVectorNf& rRhsVec);

    inline float GetLength(void) const;
    inline float GetSquaredLength(void) const;
    inline float Dot(const SEVectorNf& rRhsVec) const;
    inline float Normalize(void);

private:
    inline int CompareData(const SEVectorNf& rVec) const;

    int m_iSize;
    float* m_pData;
};

#include "SEVectorN.inl"

}

#endif