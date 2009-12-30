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

#pragma once

#include "SEManagedCamera.h"
#include "SEManagedColorRGB.h"
#include "SEManagedColorRGBA.h"
#include "SEManagedCuller.h"

using namespace System;

namespace Swing{ namespace Tools{ namespace ManagedFramework{

//----------------------------------------------------------------------------
// Name:Managed renderer class
// Description:
// Author:Sun Che
// Date:20091219
//----------------------------------------------------------------------------
public ref class ManagedRenderer sealed
{
public:
	ManagedRenderer(IntPtr hWnd, int iWidth, int iHeight);
    ~ManagedRenderer(void);

    // Camera access.
    void SetCamera(ManagedCamera^ thCamera);
    ManagedCamera^ GetCamera(void);

    // Back buffer clear color.
    void SetClearColor(ManagedColorRGBA^ thClearColor);
    ManagedColorRGBA^ GetClearColor(void);

    // Pre-draw/Post-draw, DIRECTX9 API specific stuff.
    bool BeginScene(void);
    void EndScene(void);

    // Object rendering entry point.
    void DrawSceneFromCuller(ManagedCuller^ thCuller);

    // Full window buffer operation.
    void ClearBackBuffer(void);
    void ClearZBuffer(void);
    void ClearStencilBuffer(void);
    void ClearBuffers(void);
    void DisplayBackBuffer(void);

internal:
    [CLSCompliant(false)]
    Renderer* GetNativeRenderer(void);

private:
    Renderer* m_pRenderer;
    ManagedCamera^ m_thCamera;
};

}}}