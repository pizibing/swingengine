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

#ifndef Swing_ExtremalQuery3_H
#define Swing_ExtremalQuery3_H

#include "SEPhysicsLIB.h"
#include "SEConvexPolyhedron3.h"

namespace Swing
{

class SE_PHYSICS_API ExtremalQuery3f
{
public:
    // 虚基类.
    virtual ~ExtremalQuery3f(void);

    // 根据指定方向,计算多面体在该方向上的极值顶点,
    // 并返回那些顶点在顶点数组中的索引.
    virtual void GetExtremeVertices(const Vector3f& rDirection,
        int& riPositiveDirection, int& riNegativeDirection) = 0;

    const ConvexPolyhedron3f& GetPolytope(void) const;
    const Vector3f* GetFaceNormals(void) const;

protected:
    ExtremalQuery3f(const ConvexPolyhedron3f& rPolytope);

    const ConvexPolyhedron3f* m_pPolytope;
    Vector3f* m_aFaceNormal;
};

}

#endif
