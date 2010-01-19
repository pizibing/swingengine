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

#pragma once

#include "SEINativeObject.h"
#include "SEINativeGlobalState.h"

namespace Swing{ namespace Tools{ namespace ManagedFramework{

//----------------------------------------------------------------------------
// Name:Managed stencil state class
// Description:
// Author:Sun Che
// Date:20100105
//----------------------------------------------------------------------------
public ref class ManagedStencilState sealed : INativeObject, 
    INativeGlobalState
{
public:
    ManagedStencilState(void);
    ~ManagedStencilState(void);

    enum class CompareFunction
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

    enum class OperationType
    {
        OT_KEEP,
        OT_ZERO,
        OT_REPLACE,
        OT_INCREMENT,
        OT_DECREMENT,
        OT_INVERT,
        OT_COUNT
    };

    // Properties.
    property bool Enabled
    {
        bool get(void);
        void set(bool bValue);
    }
    property CompareFunction Compare
    {
        CompareFunction get(void);
        void set(CompareFunction eValue);
    }
    property int Reference
    {
        int get(void);
        void set(int iValue);
    }
    property int Mask
    {
        int get(void);
        void set(int iValue);
    }
    property int WriteMask
    {
        int get(void);
        void set(int iValue);
    }
    property OperationType OnFail
    {
        OperationType get(void);
        void set(OperationType eValue);
    }
    property OperationType OnZFail
    {
        OperationType get(void);
        void set(OperationType eValue);
    }
    property OperationType OnZPass
    {
        OperationType get(void);
        void set(OperationType eValue);
    }

    // Implement INativeGlobalState interface.
    virtual INativeGlobalState::StateType GetStateType(void);

    // Implement INativeObject interface.
    virtual void SetName(String^ thName);
    virtual String^ GetName(void);
    //
    virtual int GetNativeReferences(void);

internal:
    [CLSCompliant(false)]
    ManagedStencilState(StencilState* pState);

    // Implement INativeGlobalState interface.
    [CLSCompliant(false)]
    virtual GlobalState* GetNativeGlobalState(void) = 
        INativeGlobalState::GetNativeGlobalState;

private:
    StencilStatePtr* m_pspStencilState;
};

}}}