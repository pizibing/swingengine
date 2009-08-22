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

#ifndef Swing_Bindable_H
#define Swing_Bindable_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SESystem.h"
#include "SEAttributes.h"
#include "SERenderer.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:资源ID类
// 说明:
// 作者:Sun Che
// 时间:20080320
//----------------------------------------------------------------------------
class SE_FOUNDATION_API ResourceIdentifier
{
public:
    // 虚基类,注意析构函数不是虚函数,
    // 因此被派生后,基类析构行为是未定义的,
    // 由于此类没有任何数据成员,也没有虚函数,
    // 从而避免了虚函数表指针的存在,
    // 这将允许派生类VBufferIdentifier首先存储自己的成员变量,
    // 并且安全的进行如下所示的类型转换操作:
    //
    //   class VBufferIdentifier : public ResourceIdentifier
    //   {
    //   public:  Attributes IAttributes;
    //   }
    //   VBufferIdentifier* pID = <some identifier>;
    //   Attributes& rIAttributes = *(Attributes*)pID;

    ~ResourceIdentifier(void){}

protected:
    ResourceIdentifier(void){}
};

//----------------------------------------------------------------------------
// 名称:资源绑定信息类
// 说明:所有需要载入显存的资源,如VB,IB,shader程序,texture的基类.
// 作者:Sun Che
// 时间:20080320
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Bindable
{
public:
    Bindable(void);
    ~Bindable(void);

    // 当资源在VRAM中有唯一表示时使用(除了vertex buffers之外的所有资源)
    ResourceIdentifier* GetIdentifier(Renderer* pUser) const;

    // 当资源在VRAM中有多个表示时使用(vertex buffers)
    int GetInfoCount(void) const;
    ResourceIdentifier* GetIdentifier(int i, Renderer* pUser) const;

    void Release(void);

private:
    friend class Renderer;

    void OnLoad(Renderer* pUser, Renderer::ReleaseFunction oRelease,
        ResourceIdentifier* pID);

    void OnRelease(Renderer* pUser, ResourceIdentifier* pID);

    struct Info
    {
        // 资源所绑定的renderer
        Renderer* User;

        // 释放资源时所需的renderer释放函数
        Renderer::ReleaseFunction Release;

        // 资源在该renderer上的ID
        ResourceIdentifier* ID;
    };

    // 可以同时绑定给多个renderer,主要用于绑定一个renderer的多个不同实例
    std::vector<Info> m_InfoArray;
};

}

#endif
