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

#ifndef Swing_Query3_H
#define Swing_Query3_H

#include "SEFoundationLIB.h"
#include "SEQuery.h"
#include "SEVector3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:Query3f类
// 说明:
// 作者:Sun Che
// 时间:20081202
//----------------------------------------------------------------------------
class Query3f : public Query
{
public:
    // The base class handles floating-point queries.
    Query3f(int iVCount, const SEVector3f* aVertex);
    virtual ~Query3f(void);

    // run-time type information
    virtual Query::Type GetType(void) const;

    // member access
    int GetCount(void) const;
    const SEVector3f* GetVertices(void) const;

    // Queries about the relation of a point to various geometric objects.

    // returns
    //   +1, on positive side of plane
    //   -1, on negative side of line
    //    0, on the plane
    virtual int ToPlane(int i, int iV0, int iV1, int iV2) const;
    virtual int ToPlane(const SEVector3f& rP, int iV0, int iV1, int iV2)
        const;

    // returns
    //   +1, outside tetrahedron
    //   -1, inside tetrahedron
    //    0, on tetrahedron
    virtual int ToTetrahedron(int i, int iV0, int iV1, int iV2, int iV3)
        const;
    virtual int ToTetrahedron(const SEVector3f& rP, int iV0, int iV1, 
        int iV2, int iV3) const;

    // returns
    //   +1, outside circumsphere of tetrahedron
    //   -1, inside circumsphere of tetrahedron
    //    0, on circumsphere of tetrahedron
    virtual int ToCircumsphere(int i, int iV0, int iV1, int iV2, int iV3)
        const;
    virtual int ToCircumsphere(const SEVector3f& rP, int iV0, int iV1, 
        int iV2, int iV3) const;

protected:
    // input points
    int m_iVCount;
    const SEVector3f* m_aVertex;

    static float Dot(float fX0, float fY0, float fZ0, float fX1, float fY1, 
        float fZ1);

    static float Det3(float fX0, float fY0, float fZ0, float fX1, float fY1, 
        float fZ1, float fX2, float fY2, float fZ2);

    static float Det4(float fX0, float fY0, float fZ0, float fW0, float fX1, 
        float fY1, float fZ1, float fW1, float fX2, float fY2, float fZ2, float fW2, 
        float fX3, float fY3, float fZ3, float fW3);
};

}

#endif
