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
#include "SEQuery2Filtered.h"

using namespace Swing;

//----------------------------------------------------------------------------
Query2Filteredf::Query2Filteredf(int iVCount, const SEVector2f* aVertex, 
    float fUncertainty)
    :
    Query2f(iVCount, aVertex),
    m_RQuery(iVCount, aVertex)
{
    SE_ASSERT( 0.0f <= fUncertainty && fUncertainty <= 1.0f );

    m_fUncertainty = fUncertainty;
}
//----------------------------------------------------------------------------
Query2Filteredf::~Query2Filteredf()
{
}
//----------------------------------------------------------------------------
Query::Type Query2Filteredf::GetType() const
{
    return Query::QT_FILTERED;
}
//----------------------------------------------------------------------------
int Query2Filteredf::ToLine(const SEVector2f& rP, int iV0, int iV1) const
{
    const SEVector2f& rV0 = m_aVertex[iV0];
    const SEVector2f& rV1 = m_aVertex[iV1];

    float fX0 = rP[0] - rV0[0];
    float fY0 = rP[1] - rV0[1];
    float fX1 = rV1[0] - rV0[0];
    float fY1 = rV1[1] - rV0[1];

    float fLen0 = Mathf::Sqrt(fX0*fX0 + fY0*fY0);
    float fLen1 = Mathf::Sqrt(fX1*fX1 + fY1*fY1);
    float fScaledUncertainty = m_fUncertainty * fLen0 * fLen1;

    float fDet2 = Det2(fX0, fY0, fX1, fY1);
    if( Mathf::FAbs(fDet2) >= fScaledUncertainty )
    {
        return (fDet2 > 0.0f ? +1 : (fDet2 < 0.0f ? -1 : 0));
    }

    return m_RQuery.ToLine(rP, iV0, iV1);
}
//----------------------------------------------------------------------------
int Query2Filteredf::ToCircumcircle(const SEVector2f& rP, int iV0,
    int iV1, int iV2) const
{
    const SEVector2f& rV0 = m_aVertex[iV0];
    const SEVector2f& rV1 = m_aVertex[iV1];
    const SEVector2f& rV2 = m_aVertex[iV2];

    float fS0x = rV0[0] + rP[0];
    float fD0x = rV0[0] - rP[0];
    float fS0y = rV0[1] + rP[1];
    float fD0y = rV0[1] - rP[1];
    float fS1x = rV1[0] + rP[0];
    float fD1x = rV1[0] - rP[0];
    float fS1y = rV1[1] + rP[1];
    float fD1y = rV1[1] - rP[1];
    float fS2x = rV2[0] + rP[0];
    float fD2x = rV2[0] - rP[0];
    float fS2y = rV2[1] + rP[1];
    float fD2y = rV2[1] - rP[1];
    float fZ0 = fS0x*fD0x + fS0y*fD0y;
    float fZ1 = fS1x*fD1x + fS1y*fD1y;
    float fZ2 = fS2x*fD2x + fS2y*fD2y;

    float fLen0 = Mathf::Sqrt(fD0x*fD0x + fD0y*fD0y + fZ0*fZ0);
    float fLen1 = Mathf::Sqrt(fD1x*fD1x + fD1y*fD1y + fZ1*fZ1);
    float fLen2 = Mathf::Sqrt(fD2x*fD2x + fD2y*fD2y + fZ2*fZ2);
    float fScaledUncertainty = m_fUncertainty * fLen0 * fLen1 * fLen2;

    float fDet3 = Det3(fD0x, fD0y, fZ0, fD1x, fD1y, fZ1, fD2x, fD2y, fZ2);
    if( Mathf::FAbs(fDet3) >= fScaledUncertainty )
    {
        return (fDet3 < 0.0f ? 1 : (fDet3 > 0.0f ? -1 : 0));
    }

    return m_RQuery.ToCircumcircle(rP, iV0, iV1, iV2);
}
//----------------------------------------------------------------------------
