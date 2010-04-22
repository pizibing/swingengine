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

#include "SEDX10RendererPCH.h"
#include "SEDX10RendererRegister.h"

// DX10 Rendering
#include "SEDX10FrameBuffer.h"
#include "SEDX10Renderer.h"
// DX10 Shaders
#include "SEDX10Program.h"
#include "SEDX10ProgramInterface.h"

using namespace Swing;

//----------------------------------------------------------------------------
void Swing::SE_DX10Renderer_Register()
{
    // DX10 Rendering
    SE_REGISTER_INITIALIZE(SEDX10FrameBuffer);
    SE_REGISTER_INITIALIZE(SEDX10Renderer);
    SE_REGISTER_INITIALIZE(SEDX10Program);
    SE_INVOKE_INITIALIZE(SEDX10FrameBuffer);
    SE_INVOKE_INITIALIZE(SEDX10Renderer);
    SE_INVOKE_INITIALIZE(SEDX10Program);

    SE_REGISTER_TERMINATE(SEDX10Renderer);
    SE_INVOKE_TERMINATE(SEDX10Renderer);

    // DX10 Shaders
    SE_REGISTER_STREAM(SEDX10ProgramInterface);
    SE_INVOKE_STREAM(SEDX10ProgramInterface);
}
//----------------------------------------------------------------------------