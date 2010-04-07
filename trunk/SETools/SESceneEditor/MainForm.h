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


namespace SceneEditor{

//----------------------------------------------------------------------------
// Name:Main form class
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

protected:
    ~MainForm()
    {
        if( components )
        {
            delete components;
        }
    }

private:
    /// <summary>
    /// ����������������
    /// </summary>
    System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// �����֧������ķ��� - ��Ҫ
    /// ʹ�ô���༭���޸Ĵ˷��������ݡ�
    /// </summary>
	void InitializeComponent(void)
	{
        this->SuspendLayout();
        // 
        // MainForm
        // 
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(710, 476);
        this->Name = L"MainForm";
        this->Text = L"MainForm";
        this->ResumeLayout(false);

    }
#pragma endregion
};

}