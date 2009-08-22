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

/*
 * Copyright (c) 2006, Creative Labs Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met:
 * 
 *     * Redistributions of source code must retain the above copyright 
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright 
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Creative Labs Inc. nor the names of its 
 *       contributors may be used to endorse or promote products derived 
 *       from this software without specific prior written permission.
 */

#ifndef Swing_WaveParser_H
#define Swing_WaveParser_H

#include <windows.h>
#include <stdio.h>
#include "SEWave.h"

#define MAX_NUM_WAVEID 1024

//----------------------------------------------------------------------------
enum WAVEFILETYPE
{
    WF_EX  = 1,
    WF_EXT = 2
};
//----------------------------------------------------------------------------
enum WAVERESULT
{
    WR_OK = 0,
    WR_INVALIDFILENAME                  = - 1,
    WR_BADWAVEFILE                      = - 2,
    WR_INVALIDPARAM                     = - 3,
    WR_INVALIDWAVEID                    = - 4,
    WR_NOTSUPPORTEDYET                  = - 5,
    WR_WAVEMUSTBEMONO                   = - 6,
    WR_WAVEMUSTBEWAVEFORMATPCM          = - 7,
    WR_WAVESMUSTHAVESAMEBITRESOLUTION   = - 8,
    WR_WAVESMUSTHAVESAMEFREQUENCY       = - 9,
    WR_WAVESMUSTHAVESAMEBITRATE         = -10,
    WR_WAVESMUSTHAVESAMEBLOCKALIGNMENT  = -11,
    WR_OFFSETOUTOFDATARANGE             = -12,
    WR_FILEERROR                        = -13,
    WR_OUTOFMEMORY                      = -14,
    WR_INVALIDSPEAKERPOS                = -15,
    WR_INVALIDWAVEFILETYPE              = -16,
    WR_NOTWAVEFORMATEXTENSIBLEFORMAT    = -17
};
//----------------------------------------------------------------------------
#ifndef _WAVEFORMATEX_
#define _WAVEFORMATEX_
typedef struct tWAVEFORMATEX
{
    WORD    wFormatTag;
    WORD    nChannels;
    DWORD   nSamplesPerSec;
    DWORD   nAvgBytesPerSec;
    WORD    nBlockAlign;
    WORD    wBitsPerSample;
    WORD    cbSize;
} WAVEFORMATEX;
#endif /* _WAVEFORMATEX_ */
//----------------------------------------------------------------------------
#ifndef _WAVEFORMATEXTENSIBLE_
#define _WAVEFORMATEXTENSIBLE_
typedef struct {
    WAVEFORMATEX    Format;
    union {
        WORD wValidBitsPerSample;       /* bits of precision  */
        WORD wSamplesPerBlock;          /* valid if wBitsPerSample==0 */
        WORD wReserved;                 /* If neither applies, set to zero. */
    } Samples;
    DWORD           dwChannelMask;      /* which channels are */
                                        /* present in stream  */
    GUID            SubFormat;
} WAVEFORMATEXTENSIBLE, *PWAVEFORMATEXTENSIBLE;
#endif // !_WAVEFORMATEXTENSIBLE_
//----------------------------------------------------------------------------
typedef struct
{
    WAVEFILETYPE wfType;
    // for non-WAVEFORMATEXTENSIBLE wavefiles, 
    // the header is stored in the Format member of wfEXT.
    WAVEFORMATEXTENSIBLE wfEXT;
    char *pData;
    unsigned int uiDataSize;
    FILE *pFile;
    unsigned int uiDataOffset;
} WAVEFILEINFO, *LPWAVEFILEINFO;
//----------------------------------------------------------------------------

// OpenAL提供的回调函数指针类型定义.
typedef int (__cdecl *PFNALGETENUMVALUE)( const char *szEnumName );
// wave id类型定义.
typedef int	WAVEID;

//----------------------------------------------------------------------------
// 名称:wave parser类
// 说明:
// 作者:Sun Che
// 时间:20090622
//----------------------------------------------------------------------------
class WaveParser
{
public:
    WaveParser(void);
    virtual ~WaveParser(void);

    WAVERESULT LoadWaveFile(const char* acFileName, WAVEID* pWaveID);
    WAVERESULT OpenWaveFile(const char* acFileName, WAVEID* pWaveID);
    WAVERESULT ReadWaveData(WAVEID WaveID, void* pData, 
        unsigned int uiDataSize, unsigned int* puiBytesWritten);

    WAVERESULT SetWaveDataOffset(WAVEID WaveID, unsigned int uiOffset);
    WAVERESULT GetWaveDataOffset(WAVEID WaveID, unsigned int* puiOffset);
    WAVERESULT GetWaveType(WAVEID WaveID, WAVEFILETYPE* pwfType);
    WAVERESULT GetWaveFormatExHeader(WAVEID WaveID, WAVEFORMATEX* pWFEX);
    WAVERESULT GetWaveFormatExtensibleHeader(WAVEID WaveID, 
        WAVEFORMATEXTENSIBLE* pWFEXT);
    WAVERESULT GetWaveData(WAVEID WaveID, void** ppAudioData);
    WAVERESULT GetWaveSize(WAVEID WaveID, unsigned int* puiDataSize);
    WAVERESULT GetWaveFrequency(WAVEID WaveID, unsigned int* puiFrequency);

    // support for OpenAL wave format.
    WAVERESULT GetWaveALBufferFormat(WAVEID WaveID,
        PFNALGETENUMVALUE pfnGetEnumValue, unsigned int* puiFormat);
    // support for Swing Engine wave format.
    WAVERESULT GetWaveSEWaveFormat(WAVEID WaveID,
        Swing::Wave::FormatMode* peFormat);

    WAVERESULT DeleteWaveFile(WAVEID WaveID);

    char* GetErrorString(WAVERESULT wr, char* acErrorString,
        unsigned int uiSizeOfErrorString);
    bool IsWaveID(WAVEID WaveID);

private:
    WAVERESULT ParseFile(const char* acFileName, LPWAVEFILEINFO pWaveInfo);
    WAVEID InsertWaveID(LPWAVEFILEINFO pWaveFileInfo);

    LPWAVEFILEINFO m_WaveIDs[MAX_NUM_WAVEID];
};

#endif
