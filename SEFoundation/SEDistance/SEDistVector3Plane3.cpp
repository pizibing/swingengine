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
#include "SEDistVector3Plane3.h"

using namespace Swing;

//----------------------------------------------------------------------------
DistVector3Plane3f::DistVector3Plane3f(const Vector3f& rVector,
    const Plane3f& rPlane)
    :
    m_pVector(&rVector),
    m_pPlane(&rPlane)
{
}
//----------------------------------------------------------------------------
const Vector3f& DistVector3Plane3f::GetVector() const
{
    return *m_pVector;
}
//----------------------------------------------------------------------------
const Plane3f& DistVector3Plane3f::GetPlane() const
{
    return *m_pPlane;
}
//----------------------------------------------------------------------------
float DistVector3Plane3f::Get()
{
    float fSigned = m_pPlane->Normal.Dot(*m_pVector) - m_pPlane->Constant;
    m_ClosestPoint0 = *m_pVector;
    m_ClosestPoint1 = *m_pVector - fSigned*m_pPlane->Normal;

    return Math<float>::FAbs(fSigned);
}
//----------------------------------------------------------------------------
float DistVector3Plane3f::GetSquared()
{
    float fSigned = m_pPlane->Normal.Dot(*m_pVector) - m_pPlane->Constant;
    m_ClosestPoint0 = *m_pVector;
    m_ClosestPoint1 = *m_pVector - fSigned*m_pPlane->Normal;

    return fSigned*fSigned;
}
//----------------------------------------------------------------------------
float DistVector3Plane3f::Get(float fT, const Vector3f& rVelocity0,
    const Vector3f& rVelocity1)
{
    Vector3f vec3fMVector = *m_pVector + fT*rVelocity0;
    float fMConstant = m_pPlane->Constant +
        fT*m_pPlane->Normal.Dot(rVelocity1);
    Plane3f tempMPlane(m_pPlane->Normal, fMConstant);

    return DistVector3Plane3f(vec3fMVector, tempMPlane).Get();
}
//----------------------------------------------------------------------------
float DistVector3Plane3f::GetSquared(float fT, const Vector3f& rVelocity0, 
    const Vector3f& rVelocity1)
{
    Vector3f vec3fMVector = *m_pVector + fT*rVelocity0;
    float fMConstant = m_pPlane->Constant +
        fT*m_pPlane->Normal.Dot(rVelocity1);
    Plane3f tempMPlane(m_pPlane->Normal, fMConstant);

    return DistVector3Plane3f(vec3fMVector, tempMPlane).GetSquared();
}
//----------------------------------------------------------------------------
