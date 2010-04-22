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

#include "SEOGLES1RendererPCH.h"
#include "SEOGLES1Renderer.h"
#include "SEOGLES1FixedEffect.h"
#include "SECamera.h"
#include "SEUnculledSet.h"
#include "SESamplerInformation.h"

using namespace Swing;

SE_IMPLEMENT_INITIALIZE(SEOGLES1Renderer);

//SE_REGISTER_INITIALIZE(SEOGLES1Renderer);

//----------------------------------------------------------------------------
void SEOGLES1Renderer::Initialize()
{
    SESamplerInformation::OnReleaseID = 
        &SEOGLES1Renderer::OnReleaseSamplerInformationID;
}
//----------------------------------------------------------------------------
SEOGLES1Renderer::SEOGLES1Renderer(SEFrameBuffer::FormatType eFormat,
    SEFrameBuffer::DepthType eDepth, SEFrameBuffer::StencilType eStencil,
    SEFrameBuffer::BufferingType eBuffering,
    SEFrameBuffer::MultisamplingType eMultisampling, int iWidth, int iHeight)
    :
    SERenderer(eFormat, eDepth, eStencil, eBuffering, eMultisampling, iWidth, 
        iHeight)
{
}
//----------------------------------------------------------------------------
SEOGLES1Renderer::~SEOGLES1Renderer()
{
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::InitializeState()
{
    // 顶点数组总是存在.
    glEnableClientState(GL_VERTEX_ARRAY);

    // 关闭颜色数组,当前颜色默认为白色.
    glDisableClientState(GL_COLOR_ARRAY);
    const SEColorRGBA& rDefaultColor = SEColorRGBA::SE_RGBA_WHITE;
    glColor4f(rDefaultColor.R, rDefaultColor.G, rDefaultColor.B,
        rDefaultColor.A);
    glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2],
        m_ClearColor[3]);

    // 关闭法线数组.
    glDisableClientState(GL_NORMAL_ARRAY);

    // 查询设备各项能力.

    // 获取vertex program最大纹理数.
    m_iMaxVShaderImages = 0;

    // 获取geometry program最大纹理数.
    m_iMaxGShaderImages = 0;

    // 获取pixel program最大纹理数.
    m_iMaxPShaderImages = 0;

    m_iMaxTCoords = 0;

    // OpenGL ES1只支持一组顶点颜色.
    m_iMaxColors = 1;

    GLint iMaxLights;
    glGetIntegerv(GL_MAX_LIGHTS, &iMaxLights);
    SE_ASSERT( iMaxLights > 0 );
    m_iMaxLights = (int)iMaxLights;
    m_aspLight = SE_NEW SEObjectPtr[m_iMaxLights];

    // 设置lighting model.关闭lighting.
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, 
        (const float*)SEColorRGBA::SE_RGBA_BLACK);
    glDisable(GL_LIGHTING);

    // 获取stencil buffer位宽.
    GLint iBits = 0;
    glGetIntegerv(GL_STENCIL_BITS, &iBits);
    m_iMaxStencilIndices = (iBits > 0 ? (1 << iBits) : 0);

    GLint iMaxUseClipPlanes = 0;
    glGetIntegerv(GL_MAX_CLIP_PLANES, &iMaxUseClipPlanes);
    m_iMaxUserClipPlanes = (int)iMaxUseClipPlanes;

    // 获取vertex program profile.
    m_iMaxVShaderProfile = -1;

    // 获取geometry program profile.
    m_iMaxGShaderProfile = -1;

    // 获取fragment program profile.
    m_iMaxPShaderProfile = -1;

    // OpenGL ES1不支持MRT.	
    m_iMaxRenderTargets = 1;

    // 初始化全局渲染状态为引擎默认设置.
    SetGlobalState(SEGlobalState::Default);
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::ClearBackBuffer()
{
    glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2],
        m_ClearColor[3]);

    glClear(GL_COLOR_BUFFER_BIT);
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::ClearZBuffer()
{
    glClearDepthf((GLclampf)m_fClearDepth);

    glClear(GL_DEPTH_BUFFER_BIT);
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::ClearStencilBuffer()
{
    glClearStencil((GLint)m_uiClearStencil);

    glClear(GL_STENCIL_BUFFER_BIT);
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::ClearBuffers()
{
    glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2],
        m_ClearColor[3]);
    glClearDepthf((GLclampf)m_fClearDepth);
    glClearStencil((GLint)m_uiClearStencil);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::ClearBackBuffer(int iXPos, int iYPos, int iWidth,
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
void SEOGLES1Renderer::ClearZBuffer(int iXPos, int iYPos, int iWidth,
    int iHeight)
{
    glClearDepthf((GLclampf)m_fClearDepth);

    glEnable(GL_SCISSOR_TEST);
    glScissor(iXPos, iYPos, iWidth, iHeight);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::ClearStencilBuffer(int iXPos, int iYPos, int iWidth,
    int iHeight)
{
    glClearStencil((GLint)m_uiClearStencil);

    glEnable(GL_SCISSOR_TEST);
    glScissor(iXPos, iYPos, iWidth, iHeight);
    glClear(GL_STENCIL_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::ClearBuffers(int iXPos, int iYPos, int iWidth,
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
void SEOGLES1Renderer::SetColorMask(bool bAllowRed, bool bAllowGreen,
    bool bAllowBlue, bool bAllowAlpha)
{
    SERenderer::SetColorMask(bAllowRed, bAllowGreen, bAllowBlue, bAllowAlpha);

    glColorMask((GLboolean)bAllowRed, (GLboolean)bAllowGreen,
        (GLboolean)bAllowBlue, (GLboolean)bAllowAlpha);
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::EnableUserClipPlane(int i, const SEPlane3f& rPlane)
{
    GLfloat afPlane[4] =
    {
        rPlane.Normal.X,
        rPlane.Normal.Y,
        rPlane.Normal.Z,
        -rPlane.Constant
    };
    glClipPlanef(GL_CLIP_PLANE0 + i, afPlane);
    glEnable(GL_CLIP_PLANE0 + i);
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::DisableUserClipPlane(int i)
{
    glDisable(GL_CLIP_PLANE0 + i);
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::OnReleaseSamplerInformationID(void* pID)
{
    SESamplerInformationID* pSIID = (SESamplerInformationID*)pID;
    SE_DELETE pSIID;
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::OnPreDrawGeometry()
{
    SERenderStateBlock* pRStateBlock = m_pGeometry->RStateBlock;
    SE_ASSERT( pRStateBlock );

    SetGlobalState(pRStateBlock->States);
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::OnPostDrawGeometry()
{
    SERenderStateBlock* pRStateBlock = m_pGeometry->RStateBlock;
    SE_ASSERT( pRStateBlock );

    RestoreGlobalState(pRStateBlock->States);
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::OnPreDrawPass(SEShaderEffect* pEffect, int iPass,
    bool bPrimaryEffect)
{
    pEffect->SetGlobalState(iPass, this, bPrimaryEffect);
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::OnPostDrawPass(SEShaderEffect* pEffect, int iPass,
    bool bPrimaryEffect)
{
    pEffect->RestoreGlobalState(iPass, this, bPrimaryEffect);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// 对象渲染入口
//----------------------------------------------------------------------------
void SEOGLES1Renderer::DrawScene(SEUnculledSet& rVisibleSet)
{
    const int iVisibleCount = rVisibleSet.GetCount();
    SEUnculledObject* pVisibleSet = rVisibleSet.GetUnculled();
    for( int i = 0; i < iVisibleCount; i++ )
    {
        if( pVisibleSet[i].IsRenderable() )
        {
            Draw((SEGeometry*)pVisibleSet[i].Object);
        }
    }
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::ApplyFixedEffect(SEOGLES1FixedEffect* pEffect, bool&)
{
    // 开启light.
    int iLCount = pEffect->GetLightCount();
    if( iLCount > 0 )
    {
        EnableLightingFixed();

        for( int i = 0; i < iLCount; i++ )
        {
            SetLightingStateFixed(i, pEffect->GetLight(i));
        }
    }

    // Keep track of the current sampler to be used in enabling the textures.
    m_iCurrentSampler = 0;

    // 开启texture.
    int iTCount = pEffect->GetTextureCount();
    for( int i = 0; i < iTCount; i++ )
    {
        SETexture* pTexture = pEffect->GetTexture(i);
        if( pTexture )
        {
            EnableTexture(pTexture);
            m_iCurrentSampler++;
        }
    }

    // 设置固定管线WVP变换矩阵.
    SetWVPMatrixFixed();

    // 渲染.
    DrawElements();

    // Keep track of the current sampler to be used in enabling the textures.
    m_iCurrentSampler = 0;

    // 关闭texture.
    for( int i = 0; i < iTCount; i++ )
    {
        SETexture* pTexture = pEffect->GetTexture(i);
        if( pTexture )
        {
            DisableTexture(pTexture);
            m_iCurrentSampler++;
        }
    }

    // 关闭light.
    if( iLCount > 0 )
    {
        for( int i = 0; i < iLCount; i++ )
        {
            RestoreLightingStateFixed(i, pEffect->GetLight(i));
        }

        DisableLightingFixed();
    }
}
//----------------------------------------------------------------------------
void SEOGLES1Renderer::Draw(SEGeometry* pGeometry)
{
    // 引用当前可渲染对象,供其它函数使用.
    m_pGeometry = pGeometry;

    // per-geometry pre-draw,渲染器派生类自定义行为入口.
    OnPreDrawGeometry();

    // 更新世界变换矩阵.
    SetWorldTransformation();

    // 开启当前可渲染对象的IB.
    // 所有应用于当前可渲染对象的effect和每个effect的所有pass都将使用该IB.
    EnableIBuffer();

    // 开启当前可渲染对象的VB.
    const SEAttributes& rAttr = m_pGeometry->VBuffer->GetAttributes();
    SEResourceIdentifier* pID = EnableVBuffer(rAttr, rAttr, 0);

    bool bPrimaryEffect = true;
    const int iMin = m_pGeometry->GetStartEffect();
    const int iMax = m_pGeometry->GetEffectCount();
    for( int i = iMin; i < iMax; i++ )
    {
        // effect必须是OpenGL ES1 fixed effect.
        SEOGLES1FixedEffect* pEffect = 
            DynamicCast<SEOGLES1FixedEffect>(m_pGeometry->GetEffect(i));
        ApplyFixedEffect(pEffect, bPrimaryEffect);
    }

    // 关闭当前可渲染对象的VB.
    DisableVBuffer(pID);

    // 关闭当前可渲染对象的IB.
    DisableIBuffer();

    // 恢复之前的世界变换矩阵.
    RestoreWorldTransformation();

    // per-geometry post-draw,渲染器派生类自定义行为入口.
    OnPostDrawGeometry();

    // 渲染完毕,解除引用当前可渲染对象.
    m_pGeometry = 0;
}
//----------------------------------------------------------------------------
