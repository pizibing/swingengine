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
#include "SEQuery2TRational.h"

using namespace Swing;

//----------------------------------------------------------------------------
Query2TRationalf::Query2TRationalf(int iVCount, const SEVector2f* aVertex)
    :
    Query2f(iVCount, aVertex)
{
    m_aRVertex = SE_NEW RVector[m_iVCount];
    m_abEvaluated = SE_NEW bool[m_iVCount];
    memset(m_abEvaluated, 0, m_iVCount*sizeof(bool));
}
//----------------------------------------------------------------------------
Query2TRationalf::~Query2TRationalf()
{
    SE_DELETE[] m_aRVertex;
    SE_DELETE[] m_abEvaluated;
}
//----------------------------------------------------------------------------
Query::Type Query2TRationalf::GetType() const
{
    return Query::QT_RATIONAL;
}
//----------------------------------------------------------------------------
int Query2TRationalf::ToLine(int i, int iV0, int iV1) const
{
    int aiIndex[3] = { i, iV0, iV1 };
    Convert(3, aiIndex);

    return ToLine(m_aRVertex[i], iV0, iV1);
}
//----------------------------------------------------------------------------
int Query2TRationalf::ToLine(const SEVector2f& rP, int iV0, int iV1) const
{
    RVector tempRP;
    tempRP[0] = Rational(rP[0]);
    tempRP[1] = Rational(rP[1]);
    int aiIndex[2] = { iV0, iV1 };
    Convert(2, aiIndex);

    return ToLine(tempRP, iV0, iV1);
}
//----------------------------------------------------------------------------
int Query2TRationalf::ToTriangle(int i, int iV0, int iV1, int iV2) const
{
    int aiIndex[4] = { i, iV0, iV1, iV2 };
    Convert(4, aiIndex);

    return ToTriangle(m_aRVertex[i], iV0, iV1, iV2);
}
//----------------------------------------------------------------------------
int Query2TRationalf::ToTriangle(const SEVector2f& rP, int iV0, int iV1, 
    int iV2) const
{
    RVector tempRP;
    tempRP[0] = Rational(rP[0]);
    tempRP[1] = Rational(rP[1]);
    int aiIndex[3] = { iV0, iV1, iV2 };
    Convert(3, aiIndex);

    return ToTriangle(tempRP, iV0, iV1, iV2);
}
//----------------------------------------------------------------------------
int Query2TRationalf::ToCircumcircle(int i, int iV0, int iV1, int iV2) const
{
    int aiIndex[4] = { i, iV0, iV1, iV2 };
    Convert(4, aiIndex);

    return ToCircumcircle(m_aRVertex[i], iV0, iV1, iV2);
}
//----------------------------------------------------------------------------
int Query2TRationalf::ToCircumcircle(const SEVector2f& rP, int iV0, int iV1, 
    int iV2) const
{
    RVector tempRP;
    tempRP[0] = Rational(rP[0]);
    tempRP[1] = Rational(rP[1]);
    int aiIndex[3] = { iV0, iV1, iV2 };
    Convert(3, aiIndex);

    return ToCircumcircle(tempRP, iV0, iV1, iV2);
}
//----------------------------------------------------------------------------
void Query2TRationalf::Convert(int iCount, int* aiIndex) const
{
    for( int i = 0; i < iCount; i++ )
    {
        int j = aiIndex[i];
        if( !m_abEvaluated[j] )
        {
            m_abEvaluated[j] = true;
            m_aRVertex[j][0] = Rational(m_aVertex[j][0]);
            m_aRVertex[j][1] = Rational(m_aVertex[j][1]);
        }
    }
}
//----------------------------------------------------------------------------
int Query2TRationalf::ToLine(const RVector& rRP, int iV0, int iV1) const
{
    Rational tempX0 = rRP[0] - m_aRVertex[iV0][0];
    Rational tempY0 = rRP[1] - m_aRVertex[iV0][1];
    Rational tempX1 = m_aRVertex[iV1][0] - m_aRVertex[iV0][0];
    Rational tempY1 = m_aRVertex[iV1][1] - m_aRVertex[iV0][1];

    Rational tempDet2 = Det2(tempX0, tempY0, tempX1, tempY1);

    return (tempDet2 > 0 ? +1 : (tempDet2 < 0 ? -1 : 0));
}
//----------------------------------------------------------------------------
int Query2TRationalf::ToTriangle(const RVector& rRP, int iV0, int iV1, 
    int iV2) const
{
    int iSign0 = ToLine(rRP, iV1, iV2);
    if( iSign0 > 0 )
    {
        return +1;
    }

    int iSign1 = ToLine(rRP, iV0, iV2);
    if( iSign1 < 0 )
    {
        return +1;
    }

    int iSign2 = ToLine(rRP, iV0, iV1);
    if( iSign2 > 0 )
    {
        return +1;
    }

    return ((iSign0 && iSign1 && iSign2) ? -1 : 0);
}
//----------------------------------------------------------------------------
int Query2TRationalf::ToCircumcircle(const RVector& rRP, int iV0, 
    int iV1, int iV2) const
{
    RVector& rRV0 = m_aRVertex[iV0];
    RVector& rRV1 = m_aRVertex[iV1];
    RVector& rRV2 = m_aRVertex[iV2];

    Rational tempS0x = rRV0[0] + rRP[0];
    Rational tempD0x = rRV0[0] - rRP[0];
    Rational tempS0y = rRV0[1] + rRP[1];
    Rational tempD0y = rRV0[1] - rRP[1];
    Rational tempS1x = rRV1[0] + rRP[0];
    Rational tempD1x = rRV1[0] - rRP[0];
    Rational tempS1y = rRV1[1] + rRP[1];
    Rational tempD1y = rRV1[1] - rRP[1];
    Rational tempS2x = rRV2[0] + rRP[0];
    Rational tempD2x = rRV2[0] - rRP[0];
    Rational tempS2y = rRV2[1] + rRP[1];
    Rational tempD2y = rRV2[1] - rRP[1];
    Rational tempZ0 = tempS0x*tempD0x + tempS0y*tempD0y;
    Rational tempZ1 = tempS1x*tempD1x + tempS1y*tempD1y;
    Rational tempZ2 = tempS2x*tempD2x + tempS2y*tempD2y;
    Rational tempDet3 = Det3(tempD0x, tempD0y, tempZ0, tempD1x, 
        tempD1y, tempZ1, tempD2x, tempD2y, tempZ2);

    return (tempDet3 < 0 ? 1 : (tempDet3 > 0 ? -1 : 0));
}
//----------------------------------------------------------------------------
Query2TRationalf::Rational Query2TRationalf::Dot(
    Rational& rX0, Rational& rY0, Rational& rX1, Rational& rY1)
{
    return rX0*rX1 + rY0*rY1;
}
//----------------------------------------------------------------------------
Query2TRationalf::Rational Query2TRationalf::Det2(
    Rational& rX0, Rational& rY0, Rational& rX1, Rational& rY1)
{
    return rX0*rY1 - rX1*rY0;
}
//----------------------------------------------------------------------------
Query2TRationalf::Rational Query2TRationalf::Det3(
    Rational& rX0, Rational& rY0, Rational& rZ0, Rational& rX1, 
    Rational& rY1, Rational& rZ1, Rational& rX2, Rational& rY2, 
    Rational& rZ2)
{
    Rational tempC00 = rY1*rZ2 - rY2*rZ1;
    Rational tempC01 = rY2*rZ0 - rY0*rZ2;
    Rational tempC02 = rY0*rZ1 - rY1*rZ0;

    return rX0*tempC00 + rX1*tempC01 + rX2*tempC02;
}
//----------------------------------------------------------------------------
