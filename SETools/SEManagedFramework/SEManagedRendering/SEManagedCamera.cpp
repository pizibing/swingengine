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

#include "SEManagedFrameworkPCH.h"
#include "SEManagedCamera.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedCamera::ManagedCamera()
{
    // Create a smart pointer which will point to the native camera.
    m_pspCamera = SE_NEW CameraPtr;

    // Create the native camera.
    (*m_pspCamera) = SE_NEW Camera;
}
//---------------------------------------------------------------------------
ManagedCamera::~ManagedCamera()
{
    SE_DELETE m_pspCamera;
    m_pspCamera = 0;
}
//---------------------------------------------------------------------------
void ManagedCamera::SetFrame(ManagedVector3f^ thLocation, 
    ManagedVector3f^ thRVector, ManagedVector3f^ thUVector, 
    ManagedVector3f^ thDVector)
{
    Vector3f vec3fLoc, vec3fR, vec3fU, vec3fD;
    thLocation->ToVector3f(vec3fLoc);
    thRVector->ToVector3f(vec3fR);
    thUVector->ToVector3f(vec3fU);
    thDVector->ToVector3f(vec3fD);
    (*m_pspCamera)->SetFrame(vec3fLoc, vec3fR, vec3fU, vec3fD);
}
//---------------------------------------------------------------------------
void ManagedCamera::SetLocation(ManagedVector3f^ thLocation)
{
    Vector3f vec3fLoc;
    thLocation->ToVector3f(vec3fLoc);
    (*m_pspCamera)->SetLocation(vec3fLoc);
}
//---------------------------------------------------------------------------
void ManagedCamera::SetAxes(ManagedVector3f^ thRVector, 
    ManagedVector3f^ thUVector, ManagedVector3f^ thDVector)
{
    Vector3f vec3fR, vec3fU, vec3fD;
    thRVector->ToVector3f(vec3fR);
    thUVector->ToVector3f(vec3fU);
    thDVector->ToVector3f(vec3fD);
    (*m_pspCamera)->SetAxes(vec3fR, vec3fU, vec3fD);
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedCamera::GetLocation()
{
    ManagedVector3f^ thRes = gcnew ManagedVector3f;
    thRes->FromVector3f((*m_pspCamera)->GetLocation());

    return thRes;
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedCamera::GetRVector()
{
    ManagedVector3f^ thRes = gcnew ManagedVector3f;
    thRes->FromVector3f((*m_pspCamera)->GetRVector());

    return thRes;
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedCamera::GetUVector()
{
    ManagedVector3f^ thRes = gcnew ManagedVector3f;
    thRes->FromVector3f((*m_pspCamera)->GetUVector());

    return thRes;
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedCamera::GetDVector()
{
    ManagedVector3f^ thRes = gcnew ManagedVector3f;
    thRes->FromVector3f((*m_pspCamera)->GetDVector());

    return thRes;
}
//---------------------------------------------------------------------------
Camera* ManagedCamera::GetNativeCamera()
{
    return (Camera*)(*m_pspCamera);
}
//---------------------------------------------------------------------------
void ManagedCamera::SetFrustum(float fRMin, float fRMax, float fUMin, 
    float fUMax, float fDMin, float fDMax)
{
    (*m_pspCamera)->SetFrustum(fRMin, fRMax, fUMin, fUMax, fDMin, fDMax);
}
//---------------------------------------------------------------------------
void ManagedCamera::GetFrustum(float% trfRMin, float% trfRMax, float% trfUMin, 
    float% trfUMax, float% trfDMin, float% trfDMax)
{
    float fRMin = trfRMin;
    float fRMax = trfRMax;
    float fUMin = trfUMin;
    float fUMax = trfUMax;
    float fDMin = trfDMin;
    float fDMax = trfDMax;
    (*m_pspCamera)->GetFrustum(fRMin, fRMax, fUMin, fUMax, fDMin, fDMax);
    trfRMin = fRMin;
    trfRMax = fRMax;
    trfUMin = fUMin;
    trfUMax = fUMax;
    trfDMin = fDMin;
    trfDMax = fDMax;
}
//---------------------------------------------------------------------------