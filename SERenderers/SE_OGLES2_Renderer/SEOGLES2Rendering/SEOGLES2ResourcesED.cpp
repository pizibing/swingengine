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

#include "SEOGLES2RendererPCH.h"
#include "SEOGLES2Renderer.h"
#include "SEOGLES2Resources.h"

using namespace Swing;

//----------------------------------------------------------------------------
// 资源开启与关闭.
//----------------------------------------------------------------------------
void OGLES2Renderer::SetVProgramRC(RendererConstant* pRC)
{
    RendererConstantID* pRCID = (RendererConstantID*)pRC->GetID();
    int iDataCount = pRC->GetDataCount();

    switch( iDataCount )
    {
    case 1:
        glUniform1fv(pRCID->ID, 1, pRC->GetData());
        break;
    case 2:
        glUniform2fv(pRCID->ID, 1, pRC->GetData());
        break;
    case 3:
        glUniform3fv(pRCID->ID, 1, pRC->GetData());
        break;
    case 4:
        glUniform4fv(pRCID->ID, 1, pRC->GetData());
        break;
    case 16:
        // The transpose argument must be false in OpenGL ES2.
        glUniformMatrix4fv(pRCID->ID, 1, GL_FALSE, pRC->GetData());
        break;
    }
}
//----------------------------------------------------------------------------
void OGLES2Renderer::SetVProgramUC(UserConstant* pUC)
{
    UserConstantID* pUCID = (UserConstantID*)pUC->GetID();
    int iDataCount = pUC->GetDataCount();

    switch( iDataCount )
    {
    case 1:
        glUniform1fv(pUCID->ID, 1, pUC->GetData());
        break;
    case 2:
        glUniform2fv(pUCID->ID, 1, pUC->GetData());
        break;
    case 3:
        glUniform3fv(pUCID->ID, 1, pUC->GetData());
        break;
    case 4:
        glUniform4fv(pUCID->ID, 1, pUC->GetData());
        break;
    case 16:
        // The transpose argument must be false in OpenGL ES2.
        glUniformMatrix4fv(pUCID->ID, 1, GL_FALSE, pUC->GetData());
        break;
    }
}
//----------------------------------------------------------------------------
void OGLES2Renderer::SetGProgramRC(RendererConstant*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void OGLES2Renderer::SetGProgramUC(UserConstant*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void OGLES2Renderer::SetPProgramRC(RendererConstant*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void OGLES2Renderer::SetPProgramUC(UserConstant* pUC)
{
    UserConstantID* pUCID = (UserConstantID*)pUC->GetID();
    int iDataCount = pUC->GetDataCount();

    switch( iDataCount )
    {
    case 1:
        glUniform1fv(pUCID->ID, 1, pUC->GetData());
        break;
    case 2:
        glUniform2fv(pUCID->ID, 1, pUC->GetData());
        break;
    case 3:
        glUniform3fv(pUCID->ID, 1, pUC->GetData());
        break;
    case 4:
        glUniform4fv(pUCID->ID, 1, pUC->GetData());
        break;
    case 16:
        // The transpose argument must be false in OpenGL ES2.
        glUniformMatrix4fv(pUCID->ID, 1, GL_FALSE, pUC->GetData());
        break;
    }
}
//----------------------------------------------------------------------------
void OGLES2Renderer::UpdateVProgramConstants(VertexProgram*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void OGLES2Renderer::UpdateGProgramConstants(GeometryProgram*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void OGLES2Renderer::UpdatePProgramConstants(PixelProgram*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnEnableVProgram(ResourceIdentifier* pID)
{
    VProgramID* pResource = (VProgramID*)pID;
    glUseProgram(pResource->Owner);
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnDisableVProgram(ResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnEnablePProgram(ResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnDisablePProgram(ResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnEnableTexture(ResourceIdentifier* pID)
{
    TextureID* pResource = (TextureID*)pID;

    SamplerInformation* pSI = m_apActiveSamplers[m_iCurrentSampler];
    SamplerInformation::Type eSType = pSI->GetType();
    int eTarget = ms_aeSamplerTypes[eSType];

    glActiveTexture(GL_TEXTURE0 + m_iCurrentSampler);
    glBindTexture(eTarget, pResource->ID);

    SamplerInformationID* pSIID = (SamplerInformationID*)pSI->GetID();
    glUniform1i(pSIID->ID, m_iCurrentSampler);
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnDisableTexture(ResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnEnableVBuffer(ResourceIdentifier* pID)
{
    // Bind当前vertex buffer.
    VBufferID* pResource = (VBufferID*)pID;
    glBindBuffer(GL_ARRAY_BUFFER, pResource->ID);

    const Attributes& rRAttr = pResource->IAttr;
    GLsizei iSize = (GLsizei)(sizeof(float)*rRAttr.GetChannelCount());
    const float* afData = 0;
    GLuint uiIndex = 0;

    if( rRAttr.HasPosition() )
    {
        glEnableVertexAttribArray(uiIndex);
        glVertexAttribPointer(uiIndex, rRAttr.GetPositionChannels(), GL_FLOAT,
            GL_FALSE, iSize, afData + rRAttr.GetPositionOffset());
        uiIndex++;
    }

    if( rRAttr.HasNormal() )
    {
        glEnableVertexAttribArray(uiIndex);
        glVertexAttribPointer(uiIndex, rRAttr.GetNormalChannels(), GL_FLOAT,
            GL_FALSE, iSize, afData + rRAttr.GetNormalOffset());
        uiIndex++;
    }

    if( rRAttr.HasColor(0) )
    {
        glEnableVertexAttribArray(uiIndex);
        glVertexAttribPointer(uiIndex, rRAttr.GetColorChannels(0), GL_FLOAT,
            GL_FALSE, iSize, afData + rRAttr.GetColorOffset(0));
        uiIndex++;
    }

    if( rRAttr.HasColor(1) )
    {
        glEnableVertexAttribArray(uiIndex);
        glVertexAttribPointer(uiIndex, rRAttr.GetColorChannels(1), GL_FLOAT,
            GL_FALSE, iSize, afData + rRAttr.GetColorOffset(1));
        uiIndex++;
    }

    for( int iUnit = 0; iUnit < rRAttr.GetMaxTCoords(); iUnit++ )
    {
        if( rRAttr.HasTCoord(iUnit) )
        {
            glActiveTexture(GL_TEXTURE0 + iUnit);
            glEnableVertexAttribArray(uiIndex);
            glVertexAttribPointer(uiIndex, rRAttr.GetTCoordChannels(iUnit),
                GL_FLOAT, GL_FALSE, iSize, afData + 
                rRAttr.GetTCoordOffset(iUnit));
            uiIndex++;
        }
    }
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnDisableVBuffer(ResourceIdentifier* pID)
{
    VBufferID* pResource = (VBufferID*)pID;
    const Attributes& rRAttr = pResource->IAttr;
    GLuint uiIndex = 0;

    // Unbind当前vertex buffer.
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if( rRAttr.HasPosition() )
    {
        glDisableVertexAttribArray(uiIndex++);
    }

    if( rRAttr.HasNormal() )
    {
        glDisableVertexAttribArray(uiIndex++);
    }

    if( rRAttr.HasColor(0) )
    {
        glDisableVertexAttribArray(uiIndex++);
    }

    if( rRAttr.HasColor(1) )
    {
        glDisableVertexAttribArray(uiIndex++);
    }

    for( int iUnit = 0; iUnit < rRAttr.GetMaxTCoords(); iUnit++ )
    {
        if( rRAttr.HasTCoord(iUnit) )
        {
            glActiveTexture(GL_TEXTURE0 + iUnit);
            glDisableVertexAttribArray(uiIndex++);
        }
    }
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnEnableIBuffer(ResourceIdentifier* pID)
{
    // Bind当前index buffer.
    IBufferID* pResource = (IBufferID*)pID;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pResource->ID);
}
//----------------------------------------------------------------------------
void OGLES2Renderer::OnDisableIBuffer(ResourceIdentifier*)
{
    // Unbind当前index buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
//----------------------------------------------------------------------------