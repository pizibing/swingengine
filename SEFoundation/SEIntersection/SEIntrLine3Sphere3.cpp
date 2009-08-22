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
#include "SEIntrLine3Sphere3.h"

using namespace Swing;

//----------------------------------------------------------------------------
IntrLine3Sphere3f::IntrLine3Sphere3f(const Line3f& rLine,
    const Sphere3f& rSphere)
    :
    m_pLine(&rLine),
    m_pSphere(&rSphere)
{
    m_iCount = 0;
}
//----------------------------------------------------------------------------
const Line3f& IntrLine3Sphere3f::GetLine() const
{
    return *m_pLine;
}
//----------------------------------------------------------------------------
const Sphere3f& IntrLine3Sphere3f::GetSphere() const
{
    return *m_pSphere;
}
//----------------------------------------------------------------------------
bool IntrLine3Sphere3f::Test()
{
    Vector3f vec3fDiff = m_pLine->Origin - m_pSphere->Center;
    float fA0 = vec3fDiff.Dot(vec3fDiff) - m_pSphere->Radius*m_pSphere->Radius;
    float fA1 = m_pLine->Direction.Dot(vec3fDiff);
    float fDiscr = fA1*fA1 - fA0;

    return fDiscr >= 0.0f;
}
//----------------------------------------------------------------------------
bool IntrLine3Sphere3f::Find ()
{
    Vector3f vec3fDiff = m_pLine->Origin - m_pSphere->Center;
    float fA0 = vec3fDiff.Dot(vec3fDiff) - m_pSphere->Radius*m_pSphere->Radius;
    float fA1 = m_pLine->Direction.Dot(vec3fDiff);
    float fDiscr = fA1*fA1 - fA0;

    if( fDiscr < 0.0f )
    {
        m_iCount = 0;
    }
    else if( fDiscr >= Math<float>::ZERO_TOLERANCE )
    {
        float fRoot = Math<float>::Sqrt(fDiscr);
        m_afLineT[0] = -fA1 - fRoot;
        m_afLineT[1] = -fA1 + fRoot;
        m_aPoint[0] = m_pLine->Origin + m_afLineT[0]*m_pLine->Direction;
        m_aPoint[1] = m_pLine->Origin + m_afLineT[1]*m_pLine->Direction;
        m_iCount = 2;
    }
    else
    {
        m_afLineT[0] = -fA1;
        m_aPoint[0] = m_pLine->Origin + m_afLineT[0]*m_pLine->Direction;
        m_iCount = 1;
    }

    return m_iCount > 0;
}
//----------------------------------------------------------------------------
int IntrLine3Sphere3f::GetCount() const
{
    return m_iCount;
}
//----------------------------------------------------------------------------
const Vector3f& IntrLine3Sphere3f::GetPoint(int i) const
{
    SE_ASSERT( 0 <= i && i < m_iCount );

    return m_aPoint[i];
}
//----------------------------------------------------------------------------
float IntrLine3Sphere3f::GetLineT(int i) const
{
    SE_ASSERT( 0 <= i && i < m_iCount );

    return m_afLineT[i];
}
//----------------------------------------------------------------------------
