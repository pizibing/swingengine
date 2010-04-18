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
// Description:N is the number of 32-bit words per SETInteger numerator/
//     denominator.
// Author:Sun Che
// Date:20081202
//----------------------------------------------------------------------------
template <int N>
class SETRational
{
public:
    // construction
    SETRational(void);  // default rational is 0/1
    SETRational(const SETRational& rR);
    SETRational(const SETInteger<N>& rNumer);
    SETRational(const SETInteger<N>& rNumer,  const SETInteger<N>& rDenom);

    // construction converters
    SETRational(int iNumer);
    SETRational(int iNumer,  int iDenom);
    SETRational(float fValue);
    SETRational(double dValue);

    // member access
    SETInteger<N>& Numer(void);
    SETInteger<N>& Denom(void);
    const SETInteger<N>& Numer(void) const;
    const SETInteger<N>& Denom(void) const;

    // assignment
    SETRational& operator = (const SETRational& rR);

    // comparison
    bool operator == (const SETRational& rR) const;
    bool operator != (const SETRational& rR) const;
    bool operator <= (const SETRational& rR) const;
    bool operator <  (const SETRational& rR) const;
    bool operator >= (const SETRational& rR) const;
    bool operator >  (const SETRational& rR) const;

    // arithmetic operations
    SETRational operator + (const SETRational& rR) const;
    SETRational operator - (const SETRational& rR) const;
    SETRational operator * (const SETRational& rR) const;
    SETRational operator / (const SETRational& rR) const;
    SETRational operator - (void) const;

    // arithmetic updates
    SETRational& operator += (const SETRational& rR);
    SETRational& operator -= (const SETRational& rR);
    SETRational& operator *= (const SETRational& rR);
    SETRational& operator /= (const SETRational& rR);

    // conversions to float and double
    void ConvertTo(float& rfValue) const;
    void ConvertTo(double& rdValue) const;

    // compute the absolute value of the rational number
    SETRational Abs(void) const;

private:
    // miscellaneous utilities
    void EliminatePowersOfTwo(void);

    static void GetPositiveFloat(const SETInteger<N>& rDenom, 
        SETInteger<N>& rQuo,  SETInteger<N>& rRem,  int iBlock, 
        unsigned int& ruiExponent,  unsigned int& ruiMantissa);

    static void GetPositiveDouble(const SETInteger<N>& rDenom, 
        SETInteger<N>& rQuo,  SETInteger<N>& rRem,  int iBlock, 
        unsigned int& ruiExponent,  unsigned int& ruiMantissaHi, 
        unsigned int& ruiMantissaLo);

    // 分子与分母.
    SETInteger<N> m_Numer,  m_Denom;
};

template <int N>
SETRational<N> operator + (const SETInteger<N>& rI, const SETRational<N>& rR);

template <int N>
SETRational<N> operator - (const SETInteger<N>& rI, const SETRational<N>& rR);

template <int N>
SETRational<N> operator * (const SETInteger<N>& rI, const SETRational<N>& rR);

template <int N>
SETRational<N> operator / (const SETInteger<N>& rI, const SETRational<N>& rR);

#include "SETRational.inl"

}

#endif
