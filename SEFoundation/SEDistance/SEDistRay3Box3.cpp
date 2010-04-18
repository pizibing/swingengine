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
#include "SEDistRay3Box3.h"
#include "SEDistVector3Box3.h"
#include "SEDistLine3Box3.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEDistRay3Box3f::SEDistRay3Box3f(const SERay3f& rRay, const SEBox3f& rBox)
    :
    m_pRay(&rRay),
    m_pBox(&rBox)
{
}
//----------------------------------------------------------------------------
const SERay3f& SEDistRay3Box3f::GetRay() const
{
    return *m_pRay;
}
//----------------------------------------------------------------------------
const SEBox3f& SEDistRay3Box3f::GetBox() const
{
    return *m_pBox;
}
//----------------------------------------------------------------------------
float SEDistRay3Box3f::Get()
{
    float fSqrDist = GetSquared();

    return SEMath<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float SEDistRay3Box3f::GetSquared()
{
    SELine3f tempLine(m_pRay->Origin, m_pRay->Direction);
    SEDistLine3Box3f tempLBDist(tempLine, *m_pBox);

    float fSqrDistance = tempLBDist.GetSquared();

    if( tempLBDist.GetLineParameter() >= 0.0f )
    {
        m_ClosestPoint0 = tempLBDist.GetClosestPoint0();
        m_ClosestPoint1 = tempLBDist.GetClosestPoint1();
    }
    else
    {
        SEDistVector3Box3f tempVBDist(m_pRay->Origin, *m_pBox);
        fSqrDistance = tempVBDist.GetSquared();
        m_ClosestPoint0 = tempVBDist.GetClosestPoint0();
        m_ClosestPoint1 = tempVBDist.GetClosestPoint1();
    }

    return fSqrDistance;
}
//----------------------------------------------------------------------------
float SEDistRay3Box3f::Get(float fT, const SEVector3f& rVelocity0,
    const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMOrigin = m_pRay->Origin + fT*rVelocity0;
    SEVector3f vec3fMCenter = m_pBox->Center + fT*rVelocity1;
    SERay3f tempMRay(vec3fMOrigin, m_pRay->Direction);
    SEBox3f tempMBox(vec3fMCenter, m_pBox->Axis,m_pBox->Extent);

    return SEDistRay3Box3f(tempMRay, tempMBox).Get();
}
//----------------------------------------------------------------------------
float SEDistRay3Box3f::GetSquared(float fT, const SEVector3f& rVelocity0, 
    const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMOrigin = m_pRay->Origin + fT*rVelocity0;
    SEVector3f vec3fMCenter = m_pBox->Center + fT*rVelocity1;
    SERay3f tempMRay(vec3fMOrigin, m_pRay->Direction);
    SEBox3f tempMBox(vec3fMCenter, m_pBox->Axis,m_pBox->Extent);

    return SEDistRay3Box3f(tempMRay, tempMBox).GetSquared();
}
//----------------------------------------------------------------------------
