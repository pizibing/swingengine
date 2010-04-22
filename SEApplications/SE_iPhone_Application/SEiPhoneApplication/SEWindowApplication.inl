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
inline const char* SEWindowApplication::GetWindowTitle() const
{
    return m_acWindowTitle;
}
//----------------------------------------------------------------------------
inline int SEWindowApplication::GetXPosition() const
{
    return m_iXPosition;
}
//----------------------------------------------------------------------------
inline int SEWindowApplication::GetYPosition() const
{
    return m_iYPosition;
}
//----------------------------------------------------------------------------
inline int SEWindowApplication::GetWidth() const
{
    return m_iWidth;
}
//----------------------------------------------------------------------------
inline int SEWindowApplication::GetHeight() const
{
    return m_iHeight;
}
//----------------------------------------------------------------------------
inline void SEWindowApplication::SetRenderer(SERenderer* pRenderer)
{
    m_pRenderer = pRenderer;
}
//----------------------------------------------------------------------------
inline SERenderer* SEWindowApplication::GetRenderer()
{
    return m_pRenderer;
}
//----------------------------------------------------------------------------
inline void SEWindowApplication::SetAudioRenderer(SEAudioRenderer* 
    pAudioRenderer)
{
    m_pAudioRenderer = pAudioRenderer;
}
//----------------------------------------------------------------------------
inline SEAudioRenderer* SEWindowApplication::GetAudioRenderer()
{
    return m_pAudioRenderer;
}
//----------------------------------------------------------------------------
inline void SEWindowApplication::SetWindowID(int iWindowID)
{
    m_iWindowID = iWindowID;
}
//----------------------------------------------------------------------------
inline int SEWindowApplication::GetWindowID() const
{
    return m_iWindowID;
}
//----------------------------------------------------------------------------
inline bool SEWindowApplication::OnPrecreate()
{
    // 由派生类负责实现.
    return true;
}
//----------------------------------------------------------------------------
inline void SEWindowApplication::OnDisplay()
{
    // 由派生类负责实现.
}
//----------------------------------------------------------------------------
inline void SEWindowApplication::OnIdle()
{
    // 由派生类负责实现.
}
//----------------------------------------------------------------------------
inline void SEWindowApplication::OnTouchBegan(int iX, int iY)
{
    // 由派生类负责实现.
}
//----------------------------------------------------------------------------
inline void SEWindowApplication::OnTouchMoved(int iX, int iY)
{
    // 由派生类负责实现.
}
//----------------------------------------------------------------------------
inline void SEWindowApplication::OnTouchEnded(int iX, int iY)
{
    // 由派生类负责实现.
}
//----------------------------------------------------------------------------
inline void SEWindowApplication::OnTouchCancelled(int iX, int iY)
{
    // 由派生类负责实现.
}
//----------------------------------------------------------------------------
inline SEFrameBuffer::FormatType SEWindowApplication::GetFormat()
{
    return m_eFormat;
}
//----------------------------------------------------------------------------
inline SEFrameBuffer::DepthType SEWindowApplication::GetDepth()
{
    return m_eDepth;
}
//----------------------------------------------------------------------------
inline SEFrameBuffer::StencilType SEWindowApplication::GetStencil()
{
    return m_eStencil;
}
//----------------------------------------------------------------------------
inline SEFrameBuffer::BufferingType SEWindowApplication::GetBuffering()
{
    return m_eBuffering;
}
//----------------------------------------------------------------------------
inline SEFrameBuffer::MultisamplingType SEWindowApplication::GetMultisampling()
{
    return m_eMultisampling;
}
//----------------------------------------------------------------------------
