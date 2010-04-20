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

#ifndef Swing_OpenGLRenderer_H
#define Swing_OpenGLRenderer_H

#include "SEglExtensions.h"
// 必须确保cg的头文件包含在我们的OpenGL封装器的后面
#include <Cg/Cg.h>
#include <Cg/cgGL.h>

#include "SEOpenGLRendererLIB.h"
#include "SEOpenGLFrameBuffer.h"
#include "SERenderer.h"
#include "SEGeometry.h"
#include "SETexture.h"

//----------------------------------------------------------------------------
#ifdef _DEBUG
#define SE_GL_DEBUG_CG_PROGRAM \
{ \
    CGerror tempError; \
    cgGetLastErrorString(&tempError); \
    SE_ASSERT( tempError == CG_NO_ERROR ); \
}
#else
#define SE_GL_DEBUG_CG_PROGRAM
#endif
//----------------------------------------------------------------------------

namespace Swing
{

class SEBitmapFont;
class SEOpenGLProgramInterfaceCatalog;

//----------------------------------------------------------------------------
// 说明:
// 作者:Sun Che
// 时间:20080919
//----------------------------------------------------------------------------
class SE_RENDERER_API SEOpenGLRenderer : public SERenderer
{
    SE_DECLARE_INITIALIZE;
    SE_DECLARE_TERMINATE;

public:
    // RTTI.
    virtual int GetType(void) const { return SERenderer::OPENGL; }

    // 虚基类.
    // 在OpenGL context创建后,由派生类构造函数调用InitializeState函数.
    virtual ~SEOpenGLRenderer(void);
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

    // 其他渲染.
    virtual bool SelectFont(int iFontID);
    virtual void UnloadFont(int iFontID);
    virtual void Draw(int iX, int iY, const SEColorRGBA& rColor,
        const char* acText);
    virtual void Draw(const unsigned char* aucBuffer);

    // color mask设置,表明哪些颜色通道允许被写入color buffer.
    virtual void SetColorMask(bool bAllowRed, bool bAllowGreen,
        bool bAllowBlue, bool bAllowAlpha);

    // 开启/关闭用户自定义裁减平面.
    // 传入平面必须是模型空间平面,它在内部被变换到摄像机空间参与clip空间裁减.
    virtual void EnableUserClipPlane(int i, const SEPlane3f& rPlane);
    virtual void DisableUserClipPlane(int i);

    // Cg runtime相关函数.
    CGcontext GetCgContext(void) const;
    CGprofile GetCgLatestVertexProfile(void) const;
    CGprofile GetCgLatestPixelProfile(void) const;
    CGprofile GetCgLatestGeometryProfile(void) const;

protected:
    SEOpenGLRenderer(SEFrameBuffer::FormatType eFormat,
        SEFrameBuffer::DepthType eDepth, SEFrameBuffer::StencilType eStencil,
        SEFrameBuffer::BufferingType eBuffering,
        SEFrameBuffer::MultisamplingType eMultisampling, int iWidth,
        int iHeight);

    // 摄像机更新.
    friend class SEOpenGLFrameBuffer;
    virtual void OnViewportChange(void);
    virtual void OnDepthRangeChange(void);

    // 全局渲染状态管理.
    virtual void SetAlphaState(SEAlphaState* pState);
    virtual void SetCullState(SECullState* pState);
    virtual void SetPolygonOffsetState(SEPolygonOffsetState* pState);
    virtual void SetStencilState(SEStencilState* pState);
    virtual void SetWireframeState(SEWireframeState* pState);
    virtual void SetZBufferState(SEZBufferState* pState);

    // per-geometry pre/post-draw函数入口.
    virtual void OnPreDrawGeometry(void);
    virtual void OnPostDrawGeometry(void);

    // per-pass pre/post-draw函数入口,
    virtual void OnPreDrawPass(SEShaderEffect* pEffect, int iPass,
        bool bPrimaryEffect);
    virtual void OnPostDrawPass(SEShaderEffect* pEffect, int iPass,
        bool bPrimaryEffect);

    // 渲染器派生类渲染函数入口.
    virtual void DrawElements(void);

