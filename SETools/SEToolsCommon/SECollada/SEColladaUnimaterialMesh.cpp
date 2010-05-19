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

#include "SEToolsCommonPCH.h"
#include "SEColladaUnimaterialMesh.h"
#include <algorithm>
#include <vector>

using namespace Swing;
using namespace std;

//----------------------------------------------------------------------------
SEColladaUnimaterialMesh::SEColladaUnimaterialMesh()
{
    m_iVCount = 0;
    m_aVertex = 0;
    m_aNormal = 0;
    m_iCCount = 0;
    m_aColor = 0;
    m_iTCount = 0;
    m_aTexture = 0;
    m_iFCount = 0;
    m_aiFace = 0;
    m_aiCFace = 0;
    m_aiTFace = 0;
}
//----------------------------------------------------------------------------
int& SEColladaUnimaterialMesh::VCount()
{
    return m_iVCount;
}
//----------------------------------------------------------------------------
SEVector3f*& SEColladaUnimaterialMesh::Vertex()
{
    return m_aVertex;
}
//----------------------------------------------------------------------------
SEVector3f*& SEColladaUnimaterialMesh::Normal()
{
    return m_aNormal;
}
//----------------------------------------------------------------------------
int& SEColladaUnimaterialMesh::CCount()
{
    return m_iCCount;
}
//----------------------------------------------------------------------------
SEColorRGB*& SEColladaUnimaterialMesh::Color()
{
    return m_aColor;
}
//----------------------------------------------------------------------------
int& SEColladaUnimaterialMesh::TCount()
{
    return m_iTCount;
}
//----------------------------------------------------------------------------
SEVector2f*& SEColladaUnimaterialMesh::SETexture()
{
    return m_aTexture;
}
//----------------------------------------------------------------------------
int& SEColladaUnimaterialMesh::FCount()
{
    return m_iFCount;
}
//----------------------------------------------------------------------------
int*& SEColladaUnimaterialMesh::Face()
{
    return m_aiFace;
}
//----------------------------------------------------------------------------
int*& SEColladaUnimaterialMesh::CFace()
{
    return m_aiCFace;
}
//----------------------------------------------------------------------------
int*& SEColladaUnimaterialMesh::TFace()
{
    return m_aiTFace;
}
//----------------------------------------------------------------------------
SEMaterialStatePtr& SEColladaUnimaterialMesh::MState()
{
    return m_spSEMaterialState;
}
//----------------------------------------------------------------------------
SETexturePtr& SEColladaUnimaterialMesh::TState()
{
    return m_spTState;
}
//----------------------------------------------------------------------------
void SEColladaUnimaterialMesh::DuplicateGeometry()
{
    // 建立一个当前网格的顶点属性数组,
    // 该数组表明了当前网格的每个顶点被平面索引的次数,
    // 每个顶点每次被平面索引时,可能使用不同的顶点颜色和纹理坐标.
    vector<VertexAttr>* aVArray = SE_NEW vector<VertexAttr>[m_iVCount];
    int i;
    for( i = 0; i < 3*m_iFCount; i++ )
    {
        VertexAttr tempAttr;

        tempAttr.V = m_aiFace[i];

        if( m_iCCount > 0 )
        {
            tempAttr.C = m_aiCFace[i];
        }

        if( m_iTCount > 0 )
        {
            tempAttr.T = m_aiTFace[i];
        }

        aVArray[m_aiFace[i]].push_back(tempAttr);
    }

    // 如果某个顶点被多次索引,并且在这些索引中指定了不同的顶点颜色或纹理坐标,
    // 则根据我们的数据要求,该顶点应该被复制,复制出的新顶点使用同样的顶点索引,
    // 但使用了不同的颜色或纹理坐标索引.
    // 因此为了包含这些新复制出的顶点,计算总共需要多少顶点.
    int iNewVCount = 0;
    for( i = 0; i < m_iVCount; i++ )
    {
        // 确保唯一性,移除重复的索引.
        sort(aVArray[i].begin(), aVArray[i].end());
        vector<VertexAttr>::iterator pEnd = unique(aVArray[i].begin(),
            aVArray[i].end());
        aVArray[i].erase(pEnd, aVArray[i].end());
        iNewVCount += (int)aVArray[i].size();
    }

    // 分配Swing Engine几何体所需数据.
    SEVector3f* aNewVertex = SE_NEW SEVector3f[iNewVCount];
    SEVector3f* aNewNormal = SE_NEW SEVector3f[iNewVCount];

    SEColorRGB* aNewColor = 0;
    if( m_iCCount > 0 )
    {
        aNewColor = SE_NEW SEColorRGB[iNewVCount];
    }

    SEVector2f* aNewTexture = 0;
    if( m_iTCount > 0 )
    {
        aNewTexture = SE_NEW SEVector2f[iNewVCount];
    }

    int j, k;
    for( i = 0, k = 0; i < m_iVCount; i++ )
    {
        vector<VertexAttr>& rVArray = aVArray[i];
        int iSize = (int)rVArray.size();
        for( j = 0; j < iSize; j++, k++ )
        {
            aNewVertex[k] = m_aVertex[i];
            aNewNormal[k] = m_aNormal[i];

            VertexAttr tempAttr = rVArray[j];

            if( aNewColor )
            {
                aNewColor[k] = m_aColor[tempAttr.C];
            }

            if( aNewTexture )
            {
                aNewTexture[k] = m_aTexture[tempAttr.T];
            }

            // 复制当前slot中的每个顶点属性,供稍后使用.
            tempAttr.V = k;
            rVArray.push_back(tempAttr);
        }
    }

    // 修改平面顶点索引,使其索引到新创建的重复顶点.
    for( i = 0; i < m_iFCount; i++ )
    {
        int iThreeI = 3 * i;
        int* aiVIndex = m_aiFace + iThreeI;
        int* aiCIndex = ( m_iCCount > 0 ? m_aiCFace + iThreeI : 0 );
        int* aiTIndex = ( m_iTCount > 0 ? m_aiTFace + iThreeI : 0 );

        for( j = 0; j < 3; j++ )
        {
            VertexAttr tempAttr;
            tempAttr.V = aiVIndex[j];

            if( aiCIndex )
            {
                tempAttr.C = aiCIndex[j];
            }

            if( aiTIndex )
            {
                tempAttr.T = aiTIndex[j];
            }

            // VArray中有N个原始顶点属性和N个复制出的顶点属性.
            vector<VertexAttr>& rVArray = aVArray[aiVIndex[j]];
            int iHalfSize = (int)rVArray.size()/2;
            for( k = 0; k < iHalfSize; k++ )
            {
                if( rVArray[k] == tempAttr )
                {
                    // 找到匹配的顶点属性,更新顶点索引.
                    aiVIndex[j] = rVArray[iHalfSize + k].V;

                    break;
                }
            }
        }
    }

    SE_DELETE[] m_aVertex;
    SE_DELETE[] m_aNormal;
    SE_DELETE[] m_aColor;
    SE_DELETE[] m_aTexture;
    SE_DELETE[] m_aiTFace;

    m_iVCount = iNewVCount;
    m_aVertex = aNewVertex;
    m_aNormal = aNewNormal;
    m_aColor = aNewColor;
    m_aTexture = aNewTexture;

    SE_DELETE[] aVArray;
}
//----------------------------------------------------------------------------
SETriMesh* SEColladaUnimaterialMesh::ToTriMesh()
{
    // 创建所需Swing Engine VB.
    SEAttributes tempSEAttr;
    tempSEAttr.SetPositionChannels(3);
    if( m_aNormal )
    {
        tempSEAttr.SetNormalChannels(3);
    }
    if( m_aColor )
    {
        tempSEAttr.SetColorChannels(0, 3);
    }
    if( m_aTexture )
    {
        tempSEAttr.SetTCoordChannels(0, 2);
    }

    SEVertexBuffer* pSEVBuffer = SE_NEW SEVertexBuffer(tempSEAttr, m_iVCount);
    for( int i = 0; i < m_iVCount; i++ )
    {
        (*(SEVector3f*)pSEVBuffer->PositionTuple(i)) = m_aVertex[i];

        if( m_aNormal )
        {
            *(SEVector3f*)pSEVBuffer->NormalTuple(i) = m_aNormal[i];
        }
        if( m_aColor )
        {
            *(SEColorRGB*)pSEVBuffer->ColorTuple(0, i) = m_aColor[i];
        }
        if( m_aTexture )
        {
            *(SEVector2f*)pSEVBuffer->TCoordTuple(0, i) = m_aTexture[i];
        }
    }

    // 创建所需Swing Engine IB.
    SEIndexBuffer* pSEIBuffer = SE_NEW SEIndexBuffer(3 * m_iFCount);
    int* pSEIBufferData = pSEIBuffer->GetData();
    memcpy(pSEIBufferData, m_aiFace, 3*m_iFCount*sizeof(int));

    SETriMesh* pSEMesh = SE_NEW SETriMesh(pSEVBuffer, pSEIBuffer);

    SEEffect* pSEEffect = 0;

    // 根据Swing Engine网格所带材质和纹理,为其添加effect.
    // 目前导出器支持的材质和纹理effect是:
    // SEMaterialEffect,SEMaterialTextureEffect,SEDefaultShaderEffect.

    if( m_spSEMaterialState )
    {
        pSEMesh->AttachGlobalState(m_spSEMaterialState);

        if( m_spTState )
        {
            // 待实现.
            // 当拆分网格后如何处理多重纹理?
            SEImage* pImage = m_spTState->GetImage();
            SE_ASSERT( pImage );
            if( pImage )
            {
                std::string tempFName = pImage->GetName();
                // 减去".seif"长度.
                size_t uiLength = strlen(tempFName.c_str()) - 5;
                char tempBuffer[64];
                SESystem::SE_Strncpy(tempBuffer, 64, tempFName.c_str(), 
                    uiLength);
                tempBuffer[uiLength] = 0;
                pSEEffect = SE_NEW SEMaterialTextureEffect(tempBuffer);
            }
        }
        else
        {
            pSEEffect = SE_NEW SEDefaultShaderEffect;

            if( m_aTexture )
            {
                SE_DELETE[] m_aTexture;
            }
        }
    }

    // 理论上不可能出现这种情况.
    if( !m_spSEMaterialState && m_spTState )
    {
        SE_ASSERT( false );
    }

    if( !m_spSEMaterialState && !m_spTState )
    {
        pSEEffect = SE_NEW SEDefaultShaderEffect;
    }

    if( pSEEffect )
    {
        pSEMesh->AttachEffect(pSEEffect);
    }

    return pSEMesh;
}
//----------------------------------------------------------------------------
SEColladaUnimaterialMesh::VertexAttr::VertexAttr()
{
    V = -1;
    C = -1;
    T = -1;
}
//----------------------------------------------------------------------------
bool SEColladaUnimaterialMesh::VertexAttr::operator==(const VertexAttr& rAttr) 
    const
{
    return V == rAttr.V && C == rAttr.C && T == rAttr.T;
}
//----------------------------------------------------------------------------
bool SEColladaUnimaterialMesh::VertexAttr::operator<(const VertexAttr& rAttr) 
    const
{
    if( V < rAttr.V )
    {
        return true;
    }

    if( V > rAttr.V )
    {
        return false;
    }

    if( C < rAttr.C )
    {
        return true;
    }

    if( C > rAttr.C )
    {
        return false;
    }

    return T < rAttr.T;
}
//----------------------------------------------------------------------------