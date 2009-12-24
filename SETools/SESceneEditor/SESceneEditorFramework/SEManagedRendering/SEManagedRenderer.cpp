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

#include "SESceneEditorFrameworkPCH.h"
#include "SEManagedRenderer.h"

using namespace Swing;
using namespace Swing::Tools::SceneEditor::Framework;

//---------------------------------------------------------------------------
ManagedRenderer::ManagedRenderer(IntPtr hWnd, int iWidth, int iHeight)
{
    m_pRenderer = SE_NEW DX9Renderer((HWND)(int)hWnd, 
        FrameBuffer::FT_FORMAT_RGBA, 
        FrameBuffer::DT_DEPTH_24, 
        FrameBuffer::ST_STENCIL_8, 
        FrameBuffer::BT_BUFFERED_DOUBLE, 
        FrameBuffer::MT_SAMPLING_NONE, 
        iWidth, iHeight);
}
//---------------------------------------------------------------------------
ManagedRenderer::~ManagedRenderer()
{
    SE_DELETE m_pRenderer;
    m_pRenderer = 0;
}
//---------------------------------------------------------------------------
void ManagedRenderer::SetCamera(ManagedCamera^ thCamera)
{
    if( thCamera )
    {
        m_pRenderer->SetCamera(thCamera->GetNativeCamera());
    }
    else
    {
        m_pRenderer->SetCamera(0);
    }
}
//---------------------------------------------------------------------------
void ManagedRenderer::SetClearColor(ManagedColorRGBA^ thClearColor)
{
    if( !thClearColor )
    {
        throw gcnew ArgumentNullException("thClearColor");
    }

    ColorRGBA tempColor;
    thClearColor->ToColorRGBA(tempColor);
    m_pRenderer->SetClearColor(tempColor);
}
//---------------------------------------------------------------------------
ManagedColorRGBA^ ManagedRenderer::GetClearColor()
{
    ManagedColorRGBA^ thClearColor = gcnew ManagedColorRGBA;
    thClearColor->FromColorRGBA(m_pRenderer->GetClearColor());
    return thClearColor;
}
//---------------------------------------------------------------------------
Renderer* ManagedRenderer::GetNativeRenderer()
{
    return m_pRenderer;
}
//---------------------------------------------------------------------------