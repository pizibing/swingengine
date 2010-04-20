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
void SEOGLES2Renderer::SetVProgramRC(SERendererConstant* pRC)
{
    SERendererConstantID* pRCID = (SERendererConstantID*)pRC->GetID();
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
void SEOGLES2Renderer::SetVProgramUC(SEUserConstant* pUC)
{
    SEUserConstantID* pUCID = (SEUserConstantID*)pUC->GetID();
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
void SEOGLES2Renderer::SetGProgramRC(SERendererConstant*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::SetGProgramUC(SEUserConstant*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::SetPProgramRC(SERendererConstant*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::SetPProgramUC(SEUserConstant* pUC)
{
    SEUserConstantID* pUCID = (SEUserConstantID*)pUC->GetID();
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
void SEOGLES2Renderer::UpdateVProgramConstants(SEVertexProgram*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::UpdateGProgramConstants(SEGeometryProgram*)
{
    // 不支持的基类功能.
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::UpdatePProgramConstants(SEPixelProgram*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::OnEnableVProgram(SEResourceIdentifier* pID)
{
    SEVProgramID* pResource = (SEVProgramID*)pID;
    glUseProgram(pResource->Owner);
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::OnDisableVProgram(SEResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::OnEnablePProgram(SEResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::OnDisablePProgram(SEResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::OnEnableTexture(SEResourceIdentifier* pID)
{
    SETextureID* pResource = (SETextureID*)pID;

    SESamplerInformation* pSI = m_apActiveSamplers[m_iCurrentSampler];
    SESamplerInformation::Type eSType = pSI->GetType();
    int eTarget = ms_aeSamplerTypes[eSType];

    glActiveTexture(GL_TEXTURE0 + m_iCurrentSampler);
    glBindTexture(eTarget, pResource->ID);

    SESamplerInformationID* pSIID = (SESamplerInformationID*)pSI->GetID();
    glUniform1i(pSIID->ID, m_iCurrentSampler);
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::OnDisableTexture(SEResourceIdentifier*)
{
    // 无需任何操作.
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::OnEnableVBuffer(SEResourceIdentifier* pID, 
    SEVertexProgram* pVProgram)
{
    // Bind当前vertex buffer.
    SEVBufferID* pResource = (SEVBufferID*)pID;
    glBindBuffer(GL_ARRAY_BUFFER, pResource->ID);

    const SEAttributes& rRAttr = pResource->IAttr;
    GLsizei iSize = (GLsizei)(sizeof(float)*rRAttr.GetChannelCount());
    const float* afData = 0;
    GLuint uiIndex = 0;
    SEProgramData* pVProgramData = (SEProgramData*)pVProgram->UserData;

    if( rRAttr.HasPosition() )
    {
        uiIndex = pVProgramData->GetPositionAttribID();
        glEnableVertexAttribArray(uiIndex);
        glVertexAttribPointer(uiIndex, rRAttr.GetPositionChannels(), GL_FLOAT,
            GL_FALSE, iSize, afData + rRAttr.GetPositionOffset());
    }

    if( rRAttr.HasNormal() )
    {
        uiIndex = pVProgramData->GetNormalAttribID();
        glEnableVertexAttribArray(uiIndex);
        glVertexAttribPointer(uiIndex, rRAttr.GetNormalChannels(), GL_FLOAT,
            GL_FALSE, iSize, afData + rRAttr.GetNormalOffset());
    }

    if( rRAttr.HasColor(0) )
    {
        uiIndex = pVProgramData->GetColorAttribID(0);
        glEnableVertexAttribArray(uiIndex);
        glVertexAttribPointer(uiIndex, rRAttr.GetColorChannels(0), GL_FLOAT,
            GL_FALSE, iSize, afData + rRAttr.GetColorOffset(0));
    }

    if( rRAttr.HasColor(1) )
    {
        uiIndex = pVProgramData->GetColorAttribID(1);
        glEnableVertexAttribArray(uiIndex);
        glVertexAttribPointer(uiIndex, rRAttr.GetColorChannels(1), GL_FLOAT,
            GL_FALSE, iSize, afData + rRAttr.GetColorOffset(1));
    }

    for( int iUnit = 0; iUnit < rRAttr.GetMaxTCoords(); iUnit++ )
    {
        if( rRAttr.HasTCoord(iUnit) )
        {
            uiIndex = pVProgramData->GetTCoordAttribID(iUnit);
            glActiveTexture(GL_TEXTURE0 + iUnit);
            glEnableVertexAttribArray(uiIndex);
            glVertexAttribPointer(uiIndex, rRAttr.GetTCoordChannels(iUnit),
                GL_FLOAT, GL_FALSE, iSize, afData + 
                rRAttr.GetTCoordOffset(iUnit));
        }
    }
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::OnDisableVBuffer(SEResourceIdentifier* pID, 
    SEVertexProgram* pVProgram)
{
    SEVBufferID* pResource = (SEVBufferID*)pID;
    const SEAttributes& rRAttr = pResource->IAttr;
    GLuint uiIndex = 0;
    SEProgramData* pVProgramData = (SEProgramData*)pVProgram->UserData;

    // Unbind当前vertex buffer.
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if( rRAttr.HasPosition() )
    {
        uiIndex = pVProgramData->GetPositionAttribID();
        glDisableVertexAttribArray(uiIndex);
    }

    if( rRAttr.HasNormal() )
    {
        uiIndex = pVProgramData->GetNormalAttribID();
        glDisableVertexAttribArray(uiIndex);
    }

    if( rRAttr.HasColor(0) )
    {
        uiIndex = pVProgramData->GetColorAttribID(0);
        glDisableVertexAttribArray(uiIndex);
    }

    if( rRAttr.HasColor(1) )
    {
        uiIndex = pVProgramData->GetColorAttribID(1);
        glDisableVertexAttribArray(uiIndex);
    }

    for( int iUnit = 0; iUnit < rRAttr.GetMaxTCoords(); iUnit++ )
    {
        if( rRAttr.HasTCoord(iUnit) )
        {
            uiIndex = pVProgramData->GetTCoordAttribID(iUnit);
            glActiveTexture(GL_TEXTURE0 + iUnit);
            glDisableVertexAttribArray(uiIndex);
        }
    }
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::OnEnableIBuffer(SEResourceIdentifier* pID)
{
    // Bind当前index buffer.
    SEIBufferID* pResource = (SEIBufferID*)pID;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pResource->ID);
}
//----------------------------------------------------------------------------
void SEOGLES2Renderer::OnDisableIBuffer(SEResourceIdentifier*)
{
    // Unbind当前index buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
//----------------------------------------------------------------------------