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
#include "SEIntrTriangle2Triangle2.h"

using namespace Swing;

//----------------------------------------------------------------------------
IntrTriangle2Triangle2f::IntrTriangle2Triangle2f(
    const Triangle2f& rTriangle0, const Triangle2f& rTriangle1)
    :
    m_pTriangle0(&rTriangle0), 
    m_pTriangle1(&rTriangle1)
{
    m_iCount = 0;
}
//----------------------------------------------------------------------------
const Triangle2f& IntrTriangle2Triangle2f::GetTriangle0() const
{
    return *m_pTriangle0;
}
//----------------------------------------------------------------------------
const Triangle2f& IntrTriangle2Triangle2f::GetTriangle1() const
{
    return *m_pTriangle1;
}
//----------------------------------------------------------------------------
bool IntrTriangle2Triangle2f::Test()
{
    int i0 = 0, i1 = 0;
    Vector2f vec2fDir;

    // test edges of triangle0 for separation
    for( i0 = 0, i1 = 2; i0 < 3; i1 = i0, i0++ )
    {
        // test axis V0[i1] + t*perp(V0[i0]-V0[i1]), perp(x, y) = (y, -x)
        vec2fDir.X = m_pTriangle0->V[i0].Y - m_pTriangle0->V[i1].Y;
        vec2fDir.Y = m_pTriangle0->V[i1].X - m_pTriangle0->V[i0].X;
        if( OnWhichSide(m_pTriangle1->V, m_pTriangle0->V[i1], vec2fDir) > 0 )
        {
            // triangle1 is entirely on positive side of triangle0 edge
            return false;
        }
    }

    // test edges of triangle1 for separation
    for( i0 = 0, i1 = 2; i0 < 3; i1 = i0, i0++ )
    {
        // test axis V1[i1] + t*perp(V1[i0]-V1[i1]), perp(x, y) = (y, -x)
        vec2fDir.X = m_pTriangle1->V[i0].Y - m_pTriangle1->V[i1].Y;
        vec2fDir.Y = m_pTriangle1->V[i1].X - m_pTriangle1->V[i0].X;
        if( OnWhichSide(m_pTriangle0->V, m_pTriangle1->V[i1], vec2fDir) > 0 )
        {
            // triangle0 is entirely on positive side of triangle1 edge
            return false;
        }
    }

    return true;
}
//----------------------------------------------------------------------------
bool IntrTriangle2Triangle2f::Find()
{
    // The potential intersection is initialized to triangle1.  The set of
    // vertices is refined based on clipping against each edge of triangle0.
    m_iCount = 3;
    for( int i = 0; i < 3; i++ )
    {
        m_aPoint[i] = m_pTriangle1->V[i];
    }

    for( int i1 = 2, i0 = 0; i0 < 3; i1 = i0, i0++ )
    {
        // clip against edge <V0[i1], V0[i0]>
        Vector2f vec2fN(
            m_pTriangle0->V[i1].Y - m_pTriangle0->V[i0].Y, 
            m_pTriangle0->V[i0].X - m_pTriangle0->V[i1].X);
        float fC = vec2fN.Dot(m_pTriangle0->V[i1]);
        ClipConvexPolygonAgainstLine(vec2fN, fC, m_iCount, m_aPoint);
        if( m_iCount == 0 )
        {
            // triangle completely clipped, no intersection occurs
            return false;
        }
    }

    return true;
}
//----------------------------------------------------------------------------
bool IntrTriangle2Triangle2f::Test(float fTMax, 
    const Vector2f& rVelocity0, const Vector2f& rVelocity1)
{
    // process as if V0-triangle is stationary and V1-triangle is moving
    Vector2f vec2fW = rVelocity1 - rVelocity0;
    int iSide = 0;  // 0 = NONE, -1 = LEFT, +1 = RIGHT
    float fTFirst = 0.0f;
    float fTLast = Math<float>::MAX_REAL;

    Configuration tempCfg0, tempCfg1, tempTCfg0, tempTCfg1;
    int i0, i1, i2;
    Vector2f vec2fD;
    float fSpeed;

    // process edges of V0-triangle
    for( i0 = 1, i1 = 2, i2 = 0; i2 < 3; i0 = i1, i1 = i2, i2++ )
    {
        // test axis V0[i1] + t*perp(V0[i2]-V0[i1]), perp(x, y) = (y, -x)
        vec2fD.X = m_pTriangle0->V[i2].Y - m_pTriangle0->V[i1].Y;
        vec2fD.Y = m_pTriangle0->V[i1].X - m_pTriangle0->V[i2].X;
        fSpeed = vec2fD.Dot(vec2fW);

        ComputeTwo(tempCfg0, m_pTriangle0->V, vec2fD, i0, i1, i2);
        ComputeThree(tempCfg1, m_pTriangle1->V, vec2fD, m_pTriangle0->V[i1]);

        if( NoIntersect(tempCfg0, tempCfg1, fTMax, fSpeed, iSide, tempTCfg0, tempTCfg1, 
            fTFirst, fTLast) )
        {
            return false;
        }
    }

    // process edges of V1-triangle
    for( i0 = 1, i1 = 2, i2 = 0; i2 < 3; i0 = i1, i1 = i2, i2++ )
    {
        // test axis V1[i1] + t*perp(V1[i2]-V1[i1]), perp(x, y) = (y, -x)
        vec2fD.X = m_pTriangle1->V[i2].Y - m_pTriangle1->V[i1].Y;
        vec2fD.Y = m_pTriangle1->V[i1].X - m_pTriangle1->V[i2].X;
        fSpeed = vec2fD.Dot(vec2fW);

        ComputeTwo(tempCfg1, m_pTriangle1->V, vec2fD, i0, i1, i2);
        ComputeThree(tempCfg0, m_pTriangle0->V, vec2fD, m_pTriangle1->V[i1]);

        if( NoIntersect(tempCfg0, tempCfg1, fTMax, fSpeed, iSide, tempTCfg0, tempTCfg1, 
            fTFirst, fTLast) )
        {
            return false;
        }
    }

    m_fContactTime = fTFirst;

    return true;
}
//----------------------------------------------------------------------------
bool IntrTriangle2Triangle2f::Find (float fTMax, 
    const Vector2f& rVelocity0, const Vector2f& rVelocity1)
{
    // process as if V0-triangle is stationary and V1-triangle is moving
    Vector2f vec2fW = rVelocity1 - rVelocity0;
    int iSide = 0;  // 0 = NONE, -1 = LEFT, +1 = RIGHT
    float fTFirst = 0.0f;
    float fTLast = Math<float>::MAX_REAL;

    Configuration tempCfg0, tempCfg1, tempTCfg0, tempTCfg1;
    int i0, i1, i2;
    Vector2f vec2fD;
    float fSpeed;

    // process edges of V0-triangle
    for( i0 = 1, i1 = 2, i2 = 0; i2 < 3; i0 = i1, i1 = i2, i2++ )
    {
        // test axis V0[i1] + t*perp(V0[i2]-V0[i1]), perp(x, y) = (y, -x)
        vec2fD.X = m_pTriangle0->V[i2].Y - m_pTriangle0->V[i1].Y;
        vec2fD.Y = m_pTriangle0->V[i1].X - m_pTriangle0->V[i2].X;
        fSpeed = vec2fD.Dot(vec2fW);

        ComputeTwo(tempCfg0, m_pTriangle0->V, vec2fD, i0, i1, i2);
        ComputeThree(tempCfg1, m_pTriangle1->V, vec2fD, m_pTriangle0->V[i1]);

        if( NoIntersect(tempCfg0, tempCfg1, fTMax, fSpeed, iSide, tempTCfg0, tempTCfg1, 
            fTFirst, fTLast) )
        {
            return false;
        }
    }

    // process edges of V1-triangle
    for( i0 = 1, i1 = 2, i2 = 0; i2 < 3; i0 = i1, i1 = i2, i2++ )
    {
        // test axis V1[i1] + t*perp(V1[i2]-V1[i1]), perp(x, y) = (y, -x)
        vec2fD.X = m_pTriangle1->V[i2].Y - m_pTriangle1->V[i1].Y;
        vec2fD.Y = m_pTriangle1->V[i1].X - m_pTriangle1->V[i2].X;
        fSpeed = vec2fD.Dot(vec2fW);

        ComputeTwo(tempCfg1, m_pTriangle1->V, vec2fD, i0, i1, i2);
        ComputeThree(tempCfg0, m_pTriangle0->V, vec2fD, m_pTriangle1->V[i1]);

        if( NoIntersect(tempCfg0, tempCfg1, fTMax, fSpeed, iSide, tempTCfg0, tempTCfg1, 
            fTFirst, fTLast) )
        {
            return false;
        }
    }

    // move triangles to first contact
    Vector2f aMoveV0[3], aMoveV1[3];
    for( int i = 0; i < 3; i++ )
    {
        aMoveV0[i] = m_pTriangle0->V[i] + fTFirst*rVelocity0;
        aMoveV1[i] = m_pTriangle1->V[i] + fTFirst*rVelocity1;
    };

    GetIntersection(tempTCfg0, tempTCfg1, iSide, aMoveV0, aMoveV1, m_iCount, 
        m_aPoint);

    m_fContactTime = fTFirst;

    return m_iCount > 0;
}
//----------------------------------------------------------------------------
int IntrTriangle2Triangle2f::GetCount() const
{
    return m_iCount;
}
//----------------------------------------------------------------------------
const Vector2f& IntrTriangle2Triangle2f::GetPoint(int i) const
{
    SE_ASSERT( 0 <= i && i < m_iCount );

    return m_aPoint[i];
}
//----------------------------------------------------------------------------
int IntrTriangle2Triangle2f::OnWhichSide(const Vector2f aV[3], 
    const Vector2f& rP, const Vector2f& rD)
{
    // Vertices are projected to the form P+t*D.  Return value is +1 if all
    // t > 0, -1 if all t < 0, 0 otherwise, in which case the line splits the
    // triangle.

    int iPositive = 0, iNegative = 0, iZero = 0;
    for( int i = 0; i < 3; i++ )
    {
        float fT = rD.Dot(aV[i] - rP);
        if( fT > 0.0f )
        {
            iPositive++;
        }
        else if( fT < 0.0f )
        {
            iNegative++;
        }
        else
        {
            iZero++;
        }

        if( iPositive > 0 && iNegative > 0 )
        {
            return 0;
        }
    }

    return (iZero == 0 ? (iPositive > 0 ? 1 : -1) : 0);
}
//----------------------------------------------------------------------------
void IntrTriangle2Triangle2f::ClipConvexPolygonAgainstLine(
    const Vector2f& rN, float fC, int& riCount, 
    Vector2f aV[6])
{
    // The input vertices are assumed to be in counterclockwise order.  The
    // ordering is an invariant of this function.

    // test on which side of line the vertices are
    int iPositive = 0, iNegative = 0, iPIndex = -1;
    float afTest[6];
    int i;
    for( i = 0; i < riCount; i++ )
    {
        afTest[i] = rN.Dot(aV[i]) - fC;
        if( afTest[i] > 0.0f )
        {
            iPositive++;
            if( iPIndex < 0 )
            {
                iPIndex = i;
            }
        }
        else if( afTest[i] < 0.0f )
        {
            iNegative++;
        }
    }

    if( iPositive > 0 )
    {
        if( iNegative > 0 )
        {
            // line transversely intersects polygon
            Vector2f aCV[6];
            int iCCount = 0, iCur, iPrv;
            float fT;

            if( iPIndex > 0 )
            {
                // first clip vertex on line
                iCur = iPIndex;
                iPrv = iCur - 1;
                fT = afTest[iCur]/(afTest[iCur] - afTest[iPrv]);
                aCV[iCCount++] = aV[iCur] + fT*(aV[iPrv] - aV[iCur]);

                // vertices on positive side of line
                while( iCur < riCount && afTest[iCur] > 0.0f )
                {
                    aCV[iCCount++] = aV[iCur++];
                }

                // last clip vertex on line
                if( iCur < riCount )
                {
                    iPrv = iCur - 1;
                }
                else
                {
                    iCur = 0;
                    iPrv = riCount - 1;
                }
                fT = afTest[iCur]/(afTest[iCur] - afTest[iPrv]);
                aCV[iCCount++] = aV[iCur] + fT*(aV[iPrv] - aV[iCur]);
            }
            else  // iPIndex is 0
            {
                // vertices on positive side of line
                iCur = 0;
                while( iCur < riCount && afTest[iCur] > 0.0f )
                {
                    aCV[iCCount++] = aV[iCur++];
                }

                // last clip vertex on line
                iPrv = iCur - 1;
                fT = afTest[iCur]/(afTest[iCur] - afTest[iPrv]);
                aCV[iCCount++] = aV[iCur] + fT*(aV[iPrv] - aV[iCur]);

                // skip vertices on negative side
                while( iCur < riCount && afTest[iCur] <= 0.0f )
                {
                    iCur++;
                }

                // first clip vertex on line
                if( iCur < riCount )
                {
                    iPrv = iCur - 1;
                    fT = afTest[iCur]/(afTest[iCur] - afTest[iPrv]);
                    aCV[iCCount++] = aV[iCur] + fT*(aV[iPrv] - aV[iCur]);

                    // vertices on positive side of line
                    while( iCur < riCount && afTest[iCur] > 0.0f )
                    {
                        aCV[iCCount++] = aV[iCur++];
                    }
                }
                else
                {
                    // iCur = 0
                    iPrv = riCount - 1;
                    fT = afTest[0]/(afTest[0] - afTest[iPrv]);
                    aCV[iCCount++] = aV[0] + fT*(aV[iPrv] - aV[0]);
                }
            }

            riCount = iCCount;
            size_t uiSize = iCCount * sizeof(Vector2f);
            System::SE_Memcpy(aV, uiSize, aCV, uiSize);
        }
        // else polygon fully on positive side of line, nothing to do
    }
    else
    {
        // polygon does not intersect positive side of line, clip all
        riCount = 0;
    }
}
//----------------------------------------------------------------------------
void IntrTriangle2Triangle2f::ComputeTwo(Configuration& rCfg, 
    const Vector2f aV[3], const Vector2f& rD, int i0, int i1, 
    int i2)
{
    rCfg.Map = M12;
    rCfg.Index[0] = i0;
    rCfg.Index[1] = i1;
    rCfg.Index[2] = i2;
    rCfg.Min = rD.Dot(aV[i0] - aV[i1]);
    rCfg.Max = 0.0f;
}
//----------------------------------------------------------------------------
void IntrTriangle2Triangle2f::ComputeThree(Configuration& rCfg, 
    const Vector2f aV[3], const Vector2f& rD, 
    const Vector2f& rP)
{
    float fD0 = rD.Dot(aV[0] - rP);
    float fD1 = rD.Dot(aV[1] - rP);
    float fD2 = rD.Dot(aV[2] - rP);

    // Make sure that m_aiIndex[...] is an even permutation of (0, 1, 2)
    // whenever the map value is M12 or M21.  This is needed to guarantee
    // the intersection of overlapping edges is properly computed.

    if( fD0 <= fD1 )
    {
        if( fD1 <= fD2 )  // d0 <= d1 <= d2
        {
            if( fD0 != fD1 )
            {
                rCfg.Map = (fD1 != fD2 ? M11 : M12);
            }
            else
            {
                rCfg.Map = M21;
            }

            rCfg.Index[0] = 0;
            rCfg.Index[1] = 1;
            rCfg.Index[2] = 2;
            rCfg.Min = fD0;
            rCfg.Max = fD2;
        }
        else if( fD0 <= fD2 )  // d0 <= d2 < d1
        {
            if( fD0 != fD2 )
            {
                rCfg.Map = M11;
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
        else  // d2 < d0 <= d1
        {
            rCfg.Map = (fD0 != fD1 ? M12 : M11);
            rCfg.Index[0] = 2;
            rCfg.Index[1] = 0;
            rCfg.Index[2] = 1;
            rCfg.Min = fD2;
            rCfg.Max = fD1;
        }
    }
    else
    {
        if( fD2 <= fD1 )  // d2 <= d1 < d0
        {
            if( fD2 != fD1 )
            {
                rCfg.Map = M11;
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
        else if( fD2 <= fD0 )  // d1 < d2 <= d0
        {
            rCfg.Map = (fD2 != fD0 ? M11 : M12);
            rCfg.Index[0] = 1;
            rCfg.Index[1] = 2;
            rCfg.Index[2] = 0;
            rCfg.Min = fD1;
            rCfg.Max = fD0;
        }
        else  // d1 < d0 < d2
        {
            rCfg.Map = M11;
            rCfg.Index[0] = 1;
            rCfg.Index[1] = 0;
            rCfg.Index[2] = 2;
            rCfg.Min = fD1;
            rCfg.Max = fD2;
        }
    }
}
//----------------------------------------------------------------------------
bool IntrTriangle2Triangle2f::NoIntersect(
    const Configuration& rCfg0, const Configuration& rCfg1, float fTMax, 
    float fSpeed, int& riSide, Configuration& rTCfg0, Configuration& rTCfg1, 
    float& rfTFirst, float& rfTLast)
{
    float fInvSpeed, fT;

    if( rCfg1.Max < rCfg0.Min )
    {
        // V1-interval initially on left of V0-interval
        if( fSpeed <= 0.0f )
        {
            return true;  // intervals moving apart
        }

        // update first time
        fInvSpeed = 1.0f / fSpeed;
        fT = (rCfg0.Min - rCfg1.Max)*fInvSpeed;
        if( fT > rfTFirst )
        {
            rfTFirst = fT;
            riSide = -1;
            rTCfg0 = rCfg0;
            rTCfg1 = rCfg1;
        }

        // test for exceedance of time interval
        if( rfTFirst > fTMax )
        {
            return true;
        }

        // update last time
        fT = (rCfg0.Max - rCfg1.Min)*fInvSpeed;
        if( fT < rfTLast )
        {
            rfTLast = fT;
        }

        // test for separation
        if( rfTFirst > rfTLast )
        {
            return true;
        }
    }
    else if( rCfg0.Max < rCfg1.Min )
    {
        // V1-interval initially on right of V0-interval
        if( fSpeed >= 0.0f )
        {
            return true;  // intervals moving apart
        }

        // update first time
        fInvSpeed = 1.0f / fSpeed;
        fT = (rCfg0.Max - rCfg1.Min)*fInvSpeed;
        if( fT > rfTFirst )
        {
            rfTFirst = fT;
            riSide = 1;
            rTCfg0 = rCfg0;
            rTCfg1 = rCfg1;
        }

        // test for exceedance of time interval
        if( rfTFirst > fTMax )
        {
            return true;
        }

        // update last time
        fT = (rCfg0.Min - rCfg1.Max)*fInvSpeed;
        if( fT < rfTLast )
        {
            rfTLast = fT;
        }

        // test for separation
        if( rfTFirst > rfTLast )
        {
            return true;
        }
    }
    else
    {
        // V0-interval and V1-interval initially overlap
        if( fSpeed > 0.0f )
        {
            // update last time
            fInvSpeed = 1.0f / fSpeed;
            fT = (rCfg0.Max - rCfg1.Min)*fInvSpeed;
            if( fT < rfTLast )
            {
                rfTLast = fT;
            }

            // test for separation
            if( rfTFirst > rfTLast )
            {
                return true;
            }
        }
        else if( fSpeed < 0.0f )
        {
            // update last time
            fInvSpeed = 1.0f / fSpeed;
            fT = (rCfg0.Min - rCfg1.Max)*fInvSpeed;
            if( fT < rfTLast )
            {
                rfTLast = fT;
            }

            // test for separation
            if( rfTFirst > rfTLast )
            {
                return true;
            }
        }
    }

    return false;
}
//----------------------------------------------------------------------------
void IntrTriangle2Triangle2f::GetIntersection(
    const Configuration& rCfg0, const Configuration& rCfg1, int iSide, 
    const Vector2f aV0[3], const Vector2f aV1[3], int& riCount, 
    Vector2f aVertex[6])
{
    Vector2f vec2fEdge, vec2fDiff;
    const Vector2f* pOrigin;
    float fInvEdE, fMin, fMax;
    int i;

    if( iSide == 1 )  // V1-interval contacts V0-interval on right
    {
        if( rCfg0.Map == M21 || rCfg0.Map == M11 )
        {
            riCount = 1;
            aVertex[0] = aV0[rCfg0.Index[2]];
        }
        else if( rCfg1.Map == M12 || rCfg1.Map == M11 )
        {
            riCount = 1;
            aVertex[0] = aV1[rCfg1.Index[0]];
        }
        else  // rCfg0.Map == M12 && rCfg1.Map == M21 (edge overlap)
        {
            pOrigin = &aV0[rCfg0.Index[1]];
            vec2fEdge = aV0[rCfg0.Index[2]] - *pOrigin;
            fInvEdE = 1.0f / vec2fEdge.Dot(vec2fEdge);
            vec2fDiff = aV1[rCfg1.Index[1]] - *pOrigin;
            fMin = vec2fEdge.Dot(vec2fDiff) * fInvEdE;
            vec2fDiff = aV1[rCfg1.Index[0]] - *pOrigin;
            fMax = vec2fEdge.Dot(vec2fDiff) * fInvEdE;
            SE_ASSERT( fMin <= fMax );

            Intersector1<float> tempIntr(0.0f, 1.0f, fMin, fMax);
            riCount = tempIntr.GetCount();
            SE_ASSERT( riCount > 0 );

            for( i = 0; i < riCount; i++ )
            {
                aVertex[i] = *pOrigin + tempIntr.GetOverlap(i)*vec2fEdge;
            }
        }
    }
    else if( iSide == -1 )  // V1-interval contacts V0-interval on left
    {
        if( rCfg1.Map == M21 || rCfg1.Map == M11 )
        {
            riCount = 1;
            aVertex[0] = aV1[rCfg1.Index[2]];
        }
        else if( rCfg0.Map == M12 || rCfg0.Map == M11 )
        {
            riCount = 1;
            aVertex[0] = aV0[rCfg0.Index[0]];
        }
        else  // rCfg1.Map == M12 && rCfg0.Map == M21 (edge overlap)
        {
            pOrigin = &aV1[rCfg1.Index[1]];
            vec2fEdge = aV1[rCfg1.Index[2]] - *pOrigin;
            fInvEdE = 1.0f / vec2fEdge.Dot(vec2fEdge);
            vec2fDiff = aV0[rCfg0.Index[1]] - *pOrigin;
            fMin = vec2fEdge.Dot(vec2fDiff) * fInvEdE;
            vec2fDiff = aV0[rCfg0.Index[0]] - *pOrigin;
            fMax = vec2fEdge.Dot(vec2fDiff) * fInvEdE;
            SE_ASSERT( fMin <= fMax );

            Intersector1<float> tempIntr(0.0f, 1.0f, fMin, fMax);
            riCount = tempIntr.GetCount();
            SE_ASSERT( riCount > 0 );

            for( i = 0; i < riCount; i++ )
            {
                aVertex[i] = *pOrigin + tempIntr.GetOverlap(i)*vec2fEdge;
            }
        }
    }
    else  // triangles were initially intersecting
    {
        Triangle2f tempTri0(aV0), tempTri1(aV1);
        IntrTriangle2Triangle2f tempIntr(tempTri0, tempTri1);
        tempIntr.Find();
        riCount = tempIntr.GetCount();
        for( i = 0; i < riCount; i++ )
        {
            aVertex[i] = tempIntr.GetPoint(i);
        }
    }
}
//----------------------------------------------------------------------------