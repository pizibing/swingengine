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
#include "decomp.h"

const float Max8SceneBuilder::ATTENUATION = 1e+03f;
const float Max8SceneBuilder::MIN_DIFFERENCE = 1e-03f;

//----------------------------------------------------------------------------
Max8SceneBuilder::Max8SceneBuilder(const TCHAR* acFilename, BOOL bExportSelected, 
    Max8ExportSettings* pSettings, ExpInterface* pExport, Interface* pMax, 
    INode* pRootNode)
{
    // acFilename:
    //     保存场景视图文件时候的文件名.
    // bExportSelected:
    //     为true时表明用户选择了一个场景视图子节点用于导出,
    //     为false时表明导出整个场景视图.
    // pSettings:
    //     用户选择的导出器配置选项用于指定所需导出的数据.
    // pExport:
    //     Max导出器的接口指针.
    // pMax:
    //     Max的接口指针.
    // pRootNode:
    //     导出场景视图的根节点(或用户选择的场景子树根节点).

    m_acFilename = new TCHAR[_tcslen(acFilename) + 1];
    _tcscpy(m_acFilename, acFilename);
    m_bExportSelected = bExportSelected;
    m_pSettings = pSettings;
    m_pExport = pExport;
    m_pMax = pMax;
    m_pRootNode = pRootNode;  
    m_iTicksPerFrame = GetTicksPerFrame();

    if( m_pSettings->IncludeCurrentFrame )
    {
        // 用户选择只导出当前桢.
        // 获取当前桢发生时间.
        m_iTimeStart = 1600;//m_pMax->GetAnimRange().Start();
        m_iTimeEnd = m_iTimeStart;
    }
    else
    {
        // 获取起始桢与结束桢的tick时间.
        m_iTimeStart = m_pMax->GetAnimRange().Start();
        m_iTimeEnd = m_pMax->GetAnimRange().End();
        if( m_pSettings->UseLocalTime )
        {
            m_iTimeOffset = m_iTimeStart;
        }
        else
        {
            m_iTimeOffset = 0;
        }
    }

    // 遍历Max场景视图层级树三遍.
    // 第一遍,处理所有材质及其纹理.
    // 第二遍,建立node层级体系.
    // 第三遍,处理所有modifier.

    // 创建Swing Engine的场景视图世界根节点.
    // 总是使用一个depth buffer state.
    // 如果应用程序不想使用,则应用程序手动移除该depth buffer state.
    m_spSEScene = new Swing::Node;
	m_spSEScene->AttachGlobalState(new Swing::ZBufferState);

    // 遍历Max场景,处理所有材质.
    ConvertMaterials(m_pRootNode);

    if( !m_bExportSelected )
    {
        // 导出整个场景.

        // 处理全局环境光.
        if( m_pSettings->IncludeLights )
        {
            BuildAmbientLight();
        }

        // 建立整个Swing Engine场景.
        for( int i = 0; i < m_pRootNode->NumberOfChildren(); i++ )
        {
            Traverse(m_pRootNode->GetChildNode(i), m_spSEScene);
        }
    }
    else
    {
        // 建立选中部分Swing Engine子场景.
        Traverse(m_pRootNode, m_spSEScene);
    }

    if( m_pSettings->IncludeModifiers )
    {
        m_spSEScene->UpdateGS((double)(TicksToSec(0.0f)));
        ApplyModifiers();
    }

    // 保存Swing Engine场景到磁盘文件.
    Swing::Stream tempStream;

    if( m_bExportSelected )
    {
        tempStream.Insert(m_spSEScene->GetChild(0));
    }
    else
    {
        tempStream.Insert(m_spSEScene);
    }

    tempStream.Save(m_acFilename); 
}
//----------------------------------------------------------------------------
Max8SceneBuilder::~Max8SceneBuilder()
{
    delete[] m_acFilename;
    m_spSEScene = NULL;
    vector<ModifierInfo*>::iterator pIter;
    for( pIter = m_ModList.begin(); pIter < m_ModList.end(); pIter++ )
    {
        delete *pIter;
    }
}
//----------------------------------------------------------------------------
bool Max8SceneBuilder::Traverse(INode* pMaxNode, Swing::Spatial* pSENode)
{
    // 递归遍历Max场景树,根据相关对象建立Swing Engine场景视图.
    // pMaxNode:
    //    Max场景树中的当前节点.
    // pSENode:
    //     即将被加入Swing Engine场景视图的节点的父节点.
    // 返回true时表明递归将继续下去,否则终止递归.

    Swing::Spatial* pSEChild = NULL;

    // 获取起始时间时的Max节点的世界状态.
    ObjectState tempObjectState = pMaxNode->EvalWorldState(m_iTimeStart);
    bool bSupported = true;

    // 判断我们要处理的是什么类型的对象,并进行相应处理.
    // 如果一个节点具有与之相关的对象(比如一个mesh对象),
    // 并且用户选择不导出该种类型的对象,
    // 则我们通过建立一个具备与该对象同样变换的虚对象来体现其空间层级关系.
    // 因此我们可以根据需要,只导出动画相关信息而不导出几何体信息.
    if( tempObjectState.obj )
    {
        switch( tempObjectState.obj->SuperClassID() )
        {
        case GEOMOBJECT_CLASS_ID:
            pSEChild = BuildGeometry(pMaxNode, pSENode);

            break;
        case CAMERA_CLASS_ID:
            // 待实现.

            break;
        case LIGHT_CLASS_ID:
            if( m_pSettings->IncludeLights && !pMaxNode->IsHidden() )
            {
                BuildLight(pMaxNode, pSENode);
            }

            break;
        case HELPER_CLASS_ID:
            // "helper"节点没有与之相关的几何体数据(比如dummy或bone节点).
            // 因此创建一个具备相同变换的虚节点并加入Swing Engine场景视图.
            pSEChild = BuildSpatial(pMaxNode, pSENode);

            break;
        default:
            assert( false );
            bSupported = false;

            return false;
        }
    }

    // 为节点添加动画信息.
    if( pSEChild )
    {   
        if( m_pSettings->IncludeKeyFrames )
        {
            BuildKeyFrameController(pMaxNode, pSEChild);
        }
        else if( m_pSettings->IncludeAllFrames )
        {
            BuildFrameController(pMaxNode, pSEChild);
        }
    }

    // 收集Max场景中的修改器信息.
    // 在场景遍历完成后,所有应用于场景节点的修改器将被加入Swing Engine场景.
    if( m_pSettings->IncludeModifiers )
    {
        ModifierInfo* pModInfo = new ModifierInfo;
        FindModifiers(pMaxNode, pModInfo->Modifiers);
        if( pModInfo->Modifiers.empty() )
        {
            delete pModInfo;
        }
        else
        {
            pModInfo->Node = pMaxNode;
            m_ModList.push_back(pModInfo);
        }
    }

    int iNumChildren = pMaxNode->NumberOfChildren();
    if( iNumChildren == 0 )
    {
        return true;
    }

    for( int i = 0; i < iNumChildren; i++ )
    {
        if( !Traverse(pMaxNode->GetChildNode(i), pSEChild) 
        ||   m_pMax->GetCancel() )
        {
            return false;
        }
    }

    return true;
}
//----------------------------------------------------------------------------
Swing::Spatial* Max8SceneBuilder::BuildGeometry(INode* pMaxNode,
    Swing::Spatial* pSENode)
{
    // 建立并连接一个几何体对象到场景视图.
    // pMaxNode:
    //     Max场景树中的带有几何体数据的节点指针.
    // pSENode:
    //     当前待建立节点的父节点指针.

    Swing::Spatial* pSEChild = NULL;
    Swing::Spatial* pSELink = NULL;

    // 在Max场景中,几何体节点允许具有几何体子节点,
    // 而在Swing Engine场景中,所有几何体节点必须是叶子节点.
    // 如果当前Max节点有几何体子节点,则为当前Max节点创建一个与其对应的"link"虚节点,
    // 从而允许当前Max节点的几何体子节点可以作为叶子节点继续加入到Swing Engine场景.
    for( int i = 0; i < pMaxNode->NumberOfChildren(); i++ )
    {
        ObjectState tempObjectState = pMaxNode->EvalWorldState(m_iTimeStart); 
        if( tempObjectState.obj->SuperClassID() == GEOMOBJECT_CLASS_ID )
        {
            pSELink = BuildSpatial(pMaxNode, pSENode);

            break;
        }
    }

    if( pSELink == NULL )
    {
        pSELink = pSENode;
    }

    if( m_pSettings->IncludeMeshes && !pMaxNode->IsHidden() )
    {
        pSEChild = BuildMesh(pMaxNode, pSELink);
    }
    else
    {
        pSEChild = BuildSpatial(pMaxNode, pSELink);
    }

    if( pSELink != pSENode )
    {
        return pSELink;
    }

    return pSEChild;
}
//----------------------------------------------------------------------------
Swing::Spatial* Max8SceneBuilder::BuildSpatial(INode* pMaxNode,
    Swing::Spatial* pSENode)
{
    Swing::Node* pSEChild = new Swing::Node;
    pSEChild->SetName(pMaxNode->GetName());

    pSEChild->Local = GetLocalTransform(pMaxNode, m_iTimeStart);

    assert( pSENode->IsDerived(Swing::Node::TYPE) );
    ((Swing::Node*)pSENode)->AttachChild(pSEChild);

    return pSEChild;
}
//----------------------------------------------------------------------------
Swing::Transformation Max8SceneBuilder::GetLocalTransform(INode* pNode,
    TimeValue iTime)
{
    // 计算节点的local变换.
    // Max的节点变换访问函数都提供针对节点的世界空间变换,
    // 因此我们必须做一些计算从而获得节点的local变换.
    // 同样,Max也提供节点的pivot变换,通过函数GetNodeTM,
    // 或对象变换,通过函数GetObjectTM,GetObjTMBeforeWSM,GetObjTMAfterWSM.
    // "object offset"指的是节点所带对象的变换,是相对于节点的pivot来说的,
    // 因此节点的pivot变换本身不足以定位其对象在local坐标系下的姿态.
    // 注意对象变换的访问函数返回的是节点的pivot变换和对象offset变换的最终结果.

    // 计算节点的对象在local坐标系下的变换.
    Matrix3 tempMaxLocal = pNode->GetObjTMAfterWSM(iTime) * 
        Inverse(pNode->GetParentNode()->GetObjTMAfterWSM(iTime));

    // 分解local变换,解析出仿射变换分量.
    AffineParts tempAffParts;
    decomp_affine(tempMaxLocal, &tempAffParts);

    // 判断平移分量是否是零向量.
    bool bTranslationIsZero =
        fabsf(tempAffParts.t.x) < MIN_DIFFERENCE &&
        fabsf(tempAffParts.t.y) < MIN_DIFFERENCE &&
        fabsf(tempAffParts.t.z) < MIN_DIFFERENCE;

    // 判断旋转分量是否为单位矩阵.
    float fQSign = ( tempAffParts.q.w >= 0.0f ? 1.0f : -1.0f );
    bool bRotationIsIdentity =
        fabsf(fQSign*tempAffParts.q.w - 1.0f) < MIN_DIFFERENCE &&
        fabsf(tempAffParts.q.x) < MIN_DIFFERENCE &&
        fabsf(tempAffParts.q.y) < MIN_DIFFERENCE &&
        fabsf(tempAffParts.q.z) < MIN_DIFFERENCE;

    // 判断变换是否包含反射变换.
    bool bHasReflection = ( tempAffParts.f < 0.0f );

    // 判断缩放分量是否为统一缩放.
    bool bScaleIsUniform =
        fabsf(tempAffParts.k.x - tempAffParts.k.y) < MIN_DIFFERENCE &&
        fabsf(tempAffParts.k.y - tempAffParts.k.z) < MIN_DIFFERENCE;

    // 如果缩放分量是统一缩放,判断缩放系数是否为1.
    bool bScaleIsUnity = bScaleIsUniform &&
        fabsf(tempAffParts.k.x - 1.0f) < MIN_DIFFERENCE;

    // 判断scale-orientation是否为单位矩阵.
    float fUSign = ( tempAffParts.u.w >= 0.0f ? 1.0f : -1.0f );
    bool bOrientIsIdentity = bScaleIsUniform || (
        fabsf(fUSign*tempAffParts.u.w - 1.0f) < MIN_DIFFERENCE &&
        fabsf(tempAffParts.u.x) < MIN_DIFFERENCE &&
        fabsf(tempAffParts.u.y) < MIN_DIFFERENCE &&
        fabsf(tempAffParts.u.z) < MIN_DIFFERENCE);

    // 计算出与以上结果对应的Swing Engine变换.
    // 由于进行了以上严谨的测试,
    // 从而可以正确的设置Swing Engine的Transformation类的相关标志.
    Swing::Transformation tempSELocal;

    if( !bTranslationIsZero )
    {
        tempSELocal.SetTranslate(Swing::Vector3f(tempAffParts.t.x, tempAffParts.t.z,
            tempAffParts.t.y));
    }

    if( bHasReflection )
    {
        tempAffParts.k *= -1.0f;
    }

    if( bScaleIsUniform )
    {
        // (s*I)*R的矩阵形式,s是统一缩放系数.
        if( !bRotationIsIdentity )
        {
            Swing::Matrix3f tempSERot;
            Swing::Quaternionf(tempAffParts.q.w, +tempAffParts.q.x, +tempAffParts.q.z,
                +tempAffParts.q.y).ToRotationMatrix(tempSERot);
            tempSELocal.SetRotate(tempSERot);
        }
        if( !bScaleIsUnity )
        {
            tempSELocal.SetUniformScale(tempAffParts.k.x);
        }
    }
    else if( bOrientIsIdentity )
    {
        // S*R的矩阵形式, S是具备非统一缩放系数的对角矩阵.
        if( !bRotationIsIdentity )
        {
            Swing::Matrix3f tempSERot;
            Swing::Quaternionf(tempAffParts.q.w, +tempAffParts.q.x, +tempAffParts.q.z,
                +tempAffParts.q.y).ToRotationMatrix(tempSERot);
            tempSELocal.SetRotate(tempSERot);
        }

        tempSELocal.SetScale(Swing::Vector3f(tempAffParts.k.x, tempAffParts.k.z,
            tempAffParts.k.y));
    }
    else
    {
        // 待检查.
        // U*S*U^t*R的矩阵形式,其中U是定位矩阵,S是具备非统一缩放系数的对角矩阵.
        Swing::Matrix3f tempSEMatrix(
            tempMaxLocal.GetAddr()[0][0],
            tempMaxLocal.GetAddr()[0][2],
            tempMaxLocal.GetAddr()[0][1],
            tempMaxLocal.GetAddr()[2][0],
            tempMaxLocal.GetAddr()[2][2],
            tempMaxLocal.GetAddr()[2][1],
            tempMaxLocal.GetAddr()[1][0],
            tempMaxLocal.GetAddr()[1][2],
            tempMaxLocal.GetAddr()[1][1]);

        tempSELocal.SetMatrix(tempSEMatrix);
    }

    return tempSELocal;
}
//----------------------------------------------------------------------------



