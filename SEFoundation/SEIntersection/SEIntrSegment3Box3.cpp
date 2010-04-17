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
#include "SEIntrSegment3Box3.h"
#include "SEIntrLine3Box3.h"

using namespace Swing;

//----------------------------------------------------------------------------
IntrSegment3Box3f::IntrSegment3Box3f(const SESegment3f& rSegment,
    const SEBox3f& rBox, bool bSolid)
    :
    m_pSegment(&rSegment),
    m_pBox(&rBox)
{
    m_bSolid = bSolid;
}
//----------------------------------------------------------------------------
const SESegment3f& IntrSegment3Box3f::GetSegment() const
{
    return *m_pSegment;
}
//----------------------------------------------------------------------------
const SEBox3f& IntrSegment3Box3f::GetBox() const
{
    return *m_pBox;
}
//----------------------------------------------------------------------------
bool IntrSegment3Box3f::Test()
{
    float afAWdU[3], afADdU[3], afAWxDdU[3], fRhs;

    SEVector3f vec3fDiff = m_pSegment->Origin - m_pBox->Center;

    afAWdU[0] = SEMath<float>::FAbs(m_pSegment->Direction.Dot(m_pBox->Axis[0]));
    afADdU[0] = SEMath<float>::FAbs(vec3fDiff.Dot(m_pBox->Axis[0]));
    fRhs = m_pBox->Extent[0] + m_pSegment->Extent*afAWdU[0];
    if( afADdU[0] > fRhs )
    {
        return false;
    }

    afAWdU[1] = SEMath<float>::FAbs(m_pSegment->Direction.Dot(m_pBox->Axis[1]));
    afADdU[1] = SEMath<float>::FAbs(vec3fDiff.Dot(m_pBox->Axis[1]));
    fRhs = m_pBox->Extent[1] + m_pSegment->Extent*afAWdU[1];
    if( afADdU[1] > fRhs )
    {
        return false;
    }

    afAWdU[2] = SEMath<float>::FAbs(m_pSegment->Direction.Dot(m_pBox->Axis[2]));
    afADdU[2] = SEMath<float>::FAbs(vec3fDiff.Dot(m_pBox->Axis[2]));
    fRhs = m_pBox->Extent[2] + m_pSegment->Extent*afAWdU[2];
    if( afADdU[2] > fRhs )
    {
        return false;
    }

    SEVector3f vec3fWxD = m_pSegment->Direction.Cross(vec3fDiff);

    afAWxDdU[0] = SEMath<float>::FAbs(vec3fWxD.Dot(m_pBox->Axis[0]));
    fRhs = m_pBox->Extent[1]*afAWdU[2] + m_pBox->Extent[2]*afAWdU[1];
    if( afAWxDdU[0] > fRhs )
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
bool IntrSegment3Box3f::Find()
{
    float fT0 = -m_pSegment->Extent, fT1 = m_pSegment->Extent;

    return IntrLine3Box3f::DoClipping(fT0, fT1, m_pSegment->Origin,
        m_pSegment->Direction, *m_pBox, m_bSolid, m_iCount, m_aPoint,
        m_iIntersectionType);
}
//----------------------------------------------------------------------------
int IntrSegment3Box3f::GetCount() const
{
    return m_iCount;
}
//----------------------------------------------------------------------------
const SEVector3f& IntrSegment3Box3f::GetPoint(int i) const
{
    SE_ASSERT( 0 <= i && i < m_iCount );

    return m_aPoint[i];
}
//----------------------------------------------------------------------------
