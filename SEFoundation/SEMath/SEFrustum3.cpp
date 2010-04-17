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
#include "SEFrustum3.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEFrustum3f::SEFrustum3f()
    :
    Origin(SEVector3f::ZERO),
    RVector(SEVector3f::UNIT_X),
    UVector(SEVector3f::UNIT_Y),
    DVector(SEVector3f::UNIT_Z)
{
    RBound = 1.0f;
    UBound = 1.0f;
    DMin = 1.0f;
    DMax = 2.0f;

    Update();
}
//----------------------------------------------------------------------------
SEFrustum3f::SEFrustum3f(const SEVector3f& rOrigin, const SEVector3f& rRVector, 
    const SEVector3f& rUVector, const SEVector3f& rDVector, 
    float fRBound, float fUBound, float fDMin, float fDMax)
    :
    Origin(rOrigin),
    RVector(rRVector),
    UVector(rUVector),
    DVector(rDVector)
{
    RBound = fRBound;
    UBound = fUBound;
    DMin = fDMin;
    DMax = fDMax;

    Update();
}
//----------------------------------------------------------------------------
void SEFrustum3f::Update()
{
    m_fDRatio = DMax / DMin;
    m_fMTwoUF = -2.0f * UBound * DMax;
    m_fMTwoRF = -2.0f * RBound * DMax;
}
//----------------------------------------------------------------------------
float SEFrustum3f::GetDRatio() const
{
    return m_fDRatio;
}
//----------------------------------------------------------------------------
float SEFrustum3f::GetMTwoUF() const
{
    return m_fMTwoUF;
}
//----------------------------------------------------------------------------
float SEFrustum3f::GetMTwoRF() const
{
    return m_fMTwoRF;
}
//----------------------------------------------------------------------------
void SEFrustum3f::ComputeVertices(SEVector3f aVertex[8]) const
{
    // 待检查.
    // 目前顶点为逆时针索引顺序.

    SEVector3f vec3fRScaled = RBound*RVector;
    SEVector3f vec3fUScaled = UBound*UVector;
    SEVector3f vec3fDScaled = DMin*DVector;

    aVertex[0] = vec3fDScaled - vec3fUScaled - vec3fRScaled;
    aVertex[1] = vec3fDScaled - vec3fUScaled + vec3fRScaled;
    aVertex[2] = vec3fDScaled + vec3fUScaled + vec3fRScaled;
    aVertex[3] = vec3fDScaled + vec3fUScaled - vec3fRScaled;

    for( int i = 0, ip = 4; i < 4; i++, ip++ )
    {
        aVertex[ip] = Origin + m_fDRatio*aVertex[i];
        aVertex[i] += Origin;
    }
}
//----------------------------------------------------------------------------
