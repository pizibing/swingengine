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
class SERVector3 : public SETRVector<3,  ISIZE>
{
public:
    // construction
    SERVector3(void);
    SERVector3(const SERVector3& rV);

#ifdef SE_USING_VC70
    SERVector3(const SETRVector<3,  ISIZE>& rV)
    {
        // The inline body is here because of an apparent MSVC++ .NET 2002
        // compiler bug.  If placed in the *.inl file,  the compiler complains:
        //
        //   error C2244: 'Swing::SERVector3<>::__ctor' : unable to match function
        //       definition to an existing declaration
        //   definition
        //       'Swing::SERVector3<>::SERVector3(const Swing::SETRVector<3, > &)'
        //   existing declarations
        //       'Swing::SERVector3<>::SERVector3(const Swing::SETRational<> &, 
        //                                  const Swing::SETRational<> &)'
        //       'Swing::SERVector3<>::SERVector3(const Swing::SETRVector<3, > &)'
        //       'Swing::SERVector3<>::SERVector3(const Swing::SERVector3<> &)'
        //       'Swing::SERVector3<>::SERVector3(void)'
        // The "definition" is in the "existing declarations" list,  so I do
        // not know what the compiler is complaining about.

        m_aTuple[0] = rV[0];
        m_aTuple[1] = rV[1];
        m_aTuple[2] = rV[2];
    }
#else
    SERVector3(const SETRVector<3,  ISIZE>& rV);
#endif

    SERVector3(const SETRational<ISIZE>& rX,  const SETRational<ISIZE>& rY, 
        const SETRational<ISIZE>& rZ);

    // member access
    SETRational<ISIZE> X(void) const;
    SETRational<ISIZE>& X(void);
    SETRational<ISIZE> Y(void) const;
    SETRational<ISIZE>& Y(void);
    SETRational<ISIZE> Z(void) const;
    SETRational<ISIZE>& Z(void);

    // assignment
    SERVector3& operator = (const SERVector3& rV);

#ifdef SE_USING_VC70
    SERVector3& operator = (const SETRVector<3,  ISIZE>& rV)
    {
        // The inline body is here because of an apparent MSVC++ .NET 2002
        // compiler bug.  If placed in the *.inl file,  the compiler complains:
        //
        //   error C2244: 'Swing::SERVector3<>::operator`='' : unable to match
        //       function definition to an existing declaration
        //   definition
        //       'Swing::SERVector3<> &Swing::SERVector3<>::operator =(
        //            const Swing::SETRVector<3, > &)'
        //   existing declarations
        //       'Swing::SERVector3<> &Swing::SERVector3<>::operator =(
        //            const Swing::SETRVector<3, > &)'
        //       'Swing::SERVector3<> &Swing::SERVector3<>::operator =(
        //            const Swing::SERVector3<> &)'

        m_aTuple[0] = rV[0];
        m_aTuple[1] = rV[1];
        m_aTuple[2] = rV[2];

        return *this;
    }
#else
    SERVector3& operator = (const SETRVector<3,  ISIZE>& rV);
#endif

    // returns Dot(this, V)
    SETRational<ISIZE> Dot(const SERVector3& rV) const;

    // returns Cross(this, V)
    SERVector3 Cross(const SERVector3& rV) const;

    // returns Dot(this, Cross(U, V))
    SETRational<ISIZE> TripleScalar(const SERVector3& rU,  const SERVector3& rV)
        const;

protected:
    using SETRVector<3,  ISIZE>::m_aTuple;
};

#include "SERVector3.inl"

}

#endif
