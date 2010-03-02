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

#include "SEINativeEffect.h"
#include "SEINativeGlobalState.h"
#include "SEManagedMatrix3.h"
#include "SEManagedLight.h"

using namespace System;

namespace Swing{ namespace Tools{ namespace ManagedFramework{

//----------------------------------------------------------------------------
// Name:Spatial interface class
// Description:
// Author:Sun Che
// Date:20091230
//----------------------------------------------------------------------------
public interface class INativeSpatial
{
    // Local transformation.
    void SetLocalRotate(ManagedMatrix3f^ thRotate);
    ManagedMatrix3f^ GetLocalRotate(void);
    void SetLocalMatrix(ManagedMatrix3f^ thMatrix);
    ManagedMatrix3f^ GetLocalMatrix(void);
    void SetLocalTranslate(ManagedVector3f^ thTranslate);
    ManagedVector3f^ GetLocalTranslate(void);
    void SetLocalScale(ManagedVector3f^ thScale);
    ManagedVector3f^ GetLocalScale(void);
    void SetLocalUniformScale(float fScale);
    float GetLocalUniformScale(void);

    // Geometry state update entry point.
    void UpdateGS(double dAppTime);
    void UpdateGS(void);

    // Render state update entry point.
    void UpdateRS(void);

    // Light state access.
    int GetLightCount(void);
    ManagedLight^ GetLight(int i);
    void AttachLight(ManagedLight^ thLight);
    void DetachLight(ManagedLight^ thLight);
    void DetachAllLights(void);

    // Effect state access.
    int GetEffectCount(void);
    INativeEffect^ GetEffect(int i);
    void AttachEffect(INativeEffect^ thEffect);
    void DetachEffect(INativeEffect^ thEffect);
    void DetachAllEffects(void);

    // Global render state access.
    int GetGlobalStateCount(void);
    INativeGlobalState^ GetGlobalState(int i);
    INativeGlobalState^ GetGlobalState(INativeGlobalState::StateType eType);
    void AttachGlobalState(INativeGlobalState^ thState);
    void DetachGlobalState(INativeGlobalState::StateType eType);
    void DetachAllGlobalStates(void);

    // Parent access.
    INativeSpatial^ GetParent(void);

    [CLSCompliant(false)]
    Spatial* GetNativeSpatial(void);
};

}}}