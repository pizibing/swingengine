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

#ifndef Swing_DX9Program_H
#define Swing_DX9Program_H

#include "SEDX9RendererLIB.h"
#include "SEDX9Utility.h"
#include "SEProgram.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:DirectX9 shader程序类
// 说明:这是一个代理类,用于实现program类的代理函数,不允许实例化.
//    这些代理函数主要用于帮助基类创建,拼接,编译Cg程序.
// 作者:Sun Che
// 时间:20090601
//----------------------------------------------------------------------------
class SE_RENDERER_API DX9Program : public Program
{
    SE_DECLARE_INITIALIZE;

public:
    // 用于创建一个shader program对象并填充其数据.
    static bool OnLoadProgram(Renderer* pRenderer, const String& rProgramName, 
        Program* pProgram, Program::ProgramType eType, 
        InterfaceDescriptor* pInterfaceDesc);
    static bool RecursParams(CGparameter hCgParam, Program* pProgram);
    static bool ParseParam(CGparameter hCgParam, Program* pProgram);

    // 用于释放shader program自定义数据.
    static void OnReleaseUserData(void* pUserData);

    // 用于创建lighting effect所需shader程序.
    static void OnConfigureLighting(LightingEffect* pLEffect);

private:
    DX9Program(void);
};

}

#endif
