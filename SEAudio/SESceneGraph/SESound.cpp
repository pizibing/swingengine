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

SE_IMPLEMENT_RTTI(Swing, SESound, SESpatial);
SE_IMPLEMENT_STREAM(SESound);

//SE_REGISTER_STREAM(SESound);

//----------------------------------------------------------------------------
SESound::SESound()
    :
    ModelBound(SEBoundingVolume::Create())
{
    Culling = SESpatial::CULL_NEVER;
    Pitch = 1.0f;
    Gain = 1.0f;
    RollOffRate = 1.0f;
    Looping = false;
}
//----------------------------------------------------------------------------
SESound::SESound(SESoundBuffer* pSBuffer)
    :
    SBuffer(pSBuffer),
    ModelBound(SEBoundingVolume::Create())
{
    Culling = SESpatial::CULL_NEVER;
    Pitch = 1.0f;
    Gain = 1.0f;
    RollOffRate = 1.0f;
    Looping = false;
}
//----------------------------------------------------------------------------
SESound::~SESound()
{
    // 通知所有使用此SESound的audio renderer,资源即将被释放,
    // 从而允许audio renderer释放与此SESound有关的资源.
    Release();
}
//----------------------------------------------------------------------------
void SESound::UpdateWorldData(double dAppTime)
{
    SESpatial::UpdateWorldData(dAppTime);

    UpdateParams();
}
//----------------------------------------------------------------------------
void SESound::UpdateWorldBound()
{
    ModelBound->TransformBy(World, WorldBound);
}
//----------------------------------------------------------------------------
void SESound::UpdateState(std::vector<SEGlobalState*>*, 
    std::vector<SELight*>*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void SESound::GetUnculledSet(SECuller& rCuller, bool)
{
    rCuller.Insert(this, 0, true);
}
//----------------------------------------------------------------------------
SESound::SEPickRecord::SEPickRecord(SESound* pIObject, float fT)
    :
    SESpatial::SEPickRecord(pIObject, fT)
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
SEObject* SESound::GetObjectByName(const std::string& rName)
{
    SEObject* pFound = SESpatial::GetObjectByName(rName);
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
void SESound::GetAllObjectsByName(const std::string& rName,
    std::vector<SEObject*>& rObjects)
{
    SESpatial::GetAllObjectsByName(rName, rObjects);

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
SEObject* SESound::GetObjectByID(unsigned int uiID)
{
    SEObject* pFound = SESpatial::GetObjectByID(uiID);
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
void SESound::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SESpatial::Load(rStream, pLink);

    // native data
    rStream.Read(Pitch);
    rStream.Read(Gain);
    rStream.Read(RollOffRate);
    rStream.Read(Looping);

    // link data
    SEObject* pObject;
    rStream.Read(pObject);  // ModelBound
    pLink->Add(pObject);

    rStream.Read(pObject);  // SBuffer
    pLink->Add(pObject);

    SE_END_DEBUG_STREAM_LOAD(SESound);
}
//----------------------------------------------------------------------------
void SESound::Link(SEStream& rStream, SEStream::SELink* pLink)
{
    SESpatial::Link(rStream, pLink);

    SEObject* pLinkID = pLink->GetLinkID();
    ModelBound = (SEBoundingVolume*)rStream.GetFromMap(pLinkID);

    pLinkID = pLink->GetLinkID();
    SBuffer = (SESoundBuffer*)rStream.GetFromMap(pLinkID);
}
//----------------------------------------------------------------------------
bool SESound::Register(SEStream& rStream) const
{
    if( !SESpatial::Register(rStream) )
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
void SESound::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SESpatial::Save(rStream);

    // native data
    rStream.Write(Pitch);
    rStream.Write(Gain);
    rStream.Write(RollOffRate);
    rStream.Write(Looping);

    // link data
    rStream.Write(ModelBound);
    rStream.Write(SBuffer);

    SE_END_DEBUG_STREAM_SAVE(SESound);
}
//----------------------------------------------------------------------------
int SESound::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SESpatial::GetDiskUsed(rVersion) +
        sizeof(Pitch) + sizeof(Gain) + sizeof(RollOffRate) + sizeof(Looping) +
        sizeof(ModelBound) + sizeof(SBuffer);
}
//----------------------------------------------------------------------------
SEStringTree* SESound::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("pitch = ", Pitch));
    pTree->Append(Format("gain = ", Gain));
    pTree->Append(Format("rolloff rate = ", RollOffRate));
    pTree->Append(Format("looping = ", Looping));

    // children
    pTree->Append(SESpatial::SaveStrings());

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
