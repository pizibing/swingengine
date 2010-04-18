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

#ifndef Swing_CollisionRecord_H
#define Swing_CollisionRecord_H

#include "SEFoundationLIB.h"
#include "SEBoundingVolumeTree.h"
#include "SEIntersector.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:Collision record类
// 说明:
// 作者:Sun Che
// 时间:20081223
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SECollisionRecord
{
public:
    typedef void (*Callback)(SECollisionRecord& rRecord0, int iT0,
        SECollisionRecord& rRecord1, int iT1,
        Intersector<float, SEVector3f>* pIntersector);

    // SECollisionRecord被假设为有责任删除传入的pTree,因此pTree应动态分配.
    SECollisionRecord(SETriMesh* pMesh, SEBoundingVolumeTree* pTree,
        SEVector3f* pVelocity, Callback oCallback, void* pvCallbackData);

    ~SECollisionRecord(void);

    // 成员访问.
    inline SETriMesh* GetMesh(void);
    inline SEVector3f* GetVelocity(void);
    inline void* GetCallbackData(void);

    // intersection查询.
    void TestIntersection(SECollisionRecord& rRecord);
    void FindIntersection(SECollisionRecord& rRecord);
    void TestIntersection(float fTMax, SECollisionRecord& rRecord);
    void FindIntersection(float fTMax, SECollisionRecord& rRecord);

protected:
    SETriMesh* m_pMesh;
    SEBoundingVolumeTree* m_pTree;
    SEVector3f* m_pVelocity;
    Callback m_oCallback;
    void* m_pvCallbackData;
};

#include "SECollisionRecord.inl"

}

#endif
