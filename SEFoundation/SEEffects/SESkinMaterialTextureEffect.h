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

#ifndef Swing_SkinMaterialTextureEffect_H
#define Swing_SkinMaterialTextureEffect_H

#include "SEFoundationLIB.h"
#include "SESkinEffect.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:Skin material texture effect class
// 说明:由GPU进行蒙皮顶点计算.所依附的node必须带有material state对象.
// 作者:Sun Che
// 时间:20080901
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SkinMaterialTextureEffect : public SkinEffect
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    SkinMaterialTextureEffect(const std::string& rBaseName, int iBoneCount, 
        SENode** apBones, SETransformation* aOffset);
    virtual ~SkinMaterialTextureEffect(void);

protected:
    // streaming
    SkinMaterialTextureEffect(void);

    virtual void OnLoadPrograms(int iPass, SEProgram* pVProgram,
        SEProgram* pPProgram, SEProgram* pGProgram);

    static bool ms_bUCInitialized;
};

typedef SESmartPointer<SkinMaterialTextureEffect> SkinMaterialTextureEffectPtr;

}

#endif
