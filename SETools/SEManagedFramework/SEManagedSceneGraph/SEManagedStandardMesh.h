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

#pragma once

#include "SEManagedAttributes.h"
#include "SEManagedTriMesh.h"

namespace Swing{ namespace Tools{ namespace ManagedFramework{

//----------------------------------------------------------------------------
// Name:Managed standard mesh class
// Description:
// Author:Sun Che
// Date:20091229
//----------------------------------------------------------------------------
public ref class ManagedStandardMesh sealed
{
public:
    ManagedStandardMesh(ManagedAttributes^ thAttr);
    ~ManagedStandardMesh(void);

    ManagedTriMesh^ Rectangle(int iXSamples, int iYSamples, float fXExtent,
        float fYExtent);
    ManagedTriMesh^ Disk(int iShellSamples, int iRadialSamples, float fRadius);
    ManagedTriMesh^ Box(float fXExtent, float fYExtent, float fZExtent);
    ManagedTriMesh^ Cylinder(int iAxisSamples, int iRadialSamples, 
        float fRadius, float fHeight, bool bOpen);
    ManagedTriMesh^ Sphere(int iZSamples, int iRadialSamples, float fRadius);
    ManagedTriMesh^ Torus(int iCircleSamples, int iRadialSamples,
        float fOuterRadius, float fInnerRadius);
    ManagedTriMesh^ Cone(int iRadialSamples, float fRadius, float fHeight);

internal:
    [CLSCompliant(false)]
    StandardMesh* GetNativeStandardMesh(void);

private:
    StandardMesh* m_pStandardMesh;
};

}}}