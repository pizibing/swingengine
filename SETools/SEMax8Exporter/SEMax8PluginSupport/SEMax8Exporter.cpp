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

#include "SEMax8Exporter.h"
#include "SEMax8ClassDesc.h"
#include "max.h"
#include "resource.h"
#include <cassert>

Max8Exporter Max8Exporter::ThePlugin;

//----------------------------------------------------------------------------
Max8Exporter::Max8Exporter()
{
    m_hInstance = NULL;
    m_bControlsInitialized = false;
    memset(m_acResourceString, 0, MAX_RESOURCE_STRING*sizeof(TCHAR));
}
//----------------------------------------------------------------------------
Max8Exporter::~Max8Exporter()
{
}
//----------------------------------------------------------------------------
void Max8Exporter::SetInstance(HINSTANCE hInstance)
{
    m_hInstance = hInstance;
}
//----------------------------------------------------------------------------
HINSTANCE Max8Exporter::GetInstance() const
{
    return m_hInstance;
}
//----------------------------------------------------------------------------
void Max8Exporter::SetControlsInitialized()
{
    m_bControlsInitialized = true;
}
//----------------------------------------------------------------------------
bool Max8Exporter::GetControlsInitialized() const
{
    return m_bControlsInitialized;
}
//----------------------------------------------------------------------------
const TCHAR* Max8Exporter::GetResourceString(unsigned int uiID) const
{
    assert( m_hInstance != NULL );

    if( !m_hInstance )
    {
        return NULL;
    }

    int iCount = LoadString(m_hInstance, uiID, (LPSTR)m_acResourceString,
        MAX_RESOURCE_STRING);

    return ( iCount > 0 ? m_acResourceString : NULL );
}
//----------------------------------------------------------------------------
BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG, LPVOID)
{
    // DLL入口函数.
    Max8Exporter::ThePlugin.SetInstance(hInstance);
    if( !Max8Exporter::ThePlugin.GetControlsInitialized() ) 
    {
        Max8Exporter::ThePlugin.SetControlsInitialized();

        // 初始化MAX自定义控件
        InitCustomControls(hInstance);

        // 初始化Windows控件
        InitCommonControls();
    }

    return TRUE;
}
//----------------------------------------------------------------------------
__declspec(dllexport) const TCHAR* LibDescription()
{
    // 获取DLL信息描述.
    return Max8Exporter::ThePlugin.GetResourceString(IDS_LIBDESCRIPTION);
}
//----------------------------------------------------------------------------
__declspec(dllexport) int LibNumberClasses()
{
    // 获取DLL中插件类数量.
    return 1;
}
//----------------------------------------------------------------------------
__declspec(dllexport) ClassDesc* LibClassDesc(int i)
{
    // 获取插件描述.
    // 本DLL中只存在一个插件.
    return &Max8ClassDesc::TheDescription;
}
//----------------------------------------------------------------------------
__declspec(dllexport) ULONG LibVersion()
{
    // 获取一个预定义常量版本信息,从而获知使用本DLL的系统软件版本.
    // 从而可以用来捕捉过时的DLL.
    return VERSION_3DSMAX;
}
//----------------------------------------------------------------------------



