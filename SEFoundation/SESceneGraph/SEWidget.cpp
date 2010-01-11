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

#include "SEFoundationPCH.h"
#include "SEWidget.h"

using namespace Swing;

//----------------------------------------------------------------------------
Node* Widget::CoordinateFrame(float fLengthOfAxis)
{
    SE_ASSERT( fLengthOfAxis > 0 );

    Node* pNode = SE_NEW Node;

    Attributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetColorChannels(0, 3);
    VertexBuffer* pVBuffer = SE_NEW VertexBuffer(tempAttr, 6);
    (*(Vector3f*)pVBuffer->PositionTuple(0)) = Vector3f::ZERO;
    (*(Vector3f*)pVBuffer->PositionTuple(1)) = fLengthOfAxis*Vector3f::UNIT_X;
    (*(Vector3f*)pVBuffer->PositionTuple(2)) = Vector3f::ZERO;
    (*(Vector3f*)pVBuffer->PositionTuple(3)) = fLengthOfAxis*Vector3f::UNIT_Y;
    (*(Vector3f*)pVBuffer->PositionTuple(4)) = Vector3f::ZERO;
    (*(Vector3f*)pVBuffer->PositionTuple(5)) = fLengthOfAxis*Vector3f::UNIT_Z;
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 0)) = ColorRGB::SE_RGB_RED;
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 1)) = ColorRGB::SE_RGB_RED;
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 2)) = ColorRGB::SE_RGB_GREEN;  
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 3)) = ColorRGB::SE_RGB_GREEN;
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 4)) = ColorRGB::SE_RGB_BLUE;
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 5)) = ColorRGB::SE_RGB_BLUE;
    Polyline* pCoordinateFrame = SE_NEW Polyline(pVBuffer, false, false);
    pNode->AttachChild(pCoordinateFrame);
    VertexColor3Effect* pEffect = SE_NEW VertexColor3Effect;
    pCoordinateFrame->AttachEffect(pEffect);

    return pNode;
}
//----------------------------------------------------------------------------
Node* Widget::ScaleFrame()
{
    // TODO:
    return 0;
}
//----------------------------------------------------------------------------
Node* Widget::RotationFrame()
{
    // TODO:
    return 0;
}
//----------------------------------------------------------------------------
Node* Widget::TranslationFrame()
{
    // TODO:
    return 0;
}
//----------------------------------------------------------------------------