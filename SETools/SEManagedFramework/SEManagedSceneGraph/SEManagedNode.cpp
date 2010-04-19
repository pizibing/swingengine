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
#include "SEManagedUtility.h"
#include "SEManagedObjectFactory.h"
#include "SEManagedTriMesh.h"
#include "SEManagedImage.h"
#include "SEManagedTextureTileEffect.h"
#include "SEManagedTextureTileL1Effect.h"
#include "SEManagedLight.h"
#include "SEManagedLightNode.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedNode::ManagedNode()
{
    m_pspNode = SE_NEW SENodePtr;
    (*m_pspNode) = SE_NEW SENode;
}
//---------------------------------------------------------------------------
ManagedNode::ManagedNode(SENode* pNode)
{
    m_pspNode = SE_NEW SENodePtr;
    (*m_pspNode) = pNode;
}
//---------------------------------------------------------------------------
ManagedNode::~ManagedNode()
{
    SE_DELETE m_pspNode;
    m_pspNode = 0;
}
//---------------------------------------------------------------------------
ManagedNode::CullingMode ManagedNode::Culling::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return (ManagedNode::CullingMode)(*m_pspNode)->Culling;
}
//---------------------------------------------------------------------------
void ManagedNode::Culling::set(ManagedNode::CullingMode eMode)
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    (*m_pspNode)->Culling = (SESpatial::CullingMode)eMode;
}
//---------------------------------------------------------------------------
bool ManagedNode::IsInHierarchy(INativeSpatial^ thSpatial)
{
    SE_NULL_ARGUMENT_CHECK(thSpatial, "thSpatial");
    Swing::SEObject* pFound = (*m_pspNode)->GetObjectByID(
        thSpatial->GetNativeSpatial()->GetID());

    return pFound ? true : false;
}
//---------------------------------------------------------------------------
void ManagedNode::GenerateNormalsForAll()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    ManagedUtility::GenerateNormalsForAll(*m_pspNode);
}
//---------------------------------------------------------------------------
void ManagedNode::DetachAllEffectsForAll()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    ManagedUtility::DetachAllEffectsForAll(*m_pspNode);
}
//---------------------------------------------------------------------------
void ManagedNode::ModulateWithLightingEffectForAll()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    ManagedUtility::ModulateWithLightingEffectForAll(*m_pspNode);
}
//---------------------------------------------------------------------------
void ManagedNode::MaterialTextureConditioner()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    ManagedUtility::MaterialTextureConditioner(*m_pspNode);
}
//---------------------------------------------------------------------------
void ManagedNode::DisableLightingConditioner()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    ManagedUtility::DisableLightingConditioner(*m_pspNode);
}
//---------------------------------------------------------------------------
void ManagedNode::ImageConditioner(ManagedImage^ thImage)
{
    SE_NULL_ARGUMENT_CHECK(thImage, "thImage");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    ManagedUtility::ImageConditioner(*m_pspNode, thImage->GetNativeImage());
}
//---------------------------------------------------------------------------
void ManagedNode::WallConditioner(ManagedTextureTileL1Effect^ thEffect)
{
    SE_NULL_ARGUMENT_CHECK(thEffect, "thEffect");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    ManagedUtility::WallConditioner(*m_pspNode, 
        (SETextureTileL1Effect*)thEffect->GetNativeEffect());
}
//---------------------------------------------------------------------------
ManagedNode^ ManagedNode::Clone()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    SENode* pClonedObject = ManagedUtility::CloneNode(*m_pspNode);

    return gcnew ManagedNode(pClonedObject);
}
//---------------------------------------------------------------------------
ManagedNode^ ManagedNode::Copy(bool bUniqueNames)
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    SEObjectPtr spCopiedObject = (*m_pspNode)->Copy(bUniqueNames);

    return gcnew ManagedNode((SENode*)(Swing::SEObject*)spCopiedObject);
}
//---------------------------------------------------------------------------
ManagedTriMesh^ ManagedNode::GetTriMeshByName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");

    const char* acBuffer = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acBuffer);
    ManagedUtility::FreeNativeCharBuffer(acBuffer);
    SETriMesh* pMesh = DynamicCast<SETriMesh>(
        (*m_pspNode)->GetObjectByName(tempName));
    if( pMesh )
    {
        return gcnew ManagedTriMesh(pMesh);
    }

    return nullptr;
}
//---------------------------------------------------------------------------
ManagedNode^ ManagedNode::GetNodeByName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");

    const char* acBuffer = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acBuffer);
    ManagedUtility::FreeNativeCharBuffer(acBuffer);
    SENode* pNode = DynamicCast<SENode>(
        (*m_pspNode)->GetObjectByName(tempName));
    if( pNode )
    {
        return gcnew ManagedNode(pNode);
    }

    return nullptr;
}
//---------------------------------------------------------------------------
ManagedTextureTileEffect^ ManagedNode::GetTextureTileEffectByName(
    String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");

    const char* acBuffer = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acBuffer);
    ManagedUtility::FreeNativeCharBuffer(acBuffer);
    SETextureTileEffect* pEffect = DynamicCast<SETextureTileEffect>(
        (*m_pspNode)->GetObjectByName(tempName));
    if( pEffect )
    {
        return gcnew ManagedTextureTileEffect(pEffect);
    }

    return nullptr;
}
//---------------------------------------------------------------------------
ManagedTextureTileL1Effect^ ManagedNode::GetTextureTileL1EffectByName(
    String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");

    const char* acBuffer = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acBuffer);
    ManagedUtility::FreeNativeCharBuffer(acBuffer);
    SETextureTileL1Effect* pEffect = DynamicCast<SETextureTileL1Effect>(
        (*m_pspNode)->GetObjectByName(tempName));
    if( pEffect )
    {
        return gcnew ManagedTextureTileL1Effect(pEffect);
    }

    return nullptr;
}
//---------------------------------------------------------------------------
ManagedLight^ ManagedNode::GetLightByName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");

    const char* acBuffer = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acBuffer);
    ManagedUtility::FreeNativeCharBuffer(acBuffer);
    SELight* pLight = DynamicCast<SELight>(
        (*m_pspNode)->GetObjectByName(tempName));
    if( pLight )
    {
        return gcnew ManagedLight(pLight);
    }

    return nullptr;
}
//---------------------------------------------------------------------------
ManagedLightNode^ ManagedNode::GetLightNodeByName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");

    const char* acBuffer = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acBuffer);
    ManagedUtility::FreeNativeCharBuffer(acBuffer);
    SELightNode* pLightNode = DynamicCast<SELightNode>(
        (*m_pspNode)->GetObjectByName(tempName));
    if( pLightNode )
    {
        return gcnew ManagedLightNode(pLightNode);
    }

    return nullptr;
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
INativeSpatial^ ManagedNode::GetChild(int i)
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    SESpatial* pChild = (*m_pspNode)->GetChild(i);
    return ManagedObjectFactory::CreateSpatialDerivedObject(pChild);
}
//---------------------------------------------------------------------------
void ManagedNode::SetLocalRotate(ManagedMatrix3f^ thRotate)
{
    SE_NULL_ARGUMENT_CHECK(thRotate, "thRotate");
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    SEMatrix3f mat3fRot;
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
    SEMatrix3f mat3fM;
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
    SEVector3f vec3fTrn;
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
    SEVector3f vec3fScl;
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
void ManagedNode::UpdateGS()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    (*m_pspNode)->UpdateGS();
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
int ManagedNode::GetEffectCount()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return (*m_pspNode)->GetEffectCount();
}
//---------------------------------------------------------------------------
INativeEffect^ ManagedNode::GetEffect(int i)
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return  ManagedObjectFactory::CreateEffectDerivedObject(
        (*m_pspNode)->GetEffect(i));
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
    SEGlobalState* pState = (*m_pspNode)->GetGlobalState(i);

    return ManagedObjectFactory::CreateGlobalStateObject(pState);
}
//---------------------------------------------------------------------------
INativeGlobalState^ ManagedNode::GetGlobalState(
    INativeGlobalState::StateType eType)
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    SEGlobalState* pState = (*m_pspNode)->GetGlobalState(
        (SEGlobalState::StateType)eType);

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
    (*m_pspNode)->DetachGlobalState((SEGlobalState::StateType)eType);
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
    SESpatial* pSpatial = (*m_pspNode)->GetParent();

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
SESpatial* ManagedNode::GetNativeSpatial()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return (SESpatial*)(*m_pspNode);
}
//---------------------------------------------------------------------------
SENode* ManagedNode::GetNativeNode()
{
    SE_NULL_REFERENCE_CHECK(m_pspNode, "Native pointer is null");
    return (SENode*)(*m_pspNode);
}
//---------------------------------------------------------------------------