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

//----------------------------------------------------------------------------
inline SECamera* SERenderer::GetCamera() const
{
    return m_pCamera;
}
//----------------------------------------------------------------------------
inline SEFrameBuffer::FormatType SERenderer::GetFormatType() const
{
    return m_eFormat;
}
//----------------------------------------------------------------------------
inline SEFrameBuffer::DepthType SERenderer::GetDepthType() const
{
    return m_eDepth;
}
//----------------------------------------------------------------------------
inline SEFrameBuffer::StencilType SERenderer::GetStencilType() const
{
    return m_eStencil;
}
//----------------------------------------------------------------------------
inline SEFrameBuffer::BufferingType SERenderer::GetBufferingType() const
{
    return m_eBuffering;
}
//----------------------------------------------------------------------------
inline SEFrameBuffer::MultisamplingType SERenderer::GetMultisamplingType() const
{
    return m_eMultisampling;
}
//----------------------------------------------------------------------------
inline int SERenderer::GetWidth() const
{
    return m_iWidth;
}
//----------------------------------------------------------------------------
inline int SERenderer::GetHeight() const
{
    return m_iHeight;
}
//----------------------------------------------------------------------------
inline void SERenderer::ToggleFullscreen()
{
    m_bFullscreen = !m_bFullscreen;
}
//----------------------------------------------------------------------------
inline void SERenderer::SetClearColor(const SEColorRGBA& rClearColor)
{
    m_ClearColor = rClearColor;
}
//----------------------------------------------------------------------------
inline const SEColorRGBA& SERenderer::GetClearColor() const
{
    return m_ClearColor;
}
//----------------------------------------------------------------------------
inline void SERenderer::SetClearDepth(float fClearDepth)
{
    m_fClearDepth = fClearDepth;
}
//----------------------------------------------------------------------------
inline float SERenderer::GetClearDepth() const
{
    return m_fClearDepth;
}
//----------------------------------------------------------------------------
inline void SERenderer::SetClearStencil(unsigned int uiClearStencil)
{
    m_uiClearStencil = uiClearStencil;
}
//----------------------------------------------------------------------------
inline unsigned int SERenderer::GetClearStencil() const
{
    return m_uiClearStencil;
}
//----------------------------------------------------------------------------
inline bool SERenderer::BeginScene()
{
    // 由派生类负责实现.
    return true;
}
//----------------------------------------------------------------------------
inline void SERenderer::EndScene()
{
    // 由派生类负责实现.
}
//----------------------------------------------------------------------------
inline int SERenderer::GetMaxLights() const
{
    return m_iMaxLights;
}
//----------------------------------------------------------------------------
inline int SERenderer::GetMaxColors() const
{
    return m_iMaxColors;
}
//----------------------------------------------------------------------------
inline int SERenderer::GetMaxTCoords() const
{
    return m_iMaxTCoords;
}
//----------------------------------------------------------------------------
inline int SERenderer::GetMaxVShaderImages() const
{
    return m_iMaxVShaderImages;
}
//----------------------------------------------------------------------------
inline int SERenderer::GetMaxGShaderImages() const
{
    return m_iMaxGShaderImages;
}
//----------------------------------------------------------------------------
inline int SERenderer::GetMaxPShaderImages() const
{
    return m_iMaxPShaderImages;
}
//----------------------------------------------------------------------------
inline int SERenderer::GetMaxStencilIndices() const
{
    return m_iMaxStencilIndices;
}
//----------------------------------------------------------------------------
inline int SERenderer::GetMaxUserClipPlanes() const
{
    return m_iMaxUserClipPlanes;
}
//----------------------------------------------------------------------------
inline int SERenderer::GetMaxVShaderProfile() const
{
    return m_iMaxVShaderProfile;
}
//----------------------------------------------------------------------------
inline int SERenderer::GetMaxGShaderProfile() const
{
    return m_iMaxGShaderProfile;
}
//----------------------------------------------------------------------------
inline int SERenderer::GetMaxPShaderProfile() const
{
    return m_iMaxPShaderProfile;
}
//----------------------------------------------------------------------------
inline int SERenderer::GetMaxRenderTargets() const
{
    return m_iMaxRenderTargets;
}
//----------------------------------------------------------------------------
inline bool SERenderer::HasShaderCompiler() const
{
    return m_bHasShaderCompiler;
}
//----------------------------------------------------------------------------
inline void SERenderer::SetAlphaState(SEAlphaState* pState)
{
    m_aspState[SEGlobalState::ALPHA] = pState;
}
//----------------------------------------------------------------------------
inline void SERenderer::SetCullState(SECullState* pState)
{
    m_aspState[SEGlobalState::CULL] = pState;
}
//----------------------------------------------------------------------------
inline void SERenderer::SetMaterialState(SEMaterialState* pState)
{
    m_aspState[SEGlobalState::MATERIAL] = pState;
}
//----------------------------------------------------------------------------
inline void SERenderer::SetPolygonOffsetState(SEPolygonOffsetState* pState)
{
    m_aspState[SEGlobalState::POLYGONOFFSET] = pState;
}
//----------------------------------------------------------------------------
inline void SERenderer::SetStencilState(SEStencilState* pState)
{
    m_aspState[SEGlobalState::STENCIL] = pState;
}
//----------------------------------------------------------------------------
inline void SERenderer::SetWireframeState(SEWireframeState* pState)
{
    m_aspState[SEGlobalState::WIREFRAME] = pState;
}
//----------------------------------------------------------------------------
inline void SERenderer::SetZBufferState(SEZBufferState* pState)
{
    m_aspState[SEGlobalState::ZBUFFER] = pState;
}
//----------------------------------------------------------------------------
inline SEAlphaState* SERenderer::GetAlphaState()
{
    return StaticCast<SEAlphaState>(m_aspState[SEGlobalState::ALPHA]);
}
//----------------------------------------------------------------------------
inline SECullState* SERenderer::GetCullState()
{
    return StaticCast<SECullState>(m_aspState[SEGlobalState::CULL]);
}
//----------------------------------------------------------------------------
inline SEMaterialState* SERenderer::GetMaterialState()
{
    return StaticCast<SEMaterialState>(m_aspState[SEGlobalState::MATERIAL]);
}
//----------------------------------------------------------------------------
inline SEPolygonOffsetState* SERenderer::GetPolygonOffsetState()
{
    return StaticCast<SEPolygonOffsetState>(
        m_aspState[SEGlobalState::POLYGONOFFSET]);
}
//----------------------------------------------------------------------------
inline SEStencilState* SERenderer::GetStencilState()
{
    return StaticCast<SEStencilState>(m_aspState[SEGlobalState::STENCIL]);
}
//----------------------------------------------------------------------------
inline SEWireframeState* SERenderer::GetWireframeState()
{
    return StaticCast<SEWireframeState>(m_aspState[SEGlobalState::WIREFRAME]);
}
//----------------------------------------------------------------------------
inline SEZBufferState* SERenderer::GetZBufferState()
{
    return StaticCast<SEZBufferState>(m_aspState[SEGlobalState::ZBUFFER]);
}
//----------------------------------------------------------------------------
inline void SERenderer::SetReverseCullFace(bool bReverseCullFace)
{
    m_bReverseCullFace = bReverseCullFace;
}
//----------------------------------------------------------------------------
inline bool SERenderer::GetReverseCullFace() const
{
    return m_bReverseCullFace;
}
//----------------------------------------------------------------------------
inline void SERenderer::SetLightCount(int iCount)
{
    SE_ASSERT( 0 <= iCount && iCount <= m_iMaxLights );

    m_iNumActiveLights = iCount;
}
//----------------------------------------------------------------------------
inline void SERenderer::SetLight(int i, SELight* pLight)
{
    SE_ASSERT( 0 <= i && i < m_iMaxLights );

    m_aspLight[i] = (SEObject*)pLight;
}
//----------------------------------------------------------------------------
inline SELight* SERenderer::GetLight(int i)
{
    SE_ASSERT( 0 <= i && i < m_iMaxLights );

    return StaticCast<SELight>(m_aspLight[i]);
}
//----------------------------------------------------------------------------
inline void SERenderer::SetProjector(SECamera* pProjector)
{
    m_pProjector = pProjector;
}
//----------------------------------------------------------------------------
inline SECamera* SERenderer::GetProjector()
{
    return m_pProjector;
}
//----------------------------------------------------------------------------
inline const SEMatrix4f& SERenderer::GetWorldMatrix(void) const
{
    return m_WorldMatrix;
}
//----------------------------------------------------------------------------
inline const SEMatrix4f& SERenderer::GetViewMatrix(void) const
{
    return m_ViewMatrix;
}
//----------------------------------------------------------------------------
inline const SEMatrix4f& SERenderer::GetProjectionMatrix(void) const
{
    return m_ProjectionMatrix;
}
//----------------------------------------------------------------------------