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

#ifndef Swing_UserConstant_H
#define Swing_UserConstant_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SESystem.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:用户定义常量类
// 说明:shader程序中的全局数值量,
//      主要指用户自定义的各种数据
// 作者:Sun Che
// 时间:20080623
//----------------------------------------------------------------------------
class SE_FOUNDATION_API UserConstant
{
public:
    UserConstant(const std::string& rName, void* pID, int iDataCount);
    UserConstant(const UserConstant& rUC);
    ~UserConstant(void);

    // 成员访问,renderer使用他们给图形API传递数据
    inline const std::string& GetName(void) const;
    inline void* GetID(void) const;
    inline int GetDataCount(void) const;
    inline float* GetData(void) const;

    // 用户可以根据需要,任意指定user constant的数据存储位置.
    // 默认情况下,所有user constant对象指向一个共享的静态数据区,
    // 从而确保渲染器在设置shader constant时的指针数据安全性.
    void SetDataSource(float* pData);

    bool Active; // default: true

    // 如果用户实现了自定义数据,则应实现自定义数据的释放过程.
    typedef void (*ReleaseID)(void*);
    static ReleaseID OnReleaseID;

    // 如果用户实现了自定义数据,则应实现自定义数据的拷贝过程.
    // 从而允许拷贝构造函数正确拷贝用户自定义数据.
    typedef void (*CopyID)(void*, void**);
    static CopyID OnCopyID;

private:
    std::string m_Name;
    void* m_pID;
    int m_iDataCount;
    float* m_pData;  // 应指向用户提供的数据区

    static float ms_afDefaultData[16];
};

#include "SEUserConstant.inl"

}

#endif
