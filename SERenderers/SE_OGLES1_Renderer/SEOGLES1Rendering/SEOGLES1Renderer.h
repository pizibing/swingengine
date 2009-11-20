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

#ifndef Swing_OGLES1Renderer_H
#define Swing_OGLES1Renderer_H

// 待实现.
// 我们暂时没有OpenGL ES1的封装器.
// 因此使用平台SDK提供的OpenGL ES1 headers.
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#include "SEOGLES1RendererLIB.h"
#include "SEOGLES1FrameBuffer.h"
#include "SEOGLES1Resources.h"
#include "SERenderer.h"
#include "SEGeometry.h"
#include "SETexture.h"

namespace Swing
{

class OGLES1FixedEffect;

//----------------------------------------------------------------------------
// 名称:OpenGL ES1 Renderer虚基类
// 说明:OpenGL ES1不支持可编程管线,因此所有用于支持基类shader能力的纯虚函数都为空函数.
// 作者:Sun Che
// 时间:20090606
//----------------------------------------------------------------------------
class SE_RENDERER_API OGLES1Renderer : public Renderer
{
    SE_DECLARE_INITIALIZE;

public:
    // RTTI.
    virtual int GetType(void) const { return Renderer::OPENGLES1; }

    // 不支持的基类功能.
    virtual const char* GetExtension(void) const { return "ogles1"; }
    virtual char GetCommentCharacter(void) const { return '0'; }

    // 虚基类.
    // 在OpenGL ES1 context创建后,由派生类构造函数调用InitializeState函数.
    virtual ~OGLES1Renderer(void);
    void InitializeState(void);

    // 全窗口buffer操作.
    virtual void ClearBackBuffer(void);
    virtual void ClearZBuffer(void);
    virtual void ClearStencilBuffer(void);
    virtual void ClearBuffers(void);
    virtual void DisplayBackBuffer(void) = 0;

    // 特定窗口buffer操作.
    virtual void ClearBackBuffer(int iXPos, int iYPos, int iWidth,
        int iHeight);
    virtual void ClearZBuffer(int iXPos, int iYPos, int iWidth,
        int iHeight);
    virtual void ClearStencilBuffer(int iXPos, int iYPos, int iWidth,
        int iHeight);
    virtual void ClearBuffers(int iXPos, int iYPos, int iWidth,
        int iHeight);

    // 固定管线对象渲染入口.
    virtual void DrawScene(UnculledSet& rVisibleSet);
    virtual void Draw(Geometry* pGeometry);

    // 其他渲染.
    virtual bool SelectFont(int iFontID);
    virtual void UnloadFont(int iFontID);
    virtual void Draw(int iX, int iY, const ColorRGBA& rColor,
        const char* acText);
    virtual void Draw(const unsigned char* aucBuffer);

    // color mask设置,表明哪些颜色通道允许被写入color buffer.
    virtual void SetColorMask(bool bAllowRed, bool bAllowGreen,
        bool bAllowBlue, bool bAllowAlpha);

    // 开启/关闭用户自定义裁减平面.
    // 传入平面必须是模型空间平面,它在内部被变换到摄像机空间参与clip空间裁减.
    virtual void EnableUserClipPlane(int i, const Plane3f& rPlane);
    virtual void DisableUserClipPlane(int i);

    // 用于释放用户自定义的sampler information ID.
    static void OnReleaseSamplerInformationID(void* pID);

protected:
    OGLES1Renderer(FrameBuffer::FormatType eFormat,
        FrameBuffer::DepthType eDepth, FrameBuffer::StencilType eStencil,
        FrameBuffer::BufferingType eBuffering,
        FrameBuffer::MultisamplingType eMultisampling, int iWidth,
        int iHeight);

    // 摄像机更新.
    friend class OGLES1FrameBuffer;
    virtual void OnViewportChange(void);
    virtual void OnDepthRangeChange(void);

    // 全局渲染状态管理.
    virtual void SetAlphaState(AlphaState* pState);
    virtual void SetCullState(CullState* pState);
    virtual void SetMaterialState(MaterialState* pState);
    virtual void SetPolygonOffsetState(PolygonOffsetState* pState);
    virtual void SetStencilState(StencilState* pState);
    virtual void SetWireframeState(WireframeState* pState);
    virtual void SetZBufferState(ZBufferState* pState);

    // 用于设置固定管线lighting.
    void EnableLightingFixed(void);
    void DisableLightingFixed(void);
    void SetLightingStateFixed(int i, Light* pLight);
    void RestoreLightingStateFixed(int i, Light* pLight);

    // per-geometry pre/post-draw函数入口.
    virtual void OnPreDrawGeometry(void);
    virtual void OnPostDrawGeometry(void);

