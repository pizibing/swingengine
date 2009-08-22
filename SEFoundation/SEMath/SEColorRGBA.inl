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
inline ColorRGBA::operator const float*() const
{
    return m_fData;
}
//----------------------------------------------------------------------------
inline ColorRGBA::operator float*()
{
    return m_fData;
}
//----------------------------------------------------------------------------
inline float ColorRGBA::operator[](int i) const
{
    SE_ASSERT( 0 <= i && i <= 3 );

    if( i < 0 )
    {
        i = 0;
    }
    else if( i > 3 )
    {
        i = 3;
    }

    return m_fData[i];
}
//----------------------------------------------------------------------------
inline float& ColorRGBA::operator[](int i)
{
    SE_ASSERT( 0 <= i && i <= 3 );

    if( i < 0 )
    {
        i = 0;
    }
    else if( i > 3 )
    {
        i = 3;
    }

    return m_fData[i];
}
//----------------------------------------------------------------------------
inline int ColorRGBA::CompareData(const ColorRGBA& rColor) const
{
    return memcmp(m_fData, rColor.m_fData, 4*sizeof(float));
}
//----------------------------------------------------------------------------
