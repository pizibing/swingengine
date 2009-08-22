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
#include "SEIntrLine3Box3.h"

using namespace Swing;

//----------------------------------------------------------------------------
IntrLine3Box3f::IntrLine3Box3f(const Line3f& rLine, const Box3f& rBox)
    :
    m_pLine(&rLine),
    m_pBox(&rBox)
{
}
//----------------------------------------------------------------------------
const Line3f& IntrLine3Box3f::GetLine() const
{
    return *m_pLine;
}
//----------------------------------------------------------------------------
const Box3f& IntrLine3Box3f::GetBox() const
{
    return *m_pBox;
}
//----------------------------------------------------------------------------
bool IntrLine3Box3f::Test()
{
    float afAWdU[3], afAWxDdU[3], fRhs;

    Vector3f vec3fDiff = m_pLine->Origin - m_pBox->Center;
    Vector3f vec3fWxD = m_pLine->Direction.Cross(vec3fDiff);

    afAWdU[1] = Math<float>::FAbs(m_pLine->Direction.Dot(m_pBox->Axis[1]));
    afAWdU[2] = Math<float>::FAbs(m_pLine->Direction.Dot(m_pBox->Axis[2]));
    afAWxDdU[0] = Math<float>::FAbs(vec3fWxD.Dot(m_pBox->Axis[0]));
    fRhs = m_pBox->Extent[1]*afAWdU[2] + m_pBox->Extent[2]*afAWdU[1];
    if( afAWxDdU[0] > fRhs )
    {
        return false;
    }

    afAWdU[0] = Math<float>::FAbs(m_pLine->Direction.Dot(m_pBox->Axis[0]));
    afAWxDdU[1] = Math<float>::FAbs(vec3fWxD.Dot(m_pBox->Axis[1]));
    fRhs = m_pBox->Extent[0]*afAWdU[2] + m_pBox->Extent[2]*afAWdU[0];
    if( afAWxDdU[1] > fRhs )
    {
        return false;
    }

    afAWxDdU[2] = Math<float>::FAbs(vec3fWxD.Dot(m_pBox->Axis[2]));
    fRhs = m_pBox->Extent[0]*afAWdU[1] + m_pBox->Extent[1]*afAWdU[0];
    if( afAWxDdU[2] > fRhs )
    {
        return false;
    }

    return true;
}
//----------------------------------------------------------------------------
bool IntrLine3Box3f::Find()
{
    float fT0 = -Math<float>::MAX_REAL, fT1 = Math<float>::MAX_REAL;

    return DoClipping(fT0, fT1, m_pLine->Origin, m_pLine->Direction, *m_pBox,
        true, m_iCount, m_aPoint, m_iIntersectionType);
}
//----------------------------------------------------------------------------
int IntrLine3Box3f::GetCount() const
{
    return m_iCount;
}
//----------------------------------------------------------------------------
const Vector3f& IntrLine3Box3f::GetPoint(int i) const
{
    SE_ASSERT( 0 <= i && i < m_iCount );

    return m_aPoint[i];
}
//----------------------------------------------------------------------------
bool IntrLine3Box3f::DoClipping(float fT0, float fT1, const Vector3f& rOrigin, 
    const Vector3f& rDirection, const Box3f& rBox, bool bSolid, int& riCount,
    Vector3f aPoint[2], int& riIntrType)
{
    SE_ASSERT( fT0 < fT1 );

    // 把linear component变换到box坐标体系下.
    Vector3f vec3fDiff = rOrigin - rBox.Center;
    Vector3f vec3fBOrigin(
        vec3fDiff.Dot(rBox.Axis[0]),
        vec3fDiff.Dot(rBox.Axis[1]),
        vec3fDiff.Dot(rBox.Axis[2])
    );
    Vector3f vec3fBDirection(
        rDirection.Dot(rBox.Axis[0]),
        rDirection.Dot(rBox.Axis[1]),
        rDirection.Dot(rBox.Axis[2])
    );

    float fSaveT0 = fT0, fSaveT1 = fT1;
    bool bNotAllClipped =
        Clip(+vec3fBDirection.X, -vec3fBOrigin.X-rBox.Extent[0], fT0, fT1) &&
        Clip(-vec3fBDirection.X, +vec3fBOrigin.X-rBox.Extent[0], fT0, fT1) &&
        Clip(+vec3fBDirection.Y, -vec3fBOrigin.Y-rBox.Extent[1], fT0, fT1) &&
        Clip(-vec3fBDirection.Y, +vec3fBOrigin.Y-rBox.Extent[1], fT0, fT1) &&
        Clip(+vec3fBDirection.Z, -vec3fBOrigin.Z-rBox.Extent[2], fT0, fT1) &&
        Clip(-vec3fBDirection.Z, +vec3fBOrigin.Z-rBox.Extent[2], fT0, fT1);

    if( bNotAllClipped && (bSolid || fT0 != fSaveT0 || fT1 != fSaveT1) )
    {
        if( fT1 > fT0 )
        {
            riIntrType = IT_SEGMENT;
            riCount = 2;
            aPoint[0] = rOrigin + fT0*rDirection;
            aPoint[1] = rOrigin + fT1*rDirection;
        }
        else
        {
            riIntrType = IT_POINT;
            riCount = 1;
            aPoint[0] = rOrigin + fT0*rDirection;
        }
    }
    else
    {
        riCount = 0;
        riIntrType = IT_EMPTY;
    }

    return riIntrType != IT_EMPTY;
}
//----------------------------------------------------------------------------
bool IntrLine3Box3f::Clip(float fDenom, float fNumer, float& rfT0, 
    float& rfT1)
{
    // 如果线段与当前测试平面相交或在平面正半空间,则表明裁减成功,返回true.
    // 否则返回false,表示线段整个被平面剔除掉了.

    if( fDenom > 0.0f )
    {
        if( fNumer > fDenom*rfT1 )
        {
            return false;
        }
        if( fNumer > fDenom*rfT0 )
        {
            rfT0 = fNumer / fDenom;
        }

        return true;
    }
    else if( fDenom < 0.0f )
    {
        if( fNumer > fDenom * rfT0 )
        {
            return false;
        }
        if( fNumer > fDenom * rfT1 )
        {
            rfT1 = fNumer / fDenom;
        }

        return true;
    }
    else
    {
        return fNumer <= 0.0f;
    }
}
//----------------------------------------------------------------------------
