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

#include "SEDX10RendererPCH.h"
#include "SEDX10Renderer.h"
#include "SECamera.h"
#include "SEDX10Program.h"
#include "SEDX10ProgramInterfaceCatalog.h"

using namespace Swing;

HRESULT DX10Renderer::ms_hResult = 0;
DX10ProgramInterfaceCatalog* DX10Renderer::ms_pProgramInterfaceCatalog = 0;

SE_IMPLEMENT_INITIALIZE(DX10Renderer);
SE_IMPLEMENT_TERMINATE(DX10Renderer);

//SE_REGISTER_INITIALIZE(DX10Renderer);
//SE_REGISTER_TERMINATE(DX10Renderer);

//----------------------------------------------------------------------------
void DX10Renderer::Initialize()
{
    ms_pProgramInterfaceCatalog = SE_NEW DX10ProgramInterfaceCatalog("Main");
    DX10ProgramInterfaceCatalog::SetActive(ms_pProgramInterfaceCatalog);
}
//----------------------------------------------------------------------------
void DX10Renderer::Terminate()
{
    if( DX10ProgramInterfaceCatalog::GetActive() == 
        ms_pProgramInterfaceCatalog )
    {
        DX10ProgramInterfaceCatalog::SetActive(0);
    }
    SE_DELETE ms_pProgramInterfaceCatalog;
}
//----------------------------------------------------------------------------
DX10Renderer::DX10Renderer(HWND hWnd, FrameBuffer::FormatType eFormat,
    FrameBuffer::DepthType eDepth, FrameBuffer::StencilType eStencil,
    FrameBuffer::BufferingType eBuffering,
    FrameBuffer::MultisamplingType eMultisampling, int iWidth, int iHeight)
    :
    Renderer(eFormat, eDepth, eStencil, eBuffering, eMultisampling, iWidth, 
        iHeight)
{
    m_SwapChainDesc.BufferDesc.Width = iWidth;
    m_SwapChainDesc.BufferDesc.Height = iHeight;
    m_SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    m_SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    m_SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    m_SwapChainDesc.BufferDesc.ScanlineOrdering = 
        DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    m_SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    m_SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    m_SwapChainDesc.BufferCount = 1;
    m_SwapChainDesc.OutputWindow = hWnd;
    m_SwapChainDesc.Windowed = true;
    m_SwapChainDesc.Flags = 0;

    // 申请multisampling.
    m_SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //multisampling所需
    m_SwapChainDesc.SampleDesc.Count = 1;
    m_SwapChainDesc.SampleDesc.Quality = 0;
    if( m_eMultisampling == FrameBuffer::MT_SAMPLING_4 )
    {
        // 待实现.
        // 检查设备是否支持multisampling 4 samples.
        m_SwapChainDesc.SampleDesc.Count = 4;
    }
    else if( m_eMultisampling == FrameBuffer::MT_SAMPLING_2 )
    {
        // 待实现.
        // 检查设备是否支持multisampling 2 samples.
        m_SwapChainDesc.SampleDesc.Count = 2;
    }

    UINT uiCreateDeviceFlags = 0;
#if defined(_DEBUG)  
    uiCreateDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

    ms_hResult = D3D10CreateDeviceAndSwapChain(
        0,  //default adapter
        D3D10_DRIVER_TYPE_HARDWARE,
        0,  // no software device
        uiCreateDeviceFlags, 
        D3D10_SDK_VERSION,
        &m_SwapChainDesc,
        &m_pDXGISwapChain,
        &m_pDX10Device);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    // 创建back buffer的d3d10 render target view.
    ID3D10Texture2D* pDX10BackBuffer;
    ms_hResult = m_pDXGISwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), 
        reinterpret_cast<void**>(&pDX10BackBuffer));
    SE_ASSERT( SUCCEEDED(ms_hResult) );
    ms_hResult = m_pDX10Device->CreateRenderTargetView(pDX10BackBuffer, 0, 
        &m_pDX10RTView);
    SE_DX10_SAFE_RELEASE(pDX10BackBuffer);

    // 创建depth/stencil buffer及其view.
    // 待实现,目前只是创建一个最基本的D24S8格式纹理作为该buffer.
    D3D10_TEXTURE2D_DESC tempDSDesc;
    tempDSDesc.Width = iWidth;
    tempDSDesc.Height = iHeight;
    tempDSDesc.MipLevels = 1;
    tempDSDesc.ArraySize = 1;
    tempDSDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    // multisampling must match swap chain values.
    tempDSDesc.SampleDesc.Count = m_SwapChainDesc.SampleDesc.Count;
    tempDSDesc.SampleDesc.Quality = m_SwapChainDesc.SampleDesc.Quality;
    tempDSDesc.Usage = D3D10_USAGE_DEFAULT;
    tempDSDesc.BindFlags = D3D10_BIND_DEPTH_STENCIL;
    tempDSDesc.CPUAccessFlags = 0; 
    tempDSDesc.MiscFlags = 0;

    ms_hResult = m_pDX10Device->CreateTexture2D(&tempDSDesc, 0, 
        &m_pDX10DSBuffer);
    SE_ASSERT( SUCCEEDED(ms_hResult) );
    ms_hResult = m_pDX10Device->CreateDepthStencilView(m_pDX10DSBuffer, 0, 
        &m_pDX10DSView);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    // bind当前render target view和depth/stencil view.
    m_pDX10Device->OMSetRenderTargets(1, &m_pDX10RTView, m_pDX10DSView);

    // 设置默认视口变换.
    D3D10_VIEWPORT tempViewport;
    tempViewport.TopLeftX = 0;
    tempViewport.TopLeftY = 0;
    tempViewport.Width = iWidth;
    tempViewport.Height = iHeight;
    tempViewport.MinDepth = 0.0f;
    tempViewport.MaxDepth = 1.0f;
    m_pDX10Device->RSSetViewports(1, &tempViewport);

    // 创建默认字体.
    m_iFontID = LoadFont("Arial", 18, false, false);
    SE_ASSERT( m_iFontID == 0 );

    // 所有支持DX10的设备都必须遵循统一的设备能力,因此DX10没有查询设备能力的
    // 支持函数.

    // OpenGL只支持primary和secondary两组顶点颜色.
    // 这里让DirectX渲染器与其保持一致.
    m_iMaxColors = 2;
    // 待实现.
    // 这些参数需参考DX10 SDK文档,目前为假设值.
    m_iMaxTCoords = 8;
    // VS_4_0支持vertex shader texture.
    m_iMaxVShaderImages = 4;
    m_iMaxGShaderImages = 4;
    m_iMaxPShaderImages = m_iMaxTCoords;
    m_iMaxUserClipPlanes = 8;
    m_iMaxStencilIndices = 8;
    m_iMaxVShaderProfile = Renderer::VS_4_0;
    m_iMaxGShaderProfile = Renderer::GS_4_0;
    m_iMaxPShaderProfile = Renderer::PS_4_0;
    m_iMaxRenderTargets = 8;

    // 相对于固定管线T&L部分,shader-based engine理论上无上限,
    // Swing Engine目前只支持8.
    m_iMaxLights = 8;
    m_aspLight = SE_NEW ObjectPtr[m_iMaxLights];

    m_iMaxActiveSamplerCount = m_iMaxVShaderImages + m_iMaxGShaderImages +
        m_iMaxPShaderImages;
    if( m_iMaxActiveSamplerCount > 0 )
    {
        m_apActiveSamplers =
            SE_NEW SamplerInformation*[m_iMaxActiveSamplerCount];

        memset(m_apActiveSamplers, 0, m_iMaxActiveSamplerCount*
            sizeof(SamplerInformation*));
    }

    // Cg runtime stuff begin.

    // Create Cg context.
    m_CgContext = cgCreateContext();
    SE_DX10_DEBUG_CG_PROGRAM;
    cgSetParameterSettingMode(m_CgContext, CG_DEFERRED_PARAMETER_SETTING);
    SE_DX10_DEBUG_CG_PROGRAM;

    // Bind the Cg context to the DX10 device.
    cgD3D10SetDevice(m_CgContext, m_pDX10Device);
    SE_DX10_DEBUG_CG_PROGRAM;

    // Get latest profiles.
    m_CgLatestVProfile = cgD3D10GetLatestVertexProfile();
    m_CgLatestGProfile = cgD3D10GetLatestGeometryProfile();
    m_CgLatestPProfile = cgD3D10GetLatestPixelProfile();

    // Cg runtime stuff end.

    // Create a default rasterizer state.
    D3D10_RASTERIZER_DESC tempRSDesc;
    tempRSDesc.FillMode = D3D10_FILL_SOLID;
    tempRSDesc.CullMode = D3D10_CULL_BACK;
    tempRSDesc.FrontCounterClockwise = false;
    tempRSDesc.DepthBias = 0;
    tempRSDesc.DepthBiasClamp = 0.0f;
    tempRSDesc.SlopeScaledDepthBias = 0.0f;
    tempRSDesc.ScissorEnable = false;
    tempRSDesc.MultisampleEnable = false;
    tempRSDesc.AntialiasedLineEnable = false;

    ms_hResult = m_pDX10Device->CreateRasterizerState(&tempRSDesc, 
        &m_pDX10RasterizerState);
    SE_ASSERT( SUCCEEDED(ms_hResult) );

    m_pDX10Device->RSSetState(m_pDX10RasterizerState);

    //// 初始化全局渲染状态为引擎默认设置.
    //SetGlobalState(GlobalState::Default);

    m_bCursorVisible = true;
    m_bDeviceLost = false;
    m_bBeginSceneActive = false;

	// test
	D3DX10_IMAGE_INFO fileInfo;
	D3DX10GetImageInfoFromFile("NVIDIA.png", 0, &fileInfo, 0);
	D3DX10_IMAGE_LOAD_INFO loadInfo;
	loadInfo.Width          = fileInfo.Width;
	loadInfo.Height         = fileInfo.Height;
	loadInfo.FirstMipLevel  = 0;
	loadInfo.MipLevels      = fileInfo.MipLevels;
	loadInfo.Usage          = D3D10_USAGE_DEFAULT;
	loadInfo.BindFlags      = D3D10_BIND_SHADER_RESOURCE;
	loadInfo.CpuAccessFlags = 0;
	loadInfo.MiscFlags      = 0;
	loadInfo.Format         = fileInfo.Format;    
	loadInfo.Filter         = D3DX10_FILTER_NONE;
	loadInfo.MipFilter      = D3DX10_FILTER_NONE;
	loadInfo.pSrcInfo       = &fileInfo;
	ms_hResult = D3DX10CreateTextureFromFile(m_pDX10Device, "NVIDIA.png", 
		&loadInfo, 0, &pTestTexture, 0);
	SE_ASSERT( SUCCEEDED(ms_hResult) );
}
//----------------------------------------------------------------------------
DX10Renderer::~DX10Renderer()
{
	// test
	pTestTexture->Release();

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

    m_pDX10RasterizerState->Release();
    m_pDX10Device->ClearState();

    // Cg runtime stuff begin.

    cgD3D10SetDevice(m_CgContext, 0);
    SE_DX10_DEBUG_CG_PROGRAM;

    // Release Cg context.
    cgDestroyContext(m_CgContext);

    // If this assertion is triggered, then most likely there are some Cg
    // runtime resources haven't been released. For example, maybe a geometry
    // object is still alive(which should be released already), and it is 
    // using a shader effect which itself is handling a Cg shader resource.
    SE_DX10_DEBUG_CG_PROGRAM;

    // Cg runtime stuff end.
}
//----------------------------------------------------------------------------
void DX10Renderer::ToggleFullscreen()
{
    //Renderer::ToggleFullscreen();
    //m_Present.Windowed = !m_Present.Windowed;

    //if( m_Present.Windowed )
    //{
    //    m_Present.FullScreen_RefreshRateInHz = 0;
    //}
    //else
    //{
    //    GetWindowRect(m_Present.hDeviceWindow, &m_rcWindow);
    //    m_Present.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    //}

    //if( m_Present.Windowed )
    //{
    //    SetWindowPos(m_Present.hDeviceWindow, 
    //        NULL, 
    //        m_rcWindow.left,
    //        m_rcWindow.top, 
    //        m_rcWindow.right - m_rcWindow.left,
    //        m_rcWindow.bottom - m_rcWindow.top,
    //        SWP_NOZORDER | SWP_DRAWFRAME | SWP_SHOWWINDOW);
    //}
}
//----------------------------------------------------------------------------
void DX10Renderer::ClearBackBuffer()
{
    //D3DXCOLOR tempClearColor(m_ClearColor.R, m_ClearColor.G, m_ClearColor.B, 
    //    m_ClearColor.A);

    m_pDX10Device->ClearRenderTargetView(m_pDX10RTView, m_ClearColor);
}
//----------------------------------------------------------------------------
void DX10Renderer::ClearZBuffer()
{
    m_pDX10Device->ClearDepthStencilView(m_pDX10DSView, D3D10_CLEAR_DEPTH,
        m_fClearDepth, 0);
}
//----------------------------------------------------------------------------
void DX10Renderer::ClearStencilBuffer()
{
    m_pDX10Device->ClearDepthStencilView(m_pDX10DSView, D3D10_CLEAR_STENCIL, 
        1.0f, (UINT8)m_uiClearStencil);
}
//----------------------------------------------------------------------------
void DX10Renderer::ClearBuffers()
{
    m_pDX10Device->ClearRenderTargetView(m_pDX10RTView, m_ClearColor);
    m_pDX10Device->ClearDepthStencilView(m_pDX10DSView, D3D10_CLEAR_DEPTH | 
        D3D10_CLEAR_STENCIL, m_fClearDepth, (UINT8)m_uiClearStencil);
}
//----------------------------------------------------------------------------
void DX10Renderer::ClearBackBuffer(int, int, int, int)
{
    // 待实现.
}
//----------------------------------------------------------------------------
void DX10Renderer::ClearZBuffer(int, int, int, int)
{
    // 待实现.
}
//----------------------------------------------------------------------------
void DX10Renderer::ClearStencilBuffer(int, int, int, int)
{
    // 待实现.
}
//----------------------------------------------------------------------------
void DX10Renderer::ClearBuffers(int, int, int, int)
{
    // 待实现.
}
//----------------------------------------------------------------------------
void DX10Renderer::DisplayBackBuffer()
{
    // 待实现.
    // 检查当前设备状态,比如是否已丢失.
    m_pDXGISwapChain->Present(0, 0);
} 
//----------------------------------------------------------------------------
void DX10Renderer::SetColorMask(bool bAllowRed, bool bAllowGreen,
    bool bAllowBlue, bool bAllowAlpha)
{
    Renderer::SetColorMask(bAllowRed, bAllowGreen, bAllowBlue, bAllowAlpha);
}
//----------------------------------------------------------------------------
void DX10Renderer::EnableUserClipPlane(int, const Plane3f&)
{
    // 待实现.
}
//----------------------------------------------------------------------------
void DX10Renderer::DisableUserClipPlane(int)
{
    // 待实现.
}
//----------------------------------------------------------------------------
const ID3D10Device* DX10Renderer::GetDevice()
{
    return m_pDX10Device;
}
//----------------------------------------------------------------------------
void DX10Renderer::OnPreDrawGeometry()
{
    SE_ASSERT( m_pGeometry->RStateBlock );

    EnableRenderStateBlock(m_pGeometry->RStateBlock);
}
//----------------------------------------------------------------------------
void DX10Renderer::OnPostDrawGeometry()
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void DX10Renderer::OnPreDrawPass(ShaderEffect* pEffect, int iPass, bool)
{
    RenderStateBlock* pRStateBlock = pEffect->GetRStateBlock(iPass);
    SE_ASSERT( pRStateBlock );

    EnableRenderStateBlock(pRStateBlock);
}
//----------------------------------------------------------------------------
void DX10Renderer::OnPostDrawPass(ShaderEffect*, int, bool)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Cg runtime stuff.
//----------------------------------------------------------------------------
CGcontext DX10Renderer::GetCgContext() const
{
    return m_CgContext;
}
//----------------------------------------------------------------------------
CGprofile DX10Renderer::GetCgLatestVertexProfile() const
{
    return m_CgLatestVProfile;
}
//----------------------------------------------------------------------------
CGprofile DX10Renderer::GetCgLatestPixelProfile() const
{
    return m_CgLatestPProfile;
}
//----------------------------------------------------------------------------
CGprofile DX10Renderer::GetCgLatestGeometryProfile() const
{
    return m_CgLatestGProfile;
}
//----------------------------------------------------------------------------