//----------------------------------------------------------------------------
template <class Type>
inline void DynamicMaxHeap<Type>::Clear()
{ 
    m_HeapArray.Clear();
    m_iUsed = 0; 
}
//----------------------------------------------------------------------------
template <class Type>
inline int DynamicMaxHeap<Type>::GetCount(void) const
{
    return m_iUsed;
}
//----------------------------------------------------------------------------
template <class Type>
inline void DynamicMaxHeap<Type>::Insert(const Type& rSrcObject)
{
    // 如果数组已满,则增长
	if( m_iUsed >= m_HeapArray.GetCount() )
		m_HeapArray.Append(m_iAllocationStep);
	
    // 加入新对象并且调整堆
	m_HeapArray[m_iUsed] = rSrcObject;
    if( UserOperationFunction )
        (*UserOperationFunction)((void*)m_HeapArray.Pointer(m_iUsed), m_iUsed);

    AdjustUpward(m_iUsed);
    m_iUsed++;
}
//----------------------------------------------------------------------------
template <class Type>
inline void DynamicMaxHeap<Type>::Remove(int iPos, Type& rDesObject)
{
    ASSERT( iPos < m_iUsed && iPos >= 0 );

    rDesObject = m_HeapArray[iPos];
    // 将堆尾对象移到堆顶,调整堆
    m_HeapArray[iPos] = m_HeapArray[m_iUsed - 1];
    if( UserOperationFunction )
        (*UserOperationFunction)((void*)m_HeapArray.Pointer(iPos), iPos);

    m_iUsed--;
	AdjustDownward(iPos, m_iUsed - 1);
}
//----------------------------------------------------------------------------
template <class Type>
inline void DynamicMaxHeap<Type>::Set(int iPos, const Type& rSrcObject)
{
    ASSERT( iPos < m_iUsed && iPos >= 0 );

    m_HeapArray[iPos] = rSrcObject;
    if( UserOperationFunction )
        (*UserOperationFunction)((void*)m_HeapArray.Pointer(iPos), iPos);

    if( iPos == 0 )
	{
        AdjustDownward(iPos, m_iUsed - 1);
        return;
	}

    int iParent = (iPos - 1) >> 1;
    // 判断调整方向
    if( CompareFunction((void*)m_HeapArray.Pointer(iPos), (void*)m_HeapArray.Pointer(iParent)) > 0 )
        AdjustUpward(iPos);
	else
        AdjustDownward(iPos, m_iUsed - 1);
}
//----------------------------------------------------------------------------
template <class Type>
inline const Type& DynamicMaxHeap<Type>::Get(int iPos) const
{
    ASSERT( iPos < m_iUsed && iPos >= 0 );

    return m_HeapArray[iPos];
}
//----------------------------------------------------------------------------
template <class Type>
inline void DynamicMaxHeap<Type>::SetAllocationStep(int iStep)
{
    ASSERT( iStep > 0 );

    m_iAllocationStep = iStep;
}
//----------------------------------------------------------------------------