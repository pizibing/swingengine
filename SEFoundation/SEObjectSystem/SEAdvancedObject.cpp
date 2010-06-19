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
#include "SEAdvancedObject.h"
#include "SEController.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SEAdvancedObject, SEObject);
SE_IMPLEMENT_ABSTRACT_STREAM(SEAdvancedObject);

//SE_REGISTER_STREAM(SEAdvancedObject);

//----------------------------------------------------------------------------
SEAdvancedObject::SEAdvancedObject()
{
}
//----------------------------------------------------------------------------
SEAdvancedObject::~SEAdvancedObject()
{
    DetachAllControllers();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Controller
//----------------------------------------------------------------------------
void SEAdvancedObject::AttachController(SEController* pController)
{
    // controller本身不允许被施加controller,从而避免复杂的对象图关系,
    // 一旦允许controller被另一个controller控制,则可能带来潜在风险...
    if( IsDerived(SEController::TYPE) )
    {
        SE_ASSERT( false );

        return;
    }

    if( !pController )
    {
        SE_ASSERT( pController );

        return;
    }

    // 是否已经存在
    for( int i = 0; i < (int)m_Controllers.size(); i++ )
    {
        if( pController == m_Controllers[i] )
        {
            return;
        }
    }

    // 双向绑定,注意不要智能指针互指
    pController->SetObject(this);          // 非智能指针
    m_Controllers.push_back(pController);  // 智能指针
}
//----------------------------------------------------------------------------
void SEAdvancedObject::DetachController(SEController* pController)
{
    std::vector<SEObjectPtr>::iterator pIter = m_Controllers.begin();
    for( /**/; pIter != m_Controllers.end(); pIter++ )
    {
        if( pController == *pIter )
        {
            pController->SetObject(0);
            m_Controllers.erase(pIter);

            return;
        }
    }
}
//----------------------------------------------------------------------------
void SEAdvancedObject::DetachAllControllers()
{
    for( int i = 0; i < (int)m_Controllers.size(); i++ )
    {
        SEController* pController = StaticCast<SEController>(m_Controllers[i]);
        pController->SetObject(0);
    }
    m_Controllers.clear();
}
//----------------------------------------------------------------------------
bool SEAdvancedObject::UpdateControllers(double dAppTime)
{
    bool bSomeoneUpdated = false;
    for( int i = 0; i < (int)m_Controllers.size(); i++ )
    {
        SEController* pController = StaticCast<SEController>(m_Controllers[i]);

        if( pController->Update(dAppTime) )
        {
            bSomeoneUpdated = true;
        }
    }

    return bSomeoneUpdated;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
SEObject* SEAdvancedObject::GetObjectByName(const std::string& rName)
{
    SEObject* pFound = SEObject::GetObjectByName(rName);
    if( pFound )
    {
        return pFound;
    }

    for( int i = 0; i < (int)m_Controllers.size(); i++ )
    {
        if( m_Controllers[i] )
        {
            SEObject* pFound = m_Controllers[i]->GetObjectByName(rName);
            if( pFound )
            {
                return pFound;
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void SEAdvancedObject::GetAllObjectsByName(const std::string& rName, 
    std::vector<SEObject*>& rObjects)
{
    SEObject::GetAllObjectsByName(rName, rObjects);

    for( int i = 0; i < (int)m_Controllers.size(); i++ )
    {
        if( m_Controllers[i] )
        {
            m_Controllers[i]->GetAllObjectsByName(rName, rObjects);
        }
    }
}
//----------------------------------------------------------------------------
SEObject* SEAdvancedObject::GetObjectByID(unsigned int uiID)
{
    SEObject* pFound = SEObject::GetObjectByID(uiID);
    if( pFound )
    {
        return pFound;
    }

    for( int i = 0; i < (int)m_Controllers.size(); i++ )
    {
        if( m_Controllers[i] )
        {
            SEObject* pFound = m_Controllers[i]->GetObjectByID(uiID);
            if( pFound )
            {
                return pFound;
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SEAdvancedObject::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEObject::Load(rStream, pLink);

    // native data
    int iCount;
    rStream.Read(iCount);
    m_Controllers.resize(iCount);
    for( int i = 0; i < iCount; i++ )
    {
        SEObject* pObject;
        rStream.Read(pObject);
        pLink->Add(pObject);
    }

    SE_END_DEBUG_STREAM_LOAD(SEAdvancedObject);
}
//----------------------------------------------------------------------------
void SEAdvancedObject::Link(SEStream& rStream, SEStream::SELink* pLink)
{
    SEObject::Link(rStream, pLink);

    for( int i = 0; i < (int)m_Controllers.size(); i++ )
    {
        SEObject* pLinkID = pLink->GetLinkID();
        m_Controllers[i] = (SEController*)rStream.GetFromMap(pLinkID);
    }
}
//----------------------------------------------------------------------------
bool SEAdvancedObject::Register(SEStream& rStream) const
{
    if( !SEObject::Register(rStream) )
    {
        return false;
    }

    for( int i = 0; i < (int)m_Controllers.size(); i++ )
    {
        if( m_Controllers[i] )
        {
            m_Controllers[i]->Register(rStream);
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void SEAdvancedObject::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEObject::Save(rStream);

    // link data
    int iCount = (int)m_Controllers.size();
    rStream.Write(iCount);
    for( int i = 0; i < iCount; i++ )
    {
        rStream.Write(m_Controllers[i]);
    }

    SE_END_DEBUG_STREAM_SAVE(SEAdvancedObject);
}
//----------------------------------------------------------------------------
int SEAdvancedObject::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    int iSize = SEObject::GetDiskUsed(rVersion);
    iSize += sizeof(int) + ((int)m_Controllers.size())*
        SE_PTRSIZE(SEControllerPtr);

    return iSize;
}
//----------------------------------------------------------------------------
SEStringTree* SEAdvancedObject::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("controller count =", (int)m_Controllers.size()));

    // children
    pTree->Append(SEObject::SaveStrings());

    if( m_Controllers.size() > 0 )
    {
        SEStringTree* pCTree = SE_NEW SEStringTree;
        pCTree->Append(Format("controllers"));
        for( int i = 0; i < (int)m_Controllers.size(); i++ )
        {
            if( m_Controllers[i] )
            {
                pCTree->Append(m_Controllers[i]->SaveStrings());
            }
        }
        pTree->Append(pCTree);
    }

    return pTree;
}
//----------------------------------------------------------------------------