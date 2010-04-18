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
#include "SEDistSegment3Rectangle3.h"
#include "SEDistLine3Rectangle3.h"
#include "SEDistVector3Rectangle3.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEDistSegment3Rectangle3f::SEDistSegment3Rectangle3f(const SESegment3f& 
    rSegment, const SERectangle3f& rRectangle)
    :
    m_pSegment(&rSegment),
    m_pRectangle(&rRectangle)
{
}
//----------------------------------------------------------------------------
const SESegment3f& SEDistSegment3Rectangle3f::GetSegment() const
{
    return *m_pSegment;
}
//----------------------------------------------------------------------------
const SERectangle3f& SEDistSegment3Rectangle3f::GetRectangle() const
{
    return *m_pRectangle;
}
//----------------------------------------------------------------------------
float SEDistSegment3Rectangle3f::Get()
{
    float fSqrDist = GetSquared();

    return SEMath<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float SEDistSegment3Rectangle3f::GetSquared()
{
    SEDistLine3Rectangle3f tempLRDist(SELine3f(m_pSegment->Origin, 
        m_pSegment->Direction), *m_pRectangle);

    float fSqrDist = tempLRDist.GetSquared();

    m_fSegmentParameter = tempLRDist.GetLineParameter();
    if( m_fSegmentParameter >= -m_pSegment->Extent)
    {
        if( m_fSegmentParameter <= m_pSegment->Extent)
        {
            m_ClosestPoint0 = tempLRDist.GetClosestPoint0();
            m_ClosestPoint1 = tempLRDist.GetClosestPoint1();
            m_afRectCoord[0] = tempLRDist.GetRectangleCoordinate(0);
            m_afRectCoord[1] = tempLRDist.GetRectangleCoordinate(1);
        }
        else
        {
            m_ClosestPoint0 = m_pSegment->GetPosEnd();
            SEDistVector3Rectangle3f tempVRDist(m_ClosestPoint0,
                *m_pRectangle);
            fSqrDist = tempVRDist.GetSquared();
            m_ClosestPoint1 = tempVRDist.GetClosestPoint1();
            m_fSegmentParameter = m_pSegment->Extent;
            m_afRectCoord[0] = tempVRDist.GetRectangleCoordinate(0);
            m_afRectCoord[1] = tempVRDist.GetRectangleCoordinate(1);
        }
    }
    else
    {
        m_ClosestPoint0 = m_pSegment->GetNegEnd();
        SEDistVector3Rectangle3f tempVRDist(m_ClosestPoint0, *m_pRectangle);
        fSqrDist = tempVRDist.GetSquared();
        m_ClosestPoint1 = tempVRDist.GetClosestPoint1();
        m_fSegmentParameter = -m_pSegment->Extent;
        m_afRectCoord[0] = tempVRDist.GetRectangleCoordinate(0);
        m_afRectCoord[1] = tempVRDist.GetRectangleCoordinate(1);
    }

    return fSqrDist;
}
//----------------------------------------------------------------------------
float SEDistSegment3Rectangle3f::Get(float fT, const SEVector3f& rVelocity0, 
    const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMOrigin = m_pSegment->Origin + fT*rVelocity0;
    SEVector3f vec3fMCenter = m_pRectangle->Center + fT*rVelocity1;
    SESegment3f tempMSegment(vec3fMOrigin, m_pSegment->Direction,
        m_pSegment->Extent);
    SERectangle3f tempMRectangle(vec3fMCenter, m_pRectangle->Axis,
        m_pRectangle->Extent);

    return SEDistSegment3Rectangle3f(tempMSegment, tempMRectangle).Get();
}
//----------------------------------------------------------------------------
float SEDistSegment3Rectangle3f::GetSquared(float fT, 
    const SEVector3f& rVelocity0, const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMOrigin = m_pSegment->Origin + fT*rVelocity0;
    SEVector3f vec3fMCenter = m_pRectangle->Center + fT*rVelocity1;
    SESegment3f tempMSegment(vec3fMOrigin, m_pSegment->Direction,
        m_pSegment->Extent);
    SERectangle3f tempMRectangle(vec3fMCenter, m_pRectangle->Axis,
        m_pRectangle->Extent);

    return SEDistSegment3Rectangle3f(tempMSegment, 
        tempMRectangle).GetSquared();
}
//----------------------------------------------------------------------------
float SEDistSegment3Rectangle3f::GetSegmentParameter() const
{
    return m_fSegmentParameter;
}
//----------------------------------------------------------------------------
float SEDistSegment3Rectangle3f::GetRectangleCoordinate(int i) const
{
    SE_ASSERT( 0 <= i && i < 2 );

    return m_afRectCoord[i];
}
//----------------------------------------------------------------------------
