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

#ifndef Swing_SamplerInformation_H
#define Swing_SamplerInformation_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SESystem.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:采样器信息类
// 说明:shader程序中的采样器
// 作者:Sun Che
// 时间:20080624
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SESamplerInformation
{
public:
    enum Type
    {
        SAMPLER_1D,       // dimension 1
        SAMPLER_2D,       // dimension 2
        SAMPLER_3D,       // dimension 3
        SAMPLER_CUBE,     // dimension 2 (a set of 2D images)
        SAMPLER_PROJ,     // dimension 2
        MAX_SAMPLER_TYPES
    };

    // 采样器名字,采样器类型,对应纹理单元的资源handle都来自于shader程序文件中,
    // 采样器维数由采样器类型推知,
    // 采样器纹理单元的资源handle在装载shader程序时被创建,
    // filter模式和wrap模式由纹理对象所确定并储存在纹理对象中
    //
    // 当有了新的类似fx文件的文件系统后,filter模式和wrap模式将由文件指定,
    // 因此要有新的模块来支持读取模式并提供给纹理对象的功能
    SESamplerInformation(const std::string& rName, Type eType, void* pID);
    SESamplerInformation(const SESamplerInformation& rSI);
    ~SESamplerInformation(void);

    inline const std::string& GetName(void) const;
    inline Type GetType(void) const;
    inline void* GetID(void) const;
    inline int GetDimension(void) const;

    // 如果用户实现了自定义数据,则应实现自定义数据的释放过程.
    typedef void (*ReleaseID)(void*);
    static ReleaseID OnReleaseID;

    // 如果用户实现了自定义数据,则应实现自定义数据的拷贝过程.
    // 从而允许拷贝构造函数正确拷贝用户自定义数据.
    typedef void (*CopyID)(void*, void**);
    static CopyID OnCopyID;

private:
    std::string m_Name;
    Type m_eType;
    int m_iDimension;
    void* m_pID;
};

#include "SESamplerInformation.inl"

}

#endif
