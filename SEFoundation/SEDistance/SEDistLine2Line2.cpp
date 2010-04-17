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
#include "SEDistLine2Line2.h"

using namespace Swing;

//----------------------------------------------------------------------------
DistLine2Line2f::DistLine2Line2f(const Line2f& rLine0, const Line2f& rLine1)
    :
    m_pLine0(&rLine0),
    m_pLine1(&rLine1)
{
}
//----------------------------------------------------------------------------
const Line2f& DistLine2Line2f::GetLine0() const
{
    return *m_pLine0;
}
//----------------------------------------------------------------------------
const Line2f& DistLine2Line2f::GetLine1() const
{
    return *m_pLine1;
}
//----------------------------------------------------------------------------
float DistLine2Line2f::Get()
{
    float fSqrDist = GetSquared();

    return Math<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float DistLine2Line2f::GetSquared()
{
    SEVector2f vec2fDiff = m_pLine0->Origin - m_pLine1->Origin;
    float fA01 = -m_pLine0->Direction.Dot(m_pLine1->Direction);
    float fB0 = vec2fDiff.Dot(m_pLine0->Direction);
    float fC = vec2fDiff.GetSquaredLength();
    float fDet = Math<float>::FAbs(1.0f - fA01*fA01);
    float fB1, fS0, fS1, fSqrDist;

    if( fDet >= Math<float>::ZERO_TOLERANCE )
    {
        // 直线不平行.
        fB1 = -vec2fDiff.Dot(m_pLine1->Direction);
        float fInvDet = 1.0f / fDet;
        fS0 = (fA01*fB1 - fB0)*fInvDet;
        fS1 = (fA01*fB0 - fB1)*fInvDet;
        fSqrDist = 0.0f;
    }
    else
    {
        // 直线平行,选择任意一对最近顶点.
        fS0 = -fB0;
        fS1 = 0.0f;
        fSqrDist = fB0*fS0 + fC;
    }

    m_ClosestPoint0 = m_pLine0->Origin + fS0*m_pLine0->Direction;
    m_ClosestPoint1 = m_pLine1->Origin + fS1*m_pLine1->Direction;

    return Math<float>::FAbs(fSqrDist);
}
//----------------------------------------------------------------------------
float DistLine2Line2f::Get(float fT, const SEVector2f& rVelocity0,
    const SEVector2f& rVelocity1)
{
    SEVector2f vec2fMOrigin0 = m_pLine0->Origin + fT*rVelocity0;
    SEVector2f vec2fMOrigin1 = m_pLine1->Origin + fT*rVelocity1;
    Line2f tempMLine0(vec2fMOrigin0, m_pLine0->Direction);
    Line2f tempMLine1(vec2fMOrigin1, m_pLine1->Direction);

    return DistLine2Line2f(tempMLine0, tempMLine1).Get();
}
//----------------------------------------------------------------------------
float DistLine2Line2f::GetSquared(float fT,
    const SEVector2f& rVelocity0, const SEVector2f& rVelocity1)
{
    SEVector2f vec2fMOrigin0 = m_pLine0->Origin + fT*rVelocity0;
    SEVector2f vec2fMOrigin1 = m_pLine1->Origin + fT*rVelocity1;
    Line2f tempMLine0(vec2fMOrigin0, m_pLine0->Direction);
    Line2f tempMLine1(vec2fMOrigin1, m_pLine1->Direction);

    return DistLine2Line2f(tempMLine0, tempMLine1).GetSquared();
}
//----------------------------------------------------------------------------
