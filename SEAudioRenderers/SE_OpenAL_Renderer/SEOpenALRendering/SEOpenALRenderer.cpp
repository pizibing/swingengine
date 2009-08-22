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

#include "SEOpenALRendererPCH.h"
#include "SEOpenALRenderer.h"
#include "SEOpenALResources.h"
#include "SEListener.h"
#include "SESound.h"

using namespace Swing;

WaveCatalog* OpenALRenderer::ms_pWaveCatalog = 0;

SE_IMPLEMENT_INITIALIZE(OpenALRenderer);
SE_IMPLEMENT_TERMINATE(OpenALRenderer);

//SE_REGISTER_INITIALIZE(OpenALRenderer);
//SE_REGISTER_TERMINATE(OpenALRenderer);

//----------------------------------------------------------------------------
void OpenALRenderer::Initialize()
{
    ms_pWaveCatalog = SE_NEW WaveCatalog("Main");
    WaveCatalog::SetActive(ms_pWaveCatalog);
}
//----------------------------------------------------------------------------
void OpenALRenderer::Terminate()
{
    if( WaveCatalog::GetActive() == ms_pWaveCatalog )
    {
        WaveCatalog::SetActive(0);
    }
    SE_DELETE ms_pWaveCatalog;
}
//----------------------------------------------------------------------------
OpenALRenderer::OpenALRenderer()
{
}
//----------------------------------------------------------------------------
OpenALRenderer::~OpenALRenderer()
{
}
//----------------------------------------------------------------------------
void OpenALRenderer::InitializeState()
{
    alDistanceModel(AL_INVERSE_DISTANCE);
}
//----------------------------------------------------------------------------
void OpenALRenderer::OnMasterGainChange()
{
    SE_AL_BEGIN_DEBUG_ALAPI;
    alListenerf(AL_GAIN, (ALfloat)m_pListener->GetMasterGain());
    SE_AL_END_DEBUG_ALAPI;
}
//----------------------------------------------------------------------------
void OpenALRenderer::SetSoundParams(AudioResourceIdentifier* pID)
{
    SoundID* pResource = (SoundID*)pID;

    // 更新sound世界姿态.
    SetSoundFrame(pResource->ID, m_pSound);

    // 更新sound其他物理参数.
    SE_AL_BEGIN_DEBUG_ALAPI;
    alSourcef(pResource->ID, AL_PITCH, (ALfloat)m_pSound->Pitch);
    alSourcef(pResource->ID, AL_GAIN, (ALfloat)m_pSound->Gain);
    alSourcef(pResource->ID, AL_ROLLOFF_FACTOR,
        (ALfloat)m_pSound->RollOffRate);
    alSourcei(pResource->ID, AL_LOOPING, m_pSound->Looping);
    SE_AL_END_DEBUG_ALAPI;
}
//----------------------------------------------------------------------------
void OpenALRenderer::SetSoundFrame(unsigned int uiID, Sound* pSound)
{
    const Vector3f& rPos = pSound->World.GetTranslate();
    Vector3f vec3fDir;
    pSound->World.GetRotate().GetRow(2, vec3fDir);

    SE_AL_BEGIN_DEBUG_ALAPI;
    ALfloat afValue[3];
    afValue[0] = rPos.X;
    afValue[1] = rPos.Y;
    afValue[2] = -rPos.Z;
    alSourcefv(uiID, AL_POSITION, afValue);
    afValue[0] = vec3fDir.X;
    afValue[1] = vec3fDir.Y;
    afValue[2] = -vec3fDir.Z;
    alSourcefv(uiID, AL_DIRECTION, afValue);
    SE_AL_END_DEBUG_ALAPI;
}
//----------------------------------------------------------------------------