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

#include "SEOGLES2RendererPCH.h"
#include "SEOGLES2Renderer.h"
#include "SECamera.h"
#include "SEUnculledSet.h"
#include "SERendererConstant.h"
#include "SEUserConstant.h"
#include "SESamplerInformation.h"

using namespace Swing;

SE_IMPLEMENT_INITIALIZE(OGLES2Renderer);

//SE_REGISTER_INITIALIZE(OGLES2Renderer);

//----------------------------------------------------------------------------
void OGLES2Renderer::Initialize()
{
	RendererConstant::OnReleaseID =
        &OGLES2Renderer::OnReleaseRendererConstantID;
	UserConstant::OnReleaseID = &OGLES2Renderer::OnReleaseUserConstantID;
    SamplerInformation::OnReleaseID = 
        &OGLES2Renderer::OnReleaseSamplerInformationID;

    RendererConstant::OnCopyID = &OGLES2Renderer::OnCopyRendererConstantID;
    UserConstant::OnCopyID = &OGLES2Renderer::OnCopyUserConstantID;
    SamplerInformation::OnCopyID = &OGLES2Renderer::OnCopySamplerInformationID;
}
//----------------------------------------------------------------------------
OGLES2Renderer::OGLES2Renderer(FrameBuffer::FormatType eFormat,
    FrameBuffer::DepthType eDepth, FrameBuffer::StencilType eStencil,
    FrameBuffer::BufferingType eBuffering,
    FrameBuffer::MultisamplingType eMultisampling, int iWidth, int iHeight)
    :
    Renderer(eFormat, eDepth, eStencil, eBuffering, eMultisampling, iWidth, 
        iHeight)
{
}
//----------------------------------------------------------------------------
OGLES2Renderer::~OGLES2Renderer()
{
}
//----------------------------------------------------------------------------
void OGLES2Renderer::InitializeState()
{
    // 设置默认clear color.
    glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2],
        m_ClearColor[3]);

    // 查询设备各项能力.

    // 获取vertex program最大纹理数.
    m_iMaxVShaderImages = 0;
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &m_iMaxVShaderImages);

    // 获取geometry program最大纹理数.
    m_iMaxGShaderImages = 0;

    // 获取pixel program最大纹理数.
    m_iMaxPShaderImages = 0;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_iMaxPShaderImages);

    // 待实现.
    // 目前假设这两个值相等.
    m_iMaxTCoords = m_iMaxPShaderImages;

    // OpenGL ES2只支持一组顶点颜色.
    m_iMaxColors = 1;

    // Swing Engine shader管线light数为8.
    m_iMaxLights = 8;
    m_aspLight = SE_NEW ObjectPtr[m_iMaxLights];

    // 获取stencil buffer位宽.
    GLint iBits = 0;
    glGetIntegerv(GL_STENCIL_BITS, &iBits);
    m_iMaxStencilIndices = (iBits > 0 ? (1 << iBits) : 0);

    // Swing Engine shader管线此值为26.
    m_iMaxUserClipPlanes = 26;

    // 获取vertex program profile.
    m_iMaxVShaderProfile = -1;

    // 获取geometry program profile.
    m_iMaxGShaderProfile = -1;

    // 获取fragment program profile.
    m_iMaxPShaderProfile = -1;

    // OpenGL ES2不支持MRT.	
    m_iMaxRenderTargets = 1;

    m_iMaxActiveSamplerCount = m_iMaxVShaderImages + m_iMaxPShaderImages;
    if( m_iMaxActiveSamplerCount > 0 )
    {
        m_apActiveSamplers =
            SE_NEW SamplerInformation*[m_iMaxActiveSamplerCount];

        memset(m_apActiveSamplers, 0, m_iMaxActiveSamplerCount*
            sizeof(SamplerInformation*));
    }

    // 检查是否具备shader compiler.
    glGetBooleanv(GL_SHADER_COMPILER, (GLboolean*)&m_bHasShaderCompiler);

    // 初始化全局渲染状态为引擎默认设置.
    SetGlobalState(GlobalState::Default);
}
//----------------------------------------------------------------------------
void OGLES2Renderer::ClearBackBuffer()
{
    glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2],
        m_ClearColor[3]);

    glClear(GL_COLOR_BUFFER_BIT);
}
//----------------------------------------------------------------------------
void OGLES2Renderer::ClearZBuffer()
{
    glClearDepthf((GLclampf)m_fClearDepth);

    glClear(GL_DEPTH_BUFFER_BIT);
}
//----------------------------------------------------------------------------
void OGLES2Renderer::ClearStencilBuffer()
{
    glClearStencil((GLint)m_uiClearStencil);

    glClear(GL_STENCIL_BUFFER_BIT);
}
//----------------------------------------------------------------------------
void OGLES2Renderer::ClearBuffers()
{
    glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2],
        m_ClearColor[3]);
    glClearDepthf((GLclampf)m_fClearDepth);
    glClearStencil((GLint)m_uiClearStencil);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}
