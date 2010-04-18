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
SERVector3<ISIZE>::SERVector3()
{
    // the vector is uninitialized
}
//----------------------------------------------------------------------------
template <int ISIZE>
SERVector3<ISIZE>::SERVector3(const SERVector3& rV)
{
    m_aTuple[0] = rV.m_aTuple[0];
    m_aTuple[1] = rV.m_aTuple[1];
    m_aTuple[2] = rV.m_aTuple[2];
}
//----------------------------------------------------------------------------
#ifndef SE_USING_VC70
template <int ISIZE>
SERVector3<ISIZE>::SERVector3(const SETRVector<3,  ISIZE>& rV)
{
    m_aTuple[0] = rV[0];
    m_aTuple[1] = rV[1];
    m_aTuple[2] = rV[2];
}
#endif
//----------------------------------------------------------------------------
template <int ISIZE>
SERVector3<ISIZE>::SERVector3(const SETRational<ISIZE>& rX, 
    const SETRational<ISIZE>& rY,  const SETRational<ISIZE>& rZ)
{
    m_aTuple[0] = rX;
    m_aTuple[1] = rY;
    m_aTuple[2] = rZ;
}
//----------------------------------------------------------------------------
template <int ISIZE>
SERVector3<ISIZE>& SERVector3<ISIZE>::operator=(const SERVector3& rV)
{
    m_aTuple[0] = rV.m_aTuple[0];
    m_aTuple[1] = rV.m_aTuple[1];
    m_aTuple[2] = rV.m_aTuple[2];

    return *this;
}
//----------------------------------------------------------------------------
#ifndef SE_USING_VC70
template <int ISIZE>
SERVector3<ISIZE>& SERVector3<ISIZE>::operator=(const SETRVector<3,  ISIZE>& 
    rV)
{
    m_aTuple[0] = rV[0];
    m_aTuple[1] = rV[1];
    m_aTuple[2] = rV[2];

    return *this;
}
#endif
//----------------------------------------------------------------------------
template <int ISIZE>
SETRational<ISIZE> SERVector3<ISIZE>::X() const
{
    return m_aTuple[0];
}
//----------------------------------------------------------------------------
template <int ISIZE>
SETRational<ISIZE>& SERVector3<ISIZE>::X()
{
    return m_aTuple[0];
}
//----------------------------------------------------------------------------
template <int ISIZE>
SETRational<ISIZE> SERVector3<ISIZE>::Y() const
{
    return m_aTuple[1];
}
//----------------------------------------------------------------------------
template <int ISIZE>
SETRational<ISIZE>& SERVector3<ISIZE>::Y()
{
    return m_aTuple[1];
}
//----------------------------------------------------------------------------
template <int ISIZE>
SETRational<ISIZE> SERVector3<ISIZE>::Z() const
{
    return m_aTuple[2];
}
//----------------------------------------------------------------------------
template <int ISIZE>
SETRational<ISIZE>& SERVector3<ISIZE>::Z()
{
    return m_aTuple[2];
}
//----------------------------------------------------------------------------
template <int ISIZE>
SETRational<ISIZE> SERVector3<ISIZE>::Dot(const SERVector3& rV) const
{
    return m_aTuple[0]*rV.m_aTuple[0] + m_aTuple[1]*rV.m_aTuple[1] +
        m_aTuple[2]*rV.m_aTuple[2];
}
//----------------------------------------------------------------------------
template <int ISIZE>
SERVector3<ISIZE> SERVector3<ISIZE>::Cross(const SERVector3& rV) const
{
    return SERVector3<ISIZE>(
        m_aTuple[1]*rV.m_aTuple[2] - m_aTuple[2]*rV.m_aTuple[1], 
        m_aTuple[2]*rV.m_aTuple[0] - m_aTuple[0]*rV.m_aTuple[2], 
        m_aTuple[0]*rV.m_aTuple[1] - m_aTuple[1]*rV.m_aTuple[0]);
}
//----------------------------------------------------------------------------
template <int ISIZE>
SETRational<ISIZE> SERVector3<ISIZE>::TripleScalar(const SERVector3& rU, 
    const SERVector3& rV) const
{
    return Dot(rU.Cross(rV));
}
//----------------------------------------------------------------------------