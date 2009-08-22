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
#include "SEOGLES1Resources.h"
#include "SEOGLES1FrameBuffer.h"
#include "SECamera.h"

using namespace Swing;

SE_IMPLEMENT_INITIALIZE(OGLES1FrameBuffer);

//SE_REGISTER_INITIALIZE(OGLES1FrameBuffer);

//----------------------------------------------------------------------------
void OGLES1FrameBuffer::Initialize()
{
    ms_aoCreator[Renderer::OPENGLES1] = &OGLES1FrameBuffer::Create;
    ms_aoDestroyer[Renderer::OPENGLES1] = &OGLES1FrameBuffer::Destroy;
}
//----------------------------------------------------------------------------
FrameBuffer* OGLES1FrameBuffer::Create(FormatType eFormat, DepthType eDepth,
    StencilType eStencil, BufferingType eBuffering,
    MultisamplingType eMultisampling, Renderer* pRenderer, int iTCount,
    Texture** apTargets)
{
    // 待实现.
    return 0;
}
//----------------------------------------------------------------------------
void OGLES1FrameBuffer::Destroy(FrameBuffer* pBuffer)
{
    ((OGLES1FrameBuffer*)pBuffer)->TerminateBuffer();
    SE_DELETE pBuffer;
}
//----------------------------------------------------------------------------
OGLES1FrameBuffer::OGLES1FrameBuffer(FormatType eFormat, DepthType eDepth,
    StencilType eStencil, BufferingType eBuffering,
    MultisamplingType eMultisampling, Renderer* pRenderer, int iTCount, 
    Texture** apTargets)
    :
    FrameBuffer(eFormat, eDepth, eStencil, eBuffering, eMultisampling, 
        pRenderer, iTCount, apTargets)
{
    // OpenGL ES1只支持一个render target.	
	SE_ASSERT( iTCount == 1 );
	
    m_TargetItems.resize(iTCount);
    m_pAttachments = SE_NEW GLenum[iTCount];
}
//----------------------------------------------------------------------------
OGLES1FrameBuffer::~OGLES1FrameBuffer()
{
    SE_DELETE[] m_pAttachments;
}
//----------------------------------------------------------------------------
bool OGLES1FrameBuffer::InitializeBuffer()
{
    // 待实现.
    return true;
}
//----------------------------------------------------------------------------
void OGLES1FrameBuffer::TerminateBuffer()
{
    // 待实现.
}
//----------------------------------------------------------------------------
void OGLES1FrameBuffer::Enable()
{
    // 待实现.
}
//----------------------------------------------------------------------------
void OGLES1FrameBuffer::Disable()
{
    // 待实现.
}
//----------------------------------------------------------------------------
void OGLES1FrameBuffer::CopyToTexture(int)
{
    // 待实现.
}
//----------------------------------------------------------------------------
