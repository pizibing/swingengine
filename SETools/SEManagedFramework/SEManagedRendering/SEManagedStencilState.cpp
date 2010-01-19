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
#include "SEManagedStencilState.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedStencilState::ManagedStencilState()
{
    m_pspStencilState = SE_NEW StencilStatePtr;
    (*m_pspStencilState) = SE_NEW StencilState;
}
//---------------------------------------------------------------------------
ManagedStencilState::ManagedStencilState(StencilState* pState)
{
    m_pspStencilState = SE_NEW StencilStatePtr;
    (*m_pspStencilState) = pState;
}
//---------------------------------------------------------------------------
ManagedStencilState::~ManagedStencilState()
{
    SE_DELETE m_pspStencilState;
    m_pspStencilState = 0;
}
//---------------------------------------------------------------------------
bool ManagedStencilState::Enabled::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    return (*m_pspStencilState)->Enabled;
}
//---------------------------------------------------------------------------
void ManagedStencilState::Enabled::set(bool bValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    (*m_pspStencilState)->Enabled = bValue;
}
//---------------------------------------------------------------------------
ManagedStencilState::CompareFunction ManagedStencilState::Compare::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    return (ManagedStencilState::CompareFunction)(
        *m_pspStencilState)->Compare;
}
//---------------------------------------------------------------------------
void ManagedStencilState::Compare::set(
    ManagedStencilState::CompareFunction eValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    (*m_pspStencilState)->Compare = (StencilState::CompareFunction)eValue;
}
//---------------------------------------------------------------------------
int ManagedStencilState::Reference::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    return (*m_pspStencilState)->Reference;
}
//---------------------------------------------------------------------------
void ManagedStencilState::Reference::set(int iValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    (*m_pspStencilState)->Reference = (unsigned int)iValue;
}
//---------------------------------------------------------------------------
int ManagedStencilState::Mask::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    return (int)(*m_pspStencilState)->Mask;
}
//---------------------------------------------------------------------------
void ManagedStencilState::Mask::set(int iValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    (*m_pspStencilState)->Mask = (unsigned int)iValue;
}
//---------------------------------------------------------------------------
int ManagedStencilState::WriteMask::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    return (int)(*m_pspStencilState)->WriteMask;
}
//---------------------------------------------------------------------------
void ManagedStencilState::WriteMask::set(int iValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    (*m_pspStencilState)->WriteMask = (unsigned int)iValue;
}
//---------------------------------------------------------------------------
ManagedStencilState::OperationType ManagedStencilState::OnFail::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    return (ManagedStencilState::OperationType)(*m_pspStencilState)->OnFail;
}
//---------------------------------------------------------------------------
void ManagedStencilState::OnFail::set(
    ManagedStencilState::OperationType eValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    (*m_pspStencilState)->OnFail = (StencilState::OperationType)eValue;
}
//---------------------------------------------------------------------------
ManagedStencilState::OperationType ManagedStencilState::OnZFail::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    return (ManagedStencilState::OperationType)(*m_pspStencilState)->OnZFail;
}
//---------------------------------------------------------------------------
void ManagedStencilState::OnZFail::set(
    ManagedStencilState::OperationType eValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    (*m_pspStencilState)->OnZFail = (StencilState::OperationType)eValue;
}
//---------------------------------------------------------------------------
ManagedStencilState::OperationType ManagedStencilState::OnZPass::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    return (ManagedStencilState::OperationType)(*m_pspStencilState)->OnZPass;
}
//---------------------------------------------------------------------------
void ManagedStencilState::OnZPass::set(
    ManagedStencilState::OperationType eValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    (*m_pspStencilState)->OnZPass = (StencilState::OperationType)eValue;
}
//---------------------------------------------------------------------------
INativeGlobalState::StateType ManagedStencilState::GetStateType()
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    return (INativeGlobalState::StateType)(
        *m_pspStencilState)->GetStateType();
}
//---------------------------------------------------------------------------
void ManagedStencilState::SetName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");

    const char* acName = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acName);
    ManagedUtility::FreeNativeCharBuffer(acName);
    (*m_pspStencilState)->SetName(tempName);
}
//---------------------------------------------------------------------------
String^ ManagedStencilState::GetName()
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    return gcnew String((*m_pspStencilState)->GetName().c_str());
}
//---------------------------------------------------------------------------
int ManagedStencilState::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    return (*m_pspStencilState)->GetReferences();
}
//---------------------------------------------------------------------------
GlobalState* ManagedStencilState::GetNativeGlobalState()
{
    SE_NULL_REFERENCE_CHECK(m_pspStencilState, "Native pointer is null");
    return (GlobalState*)(*m_pspStencilState);
}
//---------------------------------------------------------------------------