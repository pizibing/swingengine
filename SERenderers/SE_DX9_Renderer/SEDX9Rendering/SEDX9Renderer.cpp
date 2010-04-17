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

#include "SEDX9RendererPCH.h"
#include "SEDX9Renderer.h"
#include "SECamera.h"
#include "SEDX9Program.h"
#include "SEDX9ProgramInterfaceCatalog.h"

using namespace Swing;

D3DPRIMITIVETYPE DX9Renderer::ms_aeObjectType[Geometry::GT_MAX_COUNT] =
{
    D3DPT_POINTLIST,      // GT_POLYPOINT
    D3DPT_LINELIST,       // GT_POLYLINE_SEGMENTS
    D3DPT_LINESTRIP,      // GT_POLYLINE_OPEN
    D3DPT_LINESTRIP,      // GT_POLYLINE_CLOSED
    D3DPT_TRIANGLELIST    // GT_TRIMESH
};

DX9ProgramInterfaceCatalog* DX9Renderer::ms_pProgramInterfaceCatalog = 0;
HRESULT DX9Renderer::ms_hResult = 0;

SE_IMPLEMENT_INITIALIZE(DX9Renderer);
SE_IMPLEMENT_TERMINATE(DX9Renderer);

//SE_REGISTER_INITIALIZE(DX9Renderer);
//SE_REGISTER_TERMINATE(DX9Renderer);

//#define SE_USING_PERFHUD

