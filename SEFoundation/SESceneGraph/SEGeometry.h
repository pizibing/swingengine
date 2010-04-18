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

#ifndef Swing_Geometry_H
#define Swing_Geometry_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SESpatial.h"
#include "SEVertexBuffer.h"
#include "SEIndexBuffer.h"
#include "SELightingEffect.h"
#include "SERenderStateBlock.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:场景视图几何体节点虚基类
// 说明:SEGeometry类及其派生类型只能作为场景视图树的叶子节点.SEGeometry类也是
//     可渲染节点的虚基类.
// 作者:Sun Che
// 时间:20080723
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEGeometry : public SESpatial
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    // 虚基类.
    virtual ~SEGeometry(void);

    // SEGeometry对象所使用的lighting类型.
    // GLM_PIPELINE_VERTEX和GLM_PIPELINE_PIXEL必须与LightingEffect中的
    // LM_VERTEX和LM_PIXEL枚举顺序保持一致.
    // GLM_USER表示用户使用自定义lighting,从而当用户调用UpdateRS函数时,
    // SEGeometry对象将不会创建系统默认的LightingEffect对象.
    // GLM_DISABLE表示该SEGeometry对象禁止任何光照效果.
    enum GeometryLightingMode
    {
        GLM_PIPELINE_VERTEX,
        GLM_PIPELINE_PIXEL,
        GLM_USER,
        GLM_DISABLE,
        GLM_MAX_COUNT
    };

    // 成员访问.
    SEVertexBufferPtr VBuffer;
    SEIndexBufferPtr IBuffer;
    SEBoundingVolumePtr ModelBound;
    GeometryLightingMode LightingMode; // default: GLM_PIPELINE_PIXEL

    // 几何体数据更新入口.
    virtual void UpdateMS(bool bUpdateNormals = true);

    // Picking support.
    // 这个类仅仅用于维护类派生链的完整性.
    class SE_FOUNDATION_API SEPickRecord : public SESpatial::SEPickRecord
    {
    protected:
        SEPickRecord(SEGeometry* pIObject, float fT);
    };

protected:
    SEGeometry(void);
    SEGeometry(SEVertexBuffer* pVBuffer, SEIndexBuffer* pIBuffer);

    // 几何体数据更新.
    virtual void UpdateModelBound(void);
    virtual void UpdateModelNormals(void);
    virtual void UpdateWorldBound(void);

    // 渲染状态更新,实现基类接口.
    virtual void UpdateState(std::vector<SEGlobalState*>* aGStack,
        std::vector<SELight*>* pLStack);

    // 支持剔除系统,收集可渲染对象.
    virtual void GetUnculledSet(SECuller& rCuller, bool bNoCull);

    // 管线动态光照.
    // 管线光照效果被放入SESpatial的effect数组并作为首元素,
    // 因此管线光照渲染发生在其他effect之前.
    // LightingEffect是由根节点到达当前几何体节点时,
    // 所收集到的所有SELight对象的最终合并形式.
    LightingEffectPtr m_spLEffect;

// 内部使用
public:
    // 几何体节点的render state block,表示影响该节点的所有state,
    // 在UpdateRS时收集根节点到达当前几何体节点的所有堆栈顶部渲染状态.
    // 注意:
    // 允许当前节点所携带的effect提供其他任意渲染当前节点所需的渲染状态,
    // light以及其他信息.

    // 几何体节点的lights,表示影响该节点的所有light对象,
    // 在UpdateRS时收集根节点到达当前几何体节点的light堆栈中的元素.

    enum GeometryType
    {
        GT_POLYPOINT,
        GT_POLYLINE_SEGMENTS,
        GT_POLYLINE_OPEN,
        GT_POLYLINE_CLOSED,
        GT_TRIMESH,
        GT_MAX_COUNT
    };

    // 当前几何图元类型.
    GeometryType Type;

    // 通过UpdateRS函数收集到的影响当前几何体节点的render states.
    SERenderStateBlockPtr RStateBlock;

    // 通过UpdateRS函数收集到的影响当前几何体节点的lights.
    std::vector<SELightPtr> Lights;
};

typedef SESmartPointer<SEGeometry> SEGeometryPtr;

#include "SEGeometry.inl"

}

#endif
