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
#include "SEColladaTransformation.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SEColladaAnimation, SEObject);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEColladaAnimation, SEObject);

//----------------------------------------------------------------------------
SEColladaAnimation::SEColladaAnimation()
{
    NumAnimChannels = 0;
    AnimKeySets = 0;
    EndTime = 0.0f;
    SampleRate = 0.0f;

    Keys = 0;
    NumKeys = 0;

    HasRotation = false;
    HasTranslation = false;
    HasScale = false;
    HasSource = false;
    HasMatrix = false;
    FoundTarget = false;
}
//----------------------------------------------------------------------------
SEColladaAnimation::~SEColladaAnimation()
{
}
//----------------------------------------------------------------------------
void SEColladaAnimation::GenerateKeys()
{
    ToolSystem::DebugOutput("Generating Keys for Animation Channel %s", 
        GetName().c_str());

    // Allocating for generic key channels.
    AnimKeySets = SE_NEW SEColladaKeySet[NumAnimChannels];

    // Generate key frames for all the channels in this animation.
    int iAnimSetBase = 0;
    SEColladaAnimationChannel* pChannel = 0;
    for( int i = 0; i < (int)Channels.size(); i++ )
    {
        pChannel = Channels[i];
        SEColladaAnimationSource* pInputSource = pChannel->InputSource;
        SEColladaAnimationSource* pOutputSource = pChannel->OutputSource;
        int iKeyCount = pInputSource->Source->GetCount();
        
        for( int j = 0; j < pChannel->NumElementTargets; j++ )
        {
            AnimKeySets[iAnimSetBase + j].AllocateKeys(iKeyCount);
        }
        
        // Set the actual key info.
        for( int j = 0 ; j < iKeyCount; j++ )
        {
            // Fill in all the keys for each anim key set.
            int iElementTargetCount = pChannel->NumElementTargets;
            for( int k = 0; k < iElementTargetCount; k++ )
            {
                AnimKeySets[iAnimSetBase + k].Time[j] = 
                    (*pInputSource->Source)[j];
                AnimKeySets[iAnimSetBase + k].Keys[j] = 
                    (*pOutputSource->Source)[j*iElementTargetCount + k];
                
                // Update animation's end fTime.
                if( AnimKeySets[iAnimSetBase + k].Time[j] > EndTime )
                {
                    EndTime = AnimKeySets[iAnimSetBase + k].Time[j];
                }

                // Set the animKey in the channel for later interpolation.
                pChannel->Keys[k] = &AnimKeySets[iAnimSetBase + k];
            }
        }

        // Update the current iAnimSetBase index.
        iAnimSetBase += pChannel->NumElementTargets;
    }
}
//----------------------------------------------------------------------------
void SEColladaAnimation::Interp(float& rfValue, SEColladaKeySet* pKeySet, 
    float fTime)
{
    if( !pKeySet->Keys )
    {
        return;
    }

    if( fTime > pKeySet->Time[pKeySet->NumKeys-1] )
    {
        rfValue = pKeySet->Keys[pKeySet->NumKeys - 1];
    }
    else
    {
        rfValue = pKeySet->Keys[0];

        // Need to first find out where the fTime lies in the keys.
        int iNext = -1;
        int iPrev = -1;
        for( int i = 0; i < pKeySet->NumKeys - 1; i ++ )
        {
            if( fTime >= pKeySet->Time[i] && fTime < pKeySet->Time[i + 1] )
            {
                iPrev = i;
                iNext = i + 1;
                break;
            }
        }

        if( iPrev == -1 )
        {
            if( fTime < pKeySet->Time[0] )
            {
                rfValue = pKeySet->Keys[0];
            }
            else
            {
                // If fTime is not in range just set to last key value.
                rfValue = pKeySet->Keys[pKeySet->NumKeys - 1];
            }
        }
        else
        {	
            float fTSize = pKeySet->Time[iNext] - pKeySet->Time[iPrev];
            float fTDiff = fTime - pKeySet->Time[iPrev]; 
            float fTFactor = 1 - ((fTSize - fTDiff)/fTSize);
            
            float fVSize = pKeySet->Keys[iNext] - pKeySet->Keys[iPrev];
            rfValue = pKeySet->Keys[iPrev] + (fVSize*fTFactor);
        }
    }
}
//----------------------------------------------------------------------------
void SEColladaAnimation::AnimateChannel(SEColladaTransformation* pTransform, 
    SEColladaAnimationChannel::AnimationTarget eTarget, int i, float fTime)
{
    SEVector4f& rSRTData = pTransform->SRTData;

    switch( eTarget )
    {
    case SEColladaAnimationChannel::AT_TARGET_X:
    case SEColladaAnimationChannel::AT_S_X_AXIS:
    case SEColladaAnimationChannel::AT_T_X_AXIS:
        Interp(rSRTData.X, &AnimKeySets[i], fTime);
    break;

    case SEColladaAnimationChannel::AT_TARGET_Y:
    case SEColladaAnimationChannel::AT_S_Y_AXIS:
    case SEColladaAnimationChannel::AT_T_Y_AXIS:
        Interp(rSRTData.Y, &AnimKeySets[i], fTime);
    break;

    case SEColladaAnimationChannel::AT_TARGET_Z:
    case SEColladaAnimationChannel::AT_S_Z_AXIS:
    case SEColladaAnimationChannel::AT_T_Z_AXIS:
        Interp(rSRTData.Z, &AnimKeySets[i], fTime);
    break;

    case SEColladaAnimationChannel::AT_R_X_AXIS:
    case SEColladaAnimationChannel::AT_R_Y_AXIS:
    case SEColladaAnimationChannel::AT_R_Z_AXIS:
    case SEColladaAnimationChannel::AT_TARGET_ANGLE:
        Interp(rSRTData.W, &AnimKeySets[i], fTime);
    break;

    case SEColladaAnimationChannel::AT_T:
    case SEColladaAnimationChannel::AT_S:
    case SEColladaAnimationChannel::AT_TARGET_XYZ:
        Interp(rSRTData.X, &AnimKeySets[i    ], fTime);
        Interp(rSRTData.Y, &AnimKeySets[i + 1], fTime);
        Interp(rSRTData.Z, &AnimKeySets[i + 2], fTime);
        break;

    case SEColladaAnimationChannel::AT_MATRIX:
        // TODO:
        // Support this transformation.
        SE_ASSERT( false );
        break; 

    default:
        break;
    }
}
//----------------------------------------------------------------------------