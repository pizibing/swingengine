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
#include "SESphereBV.h"
#include "SEContSphere3.h"
#include "SEIntrRay3Sphere3.h"
#include "SEIntrSphere3Sphere3.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SphereBV, BoundingVolume);
SE_IMPLEMENT_STREAM(SphereBV);
SE_IMPLEMENT_DEFAULT_NAME_ID(SphereBV, BoundingVolume);

//SE_REGISTER_STREAM(SphereBV);

//----------------------------------------------------------------------------
// BoundingVolume的工厂函数默认实现为创建SphereBV对象,
// 可以删除当前函数实现,使用另一个BoundingVolume派生类型.
//----------------------------------------------------------------------------
BoundingVolume* BoundingVolume::Create()
{
    return SE_NEW SphereBV;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
SphereBV::SphereBV()
    :
    m_Sphere(Vector3f::ZERO, 0.0f)
{
}
//----------------------------------------------------------------------------
SphereBV::SphereBV(const Sphere3f& rSphere)
    :
    m_Sphere(rSphere)
{
}
//----------------------------------------------------------------------------
void SphereBV::ComputeFromData(const Vector3fArray* pVertices)
{
    if( pVertices )
    {
        int iVCount = pVertices->GetCount();
        const Vector3f* aVertex = pVertices->GetData();
        m_Sphere = ContSphereAveragef(iVCount, aVertex);
    }
}
//----------------------------------------------------------------------------
void SphereBV::ComputeFromData(const VertexBuffer* pVBuffer)
{
    // 待实现.
    // 如果传入VB的顶点为(x,y,z,w),且w不等于1,怎么办?
    if( pVBuffer )
    {
        int iPCount = pVBuffer->GetVertexCount();

        m_Sphere.Center = Vector3f::ZERO;
        m_Sphere.Radius = 0.0f;
        int i;
        for( i = 0; i < iPCount; i++ )
        {
            m_Sphere.Center += pVBuffer->Position3(i);
        }
        m_Sphere.Center /= (float)iPCount;

        for( i = 0; i < iPCount; i++ )
        {
            Vector3f vec3fDiff = pVBuffer->Position3(i) - m_Sphere.Center;
            float fRadiusSqr = vec3fDiff.GetSquaredLength();
            if( fRadiusSqr > m_Sphere.Radius )
            {
                m_Sphere.Radius = fRadiusSqr;
            }
        }

        m_Sphere.Radius = Mathf::Sqrt(m_Sphere.Radius);
    }
}
//----------------------------------------------------------------------------
void SphereBV::TransformBy(const Transformation& rTransform,
    BoundingVolume* pResult)
{
    Sphere3f& rTarget = ((SphereBV*)pResult)->m_Sphere;
    rTransform.ApplyForward(m_Sphere.Center, rTarget.Center);
    rTarget.Radius = rTransform.GetNorm() * m_Sphere.Radius;
}
//----------------------------------------------------------------------------
int SphereBV::OnWhichSide(const Plane3f& rPlane) const
{
    float fDistance = rPlane.GetDistance(m_Sphere.Center);

    if( fDistance <= -m_Sphere.Radius )
    {
        return -1;
    }

    if( fDistance >= m_Sphere.Radius )
    {
        return +1;
    }

    return 0;
}
//----------------------------------------------------------------------------
bool SphereBV::TestIntersection(const Ray3f& rRay) const
{
    return IntrRay3Sphere3f(rRay, m_Sphere).Test();
}
//----------------------------------------------------------------------------
bool SphereBV::TestIntersection(const BoundingVolume* pInput) const
{
    return IntrSphere3Sphere3f(m_Sphere,
        ((SphereBV*)pInput)->m_Sphere).Test();
}
//----------------------------------------------------------------------------
void SphereBV::CopyFrom(const BoundingVolume* pInput)
{
    m_Sphere = ((SphereBV*)pInput)->m_Sphere;
}
//----------------------------------------------------------------------------
void SphereBV::GrowToContain(const BoundingVolume* pInput)
{
    m_Sphere = MergeSpheresf(m_Sphere, ((SphereBV*)pInput)->m_Sphere);
}
//----------------------------------------------------------------------------
bool SphereBV::Contains(const Vector3f& rPoint) const
{
    return IsInSpheref(rPoint, m_Sphere);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SphereBV::Load(SEStream& rStream, SEStream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    BoundingVolume::Load(rStream, pLink);

    // native data
    rStream.Read(m_Sphere.Center);
    rStream.Read(m_Sphere.Radius);

    SE_END_DEBUG_STREAM_LOAD(SphereBV);
}
//----------------------------------------------------------------------------
void SphereBV::Link(SEStream& rStream, SEStream::Link* pLink)
{
    BoundingVolume::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SphereBV::Register(SEStream& rStream) const
{
    return BoundingVolume::Register(rStream);
}
//----------------------------------------------------------------------------
void SphereBV::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    BoundingVolume::Save(rStream);

    // native data
    rStream.Write(m_Sphere.Center);
    rStream.Write(m_Sphere.Radius);

    SE_END_DEBUG_STREAM_SAVE(SphereBV);
}
//----------------------------------------------------------------------------
int SphereBV::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return BoundingVolume::GetDiskUsed(rVersion) +
        sizeof(m_Sphere);
}
//----------------------------------------------------------------------------
SEStringTree* SphereBV::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("center =", m_Sphere.Center));
    pTree->Append(Format("radius =", m_Sphere.Radius));

    // children
    pTree->Append(BoundingVolume::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
