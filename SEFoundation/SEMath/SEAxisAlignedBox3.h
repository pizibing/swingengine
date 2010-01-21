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

#ifndef Swing_AxisAlignedBox3_H
#define Swing_AxisAlignedBox3_H

#include "SEFoundationLIB.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Name:Single precision floating-point 3D axis aligned box class
// Description:
// Author:Sun Che
// Date:20100121
//----------------------------------------------------------------------------
class SE_FOUNDATION_API AxisAlignedBox3f
{
public:
    AxisAlignedBox3f(void);

    // The caller must ensure that fXMin <= fXMax and fYMin <= fYMax. The
    // class will not check for validity of the input.
    AxisAlignedBox3f(float fXMin, float fXMax, float fYMin, float fYMax,
        float fZMin, float fZMax);

    // Overlap testing is in the strict sense. If the two boxes are just
    // touching along a common edge, the boxes are reported as overlapping.
    bool HasXOverlap(const AxisAlignedBox3f& rBox) const;
    bool HasYOverlap(const AxisAlignedBox3f& rBox) const;
    bool HasZOverlap(const AxisAlignedBox3f& rBox) const;
    bool TestIntersection(const AxisAlignedBox3f& rBox) const;

    // The return value is 'true' if there is overlap. In this case the
    // intersection is stored in rIntr. If the return value is 'false',
    // there is no overlap. In this case rIntr is undefined.
    bool FindIntersection(const AxisAlignedBox3f& rBox,
        AxisAlignedBox3f& rIntr) const;

    float Min[3], Max[3];
};

}

#endif
