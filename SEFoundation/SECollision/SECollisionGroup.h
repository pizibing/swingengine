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

#ifndef Swing_CollisionGroup_H
#define Swing_CollisionGroup_H

#include "SEFoundationLIB.h"
#include "SESystem.h"

namespace Swing
{

class SECollisionRecord;

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20081223
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SECollisionGroup
{
public:
    SECollisionGroup(void);
    ~SECollisionGroup(void);

    // SECollisionGroup被假设为有责任删除加入的所有collision record.
    // 因此传入的collision record应该是动态分配的.
    bool Add(SECollisionRecord* pRecord);
    bool Remove(SECollisionRecord* pRecord);

    // Intersection查询.
    // 如果碰撞组中的两个对象发生碰撞,则与其对应的record负责处理相关信息.

    // 待比较对象被假设为静止状态(速度被忽略),所有对象被成对进行比较.
    void TestIntersection(void);
    void FindIntersection(void);
    
    // 待比较对象被假设为运动状态.当有对象携带速度向量时(可以是零向量),
    // 有速度的对象与其他对象被成对进行比较.
    void TestIntersection(float fTMax);
    void FindIntersection(float fTMax);

protected:
    std::vector<SECollisionRecord*> m_Record;
};

}

#endif
