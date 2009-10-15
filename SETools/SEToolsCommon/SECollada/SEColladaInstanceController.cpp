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

#include "SEToolsCommonPCH.h"
#include "SEColladaInstanceController.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, ColladaInstanceController, Object);
SE_IMPLEMENT_DEFAULT_NAME_ID(ColladaInstanceController, Object);

//----------------------------------------------------------------------------
ColladaInstanceController::ColladaInstanceController(ControllerType eType,
    domController* pController, domNode* pSkeletonRoot, Node* pMeshRoot)
{
    m_eControllerType = eType;
    m_pController = pController;
    m_pSkeletonRoot = pSkeletonRoot;
    m_pMeshRoot = pMeshRoot;
}
//----------------------------------------------------------------------------
ColladaInstanceController::ColladaInstanceController()
{
}
//----------------------------------------------------------------------------
ColladaInstanceController::~ColladaInstanceController()
{
}
//----------------------------------------------------------------------------
ColladaInstanceController::ControllerType 
ColladaInstanceController::GetControllerType() const
{
    return m_eControllerType;
}
//----------------------------------------------------------------------------
domController* ColladaInstanceController::GetController()
{
    return m_pController;
}
//----------------------------------------------------------------------------
domNode* ColladaInstanceController::GetSkeletonRoot()
{
    return m_pSkeletonRoot;
}
//----------------------------------------------------------------------------
Node* ColladaInstanceController::GetMeshRoot()
{
    return m_pMeshRoot;
}
//----------------------------------------------------------------------------