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

#ifndef Swing_Query2Int64_H
#define Swing_Query2Int64_H

#include "SEFoundationLIB.h"
#include "SEQuery2.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:Query2Int64f类
// 说明:
// 作者:Sun Che
// 时间:20081202
//----------------------------------------------------------------------------
class Query2Int64f : public Query2f
{
public:
    // The components of the input vertices are truncated to 64-bit integer
    // values, so you should guarantee that the vertices are sufficiently
    // large to give a good distribution of numbers.
    Query2Int64f(int iVCount, const Vector2f* aVertex);

    // run-time type information
    virtual Query::Type GetType(void) const;

    // Queries about the relation of a point to various geometric objects.

    virtual int ToLine(const Vector2f& rP, int iV0, int iV1) const;

    virtual int ToCircumcircle(const Vector2f& rP, int iV0, int iV1, 
        int iV2) const;

private:
    static SE_Int64 Dot(SE_Int64 iX0, SE_Int64 iY0, SE_Int64 iX1, 
        SE_Int64 iY1);

    static SE_Int64 Det2(SE_Int64 iX0, SE_Int64 iY0, SE_Int64 iX1, 
        SE_Int64 iY1);

    static SE_Int64 Det3(SE_Int64 iX0, SE_Int64 iY0, SE_Int64 iZ0, 
        SE_Int64 iX1, SE_Int64 iY1, SE_Int64 iZ1, 
        SE_Int64 iX2, SE_Int64 iY2, SE_Int64 iZ2);
};

}

#endif
