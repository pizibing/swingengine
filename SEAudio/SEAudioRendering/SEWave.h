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

#ifndef Swing_Wave_H
#define Swing_Wave_H

#include "SEAudioLIB.h"
#include "SEObject.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:wave类
// 说明:支持wave声音文件.
// 作者:Sun Che
// 时间:20090617
//----------------------------------------------------------------------------
class SE_AUDIO_API Wave : public Object
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    enum FormatMode
    {
        WT_MONO4 = 0,
        WT_MONO8,
        WT_MONO16,
        WT_STEREO4,
        WT_STEREO8,
        WT_STEREO16,
        WT_QUAD16,
        WT_REAR16,
        WT_51CHN16,
        WT_61CHN16,
        WT_71CHN16,
        WT_COUNT
    };

    // 注意:16位wave数据存在endian问题.
    // 8位采样数据我们按照单字节数据读取/写入磁盘.
    // 16位采样数据我们按照little endian的双字节数据写入磁盘,
    // 因此在写入/读取16位采样数据时,如果当前系统是big endian的,则会产生swap.

    // 构造和析构.
    // Wave有责任删除传入的数组数据.
    // pWaveName用于wave共享时的唯一ID.
    // 构造函数的调用者可以提供一个wave name.
    // 如果没有提供,则构造函数将自动创建一个叫做"waveN.sewf"的唯一ID,
    // 其中N是其Object::m_uiID.
    // 出于wave共享的目的,系统维护着一个全局wave map.
    // 默认情况下,wave被成功创建后,将被插入到全局wave map,
    // 供稍后索引该资源时使用.然而用户也可以设置bInsert参数为false,
    // 从而该wave不会被插入全局wave map(比如在没有全局wave map时).

    Wave(FormatMode eFormat, unsigned int uiFrequency, int iDataSize,
        unsigned char* pData, const char* pWaveName, bool bInsert = true);

    virtual ~Wave(void);

    // 成员访问.
    inline FormatMode GetFormat(void) const;
    inline const std::string& GetFormatName(void) const;
    inline static std::string GetFormatName(int eFormat);
    inline int GetBytesPerSample(void) const;
    inline static int GetBytesPerSample(int eFormat);
    inline int GetChannelsPerSample(void) const;
    inline static int GetChannelsPerSample(int eFormat);
    inline unsigned int GetFrequency(void) const;
    inline int GetDataSize(void) const;
    inline unsigned char* GetData(void) const;

    // Streaming support.当这些函数被调用时,共享系统将被自动调用.
    // 对于Load函数,如果具有filename的wave已经载入内存,
    // 则该wave被找到并作为返回值(例如,出于共享的目的).
    // 否则,创建一个新的wave并返回.filename被用作wave name.
    // 参考WaveCatalog::Find函数中对这个函数的调用.
    static Wave* Load(const char* pWaveName);

    // 这个函数用来支持保存程序生成的wave数据,
    // 或者可以用来支持把其他类型的audio格式的数据转换为sewf格式.
    // 传入的filename不会替代原有的wave name,只是用于生成的文件名.
    bool Save(const char* pFileName);

protected:
    // support for streaming.
    Wave(void);

    FormatMode m_eFormat;
    unsigned int m_uiFrequency;
    int m_iDataSize;
    unsigned char* m_pData;

    bool m_bIsInCatalog;

    static int ms_BytesPerSample[WT_COUNT];
    static int ms_ChannelsPerSample[WT_COUNT];
    static std::string ms_FormatName[WT_COUNT];
};

typedef SmartPointer<Wave> WavePtr;

#include "SEWave.inl"

}

#endif
