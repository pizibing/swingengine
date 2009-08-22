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

#ifndef Swing_RVector3_H
#define Swing_RVector3_H

#include "SEFoundationLIB.h"
#include "SETRVector.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:RVector3类
// 说明:
// 作者:Sun Che
// 时间:20081202
//----------------------------------------------------------------------------
template <int ISIZE>
class RVector3 : public TRVector<3,  ISIZE>
{
public:
    // construction
    RVector3(void);
    RVector3(const RVector3& rV);

#ifdef SE_USING_VC70
    RVector3(const TRVector<3,  ISIZE>& rV)
    {
        // The inline body is here because of an apparent MSVC++ .NET 2002
        // compiler bug.  If placed in the *.inl file,  the compiler complains:
        //
        //   error C2244: 'Swing::RVector3<>::__ctor' : unable to match function
        //       definition to an existing declaration
        //   definition
        //       'Swing::RVector3<>::RVector3(const Swing::TRVector<3, > &)'
        //   existing declarations
        //       'Swing::RVector3<>::RVector3(const Swing::TRational<> &, 
        //                                  const Swing::TRational<> &)'
        //       'Swing::RVector3<>::RVector3(const Swing::TRVector<3, > &)'
        //       'Swing::RVector3<>::RVector3(const Swing::RVector3<> &)'
        //       'Swing::RVector3<>::RVector3(void)'
        // The "definition" is in the "existing declarations" list,  so I do
        // not know what the compiler is complaining about.

        m_aTuple[0] = rV[0];
        m_aTuple[1] = rV[1];
        m_aTuple[2] = rV[2];
    }
#else
    RVector3(const TRVector<3,  ISIZE>& rV);
#endif

    RVector3(const TRational<ISIZE>& rX,  const TRational<ISIZE>& rY, 
        const TRational<ISIZE>& rZ);

    // member access
    TRational<ISIZE> X(void) const;
    TRational<ISIZE>& X(void);
    TRational<ISIZE> Y(void) const;
    TRational<ISIZE>& Y(void);
    TRational<ISIZE> Z(void) const;
    TRational<ISIZE>& Z(void);

    // assignment
    RVector3& operator = (const RVector3& rV);

#ifdef SE_USING_VC70
    RVector3& operator = (const TRVector<3,  ISIZE>& rV)
    {
        // The inline body is here because of an apparent MSVC++ .NET 2002
        // compiler bug.  If placed in the *.inl file,  the compiler complains:
        //
        //   error C2244: 'Swing::RVector3<>::operator`='' : unable to match
        //       function definition to an existing declaration
        //   definition
        //       'Swing::RVector3<> &Swing::RVector3<>::operator =(
        //            const Swing::TRVector<3, > &)'
        //   existing declarations
        //       'Swing::RVector3<> &Swing::RVector3<>::operator =(
        //            const Swing::TRVector<3, > &)'
        //       'Swing::RVector3<> &Swing::RVector3<>::operator =(
        //            const Swing::RVector3<> &)'

        m_aTuple[0] = rV[0];
        m_aTuple[1] = rV[1];
        m_aTuple[2] = rV[2];

        return *this;
    }
#else
    RVector3& operator = (const TRVector<3,  ISIZE>& rV);
#endif

    // returns Dot(this, V)
    TRational<ISIZE> Dot(const RVector3& rV) const;

    // returns Cross(this, V)
    RVector3 Cross(const RVector3& rV) const;

    // returns Dot(this, Cross(U, V))
    TRational<ISIZE> TripleScalar(const RVector3& rU,  const RVector3& rV)
        const;

protected:
    using TRVector<3,  ISIZE>::m_aTuple;
};

#include "SERVector3.inl"

}

#endif
