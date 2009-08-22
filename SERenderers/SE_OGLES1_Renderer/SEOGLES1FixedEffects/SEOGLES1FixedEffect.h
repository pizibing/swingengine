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

#ifndef Swing_OGLES1FixedEffect_H
#define Swing_OGLES1FixedEffect_H

#include "SEOGLES1RendererLIB.h"
#include "SEEffect.h"
#include "SEString.h"
#include "SETexture.h"
#include "SELight.h"

namespace Swing
{

class Renderer;

//----------------------------------------------------------------------------
// 名称:OpenGL ES1 fixed effect基类
// 说明:
// 作者:Sun Che
// 时间:20090610
//----------------------------------------------------------------------------
class SE_RENDERER_API OGLES1FixedEffect : public Effect
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    OGLES1FixedEffect(int iTextureCount, int iLightCount);
    virtual ~OGLES1FixedEffect(void);

    // texture访问.
    int GetTextureCount(void) const;
    Texture* GetTexture(int i);
    const Texture* GetTexture(int i) const;
    void SetTexture(int i, Texture* pTexture);
    const String& GetImageName(int i) const;
    void SetImageName(int i, const String& rName);

    // light访问.
    int GetLightCount(void) const;
    Light* GetLight(int i);
    const Light* GetLight(int i) const;
    void SetLight(int i, Light* pLight);

    // 这些函数由Renderer::LoadResources和Renderer::ReleaseResources调用.
    // 也可以在应用程序中由用户手动调用初始化所需资源.
    virtual void LoadResources(Renderer* pRenderer, Geometry* pGeometry);
    virtual void ReleaseResources(Renderer* pRenderer, Geometry* pGeometry);

protected:
    // streaming support.
    OGLES1FixedEffect(void);

    // textures.
    std::vector<String> m_ImageNames;
    std::vector<TexturePtr> m_Textures;

    // lights.
    std::vector<LightPtr> m_Lights;
};

typedef SmartPointer<OGLES1FixedEffect> OGLES1FixedEffectPtr;

}

#endif
