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
#include "SERenderStateBlock.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, RenderStateBlock, Object);
SE_IMPLEMENT_STREAM(RenderStateBlock);
SE_IMPLEMENT_DEFAULT_NAME_ID(RenderStateBlock, Object);

//SE_REGISTER_STREAM(RenderStateBlock);

//----------------------------------------------------------------------------
RenderStateBlock::RenderStateBlock()
{
    memset(States, 0, GlobalState::MAX_STATE_TYPE*sizeof(GlobalState*));
}
//----------------------------------------------------------------------------
RenderStateBlock::~RenderStateBlock()
{
    Release();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void RenderStateBlock::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    Object::Load(rStream, pLink);

    // link data
    Object* pObject;
    for( int i = 0; i < GlobalState::MAX_STATE_TYPE; i++ )
    {
        rStream.Read(pObject);  // States[i]
        pLink->Add(pObject);
    }

    SE_END_DEBUG_STREAM_LOAD(RenderStateBlock);
}
//----------------------------------------------------------------------------
void RenderStateBlock::Link(Stream& rStream, Stream::Link* pLink)
{
    Object::Link(rStream, pLink);

    Object* pLinkID;
    for( int i = 0; i < GlobalState::MAX_STATE_TYPE; i++ )
    {
        pLinkID = pLink->GetLinkID();
        States[i] = (GlobalState*)rStream.GetFromMap(pLinkID);
    }
}
//----------------------------------------------------------------------------
bool RenderStateBlock::Register(Stream& rStream) const
{
    if( !Object::Register(rStream) )
    {
        return false;
    }

    for( int i = 0; i < GlobalState::MAX_STATE_TYPE; i++ )
    {
        if( States[i] )
        {
            States[i]->Register(rStream);
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void RenderStateBlock::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    Object::Save(rStream);

    // link data
    for( int i = 0; i < GlobalState::MAX_STATE_TYPE; i++ )
    {
        rStream.Write(States[i]);
    }

    SE_END_DEBUG_STREAM_SAVE(RenderStateBlock);
}
//----------------------------------------------------------------------------
int RenderStateBlock::GetDiskUsed(const StreamVersion& rVersion) const
{
    return Object::GetDiskUsed(rVersion) +
        GlobalState::MAX_STATE_TYPE*sizeof(States[0]);
}
//----------------------------------------------------------------------------
StringTree* RenderStateBlock::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));

    // children
    pTree->Append(Object::SaveStrings());

    for( int i = 0; i < GlobalState::MAX_STATE_TYPE; i++ )
    {
        if( States[i] )
        {
            pTree->Append(States[i]->SaveStrings());
        }
    }

    return pTree;
}
//----------------------------------------------------------------------------
