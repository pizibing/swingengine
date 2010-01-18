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
#include "SEManagedLightNode.h"
#include "SEManagedObjectFactory.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedLightNode::ManagedLightNode(ManagedLight^ thLight)
{
    SE_NULL_ARGUMENT_CHECK(thLight, "thLight");
    m_pspLightNode = SE_NEW LightNodePtr;
    (*m_pspLightNode) = SE_NEW LightNode(thLight->GetNativeLight());
}
//---------------------------------------------------------------------------
ManagedLightNode::ManagedLightNode(LightNode* pLightNode)
{
    m_pspLightNode = SE_NEW LightNodePtr;
    (*m_pspLightNode) = pLightNode;
}
//---------------------------------------------------------------------------
ManagedLightNode::~ManagedLightNode()
{
    SE_DELETE m_pspLightNode;
    m_pspLightNode = 0;
}
//---------------------------------------------------------------------------
void ManagedLightNode::SetLight(ManagedLight^ thLight)
{
    SE_NULL_ARGUMENT_CHECK(thLight, "thLight");
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    (*m_pspLightNode)->SetLight(thLight->GetNativeLight());
}
//---------------------------------------------------------------------------
ManagedLight^ ManagedLightNode::GetLight()
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    return gcnew ManagedLight((*m_pspLightNode)->GetLight());
}
//---------------------------------------------------------------------------
int ManagedLightNode::GetCount()
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    return (*m_pspLightNode)->GetCount();
}
//---------------------------------------------------------------------------
int ManagedLightNode::AttachChild(INativeSpatial^ thSpatial)
{
    SE_NULL_ARGUMENT_CHECK(thSpatial, "thSpatial");
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    return (*m_pspLightNode)->AttachChild(thSpatial->GetNativeSpatial());
}
//---------------------------------------------------------------------------
int ManagedLightNode::DetachChild(INativeSpatial^ thSpatial)
{
    SE_NULL_ARGUMENT_CHECK(thSpatial, "thSpatial");
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    return (*m_pspLightNode)->DetachChild(thSpatial->GetNativeSpatial());
}
//---------------------------------------------------------------------------
void ManagedLightNode::SetLocalRotate(ManagedMatrix3f^ thRotate)
{
    SE_NULL_ARGUMENT_CHECK(thRotate, "thRotate");
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    Matrix3f mat3fRot;
    thRotate->ToMatrix3f(mat3fRot);
    (*m_pspLightNode)->Local.SetRotate(mat3fRot);
}
//---------------------------------------------------------------------------
ManagedMatrix3f^ ManagedLightNode::GetLocalRotate()
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    return gcnew ManagedMatrix3f((*m_pspLightNode)->Local.GetRotate());
}
//---------------------------------------------------------------------------
void ManagedLightNode::SetLocalMatrix(ManagedMatrix3f^ thMatrix)
{
    SE_NULL_ARGUMENT_CHECK(thMatrix, "thMatrix");
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    Matrix3f mat3fM;
    thMatrix->ToMatrix3f(mat3fM);
    (*m_pspLightNode)->Local.SetMatrix(mat3fM);
}
//---------------------------------------------------------------------------
ManagedMatrix3f^ ManagedLightNode::GetLocalMatrix()
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    return gcnew ManagedMatrix3f((*m_pspLightNode)->Local.GetMatrix());
}
//---------------------------------------------------------------------------
void ManagedLightNode::SetLocalTranslate(ManagedVector3f^ thTranslate)
{
    SE_NULL_ARGUMENT_CHECK(thTranslate, "thTranslate");
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    Vector3f vec3fTrn;
    thTranslate->ToVector3f(vec3fTrn);
    (*m_pspLightNode)->Local.SetTranslate(vec3fTrn);
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedLightNode::GetLocalTranslate()
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    return gcnew ManagedVector3f((*m_pspLightNode)->Local.GetTranslate());
}
//---------------------------------------------------------------------------
void ManagedLightNode::SetLocalScale(ManagedVector3f^ thScale)
{
    SE_NULL_ARGUMENT_CHECK(thScale, "thScale");
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    Vector3f vec3fScl;
    thScale->ToVector3f(vec3fScl);
    (*m_pspLightNode)->Local.SetScale(vec3fScl);
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedLightNode::GetLocalScale()
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    return gcnew ManagedVector3f((*m_pspLightNode)->Local.GetScale());
}
//---------------------------------------------------------------------------
void ManagedLightNode::SetLocalUniformScale(float fScale)
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    (*m_pspLightNode)->Local.SetUniformScale(fScale);
}
//---------------------------------------------------------------------------
float ManagedLightNode::GetLocalUniformScale()
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    return (*m_pspLightNode)->Local.GetUniformScale();
}
//---------------------------------------------------------------------------
void ManagedLightNode::UpdateGS(double dAppTime)
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    (*m_pspLightNode)->UpdateGS(dAppTime);
}
//---------------------------------------------------------------------------
void ManagedLightNode::UpdateRS()
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    (*m_pspLightNode)->UpdateRS();
}
//---------------------------------------------------------------------------
int ManagedLightNode::GetLightCount()
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    return (*m_pspLightNode)->GetLightCount();
}
//---------------------------------------------------------------------------
ManagedLight^ ManagedLightNode::GetLight(int i)
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    return gcnew ManagedLight(((Spatial*)(*m_pspLightNode))->GetLight(i));
}
//---------------------------------------------------------------------------
void ManagedLightNode::AttachLight(ManagedLight^ thLight)
{
    SE_NULL_ARGUMENT_CHECK(thLight, "thLight");
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    (*m_pspLightNode)->AttachLight(thLight->GetNativeLight());
}
//---------------------------------------------------------------------------
void ManagedLightNode::DetachLight(ManagedLight^ thLight)
{
    SE_NULL_ARGUMENT_CHECK(thLight, "thLight");
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    (*m_pspLightNode)->DetachLight(thLight->GetNativeLight());
}
//---------------------------------------------------------------------------
void ManagedLightNode::DetachAllLights()
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    (*m_pspLightNode)->DetachAllLights();
}
//---------------------------------------------------------------------------
void ManagedLightNode::AttachEffect(INativeEffect^ thEffect)
{
    SE_NULL_ARGUMENT_CHECK(thEffect, "thEffect");
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    (*m_pspLightNode)->AttachEffect(thEffect->GetNativeEffect());
}
//---------------------------------------------------------------------------
void ManagedLightNode::DetachEffect(INativeEffect^ thEffect)
{
    SE_NULL_ARGUMENT_CHECK(thEffect, "thEffect");
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    (*m_pspLightNode)->DetachEffect(thEffect->GetNativeEffect());
}
//---------------------------------------------------------------------------
void ManagedLightNode::DetachAllEffects()
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    (*m_pspLightNode)->DetachAllEffects();
}
//---------------------------------------------------------------------------
int ManagedLightNode::GetGlobalStateCount()
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    return (*m_pspLightNode)->GetGlobalStateCount();
}
//---------------------------------------------------------------------------
INativeGlobalState^ ManagedLightNode::GetGlobalState(int i)
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    GlobalState* pState = (*m_pspLightNode)->GetGlobalState(i);

    return ManagedObjectFactory::CreateGlobalState(pState);
}
//---------------------------------------------------------------------------
INativeGlobalState^ ManagedLightNode::GetGlobalState(
    INativeGlobalState::StateType eType)
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    GlobalState* pState = (*m_pspLightNode)->GetGlobalState(
        (GlobalState::StateType)eType);

    return ManagedObjectFactory::CreateGlobalState(pState);
}
//---------------------------------------------------------------------------
void ManagedLightNode::AttachGlobalState(INativeGlobalState^ thState)
{
    SE_NULL_ARGUMENT_CHECK(thState, "thState");
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    (*m_pspLightNode)->AttachGlobalState(thState->GetNativeGlobalState());
}
//---------------------------------------------------------------------------
void ManagedLightNode::DetachGlobalState(INativeGlobalState::StateType eType)
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    (*m_pspLightNode)->DetachGlobalState((GlobalState::StateType)eType);
}
//---------------------------------------------------------------------------
void ManagedLightNode::DetachAllGlobalStates()
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    (*m_pspLightNode)->DetachAllGlobalStates();
}
//---------------------------------------------------------------------------
int ManagedLightNode::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    return (*m_pspLightNode)->GetReferences();
}
//---------------------------------------------------------------------------
Spatial* ManagedLightNode::GetNativeSpatial()
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    return (Spatial*)(*m_pspLightNode);
}
//---------------------------------------------------------------------------
Node* ManagedLightNode::GetNativeNode()
{
    SE_NULL_REFERENCE_CHECK(m_pspLightNode, "Native pointer is null");
    return (Node*)(*m_pspLightNode);
}
//---------------------------------------------------------------------------