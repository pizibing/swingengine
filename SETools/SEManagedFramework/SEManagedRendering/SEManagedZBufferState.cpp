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
#include "SEManagedZBufferState.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedZBufferState::ManagedZBufferState()
{
    m_pspZBufferState = SE_NEW SEZBufferStatePtr;
    (*m_pspZBufferState) = SE_NEW SEZBufferState;
}
//---------------------------------------------------------------------------
ManagedZBufferState::ManagedZBufferState(SEZBufferState* pState)
{
    m_pspZBufferState = SE_NEW SEZBufferStatePtr;
    (*m_pspZBufferState) = pState;
}
//---------------------------------------------------------------------------
ManagedZBufferState::~ManagedZBufferState()
{
    SE_DELETE m_pspZBufferState;
    m_pspZBufferState = 0;
}
//---------------------------------------------------------------------------
bool ManagedZBufferState::Enabled::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspZBufferState, "Native pointer is null");
    return (*m_pspZBufferState)->Enabled;
}
//---------------------------------------------------------------------------
void ManagedZBufferState::Enabled::set(bool bValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspZBufferState, "Native pointer is null");
    (*m_pspZBufferState)->Enabled = bValue;
}
//---------------------------------------------------------------------------
bool ManagedZBufferState::Writable::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspZBufferState, "Native pointer is null");
    return (*m_pspZBufferState)->Writable;
}
//---------------------------------------------------------------------------
void ManagedZBufferState::Writable::set(bool bValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspZBufferState, "Native pointer is null");
    (*m_pspZBufferState)->Writable = bValue;
}
//---------------------------------------------------------------------------
ManagedZBufferState::CompareMode ManagedZBufferState::Compare::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspZBufferState, "Native pointer is null");
    return (ManagedZBufferState::CompareMode)(*m_pspZBufferState)->Compare;
}
//---------------------------------------------------------------------------
void ManagedZBufferState::Compare::set(
    ManagedZBufferState::CompareMode eValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspZBufferState, "Native pointer is null");
    (*m_pspZBufferState)->Compare = (SEZBufferState::CompareMode)eValue;
}
//---------------------------------------------------------------------------
INativeGlobalState::StateType ManagedZBufferState::GetStateType()
{
    SE_NULL_REFERENCE_CHECK(m_pspZBufferState, "Native pointer is null");
    return (INativeGlobalState::StateType)(
        *m_pspZBufferState)->GetStateType();
}
//---------------------------------------------------------------------------
void ManagedZBufferState::SetName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspZBufferState, "Native pointer is null");

    const char* acName = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acName);
    ManagedUtility::FreeNativeCharBuffer(acName);
    (*m_pspZBufferState)->SetName(tempName);
}
//---------------------------------------------------------------------------
String^ ManagedZBufferState::GetName()
{
    SE_NULL_REFERENCE_CHECK(m_pspZBufferState, "Native pointer is null");
    return gcnew String((*m_pspZBufferState)->GetName().c_str());
}
//---------------------------------------------------------------------------
int ManagedZBufferState::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspZBufferState, "Native pointer is null");
    return (*m_pspZBufferState)->GetReferences();
}
//---------------------------------------------------------------------------
SEGlobalState* ManagedZBufferState::GetNativeGlobalState()
{
    SE_NULL_REFERENCE_CHECK(m_pspZBufferState, "Native pointer is null");
    return (SEGlobalState*)(*m_pspZBufferState);
}
//---------------------------------------------------------------------------