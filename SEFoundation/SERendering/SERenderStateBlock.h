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

#ifndef Swing_RenderStateBlock_H
#define Swing_RenderStateBlock_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEObject.h"
#include "SEBindable.h"
#include "SEGlobalState.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Name:Render state block class
// Description:用于支持DirectX 10的RenderState object资源模式,
//     同时支持旧式的DirectX 9/OpenGL2的SetRenderState函数命令模式.
// Author:Sun Che
// Date:20090524
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SERenderStateBlock : public SEObject, 
    public SEBindable
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    SERenderStateBlock(void);
    virtual ~SERenderStateBlock(void);

    SEGlobalStatePtr States[SEGlobalState::MAX_STATE_TYPE];
};

typedef SESmartPointer<SERenderStateBlock> SERenderStateBlockPtr;

}

#endif
