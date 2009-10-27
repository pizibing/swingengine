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

#ifndef Swing_ColladaTransformation_H
#define Swing_ColladaTransformation_H

#include "SEToolsCommonLIB.h"
#include "SEToolsUtility.h"
#include "SEObject.h"
#include "SEColladaAnimation.h"
#include "SETransformation.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Name:COLLADA Transformation class
// Description:
// Author:Sun Che
// Date:20091026
//----------------------------------------------------------------------------
class SE_TOOLS_COMMON_API ColladaTransformation : public Object
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;

public:
    ColladaTransformation(void);
    ~ColladaTransformation(void);

    enum TransformType
    {
        TT_SCALE,
        TT_ROTATE,
        TT_TRANSLATE,
        TT_MATRIX,
        TT_LOOKAT,
        TT_SKEW,
        TT_UNKNOWN
    };

    TransformType TransType;

    // This will be used to store scale, rotation axis, or translation.
    Vector4f SRTData;

    // Transformation can be affected by a COLLADA animation object.
    ColladaAnimation* Animation;

    // Channel access.
    void AttachChannel(int iID);
    int GetChannelCount(void) const;
    int GetChannel(int i) const;

    // Get a Swing Engine transformation from this COLLADA transformation.
    Transformation ToTransformation(void);

    static TransformType GetTransformType(char* acType);

private:
    enum { MAX_CHANNEL_COUNT = 12 };
    int m_aiChannelID[MAX_CHANNEL_COUNT];
    int m_iChannelCount;
};

typedef SmartPointer<ColladaTransformation> ColladaTransformationPtr;

}

#endif