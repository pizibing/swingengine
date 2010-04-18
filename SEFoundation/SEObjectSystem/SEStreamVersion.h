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

#ifndef Swing_StreamVersion_H
#define Swing_StreamVersion_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SESystem.h"

// Scene graphs are stored in files with extension wmof.  The header is of the
// form "Wild Magic Object File 3.xx" where the major version is 4 and the
// the minor version is xx in [00,99].  The length of the string is 27, but
// the null terminator is written to disk, so total number of file bytes used
// by the version is 28.  The current version is "3.02"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20080329
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEStreamVersion
{
public:
    static const int MAJOR;     // 3
    static const int MINOR;     // 2
    static const char LABEL[];  // "Wild Magic Object File 3.02"
    static const int LENGTH;    // 28 = strlen(LABEL)+1
    static const SEStreamVersion CURRENT;

    SEStreamVersion (int iMajor = MAJOR, int iMinor = MINOR);
    SEStreamVersion (const char* pString);

    int GetMajor () const;
    int GetMinor () const;

    // The version is valid if major is 3 and minor in [0,99].
    bool IsValid () const;

    // For comparisons of versions.  This is useful in the SEStream support in
    // an SEObject-derived class whenever a change to that class causes a file
    // format change.
    bool operator== (const SEStreamVersion& rVersion) const;
    bool operator!= (const SEStreamVersion& rVersion) const;
    bool operator<  (const SEStreamVersion& rVersion) const;
    bool operator<= (const SEStreamVersion& rVersion) const;
    bool operator>  (const SEStreamVersion& rVersion) const;
    bool operator>= (const SEStreamVersion& rVersion) const;

protected:
    int GetCombined () const;  // 100*major + minor

    int m_iMajor, m_iMinor;
};

}

#endif
