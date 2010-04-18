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
#include "SESoundBuffer.h"

using namespace Swing;

ALenum SEOpenALRenderer::ms_aeWaveType[SEWave::WT_COUNT] =
{
    0,                     // WT_MONO4
    AL_FORMAT_MONO8,       // WT_MONO8
    AL_FORMAT_MONO16,      // WT_MONO16
    0,                     // WT_STEREO4
    AL_FORMAT_STEREO8,     // WT_STEREO8
    AL_FORMAT_STEREO16,    // WT_STEREO16
    0,                     // WT_QUAD16
    0,                     // WT_REAR16
    0,                     // WT_51CHN16
    0,                     // WT_61CHN16
    0                      // WT_71CHN16
};

//----------------------------------------------------------------------------
// 资源装载与释放.
//----------------------------------------------------------------------------
void SEOpenALRenderer::OnLoadSound(SEAudioResourceIdentifier*& rpID,
    SESound* pSound)
{
    SESoundID* pResource = SE_NEW SESoundID;
    pResource->SoundObject = pSound;
    rpID = pResource;

    SE_AL_BEGIN_DEBUG_ALAPI;
    alGenSources((ALsizei)1, &pResource->ID);
    SE_AL_END_DEBUG_ALAPI;
}
//----------------------------------------------------------------------------
void SEOpenALRenderer::OnReleaseSound(SEAudioResourceIdentifier* pID)
{
    SESoundID* pResource = (SESoundID*)pID;

    SE_AL_BEGIN_DEBUG_ALAPI;
    alSourceStop(pResource->ID);
    alDeleteSources((ALsizei)1, &pResource->ID);
    SE_AL_END_DEBUG_ALAPI;

    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
void SEOpenALRenderer::OnLoadSBuffer(SEAudioResourceIdentifier*& rpID,
    SESoundBuffer* pSBuffer)
{
    SESBufferID* pResource = SE_NEW SESBufferID;
    pResource->SBufferObject = pSBuffer;
    rpID = pResource;

    pResource->BufferCount = pSBuffer->GetWaveCount();
    pResource->Buffers = SE_NEW unsigned int[pResource->BufferCount];
    SE_AL_BEGIN_DEBUG_ALAPI;
    alGenBuffers((ALsizei)pResource->BufferCount, pResource->Buffers);
    SE_AL_END_DEBUG_ALAPI;

    for( int i = 0; i < pResource->BufferCount; i++ )
    {
        SEWave* pWave = pSBuffer->GetWave(i);
        if( pWave )
        {
            // load PCM wave data for this buffer.
            ALenum eFormat = ms_aeWaveType[pWave->GetFormat()];
            SE_AL_BEGIN_DEBUG_ALAPI;
            alBufferData(pResource->Buffers[i], eFormat,
                (const ALvoid*)pWave->GetData(), pWave->GetDataSize(),
                pWave->GetFrequency());
            SE_AL_END_DEBUG_ALAPI;
        }
    }
}
//----------------------------------------------------------------------------
void SEOpenALRenderer::OnReleaseSBuffer(SEAudioResourceIdentifier* pID)
{
    SESBufferID* pResource = (SESBufferID*)pID;

    SE_AL_BEGIN_DEBUG_ALAPI;
    alDeleteBuffers((ALsizei)pResource->BufferCount, pResource->Buffers);
    SE_AL_END_DEBUG_ALAPI;

    SE_DELETE[] pResource->Buffers;
    SE_DELETE pResource;
}
//----------------------------------------------------------------------------
