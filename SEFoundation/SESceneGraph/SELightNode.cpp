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

SE_IMPLEMENT_RTTI(Swing, SELightNode, SENode);
SE_IMPLEMENT_STREAM(SELightNode);

//SE_REGISTER_STREAM(SELightNode);

//----------------------------------------------------------------------------
SELightNode::SELightNode(SELight* pLight)
    :
    m_spLight(pLight)
{
    if( m_spLight )
    {
        Local.SetTranslate(m_spLight->Position);
        Local.SetRotate(SEMatrix3f(m_spLight->RVector, m_spLight->UVector,
            m_spLight->DVector));
    }
}
//----------------------------------------------------------------------------
SELightNode::~SELightNode()
{
}
//----------------------------------------------------------------------------
void SELightNode::SetLight(SELight* pLight)
{
    m_spLight = pLight;

    if( m_spLight )
    {
        Local.SetTranslate(m_spLight->Position);
        Local.SetRotate(SEMatrix3f(m_spLight->RVector, m_spLight->UVector,
            m_spLight->DVector));

        UpdateGS();
    }
}
//----------------------------------------------------------------------------
void SELightNode::UpdateWorldData(double dAppTime)
{
    SENode::UpdateWorldData(dAppTime);

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
SEObject* SELightNode::GetObjectByName(const std::string& rName)
{
    SEObject* pFound = SENode::GetObjectByName(rName);
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
void SELightNode::GetAllObjectsByName(const std::string& rName,
    std::vector<SEObject*>& rObjects)
{
    SENode::GetAllObjectsByName(rName, rObjects);

    if( m_spLight )
    {
        m_spLight->GetAllObjectsByName(rName, rObjects);
    }
}
//----------------------------------------------------------------------------
SEObject* SELightNode::GetObjectByID(unsigned int uiID)
{
    SEObject* pFound = SENode::GetObjectByID(uiID);
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
void SELightNode::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SENode::Load(rStream, pLink);

    // link data
    SEObject* pObject;
    rStream.Read(pObject);  // m_spLight
    pLink->Add(pObject);

    SE_END_DEBUG_STREAM_LOAD(SELightNode);
}
//----------------------------------------------------------------------------
void SELightNode::SELink(SEStream& rStream, SEStream::SELink* pLink)
{
    SENode::SELink(rStream, pLink);

    SEObject* pLinkID = pLink->GetLinkID();
    m_spLight = (SELight*)rStream.GetFromMap(pLinkID);
}
//----------------------------------------------------------------------------
bool SELightNode::Register(SEStream& rStream) const
{
    if( !SENode::Register(rStream) )
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
void SELightNode::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SENode::Save(rStream);

    // link data
    rStream.Write(m_spLight);

    SE_END_DEBUG_STREAM_SAVE(SELightNode);
}
//----------------------------------------------------------------------------
int SELightNode::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SENode::GetDiskUsed(rVersion) + sizeof(m_spLight);
}
//----------------------------------------------------------------------------
SEStringTree* SELightNode::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));

    // children
    pTree->Append(SENode::SaveStrings());
    if( m_spLight )
    {
        pTree->Append(m_spLight->SaveStrings());
    }

    return pTree;
}
//----------------------------------------------------------------------------
