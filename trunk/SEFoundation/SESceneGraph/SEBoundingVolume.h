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
// ����:��Χ�������
// ˵��:��װ��Χ����ײ��������.
//      BoundingVolume�Ĺ�������Ĭ��ʵ��Ϊ����SphereBV����,
//      ����ɾ����ǰ����ʵ��,ʹ����һ��BoundingVolume��������.
// ����:Sun Che
// ʱ��:20080312
//----------------------------------------------------------------------------
class SE_FOUNDATION_API BoundingVolume : public Object
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    // �����
    virtual ~BoundingVolume(void);

    // RTTI��Ϣ
    enum BVType
    {
        BV_SPHERE,
        BV_BOX,
        BV_COUNT
    };
    virtual int GetBVType(void) const = 0;

    // ����BV��Ҫ�����е�Ͱ뾶.
    virtual void SetCenter(const Vector3f& rCenter) = 0;
    virtual void SetRadius(float fRadius) = 0;
    virtual Vector3f GetCenter(void) const = 0;
    virtual float GetRadius(void) const = 0;

    // �������е�һ������ʵ�������������,����ֻ��֧��ʹ��ͬһ��BV,
    // Ĭ��ʵ����SphererBV��.
    static BoundingVolume* Create(void);

    // ���ݴ��붥�㼯�ϴ���BV.
    virtual void ComputeFromData(const Vector3fArray* pVertices) = 0;
    virtual void ComputeFromData(const VertexBuffer* pVB) = 0;

    // �任BV(��ģ�Ϳռ䵽����ռ�).
    virtual void TransformBy(const Transformation& rTransform, BoundingVolume* pResult) = 0;

    // �ж�BV�Ƿ���ƽ������ռ�(ƽ�淨����ָ��Ŀռ�),�ཻ,����ռ�,
    // ��Ӧ�ķ���ֵΪ+1,0,-1.
    virtual int OnWhichSide(const Plane3f& rPlane) const = 0;

    // ����BV�Ƿ�������ཻ,�����㽻��,���߷������Ϊ��λ����.
    virtual bool TestIntersection(const Ray3f& rRay) const = 0;

    // �����Ƿ����һ��BV�ཻ.
    virtual bool TestIntersection(const BoundingVolume* pInput) const = 0;

    // ����һ��BV���Ƴ��Լ�.
    virtual void CopyFrom(const BoundingVolume* pInput) = 0;

    // ��ǰBV����,���������BV��֮ǰ���Լ�.
    virtual void GrowToContain(const BoundingVolume* pInput) = 0;

    // �Ƿ���������.
    virtual bool Contains(const Vector3f& rPoint) const = 0;

protected:
    BoundingVolume(void);
};

typedef SmartPointer<BoundingVolume> BoundingVolumePtr;

}

#endif