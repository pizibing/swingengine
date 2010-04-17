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

#ifndef Swing_TIVector_H
#define Swing_TIVector_H

#include "SEFoundationLIB.h"
#include "SESystem.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:TIVector类
// 说明:
// 作者:Sun Che
// 时间:20081201
//----------------------------------------------------------------------------
template <int VSIZE>
class SETIVector
{
public:
    // construction
    SETIVector(void);
    SETIVector(const SETIVector& rV);

    // coordinate access
    operator const SE_Int64* (void) const;
    operator SE_Int64* (void);
    SE_Int64 operator [] (int i) const;
    SE_Int64& operator [] (int i);

    // assignment
    SETIVector& operator = (const SETIVector& rV);

    // comparison
    bool operator == (const SETIVector& rV) const;
    bool operator != (const SETIVector& rV) const;
    bool operator <  (const SETIVector& rV) const;
    bool operator <= (const SETIVector& rV) const;
    bool operator >  (const SETIVector& rV) const;
    bool operator >= (const SETIVector& rV) const;

    // arithmetic operations
    SETIVector operator + (const SETIVector& rV) const;
    SETIVector operator - (const SETIVector& rV) const;
    SETIVector operator * (const SE_Int64& riI) const;
    SETIVector operator / (const SE_Int64& riI) const;
    SETIVector operator - (void) const;

    // arithmetic updates
    SETIVector& operator += (const SETIVector& rV);
    SETIVector& operator -= (const SETIVector& rV);
    SETIVector& operator *= (const SE_Int64& riI);
    SETIVector& operator /= (const SE_Int64& riI);

    // vector operations
    SE_Int64 GetSquaredLength(void) const;
    SE_Int64 Dot(const SETIVector& rV) const;

protected:
    // support for comparisons
    int CompareArrays(const SETIVector& rV) const;

    SE_Int64 m_aiTuple[VSIZE];
};

template <int VSIZE>
SETIVector<VSIZE> operator * (const SE_Int64& riI,  const SETIVector<VSIZE>& rV);

#include "SETIVector.inl"

}

#endif
