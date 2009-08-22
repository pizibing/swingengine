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
#include "SEDistLine2Ray2.h"

using namespace Swing;

//----------------------------------------------------------------------------
DistLine2Ray2f::DistLine2Ray2f(const Line2f& rLine, const Ray2f& rRay)
    :
    m_pLine(&rLine), 
    m_pRay(&rRay)
{
}
//----------------------------------------------------------------------------
const Line2f& DistLine2Ray2f::GetLine() const
{
    return *m_pLine;
}
//----------------------------------------------------------------------------
const Ray2f& DistLine2Ray2f::GetRay() const
{
    return *m_pRay;
}
//----------------------------------------------------------------------------
float DistLine2Ray2f::Get()
{
    float fSqrDist = GetSquared();

    return Math<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float DistLine2Ray2f::GetSquared()
{
    Vector2f vec2fDiff = m_pLine->Origin - m_pRay->Origin;
    float fA01 = -m_pLine->Direction.Dot(m_pRay->Direction);
    float fB0 = vec2fDiff.Dot(m_pLine->Direction);
    float fC = vec2fDiff.GetSquaredLength();
    float fDet = Math<float>::FAbs(1.0f - fA01*fA01);
    float fB1, fS0, fS1, fSqrDist;

    if( fDet >= Math<float>::ZERO_TOLERANCE )
    {
        fB1 = -vec2fDiff.Dot(m_pRay->Direction);
        fS1 = fA01*fB0 - fB1;

        if( fS1 >= 0.0f )
        {
            // 两个线上点是最近点,一个在直线上一个在射线上.
            float fInvDet = 1.0f / fDet;
            fS0 = (fA01*fB1 - fB0)*fInvDet;
            fS1 *= fInvDet;
            fSqrDist = 0.0f;
        }
        else
        {
            // 射线原点和直线线上点是最近点.
            fS0 = -fB0;
            fS1 = 0.0f;
            fSqrDist = fB0*fS0 + fC;
        }
    }
    else
    {
        // 直线和射线平行,选择射线原点所在的最近点对.
        fS0 = -fB0;
        fS1 = 0.0f;
        fSqrDist = fB0*fS0 + fC;
    }

    m_ClosestPoint0 = m_pLine->Origin + fS0*m_pLine->Direction;
    m_ClosestPoint1 = m_pRay->Origin + fS1*m_pRay->Direction;

    return Math<float>::FAbs(fSqrDist);
}
//----------------------------------------------------------------------------
float DistLine2Ray2f::Get(float fT, const Vector2f& rVelocity0, 
    const Vector2f& rVelocity1)
{
    Vector2f vec2fMOrigin0 = m_pLine->Origin + fT*rVelocity0;
    Vector2f vec2fMOrigin1 = m_pRay->Origin + fT*rVelocity1;
    Line2f tempMLine(vec2fMOrigin0, m_pLine->Direction);
    Ray2f tempMRay(vec2fMOrigin1, m_pRay->Direction);

    return DistLine2Ray2f(tempMLine, tempMRay).Get();
}
//----------------------------------------------------------------------------
float DistLine2Ray2f::GetSquared(float fT, 
    const Vector2f& rVelocity0, const Vector2f& rVelocity1)
{
    Vector2f vec2fMOrigin0 = m_pLine->Origin + fT*rVelocity0;
    Vector2f vec2fMOrigin1 = m_pRay->Origin + fT*rVelocity1;
    Line2f tempMLine(vec2fMOrigin0, m_pLine->Direction);
    Ray2f tempMRay(vec2fMOrigin1, m_pRay->Direction);

    return DistLine2Ray2f(tempMLine, tempMRay).GetSquared();
}
//----------------------------------------------------------------------------
