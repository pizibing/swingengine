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

#ifndef Swing_ShadowMapEffect_H
#define Swing_ShadowMapEffect_H

#include "SEShaderEffect.h"
#include "SECamera.h"
#include "SETexture.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:shadow map effect类
// 说明:
// 作者:Sun Che
// 时间:20090224
//----------------------------------------------------------------------------
class ShadowMapEffect : public Effect
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    ShadowMapEffect(SECamera* pProjector, const std::string& rProjectionImage, 
        SEImage::FormatMode eDepthFormat, int iDepthWidth, int iDepthHeight, 
        float fDepthBias);

    virtual ~ShadowMapEffect(void);

    virtual void Draw(SERenderer* pRenderer, SESpatial* pGlobalObject,
        int iMin, int iMax, SEUnculledObject* pVisibleSet);

    inline void SetDepthBias(float fDepthBias);
    inline float GetDepthBias(void) const;

protected:
    ShadowMapEffect(void);

    SECameraPtr m_spProjector;
    ShaderEffectPtr m_spDepthEffect;
    SEFrameBuffer* m_pDepthBuffer;
    ImagePtr m_spDepthImage;
    ShaderEffectPtr m_spShadowEffect;
    SETexture* m_pDepthTexture;  // 用于测试 (把深度图拷到系统内存).

    // depth bias存储在数组0索引位置.其他数组元素未使用.
    float m_afDepthBias[4];
};

typedef SESmartPointer<ShadowMapEffect> ShadowMapEffectPtr;

#include "SEShadowMapEffect.inl"

}

#endif
