#pragma once

extern ColladaImporterApp g_ColladaImporterApp;

namespace SEColladaImporter {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Form1 摘要
	///
	/// 警告: 如果更改此类的名称，则需要更改
	///          与此类所依赖的所有 .resx 文件关联的托管资源编译器工具的
	///          “资源文件名”属性。否则，
	///          设计器将不能与此窗体的关联
	///          本地化资源正确交互。
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::PictureBox^  SceneWindow;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	protected: 

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
			this->SceneWindow = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->SceneWindow))->BeginInit();
			this->SuspendLayout();
			// 
			// SceneWindow
			// 
			this->SceneWindow->Location = System::Drawing::Point(12, 12);
			this->SceneWindow->Name = L"SceneWindow";
			this->SceneWindow->Size = System::Drawing::Size(640, 480);
			this->SceneWindow->TabIndex = 0;
			this->SceneWindow->TabStop = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(670, 28);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Open File";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(670, 57);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Save As";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 562);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->SceneWindow);
			this->Name = L"Form1";
			this->Text = L"Swing Engine COLLADA Importer";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->SceneWindow))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: 
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			OpenFileDialog^ pDialog = gcnew OpenFileDialog;
			pDialog->InitialDirectory = "D:\\Work\\colladadom-source\\colladadom\\rt\\bin\\vc8_1.4_debug";
			pDialog->Filter = "dae|*.dae";
			pDialog->FilterIndex = 1;
			pDialog->RestoreDirectory = true;
			pDialog->ShowDialog();

			// 把System::String对象转换为char指针.
			char* acFilename = (char*)(void*)Marshal::StringToHGlobalAnsi(pDialog->FileName);

			size_t iLen = strlen(acFilename);
			if( strncmp(acFilename, "", iLen) != 0 )
			{
				g_ColladaImporterApp.OnOpenFile(acFilename);
			}
		}
	private: 
		System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			SaveFileDialog^ pDialog = gcnew SaveFileDialog;
			pDialog->InitialDirectory = "D:\\";
			pDialog->Filter = "seof|*.seof";
			pDialog->FilterIndex = 1;
			pDialog->RestoreDirectory = true;
			pDialog->ShowDialog();

			// 把System::String对象转换为char指针.
			char* acFilename = (char*)(void*)Marshal::StringToHGlobalAnsi(pDialog->FileName);

			size_t iLen = strlen(acFilename);
			if( strncmp(acFilename, "", iLen) != 0 )
			{
				g_ColladaImporterApp.OnSave(acFilename);
			}
		}
};
}

