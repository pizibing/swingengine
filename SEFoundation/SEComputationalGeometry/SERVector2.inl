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
//----------------------------------------------------------------------------
template <int ISIZE>
SERVector2<ISIZE>::SERVector2()
{
    // the vector is uninitialized
}
//----------------------------------------------------------------------------
template <int ISIZE>
SERVector2<ISIZE>::SERVector2(const SERVector2& rV)
{
    m_aTuple[0] = rV.m_aTuple[0];
    m_aTuple[1] = rV.m_aTuple[1];
}
//----------------------------------------------------------------------------
#ifndef SE_USING_VC70
template <int ISIZE>
SERVector2<ISIZE>::SERVector2(const SETRVector<2,  ISIZE>& rV)
{
    m_aTuple[0] = rV[0];
    m_aTuple[1] = rV[1];
}
#endif
//----------------------------------------------------------------------------
template <int ISIZE>
SERVector2<ISIZE>::SERVector2(const SETRational<ISIZE>& rX, 
    const SETRational<ISIZE>& rY)
{
    m_aTuple[0] = rX;
    m_aTuple[1] = rY;
}
//----------------------------------------------------------------------------
template <int ISIZE>
SERVector2<ISIZE>& SERVector2<ISIZE>::operator=(const SERVector2& rV)
{
    m_aTuple[0] = rV.m_aTuple[0];
    m_aTuple[1] = rV.m_aTuple[1];

    return *this;
}
//----------------------------------------------------------------------------
#ifndef SE_USING_VC70
template <int ISIZE>
SERVector2<ISIZE>& SERVector2<ISIZE>::operator=(const SETRVector<2,  ISIZE>& rV)
{
    m_aTuple[0] = rV[0];
    m_aTuple[1] = rV[1];

    return *this;
}
#endif
//----------------------------------------------------------------------------
template <int ISIZE>
SETRational<ISIZE> SERVector2<ISIZE>::X() const
{
    return m_aTuple[0];
}
//----------------------------------------------------------------------------
template <int ISIZE>
SETRational<ISIZE>& SERVector2<ISIZE>::X()
{
    return m_aTuple[0];
}
//----------------------------------------------------------------------------
template <int ISIZE>
SETRational<ISIZE> SERVector2<ISIZE>::Y() const
{
    return m_aTuple[1];
}
//----------------------------------------------------------------------------
template <int ISIZE>
SETRational<ISIZE>& SERVector2<ISIZE>::Y()
{
    return m_aTuple[1];
}
//----------------------------------------------------------------------------
template <int ISIZE>
SETRational<ISIZE> SERVector2<ISIZE>::Dot(const SERVector2& rV) const
{
    return m_aTuple[0]*rV.m_aTuple[0] + m_aTuple[1]*rV.m_aTuple[1];
}
//----------------------------------------------------------------------------
template <int ISIZE>
SERVector2<ISIZE> SERVector2<ISIZE>::Perp() const
{
    return SERVector2<ISIZE>(m_aTuple[1],  -m_aTuple[0]);
}
//----------------------------------------------------------------------------
template <int ISIZE>
SETRational<ISIZE> SERVector2<ISIZE>::DotPerp(const SERVector2& rV) const
{
    return m_aTuple[0]*rV.m_aTuple[1] - m_aTuple[1]*rV.m_aTuple[0];
}
//----------------------------------------------------------------------------