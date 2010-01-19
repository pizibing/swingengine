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
#include "SEManagedAlphaState.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedAlphaState::ManagedAlphaState()
{
    m_pspAlphaState = SE_NEW AlphaStatePtr;
    (*m_pspAlphaState) = SE_NEW AlphaState;
}
//---------------------------------------------------------------------------
ManagedAlphaState::ManagedAlphaState(AlphaState* pState)
{
    m_pspAlphaState = SE_NEW AlphaStatePtr;
    (*m_pspAlphaState) = pState;
}
//---------------------------------------------------------------------------
ManagedAlphaState::~ManagedAlphaState()
{
    SE_DELETE m_pspAlphaState;
    m_pspAlphaState = 0;
}
//---------------------------------------------------------------------------
bool ManagedAlphaState::BlendEnabled::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    return (*m_pspAlphaState)->BlendEnabled;
}
//---------------------------------------------------------------------------
void ManagedAlphaState::BlendEnabled::set(bool bValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    (*m_pspAlphaState)->BlendEnabled = bValue;
}
//---------------------------------------------------------------------------
ManagedAlphaState::SrcBlendMode ManagedAlphaState::SrcBlend::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    return (ManagedAlphaState::SrcBlendMode)(*m_pspAlphaState)->SrcBlend;
}
//---------------------------------------------------------------------------
void ManagedAlphaState::SrcBlend::set(ManagedAlphaState::SrcBlendMode eValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    (*m_pspAlphaState)->SrcBlend = (AlphaState::SrcBlendMode)eValue;
}
//---------------------------------------------------------------------------
ManagedAlphaState::DstBlendMode ManagedAlphaState::DstBlend::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    return (ManagedAlphaState::DstBlendMode)(*m_pspAlphaState)->DstBlend;
}
//---------------------------------------------------------------------------
void ManagedAlphaState::DstBlend::set(ManagedAlphaState::DstBlendMode eValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    (*m_pspAlphaState)->DstBlend = (AlphaState::DstBlendMode)eValue;
}
//---------------------------------------------------------------------------
bool ManagedAlphaState::TestEnabled::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    return (*m_pspAlphaState)->TestEnabled;
}
//---------------------------------------------------------------------------
void ManagedAlphaState::TestEnabled::set(bool bValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    (*m_pspAlphaState)->TestEnabled = bValue;
}
//---------------------------------------------------------------------------
ManagedAlphaState::TestMode ManagedAlphaState::Test::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    return (ManagedAlphaState::TestMode)(*m_pspAlphaState)->Test;
}
//---------------------------------------------------------------------------
void ManagedAlphaState::Test::set(ManagedAlphaState::TestMode eValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    (*m_pspAlphaState)->Test = (AlphaState::TestMode)eValue;
}
//---------------------------------------------------------------------------
float ManagedAlphaState::Reference::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    return (*m_pspAlphaState)->Reference;
}
//---------------------------------------------------------------------------
void ManagedAlphaState::Reference::set(float fValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    (*m_pspAlphaState)->Reference = fValue;
}
//---------------------------------------------------------------------------
ManagedColorRGBA^ ManagedAlphaState::ConstantColor::get()
{
    ManagedColorRGBA^ thColor = gcnew ManagedColorRGBA;

    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    thColor->FromColorRGBA((*m_pspAlphaState)->ConstantColor);

    return thColor;
}
//---------------------------------------------------------------------------
void ManagedAlphaState::ConstantColor::set(ManagedColorRGBA^ thColor)
{
    SE_NULL_ARGUMENT_CHECK(thColor, "thColor");
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    thColor->ToColorRGBA((*m_pspAlphaState)->ConstantColor);
}
//---------------------------------------------------------------------------
INativeGlobalState::StateType ManagedAlphaState::GetStateType()
{
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    return (INativeGlobalState::StateType)(
        *m_pspAlphaState)->GetStateType();
}
//---------------------------------------------------------------------------
void ManagedAlphaState::SetName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");

    const char* acName = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acName);
    ManagedUtility::FreeNativeCharBuffer(acName);
    (*m_pspAlphaState)->SetName(tempName);
}
//---------------------------------------------------------------------------
String^ ManagedAlphaState::GetName()
{
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    return gcnew String((*m_pspAlphaState)->GetName().c_str());
}
//---------------------------------------------------------------------------
int ManagedAlphaState::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    return (*m_pspAlphaState)->GetReferences();
}
//---------------------------------------------------------------------------
GlobalState* ManagedAlphaState::GetNativeGlobalState()
{
    SE_NULL_REFERENCE_CHECK(m_pspAlphaState, "Native pointer is null");
    return (GlobalState*)(*m_pspAlphaState);
}
//---------------------------------------------------------------------------