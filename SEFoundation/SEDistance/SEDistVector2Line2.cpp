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
#include "SEDistVector2Line2.h"

using namespace Swing;

//----------------------------------------------------------------------------
DistVector2Line2f::DistVector2Line2f(const SEVector2f& rVector,
    const SELine2f& rLine)
    :
    m_pVector(&rVector),
    m_pLine(&rLine)
{
}
//----------------------------------------------------------------------------
const SEVector2f& DistVector2Line2f::GetVector() const
{
    return *m_pVector;
}
//----------------------------------------------------------------------------
const SELine2f& DistVector2Line2f::GetLine() const
{
    return *m_pLine;
}
//----------------------------------------------------------------------------
float DistVector2Line2f::Get()
{
    float fSqrDist = GetSquared();

    return SEMath<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float DistVector2Line2f::GetSquared()
{
    SEVector2f vec2fDiff = *m_pVector - m_pLine->Origin;
    float fParam = m_pLine->Direction.Dot(vec2fDiff);
    m_ClosestPoint0 = *m_pVector;
    m_ClosestPoint1 = m_pLine->Origin + fParam*m_pLine->Direction;
    vec2fDiff = m_ClosestPoint1 - m_ClosestPoint0;

    return vec2fDiff.GetSquaredLength();
}
//----------------------------------------------------------------------------
float DistVector2Line2f::Get(float fT, const SEVector2f& rVelocity0,
    const SEVector2f& rVelocity1)
{
    SEVector2f vec2fMVector = *m_pVector + fT*rVelocity0;
    SEVector2f vec2fMOrigin = m_pLine->Origin + fT*rVelocity1;
    SELine2f tempMLine(vec2fMOrigin, m_pLine->Direction);

    return DistVector2Line2f(vec2fMVector, tempMLine).Get();
}
//----------------------------------------------------------------------------
float DistVector2Line2f::GetSquared(float fT, const SEVector2f& rVelocity0, 
    const SEVector2f& rVelocity1)
{
    SEVector2f vec2fMVector = *m_pVector + fT*rVelocity0;
    SEVector2f vec2fMOrigin = m_pLine->Origin + fT*rVelocity1;
    SELine2f tempMLine(vec2fMOrigin, m_pLine->Direction);

    return DistVector2Line2f(vec2fMVector, tempMLine).GetSquared();
}
//----------------------------------------------------------------------------
