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
#include "SEIntrRay3Sphere3.h"

using namespace Swing;

//----------------------------------------------------------------------------
IntrRay3Sphere3f::IntrRay3Sphere3f(const SERay3f& rRay, const SESphere3f& rSphere)
    :
    m_pRay(&rRay),
    m_pSphere(&rSphere)
{
    m_iCount = 0;
}
//----------------------------------------------------------------------------
const SERay3f& IntrRay3Sphere3f::GetRay() const
{
    return *m_pRay;
}
//----------------------------------------------------------------------------
const SESphere3f& IntrRay3Sphere3f::GetSphere() const
{
    return *m_pSphere;
}
//----------------------------------------------------------------------------
bool IntrRay3Sphere3f::Test()
{
    SEVector3f vec3fDiff = m_pRay->Origin - m_pSphere->Center;
    float fA0 = vec3fDiff.Dot(vec3fDiff) - m_pSphere->Radius*m_pSphere->Radius;
    if( fA0 <= 0.0f )
    {
        // P点在球内.
        return true;
    }
    // else: P点在球外.

    float fA1 = m_pRay->Direction.Dot(vec3fDiff);
    if( fA1 >= 0.0f )
    {
        return false;
    }

    // 如果判别式非负,则二次曲线有实根.
    return fA1*fA1 >= fA0;
}
//----------------------------------------------------------------------------
bool IntrRay3Sphere3f::Find()
{
    SEVector3f vec3fDiff = m_pRay->Origin - m_pSphere->Center;
    float fA0 = vec3fDiff.Dot(vec3fDiff) - m_pSphere->Radius*m_pSphere->Radius;
    float fA1, fDiscr, fRoot;
    if( fA0 <= 0.0f )
    {
        // P点在球内.
        m_iCount = 1;
        fA1 = m_pRay->Direction.Dot(vec3fDiff);
        fDiscr = fA1*fA1 - fA0;
        fRoot = SEMathf::Sqrt(fDiscr);
        m_afRayT[0] = -fA1 + fRoot;
        m_aPoint[0] = m_pRay->Origin + m_afRayT[0]*m_pRay->Direction;

        return true;
    }
    // else: P点在球外.

    fA1 = m_pRay->Direction.Dot(vec3fDiff);
    if( fA1 >= 0.0f )
    {
        m_iCount = 0;

        return false;
    }

    fDiscr = fA1*fA1 - fA0;
    if( fDiscr < 0.0f )
    {
        m_iCount = 0;
    }
    else if( fDiscr >= SEMathf::ZERO_TOLERANCE )
    {
        fRoot = SEMathf::Sqrt(fDiscr);
        m_afRayT[0] = -fA1 - fRoot;
        m_afRayT[1] = -fA1 + fRoot;
        m_aPoint[0] = m_pRay->Origin + m_afRayT[0]*m_pRay->Direction;
        m_aPoint[1] = m_pRay->Origin + m_afRayT[1]*m_pRay->Direction;
        m_iCount = 2;
    }
    else
    {
        m_afRayT[0] = -fA1;
        m_aPoint[0] = m_pRay->Origin + m_afRayT[0]*m_pRay->Direction;
        m_iCount = 1;
    }

    return m_iCount > 0;
}
//----------------------------------------------------------------------------
int IntrRay3Sphere3f::GetCount() const
{
    return m_iCount;
}
//----------------------------------------------------------------------------
const SEVector3f& IntrRay3Sphere3f::GetPoint(int i) const
{
    SE_ASSERT( 0 <= i && i < m_iCount );

    return m_aPoint[i];
}
//----------------------------------------------------------------------------
float IntrRay3Sphere3f::GetRayT(int i) const
{
    SE_ASSERT( 0 <= i && i < m_iCount );

    return m_afRayT[i];
}
//----------------------------------------------------------------------------