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
inline IVector3::IVector3()
{
    // the vector is uninitialized
}
//----------------------------------------------------------------------------
inline IVector3::IVector3(const IVector3& rV)
{
    m_aiTuple[0] = rV.m_aiTuple[0];
    m_aiTuple[1] = rV.m_aiTuple[1];
    m_aiTuple[2] = rV.m_aiTuple[2];
}
//----------------------------------------------------------------------------
inline IVector3::IVector3(const TIVector<3>& rV)
{
    m_aiTuple[0] = rV[0];
    m_aiTuple[1] = rV[1];
    m_aiTuple[2] = rV[2];
}
//----------------------------------------------------------------------------
inline IVector3::IVector3(const SE_Int64& riX,  const SE_Int64& riY, 
    const SE_Int64& riZ)
{
    m_aiTuple[0] = riX;
    m_aiTuple[1] = riY;
    m_aiTuple[2] = riZ;
}
//----------------------------------------------------------------------------
inline IVector3& IVector3::operator=(const IVector3& rV)
{
    m_aiTuple[0] = rV.m_aiTuple[0];
    m_aiTuple[1] = rV.m_aiTuple[1];
    m_aiTuple[2] = rV.m_aiTuple[2];

    return *this;
}
//----------------------------------------------------------------------------
inline IVector3& IVector3::operator=(const TIVector<3>& rV)
{
    m_aiTuple[0] = rV[0];
    m_aiTuple[1] = rV[1];
    m_aiTuple[2] = rV[2];

    return *this;
}
//----------------------------------------------------------------------------
inline SE_Int64 IVector3::X() const
{
    return m_aiTuple[0];
}
//----------------------------------------------------------------------------
inline SE_Int64& IVector3::X()
{
    return m_aiTuple[0];
}
//----------------------------------------------------------------------------
inline SE_Int64 IVector3::Y() const
{
    return m_aiTuple[1];
}
//----------------------------------------------------------------------------
inline SE_Int64& IVector3::Y()
{
    return m_aiTuple[1];
}
//----------------------------------------------------------------------------
inline SE_Int64 IVector3::Z() const
{
    return m_aiTuple[2];
}
//----------------------------------------------------------------------------
inline SE_Int64& IVector3::Z()
{
    return m_aiTuple[2];
}
//----------------------------------------------------------------------------
inline SE_Int64 IVector3::Dot(const IVector3& rV) const
{
    return m_aiTuple[0]*rV.m_aiTuple[0] + m_aiTuple[1]*rV.m_aiTuple[1] +
        m_aiTuple[2]*rV.m_aiTuple[2];
}
//----------------------------------------------------------------------------
inline IVector3 IVector3::Cross(const IVector3& rV) const
{
    return IVector3(
        m_aiTuple[1]*rV.m_aiTuple[2] - m_aiTuple[2]*rV.m_aiTuple[1], 
        m_aiTuple[2]*rV.m_aiTuple[0] - m_aiTuple[0]*rV.m_aiTuple[2], 
        m_aiTuple[0]*rV.m_aiTuple[1] - m_aiTuple[1]*rV.m_aiTuple[0]);
}
//----------------------------------------------------------------------------
inline SE_Int64 IVector3::TripleScalar(const IVector3& rU, 
    const IVector3& rV) const
{
    return Dot(rU.Cross(rV));
}
//----------------------------------------------------------------------------