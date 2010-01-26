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

SE_IMPLEMENT_RTTI(Swing, Terrain, Node);
SE_IMPLEMENT_STREAM(Terrain);
SE_IMPLEMENT_DEFAULT_NAME_ID(Terrain, Node);

//SE_REGISTER_STREAM(Terrain);

//----------------------------------------------------------------------------
Terrain::Terrain(const char* acHeightName, const char* acImageName,
    const Attributes& rAttr, Camera* pCamera, float fUVBias,
    ColorRGBA* pBorderColor)
    :
    m_Attr(rAttr),
    m_spCamera(pCamera),
    m_fUVBias(fUVBias),
    m_BorderColor(pBorderColor ? *pBorderColor : ColorRGBA::SE_RGBA_BLACK)
{
    m_iCameraRow = -1;
    m_iCameraCol = -1;

    m_fUVBias = fUVBias;

    // 装载global terrain信息.
    LoadHeader(acHeightName);

    // 装载全部terrain page.
    Allocate<TerrainPagePtr>(m_iCols, m_iRows, m_aaspPage);
    int iRow, iCol;
    for( iRow = 0; iRow < m_iRows; iRow++ )
    {
        for( iCol = 0; iCol < m_iCols; iCol++ )
        {
            const size_t uiSize = 64;
            char acSuffix[uiSize];
            System::SE_Sprintf(acSuffix, uiSize, "%d.%d", iRow, iCol);
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
Terrain::Terrain()
    :
    m_BorderColor(ColorRGBA::SE_RGBA_BLACK)
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
Terrain::~Terrain()
{
    for( int iRow = 0; iRow < m_iRows; iRow++ )
    {
        for( int iCol = 0; iCol < m_iCols; iCol++ )
        {
            m_aaspPage[iRow][iCol] = 0;
        }
    }
    Deallocate<TerrainPagePtr>(m_aaspPage);

    m_spCamera = 0;
}
//----------------------------------------------------------------------------
TerrainPage* Terrain::GetPage(int iRow, int iCol)
{
    SE_ASSERT( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols );

    if( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols )
    {
        return m_aaspPage[iRow][iCol];
    }

    return 0;
}
//----------------------------------------------------------------------------
TerrainPage* Terrain::GetCurrentPage(float fX, float fZ) const
{
    float fInvLength = 1.0f / (m_fSpacing*(float)(m_iSize - 1));

    int iCol = (int)Mathf::Floor(fX * fInvLength);
    iCol %= m_iCols;
    if( iCol < 0 )
    {
        iCol += m_iCols;
    }

    int iRow = (int)Mathf::Floor(fZ * fInvLength);
    iRow %= m_iRows;
    if( iRow < 0 )
    {
        iRow += m_iRows;
    }

    return m_aaspPage[iRow][iCol];
}
//----------------------------------------------------------------------------
float Terrain::GetHeight(float fX, float fZ) const
{
    TerrainPage* pPage = GetCurrentPage(fX, fZ);

    // 减去由wrap-around造成的page平移变换.
    fX -= pPage->Local.GetTranslate().X;
    fZ -= pPage->Local.GetTranslate().Z;

    return pPage->GetHeight(fX, fZ);
}
//----------------------------------------------------------------------------
void Terrain::LoadHeader(const char* acHeightName)
{
    char acFilename[512];
    System::SE_Sprintf(acFilename, 512, "%s.sehf", acHeightName);
    const char* acPath = System::SE_GetPath(acFilename, System::SM_READ);
    FILE* pHeader = System::SE_Fopen(acPath, "rb");

    SE_ASSERT( pHeader );

    unsigned short usSize;
    System::SE_Read4le(pHeader, 1, &m_iRows);
    System::SE_Read4le(pHeader, 1, &m_iCols);
    System::SE_Read2le(pHeader, 1, &usSize);
    m_iSize = (int)usSize;
    System::SE_Read4le(pHeader, 1, &m_fMinElevation);
    System::SE_Read4le(pHeader, 1, &m_fMaxElevation);
    System::SE_Read4le(pHeader, 1, &m_fSpacing);
    System::SE_Fclose(pHeader);
}
//----------------------------------------------------------------------------
void Terrain::LoadPage(int iRow, int iCol, const char* acHeightName,
    const char* acHeightSuffix, const char* acImageName,
    const char* acImageSuffix)
{
    int iCount = m_iSize * m_iSize;
    unsigned short* ausHeight = SE_NEW unsigned short[iCount];
    const size_t uiSize = 512;
    char acFileName[uiSize];
    System::SE_Sprintf(acFileName, uiSize, "%s.%s.sehf", acHeightName,
        acHeightSuffix);
    const char* acPath = System::SE_GetPath(acFileName, System::SM_READ);
    FILE* pHeightFile = System::SE_Fopen(acPath, "rb");
    SE_ASSERT( pHeightFile );

    if( pHeightFile )
    {
        System::SE_Read2le(pHeightFile, iCount, ausHeight);
        System::SE_Fclose(pHeightFile);
    }
    else
    {
        SE_ASSERT( false );
        memset(ausHeight, 0, iCount*sizeof(unsigned short));
    }

    float fLength = m_fSpacing*(float)(m_iSize - 1);
    // 该page在terrain模型空间的原点.
    Vector2f vec2fOrigin(iCol*fLength, iRow*fLength);
    TerrainPage* pPage = SE_NEW TerrainPage(m_Attr, m_iSize, ausHeight,
        vec2fOrigin, m_fMinElevation, m_fMaxElevation, m_fSpacing, m_fUVBias);

    System::SE_Sprintf(acFileName, uiSize, "%s.%s", acImageName, acImageSuffix);
    MultitextureEffect* pEffect = SE_NEW MultitextureEffect(1);
    pEffect->SetImageName(0, acFileName);
    pEffect->Configure();
    pPage->AttachEffect(pEffect);

    m_aaspPage[iRow][iCol] = pPage;
}
//----------------------------------------------------------------------------
TerrainPagePtr Terrain::ReplacePage(int iRow, int iCol,
    const char* acHeightName, const char* acHeightSuffix,
    const char* acImageName, const char* acImageSuffix)
{
    SE_ASSERT( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols );

    if( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols )
    {
        TerrainPagePtr spSave = m_aaspPage[iRow][iCol];
        LoadPage(iRow, iCol, acHeightName, acHeightSuffix, acImageName,
            acImageSuffix);

        return spSave;
    }

    return 0;
}
//----------------------------------------------------------------------------
TerrainPagePtr Terrain::ReplacePage(int iRow, int iCol, TerrainPage* pNewPage)
{
    SE_ASSERT( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols );

    if( 0 <= iRow && iRow < m_iRows && 0 <= iCol && iCol < m_iCols )
    {
        TerrainPagePtr spSave = m_aaspPage[iRow][iCol];
        m_aaspPage[iRow][iCol] = pNewPage;

        return spSave;
    }

    return 0;
}
//----------------------------------------------------------------------------
void Terrain::OnCameraMotion()
{
    SE_ASSERT( m_spCamera );

    if( !m_spCamera )
    {
        return;
    }

    // 获取camera在terrain模型空间的位置和方向.
    Vector3f vec3fWorldEye = m_spCamera->GetLocation();
    Vector3f vec3fWorldDir = m_spCamera->GetDVector();
    Vector3f vec3fModelEye;
    World.ApplyInverse(vec3fWorldEye, vec3fModelEye);
    Vector3f vec3fModelDir = World.GetRotate() * vec3fWorldDir;

    // 更新terrain pages的模型空间原点.
    // 从包含camera的page开始处理.
    float fLength = m_fSpacing * (float)(m_iSize - 1);
    float fInvLength = 1.0f / fLength;
    int iNewCameraCol = (int)Mathf::Floor(vec3fModelEye.X * fInvLength);
    int iNewCameraRow = (int)Mathf::Floor(vec3fModelEye.Z * fInvLength);
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
                TerrainPage* pPage = m_aaspPage[iRP][iCP];
                Vector2f vec2fOldOrigin = pPage->GetOrigin();
                Vector2f vec2fNewOrigin(iCO*fLength, iRO*fLength);
                Vector2f vec2fTrn = vec2fNewOrigin - vec2fOldOrigin;
                Vector3f vec3fPTrn(vec2fTrn.X, pPage->Local.GetTranslate().Y, 
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
ObjectPtr Terrain::Clone()
{
    // TODO:
    // Impliment this function.
    return 0;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void Terrain::Load(Stream& rStream, Stream::Link* pLink)
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
    rStream.Read(m_iCameraRow);
    rStream.Read(m_iCameraCol);
    rStream.Read(m_fUVBias);
    rStream.Read(m_BorderColor);

    // link data
    Object* pObject;
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

    SE_END_DEBUG_STREAM_LOAD(Terrain);
}
//----------------------------------------------------------------------------
void Terrain::Link(Stream& rStream, Stream::Link* pLink)
{
    Node::Link(rStream, pLink);

    Object* pLinkID = pLink->GetLinkID();
    m_spCamera = (Camera*)rStream.GetFromMap(pLinkID);

    Allocate<TerrainPagePtr>(m_iCols, m_iRows, m_aaspPage);
    for( int iRow = 0; iRow < m_iRows; iRow++ )
    {
        for( int iCol = 0; iCol < m_iCols; iCol++ )
        {
            pLinkID = pLink->GetLinkID();
            m_aaspPage[iRow][iCol] =
                (TerrainPage*)rStream.GetFromMap(pLinkID);
        }
    }
}
//----------------------------------------------------------------------------
bool Terrain::Register(Stream& rStream) const
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
            m_aaspPage[iRow][iCol]->Register(rStream);
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void Terrain::Save(Stream& rStream) const
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

    SE_END_DEBUG_STREAM_SAVE(Terrain);
}
//----------------------------------------------------------------------------
int Terrain::GetDiskUsed(const StreamVersion& rVersion) const
{
    return Node::GetDiskUsed(rVersion) +
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
StringTree* Terrain::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

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
    pTree->Append(Node::SaveStrings());

    for( int iRow = 0; iRow < m_iRows; iRow++ )
    {
        for( int iCol = 0; iCol < m_iCols; iCol++ )
        {
            const size_t uiSize = 64;
            char acPageName[uiSize];
            System::SE_Sprintf(acPageName, uiSize, "page[%d][%d] =", iRow, iCol);
            pTree->Append(m_aaspPage[iRow][iCol]->SaveStrings(acPageName));
        }
    }

    return pTree;
}
//----------------------------------------------------------------------------
