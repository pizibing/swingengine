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
#include "SEString.h"
#include "SEStringHashTable.h"

namespace Swing
{

class Wave;

//----------------------------------------------------------------------------
// 名称:wave资源管理类
// 说明:只索引资源,不释放
// 作者:Sun Che
// 时间:20090618
//----------------------------------------------------------------------------
class SE_AUDIO_API WaveCatalog
{
public:
    WaveCatalog(const String& rName);
    ~WaveCatalog(void);

    const String& GetName(void) const;
    bool Insert(Wave* pWave);
    bool Remove(Wave* pWave);
    Wave* Find(const String& rWaveName);
    bool PrintContents(const String& rFileName) const;

    static void SetActive(WaveCatalog* pActive);
    static WaveCatalog* GetActive(void);

private:
    enum { WAVE_MAP_SIZE = 256 };
    String m_Name;
    StringHashTable<Wave*> m_Entry;
    ObjectPtr m_spDefaultWave;

    static const String ms_NullString;
    static const String ms_DefaultString;
    static WaveCatalog* ms_pActive;
};

}

#endif
