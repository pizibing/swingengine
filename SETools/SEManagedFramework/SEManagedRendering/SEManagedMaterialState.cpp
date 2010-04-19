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
#include "SEManagedMaterialState.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedMaterialState::ManagedMaterialState()
{
    m_pspMaterialState = SE_NEW SEMaterialStatePtr;
    (*m_pspMaterialState) = SE_NEW SEMaterialState;
}
//---------------------------------------------------------------------------
ManagedMaterialState::ManagedMaterialState(SEMaterialState* pState)
{
    m_pspMaterialState = SE_NEW SEMaterialStatePtr;
    (*m_pspMaterialState) = pState;
}
//---------------------------------------------------------------------------
ManagedMaterialState::~ManagedMaterialState()
{
    SE_DELETE m_pspMaterialState;
    m_pspMaterialState = 0;
}
//---------------------------------------------------------------------------
ManagedColorRGB^ ManagedMaterialState::Emissive::get()
{
    ManagedColorRGB^ thColor = gcnew ManagedColorRGB;

    SE_NULL_REFERENCE_CHECK(m_pspMaterialState, "Native pointer is null");
    thColor->FromColorRGB((*m_pspMaterialState)->Emissive);

    return thColor;
}
//---------------------------------------------------------------------------
void ManagedMaterialState::Emissive::set(ManagedColorRGB^ thColor)
{
    SE_NULL_ARGUMENT_CHECK(thColor, "thColor");
    SE_NULL_REFERENCE_CHECK(m_pspMaterialState, "Native pointer is null");
    thColor->ToColorRGB((*m_pspMaterialState)->Emissive);
}
//---------------------------------------------------------------------------
ManagedColorRGB^ ManagedMaterialState::Ambient::get()
{
    ManagedColorRGB^ thColor = gcnew ManagedColorRGB;

    SE_NULL_REFERENCE_CHECK(m_pspMaterialState, "Native pointer is null");
    thColor->FromColorRGB((*m_pspMaterialState)->Ambient);

    return thColor;
}
//---------------------------------------------------------------------------
void ManagedMaterialState::Ambient::set(ManagedColorRGB^ thColor)
{
    SE_NULL_ARGUMENT_CHECK(thColor, "thColor");
    SE_NULL_REFERENCE_CHECK(m_pspMaterialState, "Native pointer is null");
    thColor->ToColorRGB((*m_pspMaterialState)->Ambient);
}
//---------------------------------------------------------------------------
ManagedColorRGB^ ManagedMaterialState::Diffuse::get()
{
    ManagedColorRGB^ thColor = gcnew ManagedColorRGB;

    SE_NULL_REFERENCE_CHECK(m_pspMaterialState, "Native pointer is null");
    thColor->FromColorRGB((*m_pspMaterialState)->Diffuse);

    return thColor;
}
//---------------------------------------------------------------------------
void ManagedMaterialState::Diffuse::set(ManagedColorRGB^ thColor)
{
    SE_NULL_ARGUMENT_CHECK(thColor, "thColor");
    SE_NULL_REFERENCE_CHECK(m_pspMaterialState, "Native pointer is null");
    thColor->ToColorRGB((*m_pspMaterialState)->Diffuse);
}
//---------------------------------------------------------------------------
ManagedColorRGB^ ManagedMaterialState::Specular::get()
{
    ManagedColorRGB^ thColor = gcnew ManagedColorRGB;

    SE_NULL_REFERENCE_CHECK(m_pspMaterialState, "Native pointer is null");
    thColor->FromColorRGB((*m_pspMaterialState)->Specular);

    return thColor;
}
//---------------------------------------------------------------------------
void ManagedMaterialState::Specular::set(ManagedColorRGB^ thColor)
{
    SE_NULL_ARGUMENT_CHECK(thColor, "thColor");
    SE_NULL_REFERENCE_CHECK(m_pspMaterialState, "Native pointer is null");
    thColor->ToColorRGB((*m_pspMaterialState)->Specular);
}
//---------------------------------------------------------------------------
float ManagedMaterialState::Alpha::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspMaterialState, "Native pointer is null");
    return (*m_pspMaterialState)->Alpha;
}
//---------------------------------------------------------------------------
void ManagedMaterialState::Alpha::set(float fValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspMaterialState, "Native pointer is null");
    (*m_pspMaterialState)->Alpha = fValue;
}
//---------------------------------------------------------------------------
float ManagedMaterialState::Shininess::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspMaterialState, "Native pointer is null");
    return (*m_pspMaterialState)->Shininess;
}
//---------------------------------------------------------------------------
void ManagedMaterialState::Shininess::set(float fValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspMaterialState, "Native pointer is null");
    (*m_pspMaterialState)->Shininess = fValue;
}
//---------------------------------------------------------------------------
INativeGlobalState::StateType ManagedMaterialState::GetStateType()
{
    SE_NULL_REFERENCE_CHECK(m_pspMaterialState, "Native pointer is null");
    return (INativeGlobalState::StateType)(
        *m_pspMaterialState)->GetStateType();
}
//---------------------------------------------------------------------------
void ManagedMaterialState::SetName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspMaterialState, "Native pointer is null");

    const char* acName = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acName);
    ManagedUtility::FreeNativeCharBuffer(acName);
    (*m_pspMaterialState)->SetName(tempName);
}
//---------------------------------------------------------------------------
String^ ManagedMaterialState::GetName()
{
    SE_NULL_REFERENCE_CHECK(m_pspMaterialState, "Native pointer is null");
    return gcnew String((*m_pspMaterialState)->GetName().c_str());
}
//---------------------------------------------------------------------------
int ManagedMaterialState::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspMaterialState, "Native pointer is null");
    return (*m_pspMaterialState)->GetReferences();
}
//---------------------------------------------------------------------------
SEGlobalState* ManagedMaterialState::GetNativeGlobalState()
{
    SE_NULL_REFERENCE_CHECK(m_pspMaterialState, "Native pointer is null");
    return (SEGlobalState*)(*m_pspMaterialState);
}
//---------------------------------------------------------------------------