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

#ifndef Swing_TriMesh_H
#define Swing_TriMesh_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEGeometry.h"
#include "SEIntArray.h"
#include "SETriangle3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 说明:
// 作者:Sun Che
// 时间:20080803
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SETriMesh : public SEGeometry
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    SETriMesh(SEVertexBuffer* pVBuffer, SEIndexBuffer* pIBuffer);
    virtual ~SETriMesh(void);

    // 成员访问.
    inline int GetTriangleCount(void) const;
    void GetModelTriangle(int i, SETriangle3f& rMTri) const;
    void GetWorldTriangle(int i, SETriangle3f& rWTri) const;

    // 生成法线.
    void GenerateNormals(void);

    // 生成切线.
    // 根据指定的一组2维顶点纹理坐标(s,t),生成顶点的T,B,N规范正交基,
    // 其中T对应纹理空间s轴,B对应纹理空间t轴.
    // 用户有责任确保当前网格具备一组2维顶点纹理坐标,创建成功返回true,
    // 否则返回false.
    bool GenerateTangents(int iSrcTCoordUnit, int iTangentUnit, 
        int iBiTangentUnit = -1);

    // Picking support.
    // 此pick record派生类储存了与射线相交的三角形索引值.
    // 同时还储存了相交点的重心权重值.
    // 这将允许应用程序插值计算出相交点的顶点属性和其他具体数据.
    class SE_FOUNDATION_API SEPickRecord : public SEGeometry::SEPickRecord
    {
    public:
        SEPickRecord(SETriMesh* pIObject, float fT, int iTriangle, float fBary0,
            float fBary1, float fBary2);
        SEPickRecord(void);

        // 与射线相交的三角形索引值.
        int Triangle;

        // 相交点在三角形中的重心权重坐标.
        // 全部在[0,1]之间,且b0 + b1 + b2 = 1.
        float Bary0, Bary1, Bary2;
    };

    // 射线的原点和方向向量都必须在世界坐标系下.
    // 应用程序不能释放PickArray中的所有pick record,
    // 因为这些pick record来自于全局内存池的堆内存.
    virtual void DoPick(const SERay3f& rRay, PickArray& rResults);

    // SEPickRecord内存池,避免调用DoPick函数时的频繁动态new和delete操作.
    // 应用程序初始化时,负责调用InitializePickRecordPool函数.
    // 应用程序终止时,负责调用TerminatePickRecordPool函数.
    // 应用程序调用DoPick函数遍历场景视图前,应先调用ResetPickRecordPool函数.
    static void InitializePickRecordPool(int iMaxCount = 32, int iGrowBy = 32);
    static void TerminatePickRecordPool(void);
    static void ResetPickRecordPool(void);

protected:
    SETriMesh(void);

    // 几何体数据更新.
    // 更新模型空间法线.
    virtual void UpdateModelNormals(void);

    // SEPickRecord内存池相关参数.
    inline SEPickRecord* AllocatePickRecord(void);
    static std::vector<SEPickRecord> ms_PickRecordPool;
    static int ms_iMaxCount;
    static int ms_iGrowBy;
    static int ms_iCount;
};

typedef SESmartPointer<SETriMesh> SETriMeshPtr;

#include "SETriMesh.inl"

}

#endif
