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
#include "SEIntrTriangle3Triangle3.h"
#include "SEIntersector1.h"
#include "SEIntrTriangle2Triangle2.h"

using namespace Swing;

//----------------------------------------------------------------------------
IntrTriangle3Triangle3f::IntrTriangle3Triangle3f(
    const Triangle3f& rTriangle0, const Triangle3f& rTriangle1)
    :
    m_pTriangle0(&rTriangle0), 
    m_pTriangle1(&rTriangle1)
{
    ReportCoplanarIntersections = true;
    m_iCount = 0;
}
//----------------------------------------------------------------------------
const Triangle3f& IntrTriangle3Triangle3f::GetTriangle0() const
{
    return *m_pTriangle0;
}
//----------------------------------------------------------------------------
const Triangle3f& IntrTriangle3Triangle3f::GetTriangle1() const
{
    return *m_pTriangle1;
}
//----------------------------------------------------------------------------
bool IntrTriangle3Triangle3f::Test()
{
    // get edge vectors for triangle0
    Vector3f aE0[3] =
    {
        m_pTriangle0->V[1] - m_pTriangle0->V[0], 
        m_pTriangle0->V[2] - m_pTriangle0->V[1], 
        m_pTriangle0->V[0] - m_pTriangle0->V[2]
    };

    // get normal vector of triangle0
    Vector3f vec3fN0 = aE0[0].UnitCross(aE0[1]);

    // project triangle1 onto normal line of triangle0, test for separation
    float fN0dT0V0 = vec3fN0.Dot(m_pTriangle0->V[0]);
    float fMin1, fMax1;
    ProjectOntoAxis(*m_pTriangle1, vec3fN0, fMin1, fMax1);
    if( fN0dT0V0 < fMin1 || fN0dT0V0 > fMax1 )
    {
        return false;
    }

    // get edge vectors for triangle1
    Vector3f aE1[3] =
    {
        m_pTriangle1->V[1] - m_pTriangle1->V[0], 
        m_pTriangle1->V[2] - m_pTriangle1->V[1], 
        m_pTriangle1->V[0] - m_pTriangle1->V[2]
    };

    // get normal vector of triangle1
    Vector3f vec3fN1 = aE1[0].UnitCross(aE1[1]);

    Vector3f vec3fDir;
    float fMin0, fMax0;
    int i0, i1;

    Vector3f vec3fN0xN1 = vec3fN0.UnitCross(vec3fN1);
    if( vec3fN0xN1.Dot(vec3fN0xN1) >= Math<float>::ZERO_TOLERANCE )
    {
        // triangles are not parallel

        // Project triangle0 onto normal line of triangle1, test for
        // separation.
        float fN1dT1V0 = vec3fN1.Dot(m_pTriangle1->V[0]);
        ProjectOntoAxis(*m_pTriangle0, vec3fN1, fMin0, fMax0);
        if( fN1dT1V0 < fMin0 || fN1dT1V0 > fMax0 )
        {
            return false;
        }

        // directions E0[i0]xE1[i1]
        for( i1 = 0; i1 < 3; i1++ )
        {
            for( i0 = 0; i0 < 3; i0++ )
            {
                vec3fDir = aE0[i0].UnitCross(aE1[i1]);
                ProjectOntoAxis(*m_pTriangle0, vec3fDir, fMin0, fMax0);
                ProjectOntoAxis(*m_pTriangle1, vec3fDir, fMin1, fMax1);
                if( fMax0 < fMin1 || fMax1 < fMin0 )
                {
                    return false;
                }
            }
        }
    }
    else  // triangles are parallel (and, in fact, coplanar)
    {
        // directions N0xE0[i0]
        for( i0 = 0; i0 < 3; i0++ )
        {
            vec3fDir = vec3fN0.UnitCross(aE0[i0]);
            ProjectOntoAxis(*m_pTriangle0, vec3fDir, fMin0, fMax0);
            ProjectOntoAxis(*m_pTriangle1, vec3fDir, fMin1, fMax1);
            if( fMax0 < fMin1 || fMax1 < fMin0 )
            {
                return false;
            }
        }

        // directions N1xE1[i1]
        for( i1 = 0; i1 < 3; i1++ )
        {
            vec3fDir = vec3fN1.UnitCross(aE1[i1]);
            ProjectOntoAxis(*m_pTriangle0, vec3fDir, fMin0, fMax0);
            ProjectOntoAxis(*m_pTriangle1, vec3fDir, fMin1, fMax1);
            if( fMax0 < fMin1 || fMax1 < fMin0 )
            {
                return false;
            }
        }
    }

    return true;
}
//----------------------------------------------------------------------------
bool IntrTriangle3Triangle3f::Find()
{
    // get the plane of triangle0
    Plane3f tempPlane0(m_pTriangle0->V[0], m_pTriangle0->V[1], 
        m_pTriangle0->V[2]);

    // Compute the signed distances of triangle1 vertices to plane0.  Use
    // an epsilon-thick plane test.
    int iPos1, iNeg1, iZero1, aiSign1[3];
    float afDist1[3];
    TrianglePlaneRelations(*m_pTriangle1, tempPlane0, afDist1, aiSign1, iPos1, 
        iNeg1, iZero1);

    if( iPos1 == 3 || iNeg1 == 3 )
    {
        // triangle1 is fully on one side of plane0
        return false;
    }

    if( iZero1 == 3 )
    {
        // triangle1 is contained by plane0
        if( ReportCoplanarIntersections )
        {
            return GetCoplanarIntersection(tempPlane0, *m_pTriangle0, 
                *m_pTriangle1);
        }

        return false;
    }

    // get the plane of triangle1
    Plane3f tempPlane1(m_pTriangle1->V[0], m_pTriangle1->V[1], 
        m_pTriangle1->V[2]);

    // Compute the signed distances of triangle0 vertices to plane1.  Use
    // an epsilon-thick plane test.
    int iPos0, iNeg0, iZero0, aiSign0[3];
    float afDist0[3];
    TrianglePlaneRelations(*m_pTriangle0, tempPlane1, afDist0, aiSign0, iPos0, iNeg0, 
        iZero0);

    if( iPos0 == 3 || iNeg0 == 3 )
    {
        // triangle0 is fully on one side of plane1
        return false;
    }

    if( iZero0 == 3 )
    {
        // triangle0 is contained by plane1
        if( ReportCoplanarIntersections )
        {
            return GetCoplanarIntersection(tempPlane1, *m_pTriangle0, 
                *m_pTriangle1);
        }

        return false;
    }

    // compute the line of intersection
    float fDot = tempPlane0.Normal.Dot(tempPlane1.Normal);
    float fInvDet = 1.0f / (1.0f - fDot*fDot);
    float fC0 = (tempPlane0.Constant - fDot*tempPlane1.Constant) * fInvDet;
    float fC1 = (tempPlane1.Constant - fDot*tempPlane0.Constant) * fInvDet;
    Line3f tempLine(fC0*tempPlane0.Normal + fC1*tempPlane1.Normal, 
        tempPlane0.Normal.UnitCross(tempPlane1.Normal));

    // compute the intervals of intersection of triangles and line
    float afT0[2], afT1[2];
    GetInterval(*m_pTriangle0, tempLine, afDist0, aiSign0, afT0);
    GetInterval(*m_pTriangle1, tempLine, afDist1, aiSign1, afT1);

    // compute the intersection of intervals
    Intersector1<float> tempIntersector(afT0, afT1);
    tempIntersector.Find();
    m_iCount = tempIntersector.GetCount();
    for( int i = 0; i < m_iCount; i++ )
    {
        m_aPoint[i] = tempLine.Origin +
            tempIntersector.GetOverlap(i)*tempLine.Direction;
    }

    return m_iCount > 0;
}
//----------------------------------------------------------------------------
bool IntrTriangle3Triangle3f::Test(float fTMax, 
    const Vector3f& rVelocity0, const Vector3f& rVelocity1)
{
    float fTFirst = 0.0f;
    float fTLast = Math<float>::MAX_REAL;

    // velocity relative to triangle0
    Vector3f vec3fVel = rVelocity1 - rVelocity0;

    // compute edge and normal directions for triangle0
    Vector3f aE[3] =
    {
        m_pTriangle0->V[1] - m_pTriangle0->V[0], 
        m_pTriangle0->V[2] - m_pTriangle0->V[1], 
        m_pTriangle0->V[0] - m_pTriangle0->V[2]
    };
    Vector3f vec3fN = aE[0].UnitCross(aE[1]);
    if( !TestOverlap(vec3fN, fTMax, vec3fVel, fTFirst, fTLast) )
    {
        return false;
    }

    // compute edge and normal directions for triangle1
    Vector3f aF[3] =
    {
        m_pTriangle1->V[1] - m_pTriangle1->V[0], 
        m_pTriangle1->V[2] - m_pTriangle1->V[1], 
        m_pTriangle1->V[0] - m_pTriangle1->V[2]
    };
    Vector3f vec3fM = aF[0].UnitCross(aF[1]);

    Vector3f vec3fDir;
    int i0, i1;

    if( Math<float>::FAbs(vec3fN.Dot(vec3fM)) < 1.0f - Math<float>::ZERO_TOLERANCE )
    {
        // triangles are not parallel

        // direction M
        if( !TestOverlap(vec3fM, fTMax, vec3fVel, fTFirst, fTLast) )
        {
            return false;
        }

        // directions E[i0]xF[i1]
        for( i1 = 0; i1 < 3; i1++ )
        {
            for( i0 = 0; i0 < 3; i0++ )
            {
                vec3fDir = aE[i0].UnitCross(aF[i1]);
                if( !TestOverlap(vec3fDir, fTMax, vec3fVel, fTFirst, fTLast) )
                {
                    return false;
                }
            }
        }
    }
    else  // triangles are parallel (and, in fact, coplanar)
    {
        // directions NxE[i0]
        for( i0 = 0; i0 < 3; i0++ )
        {
            vec3fDir = vec3fN.UnitCross(aE[i0]);
            if( !TestOverlap(vec3fDir, fTMax, vec3fVel, fTFirst, fTLast) )
            {
                return false;
            }
        }

        // directions NxF[i1]
        for( i1 = 0; i1 < 3; i1++ )
        {
            vec3fDir = vec3fM.UnitCross(aF[i1]);
            if( !TestOverlap(vec3fDir, fTMax, vec3fVel, fTFirst, fTLast) )
            {
                return false;
            }
        }
    }

    m_fContactTime = fTFirst;

    return true;
}
//----------------------------------------------------------------------------
bool IntrTriangle3Triangle3f::Find(float fTMax, 
    const Vector3f& rVelocity0, const Vector3f& rVelocity1)
{
    float fTFirst = 0.0f;
    float fTLast = Math<float>::MAX_REAL;

    // velocity relative to triangle0
    Vector3f vec3fVel = rVelocity1 - rVelocity0;

    ContactSide eSide = CS_NONE;
    Configuration tempTCfg0, tempTCfg1;

    // compute edge and normal directions for triangle0
    Vector3f aE[3] =
    {
        m_pTriangle0->V[1] - m_pTriangle0->V[0], 
        m_pTriangle0->V[2] - m_pTriangle0->V[1], 
        m_pTriangle0->V[0] - m_pTriangle0->V[2]
    };
    Vector3f vec3fN = aE[0].UnitCross(aE[1]);
    if( !FindOverlap(vec3fN, fTMax, vec3fVel, eSide, tempTCfg0, tempTCfg1, 
        fTFirst, fTLast) )
    {
        return false;
    }

    // compute edge and normal directions for triangle1
    Vector3f aF[3] =
    {
        m_pTriangle1->V[1] - m_pTriangle1->V[0], 
        m_pTriangle1->V[2] - m_pTriangle1->V[1], 
        m_pTriangle1->V[0] - m_pTriangle1->V[2]
    };
    Vector3f vec3fM = aF[0].UnitCross(aF[1]);

    Vector3f vec3fDir;
    int i0, i1;

    if( Math<float>::FAbs(vec3fN.Dot(vec3fM)) < 1.0f - Math<float>::ZERO_TOLERANCE )
    {
        // triangles are not parallel

        // direction M
        if( !FindOverlap(vec3fM, fTMax, vec3fVel, eSide, tempTCfg0, tempTCfg1, 
            fTFirst, fTLast) )
        {
            return false;
        }

        // directions E[i0]xF[i1]
        for( i1 = 0; i1 < 3; i1++ )
        {
            for( i0 = 0; i0 < 3; i0++ )
            {
                vec3fDir = aE[i0].UnitCross(aF[i1]);
                if( !FindOverlap(vec3fDir, fTMax, vec3fVel, eSide, 
                    tempTCfg0, tempTCfg1, fTFirst, fTLast) )
                {
                    return false;
                }
            }
        }
    }
    else  // triangles are parallel (and, in fact, coplanar)
    {
        // directions NxE[i0]
        for( i0 = 0; i0 < 3; i0++ )
        {
            vec3fDir = vec3fN.UnitCross(aE[i0]);
            if( !FindOverlap(vec3fDir, fTMax, vec3fVel, eSide, 
                tempTCfg0, tempTCfg1, fTFirst, fTLast) )
            {
                return false;
            }
        }

        // directions NxF[i1]
        for( i1 = 0; i1 < 3; i1++ )
        {
            vec3fDir = vec3fM.UnitCross(aF[i1]);
            if( !FindOverlap(vec3fDir, fTMax, vec3fVel, eSide, 
                tempTCfg0, tempTCfg1, fTFirst, fTLast) )
            {
                return false;
            }
        }
    }
    
    if( fTFirst <= 0.0f )
    {
        return false;
    }

    m_fContactTime = fTFirst;

    // adjust U and V for first time of contact before finding contact set
    Triangle3f aMTri0, aMTri1;
    for( i0 = 0; i0 < 3; i0++ )
    {
        aMTri0.V[i0] = m_pTriangle0->V[i0] + fTFirst*rVelocity0;
        aMTri1.V[i0] = m_pTriangle1->V[i0] + fTFirst*rVelocity1;
    }

    FindContactSet(aMTri0, aMTri1, eSide, tempTCfg0, tempTCfg1);

    return true;
}
//----------------------------------------------------------------------------
int IntrTriangle3Triangle3f::GetCount() const
{
    return m_iCount;
}
//----------------------------------------------------------------------------
const Vector3f& IntrTriangle3Triangle3f::GetPoint(int i) const
{
    SE_ASSERT( 0 <= i && i < m_iCount );

    return m_aPoint[i];
}
//----------------------------------------------------------------------------
void IntrTriangle3Triangle3f::ProjectOntoAxis(const Triangle3f& rTri, 
    const Vector3f& rAxis, float& rfMin, float& rfMax)
{
    float fDot0 = rAxis.Dot(rTri.V[0]);
    float fDot1 = rAxis.Dot(rTri.V[1]);
    float fDot2 = rAxis.Dot(rTri.V[2]);

    rfMin = fDot0;
    rfMax = rfMin;

    if( fDot1 < rfMin )
    {
        rfMin = fDot1;
    }
    else if( fDot1 > rfMax )
    {
        rfMax = fDot1;
    }

    if( fDot2 < rfMin )
    {
        rfMin = fDot2;
    }
    else if( fDot2 > rfMax )
    {
        rfMax = fDot2;
    }
}
//----------------------------------------------------------------------------
void IntrTriangle3Triangle3f::TrianglePlaneRelations(
    const Triangle3f& rTriangle, const Plane3f& rPlane, 
    float afDistance[3], int aiSign[3], int& riPositive, int& riNegative, 
    int& riZero)
{
    // Compute the signed distances of triangle vertices to the plane.  Use
    // an epsilon-thick plane test.
    riPositive = 0;
    riNegative = 0;
    riZero = 0;
    for( int i = 0; i < 3; i++ )
    {
        afDistance[i] = rPlane.GetDistance(rTriangle.V[i]);
        if( afDistance[i] > Math<float>::ZERO_TOLERANCE )
        {
            aiSign[i] = 1;
            riPositive++;
        }
        else if( afDistance[i] < -Math<float>::ZERO_TOLERANCE )
        {
            aiSign[i] = -1;
            riNegative++;
        }
        else
        {
            afDistance[i] = 0.0f;
            aiSign[i] = 0;
            riZero++;
        }
    }
}
//----------------------------------------------------------------------------
void IntrTriangle3Triangle3f::GetInterval(
    const Triangle3f& rTriangle, const Line3f& rLine, 
    const float afDistance[3], const int aiSign[3], float afParam[2])
{
    // project triangle onto line
    float afProj[3];
    int i;
    for( i = 0; i < 3; i++ )
    {
        Vector3f vec3fDiff = rTriangle.V[i] - rLine.Origin;
        afProj[i] = rLine.Direction.Dot(vec3fDiff);
    }

    // compute transverse intersections of triangle edges with line
    float fNumer, fDenom;
    int i0, i1, i2;
    int iCount = 0;
    for( i0 = 2, i1 = 0; i1 < 3; i0 = i1++ )
    {
        if( aiSign[i0]*aiSign[i1] < 0 )
        {
            SE_ASSERT( iCount < 2 );

            fNumer = afDistance[i0]*afProj[i1] - afDistance[i1]*afProj[i0];
            fDenom = afDistance[i0] - afDistance[i1];
            afParam[iCount++] = fNumer / fDenom;
        }
    }

    // check for grazing contact
    if( iCount < 2 )
    {
        for( i0 = 1, i1 = 2, i2 = 0; i2 < 3; i0 = i1, i1 = i2, i2++ )
        {
            if( aiSign[i2] == 0 )
            {
                SE_ASSERT( iCount < 2 );

                fNumer = afDistance[i0]*afProj[i1] - afDistance[i1]*afProj[i0];
                fDenom = afDistance[i0] - afDistance[i1];
                afParam[iCount++] = fNumer / fDenom;
            }
        }
    }

    // sort
    SE_ASSERT( iCount >= 1 );

    if( iCount == 2 )
    {
        if( afParam[0] > afParam[1] )
        {
            float fSave = afParam[0];
            afParam[0] = afParam[1];
            afParam[1] = fSave;
        }
    }
    else
    {
        afParam[1] = afParam[0];
    }
}
//----------------------------------------------------------------------------
bool IntrTriangle3Triangle3f::GetCoplanarIntersection(
    const Plane3f& rPlane, const Triangle3f& rTri0, 
    const Triangle3f& rTri1)
{
    // Project triangles onto coordinate plane most aligned with plane
    // normal.
    int iMaxNormal = 0;
    float fMax = Math<float>::FAbs(rPlane.Normal.X);
    float fAbs = Math<float>::FAbs(rPlane.Normal.Y);
    if( fAbs > fMax )
    {
        iMaxNormal = 1;
        fMax = fAbs;
    }
    fAbs = Math<float>::FAbs(rPlane.Normal.Z);
    if( fAbs > fMax )
    {
        iMaxNormal = 2;
    }

    Triangle2f tempProjTri0, tempProjTri1;
    int i;

    if( iMaxNormal == 0 )
    {
        // project onto yz-plane
        for( i = 0; i < 3; i++ )
        {
            tempProjTri0.V[i].X = rTri0.V[i].Y;
            tempProjTri0.V[i].Y = rTri0.V[i].Z;
            tempProjTri1.V[i].X = rTri1.V[i].Y;
            tempProjTri1.V[i].Y = rTri1.V[i].Z;
        }
    }
    else if( iMaxNormal == 1 )
    {
        // project onto xz-plane
        for( i = 0; i < 3; i++ )
        {
            tempProjTri0.V[i].X = rTri0.V[i].X;
            tempProjTri0.V[i].Y = rTri0.V[i].Z;
            tempProjTri1.V[i].X = rTri1.V[i].X;
            tempProjTri1.V[i].Y = rTri1.V[i].Z;
        }
    }
    else
    {
        // project onto xy-plane
        for( i = 0; i < 3; i++ )
        {
            tempProjTri0.V[i].X = rTri0.V[i].X;
            tempProjTri0.V[i].Y = rTri0.V[i].Y;
            tempProjTri1.V[i].X = rTri1.V[i].X;
            tempProjTri1.V[i].Y = rTri1.V[i].Y;
        }
    }

    // 2D triangle intersection routines require counterclockwise ordering
    Vector2f vec2fSave;
    Vector2f vec2fEdge0 = tempProjTri0.V[1] - tempProjTri0.V[0];
    Vector2f vec2fEdge1 = tempProjTri0.V[2] - tempProjTri0.V[0];
    if( vec2fEdge0.GetDotPerp(vec2fEdge1) < 0.0f )
    {
        // triangle is clockwise, reorder it
        vec2fSave = tempProjTri0.V[1];
        tempProjTri0.V[1] = tempProjTri0.V[2];
        tempProjTri0.V[2] = vec2fSave;
    }

    vec2fEdge0 = tempProjTri1.V[1] - tempProjTri1.V[0];
    vec2fEdge1 = tempProjTri1.V[2] - tempProjTri1.V[0];
    if( vec2fEdge0.GetDotPerp(vec2fEdge1) < 0.0f )
    {
        // triangle is clockwise, reorder it
        vec2fSave = tempProjTri1.V[1];
        tempProjTri1.V[1] = tempProjTri1.V[2];
        tempProjTri1.V[2] = vec2fSave;
    }

    IntrTriangle2Triangle2f tempIntr(tempProjTri0, tempProjTri1);
    if( !tempIntr.Find() )
    {
        return false;
    }

    // map 2D intersections back to the 3D triangle space
    m_iCount = tempIntr.GetCount();
    if( iMaxNormal == 0 )
    {
        float fInvNX = 1.0f / rPlane.Normal.X;
        for( i = 0; i < m_iCount; i++ )
        {
            m_aPoint[i].Y = tempIntr.GetPoint(i).X;
            m_aPoint[i].Z = tempIntr.GetPoint(i).Y;
            m_aPoint[i].X = fInvNX*(rPlane.Constant -
                rPlane.Normal.Y*m_aPoint[i].Y -
                rPlane.Normal.Z*m_aPoint[i].Z);
        }
    }
    else if( iMaxNormal == 1 )
    {
        float fInvNY = 1.0f / rPlane.Normal.Y;
        for( i = 0; i < m_iCount; i++ )
        {
            m_aPoint[i].X = tempIntr.GetPoint(i).X;
            m_aPoint[i].Z = tempIntr.GetPoint(i).Y;
            m_aPoint[i].Y = fInvNY*(rPlane.Constant -
                rPlane.Normal.X*m_aPoint[i].X -
                rPlane.Normal.Z*m_aPoint[i].Z);
        }
    }
    else
    {
        float fInvNZ = 1.0f / rPlane.Normal.Z;
        for( i = 0; i < m_iCount; i++ )
        {
            m_aPoint[i].X = tempIntr.GetPoint(i).X;
            m_aPoint[i].Y = tempIntr.GetPoint(i).Y;
            m_aPoint[i].Z = fInvNZ*(rPlane.Constant -
                rPlane.Normal.X*m_aPoint[i].X -
                rPlane.Normal.Y*m_aPoint[i].Y);
        }
    }

    return true;
}
//----------------------------------------------------------------------------
bool IntrTriangle3Triangle3f::TestOverlap(float fTMax, float fSpeed, 
    float fUMin, float fUMax, float fVMin, float fVMax, float& rfTFirst, 
    float& rfTLast)
{
    // Constant velocity separating axis test.

    float fT;

    if( fVMax < fUMin ) // V on left of U
    {
        if( fSpeed <= 0.0f ) // V moving away from U
        {
            return false;
        }

        // find first time of contact on this axis
        fT = (fUMin - fVMax) / fSpeed;
        if( fT > rfTFirst )
        {
            rfTFirst = fT;
        }

        // quick out: intersection after desired time interval
        if( rfTFirst > fTMax )
        {
            return false;   
        }

        // find last time of contact on this axis
        fT = (fUMax - fVMin) / fSpeed;
        if( fT < rfTLast )
        {
            rfTLast = fT;
        }

        // quick out: intersection before desired time interval
        if( rfTFirst > rfTLast )
        {
            return false; 
        }
    }
    else if( fUMax < fVMin )   // V on right of U
    {
        if( fSpeed >= 0.0f ) // V moving away from U
        {
            return false;
        }

        // find first time of contact on this axis
        fT = (fUMax - fVMin) / fSpeed;
        if( fT > rfTFirst )
        {
            rfTFirst = fT;
        }

        // quick out: intersection after desired time interval
        if( rfTFirst > fTMax )
        {
            return false;   
        }

        // find last time of contact on this axis
        fT = (fUMin - fVMax) / fSpeed;
        if( fT < rfTLast )
        {
            rfTLast = fT;
        }

        // quick out: intersection before desired time interval
        if( rfTFirst > rfTLast )
        {
            return false; 
        }

    }
    else // V and U on overlapping interval
    {
        if( fSpeed > 0.0f )
        {
            // find last time of contact on this axis
            fT = (fUMax - fVMin) / fSpeed;
            if( fT < rfTLast )
            {
                rfTLast = fT;
            }

            // quick out: intersection before desired interval
            if( rfTFirst > rfTLast )
            {
                return false; 
            }
        }
        else if( fSpeed < 0.0f )
        {
            // find last time of contact on this axis
            fT = (fUMin - fVMax) / fSpeed;
            if( fT < rfTLast )
            {
                rfTLast = fT;
            }

            // quick out: intersection before desired interval
            if( rfTFirst > rfTLast )
            {
                return false;
            }
        }
    }

    return true;
}
//----------------------------------------------------------------------------
bool IntrTriangle3Triangle3f::FindOverlap(float fTMax, float fSpeed, 
    const Configuration& rUC, const Configuration& rVC, ContactSide& rSide, 
    Configuration& rTUC, Configuration& rTVC, float& rfTFirst, float& rfTLast)
{
    // Constant velocity separating axis test.  UC and VC are the new
    // potential configurations, and TUC and TVC are the best known
    // configurations.

    float fT;

    if( rVC.Max < rUC.Min ) // V on left of U
    {
        if( fSpeed <= 0.0f ) // V moving away from U
        {
            return false;
        }

        // find first time of contact on this axis
        fT = (rUC.Min - rVC.Max) / fSpeed;

        // If this is the new maximum first time of contact, set side and
        // configuration.
        if( fT > rfTFirst )
        {
            rfTFirst = fT;
            rSide = CS_LEFT;
            rTUC = rUC;
            rTVC = rVC;
        }

        // quick out: intersection after desired interval
        if( rfTFirst > fTMax )
        {
            return false;
        }

        // find last time of contact on this axis
        fT = (rUC.Max - rVC.Min) / fSpeed;
        if( fT < rfTLast )
        {
            rfTLast = fT;
        }

        // quick out: intersection before desired interval
        if( rfTFirst > rfTLast )
        {
            return false;
        }
    }
    else if( rUC.Max < rVC.Min )   // V on right of U
    {
        if( fSpeed >= 0.0f ) // V moving away from U
        {
            return false;
        }

        // find first time of contact on this axis
        fT = (rUC.Max - rVC.Min) / fSpeed;

        // If this is the new maximum first time of contact, set side and
        // configuration.
        if( fT > rfTFirst )
        {
            rfTFirst = fT;
            rSide = CS_RIGHT;
            rTUC = rUC;
            rTVC = rVC;
        }

        // quick out: intersection after desired interval
        if( rfTFirst > fTMax )
        {
            return false;   
        }

        // find last time of contact on this axis
        fT = (rUC.Min - rVC.Max) / fSpeed;
        if( fT < rfTLast )
        {
            rfTLast = fT;
        }

        // quick out: intersection before desired interval
        if( rfTFirst > rfTLast )
        {
            return false;
        }
    }
    else // V and U on overlapping interval
    {
        if( fSpeed > 0.0f )
        {
            // find last time of contact on this axis
            fT = (rUC.Max - rVC.Min) / fSpeed;
            if( fT < rfTLast )
            {
                rfTLast = fT;
            }

            // quick out: intersection before desired interval
            if( rfTFirst > rfTLast )
            {
                return false;
            }
        }
        else if( fSpeed < 0.0f )
        {
            // find last time of contact on this axis
            fT = (rUC.Min - rVC.Max) / fSpeed;
            if( fT < rfTLast )
            {
                rfTLast = fT;
            }

            // quick out: intersection before desired interval
            if( rfTFirst > rfTLast )
            {
                return false;
            }
        }
    }

    return true;
}
//----------------------------------------------------------------------------
bool IntrTriangle3Triangle3f::TestOverlap(const Vector3f& rAxis, 
    float fTMax, const Vector3f& rVelocity, float& rfTFirst, 
    float& rfTLast)
{
    float fMin0, fMax0, fMin1, fMax1;
    ProjectOntoAxis(*m_pTriangle0, rAxis, fMin0, fMax0);
    ProjectOntoAxis(*m_pTriangle1, rAxis, fMin1, fMax1);
    float fSpeed = rVelocity.Dot(rAxis);

    return TestOverlap(fTMax, fSpeed, fMin0, fMax0, fMin1, fMax1, rfTFirst, 
        rfTLast);
}
//----------------------------------------------------------------------------
bool IntrTriangle3Triangle3f::FindOverlap(const Vector3f& rAxis, 
    float fTMax, const Vector3f& rVelocity, ContactSide& reSide, 
    Configuration& rTCfg0, Configuration& rTCfg1, float& rfTFirst, 
    float& rfTLast)
{
    Configuration tempCfg0, tempCfg1;
    ProjectOntoAxis(*m_pTriangle0, rAxis, tempCfg0);
    ProjectOntoAxis(*m_pTriangle1, rAxis, tempCfg1);
    float fSpeed = rVelocity.Dot(rAxis);

    return FindOverlap(fTMax, fSpeed, tempCfg0, tempCfg1, reSide, rTCfg0, 
        rTCfg1, rfTFirst, rfTLast);
}
//----------------------------------------------------------------------------
void IntrTriangle3Triangle3f::ProjectOntoAxis(const Triangle3f& rTri, 
    const Vector3f& rAxis, Configuration& rCfg)
{
    // find projections of vertices onto potential separating axis
    float fD0 = rAxis.Dot(rTri.V[0]);
    float fD1 = rAxis.Dot(rTri.V[1]);
    float fD2 = rAxis.Dot(rTri.V[2]);

    // explicit sort of vertices to construct a Configuration object
    if( fD0 <= fD1 )
    {
        if( fD1 <= fD2 ) // D0 <= D1 <= D2
        {
            if( fD0 != fD1 )
            {
                if( fD1 != fD2 )
                {
                    rCfg.Map = M111;
                }
                else
                {
                    rCfg.Map = M12;
                }
            }
            else // ( D0 == D1 )
            {
                if( fD1 != fD2 )
                {
                    rCfg.Map = M21;
                }
                else
                {
                    rCfg.Map = M3;
                }
            }
            rCfg.Index[0] = 0;
            rCfg.Index[1] = 1;
            rCfg.Index[2] = 2;
            rCfg.Min = fD0;
            rCfg.Max = fD2;
        }
        else if( fD0 <= fD2 ) // D0 <= D2 < D1
        {
            if( fD0 != fD2 )
            {
                rCfg.Map = M111;
                rCfg.Index[0] = 0;
                rCfg.Index[1] = 2;
                rCfg.Index[2] = 1;
            }
            else
            {
                rCfg.Map = M21;
                rCfg.Index[0] = 2;
                rCfg.Index[1] = 0;
                rCfg.Index[2] = 1;
            }
            rCfg.Min = fD0;
            rCfg.Max = fD1;
        }
        else // D2 < D0 <= D1
        {
            if( fD0 != fD1 )
            {
                rCfg.Map = M111;
            }
            else
            {
                rCfg.Map = M12;
            }

            rCfg.Index[0] = 2;
            rCfg.Index[1] = 0;
            rCfg.Index[2] = 1;
            rCfg.Min = fD2;
            rCfg.Max = fD1;
        }
    }
    else if( fD2 <= fD1 ) // D2 <= D1 < D0
    {
        if( fD2 != fD1 )
        {
            rCfg.Map = M111;
            rCfg.Index[0] = 2;
            rCfg.Index[1] = 1;
            rCfg.Index[2] = 0;
        }
        else
        {
            rCfg.Map = M21;
            rCfg.Index[0] = 1;
            rCfg.Index[1] = 2;
            rCfg.Index[2] = 0;

        }
        rCfg.Min = fD2;
        rCfg.Max = fD0;
    }
    else if( fD2 <= fD0 ) // D1 < D2 <= D0
    {
        if( fD2 != fD0 ) 
        {
            rCfg.Map = M111;
        }
        else
        {
            rCfg.Map = M12;
        }

        rCfg.Index[0] = 1;
        rCfg.Index[1] = 2;
        rCfg.Index[2] = 0;
        rCfg.Min = fD1;
        rCfg.Max = fD0;
    }
    else // D1 < D0 < D2
    {
        rCfg.Map = M111;
        rCfg.Index[0] = 1;
        rCfg.Index[1] = 0;
        rCfg.Index[2] = 2;
        rCfg.Min = fD1;
        rCfg.Max = fD2;
    }
}
//----------------------------------------------------------------------------
void IntrTriangle3Triangle3f::FindContactSet(
    const Triangle3f& rTri0, const Triangle3f& rTri1, 
    ContactSide& reSide, Configuration& rCfg0, Configuration& rCfg1)
{
    if( reSide == CS_RIGHT ) // tri1 to the right of tri0
    {
        if( rCfg0.Map == M21 || rCfg0.Map == M111 )
        {
            // tri0 touching tri1 at a single point
            m_iCount = 1;
            m_aPoint[0] = rTri0.V[2];
        }
        else if( rCfg1.Map == M12 || rCfg1.Map == M111 )
        {
            // tri1 touching tri0 at a single point
            m_iCount = 1;
            m_aPoint[0] = rTri1.V[0];
        }
        else if( rCfg0.Map == M12 )
        {
            if( rCfg1.Map == M21 )
            {
                // edge0-edge1 intersection
                GetEdgeEdgeIntersection(rTri0.V[1], rTri0.V[2], rTri1.V[0], 
                    rTri1.V[1]);
            }
            else // rCfg1.Map == m3
            {
                // uedge-vface intersection
                //Vector3f aEdge0[2] = { rTri0.V[1], rTri0.V[2] };
                //FindContactSetColinearLineTri(aEdge0, rTri1, riCount, 
                //    aP);
            }
        }
        else // rCfg0.Map == M3
        {
            if( rCfg1.Map == M21 )
            {
                // face0-edge1 intersection
                //Vector3f aEdge1[2] = { rTri1.V[0], rTri1.V[1] };
                //FindContactSetColinearLineTri(aEdge1, rTri0, riCount, 
                //    aP);
            } 
            else // rCfg1.Map == M3
            {
                // face0-face1 intersection
                Plane3f tempPlane0(rTri0.V[0], rTri0.V[1], rTri0.V[2]);
                GetCoplanarIntersection(tempPlane0, rTri0, rTri1);
            }
        }
    }
    else if( reSide == CS_LEFT ) // tri1 to the left of tri0
    {
        if( rCfg1.Map == M21 || rCfg1.Map == M111 )
        {
            // tri1 touching tri0 at a single point
            m_iCount = 1;
            m_aPoint[0] = rTri1.V[2];
        }
        else if( rCfg0.Map == M12 || rCfg0.Map == M111 )
        {
            // tri0 touching tri1 at a single point
            m_iCount = 1;
            m_aPoint[0] = rTri0.V[0];
        }
        else if( rCfg1.Map == M12 )
        {
            if( rCfg0.Map == M21 )
            {
                // edge0-edge1 intersection
                GetEdgeEdgeIntersection(rTri0.V[0], rTri0.V[1], rTri1.V[1], 
                    rTri1.V[2]);
            }
            else // rCfg0.Map == M3
            {
                // edge1-face0 intersection
                //Vector3f aEdge1[2] = { rTri1.V[1], rTri1.V[2] };
                //FindContactSetColinearLineTri(aEdge1, rTri0, riCount, 
                //    aP);
            }
        }
        else // rCfg1.Map == M3
        {
            if( rCfg0.Map == M21 )
            {
                // edge0-face1 intersection
                //Vector3f aEdge0[2] = { rTri0.V[0], rTri0.V[1] };
                //FindContactSetColinearLineTri(aEdge0, rTri1, riCount, 
                //    aP);
            } 
            else // rCfg0.Map == M
            {
                // face0-face1 intersection
                Plane3f tempPlane0(rTri0.V[0], rTri0.V[1], rTri0.V[2]);
                GetCoplanarIntersection(tempPlane0, rTri0, rTri1);
            }
        }
    }
    else // reSide == CS_NONE
    {
        // triangles are already intersecting tranversely
        IntrTriangle3Triangle3f(rTri0, rTri1).Find();
    }
}
//----------------------------------------------------------------------------
void IntrTriangle3Triangle3f::GetEdgeEdgeIntersection(
    const Vector3f& /*rU0*/, const Vector3f& /*rU1*/, 
    const Vector3f& /*rV0*/, const Vector3f& /*rV1*/)
{
    // ´ýÊµÏÖ.
}
//----------------------------------------------------------------------------
