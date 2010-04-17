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
#include "SEDistTriangle3Rectangle3.h"
#include "SEDistSegment3Triangle3.h"
#include "SEDistSegment3Rectangle3.h"

using namespace Swing;

//----------------------------------------------------------------------------
DistTriangle3Rectangle3f::DistTriangle3Rectangle3f(
    const SETriangle3f& rTriangle, const SERectangle3f& rRectangle)
    :
    m_pTriangle(&rTriangle),
    m_pRectangle(&rRectangle)
{
}
//----------------------------------------------------------------------------
const SETriangle3f& DistTriangle3Rectangle3f::GetTriangle() const
{
    return *m_pTriangle;
}
//----------------------------------------------------------------------------
const SERectangle3f& DistTriangle3Rectangle3f::GetRectangle() const
{
    return *m_pRectangle;
}
//----------------------------------------------------------------------------
float DistTriangle3Rectangle3f::Get()
{
    float fSqrDist = GetSquared();

    return SEMath<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float DistTriangle3Rectangle3f::GetSquared()
{
    // 把triangle各边和rectangle比较.
    float fSqrDist = SEMath<float>::MAX_REAL, fSqrDistTmp;
    SESegment3f tempEdge;
    int i0, i1;
    for( i0 = 2, i1 = 0; i1 < 3; i0 = i1++ )
    {
        tempEdge.Origin = 0.5f*(m_pTriangle->V[i0] + m_pTriangle->V[i1]);
        tempEdge.Direction = m_pTriangle->V[i1] - m_pTriangle->V[i0];
        tempEdge.Extent = 0.5f*tempEdge.Direction.Normalize();
        DistSegment3Rectangle3f tempSRDist(tempEdge, *m_pRectangle);
        fSqrDistTmp = tempSRDist.GetSquared();
        if( fSqrDistTmp < fSqrDist )
        {
            m_ClosestPoint0 = tempSRDist.GetClosestPoint0();
            m_ClosestPoint1 = tempSRDist.GetClosestPoint1();
            fSqrDist = fSqrDistTmp;
        }
    }

    // 把rectangle各边和triangle比较.
    for( i1 = 0; i1 < 2; i1++ )
    {
        for( i0 = -1; i0 <= 1; i0 += 2 )
        {
            tempEdge.Origin = m_pRectangle->Center +
                (i0*m_pRectangle->Extent[1 - i1]) *
                m_pRectangle->Axis[1 - i1];
            tempEdge.Direction = m_pRectangle->Axis[i1];
            tempEdge.Extent = m_pRectangle->Extent[i1];
            DistSegment3Triangle3f tempSTDist(tempEdge, *m_pTriangle);
            fSqrDistTmp = tempSTDist.GetSquared();
            if( fSqrDistTmp < fSqrDist )
            {
                m_ClosestPoint0 = tempSTDist.GetClosestPoint0();
                m_ClosestPoint1 = tempSTDist.GetClosestPoint1();
                fSqrDist = fSqrDistTmp;
            }
        }
    }

    return fSqrDist;
}
//----------------------------------------------------------------------------
float DistTriangle3Rectangle3f::Get(float fT, const SEVector3f& rVelocity0, 
    const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMV0 = m_pTriangle->V[0] + fT*rVelocity0;
    SEVector3f vec3fMV1 = m_pTriangle->V[1] + fT*rVelocity0;
    SEVector3f vec3fMV2 = m_pTriangle->V[2] + fT*rVelocity0;
    SEVector3f vec3fMCenter = m_pRectangle->Center + fT*rVelocity1;
    SETriangle3f tempMTriangle(vec3fMV0, vec3fMV1, vec3fMV2);
    SERectangle3f tempMRectangle(vec3fMCenter, m_pRectangle->Axis,
        m_pRectangle->Extent);

    return DistTriangle3Rectangle3f(tempMTriangle, tempMRectangle).Get();
}
//----------------------------------------------------------------------------
float DistTriangle3Rectangle3f::GetSquared(float fT, 
    const SEVector3f& rVelocity0, const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMV0 = m_pTriangle->V[0] + fT*rVelocity0;
    SEVector3f vec3fMV1 = m_pTriangle->V[1] + fT*rVelocity0;
    SEVector3f vec3fMV2 = m_pTriangle->V[2] + fT*rVelocity0;
    SEVector3f vec3fMCenter = m_pRectangle->Center + fT*rVelocity1;
    SETriangle3f tempMTriangle(vec3fMV0, vec3fMV1, vec3fMV2);
    SERectangle3f tempMRectangle(vec3fMCenter, m_pRectangle->Axis,
        m_pRectangle->Extent);

    return DistTriangle3Rectangle3f(tempMTriangle, 
        tempMRectangle).GetSquared();
}
//----------------------------------------------------------------------------
