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
#include "SEOpenGLBitmapFont.h"

using namespace Swing;

//#define USE_TEXT_DISPLAY_LIST

//----------------------------------------------------------------------------
bool SEOpenGLRenderer::SelectFont(int iFontID)
{
    if( 0 <= iFontID && iFontID < (int)m_DLInfo.size() )
    {
        if( m_DLInfo[iFontID].Count > 0 )
        {
            m_iFontID = iFontID;

            return true;
        }
    }

    return false;
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::UnloadFont(int iFontID)
{
    // You may not unload the default font (id = 0).
    if( iFontID <= 0 )
    {
        return;
    }

    std::vector<DisplayListInfo>::iterator tempIter;
    for( tempIter = m_DLInfo.begin(); tempIter != m_DLInfo.end(); tempIter++ );
    {
        DisplayListInfo tempInfo = *tempIter;
        glDeleteLists(tempInfo.Start, tempInfo.Count);
        m_DLInfo.erase(tempIter);
        if( m_iFontID == iFontID )
        {
            m_iFontID = 0;
        }
    }
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::DrawCharacter(const SEBitmapFont& rFont, char cChar)
{
    unsigned int uiIndex = (unsigned int)cChar;
    const SEBitmapFontChar* pBFC = rFont.Chars[uiIndex];

    // save unpack state
    GLint iSwapBytes, iLSBFirst, iRowLength, iSkipRows, iSkipPixels;
    GLint iAlignment;
    glGetIntegerv(GL_UNPACK_SWAP_BYTES, &iSwapBytes);
    glGetIntegerv(GL_UNPACK_LSB_FIRST, &iLSBFirst);
    glGetIntegerv(GL_UNPACK_ROW_LENGTH, &iRowLength);
    glGetIntegerv(GL_UNPACK_SKIP_ROWS, &iSkipRows);
    glGetIntegerv(GL_UNPACK_SKIP_PIXELS, &iSkipPixels);
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &iAlignment);

    glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
    glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBitmap(pBFC->XSize, pBFC->YSize, (float)pBFC->XOrigin,
        (float)pBFC->YOrigin, (float)pBFC->XSize, 0.0f,
        (const GLubyte*)pBFC->Bitmap);

    // restore unpack state
    glPixelStorei(GL_UNPACK_SWAP_BYTES, iSwapBytes);
    glPixelStorei(GL_UNPACK_LSB_FIRST, iLSBFirst);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, iRowLength);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, iSkipRows);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, iSkipPixels);
    glPixelStorei(GL_UNPACK_ALIGNMENT, iAlignment);
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::Draw(int iX, int iY, const SEColorRGBA& rColor,
    const char* acText)
{
    SE_ASSERT( acText );

#ifdef USE_TEXT_DISPLAY_LIST
    GLint iListBase;
    glGetIntegerv(GL_LIST_BASE, &iListBase);
#endif

    // switch to orthogonal view
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-0.5f, m_iWidth-0.5f, -0.5f, m_iHeight-0.5f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // disable depth, lighting, and texturing
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

    // set the text color
    glColor4fv((const float*)rColor);

    // draw text string (use right-handed coordinates)
    glRasterPos3i(iX, m_iHeight-1-iY, 0);
#ifdef USE_TEXT_DISPLAY_LIST
    glListBase(m_DLInfo[m_iFontID].Base);
    glCallLists((GLsizei)strlen(acText), GL_UNSIGNED_BYTE, acText);
#else
    int iLength = (int)strlen(acText);
    for( int i = 0; i < iLength; i++ )
    {
        DrawCharacter(g_Verdana_S16B0I0, acText[i]);
    }
#endif

    // restore depth, lighting, and texturing
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

    // restore matrices
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    // restore projective view
    OnFrustumChange();

#ifdef USE_TEXT_DISPLAY_LIST
    glListBase(iListBase);
#endif
}
//----------------------------------------------------------------------------
