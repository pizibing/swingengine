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
#include "SEManagedTexture.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedTexture::ManagedTexture()
{
    m_pspTexture = SE_NEW SETexturePtr;
    (*m_pspTexture) = SE_NEW SETexture;
}
//---------------------------------------------------------------------------
ManagedTexture::ManagedTexture(SETexture* pTexture)
{
    m_pspTexture = SE_NEW SETexturePtr;
    (*m_pspTexture) = pTexture;
}
//---------------------------------------------------------------------------
ManagedTexture::~ManagedTexture()
{
    SE_DELETE m_pspTexture;
    m_pspTexture = 0;
}
//---------------------------------------------------------------------------
void ManagedTexture::SetFilterType(ManagedTexture::FilterType eFType)
{
    SE_NULL_REFERENCE_CHECK(m_pspTexture, "Native pointer is null");
    (*m_pspTexture)->SetFilterType((SETexture::FilterType)eFType);
}
//---------------------------------------------------------------------------
ManagedTexture::FilterType ManagedTexture::GetFilterType()
{
    SE_NULL_REFERENCE_CHECK(m_pspTexture, "Native pointer is null");
    return (ManagedTexture::FilterType)(*m_pspTexture)->GetFilterType();
}
//---------------------------------------------------------------------------
void ManagedTexture::SetWrapType(int i, ManagedTexture::WrapType eWType)
{
    SE_NULL_REFERENCE_CHECK(m_pspTexture, "Native pointer is null");
    (*m_pspTexture)->SetWrapType(i, (SETexture::WrapType)eWType);
}
//---------------------------------------------------------------------------
ManagedTexture::WrapType ManagedTexture::GetWrapType(int i)
{
    SE_NULL_REFERENCE_CHECK(m_pspTexture, "Native pointer is null");
    return (ManagedTexture::WrapType)(*m_pspTexture)->GetWrapType(i);
}
//---------------------------------------------------------------------------
void ManagedTexture::SetBorderColor(ManagedColorRGBA^ thBorderColor)
{
    SE_NULL_ARGUMENT_CHECK(thBorderColor, "thBorderColor");
    SE_NULL_REFERENCE_CHECK(m_pspTexture, "Native pointer is null");
    SEColorRGBA tempBorderColor;
    thBorderColor->ToColorRGBA(tempBorderColor);
    (*m_pspTexture)->SetBorderColor(tempBorderColor);
}
//---------------------------------------------------------------------------
ManagedColorRGBA^ ManagedTexture::GetBorderColor()
{
    SE_NULL_REFERENCE_CHECK(m_pspTexture, "Native pointer is null");
    return gcnew ManagedColorRGBA((*m_pspTexture)->GetBorderColor());
}
//---------------------------------------------------------------------------
bool ManagedTexture::IsOffscreenTexture()
{
    SE_NULL_REFERENCE_CHECK(m_pspTexture, "Native pointer is null");
    return (*m_pspTexture)->IsOffscreenTexture();
}
//---------------------------------------------------------------------------
void ManagedTexture::SetOffscreenTexture(bool bOffscreenTexture)
{
    SE_NULL_REFERENCE_CHECK(m_pspTexture, "Native pointer is null");
    (*m_pspTexture)->SetOffscreenTexture(bOffscreenTexture);
}
//---------------------------------------------------------------------------
void ManagedTexture::SetName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspTexture, "Native pointer is null");

    const char* acName = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acName);
    ManagedUtility::FreeNativeCharBuffer(acName);
    (*m_pspTexture)->SetName(tempName);
}
//---------------------------------------------------------------------------
String^ ManagedTexture::GetName()
{
    SE_NULL_REFERENCE_CHECK(m_pspTexture, "Native pointer is null");
    return gcnew String((*m_pspTexture)->GetName().c_str());
}
//---------------------------------------------------------------------------
int ManagedTexture::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspTexture, "Native pointer is null");
    return (*m_pspTexture)->GetReferences();
}
//---------------------------------------------------------------------------
SETexture* ManagedTexture::GetNativeTexture()
{
    SE_NULL_REFERENCE_CHECK(m_pspTexture, "Native pointer is null");
    return (SETexture*)(*m_pspTexture);
}
//---------------------------------------------------------------------------