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

#include "SEWaveParser.h"

// ks.h中,声明类成员无名称struct时,避免这个编译器4级警告.
#pragma warning(disable:4201)
#include <ks.h>
#include <ksmedia.h>
#include <errno.h>

#pragma pack(push, 4)
//----------------------------------------------------------------------------
typedef struct
{
    char            acRIFF[4];
    unsigned long   ulRIFFSize;
    char            acWAVE[4];
} WAVEFILEHEADER;
//----------------------------------------------------------------------------
typedef struct
{
    char            acChunkName[4];
    unsigned long   ulChunkSize;
} RIFFCHUNK;
//----------------------------------------------------------------------------
typedef struct
{
    unsigned short  usFormatTag;
    unsigned short  usChannels;
    unsigned long   ulSamplesPerSec;
    unsigned long   ulAvgBytesPerSec;
    unsigned short  usBlockAlign;
    unsigned short  usBitsPerSample;
    unsigned short  usSize;
    unsigned short  usReserved;
    unsigned long   ulChannelMask;
    GUID            guidSubFormat;
} WAVEFMT;
//----------------------------------------------------------------------------
#pragma pack(pop)

#if _MSC_VER <= 1310 
//----------------------------------------------------------------------------
// Wrap around the deprecated functions for VS2003 support
int fopen_s(FILE** pFile, const char* filename, const char* mode)
{
    *pFile = fopen(filename, mode);
    
    return *pFile ? 0 : EBADF;
}
//----------------------------------------------------------------------------
int strncpy_s(char* strDest, size_t numberOfElements, const char* strSource,
    size_t count)
{
    strncpy(strDest, strSource, count);

    return 0;
}
//----------------------------------------------------------------------------
#endif

