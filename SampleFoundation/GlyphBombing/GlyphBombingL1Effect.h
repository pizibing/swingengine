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

#ifndef Swing_GlyphBombingL1Effect_H
#define Swing_GlyphBombingL1Effect_H

#include "SEShaderEffect.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 说明:
// 作者:Sun Che
// 时间:20090804
//----------------------------------------------------------------------------
class GlyphBombingL1Effect : public SEShaderEffect
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    GlyphBombingL1Effect(const char* acBaseName, const char* acRandomName);
    virtual ~GlyphBombingL1Effect(void);

    // Vertex program UCs.
    float SpecularContribution; // default: 0.2f
    float ScaleFactor;          // default: 4.0f

    // Pixel program UCs.
    SEColorRGBA ModelColor;       // default: white
    float ColAdjust;            // default: 0.5f
    float Percentage;           // default: 1.0f
    float SamplesPerCell;       // default: 1.0f
    float RO1;                  // default: 0.5f
    float RandomScale;          // default: 0.0f
    float RandomRotate;         // default: 0.0f

protected:
    // streaming support
    GlyphBombingL1Effect(void);

    virtual void OnLoadPrograms(int iPass, SEProgram* pVProgram,
        SEProgram* pPProgram, SEProgram* pGProgram);
    virtual void OnPreApplyEffect(SERenderer* pRenderer, bool bPrimaryEffect);

    static float ms_fSpecularContribution;
    static float ms_fScaleFactor;
    static SEColorRGBA ms_ModelColor;
    static float ms_fColAdjust;
    static float ms_fPercentage;
    static float ms_fSamplesPerCell;
    static float ms_fRO1;
    static float ms_fRandomScale;
    static float ms_fRandomRotate;
    static bool ms_bUCInitialized;
};

typedef SESmartPointer<GlyphBombingL1Effect> GlyphBombingL1EffectPtr;

}

#endif
