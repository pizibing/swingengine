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
#include "SEManagedMatrix3.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedMatrix3f::ManagedMatrix3f()
{
    m_afData = gcnew array<float>(9);

    for( int i = 0; i < 9; i++ )
    {
        m_afData[i] = 0.0f;
    }
}
//---------------------------------------------------------------------------
ManagedMatrix3f::ManagedMatrix3f(float fM11, float fM12, float fM13,
                                 float fM21, float fM22, float fM23,
                                 float fM31, float fM32, float fM33)
{
    m_afData = gcnew array<float>(9);

    m_afData[0] = fM11;
    m_afData[1] = fM12;
    m_afData[2] = fM13;
    m_afData[3] = fM21;
    m_afData[4] = fM22;
    m_afData[5] = fM23;
    m_afData[6] = fM31;
    m_afData[7] = fM32;
    m_afData[8] = fM33;
}
//---------------------------------------------------------------------------
ManagedMatrix3f::ManagedMatrix3f(ManagedVector3f^ thAxisVec, float fAngle)
{
    m_afData = gcnew array<float>(9);

    SE_NULL_ARGUMENT_CHECK(thAxisVec, "thAxisVec");
    Vector3f vec3fAxis;
    thAxisVec->ToVector3f(vec3fAxis);
    Matrix3f mat3fTemp(vec3fAxis, fAngle);
    FromMatrix3f(mat3fTemp);
}
//---------------------------------------------------------------------------
ManagedMatrix3f::ManagedMatrix3f(const Matrix3f& rMat)
{
    FromMatrix3f(rMat);
}
//---------------------------------------------------------------------------
void ManagedMatrix3f::FromEulerAnglesXYZ(float fYAngle, float fPAngle, 
    float fRAngle)
{
    Matrix3f mat3fTemp;
    mat3fTemp.FromEulerAnglesXYZ(fYAngle, fPAngle, fRAngle);
    FromMatrix3f(mat3fTemp);
}
//---------------------------------------------------------------------------
bool ManagedMatrix3f::ToEulerAnglesXYZ(float% trfYAngle, float% trfPAngle, 
    float% trfRAngle)
{
    float fYAngle = trfYAngle;
    float fPAngle = trfPAngle;
    float fRAngle = trfRAngle;

    Matrix3f mat3fTemp;
    ToMatrix3f(mat3fTemp);
    bool bRes = mat3fTemp.ToEulerAnglesXYZ(fYAngle, fPAngle, fRAngle);

    trfYAngle = fYAngle;
    trfPAngle = fPAngle;
    trfRAngle = fRAngle;

    return bRes;
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedMatrix3f::Vector3Multiply(ManagedVector3f^ thVec, 
    ManagedMatrix3f^ thMat)
{
    SE_NULL_ARGUMENT_CHECK(thVec, "thVec");
    SE_NULL_ARGUMENT_CHECK(thMat, "thMat");

    Vector3f vec3fV, vec3fRes;
    thVec->ToVector3f(vec3fV);
    Matrix3f mat3fM;
    thMat->ToMatrix3f(mat3fM);
    vec3fRes = vec3fV * mat3fM;
    ManagedVector3f^ thRes = gcnew ManagedVector3f;
    thRes->FromVector3f(vec3fRes);

    return thRes;
}
//---------------------------------------------------------------------------
void ManagedMatrix3f::ToMatrix3f(Matrix3f& rMat)
{
    rMat[0][0] = m_afData[0];
    rMat[0][1] = m_afData[1];
    rMat[0][2] = m_afData[2];
    rMat[1][0] = m_afData[3];
    rMat[1][1] = m_afData[4];
    rMat[1][2] = m_afData[5];
    rMat[2][0] = m_afData[6];
    rMat[2][1] = m_afData[7];
    rMat[2][2] = m_afData[8];
}
//---------------------------------------------------------------------------
void ManagedMatrix3f::FromMatrix3f(const Matrix3f& rMat)
{
    m_afData[0] = rMat[0][0];
    m_afData[1] = rMat[0][1];
    m_afData[2] = rMat[0][2];
    m_afData[3] = rMat[1][0];
    m_afData[4] = rMat[1][1];
    m_afData[5] = rMat[1][2];
    m_afData[6] = rMat[2][0];
    m_afData[7] = rMat[2][1];
    m_afData[8] = rMat[2][2];
}
//---------------------------------------------------------------------------
bool ManagedMatrix3f::Equals(Object^ thObj)
{
    ManagedMatrix3f^ thMat = dynamic_cast<ManagedMatrix3f^>(thObj);
    if( !thMat )
    {
        return false;
    }

    Matrix3f mat3fLhs, mat3fRhs;
    ToMatrix3f(mat3fLhs);
    thMat->ToMatrix3f(mat3fRhs);

    return (mat3fLhs == mat3fRhs);
}
//---------------------------------------------------------------------------