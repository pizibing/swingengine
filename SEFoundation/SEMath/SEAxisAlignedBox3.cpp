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
#include "SEAxisAlignedBox3.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEAxisAlignedBox3f::SEAxisAlignedBox3f()
{
}
//----------------------------------------------------------------------------
SEAxisAlignedBox3f::SEAxisAlignedBox3f(float fXMin, float fXMax, float fYMin,
    float fYMax, float fZMin, float fZMax)
{
    Min[0] = fXMin;
    Max[0] = fXMax;
    Min[1] = fYMin;
    Max[1] = fYMax;
    Min[2] = fZMin;
    Max[2] = fZMax;
}
//----------------------------------------------------------------------------
bool SEAxisAlignedBox3f::HasXOverlap(const SEAxisAlignedBox3f& rBox) const
{
    return Max[0] >= rBox.Min[0] && Min[0] <= rBox.Max[0];
}
//----------------------------------------------------------------------------
bool SEAxisAlignedBox3f::HasYOverlap(const SEAxisAlignedBox3f& rBox) const
{
    return Max[1] >= rBox.Min[1] && Min[1] <= rBox.Max[1];
}
//----------------------------------------------------------------------------
bool SEAxisAlignedBox3f::HasZOverlap(const SEAxisAlignedBox3f& rBox) const
{
    return Max[2] >= rBox.Min[2] && Min[2] <= rBox.Max[2];
}
//----------------------------------------------------------------------------
bool SEAxisAlignedBox3f::TestIntersection(const SEAxisAlignedBox3f& rBox) const
{
    for( int i = 0; i < 3; i++ )
    {
        if( Max[i] < rBox.Min[i] || Min[i] > rBox.Max[i] )
        {
            return false;
        }
    }

    return true;
}
//----------------------------------------------------------------------------
bool SEAxisAlignedBox3f::FindIntersection(const SEAxisAlignedBox3f& rBox,
    SEAxisAlignedBox3f& rIntr) const
{
    int i;
    for( i = 0; i < 3; i++ )
    {
        if( Max[i] < rBox.Min[i] || Min[i] > rBox.Max[i] )
        {
            return false;
        }
    }

    for( i = 0; i < 3; i++ )
    {
        if( Max[i] <= rBox.Max[i] )
        {
            rIntr.Max[i] = Max[i];
        }
        else
        {
            rIntr.Max[i] = rBox.Max[i];
        }

        if( Min[i] <= rBox.Min[i] )
        {
            rIntr.Min[i] = rBox.Min[i];
        }
        else
        {
            rIntr.Min[i] = Min[i];
        }
    }

    return true;
}
//----------------------------------------------------------------------------
