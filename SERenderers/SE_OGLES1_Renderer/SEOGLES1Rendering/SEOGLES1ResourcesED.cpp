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
#include "SEOGLES1Resources.h"

using namespace Swing;

//----------------------------------------------------------------------------
// 资源开启与关闭.
//----------------------------------------------------------------------------
void OGLES1Renderer::SetVProgramRC(RendererConstant*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void OGLES1Renderer::SetVProgramUC(UserConstant*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void OGLES1Renderer::SetGProgramRC(RendererConstant*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void OGLES1Renderer::SetGProgramUC(UserConstant*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void OGLES1Renderer::SetPProgramRC(RendererConstant*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void OGLES1Renderer::SetPProgramUC(UserConstant*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void OGLES1Renderer::UpdateVProgramConstants(VertexProgram*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void OGLES1Renderer::UpdateGProgramConstants(GeometryProgram*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void OGLES1Renderer::UpdatePProgramConstants(PixelProgram*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void OGLES1Renderer::OnEnableVProgram(ResourceIdentifier*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void OGLES1Renderer::OnDisableVProgram(ResourceIdentifier*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void OGLES1Renderer::OnEnablePProgram(ResourceIdentifier*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void OGLES1Renderer::OnDisablePProgram(ResourceIdentifier*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void OGLES1Renderer::OnEnableTexture(ResourceIdentifier* pID)
{
    TextureID* pResource = (TextureID*)pID;

    // 待实现.
    // 目前只支持2D texture.
    SamplerInformation::Type eSType = SamplerInformation::SAMPLER_2D;
    int iTextureUnit = m_iCurrentSampler;
    int eTarget = ms_aeSamplerTypes[eSType];

    glClientActiveTexture(GL_TEXTURE0 + iTextureUnit);
    glActiveTexture(GL_TEXTURE0 + iTextureUnit);
    glBindTexture(eTarget, pResource->ID);
    glEnable(eTarget);
}
//----------------------------------------------------------------------------
void OGLES1Renderer::OnDisableTexture(ResourceIdentifier* pID)
{
    // 待实现.
    // 目前只支持2D texture.
    SamplerInformation::Type eSType = SamplerInformation::SAMPLER_2D;
    int eTarget = ms_aeSamplerTypes[eSType];
    glBindTexture(eTarget, 0);
    glDisable(eTarget);
}
//----------------------------------------------------------------------------
void OGLES1Renderer::OnEnableVBuffer(ResourceIdentifier* pID, VertexProgram*)
{
    // Bind当前vertex buffer.
    VBufferID* pResource = (VBufferID*)pID;
    glBindBuffer(GL_ARRAY_BUFFER, pResource->ID);

    const Attributes& rRAttr = pResource->IAttr;
    GLsizei iSize = (GLsizei)(sizeof(float)*rRAttr.GetChannelCount());
    const float* afData = 0;

    if( rRAttr.HasPosition() )
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(rRAttr.GetPositionChannels(), GL_FLOAT, iSize,
            afData + rRAttr.GetPositionOffset());
    }

    if( rRAttr.HasNormal() )
    {
        // OpenGL不允许用户指定normal vector的分量个数.
        // 因此,rRAttr.GetNChannels函数返回的分量个数应该为3.
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, iSize, afData + rRAttr.GetNormalOffset());
    }

    // OpenGL ES1只支持一组顶点颜色,因此不设置其他color channel.
    if( rRAttr.HasColor(0) )
    {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(rRAttr.GetColorChannels(0), GL_FLOAT, iSize,
            afData + rRAttr.GetColorOffset(0));
    }

    for( int iUnit = 0; iUnit < rRAttr.GetMaxTCoords(); iUnit++ )
    {
        if( rRAttr.HasTCoord(iUnit) )
        {
            glClientActiveTexture(GL_TEXTURE0 + iUnit);
            glActiveTexture(GL_TEXTURE0 + iUnit);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY); 
            glTexCoordPointer(rRAttr.GetTCoordChannels(iUnit), GL_FLOAT, iSize,
                afData + rRAttr.GetTCoordOffset(iUnit));
        }
    }
}
//----------------------------------------------------------------------------
void OGLES1Renderer::OnDisableVBuffer(ResourceIdentifier* pID, VertexProgram*)
{
    VBufferID* pResource = (VBufferID*)pID;
    const Attributes& rRAttr = pResource->IAttr;

    // Unbind当前vertex buffer.
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if( rRAttr.HasPosition() )
    {
        glDisableClientState(GL_VERTEX_ARRAY);
    }

    if( rRAttr.HasNormal() )
    {
        glDisableClientState(GL_NORMAL_ARRAY);
    }

    if( rRAttr.HasColor(0) )
    {
        glDisableClientState(GL_COLOR_ARRAY);
    }

    for( int iUnit = 0; iUnit < rRAttr.GetMaxTCoords(); iUnit++ )
    {
        if( rRAttr.HasTCoord(iUnit) )
        {
            glClientActiveTexture(GL_TEXTURE0 + iUnit);
            glActiveTexture(GL_TEXTURE0 + iUnit);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
    }
}
//----------------------------------------------------------------------------
void OGLES1Renderer::OnEnableIBuffer(ResourceIdentifier* pID)
{
    // Bind当前index buffer.
    IBufferID* pResource = (IBufferID*)pID;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pResource->ID);
}
//----------------------------------------------------------------------------
void OGLES1Renderer::OnDisableIBuffer(ResourceIdentifier*)
{
    // Unbind当前index buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
//----------------------------------------------------------------------------
void OGLES1Renderer::EnableLightingFixed()
{
    glEnable(GL_LIGHTING);

    // 待实现.
    // 是否有必要频繁设置以下渲染状态?这将降低性能.

    // 要求法线在变换过程中始终保持单位长度.
    glEnable(GL_NORMALIZE);
    // 平滑着色.
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf(m_ViewMatrix);
}
//----------------------------------------------------------------------------
void OGLES1Renderer::DisableLightingFixed()
{
    glDisable(GL_LIGHTING);
}
//----------------------------------------------------------------------------
