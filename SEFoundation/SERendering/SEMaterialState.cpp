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
#include "SEMaterialState.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SEMaterialState, SEGlobalState);
SE_IMPLEMENT_STREAM(SEMaterialState);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEMaterialState, SEGlobalState);
SE_IMPLEMENT_INITIALIZE(SEMaterialState);
SE_IMPLEMENT_TERMINATE(SEMaterialState);

//SE_REGISTER_STREAM(SEMaterialState);
//SE_REGISTER_INITIALIZE(SEMaterialState);
//SE_REGISTER_TERMINATE(SEMaterialState);

//----------------------------------------------------------------------------
void SEMaterialState::Initialize()
{
    Default[MATERIAL] = SE_NEW SEMaterialState;
}
//----------------------------------------------------------------------------
void SEMaterialState::Terminate()
{
    Default[MATERIAL] = 0;
}
//----------------------------------------------------------------------------
SEMaterialState::SEMaterialState()
    :
    Emissive(0.0f,0.0f,0.0f),
    Ambient(0.2f,0.2f,0.2f),
    Diffuse(0.8f,0.8f,0.8f),
    Specular(0.0f,0.0f,0.0f)
{
    Alpha = 1.0f;
    Shininess = 1.0f;
}
//----------------------------------------------------------------------------
SEMaterialState::~SEMaterialState()
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SEMaterialState::Load (SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEGlobalState::Load(rStream, pLink);

    // native data
    rStream.Read(Emissive);
    rStream.Read(Ambient);
    rStream.Read(Diffuse);
    rStream.Read(Specular);
    rStream.Read(Alpha);
    rStream.Read(Shininess);

    SE_END_DEBUG_STREAM_LOAD(SEMaterialState);
}
//----------------------------------------------------------------------------
void SEMaterialState::Link(SEStream& rStream, SEStream::SELink* pLink)
{
    SEGlobalState::Link(rStream, pLink);
}
//----------------------------------------------------------------------------
bool SEMaterialState::Register(SEStream& rStream) const
{
    return SEGlobalState::Register(rStream);
}
//----------------------------------------------------------------------------
void SEMaterialState::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEGlobalState::Save(rStream);

    // native data
    rStream.Write(Emissive);
    rStream.Write(Ambient);
    rStream.Write(Diffuse);
    rStream.Write(Specular);
    rStream.Write(Alpha);
    rStream.Write(Shininess);

    SE_END_DEBUG_STREAM_SAVE(SEMaterialState);
}
//----------------------------------------------------------------------------
int SEMaterialState::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SEGlobalState::GetDiskUsed(rVersion) + sizeof(Emissive) +
        sizeof(Ambient) + sizeof(Diffuse) + sizeof(Specular) + sizeof(Alpha) +
        sizeof(Shininess);
}
//----------------------------------------------------------------------------
SEStringTree* SEMaterialState::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("emissive =", Emissive));
    pTree->Append(Format("ambient =", Ambient));
    pTree->Append(Format("diffuse =", Diffuse));
    pTree->Append(Format("alpha =", Alpha));
    pTree->Append(Format("shininess =", Shininess));

    // children
    pTree->Append(SEGlobalState::SaveStrings());

    return pTree;
}
//----------------------------------------------------------------------------
