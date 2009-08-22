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

#ifndef Swing_StencilState_H
#define Swing_StencilState_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEGlobalState.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:stencil state类
// 说明:
// 作者:Sun Che
// 时间:20080701
//----------------------------------------------------------------------------
class SE_FOUNDATION_API StencilState : public GlobalState
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;
    SE_DECLARE_INITIALIZE;
    SE_DECLARE_TERMINATE;

public:
    virtual StateType GetStateType(void) const { return STENCIL; }

    StencilState(void);
    virtual ~StencilState(void);

    enum CompareFunction
    {
        CF_NEVER,
        CF_LESS,
        CF_EQUAL,
        CF_LEQUAL,
        CF_GREATER,
        CF_NOTEQUAL,
        CF_GEQUAL,
        CF_ALWAYS,
        CF_COUNT
    };

    enum OperationType
    {
        OT_KEEP,
        OT_ZERO,
        OT_REPLACE,
        OT_INCREMENT,
        OT_DECREMENT,
        OT_INVERT,
        OT_COUNT
    };

    bool Enabled;             // default: false
    CompareFunction Compare;  // default: CF_NEVER
    unsigned int Reference;   // default: 0
    unsigned int Mask;        // default: ~0
    unsigned int WriteMask;   // default: ~0
    OperationType OnFail;     // default: OT_KEEP
    OperationType OnZFail;    // default: OT_KEEP
    OperationType OnZPass;    // default: OT_KEEP

private:
    static const char* ms_pCompare[CF_COUNT];
    static const char* ms_pOperation[OT_COUNT];
};

typedef SmartPointer<StencilState> StencilStatePtr;

}

#endif
