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

#ifndef Swing_ContSphere3_H
#define Swing_ContSphere3_H

#include "SEFoundationLIB.h"
#include "SESphere3.h"
#include "SEVector3.h"
#include "SEMath.h"

namespace Swing
{

// 根据输入的若干顶点,计算能容纳其最小AABBox的BV球.
SE_FOUNDATION_API SESphere3f ContSphereOfAABBf(int iCount, const SEVector3f* aPoint);

// 根据输入的若干顶点,计算其BV球,球心是顶点的平均值.
SE_FOUNDATION_API SESphere3f ContSphereAveragef(int iCount, const SEVector3f* aPoint);

// 测试指定顶点是否包含于球内.
SE_FOUNDATION_API bool IsInSpheref(const SEVector3f& rPoint, const SESphere3f& rSphere);

// 计算包含两个球的BV球.
SE_FOUNDATION_API SESphere3f MergeSpheresf(const SESphere3f& rSphere0, 
    const SESphere3f& rSphere1);

// 根据输入的若干顶点,计算其最小BV球,
// 算法随机重置输入顶点排列顺序,因此构建时间预期为O(n).
class SE_FOUNDATION_API SEMinSphere3f
{
public:
    SEMinSphere3f(int iCount, const SEVector3f* aPoint, SESphere3f& rMinimal, 
        float fEpsilon = 1.0e-03f);

private:
    // 当前最小球的顶点索引支持.
    class SE_FOUNDATION_API SESupport
    {
    public:
        // 测试输入顶点是否属于support集合,
        // 如果输入顶点距离集合内某点距离小于给定epsilon,则认为属于集合.
        bool Contains(int iIndex, SEVector3f** apPoint, float fEpsilon)
        {
            for( int i = 0; i < Count; i++ )
            {
                SEVector3f vec3fDiff = *apPoint[iIndex] - *apPoint[Index[i]];
                if( vec3fDiff.GetSquaredLength() < fEpsilon )
                {
                    return true;
                }
            }

            return false;
        }

        int Count;
        int Index[4];
    };

    // 测试顶点P是否包含于球S中.
    bool Contains(const SEVector3f& rPoint, const SESphere3f& rSphere, 
        float& rfDistDiff);

    SESphere3f ExactSphere1(const SEVector3f& rPoint);
    SESphere3f ExactSphere2(const SEVector3f& rPoint0, const SEVector3f& rPoint1);
    SESphere3f ExactSphere3(const SEVector3f& rPoint0, const SEVector3f& rPoint1, 
        const SEVector3f& rPoint2);
    SESphere3f ExactSphere4(const SEVector3f& rPoint0, const SEVector3f& rPoint1, 
        const SEVector3f& rPoint2, const SEVector3f& rPoint3);

    SESphere3f UpdateSupport1(int i, SEVector3f** apPermute, SESupport& rSupport);
    SESphere3f UpdateSupport2(int i, SEVector3f** apPermute, SESupport& rSupport);
    SESphere3f UpdateSupport3(int i, SEVector3f** apPermute, SESupport& rSupport);
    SESphere3f UpdateSupport4(int i, SEVector3f** apPermute, SESupport& rSupport);

    typedef SESphere3f (SEMinSphere3f::*UpdateFunction)(int, SEVector3f**, SESupport&);

    float m_fEpsilon, m_fOnePlusEpsilon;
    UpdateFunction m_aoUpdate[5];
};

}

#endif