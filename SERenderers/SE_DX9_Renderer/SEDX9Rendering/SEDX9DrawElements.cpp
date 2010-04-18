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

#include "SEDX9RendererPCH.h"
#include "SEDX9Renderer.h"
#include "SEPolyline.h"

using namespace Swing;

//----------------------------------------------------------------------------
void SEDX9Renderer::DrawElements()
{
    int iPCount, iACount;
    switch( m_pGeometry->Type )
    {
    case SEGeometry::GT_TRIMESH:
        iACount = m_pGeometry->VBuffer->GetVertexCount();
        iPCount = m_pGeometry->IBuffer->GetIndexCount()/3;

        break;
    case SEGeometry::GT_POLYLINE_OPEN:
        iACount = StaticCast<SEPolyline>(m_pGeometry)->GetActiveCount();
        iPCount = iACount;

        break;
    case SEGeometry::GT_POLYLINE_CLOSED:
        iACount = StaticCast<SEPolyline>(m_pGeometry)->GetActiveCount();
        iPCount = iACount + 1;

        break;
    case SEGeometry::GT_POLYLINE_SEGMENTS:
        iACount = StaticCast<SEPolyline>(m_pGeometry)->GetActiveCount();
        iPCount = iACount / 2;

        break;
    case SEGeometry::GT_POLYPOINT:
        iACount = StaticCast<SEPolyline>(m_pGeometry)->GetActiveCount();
        iPCount = iACount;

        break;
    default:
        SE_ASSERT( false );
        iACount = 0;
        iPCount = 0;

        break;
    }

    ms_hResult = m_pDXDevice->DrawIndexedPrimitive(
        ms_aeObjectType[m_pGeometry->Type], 0, 0, iACount, 0, iPCount);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
