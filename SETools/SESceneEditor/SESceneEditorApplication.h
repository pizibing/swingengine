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
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

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

    void OnWindowRenderingMouseDown(Object^ thSender, MouseEventArgs^ thEvent);

    void OnWindowRenderingMouseEnter(Object^ thSender, EventArgs^ thEvent);

    void OnWindowRenderingMouseLeave(Object^ thSender, EventArgs^ thEvent);

    void OnWindowRenderingMouseMove(Object^ thSender, MouseEventArgs^ thEvent);

    void OnWindowRenderingMouseUp(Object^ thSender, MouseEventArgs^ thEvent);

    void OnWindowRenderingMouseClick(Object^ thSender, MouseEventArgs^ thEvent);

    void OnWindowRenderingMouseWheel(Object^ thSender, MouseEventArgs^ thEvent);

    #pragma endregion

private:
    void LoadFile(String^ thFileName);

    #pragma region Data Members

    // GUI stuff.
    MainForm^ m_thAppMainForm;

    // Renderer stuff.
    SERenderer* m_pMainRenderer;

    // Camera stuff.
    SECamera* m_pMainCamera;

    // Culler stuff.
    SECuller* m_pMainCuller;

    // Importers.
    SEColladaScene* m_pColladaScene;
    SEImageConverter* m_pImageConverter;

    SENode* m_pSceneRoot;
    SEWireframeState* m_pWireframe;

    // Main rendering window camera operation.
    Point m_LastMousePos;
    bool m_bFirstEntering;
    bool m_bAllowCameraTrn;
    bool m_bAllowCameraRot;
    bool m_bAllowCameraVHTrn;
    bool m_bAllowCameraTrackBall;
    float m_fOrthogonalFactor;
    float m_fCameraRotSpeed;
    float m_fCameraTrnSpeed;
    float m_fCameraVHTrnSpeed;

    #pragma endregion
};

}}}