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
#include "SELightNode.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, LightNode, Node);
SE_IMPLEMENT_STREAM(LightNode);

//SE_REGISTER_STREAM(LightNode);

//----------------------------------------------------------------------------
LightNode::LightNode(Light* pLight)
    :
    m_spLight(pLight)
{
    if( m_spLight )
    {
        Local.SetTranslate(m_spLight->Position);
        Local.SetRotate(Matrix3f(m_spLight->RVector, m_spLight->UVector,
            m_spLight->DVector));
    }
}
//----------------------------------------------------------------------------
LightNode::~LightNode()
{
}
//----------------------------------------------------------------------------
void LightNode::SetLight(Light* pLight)
{
    m_spLight = pLight;

    if( m_spLight )
    {
        Local.SetTranslate(m_spLight->Position);
        Local.SetRotate(Matrix3f(m_spLight->RVector, m_spLight->UVector,
            m_spLight->DVector));

        UpdateGS();
    }
}
//----------------------------------------------------------------------------
ObjectPtr LightNode::Clone()
{
    // TODO:
    // Impliment this function.
    return 0;
}
//----------------------------------------------------------------------------
void LightNode::UpdateWorldData(double dAppTime)
{
    Node::UpdateWorldData(dAppTime);

    if( m_spLight )
    {
        m_spLight->Position = World.GetTranslate();
        World.GetRotate().GetRow(0, m_spLight->RVector);
        World.GetRotate().GetRow(1, m_spLight->UVector);
        World.GetRotate().GetRow(2, m_spLight->DVector);
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
Object* LightNode::GetObjectByName(const std::string& rName)
{
    Object* pFound = Node::GetObjectByName(rName);
    if( pFound )
    {
        return pFound;
    }

    if( m_spLight )
    {
        pFound = m_spLight->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void LightNode::GetAllObjectsByName(const std::string& rName,
    std::vector<Object*>& rObjects)
{
    Node::GetAllObjectsByName(rName, rObjects);

    if( m_spLight )
    {
        m_spLight->GetAllObjectsByName(rName, rObjects);
    }
}
//----------------------------------------------------------------------------
Object* LightNode::GetObjectByID(unsigned int uiID)
{
    Object* pFound = Node::GetObjectByID(uiID);
    if( pFound )
    {
        return pFound;
    }

    if( m_spLight )
    {
        pFound = m_spLight->GetObjectByID(uiID);
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
void LightNode::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    Node::Load(rStream, pLink);

    // link data
    Object* pObject;
    rStream.Read(pObject);  // m_spLight
    pLink->Add(pObject);

    SE_END_DEBUG_STREAM_LOAD(LightNode);
}
//----------------------------------------------------------------------------
void LightNode::Link(Stream& rStream, Stream::Link* pLink)
{
    Node::Link(rStream, pLink);

    Object* pLinkID = pLink->GetLinkID();
    m_spLight = (Light*)rStream.GetFromMap(pLinkID);
}
//----------------------------------------------------------------------------
bool LightNode::Register(Stream& rStream) const
{
    if( !Node::Register(rStream) )
    {
        return false;
    }

    if( m_spLight )
    {
        m_spLight->Register(rStream);
    }

    return true;
}
//----------------------------------------------------------------------------
void LightNode::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    Node::Save(rStream);

    // link data
    rStream.Write(m_spLight);

    SE_END_DEBUG_STREAM_SAVE(LightNode);
}
//----------------------------------------------------------------------------
int LightNode::GetDiskUsed(const StreamVersion& rVersion) const
{
    return Node::GetDiskUsed(rVersion) + sizeof(m_spLight);
}
//----------------------------------------------------------------------------
StringTree* LightNode::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));

    // children
    pTree->Append(Node::SaveStrings());
    if( m_spLight )
    {
        pTree->Append(m_spLight->SaveStrings());
    }

    return pTree;
}
//----------------------------------------------------------------------------
