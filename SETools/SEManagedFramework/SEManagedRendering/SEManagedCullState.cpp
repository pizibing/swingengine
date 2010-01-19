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
#include "SEManagedCullState.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedCullState::ManagedCullState()
{
    m_pspCullState = SE_NEW CullStatePtr;
    (*m_pspCullState) = SE_NEW CullState;
}
//---------------------------------------------------------------------------
ManagedCullState::ManagedCullState(CullState* pState)
{
    m_pspCullState = SE_NEW CullStatePtr;
    (*m_pspCullState) = pState;
}
//---------------------------------------------------------------------------
ManagedCullState::~ManagedCullState()
{
    SE_DELETE m_pspCullState;
    m_pspCullState = 0;
}
//---------------------------------------------------------------------------
bool ManagedCullState::Enabled::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspCullState, "Native pointer is null");
    return (*m_pspCullState)->Enabled;
}
//---------------------------------------------------------------------------
void ManagedCullState::Enabled::set(bool bValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspCullState, "Native pointer is null");
    (*m_pspCullState)->Enabled = bValue;
}
//---------------------------------------------------------------------------
ManagedCullState::FrontMode ManagedCullState::FrontFace::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspCullState, "Native pointer is null");
    return (ManagedCullState::FrontMode)(*m_pspCullState)->FrontFace;
}
//---------------------------------------------------------------------------
void ManagedCullState::FrontFace::set(ManagedCullState::FrontMode eValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspCullState, "Native pointer is null");
    (*m_pspCullState)->FrontFace = (CullState::FrontMode)eValue;
}
//---------------------------------------------------------------------------
ManagedCullState::CullMode ManagedCullState::CullFace::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspCullState, "Native pointer is null");
    return (ManagedCullState::CullMode)(*m_pspCullState)->CullFace;
}
//---------------------------------------------------------------------------
void ManagedCullState::CullFace::set(ManagedCullState::CullMode eValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspCullState, "Native pointer is null");
    (*m_pspCullState)->CullFace = (CullState::CullMode)eValue;
}
//---------------------------------------------------------------------------
INativeGlobalState::StateType ManagedCullState::GetStateType()
{
    SE_NULL_REFERENCE_CHECK(m_pspCullState, "Native pointer is null");
    return (INativeGlobalState::StateType)(
        *m_pspCullState)->GetStateType();
}
//---------------------------------------------------------------------------
void ManagedCullState::SetName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspCullState, "Native pointer is null");

    const char* acName = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acName);
    ManagedUtility::FreeNativeCharBuffer(acName);
    (*m_pspCullState)->SetName(tempName);
}
//---------------------------------------------------------------------------
String^ ManagedCullState::GetName()
{
    SE_NULL_REFERENCE_CHECK(m_pspCullState, "Native pointer is null");
    return gcnew String((*m_pspCullState)->GetName().c_str());
}
//---------------------------------------------------------------------------
int ManagedCullState::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspCullState, "Native pointer is null");
    return (*m_pspCullState)->GetReferences();
}
//---------------------------------------------------------------------------
GlobalState* ManagedCullState::GetNativeGlobalState()
{
    SE_NULL_REFERENCE_CHECK(m_pspCullState, "Native pointer is null");
    return (GlobalState*)(*m_pspCullState);
}
//---------------------------------------------------------------------------