    // per-pass pre/post-draw函数入口,
    virtual void OnPreDrawPass(ShaderEffect* pEffect, int iPass,
        bool bPrimaryEffect);
    virtual void OnPostDrawPass(ShaderEffect* pEffect, int iPass,
        bool bPrimaryEffect);

    // 渲染器派生类渲染函数入口.
    virtual void DrawElements(void);

    // 渲染器资源装载与释放.
    // 针对显存,需要具体图形API负责实现.
    virtual void OnLoadVProgram(ResourceIdentifier*& rpID,
        VertexProgram* pVProgram);
    virtual void OnReleaseVProgram(ResourceIdentifier* pID);
    virtual void OnLoadPProgram(ResourceIdentifier*& rpID,
        PixelProgram* pPProgram);
    virtual void OnReleasePProgram(ResourceIdentifier* pID);
    virtual void OnLoadTexture(ResourceIdentifier*& rpID,
        Texture* pTexture);
    virtual void OnReleaseTexture(ResourceIdentifier* pID);
    virtual void OnLoadVBuffer(ResourceIdentifier*& rpID,
        const Attributes& rIAttr, const Attributes& rOAttr,
        VertexBuffer* pVBuffer, VertexProgram* pVProgram);
    virtual void OnReleaseVBuffer(ResourceIdentifier* pID);
    virtual void OnLoadIBuffer(ResourceIdentifier*& rpID,
        IndexBuffer* pIBuffer);
    virtual void OnReleaseIBuffer(ResourceIdentifier* pID);

    // 渲染器资源开启与关闭.
    virtual void SetVProgramRC(RendererConstant* pRC);
    virtual void SetVProgramUC(UserConstant* pUC);
    virtual void SetGProgramRC(RendererConstant* pRC);
    virtual void SetGProgramUC(UserConstant* pUC);
    virtual void SetPProgramRC(RendererConstant* pRC);
    virtual void SetPProgramUC(UserConstant* pUC);
    virtual void UpdateVProgramConstants(VertexProgram* pVProgram);
    virtual void UpdateGProgramConstants(GeometryProgram* pGProgram);
    virtual void UpdatePProgramConstants(PixelProgram* pPProgram);
    virtual void OnEnableVProgram(ResourceIdentifier* pID);
    virtual void OnDisableVProgram(ResourceIdentifier* pID);
    virtual void OnEnablePProgram(ResourceIdentifier* pID);
    virtual void OnDisablePProgram(ResourceIdentifier* pID);
    virtual void OnEnableTexture(ResourceIdentifier* pID);
    virtual void OnDisableTexture(ResourceIdentifier* pID);
    virtual void OnEnableVBuffer(ResourceIdentifier* pID, 
        VertexProgram* pVProgram);
    virtual void OnDisableVBuffer(ResourceIdentifier* pID, 
        VertexProgram* pVProgram);
    virtual void OnEnableIBuffer(ResourceIdentifier* pID);
    virtual void OnDisableIBuffer(ResourceIdentifier* pID);

    // 用于渲染fixed effect.
    void ApplyFixedEffect(OGLES1FixedEffect* pEffect, bool& rbPrimaryEffect);

    // 用于设置固定管线WVP变换矩阵.
    void SetWVPMatrixFixed(void);

    // 待实现.
    // 不能使用display list实现文本渲染.    
    // 文本渲染
    //void DrawCharacter(const BitmapFont& rFont, char cChar);

    // 引擎层参数常量与OpenGL渲染器层参数常量映射表.
    static GLenum ms_aeObjectType[Geometry::GT_MAX_COUNT];
    static GLenum ms_aeAlphaSrcBlend[AlphaState::SBF_COUNT];
    static GLenum ms_aeAlphaDstBlend[AlphaState::DBF_COUNT];
    static GLenum ms_aeAlphaTest[AlphaState::TF_COUNT];
    static GLenum ms_aeFrontFace[CullState::FT_COUNT];
    static GLenum ms_aeCullFace[CullState::CT_COUNT];
    static GLenum ms_aeStencilCompare[StencilState::CF_COUNT];
    static GLenum ms_aeStencilOperation[StencilState::OT_COUNT];
    static GLenum ms_aeZBufferCompare[ZBufferState::CF_COUNT];
    static GLenum ms_aeTextureMipmap[Texture::MAX_FILTER_TYPES];
    static GLenum ms_aeDepthCompare[Texture::DC_COUNT];
    static GLenum ms_aeWrapMode[Texture::MAX_WRAP_TYPES];
    static GLenum ms_aeImageComponents[Image::IT_COUNT];
    static GLenum ms_aeImageFormats[Image::IT_COUNT];
    static GLenum ms_aeImageTypes[Image::IT_COUNT];
    static GLenum ms_aeSamplerTypes[SamplerInformation::MAX_SAMPLER_TYPES];
};

}

#endif
