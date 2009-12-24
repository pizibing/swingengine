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

            MainForm mainForm = new MainForm();
            ManagedRenderer renderer = new ManagedRenderer(mainForm.Handle, 640, 480);

            Application.Run(mainForm);

            renderer.Dispose();

            ManagedFramework.Terminate();
        }
    }
}