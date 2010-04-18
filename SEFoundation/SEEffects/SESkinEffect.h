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

#ifndef Swing_SkinEffect_H
#define Swing_SkinEffect_H

#include "SEFoundationLIB.h"
#include "SEShaderEffect.h"

namespace Swing
{

class SENode;
class SETransformation;

//----------------------------------------------------------------------------
// 名称:Skin effect class
// 说明:This is the base class of all skin-derived effect classes.
// 作者:Sun Che
// 时间:20091126
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SkinEffect : public ShaderEffect
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;
    SE_DECLARE_INITIALIZE;
    SE_DECLARE_TERMINATE;

public:
    virtual ~SkinEffect(void);

    // Member access.
    // Do a copying of these data if you want to hold them in another place.
    int GetBoneCount(void) const;
    SENode** GetBones(void);
    SETransformation* GetOffsets(void);

protected:
    // Abstract bass class.
    SkinEffect(int iBoneCount, SENode** apBones, SETransformation* aOffset);
    SkinEffect(void);

    // All derived classes should call this helper function in their 
    // OnLoadPrograms() function to initialize their skin matrix UCs.
    void InitializeUserConstants(SEProgram* pVProgram);

    virtual void OnLoadPrograms(int iPass, SEProgram* pVProgram,
        SEProgram* pPProgram, SEProgram* pGProgram);
    virtual void OnPreApplyEffect(SERenderer* pRenderer, bool bPrimaryEffect);

    int m_iBoneCount;          // bc
    SENode** m_apBones;          // bones[bc]
    SETransformation* m_aOffset; // offset[bc]

    // Max number of skin matrices.
    enum { SM_COUNT = 32 };

    // Profile specific number of skin matrices.
    enum 
    { 
        VS_2_0_COUNT = 32,
        VS_3_0_COUNT = 32,
        ARBVP1_COUNT = 22,
        VP40_COUNT = 32,
        OES2VP1_COUNT = 24,
        SFTVP1_COUNT = 22
    };

    static float* ms_apSkinMatrix;
};

typedef SESmartPointer<SkinEffect> SkinEffectPtr;

}

#endif
