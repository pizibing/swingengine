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

#include "SEMax8SceneBuilder.h"
#include "SEMax8SceneExport.h"
#include "SEMax8Exporter.h"
#include "resource.h"

using namespace Swing;

//----------------------------------------------------------------------------
Max8SceneExport::Max8SceneExport()
{
}
//----------------------------------------------------------------------------
Max8SceneExport::~Max8SceneExport()
{
}
//----------------------------------------------------------------------------
int Max8SceneExport::ExtCount()
{
    // 插件支持的导出文件扩展名.
    // 只支持一种(*.seof).
    return 1;
}
//----------------------------------------------------------------------------
const TCHAR* Max8SceneExport::Ext(int)
{       
    // 返回文件扩展名.
    return _T("seof");
}
//----------------------------------------------------------------------------
const TCHAR* Max8SceneExport::LongDesc()
{
    // 导出文件的长描述.
    return Max8Exporter::ThePlugin.GetResourceString(IDS_LONGDESCRIPTION);
}
//----------------------------------------------------------------------------
const TCHAR* Max8SceneExport::ShortDesc() 
{           
    // 导出文件的短描述.
    return Max8Exporter::ThePlugin.GetResourceString(IDS_SHORTDESCRIPTION);
}
//----------------------------------------------------------------------------
const TCHAR* Max8SceneExport::AuthorName()
{           
    // 插件作者.
    return Max8Exporter::ThePlugin.GetResourceString(IDS_AUTHORNAME);
}
//----------------------------------------------------------------------------
const TCHAR* Max8SceneExport::CopyrightMessage() 
{   
    // 版权信息.
    return
    _T("Swing Tech. Copyright (c) 2007-2008. All Rights Reserved");
}
//----------------------------------------------------------------------------
const TCHAR* Max8SceneExport::OtherMessage1() 
{       
    // 其他额外信息1.
    return _T("");
}
//----------------------------------------------------------------------------
const TCHAR* Max8SceneExport::OtherMessage2() 
{       
    // 其他额外信息2.
    return _T("");
}
//----------------------------------------------------------------------------
unsigned int Max8SceneExport::Version()
{               
    // 返回导出器版本号.
    return EXPORTER_VERSION;
}
//----------------------------------------------------------------------------
void Max8SceneExport::ShowAbout(HWND)
{           
    // 待实现.
    // 显示插件的About对话框.
}
//----------------------------------------------------------------------------
BOOL Max8SceneExport::SupportsOptions(int, DWORD)
{
    // Max调用这个函数获取插件支持给定文件扩展名的哪些选项.
    // 当前支持所有选项.
    return TRUE;
}
//----------------------------------------------------------------------------
int Max8SceneExport::DoExport(const TCHAR* acFilename, ExpInterface* pExport,
    Interface* pMax, BOOL bSuppressPrompts, DWORD dwOptions)
{
    // 从磁盘文件获取导出器的当前配置,
    // 显示UI界面,根据当前配置,建立并且保存Swing Engine scene graph,
    // 之后保存当前配置到磁盘文件.
    //    acFilename:
    //        用户指定的Swing Engine scene graph文件名.
    //    pExport:
    //        访问Max的导出器相关功能的接口指针.
    //    pMax:
    //        访问Max相关功能的主接口指针.
    //    bSuppressPrompts:
    //        允许,或禁止用户输入.
    //    dwOptions:
    //        决定导出整个场景,或场景的选中部分.

    m_pMax = pMax;
    INode* pRootNode = NULL;
    bool bExportSelected;

    if( dwOptions == SCENE_EXPORT_SELECTED )
    {
        // 用户选择导出部分场景,
        // 检查确保只能选中场景中的一个子节点,作为导出子场景的根节点.
        if( m_pMax->GetSelNodeCount() != 1 )
        {
            assert( false );

            return 0;
        }

        pRootNode = m_pMax->GetSelNode(0);
        bExportSelected = true;
    }
    else
    {
        // 导出整个场景,
        // 从Max场景的根节点开始.
        pRootNode = m_pMax->GetRootNode();
        bExportSelected = false;
    }

    // 获取导出器插件配置文件的路径.
    m_StrConfigFile = m_pMax->GetDir(APP_PLUGCFG_DIR);
    m_StrConfigFile += "\\Max8Exporter.cfg";

    // 恢复先前导出器的配置.
    ReadConfiguration();

    // 显示导出器UI.
    if( !bSuppressPrompts )
    {
        INT_PTR piResult = DialogBoxParam(Max8Exporter::ThePlugin.GetInstance(),
            MAKEINTRESOURCE(IDD_PANEL), GetActiveWindow(), DialogProcedure,
            (LPARAM)this);

        if( !piResult )
            return 1;
    }

    // 实际导出工作,将Max场景转换为Swing Engine场景并生成磁盘文件.
    Max8SceneBuilder(acFilename, bExportSelected, &m_EffectiveSettings, pExport,
        pMax, pRootNode);

    // 保存导出器的本次配置.
    WriteConfiguration();
    
    return 1;
}
//----------------------------------------------------------------------------
void Max8SceneExport::ReadConfiguration()
{
    // 从磁盘文件恢复导出器的配置情况.
    // 该配置情况是用户上次操作导出器的配置结果.

    // 如果配置文件不存在(比如第一次运行导出器),
    // 则使用默认配置.
    FILE* pConfig = SESystem::SE_Fopen(m_StrConfigFile, "rb");
    if( pConfig  == NULL )
    {
        return;
    }

    // 获取配置文件版本.
    int iVersion;
    if( fread(&iVersion, sizeof(int), 1, pConfig) != 1 )
    {
        // 文件不正确
        assert( false );
        fclose(pConfig);

        return;
    }

    // 验证导出器版本和配置文件版本是否匹配.
    if( iVersion != EXPORTER_VERSION )
    {
        // 不匹配
        assert( false );
        fclose(pConfig);

        return;
    }

    // 获取配置信息.
    Max8ExportSettings tempSettings;
    if( fread(&tempSettings, sizeof(Max8ExportSettings), 1, pConfig) != 1 )
    {
        // 文件不正确
        assert( false );
        fclose(pConfig);

        return;
    }
    
    fclose(pConfig);

    // 覆盖默认配置信息.
    memcpy(&m_Settings, &tempSettings, sizeof(Max8ExportSettings));
}
//----------------------------------------------------------------------------
void Max8SceneExport::WriteConfiguration()
{
    FILE* pConfig = SESystem::SE_Fopen(m_StrConfigFile, "wb");
    if( pConfig == NULL )
    {
        // 创建配置文件失败
        assert( false );

        return;
    }

    // 写入配置文件版本.
    int iVersion = EXPORTER_VERSION;
    if( fwrite(&iVersion, sizeof(int), 1, pConfig) != 1 )
    {
        // 写配置文件失败
        assert( false );
        fclose(pConfig);

        return;
    }

    // 写入导出器配置信息.
    if( fwrite(&m_Settings, sizeof(Max8ExportSettings), 1, pConfig) != 1 )
    {
        // 写配置文件失败
        assert( false );
        fclose(pConfig);

        return;
    }
    
    fclose(pConfig);
}
//----------------------------------------------------------------------------
BOOL CALLBACK Max8SceneExport::DialogProcedure(HWND hWnd, UINT uiMsg,
    WPARAM wParam, LPARAM lParam) 
{
    if( uiMsg == WM_INITDIALOG )
    {
        // 当对话框初始化时,Max通过LPARAM参数传递当前导出器实例的"this"指针进来.
        // 保存这个指针供稍后使用.
        SetWindowLongPtr(hWnd, GWLP_USERDATA, lParam);

        // 调用对话框实例的初始化函数.
        return ((Max8SceneExport*)lParam)->OnInitDialog(hWnd);
    }

    Max8SceneExport* pExporter = (Max8SceneExport*)GetWindowLongPtr(hWnd,
        GWLP_USERDATA); 

    switch( uiMsg )
    {
    case WM_COMMAND:
        // 用户操作UI产生了UI事件,
        // 判断事件,做出相应响应.
        switch( LOWORD(wParam) ) 
        {
        case IDC_CHECK_MESHES:
            return pExporter->OnMeshChecked(hWnd,
                IsDlgButtonChecked(hWnd, IDC_CHECK_MESHES));
        case IDC_CHECK_OBJECTS:
            return pExporter->OnObjectsChecked(hWnd,
                IsDlgButtonChecked(hWnd, IDC_CHECK_OBJECTS));
        case IDC_CHECK_MODIFIERS:
            return pExporter->OnModifiersChecked(hWnd,
                IsDlgButtonChecked(hWnd, IDC_CHECK_MODIFIERS));
        case IDC_RADIO_ALLFRAMES:
        case IDC_RADIO_KEYFRAMES:
            return pExporter->OnEnableFrameSpinners(hWnd, TRUE);
        case IDC_RADIO_CURRENTFRAME:
            return pExporter->OnEnableFrameSpinners(hWnd, FALSE);
        case IDOK:
            pExporter->OnOK(hWnd);
            EndDialog(hWnd, 1);

            break;
        case IDCANCEL:
            EndDialog(hWnd, 0);

            break;
        default:
            return FALSE;
        }
        break;

    case CC_SPINNER_CHANGE:
        // spinner控件的消息处理.
        switch( LOWORD(wParam) )
        {
        case IDC_SPINNER_ENDFRAME:
            return pExporter->OnEndFrameSpinnerChanged(hWnd);
        case IDC_SPINNER_STARTFRAME:
            return pExporter->OnStartFrameSpinnerChanged(hWnd);
        }
        break;

    case WM_CLOSE:
        EndDialog(hWnd, 0);

        return TRUE;
    }

    return FALSE;
}
//----------------------------------------------------------------------------
BOOL Max8SceneExport::OnEnableFrameSpinners(HWND hWnd, BOOL bEnabled)
{
    // 开启或关闭frame spinner控件.
    ISpinnerControl* pSpinner = GetISpinner(GetDlgItem(hWnd,
        IDC_SPINNER_STARTFRAME));
    pSpinner->Enable(bEnabled);
    ReleaseISpinner(pSpinner); 
    pSpinner = GetISpinner(GetDlgItem(hWnd, IDC_SPINNER_ENDFRAME)); 
    pSpinner->Enable(bEnabled);

    return TRUE;
}
//----------------------------------------------------------------------------
BOOL Max8SceneExport::OnEndFrameSpinnerChanged(HWND hWnd)
{
    // 当用户修改表示导出动画结束桢的spinner控件时调用.

    // 从spinner控件获取导出动画起始桢.
    ISpinnerControl* pSpinner = GetISpinner(GetDlgItem(hWnd,
        IDC_SPINNER_STARTFRAME)); 
    int iStartFrame = pSpinner->GetIVal();
    ReleaseISpinner(pSpinner);

    // 确保导出动画结束桢大于等于导出动画起始桢.
    pSpinner = GetISpinner(GetDlgItem(hWnd, IDC_SPINNER_ENDFRAME)); 
    int iEndFrame = pSpinner->GetIVal();
    if( iStartFrame > iEndFrame )
    {
        pSpinner->SetValue(iStartFrame, FALSE);
    }

    ReleaseISpinner(pSpinner);

    return TRUE;
}
//----------------------------------------------------------------------------
BOOL Max8SceneExport::OnInitDialog(HWND hWnd)
{
    // 当对话框接到WM_INITDIALOG消息时,进行导出器UI初始化工作.

    CenterWindow(hWnd, GetParent(hWnd)); 

    // 设置UI状态.
    // 如果配置文件存在,则体现上次使用导出器后的配置文件的内容.
    // 否则使用默认配置.
    CheckDlgButton(hWnd,IDC_CHECK_OBJECTS, m_Settings.IncludeObjects);
    CheckDlgButton(hWnd,IDC_CHECK_LIGHTS, m_Settings.IncludeLights);
    CheckDlgButton(hWnd,IDC_CHECK_MESHES, m_Settings.IncludeMeshes);
    CheckDlgButton(hWnd,IDC_CHECK_CAMERAS, m_Settings.IncludeCameras);
    CheckDlgButton(hWnd,IDC_CHECK_NORMALS, m_Settings.IncludeNormals);       
    CheckDlgButton(hWnd,IDC_CHECK_MATERIALS, m_Settings.IncludeMaterials);
    CheckDlgButton(hWnd,IDC_CHECK_VERTEXCOLS, m_Settings.IncludeVertexColors);
    CheckDlgButton(hWnd,IDC_CHECK_TEXCOORDS, m_Settings.IncludeTexCoords);
    CheckDlgButton(hWnd,IDC_CHECK_GENERATEMAPS, m_Settings.GenerateMaps);
    CheckDlgButton(hWnd,IDC_CHECK_MODIFIERS, m_Settings.IncludeModifiers);
    CheckDlgButton(hWnd,IDC_CHECK_SKINS, m_Settings.IncludeSkins);
    CheckDlgButton(hWnd,IDC_CHECK_GPU, m_Settings.UseGPUSkin);
    CheckDlgButton(hWnd,IDC_RADIO_CURRENTFRAME, m_Settings.IncludeCurrentFrame);
    CheckDlgButton(hWnd,IDC_RADIO_KEYFRAMES, m_Settings.IncludeKeyFrames);
    CheckDlgButton(hWnd,IDC_RADIO_ALLFRAMES, m_Settings.IncludeAllFrames);
    CheckDlgButton(hWnd,IDC_CHECK_USELOCALTIME, m_Settings.UseLocalTime);

    if( !m_Settings.IncludeObjects )
    {
        // 如果未选中"Object",则关闭其下属子选项.
        OnObjectsChecked(hWnd, FALSE);
    }
    else if( !m_Settings.IncludeMeshes )
    {
        // 如果未选中"Mesh",则关闭其下属子选项.
        OnMeshChecked(hWnd, FALSE);
    }

    // 如果未选中"Modifiers",则关闭其下属子选项.
    if( !m_Settings.IncludeModifiers )
    {
        OnModifiersChecked(hWnd, FALSE);
    }

    // 获取Max场景中的动画桢数目.
    int iNumFrames = m_pMax->GetAnimRange().Duration() / GetTicksPerFrame();

    // 设置spinner控件.
    ISpinnerControl* pSpinner = GetISpinner(GetDlgItem(hWnd,
        IDC_SPINNER_STARTFRAME));
    pSpinner->LinkToEdit(GetDlgItem(hWnd, IDC_EDIT_STARTFRAME), EDITTYPE_INT);
    pSpinner->SetLimits(0, iNumFrames, TRUE);
    pSpinner->SetScale(1.0f);
    pSpinner->SetValue(0, FALSE);
    if( m_Settings.IncludeCurrentFrame )
    {
        pSpinner->Enable(FALSE);
    }
    ReleaseISpinner(pSpinner);

    pSpinner = GetISpinner(GetDlgItem(hWnd, IDC_SPINNER_ENDFRAME));
    pSpinner->LinkToEdit(GetDlgItem(hWnd, IDC_EDIT_ENDFRAME), EDITTYPE_INT);
    pSpinner->SetLimits(0, iNumFrames, TRUE);
    pSpinner->SetScale(1.0f);
    pSpinner->SetValue(iNumFrames, FALSE);
    if( m_Settings.IncludeCurrentFrame )
    {
        pSpinner->Enable(FALSE);
    }
    ReleaseISpinner(pSpinner);

    return TRUE;
}
//----------------------------------------------------------------------------
BOOL Max8SceneExport::OnMeshChecked(HWND hWnd, BOOL bEnabled)
{
    // 点击"Mesh"时的动作.
    EnableWindow(GetDlgItem(hWnd, IDC_CHECK_NORMALS), bEnabled);
    EnableWindow(GetDlgItem(hWnd, IDC_CHECK_VERTEXCOLS), bEnabled);
    EnableWindow(GetDlgItem(hWnd, IDC_CHECK_TEXCOORDS), bEnabled);
    EnableWindow(GetDlgItem(hWnd, IDC_CHECK_MATERIALS), bEnabled);
    EnableWindow(GetDlgItem(hWnd, IDC_CHECK_GENERATEMAPS), bEnabled);

    return TRUE;
}
//----------------------------------------------------------------------------
BOOL Max8SceneExport::OnModifiersChecked(HWND hWnd, BOOL bEnabled)
{
    // 点击"Modifiers"时的动作.
    EnableWindow(GetDlgItem(hWnd, IDC_CHECK_SKINS), bEnabled);
    EnableWindow(GetDlgItem(hWnd, IDC_CHECK_GPU), bEnabled);

    return TRUE;
}
//----------------------------------------------------------------------------
BOOL Max8SceneExport::OnObjectsChecked(HWND hWnd, BOOL bEnabled)
{
    // 点击"Objects"时的动作.
    EnableWindow(GetDlgItem(hWnd, IDC_CHECK_MESHES), bEnabled);
    EnableWindow(GetDlgItem(hWnd, IDC_CHECK_CAMERAS), bEnabled);
    EnableWindow(GetDlgItem(hWnd, IDC_CHECK_LIGHTS), bEnabled);   

    // mesh及其子选项本身处在object子选项组中,因此传递给mesh组.
    OnMeshChecked(hWnd, bEnabled && IsDlgButtonChecked(hWnd, IDC_CHECK_MESHES));

    return TRUE;
}
//----------------------------------------------------------------------------
void Max8SceneExport::OnOK(HWND hWnd)
{
    // 用户点击OK按钮.
    // 在实际导出工作开始前,获取导出器UI上的相关选项配置数据并加以验证.

    m_Settings.IncludeObjects =
        IsDlgButtonChecked(hWnd, IDC_CHECK_OBJECTS);
    m_Settings.IncludeLights =
        IsDlgButtonChecked(hWnd, IDC_CHECK_LIGHTS);
    m_Settings.IncludeCameras =
        IsDlgButtonChecked(hWnd, IDC_CHECK_CAMERAS);
    m_Settings.IncludeMeshes =
        IsDlgButtonChecked(hWnd, IDC_CHECK_MESHES);
    m_Settings.IncludeNormals =
        IsDlgButtonChecked(hWnd, IDC_CHECK_NORMALS);
    m_Settings.IncludeVertexColors =
        IsDlgButtonChecked(hWnd, IDC_CHECK_VERTEXCOLS);
    m_Settings.IncludeTexCoords =
        IsDlgButtonChecked(hWnd, IDC_CHECK_TEXCOORDS);
    m_Settings.IncludeMaterials =
        IsDlgButtonChecked(hWnd, IDC_CHECK_MATERIALS);
    m_Settings.GenerateMaps =
        IsDlgButtonChecked(hWnd, IDC_CHECK_GENERATEMAPS);
    m_Settings.IncludeModifiers =
        IsDlgButtonChecked(hWnd, IDC_CHECK_MODIFIERS);
    m_Settings.IncludeSkins =
        IsDlgButtonChecked(hWnd, IDC_CHECK_SKINS);
    m_Settings.UseGPUSkin = 
        IsDlgButtonChecked(hWnd, IDC_CHECK_GPU);
    m_Settings.IncludeAllFrames =
        IsDlgButtonChecked(hWnd, IDC_RADIO_ALLFRAMES);
    m_Settings.IncludeKeyFrames =
        IsDlgButtonChecked(hWnd, IDC_RADIO_KEYFRAMES);
    m_Settings.IncludeCurrentFrame =
        IsDlgButtonChecked(hWnd, IDC_RADIO_CURRENTFRAME);
    m_Settings.UseLocalTime =
        IsDlgButtonChecked(hWnd, IDC_CHECK_USELOCALTIME);

    // 从相关spinner控件获取导出动画起始桢和结束桢.
    if( m_Settings.IncludeAllFrames || m_Settings.IncludeKeyFrames )
    {
        ISpinnerControl* pSpinner = GetISpinner(GetDlgItem(hWnd,
            IDC_SPINNER_STARTFRAME)); 
        m_Settings.StartFrame = pSpinner->GetIVal();
        ReleaseISpinner(pSpinner);

        pSpinner = GetISpinner(GetDlgItem(hWnd, IDC_SPINNER_ENDFRAME)); 
        m_Settings.EndFrame = pSpinner->GetIVal();
        ReleaseISpinner(pSpinner);
    }


    // 进行UI选项配置合理性纠正.
    m_EffectiveSettings = m_Settings;
    if( !m_Settings.IncludeObjects )
    {
        m_EffectiveSettings.IncludeCameras = FALSE;
        m_EffectiveSettings.IncludeLights = FALSE;
        m_EffectiveSettings.IncludeMeshes = FALSE;
    }
    if( !m_EffectiveSettings.IncludeMeshes )
    {
        m_EffectiveSettings.IncludeNormals = FALSE;
        m_EffectiveSettings.IncludeMaterials = FALSE;
        m_EffectiveSettings.IncludeVertexColors = FALSE;
        m_EffectiveSettings.IncludeTexCoords = FALSE;
        m_EffectiveSettings.GenerateMaps = FALSE;
    }
    if( !m_Settings.IncludeModifiers )
    {
        m_Settings.IncludeSkins = FALSE;
    }
}
//----------------------------------------------------------------------------
BOOL Max8SceneExport::OnStartFrameSpinnerChanged(HWND hWnd)
{
    // 当用户修改起始桢spinner控件的数据时调用.

    // 获取起始桢数据.
    ISpinnerControl* pSpinner = GetISpinner(GetDlgItem(hWnd,
        IDC_SPINNER_STARTFRAME)); 
    int iStartFrame = pSpinner->GetIVal();
    ReleaseISpinner(pSpinner);

    // 获取结束桢数据,并确保其值大于等于起始桢值.
    pSpinner = GetISpinner(GetDlgItem(hWnd,IDC_SPINNER_ENDFRAME)); 
    int iEndFrame = pSpinner->GetIVal();
    if( iEndFrame < iStartFrame )
        pSpinner->SetValue(iStartFrame, FALSE);
    ReleaseISpinner(pSpinner); 

    return TRUE;
}
//----------------------------------------------------------------------------



