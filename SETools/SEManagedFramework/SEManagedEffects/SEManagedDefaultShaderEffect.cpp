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
#include "SEManagedDefaultShaderEffect.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedDefaultShaderEffect::ManagedDefaultShaderEffect()
{
    m_pspDefaultShaderEffect = SE_NEW DefaultShaderEffectPtr;
    (*m_pspDefaultShaderEffect) = SE_NEW DefaultShaderEffect;
}
//---------------------------------------------------------------------------
ManagedDefaultShaderEffect::~ManagedDefaultShaderEffect()
{
    SE_DELETE m_pspDefaultShaderEffect;
    m_pspDefaultShaderEffect = 0;
}
//---------------------------------------------------------------------------
ManagedAlphaState^ ManagedDefaultShaderEffect::GetBlending(int iPass)
{
    SE_NULL_REFERENCE_CHECK(m_pspDefaultShaderEffect, 
        "Native pointer is null");
    return gcnew ManagedAlphaState(
        (*m_pspDefaultShaderEffect)->GetBlending(iPass));
}
//---------------------------------------------------------------------------
int ManagedDefaultShaderEffect::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspDefaultShaderEffect, 
        "Native pointer is null");
    return (*m_pspDefaultShaderEffect)->GetReferences();
}
//---------------------------------------------------------------------------
Effect* ManagedDefaultShaderEffect::GetNativeEffect()
{
    SE_NULL_REFERENCE_CHECK(m_pspDefaultShaderEffect, 
        "Native pointer is null");
    return (Effect*)(*m_pspDefaultShaderEffect);
}
//---------------------------------------------------------------------------
ShaderEffect* ManagedDefaultShaderEffect::GetNativeShaderEffect()
{
    SE_NULL_REFERENCE_CHECK(m_pspDefaultShaderEffect, 
        "Native pointer is null");
    return (ShaderEffect*)(*m_pspDefaultShaderEffect);
}
//---------------------------------------------------------------------------