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
#include "SEManagedRay3.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedRay3f::ManagedRay3f()
{
    m_thOrigin = nullptr;
    m_thDirection = nullptr;
}
//---------------------------------------------------------------------------
ManagedRay3f::ManagedRay3f(ManagedVector3f^ thOrigin, 
    ManagedVector3f^ thDirection)
{
    m_thOrigin = thOrigin;
    m_thDirection = thDirection;
}
//---------------------------------------------------------------------------
ManagedRay3f::ManagedRay3f(const SERay3f& rRay)
{
    FromRay3f(rRay);
}
//---------------------------------------------------------------------------
ManagedRay3f::ManagedRay3f(const SEVector3f& rOrigin, 
    const SEVector3f& rDirection)
{
    SERay3f tempRay(rOrigin, rDirection);
    FromRay3f(tempRay);
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedRay3f::Origin::get()
{
    return m_thOrigin;
}
//---------------------------------------------------------------------------
void ManagedRay3f::Origin::set(ManagedVector3f^ thOrigin)
{
    m_thOrigin = thOrigin;
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedRay3f::Direction::get()
{
    return m_thDirection;
}
//---------------------------------------------------------------------------
void ManagedRay3f::Direction::set(ManagedVector3f^ thDirection)
{
    m_thDirection = thDirection;
}
//---------------------------------------------------------------------------
void ManagedRay3f::ToRay3f(SERay3f& rRay)
{
    SEVector3f vec3fOrigin, vec3fDirection;
    if( m_thOrigin )
    {
        m_thOrigin->ToVector3f(vec3fOrigin);
    }
    if( m_thDirection )
    {
        m_thDirection->ToVector3f(vec3fDirection);
    }
    rRay.Origin = vec3fOrigin;
    rRay.Direction = vec3fDirection;
}
//---------------------------------------------------------------------------
void ManagedRay3f::FromRay3f(const SERay3f& rRay)
{
    if( !m_thOrigin )
    {
        m_thOrigin = gcnew ManagedVector3f;
    }
    if( !m_thDirection )
    {
        m_thDirection = gcnew ManagedVector3f;
    }
    m_thOrigin->FromVector3f(rRay.Origin);
    m_thDirection->FromVector3f(rRay.Direction);
}
//---------------------------------------------------------------------------