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
#include "SEDistSegment3Box3.h"
#include "SEDistVector3Box3.h"
#include "SEDistLine3Box3.h"

using namespace Swing;

//----------------------------------------------------------------------------
DistSegment3Box3f::DistSegment3Box3f(const SESegment3f& rSegment,
    const SEBox3f& rBox)
    :
    m_pSegment(&rSegment),
    m_pBox(&rBox)
{
}
//----------------------------------------------------------------------------
const SESegment3f& DistSegment3Box3f::GetSegment() const
{
    return *m_pSegment;
}
//----------------------------------------------------------------------------
const SEBox3f& DistSegment3Box3f::GetBox() const
{
    return *m_pBox;
}
//----------------------------------------------------------------------------
float DistSegment3Box3f::Get()
{
    float fSqrDist = GetSquared();

    return SEMath<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float DistSegment3Box3f::GetSquared()
{
    SELine3f tempLine(m_pSegment->Origin, m_pSegment->Direction);
    DistLine3Box3f tempLBDist(tempLine, *m_pBox);

    float fSqrDistance = tempLBDist.GetSquared();

    float fLParam = tempLBDist.GetLineParameter();
    if( fLParam >= -m_pSegment->Extent )
    {
        if( fLParam <= m_pSegment->Extent )
        {
            m_ClosestPoint0 = tempLBDist.GetClosestPoint0();
            m_ClosestPoint1 = tempLBDist.GetClosestPoint1();
        }
        else
        {
            DistVector3Box3f tempVBDist(m_pSegment->GetPosEnd(), *m_pBox);
            fSqrDistance = tempVBDist.GetSquared();
            m_ClosestPoint0 = tempVBDist.GetClosestPoint0();
            m_ClosestPoint1 = tempVBDist.GetClosestPoint1();
        }
    }
    else
    {
        DistVector3Box3f tempVBDist(m_pSegment->GetNegEnd(), *m_pBox);
        fSqrDistance = tempVBDist.GetSquared();
        m_ClosestPoint0 = tempVBDist.GetClosestPoint0();
        m_ClosestPoint1 = tempVBDist.GetClosestPoint1();
    }

    return fSqrDistance;
}
//----------------------------------------------------------------------------
float DistSegment3Box3f::Get(float fT, const SEVector3f& rVelocity0,
    const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMOrigin = m_pSegment->Origin + fT*rVelocity0;
    SEVector3f vec3fMCenter = m_pBox->Center + fT*rVelocity1;
    SESegment3f tempMSegment(vec3fMOrigin, m_pSegment->Direction,
        m_pSegment->Extent);
    SEBox3f tempMBox(vec3fMCenter, m_pBox->Axis, m_pBox->Extent);

    return DistSegment3Box3f(tempMSegment, tempMBox).Get();
}
//----------------------------------------------------------------------------
float DistSegment3Box3f::GetSquared(float fT, const SEVector3f& rVelocity0, 
    const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMOrigin = m_pSegment->Origin + fT*rVelocity0;
    SEVector3f vec3fMCenter = m_pBox->Center + fT*rVelocity1;
    SESegment3f tempMSegment(vec3fMOrigin, m_pSegment->Direction,
        m_pSegment->Extent);
    SEBox3f tempMBox(vec3fMCenter, m_pBox->Axis, m_pBox->Extent);

    return DistSegment3Box3f(tempMSegment, tempMBox).GetSquared();
}
//----------------------------------------------------------------------------
