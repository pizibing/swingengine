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

#ifndef Swing_TInteger_H
#define Swing_TInteger_H

#include "SEFoundationLIB.h"
#include "SESystem.h"

namespace Swing
{

template <int N> class SETRational;

//----------------------------------------------------------------------------
// Description:N is the number of 32-bit words you want per SETInteger.
// Author:Sun Che
// Date:20081201
//----------------------------------------------------------------------------
template <int N>
class SETInteger
{
public:
    // construction and destruction
    SETInteger(int i = 0);
    SETInteger(const SETInteger& rI);
    ~SETInteger(void);

    // assignment
    SETInteger& operator = (const SETInteger& rI);

    // comparison
    bool operator == (const SETInteger& rI) const;
    bool operator != (const SETInteger& rI) const;
    bool operator <  (const SETInteger& rI) const;
    bool operator <= (const SETInteger& rI) const;
    bool operator >  (const SETInteger& rI) const;
    bool operator >= (const SETInteger& rI) const;

    // arithmetic operations
    SETInteger operator - (void) const;
    SETInteger operator + (const SETInteger& rI) const;
    SETInteger operator - (const SETInteger& rI) const;
    SETInteger operator * (const SETInteger& rI) const;
    SETInteger operator / (const SETInteger& rI) const;
    SETInteger operator % (const SETInteger& rI) const;

    // arithmetic updates
    SETInteger& operator += (const SETInteger& rI);
    SETInteger& operator -= (const SETInteger& rI);
    SETInteger& operator *= (const SETInteger& rI);
    SETInteger& operator /= (const SETInteger& rI);

    // shift operations
    SETInteger operator << (int iShift) const;
    SETInteger operator >> (int iShift) const;

    // shift updates
    SETInteger& operator <<= (int iShift);
    SETInteger& operator >>= (int iShift);

private:
    // Support for comparisons. The return value of Compare is -1 if I0 < I1, 
    // is 0 if I0 == I1,  or is +1 if I0 > I1.
    static int Compare(const SETInteger& rI0, const SETInteger& rI1);
    int GetSign(void) const;

    // support for division and modulo
    static bool GetDivMod(const SETInteger& rNumer, const SETInteger& rDenom, 
        SETInteger& rQuotient, SETInteger& rRemainder);

    static void DivSingle(const SETInteger& rNumer, short usDenom, 
        SETInteger& rQuo, SETInteger& rRem);

    static void DivMultiple(const SETInteger& rNumer, const SETInteger& rDenom, 
        SETInteger& rQuo, SETInteger& rRem);

    // miscellaneous utilities
    int GetLeadingBlock(void) const;
    int GetTrailingBlock(void) const;
    int GetLeadingBit(int i) const;  // of m_asBuffer[i]
    int GetTrailingBit(int i) const;  // of m_asBuffer[i]
    int GetLeadingBit(void) const;  // of entire number
    int GetTrailingBit(void) const;  // of entire number
    void SetBit(int i,  bool bOn);
    bool GetBit(int i) const;
    unsigned int ToUnsignedInt(int i) const;
    void FromUnsignedInt(int i,  unsigned int uiValue);
    unsigned int ToUnsignedInt(int iLo,  int iHi) const;
    int ToInt(int i) const;

    enum
    {
        TINT_SIZE = 2 * N, 
        TINT_BYTES = TINT_SIZE * sizeof(short), 
        TINT_LAST = TINT_SIZE - 1
    };

    short m_asBuffer[TINT_SIZE];

    // SETRational needs access to private members of SETInteger.
    friend class SETRational<N>;
};

template <int N>
SETInteger<N> operator * (int i,  const SETInteger<N>& rI);

#include "SETInteger.inl"

}

#endif
