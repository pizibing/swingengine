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
#include "SEDistLine3Rectangle3.h"
#include "SEDistLine3Segment3.h"

using namespace Swing;

//----------------------------------------------------------------------------
DistLine3Rectangle3f::DistLine3Rectangle3f(const Line3f& rLine,
    const Rectangle3f& rRectangle)
    :
    m_pLine(&rLine),
    m_pRectangle(&rRectangle)
{
}
//----------------------------------------------------------------------------
const Line3f& DistLine3Rectangle3f::GetLine() const
{
    return *m_pLine;
}
//----------------------------------------------------------------------------
const Rectangle3f& DistLine3Rectangle3f::GetRectangle() const
{
    return *m_pRectangle;
}
//----------------------------------------------------------------------------
float DistLine3Rectangle3f::Get()
{
    float fSqrDist = GetSquared();

    return Math<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float DistLine3Rectangle3f::GetSquared()
{
    // ����ֱ���Ƿ�;����ཻ,����ཻ�����Ϊ��.
    Vector3f vec3fN = m_pRectangle->Axis[0].Cross(m_pRectangle->Axis[1]);
    float fNdD = vec3fN.Dot(m_pLine->Direction);
    if( Math<float>::FAbs(fNdD) > Math<float>::ZERO_TOLERANCE )
    {
        // ֱ�ߺ;��β�ƽ��,���ֱ�ߺ;�������ƽ���ཻ.
        Vector3f vec3fDiff = m_pLine->Origin - m_pRectangle->Center;
        Vector3f& rD = (Vector3f&) m_pLine->Direction;
        Vector3f vec3fU, vec3fV;
        Vector3f::GetOrthonormalBasis(vec3fU, vec3fV, rD, true);
        float fUdD0 = vec3fU.Dot(m_pRectangle->Axis[0]);
        float fUdD1 = vec3fU.Dot(m_pRectangle->Axis[1]);
        float fUdPmC = vec3fU.Dot(vec3fDiff);
        float fVdD0 = vec3fV.Dot(m_pRectangle->Axis[0]);
        float fVdD1 = vec3fV.Dot(m_pRectangle->Axis[1]);
        float fVdPmC = vec3fV.Dot(vec3fDiff);
        float fInvDet = 1.0f / (fUdD0*fVdD1 - fUdD1*fVdD0);

        // �ཻ���Rectangle coordinates.
        float fS0 = (fVdD1*fUdPmC - fUdD1*fVdPmC)*fInvDet;
        float fS1 = (fUdD0*fVdPmC - fVdD0*fUdPmC)*fInvDet;

        if( Math<float>::FAbs(fS0) <= m_pRectangle->Extent[0]
        &&  Math<float>::FAbs(fS1) <= m_pRectangle->Extent[1] )
        {
            // �ཻ���ֱ�߲���.
            float fDdD0 = rD.Dot(m_pRectangle->Axis[0]);
            float fDdD1 = rD.Dot(m_pRectangle->Axis[1]);
            float fDdDiff = m_pLine->Direction.Dot(vec3fDiff);
            m_fLineParameter = fS0*fDdD0 + fS1*fDdD1 - fDdDiff;

            // �ཻ���Rectangle coordinates.
            m_afRectCoord[0] = fS0;
            m_afRectCoord[1] = fS1;

            // �ཻ���ھ����ڻ���α���.
            m_ClosestPoint0 = m_pLine->Origin +
                m_fLineParameter*m_pLine->Direction;

            m_ClosestPoint1 = m_pRectangle->Center +
                fS0*m_pRectangle->Axis[0] + fS1*m_pRectangle->Axis[1];

            return 0.0f;
        }
    }

    // Ҫô(1)ֱ�ߺ;��β�ƽ��,ֱ�ߺ;�������ƽ����ཻ���ھ���֮��.
    // ����(2)ֱ�ߺ;���ƽ��.
    // �������������,�����ϵ������Ӧ���ھ��ε�ĳ������.
    // ��˰�ֱ�ߺ;������������αȽ�.
    float fSqrDist = Math<float>::MAX_REAL;
    Vector3f aSDir[2] =
    {
        m_pRectangle->Extent[0]*m_pRectangle->Axis[0],
        m_pRectangle->Extent[1]*m_pRectangle->Axis[1]
    };
    for( int i1 = 0; i1 < 2; i1++ )
    {
        for( int i0 = 0; i0 < 2; i0++ )
        {
            Segment3f tempSeg;
            tempSeg.Origin = m_pRectangle->Center + 
                ((float)(2*i0 - 1))*aSDir[i1];
            tempSeg.Direction = m_pRectangle->Axis[1 - i1];
            tempSeg.Extent = m_pRectangle->Extent[1 - i1];
            DistLine3Segment3f tempLSDist(*m_pLine, tempSeg);
            float fSqrDistTmp = tempLSDist.GetSquared();
            if( fSqrDistTmp < fSqrDist )
            {
                m_ClosestPoint0 = tempLSDist.GetClosestPoint0();
                m_ClosestPoint1 = tempLSDist.GetClosestPoint1();
                fSqrDist = fSqrDistTmp;

                m_fLineParameter = tempLSDist.GetLineParameter();
                float fRatio = tempLSDist.GetSegmentParameter() / 
                    tempSeg.Extent;
                m_afRectCoord[0] = m_pRectangle->Extent[0]*
                    ((1 - i1)*(2*i0 - 1) + i1*fRatio);
                m_afRectCoord[1] = m_pRectangle->Extent[1]*
                    ((1 - i0)*(2*i1 - 1) + i0*fRatio);
            }
        }
    }

    return fSqrDist;
}
//----------------------------------------------------------------------------
float DistLine3Rectangle3f::Get (float fT, const Vector3f& rVelocity0, 
    const Vector3f& rVelocity1)
{
    Vector3f vec3fMOrigin = m_pLine->Origin + fT*rVelocity0;
    Vector3f vec3fMCenter = m_pRectangle->Center + fT*rVelocity1;
    Line3f tempMLine(vec3fMOrigin, m_pLine->Direction);
    Rectangle3f tempMRectangle(vec3fMCenter, m_pRectangle->Axis,
        m_pRectangle->Extent);

    return DistLine3Rectangle3f(tempMLine, tempMRectangle).Get();
}
//----------------------------------------------------------------------------
float DistLine3Rectangle3f::GetSquared (float fT, const Vector3f& rVelocity0, 
    const Vector3f& rVelocity1)
{
    Vector3f vec3fMOrigin = m_pLine->Origin + fT*rVelocity0;
    Vector3f vec3fMCenter = m_pRectangle->Center + fT*rVelocity1;
    Line3f tempMLine(vec3fMOrigin, m_pLine->Direction);
    Rectangle3f tempMRectangle(vec3fMCenter, m_pRectangle->Axis,
        m_pRectangle->Extent);

    return DistLine3Rectangle3f(tempMLine, tempMRectangle).GetSquared();
}
//----------------------------------------------------------------------------
float DistLine3Rectangle3f::GetLineParameter() const
{
    return m_fLineParameter;
}
//----------------------------------------------------------------------------
float DistLine3Rectangle3f::GetRectangleCoordinate(int i) const
{
    SE_ASSERT( 0 <= i && i < 2 );

    return m_afRectCoord[i];
}
//----------------------------------------------------------------------------