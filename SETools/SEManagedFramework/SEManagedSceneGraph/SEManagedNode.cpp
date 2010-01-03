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
int ManagedNode::GetCount()
{
    return (*m_pspNode)->GetCount();
}
//---------------------------------------------------------------------------
int ManagedNode::AttachChild(INativeSpatial^ thSpatial)
{
    if( !thSpatial )
    {
        throw gcnew ArgumentNullException("thSpatial");
    }

    return (*m_pspNode)->AttachChild(thSpatial->GetNativeSpatial());
}
//---------------------------------------------------------------------------
int ManagedNode::DetachChild(INativeSpatial^ thSpatial)
{
    if( !thSpatial )
    {
        throw gcnew ArgumentNullException("thSpatial");
    }

    return (*m_pspNode)->DetachChild(thSpatial->GetNativeSpatial());
}
//---------------------------------------------------------------------------
void ManagedNode::UpdateGS(double dAppTime)
{
    (*m_pspNode)->UpdateGS(dAppTime);
}
//---------------------------------------------------------------------------
void ManagedNode::UpdateRS()
{
    (*m_pspNode)->UpdateRS();
}
//---------------------------------------------------------------------------
void ManagedNode::AttachEffect(INativeEffect^ thEffect)
{
    if( !thEffect )
    {
        throw gcnew ArgumentNullException("thEffect");
    }

    (*m_pspNode)->AttachEffect(thEffect->GetNativeEffect());
}
//---------------------------------------------------------------------------
void ManagedNode::DetachEffect(INativeEffect^ thEffect)
{
    if( !thEffect )
    {
        throw gcnew ArgumentNullException("thEffect");
    }

    (*m_pspNode)->DetachEffect(thEffect->GetNativeEffect());
}
//---------------------------------------------------------------------------
void ManagedNode::DetachAllEffects()
{
    (*m_pspNode)->DetachAllEffects();
}
//---------------------------------------------------------------------------
int ManagedNode::GetGlobalStateCount()
{
    return (*m_pspNode)->GetGlobalStateCount();
}
//---------------------------------------------------------------------------
INativeGlobalState^ ManagedNode::GetGlobalState(int i)
{
    GlobalState* pState = (*m_pspNode)->GetGlobalState(i);

    return ManagedObjectFactory::CreateGlobalState(pState);
}
//---------------------------------------------------------------------------
INativeGlobalState^ ManagedNode::GetGlobalState(
    INativeGlobalState::StateType eType)
{
    GlobalState* pState = (*m_pspNode)->GetGlobalState(
        (GlobalState::StateType)eType);

    return ManagedObjectFactory::CreateGlobalState(pState);
}
//---------------------------------------------------------------------------
void ManagedNode::AttachGlobalState(INativeGlobalState^ thState)
{
    if( !thState )
    {
        throw gcnew ArgumentNullException("thState");
    }

    (*m_pspNode)->AttachGlobalState(thState->GetNativeGlobalState());
}
//---------------------------------------------------------------------------
void ManagedNode::DetachGlobalState(INativeGlobalState::StateType eType)
{
    (*m_pspNode)->DetachGlobalState((GlobalState::StateType)eType);
}
//---------------------------------------------------------------------------
void ManagedNode::DetachAllGlobalStates()
{
    (*m_pspNode)->DetachAllGlobalStates();
}
//---------------------------------------------------------------------------
int ManagedNode::GetNativeReferences()
{
    return (*m_pspNode)->GetReferences();
}
//---------------------------------------------------------------------------
Spatial* ManagedNode::GetNativeSpatial()
{
    return (Spatial*)(*m_pspNode);
}
//---------------------------------------------------------------------------
Node* ManagedNode::GetNativeNode()
{
    return (Node*)(*m_pspNode);
}
//---------------------------------------------------------------------------