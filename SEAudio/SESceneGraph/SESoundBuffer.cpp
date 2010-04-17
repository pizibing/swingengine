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

#include "SEAudioPCH.h"
#include "SESoundBuffer.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SoundBuffer, SEObject);
SE_IMPLEMENT_STREAM(SoundBuffer);

//SE_REGISTER_STREAM(SoundBuffer);

//----------------------------------------------------------------------------
SoundBuffer::SoundBuffer(int iWCount, Wave** apWaves)
{
    SE_ASSERT( iWCount > 0 && apWaves );

    m_Waves.resize(iWCount);
    for( int i = 0; i < iWCount; i++ )
    {
        m_Waves[i] = apWaves[i];
    }
}
//----------------------------------------------------------------------------
SoundBuffer::SoundBuffer(const SoundBuffer* pSBuffer)
{
    SE_ASSERT( pSBuffer );

    m_Waves.resize(pSBuffer->m_Waves.size());
    for( int i = 0; i < (int)pSBuffer->m_Waves.size(); i++ )
    {
        m_Waves[i] = pSBuffer->m_Waves[i];
    }
}
//----------------------------------------------------------------------------
SoundBuffer::SoundBuffer()
{
}
//----------------------------------------------------------------------------
SoundBuffer::~SoundBuffer()
{
    // 通知所有使用此SBuffer的audio renderer,资源即将被释放,
    // 从而允许audio renderer释放与此SB有关的资源.
    Release();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
SEObject* SoundBuffer::GetObjectByName(const std::string& rName)
{
    SEObject* pFound = SEObject::GetObjectByName(rName);
    if( pFound )
    {
        return pFound;
    }

    for( int i = 0; i < (int)m_Waves.size(); i++ )
    {
        if( m_Waves[i] )
        {
            pFound = m_Waves[i]->GetObjectByName(rName);
            if( pFound )
            {
                return pFound;
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void SoundBuffer::GetAllObjectsByName(const std::string& rName,
    std::vector<SEObject*>& rObjects)
{
    SEObject::GetAllObjectsByName(rName, rObjects);

    for( int i = 0; i < (int)m_Waves.size(); i++ )
    {
        if( m_Waves[i] )
        {
            m_Waves[i]->GetAllObjectsByName(rName, rObjects);
        }
    }
}
//----------------------------------------------------------------------------
SEObject* SoundBuffer::GetObjectByID(unsigned int uiID)
{
    SEObject* pFound = SEObject::GetObjectByID(uiID);
    if( pFound )
    {
        return pFound;
    }

    for( int i = 0; i < (int)m_Waves.size(); i++ )
    {
        if( m_Waves[i] )
        {
            pFound = m_Waves[i]->GetObjectByID(uiID);
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
void SoundBuffer::Load(SEStream& rStream, SEStream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEObject::Load(rStream, pLink);

    // link data
    int iWCount;
    rStream.Read(iWCount);
    m_Waves.resize(iWCount);
    for( int i = 0; i < iWCount; i++ )
    {
        SEObject* pObject;
        rStream.Read(pObject);  // m_Waves[i]
        pLink->Add(pObject);
    }

    SE_END_DEBUG_STREAM_LOAD(SoundBuffer);
}
//----------------------------------------------------------------------------
void SoundBuffer::Link(SEStream& rStream, SEStream::Link* pLink)
{
    SEObject::Link(rStream, pLink);

    for( int i = 0; i < (int)m_Waves.size(); i++ )
    {
        SEObject* pLinkID = pLink->GetLinkID();
        m_Waves[i] = (Wave*)rStream.GetFromMap(pLinkID);
    }
}
//----------------------------------------------------------------------------
bool SoundBuffer::Register(SEStream& rStream) const
{
    if( !SEObject::Register(rStream) )
    {
        return false;
    }

    for( int i = 0; i < (int)m_Waves.size(); i++ )
    {
        if( m_Waves[i] )
        {
            m_Waves[i]->Register(rStream);
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void SoundBuffer::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEObject::Save(rStream);

    // link data
    int iWCount = (int)m_Waves.size();
    rStream.Write(iWCount);
    for( int i = 0; i < iWCount; i++ )
    {
        rStream.Write(m_Waves[i]);
    }

    SE_END_DEBUG_STREAM_SAVE(SoundBuffer);
}
//----------------------------------------------------------------------------
int SoundBuffer::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SEObject::GetDiskUsed(rVersion) +
        sizeof(int) + (int)m_Waves.size()*sizeof(m_Waves[0]);
}
//----------------------------------------------------------------------------
SEStringTree* SoundBuffer::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));

    // children
    pTree->Append(SEObject::SaveStrings());

    for( int i = 0; i < (int)m_Waves.size(); i++ )
    {
        pTree->Append(m_Waves[i]->SaveStrings());
    }

    return pTree;
}
//----------------------------------------------------------------------------
