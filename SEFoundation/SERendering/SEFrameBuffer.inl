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

//----------------------------------------------------------------------------
inline FrameBuffer::FormatType FrameBuffer::GetFormatType() const
{
    return m_eFormat;
}
//----------------------------------------------------------------------------
inline FrameBuffer::DepthType FrameBuffer::GetDepthType() const
{
    return m_eDepth;
}
//----------------------------------------------------------------------------
inline FrameBuffer::StencilType FrameBuffer::GetStencilType() const
{
    return m_eStencil;
}
//----------------------------------------------------------------------------
inline FrameBuffer::BufferingType FrameBuffer::GetBufferingType() const
{
    return m_eBuffering;
}
//----------------------------------------------------------------------------
inline FrameBuffer::MultisamplingType FrameBuffer::GetMultisamplingType()
    const
{
    return m_eMultisampling;
}
//----------------------------------------------------------------------------
inline Renderer* FrameBuffer::GetRenderer()
{
    return m_pRenderer;
}
//----------------------------------------------------------------------------
inline int FrameBuffer::GetCount() const
{
    return m_iCount;
}
//----------------------------------------------------------------------------
inline Texture* FrameBuffer::GetTarget(int i)
{
    return m_apTargets[i];
}
//----------------------------------------------------------------------------
