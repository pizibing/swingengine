#ifndef Swing_DynamicArray_CPP
#define Swing_DynamicArray_CPP

#include "SEDynamicArray.h"

namespace Swing
{

// 迭代整个动态数组
// 注意:在进行动态数组元素添加/删除操作前,这个宏定义的迭代器必须先被destroy
#define FOREACHINDYNAMICARRAY(array, type, iter) \
  for( DynamicArrayIterator<type> iter(array); !iter.IsPastEnd(); iter.MoveToNext() )

//----------------------------------------------------------------------------
template<class Type>
DynamicArray<Type>::DynamicArray(void) 
{
#if CHECKARRAYLOCKING
    m_iLockCt = 0;
#endif
	// 初始数组为空
    m_Pointers = 0;
    m_iCount = 0;
}
//----------------------------------------------------------------------------
template<class Type>
DynamicArray<Type>::DynamicArray(DynamicArray<Type>& rOriginal)
{
#if CHECKARRAYLOCKING
    m_iLockCt = 0;
#endif
    // 初始数组为空
    m_Pointers = 0;
    m_iCount = 0;

    (*this) = rOriginal;
}
//----------------------------------------------------------------------------
template<class Type>
DynamicArray<Type>::~DynamicArray(void) 
{
    Clear();
}
//----------------------------------------------------------------------------
template<class Type>
void DynamicArray<Type>::Clear(void) 
{
    ASSERT( this != 0 );
  
    // 如果分配了指针数组及其指向的数据块
  
    if( m_iCount != 0 ) 
    {
        // Serious Engine:注意:我们必须显式的释放对象,因为删除数组不会调用对象析构函数
        // 对于所有数据指针
        //for( INDEX iPointer = 0; iPointer < m_iCount; iPointer++ ) 
        //{
        //    // destroy其指向的对象
        //    ::Clear(*m_Pointers[iPointer]);
        //}

        // 释放指针数组
        free((char*)m_Pointers);

        m_Pointers = 0;
        m_iCount = 0;
    } 
    else 
    {
        ASSERT( m_Pointers == 0 );
        // 没有什么可释放的
    }

    // 释放所有已创建的内存块
    FORDELETELIST(DABlockInfo, NestedListNode, m_BlocksList, itBlock) 
    {
		// 释放当前block info节点所带的内存块(Serious Engine:这并不会调用块内对象的析构函数 - 正如上面所说的!)
        delete[] (Type*)itBlock->BlockMemory;
		// 释放当前block info
        delete &itBlock.Current();
    }
}
//----------------------------------------------------------------------------
template<class Type>
void DynamicArray<Type>::GrowPointers(INDEX iCount) 
{
    ASSERT( this != 0 && iCount > 0 );
  
    if( m_iCount == 0 ) 
    {
        // 如果还没有创建指针数组
        ASSERT( m_Pointers == 0 );
		// 创建指针数组
        m_iCount = iCount;
        m_Pointers = (Type**)malloc(m_iCount * sizeof(Type*));
    } 
    else 
    {
        // 指针数组增长
        m_iCount += iCount;
        m_Pointers = (Type**)realloc((void*)m_Pointers, m_iCount * sizeof(Type*));
    }
}
//----------------------------------------------------------------------------
template<class Type>
void DynamicArray<Type>::ShrinkPointers(INDEX iCount) 
{
    ASSERT( this != 0 && iCount > 0 );
    ASSERT( m_Pointers != 0);

    m_iCount -= iCount;
    ASSERT( m_iCount >= 0 );

    if( m_iCount == 0 ) 
	{
        // 如果缩减为0,则释放指针数组
        free(m_Pointers);
        m_Pointers = 0;
    } 
    else 
    {
        // 指针数组缩减
        m_Pointers = (Type**)realloc((void*)m_Pointers, m_iCount * sizeof(Type*));
    }
}
//----------------------------------------------------------------------------
template<class Type>
Type* DynamicArray<Type>::AllocBlock(INDEX iCount) 
{
    ASSERT( this != 0 && iCount > 0 );
    Type* pBlock;
    DABlockInfo* pBlockInfo;

    // 分配内存数据块并构造对象(+1 for cache-prefetch opt)
    pBlock = new Type[iCount + 1];
    // 分配块信息
    pBlockInfo = new DABlockInfo;
    // 把块信息加入block list
    m_BlocksList.AddTail(pBlockInfo->NestedListNode);
    // 块信息指向其内存数据块
    pBlockInfo->BlockMemory = pBlock;

    return pBlock;
}
//----------------------------------------------------------------------------
template<class Type>
Type* DynamicArray<Type>::Append(INDEX iCount) 
{
    ASSERT( this != NULL && iCount >= 0 );

    if( iCount == 0 ) 
    {
        return 0;
    }

    Type* pBlock;
    INDEX iOldCount = m_iCount;

    // 增长指针数组
    GrowPointers(iCount);
    // 分配新内存块
    pBlock = AllocBlock(iCount);
    // 让新增的指针成员逐个指向其数据区
    for( INDEX iNewMember = 0; iNewMember < iCount; iNewMember++ ) 
    {
        m_Pointers[iOldCount + iNewMember] = pBlock + iNewMember;
    }

    return pBlock;
}
//----------------------------------------------------------------------------
template<class Type>
void DynamicArray<Type>::Delete(Type* pMember) 
{
    ASSERT( this != 0 );

#if CHECKARRAYLOCKING
    ASSERT( m_iLockCt == 0 );
#endif

    // 这里会调用Type的Clear函数
    ::Clear(*pMember);

    INDEX iMember = GetIndex(pMember);
    // 把数组最后一个元素放过来
    m_Pointers[iMember] = m_Pointers[m_iCount-1];
    // 指针数组缩减1
    ShrinkPointers(1);
    // 不释放内存
    //!!!!
}
//----------------------------------------------------------------------------
template<class Type>
Type* DynamicArray<Type>::Pointer(INDEX iMember) 
{
    ASSERT( this != 0 );
    // 防止数组越界
    ASSERT( iMember >= 0 && iMember < m_iCount );

#if CHECKARRAYLOCKING
    ASSERT( m_iLockCt > 0 );
#endif

    return m_Pointers[iMember];
}
//----------------------------------------------------------------------------
template<class Type>
const Type* DynamicArray<Type>::Pointer(INDEX iMember) const 
{
    ASSERT( this != 0 );
    // 防止数组越界
    ASSERT( iMember >= 0 && iMember < m_iCount );

#if CHECKARRAYLOCKING
	ASSERT( m_iLockCt > 0 );
#endif

    return m_Pointers[iMember];
}
//----------------------------------------------------------------------------
template<class Type>
void DynamicArray<Type>::Lock() 
{
    ASSERT( this != 0 );

#if CHECKARRAYLOCKING
    ASSERT( m_iLockCt >= 0 );
    // 增加加锁计数
    m_iLockCt++;
#endif
}
//----------------------------------------------------------------------------
template<class Type>
void DynamicArray<Type>::Unlock() 
{
    ASSERT( this != 0 );

#if CHECKARRAYLOCKING
    // 减少加锁计数
    m_iLockCt--;
    ASSERT( m_iLockCt >= 0 );
#endif
}
//----------------------------------------------------------------------------
template<class Type>
INDEX DynamicArray<Type>::Index(Type* pMember) 
{
    ASSERT( this != 0 );

#if CHECKARRAYLOCKING
    ASSERT( m_iLockCt > 0 );
#endif

    return GetIndex(pMember);
}
//----------------------------------------------------------------------------
template<class Type>
INDEX DynamicArray<Type>::GetIndex(Type* pMember) 
{
    ASSERT( this != 0 );
    // 很慢的查找
    for( INDEX iMember = 0; iMember < m_iCount; iMember++ ) 
    {
        if( m_Pointers[iMember] == pMember ) 
        {
            return iMember;
        }
    }
	
    ASSERTALWAYS("DynamicArray<>::GetIndex(): Not a member of this array!");

    return 0;
}
//----------------------------------------------------------------------------
template<class Type>
INDEX DynamicArray<Type>::GetCount(void) const 
{
    ASSERT( this != 0 );

    return m_iCount;
}
//----------------------------------------------------------------------------
template<class Type>
DynamicArray<Type>& DynamicArray<Type>::operator=(DynamicArray<Type>& rOriginal)
{
    ASSERT( this!= 0 );
    ASSERT(&rOriginal != 0 );
    ASSERT( this!= &rOriginal );
    // 清除之前的内容
    Clear();

    INDEX ctOriginal = rOriginal.GetCount();
    if( ctOriginal == 0 ) 
	{
        return *this;
	}

    // 创建所需内存
    Type* pNew = Append(ctOriginal);

    // 复制数据
    rOriginal.Lock();
    for( INDEX iNew = 0; iNew < ctOriginal; iNew++ ) 
    {
        pNew[iNew] = rOriginal[iNew];
    }
    rOriginal.Unlock();

    return *this;
}
//----------------------------------------------------------------------------
template<class Type>
void DynamicArray<Type>::MoveArray(DynamicArray<Type>& rOther)
{
    ASSERT( this != 0 && &rOther != 0 );

#if CHECKARRAYLOCKING
    ASSERT( m_iLockCt == 0 && rOther.m_iLockCt == 0 );
#endif

    // 没有数据
    if( rOther.m_iCount == 0 ) 
    {
        return;
    }

    INDEX iOldCount = m_iCount;
	GrowPointers(rOther.m_iCount);

    // 其指针数组全部内容先复制过来
    for( INDEX iOtherPointer = 0; iOtherPointer < rOther.m_iCount; iOtherPointer++ ) 
    {
        // 放在当前指针数组内容之后
        m_Pointers[iOldCount + iOtherPointer] = rOther.m_Pointers[iOtherPointer];
    }
    
    // 释放其指针数组
    rOther.ShrinkPointers(rOther.m_iCount);
	// 最后把其block list连接过来
    m_BlocksList.MoveList(rOther.m_BlocksList);
}
//----------------------------------------------------------------------------

}

#endif

