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

GLenum SEOGLES1Renderer::ms_aeFrontFace[SECullState::FT_COUNT] =
{
    GL_CCW,
    GL_CW
};

GLenum SEOGLES1Renderer::ms_aeCullFace[SECullState::CT_COUNT] =
{
    GL_FRONT,
    GL_BACK
};

//----------------------------------------------------------------------------
void SEOGLES1Renderer::SetCullState(SECullState* pState)
{
    SERenderer::SetCullState(pState);

    if( pState->Enabled )
    {
        glEnable(GL_CULL_FACE);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }

    glFrontFace(ms_aeFrontFace[pState->FrontFace]);

    if( !m_bReverseCullFace )
    {
        glCullFace(ms_aeCullFace[pState->CullFace]);
    }
    else
    {
        if( ms_aeCullFace[pState->CullFace] == GL_BACK )
        {
            glCullFace(GL_FRONT);
        }
        else
        {
            glCullFace(GL_BACK);
        }
    }
}
//----------------------------------------------------------------------------
