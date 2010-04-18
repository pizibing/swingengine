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

#include "SEFoundationPCH.h"
#include "SECollisionRecord.h"
#include "SEIntrTriangle3Triangle3.h"

using namespace Swing;

//----------------------------------------------------------------------------
SECollisionRecord::SECollisionRecord(SETriMesh* pMesh, SEBoundingVolumeTree* 
    pTree, SEVector3f* pVelocity, Callback oCallback, void* pvCallbackData)
{
    SE_ASSERT( pMesh && pTree );

    m_pMesh = pMesh;
    m_pTree = pTree;
    m_pVelocity = pVelocity;
    m_oCallback = oCallback;
    m_pvCallbackData = pvCallbackData;
}
//----------------------------------------------------------------------------
SECollisionRecord::~SECollisionRecord()
{
    SE_DELETE m_pTree;
}
//----------------------------------------------------------------------------
void SECollisionRecord::TestIntersection(SECollisionRecord& rRecord)
{
    SEBoundingVolumeTree* pTree0 = m_pTree;
    SEBoundingVolumeTree* pTree1 = rRecord.m_pTree;
    const SETriMesh* pMesh0 = m_pTree->GetMesh();
    const SETriMesh* pMesh1 = rRecord.m_pTree->GetMesh();

    pTree0->UpdateWorldBound();
    pTree1->UpdateWorldBound();

    const SEBoundingVolume* pWorldBV0 = pTree0->GetWorldBound();
    const SEBoundingVolume* pWorldBV1 = pTree1->GetWorldBound();
    if( pWorldBV0->TestIntersection(pWorldBV1) )
    {
        SEBoundingVolumeTree* pRoot;

        if( pTree0->IsInteriorNode() )
        {
            pRoot = m_pTree;

            // Tree0.L和Tree1比较.
            m_pTree = pRoot->GetLChild();
            TestIntersection(rRecord);

            // Tree0.R和Tree1比较.
            m_pTree = pRoot->GetRChild();
            TestIntersection(rRecord);

            m_pTree = pRoot;
        }
        else if( pTree1->IsInteriorNode() )
        {
            pRoot = rRecord.m_pTree;

            // Tree0和Tree1.L比较.
            rRecord.m_pTree = pRoot->GetLChild();
            TestIntersection(rRecord);

            // Tree0和Tree1.R比较.
            rRecord.m_pTree = pRoot->GetRChild();
            TestIntersection(rRecord);

            rRecord.m_pTree = pRoot;
        }
        else
        {
            // 两个BV树各自提供一个叶子节点比较.
            int iMax0 = pTree0->GetTriangleCount();
            for( int i0 = 0; i0 < iMax0; i0++ )
            {
                int iT0 = pTree0->GetTriangle(i0);

                // 获取世界空间三角形.
                SETriangle3f tempTri0;
                pMesh0->GetWorldTriangle(iT0, tempTri0);

                int iMax1 = pTree1->GetTriangleCount();
                for( int i1 = 0; i1 < iMax1; i1++ )
                {
                    int iT1 = pTree1->GetTriangle(i1);

                    // 获取世界空间三角形.
                    SETriangle3f tempTri1;
                    pMesh1->GetWorldTriangle(iT1, tempTri1);

                    SEIntrTriangle3Triangle3f tempIntersector(tempTri0, 
                        tempTri1);
                    if( tempIntersector.Test() )
                    {
                        if( m_oCallback )
                        {
                            m_oCallback(*this, iT0, rRecord, iT1, 
                                &tempIntersector);
                        }

                        if( rRecord.m_oCallback )
                        {
                            rRecord.m_oCallback(rRecord, iT1, *this, iT0,
                                &tempIntersector);
                        }
                    }
                }
            }
        }
    }
}
//----------------------------------------------------------------------------
void SECollisionRecord::FindIntersection(SECollisionRecord& rRecord)
{
    SEBoundingVolumeTree* pTree0 = m_pTree;
    SEBoundingVolumeTree* pTree1 = rRecord.m_pTree;
    const SETriMesh* pMesh0 = m_pTree->GetMesh();
    const SETriMesh* pMesh1 = rRecord.m_pTree->GetMesh();

    pTree0->UpdateWorldBound();
    pTree1->UpdateWorldBound();

    const SEBoundingVolume* pWorldBV0 = pTree0->GetWorldBound();
    const SEBoundingVolume* pWorldBV1 = pTree1->GetWorldBound();
    if( pWorldBV0->TestIntersection(pWorldBV1) )
    {
        SEBoundingVolumeTree* pRoot;

        if( pTree0->IsInteriorNode() )
        {
            pRoot = m_pTree;

            // Tree0.L和Tree1比较.
            m_pTree = pRoot->GetLChild();
            FindIntersection(rRecord);

            // Tree0.R和Tree1比较.
            m_pTree = pRoot->GetRChild();
            FindIntersection(rRecord);

            m_pTree = pRoot;
        }
        else if( pTree1->IsInteriorNode() )
        {
            pRoot = rRecord.m_pTree;

            // Tree0和Tree1.L比较.
            rRecord.m_pTree = pRoot->GetLChild();
            FindIntersection(rRecord);

            // Tree0和Tree1.R比较.
            rRecord.m_pTree = pRoot->GetRChild();
            FindIntersection(rRecord);

            rRecord.m_pTree = pRoot;
        }
        else
        {
            // 两个BV树各自提供一个叶子节点比较.
            int iMax0 = pTree0->GetTriangleCount();
            for( int i0 = 0; i0 < iMax0; i0++ )
            {
                int iT0 = pTree0->GetTriangle(i0);

                // 获取世界空间三角形.
                SETriangle3f tempTri0;
                pMesh0->GetWorldTriangle(iT0, tempTri0);

                int iMax1 = pTree1->GetTriangleCount();
                for( int i1 = 0; i1 < iMax1; i1++ )
                {
                    int iT1 = pTree1->GetTriangle(i1);

                    // 获取世界空间三角形.
                    SETriangle3f tempTri1;
                    pMesh1->GetWorldTriangle(iT1, tempTri1);

                    SEIntrTriangle3Triangle3f tempIntersector(tempTri0, 
                        tempTri1);
                    if( tempIntersector.Find() )
                    {
                        if( m_oCallback )
                        {
                            m_oCallback(*this, iT0, rRecord, iT1, 
                                &tempIntersector);
                        }

                        if( rRecord.m_oCallback )
                        {
                            rRecord.m_oCallback(rRecord, iT1, *this, iT0,
                                &tempIntersector);
                        }
                    }
                }
            }
        }
    }
}
//----------------------------------------------------------------------------
void SECollisionRecord::TestIntersection(float fTMax, SECollisionRecord& 
    rRecord)
{
    SEBoundingVolumeTree* pTree0 = m_pTree;
    SEBoundingVolumeTree* pTree1 = rRecord.m_pTree;
    const SETriMesh* pMesh0 = m_pTree->GetMesh();
    const SETriMesh* pMesh1 = rRecord.m_pTree->GetMesh();
    const SEVector3f& rVelocity0 = (m_pVelocity ? *m_pVelocity :
        SEVector3f::ZERO);
    const SEVector3f& rVelocity1 = (rRecord.m_pVelocity ?
        *rRecord.m_pVelocity : SEVector3f::ZERO);

    pTree0->UpdateWorldBound();
    pTree1->UpdateWorldBound();

    const SEBoundingVolume* pWorldBV0 = pTree0->GetWorldBound();
    const SEBoundingVolume* pWorldBV1 = pTree1->GetWorldBound();

    // 待实现.
    // TestIntersection应该支持运动的BV.
    if( pWorldBV0->TestIntersection(pWorldBV1) )
    {
        SEBoundingVolumeTree* pRoot;

        if( pTree0->IsInteriorNode() )
        {
            pRoot = m_pTree;

            // Tree0.L和Tree1比较.
            m_pTree = pRoot->GetLChild();
            TestIntersection(fTMax, rRecord);

            // Tree0.R和Tree1比较.
            m_pTree = pRoot->GetRChild();
            TestIntersection(fTMax, rRecord);

            m_pTree = pRoot;
        }
        else if( pTree1->IsInteriorNode() )
        {
            pRoot = rRecord.m_pTree;

            // Tree0和Tree1.L比较.
            rRecord.m_pTree = pRoot->GetLChild();
            TestIntersection(fTMax, rRecord);

            // Tree0和Tree1.R比较.
            rRecord.m_pTree = pRoot->GetRChild();
            TestIntersection(fTMax, rRecord);

            rRecord.m_pTree = pRoot;
        }
        else
        {
            // 两个BV树各自提供一个叶子节点比较.
            int iMax0 = pTree0->GetTriangleCount();
            for( int i0 = 0; i0 < iMax0; i0++ )
            {
                int iT0 = pTree0->GetTriangle(i0);

                // 获取世界空间三角形.
                SETriangle3f tempTri0;
                pMesh0->GetWorldTriangle(iT0, tempTri0);

                int iMax1 = pTree1->GetTriangleCount();
                for( int i1 = 0; i1 < iMax1; i1++ )
                {
                    int iT1 = pTree1->GetTriangle(i1);

                    // 获取世界空间三角形.
                    SETriangle3f tempTri1;
                    pMesh1->GetWorldTriangle(iT1, tempTri1);

                    SEIntrTriangle3Triangle3f tempIntersector(tempTri0, 
                        tempTri1);
                    if( tempIntersector.Test(fTMax, rVelocity0, rVelocity1) )
                    {
                        if( m_oCallback )
                        {
                            m_oCallback(*this, iT0, rRecord, iT1, 
                                &tempIntersector);
                        }

                        if( rRecord.m_oCallback )
                        {
                            rRecord.m_oCallback(rRecord, iT1, *this, iT0,
                                &tempIntersector);
                        }
                    }
                }
            }
        }
    }
}
//----------------------------------------------------------------------------
void SECollisionRecord::FindIntersection(float fTMax, SECollisionRecord& 
    rRecord)
{
    SEBoundingVolumeTree* pTree0 = m_pTree;
    SEBoundingVolumeTree* pTree1 = rRecord.m_pTree;
    const SETriMesh* pMesh0 = m_pTree->GetMesh();
    const SETriMesh* pMesh1 = rRecord.m_pTree->GetMesh();
    const SEVector3f& rVelocity0 = (m_pVelocity ? *m_pVelocity :
        SEVector3f::ZERO);
    const SEVector3f& rVelocity1 = (rRecord.m_pVelocity ?
        *rRecord.m_pVelocity : SEVector3f::ZERO);

    pTree0->UpdateWorldBound();
    pTree1->UpdateWorldBound();

    const SEBoundingVolume* pWorldBV0 = pTree0->GetWorldBound();
    const SEBoundingVolume* pWorldBV1 = pTree1->GetWorldBound();

    // 待实现.
    // TestIntersection应该支持运动的BV.
    if( pWorldBV0->TestIntersection(pWorldBV1) )
    {
        SEBoundingVolumeTree* pRoot;

        if( pTree0->IsInteriorNode() )
        {
            pRoot = m_pTree;

            // Tree0.L和Tree1比较.
            m_pTree = pRoot->GetLChild();
            FindIntersection(fTMax, rRecord);

            // Tree0.R和Tree1比较.
            m_pTree = pRoot->GetRChild();
            FindIntersection(fTMax, rRecord);

            m_pTree = pRoot;
        }
        else if( pTree1->IsInteriorNode() )
        {
            pRoot = rRecord.m_pTree;

            // Tree0和Tree1.L比较.
            rRecord.m_pTree = pRoot->GetLChild();
            FindIntersection(fTMax, rRecord);

            // Tree0和Tree1.R比较.
            rRecord.m_pTree = pRoot->GetRChild();
            FindIntersection(fTMax, rRecord);

            rRecord.m_pTree = pRoot;
        }
        else
        {
            // 两个BV树各自提供一个叶子节点比较.
            int iMax0 = pTree0->GetTriangleCount();
            for( int i0 = 0; i0 < iMax0; i0++ )
            {
                int iT0 = pTree0->GetTriangle(i0);

                // 获取世界空间三角形.
                SETriangle3f tempTri0;
                pMesh0->GetWorldTriangle(iT0, tempTri0);

                int iMax1 = pTree1->GetTriangleCount();
                for( int i1 = 0; i1 < iMax1; i1++ )
                {
                    int iT1 = pTree1->GetTriangle(i1);

                    // 获取世界空间三角形.
                    SETriangle3f tempTri1;
                    pMesh1->GetWorldTriangle(iT1, tempTri1);

                    SEIntrTriangle3Triangle3f tempIntersector(tempTri0, 
                        tempTri1);
                    if( tempIntersector.Find(fTMax, rVelocity0, rVelocity1) )
                    {
                        if( m_oCallback )
                        {
                            m_oCallback(*this, iT0, rRecord, iT1, 
                                &tempIntersector);
                        }

                        if( rRecord.m_oCallback )
                        {
                            rRecord.m_oCallback(rRecord, iT1, *this, iT0,
                                &tempIntersector);
                        }
                    }
                }
            }
        }
    }
}
//----------------------------------------------------------------------------
