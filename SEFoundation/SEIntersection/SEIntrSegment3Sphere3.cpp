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
#include "SEIntrSegment3Sphere3.h"

using namespace Swing;

//----------------------------------------------------------------------------
IntrSegment3Sphere3f::IntrSegment3Sphere3f(const Segment3f& rSegment, 
    const Sphere3f& rSphere)
    :
    m_pSegment(&rSegment),
    m_pSphere(&rSphere)
{
    m_iCount = 0;
    ZeroThreshold = Math<float>::ZERO_TOLERANCE;
}
//----------------------------------------------------------------------------
const Segment3f& IntrSegment3Sphere3f::GetSegment() const
{
    return *m_pSegment;
}
//----------------------------------------------------------------------------
const Sphere3f& IntrSegment3Sphere3f::GetSphere() const
{
    return *m_pSphere;
}
//----------------------------------------------------------------------------
bool IntrSegment3Sphere3f::Test()
{
    Vector3f vec3fDiff = m_pSegment->Origin - m_pSphere->Center;
    float fA0 = vec3fDiff.Dot(vec3fDiff) - m_pSphere->Radius*m_pSphere->Radius;
    float fA1 = m_pSegment->Direction.Dot(vec3fDiff);
    float fDiscr = fA1*fA1 - fA0;
    if( fDiscr < 0.0f )
    {
        return false;
    }

    float fTmp0 = m_pSegment->Extent*m_pSegment->Extent + fA0;
    float fTmp1 = 2.0f*fA1*m_pSegment->Extent;
    float fQM = fTmp0 - fTmp1;
    float fQP = fTmp0 + fTmp1;
    if( fQM*fQP <= 0.0f )
    {
        return true;
    }

    return fQM > 0.0f && Math<float>::FAbs(fA1) < m_pSegment->Extent;
}
//----------------------------------------------------------------------------
bool IntrSegment3Sphere3f::Find()
{
    // 待检查.
    // 线段端点在球上的情况过于复杂.

    Vector3f vec3fDiff = m_pSegment->Origin - m_pSphere->Center;
    float fA0 = vec3fDiff.Dot(vec3fDiff) - m_pSphere->Radius*m_pSphere->Radius;
    float fA1 = m_pSegment->Direction.Dot(vec3fDiff);
    float fDiscr = fA1*fA1 - fA0;
    if( fDiscr < 0.0f )
    {
        // 判别式小于零,线段所在直线与球没有交点.
        m_iCount = 0;

        return false;
    }

    float fTmp0 = m_pSegment->Extent*m_pSegment->Extent + fA0;
    float fTmp1 = 2.0f*fA1*m_pSegment->Extent;
    float fQM = fTmp0 - fTmp1;
    float fQP = fTmp0 + fTmp1;
    float fQMmQP = fQM*fQP;
    float fRoot;
    if( fQMmQP < 0.0f )
    {
        // 线段两端点一个在球内一个在球外,必与球有一个交点.

        fRoot = Math<float>::Sqrt(fDiscr);
        m_afSegmentT[0] = (fQM > 0.0f ? -fA1 - fRoot : -fA1 + fRoot);
        m_aPoint[0] = m_pSegment->Origin + m_afSegmentT[0] *
            m_pSegment->Direction;
        m_iCount = 1;

        return true;
    }

    if( fQMmQP == 0.0f )
    {
        // 线段两端点至少有一个在球上,至少与球有一个交点.

        if( fQM == 0.0f && fQP == 0.0f )
        {
            m_afSegmentT[0] = -m_pSegment->Extent;
            m_afSegmentT[1] = m_pSegment->Extent;
            m_aPoint[0] = m_pSegment->Origin + m_afSegmentT[0] *
                m_pSegment->Direction;
            m_aPoint[1] = m_pSegment->Origin + m_afSegmentT[1] *
                m_pSegment->Direction;
            m_iCount = 2;
        }
        else if( fQM == 0.0f )
        {
            if( fQP < 0.0f )
            {
                m_afSegmentT[0] = -m_pSegment->Extent;
                m_aPoint[0] = m_pSegment->Origin + m_afSegmentT[0] *
                    m_pSegment->Direction;
                m_iCount = 1;
            }
            else
            {
                if( fDiscr >= ZeroThreshold )
                {
                    if( fA1 < m_pSegment->Extent )
                    {
                        fRoot = Math<float>::Sqrt(fDiscr);
                        m_afSegmentT[0] = -m_pSegment->Extent;
                        m_afSegmentT[1] = -fA1 + fRoot;
                        m_aPoint[0] = m_pSegment->Origin + m_afSegmentT[0] *
                            m_pSegment->Direction;
                        m_aPoint[1] = m_pSegment->Origin + m_afSegmentT[1] *
                            m_pSegment->Direction;
                        m_iCount = 2;
                    }
                    else
                    {
                        m_afSegmentT[0] = -m_pSegment->Extent;
                        m_aPoint[0] = m_pSegment->Origin + m_afSegmentT[0] *
                            m_pSegment->Direction;
                        m_iCount = 1;
                    }
                }
                else
                {
                    m_afSegmentT[0] = -m_pSegment->Extent;
                    m_aPoint[0] = m_pSegment->Origin + m_afSegmentT[0] *
                        m_pSegment->Direction;
                    m_iCount = 1;
                }
            }
        }
        else  // fQP == 0.0f
        {
            if( fQM < 0.0f )
            {
                m_afSegmentT[0] = m_pSegment->Extent;
                m_aPoint[0] = m_pSegment->Origin + m_afSegmentT[0] *
                    m_pSegment->Direction;
                m_iCount = 1;
            }
            else
            {
                if( fDiscr >= ZeroThreshold )
                {
                    if( -fA1 < m_pSegment->Extent )
                    {
                        fRoot = Math<float>::Sqrt(fDiscr);
                        m_afSegmentT[0] = -fA1 - fRoot;
                        m_afSegmentT[1] = m_pSegment->Extent;
                        m_aPoint[0] = m_pSegment->Origin + m_afSegmentT[0] *
                            m_pSegment->Direction;
                        m_aPoint[1] = m_pSegment->Origin + m_afSegmentT[1] *
                            m_pSegment->Direction;
                        m_iCount = 2;
                    }
                    else
                    {
                        m_afSegmentT[0] = m_pSegment->Extent;
                        m_aPoint[0] = m_pSegment->Origin + m_afSegmentT[0] *
                            m_pSegment->Direction;
                        m_iCount = 1;
                    }
                }
                else
                {
                    m_afSegmentT[0] = m_pSegment->Extent;
                    m_aPoint[0] = m_pSegment->Origin + m_afSegmentT[0] *
                        m_pSegment->Direction;
                    m_iCount = 1;
                }
            }
        }

        return true;
    }

    if( fQM > 0.0f && Math<float>::FAbs(fA1) < m_pSegment->Extent )
    {
        // 线段两端点都在球外,且二次曲线极小值对应的t值在线段上.

        if( fDiscr >= ZeroThreshold )
        {
            fRoot = Math<float>::Sqrt(fDiscr);
            m_afSegmentT[0] = -fA1 - fRoot;
            m_afSegmentT[1] = -fA1 + fRoot;
            m_aPoint[0] = m_pSegment->Origin + m_afSegmentT[0] *
                m_pSegment->Direction;
            m_aPoint[1] = m_pSegment->Origin + m_afSegmentT[1] *
                m_pSegment->Direction;
            m_iCount = 2;
        }
        else
        {
            m_afSegmentT[0] = -fA1;
            m_aPoint[0] = m_pSegment->Origin + m_afSegmentT[0] *
                m_pSegment->Direction;
            m_iCount = 1;
        }
    }
    else
    {
        m_iCount = 0;
    }

    return m_iCount > 0;
}
//----------------------------------------------------------------------------
bool IntrSegment3Sphere3f::Test(float/*fTMax*/, const Vector3f&/*rVelocity0*/, 
    const Vector3f&/*rVelocity1*/)
{
    // 待实现.
    return false;
}
//----------------------------------------------------------------------------
bool IntrSegment3Sphere3f::Find(float/*fTMax*/, const Vector3f&/*rVelocity0*/, 
    const Vector3f&/*rVelocity1*/)
{
    // 待实现.
    return false;
}
//----------------------------------------------------------------------------
int IntrSegment3Sphere3f::GetCount() const
{
    return m_iCount;
}
//----------------------------------------------------------------------------
const Vector3f& IntrSegment3Sphere3f::GetPoint(int i) const
{
    SE_ASSERT( 0 <= i && i < m_iCount );

    return m_aPoint[i];
}
//----------------------------------------------------------------------------
float IntrSegment3Sphere3f::GetSegmentT(int i) const
{
    SE_ASSERT( 0 <= i && i < m_iCount );

    return m_afSegmentT[i];
}
//----------------------------------------------------------------------------
