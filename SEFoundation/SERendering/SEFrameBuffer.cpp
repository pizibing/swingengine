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
#include "SEFrameBuffer.h"
#include "SERenderer.h"
#include "SETexture.h"
#include "SEImage.h"

using namespace Swing;

FrameBuffer::Creator FrameBuffer::ms_aoCreator[Renderer::MAX_RENDERER_TYPES];
FrameBuffer::Destroyer FrameBuffer::ms_aoDestroyer[Renderer::MAX_RENDERER_TYPES];

//----------------------------------------------------------------------------
FrameBuffer* FrameBuffer::Create(FormatType eFormat, DepthType eDepth,
    StencilType eStencil, BufferingType eBuffering,
    MultisamplingType eMultisampling, Renderer* pRenderer, int iTCount, 
    Texture** apTargets)
{
    Creator pCreator = ms_aoCreator[pRenderer->GetType()];

    SE_ASSERT( pCreator );

    int iMaxTargets = pRenderer->GetMaxRenderTargets();
    SE_ASSERT( iTCount >= 1 && iTCount <= iMaxTargets );
    if( iTCount < 1 || iTCount > iMaxTargets )
        return 0;

    if( pCreator )
    {
        return pCreator(eFormat, eDepth, eStencil, eBuffering, eMultisampling,
            pRenderer, iTCount, apTargets);
    }

    return 0;
}
//----------------------------------------------------------------------------
void FrameBuffer::Destroy(FrameBuffer* pBuffer)
{
    Renderer* pRenderer = pBuffer->GetRenderer();
    Destroyer pDestroyer = ms_aoDestroyer[pRenderer->GetType()];

    SE_ASSERT( pDestroyer );

    if( pDestroyer )
    {
        pDestroyer(pBuffer);
    }
}
//----------------------------------------------------------------------------
FrameBuffer::FrameBuffer(FormatType eFormat, DepthType eDepth,
    StencilType eStencil, BufferingType eBuffering,
    MultisamplingType eMultisampling, Renderer* pRenderer, int iTCount, 
    Texture** apTargets)
{
    m_eFormat = eFormat;
    m_eDepth = eDepth;
    m_eStencil = eStencil;
    m_eBuffering = eBuffering;
    m_eMultisampling = eMultisampling;
    m_pRenderer = pRenderer;
    m_iCount = iTCount;
    m_apTargets = apTargets;
}
//----------------------------------------------------------------------------
FrameBuffer::~FrameBuffer()
{
    SE_DELETE[] m_apTargets;
}
//----------------------------------------------------------------------------
