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
#include "SEManagedTextureTileL1Effect.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedTextureTileL1Effect::ManagedTextureTileL1Effect(String^ thTileName)
{
    SE_NULL_ARGUMENT_CHECK(thTileName, "thTileName");

    const char* acBuffer = ManagedUtility::StringToNativeCharBuffer(
        thTileName);
    std::string tempTileName(acBuffer);
    ManagedUtility::FreeNativeCharBuffer(acBuffer);

    m_pspTextureTileL1Effect = SE_NEW TextureTileL1EffectPtr;
    (*m_pspTextureTileL1Effect) = SE_NEW TextureTileL1Effect(tempTileName);
}
//---------------------------------------------------------------------------
ManagedTextureTileL1Effect::ManagedTextureTileL1Effect(
    TextureTileL1Effect* pEffect)
{
    m_pspTextureTileL1Effect = SE_NEW TextureTileL1EffectPtr;
    (*m_pspTextureTileL1Effect) = pEffect;
}
//---------------------------------------------------------------------------
ManagedTextureTileL1Effect::~ManagedTextureTileL1Effect()
{
    SE_DELETE m_pspTextureTileL1Effect;
    m_pspTextureTileL1Effect = 0;
}
//---------------------------------------------------------------------------
void ManagedTextureTileL1Effect::SetTileImage(ManagedImage^ thImage)
{
    SE_NULL_ARGUMENT_CHECK(thImage, "thImage");
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileL1Effect, 
        "Native pointer is null");
    Image* pImage = thImage->GetNativeImage();
    Texture* pTexture = (*m_pspTextureTileL1Effect)->GetPTexture(0, 0);
    (*m_pspTextureTileL1Effect)->SetPImageName(0, 0, pImage->GetName());
    pTexture->SetImage(pImage);
    pTexture->Release();
}
//---------------------------------------------------------------------------
float ManagedTextureTileL1Effect::TileX::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileL1Effect, 
        "Native pointer is null");
    return (*m_pspTextureTileL1Effect)->TileX;
}
//---------------------------------------------------------------------------
void ManagedTextureTileL1Effect::TileX::set(float fValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileL1Effect, 
        "Native pointer is null");
    (*m_pspTextureTileL1Effect)->TileX = fValue;
}
//---------------------------------------------------------------------------
float ManagedTextureTileL1Effect::TileY::get()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileL1Effect, 
        "Native pointer is null");
    return (*m_pspTextureTileL1Effect)->TileY;
}
//---------------------------------------------------------------------------
void ManagedTextureTileL1Effect::TileY::set(float fValue)
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileL1Effect, 
        "Native pointer is null");
    (*m_pspTextureTileL1Effect)->TileY = fValue;
}
//---------------------------------------------------------------------------
ManagedAlphaState^ ManagedTextureTileL1Effect::GetBlending(int iPass)
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileL1Effect, 
        "Native pointer is null");
    return gcnew ManagedAlphaState(
        (*m_pspTextureTileL1Effect)->GetBlending(iPass));
}
//---------------------------------------------------------------------------
ManagedTexture^ ManagedTextureTileL1Effect::GetPTexture(int iPass, int i)
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileL1Effect, "Native pointer is null");
    return gcnew ManagedTexture((*m_pspTextureTileL1Effect)->GetPTexture(
        iPass, i));
}
//---------------------------------------------------------------------------
ManagedTexture^ ManagedTextureTileL1Effect::GetPTexture(int iPass, 
    String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileL1Effect, "Native pointer is null");
    const char* acBuffer = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acBuffer);
    ManagedUtility::FreeNativeCharBuffer(acBuffer);

    return gcnew ManagedTexture((*m_pspTextureTileL1Effect)->GetPTexture(
        iPass, tempName));
}
//---------------------------------------------------------------------------
void ManagedTextureTileL1Effect::SetPTexture(int iPass, int i, 
    ManagedTexture^ thTexture)
{
    SE_NULL_ARGUMENT_CHECK(thTexture, "thTexture");
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileL1Effect, "Native pointer is null");
    (*m_pspTextureTileL1Effect)->SetPTexture(iPass, i, 
        thTexture->GetNativeTexture());
}
//---------------------------------------------------------------------------
void ManagedTextureTileL1Effect::SetName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileL1Effect, "Native pointer is null");

    const char* acName = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acName);
    ManagedUtility::FreeNativeCharBuffer(acName);
    (*m_pspTextureTileL1Effect)->SetName(tempName);
}
//---------------------------------------------------------------------------
String^ ManagedTextureTileL1Effect::GetName()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileL1Effect, "Native pointer is null");
    return gcnew String((*m_pspTextureTileL1Effect)->GetName().c_str());
}
//---------------------------------------------------------------------------
int ManagedTextureTileL1Effect::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileL1Effect, "Native pointer is null");
    return (*m_pspTextureTileL1Effect)->GetReferences();
}
//---------------------------------------------------------------------------
Effect* ManagedTextureTileL1Effect::GetNativeEffect()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileL1Effect, "Native pointer is null");
    return (Effect*)(*m_pspTextureTileL1Effect);
}
//---------------------------------------------------------------------------
ShaderEffect* ManagedTextureTileL1Effect::GetNativeShaderEffect()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureTileL1Effect, "Native pointer is null");
    return (ShaderEffect*)(*m_pspTextureTileL1Effect);
}
//---------------------------------------------------------------------------