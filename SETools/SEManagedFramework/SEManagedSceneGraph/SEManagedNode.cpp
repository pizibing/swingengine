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
#include "SEManagedNode.h"
#include "SEManagedObjectFactory.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedNode::ManagedNode()
{
    m_pspNode = SE_NEW NodePtr;
    (*m_pspNode) = SE_NEW Node;
}
//---------------------------------------------------------------------------
ManagedNode::ManagedNode(Node* pNode)
{
    m_pspNode = SE_NEW NodePtr;
    (*m_pspNode) = pNode;
}
//---------------------------------------------------------------------------
ManagedNode::~ManagedNode()
{
    SE_DELETE m_pspNode;
    m_pspNode = 0;
}
//---------------------------------------------------------------------------
ManagedNode^ ManagedNode::Clone()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    Node* pClonedObject = ManagedUtility::CloneNode(*m_pspNode);

    return gcnew ManagedNode(pClonedObject);
}
//---------------------------------------------------------------------------
int ManagedNode::GetCount()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return (*m_pspNode)->GetCount();
}
//---------------------------------------------------------------------------
int ManagedNode::AttachChild(INativeSpatial^ thSpatial)
{
    SE_NULL_ARGUMENT_CHECK(thSpatial, "thSpatial");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return (*m_pspNode)->AttachChild(thSpatial->GetNativeSpatial());
}
//---------------------------------------------------------------------------
int ManagedNode::DetachChild(INativeSpatial^ thSpatial)
{
    SE_NULL_ARGUMENT_CHECK(thSpatial, "thSpatial");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return (*m_pspNode)->DetachChild(thSpatial->GetNativeSpatial());
}
//---------------------------------------------------------------------------
void ManagedNode::SetLocalRotate(ManagedMatrix3f^ thRotate)
{
    SE_NULL_ARGUMENT_CHECK(thRotate, "thRotate");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    Matrix3f mat3fRot;
    thRotate->ToMatrix3f(mat3fRot);
    (*m_pspNode)->Local.SetRotate(mat3fRot);
}
//---------------------------------------------------------------------------
ManagedMatrix3f^ ManagedNode::GetLocalRotate()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return gcnew ManagedMatrix3f((*m_pspNode)->Local.GetRotate());
}
//---------------------------------------------------------------------------
void ManagedNode::SetLocalMatrix(ManagedMatrix3f^ thMatrix)
{
    SE_NULL_ARGUMENT_CHECK(thMatrix, "thMatrix");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    Matrix3f mat3fM;
    thMatrix->ToMatrix3f(mat3fM);
    (*m_pspNode)->Local.SetMatrix(mat3fM);
}
//---------------------------------------------------------------------------
ManagedMatrix3f^ ManagedNode::GetLocalMatrix()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return gcnew ManagedMatrix3f((*m_pspNode)->Local.GetMatrix());
}
//---------------------------------------------------------------------------
void ManagedNode::SetLocalTranslate(ManagedVector3f^ thTranslate)
{
    SE_NULL_ARGUMENT_CHECK(thTranslate, "thTranslate");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    Vector3f vec3fTrn;
    thTranslate->ToVector3f(vec3fTrn);
    (*m_pspNode)->Local.SetTranslate(vec3fTrn);
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedNode::GetLocalTranslate()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return gcnew ManagedVector3f((*m_pspNode)->Local.GetTranslate());
}
//---------------------------------------------------------------------------
void ManagedNode::SetLocalScale(ManagedVector3f^ thScale)
{
    SE_NULL_ARGUMENT_CHECK(thScale, "thScale");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    Vector3f vec3fScl;
    thScale->ToVector3f(vec3fScl);
    (*m_pspNode)->Local.SetScale(vec3fScl);
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedNode::GetLocalScale()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return gcnew ManagedVector3f((*m_pspNode)->Local.GetScale());
}
//---------------------------------------------------------------------------
void ManagedNode::SetLocalUniformScale(float fScale)
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    (*m_pspNode)->Local.SetUniformScale(fScale);
}
//---------------------------------------------------------------------------
float ManagedNode::GetLocalUniformScale()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return (*m_pspNode)->Local.GetUniformScale();
}
//---------------------------------------------------------------------------
void ManagedNode::UpdateGS(double dAppTime)
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    (*m_pspNode)->UpdateGS(dAppTime);
}
//---------------------------------------------------------------------------
void ManagedNode::UpdateRS()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    (*m_pspNode)->UpdateRS();
}
//---------------------------------------------------------------------------
int ManagedNode::GetLightCount()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return (*m_pspNode)->GetLightCount();
}
//---------------------------------------------------------------------------
ManagedLight^ ManagedNode::GetLight(int i)
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return gcnew ManagedLight((*m_pspNode)->GetLight(i));
}
//---------------------------------------------------------------------------
void ManagedNode::AttachLight(ManagedLight^ thLight)
{
    SE_NULL_ARGUMENT_CHECK(thLight, "thLight");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    (*m_pspNode)->AttachLight(thLight->GetNativeLight());
}
//---------------------------------------------------------------------------
void ManagedNode::DetachLight(ManagedLight^ thLight)
{
    SE_NULL_ARGUMENT_CHECK(thLight, "thLight");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    (*m_pspNode)->DetachLight(thLight->GetNativeLight());
}
//---------------------------------------------------------------------------
void ManagedNode::DetachAllLights()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    (*m_pspNode)->DetachAllLights();
}
//---------------------------------------------------------------------------
void ManagedNode::AttachEffect(INativeEffect^ thEffect)
{
    SE_NULL_ARGUMENT_CHECK(thEffect, "thEffect");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    (*m_pspNode)->AttachEffect(thEffect->GetNativeEffect());
}
//---------------------------------------------------------------------------
void ManagedNode::DetachEffect(INativeEffect^ thEffect)
{
    SE_NULL_ARGUMENT_CHECK(thEffect, "thEffect");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    (*m_pspNode)->DetachEffect(thEffect->GetNativeEffect());
}
//---------------------------------------------------------------------------
void ManagedNode::DetachAllEffects()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    (*m_pspNode)->DetachAllEffects();
}
//---------------------------------------------------------------------------
int ManagedNode::GetGlobalStateCount()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return (*m_pspNode)->GetGlobalStateCount();
}
//---------------------------------------------------------------------------
INativeGlobalState^ ManagedNode::GetGlobalState(int i)
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    GlobalState* pState = (*m_pspNode)->GetGlobalState(i);

    return ManagedObjectFactory::CreateGlobalStateObject(pState);
}
//---------------------------------------------------------------------------
INativeGlobalState^ ManagedNode::GetGlobalState(
    INativeGlobalState::StateType eType)
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    GlobalState* pState = (*m_pspNode)->GetGlobalState(
        (GlobalState::StateType)eType);

    return ManagedObjectFactory::CreateGlobalStateObject(pState);
}
//---------------------------------------------------------------------------
void ManagedNode::AttachGlobalState(INativeGlobalState^ thState)
{
    SE_NULL_ARGUMENT_CHECK(thState, "thState");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    (*m_pspNode)->AttachGlobalState(thState->GetNativeGlobalState());
}
//---------------------------------------------------------------------------
void ManagedNode::DetachGlobalState(INativeGlobalState::StateType eType)
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    (*m_pspNode)->DetachGlobalState((GlobalState::StateType)eType);
}
//---------------------------------------------------------------------------
void ManagedNode::DetachAllGlobalStates()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    (*m_pspNode)->DetachAllGlobalStates();
}
//---------------------------------------------------------------------------
INativeSpatial^ ManagedNode::GetParent()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    Spatial* pSpatial = (*m_pspNode)->GetParent();

    return ManagedObjectFactory::CreateSpatialDerivedObject(pSpatial);
}
//---------------------------------------------------------------------------
void ManagedNode::SetName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");

    const char* acName = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acName);
    ManagedUtility::FreeNativeCharBuffer(acName);
    (*m_pspNode)->SetName(tempName);
}
//---------------------------------------------------------------------------
String^ ManagedNode::GetName()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return gcnew String((*m_pspNode)->GetName().c_str());
}
//---------------------------------------------------------------------------
int ManagedNode::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return (*m_pspNode)->GetReferences();
}
//---------------------------------------------------------------------------
Spatial* ManagedNode::GetNativeSpatial()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return (Spatial*)(*m_pspNode);
}
//---------------------------------------------------------------------------
Node* ManagedNode::GetNativeNode()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return (Node*)(*m_pspNode);
}
//---------------------------------------------------------------------------