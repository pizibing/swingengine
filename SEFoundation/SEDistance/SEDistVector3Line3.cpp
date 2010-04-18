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
#include "SEDistVector3Line3.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEDistVector3Line3f::SEDistVector3Line3f(const SEVector3f& rVector,
    const SELine3f& rLine)
    :
    m_pVector(&rVector),
    m_pLine(&rLine)
{
}
//----------------------------------------------------------------------------
const SEVector3f& SEDistVector3Line3f::GetVector() const
{
    return *m_pVector;
}
//----------------------------------------------------------------------------
const SELine3f& SEDistVector3Line3f::GetLine() const
{
    return *m_pLine;
}
//----------------------------------------------------------------------------
float SEDistVector3Line3f::Get()
{
    float fSqrDist = GetSquared();

    return SEMath<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float SEDistVector3Line3f::GetSquared()
{
    SEVector3f vec3fDiff = *m_pVector - m_pLine->Origin;
    m_fLineParameter = m_pLine->Direction.Dot(vec3fDiff);
    m_ClosestPoint0 = *m_pVector;
    m_ClosestPoint1 = m_pLine->Origin + m_fLineParameter*m_pLine->Direction;
    vec3fDiff = m_ClosestPoint1 - m_ClosestPoint0;

    return vec3fDiff.GetSquaredLength();
}
//----------------------------------------------------------------------------
float SEDistVector3Line3f::Get(float fT, const SEVector3f& rVelocity0,
    const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMVector = *m_pVector + fT*rVelocity0;
    SEVector3f vec3fMOrigin = m_pLine->Origin + fT*rVelocity1;
    SELine3f tempMLine(vec3fMOrigin, m_pLine->Direction);

    return SEDistVector3Line3f(vec3fMVector, tempMLine).Get();
}
//----------------------------------------------------------------------------
float SEDistVector3Line3f::GetSquared(float fT, const SEVector3f& rVelocity0, 
    const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMVector = *m_pVector + fT*rVelocity0;
    SEVector3f vec3fMOrigin = m_pLine->Origin + fT*rVelocity1;
    SELine3f tempMLine(vec3fMOrigin, m_pLine->Direction);

    return SEDistVector3Line3f(vec3fMVector, tempMLine).GetSquared();
}
//----------------------------------------------------------------------------
float SEDistVector3Line3f::GetLineParameter() const
{
    return m_fLineParameter;
}
//----------------------------------------------------------------------------