    // 渲染器资源装载与释放.
    // 针对显存,需要具体图形API负责实现.
    virtual void OnLoadVProgram(SEResourceIdentifier*& rpID,
        SEVertexProgram* pVProgram);
    virtual void OnReleaseVProgram(SEResourceIdentifier* pID);
    virtual void OnLoadPProgram(SEResourceIdentifier*& rpID,
        SEPixelProgram* pPProgram);
    virtual void OnReleasePProgram(SEResourceIdentifier* pID);
    virtual void OnLoadTexture(SEResourceIdentifier*& rpID,
        SETexture* pTexture);
    virtual void OnReleaseTexture(SEResourceIdentifier* pID);
    virtual void OnLoadVBuffer(SEResourceIdentifier*& rpID,
        const SEAttributes& rIAttr, const SEAttributes& rOAttr,
        SEVertexBuffer* pVBuffer, SEVertexProgram* pVProgram);
    virtual void OnReleaseVBuffer(SEResourceIdentifier* pID);
    virtual void OnLoadIBuffer(SEResourceIdentifier*& rpID,
        SEIndexBuffer* pIBuffer);
    virtual void OnReleaseIBuffer(SEResourceIdentifier* pID);

    // 渲染器资源开启与关闭.
    virtual void SetVProgramRC(SERendererConstant* pRC);
    virtual void SetVProgramUC(SEUserConstant* pUC);
    virtual void SetGProgramRC(SERendererConstant* pRC);
    virtual void SetGProgramUC(SEUserConstant* pUC);
    virtual void SetPProgramRC(SERendererConstant* pRC);
    virtual void SetPProgramUC(SEUserConstant* pUC);
    virtual void UpdateVProgramConstants(SEVertexProgram* pVProgram);
    virtual void UpdateGProgramConstants(SEGeometryProgram* pGProgram);
    virtual void UpdatePProgramConstants(SEPixelProgram* pPProgram);
    virtual void OnEnableVProgram(SEResourceIdentifier* pID);
    virtual void OnDisableVProgram(SEResourceIdentifier* pID);
    virtual void OnEnablePProgram(SEResourceIdentifier* pID);
    virtual void OnDisablePProgram(SEResourceIdentifier* pID);
    virtual void OnEnableTexture(SEResourceIdentifier* pID);
    virtual void OnDisableTexture(SEResourceIdentifier* pID);
    virtual void OnEnableVBuffer(SEResourceIdentifier* pID, 
        SEVertexProgram* pVProgram);
    virtual void OnDisableVBuffer(SEResourceIdentifier* pID, 
        SEVertexProgram* pVProgram);
    virtual void OnEnableIBuffer(SEResourceIdentifier* pID);
    virtual void OnDisableIBuffer(SEResourceIdentifier* pID);

    // 文本渲染
    void DrawCharacter(const SEBitmapFont& rFont, char cChar);

    // 字体库由若干display list实现.
    class DisplayListInfo
    {
    public:
        int Count;     // display list数目,传给glGenLists函数
        int Start;     // start index,由glGenLists函数返回的起始索引
        int Base;      // base index,用于glListBase
    };
    std::vector<DisplayListInfo> m_DLInfo;

    // Cg runtime相关数据.
    CGcontext m_CgContext;
    CGprofile m_CgLatestVProfile;
    CGprofile m_CgLatestGProfile;
    CGprofile m_CgLatestPProfile;

    static SEOpenGLProgramInterfaceCatalog* ms_pProgramInterfaceCatalog;

    // 引擎层参数常量与OpenGL渲染器层参数常量映射表.
    static GLenum ms_aeObjectType[SEGeometry::GT_MAX_COUNT];
    static GLenum ms_aeAlphaSrcBlend[SEAlphaState::SBF_COUNT];
    static GLenum ms_aeAlphaDstBlend[SEAlphaState::DBF_COUNT];
    static GLenum ms_aeAlphaTest[SEAlphaState::TF_COUNT];
    static GLenum ms_aeFrontFace[SECullState::FT_COUNT];
    static GLenum ms_aeCullFace[SECullState::CT_COUNT];
    static GLenum ms_aeStencilCompare[SEStencilState::CF_COUNT];
    static GLenum ms_aeStencilOperation[SEStencilState::OT_COUNT];
    static GLenum ms_aeZBufferCompare[SEZBufferState::CF_COUNT];
    static GLenum ms_aeTextureMipmap[SETexture::MAX_FILTER_TYPES];
    static GLenum ms_aeDepthCompare[SETexture::DC_COUNT];
    static GLenum ms_aeWrapMode[SETexture::MAX_WRAP_TYPES];
    static GLenum ms_aeImageComponents[SEImage::IT_COUNT];
    static GLenum ms_aeImageFormats[SEImage::IT_COUNT];
    static GLenum ms_aeImageTypes[SEImage::IT_COUNT];
    static GLenum ms_aeSamplerTypes[SESamplerInformation::MAX_SAMPLER_TYPES];
};

}

#endif
