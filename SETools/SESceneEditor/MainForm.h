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

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20100407
//----------------------------------------------------------------------------
public ref class MainForm : public System::Windows::Forms::Form
{
public:
    MainForm(void)
    {
        InitializeComponent();

        m_thApplication = nullptr;
        pictureBoxRendering->MouseWheel += gcnew MouseEventHandler(this,
            &MainForm::pictureBoxRendering_MouseWheel);
    }

    #pragma region Properties

    property PictureBox^ MainRenderingWindow
    {
        PictureBox^ get(void)
        {
            return pictureBoxRendering;
        }
    }
    property SESceneEditorApplication^ App
    {
        SESceneEditorApplication^ get(void)
        {
            return m_thApplication;
        }
        void set(SESceneEditorApplication^ thApplication)
        {
            m_thApplication = thApplication;
        }
    }
    property bool UsingPlanform
    {
        bool get(void)
        {
            return false;
        }
    }

    #pragma endregion

protected:
    ~MainForm()
    {
        if( components )
        {
            delete components;
        }
    }
private: System::Windows::Forms::PictureBox^  pictureBoxRendering;
private: System::Windows::Forms::MenuStrip^  menuStripMain;
private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
protected: 

private:
    /// <summary>
    /// 必需的设计器变量。
    /// </summary>
    System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// 设计器支持所需的方法 - 不要
    /// 使用代码编辑器修改此方法的内容。
    /// </summary>
    void InitializeComponent(void)
    {
        this->pictureBoxRendering = (gcnew System::Windows::Forms::PictureBox());
        this->menuStripMain = (gcnew System::Windows::Forms::MenuStrip());
        this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxRendering))->BeginInit();
        this->menuStripMain->SuspendLayout();
        this->SuspendLayout();
        // 
        // pictureBoxRendering
        // 
        this->pictureBoxRendering->Location = System::Drawing::Point(12, 40);
        this->pictureBoxRendering->Name = L"pictureBoxRendering";
        this->pictureBoxRendering->Size = System::Drawing::Size(800, 600);
        this->pictureBoxRendering->TabIndex = 0;
        this->pictureBoxRendering->TabStop = false;
        this->pictureBoxRendering->MouseLeave += gcnew System::EventHandler(this, &MainForm::pictureBoxRendering_MouseLeave);
        this->pictureBoxRendering->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pictureBoxRendering_MouseMove);
        this->pictureBoxRendering->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pictureBoxRendering_MouseClick);
        this->pictureBoxRendering->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pictureBoxRendering_MouseDown);
        this->pictureBoxRendering->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pictureBoxRendering_MouseUp);
        this->pictureBoxRendering->MouseEnter += gcnew System::EventHandler(this, &MainForm::pictureBoxRendering_MouseEnter);
        // 
        // menuStripMain
        // 
        this->menuStripMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->fileToolStripMenuItem});
        this->menuStripMain->Location = System::Drawing::Point(0, 0);
        this->menuStripMain->Name = L"menuStripMain";
        this->menuStripMain->Size = System::Drawing::Size(1160, 25);
        this->menuStripMain->TabIndex = 1;
        this->menuStripMain->Text = L"menuStrip1";
        // 
        // fileToolStripMenuItem
        // 
        this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->openToolStripMenuItem, 
            this->saveToolStripMenuItem, this->exitToolStripMenuItem});
        this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
        this->fileToolStripMenuItem->Size = System::Drawing::Size(39, 21);
        this->fileToolStripMenuItem->Text = L"File";
        // 
        // openToolStripMenuItem
        // 
        this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
        this->openToolStripMenuItem->Size = System::Drawing::Size(108, 22);
        this->openToolStripMenuItem->Text = L"Open";
        this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openToolStripMenuItem_Click);
        // 
        // saveToolStripMenuItem
        // 
        this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
        this->saveToolStripMenuItem->Size = System::Drawing::Size(108, 22);
        this->saveToolStripMenuItem->Text = L"Save";
        // 
        // exitToolStripMenuItem
        // 
        this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
        this->exitToolStripMenuItem->Size = System::Drawing::Size(108, 22);
        this->exitToolStripMenuItem->Text = L"Exit";
        this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exitToolStripMenuItem_Click);
        // 
        // MainForm
        // 
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(1160, 673);
        this->Controls->Add(this->pictureBoxRendering);
        this->Controls->Add(this->menuStripMain);
        this->MainMenuStrip = this->menuStripMain;
        this->Name = L"MainForm";
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
        this->Text = L"Swing Engine Scene Editor";
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxRendering))->EndInit();
        this->menuStripMain->ResumeLayout(false);
        this->menuStripMain->PerformLayout();
        this->ResumeLayout(false);
        this->PerformLayout();

    }
#pragma endregion

private: 
    void openToolStripMenuItem_Click(Object^ thSender, EventArgs^ thEvent) 
    {
        if( m_thApplication )
        {
            m_thApplication->OnOpenToolStripMenuItemClick(thSender, thEvent);
        }
    }

    void pictureBoxRendering_MouseDown(Object^ thSender, MouseEventArgs^ thEvent)
    {
        if( m_thApplication )
        {
            m_thApplication->OnWindowRenderingMouseDown(thSender, thEvent);
        }
    }

    void pictureBoxRendering_MouseEnter(Object^ thSender, EventArgs^ thEvent)
    {
        // To ensure the mouse wheel event could be triggered, we focus the rendering window.
        pictureBoxRendering->Focus();

        if( m_thApplication )
        {
            m_thApplication->OnWindowRenderingMouseEnter(thSender, thEvent);
        }
    }

    void pictureBoxRendering_MouseLeave(Object^ thSender, EventArgs^ thEvent)
    {
        if( m_thApplication )
        {
            m_thApplication->OnWindowRenderingMouseLeave(thSender, thEvent);
        }
    }

    void pictureBoxRendering_MouseMove(Object^ thSender, MouseEventArgs^ thEvent)
    {
        if( m_thApplication )
        {
            m_thApplication->OnWindowRenderingMouseMove(thSender, thEvent);
        }
    }

    void pictureBoxRendering_MouseUp(Object^ thSender, MouseEventArgs^ thEvent)
    {
        if( m_thApplication )
        {
            m_thApplication->OnWindowRenderingMouseUp(thSender, thEvent);
        }
    }

    void pictureBoxRendering_MouseClick(Object^ thSender, MouseEventArgs^ thEvent)
    {
        if( m_thApplication )
        {
            m_thApplication->OnWindowRenderingMouseClick(thSender, thEvent);
        }
    }

    void pictureBoxRendering_MouseWheel(Object^ thSender, MouseEventArgs^ thEvent)
    {
        if( m_thApplication )
        {
            m_thApplication->OnWindowRenderingMouseWheel(thSender, thEvent);
        }
    }

    void exitToolStripMenuItem_Click(Object^, EventArgs^)
    {
        Application::Exit();
    }

private:
    SESceneEditorApplication^ m_thApplication;

};

}}}
