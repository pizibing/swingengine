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
#include "SEManagedTextureEffect.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedTextureEffect::ManagedTextureEffect(String^ thBaseName)
{
    SE_NULL_ARGUMENT_CHECK(thBaseName, "thBaseName");

    const char* acBuffer = ManagedUtility::StringToNativeCharBuffer(
        thBaseName);
    std::string tempBaseName(acBuffer);
    ManagedUtility::FreeNativeCharBuffer(acBuffer);

    m_pspTextureEffect = SE_NEW SETextureEffectPtr;
    (*m_pspTextureEffect) = SE_NEW SETextureEffect(tempBaseName);
}
//---------------------------------------------------------------------------
ManagedTextureEffect::ManagedTextureEffect(SETextureEffect* pEffect)
{
    m_pspTextureEffect = SE_NEW SETextureEffectPtr;
    (*m_pspTextureEffect) = pEffect;
}
//---------------------------------------------------------------------------
ManagedTextureEffect::~ManagedTextureEffect()
{
    SE_DELETE m_pspTextureEffect;
    m_pspTextureEffect = 0;
}
//---------------------------------------------------------------------------
ManagedAlphaState^ ManagedTextureEffect::GetBlending(int iPass)
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureEffect, "Native pointer is null");
    return gcnew ManagedAlphaState(
        (*m_pspTextureEffect)->GetBlending(iPass));
}
//---------------------------------------------------------------------------
ManagedTexture^ ManagedTextureEffect::GetPTexture(int iPass, int i)
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureEffect, "Native pointer is null");
    return gcnew ManagedTexture((*m_pspTextureEffect)->GetPTexture(iPass, 
        i));
}
//---------------------------------------------------------------------------
ManagedTexture^ ManagedTextureEffect::GetPTexture(int iPass, String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspTextureEffect, "Native pointer is null");
    const char* acBuffer = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acBuffer);
    ManagedUtility::FreeNativeCharBuffer(acBuffer);

    return gcnew ManagedTexture((*m_pspTextureEffect)->GetPTexture(
        iPass, tempName));
}
//---------------------------------------------------------------------------
void ManagedTextureEffect::SetPTexture(int iPass, int i, 
    ManagedTexture^ thTexture)
{
    SE_NULL_ARGUMENT_CHECK(thTexture, "thTexture");
    SE_NULL_REFERENCE_CHECK(m_pspTextureEffect, "Native pointer is null");
    (*m_pspTextureEffect)->SetPTexture(iPass, i, 
        thTexture->GetNativeTexture());
}
//---------------------------------------------------------------------------
void ManagedTextureEffect::SetName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspTextureEffect, "Native pointer is null");

    const char* acName = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acName);
    ManagedUtility::FreeNativeCharBuffer(acName);
    (*m_pspTextureEffect)->SetName(tempName);
}
//---------------------------------------------------------------------------
String^ ManagedTextureEffect::GetName()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureEffect, "Native pointer is null");
    return gcnew String((*m_pspTextureEffect)->GetName().c_str());
}
//---------------------------------------------------------------------------
int ManagedTextureEffect::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureEffect, "Native pointer is null");
    return (*m_pspTextureEffect)->GetReferences();
}
//---------------------------------------------------------------------------
SEEffect* ManagedTextureEffect::GetNativeEffect()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureEffect, "Native pointer is null");
    return (SEEffect*)(*m_pspTextureEffect);
}
//---------------------------------------------------------------------------
SEShaderEffect* ManagedTextureEffect::GetNativeShaderEffect()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureEffect, "Native pointer is null");
    return (SEShaderEffect*)(*m_pspTextureEffect);
}
//---------------------------------------------------------------------------