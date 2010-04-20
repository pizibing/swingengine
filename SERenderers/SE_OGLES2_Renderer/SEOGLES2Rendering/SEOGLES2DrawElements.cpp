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

#include "SEOGLES2RendererPCH.h"
#include "SEOGLES2Renderer.h"

using namespace Swing;

GLenum SEOGLES2Renderer::ms_aeObjectType[SEGeometry::GT_MAX_COUNT] =
{
    GL_POINTS,      // GT_POLYPOINT
    GL_LINES,       // GT_POLYLINE_SEGMENTS
    GL_LINE_STRIP,  // GT_POLYLINE_OPEN
    GL_LINE_LOOP,   // GT_POLYLINE_CLOSED
    GL_TRIANGLES    // GT_TRIMESH
};

//----------------------------------------------------------------------------
void SEOGLES2Renderer::DrawElements()
{
    SEIndexBuffer* pIBuffer = m_pGeometry->IBuffer;
    SE_ASSERT( pIBuffer );

    GLenum eType = ms_aeObjectType[m_pGeometry->Type];
    glDrawElements(eType, pIBuffer->GetIndexCount(), GL_UNSIGNED_SHORT, 0);
}
//----------------------------------------------------------------------------
