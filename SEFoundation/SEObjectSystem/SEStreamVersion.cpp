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

const int StreamVersion::MAJOR = 3;
const int StreamVersion::MINOR = 2;
const char StreamVersion::LABEL[] = "Wild Magic Object File 3.02";
const int StreamVersion::LENGTH = 28;
const StreamVersion StreamVersion::CURRENT(MAJOR,MINOR);

//----------------------------------------------------------------------------
StreamVersion::StreamVersion (int iMajor, int iMinor)
{
    m_iMajor = iMajor;
    m_iMinor = iMinor;
}
//----------------------------------------------------------------------------
StreamVersion::StreamVersion (const char* pString)
{
    m_iMajor = -1;
    m_iMinor = -1;

    if( pString
    &&  strlen(pString) >= LENGTH-1
    &&  pString[LENGTH-1] == 0
    &&  strncmp(pString,LABEL,LENGTH-5) == 0)  // 5 = strlen(" 3.xx")
    {
        // The version string is "x.yy".
        const char* acVersion = pString + LENGTH - 5;
        m_iMajor = (int)(acVersion[0]-'0');
        m_iMinor = 10*(int)(acVersion[2]-'0') + (int)(acVersion[3]-'0');
    }
}
//----------------------------------------------------------------------------
bool StreamVersion::IsValid () const
{
    return m_iMajor == StreamVersion::MAJOR
        && 0 <= m_iMinor && m_iMinor < 100;
}
//----------------------------------------------------------------------------
int StreamVersion::GetMajor () const
{
    return m_iMajor;
}
//----------------------------------------------------------------------------
int StreamVersion::GetMinor () const
{
    return m_iMinor;
}
//----------------------------------------------------------------------------
int StreamVersion::GetCombined () const
{
    return 100*m_iMajor + m_iMinor;
}
//----------------------------------------------------------------------------
bool StreamVersion::operator== (const StreamVersion& rVersion) const
{
    SE_ASSERT(IsValid() && rVersion.IsValid());
    return GetCombined() == rVersion.GetCombined();
}
//----------------------------------------------------------------------------
bool StreamVersion::operator!= (const StreamVersion& rVersion) const
{
    SE_ASSERT(IsValid() && rVersion.IsValid());
    return GetCombined() != rVersion.GetCombined();
}
//----------------------------------------------------------------------------
bool StreamVersion::operator< (const StreamVersion& rVersion) const
{
    SE_ASSERT(IsValid() && rVersion.IsValid());
    return GetCombined() < rVersion.GetCombined();
}
//----------------------------------------------------------------------------
bool StreamVersion::operator<= (const StreamVersion& rVersion) const
{
    SE_ASSERT(IsValid() && rVersion.IsValid());
    return GetCombined() <= rVersion.GetCombined();
}
//----------------------------------------------------------------------------
bool StreamVersion::operator> (const StreamVersion& rVersion) const
{
    SE_ASSERT(IsValid() && rVersion.IsValid());
    return GetCombined() > rVersion.GetCombined();
}
//----------------------------------------------------------------------------
bool StreamVersion::operator>= (const StreamVersion& rVersion) const
{
    SE_ASSERT(IsValid() && rVersion.IsValid());
    return GetCombined() >= rVersion.GetCombined();
}
//----------------------------------------------------------------------------
