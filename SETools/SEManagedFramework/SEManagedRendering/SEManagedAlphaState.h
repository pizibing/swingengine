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
#include "SEManagedColorRGBA.h"

namespace Swing{ namespace Tools{ namespace ManagedFramework{

//----------------------------------------------------------------------------
// Name:Managed alpha state class
// Description:
// Author:Sun Che
// Date:20100104
//----------------------------------------------------------------------------
public ref class ManagedAlphaState sealed : INativeObject, 
    INativeGlobalState
{
public:
    ManagedAlphaState(void);
    ~ManagedAlphaState(void);

    enum class SrcBlendMode
    {
        SBF_ZERO,
        SBF_ONE,
        SBF_DST_COLOR,
        SBF_ONE_MINUS_DST_COLOR,
        SBF_SRC_ALPHA,
        SBF_ONE_MINUS_SRC_ALPHA,
        SBF_DST_ALPHA,
        SBF_ONE_MINUS_DST_ALPHA,
        SBF_SRC_ALPHA_SATURATE,
        SBF_CONSTANT_COLOR,
        SBF_ONE_MINUS_CONSTANT_COLOR,
        SBF_CONSTANT_ALPHA,
        SBF_ONE_MINUS_CONSTANT_ALPHA,
        SBF_COUNT
    };

    enum class DstBlendMode
    {
        DBF_ZERO,
        DBF_ONE,
        DBF_SRC_COLOR,
        DBF_ONE_MINUS_SRC_COLOR,
        DBF_SRC_ALPHA,
        DBF_ONE_MINUS_SRC_ALPHA,
        DBF_DST_ALPHA,
        DBF_ONE_MINUS_DST_ALPHA,
        DBF_CONSTANT_COLOR,
        DBF_ONE_MINUS_CONSTANT_COLOR,
        DBF_CONSTANT_ALPHA,
        DBF_ONE_MINUS_CONSTANT_ALPHA,
        DBF_COUNT
    };

    enum class TestMode
    {
        TF_NEVER,
        TF_LESS,
        TF_EQUAL,
        TF_LEQUAL,
        TF_GREATER,
        TF_NOTEQUAL,
        TF_GEQUAL,
        TF_ALWAYS,
        TF_COUNT
    };

    // Properties.
    property bool BlendEnabled
    {
        bool get(void);
        void set(bool bValue);
    }
    property SrcBlendMode SrcBlend
    {
        SrcBlendMode get(void);
        void set(SrcBlendMode eValue);
    }
    property DstBlendMode DstBlend
    {
        DstBlendMode get(void);
        void set(DstBlendMode eValue);
    }
    property bool TestEnabled
    {
        bool get(void);
        void set(bool bValue);
    }
    property TestMode Test
    {
        TestMode get(void);
        void set(TestMode eValue);
    }
    property float Reference
    {
        float get(void);
        void set(float fValue);
    }
    property ManagedColorRGBA^ ConstantColor
    {
        ManagedColorRGBA^ get(void);
        void set(ManagedColorRGBA^ thColor);
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
    ManagedAlphaState(AlphaState* pState);

    // Implement INativeGlobalState interface.
    [CLSCompliant(false)]
    virtual GlobalState* GetNativeGlobalState(void) = 
        INativeGlobalState::GetNativeGlobalState;

private:
    AlphaStatePtr* m_pspAlphaState;
};

}}}