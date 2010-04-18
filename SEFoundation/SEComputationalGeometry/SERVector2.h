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

#ifndef Swing_RVector2_H
#define Swing_RVector2_H

#include "SEFoundationLIB.h"
#include "SETRVector.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20081202
//----------------------------------------------------------------------------
template <int ISIZE>
class SERVector2 : public SETRVector<2,  ISIZE>
{
public:
    // construction
    SERVector2();
    SERVector2(const SERVector2& rV);

#ifdef SE_USING_VC70
    SERVector2(const SETRVector<2,  ISIZE>& rV)
    {
        // The inline body is here because of an apparent MSVC++ .NET 2002
        // compiler bug. If placed in the *.inl file, the compiler complains:
        //
        //   error C2244: 'Swing::SERVector2<>::__ctor' : unable to match 
        //       function definition to an existing declaration
        //   definition
        //       'Swing::SERVector2<>::SERVector2(const Swing::SETRVector<2, 
        //       > &)' existing declarations
        //       'Swing::SERVector2<>::SERVector2(const Swing::SETRational<
        //       > &, const Swing::SETRational<> &)'
        //       'Swing::SERVector2<>::SERVector2(const Swing::SETRVector<2, 
        //       > &)'
        //       'Swing::SERVector2<>::SERVector2(const Swing::SERVector2<
        //       > &)' 'Swing::SERVector2<>::SERVector2(void)'
        // The "definition" is in the "existing declarations" list, so I do
        // not know what the compiler is complaining about.

        m_aTuple[0] = rV[0];
        m_aTuple[1] = rV[1];
    }
#else
    SERVector2(const SETRVector<2,  ISIZE>& rV);
#endif

    SERVector2(const SETRational<ISIZE>& rX,  const SETRational<ISIZE>& rY);

    // member access
    SETRational<ISIZE> X(void) const;
    SETRational<ISIZE>& X(void);
    SETRational<ISIZE> Y(void) const;
    SETRational<ISIZE>& Y(void);

    // assignment
    SERVector2& operator = (const SERVector2& rV);

#ifdef SE_USING_VC70
    SERVector2& operator = (const SETRVector<2,  ISIZE>& rV)
    {
        // The inline body is here because of an apparent MSVC++ .NET 2002
        // compiler bug.  If placed in the *.inl file, the compiler complains:
        //
        //   error C2244: 'Swing::SERVector2<>::operator`='' : unable to match
        //       function definition to an existing declaration
        //   definition
        //       'Swing::SERVector2<> &Swing::SERVector2<>::operator =(
        //            const Swing::SETRVector<2, > &)'
        //   existing declarations
        //       'Swing::SERVector2<> &Swing::SERVector2<>::operator =(
        //            const Swing::SETRVector<2, > &)'
        //       'Swing::SERVector2<> &Swing::SERVector2<>::operator =(
        //            const Swing::SERVector2<> &)'

        m_aTuple[0] = rV[0];
        m_aTuple[1] = rV[1];

        return *this;
    }
#else
    SERVector2& operator = (const SETRVector<2,  ISIZE>& rV);
#endif

    // returns Dot(this, V)
    SETRational<ISIZE> Dot(const SERVector2& rV) const;

    // returns (y, -x)
    SERVector2 Perp(void) const;

    // returns Cross((x, y, 0), (V.x, V.y, 0)) = x*V.y - y*V.x
    SETRational<ISIZE> DotPerp(const SERVector2& rV) const;

protected:
    using SETRVector<2,  ISIZE>::m_aTuple;
};

#include "SERVector2.inl"

}

#endif
