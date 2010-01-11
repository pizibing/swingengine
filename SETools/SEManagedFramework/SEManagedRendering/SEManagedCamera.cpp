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
    m_pspCamera = SE_NEW CameraPtr;
    (*m_pspCamera) = SE_NEW Camera;
}
//---------------------------------------------------------------------------
ManagedCamera::ManagedCamera(Camera* pCamera)
{
    m_pspCamera = SE_NEW CameraPtr;
    (*m_pspCamera) = pCamera;
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
    SE_NULL_ARGUMENT_CHECK(thLocation, "thLocation");
    SE_NULL_ARGUMENT_CHECK(thRVector, "thRVector");
    SE_NULL_ARGUMENT_CHECK(thUVector, "thUVector");
    SE_NULL_ARGUMENT_CHECK(thDVector, "thDVector");

    Vector3f vec3fLoc, vec3fR, vec3fU, vec3fD;
    thLocation->ToVector3f(vec3fLoc);
    thRVector->ToVector3f(vec3fR);
    thUVector->ToVector3f(vec3fU);
    thDVector->ToVector3f(vec3fD);

    SE_NULL_REFERENCE_CHECK(m_pspCamera, "Native pointer is null");
    (*m_pspCamera)->SetFrame(vec3fLoc, vec3fR, vec3fU, vec3fD);
}
//---------------------------------------------------------------------------
void ManagedCamera::SetLocation(ManagedVector3f^ thLocation)
{
    SE_NULL_ARGUMENT_CHECK(thLocation, "thLocation");

    Vector3f vec3fLoc;
    thLocation->ToVector3f(vec3fLoc);

    SE_NULL_REFERENCE_CHECK(m_pspCamera, "Native pointer is null");
    (*m_pspCamera)->SetLocation(vec3fLoc);
}
//---------------------------------------------------------------------------
void ManagedCamera::SetAxes(ManagedVector3f^ thRVector, 
    ManagedVector3f^ thUVector, ManagedVector3f^ thDVector)
{
    SE_NULL_ARGUMENT_CHECK(thRVector, "thRVector");
    SE_NULL_ARGUMENT_CHECK(thUVector, "thUVector");
    SE_NULL_ARGUMENT_CHECK(thDVector, "thDVector");

    Vector3f vec3fR, vec3fU, vec3fD;
    thRVector->ToVector3f(vec3fR);
    thUVector->ToVector3f(vec3fU);
    thDVector->ToVector3f(vec3fD);

    SE_NULL_REFERENCE_CHECK(m_pspCamera, "Native pointer is null");
    (*m_pspCamera)->SetAxes(vec3fR, vec3fU, vec3fD);
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedCamera::GetLocation()
{
    ManagedVector3f^ thRes = gcnew ManagedVector3f;

    SE_NULL_REFERENCE_CHECK(m_pspCamera, "Native pointer is null");
    thRes->FromVector3f((*m_pspCamera)->GetLocation());

    return thRes;
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedCamera::GetRVector()
{
    ManagedVector3f^ thRes = gcnew ManagedVector3f;

    SE_NULL_REFERENCE_CHECK(m_pspCamera, "Native pointer is null");
    thRes->FromVector3f((*m_pspCamera)->GetRVector());

    return thRes;
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedCamera::GetUVector()
{
    ManagedVector3f^ thRes = gcnew ManagedVector3f;

    SE_NULL_REFERENCE_CHECK(m_pspCamera, "Native pointer is null");
    thRes->FromVector3f((*m_pspCamera)->GetUVector());

    return thRes;
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedCamera::GetDVector()
{
    ManagedVector3f^ thRes = gcnew ManagedVector3f;

    SE_NULL_REFERENCE_CHECK(m_pspCamera, "Native pointer is null");
    thRes->FromVector3f((*m_pspCamera)->GetDVector());

    return thRes;
}
//---------------------------------------------------------------------------
Camera* ManagedCamera::GetNativeCamera()
{
    SE_NULL_REFERENCE_CHECK(m_pspCamera, "Native pointer is null");

    return (Camera*)(*m_pspCamera);
}
//---------------------------------------------------------------------------
void ManagedCamera::SetFrustum(float fRMin, float fRMax, float fUMin, 
    float fUMax, float fDMin, float fDMax)
{
    SE_NULL_REFERENCE_CHECK(m_pspCamera, "Native pointer is null");
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

    SE_NULL_REFERENCE_CHECK(m_pspCamera, "Native pointer is null");
    (*m_pspCamera)->GetFrustum(fRMin, fRMax, fUMin, fUMax, fDMin, fDMax);

    trfRMin = fRMin;
    trfRMax = fRMax;
    trfUMin = fUMin;
    trfUMax = fUMax;
    trfDMin = fDMin;
    trfDMax = fDMax;
}
//---------------------------------------------------------------------------
void ManagedCamera::SetPerspective(bool bPerspective)
{
    SE_NULL_REFERENCE_CHECK(m_pspCamera, "Native pointer is null");
    (*m_pspCamera)->SetPerspective(bPerspective);
}
//---------------------------------------------------------------------------
bool ManagedCamera::GetPerspective()
{
    SE_NULL_REFERENCE_CHECK(m_pspCamera, "Native pointer is null");
    return (*m_pspCamera)->GetPerspective();
}
//---------------------------------------------------------------------------
bool ManagedCamera::GetPickRay(int iX, int iY, int iWidth, int iHeight, 
    ManagedRay3f^ thRay)
{
    SE_NULL_ARGUMENT_CHECK(thRay, "thRay");
    SE_NULL_REFERENCE_CHECK(m_pspCamera, "Native pointer is null");

    Ray3f tempRay;
    bool bRes = (*m_pspCamera)->GetPickRay(iX, iY, iWidth, iHeight, tempRay);
    thRay->FromRay3f(tempRay);

    return bRes;
}
//---------------------------------------------------------------------------
bool ManagedCamera::GetTrackBallRotate(float fX0, float fY0, float fX1, 
    float fY1, ManagedMatrix3f^ thMat)
{
    SE_NULL_ARGUMENT_CHECK(thMat, "thMat");
    SE_NULL_REFERENCE_CHECK(m_pspCamera, "Native pointer is null");

    Matrix3f mat3fRot;
    bool bRes = (*m_pspCamera)->GetTrackBallRotate(fX0, fY0, fX1, fY1, 
        mat3fRot);
    thMat->FromMatrix3f(mat3fRot);

    return bRes;
}
//---------------------------------------------------------------------------
int ManagedCamera::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspCamera, "Native pointer is null");
    return (*m_pspCamera)->GetReferences();
}
//---------------------------------------------------------------------------