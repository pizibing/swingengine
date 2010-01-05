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
// Name:Managed z-buffer state class
// Description:
// Author:Sun Che
// Date:20100105
//----------------------------------------------------------------------------
public ref class ManagedZBufferState sealed : INativeObject, 
    INativeGlobalState
{
public:
    ManagedZBufferState(void);
    ~ManagedZBufferState(void);

    enum class CompareMode
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

    // Properties.
    property bool Enabled
    {
        bool get(void);
        void set(bool bValue);
    }
    property bool Writable
    {
        bool get(void);
        void set(bool bValue);
    }
    property CompareMode Compare
    {
        CompareMode get(void);
        void set(CompareMode eValue);
    }

    // Implement INativeGlobalState interface.
    virtual INativeGlobalState::StateType GetStateType(void);

    // Implement INativeObject interface.
    virtual int GetNativeReferences(void);

internal:
    [CLSCompliant(false)]
    ManagedZBufferState(ZBufferState* pState);

    // Implement INativeGlobalState interface.
    [CLSCompliant(false)]
    virtual GlobalState* GetNativeGlobalState(void) = 
        INativeGlobalState::GetNativeGlobalState;

private:
    ZBufferStatePtr* m_pspZBufferState;
};

}}}