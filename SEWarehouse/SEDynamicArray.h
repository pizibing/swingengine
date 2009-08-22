#ifndef Swing_DynamicArray_H
#define Swing_DynamicArray_H

#include "SESystem.h"
#include "SELists.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:动态数组内存块结构
// 说明:参考自Serious Engine
//      每次动态数组增长时,创建这个结构的新实例节点
// 作者:Sun Che
// 时间:20070608
//----------------------------------------------------------------------------
struct DABlockInfo 
{
    // 负责追踪维护当前list
    ListNode NestedListNode;
    // 指向新申请的内存空间首地址
    void*    BlockMemory;
};

//----------------------------------------------------------------------------
// 名称:动态数组类
// 说明:参考自Serious Engine
// 作者:Sun Che
// 时间:20070608
//----------------------------------------------------------------------------
template<class Type>
class DynamicArray 
{
public:
    DynamicArray(void);
    DynamicArray(DynamicArray<Type>& rOriginal);
    virtual ~DynamicArray(void);

public:
    // 动态数组增长,一个大小为iCount*sizeof(Type)的新数据块被连接进来
    Type* Append(INDEX iCount = 1);
    // 试图删除一个元素,但不释放其数据块内存
    void  Delete(Type* pObject);
    void  Clear(void);

    // 数组成员访问
    Type* Pointer(INDEX iObject);
    const Type* Pointer(INDEX iObject) const;
    inline Type& operator [] (INDEX iObject);
    inline const Type& operator [] (INDEX iObject) const;

    DynamicArray<Type>& operator = (DynamicArray<Type>& rOriginal);

    void MoveArray(DynamicArray<Type>& rOther);

    void Lock(void);
    void Unlock(void);
    INDEX Index(Type* pObject);
    INDEX GetCount(void) const;

protected:
    // 实际动态分配的对象内存空间是不连续的,为了实现random access,
    // 使用连续分配的指针内存空间间接访问m_BlocksList中的对象
    // 每当数组动态增长,新的内存被分配,指针空间也跟随增长,
    // 每个新加入的指针都指向新分配的内存block中自己对应的Type大小的内存
    ListHead m_BlocksList;  // 已分配内存的链表
    Type**   m_Pointers;    // 对象指针数组
    INDEX    m_iCount;      // 数组大小

    // 为支持多线程,当前数组正在被访问的加锁计数
#if CHECKARRAYLOCKING
    INDEX m_iLockCt;
#endif

    // 指针数组增长iCount
	void GrowPointers(INDEX iCount);
    // 指针数组缩减iCount
	void ShrinkPointers(INDEX iCount);
    // 分配一个新内存块
    Type* AllocBlock(INDEX iCount);
    // 查找指定对象是否在当前数组中,时间复杂度O(n)
    INDEX GetIndex(Type* pMember);
};

//----------------------------------------------------------------------------
// 名称:动态数组迭代器类
// 说明:参考自Serious Engine
// 作者:Sun Che
// 时间:20070608
//----------------------------------------------------------------------------
template<class Type>
class DynamicArrayIterator 
{
public:
	inline DynamicArrayIterator(DynamicArray<Type>& rDA);
	inline ~DynamicArrayIterator(void);

public:
    inline void MoveToNext(void);
    inline bool IsPastEnd(void);

    Type& Current(void) { return *m_rDynamicArray.Pointer(m_iIndex); }
    Type& operator * (void) { return *m_rDynamicArray.Pointer(m_iIndex); }
    operator Type * (void) { return m_rDynamicArray.Pointer(m_iIndex); }
    Type* operator -> (void) { return m_rDynamicArray.Pointer(m_iIndex); }

private:
	INDEX               m_iIndex;          // 当前对象索引
	DynamicArray<Type>& m_rDynamicArray;   // 被迭代的数组的引用
};

#include "SEDynamicArray.inl"

}

#endif

