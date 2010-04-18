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

#ifndef Swing_AudioBindable_H
#define Swing_AudioBindable_H

#include "SEAudioLIB.h"
#include "SEAudioRenderer.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 说明:
// 作者:Sun Che
// 时间:20090619
//----------------------------------------------------------------------------
class SE_AUDIO_API SEAudioResourceIdentifier
{
public:
    // 虚基类,注意析构函数不是虚函数,
    // 因此被派生后,基类析构行为是未定义的,
    // 由于此类没有任何数据成员,也没有虚函数,
    // 从而避免了虚函数表指针的存在,
    // 这将允许派生类首先存储自己的成员变量,
    // 并且安全的进行如下所示的类型转换操作:
    //
    //   class SubClassResourceIdentifier : public SEAudioResourceIdentifier
    //   {
    //   public:  DataType SubClassMember;
    //   }
    //   SubClassResourceIdentifier* pID = <some identifier>;
    //   Type& rSubClassMember = *(DataType*)pID;

    ~SEAudioResourceIdentifier(void){}

protected:
    SEAudioResourceIdentifier(void){}
};

//----------------------------------------------------------------------------
// 名称:音频资源绑定信息类
// 说明:
// 作者:Sun Che
// 时间:20090619
//----------------------------------------------------------------------------
class SE_AUDIO_API SEAudioBindable
{
public:
    SEAudioBindable(void);
    ~SEAudioBindable(void);

    // 当资源在音频设备中有唯一表示时使用.
    SEAudioResourceIdentifier* GetIdentifier(SEAudioRenderer* pUser) const;

    // 当资源在音频设备中有多个表示时使用.
    int GetInfoCount(void) const;
    SEAudioResourceIdentifier* GetIdentifier(int i, SEAudioRenderer* pUser) 
        const;

    void Release(void);

    // 用于音频资源在世界体系下的空间姿态以及其他相关音频参数的动态更新.
    // 由SESound对象在UpdateWorldDate函数中调用.
    void UpdateParams(void);

private:
    friend class SEAudioRenderer;

    void OnLoad(SEAudioRenderer* pUser, SEAudioRenderer::ReleaseFunction 
        oRelease, SEAudioRenderer::UpdateParamsFunction oUpdateParams,
        SEAudioResourceIdentifier* pID);

    void OnRelease(SEAudioRenderer* pUser, SEAudioResourceIdentifier* pID);

    struct Info
    {
        // 资源所绑定的audio renderer.
        SEAudioRenderer* User;

        // 释放资源时所需的audio renderer释放函数.
        SEAudioRenderer::ReleaseFunction Release;
        // 更新资源参数时所需的audio renderer更新函数.
        SEAudioRenderer::UpdateParamsFunction UpdateParams;

        // 资源在该audio renderer上的ID.
        SEAudioResourceIdentifier* ID;
    };

    // 可以同时绑定给多个audio renderer,
    // 主要用于绑定一个audio renderer的多个不同实例.
    std::vector<Info> m_InfoArray;
};

}

#endif
