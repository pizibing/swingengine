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
#include "SEManagedVector3.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

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
ManagedVector3f::ManagedVector3f(const Vector3f& rVec)
{
    FromVector3f(rVec);
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
ManagedVector3f^ ManagedVector3f::Add(ManagedVector3f^ thLhsVec, 
    ManagedVector3f^ thRhsVec)
{
    Vector3f vec3fLhs, vec3fRhs;
    thLhsVec->ToVector3f(vec3fLhs);
    thRhsVec->ToVector3f(vec3fRhs);
    ManagedVector3f^ thRes = gcnew ManagedVector3f;
    thRes->FromVector3f(vec3fLhs + vec3fRhs);

    return thRes;
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedVector3f::Subtract(ManagedVector3f^ thLhsVec, 
    ManagedVector3f^ thRhsVec)
{
    Vector3f vec3fLhs, vec3fRhs;
    thLhsVec->ToVector3f(vec3fLhs);
    thRhsVec->ToVector3f(vec3fRhs);
    ManagedVector3f^ thRes = gcnew ManagedVector3f;
    thRes->FromVector3f(vec3fLhs - vec3fRhs);

    return thRes;
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedVector3f::Multiply(float fScalar, 
    ManagedVector3f^ thVec)
{
    Vector3f vec3fTemp;
    thVec->ToVector3f(vec3fTemp);
    ManagedVector3f^ thRes = gcnew ManagedVector3f;
    thRes->FromVector3f(fScalar*vec3fTemp);

    return thRes;
}
//---------------------------------------------------------------------------
float ManagedVector3f::Dot(ManagedVector3f^ thLhsVec, 
    ManagedVector3f^ thRhsVec)
{
    Vector3f vec3fLhs, vec3fRhs;
    thLhsVec->ToVector3f(vec3fLhs);
    thRhsVec->ToVector3f(vec3fRhs);

    return vec3fLhs.Dot(vec3fRhs);
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedVector3f::Cross(ManagedVector3f^ thLhsVec, 
    ManagedVector3f^ thRhsVec)
{
    Vector3f vec3fLhs, vec3fRhs;
    thLhsVec->ToVector3f(vec3fLhs);
    thRhsVec->ToVector3f(vec3fRhs);
    ManagedVector3f^ thRes = gcnew ManagedVector3f;
    thRes->FromVector3f(vec3fLhs.Cross(vec3fRhs));

    return thRes;
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedVector3f::Normalize(ManagedVector3f^ thVec)
{
    Vector3f vec3fTemp;
    thVec->ToVector3f(vec3fTemp);
    vec3fTemp.Normalize();
    ManagedVector3f^ thRes = gcnew ManagedVector3f;
    thRes->FromVector3f(vec3fTemp);

    return thRes;
}
//---------------------------------------------------------------------------
float ManagedVector3f::GetLength(ManagedVector3f^ thVec)
{
    Vector3f vec3fTemp;
    thVec->ToVector3f(vec3fTemp);

    return vec3fTemp.GetLength();
}
//---------------------------------------------------------------------------
bool ManagedVector3f::Equals(Object^ thObj)
{
    ManagedVector3f^ thVec = dynamic_cast<ManagedVector3f^>(thObj);
    if( !thVec )
    {
        return false;
    }

    Vector3f vec3fLhs, vec3fRhs;
    ToVector3f(vec3fLhs);
    thVec->ToVector3f(vec3fRhs);

    return (vec3fLhs == vec3fRhs);
}
//---------------------------------------------------------------------------