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
#include "SETriMesh.h"
#include "SEIntrRay3Triangle3.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, TriMesh, Geometry);
SE_IMPLEMENT_STREAM(TriMesh);
SE_IMPLEMENT_DEFAULT_STREAM(TriMesh, Geometry);
SE_IMPLEMENT_DEFAULT_NAME_ID(TriMesh, Geometry);

//SE_REGISTER_STREAM(TriMesh);

std::vector<TriMesh::PickRecord> TriMesh::ms_PickRecordPool;
int TriMesh::ms_iMaxCount = 0;
int TriMesh::ms_iGrowBy = 0;
int TriMesh::ms_iCount = 0;

//----------------------------------------------------------------------------
TriMesh::TriMesh()
{
    Type = GT_TRIMESH;
}
//----------------------------------------------------------------------------
TriMesh::TriMesh(VertexBuffer* pVBuffer, IndexBuffer* pIBuffer)
    :
    Geometry(pVBuffer, pIBuffer)
{
    Type = GT_TRIMESH;
}
//----------------------------------------------------------------------------
TriMesh::~TriMesh()
{
}
//----------------------------------------------------------------------------
void TriMesh::GetModelTriangle(int i, Triangle3f& rMTri) const
{
    SE_ASSERT( 0 <= i && 3*i < IBuffer->GetIndexCount() );

    int* aiIndex = IBuffer->GetData();
    SE_ASSERT( aiIndex );

    int* piIndex = &aiIndex[3*i];
    rMTri.V[0] = VBuffer->Position3(*piIndex++);
    rMTri.V[1] = VBuffer->Position3(*piIndex++);
    rMTri.V[2] = VBuffer->Position3(*piIndex  );
}
//----------------------------------------------------------------------------
void TriMesh::GetWorldTriangle(int i, Triangle3f& rWTri) const
{
    SE_ASSERT( 0 <= i && 3*i < IBuffer->GetIndexCount() );

    int* aiIndex = IBuffer->GetData();
    SE_ASSERT( aiIndex );

    int* piIndex = &aiIndex[3*i];
    World.ApplyForward(VBuffer->Position3(*piIndex++), rWTri.V[0]);
    World.ApplyForward(VBuffer->Position3(*piIndex++), rWTri.V[1]);
    World.ApplyForward(VBuffer->Position3(*piIndex  ), rWTri.V[2]);
}
//----------------------------------------------------------------------------
void TriMesh::GenerateNormals()
{
    if( !VBuffer->GetAttributes().HasNormal() )
    {
        // 如果目前没有法线,则重新创建带有法线数据的VB.
        Attributes VBAttr = VBuffer->GetAttributes();
        VBAttr.SetNormalChannels(3);
        VertexBuffer* pVBufferPlusNormals = SE_NEW VertexBuffer(VBAttr,
            VBuffer->GetVertexCount());
        int iChannels;
        float* afData = pVBufferPlusNormals->GetData();
        VBuffer->BuildCompatibleArray(VBAttr, false, iChannels, afData);

        SE_ASSERT( iChannels == pVBufferPlusNormals->GetChannelCount() );
        VBuffer = pVBufferPlusNormals;
    }

    UpdateModelNormals();
}
//----------------------------------------------------------------------------
bool TriMesh::GenerateTangents(int iSrcTCoordUnit, int iTangentUnit, 
    int iBiTangentUnit)
{
    Attributes AttrOld = VBuffer->GetAttributes();

    // 源数据区不存在.
    if( !AttrOld.HasTCoord(iSrcTCoordUnit) ||
        AttrOld.GetTCoordChannels(iSrcTCoordUnit) != 2 )
    {
        return false;
    }

    // 目标数据区不能为源数据区,且两个目标数据区不能相同.
    if( iSrcTCoordUnit == iTangentUnit || iSrcTCoordUnit == iBiTangentUnit ||
        iTangentUnit == iBiTangentUnit )
    {
        return false;
    }

    Attributes AttrNew = VBuffer->GetAttributes();
    if( !AttrOld.HasNormal() )
    {
        AttrNew.SetNormalChannels(3);
    }

    if( AttrOld.GetTCoordChannels(iTangentUnit) < 3 )
    {
        AttrNew.SetTCoordChannels(iTangentUnit, 3);
    }

    if( iBiTangentUnit > -1 && AttrOld.GetTCoordChannels(iBiTangentUnit) < 3 )
    {
        AttrNew.SetTCoordChannels(iBiTangentUnit, 3);
    }

    // 是否有必要创建新VB.
    if( AttrNew != AttrOld )
    {
        VertexBuffer* pVBufferNew = SE_NEW VertexBuffer(AttrNew,
            VBuffer->GetVertexCount());
        int iChannels;
        float* afData = pVBufferNew->GetData();
        VBuffer->BuildCompatibleArray(AttrNew, false, iChannels, afData);

        SE_ASSERT( iChannels == pVBufferNew->GetChannelCount() );
        VBuffer = pVBufferNew;
    }

    // 如果没有法线,则首先生成法线.
    if( !AttrOld.HasNormal() )
    {
        UpdateModelNormals();
    }

    int iVCount = VBuffer->GetVertexCount();
    int i, iTangentChannels, iBiTangentChannels;
    iTangentChannels = AttrNew.GetTCoordChannels(iTangentUnit);
    iBiTangentChannels = 
        iBiTangentUnit > -1 ? AttrNew.GetTCoordChannels(iBiTangentUnit) : 0;

    if( iTangentChannels == 3 )
    {
        for( i = 0; i < iVCount; i++ )
        {
            VBuffer->TCoord3(iTangentUnit, i) = Vector3f::ZERO;
        }
    }
    else if( iTangentChannels == 4 )
    {
        for( i = 0; i < iVCount; i++ )
        {
            VBuffer->TCoord4(iTangentUnit, i) = Vector4f::ZERO;
        }
    }

    if( iBiTangentChannels == 3 )
    {
        for( i = 0; i < iVCount; i++ )
        {
            VBuffer->TCoord3(iBiTangentUnit, i) = Vector3f::ZERO;
        }
    }
    else if( iBiTangentChannels == 4 )
    {
        for( i = 0; i < iVCount; i++ )
        {
            VBuffer->TCoord4(iBiTangentUnit, i) = Vector4f::ZERO;
        }
    }

    int iTCount = IBuffer->GetIndexCount()/3;
    int* piIndex = IBuffer->GetData();
    for( i = 0; i < iTCount; i++ )
    {
        // 获取顶点索引.
        int iV0 = *piIndex++;
        int iV1 = *piIndex++;
        int iV2 = *piIndex++;

        // 获取顶点.
        Vector3f& rV0 = VBuffer->Position3(iV0);
        Vector3f& rV1 = VBuffer->Position3(iV1);
        Vector3f& rV2 = VBuffer->Position3(iV2);

        // 获取顶点UV(iSrcTCoordUnit指定的源数据区).
        Vector2f& rUV0 = VBuffer->TCoord2(iSrcTCoordUnit, iV0);
        Vector2f& rUV1 = VBuffer->TCoord2(iSrcTCoordUnit, iV1);
        Vector2f& rUV2 = VBuffer->TCoord2(iSrcTCoordUnit, iV2);

        Vector3f vec3fQ1 = rV1 - rV0;
        Vector3f vec3fQ2 = rV2 - rV0;
        float fS1 = rUV1.X - rUV0.X;
        float fT1 = rUV1.Y - rUV0.Y;
        float fS2 = rUV2.X - rUV0.X;
        float fT2 = rUV2.Y - rUV0.Y;
        float fDenom = 1.0f / (fS1*fT2 - fS2*fT1);

        // 计算切线.
        Vector3f vec3fTangent;
        vec3fTangent.X = fDenom*(fT2*vec3fQ1.X - fT1*vec3fQ2.X);
        vec3fTangent.Y = fDenom*(fT2*vec3fQ1.Y - fT1*vec3fQ2.Y);
        vec3fTangent.Z = fDenom*(fT2*vec3fQ1.Z - fT1*vec3fQ2.Z);

        VBuffer->TCoord3(iTangentUnit, iV0) += vec3fTangent;
        VBuffer->TCoord3(iTangentUnit, iV1) += vec3fTangent;
        VBuffer->TCoord3(iTangentUnit, iV2) += vec3fTangent;

        if( iBiTangentUnit > -1 )
        {
            // 计算副切线.
            Vector3f vec3fBiTangent;
            vec3fBiTangent.X = fDenom*(-fS2*vec3fQ1.X + fS1*vec3fQ2.X);
            vec3fBiTangent.Y = fDenom*(-fS2*vec3fQ1.Y + fS1*vec3fQ2.Y);
            vec3fBiTangent.Z = fDenom*(-fS2*vec3fQ1.Z + fS1*vec3fQ2.Z);

            VBuffer->TCoord3(iBiTangentUnit, iV0) += vec3fBiTangent;
            VBuffer->TCoord3(iBiTangentUnit, iV1) += vec3fBiTangent;
            VBuffer->TCoord3(iBiTangentUnit, iV2) += vec3fBiTangent;
        }
    }

    // 对顶点的T,B,N向量进行Gram-Schmidt规范正交化,
    // 生成的T',B',N构成规范正交基.

    for( i = 0; i < iVCount; i++ )
    {
        Vector3f& rTangent = VBuffer->TCoord3(iTangentUnit, i);
        Vector3f& rNormal = VBuffer->Normal3(i);
        VBuffer->TCoord3(iTangentUnit, i) = rTangent - 
            rNormal.Dot(rTangent)*rNormal;

        VBuffer->TCoord3(iTangentUnit, i).Normalize();
    }

    if( iBiTangentUnit > -1 )
    {
        for( i = 0; i < iVCount; i++ )
        {
            Vector3f& rBiTangent = VBuffer->TCoord3(iBiTangentUnit, i);
            Vector3f& rTangent = VBuffer->TCoord3(iTangentUnit, i);
            Vector3f& rNormal = VBuffer->Normal3(i);
            VBuffer->TCoord3(iBiTangentUnit, i) = rBiTangent -
                rNormal.Dot(rBiTangent)*rNormal - rTangent.Dot(rBiTangent)*
                rTangent;

            VBuffer->TCoord3(iBiTangentUnit, i).Normalize();
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void TriMesh::UpdateModelNormals()
{
    // 根据共享顶点的带权三角面(由三角面面积体现权值)法线,
    // 计算最终顶点平均法线.

    if( !VBuffer->GetAttributes().HasNormal() )
    {
        return;
    }

    int iVCount = VBuffer->GetVertexCount();
    int i;
    for( i = 0; i < iVCount; i++ )
    {
        VBuffer->Normal3(i) = Vector3f::ZERO;
    }

    int iTCount = IBuffer->GetIndexCount()/3;
    int* piIndex = IBuffer->GetData();
    for( i = 0; i < iTCount; i++ )
    {
        // 获取顶点索引.
        int iV0 = *piIndex++;
        int iV1 = *piIndex++;
        int iV2 = *piIndex++;

        // 获取顶点.
        Vector3f& rV0 = VBuffer->Position3(iV0);
        Vector3f& rV1 = VBuffer->Position3(iV1);
        Vector3f& rV2 = VBuffer->Position3(iV2);

        // 计算法线(法线长度体现了该三角面权值).
        Vector3f vec3fEdge1 = rV1 - rV0;
        Vector3f vec3fEdge2 = rV2 - rV0;
        Vector3f vec3fNormal = vec3fEdge1.Cross(vec3fEdge2);

        VBuffer->Normal3(iV0) += vec3fNormal;
        VBuffer->Normal3(iV1) += vec3fNormal;
        VBuffer->Normal3(iV2) += vec3fNormal;
    }

    for( i = 0; i < iVCount; i++ )
    {
        VBuffer->Normal3(i).Normalize();
    }
}
//----------------------------------------------------------------------------
TriMesh::PickRecord::PickRecord(TriMesh* pIObject, float fT, int iTriangle,
    float fBary0, float fBary1, float fBary2)
    :
    Geometry::PickRecord(pIObject, fT)
{
    Triangle = iTriangle;
    Bary0 = fBary0;
    Bary1 = fBary1;
    Bary2 = fBary2;
}
//----------------------------------------------------------------------------
TriMesh::PickRecord::PickRecord()
    :
    Geometry::PickRecord(0, 0.0f)
{
    Triangle = -1;
    Bary0 = 0.0f;
    Bary1 = 0.0f;
    Bary2 = 0.0f;
}
//----------------------------------------------------------------------------
void TriMesh::DoPick(const Ray3f& rRay, PickArray& rResults)
{
    if( WorldBound->TestIntersection(rRay) )
    {
        // 把射线变换到模型空间.
        Vector3f vec3fMDir, vec3fMPos;
        World.ApplyInverse(rRay.Origin, vec3fMPos);
        World.InvertVector(rRay.Direction, vec3fMDir);
        vec3fMDir.Normalize();
        Ray3f tempRay(vec3fMPos, vec3fMDir);

        // 与模型空间三角网格计算所有相交点,生成对应的pick record.
        int iTCount = IBuffer->GetIndexCount()/3;
        const int* piConnect = IBuffer->GetData();
        for( int i = 0; i < iTCount; i++ )
        {
            int iV0 = *piConnect++;
            int iV1 = *piConnect++;
            int iV2 = *piConnect++;

            Triangle3f tempTriangle(VBuffer->Position3(iV0),
                VBuffer->Position3(iV1), VBuffer->Position3(iV2));

            IntrRay3Triangle3f tempIntr(tempRay, tempTriangle);
            if( tempIntr.Find() )
            {
                // TODO:
                // T will be used as a key value for sorting the picking 
                // result array. If two TriMesh objects have different scale
                // transformation, their t values should not be compared 
                // directly. Instead, (t' = t * norm) does the right thing.
                // Do we have a better solution to make the computation 
                // faster?
                PickRecord* pRecord = AllocatePickRecord();
                pRecord->IObject = this;
                pRecord->T = tempIntr.GetRayT()*World.GetNorm();
                pRecord->Triangle = i;
                pRecord->Bary0 = tempIntr.GetTriB0();
                pRecord->Bary1 = tempIntr.GetTriB1();
                pRecord->Bary2 = tempIntr.GetTriB2();
                rResults.push_back(pRecord);
            }
        }
    }
}
//----------------------------------------------------------------------------
void TriMesh::InitializePickRecordPool(int iMaxCount, int iGrowBy)
{
    SE_ASSERT( iMaxCount > 0 && iGrowBy > 0 );

    ms_iMaxCount = iMaxCount;
    ms_iGrowBy = iGrowBy;
    ms_PickRecordPool.resize(ms_iMaxCount);
    ms_iCount = 0;
}
//----------------------------------------------------------------------------
void TriMesh::TerminatePickRecordPool()
{
    for( int i = 0; i < (int)ms_PickRecordPool.size(); i++ )
    {
        ms_PickRecordPool[i].IObject = 0;
    }
}
//----------------------------------------------------------------------------
void TriMesh::ResetPickRecordPool()
{
    ms_iCount = 0;
}
//----------------------------------------------------------------------------
inline TriMesh::PickRecord* TriMesh::AllocatePickRecord()
{
    if( ms_iCount >= ms_iMaxCount )
    {
        ms_iMaxCount += ms_iGrowBy;
        ms_PickRecordPool.resize(ms_iMaxCount);
    }

    return &(ms_PickRecordPool[ms_iCount++]);
}
//----------------------------------------------------------------------------
