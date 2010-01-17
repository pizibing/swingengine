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

using namespace Swing::Tools::ManagedFramework;
using namespace System::Runtime::InteropServices;

//---------------------------------------------------------------------------
ManagedTextureEffect::ManagedTextureEffect(String^ thBaseName)
{
    SE_NULL_ARGUMENT_CHECK(thBaseName, "thBaseName");

    // Native heap resource is allocated here.
    IntPtr pBaseName = Marshal::StringToHGlobalAnsi(thBaseName);
    
    std::string tempBaseName((const char*)(void*)pBaseName);

    // We've done with the native resource allocated by Marshal, free it.
    Marshal::FreeHGlobal(pBaseName);

    m_pspTextureEffect = SE_NEW Swing::TextureEffectPtr;
    (*m_pspTextureEffect) = SE_NEW Swing::TextureEffect(tempBaseName);
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
    return gcnew ManagedTexture((*m_pspTextureEffect)->GetPTexture(iPass, i));
}
//---------------------------------------------------------------------------
ManagedTexture^ ManagedTextureEffect::GetPTexture(int iPass, String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspTextureEffect, "Native pointer is null");
    return nullptr;
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
int ManagedTextureEffect::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureEffect, "Native pointer is null");
    return (*m_pspTextureEffect)->GetReferences();
}
//---------------------------------------------------------------------------
Swing::Effect* ManagedTextureEffect::GetNativeEffect()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureEffect, "Native pointer is null");
    return (Swing::Effect*)(*m_pspTextureEffect);
}
//---------------------------------------------------------------------------
Swing::ShaderEffect* ManagedTextureEffect::GetNativeShaderEffect()
{
    SE_NULL_REFERENCE_CHECK(m_pspTextureEffect, "Native pointer is null");
    return (Swing::ShaderEffect*)(*m_pspTextureEffect);
}
//---------------------------------------------------------------------------