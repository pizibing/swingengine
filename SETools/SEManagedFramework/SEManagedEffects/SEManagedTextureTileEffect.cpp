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
#include "SEManagedTextureTileEffect.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedTextureTileEffect::ManagedTextureTileEffect(String^ thTileName)
{
    SE_NULL_ARGUMENT_CHECK(thTileName, "thTileName");

    const char* acBuffer = ManagedUtility::StringToNativeCharBuffer(
        thTileName);
    std::string tempTileName(acBuffer);
    ManagedUtility::FreeNativeCharBuffer(acBuffer);

    m_pspTextureTileEffect = SE_NEW SETextureTileEffectPtr;
    (*m_pspTextureTileEffect) = SE_NEW SETextureTileEffect(tempTileName);
}
//---------------------------------------------------------------------------
ManagedTextureTileEffect::ManagedTextureTileEffect(
    SETextureTileEffect* pEffect)
{
    m_pspTextureTileEffect = SE_NEW SETextureTileEffectPtr;
    (*m_pspTextureTileEffect) = pEffect;
}
//---------------------------------------------------------------------------
ManagedTextureTileEffect::~ManagedTextureTileEffect()
{
    SE_DELETE m_pspTextureTileEffect;
    m_pspTextureTileEffect = 0;
}
//---------------------------------------------------------------------------
void ManagedTextureTileEffect::SetTileImage(ManagedImage^ thImage)
{
    SE_NULL_ARGUMENT_CHECK(thImage, "thImage");
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileEffect, 
        "Native pointer is null");
    SEImage* pImage = thImage->GetNativeImage();
    SETexture* pTexture = (*m_pspTextureTileEffect)->GetPTexture(0, 0);
    (*m_pspTextureTileEffect)->SetPImageName(0, 0, pImage->GetName());
    pTexture->SetImage(pImage);
    pTexture->Release();
}
//---------------------------------------------------------------------------
float ManagedTextureTileEffect::TileX::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileEffect, 
        "Native pointer is null");
    return (*m_pspTextureTileEffect)->TileX;
}
//---------------------------------------------------------------------------
void ManagedTextureTileEffect::TileX::set(float fValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileEffect, 
        "Native pointer is null");
    (*m_pspTextureTileEffect)->TileX = fValue;
}
//---------------------------------------------------------------------------
float ManagedTextureTileEffect::TileY::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileEffect, 
        "Native pointer is null");
    return (*m_pspTextureTileEffect)->TileY;
}
//---------------------------------------------------------------------------
void ManagedTextureTileEffect::TileY::set(float fValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileEffect, 
        "Native pointer is null");
    (*m_pspTextureTileEffect)->TileY = fValue;
}
//---------------------------------------------------------------------------
ManagedAlphaState^ ManagedTextureTileEffect::GetBlending(int iPass)
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileEffect, 
        "Native pointer is null");
    return gcnew ManagedAlphaState(
        (*m_pspTextureTileEffect)->GetBlending(iPass));
}
//---------------------------------------------------------------------------
ManagedTexture^ ManagedTextureTileEffect::GetPTexture(int iPass, int i)
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileEffect, "Native pointer is null");
    return gcnew ManagedTexture((*m_pspTextureTileEffect)->GetPTexture(
        iPass, i));
}
//---------------------------------------------------------------------------
ManagedTexture^ ManagedTextureTileEffect::GetPTexture(int iPass, 
    String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileEffect, "Native pointer is null");
    const char* acBuffer = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acBuffer);
    ManagedUtility::FreeNativeCharBuffer(acBuffer);

    return gcnew ManagedTexture((*m_pspTextureTileEffect)->GetPTexture(
        iPass, tempName));
}
//---------------------------------------------------------------------------
void ManagedTextureTileEffect::SetPTexture(int iPass, int i, 
    ManagedTexture^ thTexture)
{
    SE_NULL_ARGUMENT_CHECK(thTexture, "thTexture");
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileEffect, "Native pointer is null");
    (*m_pspTextureTileEffect)->SetPTexture(iPass, i, 
        thTexture->GetNativeTexture());
}
//---------------------------------------------------------------------------
void ManagedTextureTileEffect::SetName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileEffect, "Native pointer is null");

    const char* acName = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acName);
    ManagedUtility::FreeNativeCharBuffer(acName);
    (*m_pspTextureTileEffect)->SetName(tempName);
}
//---------------------------------------------------------------------------
String^ ManagedTextureTileEffect::GetName()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileEffect, "Native pointer is null");
    return gcnew String((*m_pspTextureTileEffect)->GetName().c_str());
}
//---------------------------------------------------------------------------
int ManagedTextureTileEffect::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileEffect, "Native pointer is null");
    return (*m_pspTextureTileEffect)->GetReferences();
}
//---------------------------------------------------------------------------
SEEffect* ManagedTextureTileEffect::GetNativeEffect()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileEffect, "Native pointer is null");
    return (SEEffect*)(*m_pspTextureTileEffect);
}
//---------------------------------------------------------------------------
SEShaderEffect* ManagedTextureTileEffect::GetNativeShaderEffect()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileEffect, "Native pointer is null");
    return (SEShaderEffect*)(*m_pspTextureTileEffect);
}
//---------------------------------------------------------------------------