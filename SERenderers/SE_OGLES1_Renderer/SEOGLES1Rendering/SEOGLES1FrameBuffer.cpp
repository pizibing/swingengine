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

SE_IMPLEMENT_INITIALIZE(SEOGLES1FrameBuffer);

//SE_REGISTER_INITIALIZE(SEOGLES1FrameBuffer);

//----------------------------------------------------------------------------
void SEOGLES1FrameBuffer::Initialize()
{
    ms_aoCreator[SERenderer::OPENGLES1] = &SEOGLES1FrameBuffer::Create;
    ms_aoDestroyer[SERenderer::OPENGLES1] = &SEOGLES1FrameBuffer::Destroy;
}
//----------------------------------------------------------------------------
SEFrameBuffer* SEOGLES1FrameBuffer::Create(FormatType eFormat, DepthType 
    eDepth, StencilType eStencil, BufferingType eBuffering, MultisamplingType 
    eMultisampling, SERenderer* pRenderer, int iTCount,
    SETexture** apTargets)
{
    // 待实现.
    return 0;
}
//----------------------------------------------------------------------------
void SEOGLES1FrameBuffer::Destroy(SEFrameBuffer* pBuffer)
{
    ((SEOGLES1FrameBuffer*)pBuffer)->TerminateBuffer();
    SE_DELETE pBuffer;
}
//----------------------------------------------------------------------------
SEOGLES1FrameBuffer::SEOGLES1FrameBuffer(FormatType eFormat, DepthType eDepth,
    StencilType eStencil, BufferingType eBuffering,
    MultisamplingType eMultisampling, SERenderer* pRenderer, int iTCount, 
    SETexture** apTargets)
    :
    SEFrameBuffer(eFormat, eDepth, eStencil, eBuffering, eMultisampling, 
        pRenderer, iTCount, apTargets)
{
    // OpenGL ES1只支持一个render target.	
	SE_ASSERT( iTCount == 1 );
	
    m_TargetItems.resize(iTCount);
    m_pAttachments = SE_NEW GLenum[iTCount];
}
//----------------------------------------------------------------------------
SEOGLES1FrameBuffer::~SEOGLES1FrameBuffer()
{
    SE_DELETE[] m_pAttachments;
}
//----------------------------------------------------------------------------
bool SEOGLES1FrameBuffer::InitializeBuffer()
{
    // 待实现.
    return true;
}
//----------------------------------------------------------------------------
void SEOGLES1FrameBuffer::TerminateBuffer()
{
    // 待实现.
}
//----------------------------------------------------------------------------
void SEOGLES1FrameBuffer::Enable()
{
    // 待实现.
}
//----------------------------------------------------------------------------
void SEOGLES1FrameBuffer::Disable()
{
    // 待实现.
}
//----------------------------------------------------------------------------
void SEOGLES1FrameBuffer::CopyToTexture(int)
{
    // 待实现.
}
//----------------------------------------------------------------------------
