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
#include "SEDistLine3Segment3.h"

using namespace Swing;

//----------------------------------------------------------------------------
DistLine3Segment3f::DistLine3Segment3f(const Line3f& rLine,
    const Segment3f& rSegment)
    :
    m_pLine(&rLine),
    m_pSegment(&rSegment)
{
}
//----------------------------------------------------------------------------
const Line3f& DistLine3Segment3f::GetLine() const
{
    return *m_pLine;
}
//----------------------------------------------------------------------------
const Segment3f& DistLine3Segment3f::GetSegment() const
{
    return *m_pSegment;
}
//----------------------------------------------------------------------------
float DistLine3Segment3f::Get()
{
    float fSqrDist = GetSquared();

    return Math<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float DistLine3Segment3f::GetSquared()
{
    Vector3f vec3fDiff = m_pLine->Origin - m_pSegment->Origin;
    float fA01 = -m_pLine->Direction.Dot(m_pSegment->Direction);
    float fB0 = vec3fDiff.Dot(m_pLine->Direction);
    float fC = vec3fDiff.GetSquaredLength();
    float fDet = Math<float>::FAbs(1.0f - fA01*fA01);
    float fB1, fS0, fS1, fSqrDist, fExtDet;

    if( fDet >= Math<float>::ZERO_TOLERANCE )
    {
        // 直线和线段不平行.
        fB1 = -vec3fDiff.Dot(m_pSegment->Direction);
        fS1 = fA01*fB0 - fB1;
        fExtDet = m_pSegment->Extent*fDet;

        if( fS1 >= -fExtDet )
        {
            if( fS1 <= fExtDet )
            {
                // 线上点是最近点,一个在直线上一个在线段上.
                float fInvDet = 1.0f / fDet;
                fS0 = (fA01*fB1 - fB0)*fInvDet;
                fS1 *= fInvDet;
                fSqrDist = fS0*(fS0 + fA01*fS1 + 2.0f*fB0) +
                    fS1*(fA01*fS0+fS1 + 2.0f*fB1) + fC;
            }
            else
            {
                // 线段端点e1和直线线上点是最近点.
                fS1 = m_pSegment->Extent;
                fS0 = -(fA01*fS1 + fB0);
                fSqrDist = -fS0*fS0 + fS1*(fS1 + 2.0f*fB1) + fC;
            }
        }
        else
        {
            // 线段端点e0和直线线上点是最近点.
            fS1 = -m_pSegment->Extent;
            fS0 = -(fA01*fS1 + fB0);
            fSqrDist = -fS0*fS0 + fS1*(fS1 + 2.0f*fB1) + fC;
        }
    }
    else
    {
        // 直线和线段平行,选择线段原点所在的最近点对.
        fS1 = 0.0f;
        fS0 = -fB0;
        fSqrDist = fB0*fS0 + fC;
    }

    m_ClosestPoint0 = m_pLine->Origin + fS0*m_pLine->Direction;
    m_ClosestPoint1 = m_pSegment->Origin + fS1*m_pSegment->Direction;
    m_fLineParameter = fS0;
    m_fSegmentParameter = fS1;

    return Math<float>::FAbs(fSqrDist);
}
//----------------------------------------------------------------------------
float DistLine3Segment3f::Get(float fT, const Vector3f& rVelocity0,
    const Vector3f& rVelocity1)
{
    Vector3f vec3fMOrigin0 = m_pLine->Origin + fT*rVelocity0;
    Vector3f vec3fMOrigin1 = m_pSegment->Origin + fT*rVelocity1;
    Line3f tempMLine(vec3fMOrigin0, m_pLine->Direction);
    Segment3f tempMSegment(vec3fMOrigin1, m_pSegment->Direction,
        m_pSegment->Extent);

    return DistLine3Segment3f(tempMLine, tempMSegment).Get();
}
//----------------------------------------------------------------------------
float DistLine3Segment3f::GetSquared(float fT, const Vector3f& rVelocity0, 
    const Vector3f& rVelocity1)
{
    Vector3f vec3fMOrigin0 = m_pLine->Origin + fT*rVelocity0;
    Vector3f vec3fMOrigin1 = m_pSegment->Origin + fT*rVelocity1;
    Line3f tempMLine(vec3fMOrigin0, m_pLine->Direction);
    Segment3f tempMSegment(vec3fMOrigin1, m_pSegment->Direction,
        m_pSegment->Extent);

    return DistLine3Segment3f(tempMLine, tempMSegment).GetSquared();
}
//----------------------------------------------------------------------------
float DistLine3Segment3f::GetLineParameter() const
{
    return m_fLineParameter;
}
//----------------------------------------------------------------------------
float DistLine3Segment3f::GetSegmentParameter() const
{
    return m_fSegmentParameter;
}
//----------------------------------------------------------------------------
