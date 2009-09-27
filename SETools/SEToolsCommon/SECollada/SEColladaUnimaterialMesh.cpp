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
ColladaUnimaterialMesh::ColladaUnimaterialMesh()
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
int& ColladaUnimaterialMesh::VCount()
{
    return m_iVCount;
}
//----------------------------------------------------------------------------
Vector3f*& ColladaUnimaterialMesh::Vertex()
{
    return m_aVertex;
}
//----------------------------------------------------------------------------
Vector3f*& ColladaUnimaterialMesh::Normal()
{
    return m_aNormal;
}
//----------------------------------------------------------------------------
int& ColladaUnimaterialMesh::CCount()
{
    return m_iCCount;
}
//----------------------------------------------------------------------------
ColorRGB*& ColladaUnimaterialMesh::Color()
{
    return m_aColor;
}
//----------------------------------------------------------------------------
int& ColladaUnimaterialMesh::TCount()
{
    return m_iTCount;
}
//----------------------------------------------------------------------------
Vector2f*& ColladaUnimaterialMesh::Texture()
{
    return m_aTexture;
}
//----------------------------------------------------------------------------
int& ColladaUnimaterialMesh::FCount()
{
    return m_iFCount;
}
//----------------------------------------------------------------------------
int*& ColladaUnimaterialMesh::Face()
{
    return m_aiFace;
}
//----------------------------------------------------------------------------
int*& ColladaUnimaterialMesh::CFace()
{
    return m_aiCFace;
}
//----------------------------------------------------------------------------
int*& ColladaUnimaterialMesh::TFace()
{
    return m_aiTFace;
}
//----------------------------------------------------------------------------
MaterialStatePtr& ColladaUnimaterialMesh::MState()
{
    return m_spSEMaterialState;
}
//----------------------------------------------------------------------------
TexturePtr& ColladaUnimaterialMesh::TState()
{
    return m_spTState;
}
//----------------------------------------------------------------------------
void ColladaUnimaterialMesh::DuplicateGeometry()
{
    // 建立一个当前网格的顶点属性数组,
    // 该数组表明了当前网格的每个顶点被平面索引的次数,
    // 每个顶点每次被平面索引时,可能使用不同的顶点颜色和纹理坐标.
    vector<VertexAttr>* aVArray = new vector<VertexAttr>[m_iVCount];
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
    Vector3f* aNewVertex = new Vector3f[iNewVCount];
    Vector3f* aNewNormal = new Vector3f[iNewVCount];

    ColorRGB* aNewColor = NULL;
    if( m_iCCount > 0 )
    {
        aNewColor = new ColorRGB[iNewVCount];
    }

    Vector2f* aNewTexture = NULL;
    if( m_iTCount > 0 )
    {
        aNewTexture = new Vector2f[iNewVCount];
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
        int* aiCIndex = ( m_iCCount > 0 ? m_aiCFace + iThreeI : NULL );
        int* aiTIndex = ( m_iTCount > 0 ? m_aiTFace + iThreeI : NULL );

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

    delete[] m_aVertex;
    delete[] m_aNormal;
    delete[] m_aColor;
    delete[] m_aTexture;
    delete[] m_aiTFace;

    m_iVCount = iNewVCount;
    m_aVertex = aNewVertex;
    m_aNormal = aNewNormal;
    m_aColor = aNewColor;
    m_aTexture = aNewTexture;

    delete[] aVArray;
}
//----------------------------------------------------------------------------
TriMesh* ColladaUnimaterialMesh::ToTriMesh()
{
    // 创建所需Swing Engine VB.
    Attributes tempSEAttr;
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

    VertexBuffer* pSEVBuffer = new VertexBuffer(tempSEAttr, m_iVCount);
    for( int i = 0; i < m_iVCount; i++ )
    {
        (*(Vector3f*)pSEVBuffer->PositionTuple(i)) = m_aVertex[i];

        if( m_aNormal )
        {
            *(Vector3f*)pSEVBuffer->NormalTuple(i) = m_aNormal[i];
        }
        if( m_aColor )
        {
            *(ColorRGB*)pSEVBuffer->ColorTuple(0, i) = m_aColor[i];
        }
        if( m_aTexture )
        {
            *(Vector2f*)pSEVBuffer->TCoordTuple(0, i) = m_aTexture[i];
        }
    }

    // 创建所需Swing Engine IB.
    IndexBuffer* pSEIBuffer = new IndexBuffer(3 * m_iFCount);
    int* pSEIBufferData = pSEIBuffer->GetData();
    memcpy(pSEIBufferData, m_aiFace, 3*m_iFCount*sizeof(int));

    TriMesh* pSEMesh = new TriMesh(pSEVBuffer, pSEIBuffer);

    Effect* pSEEffect = NULL;

    // 根据Swing Engine网格所带材质和纹理,为其添加effect.
    // 目前导出器支持的材质和纹理effect是:
    // MaterialEffect,MaterialTextureEffect,DefaultShaderEffect.

    if( m_spSEMaterialState )
    {
        pSEMesh->AttachGlobalState(m_spSEMaterialState);

        if( m_spTState )
        {
            // 待实现.
            // 当拆分网格后如何处理多重纹理?
            String tempFName = m_spTState->GetImage()->GetName();
            // 减去".seif"长度
            size_t uiLength = strlen((const char*)tempFName) - 5;
            char tempBuffer[64];
            System::SE_Strncpy(tempBuffer, 64, (const char*)tempFName, 
                uiLength);
            tempBuffer[uiLength] = 0;
            pSEEffect = new MaterialTextureEffect(tempBuffer);
        }
        else
        {
            pSEEffect = new MaterialEffect();

            assert( !m_aTexture );
            if( m_aTexture )
            {
                delete[] m_aTexture;
            }
        }
    }

    // 理论上不可能出现这种情况
    if( !m_spSEMaterialState && m_spTState )
    {
        assert( false );
    }

    if( !m_spSEMaterialState && !m_spTState )
    {
        pSEEffect = new DefaultShaderEffect;
    }

    if( pSEEffect )
    {
        pSEMesh->AttachEffect(pSEEffect);
    }

    return pSEMesh;
}
//----------------------------------------------------------------------------
ColladaUnimaterialMesh::VertexAttr::VertexAttr()
{
    V = -1;
    C = -1;
    T = -1;
}
//----------------------------------------------------------------------------
bool ColladaUnimaterialMesh::VertexAttr::operator==(const VertexAttr& rAttr) 
    const
{
    return V == rAttr.V && C == rAttr.C && T == rAttr.T;
}
//----------------------------------------------------------------------------
bool ColladaUnimaterialMesh::VertexAttr::operator<(const VertexAttr& rAttr) const
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