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

#include "SEOGLES1RendererPCH.h"
#include "SEOGLES1RendererRegister.h"

// OGLES1 Rendering
#include "SEOGLES1FrameBuffer.h"
#include "SEOGLES1Renderer.h"
// OGLES1 Fixed Effects
#include "SEOGLES1FixedEffect.h"

using namespace Swing;

//----------------------------------------------------------------------------
void Swing::SE_OGLES1Renderer_Register()
{
    // OGLES1 Rendering
    SE_REGISTER_INITIALIZE(SEOGLES1FrameBuffer);
    SE_REGISTER_INITIALIZE(SEOGLES1Renderer);
    SE_INVOKE_INITIALIZE(SEOGLES1FrameBuffer);
    SE_INVOKE_INITIALIZE(SEOGLES1Renderer);

    // OGLES1 Fixed Effects
    SE_REGISTER_STREAM(SEOGLES1FixedEffect);
    SE_INVOKE_STREAM(SEOGLES1FixedEffect);
}
//----------------------------------------------------------------------------