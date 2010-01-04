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
#include "SEManagedTriMesh.h"
#include "SEManagedObjectFactory.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedTriMesh::ManagedTriMesh()
{
    m_pspTriMesh = SE_NEW TriMeshPtr;

    // TODO:
    // Create a trimesh object from native VB/IB objects.
}
//---------------------------------------------------------------------------
ManagedTriMesh::ManagedTriMesh(TriMesh* pTriMesh)
{
    m_pspTriMesh = SE_NEW TriMeshPtr;
    (*m_pspTriMesh) = pTriMesh;
}
//---------------------------------------------------------------------------
ManagedTriMesh::~ManagedTriMesh()
{
    SE_DELETE m_pspTriMesh;
    m_pspTriMesh = 0;
}
//---------------------------------------------------------------------------
void ManagedTriMesh::UpdateGS(double dAppTime)
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native resource disposed");
    (*m_pspTriMesh)->UpdateGS(dAppTime);
}
//---------------------------------------------------------------------------
void ManagedTriMesh::UpdateRS()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native resource disposed");
    (*m_pspTriMesh)->UpdateRS();
}
//---------------------------------------------------------------------------
void ManagedTriMesh::AttachEffect(INativeEffect^ thEffect)
{
    SE_NULL_ARGUMENT_CHECK(thEffect, "thEffect");
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native resource disposed");
    (*m_pspTriMesh)->AttachEffect(thEffect->GetNativeEffect());
}
//---------------------------------------------------------------------------
void ManagedTriMesh::DetachEffect(INativeEffect^ thEffect)
{
    SE_NULL_ARGUMENT_CHECK(thEffect, "thEffect");
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native resource disposed");
    (*m_pspTriMesh)->DetachEffect(thEffect->GetNativeEffect());
}
//---------------------------------------------------------------------------
void ManagedTriMesh::DetachAllEffects()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native resource disposed");
    (*m_pspTriMesh)->DetachAllEffects();
}
//---------------------------------------------------------------------------
int ManagedTriMesh::GetGlobalStateCount()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native resource disposed");

    return (*m_pspTriMesh)->GetGlobalStateCount();
}
//---------------------------------------------------------------------------
INativeGlobalState^ ManagedTriMesh::GetGlobalState(int i)
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native resource disposed");
    GlobalState* pState = (*m_pspTriMesh)->GetGlobalState(i);

    return ManagedObjectFactory::CreateGlobalState(pState);
}
//---------------------------------------------------------------------------
INativeGlobalState^ ManagedTriMesh::GetGlobalState(
    INativeGlobalState::StateType eType)
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native resource disposed");
    GlobalState* pState = (*m_pspTriMesh)->GetGlobalState(
        (GlobalState::StateType)eType);

    return ManagedObjectFactory::CreateGlobalState(pState);
}
//---------------------------------------------------------------------------
void ManagedTriMesh::AttachGlobalState(INativeGlobalState^ thState)
{
    SE_NULL_ARGUMENT_CHECK(thState, "thState");
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native resource disposed");
    (*m_pspTriMesh)->AttachGlobalState(thState->GetNativeGlobalState());
}
//---------------------------------------------------------------------------
void ManagedTriMesh::DetachGlobalState(INativeGlobalState::StateType eType)
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native resource disposed");
    (*m_pspTriMesh)->DetachGlobalState((GlobalState::StateType)eType);
}
//---------------------------------------------------------------------------
void ManagedTriMesh::DetachAllGlobalStates()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native resource disposed");
    (*m_pspTriMesh)->DetachAllGlobalStates();
}
//---------------------------------------------------------------------------
int ManagedTriMesh::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native resource disposed");

    return (*m_pspTriMesh)->GetReferences();
}
//---------------------------------------------------------------------------
Spatial* ManagedTriMesh::GetNativeSpatial()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native resource disposed");

    return (Spatial*)(*m_pspTriMesh);
}
//---------------------------------------------------------------------------
Geometry* ManagedTriMesh::GetNativeGeometry()
{
    SE_NULL_REFERENCE_CHECK(m_pspTriMesh, "Native resource disposed");

    return (Geometry*)(*m_pspTriMesh);
}
//---------------------------------------------------------------------------