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

#ifndef Swing_ShaderEffect_H
#define Swing_ShaderEffect_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEEffect.h"
#include "SEVertexShader.h"
#include "SEGeometryShader.h"
#include "SEPixelShader.h"
#include "SERenderStateBlock.h"

namespace Swing
{

class SERenderer;

//----------------------------------------------------------------------------
// 名称:shader effect基类
// 说明:派生类实现者有责任知道effect所需shader program profile及相关资源.
// 作者:Sun Che
// 时间:20080702
// 更新时间:20090513
// 更新内容:加入geometry shader支持,目前这是一个可选stage.
//----------------------------------------------------------------------------
class SE_FOUNDATION_API ShaderEffect : public Effect
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    ShaderEffect(int iPassCount);
    virtual ~ShaderEffect(void);

    // shader effect是vertex/geometry/pixel shader的管理者.
    // 重新封装实现了shader类相关数据的访问接口,
    // 从而避免了较长的shader类相关数据的索引操作表达式.
    // 派生类应该在其构造函数中:
    // (1) 指定所需pass数量.
    // (2) 为每个pass指定所需vertex/geometry/pixel程序名.
    // (3) 为每个pass的shader程序指定所需纹理资源名.
    //
    // 每个pass的vertex/geometry/pixel shader所需的shader程序文本和纹理,
    // 将会作为资源,在pass被用来渲染几何体数据前,由渲染器自动装载.
    // 当然,也可以由用户手动指定装载.

    // vertex/geometry/pixel shader对数.
    // SetPassCount将重新分配vertex/geometry/pixel shader,alpha state数组大小.
    virtual void SetPassCount(int iPassCount);
    int GetPassCount(void) const;

    // multipass effect的混合模式.
    // 模式i表明pass i-1和pass i的像素颜色是如何混合的.
    // 对于一个应用于geometry对象的single effect来说,
    // 混合模式0是无关紧要的,该情况下源模式系数为SBF_ONE,
    // 目标模式系数为SDF_ZERO;也就是说,frame buffer的像素值被shader输出像素覆盖.
    // 如果多个effect应用于一个geometry对象,
    // 则混合模式0表明当前effect输出像素如何与frame buffer像素值进行混合.
    SEAlphaState* GetBlending(int iPass);

    // per-pass render state block访问.
    SERenderStateBlock* GetRStateBlock(int iPass);

    // 设置pass所需的任何global state并在稍后(渲染完毕)恢复相应state.
    // 基类默认实现:
    // 根据multipass和multieffect渲染的需要,开启和关闭alpha混合状态,
    // 从而使当前pass的输出像素值能够与frame buffer像素值正确混合.
    virtual void SetGlobalState(int iPass, SERenderer* pRenderer,
        bool bPrimaryEffect);
    virtual void RestoreGlobalState(int iPass, SERenderer* pRenderer,
        bool bPrimaryEffect);

    // vertex shader接口
    void SetVShader(int iPass, SEVertexShader* pVShader);
    SEVertexShader* GetVShader(int iPass);
    SEVertexProgram* GetVProgram(int iPass);
    const std::string& GetVShaderName(int iPass) const;
    int GetVConstantCount(int iPass) const;
    SEUserConstant* GetVConstant(int iPass, int i);
    SEUserConstant* GetVConstant(int iPass, const std::string& rName);
    int GetVTextureCount(int iPass) const;
    SETexture* GetVTexture(int iPass, int i);
    SETexture* GetVTexture(int iPass, const std::string& rName);
    void SetVTexture(int iPass, int i, SETexture* pTexture); // 允许应用程序指定纹理共享.
    void SetVImageName(int iPass, int i, const std::string& rName);
    const std::string& GetVImageName(int iPass, int i) const;

    // geometry shader接口
    void SetGShader(int iPass, SEGeometryShader* pGShader);
    SEGeometryShader* GetGShader(int iPass);
    SEGeometryProgram* GetGProgram(int iPass);
    const std::string& GetGShaderName(int iPass) const;
    int GetGConstantCount(int iPass) const;
    SEUserConstant* GetGConstant(int iPass, int i);
    SEUserConstant* GetGConstant(int iPass, const std::string& rName);
    int GetGTextureCount(int iPass) const;
    SETexture* GetGTexture(int iPass, int i);
    SETexture* GetGTexture(int iPass, const std::string& rName);
    void SetGTexture(int iPass, int i, SETexture* pTexture); // 允许应用程序指定纹理共享.
    void SetGImageName(int iPass, int i, const std::string& rName);
    const std::string& GetGImageName(int iPass, int i) const;

