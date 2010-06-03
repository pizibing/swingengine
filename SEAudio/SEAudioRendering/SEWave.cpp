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

SE_IMPLEMENT_RTTI(Swing, SEWave, SEObject);
SE_IMPLEMENT_STREAM(SEWave);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEWave, SEObject);

//SE_REGISTER_STREAM(SEWave);

int SEWave::ms_BytesPerSample[SEWave::WT_COUNT] =
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

int SEWave::ms_ChannelsPerSample[SEWave::WT_COUNT] =
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

std::string SEWave::ms_FormatName[SEWave::WT_COUNT] =
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
SEWave::SEWave(FormatMode eFormat, unsigned int uiFrequency, int iDataSize,
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
        SEWaveCatalog::GetActive()->Insert(this);
    }
}
//----------------------------------------------------------------------------
SEWave::SEWave()
{
    m_eFormat = WT_COUNT;
    m_uiFrequency = 0;
    m_iDataSize = 0;
    m_pData = 0;
}
//----------------------------------------------------------------------------
SEWave::~SEWave()
{
    SE_DELETE[] m_pData;
    if( m_bIsInCatalog )
    {
        SEWaveCatalog::GetActive()->Remove(this);
    }
}
//----------------------------------------------------------------------------
SEWave* SEWave::Load(const char* pWaveName)
{
    SE_ASSERT( pWaveName );

    std::string strFileName = std::string(pWaveName) + std::string(".sewf");
    const char* pDecorated = SESystem::SE_GetPath(strFileName.c_str(), 
        SESystem::SM_READ);
    if( !pDecorated )
    {
        return 0;
    }

    char* acBuffer;
    int iSize;
    bool bLoaded = SESystem::SE_Load(pDecorated, acBuffer, iSize);
    if( !bLoaded )
    {
        // 文件读取失败.
        return 0;
    }
    if( iSize < SEWaveVersion::LENGTH )
    {
        // 文件太小.
        SE_DELETE[] acBuffer;

        return 0;
    }

    // 获取文件版本.
    SEWaveVersion tempVersion(acBuffer);
    if( !tempVersion.IsValid() )
    {
        SE_DELETE[] acBuffer;

        return 0;
    }

    char* pcCurrent = acBuffer + SEWaveVersion::LENGTH;

    // 获取wave format和frequency.
    int iFormat;
    unsigned int uiFrequency;
    pcCurrent += SESystem::SE_Read4le(pcCurrent, 1, &iFormat);
    pcCurrent += SESystem::SE_Read4le(pcCurrent, 1, &uiFrequency);

    FormatMode eFormat = (FormatMode)iFormat;

    // 获取wave data.
    // 注意16位采样数据存在endian问题.
    int iDataSize;
    pcCurrent += SESystem::SE_Read4le(pcCurrent, 1, &iDataSize);
    unsigned char* pData = SE_NEW unsigned char[iDataSize];
    if( iFormat == WT_MONO4 || iFormat == WT_MONO8 ||
        iFormat == WT_STEREO4 || iFormat == WT_STEREO8 )
    {
        SESystem::SE_Read1(pcCurrent, iDataSize, pData);
    }
    else
    {
        // 对于16位采样数据,数据区字节数应为偶数.
        SE_ASSERT( IsEven(iDataSize) );
        SESystem::SE_Read2le(pcCurrent, iDataSize>>1, pData);
    }

    SEWave* pWave = SE_NEW SEWave(eFormat, uiFrequency, iDataSize, pData,
        pWaveName);

    SE_DELETE[] acBuffer;

    return pWave;
}
//----------------------------------------------------------------------------
bool SEWave::Save(const char* pFileName)
{
    if( !pFileName )
    {
        return false;
    }

    FILE* pFile = SESystem::SE_Fopen(pFileName, "wb");
    if( !pFile )
    {
        return false;
    }

    // 写文件版本.
    SESystem::SE_Write1(pFile, SEWaveVersion::LENGTH, SEWaveVersion::LABEL);

    // 写wave format和frequency.
    int iFormat = (int)m_eFormat;
    SESystem::SE_Write4le(pFile, 1, &iFormat);
    SESystem::SE_Write4le(pFile, 1, &m_uiFrequency);

    // 写wave data.
    // 注意16位采样数据存在endian问题.
    SESystem::SE_Write4le(pFile, 1, &m_iDataSize);
    if( iFormat == WT_MONO4 || iFormat == WT_MONO8 ||
        iFormat == WT_STEREO4 || iFormat == WT_STEREO8 )
    {
        SESystem::SE_Write1(pFile, m_iDataSize, m_pData);
    }
    else
    {
        // 对于16位采样数据,数据区字节数应为偶数.
        SE_ASSERT( IsEven(m_iDataSize) );
        SESystem::SE_Write2le(pFile, m_iDataSize>>1, m_pData);
    }

    SESystem::SE_Fclose(pFile);

    return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SEWave::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEObject::Load(rStream, pLink);

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
    SEWaveCatalog::GetActive()->Insert(this);

    SE_END_DEBUG_STREAM_LOAD(SEWave);
}
//----------------------------------------------------------------------------
void SEWave::Link(SEStream& rStream, SEStream::SELink* pLink)
{
    SEObject::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SEWave::Register(SEStream& rStream) const
{
    return SEObject::Register(rStream);
}
//----------------------------------------------------------------------------
void SEWave::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEObject::Save(rStream);

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

    SE_END_DEBUG_STREAM_SAVE(SEWave);
}
//----------------------------------------------------------------------------
int SEWave::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    int iSize = SEObject::GetDiskUsed(rVersion) +
        sizeof(int); // m_eFormat

    iSize += sizeof(m_uiFrequency) + sizeof(m_iDataSize);
    iSize += m_iDataSize*sizeof(m_pData[0]);

    return iSize;
}
//----------------------------------------------------------------------------
SEStringTree* SEWave::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("format =", ms_FormatName[m_eFormat].c_str()));
    pTree->Append(Format("frequency = ", m_uiFrequency));

    // children
    pTree->Append(SEObject::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
