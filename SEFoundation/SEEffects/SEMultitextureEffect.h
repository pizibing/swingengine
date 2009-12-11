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

#ifndef Swing_MultitextureEffect_H
#define Swing_MultitextureEffect_H

#include "SEFoundationLIB.h"
#include "SEShaderEffect.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:multitexture effect类
// 说明:
// 作者:Sun Che
// 时间:20081014
//----------------------------------------------------------------------------
class SE_FOUNDATION_API MultitextureEffect : public ShaderEffect
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    MultitextureEffect(int iTextureCount);
    virtual ~MultitextureEffect(void);

    // Selection of the textures to be used by the effect.  The first call
    // should be SetTextureCount for the desired number of textures.  For
    // each texture, specify its image with SetImageName.  Texture 0 is
    // used as is (replace mode).  Texture i is blended with texture i-1 (for
    // i > 0) according to the modes specified by alpha state i to
    // produce the current colors.  After setting all the image names and all
    // the blending modes, call Configure() to activate the correct shader
    // program for the current set of textures.
    void SetTextureCount(int iTextureCount);
    int GetTextureCount(void) const;
    void SetImageName(int i, const std::string& rImageName);
    const std::string& GetImageName(int i) const;
    void Configure(void);

protected:
    // streaming support
    MultitextureEffect(void);

    int m_iTextureCount;
    std::string* m_aImageName;
};

typedef SmartPointer<MultitextureEffect> MultitextureEffectPtr;

}

#endif
