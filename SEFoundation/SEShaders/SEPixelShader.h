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

#ifndef Swing_PixelShader_H
#define Swing_PixelShader_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEShader.h"
#include "SEPixelProgram.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:pixel shader类
// 说明:
// 作者:Sun Che
// 时间:20080701
//----------------------------------------------------------------------------
class SE_FOUNDATION_API PixelShader : public Shader
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    PixelShader(const std::string& rShaderName);
    virtual ~PixelShader(void);

    PixelProgram* GetProgram(void) const;

protected:
    PixelShader(void);
};

typedef SESmartPointer<PixelShader> PixelShaderPtr;

}

#endif
