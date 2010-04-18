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
#include "SEMaterialEffect.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, MaterialEffect, ShaderEffect);
SE_IMPLEMENT_STREAM(MaterialEffect);
SE_IMPLEMENT_DEFAULT_STREAM(MaterialEffect, ShaderEffect);
SE_IMPLEMENT_DEFAULT_NAME_ID(MaterialEffect, ShaderEffect);

//SE_REGISTER_STREAM(MaterialEffect);

//----------------------------------------------------------------------------
MaterialEffect::MaterialEffect()
    :
    ShaderEffect()
{
}
//----------------------------------------------------------------------------
MaterialEffect::~MaterialEffect()
{
}
//----------------------------------------------------------------------------
void MaterialEffect::SetPassCount(int iPassCount)
{
    ShaderEffect::SetPassCount(iPassCount);

    m_MaterialState.resize(iPassCount);
    m_CullState.resize(iPassCount);
    m_PolygonOffsetState.resize(iPassCount);
    m_WireframeState.resize(iPassCount);
    m_StencilState.resize(iPassCount);
    m_ZBufferState.resize(iPassCount);

    for( int i = 0; i < iPassCount; i++ )
    {
        m_MaterialState[i] = 0;
        m_CullState[i] = 0;
        m_PolygonOffsetState[i] = 0;
        m_WireframeState[i] = 0;
        m_StencilState[i] = 0;
        m_ZBufferState[i] = 0;
    }
}
//----------------------------------------------------------------------------
void MaterialEffect::SetGlobalState(int iPass, SERenderer* pRenderer,
        bool bPrimaryEffect)
{
    ShaderEffect::SetGlobalState(iPass, pRenderer, bPrimaryEffect);

    if( m_MaterialState[iPass] )
    {
        SEGlobalState* pState = m_MaterialState[iPass];
        SEMaterialStatePtr spSave = pRenderer->GetMaterialState();
        pRenderer->SetMaterialState((SEMaterialState*)pState);
        m_MaterialState[iPass] = spSave;
    }

    if( m_CullState[iPass] )
    {
        SEGlobalState* pState = m_CullState[iPass];
        SECullStatePtr spSave = pRenderer->GetCullState();
        pRenderer->SetCullState((SECullState*)pState);
        m_CullState[iPass] = spSave;
    }

    if( m_PolygonOffsetState[iPass] )
    {
        SEGlobalState* pState = m_PolygonOffsetState[iPass];
        SEPolygonOffsetStatePtr spSave = pRenderer->GetPolygonOffsetState();
        pRenderer->SetPolygonOffsetState((SEPolygonOffsetState*)pState);
        m_PolygonOffsetState[iPass] = spSave;
    }

    if( m_WireframeState[iPass] )
    {
        SEGlobalState* pState = m_WireframeState[iPass];
        SEWireframeStatePtr spSave = pRenderer->GetWireframeState();
        pRenderer->SetWireframeState((SEWireframeState*)pState);
        m_WireframeState[iPass] = spSave;
    }

    if( m_StencilState[iPass] )
    {
        SEGlobalState* pState = m_StencilState[iPass];
        SEStencilStatePtr spSave = pRenderer->GetStencilState();
        pRenderer->SetStencilState((SEStencilState*)pState);
        m_StencilState[iPass] = spSave;
    }

    if( m_ZBufferState[iPass] )
    {
        SEGlobalState* pState = m_ZBufferState[iPass];
        SEZBufferStatePtr spSave = pRenderer->GetZBufferState();
        pRenderer->SetZBufferState((SEZBufferState*)pState);
        m_ZBufferState[iPass] = spSave;
    }
}
//----------------------------------------------------------------------------
void MaterialEffect::RestoreGlobalState(int iPass, SERenderer* pRenderer,
        bool bPrimaryEffect)
{
    ShaderEffect::RestoreGlobalState(iPass, pRenderer, bPrimaryEffect);

    if( m_MaterialState[iPass] )
    {
        SEGlobalState* pState = m_MaterialState[iPass];
        SEMaterialStatePtr spSave = pRenderer->GetMaterialState();
        pRenderer->SetMaterialState((SEMaterialState*)pState);
        m_MaterialState[iPass] = spSave;
    }

    if( m_CullState[iPass] )
    {
        SEGlobalState* pState = m_CullState[iPass];
        SECullStatePtr spSave = pRenderer->GetCullState();
        pRenderer->SetCullState((SECullState*)pState);
        m_CullState[iPass] = spSave;
    }

    if( m_PolygonOffsetState[iPass] )
    {
        SEGlobalState* pState = m_PolygonOffsetState[iPass];
        SEPolygonOffsetStatePtr spSave = pRenderer->GetPolygonOffsetState();
        pRenderer->SetPolygonOffsetState((SEPolygonOffsetState*)pState);
        m_PolygonOffsetState[iPass] = spSave;
    }

    if( m_WireframeState[iPass] )
    {
        SEGlobalState* pState = m_WireframeState[iPass];
        SEWireframeStatePtr spSave = pRenderer->GetWireframeState();
        pRenderer->SetWireframeState((SEWireframeState*)pState);
        m_WireframeState[iPass] = spSave;
    }

    if( m_StencilState[iPass] )
    {
        SEGlobalState* pState = m_StencilState[iPass];
        SEStencilStatePtr spSave = pRenderer->GetStencilState();
        pRenderer->SetStencilState((SEStencilState*)pState);
        m_StencilState[iPass] = spSave;
    }

    if( m_ZBufferState[iPass] )
    {
        SEGlobalState* pState = m_ZBufferState[iPass];
        SEZBufferStatePtr spSave = pRenderer->GetZBufferState();
        pRenderer->SetZBufferState((SEZBufferState*)pState);
        m_ZBufferState[iPass] = spSave;
    }
}
//----------------------------------------------------------------------------
void MaterialEffect::AttachPassGlobalState(int iPass, SEGlobalState* pState)
{
    SE_ASSERT( iPass >= 0 && iPass < m_iPassCount );
    SE_ASSERT( pState );

    SEGlobalState::StateType eType = pState->GetStateType();
    switch( eType )
    {
    case SEGlobalState::MATERIAL:
        m_MaterialState[iPass] = pState;
        break;
    case SEGlobalState::CULL:
        m_CullState[iPass] = pState;
        break;
    case SEGlobalState::POLYGONOFFSET:
        m_PolygonOffsetState[iPass] = pState;
        break;
    case SEGlobalState::WIREFRAME:
        m_WireframeState[iPass] = pState;
        break;
    case SEGlobalState::STENCIL:
        m_StencilState[iPass] = pState;
        break;
    case SEGlobalState::ZBUFFER:
        m_ZBufferState[iPass] = pState;
        break;
    default:
        break;
    }
}
//----------------------------------------------------------------------------
void MaterialEffect::DetachPassGlobalState(int iPass, 
    SEGlobalState::StateType eType)
{
    SE_ASSERT( iPass >= 0 && iPass < m_iPassCount );

    switch( eType )
    {
    case SEGlobalState::MATERIAL:
        m_MaterialState[iPass] = 0;
        break;
    case SEGlobalState::CULL:
        m_CullState[iPass] = 0;
        break;
    case SEGlobalState::POLYGONOFFSET:
        m_PolygonOffsetState[iPass] = 0;
        break;
    case SEGlobalState::WIREFRAME:
        m_WireframeState[iPass] = 0;
        break;
    case SEGlobalState::STENCIL:
        m_StencilState[iPass] = 0;
        break;
    case SEGlobalState::ZBUFFER:
        m_ZBufferState[iPass] = 0;
        break;
    default:
        break;
    }
}
//----------------------------------------------------------------------------
SEGlobalState* MaterialEffect::GetPassGlobalState(int iPass, 
    SEGlobalState::StateType eType) const
{
    SE_ASSERT( iPass >= 0 && iPass < m_iPassCount );

    switch( eType )
    {
    case SEGlobalState::MATERIAL:
        return m_MaterialState[iPass];

    case SEGlobalState::CULL:
        return m_CullState[iPass];

    case SEGlobalState::POLYGONOFFSET:
        return m_PolygonOffsetState[iPass];

    case SEGlobalState::WIREFRAME:
        return m_WireframeState[iPass];

    case SEGlobalState::STENCIL:
        return m_StencilState[iPass];

    case SEGlobalState::ZBUFFER:
        return m_ZBufferState[iPass];

    default:
        return 0;
    }
}
//----------------------------------------------------------------------------
void MaterialEffect::ConfigureShader()
{
    for( int i = 0; i < m_iPassCount; i++ )
    {
        m_VShader[i] = SE_NEW SEVertexShader("IMaterial.v_Material");
        m_PShader[i] = SE_NEW SEPixelShader("IMaterial.p_Material");
    }
}
//----------------------------------------------------------------------------
