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

#ifndef Swing_Renderer_H
#define Swing_Renderer_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEFrameBuffer.h"
#include "SEAlphaState.h"
#include "SECullState.h"
#include "SEMaterialState.h"
#include "SEPolygonOffsetState.h"
#include "SEStencilState.h"
#include "SEWireframeState.h"
#include "SEZBufferState.h"
#include "SEColorRGB.h"
#include "SEColorRGBA.h"
#include "SEMatrix4.h"
#include "SERendererConstant.h"
#include "SEUserConstant.h"
#include "SESamplerInformation.h"

namespace Swing
{

class Attributes;
class Bindable;
class Camera;
class Effect;
class Geometry;
class GeometryProgram;
class IndexBuffer;
class Light;
class PixelProgram;
class ResourceIdentifier;
class ShaderEffect;
class Spatial;
class Texture;
class VertexBuffer;
class VertexProgram;
class UnculledObject;
class UnculledSet;
class RenderStateBlock;

//----------------------------------------------------------------------------
// Name:Renderer class
// Description:Renderer abstract base class
// Author:Sun Che
// Date:20080320
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Renderer
{
public:
    // Abstract base class.
    virtual ~Renderer(void);

    // RTTI.
    enum
    {
        OPENGL,
        OPENGLES1,
        OPENGLES2,
        DIRECTX9,
        DIRECTX10,
        SOFTWARE,
        MAX_RENDERER_TYPES
    };
    virtual int GetType(void) const = 0;

    // Camera access.
    void SetCamera(Camera* pCamera);
    inline Camera* GetCamera(void) const;

    // Frame buffer parameters.
    inline FrameBuffer::FormatType GetFormatType(void) const;
    inline FrameBuffer::DepthType GetDepthType(void) const;
    inline FrameBuffer::StencilType GetStencilType(void) const;
    inline FrameBuffer::BufferingType GetBufferingType(void) const;
    inline FrameBuffer::MultisamplingType GetMultisamplingType(void) const;

    // Window parameters.
    inline int GetWidth(void) const;
    inline int GetHeight(void) const;
    virtual void Resize(int iWidth, int iHeight);
    virtual void ToggleFullscreen(void);

    // Back buffer clear color.
    inline void SetClearColor(const ColorRGBA& rClearColor);
    inline const ColorRGBA& GetClearColor(void) const;

    // Depth buffer clear value.
    inline void SetClearDepth(float fClearDepth);
    inline float GetClearDepth(void) const;

    // Stencil buffer clear value.
    inline void SetClearStencil(unsigned int uiClearValue);
    inline unsigned int GetClearStencil(void) const;

    // Pre-draw/Post-draw, DIRECTX9 API specific stuff.
    virtual bool BeginScene(void);
    virtual void EndScene(void);

    // Full window buffer operation.
    virtual void ClearBackBuffer(void) = 0;
    virtual void ClearZBuffer(void) = 0;
    virtual void ClearStencilBuffer(void) = 0;
    virtual void ClearBuffers(void) = 0;
    virtual void DisplayBackBuffer(void) = 0;

    // Sub-window buffer operation.
    virtual void ClearBackBuffer(int iXPos, int iYPos, int iWidth,
        int iHeight) = 0;
    virtual void ClearZBuffer(int iXPos, int iYPos, int iWidth,
        int iHeight) = 0;
    virtual void ClearStencilBuffer(int iXPos, int iYPos, int iWidth,
        int iHeight) = 0;
    virtual void ClearBuffers(int iXPos, int iYPos, int iWidth,
        int iHeight) = 0;

    // Object rendering entry point.
    virtual void DrawScene(UnculledSet& rVisibleSet);
    virtual void Draw(Geometry* pGeometry);

    // Text rendering.
    virtual int LoadFont(const char* acFace, int iSize, bool bBold,
        bool bItalic) = 0;
    virtual void UnloadFont(int iFontID) = 0;
    virtual bool SelectFont(int iFontID) = 0;
    virtual void Draw(int iX, int iY, const ColorRGBA& rColor,
        const char* pText) = 0;

    // 2D rendering.
    virtual void Draw(const unsigned char* aucBuffer) = 0;

    // Vertex shader profiles.
    enum
    {
        VS_2_0,   // DirectX9
        VS_3_0,   // DirectX9
        VS_4_0,   // DirectX10
        ARBVP1,   // OpenGL
        VP40,     // OpenGL
        OES2VP1,  // OpenGL ES2.0
        SFTVP1,   // Software
        MAX_VP_TYPES
    };

    // Geometry shader profiles.
    // Geometry shader stage is an optional stage,
    // DirectX10 and OpenGL3 could support it for now.
    enum
    {
        GS_UNSUPPORTED, // Unsupported by current renderer
        GS_4_0,         // DirectX10
        GLSLG,          // OpenGL
        SFTGP1,         // Software
        MAX_GP_TYPES
    };

    // Pixel shader profile.
    enum
    {
        PS_2_0,    // DirectX9
        PS_3_0,    // DirectX9
        PS_4_0,    // DirectX10
        ARBFP1,    // OpenGL
        FP40,      // OpenGL
        OES2FP1,   // OpenGL ES2.0
        SFTFP1,    // Software
        MAX_PP_TYPES
    };

    // Renderer capability query.
    inline int GetMaxLights(void) const;
    inline int GetMaxColors(void) const;
    inline int GetMaxTCoords(void) const;
    inline int GetMaxVShaderImages(void) const;
    inline int GetMaxGShaderImages(void) const;
    inline int GetMaxPShaderImages(void) const;
    inline int GetMaxStencilIndices(void) const;
    inline int GetMaxUserClipPlanes(void) const;
    inline int GetMaxVShaderProfile(void) const;
    inline int GetMaxGShaderProfile(void) const;
    inline int GetMaxPShaderProfile(void) const;
    inline int GetMaxRenderTargets(void) const;

    // Shader compiler existence query.
    inline bool HasShaderCompiler(void) const;

    // Render state management.
    virtual void SetAlphaState(AlphaState* pState);
    virtual void SetCullState(CullState* pState);
    virtual void SetMaterialState(MaterialState* pState);
    virtual void SetPolygonOffsetState(PolygonOffsetState* pState);
    virtual void SetStencilState(StencilState* pState);
    virtual void SetWireframeState(WireframeState* pState);
    virtual void SetZBufferState(ZBufferState* pState);
    inline AlphaState* GetAlphaState(void);
    inline CullState* GetCullState(void);
    inline MaterialState* GetMaterialState(void);
    inline PolygonOffsetState* GetPolygonOffsetState(void);
    inline StencilState* GetStencilState(void);
    inline WireframeState* GetWireframeState(void);
    inline ZBufferState* GetZBufferState(void);
    inline void SetReverseCullFace(bool bReverseCullFace);
    inline bool GetReverseCullFace(void) const;

    // Prototype of bindable resource release function.
    typedef void (Renderer::*ReleaseFunction)(Bindable*);

    // Resource loading/releasing functions.
    void LoadAllResources(Spatial* pScene);
    void ReleaseAllResources(Spatial* pScene);
    void LoadResources(Geometry* pGeometry);
    void ReleaseResources(Geometry* pGeometry);
    void LoadResources(Effect* pEffect);
    void ReleaseResources(Effect* pEffect);
    void LoadVProgram(VertexProgram* pVProgram);
    void ReleaseVProgram(Bindable* pVProgram);
    void LoadGProgram(GeometryProgram* pGProgram);
    void ReleaseGProgram(Bindable* pGProgram);
    void LoadPProgram(PixelProgram* pPProgram);
    void ReleasePProgram(Bindable* pPProgram);
    void LoadTexture(Texture* pTexture);
    void ReleaseTexture(Bindable* pTexture);
    void LoadVBuffer(const Attributes& rIAttributes, 
        const Attributes& rOAttributes,
        VertexBuffer* pVBuffer, VertexProgram* pVProgram);
    void ReleaseVBuffer(Bindable* pVBuffer);
    void LoadIBuffer(IndexBuffer* pIBuffer);
    void ReleaseIBuffer(Bindable* pIBuffer);
    // DirectX10 specific functions.
    void LoadRenderStateBlock(RenderStateBlock* pRStateBlock);
    void ReleaseRenderStateBlock(Bindable* pRStateBlock);

    // Resource enabling/disabling functions.
    void EnableVProgram(VertexProgram* pVProgram);
    void DisableVProgram(VertexProgram* pVProgram);
    void EnableGProgram(GeometryProgram* pGProgram);
    void DisableGProgram(GeometryProgram* pGProgram);
    void EnablePProgram(PixelProgram* pPProgram);
    void DisablePProgram(PixelProgram* pPProgram);
    void EnableTexture(Texture* pTexture);
    void DisableTexture(Texture* pTexture);
    ResourceIdentifier* EnableVBuffer(const Attributes& rIAttributes,
        const Attributes& rOAttributes, VertexProgram* pVProgram = 0);
    void DisableVBuffer(ResourceIdentifier* pID, 
        VertexProgram* pVProgram = 0);
    void EnableIBuffer(void);
    void DisableIBuffer(void);
    // DirectX10 specific functions.
    void EnableRenderStateBlock(RenderStateBlock* pRStateBlock);
    void DisableRenderStateBlock(RenderStateBlock* pRStateBlock);

    // For use by effects with lights.
    inline void SetLightCount(int iCount);
    inline void SetLight(int i, Light* pLight);
    inline Light* GetLight(int i);

    // For use by effects with projectors.
    inline void SetProjector(Camera* pProjector);
    inline Camera* GetProjector(void);

    // Enable or disable which color channels will be written to the color
    // buffer.
    virtual void SetColorMask(bool bAllowRed, bool bAllowGreen,
        bool bAllowBlue, bool bAllowAlpha);
    virtual void GetColorMask(bool& rbAllowRed, bool& rbAllowGreen,
        bool& rbAllowBlue, bool& rbAllowAlpha);

    // Include additional clip planes.  The input plane must be in model
    // coordinates.  It is transformed internally to camera coordinates to
    // support clipping in clip space.
    virtual void EnableUserClipPlane(int i, const Plane3f& rPlane) = 0;
    virtual void DisableUserClipPlane(int i) = 0;

    // Support for model-to-world transformation management.
    void SetWorldTransformation(void);
    void RestoreWorldTransformation(void);

    // The input transformation is applied to world-space vertices before
    // the view matrix is applied.
    void SetPostWorldTransformation(const Matrix4f& rMatrix);
    void RestorePostWorldTransformation(void);

    // Access the current state of the matrices.
    inline const Matrix4f& GetWorldMatrix(void) const;
    inline const Matrix4f& GetViewMatrix(void) const;
    inline const Matrix4f& GetProjectionMatrix(void) const;

protected:
    // Abstract base class.
    Renderer(FrameBuffer::FormatType eFormat, FrameBuffer::DepthType eDepth,
        FrameBuffer::StencilType eStencil,
        FrameBuffer::BufferingType eBuffering,
        FrameBuffer::MultisamplingType eMultisampling,
        int iWidth, int iHeight);

    // Support for camera access and transformation setting.
    friend class Camera;
    void OnFrameChange(void);
    void OnFrustumChange(void);
    virtual void OnViewportChange(void) = 0;
    virtual void OnDepthRangeChange(void) = 0;

    // Global render state management.
    void SetGlobalState(GlobalStatePtr aspState[]);
    void RestoreGlobalState(GlobalStatePtr aspState[]);

    // Per-geometry pre/post-draw entry point.
    // CAUTION:
    // Renderer derived class should implements the setup of render state for
    // drawing a geometry.
    virtual void OnPreDrawGeometry(void) = 0;
    virtual void OnPostDrawGeometry(void) = 0;

    // Per-pass pre/post-draw entry point.
    // These functions are called by ShaderEffect class's OnPreApplyPass()/
    // OnPostApplyPass().
    // CAUTION:
    // Renderer derived class should implements the setup of render state for
    // drawing a pass.
    friend class ShaderEffect;
    virtual void OnPreDrawPass(ShaderEffect* pEffect, int iPass,
        bool bPrimaryEffect) = 0;
    virtual void OnPostDrawPass(ShaderEffect* pEffect, int iPass,
        bool bPrimaryEffect) = 0;

    // Support for light array management.
    void SetLights(void);
    void RestoreLights(void);

    // The main entry point to drawing in the derived-class renderers.
    virtual void DrawElements(void) = 0;

    // Resource loading/releasing functions.
    virtual void OnLoadVProgram(ResourceIdentifier*& rpID,
        VertexProgram* pVProgram) = 0;
    virtual void OnReleaseVProgram(ResourceIdentifier* pID) = 0;
    virtual void OnLoadGProgram(ResourceIdentifier*& rpID,
        GeometryProgram* pGProgram);
    virtual void OnReleaseGProgram(ResourceIdentifier* pID);
    virtual void OnLoadPProgram(ResourceIdentifier*& rpID,
        PixelProgram* pPProgram) = 0;
    virtual void OnReleasePProgram(ResourceIdentifier* pID) = 0;
    virtual void OnLoadTexture(ResourceIdentifier*& rpID,
        Texture* pTexture) = 0;
    virtual void OnReleaseTexture(ResourceIdentifier* pID) = 0;
    virtual void OnLoadVBuffer(ResourceIdentifier*& rpID,
        const Attributes& rIAttributes, const Attributes& rOAttributes,
        VertexBuffer* pVBuffer, VertexProgram* pVProgram) = 0;
    virtual void OnReleaseVBuffer(ResourceIdentifier* pID) = 0;
    virtual void OnLoadIBuffer(ResourceIdentifier*& rpID,
        IndexBuffer* pIBuffer) = 0;
    virtual void OnReleaseIBuffer(ResourceIdentifier* pID) = 0;
    // DirectX10 specific functions.
    virtual void OnLoadRenderStateBlock(ResourceIdentifier*& rpID,
        RenderStateBlock* pRStateBlock);
    virtual void OnReleaseRenderStateBlock(ResourceIdentifier* pID);

    // Resource enabling/disabling functions.
    virtual void SetVProgramRC(RendererConstant* pRC) = 0;
    virtual void SetVProgramUC(UserConstant* pUC) = 0;
    virtual void SetGProgramRC(RendererConstant* pRC) = 0;
    virtual void SetGProgramUC(UserConstant* pUC) = 0;
    virtual void SetPProgramRC(RendererConstant* pRC) = 0;
    virtual void SetPProgramUC(UserConstant* pUC) = 0;
    virtual void UpdateVProgramConstants(VertexProgram* pVProgram) = 0;
    virtual void UpdateGProgramConstants(GeometryProgram* pGProgram) = 0;
    virtual void UpdatePProgramConstants(PixelProgram* pPProgram) = 0;
    virtual void OnEnableVProgram(ResourceIdentifier* pID) = 0;
    virtual void OnDisableVProgram(ResourceIdentifier* pID) = 0;
    virtual void OnEnableGProgram(ResourceIdentifier* pID);
    virtual void OnDisableGProgram(ResourceIdentifier* pID);
    virtual void OnEnablePProgram(ResourceIdentifier* pID) = 0;
    virtual void OnDisablePProgram(ResourceIdentifier* pID) = 0;
    virtual void OnEnableTexture(ResourceIdentifier* pID) = 0;
    virtual void OnDisableTexture(ResourceIdentifier* pID) = 0;
    virtual void OnEnableVBuffer(ResourceIdentifier* pID, 
        VertexProgram* pVProgram) = 0;
    virtual void OnDisableVBuffer(ResourceIdentifier* pID, 
        VertexProgram* pVProgram) = 0;
    virtual void OnEnableIBuffer(ResourceIdentifier* pID) = 0;
    virtual void OnDisableIBuffer(ResourceIdentifier* pID) = 0;
    // DirectX10 specific functions.
    virtual void OnEnableRenderStateBlock(ResourceIdentifier* pID);
    virtual void OnDisableRenderStateBlock(ResourceIdentifier* pID);

    // 可选shader程序连接.
    // 某些图形管线的shader系统要求对已经装载并编译的shader程序进行连接.
    // 如GLSL,ESSL系统.
    // OpenGL ES2渲染器需要重载这个函数.
    // 连接过程发生后返回true,默认情况下没有连接过程时,返回false.
    virtual bool OnLinkPrograms(VertexProgram* pVProgram,
        GeometryProgram* pGProgram, PixelProgram* pPProgram);

    // 管线T&L的数据,主要靠设置shader程序的相关渲染器常量来实现.

    // Operation参数
    //   0 = matrix
    //   1 = transpose of matrix
    //   2 = inverse of matrix
    //   3 = inverse-transpose of matrix
    void GetTransform(const Matrix4f& rMat, int iOperation, float* afData);
    void SetConstantWMatrix(int iOperation, float* afData);
    void SetConstantVMatrix(int iOperation, float* afData);
    void SetConstantPMatrix(int iOperation, float* afData);
    void SetConstantWVMatrix(int iOperation, float* afData);
    void SetConstantVPMatrix(int iOperation, float* afData);
    void SetConstantWVPMatrix(int iOperation, float* afData);

    // 这些函数虽然没有使用option参数,但参数仍被包含了,
    // 这将允许类的静态函数指针数组来处理所有shader常量.
    void SetConstantMaterialEmissive(int, float* afData);
    void SetConstantMaterialAmbient(int, float* afData);
    void SetConstantMaterialDiffuse(int, float* afData);
    void SetConstantMaterialSpecular(int, float* afData);
    void SetConstantCameraModelPosition(int, float* afData);
    void SetConstantCameraModelRight(int, float* afData);
    void SetConstantCameraModelUp(int, float* afData);
    void SetConstantCameraModelDirection(int, float* afData);
    void SetConstantCameraWorldPosition(int, float* afData);
    void SetConstantCameraWorldRight(int, float* afData);
    void SetConstantCameraWorldUp(int, float* afData);
    void SetConstantCameraWorldDirection(int, float* afData);
    void SetConstantProjectorModelPosition(int, float* afData);
    void SetConstantProjectorModelRight(int, float* afData);
    void SetConstantProjectorModelUp(int, float* afData);
    void SetConstantProjectorModelDirection(int, float* afData);
    void SetConstantProjectorWorldPosition(int, float* afData);
    void SetConstantProjectorWorldRight(int, float* afData);
    void SetConstantProjectorWorldUp(int, float* afData);
    void SetConstantProjectorWorldDirection(int, float* afData);

    void SetConstantProjectorMatrix(int, float* afData);

    // 这些函数设置灯光状态.
    // 索引值iLight必须在0到7之间.(当前图形管线支持范围)
    void SetConstantLightModelPosition(int iLight, float* afData);
    void SetConstantLightModelDirection(int iLight, float* afData);
    void SetConstantLightWorldPosition(int iLight, float* afData);
    void SetConstantLightWorldDirection(int iLight, float* afData);
    void SetConstantLightAmbient(int iLight, float* afData);
    void SetConstantLightDiffuse(int iLight, float* afData);
    void SetConstantLightSpecular(int iLight, float* afData);
    void SetConstantLightSpotCutoff(int iLight, float* afData);
    void SetConstantLightAttenuation(int iLight, float* afData);

    void SetConstantLightCount(int, float* afData);

    enum { SC_COUNT = 37 };
    typedef void (Renderer::*SetConstantFunction)(int, float*);
    static SetConstantFunction ms_aoSCFunction[SC_COUNT];
    void SetRendererConstant(RendererConstant::Type eRCType, float* afData);

    // 对象渲染.
    void ApplyEffect(ShaderEffect* pEffect, bool& rbPrimaryEffect);

// Data member:
protected:
    // 设备能力与资源限制,由渲染器派生类负责检测并设置.
    int m_iMaxLights;
    int m_iMaxColors;
    int m_iMaxTCoords;
    int m_iMaxVShaderImages;
    int m_iMaxGShaderImages;
    int m_iMaxPShaderImages;
    int m_iMaxStencilIndices;
    int m_iMaxUserClipPlanes;
    int m_iMaxVShaderProfile;
    int m_iMaxGShaderProfile;
    int m_iMaxPShaderProfile;
    int m_iMaxRenderTargets;

    // Active samplers in shader programs, at most m_iMaxVShaderImages of them
    // for vertex programs and at most m_iMaxGShaderImages of them for geometry
    // programs and at most m_iMaxPShaderImages of them for pixel programs.
    int m_iNumActiveSamplers;
    int m_iCurrentSampler;
    int m_iMaxActiveSamplerCount;
    SamplerInformation** m_apActiveSamplers;

    // 渲染器是否具备shader compiler,
    // shader compiler可以提供shader源代码在装载阶段的online compilation.
    // 对于桌面OpenGL/DirectX系统,都具备shader compiler.
    // 对于移动设备则有可能不具备shader compiler.
    // 目前用于支持OpenGL ES2的shader compiler检测.
    bool m_bHasShaderCompiler;  // default: true

    // 窗口和frame buffer参数.
    FrameBuffer::FormatType m_eFormat;
    FrameBuffer::DepthType m_eDepth;
    FrameBuffer::StencilType m_eStencil;
    FrameBuffer::BufferingType m_eBuffering;
    FrameBuffer::MultisamplingType m_eMultisampling;
    int m_iWidth, m_iHeight;
    ColorRGBA m_ClearColor;
    float m_fClearDepth;
    unsigned int m_uiClearStencil;
    bool m_bAllowRed, m_bAllowGreen, m_bAllowBlue, m_bAllowAlpha;

    // 用于建立截投体的当前摄像机.
    Camera* m_pCamera;

    // 全局渲染状态数组.
    GlobalStatePtr m_aspState[GlobalState::MAX_STATE_TYPE];

    // shader常量设置函数用于查找的light数组.
    // 渲染器派生类必须在构造期间创建这个数组,包含m_iMaxLights个数组元素.
    // 渲染器派生类析构时释放该数组.
    int m_iNumActiveLights;
    ObjectPtr* m_aspLight;

    // 为某些特效提供方便的投影器,
    // 比如projected texture和shadow map.
    Camera* m_pProjector;

    // 当前正在渲染的几何体对象.
    Geometry* m_pGeometry;

    // 几何渲染管线所使用的矩阵变换.
    // 支持1x4的行向量乘以4x4矩阵.
    Matrix4f m_WorldMatrix, m_SaveWorldMatrix;
    Matrix4f m_ViewMatrix, m_SaveViewMatrix;
    Matrix4f m_ProjectionMatrix, m_SaveProjectionMatrix;

    // 当前渲染的字体ID.
    int m_iFontID;

    // 支持镜面特效(默认为false).
    bool m_bReverseCullFace;

    // 全屏/窗口模式标志.
    bool m_bFullscreen;
};

#include "SERenderer.inl"

}

#endif
