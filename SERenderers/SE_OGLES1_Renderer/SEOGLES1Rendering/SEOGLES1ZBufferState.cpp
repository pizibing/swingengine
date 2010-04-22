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
#include "SEOGLES1Renderer.h"

using namespace Swing;

GLenum SEOGLES1Renderer::ms_aeZBufferCompare[SEZBufferState::CF_COUNT] =
{
    GL_NEVER,
    GL_LESS,
    GL_EQUAL,
    GL_LEQUAL,
    GL_GREATER,
    GL_NOTEQUAL,
    GL_GEQUAL,
    GL_ALWAYS
};

//----------------------------------------------------------------------------
void SEOGLES1Renderer::SetZBufferState(SEZBufferState* pState)
{
    SERenderer::SetZBufferState(pState);

    if( pState->Enabled )
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(ms_aeZBufferCompare[pState->Compare]);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);
    }

    if( pState->Writable )
    {
        glDepthMask(GL_TRUE);
    }
    else
    {
        glDepthMask(GL_FALSE);
    }
}
//----------------------------------------------------------------------------
