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

#ifndef Swing_Max8SceneExport_H
#define Swing_Max8SceneExport_H

#include "max.h"
#include "SEMax8ExportSettings.h"

//----------------------------------------------------------------------------
// 名称:Max8SceneExport类
// 说明:
// 作者:Sun Che
// 时间:20080814
//----------------------------------------------------------------------------
class Max8SceneExport : public SceneExport 
{
public:
    Max8SceneExport(void);
    virtual ~Max8SceneExport(void);       

    // 重载自SceneExport
    virtual int ExtCount(void);
    virtual const TCHAR* Ext(int iExt);
    virtual const TCHAR* LongDesc(void);
    virtual const TCHAR* ShortDesc(void);
    virtual const TCHAR* AuthorName(void);
    virtual const TCHAR* CopyrightMessage(void);
    virtual const TCHAR* OtherMessage1(void);
    virtual const TCHAR* OtherMessage2(void);
    virtual unsigned int Version(void);
    virtual void ShowAbout(HWND hWnd);
    virtual int DoExport(const TCHAR* acFilename, ExpInterface* pExport,
        Interface* pMax, BOOL bSuppressPrompts = FALSE, DWORD dwOptions = 0);
    virtual BOOL SupportsOptions(int iExt, DWORD dwOptions);

    // UI界面的消息处理函数
    static BOOL CALLBACK DialogProcedure(HWND hWnd, UINT uiMsg,
        WPARAM wParam, LPARAM lParam);

    // UI界面的具体消息处理函数   
    BOOL OnEnableFrameSpinners(HWND hWnd, BOOL bEnabled);
    BOOL OnEndFrameSpinnerChanged(HWND hWnd);
    BOOL OnInitDialog(HWND hWnd);
    BOOL OnMeshChecked(HWND hWnd, BOOL bEnabled);
    BOOL OnModifiersChecked(HWND hWnd, BOOL bEnabled);
    BOOL OnObjectsChecked(HWND hWnd, BOOL bEnabled);
    void OnOK(HWND hWnd);
    BOOL OnStartFrameSpinnerChanged(HWND hWnd);

private:
    enum { EXPORTER_VERSION = 100 };

    // 导出器配置文件相关函数
    void ReadConfiguration(void);
    void WriteConfiguration(void);
    
    Interface* m_pMax;
    Max8ExportSettings m_Settings, m_EffectiveSettings;
    TSTR m_StrConfigFile;
};

#endif



