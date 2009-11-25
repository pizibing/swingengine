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
inline const char* WindowApplication::GetWindowTitle() const
{
    return m_acWindowTitle;
}
//----------------------------------------------------------------------------
inline int WindowApplication::GetXPosition() const
{
    return m_iXPosition;
}
//----------------------------------------------------------------------------
inline int WindowApplication::GetYPosition() const
{
    return m_iYPosition;
}
//----------------------------------------------------------------------------
inline int WindowApplication::GetWidth() const
{
    return m_iWidth;
}
//----------------------------------------------------------------------------
inline int WindowApplication::GetHeight() const
{
    return m_iHeight;
}
//----------------------------------------------------------------------------
inline void WindowApplication::SetRenderer(Renderer* pRenderer)
{
    m_pRenderer = pRenderer;
}
//----------------------------------------------------------------------------
inline Renderer* WindowApplication::GetRenderer()
{
    return m_pRenderer;
}
//----------------------------------------------------------------------------
inline void WindowApplication::SetAudioRenderer(AudioRenderer* pAudioRenderer)
{
    m_pAudioRenderer = pAudioRenderer;
}
//----------------------------------------------------------------------------
inline AudioRenderer* WindowApplication::GetAudioRenderer()
{
    return m_pAudioRenderer;
}
//----------------------------------------------------------------------------
inline void WindowApplication::SetWindowID(int iWindowID)
{
    m_iWindowID = iWindowID;
}
//----------------------------------------------------------------------------
inline int WindowApplication::GetWindowID() const
{
    return m_iWindowID;
}
//----------------------------------------------------------------------------
inline bool WindowApplication::OnPrecreate()
{
    // 由派生类负责实现
    return true;
}
//----------------------------------------------------------------------------
inline void WindowApplication::OnDisplay()
{
    // 由派生类负责实现
}
//----------------------------------------------------------------------------
inline void WindowApplication::OnIdle()
{
    // 由派生类负责实现
}
//----------------------------------------------------------------------------
inline bool WindowApplication::OnKeyDown(unsigned char, int, int)
{
    // 由派生类负责实现
    return false;
}
//----------------------------------------------------------------------------
inline bool WindowApplication::OnKeyUp(unsigned char, int, int)
{
    // 由派生类负责实现
    return false;
}
//----------------------------------------------------------------------------
inline bool WindowApplication::OnSpecialKeyDown(int, int, int)
{
    // 由派生类负责实现
    return false;
}
//----------------------------------------------------------------------------
inline bool WindowApplication::OnSpecialKeyUp(int, int, int)
{
    // 由派生类负责实现
    return false;
}
//----------------------------------------------------------------------------
inline bool WindowApplication::OnMouseClick(int, int, int, int, unsigned int)
{
    // 由派生类负责实现
    return false;
}
//----------------------------------------------------------------------------
inline bool WindowApplication::OnMotion(int, int, int, unsigned int)
{
    // 由派生类负责实现
    return false;
}
//----------------------------------------------------------------------------
inline bool WindowApplication::OnPassiveMotion(int, int)
{
    // 由派生类负责实现
    return false;
}
//----------------------------------------------------------------------------
