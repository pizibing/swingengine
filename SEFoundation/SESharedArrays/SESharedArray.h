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

#ifndef Swing_SharedArray_H
#define Swing_SharedArray_H

#include "SEPlatforms.h"
#include "SEObject.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:共享数组类
// 说明:
// 作者:Sun Che
// 时间:20080315
//----------------------------------------------------------------------------
template <class Type>
class SESharedArray : public SEObject
{
    SE_DECLARE_TEMPLATE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_TEMPLATE_STREAM;

public:
    SESharedArray(int iCount = 0, Type* pArray = 0);
    SESharedArray(const SESharedArray& rShared);
    virtual ~SESharedArray(void);

    SESharedArray& operator = (const SESharedArray& rShared);

    int GetCount(void) const;
    Type* GetData(void) const;

    operator const Type* (void) const;
    operator Type* (void);
    const Type& operator [] (int i) const;
    Type& operator [] (int i);

    // 这个函数不会造成数组重新分配大小,意图是允许数组部分数据处于激活状态从而被访问,
    // 调用者有责任记住该数组的实际大小
    void SetActiveCount(int iActiveCount);

protected:
    int m_iCount;
    Type* m_pArray;
};

#include "SESharedArray.inl"

}

#endif
