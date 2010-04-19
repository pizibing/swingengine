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

#ifndef Swing_WaveVersion_H
#define Swing_WaveVersion_H

#include "SEAudioLIB.h"
#include "SESystem.h"

// Waves are stored in files with extension sewf. The header is of the
// form "Swing Engine Wave File 1.xx" where the major version is 1 and the
// the minor version is xx in [00,99]. The length of the string is 27, but
// the null terminator is written to disk, so total number of file bytes used
// by the version is 28. The current version is "1.00"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20090617
//----------------------------------------------------------------------------
class SE_AUDIO_API SEWaveVersion
{
public:
    static const int MAJOR;     // 1
    static const int MINOR;     // 0
    static const char LABEL[];  // "Swing Engine Wave File 1.00"
    static const int LENGTH;    // 28 = strlen(LABEL)+1
    static const SEWaveVersion CURRENT;

    SEWaveVersion(int iMajor = -1, int iMinor = -1);
    SEWaveVersion(const char* pString);

    int GetMajor(void) const;
    int GetMinor(void) const;

    // The version is valid if major is 1 and minor in [0,99].
    bool IsValid(void) const;

    // For comparisons of versions. This is useful whenever a change to the
    // SEWave class causes a file format change.
    bool operator == (const SEWaveVersion& rVersion) const;
    bool operator != (const SEWaveVersion& rVersion) const;
    bool operator <  (const SEWaveVersion& rVersion) const;
    bool operator <= (const SEWaveVersion& rVersion) const;
    bool operator >  (const SEWaveVersion& rVersion) const;
    bool operator >= (const SEWaveVersion& rVersion) const;

protected:
    int GetCombined(void) const;  // 100*major + minor

    int m_iMajor, m_iMinor;
};

}

#endif
