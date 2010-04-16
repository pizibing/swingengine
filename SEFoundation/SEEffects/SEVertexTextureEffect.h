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

#ifndef Swing_VertexTextureEffect_H
#define Swing_VertexTextureEffect_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEShaderEffect.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:vertex texture effect类
// 说明:需要vs_3_0或vp40的shader profile支持.
//    vs_3_0最大支持4个sampler,vp40的还没查到.
// 作者:Sun Che
// 时间:20090302
//----------------------------------------------------------------------------
class SE_FOUNDATION_API VertexTextureEffect : public ShaderEffect
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    VertexTextureEffect(const std::string& rBaseName);
    virtual ~VertexTextureEffect(void);

protected:
    // streaming
    VertexTextureEffect(void);
};

typedef SESmartPointer<VertexTextureEffect> VertexTextureEffectPtr;

}

#endif
