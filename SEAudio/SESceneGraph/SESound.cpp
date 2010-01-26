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
#include "SESound.h"
#include "SECuller.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, Sound, Spatial);
SE_IMPLEMENT_STREAM(Sound);

//SE_REGISTER_STREAM(Sound);

//----------------------------------------------------------------------------
Sound::Sound()
    :
    ModelBound(BoundingVolume::Create())
{
    Culling = Spatial::CULL_NEVER;
    Pitch = 1.0f;
    Gain = 1.0f;
    RollOffRate = 1.0f;
    Looping = false;
}
//----------------------------------------------------------------------------
Sound::Sound(SoundBuffer* pSBuffer)
    :
    SBuffer(pSBuffer),
    ModelBound(BoundingVolume::Create())
{
    Culling = Spatial::CULL_NEVER;
    Pitch = 1.0f;
    Gain = 1.0f;
    RollOffRate = 1.0f;
    Looping = false;
}
//----------------------------------------------------------------------------
Sound::~Sound()
{
    // 通知所有使用此Sound的audio renderer,资源即将被释放,
    // 从而允许audio renderer释放与此Sound有关的资源.
    Release();
}
//----------------------------------------------------------------------------
void Sound::UpdateWorldData(double dAppTime)
{
    Spatial::UpdateWorldData(dAppTime);

    UpdateParams();
}
//----------------------------------------------------------------------------
void Sound::UpdateWorldBound()
{
    ModelBound->TransformBy(World, WorldBound);
}
//----------------------------------------------------------------------------
void Sound::UpdateState(std::vector<GlobalState*>*, std::vector<Light*>*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void Sound::GetUnculledSet(Culler& rCuller, bool)
{
    rCuller.Insert(this, 0, true);
}
//----------------------------------------------------------------------------
Sound::PickRecord::PickRecord(Sound* pIObject, float fT)
    :
    Spatial::PickRecord(pIObject, fT)
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
Object* Sound::GetObjectByName(const std::string& rName)
{
    Object* pFound = Spatial::GetObjectByName(rName);
    if( pFound )
    {
        return pFound;
    }

    if( ModelBound )
    {
        pFound = ModelBound->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    if( SBuffer )
    {
        pFound = SBuffer->GetObjectByName(rName);
        if( pFound )
        {
            return pFound;
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void Sound::GetAllObjectsByName(const std::string& rName,
    std::vector<Object*>& rObjects)
{
    Spatial::GetAllObjectsByName(rName, rObjects);

    if( ModelBound )
    {
        ModelBound->GetAllObjectsByName(rName, rObjects);
    }

    if( SBuffer )
    {
        SBuffer->GetAllObjectsByName(rName, rObjects);
    }
}
//----------------------------------------------------------------------------
Object* Sound::GetObjectByID(unsigned int uiID)
{
    Object* pFound = Spatial::GetObjectByID(uiID);
    if( pFound )
    {
        return pFound;
    }

    if( ModelBound )
    {
        pFound = ModelBound->GetObjectByID(uiID);
        if( pFound )
        {
            return pFound;
        }
    }

    if( SBuffer )
    {
        pFound = SBuffer->GetObjectByID(uiID);
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
void Sound::Load(Stream& rStream, Stream::Link* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    Spatial::Load(rStream, pLink);

    // native data
    rStream.Read(Pitch);
    rStream.Read(Gain);
    rStream.Read(RollOffRate);
    rStream.Read(Looping);

    // link data
    Object* pObject;
    rStream.Read(pObject);  // ModelBound
    pLink->Add(pObject);

    rStream.Read(pObject);  // SBuffer
    pLink->Add(pObject);

    SE_END_DEBUG_STREAM_LOAD(Sound);
}
//----------------------------------------------------------------------------
void Sound::Link(Stream& rStream, Stream::Link* pLink)
{
    Spatial::Link(rStream, pLink);

    Object* pLinkID = pLink->GetLinkID();
    ModelBound = (BoundingVolume*)rStream.GetFromMap(pLinkID);

    pLinkID = pLink->GetLinkID();
    SBuffer = (SoundBuffer*)rStream.GetFromMap(pLinkID);
}
//----------------------------------------------------------------------------
bool Sound::Register(Stream& rStream) const
{
    if( !Spatial::Register(rStream) )
    {
        return false;
    }

    if( ModelBound )
    {
        ModelBound->Register(rStream);
    }

    if( SBuffer )
    {
        SBuffer->Register(rStream);
    }

    return true;
}
//----------------------------------------------------------------------------
void Sound::Save(Stream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    Spatial::Save(rStream);

    // native data
    rStream.Write(Pitch);
    rStream.Write(Gain);
    rStream.Write(RollOffRate);
    rStream.Write(Looping);

    // link data
    rStream.Write(ModelBound);
    rStream.Write(SBuffer);

    SE_END_DEBUG_STREAM_SAVE(Sound);
}
//----------------------------------------------------------------------------
int Sound::GetDiskUsed(const StreamVersion& rVersion) const
{
    return Spatial::GetDiskUsed(rVersion) +
        sizeof(Pitch) + sizeof(Gain) + sizeof(RollOffRate) + sizeof(Looping) +
        sizeof(ModelBound) + sizeof(SBuffer);
}
//----------------------------------------------------------------------------
StringTree* Sound::SaveStrings(const char*)
{
    StringTree* pTree = SE_NEW StringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("pitch = ", Pitch));
    pTree->Append(Format("gain = ", Gain));
    pTree->Append(Format("rolloff rate = ", RollOffRate));
    pTree->Append(Format("looping = ", Looping));

    // children
    pTree->Append(Spatial::SaveStrings());

    if( ModelBound )
    {
        pTree->Append(ModelBound->SaveStrings());
    }

    if( SBuffer )
    {
        pTree->Append(SBuffer->SaveStrings("sound sources"));
    }

    return pTree;
}
//----------------------------------------------------------------------------
