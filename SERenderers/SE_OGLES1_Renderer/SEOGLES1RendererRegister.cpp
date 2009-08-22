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

// OGLES1Rendering
#include "SEOGLES1FrameBuffer.h"
#include "SEOGLES1Renderer.h"
// OGLES1FixedEffects
#include "SEOGLES1FixedEffect.h"

using namespace Swing;

//----------------------------------------------------------------------------
void Swing::SE_OGLES1Renderer_Register()
{
    // OGLES1Rendering
    SE_REGISTER_INITIALIZE(OGLES1FrameBuffer);
    SE_REGISTER_INITIALIZE(OGLES1Renderer);
    SE_INVOKE_INITIALIZE(OGLES1FrameBuffer);
    SE_INVOKE_INITIALIZE(OGLES1Renderer);

    // OGLES1FixedEffects
    SE_REGISTER_STREAM(OGLES1FixedEffect);
    SE_INVOKE_STREAM(OGLES1FixedEffect);
}
//----------------------------------------------------------------------------