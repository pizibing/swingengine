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
void SEOGLES1Renderer::SetLightingStateFixed(int i, SELight* pLight)
{
    if( !pLight )
    {
        return;
    }

    int iLight = GL_LIGHT0 + i;
    glEnable(iLight);

    GLfloat afAmbient[4] =
    {
        pLight->Ambient.R,
        pLight->Ambient.G,
        pLight->Ambient.B,
        1.0f
    };
    GLfloat afDiffuse[4] =
    {
        pLight->Diffuse.R,
        pLight->Diffuse.G,
        pLight->Diffuse.B,
        1.0f
    };
    GLfloat afSpecular[4] =
    {
        pLight->Specular.R,
        pLight->Specular.G,
        pLight->Specular.B,
        1.0f
    };

    switch( pLight->Type )
    {
    case SELight::LT_AMBIENT:
        // 固定管线只有一个全局ambient light.
        // 因此总是用当前的ambient light覆盖之前的ambient light.
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, afAmbient);
        break;

    case SELight::LT_DIRECTIONAL:
        {
            GLfloat afDirection[4] =
            {
                -pLight->DVector.X,
                -pLight->DVector.Y,
                -pLight->DVector.Z,
                0.0f
            };

            glLightfv(iLight, GL_AMBIENT, afAmbient);
            glLightfv(iLight, GL_DIFFUSE, afDiffuse);
            glLightfv(iLight, GL_SPECULAR, afSpecular);
            glLightfv(iLight, GL_POSITION, afDirection);
            // 确保这是一个directional light.
            glLightf(iLight, GL_SPOT_CUTOFF, 180.0f);
        }
        break;

    case SELight::LT_POINT:
        {
            GLfloat afPosition[4] =
            {
                pLight->Position.X,
                pLight->Position.Y,
                pLight->Position.Z,
                1.0f
            };

            glLightfv(iLight, GL_AMBIENT, afAmbient);
            glLightfv(iLight, GL_DIFFUSE, afDiffuse);
            glLightfv(iLight, GL_SPECULAR, afSpecular);
            glLightfv(iLight, GL_POSITION, afPosition);
            // 确保这是一个point light.
            glLightf(iLight, GL_SPOT_CUTOFF, 180.0f);
        }
        break;

    case SELight::LT_SPOT:
        {
            GLfloat afDirection[3] =
            {
                pLight->DVector.X,
                pLight->DVector.Y,
                pLight->DVector.Z
            };

            GLfloat afPosition[4] =
            {
                pLight->Position.X,
                pLight->Position.Y,
                pLight->Position.Z,
                1.0f
            };

            glLightfv(iLight, GL_AMBIENT, afAmbient);
            glLightfv(iLight, GL_DIFFUSE, afDiffuse);
            glLightfv(iLight, GL_SPECULAR, afSpecular);
            glLightfv(iLight, GL_POSITION, afPosition);

            glLightfv(iLight, GL_SPOT_DIRECTION, afDirection);
            glLightf(iLight, GL_SPOT_CUTOFF, 
                pLight->Angle*SEMathf::RAD_TO_DEG);
            glLightf(iLight, GL_SPOT_EXPONENT, pLight->Exponent);
        }
        break;

    default:
        break;
    }
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::RestoreLightingStateFixed(int i, SELight* pLight)
{
    if( !pLight )
    {
        return;
    }

    int iLight = GL_LIGHT0 + i;
    glDisable(iLight);
}
//----------------------------------------------------------------------------
