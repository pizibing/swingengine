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

#ifndef Swing_DX9Renderer_H
#define Swing_DX9Renderer_H

#include "SEDX9RendererLIB.h"
#include "SEDX9Utility.h"
#include "SEDX9FrameBuffer.h"
#include "SERenderer.h"
#include "SEGeometry.h"
#include "SEProgram.h"

namespace Swing
{

class SEDX9ProgramInterfaceCatalog;

//----------------------------------------------------------------------------
// 说明:
// 作者:Sun Che
// 时间:20080827
//----------------------------------------------------------------------------
class SE_RENDERER_API SEDX9Renderer : public SERenderer
{
    SE_DECLARE_INITIALIZE;
    SE_DECLARE_TERMINATE;

public:
    // RTTI.
    virtual int GetType(void) const { return SERenderer::DIRECTX9; }

    SEDX9Renderer(HWND hWnd, SEFrameBuffer::FormatType eFormat,
        SEFrameBuffer::DepthType eDepth, SEFrameBuffer::StencilType eStencil,
        SEFrameBuffer::BufferingType eBuffering,
        SEFrameBuffer::MultisamplingType eMultisampling, int iWidth,
        int iHeight);

    virtual ~SEDX9Renderer(void);

    virtual void ToggleFullscreen(void);
    virtual bool BeginScene(void);
    virtual void EndScene(void);

    // 全窗口buffer操作.
    virtual void ClearBackBuffer(void);
    virtual void ClearZBuffer(void);
    virtual void ClearStencilBuffer(void);
    virtual void ClearBuffers(void);
    virtual void DisplayBackBuffer(void);

    // 特定窗口buffer操作.
    virtual void ClearBackBuffer(int iXPos, int iYPos, int iWidth,
        int iHeight);
    virtual void ClearZBuffer(int iXPos, int iYPos, int iWidth, int iHeight);
    virtual void ClearStencilBuffer(int iXPos, int iYPos, int iWidth,
        int iHeight);
    virtual void ClearBuffers(int iXPos, int iYPos, int iWidth, int iHeight);

    // 其他渲染.
    virtual bool SelectFont(int iFontID);
    int LoadFont(const char* acFace, int iSize, bool bBold, bool bItalic);
    void UnloadFont(int iFontID);
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

    // windows平台下的窗体应用程序开发中使用.
    const LPDIRECT3DDEVICE9 GetDevice(void);

    // Cg runtime相关函数.
    CGcontext GetCgContext(void) const;
    CGprofile GetCgLatestVertexProfile(void) const;
    CGprofile GetCgLatestPixelProfile(void) const;
    CGprofile GetCgLatestGeometryProfile(void) const;

protected:
    // 设备管理.
    void OnLostDevice(void);
    void OnResetDevice(void);

    // 摄像机更新.
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

// 成员变量
protected:
    friend class SEDX9FrameBuffer;

    LPDIRECT3D9 m_pDXMain;
    LPDIRECT3DDEVICE9 m_pDXDevice;
    D3DPRESENT_PARAMETERS m_Present;
    RECT m_rcWindow;
    bool m_bDeviceLost;
    bool m_bCursorVisible;
    bool m_bBeginSceneActive;

    // 追踪所有由应用程序创建的frame buffer.
    // D3D要求在device lost时释放相关VRAM资源(创建声明为D3DPOOL_DEFAULT),
    // 在device reset时重新装载这些VRAM资源.
    // 目前只有frame buffer索引的offscreen texture是该类型资源.
    std::vector<SEDX9FrameBuffer*> m_FrameBuffers;

    // 字体库.
    std::vector<LPD3DXFONT> m_FontArray;

    // Cg runtime相关数据.
    CGcontext m_CgContext;
    CGprofile m_CgLatestVProfile;
    CGprofile m_CgLatestGProfile;
    CGprofile m_CgLatestPProfile;

    // 错误检查与异常获取.
    static HRESULT ms_hResult;

    static SEDX9ProgramInterfaceCatalog* ms_pProgramInterfaceCatalog;

    // 引擎层参数常量与DirectX渲染器层参数常量映射表.
    static D3DPRIMITIVETYPE ms_aeObjectType[];
    static DWORD ms_adwAlphaSrcBlend[];
    static DWORD ms_adwAlphaDstBlend[];
    static DWORD ms_adwAlphaTest[];
    static DWORD ms_adwCullType[];
    static DWORD ms_adwStencilCompare[];
    static DWORD ms_adwStencilOperation[];
    static DWORD ms_adwZBufferCompare[];
    static DWORD ms_adwTexMinFilter[];
    static DWORD ms_adwTexMipFilter[];
    static DWORD ms_adwTexWrapMode[];
    static D3DFORMAT ms_aeImageFormat[];
};

}

#endif
