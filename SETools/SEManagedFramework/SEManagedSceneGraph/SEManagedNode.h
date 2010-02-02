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
#include "SEINativeSpatial.h"
#include "SEINativeNode.h"

namespace Swing{ namespace Tools{ namespace ManagedFramework{

//----------------------------------------------------------------------------
// Name:Managed node class
// Description:
// Author:Sun Che
// Date:20091230
//----------------------------------------------------------------------------
public ref class ManagedNode sealed : INativeObject, INativeSpatial, 
    INativeNode
{
public:
    ManagedNode(void);
    ~ManagedNode(void);

    // If the given spatial derived object is in the hierarchy of this node
    // object, the return value is 'true', otherwise return 'false'.
    bool IsInHierarchy(INativeSpatial^ thSpatial);

    // Hierarchical normal generation.
    void GenerateNormalsForAll(void);

    // Hierarchical effect detachment.
    void DetachAllEffectsForAll(void);

    // Hierarchical effect adjusting.
    void ModulateWithLightingEffectForAll(void);

    // Hierarchical shallow copying.
    ManagedNode^ Clone(void);

    // Implement INativeNode interface.
    virtual int GetCount(void) = INativeNode::GetCount;
    virtual int AttachChild(INativeSpatial^ thSpatial);
    virtual int DetachChild(INativeSpatial^ thSpatial);
    virtual INativeSpatial^ GetChild(int i);

    // Implement INativeSpatial interface.
    virtual void SetLocalRotate(ManagedMatrix3f^ thRotate);
    virtual ManagedMatrix3f^ GetLocalRotate(void);
    virtual void SetLocalMatrix(ManagedMatrix3f^ thMatrix);
    virtual ManagedMatrix3f^ GetLocalMatrix(void);
    virtual void SetLocalTranslate(ManagedVector3f^ thTranslate);
    virtual ManagedVector3f^ GetLocalTranslate(void);
    virtual void SetLocalScale(ManagedVector3f^ thScale);
    virtual ManagedVector3f^ GetLocalScale(void);
    virtual void SetLocalUniformScale(float fScale);
    virtual float GetLocalUniformScale(void);
    //
    virtual void UpdateGS(double dAppTime);
    //
    virtual void UpdateRS(void);
    //
    virtual int GetLightCount(void);
    virtual ManagedLight^ GetLight(int i);
    virtual void AttachLight(ManagedLight^ thLight);
    virtual void DetachLight(ManagedLight^ thLight);
    virtual void DetachAllLights(void);
    //
    virtual int GetEffectCount(void);
    virtual INativeEffect^ GetEffect(int i);
    virtual void AttachEffect(INativeEffect^ thEffect);
    virtual void DetachEffect(INativeEffect^ thEffect);
    virtual void DetachAllEffects(void);
    //
    virtual int GetGlobalStateCount(void);
    virtual INativeGlobalState^ GetGlobalState(int i);
    virtual INativeGlobalState^ GetGlobalState(
        INativeGlobalState::StateType eType);
    virtual void AttachGlobalState(INativeGlobalState^ thState);
    virtual void DetachGlobalState(INativeGlobalState::StateType eType);
    virtual void DetachAllGlobalStates(void);
    //
    virtual INativeSpatial^ GetParent(void);

    // Implement INativeObject interface.
    virtual void SetName(String^ thName);
    virtual String^ GetName(void);
    //
    virtual int GetNativeReferences(void);

internal:
    [CLSCompliant(false)]
    ManagedNode(Node* pNode);

    // Implement INativeSpatial interface.
    [CLSCompliant(false)]
    virtual Spatial* GetNativeSpatial(void) = INativeSpatial::GetNativeSpatial;

    // Implement INativeNode interface.
    [CLSCompliant(false)]
    virtual Node* GetNativeNode(void) = INativeNode::GetNativeNode;

private:
    NodePtr* m_pspNode;
};

}}}