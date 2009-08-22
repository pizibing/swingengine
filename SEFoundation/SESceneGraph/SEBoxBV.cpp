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
#include "SEBoxBV.h"
#include "SEContBox3.h"
#include "SEIntrRay3Box3.h"
#include "SEIntrBox3Box3.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, BoxBV, BoundingVolume);
SE_IMPLEMENT_STREAM(BoxBV);
SE_IMPLEMENT_DEFAULT_NAME_ID(BoxBV, BoundingVolume);

//SE_REGISTER_STREAM(BoxBV);

//----------------------------------------------------------------------------
BoxBV::BoxBV()
    :
    m_Box(Vector3f::ZERO, Vector3f::UNIT_X, Vector3f::UNIT_Y, Vector3f::UNIT_Z,
    1.0f, 1.0f, 1.0f)
{
}
//----------------------------------------------------------------------------
BoxBV::BoxBV(const Box3f& rBox)
    :
    m_Box(rBox)
{
}
//----------------------------------------------------------------------------
BoxBV::~BoxBV()
{
}
//----------------------------------------------------------------------------
void BoxBV::SetRadius(float fRadius)
{
    m_Box.Extent[0] = fRadius;
    m_Box.Extent[1] = fRadius;
    m_Box.Extent[2] = fRadius;
}
//----------------------------------------------------------------------------
float BoxBV::GetRadius() const
{
    float fRadius = m_Box.Extent[0];
    if( fRadius < m_Box.Extent[1] )
    {
        fRadius = m_Box.Extent[1];
    }
    if( fRadius < m_Box.Extent[2] )
    {
        fRadius = m_Box.Extent[2];
    }

    return fRadius;
}
//----------------------------------------------------------------------------
void BoxBV::ComputeFromData(const Vector3fArray* pVertices)
{
    if( pVertices )
    {
        int iVCount = pVertices->GetCount();
        const Vector3f* aVertex = pVertices->GetData();
        m_Box = ContOBBf(iVCount, aVertex);
    }
}
//----------------------------------------------------------------------------
void BoxBV::ComputeFromData(const VertexBuffer* pVBuffer)
{
    // 待实现.
    // 需要实现支持带有stride的顶点数组的ContOBBf函数.
    if( pVBuffer )
    {
        SE_ASSERT( false );
    }
}
//----------------------------------------------------------------------------
void BoxBV::TransformBy(const Transformation& rTransform,
    BoundingVolume* pResult)
{
    Box3f& rTarget = ((BoxBV*)pResult)->m_Box;
    rTransform.ApplyForward(m_Box.Center, rTarget.Center);
    for( int i = 0; i < 3; i++ )
    {
        rTarget.Axis[i] = m_Box.Axis[i] * rTransform.GetRotate();
        rTarget.Extent[i] = rTransform.GetNorm() * m_Box.Extent[i];
    }
}
//----------------------------------------------------------------------------
int BoxBV::OnWhichSide(const Plane3f& rPlane) const
{
    float fProjCenter = rPlane.Normal.Dot(m_Box.Center) - rPlane.Constant;
    float fAbs0 = Mathf::FAbs(rPlane.Normal.Dot(m_Box.Axis[0]));
    float fAbs1 = Mathf::FAbs(rPlane.Normal.Dot(m_Box.Axis[1]));
    float fAbs2 = Mathf::FAbs(rPlane.Normal.Dot(m_Box.Axis[2]));
    float fProjRadius = m_Box.Extent[0]*fAbs0 + m_Box.Extent[1]*fAbs1 +
        m_Box.Extent[2]*fAbs2;

    if( fProjCenter - fProjRadius >= 0.0f )
    {
        return +1;
    }

    if( fProjCenter + fProjRadius <= 0.0f )
    {
        return -1;
    }

    return 0;
}
//----------------------------------------------------------------------------
bool BoxBV::TestIntersection(const Ray3f& rRay) const
{
    return IntrRay3Box3f(rRay, m_Box).Test();
}
//----------------------------------------------------------------------------
bool BoxBV::TestIntersection(const BoundingVolume* pInput) const
{
    return IntrBox3Box3f(m_Box, ((BoxBV*)pInput)->m_Box).Test();
}
//----------------------------------------------------------------------------
void BoxBV::CopyFrom(const BoundingVolume* pInput)
{
    m_Box = ((BoxBV*)pInput)->m_Box;
}
//----------------------------------------------------------------------------
void BoxBV::GrowToContain(const BoundingVolume* pInput)
{
    m_Box = MergeBoxesf(m_Box, ((BoxBV*)pInput)->m_Box);
}
//----------------------------------------------------------------------------
bool BoxBV::Contains(const Vector3f& rPoint) const
{
    return IsInBoxf(rPoint, m_Box);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void BoxBV::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    BoundingVolume::Load(rStream, pLink);

    // native data
    rStream.Read(m_Box.Center);
    rStream.Read(m_Box.Axis[0]);
    rStream.Read(m_Box.Axis[1]);
    rStream.Read(m_Box.Axis[2]);
    rStream.Read(m_Box.Extent[0]);
    rStream.Read(m_Box.Extent[1]);
    rStream.Read(m_Box.Extent[2]);

    SE_END_DEBUG_STREAM_LOAD(BoxBV);
}
//----------------------------------------------------------------------------
void BoxBV::Link(Stream& rStream, Stream::Link* pLink)
{
    BoundingVolume::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool BoxBV::Register(Stream& rStream) const
{
    return BoundingVolume::Register(rStream);
}
//----------------------------------------------------------------------------
void BoxBV::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    BoundingVolume::Save(rStream);

    // native data
    rStream.Write(m_Box.Center);
    rStream.Write(m_Box.Axis[0]);
    rStream.Write(m_Box.Axis[1]);
    rStream.Write(m_Box.Axis[2]);
    rStream.Write(m_Box.Extent[0]);
    rStream.Write(m_Box.Extent[1]);
    rStream.Write(m_Box.Extent[2]);

    SE_END_DEBUG_STREAM_SAVE(BoxBV);
}
//----------------------------------------------------------------------------
int BoxBV::GetDiskUsed(const StreamVersion& rVersion) const
{
    return BoundingVolume::GetDiskUsed(rVersion) +
        sizeof(m_Box);
}
//----------------------------------------------------------------------------
StringTree* BoxBV::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, (const char*)GetName()));
    pTree->Append(Format("center =", m_Box.Center));
    pTree->Append(Format("axis0 =", m_Box.Axis[0]));
    pTree->Append(Format("axis1 =", m_Box.Axis[1]));
    pTree->Append(Format("axis2 =", m_Box.Axis[2]));
    pTree->Append(Format("extent0 =", m_Box.Extent[0]));
    pTree->Append(Format("extent1 =", m_Box.Extent[1]));
    pTree->Append(Format("extent2 =", m_Box.Extent[2]));

    // children
    pTree->Append(BoundingVolume::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
