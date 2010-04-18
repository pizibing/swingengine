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

#include "SEFoundationPCH.h"
#include "SELightingEffect.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, LightingEffect, ShaderEffect);
SE_IMPLEMENT_STREAM(LightingEffect);
SE_IMPLEMENT_DEFAULT_STREAM(LightingEffect, ShaderEffect);
SE_IMPLEMENT_DEFAULT_NAME_ID(LightingEffect, ShaderEffect);

//SE_REGISTER_STREAM(LightingEffect);

LightingEffect::ConfigureLighting LightingEffect::OnConfigureLighting = 0;

//----------------------------------------------------------------------------
LightingEffect::LightingEffect()
    :
    ShaderEffect(1)
{
    // 如果没有light,则Configure函数将会关闭该effect.
}
//----------------------------------------------------------------------------
LightingEffect::~LightingEffect()
{
}
//----------------------------------------------------------------------------
void LightingEffect::AttachLight(SELight* pLight)
{
    SE_ASSERT( pLight );

    // 检查是否已经存在该light.
    for( int i = 0; i < (int)m_Lights.size(); i++ )
    {
        if( m_Lights[i] == pLight )
        {
            // 存在则返回.
            return;
        }
    }

    // 不存在则加入.
    m_Lights.push_back(pLight);
}
//----------------------------------------------------------------------------
void LightingEffect::DetachLight(SELight* pLight)
{
    std::vector<SELightPtr>::iterator pIter = m_Lights.begin();
    for( /**/; pIter != m_Lights.end(); pIter++ )
    {
        if( pLight == *pIter )
        {
            m_Lights.erase(pIter);

            return;
        }
    }
}
//----------------------------------------------------------------------------
void LightingEffect::Configure(LightingMode eMode)
{
    m_eMode = eMode;

    SE_ASSERT( OnConfigureLighting );
    if( OnConfigureLighting )
    {
        OnConfigureLighting(this);
    }
}
//----------------------------------------------------------------------------