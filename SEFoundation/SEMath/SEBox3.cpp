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
#include "SEBox3.h"

using namespace Swing;

//----------------------------------------------------------------------------
Box3f::Box3f()
{
}
//----------------------------------------------------------------------------
Box3f::Box3f(const Vector3f& rCenter, const Vector3f* aAxis, 
    const float* afExtent)
    : Center(rCenter)
{
    for( int i = 0; i < 3; i++ )
    {
        Axis[i] = aAxis[i];
        Extent[i] = afExtent[i];
    }
}
//----------------------------------------------------------------------------
Box3f::Box3f(const Vector3f& rCenter, const Vector3f& rAxis0, 
    const Vector3f& rAxis1, const Vector3f& rAxis2, float fExtent0, 
    float fExtent1, float fExtent2)
    : Center(rCenter)
{
    Axis[0] = rAxis0;
    Axis[1] = rAxis1;
    Axis[2] = rAxis2;
    Extent[0] = fExtent0;
    Extent[1] = fExtent1;
    Extent[2] = fExtent2;
}
//----------------------------------------------------------------------------
void Box3f::ComputeVertices(Vector3f aVertex[8]) const
{
    Vector3f aEAxis[3] =
    {
        Extent[0] * Axis[0],
        Extent[1] * Axis[1],
        Extent[2] * Axis[2]
    };

    aVertex[0] = Center - aEAxis[0] - aEAxis[1] - aEAxis[2];
    aVertex[1] = Center + aEAxis[0] - aEAxis[1] - aEAxis[2];
    aVertex[2] = Center + aEAxis[0] + aEAxis[1] - aEAxis[2];
    aVertex[3] = Center - aEAxis[0] + aEAxis[1] - aEAxis[2];
    aVertex[4] = Center - aEAxis[0] - aEAxis[1] + aEAxis[2];
    aVertex[5] = Center + aEAxis[0] - aEAxis[1] + aEAxis[2];
    aVertex[6] = Center + aEAxis[0] + aEAxis[1] + aEAxis[2];
    aVertex[7] = Center - aEAxis[0] + aEAxis[1] + aEAxis[2];
}
//----------------------------------------------------------------------------