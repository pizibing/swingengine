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

#ifndef Swing_StringHashTable_H
#define Swing_StringHashTable_H

#include "SEFoundationLIB.h"
#include "SESystem.h"
#include "SEString.h"

// TValue必须实现的函数:
//   TValue::TValue()
//   TValue& TValue::operator=(const TValue&)
namespace Swing
{

//----------------------------------------------------------------------------
// 名称:string哈希表类
// 说明:
// 作者:Sun Che
// 时间:20080308
//----------------------------------------------------------------------------
template <class TValue>
class StringHashTable
{
public:
    StringHashTable(int iTableSize);
    ~StringHashTable(void);

    int GetCount(void) const;

    bool Insert(const String& rKey, const TValue& rValue);
    TValue* Find(const String& rKey) const;
    bool Remove(const String& rKey);
    void RemoveAll(void);

    TValue* GetFirst(String* pKey) const;
    TValue* GetNext(String* pKey) const;

private:
    class SHTItem
    {
    public:
        SHTItem(void) : m_Key(""){}
		~SHTItem(void){}

	public:
        String m_Key;
        TValue m_Value;
        SHTItem* m_pNextHashItem;
    };

    // 哈希函数
    int HashFunction(const String& rKey) const;

    // 哈希表
    int m_iTableSize;
    int m_iCount;
    SHTItem** m_ppTable;

    // 迭代所有表项时的辅助变量
    mutable int m_iIndex;
    mutable SHTItem* m_pHashItem;
};

#include "SEStringHashTable.inl"

}

#endif
