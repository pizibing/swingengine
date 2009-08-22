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

#ifndef Swing_GeometryShader_H
#define Swing_GeometryShader_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEShader.h"
#include "SEGeometryProgram.h"
#include "SEString.h"

namespace Swing
{

//----------------------------------------------------------------------------
// ����:geometry shader��
// ˵��:
// ����:Sun Che
// ʱ��:20090523
//----------------------------------------------------------------------------
class SE_FOUNDATION_API GeometryShader : public Shader
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    GeometryShader(const String& rShaderName);
    virtual ~GeometryShader(void);

    GeometryProgram* GetProgram(void) const;

protected:
    GeometryShader(void);
};

typedef SmartPointer<GeometryShader> GeometryShaderPtr;

}

#endif