    // pixel shader接口
    void SetPShader(int iPass, SEPixelShader* pPShader);
    SEPixelShader* GetPShader(int iPass);
    SEPixelProgram* GetPProgram(int iPass);
    const std::string& GetPShaderName(int iPass) const;
    int GetPConstantCount(int iPass) const;
    SEUserConstant* GetPConstant(int iPass, int i);
    SEUserConstant* GetPConstant(int iPass, const std::string& rName);
    int GetPTextureCount(int iPass) const;
    SETexture* GetPTexture(int iPass, int i);
    SETexture* GetPTexture(int iPass, const std::string& rName);
    void SetPTexture(int iPass, int i, SETexture* pTexture); // 允许应用程序指定纹理共享.
    void SetPImageName(int iPass, int i, const std::string& rName);
    const std::string& GetPImageName(int iPass, int i) const;

    // 待实现.
    // 目前只支持effect pass携带的alpha state.
    // 在scene graph调用UpdateRS函数时,由SEGeometry类调用,
    // 更新当前shader effect各pass的render state block.
    virtual void OnUpdateData(void* pUserData);

    // 这些函数由SERenderer::LoadResources和SERenderer::ReleaseResources调用.
    // 也可以在应用程序中由用户手动调用初始化所需资源.
    virtual void LoadResources(SERenderer* pRenderer, SEGeometry* pGeometry);
    virtual void ReleaseResources(SERenderer* pRenderer, SEGeometry* pGeometry);

protected:
    // streaming support
    ShaderEffect(void);

    void SetDefaultAlphaState(void);

    int m_iPassCount;
    std::vector<SEVertexShaderPtr> m_VShader;
    std::vector<SEGeometryShaderPtr> m_GShader;
    std::vector<SEPixelShaderPtr> m_PShader;
    std::vector<SERenderStateBlockPtr> m_RStateBlocks;

// 内部使用
public:
    // 渲染器调用此函数从磁盘装载effect相应pass所需的shader程序.
    // 如果某shader程序装载失败,则使用一个默认shader.
    // 造成失败的各种情况:
    // (1) shader程序文件没找到.
    // (2) vertex程序的输出属性和pixel程序的输入属性不兼容.
    // (3) shader程序需要更多的颜色参数,超过渲染器支持范围.
    // (4) shader程序需要更多的texture image单元,超过渲染器支持范围.
    // (5) shader程序需要更多组纹理坐标,超过渲染器支持范围.
    void LoadPrograms(int iPass, SERenderer* pRenderer);

    void ReleasePrograms(int iPass);

    // 在LoadPrograms函数中,shader程序被创建后,会调用这个函数.
    // 这将允许ShaderEffect派生类重载该函数,从而实现自定义行为.
    // 派生类应该在这里为用户自定义常量指定存储位置.
    virtual void OnLoadPrograms(int iPass, SEProgram* pVProgram,
        SEProgram* pPProgram, SEProgram* pGProgram);

    // 在ReleasePrograms函数中,shader程序被释放前,会调用这个函数.
    // 这将允许ShaderEffect派生类重载该函数,从而实现自定义行为.
    virtual void OnReleasePrograms(int iPass, SEProgram* pVProgram,
        SEProgram* pPProgram, SEProgram* pGProgram);

    // 在渲染器应用当前effect进行渲染前(后),会调用这些函数.
    // 这将允许ShaderEffect派生类重载这些函数,从而实现自定义行为.
    virtual void OnPreApplyEffect(SERenderer* pRenderer, bool bPrimaryEffect);
    virtual void OnPostApplyEffect(SERenderer* pRenderer, bool bPrimaryEffect);

    // 在渲染器应用当前effect的每个pass进行渲染前(后),会调用这些函数.
    // 这将允许ShaderEffect派生类重载这些函数,从而实现自定义行为.
    virtual void OnPreApplyPass(int iPass, SERenderer* pRenderer, 
        bool bPrimaryEffect);
    virtual void OnPostApplyPass(int iPass, SERenderer* pRenderer, 
        bool bPrimaryEffect);
};

typedef SESmartPointer<ShaderEffect> ShaderEffectPtr;

}

#endif
