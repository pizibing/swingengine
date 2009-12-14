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

#include "SEMax8SceneBuilder.h"
#include "SEMax8UnimaterialMesh.h"
#include <set>

using namespace std;

// 注意Max使用右手坐标系,而Swing Engine使用左手坐标系.

//----------------------------------------------------------------------------
TriObject* Max8SceneBuilder::GetTriObject(INode* pNode, bool* pbNeedDel)
{
    // 判断一个Max节点是否带有mesh对象.
    //
    // pNode:
    //     待测试的node指针.
    // pbNeedDel:
    //     为true时,调用此函数者有责任删除返回的mesh指针,否则不用.
    // 返回所带的mesh对象,没有则为空.

    Object* pObj = pNode->EvalWorldState(m_iTimeStart).obj;

    // 判断当前节点所带对象是否可以转换为三角网格对象.
    if( !pObj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID, 0)) )
    {
        return NULL;
    }

    // 如果可以转换,则Max可能会为当前对象新建一个三角网格对象.
    TriObject* pTriObj = (TriObject*)pObj->ConvertToType(m_iTimeStart,
        Class_ID(TRIOBJ_CLASS_ID, 0));
    if( pTriObj == NULL )
    {
        return NULL;
    }

    // 判断调用者是否需要删除该三角网格对象.
    *pbNeedDel = (pTriObj != pObj ? true : false);

    return pTriObj;
}
//----------------------------------------------------------------------------
Swing::Spatial* Max8SceneBuilder::BuildMesh(INode* pMaxNode,
    Swing::Spatial* pSENode)
{
    // 把一个Max三角网格转变成一个或多个Swing Engine三角网格.
    //
    // pMaxNode:
    //     Max场景中的Mesh节点指针.
    // pSENode:
    //     即将创建的Swing Engine三角网格的父节点指针.
    // 返回新创建的Swing Engine场景子节点,
    // 如果当前Max的Mesh节点没有被拆分,则直接返回新建的Swing Engine三角网格节点,
    // 否则返回一个Swing Engine的"link"虚节点,
    // 被拆分的Max节点子Mesh都将作为该"link"节点的子节点.

    bool bNeedDel = false;
    TriObject* pTriObj = GetTriObject(pMaxNode, &bNeedDel);
    if( !pTriObj )
    {
        return NULL;
    }
    Mesh* pMaxMesh = &pTriObj->GetMesh();

    Mtl* pMtl = NULL;
    int iMtlID = -1;
    pMtl = pMaxNode->GetMtl();
    if( pMtl )
	{
        iMtlID = m_MtlList.GetID(pMtl);
        assert( iMtlID >= 0 );
	}

    Swing::Spatial* pSELink;
    bool bHasLink = ((int)pSENode->GetName().length() > 0 &&
        strcmp(pMaxNode->GetName(), pSENode->GetName().c_str()) == 0);
    char* acMaxName = pMaxNode->GetName();
    int i;

    // 因为Swing Engine网格只能带有一个材质,
    // 因此要判断当前Max网格是否带有多个材质,如果有则需要拆分该网格,
    // 拆分后生成的子网格只能带有一个材质.
    // 如果不需要拆分Max网格,则直接创建Swing Engine网格并连接给Swing Engine父节点,
    // 否则创建一个Swing Engine"link"虚节点作为拆分后的子网格的父节点.
    vector<Max8UnimaterialMesh*> tempUMeshes;
    SplitGeometry(pMaxMesh, iMtlID, tempUMeshes);
    if( tempUMeshes.size() > 1 )
    {
        // 如果拆分了,则建立一个Swing Engine"link"虚节点.
        if( !bHasLink )
        {
            pSELink = BuildSpatial(pMaxNode, pSENode);
        }
        else
        {
            pSELink = pSENode;
        }

        assert( pSELink->IsDerived(Swing::Node::TYPE) );

        // 把拆分后获得的Swing Engine子网格都作为"link"虚节点的子节点.
        for( i = 0; i < (int)tempUMeshes.size(); i++ )
        {
            Swing::TriMesh* pSETriMesh = tempUMeshes[i]->ToTriMesh();
            char acMeshNumber[6];
            Swing::System::SE_Sprintf(acMeshNumber, 6, "_%d", i + 1);
            size_t uiSize = strlen(acMaxName) + strlen(acMeshNumber) + 1;
            char* acSEName = new char[uiSize];
            Swing::System::SE_Strcpy(acSEName, uiSize, acMaxName);
            Swing::System::SE_Strcat(acSEName, uiSize, acMeshNumber);         
            pSETriMesh->SetName(acSEName);
            delete[] acSEName;
            ((Swing::Node*)pSELink)->AttachChild(pSETriMesh);
        }
    }
    else
    {
        // 如果没有拆分,则把获取的Swing Engine网格作为pSENode的子节点.
        Swing::TriMesh* pSETriMesh = tempUMeshes[0]->ToTriMesh();
        if( !bHasLink )
        {
            pSETriMesh->SetName(acMaxName);
            pSETriMesh->Local = GetLocalTransform(pMaxNode, m_iTimeStart);
        }
        else
        {
            size_t uiSize = strlen(acMaxName) + 3;
            char* acSEName = new char[uiSize];
            Swing::System::SE_Strcpy(acSEName, uiSize, acMaxName);
            Swing::System::SE_Strcat(acSEName, uiSize, "_1");
            pSETriMesh->SetName(acSEName);
            delete[] acSEName;
        }
        assert( pSENode->IsDerived(Swing::Node::TYPE) );
        ((Swing::Node*)pSENode)->AttachChild(pSETriMesh);
        pSELink = pSETriMesh;
    }
    for( i = 0; i < (int)tempUMeshes.size(); i++ )
    {
        delete tempUMeshes[i];
    }

    if( bNeedDel )
    {
        delete pTriObj;
    }

    return pSELink;
}
//----------------------------------------------------------------------------
void Max8SceneBuilder::SplitGeometry(Mesh* pMaxMesh, int iMtlID, 
    vector<Max8UnimaterialMesh*>& rUMeshes)
{
    // 如果一个Max网格使用了多个子材质,
    // 则需要拆分成若干个Swing Engine网格,因为Swing Engine网格对象只支持一个材质.
    //
    // pMaxMesh:
    //     待拆分的Max网格对象指针.
    // rUMeshes:
    //     拆分后存储子网格的数组.
    // bHasReflection:
    //     为true时,表明节点的变换包含反射变换,否则为false.

    int i, j;

    // 计算顶点法线.
    Swing::Vector3f* aNormal = NULL;
    if( m_pSettings->IncludeNormals )
    {
        pMaxMesh->buildNormals();
        aNormal = new Swing::Vector3f[pMaxMesh->numVerts];
        for( i = 0; i < pMaxMesh->numFaces; i++ )
        {
            Face& rFace = pMaxMesh->faces[i];
            for( j = 0; j < 3; j++ )
            {
                int iVertex = rFace.getVert(j);
                aNormal[iVertex] += GetVertexNormal(pMaxMesh, i, iVertex); // 待检查
            }
        }
    }

    // 子材质数
    int iSubCount = 0;
    Max8MaterialTree* pTree = 0;
    if( iMtlID >= 0 )
    {
        pTree = &m_MtlTree[iMtlID];
        iSubCount = pTree->GetMChildCount();
    }

    // 计算网格所使用的最大子材质索引.
    int iFace, iSubID, iMaxSubID = -1;
    for( iFace = 0; iFace < pMaxMesh->numFaces; iFace++ )
    {
        iSubID = pMaxMesh->faces[iFace].getMatID();
        if( iSubID >= iSubCount )
        {
            if( iSubCount > 0 )
            {
                iSubID = iSubID % iSubCount;
            }
            else
            {
                iSubID = 0;
            }
        }
        if( iSubID > iMaxSubID )
        {
            iMaxSubID = iSubID;
        }
    }

    // 根据材质ID分组网格平面.
    vector<int>* aPartition = new vector<int>[iMaxSubID + 1];
    for( iFace = 0; iFace < pMaxMesh->numFaces; iFace++ )
    {
        iSubID = pMaxMesh->faces[iFace].getMatID();
        if( iSubID >= iSubCount )
        {
            if( iSubCount > 0 )
            {
                iSubID = iSubID % iSubCount;
            }
            else
            {
                iSubID = 0;
            }
        }
        aPartition[iSubID].push_back(iFace);
    }

    // 分配unimaterial网格.
    for( iSubID = 0; iSubID <= iMaxSubID; iSubID++ )
    {
        if( aPartition[iSubID].size() == 0 )
        {
            // 没有任何网格平面使用该子材质.
            continue;
        }

        Max8UnimaterialMesh* pMesh = new Max8UnimaterialMesh;
        if( iMtlID >= 0 )
        {
            // 待实现.
            // 目前,只是简单的使用了第一个非空纹理.
            // 稍后应支持多重纹理.
            if( iSubCount > 0 )
            {
                Max8MaterialTree& rSubtree = pTree->GetMChild(iSubID);
                pMesh->MState() = rSubtree.GetMaterial();
                for( i = 0; i < (int)rSubtree.GetTChildCount(); i++ )
                {
                    if( rSubtree.GetTexture(i) )
                    {
                        pMesh->TState() = rSubtree.GetTexture(i);

                        break;
                    }
                }
            }
            else
            {
                pMesh->MState() = pTree->GetMaterial();
                for( i = 0; i < (int)pTree->GetTChildCount(); i++ )
                {
                    if( pTree->GetTexture(i) )
                    {
                        pMesh->TState() = pTree->GetTexture(i);

                        break;
                    }
                }
            }
        }

        // 打包顶点.
        PackVertices(pMesh, pMaxMesh, aPartition[iSubID], aNormal);

        // 打包颜色.
        if( m_pSettings->IncludeVertexColors && pMaxMesh->numCVerts > 0 )
        {
            PackColors(pMesh, pMaxMesh, aPartition[iSubID]);
        }

        // 打包纹理坐标.
        if( m_pSettings->IncludeTexCoords &&  pMaxMesh->numTVerts > 0
            && pMesh->TState() )
        {
            PackTextures(pMesh, pMaxMesh, aPartition[iSubID]);
        }

        rUMeshes.push_back(pMesh);
    }

    delete[] aPartition;
    delete[] aNormal;

    // 根据Swing Engine顶点数据限制要求,复制顶点数据.
    for( i = 0; i < (int)rUMeshes.size(); i++ )
    {
        rUMeshes[i]->DuplicateGeometry();
    }
}
//----------------------------------------------------------------------------
void Max8SceneBuilder::PackVertices(Max8UnimaterialMesh* pUniMesh,
    Mesh* pMaxMesh, vector<int>& rPartition, Swing::Vector3f* aNormal)
{
    // 接收Max网格的一部分(由一个平面索引数组表示),该部分使用同一材质.
    // 把相应的顶点和法线数据打包进Max8UnimaterialMesh.
    //
    // pUniMesh:
    //     用于接收数据的Max8UnimaterialMesh指针.
    // pMaxMesh:
    //     用于获取顶点数据的Max网格指针.
    // rPartition:
    //     表示Max网格一部分的平面索引数组.
    // aNormal:
    //     用于获取数据的Max网格的全部顶点法线.

    // 当前部分所使用的顶点索引,set确保顶点唯一性.
    set<int> tempVIndexSet;
    int i, j;
    for( i = 0; i < (int)rPartition.size(); i++ )
    {
        Face& rFace = pMaxMesh->faces[rPartition[i]];
        for( j = 0; j < 3; j++ )
        {
            tempVIndexSet.insert(rFace.v[j]);
        }
    }

    // 全局网格顶点索引是顶点在整个Max网格顶点资源数组中的索引.
    // 建立一个全局网格顶点索引的反向映射表,
    // 针对当前使用同一材质的子网格,建立一个子网格顶点资源数组,
    // 该顶点数组下标0到n,表示n+1个不重复的顶点),
    // 建立反向映射数组(数组下标0到m,表示顶点的全局网格顶点索引,m为最大索引值).
    // STL set类默认把插入的元素按照增序排列存储,
    // 因此当前set中末尾元素必定为当前子网格的最大全局网格顶点索引.
    // 如果tempVIndexSet[i] = j,则aiVMap[j] = i.
    // 如果是当前子网格没有用到的全局网格顶点索引,则aiVMap[j] = -1.
    int iVMax = *tempVIndexSet.rbegin();
    int* aiVMap = new int[iVMax + 1];
    memset(aiVMap, 0xFF, (iVMax + 1)*sizeof(int));

    pUniMesh->VCount() = tempVIndexSet.size();
    pUniMesh->Vertex() = new Swing::Vector3f[pUniMesh->VCount()];
    pUniMesh->Normal() = new Swing::Vector3f[pUniMesh->VCount()];

    set<int>::iterator tempIter = tempVIndexSet.begin();
    for( i = 0; i < (int)tempVIndexSet.size(); i++, tempIter++ )
    {
        j = *tempIter;
        aiVMap[j] = i;

        pUniMesh->Vertex()[i].X = pMaxMesh->verts[j].x;
        pUniMesh->Vertex()[i].Y = pMaxMesh->verts[j].z;
        pUniMesh->Vertex()[i].Z = pMaxMesh->verts[j].y;
        pUniMesh->Normal()[i].X = aNormal[j].X;
        pUniMesh->Normal()[i].Y = aNormal[j].Z;
        pUniMesh->Normal()[i].Z = aNormal[j].Y;
    }

    // 建立子网格面顶点索引.
    pUniMesh->FCount() = rPartition.size();
    pUniMesh->Face() = new int[3 * pUniMesh->FCount()];
    for( i = 0; i < (int)rPartition.size(); i++ )
    {
        Face& rFace = pMaxMesh->faces[rPartition[i]];

        pUniMesh->Face()[3*i    ] = aiVMap[rFace.v[0]];
        pUniMesh->Face()[3*i + 1] = aiVMap[rFace.v[2]];
        pUniMesh->Face()[3*i + 2] = aiVMap[rFace.v[1]];
    }
    delete[] aiVMap;
}
//----------------------------------------------------------------------------
void Max8SceneBuilder::PackColors(Max8UnimaterialMesh* pUniMesh, Mesh* pMaxMesh, 
    vector<int>& rPartition)
{
    // 接收Max网格的一部分(由一个平面索引数组表示),该部分使用同一材质.
    // 把相应的顶点颜色打包进Max8UnimaterialMesh.
    //
    // pUniMesh:
    //     用于接收数据的Max8UnimaterialMesh指针.
    // pMaxMesh:
    //     用于获取颜色数据的Max网格指针.
    // rPartition:
    //     表示Max网格一部分的平面索引数组.

    // 当前部分所使用的颜色索引,set确保颜色唯一性.
    set<int> tempCIndexSet;
    int i, j;
    for( i = 0; i < (int)rPartition.size(); i++ )
    {
        TVFace& rCFace = pMaxMesh->vcFace[rPartition[i]];
        for( j = 0; j < 3; j++ )
        {
            tempCIndexSet.insert(rCFace.t[j]);
        }
    }

    // 全局网格颜色索引是颜色在整个Max网格颜色资源数组中的索引.
    // 建立一个全局网格颜色索引的反向映射表,
    // 针对当前使用同一材质的子网格,建立一个子网格颜色资源数组,
    // 该颜色数组下标0到n,表示n+1个不重复的颜色),
    // 建立反向映射数组(数组下标0到m,表示颜色的全局网格颜色索引,m为最大索引值).
    // STL set类默认把插入的元素按照增序排列存储,
    // 因此当前set中末尾元素必定为当前子网格的最大全局网格颜色索引.
    // 如果tempCIndexSet[i] = j,则aiCMap[j] = i.
    // 如果是当前子网格没有用到的全局网格颜色索引,则aiCMap[j] = -1.
    int iCMax = *tempCIndexSet.rbegin();
    int* aiCMap = new int[iCMax + 1];
    memset(aiCMap, 0xFF, (iCMax + 1)*sizeof(int));

    pUniMesh->CCount() = tempCIndexSet.size();
    pUniMesh->Color() = new Swing::ColorRGB[pUniMesh->CCount()];

    set<int>::iterator tempIter = tempCIndexSet.begin();
    for( i = 0; i < (int)tempCIndexSet.size(); i++, tempIter++ )
    {
        j = *tempIter;
        aiCMap[j] = i;

        pUniMesh->Color()[i].R = pMaxMesh->vertCol[j].x;
        pUniMesh->Color()[i].G = pMaxMesh->vertCol[j].y;
        pUniMesh->Color()[i].B = pMaxMesh->vertCol[j].z;
    }

    // 建立子网格面颜色索引.
    pUniMesh->CFace() = new int[3*pUniMesh->FCount()];
    for( i = 0; i < (int)rPartition.size(); i++ )
    {
        TVFace& rCFace = pMaxMesh->vcFace[rPartition[i]];

        pUniMesh->CFace()[3*i    ] = aiCMap[rCFace.t[0]];
        pUniMesh->CFace()[3*i + 1] = aiCMap[rCFace.t[2]];
        pUniMesh->CFace()[3*i + 2] = aiCMap[rCFace.t[1]];
    }
    delete[] aiCMap;
}
//----------------------------------------------------------------------------
void Max8SceneBuilder::PackTextures(Max8UnimaterialMesh* pUniMesh,
    Mesh* pMaxMesh, vector<int>& rPartition)
{
    // 接收Max网格的一部分(由一个平面索引数组表示),该部分使用同一材质.
    // 把相应的顶点纹理坐标打包进Max8UnimaterialMesh.
    //
    // pUniMesh:
    //     用于接收数据的Max8UnimaterialMesh指针.
    // pMaxMesh:
    //     用于获取纹理坐标数据的Max网格指针.
    // rPartition:
    //     表示Max网格一部分的平面索引数组.

    // 当前部分所使用的纹理坐标索引,set确保纹理坐标唯一性.
    set<int> tempTIndexSet;
    int i, j;
    for( i = 0; i < (int)rPartition.size(); i++ )
    {
        TVFace& rTFace = pMaxMesh->tvFace[rPartition[i]];
        for( j = 0; j < 3; j++ )
        {
            tempTIndexSet.insert(rTFace.t[j]);
        }
    }

    // 全局网格纹理坐标索引是纹理坐标在整个Max网格纹理坐标资源数组中的索引.
    // 建立一个全局网格纹理坐标索引的反向映射表,
    // 针对当前使用同一材质的子网格,建立一个子网格纹理坐标资源数组,
    // 该纹理坐标数组下标0到n,表示n+1个不重复的纹理坐标),
    // 建立反向映射数组(数组下标0到m,表示纹理坐标的全局网格纹理坐标索引,m为最大索引值).
    // STL set类默认把插入的元素按照增序排列存储,
    // 因此当前set中末尾元素必定为当前子网格的最大全局网格纹理坐标索引.
    // 如果tempTIndexSet[i] = j,则aiTMap[j] = i.
    // 如果是当前子网格没有用到的全局网格纹理坐标索引,则aTMap[j] = -1.
    int iTMax = *tempTIndexSet.rbegin();
    int* aiTMap = new int[iTMax + 1];
    memset(aiTMap, 0xFF, (iTMax + 1)*sizeof(int));

    pUniMesh->TCount() = tempTIndexSet.size();
    pUniMesh->Texture() = new Swing::Vector2f[pUniMesh->TCount()];

    set<int>::iterator tempIter = tempTIndexSet.begin();
    for( i = 0; i < (int)tempTIndexSet.size(); i++, tempIter++ )
    {
        j = *tempIter;
        aiTMap[j] = i;

        pUniMesh->Texture()[i].X = pMaxMesh->tVerts[j].x;
        pUniMesh->Texture()[i].Y = pMaxMesh->tVerts[j].y;
    }

    // 建立子网格面纹理坐标索引.
    pUniMesh->TFace() = new int[3 * pUniMesh->FCount()];
    for( i = 0; i < (int)rPartition.size(); i++ )
    {
        TVFace& rTFace = pMaxMesh->tvFace[rPartition[i]];

        pUniMesh->TFace()[3*i    ] = aiTMap[rTFace.t[0]];
        pUniMesh->TFace()[3*i + 1] = aiTMap[rTFace.t[2]];
        pUniMesh->TFace()[3*i + 2] = aiTMap[rTFace.t[1]];
    }
    delete[] aiTMap;
}
//----------------------------------------------------------------------------
Swing::Vector3f Max8SceneBuilder::GetVertexNormal(Mesh* pMaxMesh, int iFace,
    int iVertex)
{
    // 获取顶点法线,针对一个Max网格顶点索引.
    // 
    // pMaxMesh:
    //     包含该顶点的Max网格.
    // iFace:
    //     该顶点所属平面的索引.
    // iVertex:
    //     该顶点的索引.
    // 返回顶点法线.

    Point3 tempNormal;

    RVertex* pRV = pMaxMesh->getRVertPtr(iVertex);
    
    if( pRV->rFlags & SPECIFIED_NORMAL )
    {
        tempNormal = pRV->rn.getNormal();
    }
    else
    {
        // 如果RVertex不包含与之相关的法线向量,
        // 则通过一个smoothing group来计算该法线,
        // 如果这个smoothing group也不存在,则使用面法线.
        Face& rFace = pMaxMesh->faces[iFace];
        DWORD dwSmoothingGroup = rFace.smGroup;
        int iNumNormals = pRV->rFlags & NORCT_MASK;
        if( iNumNormals && dwSmoothingGroup )
        {
            if( iNumNormals == 1 )
            {
                // 如果group中只有一个法线,则rRV中已经存储了该法线.
                tempNormal = pRV->rn.getNormal();
            }
            else
            {
                // 从smoothing group中找到所需法线.
                for( int i = 0; i < iNumNormals; i++ )
                {
                    if( pRV->ern[i].getSmGroup() & dwSmoothingGroup )
                    {
                        tempNormal = pRV->ern[i].getNormal();

                        break;
                    }
                }
            }
        }
        else
        {
            // 没有smoothing group时则使用相关平面的法线.
            tempNormal = pMaxMesh->FaceNormal(iFace, true);
        }
    }

    return Swing::Vector3f(tempNormal.x, tempNormal.y, tempNormal.z);
}
//----------------------------------------------------------------------------