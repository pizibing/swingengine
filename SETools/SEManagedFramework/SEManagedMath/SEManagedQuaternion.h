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

#include "SEManagedMatrix3.h"

namespace Swing{ namespace Tools{ namespace ManagedFramework{

//----------------------------------------------------------------------------
// Name:Managed single precision floating-point quaternion class
// Description:
// Author:Sun Che
// Date:20091229
//----------------------------------------------------------------------------
public ref class ManagedQuaternionf sealed
{
public:
    ManagedQuaternionf(void);
    ManagedQuaternionf(float fW, float fX, float fY, float fZ);
    ManagedQuaternionf(ManagedMatrix3f^ thRotMat);

    // Properties.
    property float W
    {
        float get(void);
        void set(float fW);
    }
    property float X
    {
        float get(void);
        void set(float fX);
    }
    property float Y
    {
        float get(void);
        void set(float fY);
    }
    property float Z
    {
        float get(void);
        void set(float fZ);
    }

    // Rotation matrix convertion.
    void FromRotationMatrix(ManagedMatrix3f^ thRotMat);
    ManagedMatrix3f^ GetRotationMatrix(void);

    // System::Object overrides.
    virtual bool Equals(Object^ thObj) override;

internal:
    [CLSCompliant(false)]
    void ToQuaternionf(Quaternionf& rQ);
    [CLSCompliant(false)]
    void FromQuaternionf(const Quaternionf& rQ);

private:
    float m_fW;
    float m_fX;
    float m_fY;
    float m_fZ;
};

}}}