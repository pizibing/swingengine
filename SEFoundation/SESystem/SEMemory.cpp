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

#include "SEFoundationPCH.h"

#ifdef ENGINE_MEMORY_MANAGER

// 如果想进行new/delete[]或new[]/delete的不匹配校验,则打开下面的注释
//#define SE_ENABLE_NEW_DELETE_MISMATCH_ASSERT

// 如果想在Memory::GenerateReport中进行内存一致性检测,则打开下面的注释
//#define SE_ENABLE_CONSISTENCY_CHECK

#include <cassert>
#include <cstdlib>
#include <fstream>
#include "SEMemory.h"

using namespace Swing;

size_t Memory::CurNumNewCalls = 0;
size_t Memory::CurNumDeleteCalls = 0;
size_t Memory::CurMaxAllowedBytes = 0;
size_t Memory::CurNumBlocks = 0;
size_t Memory::CurNumBytes = 0;
Memory::MemoryBlock* Memory::MemBlockHead = 0;
Memory::MemoryBlock* Memory::MemBlockTail = 0;
bool Memory::IsTrackSizes = false;
size_t Memory::CurMaxAllocatedBytes = 0;
size_t Memory::CurMaxBlockSize = 0;
size_t Memory::Histogram[32] =
{
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};

//----------------------------------------------------------------------------
void* Memory::Allocate(size_t uiSize, char* pFile, unsigned int uiLine, 
    bool bIsArray)
{
    CurNumNewCalls++;

    // SE_ASSERT( uiSize > 0 );

    size_t uiExtendedSize = sizeof(MemoryBlock) + uiSize;
    char* pAddr = (char*)malloc(uiExtendedSize);

    MemoryBlock* pBlock = (MemoryBlock*)pAddr;
    pBlock->Size = uiSize;
    pBlock->File = pFile;
    pBlock->Line = uiLine;
    pBlock->IsArray = bIsArray;
    InsertBlock(pBlock);

    // 内存申请者应指向这个位置
    pAddr += sizeof(MemoryBlock);

    CurNumBlocks++;
    CurNumBytes += uiSize;

    // 如果超过应用程序指定的内存最大使用临界值
    if( CurMaxAllowedBytes > 0 && CurNumBytes > CurMaxAllowedBytes )
    {
        // 警告应用程序
        SE_ASSERT( false );
    }

    // 记录内存字节总数历史最大值
    if( CurNumBytes > CurMaxAllocatedBytes )
    {
        CurMaxAllocatedBytes = CurNumBytes;
    }

    if( IsTrackSizes )
    {
        if( uiSize > CurMaxBlockSize )
        {
            CurMaxBlockSize = uiSize;
        }

        unsigned int uiTwoPowerI = 1;
        int i;
        for( i = 0; i <= 30; i++, uiTwoPowerI <<= 1 )
        {
            if( uiSize <= uiTwoPowerI )
            {
                Histogram[i]++;

                break;
            }
        }
        if( i == 31)
        {
            Histogram[i]++;
        }
    }

    return (void*)pAddr;
}
//----------------------------------------------------------------------------
void Memory::Deallocate(char* pAddr, bool bIsArray)
{
    CurNumDeleteCalls++;

    if( !pAddr)
    {
        return;
    }

    pAddr -= sizeof(MemoryBlock);

    // 从双向list中移除此block
    MemoryBlock* pBlock = (MemoryBlock*)pAddr;
    RemoveBlock(pBlock);

#ifdef SE_ENABLE_NEW_DELETE_MISMATCH_ASSERT
    SE_ASSERT( pBlock->IsArray == bIsArray );
#endif

    SE_ASSERT(CurNumBlocks > 0 && CurNumBytes >= pBlock->Size);
    CurNumBlocks--;
    CurNumBytes -= pBlock->Size;

    free(pAddr);
}
//----------------------------------------------------------------------------
void Memory::InsertBlock(MemoryBlock* pBlock)
{
    if( MemBlockTail )
    {
        pBlock->Prev = MemBlockTail;
        pBlock->Next = 0;
        MemBlockTail->Next = pBlock;
        MemBlockTail = pBlock;
    }
    else
    {
        pBlock->Prev = 0;
        pBlock->Next = 0;
        MemBlockHead = pBlock;
        MemBlockTail = pBlock;
    }
}
//----------------------------------------------------------------------------
void Memory::RemoveBlock(MemoryBlock* pBlock)
{
    if( pBlock->Prev )
    {
        pBlock->Prev->Next = pBlock->Next;
    }
    else
    {
        MemBlockHead = pBlock->Next;
    }
    
    if( pBlock->Next )
    {
        pBlock->Next->Prev = pBlock->Prev;
    }
    else
    {
        MemBlockTail = pBlock->Prev;
    }
}
//----------------------------------------------------------------------------
void Memory::GenerateReport(const char* pFileName)
{
    std::ofstream OStr(pFileName);
    SE_ASSERT( OStr );
    if( !OStr )
    {
        return;
    }

    OStr << "Total number of 'new' calls = "
        << (unsigned int)CurNumNewCalls << std::endl;
    OStr << "Total number of 'delete' calls = "
        << (unsigned int)CurNumDeleteCalls << std::endl;
    OStr << "Maximum number of allocated bytes = "
        << (unsigned int)CurMaxAllocatedBytes << std::endl << std::endl;

    OStr << "Remaining number of blocks = "
        << (unsigned int)CurNumBlocks << std::endl;
    OStr << "Remaining number of bytes  = "
        << (unsigned int)CurNumBytes << std::endl << std::endl;

    size_t uiNumKnownBlocks = 0;
    size_t uiNumKnownBytes = 0;
    size_t uiNumUnknownBlocks = 0;
    size_t uiNumUnknownBytes = 0;
    MemoryBlock* pBlock = MemBlockHead;
    while( pBlock )
    {
        if( pBlock->File )
        {
            uiNumKnownBlocks++;
            uiNumKnownBytes += pBlock->Size;
        }
        else
        {
            uiNumUnknownBlocks++;
            uiNumUnknownBytes += pBlock->Size;
        }

        pBlock = pBlock->Next;
    }

#ifdef SE_ENABLE_CONSISTENCY_CHECK
    // 内存一致性检测
    SE_ASSERT( uiNumKnownBlocks + uiNumUnknownBlocks == CurNumBlocks );
    SE_ASSERT( uiNumKnownBytes + uiNumUnknownBytes == CurNumBytes );
#endif

    OStr << "Remaining number of known blocks = "
        << (unsigned int)uiNumKnownBlocks << std::endl;
    OStr << "Remaining number of known bytes  = "
        << (unsigned int)uiNumKnownBytes << std::endl << std::endl;

    OStr << "Remaining number of unknown blocks = "
        << (unsigned int)uiNumUnknownBlocks << std::endl;
    OStr << "Remaining number of unknown bytes  = "
        << (unsigned int)uiNumUnknownBytes << std::endl << std::endl;

    // 输出每个块信息
    pBlock = MemBlockHead;
    size_t uiIndex = 0;
    while( pBlock )
    {
        OStr << "block = " << (unsigned int)uiIndex << std::endl;
        OStr << "size  = " << (unsigned int)pBlock->Size << std::endl;
        if( pBlock->File )
        {
            OStr << "file  = " << pBlock->File << std::endl;
            OStr << "line  = " << pBlock->Line << std::endl;
        }
        else
        {
            OStr << "file  = unknown" << std::endl;
            OStr << "line  = unknown" << std::endl;
        }
        OStr << "array = " << pBlock->IsArray << std::endl << std::endl;
        
		pBlock = pBlock->Next;
        uiIndex++;
    }
    OStr.close();

#ifdef SE_ENABLE_CONSISTENCY_CHECK
    SE_ASSERT( uiIndex == CurNumBlocks );
#endif
}
//----------------------------------------------------------------------------
void* operator new(size_t uiSize)
{
    return Memory::Allocate(uiSize, 0, 0, false);
}
//----------------------------------------------------------------------------
void* operator new[](size_t uiSize)
{
    return Memory::Allocate(uiSize, 0, 0, true);
}
//----------------------------------------------------------------------------
void* operator new(size_t uiSize, char* pFile, unsigned int uiLine)
{
    return Memory::Allocate(uiSize, pFile, uiLine, false);
}
//----------------------------------------------------------------------------
void* operator new[](size_t uiSize, char* pFile, unsigned int uiLine)
{
    return Memory::Allocate(uiSize, pFile, uiLine, true);
}
//----------------------------------------------------------------------------
void operator delete(void* pAddr)
{
    Memory::Deallocate((char*)pAddr, false);
}
//----------------------------------------------------------------------------
void operator delete[](void* pAddr)
{
    Memory::Deallocate((char*)pAddr, true);
}
//----------------------------------------------------------------------------
void operator delete (void* pAddr, char* pFile, unsigned int)
{
    Memory::Deallocate((char*)pAddr,false);
}
//----------------------------------------------------------------------------
void operator delete[](void* pAddr, char* pFile, unsigned int)
{
    Memory::Deallocate((char*)pAddr, true);
}
//----------------------------------------------------------------------------

#endif
