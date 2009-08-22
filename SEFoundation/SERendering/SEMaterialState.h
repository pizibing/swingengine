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

#ifndef Swing_MaterialState_H
#define Swing_MaterialState_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEGlobalState.h"
#include "SEColorRGB.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:material state类
// 说明:
// 作者:Sun Che
// 时间:20080701
//----------------------------------------------------------------------------
class SE_FOUNDATION_API MaterialState : public GlobalState
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;
    SE_DECLARE_INITIALIZE;
    SE_DECLARE_TERMINATE;

public:
    virtual StateType GetStateType(void) const { return MATERIAL; }

    MaterialState(void);
    virtual ~MaterialState(void);

    ColorRGB Emissive;  // default: ColorRGB(0,0,0)
    ColorRGB Ambient;   // default: ColorRGB(0.2,0.2,0.2)
    ColorRGB Diffuse;   // default: ColorRGB(0.8,0.8,0.8)
    ColorRGB Specular;  // default: ColorRGB(0,0,0)
    float Alpha;        // default: 1
    float Shininess;    // default: 1
};

typedef SmartPointer<MaterialState> MaterialStatePtr;

}

#endif
