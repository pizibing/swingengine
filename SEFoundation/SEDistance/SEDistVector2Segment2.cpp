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
#include "SEDistVector2Segment2.h"

using namespace Swing;

//----------------------------------------------------------------------------
DistVector2Segment2f::DistVector2Segment2f(const SEVector2f& rVector,
    const SESegment2f& rSegment)
    :
    m_pVector(&rVector),
    m_pSegment(&rSegment)
{
}
//----------------------------------------------------------------------------
const SEVector2f& DistVector2Segment2f::GetVector() const
{
    return *m_pVector;
}
//----------------------------------------------------------------------------
const SESegment2f& DistVector2Segment2f::GetSegment() const
{
    return *m_pSegment;
}
//----------------------------------------------------------------------------
float DistVector2Segment2f::Get()
{
    float fSqrDist = GetSquared();

    return SEMath<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float DistVector2Segment2f::GetSquared()
{
    SEVector2f vec2fDiff = *m_pVector - m_pSegment->Origin;
    float fParam = m_pSegment->Direction.Dot(vec2fDiff);

    if( -m_pSegment->Extent < fParam )
    {
        if( fParam < m_pSegment->Extent )
        {
            m_ClosestPoint1 = m_pSegment->Origin +
                fParam*m_pSegment->Direction;
        }
        else
        {
            m_ClosestPoint1 = m_pSegment->Origin +
                m_pSegment->Extent*m_pSegment->Direction;
        }
    }
    else
    {
        m_ClosestPoint1 = m_pSegment->Origin -
            m_pSegment->Extent*m_pSegment->Direction;
    }

    m_ClosestPoint0 = *m_pVector;
    vec2fDiff = m_ClosestPoint1 - m_ClosestPoint0;

    return vec2fDiff.GetSquaredLength();
}
//----------------------------------------------------------------------------
float DistVector2Segment2f::Get(float fT, const SEVector2f& rVelocity0, 
    const SEVector2f& rVelocity1)
{
    SEVector2f vec2fMVector = *m_pVector + fT*rVelocity0;
    SEVector2f vec2fMOrigin = m_pSegment->Origin + fT*rVelocity1;
    SESegment2f tempMSegment(vec2fMOrigin, m_pSegment->Direction,
        m_pSegment->Extent);

    return DistVector2Segment2f(vec2fMVector, tempMSegment).Get();
}
//----------------------------------------------------------------------------
float DistVector2Segment2f::GetSquared(float fT, const SEVector2f& rVelocity0, 
    const SEVector2f& rVelocity1)
{
    SEVector2f vec2fMVector = *m_pVector + fT*rVelocity0;
    SEVector2f vec2fMOrigin = m_pSegment->Origin + fT*rVelocity1;
    SESegment2f tempMSegment(vec2fMOrigin, m_pSegment->Direction,
        m_pSegment->Extent);

    return DistVector2Segment2f(vec2fMVector, tempMSegment).GetSquared();
}
//----------------------------------------------------------------------------
