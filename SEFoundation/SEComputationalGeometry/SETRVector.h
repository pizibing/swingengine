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

#ifndef Swing_TRVector_H
#define Swing_TRVector_H

#include "SEFoundationLIB.h"
#include "SETRational.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:TRVector类
// 说明:
// 作者:Sun Che
// 时间:20081202
//----------------------------------------------------------------------------
template <int VSIZE,  int ISIZE>
class SETRVector
{
public:
    // construction
    SETRVector(void);
    SETRVector(const SETRVector& rV);

    // coordinate access
    operator const SETRational<ISIZE>* (void) const;
    operator SETRational<ISIZE>* (void);
    SETRational<ISIZE> operator [] (int i) const;
    SETRational<ISIZE>& operator [] (int i);

    // assignment
    SETRVector& operator = (const SETRVector& rV);

    // comparison
    bool operator == (const SETRVector& rV) const;
    bool operator != (const SETRVector& rV) const;
    bool operator <  (const SETRVector& rV) const;
    bool operator <= (const SETRVector& rV) const;
    bool operator >  (const SETRVector& rV) const;
    bool operator >= (const SETRVector& rV) const;

    // arithmetic operations
    SETRVector operator + (const SETRVector& rV) const;
    SETRVector operator - (const SETRVector& rV) const;
    SETRVector operator * (const SETRational<ISIZE>& rR) const;
    SETRVector operator / (const SETRational<ISIZE>& rR) const;
    SETRVector operator - (void) const;

    // arithmetic updates
    SETRVector& operator += (const SETRVector& rV);
    SETRVector& operator -= (const SETRVector& rV);
    SETRVector& operator *= (const SETRational<ISIZE>& rR);
    SETRVector& operator /= (const SETRational<ISIZE>& rR);

    // vector operations
    SETRational<ISIZE> GetSquaredLength(void) const;
    SETRational<ISIZE> Dot(const SETRVector& rV) const;

protected:
    // support for comparisons
    int CompareArrays(const SETRVector& rV) const;

    SETRational<ISIZE> m_aTuple[VSIZE];
};

template <int VSIZE,  int ISIZE>
SETRVector<VSIZE,  ISIZE> operator * (const SETRational<ISIZE>& rR, 
    const SETRVector<VSIZE,  ISIZE>& rV);

#include "SETRVector.inl"

}

#endif
