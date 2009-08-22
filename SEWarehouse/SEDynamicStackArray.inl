//----------------------------------------------------------------------------
template<class Type>
inline DynamicStackArray<Type>::DynamicStackArray() 
    : DynamicArray<Type>() 
{
    m_iUsed = 0;
    m_iAllocationStep = 16;

    DynamicArray<Type>::Lock();
}
//----------------------------------------------------------------------------
template<class Type>
inline DynamicStackArray<Type>::~DynamicStackArray() 
{
    DynamicArray<Type>::Unlock();
}
//----------------------------------------------------------------------------
template<class Type>
inline void DynamicStackArray<Type>::Clear() 
{
    DynamicArray<Type>::Clear(); 
    m_iUsed = 0; 
}
//----------------------------------------------------------------------------
template<class Type>
inline void DynamicStackArray<Type>::SetAllocationStep(INDEX iStep) 
{
    ASSERT( iStep > 0 );

    m_iAllocationStep = iStep;
}
//----------------------------------------------------------------------------
template<class Type>
inline Type& DynamicStackArray<Type>::Push() 
{
    // 如果数组内存用完了,则动态增长
    if( DynamicArray<Type>::GetCount() - m_iUsed < 1 ) 
    {
        DynamicArray<Type>::Append(m_iAllocationStep);
    }
  
    // 稍后应压入新对象
    m_iUsed++;
	
    ASSERT( m_iUsed <= DynamicArray<Type>::GetCount() );
	
    return DynamicArray<Type>::operator[](m_iUsed - 1);
}
//----------------------------------------------------------------------------
template<class Type>
inline Type* DynamicStackArray<Type>::Push(INDEX iCount) 
{
    while( DynamicArray<Type>::GetCount() - m_iUsed < iCount ) 
    {
        DynamicArray<Type>::Append(m_iAllocationStep);
    }

    // 稍后应压入若干新对象
    m_iUsed += iCount;
	
    ASSERT( m_iUsed <= DynamicArray<Type>::GetCount() );
	
    return &DynamicArray<Type>::operator[](m_iUsed - iCount);
}
//----------------------------------------------------------------------------
template<class Type>
inline void DynamicStackArray<Type>::PopAll() 
{
    if( m_BlocksList.IsEmpty() || &m_BlocksList.GetHead() == &m_BlocksList.GetTail() ) 
    {
        m_iUsed = 0;
    } 
    else
    {
        // 记住之前分配过的内存大小
        INDEX iUsedBefore = DynamicArray<Type>::GetCount();
        // 释放掉之前分配的所有内存
        DynamicArray<Type>::Clear();
        // 重新分配之前大小的一个内存块
        DynamicArray<Type>::Append(iUsedBefore);
        m_iUsed = 0;
    }
}
//----------------------------------------------------------------------------
template<class Type>
inline Type& DynamicStackArray<Type>::operator[](INDEX iObject) 
{
    ASSERT( this != 0 );
    ASSERT( i < m_iUsed );     // 检查是否越界

    return DynamicArray<Type>::operator[](iObject);
}
//----------------------------------------------------------------------------
template<class Type>
inline const Type& DynamicStackArray<Type>::operator[](INDEX iObject) const 
{
    ASSERT( this != 0 );
    ASSERT( i < m_iUsed );     // 检查是否越界

    return DynamicArray<Type>::operator[](iObject);
}
//----------------------------------------------------------------------------