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
#include "SEManagedVector3.h"

using namespace Swing;
using namespace Swing::Tools::SceneEditor::Framework;

//---------------------------------------------------------------------------
ManagedVector3f::ManagedVector3f()
{
}
//---------------------------------------------------------------------------
ManagedVector3f::ManagedVector3f(float fX, float fY, float fZ)
{
    m_fX = fX;
    m_fY = fY;
    m_fZ = fZ;
}
//---------------------------------------------------------------------------
float ManagedVector3f::X::get()
{
    return m_fX;
}
//---------------------------------------------------------------------------
void ManagedVector3f::X::set(float fX)
{
    m_fX = fX;
}
//---------------------------------------------------------------------------
float ManagedVector3f::Y::get()
{
    return m_fY;
}
//---------------------------------------------------------------------------
void ManagedVector3f::Y::set(float fY)
{
    m_fY = fY;
}
//---------------------------------------------------------------------------
float ManagedVector3f::Z::get()
{
    return m_fZ;
}
//---------------------------------------------------------------------------
void ManagedVector3f::Z::set(float fZ)
{
    m_fZ = fZ;
}
//---------------------------------------------------------------------------
void ManagedVector3f::ToVector3f(Vector3f& rVec)
{
    rVec.X = m_fX;
    rVec.Y = m_fY;
    rVec.Z = m_fZ;
}
//---------------------------------------------------------------------------
void ManagedVector3f::FromVector3f(const Vector3f& rVec)
{
    m_fX = rVec.X;
    m_fY = rVec.Y;
    m_fZ = rVec.Z;
}
//---------------------------------------------------------------------------