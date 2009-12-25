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

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Swing.Tools.SceneEditor.Framework;

namespace Swing.Tools.SceneEditor.GUI
{

//----------------------------------------------------------------------------
// Name:Scene editor main form class
// Description:
// Author:Sun Che
// Date:20091224
//----------------------------------------------------------------------------
/// <summary>
/// Scene editor main form class.
/// </summary>
public partial class MainForm : Form
{
    public MainForm()
    {
        InitializeComponent();
    }

    /// <summary>
    /// Application main entry point.
    /// </summary>
    [STAThread]
    static void Main()
    {
        ManagedFramework.Initialize();

        // Create main form.
        MainForm mainForm = new MainForm();

        // Create renderer.
        ManagedRenderer renderer = new ManagedRenderer(mainForm.Handle, 640, 
            480);
        renderer.SetClearColor(new ManagedColorRGBA(0.0f, 0.5f, 0.5f, 1.0f));
        mainForm.Renderer = renderer; 

        // Initialize shader program catalog.
        ManagedFramework.InitializeShaderProgramCatalog(renderer);

        // Create main camera.
        ManagedCamera mainCamera = new ManagedCamera();
        renderer.SetCamera(mainCamera);
        float fDMin = 1.0f;
        float fDMax = 1000.0f;
        float fRMax = 0.55f * fDMin;
        float fRMin = -fRMax;
        float fUMax = 0.4125f/*0.309375f*/ * fDMin;
        float fUMin = -fUMax;
        mainCamera.SetFrustum(fRMin, fRMax, fUMin, fUMax, fDMin, fDMax);
        ManagedVector3f tempCLoc = new ManagedVector3f(0.0f, 5.0f, -30.0f);
        ManagedVector3f tempCDir = new ManagedVector3f(0.0f, 0.0f, 1.0f);
        ManagedVector3f tempCUp = new ManagedVector3f(0.0f, 1.0f, 0.0f);
        ManagedVector3f tempCRight = ManagedVector3f.Cross(tempCUp, tempCDir);
        mainCamera.SetFrame(tempCLoc, tempCRight, tempCUp, tempCDir);
        mainForm.MainCamera = mainCamera;

        // Register idle handler.
        Application.Idle += new EventHandler(mainForm.OnIdle);

        // Start main loop.
        Application.Run(mainForm);

        // Release main camera.
        renderer.SetCamera(null);
        mainForm.MainCamera = null;
        mainCamera.Dispose();

        // Terminate shader program catalog.
        ManagedFramework.TerminateShaderProgramCatalog();

        // Release renderer.
        mainForm.Renderer = null;
        renderer.Dispose();

        ManagedFramework.Terminate();
    }

    /// <summary>
    /// Renderer access.
    /// </summary>
    public ManagedRenderer Renderer
    {
        get
        {
            return renderer;
        }
        set
        {
            renderer = value;
        }
    }

    /// <summary>
    /// Main camera access.
    /// </summary>
    public ManagedCamera MainCamera
    {
        get
        {
            return mainCamera;
        }
        set
        {
            mainCamera = value;
        }
    }

    private void OnIdle(object sender, EventArgs e)
    {
        if( this.Visible && this.WindowState != FormWindowState.Minimized 
            && Form.ActiveForm == this )
        {
            renderer.ClearBuffers();
            if( renderer.BeginScene() )
            {
                renderer.EndScene();
            }
            renderer.DisplayBackBuffer();
        }
    }

    private ManagedRenderer renderer;
    private ManagedCamera mainCamera;
}

}