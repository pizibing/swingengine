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
    }

    // Properties.
    property PictureBox^ MainRenderingWindow
    {
        PictureBox^ get(void)
        {
            return pictureBoxRendering;
        }
    }

protected:
    ~MainForm()
    {
        if( components )
        {
            delete components;
        }
    }
private: System::Windows::Forms::PictureBox^  pictureBoxRendering;
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
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxRendering))->BeginInit();
        this->SuspendLayout();
        // 
        // pictureBoxRendering
        // 
        this->pictureBoxRendering->Location = System::Drawing::Point(12, 26);
        this->pictureBoxRendering->Name = L"pictureBoxRendering";
        this->pictureBoxRendering->Size = System::Drawing::Size(640, 480);
        this->pictureBoxRendering->TabIndex = 0;
        this->pictureBoxRendering->TabStop = false;
        // 
        // MainForm
        // 
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(710, 522);
        this->Controls->Add(this->pictureBoxRendering);
        this->Name = L"MainForm";
        this->Text = L"MainForm";
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBoxRendering))->EndInit();
        this->ResumeLayout(false);

    }
#pragma endregion
};

}}}
