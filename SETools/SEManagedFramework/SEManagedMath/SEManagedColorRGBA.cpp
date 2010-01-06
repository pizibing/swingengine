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
#include "SEManagedColorRGBA.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedColorRGBA::ManagedColorRGBA()
{
}
//---------------------------------------------------------------------------
ManagedColorRGBA::ManagedColorRGBA(float fR, float fG, float fB, float fA)
{
    m_fR = fR;
    m_fG = fG;
    m_fB = fB;
    m_fA = fA;
}
//---------------------------------------------------------------------------
ManagedColorRGBA::ManagedColorRGBA(const ColorRGBA& rColor)
{
    FromColorRGBA(rColor);
}
//---------------------------------------------------------------------------
float ManagedColorRGBA::R::get()
{
    return m_fR;
}
//---------------------------------------------------------------------------
void ManagedColorRGBA::R::set(float fR)
{
    m_fR = fR;
}
//---------------------------------------------------------------------------
float ManagedColorRGBA::G::get()
{
    return m_fG;
}
//---------------------------------------------------------------------------
void ManagedColorRGBA::G::set(float fG)
{
    m_fG = fG;
}
//---------------------------------------------------------------------------
float ManagedColorRGBA::B::get()
{
    return m_fB;
}
//---------------------------------------------------------------------------
void ManagedColorRGBA::B::set(float fB)
{
    m_fB = fB;
}
//---------------------------------------------------------------------------
float ManagedColorRGBA::A::get()
{
    return m_fA;
}
//---------------------------------------------------------------------------
void ManagedColorRGBA::A::set(float fA)
{
    m_fA = fA;
}
//---------------------------------------------------------------------------
void ManagedColorRGBA::ToColorRGBA(ColorRGBA& rColor)
{
    rColor.R = m_fR;
    rColor.G = m_fG;
    rColor.B = m_fB;
    rColor.A = m_fA;
}
//---------------------------------------------------------------------------
void ManagedColorRGBA::FromColorRGBA(const ColorRGBA& rColor)
{
    m_fR = rColor.R;
    m_fG = rColor.G;
    m_fB = rColor.B;
    m_fA = rColor.A;
}
//---------------------------------------------------------------------------