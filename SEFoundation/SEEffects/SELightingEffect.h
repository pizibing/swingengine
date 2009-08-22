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

#ifndef Swing_LightingEffect_H
#define Swing_LightingEffect_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEShaderEffect.h"
#include "SEMaterialState.h"
#include "SELight.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:lighting effect类
// 说明:
// 作者:Sun Che
// 时间:20080702
//----------------------------------------------------------------------------
class SE_FOUNDATION_API LightingEffect : public ShaderEffect
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    LightingEffect(void);
    virtual ~LightingEffect(void);

    // 在添加或移除light后,需调用Configure函数来创建新的lighting shader程序.
    inline int GetLightCount(void) const;
    inline Light* GetLight(int i) const;
    void AttachLight(Light* pLight);
    void DetachLight(Light* pLight);
    inline void DetachAllLights(void);

    enum LightingMode
    {
        LM_VERTEX,
        LM_PIXEL,
        LM_COUNT
    };
    inline LightingMode GetLightingMode(void) const;

    void Configure(LightingMode eMode = LM_PIXEL);

    // 用户应根据具体渲染器所使用的shader系统,来实现此函数装载所需shader程序.
    typedef void (*ConfigureLighting)(LightingEffect*);
    static ConfigureLighting OnConfigureLighting;

protected:
    LightingMode m_eMode;  // default: LM_PIXEL
    std::vector<LightPtr> m_Lights;
};

typedef SmartPointer<LightingEffect> LightingEffectPtr;

#include "SELightingEffect.inl"

}

#endif
