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

#ifndef Swing_DynamicMultiTextureEffect_H
#define Swing_DynamicMultiTextureEffect_H

#include "SEFoundationLIB.h"
#include "SEShaderEffect.h"
#include "SEString.h"

namespace Swing
{

class SE_FOUNDATION_API DynamicMultiTextureEffect : public ShaderEffect
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    DynamicMultiTextureEffect(int iTextureCount);
    virtual ~DynamicMultiTextureEffect(void);

    void SetTextureCount(int iTextureCount);
    int GetTextureCount(void) const;
    void SetImageName(int i, const String& rImageName);
    const String& GetImageName(int i) const;
    void SetTextureTypeName(int i, const String& rTextureTypeName);
    const String& GetTextureTypeName(int i) const;
    void Configure(void);

    static Vector3f ConstantColor;

protected:
    // streaming support
    DynamicMultiTextureEffect(void);

    virtual void OnLoadPrograms(int iPass, Program* pVProgram,
        Program* pPProgram, Program* pGProgram);

    int m_iTextureCount;
    String* m_aImageName;
    String* m_aTextureTypeName;
};

typedef SmartPointer<DynamicMultiTextureEffect> DynamicMultiTextureEffectPtr;

}

#endif
