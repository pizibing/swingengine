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

#include "SEAudioPCH.h"
#include "SEWaveVersion.h"

using namespace Swing;

const int SEWaveVersion::MAJOR = 1;
const int SEWaveVersion::MINOR = 0;
const char SEWaveVersion::LABEL[] = "Swing Engine Wave File 1.00";
const int SEWaveVersion::LENGTH = 28;
const SEWaveVersion SEWaveVersion::CURRENT(MAJOR, MINOR);

//----------------------------------------------------------------------------
SEWaveVersion::SEWaveVersion(int iMajor, int iMinor)
{
    m_iMajor = iMajor;
    m_iMinor = iMinor;
}
//----------------------------------------------------------------------------
SEWaveVersion::SEWaveVersion(const char* pString)
{
    m_iMajor = -1;
    m_iMinor = -1;

    if( pString
    &&  strlen(pString) >= LENGTH-1
    &&  pString[LENGTH-1] == 0
    &&  strncmp(pString, LABEL, LENGTH-5) == 0 )  // 5 = strlen(" x.yy")
    {
        // The version string is "x.yy".
        const char* pVersion = pString + LENGTH - 5;
        m_iMajor = (int)(pVersion[0] - '0');
        m_iMinor = 10*(int)(pVersion[2] - '0') + (int)(pVersion[3] - '0');
    }
}
//----------------------------------------------------------------------------
bool SEWaveVersion::IsValid() const
{
    return m_iMajor == MAJOR && 0 <= m_iMinor && m_iMinor < 100;
}
//----------------------------------------------------------------------------
int SEWaveVersion::GetMajor() const
{
    return m_iMajor;
}
//----------------------------------------------------------------------------
int SEWaveVersion::GetMinor() const
{
    return m_iMinor;
}
//----------------------------------------------------------------------------
int SEWaveVersion::GetCombined() const
{
    return 100*m_iMajor + m_iMinor;
}
//----------------------------------------------------------------------------
bool SEWaveVersion::operator==(const SEWaveVersion& rVersion) const
{
    return GetCombined() == rVersion.GetCombined();
}
//----------------------------------------------------------------------------
bool SEWaveVersion::operator!=(const SEWaveVersion& rVersion) const
{
    return GetCombined() != rVersion.GetCombined();
}
//----------------------------------------------------------------------------
bool SEWaveVersion::operator<(const SEWaveVersion& rVersion) const
{
    return GetCombined() < rVersion.GetCombined();
}
//----------------------------------------------------------------------------
bool SEWaveVersion::operator<=(const SEWaveVersion& rVersion) const
{
    return GetCombined() <= rVersion.GetCombined();
}
//----------------------------------------------------------------------------
bool SEWaveVersion::operator>(const SEWaveVersion& rVersion) const
{
    return GetCombined() > rVersion.GetCombined();
}
//----------------------------------------------------------------------------
bool SEWaveVersion::operator>=(const SEWaveVersion& rVersion) const
{
    return GetCombined() >= rVersion.GetCombined();
}
//----------------------------------------------------------------------------
