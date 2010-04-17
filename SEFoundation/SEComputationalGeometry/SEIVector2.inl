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
inline SEIVector2::SEIVector2()
{
    // the vector is uninitialized
}
//----------------------------------------------------------------------------
inline SEIVector2::SEIVector2(const SEIVector2& rV)
{
    m_aiTuple[0] = rV.m_aiTuple[0];
    m_aiTuple[1] = rV.m_aiTuple[1];
}
//----------------------------------------------------------------------------
inline SEIVector2::SEIVector2(const SETIVector<2>& rV)
{
    m_aiTuple[0] = rV[0];
    m_aiTuple[1] = rV[1];
}
//----------------------------------------------------------------------------
inline SEIVector2::SEIVector2(const SE_Int64& riX,  const SE_Int64& riY)
{
    m_aiTuple[0] = riX;
    m_aiTuple[1] = riY;
}
//----------------------------------------------------------------------------
inline SEIVector2& SEIVector2::operator=(const SEIVector2& rV)
{
    m_aiTuple[0] = rV.m_aiTuple[0];
    m_aiTuple[1] = rV.m_aiTuple[1];

    return *this;
}
//----------------------------------------------------------------------------
inline SEIVector2& SEIVector2::operator=(const SETIVector<2>& rV)
{
    m_aiTuple[0] = rV[0];
    m_aiTuple[1] = rV[1];

    return *this;
}
//----------------------------------------------------------------------------
inline SE_Int64 SEIVector2::X() const
{
    return m_aiTuple[0];
}
//----------------------------------------------------------------------------
inline SE_Int64& SEIVector2::X()
{
    return m_aiTuple[0];
}
//----------------------------------------------------------------------------
inline SE_Int64 SEIVector2::Y() const
{
    return m_aiTuple[1];
}
//----------------------------------------------------------------------------
inline SE_Int64& SEIVector2::Y()
{
    return m_aiTuple[1];
}
//----------------------------------------------------------------------------
inline SE_Int64 SEIVector2::Dot(const SEIVector2& rV) const
{
    return m_aiTuple[0]*rV.m_aiTuple[0] + m_aiTuple[1]*rV.m_aiTuple[1];
}
//----------------------------------------------------------------------------
inline SEIVector2 SEIVector2::Perp() const
{
    return SEIVector2(m_aiTuple[1],  -m_aiTuple[0]);
}
//----------------------------------------------------------------------------
inline SE_Int64 SEIVector2::DotPerp(const SEIVector2& rV) const
{
    return m_aiTuple[0]*rV.m_aiTuple[1] - m_aiTuple[1]*rV.m_aiTuple[0];
}
//----------------------------------------------------------------------------