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
// Name:Managed single precision floating-point 3x3 matrix class
// Description:
// Author:Sun Che
// Date:20091227
//----------------------------------------------------------------------------
public ref class ManagedMatrix3f sealed
{
public:
    ManagedMatrix3f(void);
    ManagedMatrix3f(float fM11, float fM12, float fM13,
                    float fM21, float fM22, float fM23,
                    float fM31, float fM32, float fM33);
    ManagedMatrix3f(ManagedVector3f^ thAxisVec, float fAngle);

    // Euler operations.
    void FromEulerAnglesXYZ(float fYAngle, float fPAngle, float fRAngle);
    bool ToEulerAnglesXYZ(float% trfYAngle, float% trfPAngle, float% trfRAngle);

	// Algebra operations.
    static ManagedVector3f^ Vector3Multiply(ManagedVector3f^ thVec, 
        ManagedMatrix3f^ thMat);
    static ManagedVector3f^ MultiplyVector3(ManagedMatrix3f^ thMat, 
        ManagedVector3f^ thVec);
    static ManagedMatrix3f^ Multiply(ManagedMatrix3f^ thLhsMat, 
        ManagedMatrix3f^ thRhsMat);

    // Gram-Schmidt orthonormalization(must be applied to a rotation matrix).
    void Orthonormalize(void);

    // System::Object overrides.
    virtual bool Equals(Object^ thObj) override;

internal:
    [CLSCompliant(false)]
    ManagedMatrix3f(const Matrix3f& rMat);

    [CLSCompliant(false)]
    void ToMatrix3f(Matrix3f& rMat);

    [CLSCompliant(false)]
    void FromMatrix3f(const Matrix3f& rMat);

private:
    array<float>^ m_afData;
};

}}}