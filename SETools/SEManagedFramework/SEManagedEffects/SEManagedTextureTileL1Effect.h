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
#include "SEINativeEffect.h"
#include "SEINativeShaderEffect.h"
#include "SEManagedImage.h"

namespace Swing{ namespace Tools{ namespace ManagedFramework{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20100318
//----------------------------------------------------------------------------
public ref class ManagedTextureTileL1Effect sealed : INativeObject, 
    INativeEffect, INativeShaderEffect
{
public:
    ManagedTextureTileL1Effect(String^ thTileName);
    ~ManagedTextureTileL1Effect(void);

    void SetTileImage(ManagedImage^ thImage);

    // Properties.
    property float TileX
    {
        float get(void);
        void set(float fValue);
    }
    property float TileY
    {
        float get(void);
        void set(float fValue);
    }
    property float AmbientWeight
    {
        float get(void);
        void set(float fValue);
    }
    property float DiffuseWeight
    {
        float get(void);
        void set(float fValue);
    }
    property float SpecularWeight
    {
        float get(void);
        void set(float fValue);
    }

    // Implement INativeShaderEffect interface.
    virtual ManagedAlphaState^ GetBlending(int iPass);
    //
    virtual ManagedTexture^ GetPTexture(int iPass, int i);
    virtual ManagedTexture^ GetPTexture(int iPass, String^ thName);
    virtual void SetPTexture(int iPass, int i, ManagedTexture^ thTexture);

    // Implement INativeObject interface.
    virtual void SetName(String^ thName);
    virtual String^ GetName(void);
    //
    virtual int GetNativeReferences(void);

internal:
    [CLSCompliant(false)]
    ManagedTextureTileL1Effect(SETextureTileL1Effect* pEffect);

    // Implement INativeEffect interface.
    [CLSCompliant(false)]
    virtual SEEffect* GetNativeEffect(void) = INativeEffect::GetNativeEffect;

    // Implement INativeShaderEffect interface.
    [CLSCompliant(false)]
    virtual SEShaderEffect* GetNativeShaderEffect(void) = 
        INativeShaderEffect::GetNativeShaderEffect;

private:
    SETextureTileL1EffectPtr* m_pspTextureTileL1Effect;
};

}}}