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

#ifndef Swing_HashTable_H
#define Swing_HashTable_H

// TKey必须实现的函数:
//   TKey::TKey()
//   TKey& TKey::operator=(const TKey&)
//   bool TKey::operator==(const TKey&) const
//   bool TKey::operator!=(const TKey&) const
//   TKey::operator unsigned int() const
// 隐式类型转换到unsigned int用来生成哈希表索引,
// 返回值不一定要在哈希表索引范围内,哈希表通过取模运算来映射到合法范围
// TValue必须实现的函数:
//   TValue::TValue()
//   TValue& TValue::operator=(const TValue&)

#include "SESystem.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:哈希表类
// 说明:
// 作者:Sun Che
// 时间:20080308
//----------------------------------------------------------------------------
template <class TKey, class TValue>
class HashTable
{
public:
    HashTable(int iTableSize);
    ~HashTable(void);

    int GetCount(void) const;

    bool Insert(const TKey& rKey, const TValue& rValue);
    TValue* Find(const TKey& rKey) const;
    bool Remove(const TKey& rKey);
    void RemoveAll(void);

    TValue* GetFirst(TKey* pKey) const;
    TValue* GetNext(TKey* pKey) const;

    // 用户自定义的哈希函数
    int (*UserHashFunction)(const TKey&);

private:
    class HTItem
    {
    public:
        TKey m_Key;
        TValue m_Value;
        HTItem* m_pNextHashItem;
    };

    // 默认哈希函数,可被用户函数覆盖
    int HashFunction(const TKey& rKey) const;

    // 哈希表
    int m_iTableSize;
    int m_iCount;
    HTItem** m_ppTable;

    // 迭代所有表项时的辅助变量
    mutable int m_iIndex;
    mutable HTItem* m_pHashItem;
};

#include "SEHashTable.inl"

}

#endif
