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
#include "SETerrain.h"
#include "SECamera.h"
#include "SEMultitextureEffect.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SETerrain, SENode);
SE_IMPLEMENT_STREAM(SETerrain);
SE_IMPLEMENT_DEFAULT_NAME_ID(SETerrain, SENode);

//SE_REGISTER_STREAM(SETerrain);

//----------------------------------------------------------------------------
SETerrain::SETerrain(const char* acHeightName, const char* acImageName,
    const SEAttributes& rAttr, SECamera* pCamera, float fUVBias,
    SEColorRGBA* pBorderColor)
    :
    m_Attr(rAttr),
    m_spCamera(pCamera),
    m_fUVBias(fUVBias),
    m_BorderColor(pBorderColor ? *pBorderColor : SEColorRGBA::SE_RGBA_BLACK)
{
    m_iCameraRow = -1;
    m_iCameraCol = -1;

    m_fUVBias = fUVBias;

    // 装载global terrain信息.
    LoadHeader(acHeightName);

    // 装载全部terrain page.
    Allocate<SETerrainPagePtr>(m_iCols, m_iRows, m_aaspPage);
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
            AttachChild(m_aaspPage[iRow][iCol]);
        }
    }
}
//----------------------------------------------------------------------------
SETerrain::SETerrain()
    :
    m_BorderColor(SEColorRGBA::SE_RGBA_BLACK)
{
    m_iRows = 0;
    m_iCols = 0;
    m_iSize = 0;
    m_fMinElevation = 0.0f;
    m_fMaxElevation = 0.0f;
    m_fSpacing = 0.0f;
    m_aaspPage = 0;
    m_iCameraRow = -1;
    m_iCameraCol = -1;
    m_fUVBias = 0.0f;
}
//----------------------------------------------------------------------------
SETerrain::~SETerrain()
{
    for( int iRow = 0; iRow < m_iRows; iRow++ )
    {
        for( int iCol = 0; iCol < m_iCols; iCol++ )
        {
            m_aaspPage[iRow][iCol] = 0;
        }
    }
    Deallocate<SETerrainPagePtr>(m_aaspPage);

    m_spCamera = 0;
}
//----------------------------------------------------------------------------
SETerrainPage* SETerrain::GetPage(int iRow, int iCol)
{
    SE_ASSERT( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols );

    if( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols )
    {
        return m_aaspPage[iRow][iCol];
    }

    return 0;
}
//----------------------------------------------------------------------------
SETerrainPage* SETerrain::GetCurrentPage(float fX, float fZ) const
{
    float fInvLength = 1.0f / (m_fSpacing*(float)(m_iSize - 1));

    int iCol = (int)SEMathf::Floor(fX * fInvLength);
    iCol %= m_iCols;
    if( iCol < 0 )
    {
        iCol += m_iCols;
    }

    int iRow = (int)SEMathf::Floor(fZ * fInvLength);
    iRow %= m_iRows;
    if( iRow < 0 )
    {
        iRow += m_iRows;
    }

    return m_aaspPage[iRow][iCol];
}
//----------------------------------------------------------------------------
float SETerrain::GetHeight(float fX, float fZ) const
{
    SETerrainPage* pPage = GetCurrentPage(fX, fZ);

    // 减去由wrap-around造成的page平移变换.
    fX -= pPage->Local.GetTranslate().X;
    fZ -= pPage->Local.GetTranslate().Z;

    return pPage->GetHeight(fX, fZ);
}
//----------------------------------------------------------------------------
void SETerrain::LoadHeader(const char* acHeightName)
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
}
//----------------------------------------------------------------------------
void SETerrain::LoadPage(int iRow, int iCol, const char* acHeightName,
    const char* acHeightSuffix, const char* acImageName,
    const char* acImageSuffix)
{
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
    SETerrainPage* pPage = SE_NEW SETerrainPage(m_Attr, m_iSize, ausHeight,
        vec2fOrigin, m_fMinElevation, m_fMaxElevation, m_fSpacing, m_fUVBias);

    SESystem::SE_Sprintf(acFileName, uiSize, "%s.%s", acImageName, acImageSuffix);
    MultitextureEffect* pEffect = SE_NEW MultitextureEffect(1);
    pEffect->SetImageName(0, acFileName);
    pEffect->Configure();
    pPage->AttachEffect(pEffect);

    m_aaspPage[iRow][iCol] = pPage;
}
//----------------------------------------------------------------------------
SETerrainPagePtr SETerrain::ReplacePage(int iRow, int iCol,
    const char* acHeightName, const char* acHeightSuffix,
    const char* acImageName, const char* acImageSuffix)
{
    SE_ASSERT( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols );

    if( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols )
    {
        SETerrainPagePtr spSave = m_aaspPage[iRow][iCol];
        LoadPage(iRow, iCol, acHeightName, acHeightSuffix, acImageName,
            acImageSuffix);

        return spSave;
    }

    return 0;
}
//----------------------------------------------------------------------------
SETerrainPagePtr SETerrain::ReplacePage(int iRow, int iCol, SETerrainPage* pNewPage)
{
    SE_ASSERT( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols );

    if( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols )
    {
        SETerrainPagePtr spSave = m_aaspPage[iRow][iCol];
        m_aaspPage[iRow][iCol] = pNewPage;

        return spSave;
    }

    return 0;
}
//----------------------------------------------------------------------------
void SETerrain::OnCameraMotion()
{
    SE_ASSERT( m_spCamera );

    if( !m_spCamera )
    {
        return;
    }

    // 获取camera在terrain模型空间的位置和方向.
    SEVector3f vec3fWorldEye = m_spCamera->GetLocation();
    SEVector3f vec3fWorldDir = m_spCamera->GetDVector();
    SEVector3f vec3fModelEye;
    World.ApplyInverse(vec3fWorldEye, vec3fModelEye);
    SEVector3f vec3fModelDir = World.GetRotate() * vec3fWorldDir;

    // 更新terrain pages的模型空间原点.
    // 从包含camera的page开始处理.
    float fLength = m_fSpacing * (float)(m_iSize - 1);
    float fInvLength = 1.0f / fLength;
    int iNewCameraCol = (int)SEMathf::Floor(vec3fModelEye.X * fInvLength);
    int iNewCameraRow = (int)SEMathf::Floor(vec3fModelEye.Z * fInvLength);
    if( iNewCameraCol != m_iCameraCol || iNewCameraRow != m_iCameraRow )
    {
        m_iCameraCol = iNewCameraCol;
        m_iCameraRow = iNewCameraRow;

        // 为toroidal wraparound变换page原点.
        int iCMinO = m_iCameraCol - m_iCols/2;
        int iCMinP = iCMinO % m_iCols;
        if( iCMinP < 0 )
        {
            iCMinP += m_iCols;
        }

        int iRMinO = m_iCameraRow - m_iRows/2;
        int iRMinP = iRMinO % m_iRows;
        if( iRMinP < 0 )
        {
            iRMinP += m_iRows;
        }

        int iRO = iRMinO, iRP = iRMinP;
        for( int iRow = 0; iRow < m_iRows; iRow++ )
        {
            int iCO = iCMinO, iCP = iCMinP;
            for( int iCol = 0; iCol < m_iCols; iCol++ )
            {
                SETerrainPage* pPage = m_aaspPage[iRP][iCP];
                SEVector2f vec2fOldOrigin = pPage->GetOrigin();
                SEVector2f vec2fNewOrigin(iCO*fLength, iRO*fLength);
                SEVector2f vec2fTrn = vec2fNewOrigin - vec2fOldOrigin;
                SEVector3f vec3fPTrn(vec2fTrn.X, pPage->Local.GetTranslate().Y, 
                    vec2fTrn.Y);
                pPage->Local.SetTranslate(vec3fPTrn);

                iCO++;
                if( ++iCP == m_iCols )
                {
                    iCP = 0;
                }
            }

            iRO++;
            if( ++iRP == m_iRows )
            {
                iRP = 0;
            }
        }
        UpdateGS();
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SETerrain::Load(SEStream& rStream, SEStream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SENode::Load(rStream, pLink);

    // native data
    rStream.Read(m_iRows);
    rStream.Read(m_iCols);
    rStream.Read(m_iSize);
    rStream.Read(m_fMinElevation);
    rStream.Read(m_fMaxElevation);
    rStream.Read(m_fSpacing);
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
            rStream.Read(pObject);  // m_aaspPage[iRow][iCol]
            pLink->Add(pObject);
        }
    }

    SE_END_DEBUG_STREAM_LOAD(SETerrain);
}
//----------------------------------------------------------------------------
void SETerrain::Link(SEStream& rStream, SEStream::Link* pLink)
{
    SENode::Link(rStream, pLink);

    SEObject* pLinkID = pLink->GetLinkID();
    m_spCamera = (SECamera*)rStream.GetFromMap(pLinkID);

    Allocate<SETerrainPagePtr>(m_iCols, m_iRows, m_aaspPage);
    for( int iRow = 0; iRow < m_iRows; iRow++ )
    {
        for( int iCol = 0; iCol < m_iCols; iCol++ )
        {
            pLinkID = pLink->GetLinkID();
            m_aaspPage[iRow][iCol] =
                (SETerrainPage*)rStream.GetFromMap(pLinkID);
        }
    }
}
//----------------------------------------------------------------------------
bool SETerrain::Register(SEStream& rStream) const
{
    if( !SENode::Register(rStream) )
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
            m_aaspPage[iRow][iCol]->Register(rStream);
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void SETerrain::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SENode::Save(rStream);

    // native data
    rStream.Write(m_iRows);
    rStream.Write(m_iCols);
    rStream.Write(m_iSize);
    rStream.Write(m_fMinElevation);
    rStream.Write(m_fMaxElevation);
    rStream.Write(m_fSpacing);
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
            rStream.Write(m_aaspPage[iRow][iCol]);
        }
    }

    SE_END_DEBUG_STREAM_SAVE(SETerrain);
}
//----------------------------------------------------------------------------
int SETerrain::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SENode::GetDiskUsed(rVersion) +
        sizeof(m_iRows) +
        sizeof(m_iCols) +
        sizeof(m_iSize) +
        sizeof(m_fMinElevation) +
        sizeof(m_fMaxElevation) +
        sizeof(m_fSpacing) +
        sizeof(m_iCameraRow) +
        sizeof(m_iCameraCol) +
        sizeof(m_fUVBias) +
        sizeof(m_BorderColor) +
        sizeof(m_spCamera) +
        m_iRows*m_iCols*sizeof(m_aaspPage[0][0]);
}
//----------------------------------------------------------------------------
SEStringTree* SETerrain::SaveStrings(const char*)
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
    pTree->Append(Format("camera row =", m_iCameraRow));
    pTree->Append(Format("camera col =", m_iCameraCol));
    pTree->Append(Format("uv bias =", m_fUVBias));
    pTree->Append(Format("border color =", m_BorderColor));

    // children
    pTree->Append(SENode::SaveStrings());

    for( int iRow = 0; iRow < m_iRows; iRow++ )
    {
        for( int iCol = 0; iCol < m_iCols; iCol++ )
        {
            const size_t uiSize = 64;
            char acPageName[uiSize];
            SESystem::SE_Sprintf(acPageName, uiSize, "page[%d][%d] =", iRow, iCol);
            pTree->Append(m_aaspPage[iRow][iCol]->SaveStrings(acPageName));
        }
    }

    return pTree;
}
//----------------------------------------------------------------------------
