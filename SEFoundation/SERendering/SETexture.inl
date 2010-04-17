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
inline void Texture::SetImage(Image* pImage)
{
    m_spImage = pImage;
}
//----------------------------------------------------------------------------
inline Image* Texture::GetImage()
{
    return m_spImage;
}
//----------------------------------------------------------------------------
inline const Image* Texture::GetImage() const
{
    return m_spImage;
}
//----------------------------------------------------------------------------
inline void Texture::SetFilterType(FilterType eFType)
{
    m_eFType = eFType;
}
//----------------------------------------------------------------------------
inline Texture::FilterType Texture::GetFilterType() const
{
    return m_eFType;
}
//----------------------------------------------------------------------------
inline void Texture::SetWrapType(int i, WrapType eWType)
{
    SE_ASSERT( 0 <= i && i < 3 );

    m_eWrapTypes[i] = eWType;
}
//----------------------------------------------------------------------------
inline Texture::WrapType Texture::GetWrapType(int i) const
{
    SE_ASSERT( 0 <= i && i < 3 );

    return m_eWrapTypes[i];
}
//----------------------------------------------------------------------------
inline void Texture::SetBorderColor(const SEColorRGBA& rBorderColor)
{
    m_BorderColor = rBorderColor;
}
//----------------------------------------------------------------------------
inline SEColorRGBA Texture::GetBorderColor() const
{
    return m_BorderColor;
}
//----------------------------------------------------------------------------
inline bool Texture::IsOffscreenTexture() const
{
    return m_bOffscreenTexture;
}
//----------------------------------------------------------------------------
inline void Texture::SetOffscreenTexture(bool bOffscreenTexture)
{
    m_bOffscreenTexture = bOffscreenTexture;
}
//----------------------------------------------------------------------------
