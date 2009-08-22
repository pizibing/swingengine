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

#include "SEOpenGLRendererPCH.h"
#include "SEOpenGLRenderer.h"

using namespace Swing;

//----------------------------------------------------------------------------
void OpenGLRenderer::Draw(const unsigned char* aucBuffer)
{
    if( !aucBuffer )
    {
        return;
    }

    // 关闭其他对buffer copy不必要的states.
    GLboolean bDepthTest = glIsEnabled(GL_DEPTH_TEST);
    GLboolean bLighting = glIsEnabled(GL_LIGHTING);
    GLboolean bTexture2D = glIsEnabled(GL_TEXTURE_2D);
    if( bDepthTest )
    {
        glDisable(GL_DEPTH_TEST);
    }
    if( bLighting )
    {
        glDisable(GL_LIGHTING);
    }
    if( bTexture2D )
    {
        glDisable(GL_TEXTURE_2D);
    }

    // Set raster position to window coord (0,H-1).  The hack here avoids
    // problems with invalid raster positions which would cause glDrawPixels
    // not to execute.  OpenGL uses right-handed screen coordinates, so using
    // (0,H-1) as the raster position followed by glPixelZoom(1,-1) tells
    // OpenGL to draw the screen in left-handed coordinates starting at the
    // top row of the screen and finishing at the bottom row.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, (double)m_iWidth, 0.0, (double)m_iHeight, 0.0, 1.0);
    glRasterPos3f(0.0, 0.0, 0.0);
    GLubyte aucBitmap[1] = {0};
    glBitmap(0, 0, 0.0f, 0.0f, 0.0f, (float)m_iHeight, aucBitmap);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPixelZoom(1.0f, -1.0f);
    glDrawPixels(m_iWidth, m_iHeight, GL_BGR, GL_UNSIGNED_BYTE, aucBuffer);
    glPixelZoom(1.0f, 1.0f);

    // 重新开启这些states.
    if( bDepthTest )
    {
        glEnable(GL_DEPTH_TEST);
    }
    if( bLighting )
    {
        glEnable(GL_LIGHTING);
    }
    if( bTexture2D )
    {
        glEnable(GL_TEXTURE_2D);
    }
}
//----------------------------------------------------------------------------
