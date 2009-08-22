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
#include "SEQuery3Filtered.h"

using namespace Swing;

//----------------------------------------------------------------------------
Query3Filteredf::Query3Filteredf (int iVCount, const Vector3f* aVertex, 
    float fUncertainty)
    :
    Query3f(iVCount, aVertex), 
    m_RQuery(iVCount, aVertex)
{
    SE_ASSERT( 0.0f <= fUncertainty && fUncertainty <= 1.0f );

    m_fUncertainty = fUncertainty;
}
//----------------------------------------------------------------------------
Query3Filteredf::~Query3Filteredf()
{
}
//----------------------------------------------------------------------------
Query::Type Query3Filteredf::GetType() const
{
    return Query::QT_FILTERED;
}
//----------------------------------------------------------------------------
int Query3Filteredf::ToPlane(const Vector3f& rP, int iV0, int iV1, int iV2) 
    const
{
    const Vector3f& rV0 = m_aVertex[iV0];
    const Vector3f& rV1 = m_aVertex[iV1];
    const Vector3f& rV2 = m_aVertex[iV2];

    float fX0 = rP[0] - rV0[0];
    float fY0 = rP[1] - rV0[1];
    float fZ0 = rP[2] - rV0[2];
    float fX1 = rV1[0] - rV0[0];
    float fY1 = rV1[1] - rV0[1];
    float fZ1 = rV1[2] - rV0[2];
    float fX2 = rV2[0] - rV0[0];
    float fY2 = rV2[1] - rV0[1];
    float fZ2 = rV2[2] - rV0[2];

    float fLen0 = Mathf::Sqrt(fX0*fX0 + fY0*fY0 + fZ0*fZ0);
    float fLen1 = Mathf::Sqrt(fX1*fX1 + fY1*fY1 + fZ1*fZ1);
    float fLen2 = Mathf::Sqrt(fX2*fX2 + fY2*fY2 + fZ2*fZ2);
    float fScaledUncertainty = m_fUncertainty * fLen0 * fLen1 * fLen2;

    float fDet3 = Det3(fX0, fY0, fZ0, fX1, fY1, fZ1, fX2, fY2, fZ2);
    if( Mathf::FAbs(fDet3) >= fScaledUncertainty )
    {
        return (fDet3 > 0.0f ? +1 : (fDet3 < 0.0f ? -1 : 0));
    }

    return m_RQuery.ToPlane(rP, iV0, iV1, iV2);
}
//----------------------------------------------------------------------------
int Query3Filteredf::ToCircumsphere(const Vector3f& rP, int iV0, 
    int iV1, int iV2, int iV3) const
{
    const Vector3f& rV0 = m_aVertex[iV0];
    const Vector3f& rV1 = m_aVertex[iV1];
    const Vector3f& rV2 = m_aVertex[iV2];
    const Vector3f& rV3 = m_aVertex[iV3];

    float fS0x = rV0[0] + rP[0];
    float fD0x = rV0[0] - rP[0];
    float fS0y = rV0[1] + rP[1];
    float fD0y = rV0[1] - rP[1];
    float fS0z = rV0[2] + rP[2];
    float fD0z = rV0[2] - rP[2];
    float fS1x = rV1[0] + rP[0];
    float fD1x = rV1[0] - rP[0];
    float fS1y = rV1[1] + rP[1];
    float fD1y = rV1[1] - rP[1];
    float fS1z = rV1[2] + rP[2];
    float fD1z = rV1[2] - rP[2];
    float fS2x = rV2[0] + rP[0];
    float fD2x = rV2[0] - rP[0];
    float fS2y = rV2[1] + rP[1];
    float fD2y = rV2[1] - rP[1];
    float fS2z = rV2[2] + rP[2];
    float fD2z = rV2[2] - rP[2];
    float fS3x = rV3[0] + rP[0];
    float fD3x = rV3[0] - rP[0];
    float fS3y = rV3[1] + rP[1];
    float fD3y = rV3[1] - rP[1];
    float fS3z = rV3[2] + rP[2];
    float fD3z = rV3[2] - rP[2];
    float fW0 = fS0x*fD0x + fS0y*fD0y + fS0z*fD0z;
    float fW1 = fS1x*fD1x + fS1y*fD1y + fS1z*fD1z;
    float fW2 = fS2x*fD2x + fS2y*fD2y + fS2z*fD2z;
    float fW3 = fS3x*fD3x + fS3y*fD3y + fS3z*fD3z;

    float fLen0 = Mathf::Sqrt(fD0x*fD0x + fD0y*fD0y + fD0z*fD0z + fW0*fW0);
    float fLen1 = Mathf::Sqrt(fD1x*fD1x + fD1y*fD1y + fD1z*fD1z + fW1*fW1);
    float fLen2 = Mathf::Sqrt(fD2x*fD2x + fD2y*fD2y + fD2z*fD2z + fW2*fW2);
    float fLen3 = Mathf::Sqrt(fD3x*fD3x + fD3y*fD3y + fD3z*fD3z + fW3*fW3);
    float fScaledUncertainty = m_fUncertainty * fLen0 * fLen1 * fLen2 * fLen3;

    float fDet4 = Det4(fD0x, fD0y, fD0z, fW0, fD1x, fD1y, fD1z, fW1, fD2x, 
        fD2y, fD2z, fW2, fD3x, fD3y, fD3z, fW3);

    if( Mathf::FAbs(fDet4) >= fScaledUncertainty )
    {
        return (fDet4 > 0.0f ? 1 : (fDet4 < 0.0f ? -1 : 0));
    }

    return m_RQuery.ToCircumsphere(rP, iV0, iV1, iV2, iV3);
}
//----------------------------------------------------------------------------
