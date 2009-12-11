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

#ifndef Swing_ColladaAnimation_H
#define Swing_ColladaAnimation_H

#include "SEToolsCommonLIB.h"
#include "SEToolsUtility.h"
#include "SEObject.h"
#include "SEColladaAnimationSource.h"
#include "SEColladaAnimationSampler.h"
#include "SEColladaAnimationChannel.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Name:COLLADA Animation Key struct
// Description:
// Author:Sun Che
// Date:20090917
//----------------------------------------------------------------------------
struct SE_TOOLS_COMMON_API ColladaAnimationKey
{
    ColladaAnimationKey()
    {
        Time = 0; 
        HasRotation = false;  
        HasTranslation = false;  
    }

    float Time;
    bool HasRotation;
    bool HasTranslation;
};

//----------------------------------------------------------------------------
// Name:COLLADA Key Set struct
// Description:
// Author:Sun Che
// Date:20090917
//----------------------------------------------------------------------------
struct SE_TOOLS_COMMON_API ColladaKeySet
{
    ColladaKeySet()
    {
        NumKeys = 0; 
        Keys = 0;
        Time = 0; 
    }

    int NumKeys;
    float* Keys;
    float* Time;

    bool AllocateKeys(int nKeys)
    {
        Keys = SE_NEW float[nKeys];
        Time = SE_NEW float[nKeys];
        NumKeys = nKeys; 

        for( int i = 0; i < nKeys; i++ )
        {
            Keys[i] = 0;
        }
        return true; 
    }

    void DeallocateKeys()
    {
        SE_DELETE[] Keys;
        SE_DELETE[] Time;
    }
};

class ColladaTransformation;
//----------------------------------------------------------------------------
// Name:COLLADA Animation class
// Description:
// Author:Sun Che
// Date:20090916
//----------------------------------------------------------------------------
class SE_TOOLS_COMMON_API ColladaAnimation : public Object
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;

public:
    ColladaAnimation(void);
    ~ColladaAnimation(void);

    // Multiple elements can be targeted by one channel.
    int	NumAnimChannels;

    ColladaKeySet* AnimKeySets;
    float EndTime;

    float SampleRate;

    std::map<std::string, ColladaAnimationSamplerPtr> Samplers;
    std::map<std::string, ColladaAnimationSourcePtr> Sources;

    std::string TargetName;
    std::string TargetTransformName;
    std::string TargetTransformElementName;

    // Export data.
    ColladaAnimationKey* Keys;
    int	NumKeys;
    
    bool HasRotation;
    bool HasTranslation;
    bool HasScale;
    bool HasSource;
    bool HasMatrix;
    bool FoundTarget;

    std::vector<ColladaAnimationChannelPtr> Channels;

private:
    friend class ColladaScene;
    void GenerateKeys(void);

    void AnimateChannel(ColladaTransformation* pTransform, 
        ColladaAnimationChannel::AnimationTarget eTarget, int i, float fTime);

    void Interp(float& rfValue, ColladaKeySet* pKeySet, float fTime);
};

typedef SmartPointer<ColladaAnimation> ColladaAnimationPtr;

}

#endif