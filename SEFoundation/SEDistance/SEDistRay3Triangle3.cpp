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
#include "SEDistRay3Triangle3.h"
#include "SEDistLine3Triangle3.h"
#include "SEDistVector3Triangle3.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEDistRay3Triangle3f::SEDistRay3Triangle3f(const SERay3f& rRay,
    const SETriangle3f& rTriangle)
    :
    m_pRay(&rRay),
    m_pTriangle(&rTriangle)
{
}
//----------------------------------------------------------------------------
const SERay3f& SEDistRay3Triangle3f::GetRay() const
{
    return *m_pRay;
}
//----------------------------------------------------------------------------
const SETriangle3f& SEDistRay3Triangle3f::GetTriangle() const
{
    return *m_pTriangle;
}
//----------------------------------------------------------------------------
float SEDistRay3Triangle3f::Get()
{
    float fSqrDist = GetSquared();

    return SEMath<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float SEDistRay3Triangle3f::GetSquared()
{
    SEDistLine3Triangle3f tempLTDist(SELine3f(m_pRay->Origin, 
        m_pRay->Direction), *m_pTriangle);

    float fSqrDist = tempLTDist.GetSquared();

    m_fRayParameter = tempLTDist.GetLineParameter();
    if( m_fRayParameter >= 0.0f )
    {
        m_ClosestPoint0 = tempLTDist.GetClosestPoint0();
        m_ClosestPoint1 = tempLTDist.GetClosestPoint1();
        m_afTriangleBary[0] = tempLTDist.GetTriangleBary(0);
        m_afTriangleBary[1] = tempLTDist.GetTriangleBary(1);
        m_afTriangleBary[2] = tempLTDist.GetTriangleBary(2);
    }
    else
    {
        m_ClosestPoint0 = m_pRay->Origin;
        SEDistVector3Triangle3f tempVTDist(m_ClosestPoint0, *m_pTriangle);
        fSqrDist = tempVTDist.GetSquared();
        m_ClosestPoint1 = tempVTDist.GetClosestPoint1();
        m_fRayParameter = 0.0f;
        m_afTriangleBary[0] = tempVTDist.GetTriangleBary(0);
        m_afTriangleBary[1] = tempVTDist.GetTriangleBary(1);
        m_afTriangleBary[2] = tempVTDist.GetTriangleBary(2);
    }

    return fSqrDist;
}
//----------------------------------------------------------------------------
float SEDistRay3Triangle3f::Get(float fT, const SEVector3f& rVelocity0,
    const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMOrigin = m_pRay->Origin + fT*rVelocity0;
    SEVector3f vec3fMV0 = m_pTriangle->V[0] + fT*rVelocity1;
    SEVector3f vec3fMV1 = m_pTriangle->V[1] + fT*rVelocity1;
    SEVector3f vec3fMV2 = m_pTriangle->V[2] + fT*rVelocity1;
    SERay3f tempMRay(vec3fMOrigin, m_pRay->Direction);
    SETriangle3f tempMTriangle(vec3fMV0, vec3fMV1, vec3fMV2);

    return SEDistRay3Triangle3f(tempMRay, tempMTriangle).Get();
}
//----------------------------------------------------------------------------
float SEDistRay3Triangle3f::GetSquared(float fT, const SEVector3f& rVelocity0, 
    const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMOrigin = m_pRay->Origin + fT*rVelocity0;
    SEVector3f vec3fMV0 = m_pTriangle->V[0] + fT*rVelocity1;
    SEVector3f vec3fMV1 = m_pTriangle->V[1] + fT*rVelocity1;
    SEVector3f vec3fMV2 = m_pTriangle->V[2] + fT*rVelocity1;
    SERay3f tempMRay(vec3fMOrigin, m_pRay->Direction);
    SETriangle3f tempMTriangle(vec3fMV0, vec3fMV1, vec3fMV2);

    return SEDistRay3Triangle3f(tempMRay, tempMTriangle).GetSquared();
}
//----------------------------------------------------------------------------
float SEDistRay3Triangle3f::GetRayParameter() const
{
    return m_fRayParameter;
}
//----------------------------------------------------------------------------
float SEDistRay3Triangle3f::GetTriangleBary(int i) const
{
    SE_ASSERT( 0 <= i && i < 3 );

    return m_afTriangleBary[i];
}
//----------------------------------------------------------------------------
