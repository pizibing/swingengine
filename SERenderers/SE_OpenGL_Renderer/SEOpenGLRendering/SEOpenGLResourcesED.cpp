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

#include "SEOpenGLRendererPCH.h"
#include "SEOpenGLRenderer.h"
#include "SEOpenGLResources.h"

using namespace Swing;

//----------------------------------------------------------------------------
// 资源开启与关闭.
//----------------------------------------------------------------------------
void OpenGLRenderer::SetVProgramRC(RendererConstant* pRC)
{
    cgSetParameterValuefr((CGparameter)pRC->GetID(), pRC->GetDataCount(), 
        pRC->GetData());
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::SetVProgramUC(UserConstant* pUC)
{
    cgSetParameterValuefr((CGparameter)pUC->GetID(), pUC->GetDataCount(), 
        pUC->GetData());
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::SetGProgramRC(RendererConstant* pRC)
{
    cgSetParameterValuefr((CGparameter)pRC->GetID(), pRC->GetDataCount(), 
        pRC->GetData());
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::SetGProgramUC(UserConstant* pUC)
{
    cgSetParameterValuefr((CGparameter)pUC->GetID(), pUC->GetDataCount(), 
        pUC->GetData());
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::SetPProgramRC(RendererConstant* pRC)
{
    cgSetParameterValuefr((CGparameter)pRC->GetID(), pRC->GetDataCount(), 
        pRC->GetData());
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::SetPProgramUC(UserConstant* pUC)
{
    cgSetParameterValuefr((CGparameter)pUC->GetID(), pUC->GetDataCount(), 
        pUC->GetData());
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::UpdateVProgramConstants(VertexProgram* pVProgram)
{
    ProgramData* pData = (ProgramData*)pVProgram->UserData;
    cgUpdateProgramParameters(pData->ID);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::UpdateGProgramConstants(GeometryProgram* pGProgram)
{
    ProgramData* pData = (ProgramData*)pGProgram->UserData;
    cgUpdateProgramParameters(pData->ID);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::UpdatePProgramConstants(PixelProgram* pPProgram)
{
    ProgramData* pData = (ProgramData*)pPProgram->UserData;
    cgUpdateProgramParameters(pData->ID);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::OnEnableVProgram(ResourceIdentifier* pID)
{
    VProgramID* pResource = (VProgramID*)pID;

    cgGLEnableProfile(m_CgLatestVProfile);
    SE_GL_DEBUG_CG_PROGRAM;

    cgGLBindProgram(pResource->ID);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::OnDisableVProgram(ResourceIdentifier*)
{
    cgGLDisableProfile(m_CgLatestVProfile);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::OnEnablePProgram(ResourceIdentifier* pID)
{
    PProgramID* pResource = (PProgramID*)pID;

    cgGLEnableProfile(m_CgLatestPProfile);
    SE_GL_DEBUG_CG_PROGRAM;

    cgGLBindProgram(pResource->ID);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::OnDisablePProgram(ResourceIdentifier*)
{
    cgGLDisableProfile(m_CgLatestPProfile);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::OnEnableTexture(ResourceIdentifier* pID)
{
    TextureID* pResource = (TextureID*)pID;

    SamplerInformation* pSI = m_apActiveSamplers[m_iCurrentSampler];
    CGparameter hParam = (CGparameter)pSI->GetID();

    cgGLSetTextureParameter(hParam, pResource->ID);
    SE_GL_DEBUG_CG_PROGRAM;

    cgGLEnableTextureParameter(hParam);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::OnDisableTexture(ResourceIdentifier*)
{
    SamplerInformation* pSI = m_apActiveSamplers[m_iCurrentSampler];
    CGparameter hParam = (CGparameter)pSI->GetID();

    cgGLDisableTextureParameter(hParam);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void OpenGLRenderer::OnEnableVBuffer(ResourceIdentifier* pID)
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

    if( rRAttr.HasColor(0) )
    {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(rRAttr.GetColorChannels(0), GL_FLOAT, iSize,
            afData + rRAttr.GetColorOffset(0));
    }

    if( rRAttr.HasColor(1) )
    {
        glEnableClientState(GL_SECONDARY_COLOR_ARRAY);
        glSecondaryColorPointer(rRAttr.GetColorChannels(1), GL_FLOAT, iSize,
            afData + rRAttr.GetColorOffset(1));
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
void OpenGLRenderer::OnDisableVBuffer(ResourceIdentifier* pID)
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

    if( rRAttr.HasColor(1) )
    {
        glDisableClientState(GL_SECONDARY_COLOR_ARRAY);
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
void OpenGLRenderer::OnEnableIBuffer(ResourceIdentifier* pID)
{
    // Bind当前index buffer.
    IBufferID* pResource = (IBufferID*)pID;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pResource->ID);
}
//----------------------------------------------------------------------------
void OpenGLRenderer::OnDisableIBuffer(ResourceIdentifier*)
{
    // Unbind当前index buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
//----------------------------------------------------------------------------