//----------------------------------------------------------------------------
void DX9Renderer::Initialize()
{
    ms_pProgramInterfaceCatalog = SE_NEW DX9ProgramInterfaceCatalog("Main");
    DX9ProgramInterfaceCatalog::SetActive(ms_pProgramInterfaceCatalog);
}
//----------------------------------------------------------------------------
void DX9Renderer::Terminate()
{
    if( DX9ProgramInterfaceCatalog::GetActive() == 
        ms_pProgramInterfaceCatalog )
    {
        DX9ProgramInterfaceCatalog::SetActive(0);
    }
    SE_DELETE ms_pProgramInterfaceCatalog;
}
//----------------------------------------------------------------------------
DX9Renderer::DX9Renderer(HWND hWnd, FrameBuffer::FormatType eFormat,
    FrameBuffer::DepthType eDepth, FrameBuffer::StencilType eStencil,
    FrameBuffer::BufferingType eBuffering,
    FrameBuffer::MultisamplingType eMultisampling, int iWidth, int iHeight)
    :
    Renderer(eFormat, eDepth, eStencil, eBuffering, eMultisampling, iWidth,
        iHeight)
{
    m_pDXMain = Direct3DCreate9(D3D_SDK_VERSION);
    SE_ASSERT( m_pDXMain );

    m_Present.BackBufferWidth = iWidth;
    m_Present.BackBufferHeight = iHeight;
    m_Present.BackBufferFormat = D3DFMT_A8R8G8B8;
    m_Present.BackBufferCount = 1;
    m_Present.hDeviceWindow = hWnd;
    m_Present.Windowed = true;
    m_Present.Flags = 0;
    m_Present.FullScreen_RefreshRateInHz = 0;
    m_Present.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    // 申请depth和stencil buffers.
    // 对于DirectX来说这两者的参数不是独立的.
    // 待实现.
    // 当前,只是创建一个最常见的24-bit depth buffer和8-bit stencil buffer.
    // 两者共用一个surface.
    m_Present.EnableAutoDepthStencil = TRUE;
    m_Present.AutoDepthStencilFormat = D3DFMT_D24S8;

    // 申请multisampling.
    m_Present.SwapEffect = D3DSWAPEFFECT_FLIP; 
    m_Present.MultiSampleType = D3DMULTISAMPLE_NONE;
    m_Present.MultiSampleQuality = 0;
    if( m_eMultisampling == FrameBuffer::MT_SAMPLING_4 )
    {
        if( SUCCEEDED(m_pDXMain->CheckDeviceMultiSampleType(
            D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_A8R8G8B8, FALSE,
            D3DMULTISAMPLE_4_SAMPLES, NULL)) )
        {
            m_Present.SwapEffect = D3DSWAPEFFECT_DISCARD; 
            m_Present.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
        }
    }
    else if( m_eMultisampling == FrameBuffer::MT_SAMPLING_2 )
    {
        if( SUCCEEDED(m_pDXMain->CheckDeviceMultiSampleType(
            D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_A8R8G8B8, FALSE,
            D3DMULTISAMPLE_2_SAMPLES, NULL)) )
        {
            m_Present.SwapEffect = D3DSWAPEFFECT_DISCARD; 
            m_Present.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
        }
    }

    UINT uiAdapterToUse = D3DADAPTER_DEFAULT;
    D3DDEVTYPE eDeviceType = D3DDEVTYPE_HAL;

#if defined(SE_USING_PERFHUD)
    // Look for 'NVIDIA PerfHUD' adapter.
    // If it is present, override default settings.
    UINT uiAdapterCount = m_pDXMain->GetAdapterCount();
    for( UINT uiAdapter = 0; uiAdapter < uiAdapterCount; uiAdapter++ )
    {
        D3DADAPTER_IDENTIFIER9 Identifier;
        HRESULT Res;
        Res = m_pDXMain->GetAdapterIdentifier(uiAdapter, 0, &Identifier);
        if( strstr(Identifier.Description, "PerfHUD") != 0 )
        {
            uiAdapterToUse = uiAdapter;
            eDeviceType = D3DDEVTYPE_REF;
            break;
        }
    }
#endif

    ms_hResult = m_pDXMain->CreateDevice(
        uiAdapterToUse,
        eDeviceType,
        hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE,
        &m_Present, &m_pDXDevice);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
    
    // 创建默认字体.
    m_iFontID = LoadFont("Arial", 18, false, false);
    SE_ASSERT( m_iFontID == 0 );

    // 查询设备各项能力.
    D3DCAPS9 tempDeviceCaps;
    ms_hResult = m_pDXMain->GetDeviceCaps(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        &tempDeviceCaps);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    // OpenGL只支持primary和secondary两组顶点颜色.
    // 这里让DirectX渲染器与其保持一致.
    m_iMaxColors = 2;
    // 待实现.
    // 这个参数其实只适用于固定管线,对于可编程管线,由具体的shader profile决定.
    m_iMaxTCoords = tempDeviceCaps.MaxSimultaneousTextures;
    // VS_3_0才能支持vertex shader texture,稍后检查.
    m_iMaxVShaderImages = 0;
    // DirectX9不支持geometry shader及其texture.
    m_iMaxGShaderImages = 0;
    m_iMaxPShaderImages = m_iMaxTCoords;
    m_iMaxUserClipPlanes = (int)tempDeviceCaps.MaxUserClipPlanes;

    m_iMaxLights = (int)tempDeviceCaps.MaxActiveLights;
    SE_ASSERT( m_iMaxLights > 0 );
    m_aspLight = SE_NEW SEObjectPtr[m_iMaxLights];

    if( tempDeviceCaps.StencilCaps & (D3DSTENCILOP_KEEP | D3DSTENCILOP_REPLACE) )
    {
        m_iMaxStencilIndices = 8;
    }

    if( tempDeviceCaps.VertexShaderVersion >= D3DVS_VERSION(3, 0) )
    {
        m_iMaxVShaderProfile = Renderer::VS_3_0;
        m_iMaxVShaderImages = 4;
    }
    else if( tempDeviceCaps.VertexShaderVersion >= D3DVS_VERSION(2, 0) )
    {
        m_iMaxVShaderProfile = Renderer::VS_2_0;
    }
    else
    {
        // 目前不支持的vertex shader profile.
        SE_ASSERT( false );
    }

    // DirectX9不支持geometry shader.
    m_iMaxGShaderProfile = Renderer::GS_UNSUPPORTED;

    if( tempDeviceCaps.PixelShaderVersion >= D3DPS_VERSION(3, 0) )
    {
        m_iMaxPShaderProfile = Renderer::PS_3_0;
    }
    else if( tempDeviceCaps.PixelShaderVersion >= D3DPS_VERSION(2, 0) )
    {
        m_iMaxPShaderProfile = Renderer::PS_2_0;
    }
    else
    {
        // 目前不支持的pixel shader profile.
        SE_ASSERT( false );
    }

    m_iMaxRenderTargets = tempDeviceCaps.NumSimultaneousRTs;

    m_iMaxActiveSamplerCount = m_iMaxVShaderImages + m_iMaxPShaderImages;
    if( m_iMaxActiveSamplerCount > 0 )
    {
        m_apActiveSamplers =
            SE_NEW SamplerInformation*[m_iMaxActiveSamplerCount];

        memset(m_apActiveSamplers, 0, m_iMaxActiveSamplerCount*
            sizeof(SamplerInformation*));
    }

    // Cg runtime stuff begin.

    // 创建渲染器的Cg context.
    m_CgContext = cgCreateContext();
    SE_DX9_DEBUG_CG_PROGRAM;
    cgSetParameterSettingMode(m_CgContext, CG_DEFERRED_PARAMETER_SETTING);
    SE_DX9_DEBUG_CG_PROGRAM;

    // 与DX9设备绑定.
    cgD3D9SetDevice(m_pDXDevice);
    SE_DX9_DEBUG_CG_PROGRAM;
    m_CgLatestVProfile = cgD3D9GetLatestVertexProfile();
    m_CgLatestPProfile = cgD3D9GetLatestPixelProfile();

    // Cg runtime stuff end.

    // 初始化全局渲染状态为引擎默认设置.
    SetGlobalState(GlobalState::Default);

    // 关闭lighting(DirectX默认为开启).  
    // 待实现:  对于一个shader-based引擎,还有必要做这些吗?
    ms_hResult = m_pDXDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    m_bCursorVisible = true;
    m_bDeviceLost = false;
    m_bBeginSceneActive = false;
}
//----------------------------------------------------------------------------
DX9Renderer::~DX9Renderer()
{
    // Release all fonts.
    for( int i = 0; i < (int)m_FontArray.size(); i++ )
    {
        UnloadFont(i);
    }

    // Clear cursor.
    if( !m_bCursorVisible )
    {
        ShowCursor(true);
    }

    // Cg runtime stuff begin.

    cgD3D9SetDevice(0);
    SE_DX9_DEBUG_CG_PROGRAM;

    // Release Cg context.
    cgDestroyContext(m_CgContext);

    // If this assertion is triggered, then most likely there are some Cg
    // runtime resources haven't been released. For example, maybe a geometry
    // object is still alive(which should be released already), and it is 
    // using a shader effect which itself is handling a Cg shader resource.
    SE_DX9_DEBUG_CG_PROGRAM;

    // Cg runtime stuff end.
}
//----------------------------------------------------------------------------
void DX9Renderer::ToggleFullscreen()
{
    Renderer::ToggleFullscreen();
    m_Present.Windowed = !m_Present.Windowed;

    if( m_Present.Windowed )
    {
        m_Present.FullScreen_RefreshRateInHz = 0;
    }
    else
    {
        GetWindowRect(m_Present.hDeviceWindow, &m_rcWindow);
        m_Present.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    }

    OnLostDevice();
    OnResetDevice(); 

    if( m_Present.Windowed )
    {
        SetWindowPos(m_Present.hDeviceWindow, 
            NULL, 
            m_rcWindow.left,
            m_rcWindow.top, 
            m_rcWindow.right - m_rcWindow.left,
            m_rcWindow.bottom - m_rcWindow.top,
            SWP_NOZORDER | SWP_DRAWFRAME | SWP_SHOWWINDOW);
    }
}
//----------------------------------------------------------------------------
bool DX9Renderer::BeginScene()
{
    // When using multiple renderers, cgD3D9 runtime can not support a 
    // one-to-one relationship between a cg context and a DX device.
    // Every cg context shares the same active DX device, and manages DX
    // related resource(shader programs,parameter handles) by using this
    // active DX device. So it is important to re-set the current renderer's
    // device to the cgD3D9 runtime by using this function.
    // This is a disadvantage of cgD3D9 which reduces renderer's performance.
    cgD3D9SetDevice(m_pDXDevice);
    SE_DX9_DEBUG_CG_PROGRAM;

    ms_hResult = m_pDXDevice->TestCooperativeLevel();
    switch( ms_hResult )
    {
    case D3DERR_DEVICELOST:
        if( !m_bDeviceLost )
        {
            m_bDeviceLost = true;
            OnLostDevice();
        }
        return false;
    case D3DERR_DEVICENOTRESET:
        OnResetDevice();
        m_bDeviceLost = false;
        break;
    }

    ms_hResult = m_pDXDevice->BeginScene();
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    m_bBeginSceneActive = true;

    return true;
}
//----------------------------------------------------------------------------
void DX9Renderer::EndScene()
{
    ms_hResult = m_pDXDevice->EndScene();
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    m_bBeginSceneActive = false;
}
//----------------------------------------------------------------------------
void DX9Renderer::OnLostDevice()
{
    // release font.
    m_FontArray[0]->OnLostDevice();

    // release framebuffer.
    int iFrameBufferCount = (int)m_FrameBuffers.size();
    for( int i = 0; i < iFrameBufferCount; i++ )
    {
        m_FrameBuffers[i]->OnLostDevice();
    }
}
//----------------------------------------------------------------------------
void DX9Renderer::OnResetDevice()
{
    ms_hResult = m_pDXDevice->Reset(&m_Present);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    // reset font.
    m_FontArray[0]->OnResetDevice();

    // reset framebuffer.
    int iFrameBufferCount = (int)m_FrameBuffers.size();
    for( int i = 0; i < iFrameBufferCount; i++ )
    {
        m_FrameBuffers[i]->OnResetDevice();
    }

    OnFrustumChange();
    OnViewportChange();
    OnFrameChange();
}
//----------------------------------------------------------------------------
void DX9Renderer::ClearBackBuffer()
{
    DWORD dwClearColor = D3DCOLOR_COLORVALUE(m_ClearColor.R, m_ClearColor.G,
        m_ClearColor.B, m_ClearColor.A);

    ms_hResult = m_pDXDevice->Clear(0, 0, D3DCLEAR_TARGET, dwClearColor, 1.0f,
        0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX9Renderer::ClearZBuffer()
{
    ms_hResult = m_pDXDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, m_fClearDepth, 
        0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX9Renderer::ClearStencilBuffer()
{
    ms_hResult = m_pDXDevice->Clear(0, 0, D3DCLEAR_STENCIL, 0, 1.0f, 
        (DWORD)m_uiClearStencil);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX9Renderer::ClearBuffers()
{
    DWORD dwClearColor = D3DCOLOR_COLORVALUE(m_ClearColor.R, m_ClearColor.G,
        m_ClearColor.B, m_ClearColor.A);

    ms_hResult = m_pDXDevice->Clear(0, 0,
        D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
        dwClearColor, m_fClearDepth, (DWORD)m_uiClearStencil);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX9Renderer::ClearBackBuffer(int iXPos, int iYPos, int iWidth, int iHeight)
{
    D3DRECT tempRect;
    tempRect.x1 = (long)iXPos;
    tempRect.y1 = (long)iYPos;
    tempRect.x2 = (long)(iXPos + iWidth - 1);
    tempRect.y2 = (long)(iYPos + iHeight - 1);

    DWORD dwClearColor = D3DCOLOR_COLORVALUE(m_ClearColor.R, m_ClearColor.G,
        m_ClearColor.B, m_ClearColor.A);

    ms_hResult = m_pDXDevice->Clear(1, &tempRect, D3DCLEAR_TARGET, 
        dwClearColor, 1.0f, 0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX9Renderer::ClearZBuffer(int iXPos, int iYPos, int iWidth, int iHeight)
{
    D3DRECT tempRect;
    tempRect.x1 = (long)iXPos;
    tempRect.y1 = (long)iYPos;
    tempRect.x2 = (long)(iXPos + iWidth - 1);
    tempRect.y2 = (long)(iYPos + iHeight - 1);

    ms_hResult = m_pDXDevice->Clear(1, &tempRect, D3DCLEAR_ZBUFFER, 0, 
        m_fClearDepth, 0);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX9Renderer::ClearStencilBuffer(int iXPos, int iYPos, int iWidth, 
    int iHeight)
{
    D3DRECT tempRect;
    tempRect.x1 = (long)iXPos;
    tempRect.y1 = (long)iYPos;
    tempRect.x2 = (long)(iXPos + iWidth - 1);
    tempRect.y2 = (long)(iYPos + iHeight - 1);

    ms_hResult = m_pDXDevice->Clear(1, &tempRect, D3DCLEAR_STENCIL, 0, 1.0f, 
        (DWORD)m_uiClearStencil);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX9Renderer::ClearBuffers(int iXPos, int iYPos, int iWidth, int iHeight)
{
    D3DRECT tempRect;
    tempRect.x1 = (long)iXPos;
    tempRect.y1 = (long)iYPos;
    tempRect.x2 = (long)(iXPos + iWidth - 1);
    tempRect.y2 = (long)(iYPos + iHeight - 1);

    DWORD dwClearColor = D3DCOLOR_COLORVALUE(m_ClearColor.R, m_ClearColor.G,
        m_ClearColor.B, m_ClearColor.A);

    ms_hResult = m_pDXDevice->Clear(1, &tempRect,
        D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
        dwClearColor, m_fClearDepth, (DWORD)m_uiClearStencil);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX9Renderer::DisplayBackBuffer()
{
    ms_hResult = m_pDXDevice->Present(0, 0, 0, 0);
    if( ms_hResult != D3DERR_DEVICELOST )
    {
        SE_ASSERT( SUCCEEDED(ms_hResult) );
    }
} 
//----------------------------------------------------------------------------
void DX9Renderer::SetColorMask(bool bAllowRed, bool bAllowGreen,
    bool bAllowBlue, bool bAllowAlpha)
{
    Renderer::SetColorMask(bAllowRed, bAllowGreen, bAllowBlue, bAllowAlpha);

    DWORD dwMask = 0;

    if( bAllowRed )
    {
        dwMask |= D3DCOLORWRITEENABLE_RED;
    }

    if( bAllowGreen )
    {
        dwMask |= D3DCOLORWRITEENABLE_GREEN;
    }

    if( bAllowBlue )
    {
        dwMask |= D3DCOLORWRITEENABLE_BLUE;
    }

    if( bAllowAlpha )
    {
        dwMask |= D3DCOLORWRITEENABLE_ALPHA;
    }

    ms_hResult = m_pDXDevice->SetRenderState(D3DRS_COLORWRITEENABLE, dwMask);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX9Renderer::EnableUserClipPlane(int i, const SEPlane3f& rPlane)
{
    SEVector4f vec4fMPlane(rPlane.Normal[0], rPlane.Normal[1], rPlane.Normal[2],
        -rPlane.Constant);
    SEMatrix4f mat4fWorldViewMatrix = m_WorldMatrix * m_ViewMatrix;
    SEMatrix4f mat4fWVMatrixInv;
    mat4fWorldViewMatrix.GetInverse(mat4fWVMatrixInv);
    // Plane * ((M^(-1))^T),把平面从模型空间变换到view空间下.
    SEVector4f vec4fCPlane = mat4fWVMatrixInv * vec4fMPlane;

    // 获取当前处于激活状态的裁减平面.
    DWORD dwClipPlanesEnabled;
    ms_hResult = m_pDXDevice->GetRenderState(D3DRS_CLIPPLANEENABLE,
        &dwClipPlanesEnabled);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    ms_hResult = m_pDXDevice->SetClipPlane((DWORD)i, (float*)vec4fCPlane);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    // 更新处于激活状态的裁减平面.
    dwClipPlanesEnabled |= (1 << i);
    ms_hResult = m_pDXDevice->SetRenderState(D3DRS_CLIPPLANEENABLE,
        dwClipPlanesEnabled);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
void DX9Renderer::DisableUserClipPlane(int i)
{
    DWORD dwClipPlanesEnabled;
    ms_hResult = m_pDXDevice->GetRenderState(D3DRS_CLIPPLANEENABLE,
        &dwClipPlanesEnabled);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    dwClipPlanesEnabled &= ~(1 << i);
    ms_hResult = m_pDXDevice->SetRenderState(D3DRS_CLIPPLANEENABLE,
        dwClipPlanesEnabled);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
const LPDIRECT3DDEVICE9 DX9Renderer::GetDevice()
{
    return m_pDXDevice;
}
//----------------------------------------------------------------------------
void DX9Renderer::OnPreDrawGeometry()
{
    RenderStateBlock* pRStateBlock = m_pGeometry->RStateBlock;
    SE_ASSERT( pRStateBlock );

    SetGlobalState(pRStateBlock->States);
}
//----------------------------------------------------------------------------
void DX9Renderer::OnPostDrawGeometry()
{
    RenderStateBlock* pRStateBlock = m_pGeometry->RStateBlock;
    SE_ASSERT( pRStateBlock );

    RestoreGlobalState(pRStateBlock->States);
}
//----------------------------------------------------------------------------
void DX9Renderer::OnPreDrawPass(ShaderEffect* pEffect, int iPass,
    bool bPrimaryEffect)
{
    pEffect->SetGlobalState(iPass, this, bPrimaryEffect);
}
//----------------------------------------------------------------------------
void DX9Renderer::OnPostDrawPass(ShaderEffect* pEffect, int iPass,
    bool bPrimaryEffect)
{
    pEffect->RestoreGlobalState(iPass, this, bPrimaryEffect);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Cg runtime相关
//----------------------------------------------------------------------------
CGcontext DX9Renderer::GetCgContext() const
{
    return m_CgContext;
}
//----------------------------------------------------------------------------
CGprofile DX9Renderer::GetCgLatestVertexProfile() const
{
    return m_CgLatestVProfile;
}
//----------------------------------------------------------------------------
CGprofile DX9Renderer::GetCgLatestPixelProfile() const
{
    return m_CgLatestPProfile;
}
//----------------------------------------------------------------------------
CGprofile DX9Renderer::GetCgLatestGeometryProfile() const
{
    return m_CgLatestGProfile;
}
//----------------------------------------------------------------------------