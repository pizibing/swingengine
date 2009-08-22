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

//----------------------------------------------------------------------------
// 资源开启与关闭.
//----------------------------------------------------------------------------
void OpenALRenderer::OnEnableSound(AudioResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void OpenALRenderer::OnDisableSound(AudioResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void OpenALRenderer::OnEnableSBuffer(AudioResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void OpenALRenderer::OnDisableSBuffer(AudioResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void OpenALRenderer::OnAttachSBuffer(AudioResourceIdentifier* pSoundID,
    AudioResourceIdentifier* pSBufferID)
{
    SoundID* pSoundResource = (SoundID*)pSoundID;
    SBufferID* pSBufferResource = (SBufferID*)pSBufferID;

    for( int i = 0; i < pSBufferResource->BufferCount; i++ )
    {
        Wave* pWave = pSBufferResource->SBufferObject->GetWave(i);
        if( pWave )
        {
            // attach this buffer to the source.
            SE_AL_BEGIN_DEBUG_ALAPI;
            alSourcei(pSoundResource->ID, AL_BUFFER,
                pSBufferResource->Buffers[i]);
            SE_AL_END_DEBUG_ALAPI;
        }
    }
}
//----------------------------------------------------------------------------