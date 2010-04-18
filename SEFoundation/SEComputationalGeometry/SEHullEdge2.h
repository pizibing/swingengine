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

#ifndef Swing_HullEdge2_H
#define Swing_HullEdge2_H

#include "SEFoundationLIB.h"
#include "SEQuery2.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 说明:
// 作者:Sun Che
// 时间:20081201
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEHullEdge2f
{
public:
    SEHullEdge2f(int iV0,  int iV1);

    int GetSign(int i,  const SEQuery2f* pQuery);

    void Insert(SEHullEdge2f* pAdj0,  SEHullEdge2f* pAdj1);
    void DeleteSelf(void);
    void DeleteAll(void);

    void GetIndices(int& riHCount,  int*& raiHIndex);

    int V[2];
    SEHullEdge2f* A[2];
    int Sign;
    int Time;
};

}

#endif
