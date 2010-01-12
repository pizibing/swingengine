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
#include "SEPolyline.h"
#include "SEStandardMesh.h"

using namespace Swing;

//----------------------------------------------------------------------------
Node* Widget::CoordinateFrame(float fLengthOfAxis)
{
    SE_ASSERT( fLengthOfAxis > 0 );

    Node* pNode = SE_NEW Node;

    Attributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetColorChannels(0, 3);
    StandardMesh tempSM(tempAttr);

    Matrix3f mat3fRot;
    float fArrowRadius = 0.08f*fLengthOfAxis;
    float fArrowHeight = 0.5f*fLengthOfAxis;

    // Create axis x.
    VertexBuffer* pVBuffer = SE_NEW VertexBuffer(tempAttr, 2);
    (*(Vector3f*)pVBuffer->PositionTuple(0)) = Vector3f::ZERO;
    (*(Vector3f*)pVBuffer->PositionTuple(1)) = fLengthOfAxis*Vector3f::UNIT_X;
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 0)) = ColorRGB::SE_RGB_RED;
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 1)) = ColorRGB::SE_RGB_RED;
    Polyline* pAxisX = SE_NEW Polyline(pVBuffer, false, false);
    pAxisX->SetName("AxisX");

    // Create axis x's ending arrow.
    TriMesh* pArrowX = tempSM.Cone(16, fArrowRadius, fArrowHeight);
    for( int i = 0; i < pArrowX->VBuffer->GetVertexCount(); i++ )
    {
        pArrowX->VBuffer->Color3(0, i) = ColorRGB::SE_RGB_RED;
    }
    mat3fRot.FromAxisAngle(Vector3f::UNIT_Y, Mathf::HALF_PI);
    pArrowX->Local.SetRotate(mat3fRot);
    pArrowX->Local.SetTranslate(fLengthOfAxis*Vector3f::UNIT_X);
    pArrowX->SetName("ArrowX");

    // Create axis y.
    pVBuffer = SE_NEW VertexBuffer(tempAttr, 2);
    (*(Vector3f*)pVBuffer->PositionTuple(0)) = Vector3f::ZERO;
    (*(Vector3f*)pVBuffer->PositionTuple(1)) = fLengthOfAxis*Vector3f::UNIT_Y;
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 0)) = ColorRGB::SE_RGB_GREEN;
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 1)) = ColorRGB::SE_RGB_GREEN;
    Polyline* pAxisY = SE_NEW Polyline(pVBuffer, false, false);
    pAxisY->SetName("AxisY");

    // Create axis y's ending arrow.
    TriMesh* pArrowY = tempSM.Cone(16, fArrowRadius, fArrowHeight);
    for( int i = 0; i < pArrowY->VBuffer->GetVertexCount(); i++ )
    {
        pArrowY->VBuffer->Color3(0, i) = ColorRGB::SE_RGB_GREEN;
    }
    mat3fRot.FromAxisAngle(Vector3f::UNIT_X, -Mathf::HALF_PI);
    pArrowY->Local.SetRotate(mat3fRot);
    pArrowY->Local.SetTranslate(fLengthOfAxis*Vector3f::UNIT_Y);
    pArrowY->SetName("ArrowY");

    // Create axis z.
    pVBuffer = SE_NEW VertexBuffer(tempAttr, 2);
    (*(Vector3f*)pVBuffer->PositionTuple(0)) = Vector3f::ZERO;
    (*(Vector3f*)pVBuffer->PositionTuple(1)) = fLengthOfAxis*Vector3f::UNIT_Z;
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 0)) = ColorRGB::SE_RGB_BLUE;
    (*(ColorRGB*)pVBuffer->ColorTuple(0, 1)) = ColorRGB::SE_RGB_BLUE;
    Polyline* pAxisZ = SE_NEW Polyline(pVBuffer, false, false);
    pAxisZ->SetName("AxisZ");

    // Create axis z's ending arrow.
    TriMesh* pArrowZ = tempSM.Cone(16, fArrowRadius, fArrowHeight);
    for( int i = 0; i < pArrowZ->VBuffer->GetVertexCount(); i++ )
    {
        pArrowZ->VBuffer->Color3(0, i) = ColorRGB::SE_RGB_BLUE;
    }
    pArrowZ->Local.SetTranslate(fLengthOfAxis*Vector3f::UNIT_Z);
    pArrowZ->SetName("ArrowZ");

    VertexColor3Effect* pEffect = SE_NEW VertexColor3Effect;
    pAxisX->AttachEffect(pEffect);
    pArrowX->AttachEffect(pEffect);
    pAxisY->AttachEffect(pEffect);
    pArrowY->AttachEffect(pEffect);
    pAxisZ->AttachEffect(pEffect);
    pArrowZ->AttachEffect(pEffect);

    pNode->AttachChild(pAxisX);
    pNode->AttachChild(pArrowX);
    pNode->AttachChild(pAxisY);
    pNode->AttachChild(pArrowY);
    pNode->AttachChild(pAxisZ);
    pNode->AttachChild(pArrowZ);
    pNode->UpdateGS();

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