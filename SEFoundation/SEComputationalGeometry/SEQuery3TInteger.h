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
// 名称:Query3 TIntegerf类
// 说明:
// 作者:Sun Che
// 时间:20081202
//----------------------------------------------------------------------------
class SEQuery3TIntegerf : public SEQuery3f
{
public:
    // The components of the input vertices are truncated to 32-bit integer
    // values, so you should guarantee that the vertices are sufficiently
    // large to give a good distribution of numbers.  The value N in
    // SETInteger<N> is chosen large enough so that the exact arithmetic is
    // correct for the functions.
    SEQuery3TIntegerf(int iVCount, const SEVector3f* aVertex);

    // run-time type information
    virtual SEQuery::Type GetType(void) const;

    // Queries about the relation of a point to various geometric objects.

    virtual int ToPlane(const SEVector3f& rP, int iV0, int iV1, int iV2)
        const;

    virtual int ToCircumsphere(const SEVector3f& rP, int iV0, int iV1, 
        int iV2, int iV3) const;

private:
    static SETInteger<3> Dot(SETInteger<3>& rX0, SETInteger<3>& rY0, 
        SETInteger<3>& rZ0, SETInteger<3>& rX1, SETInteger<3>& rY1, 
        SETInteger<3>& rZ1);

    static SETInteger<4> Det3(SETInteger<4>& rX0, SETInteger<4>& rY0, 
        SETInteger<4>& rZ0, SETInteger<4>& rX1, SETInteger<4>& rY1, 
        SETInteger<4>& rZ1, SETInteger<4>& rX2, SETInteger<4>& rY2, 
        SETInteger<4>& rZ2);

    static SETInteger<6> Det4(SETInteger<6>& rX0, SETInteger<6>& rY0, 
        SETInteger<6>& rZ0, SETInteger<6>& rW0, SETInteger<6>& rX1, 
        SETInteger<6>& rY1, SETInteger<6>& rZ1, SETInteger<6>& rW1, 
        SETInteger<6>& rX2, SETInteger<6>& rY2, SETInteger<6>& rZ2, 
        SETInteger<6>& rW2, SETInteger<6>& rX3, SETInteger<6>& rY3, 
        SETInteger<6>& rZ3, SETInteger<6>& rW3);
};

}

#endif
