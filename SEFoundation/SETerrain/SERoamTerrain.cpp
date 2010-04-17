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
#include "SERoamTerrain.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, RoamTerrain, Node);
SE_IMPLEMENT_STREAM(RoamTerrain);
SE_IMPLEMENT_DEFAULT_NAME_ID(RoamTerrain, Node);

//SE_REGISTER_STREAM(RoamTerrain);

//----------------------------------------------------------------------------
RoamTerrain::RoamTerrain(const char* acHeightName, const char* acImageName,
    const Attributes& rAttr, Camera* pCamera, float fUVBias,
    SEColorRGBA* pBorderColor)
    :
    m_Attr(rAttr),
    m_spCamera(pCamera),
    m_fUVBias(fUVBias),
    m_BorderColor(pBorderColor ? *pBorderColor : SEColorRGBA::SE_RGBA_BLACK)
{
    m_bLod = true;

    m_iCameraRow = -1;
    m_iCameraCol = -1;

    m_fUVBias = fUVBias;

    // 装载global terrain信息.
    LoadHeader(acHeightName);

    // 装载全部terrain page.
    m_Pages.resize(m_iRows);
    for( int i = 0; i < m_iRows; i++ )
    {
        m_Pages[i].resize(m_iCols);
    }
    int iRow, iCol;
    for( iRow = 0; iRow < m_iRows; iRow++ )
    {
        for( iCol = 0; iCol < m_iCols; iCol++ )
        {
            const size_t uiSize = 64;
            char acSuffix[uiSize];
            SESystem::SE_Sprintf(acSuffix, uiSize, "%d.%d", iRow, iCol);
            LoadPage(iRow, iCol, acHeightName, acSuffix, acImageName, acSuffix);
        }
    }

    // 全部terrain page将作为该terrain node的子节点.
    m_Child.resize(m_iRows * m_iCols);
    for( iRow = 0; iRow < m_iRows; iRow++ )
    {
        for( iCol = 0; iCol < m_iCols; iCol++ )    
        {
            AttachChild(m_Pages[iRow][iCol]);
        }
    }
}
//----------------------------------------------------------------------------
RoamTerrain::RoamTerrain()
    :
    m_BorderColor(SEColorRGBA::SE_RGBA_BLACK)
{
    m_bLod = true;
    m_iRows = 0;
    m_iCols = 0;
    m_iSize = 0;
    m_fMinElevation = 0.0f;
    m_fMaxElevation = 0.0f;
    m_fSpacing = 0.0f;
    m_iCameraRow = -1;
    m_iCameraCol = -1;
    m_fUVBias = 0.0f;
    m_iPoolSize = 0;
    m_iPatchSize = 0;
    m_iSplitLevel = 0;
    m_iVarianceLevel = 0;
}
//----------------------------------------------------------------------------
RoamTerrain::~RoamTerrain()
{
    for( int iRow = 0; iRow < m_iRows; iRow++ )
    {
        for( int iCol = 0; iCol < m_iCols; iCol++ )
        {
            m_Pages[iRow][iCol] = 0;
        }
    }

    m_spCamera = 0;
}
//----------------------------------------------------------------------------
void RoamTerrain::SetLod(bool bLod)
{
    m_bLod = bLod;

    if( m_bLod )
    {
        for( int iRow = 0; iRow < m_iRows; iRow++ )
        {
            for( int iCol = 0; iCol < m_iCols; iCol++ )
            {		
                m_Pages[iRow][iCol]->m_bNeedsTessellation = true;
            }
        }
    }
    else
    {
        for( int iRow = 0; iRow < m_iRows; iRow++ )
        {
            for( int iCol = 0; iCol < m_iCols; iCol++ )
            {		
                m_Pages[iRow][iCol]->m_bNeedsResetIB = true;
            }
        }
    }
}
//----------------------------------------------------------------------------
RoamTerrainPage* RoamTerrain::GetPage(int iRow, int iCol)
{
    SE_ASSERT( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols );

    if( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols )
    {
        return m_Pages[iRow][iCol];
    }

    return 0;
}
//----------------------------------------------------------------------------
RoamTerrainPage* RoamTerrain::GetCurrentPage(float fX, float fZ) const
{
    float fInvLength = 1.0f / (m_fSpacing*(float)(m_iSize - 1));

    // 把世界空间X,Z变换到terrain模型空间.
    float fMSpaceX = fX - World.GetTranslate().X;
    float fMSpaceZ = fZ - World.GetTranslate().Z;

    int iCol = (int)SEMathf::Floor(fMSpaceX * fInvLength);
    iCol %= m_iCols;
    if( iCol < 0 )
    {
        iCol += m_iCols;
    }

    int iRow = (int)SEMathf::Floor(fMSpaceZ * fInvLength);
    iRow %= m_iRows;
    if( iRow < 0 )
    {
        iRow += m_iRows;
    }

    return m_Pages[iRow][iCol];
}
//----------------------------------------------------------------------------
float RoamTerrain::GetHeight(float fX, float fZ) const
{
    RoamTerrainPage* pPage = GetCurrentPage(fX, fZ);

    return pPage->GetHeight(fX, fZ);
}
//----------------------------------------------------------------------------
RoamTerrainPagePtr RoamTerrain::ReplacePage(int iRow, int iCol,
    const char* acHeightName, const char* acHeightSuffix,
    const char* acImageName, const char* acImageSuffix)
{
    SE_ASSERT( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols );

    if( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols )
    {
        RoamTerrainPagePtr spSave = m_Pages[iRow][iCol];
        LoadPage(iRow, iCol, acHeightName, acHeightSuffix, acImageName,
            acImageSuffix);

        return spSave;
    }

    return 0;
}
//----------------------------------------------------------------------------
RoamTerrainPagePtr RoamTerrain::ReplacePage(int iRow, int iCol, 
    RoamTerrainPage* pNewPage)
{
    SE_ASSERT( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols );

    if( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols )
    {
        RoamTerrainPagePtr spSave = m_Pages[iRow][iCol];
        m_Pages[iRow][iCol] = pNewPage;

        return spSave;
    }

    return 0;
}
//----------------------------------------------------------------------------
void RoamTerrain::Simplify(Culler& rCuller)
{
    if( m_bLod )
    {
        int iRow, iCol;
        for( iRow = 0; iRow < m_iRows; iRow++ )
        {
            for( iCol = 0; iCol < m_iCols; iCol++ )
            {		
                m_Pages[iRow][iCol]->ResetPatches();
            }
        }

        for( iRow = 0; iRow < m_iRows; iRow++ )
        {
            for( iCol = 0; iCol < m_iCols; iCol++ )
            {		
                m_Pages[iRow][iCol]->SimplifyPatches(m_spCamera, rCuller);
            }
        }
    }
}
//----------------------------------------------------------------------------
void RoamTerrain::LoadHeader(const char* acHeightName)
{
    char acFilename[512];
    SESystem::SE_Sprintf(acFilename, 512, "%s.sehf", acHeightName);
    const char* acPath = SESystem::SE_GetPath(acFilename, SESystem::SM_READ);
    FILE* pHeader = SESystem::SE_Fopen(acPath, "rb");

    SE_ASSERT( pHeader );

    unsigned short usSize;
    SESystem::SE_Read4le(pHeader, 1, &m_iRows);
    SESystem::SE_Read4le(pHeader, 1, &m_iCols);
    SESystem::SE_Read2le(pHeader, 1, &usSize);
    m_iSize = (int)usSize;
    SESystem::SE_Read4le(pHeader, 1, &m_fMinElevation);
    SESystem::SE_Read4le(pHeader, 1, &m_fMaxElevation);
    SESystem::SE_Read4le(pHeader, 1, &m_fSpacing);
    SESystem::SE_Fclose(pHeader);

    // 待实现.
    // 从文件读取.
    m_iPoolSize = 2048;
    m_iPatchSize = 17;
    m_iSplitLevel = 3;
    m_iVarianceLevel = 4;
}
//----------------------------------------------------------------------------
void RoamTerrain::LoadPage(int iRow, int iCol, const char* acHeightName,
    const char* acHeightSuffix, const char* acImageName,
    const char* acImageSuffix)
{
    // 获取page高度图.
    int iCount = m_iSize * m_iSize;
    unsigned short* ausHeight = SE_NEW unsigned short[iCount];
    const size_t uiSize = 512;
    char acFileName[uiSize];
    SESystem::SE_Sprintf(acFileName, uiSize, "%s.%s.sehf", acHeightName,
        acHeightSuffix);
    const char* acPath = SESystem::SE_GetPath(acFileName, SESystem::SM_READ);
    FILE* pHeightFile = SESystem::SE_Fopen(acPath, "rb");
    SE_ASSERT( pHeightFile );

    if( pHeightFile )
    {
        SESystem::SE_Read2le(pHeightFile, iCount, ausHeight);
        SESystem::SE_Fclose(pHeightFile);
    }
    else
    {
        SE_ASSERT( false );
        memset(ausHeight, 0, iCount*sizeof(unsigned short));
    }

    float fLength = m_fSpacing*(float)(m_iSize - 1);
    // 该page在terrain模型空间的原点.
    SEVector2f vec2fOrigin(iCol*fLength, iRow*fLength);
    // 创建page.
    RoamTerrainPage* pPage = SE_NEW RoamTerrainPage(m_Attr, m_iSize, ausHeight,
        vec2fOrigin, m_fMinElevation, m_fMaxElevation, m_fSpacing, m_fUVBias,
        m_iPoolSize, m_iPatchSize, m_iSplitLevel, m_iVarianceLevel);
    pPage->SetPageGrid(iRow, iCol, this);

    // 为page添加effect.
    SESystem::SE_Sprintf(acFileName, uiSize, "%s.%s", acImageName, acImageSuffix);
    MultitextureEffect* pEffect = SE_NEW MultitextureEffect(1);
    pEffect->SetImageName(0, acFileName);
    pEffect->Configure();
    pPage->AttachEffect(pEffect);
    //DefaultShaderEffect* pEffect = SE_NEW DefaultShaderEffect;
    //pPage->AttachEffect(pEffect);

    m_Pages[iRow][iCol] = pPage;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void RoamTerrain::Load(SEStream& rStream, SEStream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    Node::Load(rStream, pLink);

    // native data
    rStream.Read(m_iRows);
    rStream.Read(m_iCols);
    rStream.Read(m_iSize);
    rStream.Read(m_fMinElevation);
    rStream.Read(m_fMaxElevation);
    rStream.Read(m_fSpacing);
    rStream.Read(m_iPoolSize);
    rStream.Read(m_iPatchSize);
    rStream.Read(m_iSplitLevel);
    rStream.Read(m_iVarianceLevel);
    rStream.Read(m_iCameraRow);
    rStream.Read(m_iCameraCol);
    rStream.Read(m_fUVBias);
    rStream.Read(m_BorderColor);

    // link data
    SEObject* pObject;
    rStream.Read(pObject);  // m_spCamera
    pLink->Add(pObject);
    for( int iRow = 0; iRow < m_iRows; iRow++ )
    {
        for( int iCol = 0; iCol < m_iCols; iCol++ )
        {
            rStream.Read(pObject);  // m_Pages[iRow][iCol]
            pLink->Add(pObject);
        }
    }

    SE_END_DEBUG_STREAM_LOAD(RoamTerrain);
}
//----------------------------------------------------------------------------
void RoamTerrain::Link(SEStream& rStream, SEStream::Link* pLink)
{
    Node::Link(rStream, pLink);

    SEObject* pLinkID = pLink->GetLinkID();
    m_spCamera = (Camera*)rStream.GetFromMap(pLinkID);

    m_Pages.resize(m_iRows);
    for( int i = 0; i < m_iRows; i++ )
    {
        m_Pages[i].resize(m_iCols);
    }
    for( int iRow = 0; iRow < m_iRows; iRow++ )
    {
        for( int iCol = 0; iCol < m_iCols; iCol++ )
        {
            pLinkID = pLink->GetLinkID();
            m_Pages[iRow][iCol] =
                (RoamTerrainPage*)rStream.GetFromMap(pLinkID);

            m_Pages[iRow][iCol]->SetPageGrid(iRow, iCol, this);
        }
    }
}
//----------------------------------------------------------------------------
bool RoamTerrain::Register(SEStream& rStream) const
{
    if( !Node::Register(rStream) )
    {
        return false;
    }

    if( m_spCamera )
    {
        m_spCamera->Register(rStream);
    }

    for( int iRow = 0; iRow < m_iRows; iRow++ )
    {
        for( int iCol = 0; iCol < m_iCols; iCol++ )
        {
            m_Pages[iRow][iCol]->Register(rStream);
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void RoamTerrain::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    Node::Save(rStream);

    // native data
    rStream.Write(m_iRows);
    rStream.Write(m_iCols);
    rStream.Write(m_iSize);
    rStream.Write(m_fMinElevation);
    rStream.Write(m_fMaxElevation);
    rStream.Write(m_fSpacing);
    rStream.Write(m_iPoolSize);
    rStream.Write(m_iPatchSize);
    rStream.Write(m_iSplitLevel);
    rStream.Write(m_iVarianceLevel);
    rStream.Write(m_iCameraRow);
    rStream.Write(m_iCameraCol);
    rStream.Write(m_fUVBias);
    rStream.Write(m_BorderColor);

    // link data
    rStream.Write(m_spCamera);
    for( int iRow = 0; iRow < m_iRows; iRow++ )
    {
        for( int iCol = 0; iCol < m_iCols; iCol++ )
        {
            rStream.Write(m_Pages[iRow][iCol]);
        }
    }

    SE_END_DEBUG_STREAM_SAVE(RoamTerrain);
}
//----------------------------------------------------------------------------
int RoamTerrain::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return Node::GetDiskUsed(rVersion) +
        sizeof(m_iRows) +
        sizeof(m_iCols) +
        sizeof(m_iSize) +
        sizeof(m_fMinElevation) +
        sizeof(m_fMaxElevation) +
        sizeof(m_fSpacing) +
        sizeof(m_iPoolSize) + 
        sizeof(m_iPatchSize) + 
        sizeof(m_iSplitLevel) + 
        sizeof(m_iVarianceLevel) + 
        sizeof(m_iCameraRow) +
        sizeof(m_iCameraCol) +
        sizeof(m_fUVBias) +
        sizeof(m_BorderColor) +
        sizeof(m_spCamera) +
        m_iRows*m_iCols*sizeof(m_Pages[0][0]);
}
//----------------------------------------------------------------------------
SEStringTree* RoamTerrain::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("rows =", m_iRows));
    pTree->Append(Format("cols =", m_iCols));
    pTree->Append(Format("size =", m_iSize));
    pTree->Append(Format("min elevation =", m_fMinElevation));
    pTree->Append(Format("max elevation =", m_fMaxElevation));
    pTree->Append(Format("spacing =", m_fSpacing));
    pTree->Append(Format("pool size =", m_iPoolSize));
    pTree->Append(Format("patch size =", m_iPatchSize));
    pTree->Append(Format("split level =", m_iSplitLevel));
    pTree->Append(Format("variance level =", m_iVarianceLevel));
    pTree->Append(Format("camera row =", m_iCameraRow));
    pTree->Append(Format("camera col =", m_iCameraCol));
    pTree->Append(Format("uv bias =", m_fUVBias));
    pTree->Append(Format("border color =", m_BorderColor));

    // children
    pTree->Append(Node::SaveStrings());

    for( int iRow = 0; iRow < m_iRows; iRow++ )
    {
        for( int iCol = 0; iCol < m_iCols; iCol++ )
        {
            const size_t uiSize = 64;
            char acPageName[uiSize];
            SESystem::SE_Sprintf(acPageName, uiSize, "page[%d][%d] =", iRow, iCol);
            pTree->Append(m_Pages[iRow][iCol]->SaveStrings(acPageName));
        }
    }

    return pTree;
}
//----------------------------------------------------------------------------
