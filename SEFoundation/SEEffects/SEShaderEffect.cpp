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

#include "SEFoundationPCH.h"
#include "SEShaderEffect.h"
#include "SEVertexProgramCatalog.h"
#include "SEGeometryProgramCatalog.h"
#include "SEPixelProgramCatalog.h"
#include "SERenderer.h"
#include "SEGeometry.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SEShaderEffect, SEEffect);
SE_IMPLEMENT_STREAM(SEShaderEffect);

//SE_REGISTER_STREAM(SEShaderEffect);

//----------------------------------------------------------------------------
SEShaderEffect::SEShaderEffect(int iPassCount)
{
    SE_ASSERT( iPassCount > 0 );

    SetPassCount(iPassCount);
}
//----------------------------------------------------------------------------
SEShaderEffect::SEShaderEffect()
{
    m_iPassCount = 0;
}
//----------------------------------------------------------------------------
SEShaderEffect::~SEShaderEffect()
{
}
//----------------------------------------------------------------------------
void SEShaderEffect::SetPassCount(int iPassCount)
{
    SE_ASSERT( iPassCount > 0 );

    m_iPassCount = iPassCount;

    m_VShader.resize(m_iPassCount);
    m_GShader.resize(m_iPassCount);
    m_PShader.resize(m_iPassCount);
    m_RStateBlocks.resize(m_iPassCount);
    for( int i = 0; i < m_iPassCount; i++ )
    {
        if( !m_RStateBlocks[i] )
        {
            m_RStateBlocks[i] = SE_NEW SERenderStateBlock;
        }
    }
    SetDefaultAlphaState();
}
//----------------------------------------------------------------------------
int SEShaderEffect::GetPassCount() const
{
    return m_iPassCount;
}
//----------------------------------------------------------------------------
SEAlphaState* SEShaderEffect::GetBlending(int iPass)
{
    // 派生类也许希望通过使用alpha state来选择shader程序进行single-pass渲染.
    // 派生类可以改变render state block数组大小,
    // 从而使其包含更多的自定义alpha state.
    // 因此,render state block数组元素个数可以超过effect pass个数,
    // 这里不对iPass和m_iPassCount进行比较.
    SE_ASSERT( 0 <= iPass && iPass < (int)m_RStateBlocks.size() );

    SEGlobalState* pState = m_RStateBlocks[iPass]->States[
        SEGlobalState::ALPHA];
    return (SEAlphaState*)pState;
}
//----------------------------------------------------------------------------
SERenderStateBlock* SEShaderEffect::GetRStateBlock(int iPass)
{
    SE_ASSERT( 0 <= iPass && iPass < (int)m_RStateBlocks.size() );

    return m_RStateBlocks[iPass];
}
//----------------------------------------------------------------------------
void SEShaderEffect::SetGlobalState(int iPass, SERenderer* pRenderer,
    bool bPrimaryEffect)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount && pRenderer );

    // 允许所有非primary effect的effect pass开启alpha混合,
    // 允许所有大于1的pass开启alpha混合,
    // 从而允许当前pass输出像素值与之前pass的输出像素值进行alpha混合.
    if( !bPrimaryEffect || iPass > 0 )
    {
        SEGlobalState* pState = 
            m_RStateBlocks[iPass]->States[SEGlobalState::ALPHA];
        SEAlphaState* pAState = (SEAlphaState*)pState;
        pAState->BlendEnabled = true;

        SEAlphaStatePtr spSave = pRenderer->GetAlphaState();
        pRenderer->SetAlphaState(pAState);
        m_RStateBlocks[iPass]->States[SEGlobalState::ALPHA] = spSave;
    }
}
//----------------------------------------------------------------------------
void SEShaderEffect::RestoreGlobalState(int iPass, SERenderer* pRenderer,
    bool bPrimaryEffect)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount && pRenderer );

    if( !bPrimaryEffect || iPass > 0 )
    {
        SEGlobalState* pState = 
            m_RStateBlocks[iPass]->States[SEGlobalState::ALPHA];
        SEAlphaState* pAState = (SEAlphaState*)pState;

        SEAlphaStatePtr spSave = pRenderer->GetAlphaState();
        pRenderer->SetAlphaState(pAState);
        m_RStateBlocks[iPass]->States[SEGlobalState::ALPHA] = spSave;
    }
}
//----------------------------------------------------------------------------
void SEShaderEffect::SetVShader(int iPass, SEVertexShader* pVShader)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    m_VShader[iPass] = pVShader;
}
//----------------------------------------------------------------------------
SEVertexShader* SEShaderEffect::GetVShader(int iPass)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_VShader[iPass];
}
//----------------------------------------------------------------------------
SEVertexProgram* SEShaderEffect::GetVProgram(int iPass)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_VShader[iPass]->GetProgram();
}
//----------------------------------------------------------------------------
const std::string& SEShaderEffect::GetVShaderName(int iPass) const
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_VShader[iPass]->GetShaderName();
}
//----------------------------------------------------------------------------
int SEShaderEffect::GetVConstantCount(int iPass) const
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    SEProgram* pVProgram = m_VShader[iPass]->GetProgram();

    return pVProgram ? pVProgram->GetUCCount() : 0;
}
//----------------------------------------------------------------------------
SEUserConstant* SEShaderEffect::GetVConstant(int iPass, int i)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    SEProgram* pVProgram = m_VShader[iPass]->GetProgram();
    if( pVProgram )
    {
        SE_ASSERT( 0 <= i && i < pVProgram->GetUCCount() );

        return pVProgram->GetUC(i);
    }

    return 0;
}
//----------------------------------------------------------------------------
SEUserConstant* SEShaderEffect::GetVConstant(int iPass, const std::string& 
    rName)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    SEProgram* pVProgram = m_VShader[iPass]->GetProgram();

    return pVProgram ? pVProgram->GetUC(rName) : 0;
}
//----------------------------------------------------------------------------
int SEShaderEffect::GetVTextureCount(int iPass) const
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_VShader[iPass]->GetTextureCount();
}
//----------------------------------------------------------------------------
SETexture* SEShaderEffect::GetVTexture(int iPass, int i)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_VShader[iPass]->GetTexture(i);
}
//----------------------------------------------------------------------------
SETexture* SEShaderEffect::GetVTexture(int iPass, const std::string& rName)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_VShader[iPass]->GetTexture(rName);
}
//----------------------------------------------------------------------------
void SEShaderEffect::SetVTexture(int iPass, int i, SETexture* pTexture)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    m_VShader[iPass]->SetTexture(i, pTexture);
}
//----------------------------------------------------------------------------
void SEShaderEffect::SetVImageName(int iPass, int i, const std::string& rName)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    m_VShader[iPass]->SetImageName(i, rName);
}
//----------------------------------------------------------------------------
const std::string& SEShaderEffect::GetVImageName(int iPass, int i) const
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_VShader[iPass]->GetImageName(i);
}
//----------------------------------------------------------------------------
void SEShaderEffect::SetGShader(int iPass, SEGeometryShader* pGShader)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    m_GShader[iPass] = pGShader;
}
//----------------------------------------------------------------------------
SEGeometryShader* SEShaderEffect::GetGShader(int iPass)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_GShader[iPass];
}
//----------------------------------------------------------------------------
SEGeometryProgram* SEShaderEffect::GetGProgram(int iPass)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_GShader[iPass]->GetProgram();
}
//----------------------------------------------------------------------------
const std::string& SEShaderEffect::GetGShaderName(int iPass) const
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_GShader[iPass]->GetShaderName();
}
//----------------------------------------------------------------------------
int SEShaderEffect::GetGConstantCount(int iPass) const
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    SEProgram* pGProgram = m_GShader[iPass]->GetProgram();

    return pGProgram ? pGProgram->GetUCCount() : 0;
}
//----------------------------------------------------------------------------
SEUserConstant* SEShaderEffect::GetGConstant(int iPass, int i)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    SEProgram* pGProgram = m_GShader[iPass]->GetProgram();
    if( pGProgram )
    {
        SE_ASSERT( 0 <= i && i < pGProgram->GetUCCount() );

        return pGProgram->GetUC(i);
    }

    return 0;
}
//----------------------------------------------------------------------------
SEUserConstant* SEShaderEffect::GetGConstant(int iPass, const std::string& 
    rName)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    SEProgram* pGProgram = m_GShader[iPass]->GetProgram();

    return pGProgram ? pGProgram->GetUC(rName) : 0;
}
//----------------------------------------------------------------------------
int SEShaderEffect::GetGTextureCount(int iPass) const
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_GShader[iPass]->GetTextureCount();
}
//----------------------------------------------------------------------------
SETexture* SEShaderEffect::GetGTexture(int iPass, int i)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_GShader[iPass]->GetTexture(i);
}
//----------------------------------------------------------------------------
SETexture* SEShaderEffect::GetGTexture(int iPass, const std::string& rName)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_GShader[iPass]->GetTexture(rName);
}
//----------------------------------------------------------------------------
void SEShaderEffect::SetGTexture(int iPass, int i, SETexture* pTexture)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    m_GShader[iPass]->SetTexture(i, pTexture);
}
//----------------------------------------------------------------------------
void SEShaderEffect::SetGImageName(int iPass, int i, const std::string& rName)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    m_GShader[iPass]->SetImageName(i, rName);
}
//----------------------------------------------------------------------------
const std::string& SEShaderEffect::GetGImageName(int iPass, int i) const
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_GShader[iPass]->GetImageName(i);
}
//----------------------------------------------------------------------------
void SEShaderEffect::SetPShader(int iPass, SEPixelShader* pPShader)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    m_PShader[iPass] = pPShader;
}
//----------------------------------------------------------------------------
SEPixelShader* SEShaderEffect::GetPShader(int iPass)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_PShader[iPass];
}
//----------------------------------------------------------------------------
SEPixelProgram* SEShaderEffect::GetPProgram(int iPass)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_PShader[iPass]->GetProgram();
}
//----------------------------------------------------------------------------
const std::string& SEShaderEffect::GetPShaderName(int iPass) const
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_PShader[iPass]->GetShaderName();
}
//----------------------------------------------------------------------------
int SEShaderEffect::GetPConstantCount(int iPass) const
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    SEProgram* pPProgram = m_PShader[iPass]->GetProgram();

    return pPProgram ? pPProgram->GetUCCount() : 0;
}
//----------------------------------------------------------------------------
SEUserConstant* SEShaderEffect::GetPConstant(int iPass, int i)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    SEProgram* pPProgram = m_PShader[iPass]->GetProgram();
    if( pPProgram )
    {
        SE_ASSERT( 0 <= i && i < pPProgram->GetUCCount() );

        return pPProgram->GetUC(i);
    }

    return 0;
}
//----------------------------------------------------------------------------
SEUserConstant* SEShaderEffect::GetPConstant(int iPass, const std::string& 
    rName)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    SEProgram* pPProgram = m_PShader[iPass]->GetProgram();

    return pPProgram ? pPProgram->GetUC(rName) : 0;
}
//----------------------------------------------------------------------------
int SEShaderEffect::GetPTextureCount(int iPass) const
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    SEProgram* pPProgram = m_PShader[iPass]->GetProgram();

    return pPProgram ? pPProgram->GetSICount() : 0;
}
//----------------------------------------------------------------------------
SETexture* SEShaderEffect::GetPTexture(int iPass, int i)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_PShader[iPass]->GetTexture(i);
}
//----------------------------------------------------------------------------
SETexture* SEShaderEffect::GetPTexture(int iPass, const std::string& rName)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_PShader[iPass]->GetTexture(rName);
}
//----------------------------------------------------------------------------
void SEShaderEffect::SetPTexture(int iPass, int i, SETexture* pTexture)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    m_PShader[iPass]->SetTexture(i, pTexture);
}
//----------------------------------------------------------------------------
void SEShaderEffect::SetPImageName(int iPass, int i, const std::string& rName)
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    m_PShader[iPass]->SetImageName(i, rName);
}
//----------------------------------------------------------------------------
const std::string& SEShaderEffect::GetPImageName(int iPass, int i) const
{
    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );

    return m_PShader[iPass]->GetImageName(i);
}
//----------------------------------------------------------------------------
void SEShaderEffect::SetDefaultAlphaState()
{
    // 创建所有pass所需的默认alpha state.
    // 渲染器在multi-effect和multi-pass渲染时使用这些state.
    // 第一个pass使用默认alpha state(SBF_SRC_ALPHA, DBF_ONE_MINUS_SRC_ALPHA).
    // 其他pass使用颜色调制运算(SBF_DST_COLOR, DBF_ZERO).
    // 应用程序通过调用effect->GetBlending(pass)访问pass的alpha state,
    // 从而可以任意修改这些alpha state的混合运算方式.
    SEAlphaState* pAState = SE_NEW SEAlphaState;
    pAState->BlendEnabled = true;
    if( !m_RStateBlocks[0] )
    {
        m_RStateBlocks[0] = SE_NEW SERenderStateBlock;
    }
    m_RStateBlocks[0] = SE_NEW SERenderStateBlock;
    m_RStateBlocks[0]->States[SEGlobalState::ALPHA] = pAState;

    for( int i = 1; i < (int)m_RStateBlocks.size(); i++ )
    {
        pAState = SE_NEW SEAlphaState; 
        pAState->BlendEnabled = true;
        pAState->SrcBlend = SEAlphaState::SBF_DST_COLOR;
        pAState->DstBlend = SEAlphaState::DBF_ZERO;

        if( !m_RStateBlocks[i] )
        {
            m_RStateBlocks[i] = SE_NEW SERenderStateBlock;
        }
        m_RStateBlocks[i]->States[SEGlobalState::ALPHA] = pAState;
    }
}
//----------------------------------------------------------------------------
void SEShaderEffect::LoadPrograms(int iPass, SERenderer* pRenderer)
{
    // 当前pass的vertex/pixel shader都必须装载到系统内存,
    // geometry shader为可选stage.

    SE_ASSERT( 0 <= iPass && iPass < m_iPassCount );
    SE_ASSERT( m_VShader[iPass] && m_PShader[iPass] );

    SEProgram* pVProgram = m_VShader[iPass]->GetProgram();
    SEProgram* pPProgram = m_PShader[iPass]->GetProgram();

    SE_ASSERT( (pVProgram != 0) == (pPProgram != 0) );
    (void)pPProgram;  // 避免release版本编译器警告

    if( pVProgram )
    {
        // 程序已经装载,则返回.
        return;
    }

    // 检查当前pass是否指定了geometry shader.
    SEProgram* pGProgram = 0;
    bool bIsGShaderEnabled = false;
    if( m_GShader[iPass] )
    {
        bIsGShaderEnabled = true;
        pGProgram = m_GShader[iPass]->GetProgram();
    }

    // 装载vertex程序到系统内存.
    SEVertexProgramPtr spVProgram = SEVertexProgramCatalog::GetActive()->Find(
        m_VShader[iPass]->GetShaderName(), 
        m_VShader[iPass]->GetInterfaceDescriptor());
    SE_ASSERT( spVProgram );

    // 装载geometry程序到系统内存.
    if( bIsGShaderEnabled && !pGProgram )
    {
        // 确保应用层必须创建了一个可用的SEGeometryProgramCatalog.
        SEGeometryProgramCatalog* pGProgramCatalog = 
            SEGeometryProgramCatalog::GetActive();
        SE_ASSERT( pGProgramCatalog );

        pGProgram = pGProgramCatalog->Find(m_GShader[iPass]->GetShaderName(), 
            m_GShader[iPass]->GetInterfaceDescriptor());
        SE_ASSERT( pGProgram );
    }
    SEGeometryProgramPtr spGProgram = StaticCast<SEGeometryProgram>(pGProgram);

    // 装载pixel程序到系统内存.
    SEPixelProgramPtr spPProgram = SEPixelProgramCatalog::GetActive()->Find(
        m_PShader[iPass]->GetShaderName(), 
        m_PShader[iPass]->GetInterfaceDescriptor());
    SE_ASSERT( spPProgram );

    // 根据某些图形管线shader系统的需要,
    // 对已经提前装载到显存的shader程序进行连接.
    // 目前用于支持OpenGL ES2渲染器的shader系统.
    // 如果连接后的shader程序已经由图形API进行过兼容性验证,
    // 则我们无需再次验证.
    bool bLinked = pRenderer->OnLinkPrograms(spVProgram, spGProgram,
        spPProgram);

    if( !bLinked )
    {
        // 确保vertex程序输出属性和pixel程序输入属性兼容(无geometry程序时).
        // 每个vertex程序都总会输出一个clip position(无geometry程序时).
        // vertex/geometry程序两者之一必须输出一个clip position,
        // 这与兼容性检查无关.
        // 待实现.
        // 如果当前pass指定了geometry程序,
        // 则需确保vertex程序输出属性和geometry程序输入属性兼容,
        // geometry程序输出属性与pixel程序输入属性兼容.
        std::string StrDefault("Default");
        const SEAttributes& rVOAttributes = spVProgram->GetOutputAttributes();
        const SEAttributes& rPIAttributes = spPProgram->GetInputAttributes();
        if( !rVOAttributes.Matches(rPIAttributes, false, true, true, true) )
        {
            // vertex程序输出属性与pixel程序输入属性不兼容.
            // 则使用默认shader对象.
            if( spVProgram->GetName() != StrDefault )
            {
                m_VShader[iPass] = SE_NEW SEVertexShader(StrDefault);
                spVProgram = SEVertexProgramCatalog::GetActive()->Find(
                    StrDefault);
                SE_ASSERT( spVProgram );
            }

            if( spPProgram->GetName() != StrDefault )
            {
                m_PShader[iPass] = SE_NEW SEPixelShader(StrDefault);
                spPProgram = SEPixelProgramCatalog::GetActive()->Find(
                    StrDefault);
                SE_ASSERT( spPProgram );
            }
        }

        // 验证shader程序所需资源是否超过渲染器支持范围.
        // 待实现.
        // 验证geometry程序所需资源是否超过渲染器支持范围.
        const SEAttributes& rVIAttributes = spVProgram->GetInputAttributes();
        if( rVIAttributes.GetMaxColors()  > pRenderer->GetMaxColors()
            || rVIAttributes.GetMaxTCoords() > pRenderer->GetMaxTCoords()
            || rVOAttributes.GetMaxColors()  > pRenderer->GetMaxColors()
            || rVOAttributes.GetMaxTCoords() > pRenderer->GetMaxTCoords()
            || rPIAttributes.GetMaxColors()  > pRenderer->GetMaxColors()
            || rPIAttributes.GetMaxTCoords() > pRenderer->GetMaxTCoords()
            || spVProgram->GetSICount() > pRenderer->GetMaxVShaderImages()
            || spPProgram->GetSICount() > pRenderer->GetMaxPShaderImages() )
        {
            // 所需资源超过渲染器支持范围.则使用默认shader对象.
            if( spVProgram->GetName() != StrDefault )
            {
                m_VShader[iPass] = SE_NEW SEVertexShader(StrDefault);
                spVProgram = SEVertexProgramCatalog::GetActive()->Find(
                    StrDefault);
                SE_ASSERT( spVProgram );
            }

            if( spPProgram->GetName() != StrDefault )
            {
                m_PShader[iPass] = SE_NEW SEPixelShader(StrDefault);
                spPProgram = SEPixelProgramCatalog::GetActive()->Find(
                    StrDefault);
                SE_ASSERT( spPProgram );
            }
        }
    }

    // 装载shader程序所需纹理资源到系统内存.
    m_VShader[iPass]->OnLoadProgram(spVProgram);
    m_PShader[iPass]->OnLoadProgram(spPProgram);
    if( bIsGShaderEnabled )
    {
        m_GShader[iPass]->OnLoadProgram(spGProgram);
    }

    // SEShaderEffect派生类自定义行为入口.
    // 派生类应该在这里为用户自定义常量指定存储位置.
    OnLoadPrograms(iPass, spVProgram, spPProgram, spGProgram);
}
//----------------------------------------------------------------------------
void SEShaderEffect::ReleasePrograms(int iPass)
{
    SEProgram* pGProgram = 0;
    if( m_GShader[iPass] )
    {
        pGProgram = m_GShader[iPass]->GetProgram();
    }

    OnReleasePrograms(iPass, m_VShader[iPass]->GetProgram(),
        m_PShader[iPass]->GetProgram(), pGProgram);

    m_VShader[iPass]->OnReleaseProgram();
    m_PShader[iPass]->OnReleaseProgram();

    if( m_GShader[iPass] )
    {
        m_GShader[iPass]->OnReleaseProgram();
    }
}
//----------------------------------------------------------------------------
void SEShaderEffect::OnLoadPrograms(int, SEProgram*, SEProgram*, SEProgram*)
{
}
//----------------------------------------------------------------------------
void SEShaderEffect::OnReleasePrograms(int, SEProgram*, SEProgram*, 
    SEProgram*)
{
}
//----------------------------------------------------------------------------
void SEShaderEffect::OnPreApplyEffect(SERenderer*, bool)
{
}
//----------------------------------------------------------------------------
void SEShaderEffect::OnPostApplyEffect(SERenderer*, bool)
{
}
//----------------------------------------------------------------------------
void SEShaderEffect::OnPreApplyPass(int iPass, SERenderer* pRenderer,
    bool bPrimaryEffect)
{
    pRenderer->OnPreDrawPass(this, iPass, bPrimaryEffect);
}
//----------------------------------------------------------------------------
void SEShaderEffect::OnPostApplyPass(int iPass, SERenderer* pRenderer,
    bool bPrimaryEffect)
{
    pRenderer->OnPostDrawPass(this, iPass, bPrimaryEffect);
}
//----------------------------------------------------------------------------
void SEShaderEffect::OnUpdateData(void*)
{
}
//----------------------------------------------------------------------------
void SEShaderEffect::LoadResources(SERenderer* pRenderer, SEGeometry* 
    pGeometry)
{
    for( int iPass = 0; iPass < m_iPassCount; iPass++ )
    {
        // 为shader对象装载shader程序到系统内存.
        // 为shader constant分配默认系统内存数据存储位置.
        // 把shader程序所需纹理装载入系统内存.
        //
        // 当前pass的vertex/pixel shader都必须装载到显存,
        // geometry shader为可选stage.

        LoadPrograms(iPass, pRenderer);

        // 把shader程序资源装载入显存.
        SEVertexProgram* pVProgram = m_VShader[iPass]->GetProgram();
        pRenderer->LoadVProgram(pVProgram);
        SEPixelProgram* pPProgram = m_PShader[iPass]->GetProgram(); 
        pRenderer->LoadPProgram(pPProgram);
        if( m_GShader[iPass] )
        {
            SEGeometryProgram* pGProgram = m_GShader[iPass]->GetProgram();
            pRenderer->LoadGProgram(pGProgram);
        }

        // 把shader程序所需纹理资源装载入显存.
        int i, iTCount; 
        iTCount = GetVTextureCount(iPass);
        for( i = 0; i < iTCount; i++ )
        {
            pRenderer->LoadTexture(m_VShader[iPass]->GetTexture(i));
        }
        iTCount = GetPTextureCount(iPass);
        for( i = 0; i < iTCount; i++ )
        {
            pRenderer->LoadTexture(m_PShader[iPass]->GetTexture(i));
        }
        if( m_GShader[iPass] )
        {
            iTCount = GetGTextureCount(iPass);
            for( i = 0; i < iTCount; i++ )
            {
                pRenderer->LoadTexture(m_GShader[iPass]->GetTexture(i));
            }
        }

        if( pGeometry )
        {
            // 把shader程序所需VB子集装载入显存.
            const SEAttributes& rIAttr = pVProgram->GetInputAttributes();
            const SEAttributes& rOAttr = pVProgram->GetOutputAttributes();
            pRenderer->LoadVBuffer(rIAttr, rOAttr, pGeometry->VBuffer, 
            pVProgram);
        }
    }
}
//----------------------------------------------------------------------------
void SEShaderEffect::ReleaseResources(SERenderer* pRenderer, SEGeometry*)
{
    for( int iPass = 0; iPass < m_iPassCount; iPass++ )
    {
        // 从显存释放纹理.
        int i, iTCount;
        iTCount = GetVTextureCount(iPass);
        for( i = 0; i < iTCount; i++ )
        {
            pRenderer->ReleaseTexture(m_VShader[iPass]->GetTexture(i));
        }
        iTCount = GetPTextureCount(iPass);
        for( int i = 0; i < iTCount; i++ )
        {
            pRenderer->ReleaseTexture(m_PShader[iPass]->GetTexture(i));
        }
        if( m_GShader[iPass] )
        {
            iTCount = GetGTextureCount(iPass);
            for( i = 0; i < iTCount; i++ )
            {
                pRenderer->ReleaseTexture(m_GShader[iPass]->GetTexture(i));
            }
        }

        // 从显存释放shader程序.
        pRenderer->ReleaseVProgram(m_VShader[iPass]->GetProgram());
        pRenderer->ReleasePProgram(m_PShader[iPass]->GetProgram());
        if( m_GShader[iPass] )
        {
            pRenderer->ReleaseGProgram(m_GShader[iPass]->GetProgram());
        }

        // 从shader对象释放shader程序.
        ReleasePrograms(iPass);
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// name and unique id
//----------------------------------------------------------------------------
SEObject* SEShaderEffect::GetObjectByName(const std::string& rName)
{
    SEObject* pFound = SEEffect::GetObjectByName(rName);
    if( pFound )
    {
        return pFound;
    }

    for( int iPass = 0; iPass < m_iPassCount; iPass++ )
    {
        if( m_VShader[iPass] )
        {
            pFound = m_VShader[iPass]->GetObjectByName(rName);
            if( pFound )
            {
                return pFound;
            }
        }

        if( m_GShader[iPass] )
        {
            pFound = m_GShader[iPass]->GetObjectByName(rName);
            if( pFound )
            {
                return pFound;
            }
        }

        if( m_PShader[iPass] )
        {
            pFound = m_PShader[iPass]->GetObjectByName(rName);
            if( pFound )
            {
                return pFound;
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
void SEShaderEffect::GetAllObjectsByName(const std::string& rName,
    std::vector<SEObject*>& rObjects)
{
    SEEffect::GetAllObjectsByName(rName, rObjects);

    for( int iPass = 0; iPass < m_iPassCount; iPass++ )
    {
        if( m_VShader[iPass] )
        {
            m_VShader[iPass]->GetAllObjectsByName(rName, rObjects);
        }

        if( m_GShader[iPass] )
        {
            m_GShader[iPass]->GetAllObjectsByName(rName, rObjects);
        }

        if( m_PShader[iPass] )
        {
            m_PShader[iPass]->GetAllObjectsByName(rName, rObjects);
        }
    }
}
//----------------------------------------------------------------------------
SEObject* SEShaderEffect::GetObjectByID(unsigned int uiID)
{
    SEObject* pFound = SEEffect::GetObjectByID(uiID);
    if( pFound )
    {
        return pFound;
    }

    for( int iPass = 0; iPass < m_iPassCount; iPass++ )
    {
        if( m_VShader[iPass] )
        {
            pFound = m_VShader[iPass]->GetObjectByID(uiID);
            if( pFound )
            {
                return pFound;
            }
        }

        if( m_GShader[iPass] )
        {
            pFound = m_GShader[iPass]->GetObjectByID(uiID);
            if( pFound )
            {
                return pFound;
            }
        }

        if( m_PShader[iPass] )
        {
            pFound = m_PShader[iPass]->GetObjectByID(uiID);
            if( pFound )
            {
                return pFound;
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// streaming
//----------------------------------------------------------------------------
void SEShaderEffect::Load(SEStream& rStream, SEStream::SELink* pLink)
{
    SE_BEGIN_DEBUG_STREAM_LOAD;

    SEEffect::Load(rStream, pLink);

    // native data
    rStream.Read(m_iPassCount);
    m_VShader.resize(m_iPassCount);
    m_GShader.resize(m_iPassCount);
    m_PShader.resize(m_iPassCount);

    // link data
    SEObject* pObject;
    for( int iPass = 0; iPass < m_iPassCount; iPass++ )
    {
        rStream.Read(pObject);  // m_VShader[iPass]
        pLink->Add(pObject);

        rStream.Read(pObject);  // m_GShader[iPass]
        pLink->Add(pObject);

        rStream.Read(pObject);  // m_PShader[iPass]
        pLink->Add(pObject);
    }

    int iCount;
    rStream.Read(iCount);
    m_RStateBlocks.resize(iCount);

    for( int i = 0; i < iCount; i++ )
    {
        rStream.Read(pObject);  // m_RStateBlocks[i]
        pLink->Add(pObject);
    }

    SE_END_DEBUG_STREAM_LOAD(SEShaderEffect);
}
//----------------------------------------------------------------------------
void SEShaderEffect::SELink(SEStream& rStream, SEStream::SELink* pLink)
{
    SEEffect::SELink(rStream, pLink);

    SEObject* pLinkID;
    for( int iPass = 0; iPass < m_iPassCount; iPass++ )
    {
        pLinkID = pLink->GetLinkID();
        m_VShader[iPass] = (SEVertexShader*)rStream.GetFromMap(pLinkID);

        pLinkID = pLink->GetLinkID();
        m_GShader[iPass] = (SEGeometryShader*)rStream.GetFromMap(pLinkID);

        pLinkID = pLink->GetLinkID();
        m_PShader[iPass] = (SEPixelShader*)rStream.GetFromMap(pLinkID);
    }

    int iCount = (int)m_RStateBlocks.size();
    for( int i = 0; i < iCount; i++ )
    {
        pLinkID = pLink->GetLinkID();
        m_RStateBlocks[i] = (SERenderStateBlock*)rStream.GetFromMap(pLinkID);
    }
}
//----------------------------------------------------------------------------
bool SEShaderEffect::Register(SEStream& rStream) const
{
    if( !SEEffect::Register(rStream) )
    {
        return false;
    }

    for( int iPass = 0; iPass < m_iPassCount; iPass++ )
    {
        if( m_VShader[iPass] )
        {
            m_VShader[iPass]->Register(rStream);
        }

        if( m_GShader[iPass] )
        {
            m_GShader[iPass]->Register(rStream);
        }

        if( m_PShader[iPass] )
        {
            m_PShader[iPass]->Register(rStream);
        }
    }

    for( int i = 0; i < (int)m_RStateBlocks.size(); i++ )
    {
        if( m_RStateBlocks[i] )
        {
            m_RStateBlocks[i]->Register(rStream);
        }
    }

    return true;
}
//----------------------------------------------------------------------------
void SEShaderEffect::Save(SEStream& rStream) const
{
    SE_BEGIN_DEBUG_STREAM_SAVE;

    SEEffect::Save(rStream);

    // native data
    rStream.Write(m_iPassCount);

    // link data
    for( int iPass = 0; iPass < m_iPassCount; iPass++ )
    {
        rStream.Write(m_VShader[iPass]);
        rStream.Write(m_GShader[iPass]);
        rStream.Write(m_PShader[iPass]);
    }

    int iCount = (int)m_RStateBlocks.size();
    rStream.Write(iCount);
    for( int i = 0; i < iCount; i++ )
    {
        rStream.Write(m_RStateBlocks[i]);
    }

    SE_END_DEBUG_STREAM_SAVE(SEShaderEffect);
}
//----------------------------------------------------------------------------
int SEShaderEffect::GetDiskUsed(const SEStreamVersion& rVersion) const
{
    return SEEffect::GetDiskUsed(rVersion) +
        sizeof(m_iPassCount) +
        m_iPassCount*sizeof(m_VShader[0]) +
        m_iPassCount*sizeof(m_GShader[0]) +
        m_iPassCount*sizeof(m_PShader[0]) +
        sizeof(int) +
        ((int)m_RStateBlocks.size())*sizeof(m_RStateBlocks[0]);
}
//----------------------------------------------------------------------------
SEStringTree* SEShaderEffect::SaveStrings(const char*)
{
    SEStringTree* pTree = SE_NEW SEStringTree;

    // strings
    pTree->Append(Format(&TYPE, GetName().c_str()));
    pTree->Append(Format("pass count =", m_iPassCount));

    // children
    pTree->Append(SEEffect::SaveStrings());

    if( m_iPassCount > 0 )
    {
        SEStringTree* pCTree = SE_NEW SEStringTree;
        pCTree->Append(Format("shaders"));
        for( int iPass = 0; iPass < m_iPassCount; iPass++ )
        {
            pCTree->Append(m_VShader[iPass]->SaveStrings());

            if( m_GShader[iPass] )
            {
                pCTree->Append(m_GShader[iPass]->SaveStrings());
            }

            pCTree->Append(m_PShader[iPass]->SaveStrings());
        }
        pTree->Append(pCTree);
    }

    int iCount = (int)m_RStateBlocks.size();
    if( iCount > 0 )
    {
        SEStringTree* pCTree = SE_NEW SEStringTree;
        pCTree->Append(Format("render state blocks"));
        for( int i = 0; i < iCount; i++ )
        {
            pCTree->Append(m_RStateBlocks[i]->SaveStrings());
        }
        pTree->Append(pCTree);
    }

    return pTree;
}
//----------------------------------------------------------------------------
