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
#include "SEStreamVersion.h"

using namespace Swing;

const int SEStreamVersion::MAJOR = 1;
const int SEStreamVersion::MINOR = 0;
const char SEStreamVersion::LABEL[] = "Swing Engine Object File 1.00";
const int SEStreamVersion::LENGTH = 30;
const SEStreamVersion SEStreamVersion::CURRENT(MAJOR,MINOR);

//----------------------------------------------------------------------------
SEStreamVersion::SEStreamVersion(int iMajor, int iMinor)
{
    m_iMajor = iMajor;
    m_iMinor = iMinor;
}
//----------------------------------------------------------------------------
SEStreamVersion::SEStreamVersion(const char* pString)
{
    m_iMajor = -1;
    m_iMinor = -1;

    if( pString 
        &&  strlen(pString) >= LENGTH-1 
        &&  pString[LENGTH-1] == 0 
        &&  strncmp(pString, LABEL, LENGTH-5) == 0 )  // 5 = strlen(" 1.xx")
    {
        // The version string is "x.yy".
        const char* acVersion = pString + LENGTH - 5;
        m_iMajor = (int)(acVersion[0]-'0');
        m_iMinor = 10*(int)(acVersion[2]-'0') + (int)(acVersion[3]-'0');
    }
}
//----------------------------------------------------------------------------
bool SEStreamVersion::IsValid() const
{
    return m_iMajor == SEStreamVersion::MAJOR
        && 0 <= m_iMinor && m_iMinor < 100;
}
//----------------------------------------------------------------------------
int SEStreamVersion::GetMajor() const
{
    return m_iMajor;
}
//----------------------------------------------------------------------------
int SEStreamVersion::GetMinor() const
{
    return m_iMinor;
}
//----------------------------------------------------------------------------
int SEStreamVersion::GetCombined() const
{
    return 100*m_iMajor + m_iMinor;
}
//----------------------------------------------------------------------------
bool SEStreamVersion::operator==(const SEStreamVersion& rVersion) const
{
    SE_ASSERT( IsValid() && rVersion.IsValid() );
    return GetCombined() == rVersion.GetCombined();
}
//----------------------------------------------------------------------------
bool SEStreamVersion::operator!=(const SEStreamVersion& rVersion) const
{
    SE_ASSERT( IsValid() && rVersion.IsValid() );
    return GetCombined() != rVersion.GetCombined();
}
//----------------------------------------------------------------------------
bool SEStreamVersion::operator<(const SEStreamVersion& rVersion) const
{
    SE_ASSERT( IsValid() && rVersion.IsValid() );
    return GetCombined() < rVersion.GetCombined();
}
//----------------------------------------------------------------------------
bool SEStreamVersion::operator<=(const SEStreamVersion& rVersion) const
{
    SE_ASSERT( IsValid() && rVersion.IsValid() );
    return GetCombined() <= rVersion.GetCombined();
}
//----------------------------------------------------------------------------
bool SEStreamVersion::operator>(const SEStreamVersion& rVersion) const
{
    SE_ASSERT( IsValid() && rVersion.IsValid() );
    return GetCombined() > rVersion.GetCombined();
}
//----------------------------------------------------------------------------
bool SEStreamVersion::operator>=(const SEStreamVersion& rVersion) const
{
    SE_ASSERT( IsValid() && rVersion.IsValid() );
    return GetCombined() >= rVersion.GetCombined();
}
//----------------------------------------------------------------------------
