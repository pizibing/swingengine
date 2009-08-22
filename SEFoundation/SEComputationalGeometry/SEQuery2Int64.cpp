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
#include "SEQuery2Int64.h"

using namespace Swing;

//----------------------------------------------------------------------------
Query2Int64f::Query2Int64f(int iVCount, const Vector2f* aVertex)
    :
    Query2f(iVCount, aVertex)
{
}
//----------------------------------------------------------------------------
Query::Type Query2Int64f::GetType() const
{
    return Query::QT_INT64;
}
//----------------------------------------------------------------------------
int Query2Int64f::ToLine(const Vector2f& rP, int iV0, int iV1) const
{
    const Vector2f& rV0 = m_aVertex[iV0];
    const Vector2f& rV1 = m_aVertex[iV1];

    SE_Int64 iX0 = (SE_Int64)rP[0] - (SE_Int64)rV0[0];
    SE_Int64 iY0 = (SE_Int64)rP[1] - (SE_Int64)rV0[1];
    SE_Int64 iX1 = (SE_Int64)rV1[0] - (SE_Int64)rV0[0];
    SE_Int64 iY1 = (SE_Int64)rV1[1] - (SE_Int64)rV0[1];

    SE_Int64 iDet2 = Det2(iX0, iY0, iX1, iY1);

    return (iDet2 > 0 ? +1 : (iDet2 < 0 ? -1 : 0));
}
//----------------------------------------------------------------------------
int Query2Int64f::ToCircumcircle(const Vector2f& rP, int iV0, 
    int iV1, int iV2) const
{
    const Vector2f& rV0 = m_aVertex[iV0];
    const Vector2f& rV1 = m_aVertex[iV1];
    const Vector2f& rV2 = m_aVertex[iV2];

    SE_Int64 aiP[2] = { (SE_Int64)rP[0], (SE_Int64)rP[1] };
    SE_Int64 aiV0[2] = { (SE_Int64)rV0[0], (SE_Int64)rV0[1] };
    SE_Int64 aiV1[2] = { (SE_Int64)rV1[0], (SE_Int64)rV1[1] };
    SE_Int64 aiV2[2] = { (SE_Int64)rV2[0], (SE_Int64)rV2[1] };

    SE_Int64 iS0x = aiV0[0] + aiP[0];
    SE_Int64 iD0x = aiV0[0] - aiP[0];
    SE_Int64 iS0y = aiV0[1] + aiP[1];
    SE_Int64 iD0y = aiV0[1] - aiP[1];
    SE_Int64 iS1x = aiV1[0] + aiP[0];
    SE_Int64 iD1x = aiV1[0] - aiP[0];
    SE_Int64 iS1y = aiV1[1] + aiP[1];
    SE_Int64 iD1y = aiV1[1] - aiP[1];
    SE_Int64 iS2x = aiV2[0] + aiP[0];
    SE_Int64 iD2x = aiV2[0] - aiP[0];
    SE_Int64 iS2y = aiV2[1] + aiP[1];
    SE_Int64 iD2y = aiV2[1] - aiP[1];
    SE_Int64 iZ0 = iS0x*iD0x + iS0y*iD0y;
    SE_Int64 iZ1 = iS1x*iD1x + iS1y*iD1y;
    SE_Int64 iZ2 = iS2x*iD2x + iS2y*iD2y;
    SE_Int64 iDet3 = Det3(iD0x, iD0y, iZ0, 
        iD1x, iD1y, iZ1, iD2x, iD2y, iZ2);

    return (iDet3 < 0 ? 1 : (iDet3 > 0 ? -1 : 0));
}
//----------------------------------------------------------------------------
SE_Int64 Query2Int64f::Dot(SE_Int64 iX0, SE_Int64 iY0, SE_Int64 iX1, 
    SE_Int64 iY1)
{
    return iX0*iX1 + iY0*iY1;
}
//----------------------------------------------------------------------------
SE_Int64 Query2Int64f::Det2(SE_Int64 iX0, SE_Int64 iY0, 
    SE_Int64 iX1, SE_Int64 iY1)
{
    return iX0*iY1 - iX1*iY0;
}
//----------------------------------------------------------------------------
SE_Int64 Query2Int64f::Det3(SE_Int64 iX0, SE_Int64 iY0, 
    SE_Int64 iZ0, SE_Int64 iX1, SE_Int64 iY1, SE_Int64 iZ1, SE_Int64 iX2, 
    SE_Int64 iY2, SE_Int64 iZ2)
{
    SE_Int64 iC00 = iY1*iZ2 - iY2*iZ1;
    SE_Int64 iC01 = iY2*iZ0 - iY0*iZ2;
    SE_Int64 iC02 = iY0*iZ1 - iY1*iZ0;

    return iX0*iC00 + iX1*iC01 + iX2*iC02;
}
//----------------------------------------------------------------------------
