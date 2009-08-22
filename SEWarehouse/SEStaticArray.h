#ifndef Swing_StaticArray_H
#define Swing_StaticArray_H

#include "SESystem.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:静态数组类
// 说明:参考自Serious Engine
// 作者:Sun Che
// 时间:20070618
//----------------------------------------------------------------------------
template<class Type>
class StaticArray 
{
public:
    StaticArray(void);
    virtual ~StaticArray(void);

public:
    void operator = (const StaticArray<Type>& rOriginal);

    inline void Append(INDEX iCount);
    // 扩大尺寸但保持旧有对象
    inline void Expand(INDEX iNewCount);
    // 释放内存,恢复初始空状态
    inline void Delete(void);
    // 调用Delete释放内存,恢复初始空状态
    inline void Clear(void);

    inline Type& operator [] (INDEX iObject);
    inline const Type& operator [] (INDEX iObject) const;
    
    INDEX GetCount(void) const;
    INDEX Index(Type* pObject);

    // 复制另一个数组的所有数据过来
    void CopyArray(const StaticArray<Type>& rOriginal);
    // 把另一个数组的数据指针直接接过来
    void MoveArray(StaticArray<Type>& rOther);

public:
	INDEX m_iCount;
	Type* m_pArray;
};

//----------------------------------------------------------------------------
// 名称:静态数组迭代器类
// 说明:参考自Serious Engine
// 作者:Sun Che
// 时间:20070618
//----------------------------------------------------------------------------
template<class Type>
class StaticArrayIterator
{
public:
    inline StaticArrayIterator(StaticArray<Type>& rSA);
    inline ~StaticArrayIterator(void);

public:
    // 只能向后迭代
    inline void MoveToNext(void);
    inline bool IsPastEnd(void);

    // 获取当前对象
    Type& Current(void) { return m_rStaticArray[m_iIndex]; }
    Type& operator * (void) { return m_rStaticArray[m_iIndex]; }
    operator Type* (void) { return &m_rStaticArray[m_iIndex]; }
    Type* operator -> (void) { return &m_rStaticArray[m_iIndex]; }

private:
    INDEX m_iIndex;                      // 当前对象索引
    StaticArray<Type>& m_rStaticArray;   // 被迭代的静态数组的引用
};

#include "SEStaticArray.inl"

#define FOREACHINSTATICARRAY(array, type, iter) \
  for(StaticArrayIterator<type> iter(array); !iter.IsPastEnd(); iter.MoveToNext() )

}

#endif

