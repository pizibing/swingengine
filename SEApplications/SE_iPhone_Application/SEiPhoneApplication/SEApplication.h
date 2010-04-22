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

#ifndef Swing_Application_H
#define Swing_Application_H

#include "SwingFoundation.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 说明:for iPhone application
// 作者:jazzboysc
// 时间:20090604
//----------------------------------------------------------------------------
class SEApplication
{
public:
    // 虚基类
    virtual ~SEApplication(void);

    // 唯一应用程序对象
    static SEApplication* TheApplication;

    // 唯一命令行参数对象
	static SECommand* TheCommand;

    // 派生类必须设置这个函数指针.
    // int参数是命令行参数个数.char**参数是参数字符串数组.
    typedef int (*EntryPoint)(int, char**);
    static EntryPoint Run;

    // 平台相关实现所使用的额外数据存储.
    void SetExtraData(int iIndex, int iSize, const void* pvData);
    void GetExtraData(int iIndex, int iSize, void* pvData) const;

    bool LaunchFileDialog(void) const;

    // 待实现:
    // 这个功能目前只支持Microsoft Windows.
    // 其它平台尚不支持.
    void LaunchTreeControl(SESpatial* pScene, int iXPos, int iYPos,
        int iXSize, int iYSize);
    void ShutdownTreeControl(void);

    // 用于测试disk-streaming和string-tree系统.
    // 传入对象被存储到磁盘并在稍后装载.在debug版本下,
    // 发生存储和装载数据不匹配时,将产生断言.
    // 在装载之后,LaunchTreeControl函数被调用,用于测试string-tree系统.
    // 这个功能目前只支持Microsoft Windows.
    void TestStreaming(SESpatial* pScene, int iXPos, int iYPos, int iXSize,
        int iYSize, const char* acFilename);

protected:
    SEApplication(void);

    // 额外数据
    enum { APP_EXTRA_DATA_COUNT = 128 };
    char m_acExtraData[APP_EXTRA_DATA_COUNT];

    // 支持文件对话框
    bool m_bLaunchFileDialog;
};

#include "SEApplicationMCR.h"

}

#endif
