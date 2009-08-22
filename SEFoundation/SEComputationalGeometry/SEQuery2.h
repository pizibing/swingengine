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

#ifndef Swing_Query2_H
#define Swing_Query2_H

#include "SEFoundationLIB.h"
#include "SEQuery.h"
#include "SEVector2.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:Query2f类
// 说明:
// 作者:Sun Che
// 时间:20081202
//----------------------------------------------------------------------------
class Query2f : public Query
{
public:
    // The base class handles floating-point queries.
    Query2f(int iVCount, const Vector2f* aVertex);
    virtual ~Query2f(void);

    // run-time type information
    virtual Query::Type GetType(void) const;

    // member access
    int GetCount(void) const;
    const Vector2f* GetVertices(void) const;

    // Queries about the relation of a point to various geometric objects.

    // returns
    //   +1, on right of line
    //   -1, on left of line
    //    0, on the line
    virtual int ToLine(int i, int iV0, int iV1) const;
    virtual int ToLine(const Vector2f& rP, int iV0, int iV1) const;

    // returns
    //   +1, outside triangle
    //   -1, inside triangle
    //    0, on triangle
    virtual int ToTriangle(int i, int iV0, int iV1, int iV2) const;
    virtual int ToTriangle(const Vector2f& rP, int iV0, int iV1,
        int iV2) const;

    // returns
    //   +1, outside circumcircle of triangle
    //   -1, inside circumcircle of triangle
    //    0, on circumcircle of triangle
    virtual int ToCircumcircle(int i, int iV0, int iV1, int iV2) const;
    virtual int ToCircumcircle(const Vector2f& rP, int iV0, int iV1,
        int iV2) const;

protected:
    // input points
    int m_iVCount;
    const Vector2f* m_aVertex;

    static float Dot(float fX0, float fY0, float fX1, float fY1);

    static float Det2(float fX0, float fY0, float fX1, float fY1);

    static float Det3(float iX0, float iY0, float iZ0, float iX1, float iY1,
        float iZ1, float iX2, float iY2, float iZ2);
};

}

#endif
