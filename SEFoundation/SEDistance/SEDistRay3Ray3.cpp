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
#include "SEDistRay3Ray3.h"

using namespace Swing;

//----------------------------------------------------------------------------
DistRay3Ray3f::DistRay3Ray3f(const Ray3f& rRay0, const Ray3f& rRay1)
    :
    m_pRay0(&rRay0),
    m_pRay1(&rRay1)
{
}
//----------------------------------------------------------------------------
const Ray3f& DistRay3Ray3f::GetRay0() const
{
    return *m_pRay0;
}
//----------------------------------------------------------------------------
const Ray3f& DistRay3Ray3f::GetRay1() const
{
    return *m_pRay1;
}
//----------------------------------------------------------------------------
float DistRay3Ray3f::Get()
{
    float fSqrDist = GetSquared();

    return Math<float>::Sqrt(fSqrDist);
}
//----------------------------------------------------------------------------
float DistRay3Ray3f::GetSquared()
{
    Vector3f vec3fDiff = m_pRay0->Origin - m_pRay1->Origin;
    float fA01 = -m_pRay0->Direction.Dot(m_pRay1->Direction);
    float fB0 = vec3fDiff.Dot(m_pRay0->Direction);
    float fC = vec3fDiff.GetSquaredLength();
    float fDet = Math<float>::FAbs(1.0f - fA01*fA01);
    float fB1, fS0, fS1, fSqrDist;

    if( fDet >= Math<float>::ZERO_TOLERANCE )
    {
        // 两射线不平行.
        fB1 = -vec3fDiff.Dot(m_pRay1->Direction);
        fS0 = fA01*fB1 - fB0;
        fS1 = fA01*fB0 - fB1;

        if( fS0 >= 0.0f )
        {
            if( fS1 >= 0.0f )  // region 0 (interior)
            {
                // 最近点是两射线线上点.
                float fInvDet = 1.0f / fDet;
                fS0 *= fInvDet;
                fS1 *= fInvDet;
                fSqrDist = fS0*(fS0 + fA01*fS1 + 2.0f*fB0) +
                    fS1*(fA01*fS0 + fS1 + 2.0f*fB1) + fC;
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
                fB1 = -vec3fDiff.Dot(m_pRay1->Direction);
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
    m_fRay0Parameter = fS0;
    m_fRay1Parameter = fS1;

    return Math<float>::FAbs(fSqrDist);
}
//----------------------------------------------------------------------------
float DistRay3Ray3f::Get(float fT, const Vector3f& rVelocity0,
    const Vector3f& rVelocity1)
{
    Vector3f vec3fMOrigin0 = m_pRay0->Origin + fT*rVelocity0;
    Vector3f vec3fMOrigin1 = m_pRay1->Origin + fT*rVelocity1;
    Ray3f tempMRay0(vec3fMOrigin0, m_pRay0->Direction);
    Ray3f tempMRay1(vec3fMOrigin1, m_pRay1->Direction);

    return DistRay3Ray3f(tempMRay0, tempMRay1).Get();
}
//----------------------------------------------------------------------------
float DistRay3Ray3f::GetSquared(float fT, const Vector3f& rVelocity0, 
    const Vector3f& rVelocity1)
{
    Vector3f vec3fMOrigin0 = m_pRay0->Origin + fT*rVelocity0;
    Vector3f vec3fMOrigin1 = m_pRay1->Origin + fT*rVelocity1;
    Ray3f tempMRay0(vec3fMOrigin0, m_pRay0->Direction);
    Ray3f tempMRay1(vec3fMOrigin1, m_pRay1->Direction);

    return DistRay3Ray3f(tempMRay0, tempMRay1).GetSquared();
}
//----------------------------------------------------------------------------
float DistRay3Ray3f::GetRay0Parameter() const
{
    return m_fRay0Parameter;
}
//----------------------------------------------------------------------------
float DistRay3Ray3f::GetRay1Parameter() const
{
    return m_fRay1Parameter;
}
//----------------------------------------------------------------------------
