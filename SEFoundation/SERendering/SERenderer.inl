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
inline Camera* Renderer::GetCamera() const
{
    return m_pCamera;
}
//----------------------------------------------------------------------------
inline FrameBuffer::FormatType Renderer::GetFormatType() const
{
    return m_eFormat;
}
//----------------------------------------------------------------------------
inline FrameBuffer::DepthType Renderer::GetDepthType() const
{
    return m_eDepth;
}
//----------------------------------------------------------------------------
inline FrameBuffer::StencilType Renderer::GetStencilType() const
{
    return m_eStencil;
}
//----------------------------------------------------------------------------
inline FrameBuffer::BufferingType Renderer::GetBufferingType() const
{
    return m_eBuffering;
}
//----------------------------------------------------------------------------
inline FrameBuffer::MultisamplingType Renderer::GetMultisamplingType() const
{
    return m_eMultisampling;
}
//----------------------------------------------------------------------------
inline int Renderer::GetWidth() const
{
    return m_iWidth;
}
//----------------------------------------------------------------------------
inline int Renderer::GetHeight() const
{
    return m_iHeight;
}
//----------------------------------------------------------------------------
inline void Renderer::ToggleFullscreen()
{
    m_bFullscreen = !m_bFullscreen;
}
//----------------------------------------------------------------------------
inline void Renderer::SetClearColor(const ColorRGBA& rClearColor)
{
    m_ClearColor = rClearColor;
}
//----------------------------------------------------------------------------
inline const ColorRGBA& Renderer::GetClearColor() const
{
    return m_ClearColor;
}
//----------------------------------------------------------------------------
inline void Renderer::SetClearDepth(float fClearDepth)
{
    m_fClearDepth = fClearDepth;
}
//----------------------------------------------------------------------------
inline float Renderer::GetClearDepth() const
{
    return m_fClearDepth;
}
//----------------------------------------------------------------------------
inline void Renderer::SetClearStencil(unsigned int uiClearStencil)
{
    m_uiClearStencil = uiClearStencil;
}
//----------------------------------------------------------------------------
inline unsigned int Renderer::GetClearStencil() const
{
    return m_uiClearStencil;
}
//----------------------------------------------------------------------------
inline bool Renderer::BeginScene()
{
    // 由派生类负责实现.
    return true;
}
//----------------------------------------------------------------------------
inline void Renderer::EndScene()
{
    // 由派生类负责实现.
}
//----------------------------------------------------------------------------
inline int Renderer::GetMaxLights() const
{
    return m_iMaxLights;
}
//----------------------------------------------------------------------------
inline int Renderer::GetMaxColors() const
{
    return m_iMaxColors;
}
//----------------------------------------------------------------------------
inline int Renderer::GetMaxTCoords() const
{
    return m_iMaxTCoords;
}
//----------------------------------------------------------------------------
inline int Renderer::GetMaxVShaderImages() const
{
    return m_iMaxVShaderImages;
}
//----------------------------------------------------------------------------
inline int Renderer::GetMaxGShaderImages() const
{
    return m_iMaxGShaderImages;
}
//----------------------------------------------------------------------------
inline int Renderer::GetMaxPShaderImages() const
{
    return m_iMaxPShaderImages;
}
//----------------------------------------------------------------------------
inline int Renderer::GetMaxStencilIndices() const
{
    return m_iMaxStencilIndices;
}
//----------------------------------------------------------------------------
inline int Renderer::GetMaxUserClipPlanes() const
{
    return m_iMaxUserClipPlanes;
}
//----------------------------------------------------------------------------
inline int Renderer::GetMaxVShaderProfile() const
{
    return m_iMaxVShaderProfile;
}
//----------------------------------------------------------------------------
inline int Renderer::GetMaxGShaderProfile() const
{
    return m_iMaxGShaderProfile;
}
//----------------------------------------------------------------------------
inline int Renderer::GetMaxPShaderProfile() const
{
    return m_iMaxPShaderProfile;
}
//----------------------------------------------------------------------------
inline int Renderer::GetMaxRenderTargets() const
{
    return m_iMaxRenderTargets;
}
//----------------------------------------------------------------------------
inline bool Renderer::HasShaderCompiler() const
{
    return m_bHasShaderCompiler;
}
//----------------------------------------------------------------------------
inline void Renderer::SetAlphaState(AlphaState* pState)
{
    m_aspState[GlobalState::ALPHA] = pState;
}
//----------------------------------------------------------------------------
inline void Renderer::SetCullState(CullState* pState)
{
    m_aspState[GlobalState::CULL] = pState;
}
//----------------------------------------------------------------------------
inline void Renderer::SetMaterialState(MaterialState* pState)
{
    m_aspState[GlobalState::MATERIAL] = pState;
}
//----------------------------------------------------------------------------
inline void Renderer::SetPolygonOffsetState(PolygonOffsetState* pState)
{
    m_aspState[GlobalState::POLYGONOFFSET] = pState;
}
//----------------------------------------------------------------------------
inline void Renderer::SetStencilState(StencilState* pState)
{
    m_aspState[GlobalState::STENCIL] = pState;
}
//----------------------------------------------------------------------------
inline void Renderer::SetWireframeState(WireframeState* pState)
{
    m_aspState[GlobalState::WIREFRAME] = pState;
}
//----------------------------------------------------------------------------
inline void Renderer::SetZBufferState(ZBufferState* pState)
{
    m_aspState[GlobalState::ZBUFFER] = pState;
}
//----------------------------------------------------------------------------
inline AlphaState* Renderer::GetAlphaState()
{
    return StaticCast<AlphaState>(m_aspState[GlobalState::ALPHA]);
}
//----------------------------------------------------------------------------
inline CullState* Renderer::GetCullState()
{
    return StaticCast<CullState>(m_aspState[GlobalState::CULL]);
}
//----------------------------------------------------------------------------
inline MaterialState* Renderer::GetMaterialState()
{
    return StaticCast<MaterialState>(m_aspState[GlobalState::MATERIAL]);
}
//----------------------------------------------------------------------------
inline PolygonOffsetState* Renderer::GetPolygonOffsetState()
{
    return StaticCast<PolygonOffsetState>(
        m_aspState[GlobalState::POLYGONOFFSET]);
}
//----------------------------------------------------------------------------
inline StencilState* Renderer::GetStencilState()
{
    return StaticCast<StencilState>(m_aspState[GlobalState::STENCIL]);
}
//----------------------------------------------------------------------------
inline WireframeState* Renderer::GetWireframeState()
{
    return StaticCast<WireframeState>(m_aspState[GlobalState::WIREFRAME]);
}
//----------------------------------------------------------------------------
inline ZBufferState* Renderer::GetZBufferState()
{
    return StaticCast<ZBufferState>(m_aspState[GlobalState::ZBUFFER]);
}
//----------------------------------------------------------------------------
inline void Renderer::SetReverseCullFace(bool bReverseCullFace)
{
    m_bReverseCullFace = bReverseCullFace;
}
//----------------------------------------------------------------------------
inline bool Renderer::GetReverseCullFace() const
{
    return m_bReverseCullFace;
}
//----------------------------------------------------------------------------
inline void Renderer::SetLightCount(int iCount)
{
    SE_ASSERT( 0 <= iCount && iCount <= m_iMaxLights );

    m_iNumActiveLights = iCount;
}
//----------------------------------------------------------------------------
inline void Renderer::SetLight(int i, Light* pLight)
{
    SE_ASSERT( 0 <= i && i < m_iMaxLights );

    m_aspLight[i] = (SEObject*)pLight;
}
//----------------------------------------------------------------------------
inline Light* Renderer::GetLight(int i)
{
    SE_ASSERT( 0 <= i && i < m_iMaxLights );

    return StaticCast<Light>(m_aspLight[i]);
}
//----------------------------------------------------------------------------
inline void Renderer::SetProjector(Camera* pProjector)
{
    m_pProjector = pProjector;
}
//----------------------------------------------------------------------------
inline Camera* Renderer::GetProjector()
{
    return m_pProjector;
}
//----------------------------------------------------------------------------
inline const Matrix4f& Renderer::GetWorldMatrix(void) const
{
    return m_WorldMatrix;
}
//----------------------------------------------------------------------------
inline const Matrix4f& Renderer::GetViewMatrix(void) const
{
    return m_ViewMatrix;
}
//----------------------------------------------------------------------------
inline const Matrix4f& Renderer::GetProjectionMatrix(void) const
{
    return m_ProjectionMatrix;
}
//----------------------------------------------------------------------------