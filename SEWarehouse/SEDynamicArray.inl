//----------------------------------------------------------------------------
template<class Type>
inline Type& DynamicArray<Type>::operator[](INDEX iObject) 
{
    return *Pointer(iObject); 
}
//----------------------------------------------------------------------------
template<class Type>
inline const Type& DynamicArray<Type>::operator[](INDEX iObject) const 
{
    return *Pointer(iObject); 
}
//----------------------------------------------------------------------------
template<class Type>
inline DynamicArrayIterator<Type>::DynamicArrayIterator(DynamicArray<Type>& rDa) 
    : m_rDynamicArray(rDa) 
{
    m_rDynamicArray.Lock();
    m_iIndex = 0;
}
//----------------------------------------------------------------------------
template<class Type>
inline DynamicArrayIterator<Type>::~DynamicArrayIterator() 
{
    m_rDynamicArray.Unlock();
    m_iIndex = -1;
}
//----------------------------------------------------------------------------
template<class Type>
inline void DynamicArrayIterator<Type>::MoveToNext() 
{
    ASSERT( this != 0 );
	
    m_iIndex++;
}
//----------------------------------------------------------------------------
template<class Type>
inline bool DynamicArrayIterator<Type>::IsPastEnd() 
{
    ASSERT( this != 0 );

	return m_iIndex >= m_rDynamicArray.GetCount();
}
//----------------------------------------------------------------------------