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
#include "SEIntrRay3Box3.h"

using namespace Swing;

//----------------------------------------------------------------------------
IntrRay3Box3f::IntrRay3Box3f(const SERay3f& rRay, const SEBox3f& rBox)
    :
    m_pRay(&rRay),
    m_pBox(&rBox)
{
}
//----------------------------------------------------------------------------
const SERay3f& IntrRay3Box3f::GetRay() const
{
    return *m_pRay;
}
//----------------------------------------------------------------------------
const SEBox3f& IntrRay3Box3f::GetBox() const
{
    return *m_pBox;
}
//----------------------------------------------------------------------------
bool IntrRay3Box3f::Test()
{
    float afWdU[3], afAWdU[3], afDdU[3], afADdU[3], afAWxDdU[3], fRhs;

    SEVector3f vec3fDiff = m_pRay->Origin - m_pBox->Center;

    afWdU[0] = m_pRay->Direction.Dot(m_pBox->Axis[0]);
    afAWdU[0] = SEMath<float>::FAbs(afWdU[0]);
    afDdU[0] = vec3fDiff.Dot(m_pBox->Axis[0]);
    afADdU[0] = SEMath<float>::FAbs(afDdU[0]);
    if( afADdU[0] > m_pBox->Extent[0] && afDdU[0]*afWdU[0] >= 0.0f )
    {
        return false;
    }

    afWdU[1] = m_pRay->Direction.Dot(m_pBox->Axis[1]);
    afAWdU[1] = SEMath<float>::FAbs(afWdU[1]);
    afDdU[1] = vec3fDiff.Dot(m_pBox->Axis[1]);
    afADdU[1] = SEMath<float>::FAbs(afDdU[1]);
    if( afADdU[1] > m_pBox->Extent[1] && afDdU[1]*afWdU[1] >= 0.0f )
    {
        return false;
    }

    afWdU[2] = m_pRay->Direction.Dot(m_pBox->Axis[2]);
    afAWdU[2] = SEMath<float>::FAbs(afWdU[2]);
    afDdU[2] = vec3fDiff.Dot(m_pBox->Axis[2]);
    afADdU[2] = SEMath<float>::FAbs(afDdU[2]);
    if( afADdU[2] > m_pBox->Extent[2] && afDdU[2]*afWdU[2] >= 0.0f )
    {
        return false;
    }

    SEVector3f vec3fWxD = m_pRay->Direction.Cross(vec3fDiff);

    afAWxDdU[0] = SEMath<float>::FAbs(vec3fWxD.Dot(m_pBox->Axis[0]));
    fRhs = m_pBox->Extent[1]*afAWdU[2] + m_pBox->Extent[2]*afAWdU[1];
    if( afAWxDdU[0] > fRhs)
    {
        return false;
    }

    afAWxDdU[1] = SEMath<float>::FAbs(vec3fWxD.Dot(m_pBox->Axis[1]));
    fRhs = m_pBox->Extent[0]*afAWdU[2] + m_pBox->Extent[2]*afAWdU[0];
    if( afAWxDdU[1] > fRhs )
    {
        return false;
    }

    afAWxDdU[2] = SEMath<float>::FAbs(vec3fWxD.Dot(m_pBox->Axis[2]));
    fRhs = m_pBox->Extent[0]*afAWdU[1] + m_pBox->Extent[1]*afAWdU[0];
    if( afAWxDdU[2] > fRhs )
    {
        return false;
    }

    return true;
}
//----------------------------------------------------------------------------
bool IntrRay3Box3f::Find()
{
    float fT0 = 0.0f, fT1 = SEMath<float>::MAX_REAL;

    return IntrLine3Box3f::DoClipping(fT0, fT1, m_pRay->Origin,
        m_pRay->Direction, *m_pBox, true, m_iCount, m_aPoint,
        m_iIntersectionType);
}
//----------------------------------------------------------------------------
int IntrRay3Box3f::GetCount() const
{
    return m_iCount;
}
//----------------------------------------------------------------------------
const SEVector3f& IntrRay3Box3f::GetPoint(int i) const
{
    SE_ASSERT( 0 <= i && i < m_iCount );

    return m_aPoint[i];
}
//----------------------------------------------------------------------------
