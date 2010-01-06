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
#include "SEManagedQuaternion.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedQuaternionf::ManagedQuaternionf()
{
}
//---------------------------------------------------------------------------
ManagedQuaternionf::ManagedQuaternionf(float fW, float fX, float fY, 
    float fZ)
{
    m_fW = fW;
    m_fX = fX;
    m_fY = fY;
    m_fZ = fZ;
}
//---------------------------------------------------------------------------
ManagedQuaternionf::ManagedQuaternionf(ManagedMatrix3f^ thRotMat)
{
    FromRotationMatrix(thRotMat);
}
//---------------------------------------------------------------------------
ManagedQuaternionf::ManagedQuaternionf(const Quaternionf& rQ)
{
    FromQuaternionf(rQ);
}
//---------------------------------------------------------------------------
float ManagedQuaternionf::W::get()
{
    return m_fW;
}
//---------------------------------------------------------------------------
void ManagedQuaternionf::W::set(float fW)
{
    m_fW = fW;
}
//---------------------------------------------------------------------------
float ManagedQuaternionf::X::get()
{
    return m_fX;
}
//---------------------------------------------------------------------------
void ManagedQuaternionf::X::set(float fX)
{
    m_fX = fX;
}
//---------------------------------------------------------------------------
float ManagedQuaternionf::Y::get()
{
    return m_fY;
}
//---------------------------------------------------------------------------
void ManagedQuaternionf::Y::set(float fY)
{
    m_fY = fY;
}
//---------------------------------------------------------------------------
float ManagedQuaternionf::Z::get()
{
    return m_fZ;
}
//---------------------------------------------------------------------------
void ManagedQuaternionf::Z::set(float fZ)
{
    m_fZ = fZ;
}
//---------------------------------------------------------------------------
void ManagedQuaternionf::FromRotationMatrix(ManagedMatrix3f^ thRotMat)
{
    if( thRotMat )
    {
        Matrix3f mat3fTemp;
        thRotMat->ToMatrix3f(mat3fTemp);
        Quaternionf tempQ;
        tempQ.FromRotationMatrix(mat3fTemp);
        FromQuaternionf(tempQ);
    }
}
//---------------------------------------------------------------------------
ManagedMatrix3f^ ManagedQuaternionf::GetRotationMatrix()
{
    Quaternionf tempQ;
    ToQuaternionf(tempQ);
    Matrix3f mat3fTemp;
    tempQ.ToRotationMatrix(mat3fTemp);
    ManagedMatrix3f^ thRes = gcnew ManagedMatrix3f;
    thRes->FromMatrix3f(mat3fTemp);

    return thRes;
}
//---------------------------------------------------------------------------
void ManagedQuaternionf::ToQuaternionf(Quaternionf& rQ)
{
    rQ.W = m_fW;
    rQ.X = m_fX;
    rQ.Y = m_fY;
    rQ.Z = m_fZ;
}
//---------------------------------------------------------------------------
void ManagedQuaternionf::FromQuaternionf(const Quaternionf& rQ)
{
    m_fW = rQ.W;
    m_fX = rQ.X;
    m_fY = rQ.Y;
    m_fZ = rQ.Z;
}
//---------------------------------------------------------------------------
bool ManagedQuaternionf::Equals(Object^ thObj)
{
    ManagedQuaternionf^ thQ = dynamic_cast<ManagedQuaternionf^>(thObj);
    if( !thQ )
    {
        return false;
    }

    Quaternionf tempLhs, tempfRhs;
    ToQuaternionf(tempLhs);
    thQ->ToQuaternionf(tempfRhs);

    return (tempLhs == tempfRhs);
}
//---------------------------------------------------------------------------