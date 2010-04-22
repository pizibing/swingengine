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

//----------------------------------------------------------------------------
void SEOGLES1Renderer::SetMaterialState(SEMaterialState* pState)
{
    GLfloat afEmissive[4] = 
    {
        pState->Emissive.R,
        pState->Emissive.G,
        pState->Emissive.B,
        1.0f
    };
    GLfloat afAmbient[4] = 
    {
        pState->Ambient.R,
        pState->Ambient.G,
        pState->Ambient.B,
        1.0f
    };
    GLfloat afDiffuse[4] =
    {
        pState->Diffuse.R,
        pState->Diffuse.G,
        pState->Diffuse.B,
        pState->Alpha
    };
    GLfloat afSpecular[4] = 
    {
        pState->Specular.R,
        pState->Specular.G,
        pState->Specular.B,
        1.0f
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, afEmissive);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, afAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, afDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, afSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pState->Shininess);
}
//----------------------------------------------------------------------------