//----------------------------------------------------------------------------
WaveParser::WaveParser()
{
    memset(&m_WaveIDs, 0, sizeof(m_WaveIDs));
}
//----------------------------------------------------------------------------
WaveParser::~WaveParser()
{
    for( int i = 0; i < MAX_NUM_WAVEID; i++ )
    {
        if( m_WaveIDs[i] )
        {
            if( m_WaveIDs[i]->pData )
            {
                delete m_WaveIDs[i]->pData;
            }

            if( m_WaveIDs[i]->pFile )
            {
                fclose(m_WaveIDs[i]->pFile);
            }

            delete m_WaveIDs[i];
            m_WaveIDs[i] = 0;
        }
    }
}
//----------------------------------------------------------------------------
WAVERESULT WaveParser::LoadWaveFile(const char* acFileName, WAVEID* pWaveID)
{
    WAVERESULT wr = WR_OUTOFMEMORY;
    LPWAVEFILEINFO pWaveInfo;

    pWaveInfo = new WAVEFILEINFO;
    if( pWaveInfo )
	{
        if( SUCCEEDED(wr = ParseFile(acFileName, pWaveInfo)) )
        {
            // Allocate memory for sample data.
            pWaveInfo->pData = new char[pWaveInfo->uiDataSize];
            if( pWaveInfo->pData )
            {
                // Seek to start of audio data.
                fseek(pWaveInfo->pFile, pWaveInfo->uiDataOffset, SEEK_SET);

                // Read Sample Data.
                if( fread(pWaveInfo->pData, 1, pWaveInfo->uiDataSize, 
                    pWaveInfo->pFile) == pWaveInfo->uiDataSize )
                {
                    int i;
                    for( i = 0; i < MAX_NUM_WAVEID; i++ )
                    {
                        if( !m_WaveIDs[i] )
                        {
                            m_WaveIDs[i] = pWaveInfo;
                            *pWaveID = i;
                            wr = WR_OK;
                            break;
                        }
                    }

                    if( i == MAX_NUM_WAVEID )
                    {
                        delete pWaveInfo->pData;
                        wr = WR_OUTOFMEMORY;
                    }
                }
                else
                {
                    delete pWaveInfo->pData;
                    wr = WR_BADWAVEFILE;
                }
            }
            else
            {
                wr = WR_OUTOFMEMORY;
            }

            fclose(pWaveInfo->pFile);
            pWaveInfo->pFile = 0;
        }

        if( wr != WR_OK )
        {
            delete pWaveInfo;
        }
    }

    return wr;
}
//----------------------------------------------------------------------------
WAVERESULT WaveParser::OpenWaveFile(const char* acFileName, WAVEID* pWaveID)
{
    WAVERESULT wr = WR_OUTOFMEMORY;
    LPWAVEFILEINFO pWaveInfo;

    pWaveInfo = new WAVEFILEINFO;
    if( pWaveInfo )
    {
        if( SUCCEEDED(wr = ParseFile(acFileName, pWaveInfo)) )
        {
            int i;
            for( i = 0; i < MAX_NUM_WAVEID; i++ )
            {
                if( !m_WaveIDs[i] )
                {
                    m_WaveIDs[i] = pWaveInfo;
                    *pWaveID = i;
                    wr = WR_OK;
                    break;
                }
            }

            if( i == MAX_NUM_WAVEID )
            {
                wr = WR_OUTOFMEMORY;
            }
        }

        if( wr != WR_OK )
        {
            delete pWaveInfo;
        }
    }

    return wr;
}
//----------------------------------------------------------------------------
WAVERESULT WaveParser::ReadWaveData(WAVEID WaveID, void* pData,
    unsigned int uiDataSize, unsigned int* puiBytesWritten)
{
    LPWAVEFILEINFO pWaveInfo;
    WAVERESULT wr = WR_BADWAVEFILE;

    if( !pData || !puiBytesWritten || uiDataSize == 0 )
    {
        return WR_INVALIDPARAM;
    }

    if( IsWaveID(WaveID) )
    {
        pWaveInfo = m_WaveIDs[WaveID];
        if( pWaveInfo->pFile )
        {
            unsigned int uiOffset = (unsigned int)ftell(pWaveInfo->pFile);

            if( (uiOffset - pWaveInfo->uiDataOffset + uiDataSize) >
                pWaveInfo->uiDataSize )
            {
                uiDataSize = pWaveInfo->uiDataSize - 
                    (uiOffset - pWaveInfo->uiDataOffset);
            }

            *puiBytesWritten = (unsigned int)fread(pData, 1, uiDataSize,
                pWaveInfo->pFile);

            wr = WR_OK;
        }
    }
    else
    {
        wr = WR_INVALIDWAVEID;
    }

    return wr;
}
//----------------------------------------------------------------------------
WAVERESULT WaveParser::SetWaveDataOffset(WAVEID WaveID, unsigned int uiOffset)
{
    LPWAVEFILEINFO pWaveInfo;
    WAVERESULT wr = WR_INVALIDPARAM;

    if( IsWaveID(WaveID) )
    {
        pWaveInfo = m_WaveIDs[WaveID];
        if( pWaveInfo->pFile )
        {
            // Seek into audio data.
            fseek(pWaveInfo->pFile, pWaveInfo->uiDataOffset + uiOffset,
                SEEK_SET);
            wr = WR_OK;
        }
    }
    else
    {
        wr = WR_INVALIDWAVEID;
    }

    return wr;
}
//----------------------------------------------------------------------------
WAVERESULT WaveParser::GetWaveDataOffset(WAVEID WaveID,
    unsigned int* puiOffset)
{
    LPWAVEFILEINFO pWaveInfo;
    WAVERESULT wr = WR_INVALIDPARAM;

    if( IsWaveID(WaveID) )
    {
        pWaveInfo = m_WaveIDs[WaveID];
        if( (pWaveInfo->pFile) && (puiOffset) )
        {
            // Get current position.
            *puiOffset = (unsigned int)ftell(pWaveInfo->pFile);
            *puiOffset -= pWaveInfo->uiDataOffset;
            wr = WR_OK;
        }
    }
    else
    {
        wr = WR_INVALIDWAVEID;
    }

    return wr;
}
//----------------------------------------------------------------------------
WAVERESULT WaveParser::ParseFile(const char* acFileName,
    LPWAVEFILEINFO pWaveInfo)
{
    WAVEFILEHEADER  waveFileHeader;
    RIFFCHUNK       riffChunk;
    WAVEFMT         waveFmt;
    WAVERESULT      wr = WR_BADWAVEFILE;

    if( !acFileName || !pWaveInfo )
    {
        return WR_INVALIDPARAM;
    }

    memset(pWaveInfo, 0, sizeof(WAVEFILEINFO));

    // Open the wave file for reading.
    fopen_s(&pWaveInfo->pFile, acFileName, "rb");
    if( pWaveInfo->pFile )
    {
        // Read wave file header.
        fread(&waveFileHeader, 1, sizeof(WAVEFILEHEADER), pWaveInfo->pFile);
        if( !_strnicmp(waveFileHeader.acRIFF, "RIFF", 4) && 
            !_strnicmp(waveFileHeader.acWAVE, "WAVE", 4) )
        {
            while( fread(&riffChunk, 1, sizeof(RIFFCHUNK), pWaveInfo->pFile) ==
                sizeof(RIFFCHUNK) )
            {
                if( !_strnicmp(riffChunk.acChunkName, "fmt ", 4) )
                {
                    if( riffChunk.ulChunkSize <= sizeof(WAVEFMT) )
                    {
                        fread(&waveFmt, 1, riffChunk.ulChunkSize, 
                            pWaveInfo->pFile);

                        // Determine if this is a WAVEFORMATEX or 
                        // WAVEFORMATEXTENSIBLE wave file.
                        if( waveFmt.usFormatTag == WAVE_FORMAT_PCM )
                        {
                            pWaveInfo->wfType = WF_EX;
                            memcpy(&pWaveInfo->wfEXT.Format, &waveFmt, 
                                sizeof(PCMWAVEFORMAT));
                        }
                        else if( waveFmt.usFormatTag == WAVE_FORMAT_EXTENSIBLE )
                        {
                            pWaveInfo->wfType = WF_EXT;
                            memcpy(&pWaveInfo->wfEXT, &waveFmt, 
                                sizeof(WAVEFORMATEXTENSIBLE));
                        }
                    }
                    else
                    {
                        fseek(pWaveInfo->pFile, riffChunk.ulChunkSize, 
                            SEEK_CUR);
                    }
                }
                else if( !_strnicmp(riffChunk.acChunkName, "data", 4) )
                {
                    pWaveInfo->uiDataSize = riffChunk.ulChunkSize;
                    pWaveInfo->uiDataOffset = (unsigned int)ftell(
                        pWaveInfo->pFile);
                    fseek(pWaveInfo->pFile, riffChunk.ulChunkSize, SEEK_CUR);
                }
                else
                {
                    fseek(pWaveInfo->pFile, riffChunk.ulChunkSize, SEEK_CUR);
                }

                // Ensure that we are correctly aligned for next chunk.
                if( riffChunk.ulChunkSize & 1 )
                {
                    fseek(pWaveInfo->pFile, 1, SEEK_CUR);
                }
            }

            if( pWaveInfo->uiDataSize && pWaveInfo->uiDataOffset && 
                ((pWaveInfo->wfType == WF_EX) || (pWaveInfo->wfType == 
                WF_EXT)) )
            {
                wr = WR_OK;
            }
            else
            {
                fclose(pWaveInfo->pFile);
            }
        }
    }
    else
    {
        wr = WR_INVALIDFILENAME;
    }

    return wr;
}
//----------------------------------------------------------------------------
WAVERESULT WaveParser::DeleteWaveFile(WAVEID WaveID)
{
    WAVERESULT wr = WR_OK;

    if( IsWaveID(WaveID) )
    {
        if( m_WaveIDs[WaveID]->pData )
        {
            delete m_WaveIDs[WaveID]->pData;
        }

        if( m_WaveIDs[WaveID]->pFile )
        {
            fclose(m_WaveIDs[WaveID]->pFile);
        }

        delete m_WaveIDs[WaveID];
        m_WaveIDs[WaveID] = 0;
    }
    else
    {
        wr = WR_INVALIDWAVEID;
    }

    return wr;
}
//----------------------------------------------------------------------------
WAVERESULT WaveParser::GetWaveType(WAVEID WaveID, WAVEFILETYPE* wfType)
{
    if( !IsWaveID(WaveID) )
    {
        return WR_INVALIDWAVEID;
    }

    if( !wfType )
    {
        return WR_INVALIDPARAM;
    }

    *wfType = m_WaveIDs[WaveID]->wfType;

    return WR_OK;
}
//----------------------------------------------------------------------------
WAVERESULT WaveParser::GetWaveFormatExHeader(WAVEID WaveID, 
    WAVEFORMATEX* wfex)
{
    if( !IsWaveID(WaveID) )
    {
        return WR_INVALIDWAVEID;
    }

    if( !wfex )
    {
        return WR_INVALIDPARAM;
    }

    memcpy(wfex, &(m_WaveIDs[WaveID]->wfEXT.Format), sizeof(WAVEFORMATEX));

    return WR_OK;
}
//----------------------------------------------------------------------------
WAVERESULT WaveParser::GetWaveFormatExtensibleHeader(WAVEID WaveID, 
    WAVEFORMATEXTENSIBLE* wfext)
{
    if( !IsWaveID(WaveID) )
    {
        return WR_INVALIDWAVEID;
    }

    if( m_WaveIDs[WaveID]->wfType != WF_EXT )
    {
        return WR_NOTWAVEFORMATEXTENSIBLEFORMAT;
    }

    if( !wfext )
    {
        return WR_INVALIDPARAM;
    }

    memcpy(wfext, &(m_WaveIDs[WaveID]->wfEXT), sizeof(WAVEFORMATEXTENSIBLE));

    return WR_OK;
}
//----------------------------------------------------------------------------
WAVERESULT WaveParser::GetWaveData(WAVEID WaveID, void** lplpAudioData)
{
	if (!IsWaveID(WaveID))
		return WR_INVALIDWAVEID;

	if (!lplpAudioData)
		return WR_INVALIDPARAM;

	*lplpAudioData = m_WaveIDs[WaveID]->pData;

	return WR_OK;
}
//----------------------------------------------------------------------------
WAVERESULT WaveParser::GetWaveSize(WAVEID WaveID, unsigned int* puiDataSize)
{
    if( !IsWaveID(WaveID) )
    {
        return WR_INVALIDWAVEID;
    }

    if( !puiDataSize )
    {
        return WR_INVALIDPARAM;
    }

    *puiDataSize = m_WaveIDs[WaveID]->uiDataSize;

    return WR_OK;
}
//----------------------------------------------------------------------------
WAVERESULT WaveParser::GetWaveFrequency(WAVEID WaveID, 
    unsigned int* puiFrequency)
{
    WAVERESULT wr = WR_OK;

    if( IsWaveID(WaveID) )
    {
        if( puiFrequency )
        {
            *puiFrequency = m_WaveIDs[WaveID]->wfEXT.Format.nSamplesPerSec;
        }
        else
        {
            wr = WR_INVALIDPARAM;
        }
    }
    else
    {
        wr = WR_INVALIDWAVEID;
    }

    return wr;
}
//----------------------------------------------------------------------------
WAVERESULT WaveParser::GetWaveALBufferFormat(WAVEID WaveID, 
    PFNALGETENUMVALUE pfnGetEnumValue, unsigned int *puiFormat)
{
    WAVERESULT wr = WR_OK;

    if( IsWaveID(WaveID) )
    {
        if( pfnGetEnumValue && puiFormat )
        {
            *puiFormat = 0;

            if( m_WaveIDs[WaveID]->wfType == WF_EX )
            {
                if( m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 1 )
                {
                    switch( m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample )
                    {
                    case 4:
                        *puiFormat = pfnGetEnumValue("AL_FORMAT_MONO_IMA4");
                        break;
                    case 8:
                        *puiFormat = pfnGetEnumValue("AL_FORMAT_MONO8");
                        break;
                    case 16:
                        *puiFormat = pfnGetEnumValue("AL_FORMAT_MONO16");
                        break;
                    }
                }
                else if( m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 2 )
                {
                    switch( m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample )
                    {
                    case 4:
                        *puiFormat = pfnGetEnumValue("AL_FORMAT_STEREO_IMA4");
                        break;
                    case 8:
                        *puiFormat = pfnGetEnumValue("AL_FORMAT_STEREO8");
                        break;
                    case 16:
                        *puiFormat = pfnGetEnumValue("AL_FORMAT_STEREO16");
                        break;
                    }
                }
                else if( (m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 4) && 
                    (m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample == 16) )
                {
                    *puiFormat = pfnGetEnumValue("AL_FORMAT_QUAD16");
                }
            }
            else if( m_WaveIDs[WaveID]->wfType == WF_EXT )
            {
                if( (m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 1) &&
                    ((m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 
                    SPEAKER_FRONT_CENTER) ||
                    (m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 
                    (SPEAKER_FRONT_LEFT|SPEAKER_FRONT_RIGHT)) ||
                    (m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 0)) )
                {
                    switch( m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample )
                    {
                    case 4:
                        *puiFormat = pfnGetEnumValue("AL_FORMAT_MONO_IMA4");
                        break;
                    case 8:
                        *puiFormat = pfnGetEnumValue("AL_FORMAT_MONO8");
                        break;
                    case 16:
                        *puiFormat = pfnGetEnumValue("AL_FORMAT_MONO16");
                        break;
                    }
                }
                else if( (m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 2) && 
                    (m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 
                    (SPEAKER_FRONT_LEFT|SPEAKER_FRONT_RIGHT)) )
                {
                    switch (m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample)
                    {
                    case 4:
                        *puiFormat = pfnGetEnumValue("AL_FORMAT_STEREO_IMA4");
                        break;
                    case 8:
                        *puiFormat = pfnGetEnumValue("AL_FORMAT_STEREO8");
                        break;
                    case 16:
                        *puiFormat = pfnGetEnumValue("AL_FORMAT_STEREO16");
                        break;
                    }
                }
                else if( (m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 2) && 
                    (m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample == 16) &&
                    (m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 
                    (SPEAKER_BACK_LEFT|SPEAKER_BACK_RIGHT)) )
                {
                    *puiFormat =  pfnGetEnumValue("AL_FORMAT_REAR16");
                }
                else if( (m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 4) && 
                    (m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample == 16) &&
                    (m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 
                    (SPEAKER_FRONT_LEFT|SPEAKER_FRONT_RIGHT|SPEAKER_BACK_LEFT|
                    SPEAKER_BACK_RIGHT)) )
                {
                    *puiFormat = pfnGetEnumValue("AL_FORMAT_QUAD16");
                }
                else if( (m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 6) &&
                    (m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample == 16) &&
                    (m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 
                    (SPEAKER_FRONT_LEFT|SPEAKER_FRONT_RIGHT|
                    SPEAKER_FRONT_CENTER|SPEAKER_LOW_FREQUENCY|
                    SPEAKER_BACK_LEFT|SPEAKER_BACK_RIGHT)) )
                {
                    *puiFormat = pfnGetEnumValue("AL_FORMAT_51CHN16");
                }
                else if( (m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 7) &&
                    (m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample == 16) &&
                    (m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 
                    (SPEAKER_FRONT_LEFT|SPEAKER_FRONT_RIGHT|
                    SPEAKER_FRONT_CENTER|SPEAKER_LOW_FREQUENCY|
                    SPEAKER_BACK_LEFT|SPEAKER_BACK_RIGHT|
                    SPEAKER_BACK_CENTER)) )
                {
			        *puiFormat = pfnGetEnumValue("AL_FORMAT_61CHN16");
                }
                else if( (m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 8) &&
                    (m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample == 16) &&
                    (m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 
                    (SPEAKER_FRONT_LEFT|SPEAKER_FRONT_RIGHT|
                    SPEAKER_FRONT_CENTER|SPEAKER_LOW_FREQUENCY|
                    SPEAKER_BACK_LEFT|SPEAKER_BACK_RIGHT|SPEAKER_SIDE_LEFT|
                    SPEAKER_SIDE_RIGHT)) )
                {
                    *puiFormat = pfnGetEnumValue("AL_FORMAT_71CHN16");
                }
            }

            if( *puiFormat == 0 )
            {
                wr = WR_INVALIDWAVEFILETYPE;
            }
        }
        else
        {
            wr = WR_INVALIDPARAM;
        }
    }
    else
    {
        wr = WR_INVALIDWAVEID;
    }

    return wr;
}
//----------------------------------------------------------------------------
WAVERESULT WaveParser::GetWaveSEWaveFormat(WAVEID WaveID, 
    Swing::SEWave::FormatMode* peFormat)
{
    WAVERESULT wr = WR_OK;

    if( IsWaveID(WaveID) )
    {
        if( peFormat )
        {
            *peFormat = (Swing::SEWave::FormatMode)-1;

            if( m_WaveIDs[WaveID]->wfType == WF_EX )
            {
                if( m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 1 )
                {
                    switch( m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample )
                    {
                    case 4:
                        *peFormat = Swing::SEWave::WT_MONO4;
                        break;
                    case 8:
                        *peFormat = Swing::SEWave::WT_MONO8;
                        break;
                    case 16:
                        *peFormat = Swing::SEWave::WT_MONO16;
                        break;
                    }
                }
                else if( m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 2 )
                {
                    switch( m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample )
                    {
                    case 4:
                        *peFormat = Swing::SEWave::WT_STEREO4;
                        break;
                    case 8:
                        *peFormat = Swing::SEWave::WT_STEREO8;
                        break;
                    case 16:
                        *peFormat = Swing::SEWave::WT_STEREO16;
                        break;
                    }
                }
                else if( (m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 4) && 
                    (m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample == 16) )
                {
                    *peFormat = Swing::SEWave::WT_QUAD16;
                }
            }
            else if( m_WaveIDs[WaveID]->wfType == WF_EXT )
            {
                if( (m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 1) &&
                    ((m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 
                    SPEAKER_FRONT_CENTER) ||
                    (m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 
                    (SPEAKER_FRONT_LEFT|SPEAKER_FRONT_RIGHT)) ||
                    (m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 0)) )
                {
                    switch( m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample )
                    {
                    case 4:
                        *peFormat = Swing::SEWave::WT_MONO4;
                        break;
                    case 8:
                        *peFormat = Swing::SEWave::WT_MONO8;
                        break;
                    case 16:
                        *peFormat = Swing::SEWave::WT_MONO16;
                        break;
                    }
                }
                else if( (m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 2) && 
                    (m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 
                    (SPEAKER_FRONT_LEFT|SPEAKER_FRONT_RIGHT)) )
                {
                    switch (m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample)
                    {
                    case 4:
                        *peFormat = Swing::SEWave::WT_STEREO4;
                        break;
                    case 8:
                        *peFormat = Swing::SEWave::WT_STEREO8;
                        break;
                    case 16:
                        *peFormat = Swing::SEWave::WT_STEREO16;
                        break;
                    }
                }
                else if( (m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 2) && 
                    (m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample == 16) &&
                    (m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 
                    (SPEAKER_BACK_LEFT|SPEAKER_BACK_RIGHT)) )
                {
                    *peFormat = Swing::SEWave::WT_REAR16;
                }
                else if( (m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 4) && 
                    (m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample == 16) &&
                    (m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 
                    (SPEAKER_FRONT_LEFT|SPEAKER_FRONT_RIGHT|SPEAKER_BACK_LEFT|
                    SPEAKER_BACK_RIGHT)) )
                {
                    *peFormat = Swing::SEWave::WT_QUAD16;
                }
                else if( (m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 6) &&
                    (m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample == 16) &&
                    (m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 
                    (SPEAKER_FRONT_LEFT|SPEAKER_FRONT_RIGHT|
                    SPEAKER_FRONT_CENTER|SPEAKER_LOW_FREQUENCY|
                    SPEAKER_BACK_LEFT|SPEAKER_BACK_RIGHT)) )
                {
                    *peFormat = Swing::SEWave::WT_51CHN16;
                }
                else if( (m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 7) &&
                    (m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample == 16) &&
                    (m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 
                    (SPEAKER_FRONT_LEFT|SPEAKER_FRONT_RIGHT|
                    SPEAKER_FRONT_CENTER|SPEAKER_LOW_FREQUENCY|
                    SPEAKER_BACK_LEFT|SPEAKER_BACK_RIGHT|
                    SPEAKER_BACK_CENTER)) )
                {
			        *peFormat = Swing::SEWave::WT_61CHN16;
                }
                else if( (m_WaveIDs[WaveID]->wfEXT.Format.nChannels == 8) &&
                    (m_WaveIDs[WaveID]->wfEXT.Format.wBitsPerSample == 16) &&
                    (m_WaveIDs[WaveID]->wfEXT.dwChannelMask == 
                    (SPEAKER_FRONT_LEFT|SPEAKER_FRONT_RIGHT|
                    SPEAKER_FRONT_CENTER|SPEAKER_LOW_FREQUENCY|
                    SPEAKER_BACK_LEFT|SPEAKER_BACK_RIGHT|SPEAKER_SIDE_LEFT|
                    SPEAKER_SIDE_RIGHT)) )
                {
                    *peFormat = Swing::SEWave::WT_71CHN16;
                }
            }

            if( *peFormat == -1 )
            {
                wr = WR_INVALIDWAVEFILETYPE;
            }
        }
        else
        {
            wr = WR_INVALIDPARAM;
        }
    }
    else
    {
        wr = WR_INVALIDWAVEID;
    }

    return wr;
}
//----------------------------------------------------------------------------
bool WaveParser::IsWaveID(WAVEID WaveID)
{
    bool bReturn = false;

    if( (WaveID >= 0) && (WaveID < MAX_NUM_WAVEID) )
    {
        if( m_WaveIDs[WaveID] )
        {
            bReturn = true;
        }
    }

    return bReturn;
}
//----------------------------------------------------------------------------
char* WaveParser::GetErrorString(WAVERESULT wr, char* acErrorString, 
    unsigned int uiSizeOfErrorString)
{	
    switch( wr )
    {
    case WR_OK:
        strncpy_s(acErrorString, uiSizeOfErrorString, "Success\n", 
            uiSizeOfErrorString-1);
        break;

    case WR_INVALIDFILENAME:
        strncpy_s(acErrorString, uiSizeOfErrorString, 
            "Invalid file name or file does not exist\n", 
            uiSizeOfErrorString-1);
        break;

    case WR_BADWAVEFILE:
        strncpy_s(acErrorString, uiSizeOfErrorString, "Invalid wave file\n", 
            uiSizeOfErrorString-1);
        break;

    case WR_INVALIDPARAM:
        strncpy_s(acErrorString, uiSizeOfErrorString, 
            "Invalid parameter passed to function\n", uiSizeOfErrorString-1);
        break;

    case WR_FILEERROR:
        strncpy_s(acErrorString, uiSizeOfErrorString, "File I/O error\n", 
            uiSizeOfErrorString-1);
        break;

    case WR_INVALIDWAVEID:
        strncpy_s(acErrorString, uiSizeOfErrorString, "Invalid WAVEID\n", 
            uiSizeOfErrorString-1);
        break;

    case WR_NOTSUPPORTEDYET:
        strncpy_s(acErrorString, uiSizeOfErrorString, 
            "Function not supported yet\n", uiSizeOfErrorString-1);
        break;

    case WR_WAVEMUSTBEMONO:
        strncpy_s(acErrorString, uiSizeOfErrorString, 
            "Input wave files must be mono\n", uiSizeOfErrorString-1);
        break;

    case WR_WAVEMUSTBEWAVEFORMATPCM:
        strncpy_s(acErrorString, uiSizeOfErrorString, 
            "Input wave files must be in Wave Format PCM\n", 
            uiSizeOfErrorString-1);
        break;
		
    case WR_WAVESMUSTHAVESAMEBITRESOLUTION:
        strncpy_s(acErrorString, uiSizeOfErrorString, 
            "Input wave files must have the same Bit Resolution\n", 
            uiSizeOfErrorString-1);
        break;

    case WR_WAVESMUSTHAVESAMEFREQUENCY:
        strncpy_s(acErrorString, uiSizeOfErrorString, 
            "Input wave files must have the same Frequency\n", 
            uiSizeOfErrorString-1);
        break;

    case WR_WAVESMUSTHAVESAMEBITRATE:
        strncpy_s(acErrorString, uiSizeOfErrorString, 
            "Input wave files must have the same Bit Rate\n", 
            uiSizeOfErrorString-1);
        break;

    case WR_WAVESMUSTHAVESAMEBLOCKALIGNMENT:
        strncpy_s(acErrorString, uiSizeOfErrorString, 
            "Input wave files must have the same Block Alignment\n", 
            uiSizeOfErrorString-1);
        break;

    case WR_OFFSETOUTOFDATARANGE:
        strncpy_s(acErrorString, uiSizeOfErrorString, 
            "Wave files Offset is not within audio data\n", 
            uiSizeOfErrorString-1);
        break;

    case WR_INVALIDSPEAKERPOS:
        strncpy_s(acErrorString, uiSizeOfErrorString, 
            "Invalid Speaker Destinations\n", uiSizeOfErrorString-1);
        break;

    case WR_OUTOFMEMORY:
        strncpy_s(acErrorString, uiSizeOfErrorString, "Out of memory\n", 
            uiSizeOfErrorString-1);
        break;

    case WR_INVALIDWAVEFILETYPE:
        strncpy_s(acErrorString, uiSizeOfErrorString, 
            "Invalid Wave File Type\n", uiSizeOfErrorString-1);
        break;

    case WR_NOTWAVEFORMATEXTENSIBLEFORMAT:
        strncpy_s(acErrorString, uiSizeOfErrorString, 
            "Wave file is not in WAVEFORMATEXTENSIBLE format\n", 
            uiSizeOfErrorString-1);
        break;

    default:
        strncpy_s(acErrorString, uiSizeOfErrorString, "Undefined error\n", 
            uiSizeOfErrorString-1);
    }
    acErrorString[uiSizeOfErrorString-1] = '\0';
    return acErrorString;
}
//----------------------------------------------------------------------------