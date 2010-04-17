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
#include "SEDistRectangle3Rectangle3.h"
#include "SEDistSegment3Rectangle3.h"

using namespace Swing;

//----------------------------------------------------------------------------
DistRectangle3Rectangle3f::DistRectangle3Rectangle3f(
    const SERectangle3f& rRectangle0, const SERectangle3f& rRectangle1)
    :
    m_pRectangle0(&rRectangle0),
    m_pRectangle1(&rRectangle1)
{
}
//----------------------------------------------------------------------------
const SERectangle3f& DistRectangle3Rectangle3f::GetRectangle0() const
{
    return *m_pRectangle0;
}
//----------------------------------------------------------------------------
const SERectangle3f& DistRectangle3Rectangle3f::GetRectangle1() const
{
    return *m_pRectangle1;
}
//----------------------------------------------------------------------------
float DistRectangle3Rectangle3f::Get()
{
    float fSqrDist = GetSquared();

    return SEMath<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float DistRectangle3Rectangle3f::GetSquared()
{
    // 把rectangle0各边和rectangle1比较.
    float fSqrDist = SEMath<float>::MAX_REAL, fSqrDistTmp;
    SESegment3f tempEdge;
    int i0, i1;
    for( i1 = 0; i1 < 2; i1++ )
    {
        for( i0 = -1; i0 <= 1; i0 += 2 )
        {
            tempEdge.Origin = m_pRectangle0->Center +
                (i0*m_pRectangle0->Extent[1 - i1]) *
                m_pRectangle0->Axis[1 - i1];
            tempEdge.Direction = m_pRectangle0->Axis[i1];
            tempEdge.Extent = m_pRectangle0->Extent[i1];
            DistSegment3Rectangle3f tempSRDist(tempEdge, *m_pRectangle1);
            fSqrDistTmp = tempSRDist.GetSquared();
            if( fSqrDistTmp < fSqrDist )
            {
                m_ClosestPoint0 = tempSRDist.GetClosestPoint0();
                m_ClosestPoint1 = tempSRDist.GetClosestPoint1();
                fSqrDist = fSqrDistTmp;
            }
        }
    }

    // 把rectangle1各边和rectangle0比较.
    for( i1 = 0; i1 < 2; i1++ )
    {
        for( i0 = -1; i0 <= 1; i0 += 2 )
        {
            tempEdge.Origin = m_pRectangle1->Center +
                (i0*m_pRectangle1->Extent[1 - i1]) *
                m_pRectangle1->Axis[1 - i1];
            tempEdge.Direction = m_pRectangle1->Axis[i1];
            tempEdge.Extent = m_pRectangle1->Extent[i1];
            DistSegment3Rectangle3f tempSRDist(tempEdge, *m_pRectangle0);
            fSqrDistTmp = tempSRDist.GetSquared();
            if( fSqrDistTmp < fSqrDist )
            {
                m_ClosestPoint0 = tempSRDist.GetClosestPoint0();
                m_ClosestPoint1 = tempSRDist.GetClosestPoint1();
                fSqrDist = fSqrDistTmp;
            }
        }
    }

    return fSqrDist;
}
//----------------------------------------------------------------------------
float DistRectangle3Rectangle3f::Get(float fT, const SEVector3f& rVelocity0, 
    const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMCenter0 = m_pRectangle0->Center + fT*rVelocity0;
    SEVector3f vec3fMCenter1 = m_pRectangle1->Center + fT*rVelocity1;
    SERectangle3f tempMRectangle0(vec3fMCenter0, m_pRectangle0->Axis,
        m_pRectangle0->Extent);
    SERectangle3f tempMRectangle1(vec3fMCenter1, m_pRectangle1->Axis,
        m_pRectangle1->Extent);

    return DistRectangle3Rectangle3f(tempMRectangle0, tempMRectangle1).Get();
}
//----------------------------------------------------------------------------
float DistRectangle3Rectangle3f::GetSquared(float fT,
    const SEVector3f& rVelocity0, const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMCenter0 = m_pRectangle0->Center + fT*rVelocity0;
    SEVector3f vec3fMCenter1 = m_pRectangle1->Center + fT*rVelocity1;
    SERectangle3f tempMRectangle0(vec3fMCenter0, m_pRectangle0->Axis,
        m_pRectangle0->Extent);
    SERectangle3f tempMRectangle1(vec3fMCenter1, m_pRectangle1->Axis,
        m_pRectangle1->Extent);

    return DistRectangle3Rectangle3f(tempMRectangle0,
        tempMRectangle1).GetSquared();
}
//----------------------------------------------------------------------------
