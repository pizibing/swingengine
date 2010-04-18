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
inline SEWave::FormatMode SEWave::GetFormat() const
{
    return m_eFormat;
}
//----------------------------------------------------------------------------
inline const std::string& SEWave::GetFormatName() const
{
    return ms_FormatName[m_eFormat];
}
//----------------------------------------------------------------------------
inline std::string SEWave::GetFormatName(int eFormat)
{
    return ms_FormatName[eFormat];
}
//----------------------------------------------------------------------------
inline int SEWave::GetBytesPerSample() const
{
    return ms_BytesPerSample[m_eFormat];
}
//----------------------------------------------------------------------------
inline int SEWave::GetBytesPerSample(int eFormat)
{
    return ms_BytesPerSample[eFormat];
}
//----------------------------------------------------------------------------
inline int SEWave::GetChannelsPerSample() const
{
    return ms_ChannelsPerSample[m_eFormat];
}
//----------------------------------------------------------------------------
inline int SEWave::GetChannelsPerSample(int eFormat)
{
    return ms_ChannelsPerSample[eFormat];
}
//----------------------------------------------------------------------------
inline unsigned int SEWave::GetFrequency() const
{
    return m_uiFrequency;
}
//----------------------------------------------------------------------------
inline int SEWave::GetDataSize() const
{
    return m_iDataSize;
}
//----------------------------------------------------------------------------
inline unsigned char* SEWave::GetData() const
{
    return m_pData;
}
//----------------------------------------------------------------------------
