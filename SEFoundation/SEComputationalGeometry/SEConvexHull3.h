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

#ifndef Swing_ConvexHull3_H
#define Swing_ConvexHull3_H

#include "SEFoundationLIB.h"
#include "SEConvexHull1.h"
#include "SEConvexHull2.h"
#include "SEHullTriangle3.h"
#include "SEQuery3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:ConvexHull3f类
// 说明:
// 作者:Sun Che
// 时间:20081201
//----------------------------------------------------------------------------
class SE_FOUNDATION_API ConvexHull3f : public ConvexHullf
{
public:
    // The input to the constructor is the array of vertices whose convex hull
    // is required.  If you want ConvexHull3f to delete the vertices during
    // destruction,  set bOwner to 'true'.  Otherwise,  you own the vertices and
    // must delete them yourself.
    //
    // You have a choice of speed versus accuracy.  The fastest choice is
    // Query::QT_INT64,  but it gives up a lot of precision,  scaling the points
    // to [0, 2^{20}]^3.  The choice Query::QT_INTEGER gives up less precision, 
    // scaling the points to [0, 2^{24}]^3.  The choice Query::QT_RATIONAL uses
    // exact arithmetic,  but is the slowest choice.  The choice Query::QT_REAL
    // uses floating-point arithmetic,  but is not robust in all cases.

    ConvexHull3f(int iVertexCount,  Vector3f* aVertex,  float fEpsilon, 
        bool bOwner,  Query::Type eQueryType);
    virtual ~ConvexHull3f(void);

    // If GetDimension() returns 1,  then the points lie on a line.  You must
    // create a ConvexHull1f object using the function provided.
    const Vector3f& GetLineOrigin(void) const;
    const Vector3f& GetLineDirection(void) const;
    ConvexHull1f* GetConvexHull1(void) const;

    // If GetDimension() returns 2,  then the points lie on a plane.  The plane
    // has two direction vectors (inputs 0 or 1).  You must create a
    // ConvexHull2f object using the function provided.
    const Vector3f& GetPlaneOrigin(void) const;
    const Vector3f& GetPlaneDirection(int i) const;
    ConvexHull2f* GetConvexHull2(void) const;

    // Support for streaming to/from disk.
    ConvexHull3f(const char* acFilename);
    bool Load(const char* acFilename);
    bool Save(const char* acFilename) const;

private:
    bool Update(int i);
    void ExtractIndices(void);
    void DeleteHull(void);

    // The input points.
    Vector3f* m_aVertex;

    // Support for robust queries.
    Vector3f* m_aSVertex;
    Query3f* m_pQuery;

    // The line of containment if the dimension is 1.
    Vector3f m_LineOrigin,  m_LineDirection;

    // The plane of containment if the dimension is 2.
    Vector3f m_PlaneOrigin,  m_aPlaneDirection[2];

    // The current hull.
    std::set<HullTriangle3f*> m_Hull;

    class TerminatorData
    {
    public:
        TerminatorData(int iV0 = -1,  int iV1 = -1,  int iNullIndex = -1, 
            HullTriangle3f* pTri = 0)
        {
            V[0] = iV0;
            V[1] = iV1;
            NullIndex = iNullIndex;
            Tri = pTri;
        }

        int V[2];
        int NullIndex;
        HullTriangle3f* Tri;
    };
};

}

#endif
