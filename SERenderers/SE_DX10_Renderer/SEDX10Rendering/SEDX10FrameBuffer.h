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

#ifndef Swing_DX10FrameBuffer_H
#define Swing_DX10FrameBuffer_H

#include "SEDX10Renderer.h"
#include "SEDX10Utility.h"
#include "SEMain.h"
#include "SEFrameBuffer.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20090519
//----------------------------------------------------------------------------
class SE_RENDERER_API SEDX10FrameBuffer : public SEFrameBuffer
{
    SE_DECLARE_INITIALIZE;

public:
    SEDX10FrameBuffer(FormatType eFormat, DepthType eDepth,
        StencilType eStencil, BufferingType eBuffering,
        MultisamplingType eMultisampling, SERenderer* pRenderer,
        int iTCount, SETexture** apTargets);

    virtual ~SEDX10FrameBuffer(void);

    bool InitializeBuffer(void);
    void TerminateBuffer(void);

    virtual void Enable(void);
    virtual void Disable(void);
    virtual void CopyToTexture(int i);

protected:
    class TargetItem
    {
    public:
        TargetItem(void){ memset(this, 0, sizeof(TargetItem)); }
        ~TargetItem(void){}

        //IDirect3DTexture9* TargetID;
        //IDirect3DSurface9* TextureSurface;
        //IDirect3DSurface9* SaveTextureSurface;
        //IDirect3DSurface9* DepthStencilSurface;
        //IDirect3DSurface9* SaveDepthStencilSurface;

        //IDirect3DTexture9* CopyTexture;
        //IDirect3DSurface9* CopySurface;
    };

    std::vector<TargetItem> m_TargetItems;

    //ID3DXRenderToSurface* m_pRenderToTexture;

    // ¹¤³§º¯Êý
    static SEFrameBuffer* Create(FormatType eFormat, DepthType eDepth,
        StencilType eStencil, BufferingType eBuffering,
        MultisamplingType eMultisampling, SERenderer* pRenderer,
        int iTCount, SETexture** apTargets);

    static void Destroy(SEFrameBuffer* pBuffer);
};

}

#endif
