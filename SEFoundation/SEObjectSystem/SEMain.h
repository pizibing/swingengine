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

#ifndef Swing_Main_H
#define Swing_Main_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SESystem.h"
#include "SEMainMCR.h"

namespace Swing
{

class ImageCatalog;
class VertexProgramCatalog;
class GeometryProgramCatalog;
class PixelProgramCatalog;

//----------------------------------------------------------------------------
// 名称:应用程序入口类
// 说明:管理在应用程序启动前和结束后所需的所有操作,
//      一系列pre-main,post-main函数被调用用于创建和释放各个类型所需的全局数据,
//      pre-main,post-main函数由派生类根据各自需求实现
// 作者:Sun Che
// 时间:20080324
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Main
{
public:
    typedef void (*Initializer)(void);  // 定义pre-main函数指针类型
    typedef std::vector<Initializer> InitializerArray; // 定义pre-main函数指针数组类型
    static void AddInitializer(Initializer FuncInitialize);
    static void Initialize(void);

    typedef void (*Terminator)(void); // 定义post-main函数指针类型
    typedef std::vector<Terminator> TerminatorArray; // 定义post-main函数指针数组类型
    static void AddTerminator(Terminator FuncTerminate);
    static void Terminate(void);

private:
    static InitializerArray* ms_pInitializers; // 全局pre-main函数指针数组
    static TerminatorArray* ms_pTerminators; // 全局post-main函数指针数组
    static int ms_iStartObjects;
    static int ms_iFinalObjects;

    static ImageCatalog* ms_pImageCatalog;
    static VertexProgramCatalog* ms_pVertexProgramCatalog;
    static GeometryProgramCatalog* ms_pGeometryProgramCatalog;
    static PixelProgramCatalog* ms_pPixelProgramCatalog;
};

}

#endif
