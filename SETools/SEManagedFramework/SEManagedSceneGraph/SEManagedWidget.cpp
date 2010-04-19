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

#include "SEManagedFrameworkPCH.h"
#include "SEManagedWidget.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedNode^ ManagedWidget::CoordinateFrame(float fLengthOfAxis)
{
    SENode* pNode = SEWidget::CoordinateFrame(fLengthOfAxis);
    return gcnew ManagedNode(pNode);
}
//---------------------------------------------------------------------------
ManagedNode^ ManagedWidget::ScaleFrame()
{
    SENode* pNode = SEWidget::ScaleFrame();
    return gcnew ManagedNode(pNode);
}
//---------------------------------------------------------------------------
ManagedNode^ ManagedWidget::RotationFrame()
{
    SENode* pNode = SEWidget::RotationFrame();
    return gcnew ManagedNode(pNode);
}
//---------------------------------------------------------------------------
ManagedNode^ ManagedWidget::TranslationFrame()
{
    SENode* pNode = SEWidget::TranslationFrame();
    return gcnew ManagedNode(pNode);
}
//---------------------------------------------------------------------------
ManagedNode^ ManagedWidget::AABBFrame(ManagedVector3f^ thVecMin, 
    ManagedVector3f^ thVecMax, ManagedColorRGB^ thColor)
{
    SE_NULL_ARGUMENT_CHECK(thVecMin, "thVecMin");
    SE_NULL_ARGUMENT_CHECK(thVecMax, "thVecMax");
    SE_NULL_ARGUMENT_CHECK(thColor, "thColor");

    SEVector3f vec3fMin, vec3fMax;
    SEColorRGB tempColor;
    thVecMin->ToVector3f(vec3fMin);
    thVecMax->ToVector3f(vec3fMax);
    thColor->ToColorRGB(tempColor);
    SENode* pNode = SEWidget::AABBFrame(vec3fMin, vec3fMax, tempColor);

    return gcnew ManagedNode(pNode);
}
//---------------------------------------------------------------------------