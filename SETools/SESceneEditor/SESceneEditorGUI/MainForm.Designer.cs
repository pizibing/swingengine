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

namespace Swing.Tools.SceneEditor.GUI
{

partial class MainForm
{
    /// <summary>
    /// 必需的设计器变量。
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// 清理所有正在使用的资源。
    /// </summary>
    /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
    protected override void Dispose(bool disposing)
    {
        if (disposing && (components != null))
        {
            components.Dispose();
        }
        base.Dispose(disposing);
    }

    #region Windows 窗体设计器生成的代码

    /// <summary>
    /// 设计器支持所需的方法 - 不要
    /// 使用代码编辑器修改此方法的内容。
    /// </summary>
    private void InitializeComponent()
    {
        System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
        this.menuStripMain = new System.Windows.Forms.MenuStrip();
        this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.statusStripMain = new System.Windows.Forms.StatusStrip();
        this.toolStripMain = new System.Windows.Forms.ToolStrip();
        this.newToolStripButton = new System.Windows.Forms.ToolStripButton();
        this.openToolStripButton = new System.Windows.Forms.ToolStripButton();
        this.saveToolStripButton = new System.Windows.Forms.ToolStripButton();
        this.toolStripSeparator = new System.Windows.Forms.ToolStripSeparator();
        this.helpToolStripButton = new System.Windows.Forms.ToolStripButton();
        this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
        this.menuStripMain.SuspendLayout();
        this.toolStripMain.SuspendLayout();
        this.SuspendLayout();
        // 
        // menuStripMain
        // 
        this.menuStripMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
        this.menuStripMain.Location = new System.Drawing.Point(0, 0);
        this.menuStripMain.Name = "menuStripMain";
        this.menuStripMain.Size = new System.Drawing.Size(821, 25);
        this.menuStripMain.TabIndex = 0;
        // 
        // fileToolStripMenuItem
        // 
        this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.exitToolStripMenuItem});
        this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
        this.fileToolStripMenuItem.Size = new System.Drawing.Size(39, 21);
        this.fileToolStripMenuItem.Text = "&File";
        // 
        // exitToolStripMenuItem
        // 
        this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
        this.exitToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
        this.exitToolStripMenuItem.Text = "E&xit";
        this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
        // 
        // statusStripMain
        // 
        this.statusStripMain.Location = new System.Drawing.Point(0, 560);
        this.statusStripMain.Name = "statusStripMain";
        this.statusStripMain.Size = new System.Drawing.Size(821, 22);
        this.statusStripMain.TabIndex = 1;
        // 
        // toolStripMain
        // 
        this.toolStripMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripButton,
            this.openToolStripButton,
            this.saveToolStripButton,
            this.toolStripSeparator,
            this.helpToolStripButton});
        this.toolStripMain.Location = new System.Drawing.Point(0, 25);
        this.toolStripMain.Name = "toolStripMain";
        this.toolStripMain.Size = new System.Drawing.Size(821, 25);
        this.toolStripMain.TabIndex = 2;
        // 
        // newToolStripButton
        // 
        this.newToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
        this.newToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("newToolStripButton.Image")));
        this.newToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
        this.newToolStripButton.Name = "newToolStripButton";
        this.newToolStripButton.Size = new System.Drawing.Size(23, 22);
        this.newToolStripButton.Text = "New(&N)";
        // 
        // openToolStripButton
        // 
        this.openToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
        this.openToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("openToolStripButton.Image")));
        this.openToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
        this.openToolStripButton.Name = "openToolStripButton";
        this.openToolStripButton.Size = new System.Drawing.Size(23, 22);
        this.openToolStripButton.Text = "Open(&O)";
        // 
        // saveToolStripButton
        // 
        this.saveToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
        this.saveToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("saveToolStripButton.Image")));
        this.saveToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
        this.saveToolStripButton.Name = "saveToolStripButton";
        this.saveToolStripButton.Size = new System.Drawing.Size(23, 22);
        this.saveToolStripButton.Text = "Save(&S)";
        // 
        // toolStripSeparator
        // 
        this.toolStripSeparator.Name = "toolStripSeparator";
        this.toolStripSeparator.Size = new System.Drawing.Size(6, 25);
        // 
        // helpToolStripButton
        // 
        this.helpToolStripButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
        this.helpToolStripButton.Image = ((System.Drawing.Image)(resources.GetObject("helpToolStripButton.Image")));
        this.helpToolStripButton.ImageTransparentColor = System.Drawing.Color.Magenta;
        this.helpToolStripButton.Name = "helpToolStripButton";
        this.helpToolStripButton.Size = new System.Drawing.Size(23, 22);
        this.helpToolStripButton.Text = "Help(&L)";
        // 
        // newToolStripMenuItem
        // 
        this.newToolStripMenuItem.Name = "newToolStripMenuItem";
        this.newToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
        this.newToolStripMenuItem.Text = "&New";
        // 
        // openToolStripMenuItem
        // 
        this.openToolStripMenuItem.Name = "openToolStripMenuItem";
        this.openToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
        this.openToolStripMenuItem.Text = "&Open";
        // 
        // saveToolStripMenuItem
        // 
        this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
        this.saveToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
        this.saveToolStripMenuItem.Text = "&Save";
        // 
        // MainForm
        // 
        this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
        this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        this.ClientSize = new System.Drawing.Size(821, 582);
        this.Controls.Add(this.toolStripMain);
        this.Controls.Add(this.statusStripMain);
        this.Controls.Add(this.menuStripMain);
        this.MainMenuStrip = this.menuStripMain;
        this.Name = "MainForm";
        this.Text = "SwingEngine Scene Editor";
        this.menuStripMain.ResumeLayout(false);
        this.menuStripMain.PerformLayout();
        this.toolStripMain.ResumeLayout(false);
        this.toolStripMain.PerformLayout();
        this.ResumeLayout(false);
        this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.MenuStrip menuStripMain;
    private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
    private System.Windows.Forms.StatusStrip statusStripMain;
    private System.Windows.Forms.ToolStrip toolStripMain;
    private System.Windows.Forms.ToolStripButton newToolStripButton;
    private System.Windows.Forms.ToolStripButton openToolStripButton;
    private System.Windows.Forms.ToolStripButton saveToolStripButton;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator;
    private System.Windows.Forms.ToolStripButton helpToolStripButton;
    private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
}

}