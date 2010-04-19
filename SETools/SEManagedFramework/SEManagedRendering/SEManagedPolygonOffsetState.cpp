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
#include "SEManagedPolygonOffsetState.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedPolygonOffsetState::ManagedPolygonOffsetState()
{
    m_pspPolygonOffsetState = SE_NEW SEPolygonOffsetStatePtr;
    (*m_pspPolygonOffsetState) = SE_NEW SEPolygonOffsetState;
}
//---------------------------------------------------------------------------
ManagedPolygonOffsetState::ManagedPolygonOffsetState(
    SEPolygonOffsetState* pState)
{
    m_pspPolygonOffsetState = SE_NEW SEPolygonOffsetStatePtr;
    (*m_pspPolygonOffsetState) = pState;
}
//---------------------------------------------------------------------------
ManagedPolygonOffsetState::~ManagedPolygonOffsetState()
{
    SE_DELETE m_pspPolygonOffsetState;
    m_pspPolygonOffsetState = 0;
}
//---------------------------------------------------------------------------
bool ManagedPolygonOffsetState::FillEnabled::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspPolygonOffsetState, 
        "Native pointer is null");
    return (*m_pspPolygonOffsetState)->FillEnabled;
}
//---------------------------------------------------------------------------
void ManagedPolygonOffsetState::FillEnabled::set(bool bValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspPolygonOffsetState, 
        "Native pointer is null");
    (*m_pspPolygonOffsetState)->FillEnabled = bValue;
}
//---------------------------------------------------------------------------
bool ManagedPolygonOffsetState::LineEnabled::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspPolygonOffsetState, 
        "Native pointer is null");
    return (*m_pspPolygonOffsetState)->LineEnabled;
}
//---------------------------------------------------------------------------
void ManagedPolygonOffsetState::LineEnabled::set(bool bValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspPolygonOffsetState, 
        "Native pointer is null");
    (*m_pspPolygonOffsetState)->LineEnabled = bValue;
}
//---------------------------------------------------------------------------
bool ManagedPolygonOffsetState::PointEnabled::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspPolygonOffsetState, 
        "Native pointer is null");
    return (*m_pspPolygonOffsetState)->PointEnabled;
}
//---------------------------------------------------------------------------
void ManagedPolygonOffsetState::PointEnabled::set(bool bValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspPolygonOffsetState, 
        "Native pointer is null");
    (*m_pspPolygonOffsetState)->PointEnabled = bValue;
}
//---------------------------------------------------------------------------
float ManagedPolygonOffsetState::Scale::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspPolygonOffsetState, 
        "Native pointer is null");
    return (*m_pspPolygonOffsetState)->Scale;
}
//---------------------------------------------------------------------------
void ManagedPolygonOffsetState::Scale::set(float fValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspPolygonOffsetState, 
        "Native pointer is null");
    (*m_pspPolygonOffsetState)->Scale = fValue;
}
//---------------------------------------------------------------------------
float ManagedPolygonOffsetState::Bias::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspPolygonOffsetState, 
        "Native pointer is null");
    return (*m_pspPolygonOffsetState)->Bias;
}
//---------------------------------------------------------------------------
void ManagedPolygonOffsetState::Bias::set(float fValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspPolygonOffsetState, 
        "Native pointer is null");
    (*m_pspPolygonOffsetState)->Bias = fValue;
}
//---------------------------------------------------------------------------
INativeGlobalState::StateType ManagedPolygonOffsetState::GetStateType()
{
    SE_NULL_REFERENCE_CHECK(m_pspPolygonOffsetState, 
        "Native pointer is null");
    return (INativeGlobalState::StateType)(
        *m_pspPolygonOffsetState)->GetStateType();
}
//---------------------------------------------------------------------------
void ManagedPolygonOffsetState::SetName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspPolygonOffsetState, 
        "Native pointer is null");

    const char* acName = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acName);
    ManagedUtility::FreeNativeCharBuffer(acName);
    (*m_pspPolygonOffsetState)->SetName(tempName);
}
//---------------------------------------------------------------------------
String^ ManagedPolygonOffsetState::GetName()
{
    SE_NULL_REFERENCE_CHECK(m_pspPolygonOffsetState, 
        "Native pointer is null");
    return gcnew String((*m_pspPolygonOffsetState)->GetName().c_str());
}
//---------------------------------------------------------------------------
int ManagedPolygonOffsetState::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspPolygonOffsetState, 
        "Native pointer is null");
    return (*m_pspPolygonOffsetState)->GetReferences();
}
//---------------------------------------------------------------------------
SEGlobalState* ManagedPolygonOffsetState::GetNativeGlobalState()
{
    SE_NULL_REFERENCE_CHECK(m_pspPolygonOffsetState, 
        "Native pointer is null");
    return (SEGlobalState*)(*m_pspPolygonOffsetState);
}
//---------------------------------------------------------------------------