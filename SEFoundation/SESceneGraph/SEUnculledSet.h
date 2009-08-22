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

#ifndef Swing_UnculledSet_H
#define Swing_UnculledSet_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEUnculledObject.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:可视听对象集合类
// 说明:
// 作者:Sun Che
// 时间:20080707
//----------------------------------------------------------------------------
class SE_FOUNDATION_API UnculledSet
{
public:
    UnculledSet(int iMaxCount = 0, int iGrowBy = 0);
    virtual ~UnculledSet(void);

    inline int GetCount(void) const;
    inline UnculledObject* GetUnculled(void);
    inline UnculledObject& GetUnculled(int i);

    // 根据输入数据创建一个UnculledObject并放在可见对象集合尾部
    void Insert(Spatial* pObject, Effect* pGlobalEffect);
    // 并不释放已分配数据
    inline void Clear(void);
    void Resize(int iMaxCount, int iGrowBy);

private:
    enum
    {
        US_DEFAULT_MAX_COUNT = 32,
        US_DEFAULT_GROWBY = 32,
    };

    int m_iMaxCount, m_iGrowBy, m_iCount;
    UnculledObject* m_pUnculled;
};

#include "SEUnculledSet.inl"

}

#endif
