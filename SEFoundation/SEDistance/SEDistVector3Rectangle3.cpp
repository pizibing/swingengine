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
#include "SEDistVector3Rectangle3.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEDistVector3Rectangle3f::SEDistVector3Rectangle3f(const SEVector3f& rVector, 
    const SERectangle3f& rRectangle)
    :
    m_pVector(&rVector),
    m_pRectangle(&rRectangle)
{
}
//----------------------------------------------------------------------------
const SEVector3f& SEDistVector3Rectangle3f::GetVector() const
{
    return *m_pVector;
}
//----------------------------------------------------------------------------
const SERectangle3f& SEDistVector3Rectangle3f::GetRectangle()
    const
{
    return *m_pRectangle;
}
//----------------------------------------------------------------------------
float SEDistVector3Rectangle3f::Get()
{
    float fSqrDist = GetSquared();

    return SEMath<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float SEDistVector3Rectangle3f::GetSquared()
{
    SEVector3f vec3fDiff = m_pRectangle->Center - *m_pVector;
    float fB0 = vec3fDiff.Dot(m_pRectangle->Axis[0]);
    float fB1 = vec3fDiff.Dot(m_pRectangle->Axis[1]);
    float fS0 = -fB0, fS1 = -fB1;
    float fSqrDistance = vec3fDiff.GetSquaredLength();

    if( fS0 < -m_pRectangle->Extent[0] )
    {
        fS0 = -m_pRectangle->Extent[0];
    }
    else if( fS0 > m_pRectangle->Extent[0] )
    {
        fS0 = m_pRectangle->Extent[0];
    }
    fSqrDistance += fS0*(fS0 + 2.0f*fB0);

    if( fS1 < -m_pRectangle->Extent[1] )
    {
        fS1 = -m_pRectangle->Extent[1];
    }
    else if( fS1 > m_pRectangle->Extent[1] )
    {
        fS1 = m_pRectangle->Extent[1];
    }
    fSqrDistance += fS1*(fS1 + 2.0f*fB1);

    // account for numerical round-off error
    if( fSqrDistance < 0.0f )
    {
        fSqrDistance = 0.0f;
    }

    m_ClosestPoint0 = *m_pVector;
    m_ClosestPoint1 = m_pRectangle->Center + fS0*m_pRectangle->Axis[0] +
        fS1*m_pRectangle->Axis[1];
    m_afRectCoord[0] = fS0;
    m_afRectCoord[1] = fS1;

    return fSqrDistance;
}
//----------------------------------------------------------------------------
float SEDistVector3Rectangle3f::Get(float fT, const SEVector3f& rVelocity0, 
    const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMVector = *m_pVector + fT*rVelocity0;
    SEVector3f vec3fMCenter = m_pRectangle->Center + fT*rVelocity1;
    SERectangle3f tempMRectangle(vec3fMCenter, m_pRectangle->Axis[0],
        m_pRectangle->Axis[1], m_pRectangle->Extent[0], 
        m_pRectangle->Extent[1]);

    return SEDistVector3Rectangle3f(vec3fMVector, tempMRectangle).Get();
}
//----------------------------------------------------------------------------
float SEDistVector3Rectangle3f::GetSquared(float fT, const SEVector3f& rVelocity0, 
    const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMVector = *m_pVector + fT*rVelocity0;
    SEVector3f vec3fMCenter = m_pRectangle->Center + fT*rVelocity1;
    SERectangle3f tempMRectangle(vec3fMCenter, m_pRectangle->Axis[0],
        m_pRectangle->Axis[1], m_pRectangle->Extent[0], 
        m_pRectangle->Extent[1]);

    return SEDistVector3Rectangle3f(vec3fMVector, tempMRectangle).GetSquared();
}
//----------------------------------------------------------------------------
float SEDistVector3Rectangle3f::GetRectangleCoordinate(int i) const
{
    SE_ASSERT( 0 <= i && i < 2 );

    return m_afRectCoord[i];
}
//----------------------------------------------------------------------------
