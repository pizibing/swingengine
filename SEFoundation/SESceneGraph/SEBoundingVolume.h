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

#ifndef Swing_BoundingVolume_H
#define Swing_BoundingVolume_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEObject.h"
#include "SEPlane3.h"
#include "SERay3.h"
#include "SETransformation.h"
#include "SEVector3Array.h"
#include "SEVertexBuffer.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:包围体虚基类
// 说明:封装包围体碰撞检测等问题.
//      SEBoundingVolume的工厂函数默认实现为创建SESphereBV对象,
//      可以删除当前函数实现,使用另一个SEBoundingVolume派生类型.
// 作者:Sun Che
// 时间:20080312
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEBoundingVolume : public SEObject
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    // 虚基类
    virtual ~SEBoundingVolume(void);

    // RTTI信息
    enum BVType
    {
        BV_SPHERE,
        BV_BOX,
        BV_COUNT
    };
    virtual int GetBVType(void) const = 0;

    // 所有BV都要定义中点和半径.
    virtual void SetCenter(const SEVector3f& rCenter) = 0;
    virtual void SetRadius(float fRadius) = 0;
    virtual SEVector3f GetCenter(void) const = 0;
    virtual float GetRadius(void) const = 0;

    // 派生类中的一个必须实现这个工厂函数,引擎只能支持使用同一种BV,
    // 默认实现在SphererBV中.
    static SEBoundingVolume* Create(void);

    // 根据传入顶点集合创建BV.
    virtual void ComputeFromData(const SEVector3fArray* pVertices) = 0;
    virtual void ComputeFromData(const SEVertexBuffer* pVB) = 0;

    // 变换BV(从模型空间到世界空间).
    virtual void TransformBy(const SETransformation& rTransform, SEBoundingVolume* pResult) = 0;

    // 判断BV是否在平面正半空间(平面法线所指向的空间),相交,负半空间,
    // 相应的返回值为+1,0,-1.
    virtual int OnWhichSide(const SEPlane3f& rPlane) const = 0;

    // 测试BV是否和射线相交,不计算交点,射线方向必须为单位向量.
    virtual bool TestIntersection(const SERay3f& rRay) const = 0;

    // 测试是否和另一个BV相交.
    virtual bool TestIntersection(const SEBoundingVolume* pInput) const = 0;

    // 用另一个BV复制出自己.
    virtual void CopyFrom(const SEBoundingVolume* pInput) = 0;

    // 当前BV增长,包含传入的BV和之前的自己.
    virtual void GrowToContain(const SEBoundingVolume* pInput) = 0;

    // 是否包含传入点.
    virtual bool Contains(const SEVector3f& rPoint) const = 0;

protected:
    SEBoundingVolume(void);
};

typedef SESmartPointer<SEBoundingVolume> SEBoundingVolumePtr;

}

#endif
