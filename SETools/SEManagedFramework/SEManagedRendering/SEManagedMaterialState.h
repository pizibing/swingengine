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
#include "SEManagedColorRGB.h"

namespace Swing{ namespace Tools{ namespace ManagedFramework{

//----------------------------------------------------------------------------
// Name:Managed material state class
// Description:
// Author:Sun Che
// Date:20100104
//----------------------------------------------------------------------------
public ref class ManagedMaterialState sealed : INativeObject, 
    INativeGlobalState
{
public:
    ManagedMaterialState(void);
    ~ManagedMaterialState(void);

    // Properties.
    property ManagedColorRGB^ Emissive
    {
        ManagedColorRGB^ get(void);
        void set(ManagedColorRGB^ thColor);
    }
    property ManagedColorRGB^ Ambient
    {
        ManagedColorRGB^ get(void);
        void set(ManagedColorRGB^ thColor);
    }
    property ManagedColorRGB^ Diffuse
    {
        ManagedColorRGB^ get(void);
        void set(ManagedColorRGB^ thColor);
    }
    property ManagedColorRGB^ Specular
    {
        ManagedColorRGB^ get(void);
        void set(ManagedColorRGB^ thColor);
    }
    property float Alpha
    {
        float get(void);
        void set(float fValue);
    }
    property float Shininess
    {
        float get(void);
        void set(float fValue);
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
    ManagedMaterialState(MaterialState* pState);

    // Implement INativeGlobalState interface.
    [CLSCompliant(false)]
    virtual GlobalState* GetNativeGlobalState(void) = 
        INativeGlobalState::GetNativeGlobalState;

private:
    MaterialStatePtr* m_pspMaterialState;
};

}}}