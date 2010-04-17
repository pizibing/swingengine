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

#ifndef Swing_Query2TInteger_H
#define Swing_Query2TInteger_H

#include "SEFoundationLIB.h"
#include "SEQuery2.h"
#include "SETInteger.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:Query2TIntegerf类
// 说明:
// 作者:Sun Che
// 时间:20081202
//----------------------------------------------------------------------------
class Query2TIntegerf : public Query2f
{
public:
    // The components of the input vertices are truncated to 32-bit integer
    // values, so you should guarantee that the vertices are sufficiently
    // large to give a good distribution of numbers.  The value N in
    // TInteger<N> is chosen large enough so that the exact arithmetic is
    // correct for the functions.
    Query2TIntegerf(int iVCount, const SEVector2f* aVertex);

    // run-time type information
    virtual Query::Type GetType(void) const;

    // Queries about the relation of a point to various geometric objects.

    virtual int ToLine(const SEVector2f& rP, int iV0, int iV1) const;

    virtual int ToCircumcircle(const SEVector2f& rP, int iV0, int iV1, 
        int iV2) const;

private:
    static TInteger<2> Dot(TInteger<2>& rX0, TInteger<2>& rY0, 
        TInteger<2>& rX1, TInteger<2>& rY1);

    static TInteger<2> Det2(TInteger<2>& rX0, TInteger<2>& rY0, 
        TInteger<2>& rX1, TInteger<2>& rY1);

    static TInteger<4> Det3(TInteger<4>& rX0, TInteger<4>& rY0, 
        TInteger<4>& rZ0, TInteger<4>& rX1, TInteger<4>& rY1, 
        TInteger<4>& rZ1, TInteger<4>& rX2, TInteger<4>& rY2, 
        TInteger<4>& rZ2);
};

}

#endif
