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
#include "SEManagedVector2.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

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
ManagedVector2f::ManagedVector2f(const SEVector2f& rVec)
{
    FromVector2f(rVec);
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
void ManagedVector2f::ToVector2f(SEVector2f& rVec)
{
    rVec.X = m_fX;
    rVec.Y = m_fY;
}
//---------------------------------------------------------------------------
void ManagedVector2f::FromVector2f(const SEVector2f& rVec)
{
    m_fX = rVec.X;
    m_fY = rVec.Y;
}
//---------------------------------------------------------------------------
ManagedVector2f^ ManagedVector2f::Add(ManagedVector2f^ thLhsVec, 
    ManagedVector2f^ thRhsVec)
{
    SEVector2f vec2fLhs, vec2fRhs;
    thLhsVec->ToVector2f(vec2fLhs);
    thRhsVec->ToVector2f(vec2fRhs);
    ManagedVector2f^ thRes = gcnew ManagedVector2f;
    thRes->FromVector2f(vec2fLhs + vec2fRhs);

    return thRes;
}
//---------------------------------------------------------------------------
ManagedVector2f^ ManagedVector2f::Subtract(ManagedVector2f^ thLhsVec, 
    ManagedVector2f^ thRhsVec)
{
    SEVector2f vec2fLhs, vec2fRhs;
    thLhsVec->ToVector2f(vec2fLhs);
    thRhsVec->ToVector2f(vec2fRhs);
    ManagedVector2f^ thRes = gcnew ManagedVector2f;
    thRes->FromVector2f(vec2fLhs - vec2fRhs);

    return thRes;
}
//---------------------------------------------------------------------------
ManagedVector2f^ ManagedVector2f::Multiply(float fScalar, 
    ManagedVector2f^ thVec)
{
    SEVector2f vec2fTemp;
    thVec->ToVector2f(vec2fTemp);
    ManagedVector2f^ thRes = gcnew ManagedVector2f;
    thRes->FromVector2f(fScalar*vec2fTemp);

    return thRes;
}
//---------------------------------------------------------------------------
float ManagedVector2f::Dot(ManagedVector2f^ thLhsVec, 
    ManagedVector2f^ thRhsVec)
{
    SEVector2f vec2fLhs, vec2fRhs;
    thLhsVec->ToVector2f(vec2fLhs);
    thRhsVec->ToVector2f(vec2fRhs);

    return vec2fLhs.Dot(vec2fRhs);
}
//---------------------------------------------------------------------------
ManagedVector2f^ ManagedVector2f::Normalize(ManagedVector2f^ thVec)
{
    SEVector2f vec2fTemp;
    thVec->ToVector2f(vec2fTemp);
    vec2fTemp.Normalize();
    ManagedVector2f^ thRes = gcnew ManagedVector2f;
    thRes->FromVector2f(vec2fTemp);

    return thRes;
}
//---------------------------------------------------------------------------
float ManagedVector2f::GetLength(ManagedVector2f^ thVec)
{
    SEVector2f vec2fTemp;
    thVec->ToVector2f(vec2fTemp);

    return vec2fTemp.GetLength();
}
//---------------------------------------------------------------------------
bool ManagedVector2f::Equals(Object^ thObj)
{
    ManagedVector2f^ thVec = dynamic_cast<ManagedVector2f^>(thObj);
    if( !thVec )
    {
        return false;
    }

    SEVector2f vec2fLhs, vec2fRhs;
    ToVector2f(vec2fLhs);
    thVec->ToVector2f(vec2fRhs);

    return (vec2fLhs == vec2fRhs);
}
//---------------------------------------------------------------------------