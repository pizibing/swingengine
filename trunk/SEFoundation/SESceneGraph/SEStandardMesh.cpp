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
#include "SEStandardMesh.h"
//#include "SEBSplineSurfacePatch.h"
//#include "SESurfaceMesh.h"

using namespace Swing;

// �����.
// normal,uv,IB

//----------------------------------------------------------------------------
StandardMesh::StandardMesh(const Attributes& rAttr, bool bInside, 
    const Transformation* pXFrm)
    :
    m_Attr(rAttr)
{
    SE_ASSERT( m_Attr.GetPositionChannels() == 3 );

    if( m_Attr.HasNormal() )
    {
        SE_ASSERT( m_Attr.GetNormalChannels() == 3 );
    }

    for( int iUnit = 0; iUnit < m_Attr.GetMaxTCoords(); iUnit++ )
    {
        if( m_Attr.HasTCoord(iUnit) )
        {
            SE_ASSERT( m_Attr.GetTCoordChannels(iUnit) == 2 );
        }
    }

    if( pXFrm )
    {
        m_XFrm = *pXFrm;
    }
    m_bInside = bInside;

    m_pVBuffer = 0;
    m_pIBuffer = 0;
}
//----------------------------------------------------------------------------
StandardMesh::~StandardMesh()
{
}
//----------------------------------------------------------------------------
void StandardMesh::SetTransformation(const Transformation& rXFrm)
{
    m_XFrm = rXFrm;
}
//----------------------------------------------------------------------------
const Transformation& StandardMesh::GetTransformation() const
{
    return m_XFrm;
}
//----------------------------------------------------------------------------
void StandardMesh::TransformData(VertexBuffer* pVB)
{
    if( m_XFrm.IsIdentity() )
    {
        return;
    }

    int iVCount = pVB->GetVertexCount();
    int i;
    Vector3f vec3fInput;
    for( i = 0; i < iVCount; i++ )
    {
        vec3fInput = pVB->Position3(i);
        m_XFrm.ApplyForward(vec3fInput, pVB->Position3(i));
    }

    if( m_Attr.HasNormal() )
    {
        Vector3f vec3fSave = m_XFrm.GetTranslate();
        m_XFrm.SetTranslate(Vector3f::ZERO);

        for( i = 0; i < iVCount; i++ )
        {
            vec3fInput = pVB->Normal3(i);
            m_XFrm.ApplyForward(vec3fInput, pVB->Normal3(i));
            pVB->Normal3(i).Normalize();
        }
        m_XFrm.SetTranslate(vec3fSave);
    }
}
//----------------------------------------------------------------------------
void StandardMesh::ReverseTriangleOrder(int iTCount, int* aiIndex)
{
    for( int i = 0; i < iTCount; i++ )
    {
        int j1 = 3*i+1, j2 = j1+1;
        int iSave = aiIndex[j1];
        aiIndex[j1] = aiIndex[j2];
        aiIndex[j2] = iSave;
    }
}
//----------------------------------------------------------------------------
TriMesh* StandardMesh::Rectangle(int iXSamples, int iYSamples, 
    float fXExtent, float fYExtent)
{
    int iVCount = iXSamples * iYSamples;
    int iTCount = 2 * (iXSamples - 1) * (iYSamples - 1);
    VertexBuffer* pVB = SE_NEW VertexBuffer(m_Attr, iVCount);
    IndexBuffer* pIB = SE_NEW IndexBuffer(3 * iTCount);

    // ����geometry.
    float fInv0 = 1.0f / (iXSamples - 1.0f);
    float fInv1 = 1.0f / (iYSamples - 1.0f);
    float fU, fV;
    int i, i0, i1;
    for( i1 = 0, i = 0; i1 < iYSamples; i1++ )
    {
        fV = i1 * fInv1;
        Vector3f vec3fYTmp = ((2.0f*fV - 1.0f)*fYExtent) * Vector3f::UNIT_Y;
        for( i0 = 0; i0 < iXSamples; i0++ )
        {
            fU = i0 * fInv0;
            Vector3f vec3fXTmp = ((2.0f*fU - 1.0f)*fXExtent) * Vector3f::UNIT_X;
            pVB->Position3(i) = vec3fXTmp + vec3fYTmp;

            if( m_Attr.HasNormal() )
            {
                pVB->Normal3(i) = -Vector3f::UNIT_Z;
            }

            if( m_Attr.GetMaxTCoords() > 0 )
            {
                Vector2f vec2fTCoord(fU, 1.0f - fV);
                for( int iUnit = 0; iUnit < m_Attr.GetMaxTCoords(); iUnit++ )
                {
                    if( m_Attr.HasTCoord(iUnit) )
                    {
                        pVB->TCoord2(iUnit, i) = vec2fTCoord;
                    }
                }
            }

            i++;
        }
    }

    // ����connectivity.
    int* aiIndex = pIB->GetData();
    for( i1 = 0, i = 0; i1 < iYSamples - 1; i1++ )
    {
        for( i0 = 0; i0 < iXSamples - 1; i0++ )
        {
            int iV0 = i0 + iXSamples * i1;
            int iV1 = iV0 + 1;
            int iV2 = iV1 + iXSamples;
            int iV3 = iV0 + iXSamples;
            aiIndex[i++] = iV0;
            aiIndex[i++] = iV2;
            aiIndex[i++] = iV1;
            aiIndex[i++] = iV0;
            aiIndex[i++] = iV3;
            aiIndex[i++] = iV2;
        }
    }

    TransformData(pVB);
    TriMesh* pMesh = SE_NEW TriMesh(pVB, pIB);

    return pMesh;
}
//----------------------------------------------------------------------------
TriMesh* StandardMesh::Disk(int iShellSamples, int iRadialSamples, 
    float fRadius)
{
    int iRSm1 = iRadialSamples - 1, iSSm1 = iShellSamples - 1;
    int iVCount = 1 + iRadialSamples * iSSm1;
    int iTCount = iRadialSamples * (2*iSSm1 - 1);
    VertexBuffer* pVB = SE_NEW VertexBuffer(m_Attr, iVCount);
    IndexBuffer* pIB = SE_NEW IndexBuffer(3 * iTCount);

    // ����geometry.
    int iR, iS, i, iUnit;
    Vector2f vec2fTCoord;

    // disk����.
    pVB->Position3(0) = Vector3f::ZERO;
    if( m_Attr.HasNormal() )
    {
        pVB->Normal3(0) = -Vector3f::UNIT_Z;
    }

    if( m_Attr.GetMaxTCoords() > 0 )
    {
        vec2fTCoord = Vector2f(0.5f, 0.5f);
        for( iUnit = 0; iUnit < m_Attr.GetMaxTCoords(); iUnit++ )
        {
            if( m_Attr.HasTCoord(iUnit) )
            {
                pVB->TCoord2(iUnit, 0) = vec2fTCoord;
            }
        }
    }

    float fInvSSm1 = 1.0f / (float)iSSm1;
    float fInvRS = 1.0f / (float)iRadialSamples;
    for( iR = 0; iR < iRadialSamples; iR++ )
    {
        float fAngle = Mathf::TWO_PI * fInvRS * iR;
        float fCos = Mathf::Cos(fAngle);
        float fSin = Mathf::Sin(fAngle);
        Vector3f vec3fRadial(fCos, fSin, 0.0f);

        for( iS = 1; iS < iShellSamples; iS++ )
        {
            float fFraction = fInvSSm1 * iS;  // in (0, R]
            Vector3f vec3fFracRadial = fFraction * vec3fRadial;
            i = iS + iSSm1*iR;
            pVB->Position3(i) = fRadius * vec3fFracRadial;
            if( m_Attr.HasNormal() )
            {
                pVB->Normal3(i) = -Vector3f::UNIT_Z;
            }

            if( m_Attr.GetMaxTCoords() > 0 )
            {
                vec2fTCoord = 0.5f * Vector2f(1.0f + vec3fFracRadial.X, 
                    1.0f + vec3fFracRadial.Y);
                for( iUnit = 0; iUnit < m_Attr.GetMaxTCoords(); iUnit++ )
                {
                    if( m_Attr.HasTCoord(iUnit) )
                    {
                        pVB->TCoord2(iUnit, i) = vec2fTCoord;
                    }
                }
            }
        }
    }

    // ����connectivity.
    int* aiLocalIndex = pIB->GetData();
    int iT = 0;
    for( int iR0 = iRSm1, iR1 = 0; iR1 < iRadialSamples; iR0 = iR1++ )
    {
        aiLocalIndex[0] = 0;
        aiLocalIndex[1] = 1 + iSSm1*iR1;
        aiLocalIndex[2] = 1 + iSSm1*iR0;
        aiLocalIndex += 3;
        iT++;
        for( int iS = 1; iS < iSSm1; iS++, aiLocalIndex += 6 )
        {
            int i00 = iS + iSSm1*iR0;
            int i01 = iS + iSSm1*iR1;
            int i10 = i00 + 1;
            int i11 = i01 + 1;
            aiLocalIndex[0] = i00;
            aiLocalIndex[1] = i11;
            aiLocalIndex[2] = i10;
            aiLocalIndex[3] = i00;
            aiLocalIndex[4] = i01;
            aiLocalIndex[5] = i11;
            iT += 2;
        }
    }
    SE_ASSERT( iT == iTCount );

    TransformData(pVB);
    TriMesh* pMesh = SE_NEW TriMesh(pVB, pIB);

    return pMesh;
}
//----------------------------------------------------------------------------
TriMesh* StandardMesh::Box(float fXExtent, float fYExtent, float fZExtent)
{
    int iVCount = 24;
    int iTCount = 12;
    VertexBuffer* pVB = SE_NEW VertexBuffer(m_Attr, iVCount);
    IndexBuffer* pIB = SE_NEW IndexBuffer(3 * iTCount);

    // ����geometry.
    pVB->Position3(0) = Vector3f(-fXExtent, -fYExtent, -fZExtent);
    pVB->Position3(1) = Vector3f(-fXExtent, -fYExtent, -fZExtent);
    pVB->Position3(2) = Vector3f(-fXExtent, -fYExtent, -fZExtent);
    pVB->Position3(3) = Vector3f(+fXExtent, -fYExtent, -fZExtent);
    pVB->Position3(4) = Vector3f(+fXExtent, -fYExtent, -fZExtent);
    pVB->Position3(5) = Vector3f(+fXExtent, -fYExtent, -fZExtent);
    pVB->Position3(6) = Vector3f(+fXExtent, +fYExtent, -fZExtent);
    pVB->Position3(7) = Vector3f(+fXExtent, +fYExtent, -fZExtent);
    pVB->Position3(8) = Vector3f(+fXExtent, +fYExtent, -fZExtent);
    pVB->Position3(9) = Vector3f(-fXExtent, +fYExtent, -fZExtent);
    pVB->Position3(10) = Vector3f(-fXExtent, +fYExtent, -fZExtent);
    pVB->Position3(11) = Vector3f(-fXExtent, +fYExtent, -fZExtent);
    pVB->Position3(12) = Vector3f(-fXExtent, -fYExtent, +fZExtent);
    pVB->Position3(13) = Vector3f(-fXExtent, -fYExtent, +fZExtent);
    pVB->Position3(14) = Vector3f(-fXExtent, -fYExtent, +fZExtent);
    pVB->Position3(15) = Vector3f(+fXExtent, -fYExtent, +fZExtent);
    pVB->Position3(16) = Vector3f(+fXExtent, -fYExtent, +fZExtent);
    pVB->Position3(17) = Vector3f(+fXExtent, -fYExtent, +fZExtent);
    pVB->Position3(18) = Vector3f(+fXExtent, +fYExtent, +fZExtent);
    pVB->Position3(19) = Vector3f(+fXExtent, +fYExtent, +fZExtent);
    pVB->Position3(20) = Vector3f(+fXExtent, +fYExtent, +fZExtent);
    pVB->Position3(21) = Vector3f(-fXExtent, +fYExtent, +fZExtent);
    pVB->Position3(22) = Vector3f(-fXExtent, +fYExtent, +fZExtent);
    pVB->Position3(23) = Vector3f(-fXExtent, +fYExtent, +fZExtent);

    if( m_Attr.GetMaxTCoords() > 0 )
    {
        for( int iUnit = 0; iUnit < m_Attr.GetMaxTCoords(); iUnit++ )
        {
            if( m_Attr.HasTCoord(iUnit) )
            {
                pVB->TCoord2(iUnit, 0) = Vector2f(0.25f, 0.75f);
                pVB->TCoord2(iUnit, 1) = Vector2f(0.25f, 0.75f);
                pVB->TCoord2(iUnit, 2) = Vector2f(0.25f, 0.75f);
                pVB->TCoord2(iUnit, 3) = Vector2f(0.75f, 0.75f);
                pVB->TCoord2(iUnit, 4) = Vector2f(0.75f, 0.75f);
                pVB->TCoord2(iUnit, 5) = Vector2f(0.75f, 0.75f);
                pVB->TCoord2(iUnit, 6) = Vector2f(0.75f, 0.25f);
                pVB->TCoord2(iUnit, 7) = Vector2f(0.75f, 0.25f);
                pVB->TCoord2(iUnit, 8) = Vector2f(0.75f, 0.25f);
                pVB->TCoord2(iUnit, 9) = Vector2f(0.25f, 0.25f);
                pVB->TCoord2(iUnit, 10) = Vector2f(0.25f, 0.25f);
                pVB->TCoord2(iUnit, 11) = Vector2f(0.25f, 0.25f);
                pVB->TCoord2(iUnit, 12) = Vector2f(0.0f, 1.0f);
                pVB->TCoord2(iUnit, 13) = Vector2f(0.0f, 1.0f);
                pVB->TCoord2(iUnit, 14) = Vector2f(0.0f, 1.0f);
                pVB->TCoord2(iUnit, 15) = Vector2f(1.0f, 1.0f);
                pVB->TCoord2(iUnit, 16) = Vector2f(1.0f, 1.0f);
                pVB->TCoord2(iUnit, 17) = Vector2f(1.0f, 1.0f);
                pVB->TCoord2(iUnit, 18) = Vector2f(1.0f, 0.0f);
                pVB->TCoord2(iUnit, 19) = Vector2f(1.0f, 0.0f);
                pVB->TCoord2(iUnit, 20) = Vector2f(1.0f, 0.0f);
                pVB->TCoord2(iUnit, 21) = Vector2f(0.0f, 0.0f);
                pVB->TCoord2(iUnit, 22) = Vector2f(0.0f, 0.0f);
                pVB->TCoord2(iUnit, 23) = Vector2f(0.0f, 0.0f);
            }
        }
    }

    // ����connectivity (outside view).
    int* aiIndex = pIB->GetData();
    aiIndex[ 0] = 0;   aiIndex[ 1] = 6;   aiIndex[ 2] = 3;
    aiIndex[ 3] = 0;   aiIndex[ 4] = 9;   aiIndex[ 5] = 6;
    aiIndex[ 6] = 10;  aiIndex[ 7] = 1;   aiIndex[ 8] = 12;
    aiIndex[ 9] = 21;  aiIndex[10] = 10;  aiIndex[11] = 12;

    aiIndex[12] = 22;  aiIndex[13] = 13;  aiIndex[14] = 15;
    aiIndex[15] = 22;  aiIndex[16] = 15;  aiIndex[17] = 18;

    aiIndex[18] = 7;   aiIndex[19] = 19;  aiIndex[20] = 4;
    aiIndex[21] = 19;  aiIndex[22] = 16;  aiIndex[23] = 4;

    aiIndex[24] = 11;  aiIndex[25] = 23;  aiIndex[26] = 8;
    aiIndex[27] = 23;  aiIndex[28] = 20;  aiIndex[29] = 8;
    aiIndex[30] = 2;   aiIndex[31] = 5;   aiIndex[32] = 14;
    aiIndex[33] = 14;  aiIndex[34] = 5;   aiIndex[35] = 17;

    if( m_bInside )
    {
        ReverseTriangleOrder(iTCount, aiIndex);
    }

    TransformData(pVB);
    TriMesh* pMesh = SE_NEW TriMesh(pVB, pIB);
    pMesh->UpdateMS(true);

    return pMesh;
}
//----------------------------------------------------------------------------
TriMesh* StandardMesh::Cylinder(int iAxisSamples, int iRadialSamples, 
    float fRadius, float fHeight, bool bOpen)
{
    TriMesh* pMesh;

    if( bOpen )
    {
        int iVCount = iAxisSamples * (iRadialSamples + 1);
        int iTCount = 2 * (iAxisSamples - 1) * iRadialSamples;
        VertexBuffer* pVB = SE_NEW VertexBuffer(m_Attr, iVCount);
        IndexBuffer* pIB = SE_NEW IndexBuffer(3 * iTCount);

        // generate geometry.
        float fInvRS = 1.0f / (float)iRadialSamples;
        float fInvASm1 = 1.0f / (float)(iAxisSamples - 1);
        float fHalfHeight = 0.5f * fHeight;
        int iR, iA, iAStart, i, iUnit;
        Vector2f vec2fTCoord;

        // Generate points on the unit circle to be used in computing the
        // mesh points on a cylinder slice.
        float* afSin = SE_NEW float[iRadialSamples + 1];
        float* afCos = SE_NEW float[iRadialSamples + 1];
        for( iR = 0; iR < iRadialSamples; iR++ )
        {
            float fAngle = Mathf::TWO_PI * fInvRS * iR;
            afCos[iR] = Mathf::Cos(fAngle);
            afSin[iR] = Mathf::Sin(fAngle);
        }
        afSin[iRadialSamples] = afSin[0];
        afCos[iRadialSamples] = afCos[0];

        // generate the cylinder itself
        for( iA = 0, i = 0; iA < iAxisSamples; iA++ )
        {
            float fAxisFraction = iA * fInvASm1;  // in [0, 1]
            float fZ = -fHalfHeight + fHeight*fAxisFraction;

            // compute center of slice
            Vector3f vec3fSliceCenter(0.0f, 0.0f, fZ);

            // compute slice vertices with duplication at end point
            int iSave = i;
            for( iR = 0; iR < iRadialSamples; iR++ )
            {
                float fRadialFraction = iR * fInvRS;  // in [0, 1)
                Vector3f vec3fNormal(afCos[iR], afSin[iR], 0.0f);
                pVB->Position3(i) = vec3fSliceCenter + fRadius*vec3fNormal;
                if( m_Attr.HasNormal() )
                {
                    if( m_bInside )
                    {
                        pVB->Normal3(i) = -vec3fNormal;
                    }
                    else
                    {
                        pVB->Normal3(i) = vec3fNormal;
                    }
                }

                if( m_Attr.GetMaxTCoords() > 0 )
                {
                    vec2fTCoord = Vector2f(fRadialFraction, fAxisFraction);
                    for( iUnit = 0; iUnit < m_Attr.GetMaxTCoords(); iUnit++ )
                    {
                        if( m_Attr.HasTCoord(iUnit) )
                        {
                            pVB->TCoord2(iUnit, i) = vec2fTCoord;
                        }
                    }
                }

                i++;
            }

            pVB->Position3(i) = pVB->Position3(iSave);
            if( m_Attr.HasNormal() )
            {
                pVB->Normal3(i) = pVB->Normal3(iSave);
            }

            if( m_Attr.GetMaxTCoords() > 0 )
            {
                vec2fTCoord = Vector2f(1.0f, fAxisFraction);
                for( iUnit = 0; iUnit < m_Attr.GetMaxTCoords(); iUnit++ )
                {
                    if( m_Attr.HasTCoord(iUnit) )
                    {
                        pVB->TCoord2(iUnit, i) = vec2fTCoord;
                    }
                }
            }

            i++;
        }

        // generate connectivity.
        int* aiLocalIndex = pIB->GetData();
        for( iA = 0, iAStart = 0; iA < iAxisSamples-1; iA++ )
        {
            int i0 = iAStart;
            int i1 = i0 + 1;
            iAStart += iRadialSamples + 1;
            int i2 = iAStart;
            int i3 = i2 + 1;
            for( i = 0; i < iRadialSamples; i++, aiLocalIndex += 6 )
            {
                if( m_bInside )
                {
                    aiLocalIndex[0] = i0++;
                    aiLocalIndex[1] = i2;
                    aiLocalIndex[2] = i1;
                    aiLocalIndex[3] = i1++;
                    aiLocalIndex[4] = i2++;
                    aiLocalIndex[5] = i3++;
                }
                else // outside view
                {
                    aiLocalIndex[0] = i0++;
                    aiLocalIndex[1] = i1;
                    aiLocalIndex[2] = i2;
                    aiLocalIndex[3] = i1++;
                    aiLocalIndex[4] = i3++;
                    aiLocalIndex[5] = i2++;
                }
            }
        }

        SE_DELETE[] afCos;
        SE_DELETE[] afSin;

        TransformData(pVB);
        pMesh = SE_NEW TriMesh(pVB, pIB);
    }
    else
    {
        pMesh = Sphere(iAxisSamples, iRadialSamples, fRadius);
        VertexBuffer* pVB = pMesh->VBuffer;
        int iVCount = pVB->GetVertexCount();

        // flatten sphere at poles
        float fHDiv2 = 0.5f * fHeight;
        pVB->Position3(iVCount - 2).Z = -fHDiv2;  // south pole
        pVB->Position3(iVCount - 1).Z = fHDiv2;  // north pole

        // remap z-values to [-h/2, h/2]
        float fZFactor = 2.0f / (iAxisSamples - 1);
        float fTmp0 = fRadius * (-1.0f + fZFactor);
        float fTmp1 = 1.0f / (fRadius*(+1.0f - fZFactor));
        for( int i = 0; i < iVCount - 2; i++ )
        {
            pVB->Position3(i).Z = fHDiv2 * (-1.0f + fTmp1*(
                pVB->Position3(i).Z - fTmp0));
            float fX = pVB->Position3(i).X, fY = pVB->Position3(i).Y;
            float fAdjust = fRadius*Mathf::InvSqrt(fX*fX + fY*fY);
            pVB->Position3(i).X *= fAdjust;
            pVB->Position3(i).Y *= fAdjust;
        }
        TransformData(pVB);
        pMesh->UpdateMS(true);
    }

    // The duplication of vertices at the seam cause the automatically
    // generated bounding volume to be slightly off center.  Reset the bound
    // to use the true information.
    float fMaxDist = Mathf::Sqrt(fRadius*fRadius + fHeight*fHeight);
    pMesh->ModelBound->SetCenter(Vector3f::ZERO);
    pMesh->ModelBound->SetRadius(fMaxDist);

    return pMesh;
}
//----------------------------------------------------------------------------
TriMesh* StandardMesh::Sphere(int iZSamples, int iRadialSamples, 
    float fRadius)
{
    int iZSm1 = iZSamples - 1, iZSm2 = iZSamples - 2, iZSm3 = iZSamples - 3;
    int iRSp1 = iRadialSamples + 1;
    int iVCount = iZSm2*iRSp1 + 2;
    int iTCount = 2 * iZSm2 * iRadialSamples;
    VertexBuffer* pVB = SE_NEW VertexBuffer(m_Attr, iVCount);
    IndexBuffer* pIB = SE_NEW IndexBuffer(3 * iTCount);

    // generate geometry
    float fInvRS = 1.0f / (float)iRadialSamples;
    float fZFactor = 2.0f / (float)iZSm1;
    int iR, iZ, iZStart, i, iUnit;
    Vector2f vec2fTCoord;

    // Generate points on the unit circle to be used in computing the mesh
    // points on a cylinder slice.
    float* afSin = SE_NEW float[iRSp1];
    float* afCos = SE_NEW float[iRSp1];
    for( iR = 0; iR < iRadialSamples; iR++ )
    {
        float fAngle = Mathf::TWO_PI * fInvRS * iR;
        afCos[iR] = Mathf::Cos(fAngle);
        afSin[iR] = Mathf::Sin(fAngle);
    }
    afSin[iRadialSamples] = afSin[0];
    afCos[iRadialSamples] = afCos[0];

    // generate the cylinder itself
    for( iZ = 1, i = 0; iZ < iZSm1; iZ++ )
    {
        float fZFraction = -1.0f + fZFactor*iZ;  // in (-1, 1)
        float fZ = fRadius * fZFraction;

        // compute center of slice
        Vector3f vec3fSliceCenter(0.0f, 0.0f, fZ);

        // compute radius of slice
        float fSliceRadius = Mathf::Sqrt(Mathf::FAbs(fRadius*fRadius - fZ*fZ));

        // compute slice vertices with duplication at end point
        Vector3f vec3fNormal;
        int iSave = i;
        for( iR = 0; iR < iRadialSamples; iR++ )
        {
            float fRadialFraction = iR * fInvRS;  // in [0, 1)
            Vector3f vec3fRadial(afCos[iR], afSin[iR], 0.0f);
            pVB->Position3(i) = vec3fSliceCenter + fSliceRadius*vec3fRadial;
            if( m_Attr.HasNormal() )
            {
                vec3fNormal = pVB->Position3(i);
                vec3fNormal.Normalize();
                if( m_bInside )
                {
                    pVB->Normal3(i) = -vec3fNormal;
                }
                else
                {
                    pVB->Normal3(i) = vec3fNormal;
                }
            }

            if( m_Attr.GetMaxTCoords() > 0 )
            {
                vec2fTCoord = Vector2f(fRadialFraction, 
                    0.5f*(fZFraction + 1.0f));
                for( iUnit = 0; iUnit < m_Attr.GetMaxTCoords(); iUnit++ )
                {
                    if( m_Attr.HasTCoord(iUnit) )
                    {
                        pVB->TCoord2(iUnit, i) = vec2fTCoord;
                    }
                }
            }

            i++;
        }

        pVB->Position3(i) = pVB->Position3(iSave);
        if( m_Attr.HasNormal() )
        {
            pVB->Normal3(i) = pVB->Normal3(iSave);
        }

        if( m_Attr.GetMaxTCoords() > 0 )
        {
            vec2fTCoord = Vector2f(1.0f, 0.5f*(fZFraction + 1.0f));
            for( iUnit = 0; iUnit < m_Attr.GetMaxTCoords(); iUnit++ )
            {
                if( m_Attr.HasTCoord(iUnit) )
                {
                    pVB->TCoord2(iUnit, i) = vec2fTCoord;
                }
            }
        }

        i++;
    }

    // south pole
    pVB->Position3(i) = -fRadius*Vector3f::UNIT_Z;
    if( m_Attr.HasNormal() )
    {
        if( m_bInside )
        {
            pVB->Normal3(i) = Vector3f::UNIT_Z;
        }
        else
        {
            pVB->Normal3(i) = -Vector3f::UNIT_Z;
        }
    }

    if( m_Attr.GetMaxTCoords() > 0 )
    {
        vec2fTCoord = Vector2f(0.5f, 0.5f);
        for( iUnit = 0; iUnit < m_Attr.GetMaxTCoords(); iUnit++ )
        {
            if( m_Attr.HasTCoord(iUnit) )
            {
                pVB->TCoord2(iUnit, i) = vec2fTCoord;
            }
        }
    }

    i++;

    // north pole
    pVB->Position3(i) = fRadius * Vector3f::UNIT_Z;
    if( m_Attr.HasNormal() )
    {
        if( m_bInside )
        {
            pVB->Normal3(i) = -Vector3f::UNIT_Z;
        }
        else
        {
            pVB->Normal3(i) = Vector3f::UNIT_Z;
        }
    }

    if( m_Attr.GetMaxTCoords() > 0 )
    {
        vec2fTCoord = Vector2f(0.5f, 1.0f);
        for( iUnit = 0; iUnit < m_Attr.GetMaxTCoords(); iUnit++ )
        {
            if( m_Attr.HasTCoord(iUnit) )
            {
                pVB->TCoord2(iUnit, i) = vec2fTCoord;
            }
        }
    }

    i++;
    SE_ASSERT( i == iVCount );

    // generate connectivity
    int* aiLocalIndex = pIB->GetData();
    for( iZ = 0, iZStart = 0; iZ < iZSm3; iZ++ )
    {
        int i0 = iZStart;
        int i1 = i0 + 1;
        iZStart += iRSp1;
        int i2 = iZStart;
        int i3 = i2 + 1;
        for( i = 0; i < iRadialSamples; i++, aiLocalIndex += 6 )
        {
            if( m_bInside )
            {
                aiLocalIndex[0] = i0++;
                aiLocalIndex[1] = i2;
                aiLocalIndex[2] = i1;
                aiLocalIndex[3] = i1++;
                aiLocalIndex[4] = i2++;
                aiLocalIndex[5] = i3++;
            }
            else  // inside view
            {
                aiLocalIndex[0] = i0++;
                aiLocalIndex[1] = i1;
                aiLocalIndex[2] = i2;
                aiLocalIndex[3] = i1++;
                aiLocalIndex[4] = i3++;
                aiLocalIndex[5] = i2++;
            }
        }
    }

    // south pole triangles
    int iVCm2 = iVCount - 2;
    for( i = 0; i < iRadialSamples; i++, aiLocalIndex += 3 )
    {
        if( m_bInside )
        {
            aiLocalIndex[0] = i;
            aiLocalIndex[1] = i + 1;
            aiLocalIndex[2] = iVCm2;
        }
        else  // inside view
        {
            aiLocalIndex[0] = i;
            aiLocalIndex[1] = iVCm2;
            aiLocalIndex[2] = i + 1;
        }
    }

    // north pole triangles
    int iVCm1 = iVCount - 1, iOffset = iZSm3 * iRSp1;
    for( i = 0; i < iRadialSamples; i++, aiLocalIndex += 3 )
    {
        if( m_bInside )
        {
            aiLocalIndex[0] = i + iOffset;
            aiLocalIndex[1] = iVCm1;
            aiLocalIndex[2] = i + 1 + iOffset;
        }
        else  // inside view
        {
            aiLocalIndex[0] = i + iOffset;
            aiLocalIndex[1] = i + 1 + iOffset;
            aiLocalIndex[2] = iVCm1;
        }
    }

    SE_ASSERT( aiLocalIndex == pIB->GetData() + 3*iTCount );

    SE_DELETE[] afCos;
    SE_DELETE[] afSin;

    TransformData(pVB);
    TriMesh* pMesh = SE_NEW TriMesh(pVB, pIB);

    // The duplication of vertices at the seam cause the automatically
    // generated bounding volume to be slightly off center.  Reset the bound
    // to use the true information.
    pMesh->ModelBound->SetCenter(Vector3f::ZERO);
    pMesh->ModelBound->SetRadius(fRadius);

    return pMesh;
}
//----------------------------------------------------------------------------
TriMesh* StandardMesh::Torus(int iCircleSamples, int iRadialSamples, 
    float fOuterRadius, float fInnerRadius)
{
    int iVCount = (iCircleSamples + 1) * (iRadialSamples + 1);
    int iTCount = 2 * iCircleSamples * iRadialSamples;
    VertexBuffer* pVB = SE_NEW VertexBuffer(m_Attr, iVCount);
    IndexBuffer* pIB = SE_NEW IndexBuffer(3 * iTCount);

    // generate geometry
    float fInvCS = 1.0f / (float)iCircleSamples;
    float fInvRS = 1.0f / (float)iRadialSamples;
    int iC, iR, i, iUnit;
    Vector2f vec2fTCoord;

    // generate the cylinder itself
    for( iC = 0, i = 0; iC < iCircleSamples; iC++ )
    {
        // compute center point on torus circle at specified angle
        float fCircleFraction = iC * fInvCS;  // in [0, 1)
        float fTheta = Mathf::TWO_PI * fCircleFraction;
        float fCosTheta = Mathf::Cos(fTheta);
        float fSinTheta = Mathf::Sin(fTheta);
        Vector3f vec3fRadial(fCosTheta, fSinTheta, 0.0f);
        Vector3f vec3fTorusMiddle = fOuterRadius * vec3fRadial;

        // compute slice vertices with duplication at end point
        int iSave = i;
        for( iR = 0; iR < iRadialSamples; iR++ )
        {
            float fRadialFraction = iR * fInvRS;  // in [0, 1)
            float fPhi = Mathf::TWO_PI * fRadialFraction;
            float fCosPhi = Mathf::Cos(fPhi);
            float fSinPhi = Mathf::Sin(fPhi);
            Vector3f vec3fNormal = fCosPhi*vec3fRadial + fSinPhi*Vector3f::UNIT_Z;
            pVB->Position3(i) = vec3fTorusMiddle + fInnerRadius*vec3fNormal;
            if( m_Attr.HasNormal() )
            {
                if( m_bInside )
                {
                    pVB->Normal3(i) = -vec3fNormal;
                }
                else
                {
                    pVB->Normal3(i) = vec3fNormal;
                }
            }

            if( m_Attr.GetMaxTCoords() > 0 )
            {
                vec2fTCoord = Vector2f(fRadialFraction, fCircleFraction);
                for( iUnit = 0; iUnit < m_Attr.GetMaxTCoords(); iUnit++ )
                {
                    if( m_Attr.HasTCoord(iUnit) )
                    {
                        pVB->TCoord2(iUnit, i) = vec2fTCoord;
                    }
                }
            }

            i++;
        }

        pVB->Position3(i) = pVB->Position3(iSave);
        if( m_Attr.HasNormal() )
        {
            pVB->Normal3(i) = pVB->Normal3(iSave);
        }

        if( m_Attr.GetMaxTCoords() > 0 )
        {
            vec2fTCoord = Vector2f(1.0f, fCircleFraction);
            for( iUnit = 0; iUnit < m_Attr.GetMaxTCoords(); iUnit++ )
            {
                if( m_Attr.HasTCoord(iUnit) )
                {
                    pVB->TCoord2(iUnit, i) = vec2fTCoord;
                }
            }
        }

        i++;
    }

    // duplicate the cylinder ends to form a torus
    for( iR = 0; iR <= iRadialSamples; iR++, i++ )
    {
        pVB->Position3(i) = pVB->Position3(iR);
        if( m_Attr.HasNormal() )
        {
            pVB->Normal3(i) = pVB->Normal3(iR);
        }

        if( m_Attr.GetMaxTCoords() > 0 )
        {
            vec2fTCoord = Vector2f(pVB->TCoord2(0, iR).X, 1.0f);
            for( iUnit = 0; iUnit < m_Attr.GetMaxTCoords(); iUnit++ )
            {
                if( m_Attr.HasTCoord(iUnit) )
                {
                    pVB->TCoord2(iUnit, i) = vec2fTCoord;
                }
            }
        }
    }
    SE_ASSERT( i == iVCount );

    // generate connectivity
    int* aiLocalIndex = pIB->GetData();
    int iCStart = 0;
    for( iC = 0; iC < iCircleSamples; iC++ )
    {
        int i0 = iCStart;
        int i1 = i0 + 1;
        iCStart += iRadialSamples + 1;
        int i2 = iCStart;
        int i3 = i2 + 1;
        for( i = 0; i < iRadialSamples; i++, aiLocalIndex += 6 )
        {
            if( m_bInside )
            {
                aiLocalIndex[0] = i0++;
                aiLocalIndex[1] = i1;
                aiLocalIndex[2] = i2;
                aiLocalIndex[3] = i1++;
                aiLocalIndex[4] = i3++;
                aiLocalIndex[5] = i2++;
            }
            else  // inside view
            {
                aiLocalIndex[0] = i0++;
                aiLocalIndex[1] = i2;
                aiLocalIndex[2] = i1;
                aiLocalIndex[3] = i1++;
                aiLocalIndex[4] = i2++;
                aiLocalIndex[5] = i3++;
            }
        }
    }

    TransformData(pVB);
    TriMesh* pMesh = SE_NEW TriMesh(pVB, pIB);

    // The duplication of vertices at the seam cause the automatically
    // generated bounding volume to be slightly off center.  Reset the bound
    // to use the true information.
    pMesh->ModelBound->SetCenter(Vector3f::ZERO);
    pMesh->ModelBound->SetRadius(fOuterRadius);

    return pMesh;
}
//----------------------------------------------------------------------------
TriMesh* StandardMesh::Tetrahedron()
{
    float fSqrt2Div3 = Mathf::Sqrt(2.0f) / 3.0f;
    float fSqrt6Div3 = Mathf::Sqrt(6.0f) / 3.0f;
    float f2Sqrt2Div3 = 2.0f*fSqrt2Div3;
    float fOneThird = 1.0f / 3.0f;

    int iVCount = 12;
    int iTCount = 4;
    VertexBuffer* pVB = SE_NEW VertexBuffer(m_Attr, iVCount);
    IndexBuffer* pIB = SE_NEW IndexBuffer(3 * iTCount);

    pVB->Position3(0) = Vector3f(0.0f, 0.0f, 1.0f);
    pVB->Position3(1) = Vector3f(0.0f, 0.0f, 1.0f);
    pVB->Position3(2) = Vector3f(0.0f, 0.0f, 1.0f);

    pVB->Position3(3) = Vector3f(f2Sqrt2Div3, 0.0f, -fOneThird);
    pVB->Position3(4) = Vector3f(f2Sqrt2Div3, 0.0f, -fOneThird);
    pVB->Position3(5) = Vector3f(f2Sqrt2Div3, 0.0f, -fOneThird);

    pVB->Position3(6) = Vector3f(-fSqrt2Div3, fSqrt6Div3, -fOneThird);
    pVB->Position3(7) = Vector3f(-fSqrt2Div3, fSqrt6Div3, -fOneThird);
    pVB->Position3(8) = Vector3f(-fSqrt2Div3, fSqrt6Div3, -fOneThird);

    pVB->Position3(9) = Vector3f(-fSqrt2Div3, -fSqrt6Div3, -fOneThird);
    pVB->Position3(10) = Vector3f(-fSqrt2Div3, -fSqrt6Div3, -fOneThird);
    pVB->Position3(11) = Vector3f(-fSqrt2Div3, -fSqrt6Div3, -fOneThird);

    int* aiIndex = pIB->GetData();
    aiIndex[ 0] = 0;  aiIndex[ 1] = 3;  aiIndex[ 2] = 6;
    aiIndex[ 3] = 9;  aiIndex[ 4] = 7;  aiIndex[ 5] = 4;
    aiIndex[ 6] = 8;  aiIndex[ 7] = 10; aiIndex[ 8] = 1;
    aiIndex[ 9] = 5;  aiIndex[10] = 2;  aiIndex[11] = 11;

    CreatePlatonicUVs(pVB);
    if( m_bInside )
    {
        ReverseTriangleOrder(iTCount, aiIndex);
    }

    TransformData(pVB);
    TriMesh* pMesh = SE_NEW TriMesh(pVB, pIB);
    pMesh->UpdateMS(true);

    return pMesh;
}
//----------------------------------------------------------------------------
TriMesh* StandardMesh::Hexahedron()
{
    float fSqrtThird = Mathf::Sqrt(1.0f / 3.0f);

    int iVCount = 8;
    int iTCount = 12;
    VertexBuffer* pVB = SE_NEW VertexBuffer(m_Attr, iVCount);
    IndexBuffer* pIB = SE_NEW IndexBuffer(3 * iTCount);

    pVB->Position3(0) = Vector3f(-fSqrtThird, -fSqrtThird, -fSqrtThird);
    pVB->Position3(1) = Vector3f( fSqrtThird, -fSqrtThird, -fSqrtThird);
    pVB->Position3(2) = Vector3f( fSqrtThird, fSqrtThird, -fSqrtThird);
    pVB->Position3(3) = Vector3f(-fSqrtThird, fSqrtThird, -fSqrtThird);
    pVB->Position3(4) = Vector3f(-fSqrtThird, -fSqrtThird, fSqrtThird);
    pVB->Position3(5) = Vector3f( fSqrtThird, -fSqrtThird, fSqrtThird);
    pVB->Position3(6) = Vector3f( fSqrtThird, fSqrtThird, fSqrtThird);
    pVB->Position3(7) = Vector3f(-fSqrtThird, fSqrtThird, fSqrtThird);

    int* aiIndex = pIB->GetData();
    aiIndex[ 0] = 0;  aiIndex[ 1] = 3;  aiIndex[ 2] = 2;
    aiIndex[ 3] = 0;  aiIndex[ 4] = 2;  aiIndex[ 5] = 1;
    aiIndex[ 6] = 0;  aiIndex[ 7] = 1;  aiIndex[ 8] = 5;
    aiIndex[ 9] = 0;  aiIndex[10] = 5;  aiIndex[11] = 4;
    aiIndex[12] = 0;  aiIndex[13] = 4;  aiIndex[14] = 7;
    aiIndex[15] = 0;  aiIndex[16] = 7;  aiIndex[17] = 3;
    aiIndex[18] = 6;  aiIndex[19] = 5;  aiIndex[20] = 1;
    aiIndex[21] = 6;  aiIndex[22] = 1;  aiIndex[23] = 2;
    aiIndex[24] = 6;  aiIndex[25] = 2;  aiIndex[26] = 3;
    aiIndex[27] = 6;  aiIndex[28] = 3;  aiIndex[29] = 7;
    aiIndex[30] = 6;  aiIndex[31] = 7;  aiIndex[32] = 4;
    aiIndex[33] = 6;  aiIndex[34] = 4;  aiIndex[35] = 5;

    CreatePlatonicNormals(pVB);
    CreatePlatonicUVs(pVB);
    if( m_bInside )
    {
        ReverseTriangleOrder(iTCount, aiIndex);
    }

    TransformData(pVB);
    TriMesh* pMesh = SE_NEW TriMesh(pVB, pIB);

    return pMesh;
}
//----------------------------------------------------------------------------
TriMesh* StandardMesh::Octahedron()
{
    int iVCount = 6;
    int iTCount = 8;
    VertexBuffer* pVB = SE_NEW VertexBuffer(m_Attr, iVCount);
    IndexBuffer* pIB = SE_NEW IndexBuffer(3 * iTCount);

    pVB->Position3(0) = Vector3f( 1.0f, 0.0f, 0.0f);
    pVB->Position3(1) = Vector3f(-1.0f, 0.0f, 0.0f);
    pVB->Position3(2) = Vector3f( 0.0f, 1.0f, 0.0f);
    pVB->Position3(3) = Vector3f( 0.0f, -1.0f, 0.0f);
    pVB->Position3(4) = Vector3f( 0.0f, 0.0f, 1.0f);
    pVB->Position3(5) = Vector3f( 0.0f, 0.0f, -1.0f);

    int* aiIndex = pIB->GetData();
    aiIndex[ 0] = 4;  aiIndex[ 1] = 0;  aiIndex[ 2] = 2;
    aiIndex[ 3] = 4;  aiIndex[ 4] = 2;  aiIndex[ 5] = 1;
    aiIndex[ 6] = 4;  aiIndex[ 7] = 1;  aiIndex[ 8] = 3;
    aiIndex[ 9] = 4;  aiIndex[10] = 3;  aiIndex[11] = 0;
    aiIndex[12] = 5;  aiIndex[13] = 2;  aiIndex[14] = 0;
    aiIndex[15] = 5;  aiIndex[16] = 1;  aiIndex[17] = 2;
    aiIndex[18] = 5;  aiIndex[19] = 3;  aiIndex[20] = 1;
    aiIndex[21] = 5;  aiIndex[22] = 0;  aiIndex[23] = 3;

    CreatePlatonicNormals(pVB);
    CreatePlatonicUVs(pVB);
    if( m_bInside )
    {
        ReverseTriangleOrder(iTCount, aiIndex);
    }

    TransformData(pVB);
    TriMesh* pMesh = SE_NEW TriMesh(pVB, pIB);

    return pMesh;
}
//----------------------------------------------------------------------------
TriMesh* StandardMesh::Dodecahedron()
{
    float fA = 1.0f / Mathf::Sqrt(3.0f);
    float fB = Mathf::Sqrt((3.0f - Mathf::Sqrt(5.0f))/6.0f);
    float fC = Mathf::Sqrt((3.0f + Mathf::Sqrt(5.0f))/6.0f);

    int iVCount = 20;
    int iTCount = 36;
    VertexBuffer* pVB = SE_NEW VertexBuffer(m_Attr, iVCount);
    IndexBuffer* pIB = SE_NEW IndexBuffer(3 * iTCount);

    pVB->Position3( 0) = Vector3f( fA, fA, fA);
    pVB->Position3( 1) = Vector3f( fA, fA, -fA);
    pVB->Position3( 2) = Vector3f( fA, -fA, fA);
    pVB->Position3( 3) = Vector3f( fA, -fA, -fA);
    pVB->Position3( 4) = Vector3f(-fA, fA, fA);
    pVB->Position3( 5) = Vector3f(-fA, fA, -fA);
    pVB->Position3( 6) = Vector3f(-fA, -fA, fA);
    pVB->Position3( 7) = Vector3f(-fA, -fA, -fA);
    pVB->Position3( 8) = Vector3f(  fB,  fC, 0.0f);
    pVB->Position3( 9) = Vector3f( -fB,  fC, 0.0f);
    pVB->Position3(10) = Vector3f(  fB, -fC, 0.0f);
    pVB->Position3(11) = Vector3f( -fB, -fC, 0.0f);
    pVB->Position3(12) = Vector3f(  fC, 0.0f,  fB);
    pVB->Position3(13) = Vector3f(  fC, 0.0f, -fB);
    pVB->Position3(14) = Vector3f( -fC, 0.0f,  fB);
    pVB->Position3(15) = Vector3f( -fC, 0.0f, -fB);
    pVB->Position3(16) = Vector3f(0.0f,   fB,  fC);
    pVB->Position3(17) = Vector3f(0.0f,  -fB,  fC);
    pVB->Position3(18) = Vector3f(0.0f,   fB, -fC);
    pVB->Position3(19) = Vector3f(0.0f,  -fB, -fC);

    int* aiIndex = pIB->GetData();
    //aiIndex[  0] =  0;  aiIndex[  1] =  9;  aiIndex[  2] =  8;
    //aiIndex[  3] =  0;  aiIndex[  4] =  4;  aiIndex[  5] =  9;
    //aiIndex[  6] =  0;  aiIndex[  7] = 16;  aiIndex[  8] =  4;
    //aiIndex[  9] =  0;  aiIndex[ 10] = 13;  aiIndex[ 11] = 12;
    //aiIndex[ 12] =  0;  aiIndex[ 13] =  1;  aiIndex[ 14] = 13;
    //aiIndex[ 15] =  0;  aiIndex[ 16] =  8;  aiIndex[ 17] =  1;
    //aiIndex[ 18] =  0;  aiIndex[ 19] = 17;  aiIndex[ 20] = 16;
    //aiIndex[ 21] =  0;  aiIndex[ 22] =  2;  aiIndex[ 23] = 17;
    //aiIndex[ 24] =  0;  aiIndex[ 25] = 12;  aiIndex[ 26] =  2;
    //aiIndex[ 27] =  8;  aiIndex[ 28] = 18;  aiIndex[ 29] =  1;
    //aiIndex[ 30] =  8;  aiIndex[ 31] =  5;  aiIndex[ 32] = 18;
    //aiIndex[ 33] =  8;  aiIndex[ 34] =  9;  aiIndex[ 35] =  5;
    //aiIndex[ 36] = 12;  aiIndex[ 37] = 10;  aiIndex[ 38] =  2;
    //aiIndex[ 39] = 12;  aiIndex[ 40] =  3;  aiIndex[ 41] = 10;
    //aiIndex[ 42] = 12;  aiIndex[ 43] = 13;  aiIndex[ 44] =  3;
    //aiIndex[ 45] = 16;  aiIndex[ 46] = 14;  aiIndex[ 47] =  4;
    //aiIndex[ 48] = 16;  aiIndex[ 49] =  6;  aiIndex[ 50] = 14;
    //aiIndex[ 51] = 16;  aiIndex[ 52] = 17;  aiIndex[ 53] =  6;
    //aiIndex[ 54] =  9;  aiIndex[ 55] = 15;  aiIndex[ 56] =  5;
    //aiIndex[ 57] =  9;  aiIndex[ 58] = 14;  aiIndex[ 59] = 15;
    //aiIndex[ 60] =  9;  aiIndex[ 61] =  4;  aiIndex[ 62] = 14;
    //aiIndex[ 63] =  6;  aiIndex[ 64] = 10;  aiIndex[ 65] = 11;
    //aiIndex[ 66] =  6;  aiIndex[ 67] =  2;  aiIndex[ 68] = 10;
    //aiIndex[ 69] =  6;  aiIndex[ 70] = 17;  aiIndex[ 71] =  2;
    //aiIndex[ 72] =  3;  aiIndex[ 73] = 18;  aiIndex[ 74] = 19;
    //aiIndex[ 75] =  3;  aiIndex[ 76] =  1;  aiIndex[ 77] = 18;
    //aiIndex[ 78] =  3;  aiIndex[ 79] = 13;  aiIndex[ 80] =  1;
    //aiIndex[ 81] =  7;  aiIndex[ 82] =  5;  aiIndex[ 83] = 15;
    //aiIndex[ 84] =  7;  aiIndex[ 85] = 18;  aiIndex[ 86] =  5;
    //aiIndex[ 87] =  7;  aiIndex[ 88] = 19;  aiIndex[ 89] = 18;
    //aiIndex[ 90] =  7;  aiIndex[ 91] =  6;  aiIndex[ 92] = 11;
    //aiIndex[ 93] =  7;  aiIndex[ 94] = 14;  aiIndex[ 95] =  6;
    //aiIndex[ 96] =  7;  aiIndex[ 97] = 15;  aiIndex[ 98] = 14;
    //aiIndex[ 99] =  7;  aiIndex[100] =  3;  aiIndex[101] = 19;
    //aiIndex[102] =  7;  aiIndex[103] = 10;  aiIndex[104] =  3;
    //aiIndex[105] =  7;  aiIndex[106] = 11;  aiIndex[107] = 10;
    aiIndex[  0] =  0;  aiIndex[  1] =  8;  aiIndex[  2] =  9;
    aiIndex[  3] =  0;  aiIndex[  4] =  9;  aiIndex[  5] =  4;
    aiIndex[  6] =  0;  aiIndex[  7] =  4;  aiIndex[  8] = 16;
    aiIndex[  9] =  0;  aiIndex[ 10] = 12;  aiIndex[ 11] = 13;
    aiIndex[ 12] =  0;  aiIndex[ 13] = 13;  aiIndex[ 14] =  1;
    aiIndex[ 15] =  0;  aiIndex[ 16] =  1;  aiIndex[ 17] =  8;
    aiIndex[ 18] =  0;  aiIndex[ 19] = 16;  aiIndex[ 20] = 17;
    aiIndex[ 21] =  0;  aiIndex[ 22] = 17;  aiIndex[ 23] =  2;
    aiIndex[ 24] =  0;  aiIndex[ 25] =  2;  aiIndex[ 26] = 12;
    aiIndex[ 27] =  8;  aiIndex[ 28] =  1;  aiIndex[ 29] = 18;
    aiIndex[ 30] =  8;  aiIndex[ 31] = 18;  aiIndex[ 32] =  5;
    aiIndex[ 33] =  8;  aiIndex[ 34] =  5;  aiIndex[ 35] =  9;
    aiIndex[ 36] = 12;  aiIndex[ 37] =  2;  aiIndex[ 38] = 10;
    aiIndex[ 39] = 12;  aiIndex[ 40] = 10;  aiIndex[ 41] =  3;
    aiIndex[ 42] = 12;  aiIndex[ 43] =  3;  aiIndex[ 44] = 13;
    aiIndex[ 45] = 16;  aiIndex[ 46] =  4;  aiIndex[ 47] = 14;
    aiIndex[ 48] = 16;  aiIndex[ 49] = 14;  aiIndex[ 50] =  6;
    aiIndex[ 51] = 16;  aiIndex[ 52] =  6;  aiIndex[ 53] = 17;
    aiIndex[ 54] =  9;  aiIndex[ 55] =  5;  aiIndex[ 56] = 15;
    aiIndex[ 57] =  9;  aiIndex[ 58] = 15;  aiIndex[ 59] = 14;
    aiIndex[ 60] =  9;  aiIndex[ 61] = 14;  aiIndex[ 62] =  4;
    aiIndex[ 63] =  6;  aiIndex[ 64] = 11;  aiIndex[ 65] = 10;
    aiIndex[ 66] =  6;  aiIndex[ 67] = 10;  aiIndex[ 68] =  2;
    aiIndex[ 69] =  6;  aiIndex[ 70] =  2;  aiIndex[ 71] = 17;
    aiIndex[ 72] =  3;  aiIndex[ 73] = 19;  aiIndex[ 74] = 18;
    aiIndex[ 75] =  3;  aiIndex[ 76] = 18;  aiIndex[ 77] =  1;
    aiIndex[ 78] =  3;  aiIndex[ 79] =  1;  aiIndex[ 80] = 13;
    aiIndex[ 81] =  7;  aiIndex[ 82] = 15;  aiIndex[ 83] =  5;
    aiIndex[ 84] =  7;  aiIndex[ 85] =  5;  aiIndex[ 86] = 18;
    aiIndex[ 87] =  7;  aiIndex[ 88] = 18;  aiIndex[ 89] = 19;
    aiIndex[ 90] =  7;  aiIndex[ 91] = 11;  aiIndex[ 92] =  6;
    aiIndex[ 93] =  7;  aiIndex[ 94] =  6;  aiIndex[ 95] = 14;
    aiIndex[ 96] =  7;  aiIndex[ 97] = 14;  aiIndex[ 98] = 15;
    aiIndex[ 99] =  7;  aiIndex[100] = 19;  aiIndex[101] =  3;
    aiIndex[102] =  7;  aiIndex[103] =  3;  aiIndex[104] = 10;
    aiIndex[105] =  7;  aiIndex[106] = 10;  aiIndex[107] = 11;

    CreatePlatonicNormals(pVB);
    CreatePlatonicUVs(pVB);
    if( m_bInside )
    {
        ReverseTriangleOrder(iTCount, aiIndex);
    }

    TransformData(pVB);
    TriMesh* pMesh = SE_NEW TriMesh(pVB, pIB);

    return pMesh;
}
//----------------------------------------------------------------------------
TriMesh* StandardMesh::Icosahedron()
{
    float fGoldenRatio = 0.5f * (1.0f + Mathf::Sqrt(5.0f));
    float fInvRoot = 1.0f / Mathf::Sqrt(1.0f + fGoldenRatio*fGoldenRatio);
    float fU = fGoldenRatio * fInvRoot;
    float fV = fInvRoot;

    int iVCount = 12;
    int iTCount = 20;
    VertexBuffer* pVB = SE_NEW VertexBuffer(m_Attr, iVCount);
    IndexBuffer* pIB = SE_NEW IndexBuffer(3 * iTCount);

    pVB->Position3( 0) = Vector3f(  fU,  fV, 0.0f);
    pVB->Position3( 1) = Vector3f( -fU,  fV, 0.0f);
    pVB->Position3( 2) = Vector3f(  fU, -fV, 0.0f);
    pVB->Position3( 3) = Vector3f( -fU, -fV, 0.0f);
    pVB->Position3( 4) = Vector3f(  fV, 0.0f,  fU);
    pVB->Position3( 5) = Vector3f(  fV, 0.0f, -fU);
    pVB->Position3( 6) = Vector3f( -fV, 0.0f,  fU);
    pVB->Position3( 7) = Vector3f( -fV, 0.0f, -fU);
    pVB->Position3( 8) = Vector3f(0.0f,  fU,  fV);
    pVB->Position3( 9) = Vector3f(0.0f, -fU,  fV);
    pVB->Position3(10) = Vector3f(0.0f,  fU, -fV);
    pVB->Position3(11) = Vector3f(0.0f, -fU, -fV);

    int* aiIndex = pIB->GetData();
    //aiIndex[ 0] =  0;  aiIndex[ 1] =  4;  aiIndex[ 2] =  8;
    //aiIndex[ 3] =  0;  aiIndex[ 4] = 10;  aiIndex[ 5] =  5;
    //aiIndex[ 6] =  2;  aiIndex[ 7] =  9;  aiIndex[ 8] =  4;
    //aiIndex[ 9] =  2;  aiIndex[10] =  5;  aiIndex[11] = 11;
    //aiIndex[12] =  1;  aiIndex[13] =  8;  aiIndex[14] =  6;
    //aiIndex[15] =  1;  aiIndex[16] =  7;  aiIndex[17] = 10;
    //aiIndex[18] =  3;  aiIndex[19] =  6;  aiIndex[20] =  9;
    //aiIndex[21] =  3;  aiIndex[22] = 11;  aiIndex[23] =  7;
    //aiIndex[24] =  0;  aiIndex[25] =  8;  aiIndex[26] = 10;
    //aiIndex[27] =  1;  aiIndex[28] = 10;  aiIndex[29] =  8;
    //aiIndex[30] =  2;  aiIndex[31] = 11;  aiIndex[32] =  9;
    //aiIndex[33] =  3;  aiIndex[34] =  9;  aiIndex[35] = 11;
    //aiIndex[36] =  4;  aiIndex[37] =  0;  aiIndex[38] =  2;
    //aiIndex[39] =  5;  aiIndex[40] =  2;  aiIndex[41] =  0;
    //aiIndex[42] =  6;  aiIndex[43] =  3;  aiIndex[44] =  1;
    //aiIndex[45] =  7;  aiIndex[46] =  1;  aiIndex[47] =  3;
    //aiIndex[48] =  8;  aiIndex[49] =  4;  aiIndex[50] =  6;
    //aiIndex[51] =  9;  aiIndex[52] =  6;  aiIndex[53] =  4;
    //aiIndex[54] = 10;  aiIndex[55] =  7;  aiIndex[56] =  5;
    //aiIndex[57] = 11;  aiIndex[58] =  5;  aiIndex[59] =  7;
    aiIndex[ 0] =  0;  aiIndex[ 1] =  8;  aiIndex[ 2] =  4;
    aiIndex[ 3] =  0;  aiIndex[ 4] =  5;  aiIndex[ 5] = 10;
    aiIndex[ 6] =  2;  aiIndex[ 7] =  4;  aiIndex[ 8] =  9;
    aiIndex[ 9] =  2;  aiIndex[10] = 11;  aiIndex[11] =  5;
    aiIndex[12] =  1;  aiIndex[13] =  6;  aiIndex[14] =  8;
    aiIndex[15] =  1;  aiIndex[16] = 10;  aiIndex[17] =  7;
    aiIndex[18] =  3;  aiIndex[19] =  9;  aiIndex[20] =  6;
    aiIndex[21] =  3;  aiIndex[22] =  7;  aiIndex[23] = 11;
    aiIndex[24] =  0;  aiIndex[25] = 10;  aiIndex[26] =  8;
    aiIndex[27] =  1;  aiIndex[28] =  8;  aiIndex[29] = 10;
    aiIndex[30] =  2;  aiIndex[31] =  9;  aiIndex[32] = 11;
    aiIndex[33] =  3;  aiIndex[34] = 11;  aiIndex[35] =  9;
    aiIndex[36] =  4;  aiIndex[37] =  2;  aiIndex[38] =  0;
    aiIndex[39] =  5;  aiIndex[40] =  0;  aiIndex[41] =  2;
    aiIndex[42] =  6;  aiIndex[43] =  1;  aiIndex[44] =  3;
    aiIndex[45] =  7;  aiIndex[46] =  3;  aiIndex[47] =  1;
    aiIndex[48] =  8;  aiIndex[49] =  6;  aiIndex[50] =  4;
    aiIndex[51] =  9;  aiIndex[52] =  4;  aiIndex[53] =  6;
    aiIndex[54] = 10;  aiIndex[55] =  5;  aiIndex[56] =  7;
    aiIndex[57] = 11;  aiIndex[58] =  7;  aiIndex[59] =  5;

    CreatePlatonicNormals(pVB);
    CreatePlatonicUVs(pVB);
    if( m_bInside )
    {
        ReverseTriangleOrder(iTCount, aiIndex);
    }

    TransformData(pVB);
    TriMesh* pMesh = SE_NEW TriMesh(pVB, pIB);

    return pMesh;
}
//----------------------------------------------------------------------------
void StandardMesh::CreatePlatonicNormals(VertexBuffer* pVBuffer)
{
    if( m_Attr.HasNormal() )
    {
        for( int i = 0; i < pVBuffer->GetVertexCount(); i++ )
        {
            pVBuffer->Normal3(i) = pVBuffer->Position3(i);
        }
    }
}
//----------------------------------------------------------------------------
void StandardMesh::CreatePlatonicUVs(VertexBuffer* pVBuffer)
{
    if( m_Attr.GetMaxTCoords() > 0 )
    {
        for( int iUnit = 0; iUnit < m_Attr.GetMaxTCoords(); iUnit++ )
        {
            if( m_Attr.HasTCoord(iUnit) )
            {
                for( int i = 0; i < pVBuffer->GetVertexCount(); i++ )
                {
                    if( Mathf::FAbs(pVBuffer->Position3(i).Z) < 1.0f )
                    {
                        pVBuffer->TCoord2(iUnit, i).X = 0.5f * (1.0f +
                            Mathf::ATan2(pVBuffer->Position3(i).Y, 
                            pVBuffer->Position3(i).X) * Mathf::INV_PI);
                    }
                    else
                    {
                        pVBuffer->TCoord2(iUnit, i).X = 0.5f;
                    }
                    pVBuffer->TCoord2(iUnit, i).Y = Mathf::ACos(
                        pVBuffer->Position3(i).Z) * Mathf::INV_PI;
                }
            }
        }
    }
}
//----------------------------------------------------------------------------