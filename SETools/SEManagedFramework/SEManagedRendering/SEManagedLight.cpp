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
#include "SEManagedLight.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedLight::ManagedLight(ManagedLight::LightType eType)
{
    m_pspLight = SE_NEW SELightPtr;
    (*m_pspLight) = SE_NEW SELight((SELight::LightType)eType);
}
//---------------------------------------------------------------------------
ManagedLight::ManagedLight(SELight* pLight)
{
    m_pspLight = SE_NEW SELightPtr;
    (*m_pspLight) = pLight;
}
//---------------------------------------------------------------------------
ManagedLight::~ManagedLight()
{
    SE_DELETE m_pspLight;
    m_pspLight = 0;
}
//---------------------------------------------------------------------------
ManagedLight::LightType ManagedLight::Type::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return (ManagedLight::LightType)(*m_pspLight)->Type;
}
//---------------------------------------------------------------------------
void ManagedLight::Type::set(ManagedLight::LightType eType)
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    (*m_pspLight)->Type = (SELight::LightType)eType;
}
//---------------------------------------------------------------------------
ManagedColorRGB^ ManagedLight::Ambient::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return gcnew ManagedColorRGB((*m_pspLight)->Ambient);
}
//---------------------------------------------------------------------------
void ManagedLight::Ambient::set(ManagedColorRGB^ thColor)
{
    SE_NULL_ARGUMENT_CHECK(thColor, "thColor");
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    thColor->ToColorRGB((*m_pspLight)->Ambient);
}
//---------------------------------------------------------------------------
ManagedColorRGB^ ManagedLight::Diffuse::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return gcnew ManagedColorRGB((*m_pspLight)->Diffuse);
}
//---------------------------------------------------------------------------
void ManagedLight::Diffuse::set(ManagedColorRGB^ thColor)
{
    SE_NULL_ARGUMENT_CHECK(thColor, "thColor");
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    thColor->ToColorRGB((*m_pspLight)->Diffuse);
}
//---------------------------------------------------------------------------
ManagedColorRGB^ ManagedLight::Specular::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return gcnew ManagedColorRGB((*m_pspLight)->Specular);
}
//---------------------------------------------------------------------------
void ManagedLight::Specular::set(ManagedColorRGB^ thColor)
{
    SE_NULL_ARGUMENT_CHECK(thColor, "thColor");
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    thColor->ToColorRGB((*m_pspLight)->Specular);
}
//---------------------------------------------------------------------------
float ManagedLight::Constant::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return (*m_pspLight)->Constant;
}
//---------------------------------------------------------------------------
void ManagedLight::Constant::set(float fValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    (*m_pspLight)->Constant = fValue;
}
//---------------------------------------------------------------------------
float ManagedLight::Linear::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return (*m_pspLight)->Linear;
}
//---------------------------------------------------------------------------
void ManagedLight::Linear::set(float fValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    (*m_pspLight)->Linear = fValue;
}
//---------------------------------------------------------------------------
float ManagedLight::Quadratic::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return (*m_pspLight)->Quadratic;
}
//---------------------------------------------------------------------------
void ManagedLight::Quadratic::set(float fValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    (*m_pspLight)->Quadratic = fValue;
}
//---------------------------------------------------------------------------
float ManagedLight::Intensity::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return (*m_pspLight)->Intensity;
}
//---------------------------------------------------------------------------
void ManagedLight::Intensity::set(float fValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    (*m_pspLight)->Intensity = fValue;
}
//---------------------------------------------------------------------------
float ManagedLight::Angle::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return (*m_pspLight)->Angle;
}
//---------------------------------------------------------------------------
void ManagedLight::Angle::set(float fValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    (*m_pspLight)->Angle = fValue;
}
//---------------------------------------------------------------------------
float ManagedLight::CosAngle::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return (*m_pspLight)->CosAngle;
}
//---------------------------------------------------------------------------
void ManagedLight::CosAngle::set(float fValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    (*m_pspLight)->CosAngle = fValue;
}
//---------------------------------------------------------------------------
float ManagedLight::SinAngle::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return (*m_pspLight)->SinAngle;
}
//---------------------------------------------------------------------------
void ManagedLight::SinAngle::set(float fValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    (*m_pspLight)->SinAngle = fValue;
}
//---------------------------------------------------------------------------
float ManagedLight::Exponent::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return (*m_pspLight)->Exponent;
}
//---------------------------------------------------------------------------
void ManagedLight::Exponent::set(float fValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    (*m_pspLight)->Exponent = fValue;
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedLight::Position::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return gcnew ManagedVector3f((*m_pspLight)->Position);
}
//---------------------------------------------------------------------------
void ManagedLight::Position::set(ManagedVector3f^ thPosition)
{
    SE_NULL_ARGUMENT_CHECK(thPosition, "thPosition");
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    thPosition->ToVector3f((*m_pspLight)->Position);
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedLight::RVector::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return gcnew ManagedVector3f((*m_pspLight)->RVector);
}
//---------------------------------------------------------------------------
void ManagedLight::RVector::set(ManagedVector3f^ thRVector)
{
    SE_NULL_ARGUMENT_CHECK(thRVector, "thRVector");
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    thRVector->ToVector3f((*m_pspLight)->RVector);
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedLight::UVector::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return gcnew ManagedVector3f((*m_pspLight)->UVector);
}
//---------------------------------------------------------------------------
void ManagedLight::UVector::set(ManagedVector3f^ thUVector)
{
    SE_NULL_ARGUMENT_CHECK(thUVector, "thUVector");
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    thUVector->ToVector3f((*m_pspLight)->UVector);
}
//---------------------------------------------------------------------------
ManagedVector3f^ ManagedLight::DVector::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return gcnew ManagedVector3f((*m_pspLight)->DVector);
}
//---------------------------------------------------------------------------
void ManagedLight::DVector::set(ManagedVector3f^ thDVector)
{
    SE_NULL_ARGUMENT_CHECK(thDVector, "thDVector");
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    thDVector->ToVector3f((*m_pspLight)->DVector);
}
//---------------------------------------------------------------------------
void ManagedLight::SetAngle(float fAngle)
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    (*m_pspLight)->SetAngle(fAngle);
}
//---------------------------------------------------------------------------
SELight* ManagedLight::GetNativeLight()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return (SELight*)(*m_pspLight);
}
//---------------------------------------------------------------------------
void ManagedLight::SetName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");

    const char* acName = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acName);
    ManagedUtility::FreeNativeCharBuffer(acName);
    (*m_pspLight)->SetName(tempName);
}
//---------------------------------------------------------------------------
String^ ManagedLight::GetName()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return gcnew String((*m_pspLight)->GetName().c_str());
}
//---------------------------------------------------------------------------
int ManagedLight::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspLight, "Native pointer is null");
    return (*m_pspLight)->GetReferences();
}
//---------------------------------------------------------------------------