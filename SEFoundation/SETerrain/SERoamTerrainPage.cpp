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
#include "SERoamTerrainPage.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SERoamTerrainPage, SETriMesh);
SE_IMPLEMENT_STREAM(SERoamTerrainPage);
SE_IMPLEMENT_DEFAULT_NAME_ID(SERoamTerrainPage, SETriMesh);

//SE_REGISTER_STREAM(SERoamTerrainPage);

//float SERoamTerrainPage::FrameVariance = 50.0f;
int SERoamTerrainPage::DesiredTris = 20000;
int SERoamTerrainPage::NumTrisRendered = 0;

//----------------------------------------------------------------------------
SERoamTerrainPage::SERoamTerrainPage(const SEAttributes& rAttr, int iSize,
    unsigned short* ausHeight, const SEVector2f& rOrigin,
    float fMinElevation, float fMaxElevation, float fSpacing,
    float fUVBias, int iPoolSize, int iPatchSize, int iSplitLevel, 
    int iVarianceLevel)
    :
    m_Origin(rOrigin)
{
    SE_ASSERT( iSize == 33 || iSize == 65 || iSize == 129 );

    m_iSize = iSize;
    m_ausHeight = ausHeight;
    m_fMinElevation = fMinElevation;
    m_fMaxElevation = fMaxElevation;
    m_fSpacing = fSpacing;
    m_iPoolSize = iPoolSize;
    m_iPatchSize = iPatchSize;
    m_iSplitLevel = iSplitLevel;
    m_iVarianceLevel = iVarianceLevel;
    FrameVariance = 50.0f;
    m_iNextTriNode = 0;

    // 稍后待构造函数结束,由SERoamTerrain对象调用SetPageGrid函数设置.
    m_iRow = -1;
    m_iCol = -1;
    m_pTerrain = 0;

    InitializeDerivedData();

    // 创建mesh.
    SEStandardMesh tempSM(rAttr);

    float fExtent = m_fSpacing * m_iSizeM1;
    SETriMesh* pMesh = tempSM.Rectangle(m_iSize, m_iSize, fExtent, fExtent);
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
SERoamTerrainPage::SERoamTerrainPage()
    :
    m_Origin(SEVector2f::ZERO)
{
    m_iSize = 0;
    m_ausHeight = 0;
    m_fMinElevation = 0.0f;
    m_fMaxElevation = 0.0f;
    m_fSpacing = 0.0f;
    m_iPoolSize = 0;
    m_iPatchSize = 0;
    m_iSplitLevel = 0;
    m_iVarianceLevel = 0;
    FrameVariance = 50.0f;
    m_fUVBias = 0.0f;
    m_iNextTriNode = 0;

    // 通过SetPageGrid函数设置.
    m_iRow = -1;
    m_iCol = -1;
    m_pTerrain = 0;

    // derived.
    m_iSizeM1 = 0;
    m_iPatchSizeM1 = 0;
    m_fInvSpacing = 0.0f;
    m_fTextureSpacing = 0.0f;
    m_fMultiplier = 0.0f;
    m_iPatchesPerSide = 0;
    m_iMaxIndexCount = 0;
    m_bNeedsTessellation = false;
    m_bNeedsResetIB = false;
}
//----------------------------------------------------------------------------
SERoamTerrainPage::~SERoamTerrainPage()
{
    SE_DELETE[] m_ausHeight;
}
//----------------------------------------------------------------------------
float SERoamTerrainPage::GetHeight(float fX, float fZ) const
{
    float fTempHeight = 0.0f;
    // 将世界空间X,Z变换到terrain空间.
    float fTerrainMSpaceX = fX - World.GetTranslate().X;
    float fTerrainMSpaceZ = fZ - World.GetTranslate().Z;
    // 将terrain空间X,Z变换到terrain page空间.
    float fMSpaceX = fTerrainMSpaceX - m_Origin.X;
    float fMSpaceZ = fTerrainMSpaceZ - m_Origin.Y;
    fMSpaceX *= m_fInvSpacing;
    fMSpaceZ *= m_fInvSpacing;

    SE_ASSERT( m_pTerrain );

    if( m_pTerrain->GetLod() )
    {
        // 获取坐标所在patch.
        float fInvPatchSizeM1 = 1.0f / (float)m_iPatchSizeM1;
        int iPatchX = (int)SEMathf::Floor(fMSpaceX * fInvPatchSizeM1);
        int iPatchY = (int)SEMathf::Floor(fMSpaceZ * fInvPatchSizeM1);
        if( iPatchX >= m_iPatchesPerSide )
            iPatchX = m_iPatchesPerSide - 1;
        if( iPatchX < 0 )
            iPatchX = 0;
        if( iPatchY >= m_iPatchesPerSide )
            iPatchY = m_iPatchesPerSide - 1;
        if( iPatchY < 0 )
            iPatchY = 0;
    
        // 判断所处base triangle.
        float fPatchLBX = (float)(iPatchX * m_iPatchSizeM1);
        float fPatchLBY = (float)(iPatchY * m_iPatchSizeM1);
        float fPatchRBX = fPatchLBX + (float)m_iPatchSizeM1;
        float fPatchRBY = fPatchLBY;
        float fdX = fMSpaceX - fPatchRBX;
        float fdY = fMSpaceZ - fPatchRBY;

        SERoamTriTreeNode* pCurTriangle = 0;
        if( -fdX >= fdY )
        {
            pCurTriangle = m_Patches[iPatchY][iPatchX].GetBaseLeft();
        }
        else
        {
            pCurTriangle = m_Patches[iPatchY][iPatchX].GetBaseRight();
        }

        SEVector2f Apex, Left, Right, CurPoint;
        SEVector2f A, B, C;
        float fCdA, fCdB;

        CurPoint.X = fTerrainMSpaceX;
        CurPoint.Y = fTerrainMSpaceZ;

        // 获取当前所在最小triangle.
        while( pCurTriangle->pLeftChild != 0 )
        {
            Apex.X = (*(SEVector3f*)VBuffer->PositionTuple(
                pCurTriangle->ApexIndex)).X;
            Apex.Y = (*(SEVector3f*)VBuffer->PositionTuple(
                pCurTriangle->ApexIndex)).Z;
            Left.X = (*(SEVector3f*)VBuffer->PositionTuple(
                pCurTriangle->LeftIndex)).X;
            Left.Y = (*(SEVector3f*)VBuffer->PositionTuple(
                pCurTriangle->LeftIndex)).Z;
            Right.X = (*(SEVector3f*)VBuffer->PositionTuple(
                pCurTriangle->RightIndex)).X;
            Right.Y = (*(SEVector3f*)VBuffer->PositionTuple(
                pCurTriangle->RightIndex)).Z;

            A = Left - Apex;
            B = Right - Apex;
            C = CurPoint - Apex;
            A.Normalize();
            B.Normalize();

            fCdA = C.Dot(A);
            fCdB = C.Dot(B);

            if( fCdA >= fCdB )
            {
                pCurTriangle = pCurTriangle->pLeftChild;
            }
            else
            {
                pCurTriangle = pCurTriangle->pRightChild;
            }
        }

        // 插值计算所在点高度.
        Apex.X = (*(SEVector3f*)VBuffer->PositionTuple(
            pCurTriangle->ApexIndex)).X;
        Apex.Y = (*(SEVector3f*)VBuffer->PositionTuple(
            pCurTriangle->ApexIndex)).Z;
        Left.X = (*(SEVector3f*)VBuffer->PositionTuple(
            pCurTriangle->LeftIndex)).X;
        Left.Y = (*(SEVector3f*)VBuffer->PositionTuple(
            pCurTriangle->LeftIndex)).Z;
        Right.X = (*(SEVector3f*)VBuffer->PositionTuple(
            pCurTriangle->RightIndex)).X;
        Right.Y = (*(SEVector3f*)VBuffer->PositionTuple(
            pCurTriangle->RightIndex)).Z;

        A = Left - Apex;
        B = Right - Apex;
        C = CurPoint - Apex;
        float fCurTriSpacing = A.GetLength();
        float fInvCurTriSpacing = 1.0f / fCurTriSpacing;
        A.Normalize();
        B.Normalize();

        fCdA = C.Dot(A);
        fCdB = C.Dot(B);

        SEVector3f Apex3, Left3, Right3, CurPoint3;
        Apex3.X = (*(SEVector3f*)VBuffer->PositionTuple(
            pCurTriangle->ApexIndex)).X;
        Apex3.Y = (*(SEVector3f*)VBuffer->PositionTuple(
            pCurTriangle->ApexIndex)).Z;
        Apex3.Z = (*(SEVector3f*)VBuffer->PositionTuple(
            pCurTriangle->ApexIndex)).Y;
        Left3.X = (*(SEVector3f*)VBuffer->PositionTuple(
            pCurTriangle->LeftIndex)).X;
        Left3.Y = (*(SEVector3f*)VBuffer->PositionTuple(
            pCurTriangle->LeftIndex)).Z;
        Left3.Z = (*(SEVector3f*)VBuffer->PositionTuple(
            pCurTriangle->LeftIndex)).Y;
        Right3.X = (*(SEVector3f*)VBuffer->PositionTuple(
            pCurTriangle->RightIndex)).X;
        Right3.Y = (*(SEVector3f*)VBuffer->PositionTuple(
            pCurTriangle->RightIndex)).Z;
        Right3.Z = (*(SEVector3f*)VBuffer->PositionTuple(
            pCurTriangle->RightIndex)).Y;

        float fdLAHeight = Left3.Z - Apex3.Z;
        float fdRAHeight = Right3.Z - Apex3.Z;
        
        // 模型空间z变换回世界空间的y.
        fTempHeight = Apex3.Z + fCdA*fInvCurTriSpacing*fdLAHeight + 
            fCdB*fInvCurTriSpacing*fdRAHeight;
    }
    else
    {
        int iCellX = (int)SEMathf::Floor(fMSpaceX);
        int iCellY = (int)SEMathf::Floor(fMSpaceZ);
        float fdX = fMSpaceX - iCellX;
        float fdY = fMSpaceZ - iCellY;

        float fLBHeight = 
            (*(SEVector3f*)VBuffer->PositionTuple(iCellX + 
            iCellY*m_iSize)).Y;
        float fRBHeight = 
            (*(SEVector3f*)VBuffer->PositionTuple(iCellX + 1 + 
            iCellY*m_iSize)).Y;
        float fLTHeight = 
            (*(SEVector3f*)VBuffer->PositionTuple(iCellX + (iCellY + 1)*
            m_iSize)).Y;
        float fRTHeight = 
            (*(SEVector3f*)VBuffer->PositionTuple(iCellX + 1 + (iCellY + 1)*
            m_iSize)).Y;

        if( fdY <= -fdX + 1 )
        {
            float fdBottomHeight = fRBHeight - fLBHeight;
            float fdLeftHeight = fLTHeight - fLBHeight;

            fTempHeight = fLBHeight + fdX*fdBottomHeight + fdY*fdLeftHeight;
        }
        else
        {
            float fdTopHeight = fLTHeight - fRTHeight;
            float fdRightHeight = fRBHeight - fRTHeight;
            
            fTempHeight = fRTHeight + (1.0f - fdX)*fdTopHeight + (1.0f - fdY)
                *fdRightHeight;
        }
    }

    return fTempHeight + World.GetTranslate().Y;
}
//----------------------------------------------------------------------------
void SERoamTerrainPage::InitializeDerivedData()
{
    m_iSizeM1 = m_iSize - 1;
    m_iPatchSizeM1 = m_iPatchSize - 1;
    m_fInvSpacing = 1.0f / m_fSpacing;
    m_fTextureSpacing = 1.0f / (float)m_iSizeM1;
    m_fMultiplier = (m_fMaxElevation - m_fMinElevation) / 65535.0f;
    m_iPatchesPerSide = m_iSizeM1 / m_iPatchSizeM1;
    m_iMaxIndexCount = 6 * m_iSizeM1 * m_iSizeM1;
    m_bNeedsTessellation = true;
    m_bNeedsResetIB = true;

    // 创建patch数组.
    m_Patches.resize(m_iPatchesPerSide);
    for( int i = 0; i < m_iPatchesPerSide; i++ )
    {
        m_Patches[i].resize(m_iPatchesPerSide);
    }

    // 创建triangle pool.
    m_TriPool.resize(m_iPoolSize);

    // 初始化patches.
    for( int iPatchY = 0; iPatchY < m_iPatchesPerSide; iPatchY++ )
    {
        for( int iPatchX = 0; iPatchX < m_iPatchesPerSide; iPatchX++ )
        {
            m_Patches[iPatchY][iPatchX].Initialize(m_ausHeight, this, 
                iPatchX, iPatchY);
            m_Patches[iPatchY][iPatchX].ComputeVariance();
        }
    }
}
//----------------------------------------------------------------------------
void SERoamTerrainPage::ResetPatches()
{
    // 回收Pool中的所有资源.
    SetNextTriNode(0);

    NumTrisRendered = 0;

    SE_ASSERT( m_pTerrain );

    for( int iPatchY = 0; iPatchY < m_iPatchesPerSide; iPatchY++ )
    {
        for( int iPatchX = 0; iPatchX < m_iPatchesPerSide; iPatchX++ )
        {			
            m_Patches[iPatchY][iPatchX].Reset();
            
            // 待实现.
            // patch剔除.

            // 如果该patch高度图数据被修改,则需重新构建静态三角variance树
            if( m_Patches[iPatchY][iPatchX].GetDirty() )
                m_Patches[iPatchY][iPatchX].ComputeVariance();

            if( m_Patches[iPatchY][iPatchX].IsVisible() )
            {
                // 把patch相互连接起来.
                SERoamTriTreeNode* pBaseLeft;
                SERoamTriTreeNode* pBaseRight;

                if( iPatchX > 0 )
                {
                    pBaseLeft = m_Patches[iPatchY][iPatchX].GetBaseLeft();
                    pBaseLeft->pRightNeighbor = 
                        m_Patches[iPatchY][iPatchX - 1].GetBaseRight();
                }
                else
                {
                    if( m_iCol == 0 )
                    {
                        pBaseLeft = m_Patches[iPatchY][iPatchX].GetBaseLeft();
                        pBaseLeft->pRightNeighbor = 0;
                    }
                    else
                    {
                        // 这里应该连接到左边相邻的SERoamTerrainPage.
                        SERoamTerrainPage* pLeftPage = 
                            m_pTerrain->GetPage(m_iRow, m_iCol - 1);
                        pBaseLeft = m_Patches[iPatchY][iPatchX].GetBaseLeft();
                        pBaseLeft->pRightNeighbor = 
                            pLeftPage->m_Patches[iPatchY][m_iPatchesPerSide - 
                            1].GetBaseRight();
                    }
                }

                if( iPatchX < m_iPatchesPerSide - 1 )
                {
                    pBaseRight = m_Patches[iPatchY][iPatchX].GetBaseRight();
                    pBaseRight->pRightNeighbor = 
                        m_Patches[iPatchY][iPatchX + 1].GetBaseLeft();
                }
                else
                {
                    if( m_iCol == m_pTerrain->GetColCount() - 1 )
                    {
                        pBaseRight = m_Patches[iPatchY][iPatchX].GetBaseRight();
                        pBaseRight->pRightNeighbor = 0;
                    }
                    else
                    {
                        // 这里应该连接到右边相邻的SERoamTerrainPage.
                        SERoamTerrainPage* pRightPage = 
                            m_pTerrain->GetPage(m_iRow, m_iCol + 1);
                        pBaseRight = m_Patches[iPatchY][iPatchX].GetBaseRight();
                        pBaseRight->pRightNeighbor = 
                            pRightPage->m_Patches[iPatchY][0].GetBaseLeft();
                    }
                }

                if( iPatchY > 0 )
                {
                    pBaseLeft = m_Patches[iPatchY][iPatchX].GetBaseLeft();
                    pBaseLeft->pLeftNeighbor = 
                        m_Patches[iPatchY - 1][iPatchX].GetBaseRight();
                }
                else
                {
                    if( m_iRow == 0 )
                    {
                        pBaseLeft = m_Patches[iPatchY][iPatchX].GetBaseLeft();
                        pBaseLeft->pLeftNeighbor = 0;
                    }
                    else
                    {
                        // 这里应该连接到下面相邻的SERoamTerrainPage.
                        SERoamTerrainPage* pDownwardPage = 
                            m_pTerrain->GetPage(m_iRow - 1, m_iCol);
                        pBaseLeft = m_Patches[iPatchY][iPatchX].GetBaseLeft();
                        pBaseLeft->pLeftNeighbor = pDownwardPage->m_Patches[
                            m_iPatchesPerSide - 1][iPatchX].GetBaseRight();
                    }
                }

                if( iPatchY < m_iPatchesPerSide - 1 )
                {
                    pBaseRight = m_Patches[iPatchY][iPatchX].GetBaseRight();
                    pBaseRight->pLeftNeighbor = 
                        m_Patches[iPatchY + 1][iPatchX].GetBaseLeft();
                }
                else
                {
                    if( m_iRow == m_pTerrain->GetRowCount() - 1 )
                    {
                        pBaseRight = m_Patches[iPatchY][iPatchX].GetBaseRight();
                        pBaseRight->pLeftNeighbor = 0;
                    }
                    else
                    {
                        // 这里应该连接到上面相邻的SERoamTerrainPage.
                        SERoamTerrainPage* pUpwardPage = 
                            m_pTerrain->GetPage(m_iRow + 1, m_iCol);
                        pBaseRight = m_Patches[iPatchY][
                            iPatchX].GetBaseRight();
                        pBaseRight->pLeftNeighbor = 
                            pUpwardPage->m_Patches[0][iPatchX].GetBaseLeft();
                    }
                }
            }
        }
    }
}
//----------------------------------------------------------------------------
void SERoamTerrainPage::SimplifyPatches(const SECamera* pCamera, SECuller& 
    rCuller)
{
    bool bSingleVisible = rCuller.IsSingleInFrustum(WorldBound);
    if( !bSingleVisible )
        return;

    for( int i = 0; i < m_iPatchesPerSide; i++ )
    {
        for( int j = 0; j < m_iPatchesPerSide; j++ )
        {
            if( m_Patches[i][j].IsVisible() )
                m_Patches[i][j].Tessellate(pCamera);
        }
    }

    m_bNeedsTessellation = true;
}
//----------------------------------------------------------------------------
void SERoamTerrainPage::CollectPatches()
{
    Triangles.clear();
    for( int i = 0; i < m_iPatchesPerSide; i++ )
    {
        for( int j = 0; j < m_iPatchesPerSide; j++ )
        {
            if( m_Patches[i][j].IsVisible() )
                m_Patches[i][j].Collect();
        }
    }
}
//----------------------------------------------------------------------------
void SERoamTerrainPage::GetUnculledSet(SECuller& rCuller, bool bNoCull)
{
    SE_ASSERT( m_pTerrain );

    if( m_pTerrain->GetLod() )
    {
        // 根据收集到的二叉三角树的叶子节点三角形,重建IB.
        if( m_bNeedsTessellation )
        {
            m_bNeedsTessellation = false;

            CollectPatches();

            int iCount, iIndexCount;
            iCount = (int)Triangles.size();
            iIndexCount = 3 * iCount;
            SE_ASSERT( iIndexCount <= m_iMaxIndexCount );

            IBuffer->SetIndexCount(iIndexCount);
            int* aiIndex = IBuffer->GetData();
            for( int i = 0; i < iCount; i++ )
            {
                SERoamTriTreeNode* pTriangle = Triangles[i];
                aiIndex[3*i    ] = pTriangle->LeftIndex;
                aiIndex[3*i + 1] = pTriangle->ApexIndex;
                aiIndex[3*i + 2] = pTriangle->RightIndex;
            }   
            IBuffer->Release();

            // 这里可能引起震荡.
            if( SEMathf::FAbs((float)(GetNextTriNode() - DesiredTris)) >= 50 )
            {
                FrameVariance += ((float)GetNextTriNode() - 
                    (float)DesiredTris)/(float)DesiredTris;
            }

            if( FrameVariance < 1.0f )
                FrameVariance = 1.0f;
        }
    }
    else
    {
        // 重建非LOD状态的IB.
        if( m_bNeedsResetIB )
        {
            m_bNeedsResetIB = false;

            IBuffer->SetIndexCount(m_iMaxIndexCount);
            int* aiIndex = IBuffer->GetData();
            int i, i0, i1;
            for( i1 = 0, i = 0; i1 < m_iSizeM1; i1++ )
            {
                for( i0 = 0; i0 < m_iSizeM1; i0++ )
                {
                    int iV0 = i0 + m_iSize * i1;
                    int iV1 = iV0 + 1;
                    int iV2 = iV1 + m_iSize;
                    int iV3 = iV0 + m_iSize;
                    aiIndex[i++] = iV0;
                    aiIndex[i++] = iV2;
                    aiIndex[i++] = iV1;
                    aiIndex[i++] = iV0;
                    aiIndex[i++] = iV3;
                    aiIndex[i++] = iV2;
                }
            }
            IBuffer->Release();
        }
    }

    if( IBuffer->GetIndexCount() > 0 )
    {
        SETriMesh::GetUnculledSet(rCuller, bNoCull);
    }
}
//----------------------------------------------------------------------------
SERoamTriTreeNode* SERoamTerrainPage::AllocateTri()
{
    SERoamTriTreeNode* pTriTreeNode;
    if( m_iNextTriNode >= m_iPoolSize )
        return 0;

    pTriTreeNode = &(m_TriPool[m_iNextTriNode++]);
    pTriTreeNode->pLeftChild = 0;
    pTriTreeNode->pRightChild = 0;

    return pTriTreeNode;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SERoamTerrainPage::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SETriMesh::Load(rStream, pLink);

    rStream.Read(m_iSize);
    int iVCount = m_iSize * m_iSize;
    m_ausHeight = SE_NEW unsigned short[iVCount];
    rStream.Read(iVCount, m_ausHeight);
    rStream.Read(m_Origin);
    rStream.Read(m_fMinElevation);
    rStream.Read(m_fMaxElevation);
    rStream.Read(m_fSpacing);
    rStream.Read(m_iPoolSize);
    rStream.Read(m_iPatchSize);
    rStream.Read(m_iSplitLevel);
    rStream.Read(m_iVarianceLevel);

    InitializeDerivedData();

    SE_END_DEBUG_STREAM_LOAD(SERoamTerrainPage);
}
//----------------------------------------------------------------------------
void SERoamTerrainPage::SELink(SEStream& rStream, SEStream::SELink* pLink)
{
    SETriMesh::SELink(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SERoamTerrainPage::Register(SEStream& rStream) const
{
    return SETriMesh::Register(rStream);
}
//----------------------------------------------------------------------------
void SERoamTerrainPage::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SETriMesh::Save(rStream);

    rStream.Write(m_iSize);
    int iVCount = VBuffer->GetVertexCount();
    rStream.Write(iVCount, m_ausHeight);
    rStream.Write(m_Origin);
    rStream.Write(m_fMinElevation);
    rStream.Write(m_fMaxElevation);
    rStream.Write(m_fSpacing);
    rStream.Write(m_iPoolSize);
    rStream.Write(m_iPatchSize);
    rStream.Write(m_iSplitLevel);
    rStream.Write(m_iVarianceLevel);

    SE_END_DEBUG_STREAM_SAVE(SERoamTerrainPage);
}
//----------------------------------------------------------------------------
int SERoamTerrainPage::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SETriMesh::GetDiskUsed(rVersion) +
        sizeof(m_iSize) +
        m_iSize*m_iSize*sizeof(m_ausHeight[0]) +
        sizeof(m_Origin) +
        sizeof(m_fMinElevation) +
        sizeof(m_fMaxElevation) +
        sizeof(m_fSpacing) +
        sizeof(m_iPoolSize) +
        sizeof(m_iPatchSize) +
        sizeof(m_iSplitLevel) +
        sizeof(m_iVarianceLevel);
}
//----------------------------------------------------------------------------
SEStringTree* SERoamTerrainPage::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("size =", m_iSize));
    pTree->Append(Format("origin =", m_Origin));
    pTree->Append(Format("min elevation =", m_fMinElevation));
    pTree->Append(Format("max elevation =", m_fMaxElevation));
    pTree->Append(Format("spacing =", m_fSpacing));
    pTree->Append(Format("pool size =", m_iPoolSize));
    pTree->Append(Format("patch size =", m_iPatchSize));
    pTree->Append(Format("split level =", m_iSplitLevel));
    pTree->Append(Format("variance level =", m_iVarianceLevel));
    pTree->Append(Format("uv bias =", m_fUVBias));

    // children
    pTree->Append(SETriMesh::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
