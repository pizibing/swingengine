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
inline Image::FormatMode Image::GetFormat() const
{
    return m_eFormat;
}
//----------------------------------------------------------------------------
inline const std::string& Image::GetFormatName() const
{
    return ms_FormatName[m_eFormat];
}
//----------------------------------------------------------------------------
inline std::string Image::GetFormatName(int eFormat)
{
    return ms_FormatName[eFormat];
}
//----------------------------------------------------------------------------
inline bool Image::IsDepthImage() const
{
    return m_eFormat == IT_DEPTH16
        || m_eFormat == IT_DEPTH24
        || m_eFormat == IT_DEPTH32;
}
//----------------------------------------------------------------------------
inline bool Image::IsCubeImage() const
{
    return m_eFormat == IT_CUBE_RGB888 || m_eFormat == IT_CUBE_RGBA8888;
}
//----------------------------------------------------------------------------
inline int Image::GetBytesPerPixel() const
{
    return ms_BytesPerPixel[m_eFormat];
}
//----------------------------------------------------------------------------
inline int Image::GetBytesPerPixel(int eFormat)
{
    return ms_BytesPerPixel[eFormat];
}
//----------------------------------------------------------------------------
inline int Image::GetDimension() const
{
    return m_iDimension;
}
//----------------------------------------------------------------------------
inline int Image::GetBound(int i) const
{
    SE_ASSERT( 0 <= i && i < 3 );

    return m_Bound[i];
}
//----------------------------------------------------------------------------
inline int Image::GetCount() const
{
    return m_iCount;
}
//----------------------------------------------------------------------------
inline unsigned char* Image::GetData() const
{
    return m_pData;
}
//----------------------------------------------------------------------------
inline unsigned char* Image::operator()(int i)
{
    return m_pData + i*ms_BytesPerPixel[m_eFormat];
}
//----------------------------------------------------------------------------
