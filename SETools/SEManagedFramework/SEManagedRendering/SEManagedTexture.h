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
#include "SEManagedColorRGBA.h"

namespace Swing{ namespace Tools{ namespace ManagedFramework{

//----------------------------------------------------------------------------
// Name:Managed texture class
// Description:
// Author:Sun Che
// Date:20100117
//----------------------------------------------------------------------------
public ref class ManagedTexture sealed : INativeObject
{
public:
    enum class FilterType
    {
        NEAREST,
        LINEAR,
        NEAREST_NEAREST,
        NEAREST_LINEAR,
        LINEAR_NEAREST,
        LINEAR_LINEAR,
        MAX_FILTER_TYPES
    };

    enum class WrapType
    {
        CLAMP,
        REPEAT,
        MIRRORED_REPEAT,
        CLAMP_BORDER,
        CLAMP_EDGE,
        MAX_WRAP_TYPES
    };

    enum class DepthCompare
    {
        DC_NEVER,
        DC_LESS,
        DC_EQUAL,
        DC_LEQUAL,
        DC_GREATER,
        DC_NOTEQUAL,
        DC_GEQUAL,
        DC_ALWAYS,
        DC_COUNT
    };

    ManagedTexture(void);
    ~ManagedTexture(void);

    // Filter type access.
    void SetFilterType(FilterType eFType);
    FilterType GetFilterType(void);

    // Wrap type access.
    void SetWrapType(int i, WrapType eWType);
    WrapType GetWrapType(int i);

    // Border color access.
    void SetBorderColor(ManagedColorRGBA^ thBorderColor);
    ManagedColorRGBA^ GetBorderColor(void);

    // Offscreen texture access.
    bool IsOffscreenTexture(void);
    void SetOffscreenTexture(bool bOffscreenTexture);

    // Implement INativeObject interface.
    virtual void SetName(String^ thName);
    virtual String^ GetName(void);
    //
    virtual int GetNativeReferences(void);

internal:
    [CLSCompliant(false)]
    ManagedTexture(Texture* pTexture);

    [CLSCompliant(false)]
    Texture* GetNativeTexture(void);

private:
    TexturePtr* m_pspTexture;
};

}}}