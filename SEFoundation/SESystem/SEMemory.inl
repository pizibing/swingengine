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

//----------------------------------------------------------------------------
inline size_t& SEMemory::MaxAllowedBytes()
{
    return CurMaxAllowedBytes;
}
//----------------------------------------------------------------------------
inline bool& SEMemory::TrackSizes()
{
    return IsTrackSizes;
}
//----------------------------------------------------------------------------
inline size_t SEMemory::GetNumNewCalls()
{
    return CurNumNewCalls;
}
//----------------------------------------------------------------------------
inline size_t SEMemory::GetNumDeleteCalls()
{
    return CurNumDeleteCalls;
}
//----------------------------------------------------------------------------
inline size_t SEMemory::GetNumBlocks()
{
    return CurNumBlocks;
}
//----------------------------------------------------------------------------
inline size_t SEMemory::GetNumBytes()
{
    return CurNumBytes;
}
//----------------------------------------------------------------------------
inline size_t SEMemory::GetMaxAllocatedBytes()
{
    return CurMaxAllocatedBytes;
}
//----------------------------------------------------------------------------
inline size_t SEMemory::GetMaxBlockSize()
{
    return CurMaxBlockSize;
}
//----------------------------------------------------------------------------
inline size_t SEMemory::GetHistogram(int i)
{
    if( 0 <= i && i <= 31 )
    {
        return Histogram[i];
    }

    return 0;
}
//----------------------------------------------------------------------------
inline const SEMemory::SEMemoryBlock* SEMemory::GetHead()
{
    return MemBlockHead;
}
//----------------------------------------------------------------------------
inline const SEMemory::SEMemoryBlock* SEMemory::GetTail()
{
    return MemBlockTail;
}
//----------------------------------------------------------------------------
