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

#ifndef Swing_DX9Resources_H
#define Swing_DX9Resources_H

#include "SEDX9RendererLIB.h"
#include "SEDX9Utility.h"
#include "SEAttributes.h"
#include "SEBindable.h"
#include "SEDX9ProgramInterface.h"

namespace Swing
{

class SE_RENDERER_API VProgramID : public ResourceIdentifier
{
public:
    CGprogram ID;
};

class SE_RENDERER_API PProgramID : public ResourceIdentifier
{
public:
    CGprogram ID;
};

class SE_RENDERER_API TextureID : public ResourceIdentifier
{
public:
    IDirect3DBaseTexture9* ID;
    Texture* TextureObject;
};

class SE_RENDERER_API VBufferID : public ResourceIdentifier
{
public:
    Attributes IAttr;  // multipass时,用于shader输入属性匹配性检测.
    Attributes OAttr;
    LPDIRECT3DVERTEXBUFFER9 ID;
    int VertexSize;
    DWORD Format;
};

class SE_RENDERER_API IBufferID : public ResourceIdentifier
{
public:
    LPDIRECT3DINDEXBUFFER9 ID;
};

class SE_RENDERER_API ProgramData
{
public:
    ProgramData(void){ ID = 0; }

    CGprogram ID;

    // 该程序所需的程序接口.
    std::vector<DX9ProgramInterfacePtr> Interfaces;
};

}

#endif
