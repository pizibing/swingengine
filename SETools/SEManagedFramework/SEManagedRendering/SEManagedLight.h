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
#include "SEManagedVector3.h"
#include "SEManagedColorRGB.h"

namespace Swing{ namespace Tools{ namespace ManagedFramework{

//----------------------------------------------------------------------------
// Name:Managed light class
// Description:
// Author:Sun Che
// Date:20100115
//----------------------------------------------------------------------------
public ref class ManagedLight sealed : INativeObject
{
public:
    enum class LightType
    {
        LT_AMBIENT,
        LT_DIRECTIONAL,
        LT_POINT,
        LT_SPOT,
        LT_COUNT
    };

    ManagedLight(LightType eType);
    ~ManagedLight(void);

    // Properties.
    property LightType Type
    {
        LightType get(void);
        void set(LightType eType);
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
    property float Constant
    {
        float get(void);
        void set(float fValue);
    }
    property float Linear
    {
        float get(void);
        void set(float fValue);
    }
    property float Quadratic
    {
        float get(void);
        void set(float fValue);
    }
    property float Intensity
    {
        float get(void);
        void set(float fValue);
    }
    property float Angle
    {
        float get(void);
        void set(float fValue);
    }
    property float CosAngle
    {
        float get(void);
        void set(float fValue);
    }
    property float SinAngle
    {
        float get(void);
        void set(float fValue);
    }
    property float Exponent
    {
        float get(void);
        void set(float fValue);
    }
    property ManagedVector3f^ Position
    {
        ManagedVector3f^ get(void);
        void set(ManagedVector3f^ thPosition);
    }
    property ManagedVector3f^ RVector
    {
        ManagedVector3f^ get(void);
        void set(ManagedVector3f^ thRVector);
    }
    property ManagedVector3f^ UVector
    {
        ManagedVector3f^ get(void);
        void set(ManagedVector3f^ thUVector);
    }
    property ManagedVector3f^ DVector
    {
        ManagedVector3f^ get(void);
        void set(ManagedVector3f^ thDVector);
    }

    void SetAngle(float fAngle);

    // Implement INativeObject interface.
    virtual void SetName(String^ thName);
    virtual String^ GetName(void);
    //
    virtual int GetNativeReferences(void);

internal:
    [CLSCompliant(false)]
    ManagedLight(Light* pLight);

    [CLSCompliant(false)]
    Light* GetNativeLight(void);

private:
    LightPtr* m_pspLight;
};

}}}