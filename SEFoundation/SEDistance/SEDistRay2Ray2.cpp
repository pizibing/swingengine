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
#include "SEDistRay2Ray2.h"

using namespace Swing;

//----------------------------------------------------------------------------
DistRay2Ray2f::DistRay2Ray2f(const SERay2f& rRay0, const SERay2f& rRay1)
    :
    m_pRay0(&rRay0),
    m_pRay1(&rRay1)
{
}
//----------------------------------------------------------------------------
const SERay2f& DistRay2Ray2f::GetRay0() const
{
    return *m_pRay0;
}
//----------------------------------------------------------------------------
const SERay2f& DistRay2Ray2f::GetRay1() const
{
    return *m_pRay1;
}
//----------------------------------------------------------------------------
float DistRay2Ray2f::Get()
{
    float fSqrDist = GetSquared();

    return SEMath<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float DistRay2Ray2f::GetSquared()
{
    SEVector2f vec2fDiff = m_pRay0->Origin - m_pRay1->Origin;
    float fA01 = -m_pRay0->Direction.Dot(m_pRay1->Direction);
    float fB0 = vec2fDiff.Dot(m_pRay0->Direction);
    float fC = vec2fDiff.GetSquaredLength();
    float fDet = SEMath<float>::FAbs(1.0f - fA01*fA01);
    float fB1, fS0, fS1, fSqrDist;

    if( fDet >= SEMath<float>::ZERO_TOLERANCE )
    {
        // 射线不平行.
        fB1 = -vec2fDiff.Dot(m_pRay1->Direction);
        fS0 = fA01*fB1-fB0;
        fS1 = fA01*fB0-fB1;

        if( fS0 >= 0.0f )
        {
            if( fS1 >= 0.0f )  // region 0 (interior)
            {
                // 最近点是两射线线上点.
                float fInvDet = 1.0f / fDet;
                fS0 *= fInvDet;
                fS1 *= fInvDet;
                fSqrDist = 0.0f;
            }
            else  // region 3 (side)
            {
                fS1 = 0.0f;
                if( fB0 >= 0.0f )
                {
                    fS0 = 0.0f;
                    fSqrDist = fC;
                }
                else
                {
                    fS0 = -fB0;
                    fSqrDist = fB0*fS0 + fC;
                }
            }
        }
        else
        {
            if( fS1 >= 0.0f )  // region 1 (side)
            {
                fS0 = 0.0f;
                if( fB1 >= 0.0f )
                {
                    fS1 = 0.0f;
                    fSqrDist = fC;
                }
                else
                {
                    fS1 = -fB1;
                    fSqrDist = fB1*fS1 + fC;
                }
            }
            else  // region 2 (corner)
            {
                if( fB0 < 0.0f )
                {
                    fS0 = -fB0;
                    fS1 = 0.0f;
                    fSqrDist = fB0*fS0 + fC;
                }
                else
                {
                    fS0 = 0.0f;
                    if( fB1 >= 0.0f )
                    {
                        fS1 = 0.0f;
                        fSqrDist = fC;
                    }
                    else
                    {
                        fS1 = -fB1;
                        fSqrDist = fB1*fS1 + fC;
                    }
                }
            }
        }
    }
    else
    {
        // 两射线平行.
        if( fA01 > 0.0f )
        {
            // 方向向量的方向相反.
            fS1 = 0.0f;
            if( fB0 >= 0.0f )
            {
                fS0 = 0.0f;
                fSqrDist = fC;
            }
            else
            {
                fS0 = -fB0;
                fSqrDist = fB0*fS0 + fC;
            }
        }
        else
        {
            // 方向向量的方向相同.
            if( fB0 >= 0.0f )
            {
                fB1 = -vec2fDiff.Dot(m_pRay1->Direction);
                fS0 = 0.0f;
                fS1 = -fB1;
                fSqrDist = fB1*fS1 + fC;
            }
            else
            {
                fS0 = -fB0;
                fS1 = 0.0f;
                fSqrDist = fB0*fS0 + fC;
            }
        }
    }

    m_ClosestPoint0 = m_pRay0->Origin + fS0*m_pRay0->Direction;
    m_ClosestPoint1 = m_pRay1->Origin + fS1*m_pRay1->Direction;

    return SEMath<float>::FAbs(fSqrDist);
}
//----------------------------------------------------------------------------
float DistRay2Ray2f::Get(float fT, const SEVector2f& rVelocity0,
    const SEVector2f& rVelocity1)
{
    SEVector2f vec2fMOrigin0 = m_pRay0->Origin + fT*rVelocity0;
    SEVector2f vec2fMOrigin1 = m_pRay1->Origin + fT*rVelocity1;
    SERay2f tempMRay0(vec2fMOrigin0, m_pRay0->Direction);
    SERay2f tempMRay1(vec2fMOrigin1, m_pRay1->Direction);

    return DistRay2Ray2f(tempMRay0, tempMRay1).Get();
}
//----------------------------------------------------------------------------
float DistRay2Ray2f::GetSquared(float fT, const SEVector2f& rVelocity0, 
    const SEVector2f& rVelocity1)
{
    SEVector2f vec2fMOrigin0 = m_pRay0->Origin + fT*rVelocity0;
    SEVector2f vec2fMOrigin1 = m_pRay1->Origin + fT*rVelocity1;
    SERay2f tempMRay0(vec2fMOrigin0, m_pRay0->Direction);
    SERay2f tempMRay1(vec2fMOrigin1, m_pRay1->Direction);

    return DistRay2Ray2f(tempMRay0, tempMRay1).GetSquared();
}
//----------------------------------------------------------------------------
