//----------------------------------------------------------------------------
template<class Type>
inline void StaticArray<Type>::operator=(const StaticArray<Type>& rOriginal) 
{
    CopyArray(rOriginal);
}
//----------------------------------------------------------------------------
template<class Type>
inline void StaticArray<Type>::Clear() 
{
    if( m_iCount != 0 ) 
        Delete(); 
}
//----------------------------------------------------------------------------
template<class Type>
inline void StaticArray<Type>::Append(INDEX iCount) 
{
    ASSERT( this != 0 && iCount >= 0 );

    if( iCount == 0 ) 
    {
        return;
	}

    ASSERT( m_iCount == 0 && m_pArray == 0 );

    m_iCount = iCount;
    m_pArray = new Type[iCount + 1]; //(+1 for cache-prefetch opt)
}
//----------------------------------------------------------------------------
template<class Type>
inline void StaticArray<Type>::Expand(INDEX iNewCount)
{
    // 确保新尺寸大于现有尺寸才有意义
    ASSERT( this != 0 && iNewCount > m_iCount );

    // 如果还没有分配内存
    if( m_iCount == 0 ) 
    {
        Append(iNewCount);
        return;
    } 
    else 
    {
        ASSERT( m_iCount != 0 && m_Array != 0 );

        // 分配新尺寸的内存
        Type* pNewArray = new Type[iNewCount + 1]; //(+1 for cache-prefetch opt)
        // 复制现有对象数据到新分配的内存中
        for( INDEX iOld = 0; iOld < m_iCount; iOld++ ) 
        {
            pNewArray[iOld] = m_pArray[iOld];
        }
        // 释放原来的内存
        delete[] m_pArray;
        // 指向新内存
        m_iCount = iNewCount;
        m_pArray = pNewArray;
    }
}
//----------------------------------------------------------------------------
template<class Type>
inline void StaticArray<Type>::Delete() 
{
    // 确保有对象
    ASSERT( this != 0 && m_iCount != 0 && m_pArray != 0 );

    delete[] m_pArray;
    m_iCount = 0;
    m_pArray = 0;
}
//----------------------------------------------------------------------------
template<class Type>
inline Type& StaticArray<Type>::operator[](INDEX iObject) 
{
    // 检查越界访问
    ASSERT( this != 0 && iObject >= 0 && iObject < m_iCount);

    return m_pArray[iObject];
}
//----------------------------------------------------------------------------
template<class Type>
inline const Type& StaticArray<Type>::operator[](INDEX iObject) const 
{
    // 检查越界访问
    ASSERT( this! = 0 && iObject >= 0 && iObject < m_iCount );

    return m_pArray[iObject];
}
//----------------------------------------------------------------------------
template<class Type>
inline StaticArrayIterator<Type>::StaticArrayIterator(StaticArray<Type>& rSA) 
    : m_rStaticArray(rSA)
{
    m_iIndex = 0;
}
//----------------------------------------------------------------------------
template<class Type>
inline StaticArrayIterator<Type>::~StaticArrayIterator()
{
    m_iIndex = -1;
}
//----------------------------------------------------------------------------
template<class Type>
inline void StaticArrayIterator<Type>::MoveToNext()
{
    ASSERT( this != 0 );
  
    m_iIndex++;
}
//----------------------------------------------------------------------------
template<class Type>
inline bool StaticArrayIterator<Type>::IsPastEnd()
{
    ASSERT( this != 0 );
  
    return m_iIndex >= m_rStaticArray.m_iCount;
}
//----------------------------------------------------------------------------