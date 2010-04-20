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

#include "SEWavToSewf.h"

using namespace std;

SE_CONSOLE_APPLICATION(WavToSewf);

SE_REGISTER_INITIALIZE(WavToSewf);

//----------------------------------------------------------------------------
void WavToSewf::Usage()
{
    cout << endl;
    cout << "To convert Windows Wave Format to Swing Engine Wave" << endl;
    cout << "Format (sewf), use" << endl;
    cout << "    SEWavToSewf80 myfile.wav" << endl;
    cout << "Warning: Only support PCM wave format." << endl;
}
//----------------------------------------------------------------------------
int WavToSewf::GetWave(const char* acWAVName, SEWave::FormatMode& reFormat,
    unsigned int& ruiFrequency, unsigned int& ruiDataSize,
    unsigned char*& raucData)
{
    WAVERESULT wr;
    WaveParser* pParser = SE_NEW WaveParser;

    unsigned char* aucSrcData;
    WAVEID tempSrcID;
    wr = pParser->LoadWaveFile(acWAVName, &tempSrcID);
    if( wr != WR_OK )
    {
        SE_DELETE pParser;
        return -4;
    }

    wr = pParser->GetWaveSEWaveFormat(tempSrcID, &reFormat);
    if( wr != WR_OK )
    {
        SE_DELETE pParser;
        return -5;
    }

    wr = pParser->GetWaveFrequency(tempSrcID, &ruiFrequency);
    if( wr != WR_OK )
    {
        SE_DELETE pParser;
        return -6;
    }

    wr = pParser->GetWaveSize(tempSrcID, &ruiDataSize);
    if( wr != WR_OK )
    {
        SE_DELETE pParser;
        return -7;
    }

    wr = pParser->GetWaveData(tempSrcID, (void**)&aucSrcData);
    if( wr != WR_OK )
    {
        SE_DELETE pParser;
        return -8;
    }

    raucData = SE_NEW unsigned char[ruiDataSize];
    if( !raucData )
    {
        SE_DELETE pParser;
        return -9;
    }
    memcpy(raucData, aucSrcData, ruiDataSize);

    SE_DELETE pParser;
    return 0;
}
//----------------------------------------------------------------------------
int WavToSewf::Main(int iArgCount, char** aacArgument)
{
    if( iArgCount <= 1 )
    {
        Usage();
        return -1;
    }

    // Get WAV input file.  The filename must have extension ".wav", so the
    // filename is at least 5 characters long.
    const char* acWAVFileName = aacArgument[1];
    const size_t uiWAVFileNameSize = strlen(acWAVFileName);
    if( uiWAVFileNameSize < 5 )
    {
        return -2;
    }
    const char* acWAVFileExt = acWAVFileName + uiWAVFileNameSize - 4;
    if( acWAVFileExt[0] != '.'
    ||  tolower(acWAVFileExt[1]) != 'w'
    ||  tolower(acWAVFileExt[2]) != 'a'
    ||  tolower(acWAVFileExt[3]) != 'v' )
    {
        return -3;
    }

    // Generate the wave name without an extension.
    std::string tempWaveName;
    int i;
    for( i = 0; i < (int)uiWAVFileNameSize - 4; i++ )
    {
        tempWaveName += acWAVFileName[i];
    }

    SEWave::FormatMode eFormat;
    unsigned int uiFrequency;
    unsigned int uiDataSize;
    unsigned char* aucWAVData;  // 由GetWave函数创建数据区内存,稍后释放
    int iErrorCode = GetWave(acWAVFileName, eFormat, uiFrequency, uiDataSize,
        aucWAVData);
    if( iErrorCode != 0 )
    {
        SE_DELETE[] aucWAVData;
        return iErrorCode;
    }

    // The input file is SomeFile.wav.  Allocate enough space to change
    // this to SomeFile.sewf.
    const size_t uiDstSize = strlen(acWAVFileName) + 2;
    char* acSewfName = SE_NEW char[uiDstSize];
    SESystem::SE_Strcpy(acSewfName, uiDstSize, acWAVFileName);
    char* acSewfFileExt = acSewfName + uiDstSize - 5;
    acSewfFileExt[0] = 's';
    acSewfFileExt[1] = 'e';
    acSewfFileExt[2] = 'w';
    acSewfFileExt[3] = 'f';
    acSewfFileExt[4] = 0;

    SEWave* pWave = SE_NEW SEWave(eFormat, uiFrequency, uiDataSize, 
        aucWAVData, (const char*)tempWaveName.c_str(), false);
    if( !pWave )
    {
            SE_DELETE[] aucWAVData;
            return -10;
    }
    if( !pWave->Save(acSewfName) )
    {
            SE_DELETE pWave;
            return -11;
    }

    SE_DELETE pWave;
    return 0;
}
//----------------------------------------------------------------------------
