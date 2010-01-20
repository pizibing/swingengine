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

#include "SEINativeSpatial.h"
#include "SEManagedRay3.h"
#include "SEManagedTriMesh.h"

namespace Swing{ namespace Tools{ namespace ManagedFramework{

//----------------------------------------------------------------------------
// Name:Managed pick manager class
// Description: This is a wrapper class which wrapps the native picking system.
// Author:Sun Che
// Date:20100120
//----------------------------------------------------------------------------
public ref class ManagedPickManager sealed
{
public:
    ManagedPickManager(void);
    ~ManagedPickManager(void);

    // Do a picking operation on the given native spatial object with the 
    // given ray(in world space).The result pick array is stored inside this 
    // pick manager.
    void DoPick(ManagedRay3f^ thRay, INativeSpatial^ thSpatial);

    // Get the closest ManagedTriMesh object from the result of last picking 
    // operation.
    // TODO:
    // Impliment enumeration functions to let user examine the result array.
    ManagedTriMesh^ GetClosestTriMesh(void);

private:
    Spatial::PickArray* m_pPickResults;
};

}}}