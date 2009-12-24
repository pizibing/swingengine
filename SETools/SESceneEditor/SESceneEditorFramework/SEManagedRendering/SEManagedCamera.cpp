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
#include "SEManagedCamera.h"

using namespace Swing;
using namespace Swing::Tools::SceneEditor::Framework;

//---------------------------------------------------------------------------
ManagedCamera::ManagedCamera()
{
    // Create a smart pointer which will point to the native camera.
    m_pspCamera = SE_NEW CameraPtr;

    // Create the native camera.
    (*m_pspCamera) = SE_NEW Camera;
}
//---------------------------------------------------------------------------
ManagedCamera::~ManagedCamera()
{
    SE_DELETE m_pspCamera;
    m_pspCamera = 0;
}
//---------------------------------------------------------------------------
Camera* ManagedCamera::GetNativeCamera()
{
    return (Camera*)(*m_pspCamera);
}
//---------------------------------------------------------------------------
void ManagedCamera::SetFrustum(float fRMin, float fRMax, float fUMin, 
    float fUMax, float fDMin, float fDMax)
{
    (*m_pspCamera)->SetFrustum(fRMin, fRMax, fUMin, fUMax, fDMin, fDMax);
}
//---------------------------------------------------------------------------
void ManagedCamera::GetFrustum(float& rRMin, float& rRMax, float& rUMin, 
    float& rUMax, float& rDMin, float& rDMax)
{
    (*m_pspCamera)->GetFrustum(rRMin, rRMax, rUMin, rUMax, rDMin, rDMax);
}
//---------------------------------------------------------------------------