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

SE_IMPLEMENT_RTTI(Swing, SESphereBV, SEBoundingVolume);
SE_IMPLEMENT_STREAM(SESphereBV);
SE_IMPLEMENT_DEFAULT_NAME_ID(SESphereBV, SEBoundingVolume);

//SE_REGISTER_STREAM(SESphereBV);

//----------------------------------------------------------------------------
// SEBoundingVolume的工厂函数默认实现为创建SESphereBV对象,
// 可以删除当前函数实现,使用另一个SEBoundingVolume派生类型.
//----------------------------------------------------------------------------
SEBoundingVolume* SEBoundingVolume::Create()
{
    return SE_NEW SESphereBV;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
SESphereBV::SESphereBV()
    :
    m_Sphere(SEVector3f::ZERO, 0.0f)
{
}
//----------------------------------------------------------------------------
SESphereBV::SESphereBV(const SESphere3f& rSphere)
    :
    m_Sphere(rSphere)
{
}
//----------------------------------------------------------------------------
void SESphereBV::ComputeFromData(const SEVector3fArray* pVertices)
{
    if( pVertices )
    {
        int iVCount = pVertices->GetCount();
        const SEVector3f* aVertex = pVertices->GetData();
        m_Sphere = ContSphereAveragef(iVCount, aVertex);
    }
}
//----------------------------------------------------------------------------
void SESphereBV::ComputeFromData(const SEVertexBuffer* pVBuffer)
{
    // 待实现.
    // 如果传入VB的顶点为(x,y,z,w),且w不等于1,怎么办?
    if( pVBuffer )
    {
        int iPCount = pVBuffer->GetVertexCount();

        m_Sphere.Center = SEVector3f::ZERO;
        m_Sphere.Radius = 0.0f;
        int i;
        for( i = 0; i < iPCount; i++ )
        {
            m_Sphere.Center += pVBuffer->Position3(i);
        }
        m_Sphere.Center /= (float)iPCount;

        for( i = 0; i < iPCount; i++ )
        {
            SEVector3f vec3fDiff = pVBuffer->Position3(i) - m_Sphere.Center;
            float fRadiusSqr = vec3fDiff.GetSquaredLength();
            if( fRadiusSqr > m_Sphere.Radius )
            {
                m_Sphere.Radius = fRadiusSqr;
            }
        }

        m_Sphere.Radius = SEMathf::Sqrt(m_Sphere.Radius);
    }
}
//----------------------------------------------------------------------------
void SESphereBV::TransformBy(const SETransformation& rTransform,
    SEBoundingVolume* pResult)
{
    SESphere3f& rTarget = ((SESphereBV*)pResult)->m_Sphere;
    rTransform.ApplyForward(m_Sphere.Center, rTarget.Center);
    rTarget.Radius = rTransform.GetNorm() * m_Sphere.Radius;
}
//----------------------------------------------------------------------------
int SESphereBV::OnWhichSide(const SEPlane3f& rPlane) const
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
bool SESphereBV::TestIntersection(const SERay3f& rRay) const
{
    return SEIntrRay3Sphere3f(rRay, m_Sphere).Test();
}
//----------------------------------------------------------------------------
bool SESphereBV::TestIntersection(const SEBoundingVolume* pInput) const
{
    return SEIntrSphere3Sphere3f(m_Sphere,
        ((SESphereBV*)pInput)->m_Sphere).Test();
}
//----------------------------------------------------------------------------
void SESphereBV::CopyFrom(const SEBoundingVolume* pInput)
{
    m_Sphere = ((SESphereBV*)pInput)->m_Sphere;
}
//----------------------------------------------------------------------------
void SESphereBV::GrowToContain(const SEBoundingVolume* pInput)
{
    m_Sphere = MergeSpheresf(m_Sphere, ((SESphereBV*)pInput)->m_Sphere);
}
//----------------------------------------------------------------------------
bool SESphereBV::Contains(const SEVector3f& rPoint) const
{
    return IsInSpheref(rPoint, m_Sphere);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SESphereBV::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEBoundingVolume::Load(rStream, pLink);

    // native data
    rStream.Read(m_Sphere.Center);
    rStream.Read(m_Sphere.Radius);

    SE_END_DEBUG_STREAM_LOAD(SESphereBV);
}
//----------------------------------------------------------------------------
void SESphereBV::SELink(SEStream& rStream, SEStream::SELink* pLink)
{
    SEBoundingVolume::SELink(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SESphereBV::Register(SEStream& rStream) const
{
    return SEBoundingVolume::Register(rStream);
}
//----------------------------------------------------------------------------
void SESphereBV::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEBoundingVolume::Save(rStream);

    // native data
    rStream.Write(m_Sphere.Center);
    rStream.Write(m_Sphere.Radius);

    SE_END_DEBUG_STREAM_SAVE(SESphereBV);
}
//----------------------------------------------------------------------------
int SESphereBV::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SEBoundingVolume::GetDiskUsed(rVersion) +
        sizeof(m_Sphere);
}
//----------------------------------------------------------------------------
SEStringTree* SESphereBV::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("center =", m_Sphere.Center));
    pTree->Append(Format("radius =", m_Sphere.Radius));

    // children
    pTree->Append(SEBoundingVolume::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
