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
#include "SEDistLine3Triangle3.h"
#include "SEDistLine3Segment3.h"

using namespace Swing;

//----------------------------------------------------------------------------
DistLine3Triangle3f::DistLine3Triangle3f(const SELine3f& rLine,
    const SETriangle3f& rTriangle)
    :
    m_pLine(&rLine),
    m_pTriangle(&rTriangle)
{
}
//----------------------------------------------------------------------------
const SELine3f& DistLine3Triangle3f::GetLine() const
{
    return *m_pLine;
}
//----------------------------------------------------------------------------
const SETriangle3f& DistLine3Triangle3f::GetTriangle() const
{
    return *m_pTriangle;
}
//----------------------------------------------------------------------------
float DistLine3Triangle3f::Get()
{
    float fSqrDist = GetSquared();

    return SEMath<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float DistLine3Triangle3f::GetSquared()
{
    // 测试直线是否和三角形相交,如果相交则距离为零.
    SEVector3f vec3fEdge0 = m_pTriangle->V[1] - m_pTriangle->V[0];
    SEVector3f vec3fEdge1 = m_pTriangle->V[2] - m_pTriangle->V[0];
    SEVector3f vec3fNormal = vec3fEdge0.UnitCross(vec3fEdge1);
    float fNdD = vec3fNormal.Dot(m_pLine->Direction);
    if( SEMath<float>::FAbs(fNdD) > SEMath<float>::ZERO_TOLERANCE )
    {
        // 直线和三角形不平行,因此直线和三角形所在平面相交.
        SEVector3f vec3fDiff = m_pLine->Origin - m_pTriangle->V[0];
        SEVector3f& rD = (SEVector3f&) m_pLine->Direction;
        SEVector3f vec3fU, vec3fV;
        SEVector3f::GetOrthonormalBasis(vec3fU, vec3fV, rD, true);
        float fUdE0 = vec3fU.Dot(vec3fEdge0);
        float fUdE1 = vec3fU.Dot(vec3fEdge0);
        float fUdDiff = vec3fU.Dot(vec3fDiff);
        float fVdE0 = vec3fV.Dot(vec3fEdge0);
        float fVdE1 = vec3fV.Dot(vec3fEdge0);
        float fVdDiff = vec3fV.Dot(vec3fDiff);
        float fInvDet = 1.0f / (fUdE0*fVdE1 - fUdE1*fVdE0);

        // 相交点的Barycentric coordinates.
        float fB1 = (fVdE1*fUdDiff - fUdE1*fVdDiff)*fInvDet;
        float fB2 = (fUdE0*fVdDiff - fVdE0*fUdDiff)*fInvDet;
        float fB0 = 1.0f - fB1 - fB2;

        if( fB0 >= 0.0f && fB1 >= 0.0f && fB2 >= 0.0f )
        {
            // 相交点的直线参数.
            float fDdE0 = rD.Dot(vec3fEdge0);
            float fDdE1 = rD.Dot(vec3fEdge1);
            float fDdDiff = m_pLine->Direction.Dot(vec3fDiff);
            m_fLineParameter = fB1*fDdE0 + fB2*fDdE1 - fDdDiff;

            // 相交点的Barycentric coordinates.
            m_afTriangleBary[0] = fB0;
            m_afTriangleBary[1] = fB1;
            m_afTriangleBary[2] = fB2;

            // 相交点在三角形内或三角形边上.
            m_ClosestPoint0 = m_pLine->Origin +
                m_fLineParameter*m_pLine->Direction;

            m_ClosestPoint1 = m_pTriangle->V[0] + fB1*vec3fEdge0 + 
                fB2*vec3fEdge1;

            return 0.0f;
        }
    }

    // 要么(1)直线和三角形不平行,直线和三角形所在平面的相交点在三角形之外.
    // 或者(2)直线和三角形平行.
    // 不管是哪种情况,三角形上的最近点应该在三角形的某条边上.
    // 因此把直线和三角形三条边依次比较.
    float fSqrDist = SEMath<float>::MAX_REAL;
    for( int i0 = 2, i1 = 0; i1 < 3; i0 = i1++ )
    {
        SESegment3f tempSeg;
        tempSeg.Origin = 0.5f*(m_pTriangle->V[i0] + m_pTriangle->V[i1]);
        tempSeg.Direction = m_pTriangle->V[i1] - m_pTriangle->V[i0];
        tempSeg.Extent = 0.5f*tempSeg.Direction.Normalize();
        DistLine3Segment3f tempLSDist(*m_pLine, tempSeg);
        float fSqrDistTmp = tempLSDist.GetSquared();
        if( fSqrDistTmp < fSqrDist )
        {
            m_ClosestPoint0 = tempLSDist.GetClosestPoint0();
            m_ClosestPoint1 = tempLSDist.GetClosestPoint1();
            fSqrDist = fSqrDistTmp;

            m_fLineParameter = tempLSDist.GetLineParameter();
            float fRatio = tempLSDist.GetSegmentParameter()/tempSeg.Extent;
            m_afTriangleBary[i0] = 0.5f*(1.0f - fRatio);
            m_afTriangleBary[i1] = 1.0f - m_afTriangleBary[i0];
            m_afTriangleBary[3 - i0 - i1] = 0.0f;
        }
    }

    return fSqrDist;
}
//----------------------------------------------------------------------------
float DistLine3Triangle3f::Get(float fT, const SEVector3f& rVelocity0,
    const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMOrigin = m_pLine->Origin + fT*rVelocity0;
    SEVector3f vec3fMV0 = m_pTriangle->V[0] + fT*rVelocity1;
    SEVector3f vec3fMV1 = m_pTriangle->V[1] + fT*rVelocity1;
    SEVector3f vec3fMV2 = m_pTriangle->V[2] + fT*rVelocity1;
    SELine3f tempMLine(vec3fMOrigin, m_pLine->Direction);
    SETriangle3f tempMTriangle(vec3fMV0, vec3fMV1, vec3fMV2);

    return DistLine3Triangle3f(tempMLine, tempMTriangle).Get();
}
//----------------------------------------------------------------------------
float DistLine3Triangle3f::GetSquared(float fT, const SEVector3f& rVelocity0, 
    const SEVector3f& rVelocity1)
{
    SEVector3f vec3fMOrigin = m_pLine->Origin + fT*rVelocity0;
    SEVector3f vec3fMV0 = m_pTriangle->V[0] + fT*rVelocity1;
    SEVector3f vec3fMV1 = m_pTriangle->V[1] + fT*rVelocity1;
    SEVector3f vec3fMV2 = m_pTriangle->V[2] + fT*rVelocity1;
    SELine3f tempMLine(vec3fMOrigin, m_pLine->Direction);
    SETriangle3f tempMTriangle(vec3fMV0, vec3fMV1, vec3fMV2);

    return DistLine3Triangle3f(tempMLine, tempMTriangle).GetSquared();
}
//----------------------------------------------------------------------------
float DistLine3Triangle3f::GetLineParameter() const
{
    return m_fLineParameter;
}
//----------------------------------------------------------------------------
float DistLine3Triangle3f::GetTriangleBary(int i) const
{
    SE_ASSERT( 0 <= i && i < 3 );

    return m_afTriangleBary[i];
}
//----------------------------------------------------------------------------