//----------------------------------------------------------------------------
void OGLES2Renderer::ClearBackBuffer(int iXPos, int iYPos, int iWidth,
    int iHeight)
{
    glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2],
        m_ClearColor[3]);

    glEnable(GL_SCISSOR_TEST);
    glScissor(iXPos, iYPos, iWidth, iHeight);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void OGLES2Renderer::ClearZBuffer(int iXPos, int iYPos, int iWidth,
    int iHeight)
{
    glClearDepthf((GLclampf)m_fClearDepth);

    glEnable(GL_SCISSOR_TEST);
    glScissor(iXPos, iYPos, iWidth, iHeight);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void OGLES2Renderer::ClearStencilBuffer(int iXPos, int iYPos, int iWidth,
    int iHeight)
{
    glClearStencil((GLint)m_uiClearStencil);

    glEnable(GL_SCISSOR_TEST);
    glScissor(iXPos, iYPos, iWidth, iHeight);
    glClear(GL_STENCIL_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void OGLES2Renderer::ClearBuffers(int iXPos, int iYPos, int iWidth,
    int iHeight)
{
    glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2],
        m_ClearColor[3]);
    glClearDepthf((GLclampf)m_fClearDepth);
    glClearStencil((GLint)m_uiClearStencil);

    glEnable(GL_SCISSOR_TEST);
    glScissor(iXPos, iYPos, iWidth, iHeight);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glStencilMask((GLuint)~0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void OGLES2Renderer::SetColorMask(bool bAllowRed, bool bAllowGreen,
    bool bAllowBlue, bool bAllowAlpha)
{
    Renderer::SetColorMask(bAllowRed, bAllowGreen, bAllowBlue, bAllowAlpha);

    glColorMask((GLboolean)bAllowRed, (GLboolean)bAllowGreen,
        (GLboolean)bAllowBlue, (GLboolean)bAllowAlpha);
}
//----------------------------------------------------------------------------
void OGLES2Renderer::EnableUserClipPlane(int, const Plane3f&)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void OGLES2Renderer::DisableUserClipPlane(int)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnPreDrawGeometry()
{
    RenderStateBlock* pRStateBlock = m_pGeometry->RStateBlock;
    SE_ASSERT( pRStateBlock );

    SetGlobalState(pRStateBlock->States);
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnPostDrawGeometry()
{
    RenderStateBlock* pRStateBlock = m_pGeometry->RStateBlock;
    SE_ASSERT( pRStateBlock );

    RestoreGlobalState(pRStateBlock->States);
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnPreDrawPass(ShaderEffect* pEffect, int iPass,
    bool bPrimaryEffect)
{
    pEffect->SetGlobalState(iPass, this, bPrimaryEffect);
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnPostDrawPass(ShaderEffect* pEffect, int iPass,
    bool bPrimaryEffect)
{
    pEffect->RestoreGlobalState(iPass, this, bPrimaryEffect);
}
//----------------------------------------------------------------------------