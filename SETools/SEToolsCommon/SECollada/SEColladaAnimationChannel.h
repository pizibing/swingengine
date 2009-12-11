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

#ifndef Swing_ColladaAnimationChannel_H
#define Swing_ColladaAnimationChannel_H

#include "SEToolsCommonLIB.h"
#include "SEToolsUtility.h"
#include "SEObject.h"
#include "SEColladaAnimationSource.h"
#include "SEColladaAnimationSampler.h"

namespace Swing
{

class ColladaKeySet;
//----------------------------------------------------------------------------
// Name:COLLADA Animation Channel class
// Description:
// Author:Sun Che
// Date:20090917
//----------------------------------------------------------------------------
class SE_TOOLS_COMMON_API ColladaAnimationChannel : public Object
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;

public:
    ColladaAnimationChannel(void);
    ~ColladaAnimationChannel(void);

    enum AnimationTarget
    {
        AT_TARGET_X,
        AT_TARGET_Y,
        AT_TARGET_Z,
        AT_TARGET_XYZ,
        AT_TARGET_ANGLE,

        AT_TARGET_UNKNOWN,

        AT_S_X_AXIS,
        AT_S_Y_AXIS,
        AT_S_Z_AXIS,
        AT_S,

        AT_R_X_AXIS,
        AT_R_Y_AXIS,
        AT_R_Z_AXIS,
        AT_R,

        AT_T_X_AXIS,
        AT_T_Y_AXIS,
        AT_T_Z_AXIS,
        AT_T,

        AT_SOURCE,
        AT_MATRIX
    };

    ColladaAnimationSamplerPtr Sampler;
    
    std::string TargetID;
    std::string TargetSID;
    std::string TargetMember;

    AnimationTarget TargetType;
    
    ColladaAnimationSourcePtr InputSource;
    ColladaAnimationSourcePtr OutputSource;

    enum { MAX_KEY_SETS = 10 };
    ColladaKeySet* Keys[MAX_KEY_SETS];
    int NumElementTargets;
};

typedef SmartPointer<ColladaAnimationChannel> ColladaAnimationChannelPtr;

}

#endif