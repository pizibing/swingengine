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
SENode* SEWidget::CoordinateFrame(float fLengthOfAxis)
{
    SE_ASSERT( fLengthOfAxis > 0 );

    SENode* pNode = SE_NEW SENode;

    SEAttributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetColorChannels(0, 3);
    SEStandardMesh tempSM(tempAttr);

    SEMatrix3f mat3fRot;
    float fAxisHeight = 0.667f*fLengthOfAxis;
    float fArrowRadius = 0.08f*fLengthOfAxis;
    float fArrowHeight = (1.0f - 0.667f)*fLengthOfAxis;

    // Create axis x.
    SEVertexBuffer* pVBuffer = SE_NEW SEVertexBuffer(tempAttr, 2);
    pVBuffer->Position3(0) = SEVector3f::ZERO;
    pVBuffer->Position3(1) = fAxisHeight*SEVector3f::UNIT_X;
    pVBuffer->Color3(0, 0) = SEColorRGB::SE_RGB_RED;
    pVBuffer->Color3(0, 1) = SEColorRGB::SE_RGB_RED;
    SEPolyline* pAxisX = SE_NEW SEPolyline(pVBuffer, false, false);
    pAxisX->SetName("AxisX");

    // Create axis x's ending arrow.
    SETriMesh* pArrowX = tempSM.Cone(16, fArrowRadius, fArrowHeight);
    for( int i = 0; i < pArrowX->VBuffer->GetVertexCount(); i++ )
    {
        pArrowX->VBuffer->Color3(0, i) = SEColorRGB::SE_RGB_RED;
    }
    mat3fRot.FromAxisAngle(SEVector3f::UNIT_Y, SEMathf::HALF_PI);
    pArrowX->Local.SetRotate(mat3fRot);
    pArrowX->Local.SetTranslate(fAxisHeight*SEVector3f::UNIT_X);
    pArrowX->SetName("ArrowX");

    // Create axis y.
    pVBuffer = SE_NEW SEVertexBuffer(tempAttr, 2);
    pVBuffer->Position3(0) = SEVector3f::ZERO;
    pVBuffer->Position3(1) = fAxisHeight*SEVector3f::UNIT_Y;
    pVBuffer->Color3(0, 0) = SEColorRGB::SE_RGB_GREEN;
    pVBuffer->Color3(0, 1) = SEColorRGB::SE_RGB_GREEN;
    SEPolyline* pAxisY = SE_NEW SEPolyline(pVBuffer, false, false);
    pAxisY->SetName("AxisY");

    // Create axis y's ending arrow.
    SETriMesh* pArrowY = tempSM.Cone(16, fArrowRadius, fArrowHeight);
    for( int i = 0; i < pArrowY->VBuffer->GetVertexCount(); i++ )
    {
        pArrowY->VBuffer->Color3(0, i) = SEColorRGB::SE_RGB_GREEN;
    }
    mat3fRot.FromAxisAngle(SEVector3f::UNIT_X, -SEMathf::HALF_PI);
    pArrowY->Local.SetRotate(mat3fRot);
    pArrowY->Local.SetTranslate(fAxisHeight*SEVector3f::UNIT_Y);
    pArrowY->SetName("ArrowY");

    // Create axis z.
    pVBuffer = SE_NEW SEVertexBuffer(tempAttr, 2);
    pVBuffer->Position3(0) = SEVector3f::ZERO;
    pVBuffer->Position3(1) = fAxisHeight*SEVector3f::UNIT_Z;
    pVBuffer->Color3(0, 0) = SEColorRGB::SE_RGB_BLUE;
    pVBuffer->Color3(0, 1) = SEColorRGB::SE_RGB_BLUE;
    SEPolyline* pAxisZ = SE_NEW SEPolyline(pVBuffer, false, false);
    pAxisZ->SetName("AxisZ");

    // Create axis z's ending arrow.
    SETriMesh* pArrowZ = tempSM.Cone(16, fArrowRadius, fArrowHeight);
    for( int i = 0; i < pArrowZ->VBuffer->GetVertexCount(); i++ )
    {
        pArrowZ->VBuffer->Color3(0, i) = SEColorRGB::SE_RGB_BLUE;
    }
    pArrowZ->Local.SetTranslate(fAxisHeight*SEVector3f::UNIT_Z);
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
SENode* SEWidget::ScaleFrame()
{
    // TODO:
    return 0;
}
//----------------------------------------------------------------------------
SENode* SEWidget::RotationFrame()
{
    // TODO:
    return 0;
}
//----------------------------------------------------------------------------
SENode* SEWidget::TranslationFrame()
{
    // TODO:
    return 0;
}
//----------------------------------------------------------------------------
SENode* SEWidget::AABBFrame(const SEVector3f& rMin, const SEVector3f& rMax, 
    const SEColorRGB& rColor)
{
    SENode* pNode = SE_NEW SENode;

    SEAttributes tempAttr;
    tempAttr.SetPositionChannels(3);
    tempAttr.SetColorChannels(0, 3);

    SEVector3f vec3fV0(rMin);
    SEVector3f vec3fV1(rMin.X, rMin.Y, rMax.Z);
    SEVector3f vec3fV2(rMax.X, rMin.Y, rMax.Z);
    SEVector3f vec3fV3(rMax.X, rMin.Y, rMin.Z);
    SEVector3f vec3fV4(rMax.X, rMax.Y, rMin.Z);
    SEVector3f vec3fV5(rMin.X, rMax.Y, rMin.Z);
    SEVector3f vec3fV6(rMin.X, rMax.Y, rMax.Z);
    SEVector3f vec3fV7(rMax);

    // AABBFrame has 12 edges, 24 ending points.
    SEVertexBuffer* pVBuffer = SE_NEW SEVertexBuffer(tempAttr, 24);
    pVBuffer->Position3(0 ) = vec3fV0;
    pVBuffer->Position3(1 ) = vec3fV1;
    pVBuffer->Position3(2 ) = vec3fV1;
    pVBuffer->Position3(3 ) = vec3fV2;
    pVBuffer->Position3(4 ) = vec3fV2;
    pVBuffer->Position3(5 ) = vec3fV3;
    pVBuffer->Position3(6 ) = vec3fV3;
    pVBuffer->Position3(7 ) = vec3fV0;
    pVBuffer->Position3(8 ) = vec3fV5;
    pVBuffer->Position3(9 ) = vec3fV6;
    pVBuffer->Position3(10) = vec3fV6;
    pVBuffer->Position3(11) = vec3fV7;
    pVBuffer->Position3(12) = vec3fV7;
    pVBuffer->Position3(13) = vec3fV4;
    pVBuffer->Position3(14) = vec3fV4;
    pVBuffer->Position3(15) = vec3fV5;
    pVBuffer->Position3(16) = vec3fV0;
    pVBuffer->Position3(17) = vec3fV5;
    pVBuffer->Position3(18) = vec3fV1;
    pVBuffer->Position3(19) = vec3fV6;
    pVBuffer->Position3(20) = vec3fV2;
    pVBuffer->Position3(21) = vec3fV7;
    pVBuffer->Position3(22) = vec3fV3;
    pVBuffer->Position3(23) = vec3fV4;
    for( int i = 0; i < 24; i++ )
    {
        pVBuffer->Color3(0, i) = rColor;
    }
    SEPolyline* pAABBFrame = SE_NEW SEPolyline(pVBuffer, false, false);
    pAABBFrame->SetName("AABBFrame");

    VertexColor3Effect* pEffect = SE_NEW VertexColor3Effect;
    pAABBFrame->AttachEffect(pEffect);

    pNode->AttachChild(pAABBFrame);
    pNode->UpdateGS();

    return pNode;
}
//----------------------------------------------------------------------------