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

#ifndef Swing_GaussianBlurVEffect2_H
#define Swing_GaussianBlurVEffect2_H

#include "SEShaderEffect.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:Gaussian blur vertically effect2类
// 说明:专门用于OpenGL ES2 shading language
// 作者:Sun Che
// 时间:20090715
//----------------------------------------------------------------------------
class GaussianBlurVEffect2 : public ShaderEffect
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    GaussianBlurVEffect2(const std::string& rBaseName);
    virtual ~GaussianBlurVEffect2(void);

    // 根据color buffer尺寸调整texel kernel step.
    static void GenerateTexelKernelStep(int iWidth, int iHeight);

protected:
    // streaming
    GaussianBlurVEffect2(void);

    virtual void OnLoadPrograms(int iPass, Program* pVProgram,
        Program* pPProgram, Program* pGProgram);

    // x: 1/width y: 1/height z: direction
    static Vector3f ms_TexelKernelStep;
    static bool ms_bUCInitialized;
};

typedef SmartPointer<GaussianBlurVEffect2> GaussianBlurVEffect2Ptr;

}

#endif
