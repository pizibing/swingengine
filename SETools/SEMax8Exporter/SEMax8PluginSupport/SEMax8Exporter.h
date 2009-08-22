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

#ifndef Swing_Max8Exporter_H
#define Swing_Max8Exporter_H

#include <windows.h>

// 关于使用VC2005(VC80)编译此项目的编译错误问题:
// max8 SDK的头文件polyobj.h和imtl.h存在int i定义域不严格的问题,比如:
// for( int i; condition; i++ )
// {
//     do something...
// }
// int j = i; // 这将被VC2005视为错误
// 因此手动需要修改以上两个头文件,比如:
// int i;
// for( i = 0; condition; i++ )
// {
//     do something...
// }
// int j = i; // 正确

//----------------------------------------------------------------------------
// 名称:Max8Exporter类
// 说明:
// 作者:Sun Che
// 时间:20080814
//----------------------------------------------------------------------------
class Max8Exporter
{
public:
    Max8Exporter(void);
    ~Max8Exporter(void);

    void SetInstance(HINSTANCE hInstance);
    HINSTANCE GetInstance(void) const;
    void SetControlsInitialized(void);
    bool GetControlsInitialized(void) const;
    const TCHAR* GetResourceString(unsigned int uiID) const;

    static Max8Exporter ThePlugin;

private:
    HINSTANCE m_hInstance;
    bool m_bControlsInitialized;

    enum { MAX_RESOURCE_STRING = 512 };
    TCHAR m_acResourceString[MAX_RESOURCE_STRING];
};

#endif



