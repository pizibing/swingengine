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

#ifndef Swing_Node_H
#define Swing_Node_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SESpatial.h"
#include "SECuller.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:场景视图关系节点基类
// 说明:一些开发者希望Node节点对象可以有多个父节点,从而使场景视图成为DAG.
//      实际上不是这样,场景视图结构是一个树型结构.
// 作者:Sun Che
// 时间:20080723
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Node : public Spatial
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    Node(void);
    virtual ~Node(void);

    // 子节点访问.
    inline int GetCount(void) const;
    int AttachChild(Spatial* pChild);
    int DetachChild(Spatial* pChild);
    SpatialPtr DetachChildAt(int i);
    SpatialPtr SetChild(int i, Spatial* pChild);
    SpatialPtr GetChild(int i);

    // Picking support.
    // 射线的原点和方向向量都必须在世界坐标系下.
    // 应用程序有责任迭代释放PickArray中的所有pick record.
    virtual void DoPick(const Ray3f& rRay, PickArray& rResults);

protected:
    // 几何数据更新
    virtual void UpdateWorldData(double dAppTime);
    virtual void UpdateWorldBound(void);

    // 渲染状态更新
    virtual void UpdateState(std::vector<GlobalState*>* aGStack,
        std::vector<Light*>* pLStack);

    // 支持剔除系统
    virtual void GetUnculledSet(Culler& rCuller, bool bNoCull);

    // 子节点数组
    std::vector<SpatialPtr> m_Child;
};

typedef SESmartPointer<Node> NodePtr;

#include "SENode.inl"

}

#endif
