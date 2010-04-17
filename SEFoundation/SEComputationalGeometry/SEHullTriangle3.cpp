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

#include "SEFoundationPCH.h"
#include "SEHullTriangle3.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEHullTriangle3f::SEHullTriangle3f(int iV0,  int iV1,  int iV2)
{
    V[0] = iV0;
    V[1] = iV1;
    V[2] = iV2;
    A[0] = 0;
    A[1] = 0;
    A[2] = 0;
    Sign = 0;
    Time = -1;
    OnStack = false;
}
//----------------------------------------------------------------------------
int SEHullTriangle3f::GetSign(int i,  const SEQuery3f* pQuery)
{
    if( i != Time )
    {
        Time = i;
        Sign = pQuery->ToPlane(i,  V[0],  V[1],  V[2]);
    }

    return Sign;
}
//----------------------------------------------------------------------------
void SEHullTriangle3f::AttachTo(SEHullTriangle3f* pAdj0, 
    SEHullTriangle3f* pAdj1,  SEHullTriangle3f* pAdj2)
{
    // assert:  The input adjacent triangles are correctly ordered.
    A[0] = pAdj0;
    A[1] = pAdj1;
    A[2] = pAdj2;
}
//----------------------------------------------------------------------------
int SEHullTriangle3f::DetachFrom(int iAdj,  SEHullTriangle3f* pAdj)
{
    SE_ASSERT( 0 <= iAdj && iAdj < 3 && A[iAdj] == pAdj );

    A[iAdj] = 0;
    for( int i = 0; i < 3; i++ )
    {
        if( pAdj->A[i] == this )
        {
            pAdj->A[i] = 0;

            return i;
        }
    }

    return -1;
}
//----------------------------------------------------------------------------