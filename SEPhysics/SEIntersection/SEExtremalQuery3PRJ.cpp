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

#include "SEPhysicsPCH.h"
#include "SEExtremalQuery3PRJ.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEExtremalQuery3PRJf::SEExtremalQuery3PRJf(const SEConvexPolyhedron3f& 
    rPolytope)
    :
    SEExtremalQuery3f(rPolytope)
{
    m_Centroid = m_pPolytope->ComputeVertexAverage();
}
//----------------------------------------------------------------------------
SEExtremalQuery3PRJf::~SEExtremalQuery3PRJf()
{
}
//----------------------------------------------------------------------------
void SEExtremalQuery3PRJf::GetExtremeVertices(const SEVector3f& rDirection, 
    int& riPositiveDirection, int& riNegativeDirection)
{
    SEVector3f vec3fDiff = m_pPolytope->GetVertex(0) - m_Centroid;
    float fMin = rDirection.Dot(vec3fDiff), fMax = fMin;
    riNegativeDirection = 0;
    riPositiveDirection = 0;

    for( int i = 1; i < m_pPolytope->GetVCount(); i++ )
    {
        vec3fDiff = m_pPolytope->GetVertex(i) - m_Centroid;
        float fDot = rDirection.Dot(vec3fDiff);
        if( fDot < fMin )
        {
            riNegativeDirection = i;
            fMin = fDot;
        }
        else if( fDot > fMax )
        {
            riPositiveDirection = i;
            fMax = fDot;
        }
    }
}
//----------------------------------------------------------------------------
