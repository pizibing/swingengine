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

#ifndef Swing_Query3TInteger_H
#define Swing_Query3TInteger_H

#include "SEFoundationLIB.h"
#include "SEQuery3.h"
#include "SETInteger.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:Query3TIntegerf类
// 说明:
// 作者:Sun Che
// 时间:20081202
//----------------------------------------------------------------------------
class Query3TIntegerf : public Query3f
{
public:
    // The components of the input vertices are truncated to 32-bit integer
    // values, so you should guarantee that the vertices are sufficiently
    // large to give a good distribution of numbers.  The value N in
    // TInteger<N> is chosen large enough so that the exact arithmetic is
    // correct for the functions.
    Query3TIntegerf(int iVCount, const Vector3f* aVertex);

    // run-time type information
    virtual Query::Type GetType(void) const;

    // Queries about the relation of a point to various geometric objects.

    virtual int ToPlane(const Vector3f& rP, int iV0, int iV1, int iV2)
        const;

    virtual int ToCircumsphere(const Vector3f& rP, int iV0, int iV1, 
        int iV2, int iV3) const;

private:
    static TInteger<3> Dot(TInteger<3>& rX0, TInteger<3>& rY0, 
        TInteger<3>& rZ0, TInteger<3>& rX1, TInteger<3>& rY1, 
        TInteger<3>& rZ1);

    static TInteger<4> Det3(TInteger<4>& rX0, TInteger<4>& rY0, 
        TInteger<4>& rZ0, TInteger<4>& rX1, TInteger<4>& rY1, 
        TInteger<4>& rZ1, TInteger<4>& rX2, TInteger<4>& rY2, 
        TInteger<4>& rZ2);

    static TInteger<6> Det4(TInteger<6>& rX0, TInteger<6>& rY0, 
        TInteger<6>& rZ0, TInteger<6>& rW0, TInteger<6>& rX1, 
        TInteger<6>& rY1, TInteger<6>& rZ1, TInteger<6>& rW1, 
        TInteger<6>& rX2, TInteger<6>& rY2, TInteger<6>& rZ2, 
        TInteger<6>& rW2, TInteger<6>& rX3, TInteger<6>& rY3, 
        TInteger<6>& rZ3, TInteger<6>& rW3);
};

}

#endif
