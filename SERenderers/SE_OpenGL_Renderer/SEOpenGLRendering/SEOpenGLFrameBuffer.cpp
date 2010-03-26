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
#include "SEOpenGLResources.h"
#include "SEOpenGLFrameBuffer.h"
#include "SECamera.h"

using namespace Swing;

SE_IMPLEMENT_INITIALIZE(OpenGLFrameBuffer);

//SE_REGISTER_INITIALIZE(OpenGLFrameBuffer);

//----------------------------------------------------------------------------
void OpenGLFrameBuffer::Initialize()
{
    ms_aoCreator[Renderer::OPENGL] = &OpenGLFrameBuffer::Create;
    ms_aoDestroyer[Renderer::OPENGL] = &OpenGLFrameBuffer::Destroy;
}
//----------------------------------------------------------------------------
FrameBuffer* OpenGLFrameBuffer::Create(FormatType eFormat, DepthType eDepth,
    StencilType eStencil, BufferingType eBuffering,
    MultisamplingType eMultisampling, Renderer* pRenderer, int iTCount,
    Texture** apTargets)
{
    // 检查所需extensions.
    if( !SE_ExistsGlExtFrameBufferObject )
    {
        return 0;
    }

    if( pRenderer && apTargets )
    {
        OpenGLFrameBuffer* pBuffer = SE_NEW OpenGLFrameBuffer(eFormat,
            eDepth, eStencil, eBuffering, eMultisampling, pRenderer, iTCount,
            apTargets);

        if( pBuffer->InitializeBuffer() )
        {
            return pBuffer;
        }

        SE_DELETE pBuffer;
    }

    return 0;
}
//----------------------------------------------------------------------------
void OpenGLFrameBuffer::Destroy(FrameBuffer* pBuffer)
{
    ((OpenGLFrameBuffer*)pBuffer)->TerminateBuffer();
    SE_DELETE pBuffer;
}
//----------------------------------------------------------------------------
OpenGLFrameBuffer::OpenGLFrameBuffer(FormatType eFormat, DepthType eDepth,
    StencilType eStencil, BufferingType eBuffering,
    MultisamplingType eMultisampling, Renderer* pRenderer, int iTCount, 
    Texture** apTargets)
    :
    FrameBuffer(eFormat, eDepth, eStencil, eBuffering, eMultisampling, 
        pRenderer, iTCount, apTargets)
{
    m_TargetItems.resize(iTCount);
    m_pAttachments = SE_NEW GLenum[iTCount];
}
//----------------------------------------------------------------------------
OpenGLFrameBuffer::~OpenGLFrameBuffer()
{
    SE_DELETE[] m_pAttachments;
}
//----------------------------------------------------------------------------
bool OpenGLFrameBuffer::InitializeBuffer()
{
    // 支持嵌套调用FBO,暂存当前正在使用的FBO,稍后用于恢复.
    glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, (GLint*)&m_uiSaveFrameBufferID);

    // 首先创建一个FBO对象.
    glGenFramebuffersEXT(1, &m_uiFrameBufferID);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_uiFrameBufferID);

    // 为FBO对象创建depth buffer.
    glGenRenderbuffersEXT(1, &m_uiDepthBufferID);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_uiDepthBufferID);
    Image* pImage = m_apTargets[0]->GetImage();
    SE_ASSERT( pImage );
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, 
        pImage->GetBound(0), pImage->GetBound(1));
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, 
        GL_RENDERBUFFER_EXT, m_uiDepthBufferID);

    // 为FBO对象关联纹理.
	for( int i = 0; i < m_iCount; i++ )
    {
        Image* pImage = m_apTargets[i]->GetImage();
        if( pImage->IsCubeImage() )
        {
            // 待实现.
            // 尚未支持cube map.
            TerminateBuffer();
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_uiSaveFrameBufferID);
            return false;
        }

        // 确保用作buffer的纹理已经装载入显存.
        ResourceIdentifier* pID = m_apTargets[i]->GetIdentifier(m_pRenderer);
        SE_ASSERT( pID );
        TextureID* pResource = (TextureID*)pID;
        m_TargetItems[i].TargetID = pResource->ID;
        glBindTexture(GL_TEXTURE_2D, m_TargetItems[i].TargetID);

        if( !pImage->IsDepthImage() )
        {
            m_pAttachments[i] = GL_COLOR_ATTACHMENT0_EXT + i;
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, m_pAttachments[i],
                GL_TEXTURE_2D, m_TargetItems[i].TargetID, 0);
        }
        else
        {
            m_pAttachments[i] = GL_DEPTH_ATTACHMENT_EXT;
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, m_pAttachments[i],
                GL_TEXTURE_2D, m_TargetItems[i].TargetID, 0);
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);
        }

        GLenum uiStatus = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
        int iStopHere;
        switch( uiStatus )
        {
        case GL_FRAMEBUFFER_COMPLETE_EXT:
            iStopHere = 0;
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENTS_EXT:
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:

            TerminateBuffer();
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_uiSaveFrameBufferID);
            return false;
        }
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_uiSaveFrameBufferID);

    return true;
}
//----------------------------------------------------------------------------
void OpenGLFrameBuffer::TerminateBuffer()
{
    glDeleteFramebuffersEXT(1, &m_uiFrameBufferID);
    glDeleteRenderbuffersEXT(1, &m_uiDepthBufferID);
}
//----------------------------------------------------------------------------
void OpenGLFrameBuffer::Enable()
{
    OpenGLRenderer* pRenderer = (OpenGLRenderer*)m_pRenderer;

    glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, (GLint*)&m_uiSaveFrameBufferID);

    glBindTexture(GL_TEXTURE_2D, 0); // 确保即将使用的纹理不是已绑定的targets
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_uiFrameBufferID);
    glDrawBuffers(m_iCount, m_pAttachments);

    pRenderer->OnFrustumChange();

    if( pRenderer->m_pCamera->IsPerspective() )
    {
        pRenderer->m_ProjectionMatrix[1][1] = 
            -pRenderer->m_ProjectionMatrix[1][1];
        pRenderer->m_ProjectionMatrix[2][1] = 
            -pRenderer->m_ProjectionMatrix[2][1];
    }
    else
    {
        pRenderer->m_ProjectionMatrix[1][1] = 
            -pRenderer->m_ProjectionMatrix[1][1];
        pRenderer->m_ProjectionMatrix[3][1] = 
            -pRenderer->m_ProjectionMatrix[3][1];
    }

    // 顶层使用FBO时要翻转cull state,嵌套中的FBO则不能再次翻转.
    if( m_uiSaveFrameBufferID == 0 )
    {
        pRenderer->m_bReverseCullFace = !pRenderer->m_bReverseCullFace;
        CullState* pCState = pRenderer->GetCullState();
        pRenderer->SetCullState(pCState);
    }

    Image* pImage = m_apTargets[0]->GetImage();
    glViewport(0, 0, pImage->GetBound(0), pImage->GetBound(1));
}
//----------------------------------------------------------------------------
void OpenGLFrameBuffer::Disable()
{
    OpenGLRenderer* pRenderer = (OpenGLRenderer*)m_pRenderer;

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_uiSaveFrameBufferID);

    pRenderer->OnViewportChange();
    pRenderer->OnFrustumChange();

    if( m_uiSaveFrameBufferID == 0 )
    {
        // 结束顶层FBO时,恢复正常的view matrix和cull state.
        pRenderer->OnFrameChange();

        pRenderer->m_bReverseCullFace = !pRenderer->m_bReverseCullFace;
        CullState* pCState = pRenderer->GetCullState();
        pRenderer->SetCullState(pCState);
    }
    else
    {
        // 结束当前嵌套的FBO时,需要把相关matrix恢复成之前的FBO所需要的形式.
        if( pRenderer->m_pCamera->IsPerspective() )
        {
            pRenderer->m_ProjectionMatrix[1][1] = 
                -pRenderer->m_ProjectionMatrix[1][1];
            pRenderer->m_ProjectionMatrix[2][1] = 
                -pRenderer->m_ProjectionMatrix[2][1];
        }
        else
        {
            pRenderer->m_ProjectionMatrix[1][1] = 
                -pRenderer->m_ProjectionMatrix[1][1];
            pRenderer->m_ProjectionMatrix[3][1] = 
                -pRenderer->m_ProjectionMatrix[3][1];
        }
    }
}
//----------------------------------------------------------------------------
void OpenGLFrameBuffer::CopyToTexture(int i)
{
    SE_ASSERT( i >= 0 && i < m_iCount );
    i = i < 0 ? 0 : (i >= m_iCount ? m_iCount - 1 : i );

    Image* pImage = m_apTargets[i]->GetImage();
    unsigned char* aucData = pImage->GetData();
    int iBound0 = pImage->GetBound(0);
    int iBound1 = pImage->GetBound(1);

    switch( m_eFormat )
    {
    case FT_FORMAT_RGB:
        glReadBuffer(GL_COLOR_ATTACHMENT0_EXT + i);
        glReadPixels(0, 0, iBound0, iBound1, GL_RGB, GL_UNSIGNED_BYTE, aucData);
        break;

    case FT_FORMAT_RGBA:
        glReadBuffer(GL_COLOR_ATTACHMENT0_EXT + i);
        glReadPixels(0, 0, iBound0, iBound1, GL_RGBA, GL_UNSIGNED_BYTE, 
            aucData);
        break;

    case FT_FORMAT_DEPTH:
        glReadBuffer(GL_DEPTH_ATTACHMENT_EXT);
        glReadPixels(0, 0, iBound0, iBound1, GL_DEPTH_COMPONENT, GL_FLOAT,
            aucData);
        break;

    default:
        SE_ASSERT( false );
        break;
    }
}
//----------------------------------------------------------------------------
