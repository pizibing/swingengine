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
public ref class StringTreeForm : public System::Windows::Forms::Form
{
public:
	StringTreeForm(void)
	{
		InitializeComponent();
		//
		//TODO: Add the constructor code here
		//
	}

    #pragma region Properties

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

    #pragma endregion

    void CreateStringTree(SEStringTree* pTree);

protected:
	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
	~StringTreeForm()
	{
		if (components)
		{
			delete components;
		}
	}
private: System::Windows::Forms::TreeView^  treeViewStringTree;
protected: 

private:
	/// <summary>
	/// Required designer variable.
	/// </summary>
	System::ComponentModel::Container ^components;

    #pragma region Windows Form Designer generated code
	/// <summary>
	/// Required method for Designer support - do not modify
	/// the contents of this method with the code editor.
	/// </summary>
	void InitializeComponent(void)
	{
        this->treeViewStringTree = (gcnew System::Windows::Forms::TreeView());
        this->SuspendLayout();
        // 
        // treeViewStringTree
        // 
        this->treeViewStringTree->Location = System::Drawing::Point(12, 12);
        this->treeViewStringTree->Name = L"treeViewStringTree";
        this->treeViewStringTree->Size = System::Drawing::Size(600, 418);
        this->treeViewStringTree->TabIndex = 0;
        // 
        // StringTreeForm
        // 
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(624, 442);
        this->Controls->Add(this->treeViewStringTree);
        this->Name = L"StringTreeForm";
        this->Text = L"Scene Graph String Tree";
        this->ResumeLayout(false);

    }
    #pragma endregion

private:
    SESceneEditorApplication^ m_thApplication;
};

}}}
