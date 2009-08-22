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

#ifndef Swing_TRational_H
#define Swing_TRational_H

#include "SEFoundationLIB.h"
#include "SETInteger.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:TRational类
// 说明:N is the number of 32-bit words per TInteger numerator/denominator
// 作者:Sun Che
// 时间:20081202
//----------------------------------------------------------------------------
template <int N>
class TRational
{
public:
    // construction
    TRational(void);  // default rational is 0/1
    TRational(const TRational& rR);
    TRational(const TInteger<N>& rNumer);
    TRational(const TInteger<N>& rNumer,  const TInteger<N>& rDenom);

    // construction converters
    TRational(int iNumer);
    TRational(int iNumer,  int iDenom);
    TRational(float fValue);
    TRational(double dValue);

    // member access
    TInteger<N>& Numer(void);
    TInteger<N>& Denom(void);
    const TInteger<N>& Numer(void) const;
    const TInteger<N>& Denom(void) const;

    // assignment
    TRational& operator = (const TRational& rR);

    // comparison
    bool operator == (const TRational& rR) const;
    bool operator != (const TRational& rR) const;
    bool operator <= (const TRational& rR) const;
    bool operator <  (const TRational& rR) const;
    bool operator >= (const TRational& rR) const;
    bool operator >  (const TRational& rR) const;

    // arithmetic operations
    TRational operator + (const TRational& rR) const;
    TRational operator - (const TRational& rR) const;
    TRational operator * (const TRational& rR) const;
    TRational operator / (const TRational& rR) const;
    TRational operator - (void) const;

    // arithmetic updates
    TRational& operator += (const TRational& rR);
    TRational& operator -= (const TRational& rR);
    TRational& operator *= (const TRational& rR);
    TRational& operator /= (const TRational& rR);

    // conversions to float and double
    void ConvertTo(float& rfValue) const;
    void ConvertTo(double& rdValue) const;

    // compute the absolute value of the rational number
    TRational Abs(void) const;

private:
    // miscellaneous utilities
    void EliminatePowersOfTwo(void);

    static void GetPositiveFloat(const TInteger<N>& rDenom, 
        TInteger<N>& rQuo,  TInteger<N>& rRem,  int iBlock, 
        unsigned int& ruiExponent,  unsigned int& ruiMantissa);

    static void GetPositiveDouble(const TInteger<N>& rDenom, 
        TInteger<N>& rQuo,  TInteger<N>& rRem,  int iBlock, 
        unsigned int& ruiExponent,  unsigned int& ruiMantissaHi, 
        unsigned int& ruiMantissaLo);

    // 分子与分母.
    TInteger<N> m_Numer,  m_Denom;
};

template <int N>
TRational<N> operator + (const TInteger<N>& rI,  const TRational<N>& rR);

template <int N>
TRational<N> operator - (const TInteger<N>& rI,  const TRational<N>& rR);

template <int N>
TRational<N> operator * (const TInteger<N>& rI,  const TRational<N>& rR);

template <int N>
TRational<N> operator / (const TInteger<N>& rI,  const TRational<N>& rR);

#include "SETRational.inl"

}

#endif
