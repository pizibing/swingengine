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
#include "SESkinController.h"
#include "SEGeometry.h"
#include "SENode.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SESkinController, SEController);
SE_IMPLEMENT_STREAM(SESkinController);
SE_IMPLEMENT_DEFAULT_NAME_ID(SESkinController, SEController);

//SE_REGISTER_STREAM(SESkinController);

//----------------------------------------------------------------------------
SESkinController::SESkinController(int iVertexCount, int iBoneCount,
    SENode** apBones, float** aafWeight, SEVector3f** aaOffset)
{
    m_iVertexCount = iVertexCount;
    m_iBoneCount = iBoneCount;
    m_apBones = apBones;
    m_aafWeight = aafWeight;
    m_aaOffset = aaOffset;
}
//----------------------------------------------------------------------------
SESkinController::SESkinController()
{
    m_iVertexCount = 0;
    m_iBoneCount = 0;
    m_apBones = 0;
    m_aafWeight = 0;
    m_aaOffset = 0;
}
//----------------------------------------------------------------------------
SESkinController::~SESkinController()
{
    SE_DELETE[] m_apBones;
    Deallocate<float>(m_aafWeight);
    Deallocate<SEVector3f>(m_aaOffset);
}
//----------------------------------------------------------------------------
bool SESkinController::Update(double dAppTime)
{
    if( !SEController::Update(dAppTime) )
    {
        return false;
    }

    // 所有蒙皮顶点都在骨骼世界坐标体系下计算出世界位置,
    // 因此SETriMesh的世界变换必须设置成单位变换.
    SEGeometry* pGeometry = StaticCast<SEGeometry>(m_pObject);
    pGeometry->World = SETransformation::IDENTITY;
    pGeometry->WorldIsCurrent = true;

    // 计算蒙皮顶点位置.
    SE_ASSERT( m_iVertexCount == pGeometry->VBuffer->GetVertexCount() );
    for( int i = 0; i < m_iVertexCount; i++ )
    {
        SEVector3f vec3fTemp;
        m_apBones[0]->World.ApplyForward(m_aaOffset[i][0], vec3fTemp);
        pGeometry->VBuffer->Position3(i) = m_aafWeight[i][0] * vec3fTemp;
        for( int j = 1; j < m_iBoneCount; j++ )
        {
            if( m_aafWeight[i][j] != 0.0f )
            {
                m_apBones[j]->World.ApplyForward(m_aaOffset[i][j], vec3fTemp);
                pGeometry->VBuffer->Position3(i) += m_aafWeight[i][j] *
                    vec3fTemp;
            }
        }
    }

    pGeometry->VBuffer->Release(); // 通知渲染器放弃该VB在显存中的旧数据
    pGeometry->UpdateMS();

    return true;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SESkinController::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEController::Load(rStream, pLink);

    // native data
    rStream.Read(m_iVertexCount);
    rStream.Read(m_iBoneCount);

    int i;

    Allocate<float>(m_iBoneCount, m_iVertexCount, m_aafWeight);
    for( i = 0; i < m_iVertexCount; i++ )
    {
        rStream.Read(m_iBoneCount, m_aafWeight[i]);
    }

    Allocate<SEVector3f>(m_iBoneCount, m_iVertexCount, m_aaOffset);
    for( i = 0; i < m_iVertexCount; i++ )
    {
        rStream.Read(m_iBoneCount, m_aaOffset[i]);
    }

    // link data
    for( i = 0; i < m_iBoneCount; i++ )
    {
        SEObject* pObject;
        rStream.Read(pObject);  // m_apBones[i]
        pLink->Add(pObject);
    }

    SE_END_DEBUG_STREAM_LOAD(SESkinController);
}
//----------------------------------------------------------------------------
void SESkinController::Link(SEStream& rStream, SEStream::SELink* pLink)
{
    SEController::Link(rStream, pLink);

    m_apBones = SE_NEW SENode*[m_iBoneCount];
    for( int i = 0; i < m_iBoneCount; i++ )
    {
        SEObject* pLinkID = pLink->GetLinkID();
        m_apBones[i] = (SENode*)rStream.GetFromMap(pLinkID);
    }
}
//----------------------------------------------------------------------------
bool SESkinController::Register(SEStream& rStream) const
{
    if( !SEController::Register(rStream) )
    {
        return false;
    }

    for( int i = 0; i < m_iBoneCount; i++ )
    {
        if( m_apBones[i] )
        {
            m_apBones[i]->Register(rStream);
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void SESkinController::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEController::Save(rStream);

    // native data
    rStream.Write(m_iVertexCount);
    rStream.Write(m_iBoneCount);

    int i;
    for( i = 0; i < m_iVertexCount; i++ )
    {
        rStream.Write(m_iBoneCount, m_aafWeight[i]);
    }

    for( i = 0; i < m_iVertexCount; i++ )
    {
        rStream.Write(m_iBoneCount, m_aaOffset[i]);
    }

    // link data
    rStream.Write(m_iBoneCount, (SEObject**)m_apBones);

    SE_END_DEBUG_STREAM_SAVE(SESkinController);
}
//----------------------------------------------------------------------------
int SESkinController::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SEController::GetDiskUsed(rVersion) +
        sizeof(m_iVertexCount) +
        sizeof(m_iBoneCount) +
        m_iVertexCount*m_iBoneCount*sizeof(m_aafWeight[0][0]) +
        m_iVertexCount*m_iBoneCount*sizeof(m_aaOffset[0][0]) +
        m_iBoneCount*sizeof(m_apBones[0]);
}
//----------------------------------------------------------------------------
SEStringTree* SESkinController::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("vertex count = ", m_iVertexCount));
    pTree->Append(Format("bone count = ", m_iBoneCount));

    // children
    pTree->Append(SEController::SaveStrings());
    pTree->Append(Format("bones", m_iBoneCount, m_apBones));

    const size_t uiTitleSize = 256;
    char acTitle[uiTitleSize];
    int i;
    for( i = 0; i < m_iVertexCount; i++ )
    {
        SESystem::SE_Sprintf(acTitle, uiTitleSize, "weights for vertex %d", i);
        pTree->Append(Format(acTitle, m_iBoneCount, m_aafWeight[i]));
    }

    for( i = 0; i < m_iVertexCount; i++ )
    {
        SESystem::SE_Sprintf(acTitle, uiTitleSize, "offsets for vertex %d", i);
        pTree->Append(Format(acTitle, m_iBoneCount, m_aaOffset[i]));
    }

    return pTree;
}
//----------------------------------------------------------------------------
