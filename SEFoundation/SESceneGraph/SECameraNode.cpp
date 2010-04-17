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

#include "SEFoundationPCH.h"
#include "SECameraNode.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, CameraNode, Node);
SE_IMPLEMENT_STREAM(CameraNode);

//SE_REGISTER_STREAM(CameraNode);

//----------------------------------------------------------------------------
CameraNode::CameraNode(Camera* pCamera)
    :
    m_spCamera(pCamera)
{
    if( m_spCamera )
    {
        Local.SetTranslate(m_spCamera->GetLocation());
        Local.SetRotate(SEMatrix3f(m_spCamera->GetRVector(),
            m_spCamera->GetUVector(), m_spCamera->GetDVector()));
    }
}
//----------------------------------------------------------------------------
CameraNode::~CameraNode()
{
}
//----------------------------------------------------------------------------
void CameraNode::SetCamera(Camera* pCamera)
{
    m_spCamera = pCamera;

    if( m_spCamera )
    {
        Local.SetTranslate(m_spCamera->GetLocation());
        Local.SetRotate(SEMatrix3f(m_spCamera->GetRVector(),
            m_spCamera->GetUVector(), m_spCamera->GetDVector()));

        UpdateGS();
    }
}
//----------------------------------------------------------------------------
void CameraNode::UpdateWorldData(double dAppTime)
{
    Node::UpdateWorldData(dAppTime);

    if( m_spCamera )
    {
        SEVector3f vec3fR, vec3fU, vec3fD;
        World.GetRotate().GetRow(0, vec3fR);
        World.GetRotate().GetRow(1, vec3fU);
        World.GetRotate().GetRow(2, vec3fD);
        m_spCamera->SetFrame(World.GetTranslate(), vec3fR, vec3fU, vec3fD);
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
SEObject* CameraNode::GetObjectByName(const std::string& rName)
{
    SEObject* pFound = Node::GetObjectByName(rName);
    if( pFound )
    {
        return pFound;
    }

    if( m_spCamera )
    {
        pFound = m_spCamera->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void CameraNode::GetAllObjectsByName(const std::string& rName,
    std::vector<SEObject*>& rObjects)
{
    Node::GetAllObjectsByName(rName, rObjects);

    if( m_spCamera )
    {
        m_spCamera->GetAllObjectsByName(rName, rObjects);
    }
}
//----------------------------------------------------------------------------
SEObject* CameraNode::GetObjectByID(unsigned int uiID)
{
    SEObject* pFound = Node::GetObjectByID(uiID);
    if( pFound )
    {
        return pFound;
    }

    if( m_spCamera )
    {
        pFound = m_spCamera->GetObjectByID(uiID);
        if( pFound )
        {
            return pFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void CameraNode::Load(SEStream& rStream, SEStream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    Node::Load(rStream, pLink);

    // link data
    SEObject* pObject;
    rStream.Read(pObject);  // m_spCamera
    pLink->Add(pObject);

    SE_END_DEBUG_STREAM_LOAD(CameraNode);
}
//----------------------------------------------------------------------------
void CameraNode::Link(SEStream& rStream, SEStream::Link* pLink)
{
    Node::Link(rStream, pLink);

    SEObject* pLinkID = pLink->GetLinkID();
    m_spCamera = (Camera*)rStream.GetFromMap(pLinkID);
}
//----------------------------------------------------------------------------
bool CameraNode::Register(SEStream& rStream) const
{
    if( !Node::Register(rStream) )
    {
        return false;
    }

    if( m_spCamera )
    {
        m_spCamera->Register(rStream);
    }

    return true;
}
//----------------------------------------------------------------------------
void CameraNode::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    Node::Save(rStream);

    // link data
    rStream.Write(m_spCamera);

    SE_END_DEBUG_STREAM_SAVE(CameraNode);
}
//----------------------------------------------------------------------------
int CameraNode::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return Node::GetDiskUsed(rVersion) + sizeof(m_spCamera);
}
//----------------------------------------------------------------------------
SEStringTree* CameraNode::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));

    // children
    pTree->Append(Node::SaveStrings());
    if( m_spCamera )
    {
        pTree->Append(m_spCamera->SaveStrings());
    }

    return pTree;
}
//----------------------------------------------------------------------------
