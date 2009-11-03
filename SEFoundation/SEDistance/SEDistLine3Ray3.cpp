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
#include "SEDistLine3Ray3.h"

using namespace Swing;

//----------------------------------------------------------------------------
DistLine3Ray3f::DistLine3Ray3f(const Line3f& rLine, const Ray3f& rRay)
    :
    m_pLine(&rLine),
    m_pRay(&rRay)
{
}
//----------------------------------------------------------------------------
const Line3f& DistLine3Ray3f::GetLine() const
{
    return *m_pLine;
}
//----------------------------------------------------------------------------
const Ray3f& DistLine3Ray3f::GetRay() const
{
    return *m_pRay;
}
//----------------------------------------------------------------------------
float DistLine3Ray3f::Get()
{
    float fSqrDist = GetSquared();

    return Math<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float DistLine3Ray3f::GetSquared()
{
    Vector3f vec3fDiff = m_pLine->Origin - m_pRay->Origin;
    float fA01 = -m_pLine->Direction.Dot(m_pRay->Direction);
    float fB0 = vec3fDiff.Dot(m_pLine->Direction);
    float fC = vec3fDiff.GetSquaredLength();
    float fDet = Math<float>::FAbs(1.0f - fA01*fA01);
    float fB1, fS0, fS1, fSqrDist;

    if( fDet >= Math<float>::ZERO_TOLERANCE )
    {
        fB1 = -vec3fDiff.Dot(m_pRay->Direction);
        fS1 = fA01*fB0 - fB1;

        if( fS1 >= 0.0f )
        {
            // ���ϵ��������,һ����ֱ����һ����������.
            float fInvDet = 1.0f / fDet;
            fS0 = (fA01*fB1 - fB0)*fInvDet;
            fS1 *= fInvDet;
            fSqrDist = fS0*(fS0 + fA01*fS1 + 2.0f*fB0) +
                fS1*(fA01*fS0 + fS1 + 2.0f*fB1) + fC;
        }
        else
        {
            // ����ԭ���ֱ�����ϵ��������.
            fS0 = -fB0;
            fS1 = 0.0f;
            fSqrDist = fB0*fS0 + fC;
        }
    }
    else
    {
        // ֱ�ߺ�����ƽ��,ѡ������ԭ�����ڵ�������.
        fS0 = -fB0;
        fS1 = 0.0f;
        fSqrDist = fB0*fS0 + fC;
    }

    m_ClosestPoint0 = m_pLine->Origin + fS0*m_pLine->Direction;
    m_ClosestPoint1 = m_pRay->Origin + fS1*m_pRay->Direction;
    m_fLineParameter = fS0;
    m_fRayParameter = fS1;

    return Math<float>::FAbs(fSqrDist);
}
//----------------------------------------------------------------------------
float DistLine3Ray3f::Get(float fT, const Vector3f& rVelocity0,
    const Vector3f& rVelocity1)
{
    Vector3f vec3fMOrigin0 = m_pLine->Origin + fT*rVelocity0;
    Vector3f vec3fMOrigin1 = m_pRay->Origin + fT*rVelocity1;
    Line3f tempMLine(vec3fMOrigin0, m_pLine->Direction);
    Ray3f tempMRay(vec3fMOrigin1, m_pRay->Direction);

    return DistLine3Ray3f(tempMLine, tempMRay).Get();
}
//----------------------------------------------------------------------------
float DistLine3Ray3f::GetSquared(float fT, const Vector3f& rVelocity0, 
    const Vector3f& rVelocity1)
{
    Vector3f vec3fMOrigin0 = m_pLine->Origin + fT*rVelocity0;
    Vector3f vec3fMOrigin1 = m_pRay->Origin + fT*rVelocity1;
    Line3f tempMLine(vec3fMOrigin0, m_pLine->Direction);
    Ray3f tempMRay(vec3fMOrigin1, m_pRay->Direction);

    return DistLine3Ray3f(tempMLine, tempMRay).GetSquared();
}
//----------------------------------------------------------------------------
float DistLine3Ray3f::GetLineParameter() const
{
    return m_fLineParameter;
}
//----------------------------------------------------------------------------
float DistLine3Ray3f::GetRayParameter() const
{
    return m_fRayParameter;
}
//----------------------------------------------------------------------------