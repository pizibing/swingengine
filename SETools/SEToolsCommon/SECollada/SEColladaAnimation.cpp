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

#include "SEToolsCommonPCH.h"
#include "SEColladaAnimation.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, ColladaAnimationSource, Object);
SE_IMPLEMENT_DEFAULT_NAME_ID(ColladaAnimationSource, Object);

//----------------------------------------------------------------------------
ColladaAnimationSource::ColladaAnimationSource(void)
{
}
//----------------------------------------------------------------------------
ColladaAnimationSource::~ColladaAnimationSource(void)
{
}
//----------------------------------------------------------------------------

SE_IMPLEMENT_RTTI(Swing, ColladaAnimationSampler, Object);
SE_IMPLEMENT_DEFAULT_NAME_ID(ColladaAnimationSampler, Object);

//----------------------------------------------------------------------------
ColladaAnimationSampler::ColladaAnimationSampler(void)
{
}
//----------------------------------------------------------------------------
ColladaAnimationSampler::~ColladaAnimationSampler(void)
{
}
//----------------------------------------------------------------------------

SE_IMPLEMENT_RTTI(Swing, ColladaAnimationChannel, Object);
SE_IMPLEMENT_DEFAULT_NAME_ID(ColladaAnimationChannel, Object);

//----------------------------------------------------------------------------
ColladaAnimationChannel::ColladaAnimationChannel(void)
{
}
//----------------------------------------------------------------------------
ColladaAnimationChannel::~ColladaAnimationChannel(void)
{
}
//----------------------------------------------------------------------------

SE_IMPLEMENT_RTTI(Swing, ColladaAnimation, Object);
SE_IMPLEMENT_DEFAULT_NAME_ID(ColladaAnimation, Object);

//----------------------------------------------------------------------------
ColladaAnimation::ColladaAnimation(void)
{
}
//----------------------------------------------------------------------------
ColladaAnimation::~ColladaAnimation(void)
{
}
//----------------------------------------------------------------------------
void ColladaAnimation::GenerateKeys()
{
    ToolSystem::SE_DebugOutput("Generating Keys for Animation Channel %s", 
        (const char*)GetName());

    // Generate key frames for the channels in this animation.
    ColladaAnimationChannel* pChannel = Channels[0];

    // Allocating for generic key channels.
    AnimKeySets = SE_NEW ColladaKeySet[NumAnimChannels];

    int iAnimSet = 0; 
    for( int i = 0; i < (int)Channels.size(); i++ )
    {
        pChannel = Channels[i];
        ColladaAnimationSource* pInputSource = pChannel->InputSource;
        ColladaAnimationSource* pOutputSource = pChannel->OutputSource;
        int NumKeys = pInputSource->Source->GetCount();
        
        // New way.
        for ( int j = 0; j < pChannel->NumElementTargets; j++ )
        {
            AnimKeySets[iAnimSet + j].AllocateKeys(NumKeys);
        }
        
        // Set the actual key info.
        for( int i = 0 ; i < NumKeys; i++ )
        {
            // Fill in all the keys for each anim key set.
            int numCh = pChannel->NumElementTargets;

            for( int ch = 0; ch < pChannel->NumElementTargets; ch ++ )
            {
                AnimKeySets[iAnimSet + ch].Time[i] = (*pInputSource->Source)[i];
                AnimKeySets[iAnimSet + ch].Keys[i] = (*pOutputSource->Source)[i*numCh + ch];
                
                if( AnimKeySets[iAnimSet + ch].Time[i] > EndTime )
                {
                    EndTime = AnimKeySets[iAnimSet + ch].Time[i];
                }

                // Set the animKey in the channel for later interpolation.
                pChannel->Keys[ch] = &AnimKeySets[iAnimSet + ch];
            }
        }

        // Update the current iAnimSet.
        iAnimSet += pChannel->NumElementTargets;
    }
}
//----------------------------------------------------------------------------