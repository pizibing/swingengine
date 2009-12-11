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

#include "SEAudioPCH.h"
#include "SEWave.h"
#include "SEWaveCatalog.h"
#include "SEWaveVersion.h"
#include "SEBitHacks.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, Wave, Object);
SE_IMPLEMENT_STREAM(Wave);
SE_IMPLEMENT_DEFAULT_NAME_ID(Wave, Object);

//SE_REGISTER_STREAM(Wave);

int Wave::ms_BytesPerSample[Wave::WT_COUNT] =
{
    1,  // WT_MONO4
    1,  // WT_MONO8
    2,  // WT_MONO16
    1,  // WT_STEREO4
    1,  // WT_STEREO8
    2,  // WT_STEREO16
    2,  // WT_QUAD16
    2,  // WT_REAR16
    2,  // WT_51CHN16
    2,  // WT_61CHN16
    2   // WT_71CHN16
};

int Wave::ms_ChannelsPerSample[Wave::WT_COUNT] =
{
    1,  // WT_MONO4
    1,  // WT_MONO8
    1,  // WT_MONO16
    2,  // WT_STEREO4
    2,  // WT_STEREO8
    2,  // WT_STEREO16
    4,  // WT_QUAD16
    2,  // WT_REAR16
    6,  // WT_51CHN16
    7,  // WT_61CHN16
    8   // WT_71CHN16
};

std::string Wave::ms_FormatName[Wave::WT_COUNT] =
{
    "WT_MONO4",
    "WT_MONO8",
    "WT_MONO16",
    "WT_STEREO4",
    "WT_STEREO8",
    "WT_STEREO16",
    "WT_QUAD16",
    "WT_REAR16",
    "WT_51CHN16",
    "WT_61CHN16",
    "WT_71CHN16"
};

