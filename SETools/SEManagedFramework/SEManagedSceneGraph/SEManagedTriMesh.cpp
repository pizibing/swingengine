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

#include "SEManagedFrameworkPCH.h"
#include "SEManagedTriMesh.h"
#include "SEManagedObjectFactory.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedTriMesh::ManagedTriMesh()
{
    m_pspTriMesh = SE_NEW TriMeshPtr;

    // TODO:
    // Create a trimesh object from native VB/IB objects.
}
//---------------------------------------------------------------------------
ManagedTriMesh::ManagedTriMesh(TriMesh* pTriMesh)
{
    m_pspTriMesh = SE_NEW TriMeshPtr;
    (*m_pspTriMesh) = pTriMesh;
}
//---------------------------------------------------------------------------
ManagedTriMesh::~ManagedTriMesh()
{
    SE_DELETE m_pspTriMesh;
    m_pspTriMesh = 0;
}
//---------------------------------------------------------------------------
ManagedTriMesh^ ManagedTriMesh::Clone()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    TriMesh* pTriMesh = SE_NEW TriMesh((*m_pspTriMesh)->VBuffer, 
        (*m_pspTriMesh)->IBuffer);

    return gcnew ManagedTriMesh(pTriMesh);
}
//---------------------------------------------------------------------------
ManagedNode^ ManagedTriMesh::GetLocalAABBFrame(ManagedColorRGB^ thColor)
{
    SE_NULL_ARGUMENT_CHECK(thColor, "thColor");
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    VertexBuffer* pVB = (*m_pspTriMesh)->VBuffer;

    SE_NULL_REFERENCE_CHECK(pVB, "Native pointer is null");
    int iVCount = pVB->GetVertexCount();

    // Compute the local AABB from the vertex buffer.
    Vector3f vec3fMin = pVB->Position3(0);
    Vector3f vec3fMax(vec3fMin);
    for( int i = 1; i < iVCount; i++ )
    {
        const Vector3f& rPoint = pVB->Position3(i);
        for( int j = 0; j < 3; j++ )
        {
            if( rPoint[j] < vec3fMin[j] )
            {
                vec3fMin[j] = rPoint[j];
            }
            else if( rPoint[j] > vec3fMax[j] )
            {
                vec3fMax[j] = rPoint[j];
            }
        }
    }

    // Create the AABBFrame.
    ColorRGB tempColor;
    thColor->ToColorRGB(tempColor);
    Node* pAABBFrame = Widget::AABBFrame(vec3fMin, vec3fMax, tempColor);

    return gcnew ManagedNode(pAABBFrame);
}
//---------------------------------------------------------------------------
void ManagedTriMesh::SetLocalRotate(ManagedMatrix3f^ thRotate)
{
    SE_NULL_ARGUMENT_CHECK(thRotate, "thRotate");
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    Matrix3f mat3fRot;
    thRotate->ToMatrix3f(mat3fRot);
    (*m_pspTriMesh)->Local.SetRotate(mat3fRot);
}
//---------------------------------------------------------------------------
ManagedMatrix3f^ ManagedTriMesh::GetLocalRotate()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    return gcnew ManagedMatrix3f((*m_pspTriMesh)->Local.GetRotate());
}
//---------------------------------------------------------------------------
void ManagedTriMesh::SetLocalMatrix(ManagedMatrix3f^ thMatrix)
{
    SE_NULL_ARGUMENT_CHECK(thMatrix, "thMatrix");
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    Matrix3f mat3fM;
    thMatrix->ToMatrix3f(mat3fM);
    (*m_pspTriMesh)->Local.SetMatrix(mat3fM);
}
//---------------------------------------------------------------------------
ManagedMatrix3f^ ManagedTriMesh::GetLocalMatrix()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    return gcnew ManagedMatrix3f((*m_pspTriMesh)->Local.GetMatrix());
}
//---------------------------------------------------------------------------
void ManagedTriMesh::SetLocalTranslate(ManagedVector3f^ thTranslate)
{
    SE_NULL_ARGUMENT_CHECK(thTranslate, "thTranslate");
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    Vector3f vec3fTrn;
    thTranslate->ToVector3f(vec3fTrn);
    (*m_pspTriMesh)->Local.SetTranslate(vec3fTrn);
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedTriMesh::GetLocalTranslate()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    return gcnew ManagedVector3f((*m_pspTriMesh)->Local.GetTranslate());
}
//---------------------------------------------------------------------------
void ManagedTriMesh::SetLocalScale(ManagedVector3f^ thScale)
{
    SE_NULL_ARGUMENT_CHECK(thScale, "thScale");
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    Vector3f vec3fScl;
    thScale->ToVector3f(vec3fScl);
    (*m_pspTriMesh)->Local.SetScale(vec3fScl);
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedTriMesh::GetLocalScale()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    return gcnew ManagedVector3f((*m_pspTriMesh)->Local.GetScale());
}
//---------------------------------------------------------------------------
void ManagedTriMesh::SetLocalUniformScale(float fScale)
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    (*m_pspTriMesh)->Local.SetUniformScale(fScale);
}
//---------------------------------------------------------------------------
float ManagedTriMesh::GetLocalUniformScale()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    return (*m_pspTriMesh)->Local.GetUniformScale();
}
//---------------------------------------------------------------------------
void ManagedTriMesh::UpdateGS(double dAppTime)
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    (*m_pspTriMesh)->UpdateGS(dAppTime);
}
//---------------------------------------------------------------------------
void ManagedTriMesh::UpdateRS()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    (*m_pspTriMesh)->UpdateRS();
}
//---------------------------------------------------------------------------
int ManagedTriMesh::GetLightCount()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    return (*m_pspTriMesh)->GetLightCount();
}
//---------------------------------------------------------------------------
ManagedLight^ ManagedTriMesh::GetLight(int i)
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    return gcnew ManagedLight((*m_pspTriMesh)->GetLight(i));
}
//---------------------------------------------------------------------------
void ManagedTriMesh::AttachLight(ManagedLight^ thLight)
{
    SE_NULL_ARGUMENT_CHECK(thLight, "thLight");
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    (*m_pspTriMesh)->AttachLight(thLight->GetNativeLight());
}
//---------------------------------------------------------------------------
void ManagedTriMesh::DetachLight(ManagedLight^ thLight)
{
    SE_NULL_ARGUMENT_CHECK(thLight, "thLight");
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    (*m_pspTriMesh)->DetachLight(thLight->GetNativeLight());
}
//---------------------------------------------------------------------------
void ManagedTriMesh::DetachAllLights()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    (*m_pspTriMesh)->DetachAllLights();
}
//---------------------------------------------------------------------------
void ManagedTriMesh::AttachEffect(INativeEffect^ thEffect)
{
    SE_NULL_ARGUMENT_CHECK(thEffect, "thEffect");
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    (*m_pspTriMesh)->AttachEffect(thEffect->GetNativeEffect());
}
//---------------------------------------------------------------------------
void ManagedTriMesh::DetachEffect(INativeEffect^ thEffect)
{
    SE_NULL_ARGUMENT_CHECK(thEffect, "thEffect");
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    (*m_pspTriMesh)->DetachEffect(thEffect->GetNativeEffect());
}
//---------------------------------------------------------------------------
void ManagedTriMesh::DetachAllEffects()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    (*m_pspTriMesh)->DetachAllEffects();
}
//---------------------------------------------------------------------------
int ManagedTriMesh::GetGlobalStateCount()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    return (*m_pspTriMesh)->GetGlobalStateCount();
}
//---------------------------------------------------------------------------
INativeGlobalState^ ManagedTriMesh::GetGlobalState(int i)
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    GlobalState* pState = (*m_pspTriMesh)->GetGlobalState(i);

    return ManagedObjectFactory::CreateGlobalStateObject(pState);
}
//---------------------------------------------------------------------------
INativeGlobalState^ ManagedTriMesh::GetGlobalState(
    INativeGlobalState::StateType eType)
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    GlobalState* pState = (*m_pspTriMesh)->GetGlobalState(
        (GlobalState::StateType)eType);

    return ManagedObjectFactory::CreateGlobalStateObject(pState);
}
//---------------------------------------------------------------------------
void ManagedTriMesh::AttachGlobalState(INativeGlobalState^ thState)
{
    SE_NULL_ARGUMENT_CHECK(thState, "thState");
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    (*m_pspTriMesh)->AttachGlobalState(thState->GetNativeGlobalState());
}
//---------------------------------------------------------------------------
void ManagedTriMesh::DetachGlobalState(INativeGlobalState::StateType eType)
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    (*m_pspTriMesh)->DetachGlobalState((GlobalState::StateType)eType);
}
//---------------------------------------------------------------------------
void ManagedTriMesh::DetachAllGlobalStates()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    (*m_pspTriMesh)->DetachAllGlobalStates();
}
//---------------------------------------------------------------------------
INativeSpatial^ ManagedTriMesh::GetParent()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    Spatial* pSpatial = (*m_pspTriMesh)->GetParent();

    return ManagedObjectFactory::CreateSpatialDerivedObject(pSpatial);
}
//---------------------------------------------------------------------------
void ManagedTriMesh::SetName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");

    const char* acName = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acName);
    ManagedUtility::FreeNativeCharBuffer(acName);
    (*m_pspTriMesh)->SetName(tempName);
}
//---------------------------------------------------------------------------
String^ ManagedTriMesh::GetName()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    return gcnew String((*m_pspTriMesh)->GetName().c_str());
}
//---------------------------------------------------------------------------
int ManagedTriMesh::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    return (*m_pspTriMesh)->GetReferences();
}
//---------------------------------------------------------------------------
void ManagedTriMesh::InitializePickRecordPool(int iMaxCount, int iGrowBy)
{
    TriMesh::InitializePickRecordPool(iMaxCount, iGrowBy);
}
//---------------------------------------------------------------------------
void ManagedTriMesh::TerminatePickRecordPool()
{
    TriMesh::TerminatePickRecordPool();
}
//---------------------------------------------------------------------------
Spatial* ManagedTriMesh::GetNativeSpatial()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    return (Spatial*)(*m_pspTriMesh);
}
//---------------------------------------------------------------------------
Geometry* ManagedTriMesh::GetNativeGeometry()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native pointer is null");
    return (Geometry*)(*m_pspTriMesh);
}
//---------------------------------------------------------------------------