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
// 名称:RVector2类
// 说明:
// 作者:Sun Che
// 时间:20081202
//----------------------------------------------------------------------------
template <int ISIZE>
class RVector2 : public TRVector<2,  ISIZE>
{
public:
    // construction
    RVector2();
    RVector2(const RVector2& rV);

#ifdef SE_USING_VC70
    RVector2(const TRVector<2,  ISIZE>& rV)
    {
        // The inline body is here because of an apparent MSVC++ .NET 2002
        // compiler bug.  If placed in the *.inl file,  the compiler complains:
        //
        //   error C2244: 'Swing::RVector2<>::__ctor' : unable to match function
        //       definition to an existing declaration
        //   definition
        //       'Swing::RVector2<>::RVector2(const Swing::TRVector<2, > &)'
        //   existing declarations
        //       'Swing::RVector2<>::RVector2(const Swing::TRational<> &, 
        //                                  const Swing::TRational<> &)'
        //       'Swing::RVector2<>::RVector2(const Swing::TRVector<2, > &)'
        //       'Swing::RVector2<>::RVector2(const Swing::RVector2<> &)'
        //       'Swing::RVector2<>::RVector2(void)'
        // The "definition" is in the "existing declarations" list,  so I do
        // not know what the compiler is complaining about.

        m_aTuple[0] = rV[0];
        m_aTuple[1] = rV[1];
    }
#else
    RVector2(const TRVector<2,  ISIZE>& rV);
#endif

    RVector2(const TRational<ISIZE>& rX,  const TRational<ISIZE>& rY);

    // member access
    TRational<ISIZE> X(void) const;
    TRational<ISIZE>& X(void);
    TRational<ISIZE> Y(void) const;
    TRational<ISIZE>& Y(void);

    // assignment
    RVector2& operator = (const RVector2& rV);

#ifdef SE_USING_VC70
    RVector2& operator = (const TRVector<2,  ISIZE>& rV)
    {
        // The inline body is here because of an apparent MSVC++ .NET 2002
        // compiler bug.  If placed in the *.inl file,  the compiler complains:
        //
        //   error C2244: 'Swing::RVector2<>::operator`='' : unable to match
        //       function definition to an existing declaration
        //   definition
        //       'Swing::RVector2<> &Swing::RVector2<>::operator =(
        //            const Swing::TRVector<2, > &)'
        //   existing declarations
        //       'Swing::RVector2<> &Swing::RVector2<>::operator =(
        //            const Swing::TRVector<2, > &)'
        //       'Swing::RVector2<> &Swing::RVector2<>::operator =(
        //            const Swing::RVector2<> &)'

        m_aTuple[0] = rV[0];
        m_aTuple[1] = rV[1];

        return *this;
    }
#else
    RVector2& operator = (const TRVector<2,  ISIZE>& rV);
#endif

    // returns Dot(this, V)
    TRational<ISIZE> Dot(const RVector2& rV) const;

    // returns (y, -x)
    RVector2 Perp(void) const;

    // returns Cross((x, y, 0), (V.x, V.y, 0)) = x*V.y - y*V.x
    TRational<ISIZE> DotPerp(const RVector2& rV) const;

protected:
    using TRVector<2,  ISIZE>::m_aTuple;
};

#include "SERVector2.inl"

}

#endif
