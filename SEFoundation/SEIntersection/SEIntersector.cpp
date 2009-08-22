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

#include "SEFoundationPCH.h"
#include "SEIntersector.h"

namespace Swing
{
//----------------------------------------------------------------------------
template <class Real, class TVector>
Intersector<Real, TVector>::Intersector()
{
    m_fContactTime = (Real)0.0;
    m_iIntersectionType = IT_EMPTY;
}
//----------------------------------------------------------------------------
template <class Real, class TVector>
Intersector<Real, TVector>::~Intersector()
{
}
//----------------------------------------------------------------------------
template <class Real, class TVector>
Real Intersector<Real, TVector>::GetContactTime() const
{
    return m_fContactTime;
}
//----------------------------------------------------------------------------
template <class Real, class TVector>
int Intersector<Real, TVector>::GetIntersectionType() const
{
    return m_iIntersectionType;
}
//----------------------------------------------------------------------------
template <class Real, class TVector>
bool Intersector<Real, TVector>::Test()
{
    // 由派生类负责实现.
    SE_ASSERT( false );

    return false;
}
//----------------------------------------------------------------------------
template <class Real, class TVector>
bool Intersector<Real, TVector>::Find()
{
    // 由派生类负责实现.
    SE_ASSERT( false );

    return false;
}
//----------------------------------------------------------------------------
template <class Real, class TVector>
bool Intersector<Real, TVector>::Test(Real, const TVector&, const TVector&)
{
    // 由派生类负责实现.
    SE_ASSERT( false );

    return false;
}
//----------------------------------------------------------------------------
template <class Real, class TVector>
bool Intersector<Real, TVector>::Find(Real, const TVector&, const TVector&)
{
    // 由派生类负责实现.
    SE_ASSERT( false );

    return false;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// explicit instantiation
//----------------------------------------------------------------------------
template SE_FOUNDATION_API
class Intersector<float, Vector2f>;

template SE_FOUNDATION_API
class Intersector<float, Vector3f>;

//template SE_FOUNDATION_API
//class Intersector<double, Vector2d>;
//
//template SE_FOUNDATION_API
//class Intersector<double, Vector3d>;
//----------------------------------------------------------------------------
}
