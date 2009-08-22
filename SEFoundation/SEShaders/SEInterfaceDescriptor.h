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

#ifndef Swing_InterfaceDescriptor_H
#define Swing_InterfaceDescriptor_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SESystem.h"
#include "SEObject.h"
#include "SEString.h"
#include "SEDescriptorItem.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:interface descriptor类
// 说明:帮助Program类装载含有shader interface的程序,使其完成动态拼接并编译.
// 作者:Sun Che
// 时间:20090418
//----------------------------------------------------------------------------
class SE_FOUNDATION_API InterfaceDescriptor : public Object
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    InterfaceDescriptor(void);
    ~InterfaceDescriptor(void);

    // descriptor item访问.
    inline int GetCount(void) const;
    void AttachItem(DescriptorItem* pItem);
    void DetachItem(DescriptorItem* pItem);
    DescriptorItem* GetItem(int i) const;

    // 获取接口描述.
    void GetDescription(String& rDesc) const;

protected:
    std::vector<DescriptorItemPtr> m_DescriptorItems;
};

typedef SmartPointer<InterfaceDescriptor> InterfaceDescriptorPtr;

#include "SEInterfaceDescriptor.inl"

}

#endif
