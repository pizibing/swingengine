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
// 名称:Convex hull3f类
// 说明:
// 作者:Sun Che
// 时间:20081201
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEConvexHull3f : public SEConvexHullf
{
public:
    // The input to the constructor is the array of vertices whose convex hull
    // is required. If you want SEConvexHull3f to delete the vertices during
    // destruction, set bOwner to 'true'. Otherwise, you own the vertices and
    // must delete them yourself.
    //
    // You have a choice of speed versus accuracy. The fastest choice is
    // SEQuery::QT_INT64, but it gives up a lot of precision, scaling the points
    // to [0, 2^{20}]^3. The choice SEQuery::QT_INTEGER gives up less precision, 
    // scaling the points to [0, 2^{24}]^3. The choice SEQuery::QT_RATIONAL uses
    // exact arithmetic, but is the slowest choice.  The choice SEQuery::QT_REAL
    // uses floating-point arithmetic, but is not robust in all cases.

    SEConvexHull3f(int iVertexCount,  SEVector3f* aVertex,  float fEpsilon, 
        bool bOwner,  SEQuery::Type eQueryType);
    virtual ~SEConvexHull3f(void);

    // If GetDimension() returns 1, then the points lie on a line. You must
    // create a SEConvexHull1f object using the function provided.
    const SEVector3f& GetLineOrigin(void) const;
    const SEVector3f& GetLineDirection(void) const;
    SEConvexHull1f* GetConvexHull1(void) const;

    // If GetDimension() returns 2, then the points lie on a plane. The plane
    // has two direction vectors (inputs 0 or 1). You must create a
    // SEConvexHull2f object using the function provided.
    const SEVector3f& GetPlaneOrigin(void) const;
    const SEVector3f& GetPlaneDirection(int i) const;
    SEConvexHull2f* GetConvexHull2(void) const;

    // Support for streaming to/from disk.
    SEConvexHull3f(const char* acFilename);
    bool Load(const char* acFilename);
    bool Save(const char* acFilename) const;

private:
    bool Update(int i);
    void ExtractIndices(void);
    void DeleteHull(void);

    // The input points.
    SEVector3f* m_aVertex;

    // Support for robust queries.
    SEVector3f* m_aSVertex;
    SEQuery3f* m_pQuery;

    // The line of containment if the dimension is 1.
    SEVector3f m_LineOrigin,  m_LineDirection;

    // The plane of containment if the dimension is 2.
    SEVector3f m_PlaneOrigin,  m_aPlaneDirection[2];

    // The current hull.
    std::set<SEHullTriangle3f*> m_Hull;

    class SETerminatorData
    {
    public:
        SETerminatorData(int iV0 = -1, int iV1 = -1, int iNullIndex = -1, 
            SEHullTriangle3f* pTri = 0)
        {
            V[0] = iV0;
            V[1] = iV1;
            NullIndex = iNullIndex;
            Tri = pTri;
        }

        int V[2];
        int NullIndex;
        SEHullTriangle3f* Tri;
    };
};

}

#endif
