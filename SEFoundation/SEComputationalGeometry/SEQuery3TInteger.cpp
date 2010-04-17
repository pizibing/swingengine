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
#include "SEQuery3TInteger.h"

using namespace Swing;

//----------------------------------------------------------------------------
Query3TIntegerf::Query3TIntegerf(int iVCount, const SEVector3f* aVertex)
    :
    Query3f(iVCount, aVertex)
{
}
//----------------------------------------------------------------------------
Query::Type Query3TIntegerf::GetType() const
{
    return Query::QT_INTEGER;
}
//----------------------------------------------------------------------------
int Query3TIntegerf::ToPlane(const SEVector3f& rP, int iV0, int iV1, int iV2) 
    const
{
    const SEVector3f& rV0 = m_aVertex[iV0];
    const SEVector3f& rV1 = m_aVertex[iV1];
    const SEVector3f& rV2 = m_aVertex[iV2];

    TInteger<4> tempX0((int)rP[0] - (int)rV0[0]);
    TInteger<4> tempY0((int)rP[1] - (int)rV0[1]);
    TInteger<4> tempZ0((int)rP[2] - (int)rV0[2]);
    TInteger<4> tempX1((int)rV1[0] - (int)rV0[0]);
    TInteger<4> tempY1((int)rV1[1] - (int)rV0[1]);
    TInteger<4> tempZ1((int)rV1[2] - (int)rV0[2]);
    TInteger<4> tempX2((int)rV2[0] - (int)rV0[0]);
    TInteger<4> tempY2((int)rV2[1] - (int)rV0[1]);
    TInteger<4> tempZ2((int)rV2[2] - (int)rV0[2]);

    TInteger<4> tempDet3 = Det3(tempX0, tempY0, tempZ0, 
        tempX1, tempY1, tempZ1, tempX2, tempY2, tempZ2);

    return (tempDet3 > 0 ? +1 : (tempDet3 < 0 ? -1 : 0));
}
//----------------------------------------------------------------------------
int Query3TIntegerf::ToCircumsphere(const SEVector3f& rP, int iV0, 
    int iV1, int iV2, int iV3) const
{
    const SEVector3f& rV0 = m_aVertex[iV0];
    const SEVector3f& rV1 = m_aVertex[iV1];
    const SEVector3f& rV2 = m_aVertex[iV2];
    const SEVector3f& rV3 = m_aVertex[iV3];

    int aiP[3] = { (int)rP[0], (int)rP[1], (int)rP[2] };
    int aiV0[3] = { (int)rV0[0], (int)rV0[1], (int)rV0[2] };
    int aiV1[3] = { (int)rV1[0], (int)rV1[1], (int)rV1[2] };
    int aiV2[3] = { (int)rV2[0], (int)rV2[1], (int)rV2[2] };
    int aiV3[3] = { (int)rV3[0], (int)rV3[1], (int)rV3[2] };

    TInteger<6> tempS0x(aiV0[0] + aiP[0]);
    TInteger<6> tempD0x(aiV0[0] - aiP[0]);
    TInteger<6> tempS0y(aiV0[1] + aiP[1]);
    TInteger<6> tempD0y(aiV0[1] - aiP[1]);
    TInteger<6> tempS0z(aiV0[2] + aiP[2]);
    TInteger<6> tempD0z(aiV0[2] - aiP[2]);
    TInteger<6> tempS1x(aiV1[0] + aiP[0]);
    TInteger<6> tempD1x(aiV1[0] - aiP[0]);
    TInteger<6> tempS1y(aiV1[1] + aiP[1]);
    TInteger<6> tempD1y(aiV1[1] - aiP[1]);
    TInteger<6> tempS1z(aiV1[2] + aiP[2]);
    TInteger<6> tempD1z(aiV1[2] - aiP[2]);
    TInteger<6> tempS2x(aiV2[0] + aiP[0]);
    TInteger<6> tempD2x(aiV2[0] - aiP[0]);
    TInteger<6> tempS2y(aiV2[1] + aiP[1]);
    TInteger<6> tempD2y(aiV2[1] - aiP[1]);
    TInteger<6> tempS2z(aiV2[2] + aiP[2]);
    TInteger<6> tempD2z(aiV2[2] - aiP[2]);
    TInteger<6> tempS3x(aiV3[0] + aiP[0]);
    TInteger<6> tempD3x(aiV3[0] - aiP[0]);
    TInteger<6> tempS3y(aiV3[1] + aiP[1]);
    TInteger<6> tempD3y(aiV3[1] - aiP[1]);
    TInteger<6> tempS3z(aiV3[2] + aiP[2]);
    TInteger<6> tempD3z(aiV3[2] - aiP[2]);
    TInteger<6> tempW0 = tempS0x*tempD0x + tempS0y*tempD0y + tempS0z*tempD0z;
    TInteger<6> tempW1 = tempS1x*tempD1x + tempS1y*tempD1y + tempS1z*tempD1z;
    TInteger<6> tempW2 = tempS2x*tempD2x + tempS2y*tempD2y + tempS2z*tempD2z;
    TInteger<6> tempW3 = tempS3x*tempD3x + tempS3y*tempD3y + tempS3z*tempD3z;
    TInteger<6> tempDet4 = Det4(tempD0x, tempD0y, tempD0z, tempW0, 
        tempD1x, tempD1y, tempD1z, tempW1, tempD2x, tempD2y, tempD2z, tempW2, 
        tempD3x, tempD3y, tempD3z, tempW3);

    return (tempDet4 > 0 ? 1 : (tempDet4 < 0 ? -1 : 0));
}
//----------------------------------------------------------------------------
TInteger<3> Query3TIntegerf::Dot(TInteger<3>& rX0, TInteger<3>& rY0, 
    TInteger<3>& rZ0, TInteger<3>& rX1, TInteger<3>& rY1, 
    TInteger<3>& rZ1)
{
    return rX0*rX1 + rY0*rY1 + rZ0*rZ1;
}
//----------------------------------------------------------------------------
TInteger<4> Query3TIntegerf::Det3(TInteger<4>& rX0, TInteger<4>& rY0, 
    TInteger<4>& rZ0, TInteger<4>& rX1, TInteger<4>& rY1, 
    TInteger<4>& rZ1, TInteger<4>& rX2, TInteger<4>& rY2, 
    TInteger<4>& rZ2)
{
    TInteger<4> tempC00 = rY1*rZ2 - rY2*rZ1;
    TInteger<4> tempC01 = rY2*rZ0 - rY0*rZ2;
    TInteger<4> tempC02 = rY0*rZ1 - rY1*rZ0;

    return rX0*tempC00 + rX1*tempC01 + rX2*tempC02;
}
//----------------------------------------------------------------------------
TInteger<6> Query3TIntegerf::Det4(TInteger<6>& rX0, TInteger<6>& rY0, 
    TInteger<6>& rZ0, TInteger<6>& rW0, TInteger<6>& rX1, 
    TInteger<6>& rY1, TInteger<6>& rZ1, TInteger<6>& rW1, 
    TInteger<6>& rX2, TInteger<6>& rY2, TInteger<6>& rZ2, 
    TInteger<6>& rW2, TInteger<6>& rX3, TInteger<6>& rY3, 
    TInteger<6>& rZ3, TInteger<6>& rW3)
{
    TInteger<6> tempA0 = rX0*rY1 - rX1*rY0;
    TInteger<6> tempA1 = rX0*rY2 - rX2*rY0;
    TInteger<6> tempA2 = rX0*rY3 - rX3*rY0;
    TInteger<6> tempA3 = rX1*rY2 - rX2*rY1;
    TInteger<6> tempA4 = rX1*rY3 - rX3*rY1;
    TInteger<6> tempA5 = rX2*rY3 - rX3*rY2;
    TInteger<6> tempB0 = rZ0*rW1 - rZ1*rW0;
    TInteger<6> tempB1 = rZ0*rW2 - rZ2*rW0;
    TInteger<6> tempB2 = rZ0*rW3 - rZ3*rW0;
    TInteger<6> tempB3 = rZ1*rW2 - rZ2*rW1;
    TInteger<6> tempB4 = rZ1*rW3 - rZ3*rW1;
    TInteger<6> tempB5 = rZ2*rW3 - rZ3*rW2;

    return tempA0*tempB5 - tempA1*tempB4 + tempA2*tempB3 + tempA3*tempB2 - 
        tempA4*tempB1 + tempA5*tempB0;
}
//----------------------------------------------------------------------------
