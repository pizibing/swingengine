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

#include "SEManagedVector3.h"

using namespace System;

namespace Swing{ namespace Tools{ namespace ManagedFramework{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20100107
//----------------------------------------------------------------------------
public ref class ManagedRay3f sealed
{
public:
    ManagedRay3f(void);
    ManagedRay3f(ManagedVector3f^ thOrigin, ManagedVector3f^ thDirection);

    // Properties.
    property ManagedVector3f^ Origin
    {
        ManagedVector3f^ get(void);
        void set(ManagedVector3f^ thOrigin);
    }
    property ManagedVector3f^ Direction
    {
        ManagedVector3f^ get(void);
        void set(ManagedVector3f^ thDirection);
    }

internal:
    [CLSCompliant(false)]
    ManagedRay3f(const SERay3f& rRay);
    [CLSCompliant(false)]
    ManagedRay3f(const SEVector3f& rOrigin, const SEVector3f& rDirection);

    [CLSCompliant(false)]
    void ToRay3f(SERay3f& rRay);

    [CLSCompliant(false)]
    void FromRay3f(const SERay3f& rRay);

private:
    ManagedVector3f^ m_thOrigin;
    ManagedVector3f^ m_thDirection;
};

}}}