//----------------------------------------------------------------------------
Wave::Wave(FormatMode eFormat, unsigned int uiFrequency, int iDataSize,
    unsigned char* pData, const char* pWaveName, bool bInsert)
{
    SE_ASSERT( pWaveName );

    m_eFormat = eFormat;
    m_uiFrequency = uiFrequency;
    m_iDataSize = iDataSize;
    m_pData = pData;
    SetName(pWaveName);
    m_bIsInCatalog = bInsert;
    if( bInsert )
    {
        WaveCatalog::GetActive()->Insert(this);
    }
}
//----------------------------------------------------------------------------
Wave::Wave()
{
    m_eFormat = WT_COUNT;
    m_uiFrequency = 0;
    m_iDataSize = 0;
    m_pData = 0;
}
//----------------------------------------------------------------------------
Wave::~Wave()
{
    SE_DELETE[] m_pData;
    if( m_bIsInCatalog )
    {
        WaveCatalog::GetActive()->Remove(this);
    }
}
//----------------------------------------------------------------------------
Wave* Wave::Load(const char* pWaveName)
{
    SE_ASSERT( pWaveName );

    std::string strFileName = std::string(pWaveName) + std::string(".sewf");
    const char* pDecorated = System::SE_GetPath(strFileName.c_str(), 
        System::SM_READ);
    if( !pDecorated )
    {
        return 0;
    }

    char* acBuffer;
    int iSize;
    bool bLoaded = System::SE_Load(pDecorated, acBuffer, iSize);
    if( !bLoaded )
    {
        // 文件不存在.
        return 0;
    }
    if( iSize < WaveVersion::LENGTH )
    {
        // 文件太小.
        SE_DELETE[] acBuffer;

        return 0;
    }

    // 获取文件版本.
    WaveVersion tempVersion(acBuffer);
    if( !tempVersion.IsValid() )
    {
        SE_DELETE[] acBuffer;

        return 0;
    }

    char* pcCurrent = acBuffer + WaveVersion::LENGTH;

    // 获取wave format和frequency.
    int iFormat;
    unsigned int uiFrequency;
    pcCurrent += System::SE_Read4le(pcCurrent, 1, &iFormat);
    pcCurrent += System::SE_Read4le(pcCurrent, 1, &uiFrequency);

    FormatMode eFormat = (FormatMode)iFormat;

    // 获取wave data.
    // 注意16位采样数据存在endian问题.
    int iDataSize;
    pcCurrent += System::SE_Read4le(pcCurrent, 1, &iDataSize);
    unsigned char* pData = SE_NEW unsigned char[iDataSize];
    if( iFormat == WT_MONO4 || iFormat == WT_MONO8 ||
        iFormat == WT_STEREO4 || iFormat == WT_STEREO8 )
    {
        System::SE_Read1(pcCurrent, iDataSize, pData);
    }
    else
    {
        // 对于16位采样数据,数据区字节数应为偶数.
        SE_ASSERT( IsEven(iDataSize) );
        System::SE_Read2le(pcCurrent, iDataSize>>1, pData);
    }

    Wave* pWave = SE_NEW Wave(eFormat, uiFrequency, iDataSize, pData,
        pWaveName);

    SE_DELETE[] acBuffer;

    return pWave;
}
//----------------------------------------------------------------------------
bool Wave::Save(const char* pFileName)
{
    if( !pFileName )
    {
        return false;
    }

    FILE* pFile = System::SE_Fopen(pFileName, "wb");
    if( !pFile )
    {
        return false;
    }

    // 写文件版本.
    System::SE_Write1(pFile, WaveVersion::LENGTH, WaveVersion::LABEL);

    // 写wave format和frequency.
    int iFormat = (int)m_eFormat;
    System::SE_Write4le(pFile, 1, &iFormat);
    System::SE_Write4le(pFile, 1, &m_uiFrequency);

    // 写wave data.
    // 注意16位采样数据存在endian问题.
    System::SE_Write4le(pFile, 1, &m_iDataSize);
    if( iFormat == WT_MONO4 || iFormat == WT_MONO8 ||
        iFormat == WT_STEREO4 || iFormat == WT_STEREO8 )
    {
        System::SE_Write1(pFile, m_iDataSize, m_pData);
    }
    else
    {
        // 对于16位采样数据,数据区字节数应为偶数.
        SE_ASSERT( IsEven(m_iDataSize) );
        System::SE_Write2le(pFile, m_iDataSize>>1, m_pData);
    }

    System::SE_Fclose(pFile);

    return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void Wave::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    Object::Load(rStream, pLink);

    // native data
    int iFormat;
    rStream.Read(iFormat);
    m_eFormat = (FormatMode)iFormat;
    rStream.Read(m_uiFrequency);

    // 获取wave data.
    // 注意16位采样数据存在endian问题.
    rStream.Read(m_iDataSize);
    m_pData = SE_NEW unsigned char[m_iDataSize];
    if( iFormat == WT_MONO4 || iFormat == WT_MONO8 ||
        iFormat == WT_STEREO4 || iFormat == WT_STEREO8 )
    {
        rStream.Read(m_iDataSize, m_pData);
    }
    else
    {
        // 对于16位采样数据,数据区字节数应为偶数.
        SE_ASSERT( IsEven(m_iDataSize) );
        rStream.Read(m_iDataSize>>1, (unsigned short*)m_pData);
    }

    m_bIsInCatalog = true;
    WaveCatalog::GetActive()->Insert(this);

    SE_END_DEBUG_STREAM_LOAD(Wave);
}
//----------------------------------------------------------------------------
void Wave::Link(Stream& rStream, Stream::Link* pLink)
{
    Object::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool Wave::Register(Stream& rStream) const
{
    return Object::Register(rStream);
}
//----------------------------------------------------------------------------
void Wave::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    Object::Save(rStream);

    // native data
    rStream.Write((int)m_eFormat);
    rStream.Write(m_uiFrequency);

    // 写wave data.
    // 注意16位采样数据存在endian问题.
    rStream.Write(m_iDataSize);
    if( m_eFormat == WT_MONO4 || m_eFormat == WT_MONO8 ||
        m_eFormat == WT_STEREO4 || m_eFormat == WT_STEREO8 )
    {
        rStream.Write(m_iDataSize, m_pData);
    }
    else
    {
        // 对于16位采样数据,数据区字节数应为偶数.
        SE_ASSERT( IsEven(m_iDataSize) );
        rStream.Write(m_iDataSize>>1, (unsigned short*)m_pData);
    }

    SE_END_DEBUG_STREAM_SAVE(Wave);
}
//----------------------------------------------------------------------------
int Wave::GetDiskUsed(const StreamVersion& rVersion) const
{
    int iSize = Object::GetDiskUsed(rVersion) +
        sizeof(int); // m_eFormat

    iSize += sizeof(m_uiFrequency) + sizeof(m_iDataSize);
    iSize += m_iDataSize*sizeof(m_pData[0]);

    return iSize;
}
//----------------------------------------------------------------------------
StringTree* Wave::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("format =", ms_FormatName[m_eFormat].c_str()));
    pTree->Append(Format("frequency = ", m_uiFrequency));

    // children
    pTree->Append(Object::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
