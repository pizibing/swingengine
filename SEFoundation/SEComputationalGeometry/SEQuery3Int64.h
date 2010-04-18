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

#ifndef Swing_Query3Int64_H
#define Swing_Query3Int64_H

#include "SEFoundationLIB.h"
#include "SEQuery3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20081202
//----------------------------------------------------------------------------
class SEQuery3Int64f : public SEQuery3f
{
public:
    // The components of the input vertices are truncated to 64-bit integer
    // values, so you should guarantee that the vertices are sufficiently
    // large to give a good distribution of numbers.
    SEQuery3Int64f(int iVCount, const SEVector3f* aVertex);

    // run-time type information
    virtual SEQuery::Type GetType(void) const;

    // Queries about the relation of a point to various geometric objects.

    virtual int ToPlane(const SEVector3f& rP, int iV0, int iV1, int iV2)
        const;

    virtual int ToCircumsphere(const SEVector3f& rP, int iV0, int iV1, 
        int iV2, int iV3) const;

private:
    static SE_Int64 Dot(SE_Int64 iX0, SE_Int64 iY0, SE_Int64 iZ0, 
        SE_Int64 iX1, SE_Int64 iY1, SE_Int64 iZ1);

    static SE_Int64 Det3(SE_Int64 iX0, SE_Int64 iY0, SE_Int64 iZ0, 
        SE_Int64 iX1, SE_Int64 iY1, SE_Int64 iZ1, SE_Int64 iX2, 
        SE_Int64 iY2, SE_Int64 iZ2);

    static SE_Int64 Det4(SE_Int64 iX0, SE_Int64 iY0, SE_Int64 iZ0, 
        SE_Int64 iW0, SE_Int64 iX1, SE_Int64 iY1, SE_Int64 iZ1, 
        SE_Int64 iW1, SE_Int64 iX2, SE_Int64 iY2, SE_Int64 iZ2, 
        SE_Int64 iW2, SE_Int64 iX3, SE_Int64 iY3, SE_Int64 iZ3, 
        SE_Int64 iW3);
};

}

#endif
