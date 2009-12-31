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

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedNode::ManagedNode()
{
    // Create a smart pointer which will point to the native camera.
    m_pspNode = SE_NEW NodePtr;

    // Create the native node.
    (*m_pspNode) = SE_NEW Node;
}
//---------------------------------------------------------------------------
ManagedNode::~ManagedNode()
{
    SE_DELETE m_pspNode;
    m_pspNode = 0;
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