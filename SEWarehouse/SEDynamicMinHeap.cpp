#ifndef Swing_DynamicMinHeap_CPP
#define Swing_DynamicMinHeap_CPP

#include "SEDynamicMinHeap.h"
#include "SEDynamicArray.cpp"

namespace Swing
{

//----------------------------------------------------------------------------
template <class Type>
DynamicMinHeap<Type>::DynamicMinHeap()
{
    m_iUsed = 0;
    m_iAllocationStep = 16;
    
    UserCompareFunction = 0;
    UserOperationFunction = 0;

	m_HeapArray.Lock();
}
//----------------------------------------------------------------------------
template <class Type>
DynamicMinHeap<Type>::DynamicMinHeap(DynamicArray<Type>& rDA, int iUsed, 
                                     int (*pCompare)(const void* p0, const void* p1),
                                     void (*pOperation)(void* pObject, int iIndex))
{
    ASSERT( rDA.GetCount() >= iUsed );

    m_HeapArray.MoveArray(rDA);

    m_iUsed = iUsed;
    m_iAllocationStep = 16;
    
    UserCompareFunction = pCompare;
    UserOperationFunction = pOperation;

    if( UserOperationFunction )
        for( int i = 0; i < m_iUsed; i++ )
            (*UserOperationFunction)((void*)m_HeapArray.Pointer(i), i);

    // 获取最后一个非叶子节点的位置
    int CurrentPos = (m_iUsed - 2) >> 1;
    while( CurrentPos >= 0 )
    {
        AdjustDownward(CurrentPos, m_iUsed - 1);
        CurrentPos--;
    }

	m_HeapArray.Lock();
}
//----------------------------------------------------------------------------
template <class Type>
DynamicMinHeap<Type>::~DynamicMinHeap()
{ 
    m_HeapArray.Clear();

	m_HeapArray.Unlock();
}
//----------------------------------------------------------------------------
template <class Type>
DynamicMinHeap<Type>& DynamicMinHeap<Type>::operator=(const DynamicMinHeap<Type>& rOther)
{
    m_HeapArray = rOther.m_HeapArray;
    m_iUsed = rOther.m_iUsed;

    return *this;
}
//----------------------------------------------------------------------------
template <class Type>
void DynamicMinHeap<Type>::AdjustDownward(int iStart, int iEnd)
{
    int i = iStart, j = (i << 1) + 1;
    // 暂存当前被移动的对象
    Type TempObject = m_HeapArray[i];

    while( j <= iEnd )
    {
        // 指向两孩子中较小者
		if( j < iEnd && 
            CompareFunction((void*)m_HeapArray.Pointer(j), (void*)m_HeapArray.Pointer(j + 1)) > 0 )
			j++;

        // 如果不需要调整
        if( CompareFunction((void*)&TempObject, (void*)m_HeapArray.Pointer(j)) <= 0 )
            break;
        else
        {
            m_HeapArray[i] = m_HeapArray[j];
            if( UserOperationFunction )
                (*UserOperationFunction)((void*)m_HeapArray.Pointer(i), i);

            i = j;
            j = (j << 1) + 1;
        }
    }

    m_HeapArray[i] = TempObject;
    if( UserOperationFunction )
        (*UserOperationFunction)((void*)m_HeapArray.Pointer(i), i);
}
//----------------------------------------------------------------------------
template <class Type>
void DynamicMinHeap<Type>::AdjustUpward(int iStart)
{
    int j = iStart, i = (j - 1) >> 1;
    // 暂存当前被移动的对象
    Type TempObject = m_HeapArray[j];

    while( j > 0 )
    {
        // 如果不需要调整
        if( CompareFunction((void*)m_HeapArray.Pointer(i), (void*)&TempObject) <= 0 )
            break;
        else
        {
            m_HeapArray[j] = m_HeapArray[i];
            if( UserOperationFunction )
                (*UserOperationFunction)((void*)m_HeapArray.Pointer(j), j);

            j = i;
            i = (i - 1) >> 1;
        }
    }

    m_HeapArray[j] = TempObject;
    if( UserOperationFunction )
        (*UserOperationFunction)((void*)m_HeapArray.Pointer(j), j);
}
//----------------------------------------------------------------------------
template <class Type>
int DynamicMinHeap<Type>::CompareFunction(const void* p1, const void* p2)
{
    ASSERT( p1 && p2 );

    if( UserCompareFunction )
        return (*UserCompareFunction)(p1, p2);

    return memcmp(p1, p2, sizeof(Type));
}
//----------------------------------------------------------------------------

}

#endif