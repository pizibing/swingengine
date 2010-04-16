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

#ifndef Swing_Memory_H
#define Swing_Memory_H

#ifndef SE_MEMORY_MANAGER

#define SE_NEW new
#define SE_DELETE delete

#else

// 重载new和delete,实现内存追踪

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:内存追踪管理类
// 说明:
// 作者:Sun Che
// 时间:20080202
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEMemory
{
public:
    struct SEMemoryBlock
    {
        size_t Size;
        const char* File;
        unsigned int Line;
        bool IsArray;
        SEMemoryBlock* Prev;
        SEMemoryBlock* Next;
    };

    static size_t& MaxAllowedBytes(void);
    static bool& TrackSizes(void);

    static size_t GetNumNewCalls(void);
    static size_t GetNumDeleteCalls(void);
    static size_t GetNumBlocks(void);
    static size_t GetNumBytes(void);
    static size_t GetMaxAllocatedBytes(void);
    static size_t GetMaxBlockSize(void);
    static size_t GetHistogram(int i);

    // 用于迭代当前内存list
    static const SEMemoryBlock* GetHead(void);
    static const SEMemoryBlock* GetTail(void);

    // 生成当前内存报告
    static void GenerateReport(const char* pFileName);

private:
    // 记录当前运行期间new和delete的调用次数
    static size_t CurNumNewCalls;
    static size_t CurNumDeleteCalls;

    // 如果希望限制内存使用量,则应用程序可设置此值,
    // 当应用程序超过指定内存使用量后,断言提示
    // 默认值为0,此时不进行内存使用量比较
    static size_t CurMaxAllowedBytes;

    // 当前已分配的内存块数量
    static size_t CurNumBlocks;

    // 当前已分配的字节总数(不包括SEMemoryBlock结构占用的字节总数)
    static size_t CurNumBytes;

    // 内存块list头,尾
    static SEMemoryBlock* MemBlockHead;
    static SEMemoryBlock* MemBlockTail;

    // 设置为true时追踪CurMaxBlockSize,Histogram
    static bool IsTrackSizes;

    // 内存字节总数历史最大值(不包括SEMemoryBlock结构占用的字节总数)
    static size_t CurMaxAllocatedBytes;

    // 当前已分配的最大内存块字节数
    static size_t CurMaxBlockSize;

    // 追踪已经分配的各种尺寸的内存块的各自数量,
    // Histogram[0]记录已经分配的1字节的内存块数量,
    // Histogram[31]记录已经分配的大于等于pow(2,30)字节的内存块数量
    // 其余Histogram[i]记录已经分配的N字节内存块数量,
    // 其中N满足:pow(2,i-1) < N <= pow(2,i)
    static size_t Histogram[32];

public:
    // 内部使用
    static void* Allocate(size_t uiSize, char* pFile, unsigned int uiLine,
        bool bIsArray);
    static void Deallocate(char* pAddr, bool bIsArray);
    static void InsertBlock(SEMemoryBlock* pBlock);
    static void RemoveBlock(SEMemoryBlock* pBlock);
};

#include "SEMemory.inl"

}

#define SE_NEW new(__FILE__,__LINE__)
#define SE_DELETE delete

void* operator new(size_t uiSize);
void* operator new[](size_t uiSize);
void* operator new(size_t uiSize, char* pFile, unsigned int uiLine);
void* operator new[](size_t uiSize, char* pFile, unsigned int uiLine);
void operator delete(void* pAddr);
void operator delete[](void* pAddr);
void operator delete(void* pAddr, char* pFile, unsigned int uiLine);
void operator delete[](void* pAddr, char* pFile, unsigned int uiLine);

#endif
#endif
