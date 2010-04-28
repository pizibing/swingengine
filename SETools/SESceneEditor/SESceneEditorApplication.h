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

using namespace System;

namespace Swing{ namespace Tools{ namespace SceneEditor{

ref class MainForm;

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20100427
//----------------------------------------------------------------------------
[CLSCompliant(false)]
public ref class SESceneEditorApplication sealed
{
public:
    SESceneEditorApplication(MainForm^ thForm);
    ~SESceneEditorApplication(void);

    #pragma region Properties

    property MainForm^ AppMainForm
    {
        MainForm^ get(void);
    }
    property SERenderer* MainRenderer
    {
        SERenderer* get(void);
    }
    property SECamera* MainCamera
    {
        SECamera* get(void);
    }
    property SECuller* MainCuller
    {
        SECuller* get(void);
    }

    #pragma endregion

    void OnIdle(Object^ thSender, EventArgs^ thEvent);

    #pragma region WinForm Event Callbacks

    void OnOpenToolStripMenuItemClick(Object^ thSender, EventArgs^ thEvent);

    #pragma endregion

private:
    #pragma region Data Members

    MainForm^ m_thAppMainForm;
    SERenderer* m_pMainRenderer;
    SECamera* m_pMainCamera;
    SECuller* m_pMainCuller;

    SENode* m_pSceneRoot;

    #pragma endregion
};

}}}