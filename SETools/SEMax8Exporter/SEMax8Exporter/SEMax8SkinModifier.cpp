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
#include "iparamb2.h"
#include "iskin.h"

//----------------------------------------------------------------------------
void Max8SceneBuilder::ProcessSkin(INode* pMaxNode, Modifier* pSkinMod)
{
    // 蒙皮控制器是基于CPU的蒙皮方法.
    // 蒙皮Effect是基于GPU的蒙皮方法.
    // 构建蒙皮控制器或蒙皮Effect.如果Max网格在导出时需要被拆分,
    // 则在拆分过程中创建的Swing Engine子网格都需要添加蒙皮控制器或蒙皮Effect.
    // 蒙皮顶点偏移量是蒙皮顶点在骨骼局部坐标系下的坐标,
    // 蒙皮控制器使用蒙皮顶点偏移量.
    // 通过动画开始时间处的网格顶点世界坐标和骨骼世界变换来计算获得.
    //
    // pMaxNode:
    //     带有Max蒙皮修改器的Max节点指针.
    // pSkinMod:
    //     Max蒙皮修改器对象指针.

    bool bNeedDel;
    TriObject* pTriObj = GetTriObject(pMaxNode, &bNeedDel);
    Mesh* pMesh = &pTriObj->GetMesh();

    // 获取Max蒙皮修改器类接口指针.
    ISkin* pSkin = (ISkin*)pSkinMod->GetInterface(I_SKIN);
    ISkinContextData* pSkinData = pSkin->GetContextInterface(pMaxNode);

    // 循环遍历所有骨骼,存储初始骨骼旋转和缩放变换,
    // 并从场景视图找到与之相应的Swing Engine节点.
    int iB, iBoneCount = pSkin->GetNumBones();
    Swing::Node** apSEBones = new Swing::Node*[iBoneCount];
    for( iB = 0; iB < iBoneCount; iB++ )
    {
        INode* pBoneNode = pSkin->GetBone(iB);
        apSEBones[iB] = Swing::StaticCast<Swing::Node>(
            m_spSEScene->GetObjectByName(pBoneNode->GetName()));
    }

    // 检查对应于Max蒙皮网格的Swing Engine节点,
    // 如果它自身是一个网格节点,
    // 则说明在之前的场景遍历过程中,与之对应的Max网格没有被拆分,
    // 否则它应该是一个"link"节点,连接着拆分生成的Swing Engine子网格节点.
    vector<Swing::TriMesh*> aSEMeshes;
    Swing::Object* pSEObject = m_spSEScene->GetObjectByName(pMaxNode->GetName());
    if( pSEObject->IsExactly(Swing::TriMesh::TYPE) )
    {
        aSEMeshes.push_back(Swing::StaticCast<Swing::TriMesh>(pSEObject));
    }
    else
    {
        Swing::Node* pSENode = Swing::StaticCast<Swing::Node>(pSEObject);
        const char* acName = pSENode->GetName();
        for( int iC = 0; iC < pSENode->GetCount(); iC++ )
        {
            Swing::Spatial* pSEChild = pSENode->GetChild(iC);
            const char* acCName = pSEChild->GetName();
            if( strncmp(acCName, acName, strlen(acName)) == 0 )
            {
                aSEMeshes.push_back(Swing::StaticCast<Swing::TriMesh>(pSEChild));
            }
        }
    }

    // 为对应Max网格的所有Swing Engine子网格创建蒙皮控制器或蒙皮修改器.
    int* aiVerticesPerBone = new int[iBoneCount];
    for( int iM = 0; iM < (int)aSEMeshes.size(); iM++ )
    {
        Swing::TriMesh* pSEMesh = aSEMeshes[iM];

        // 判断Max网格的哪些顶点被包含在当前Swing Engine子网格中,
        // 并保存那些Max顶点索引.
        // 待实现:
        // 比较操作是顶点对顶点的.如果原始顶点数组有冗余重复顶点怎么办?
        // 在PackVertices函数中所使用的hash数据结构应该被保存下来,
        // 那样的话我们可以利用那些数据,从而不用进行潜在低效率的双重循环算法.
        int iVCount = pSEMesh->VBuffer->GetVertexCount();
        vector<int> tempVIArray;
        int iV, i, j, k;
        for( iV = 0; iV < iVCount; iV++ )
        {
            for( i = 0; i < pMesh->getNumVerts(); i++ )
            {
                if( pMesh->verts[i].x == (*(Swing::Vector3f*)pSEMesh->VBuffer->PositionTuple(iV)).X
                &&  pMesh->verts[i].y == (*(Swing::Vector3f*)pSEMesh->VBuffer->PositionTuple(iV)).Z
                &&  pMesh->verts[i].z == (*(Swing::Vector3f*)pSEMesh->VBuffer->PositionTuple(iV)).Y )
                {
                    tempVIArray.push_back(i);

                    break;
                }
            }
        }

        // 判断每个骨骼分别影响了多少顶点.
        iVCount = (int)tempVIArray.size();
        assert( iVCount == pSEMesh->VBuffer->GetVertexCount() );
        memset(aiVerticesPerBone, 0, sizeof(int)*iBoneCount);
        for( i = 0; i < iVCount; i++ )
        {
            iV = tempVIArray[i];
            for( j = 0; j < pSkinData->GetNumAssignedBones(iV); j++ )
            {
                iB = pSkinData->GetAssignedBone(iV, j);
                aiVerticesPerBone[iB]++;
            }
        }

        // 如果Max网格被拆分了,则很有可能有些骨骼没有影响当前Swing Engine子网格,
        // 因此我们需要判断影响当前Swing Engine子网格的骨骼数量.
        int iActiveBoneCount = 0;
        for( iB = 0; iB < iBoneCount; iB++ )
        {
            if( aiVerticesPerBone[iB] > 0 )
            {
                iActiveBoneCount++;
            }
        }
        assert( iActiveBoneCount > 0 );
        if( iActiveBoneCount == 0 )
        {
            // 当前子网格没有受到任何骨骼影响,则继续处理下一个子网格
            continue;
        }

        // 为当前Swing Engine子网格的蒙皮控制器或蒙皮Effect创建相关数组.
        Swing::Node** apSEActiveBones = new Swing::Node*[iActiveBoneCount];
        float** aafWeight;
        Swing::Allocate(iActiveBoneCount, iVCount, aafWeight);
        memset(aafWeight[0], 0, iActiveBoneCount*iVCount*sizeof(float));
        Swing::Vector3f** aaOffset;
        Swing::Allocate(iActiveBoneCount, iVCount, aaOffset);
        memset(aaOffset[0], 0, iActiveBoneCount*iVCount*sizeof(Swing::Vector3f));

        // 为当前Swing Engine子网格存储影响它的所有骨骼,这些骨骼都是Swing Engine节点.
        vector<int> tempBIArray(iBoneCount);
        for( iB = 0, k = 0; iB < iBoneCount; iB++ )
        {
            if( aiVerticesPerBone[iB] > 0 )
            {
                apSEActiveBones[k] = apSEBones[iB];
                tempBIArray[iB] = k;
                k++;
            }
        }

        // 循环遍历当前Swing Engine子网格所用到的Max顶点列表,
        // 获取顶点骨骼权重和顶点偏移量.
        for( i = 0; i < iVCount; i++ )
        {
            iV = tempVIArray[i];
            for( j = 0; j < pSkinData->GetNumAssignedBones(iV); j++ )
            {
                iB = pSkinData->GetAssignedBone(iV, j);
                k = tempBIArray[iB];
                aafWeight[i][k] = pSkinData->GetBoneWeight(iV, j);

                Swing::Vector3f tempWorldVertex;
                pSEMesh->World.ApplyForward(*(Swing::Vector3f*)pSEMesh->VBuffer->PositionTuple(i), 
                    tempWorldVertex);
                apSEActiveBones[k]->World.ApplyInverse(tempWorldVertex, aaOffset[i][k]);
            }
        }
        
        if( !m_pSettings->UseGPUSkin )
        {
            // 为当前Swing Engine子网格创建蒙皮控制器.

            Swing::SkinController* pSESkinController = new Swing::SkinController(
                iVCount, iActiveBoneCount, apSEActiveBones, aafWeight, aaOffset);
            pSESkinController->MinTime = 0.0f;
            pSESkinController->MaxTime = TicksToSec(m_iTimeEnd - m_iTimeStart);
            pSEMesh->AttachController(pSESkinController);
        }
        else
        {
            // 为当前Swing Engine子网格创建蒙皮Effect.

            enum SkinEffect
            {
                ST_DEFAULT,
                ST_MATERIAL,
                ST_MATERIALTEXTURE,
                ST_COUNT
            };

            vector<BoneWeight>* aBWArray;
            Swing::Transformation* aOffset;

            // 判断应该生成的蒙皮effect类型.
            SkinEffect eSkinEffect = ST_DEFAULT;
            Swing::Effect* pSaveEffect = 0;
            for( i = 0; i < pSEMesh->GetEffectCount(); i++ )
            {
                Swing::Effect* pTempEffect = pSEMesh->GetEffect(i);
                if( Swing::DynamicCast<Swing::MaterialEffect>(pTempEffect) )
                {
                    eSkinEffect = ST_MATERIAL;
                    pSaveEffect = pTempEffect;

                    break;
                }
                else if( Swing::DynamicCast<Swing::MaterialTextureEffect>(pTempEffect) )
                {
                    eSkinEffect = ST_MATERIALTEXTURE;
                    pSaveEffect = pTempEffect;

                    break;
                }
                else if( Swing::DynamicCast<Swing::DefaultShaderEffect>(pTempEffect ))
                {
                    eSkinEffect = ST_DEFAULT;
                    pSaveEffect = pTempEffect;

                    break;
                }
            }

            // 创建当前Swing Engine子网格针对其每个骨骼的相对变换.
            aOffset = new Swing::Transformation[iActiveBoneCount];
            for( i = 0; i < iActiveBoneCount; i++ )
            {
                Swing::Transformation tempInvT;
                apSEActiveBones[i]->World.GetInverse(tempInvT);
                aOffset[i].Product(pSEMesh->World, tempInvT);
            }

            // 创建当前Swing Engine子网格所需的新VB.
            Swing::Attributes tempAttr;
            switch( eSkinEffect )
            {
            case ST_DEFAULT:
		        tempAttr.SetPositionChannels(3);
                tempAttr.SetTCoordChannels(0, 4); // BlendWeight
                tempAttr.SetTCoordChannels(1, 4); // BlendIndices

                break;
            case ST_MATERIAL:
		        tempAttr.SetPositionChannels(3);
                tempAttr.SetNormalChannels(3);
                tempAttr.SetTCoordChannels(0, 4); // BlendWeight
                tempAttr.SetTCoordChannels(1, 4); // BlendIndices

                break;
            case ST_MATERIALTEXTURE:
		        tempAttr.SetPositionChannels(3);
                tempAttr.SetNormalChannels(3);
                tempAttr.SetTCoordChannels(0, 2); // BaseTexture
                tempAttr.SetTCoordChannels(1, 4); // BlendWeight
                tempAttr.SetTCoordChannels(2, 4); // BlendIndices

                break;
            default :
                assert( false );
                break;
            }
            Swing::VertexBuffer* pVBNew = new Swing::VertexBuffer(tempAttr, 
                pSEMesh->VBuffer->GetVertexCount());
            int iChannels;
            float* afData = pVBNew->GetData();
            pSEMesh->VBuffer->BuildCompatibleArray(tempAttr, false, iChannels, afData);
            assert( iChannels == pVBNew->GetChannelCount() );
            pSEMesh->VBuffer = pVBNew;

            // 创建子网格顶点权重表,从而为每个顶点选出对其影响效果最大的4个骨骼.
            aBWArray = new vector<BoneWeight>[iVCount];
            for( i = 0; i < iVCount; i++ )
            {
                for( j = 0; j < iActiveBoneCount; j++ )
                {
                    BoneWeight tempBW;
                    tempBW.BoneID = j;
                    tempBW.Weight = aafWeight[i][j];

                    aBWArray[i].push_back(tempBW);
                }
                sort(aBWArray[i].begin(), aBWArray[i].end());

                float* pWeight = 0;
                float* pIndices = 0;
                switch( eSkinEffect )
                {
                case ST_DEFAULT:
                    pWeight = pSEMesh->VBuffer->TCoordTuple(0, i);
                    pIndices = pSEMesh->VBuffer->TCoordTuple(1, i);

                    break;
                case ST_MATERIAL:
                    pWeight = pSEMesh->VBuffer->TCoordTuple(0, i);
                    pIndices = pSEMesh->VBuffer->TCoordTuple(1, i);

                    break;
                case ST_MATERIALTEXTURE:
                    pWeight = pSEMesh->VBuffer->TCoordTuple(1, i);
                    pIndices = pSEMesh->VBuffer->TCoordTuple(2, i);

                    break;
                default :
                    assert( false );

                    break;
                }
                for( j = 0, k = iActiveBoneCount-1; k >= 0 && j < 4 ; k--, j++ )
                {
                    *pWeight++ = aBWArray[i][k].Weight;
                    *pIndices++ = (float)aBWArray[i][k].BoneID;
                }

                int iStopHere = 0;
            }

            Swing::Effect* pNewEffect = 0;
            Swing::String tempImageName;
            switch( eSkinEffect )
            {
            case ST_DEFAULT:
                pNewEffect = 
                    new Swing::SkinDefaultEffect(iActiveBoneCount, apSEActiveBones, aOffset);

                break;
            case ST_MATERIAL:
                pNewEffect = 
                    new Swing::SkinMaterialEffect(iActiveBoneCount, apSEActiveBones, aOffset);

                break;
            case ST_MATERIALTEXTURE:
                tempImageName = 
                    Swing::StaticCast<Swing::ShaderEffect>(pSaveEffect)->GetPImageName(0, 0);
                pNewEffect = 
                    new Swing::SkinMaterialTextureEffect(tempImageName, iActiveBoneCount, apSEActiveBones, aOffset);

                break;
            default :
                assert( false );

                break;
            }

            if( pSaveEffect )
            {
                pSEMesh->DetachEffect(pSaveEffect);
            }

            pSEMesh->AttachEffect(pNewEffect);

            delete[] aBWArray;
            Swing::Deallocate(aafWeight);
            Swing::Deallocate(aaOffset);
        }
    }
    
    if( bNeedDel )
    {
        delete pTriObj;
    }

    delete[] apSEBones;
    delete[] aiVerticesPerBone;
}
//----------------------------------------------------------------------------