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

#ifndef Swing_ConvexHull2_H
#define Swing_ConvexHull2_H

#include "SEFoundationLIB.h"
#include "SEConvexHull1.h"
#include "SEHullEdge2.h"
#include "SEQuery2.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:ConvexHull2f类
// 说明:
// 作者:Sun Che
// 时间:20081201
//----------------------------------------------------------------------------
class SE_FOUNDATION_API ConvexHull2f : public ConvexHullf
{
public:
    // The input to the constructor is the array of vertices whose convex hull
    // is required.  If you want ConvexHull2f to delete the vertices during
    // destruction,  set bOwner to 'true'.  Otherwise,  you own the vertices and
    // must delete them yourself.
    //
    // You have a choice of speed versus accuracy.  The fastest choice is
    // Query::QT_INT64,  but it gives up a lot of precision,  scaling the points
    // to [0, 2^{20}]^3.  The choice Query::QT_INTEGER gives up less precision, 
    // scaling the points to [0, 2^{24}]^3.  The choice Query::QT_RATIONAL uses
    // exact arithmetic,  but is the slowest choice.  The choice Query::QT_REAL
    // uses floating-point arithmetic,  but is not robust in all cases.

    ConvexHull2f(int iVertexCount,  Vector2f* aVertex,  float fEpsilon, 
        bool bOwner,  Query::Type eQueryType);
    virtual ~ConvexHull2f(void);

    // If GetDimension() returns 1,  then the points lie on a line.  You must
    // create a ConvexHull1f object using the function provided.
    const Vector2f& GetLineOrigin(void) const;
    const Vector2f& GetLineDirection(void) const;
    ConvexHull1f* GetConvexHull1(void) const;

private:
    // Support for streaming to/from disk.
    ConvexHull2f(const char* acFilename);
    bool Load(const char* acFilename);
    bool Save(const char* acFilename) const;

    bool Update(HullEdge2f*& rpHull,  int i);

    // The input points.
    Vector2f* m_aVertex;

    // Support for robust queries.
    Vector2f* m_aSVertex;
    Query2f* m_pQuery;

    // The line of containment if the dimension is 1.
    Vector2f m_LineOrigin,  m_LineDirection;
};

}

#endif
