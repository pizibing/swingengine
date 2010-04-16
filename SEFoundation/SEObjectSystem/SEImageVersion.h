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

#ifndef Swing_ImageVersion_H
#define Swing_ImageVersion_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SESystem.h"

// Images are stored in files with extension wmif.  The header is of the
// form "Wild Magic Image File 4.xx" where the major version is 4 and the
// the minor version is xx in [00,99].  The length of the string is 26, but
// the null terminator is written to disk, so total number of file bytes used
// by the version is 27.  The current version is "4.00"

namespace Swing
{

class SE_FOUNDATION_API SEImageVersion
{
public:
    static const int MAJOR;     // 4
    static const int MINOR;     // 0
    static const char LABEL[];  // "Wild Magic Image File 4.00"
    static const int LENGTH;    // 27 = strlen(LABEL)+1
    static const SEImageVersion CURRENT;

    SEImageVersion(int iMajor = -1, int iMinor = -1);
    SEImageVersion(const char* pString);

    int GetMajor(void) const;
    int GetMinor(void) const;

    // The version is valid if major is 4 and minor in [0,99].
    bool IsValid(void) const;

    // For comparisons of versions.  This is useful whenever a change to the
    // Image class causes a file format change.
    bool operator == (const SEImageVersion& rVersion) const;
    bool operator != (const SEImageVersion& rVersion) const;
    bool operator <  (const SEImageVersion& rVersion) const;
    bool operator <= (const SEImageVersion& rVersion) const;
    bool operator >  (const SEImageVersion& rVersion) const;
    bool operator >= (const SEImageVersion& rVersion) const;

protected:
    int GetCombined(void) const;  // 100*major + minor

    int m_iMajor, m_iMinor;
};

}

#endif
