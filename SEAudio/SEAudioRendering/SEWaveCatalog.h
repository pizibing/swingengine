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

#ifndef Swing_WaveCatalog_H
#define Swing_WaveCatalog_H

#include "SEAudioLIB.h"
#include "SEObject.h"
#include "SEMainMCR.h"
#include "SEStringHashTable.h"

namespace Swing
{

class SEWave;

//----------------------------------------------------------------------------
// Description:只索引资源,不释放
// Author:Sun Che
// Date:20090618
//----------------------------------------------------------------------------
class SE_AUDIO_API SEWaveCatalog
{
public:
    SEWaveCatalog(const std::string& rName);
    ~SEWaveCatalog(void);

    const std::string& GetName(void) const;
    bool Insert(SEWave* pWave);
    bool Remove(SEWave* pWave);
    SEWave* Find(const std::string& rWaveName);
    bool PrintContents(const std::string& rFileName) const;

    static void SetActive(SEWaveCatalog* pActive);
    static SEWaveCatalog* GetActive(void);

private:
    enum { WAVE_MAP_SIZE = 256 };
    std::string m_Name;
    SEStringHashTable<SEWave*> m_Entry;
    SEObjectPtr m_spDefaultWave;

    static const std::string ms_NullString;
    static const std::string ms_DefaultString;
    static SEWaveCatalog* ms_pActive;
};

}

#endif
