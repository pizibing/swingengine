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
#include "SETerrainPage.h"
#include "SEStandardMesh.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, TerrainPage, TriMesh);
SE_IMPLEMENT_STREAM(TerrainPage);
SE_IMPLEMENT_DEFAULT_NAME_ID(TerrainPage, TriMesh);

//SE_REGISTER_STREAM(TerrainPage);

//----------------------------------------------------------------------------
TerrainPage::TerrainPage(const Attributes& rAttr, int iSize,
    unsigned short* ausHeight, const SEVector2f& rOrigin, float fMinElevation,
    float fMaxElevation, float fSpacing, float fUVBias)
    :
    m_Origin(rOrigin)
{
    // iSize = 2^p + 1, p <= 7
    SE_ASSERT( iSize ==  3 || iSize ==  5 || iSize ==   9 || iSize == 17
        || iSize == 33 || iSize == 65 || iSize == 129 );

    m_iSize = iSize;
    m_ausHeight = ausHeight;
    m_fMinElevation = fMinElevation;
    m_fMaxElevation = fMaxElevation;
    m_fSpacing = fSpacing;

    InitializeDerivedData();

    // 创建mesh.
    StandardMesh tempSM(rAttr);

    float fExtent = m_fSpacing * m_iSizeM1;
    TriMesh* pMesh = tempSM.Rectangle(m_iSize, m_iSize, fExtent, fExtent);
    VBuffer = pMesh->VBuffer;
    IBuffer = pMesh->IBuffer;

    m_fUVBias = fUVBias;
    SE_DELETE pMesh;

    // 修改顶点并使用高度图数据.
    int iVCount = VBuffer->GetVertexCount();
    for( int i = 0; i < iVCount; i++ )
    {
        int iX = i % m_iSize;
        int iZ = i / m_iSize;
        VBuffer->Position3(i) = SEVector3f(GetX(iX), GetHeight(i), GetZ(iZ));
    }

    UpdateMS();
}
//----------------------------------------------------------------------------
TerrainPage::TerrainPage()
    :
    m_Origin(SEVector2f::ZERO)
{
    m_iSize = 0;
    m_ausHeight = 0;
    m_fMinElevation = 0.0f;
    m_fMaxElevation = 0.0f;
    m_fSpacing = 0.0f;
    m_iSizeM1 = 0;
    m_fInvSpacing = 0.0f;
    m_fTextureSpacing = 0.0f;
    m_fMultiplier = 0.0f;
}
//----------------------------------------------------------------------------
TerrainPage::~TerrainPage()
{
    SE_DELETE[] m_ausHeight;
}
//----------------------------------------------------------------------------
void TerrainPage::InitializeDerivedData()
{
    m_iSizeM1 = m_iSize - 1;
    m_fInvSpacing = 1.0f / m_fSpacing;
    m_fTextureSpacing = 1.0f / (float)m_iSizeM1;
    m_fMultiplier = (m_fMaxElevation - m_fMinElevation) / 65535.0f;
}
//----------------------------------------------------------------------------
float TerrainPage::GetHeight(float fX, float fZ) const
{
    // 待检查.

    float fXGrid = (fX - m_Origin.X) * m_fInvSpacing;
    if( fXGrid < 0.0f || fXGrid >= (float)m_iSizeM1 )
    {
        // 指定位置不在page中.
        return SEMathf::MAX_REAL;
    }

    float fZGrid = (fZ - m_Origin.Y) * m_fInvSpacing;
    if( fZGrid < 0.0f || fZGrid >= (float)m_iSizeM1 )
    {
        // 指定位置不在page中.
        return SEMathf::MAX_REAL;
    }

    float fCol = SEMathf::Floor(fXGrid);
    int iCol = (int)fCol;
    float fRow = SEMathf::Floor(fZGrid);
    int iRow = (int)fRow;

    int iIndex = iCol + m_iSize*iRow;
    float fDx = fXGrid - fCol;  // [0,1)
    float fDz = fZGrid - fRow;  // [0,1)
    float fH00, fH10, fH01, fH11, fHeight;

    if( (iCol & 1) == (iRow & 1) )
    {
        float fDiff = fDx - fDz;
        fH00 = m_fMinElevation + m_fMultiplier*m_ausHeight[iIndex];
        fH11 = m_fMinElevation + m_fMultiplier *
            m_ausHeight[iIndex + 1 + m_iSize];

        if( fDiff > 0.0f )
        {
            fH10 = m_fMinElevation + m_fMultiplier*m_ausHeight[iIndex + 1];
            fHeight = (1.0f - fDiff - fDz)*fH00 + fDiff*fH10 + fDz*fH11;
        }
        else
        {
            fH01 = m_fMinElevation + m_fMultiplier *
                m_ausHeight[iIndex + m_iSize];
            fHeight = (1.0f + fDiff - fDx)*fH00 - fDiff*fH01 + fDx*fH11;
        }
    }
    else
    {
        float fSum = fDx + fDz;
        fH10 = m_fMinElevation + m_fMultiplier*m_ausHeight[iIndex + 1];
        fH01 = m_fMinElevation + m_fMultiplier*m_ausHeight[iIndex + m_iSize];
        if( fSum <= 1.0f )
        {
            fH00 = m_fMinElevation + m_fMultiplier*m_ausHeight[iIndex];
            fHeight = (1.0f - fSum)*fH00 + fDx*fH10 + fDz*fH01;
        }
        else
        {
            fH11 = m_fMinElevation + m_fMultiplier *
                m_ausHeight[iIndex + 1 + m_iSize];
            fHeight = (fSum - 1.0f)*fH11 + (1.0f - fDz)*fH10 + (1.0f - fDx)*fH01;
        }
    }

    return fHeight;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void TerrainPage::Load(SEStream& rStream, SEStream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    TriMesh::Load(rStream, pLink);

    rStream.Read(m_iSize);
    int iVCount = m_iSize * m_iSize;
    m_ausHeight = SE_NEW unsigned short[iVCount];
    rStream.Read(iVCount, m_ausHeight);
    rStream.Read(m_Origin);
    rStream.Read(m_fMinElevation);
    rStream.Read(m_fMaxElevation);
    rStream.Read(m_fSpacing);

    InitializeDerivedData();

    SE_END_DEBUG_STREAM_LOAD(TerrainPage);
}
//----------------------------------------------------------------------------
void TerrainPage::Link(SEStream& rStream, SEStream::Link* pLink)
{
    TriMesh::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool TerrainPage::Register(SEStream& rStream) const
{
    return TriMesh::Register(rStream);
}
//----------------------------------------------------------------------------
void TerrainPage::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    TriMesh::Save(rStream);

    rStream.Write(m_iSize);
    int iVCount = VBuffer->GetVertexCount();
    rStream.Write(iVCount, m_ausHeight);
    rStream.Write(m_Origin);
    rStream.Write(m_fMinElevation);
    rStream.Write(m_fMaxElevation);
    rStream.Write(m_fSpacing);

    SE_END_DEBUG_STREAM_SAVE(TerrainPage);
}
//----------------------------------------------------------------------------
int TerrainPage::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return TriMesh::GetDiskUsed(rVersion) +
        sizeof(m_iSize) +
        m_iSize*m_iSize*sizeof(m_ausHeight[0]) +
        sizeof(m_Origin) +
        sizeof(m_fMinElevation) +
        sizeof(m_fMaxElevation) +
        sizeof(m_fSpacing);
}
//----------------------------------------------------------------------------
SEStringTree* TerrainPage::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("size =", m_iSize));
    pTree->Append(Format("origin =", m_Origin));
    pTree->Append(Format("min elevation =", m_fMinElevation));
    pTree->Append(Format("max elevation =", m_fMaxElevation));
    pTree->Append(Format("spacing =", m_fSpacing));
    pTree->Append(Format("uv bias =", m_fUVBias));

    // children
    pTree->Append(TriMesh::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
