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
void SEOpenGLRenderer::SetVProgramRC(SERendererConstant* pRC)
{
    cgSetParameterValuefr((CGparameter)pRC->GetID(), pRC->GetDataCount(), 
        pRC->GetData());
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::SetVProgramUC(SEUserConstant* pUC)
{
    cgSetParameterValuefr((CGparameter)pUC->GetID(), pUC->GetDataCount(), 
        pUC->GetData());
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::SetGProgramRC(SERendererConstant* pRC)
{
    cgSetParameterValuefr((CGparameter)pRC->GetID(), pRC->GetDataCount(), 
        pRC->GetData());
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::SetGProgramUC(SEUserConstant* pUC)
{
    cgSetParameterValuefr((CGparameter)pUC->GetID(), pUC->GetDataCount(), 
        pUC->GetData());
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::SetPProgramRC(SERendererConstant* pRC)
{
    cgSetParameterValuefr((CGparameter)pRC->GetID(), pRC->GetDataCount(), 
        pRC->GetData());
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::SetPProgramUC(SEUserConstant* pUC)
{
    cgSetParameterValuefr((CGparameter)pUC->GetID(), pUC->GetDataCount(), 
        pUC->GetData());
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::UpdateVProgramConstants(SEVertexProgram* pVProgram)
{
    SEProgramData* pData = (SEProgramData*)pVProgram->UserData;
    cgUpdateProgramParameters(pData->ID);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::UpdateGProgramConstants(SEGeometryProgram* pGProgram)
{
    SEProgramData* pData = (SEProgramData*)pGProgram->UserData;
    cgUpdateProgramParameters(pData->ID);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::UpdatePProgramConstants(SEPixelProgram* pPProgram)
{
    SEProgramData* pData = (SEProgramData*)pPProgram->UserData;
    cgUpdateProgramParameters(pData->ID);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::OnEnableVProgram(SEResourceIdentifier* pID)
{
    SEVProgramID* pResource = (SEVProgramID*)pID;

    cgGLEnableProfile(m_CgLatestVProfile);
    SE_GL_DEBUG_CG_PROGRAM;

    cgGLBindProgram(pResource->ID);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::OnDisableVProgram(SEResourceIdentifier*)
{
    cgGLDisableProfile(m_CgLatestVProfile);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::OnEnablePProgram(SEResourceIdentifier* pID)
{
    SEPProgramID* pResource = (SEPProgramID*)pID;

    cgGLEnableProfile(m_CgLatestPProfile);
    SE_GL_DEBUG_CG_PROGRAM;

    cgGLBindProgram(pResource->ID);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::OnDisablePProgram(SEResourceIdentifier*)
{
    cgGLDisableProfile(m_CgLatestPProfile);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::OnEnableTexture(SEResourceIdentifier* pID)
{
    SETextureID* pResource = (SETextureID*)pID;

    SESamplerInformation* pSI = m_apActiveSamplers[m_iCurrentSampler];
    CGparameter hParam = (CGparameter)pSI->GetID();

    cgGLSetTextureParameter(hParam, pResource->ID);
    SE_GL_DEBUG_CG_PROGRAM;

    cgGLEnableTextureParameter(hParam);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::OnDisableTexture(SEResourceIdentifier*)
{
    SESamplerInformation* pSI = m_apActiveSamplers[m_iCurrentSampler];
    CGparameter hParam = (CGparameter)pSI->GetID();

    cgGLDisableTextureParameter(hParam);
    SE_GL_DEBUG_CG_PROGRAM;
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::OnEnableVBuffer(SEResourceIdentifier* pID, 
    SEVertexProgram*)
{
    // Bind当前vertex buffer.
    SEVBufferID* pResource = (SEVBufferID*)pID;
    glBindBuffer(GL_ARRAY_BUFFER, pResource->ID);

    const SEAttributes& rRAttr = pResource->IAttr;
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
void SEOpenGLRenderer::OnDisableVBuffer(SEResourceIdentifier* pID, 
    SEVertexProgram*)
{
    SEVBufferID* pResource = (SEVBufferID*)pID;
    const SEAttributes& rRAttr = pResource->IAttr;

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
void SEOpenGLRenderer::OnEnableIBuffer(SEResourceIdentifier* pID)
{
    // Bind当前index buffer.
    SEIBufferID* pResource = (SEIBufferID*)pID;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pResource->ID);
}
//----------------------------------------------------------------------------
void SEOpenGLRenderer::OnDisableIBuffer(SEResourceIdentifier*)
{
    // Unbind当前index buffer.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
//----------------------------------------------------------------------------
