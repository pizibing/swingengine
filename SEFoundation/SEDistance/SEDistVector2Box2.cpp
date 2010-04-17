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
#include "SEDistVector2Box2.h"

using namespace Swing;

//----------------------------------------------------------------------------
DistVector2Box2f::DistVector2Box2f(const SEVector2f& rVector, const SEBox2f& rBox)
    :
    m_pVector(&rVector),
    m_pBox(&rBox)
{
}
//----------------------------------------------------------------------------
const SEVector2f& DistVector2Box2f::GetVector() const
{
    return *m_pVector;
}
//----------------------------------------------------------------------------
const SEBox2f& DistVector2Box2f::GetBox() const
{
    return *m_pBox;
}
//----------------------------------------------------------------------------
float DistVector2Box2f::Get()
{
    return SEMath<float>::Sqrt(GetSquared());
}
//----------------------------------------------------------------------------
float DistVector2Box2f::GetSquared()
{
    // 在box的坐标体系下计算.
    SEVector2f vec2fDiff = *m_pVector - m_pBox->Center;

    // 计算squared distance和box上的最近点.
    float fSqrDistance = 0.0f, fDelta;
    SEVector2f vec2fClosest;
    int i;
    for( i = 0; i < 2; i++ )
    {
        vec2fClosest[i] = vec2fDiff.Dot(m_pBox->Axis[i]);
        if( vec2fClosest[i] < -m_pBox->Extent[i] )
        {
            fDelta = vec2fClosest[i] + m_pBox->Extent[i];
            fSqrDistance += fDelta*fDelta;
            vec2fClosest[i] = -m_pBox->Extent[i];
        }
        else if( vec2fClosest[i] > m_pBox->Extent[i] )
        {
            fDelta = vec2fClosest[i] - m_pBox->Extent[i];
            fSqrDistance += fDelta*fDelta;
            vec2fClosest[i] = m_pBox->Extent[i];
        }
    }

    m_ClosestPoint0 = *m_pVector;
    m_ClosestPoint1 = m_pBox->Center;
    for( i = 0; i < 2; i++ )
    {
        m_ClosestPoint1 += vec2fClosest[i]*m_pBox->Axis[i];
    }

    return fSqrDistance;
}
//----------------------------------------------------------------------------
float DistVector2Box2f::Get(float fT, const SEVector2f& rVelocity0,
    const SEVector2f& rVelocity1)
{
    SEVector2f vec2fMVector = *m_pVector + fT*rVelocity0;
    SEVector2f vec2fMCenter = m_pBox->Center + fT*rVelocity1;
    SEBox2f tempMBox(vec2fMCenter, m_pBox->Axis, m_pBox->Extent);

    return DistVector2Box2f(vec2fMVector, tempMBox).Get();
}
//----------------------------------------------------------------------------
float DistVector2Box2f::GetSquared(float fT, const SEVector2f& rVelocity0, 
    const SEVector2f& rVelocity1)
{
    SEVector2f vec2fMVector = *m_pVector + fT*rVelocity0;
    SEVector2f vec2fMCenter = m_pBox->Center + fT*rVelocity1;
    SEBox2f tempMBox(vec2fMCenter, m_pBox->Axis, m_pBox->Extent);

    return DistVector2Box2f(vec2fMVector, tempMBox).GetSquared();
}
//----------------------------------------------------------------------------
