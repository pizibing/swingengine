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
#include "SEManagedWireframeState.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedWireframeState::ManagedWireframeState()
{
    m_pspWireframeState = SE_NEW WireframeStatePtr;
    (*m_pspWireframeState) = SE_NEW WireframeState;
}
//---------------------------------------------------------------------------
ManagedWireframeState::ManagedWireframeState(WireframeState* pState)
{
    m_pspWireframeState = SE_NEW WireframeStatePtr;
    (*m_pspWireframeState) = pState;
}
//---------------------------------------------------------------------------
ManagedWireframeState::~ManagedWireframeState()
{
    SE_DELETE m_pspWireframeState;
    m_pspWireframeState = 0;
}
//---------------------------------------------------------------------------
bool ManagedWireframeState::Enabled::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspWireframeState, "Native pointer is null");
    return (*m_pspWireframeState)->Enabled;
}
//---------------------------------------------------------------------------
void ManagedWireframeState::Enabled::set(bool bValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspWireframeState, "Native pointer is null");
    (*m_pspWireframeState)->Enabled = bValue;
}
//---------------------------------------------------------------------------
INativeGlobalState::StateType ManagedWireframeState::GetStateType()
{
    SE_NULL_REFERENCE_CHECK(m_pspWireframeState, "Native pointer is null");
    return (INativeGlobalState::StateType)(
        *m_pspWireframeState)->GetStateType();
}
//---------------------------------------------------------------------------
int ManagedWireframeState::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspWireframeState, "Native pointer is null");
    return (*m_pspWireframeState)->GetReferences();
}
//---------------------------------------------------------------------------
GlobalState* ManagedWireframeState::GetNativeGlobalState()
{
    SE_NULL_REFERENCE_CHECK(m_pspWireframeState, "Native pointer is null");
    return (GlobalState*)(*m_pspWireframeState);
}
//---------------------------------------------------------------------------