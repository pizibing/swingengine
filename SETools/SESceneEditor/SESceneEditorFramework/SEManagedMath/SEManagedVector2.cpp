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

#include "SESceneEditorFrameworkPCH.h"
#include "SEManagedVector2.h"

using namespace Swing;
using namespace Swing::Tools::SceneEditor::Framework;

//---------------------------------------------------------------------------
ManagedVector2f::ManagedVector2f()
{
}
//---------------------------------------------------------------------------
ManagedVector2f::ManagedVector2f(float fX, float fY)
{
    m_fX = fX;
    m_fY = fY;
}
//---------------------------------------------------------------------------
float ManagedVector2f::X::get()
{
    return m_fX;
}
//---------------------------------------------------------------------------
void ManagedVector2f::X::set(float fX)
{
    m_fX = fX;
}
//---------------------------------------------------------------------------
float ManagedVector2f::Y::get()
{
    return m_fY;
}
//---------------------------------------------------------------------------
void ManagedVector2f::Y::set(float fY)
{
    m_fY = fY;
}
//---------------------------------------------------------------------------
void ManagedVector2f::ToVector2f(Vector2f& rVec)
{
    rVec.X = m_fX;
    rVec.Y = m_fY;
}
//---------------------------------------------------------------------------
void ManagedVector2f::FromVector2f(const Vector2f& rVec)
{
    m_fX = rVec.X;
    m_fY = rVec.Y;
}
//---------------------------------------------------------------------------