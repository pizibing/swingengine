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
#include "SEExtremalQuery3.h"

using namespace Swing;

//----------------------------------------------------------------------------
ExtremalQuery3f::ExtremalQuery3f(const ConvexPolyhedron3f& rPolytope)
    :
    m_pPolytope(&rPolytope)
{
    // 创建三角面法线.
    const Vector3f* aVertex = m_pPolytope->GetVertices();
    int iTCount = m_pPolytope->GetTCount();
    const int* piIndex = m_pPolytope->GetIndices();
    m_aFaceNormal = SE_NEW Vector3f[iTCount];
    for( int i = 0; i < iTCount; i++ )
    {
        const Vector3f& rV0 = aVertex[*piIndex++];
        const Vector3f& rV1 = aVertex[*piIndex++];
        const Vector3f& rV2 = aVertex[*piIndex++];
        Vector3f vec3fEdge1 = rV1 - rV0;
        Vector3f vec3fEdge2 = rV2 - rV0;
        m_aFaceNormal[i] = vec3fEdge1.UnitCross(vec3fEdge2);
    }
}
//----------------------------------------------------------------------------
ExtremalQuery3f::~ExtremalQuery3f()
{
    SE_DELETE[] m_aFaceNormal;
}
//----------------------------------------------------------------------------
const ConvexPolyhedron3f& ExtremalQuery3f::GetPolytope() const
{
    return *m_pPolytope;
}
//----------------------------------------------------------------------------
const Vector3f* ExtremalQuery3f::GetFaceNormals() const
{
    return m_aFaceNormal;
}
//----------------------------------------------------------------------------
