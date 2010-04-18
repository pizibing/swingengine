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

#include "SEDX9RendererPCH.h"
#include "SEDX9RendererRegister.h"

// DX9Rendering
#include "SEDX9FrameBuffer.h"
#include "SEDX9Renderer.h"
// DX9Shaders
#include "SEDX9Program.h"
#include "SEDX9ProgramInterface.h"

using namespace Swing;

//----------------------------------------------------------------------------
void Swing::SE_DX9Renderer_Register()
{
    // DX9Rendering
    SE_REGISTER_INITIALIZE(SEDX9FrameBuffer);
    SE_REGISTER_INITIALIZE(SEDX9Renderer);
    SE_REGISTER_INITIALIZE(SEDX9Program);
    SE_INVOKE_INITIALIZE(SEDX9FrameBuffer);
    SE_INVOKE_INITIALIZE(SEDX9Renderer);
    SE_INVOKE_INITIALIZE(SEDX9Program);

    SE_REGISTER_TERMINATE(SEDX9Renderer);
    SE_INVOKE_TERMINATE(SEDX9Renderer);

    // DX9Shaders
    SE_REGISTER_STREAM(SEDX9ProgramInterface);
    SE_INVOKE_STREAM(SEDX9ProgramInterface);
}
//----------------------------------------------------------------------------