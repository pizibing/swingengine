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

#include "SEINativeObject.h"
#include "SEManagedVector3.h"
#include "SEManagedMatrix3.h"
#include "SEManagedRay3.h"

namespace Swing{ namespace Tools{ namespace ManagedFramework{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20091219
//----------------------------------------------------------------------------
public ref class ManagedCamera sealed : INativeObject
{
public:
    ManagedCamera(void);
    ~ManagedCamera(void);

    // Orientation access.
    void SetFrame(ManagedVector3f^ thLocation, ManagedVector3f^ thRVector,
        ManagedVector3f^ thUVector, ManagedVector3f^ thDVector);
    void SetLocation(ManagedVector3f^ thLocation);
    void SetAxes(ManagedVector3f^ thRVector, ManagedVector3f^ thUVector, 
        ManagedVector3f^ thDVector);
    ManagedVector3f^ GetLocation(void);
    ManagedVector3f^ GetRVector(void);
    ManagedVector3f^ GetUVector(void);
    ManagedVector3f^ GetDVector(void);

    // Frustum access.
    void SetFrustum(float fRMin, float fRMax, float fUMin, float fUMax,
        float fDMin, float fDMax);
    void GetFrustum(float% trfRMin, float% trfRMax, float% trfUMin, 
        float% trfUMax, float% trfDMin, float% trfDMax);

    // Perspective/orthogonal projection access.
    void SetPerspective(bool bPerspective);
    bool IsPerspective(void);

    // Mouse picking support.
    bool GetPickRay(int iX, int iY, int iWidth, int iHeight, 
        ManagedRay3f^ thRay);

    // Virtual track ball rotation support.
    bool GetTrackBallRotate(float fX0, float fY0, float fX1, float fY1, 
        ManagedMatrix3f^ thMat);

    // Implement INativeObject interface.
    virtual void SetName(String^ thName);
    virtual String^ GetName(void);
    //
    virtual int GetNativeReferences(void);

internal:
    [CLSCompliant(false)]
    ManagedCamera(SECamera* pCamera);

    [CLSCompliant(false)]
    SECamera* GetNativeCamera(void);

private:
    SECameraPtr* m_pspCamera;
};

}}}