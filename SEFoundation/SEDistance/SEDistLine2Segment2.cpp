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
#include "SEDistLine2Segment2.h"

using namespace Swing;

//----------------------------------------------------------------------------
DistLine2Segment2f::DistLine2Segment2f(const Line2f& rLine,
    const Segment2f& rSegment)
    :
    m_pLine(&rLine),
    m_pSegment(&rSegment)
{
}
//----------------------------------------------------------------------------
const Line2f& DistLine2Segment2f::GetLine() const
{
    return *m_pLine;
}
//----------------------------------------------------------------------------
const Segment2f& DistLine2Segment2f::GetSegment() const
{
    return *m_pSegment;
}
//----------------------------------------------------------------------------
float DistLine2Segment2f::Get()
{
    float fSqrDist = GetSquared();

    return Math<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float DistLine2Segment2f::GetSquared()
{
    SEVector2f vec2fDiff = m_pLine->Origin - m_pSegment->Origin;
    float fA01 = -m_pLine->Direction.Dot(m_pSegment->Direction);
    float fB0 = vec2fDiff.Dot(m_pLine->Direction);
    float fC = vec2fDiff.GetSquaredLength();
    float fDet = Math<float>::FAbs(1.0f - fA01*fA01);
    float fB1, fS0, fS1, fSqrDist, fExtDet;

    if( fDet >= Math<float>::ZERO_TOLERANCE )
    {
        // 直线和线段不平行.
        fB1 = -vec2fDiff.Dot(m_pSegment->Direction);
        fS1 = fA01*fB0 - fB1;
        fExtDet = m_pSegment->Extent * fDet;

        if( fS1 >= -fExtDet )
        {
            if( fS1 <= fExtDet )
            {
                // 两个线上点是最近点,一个在直线上一个在线段上.
                float fInvDet = 1.0f / fDet;
                fS0 = (fA01*fB1 - fB0)*fInvDet;
                fS1 *= fInvDet;
                fSqrDist = 0.0f;
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

    return Math<float>::FAbs(fSqrDist);
}
//----------------------------------------------------------------------------
float DistLine2Segment2f::Get(float fT, const SEVector2f& rVelocity0,
    const SEVector2f& rVelocity1)
{
    SEVector2f vec2fMOrigin0 = m_pLine->Origin + fT*rVelocity0;
    SEVector2f vec2fMOrigin1 = m_pSegment->Origin + fT*rVelocity1;
    Line2f tempMLine(vec2fMOrigin0, m_pLine->Direction);
    Segment2f tempMSegment(vec2fMOrigin1, m_pSegment->Direction,
        m_pSegment->Extent);

    return DistLine2Segment2f(tempMLine, tempMSegment).Get();
}
//----------------------------------------------------------------------------
float DistLine2Segment2f::GetSquared(float fT,
    const SEVector2f& rVelocity0, const SEVector2f& rVelocity1)
{
    SEVector2f vec2fMOrigin0 = m_pLine->Origin + fT*rVelocity0;
    SEVector2f vec2fMOrigin1 = m_pSegment->Origin + fT*rVelocity1;
    Line2f tempMLine(vec2fMOrigin0, m_pLine->Direction);
    Segment2f tempMSegment(vec2fMOrigin1, m_pSegment->Direction,
        m_pSegment->Extent);

    return DistLine2Segment2f(tempMLine, tempMSegment).GetSquared();
}
//----------------------------------------------------------------------------
