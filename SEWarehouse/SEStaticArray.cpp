#ifndef Swing_StaticArray_CPP
#define Swing_StaticArray_CPP

#include "SEStaticArray.h"

namespace Swing
{

//----------------------------------------------------------------------------
template<class Type>
StaticArray<Type>::StaticArray() 
{
    m_iCount = 0;
    m_iArray = 0;
}
//----------------------------------------------------------------------------
template<class Type>
StaticArray<Type>::~StaticArray() 
{
    if( m_iCount != 0 ) 
    {
        Delete();
    }
}
//----------------------------------------------------------------------------
template<class Type>
INDEX StaticArray<Type>::GetCount() const 
{
    ASSERT( this != 0 );
	
    return m_iCount;
}
//----------------------------------------------------------------------------
template<class Type>
INDEX StaticArray<Type>::Index(Type* pObject) 
{
    ASSERT( this != 0 );
    // 用当前对象指针减去数组首地址指针可以快速得出当前对象是否在数组中的结论
    INDEX i = pObject - m_pArray;
    // 确保当前对象在数组范围内
    ASSERT( i >= 0 && i < m_iCount );

    return i;
}
//----------------------------------------------------------------------------
template<class Type>
void StaticArray<Type>::CopyArray(const StaticArray<Type>& rOriginal)
{
    ASSERT( this != 0 && &rOriginal != 0 && this != &rOriginal );

    // 首先清除自己之前的对象并释放内存
    Clear();
    // 获取新尺寸
    INDEX iOriginal = rOriginal.GetCount();
    if( iOriginal == 0 ) 
    {
        return;
    }

    // 按照新尺寸分配内存
    Append(ctOriginal);
    // 复制所有对象过来
    for( INDEX iNew = 0; iNew < iOriginal; iNew++ ) 
    {
        m_pArray[iNew] = rOriginal[iNew];
    }
}
//----------------------------------------------------------------------------
template<class Type>
void StaticArray<Type>::MoveArray(StaticArray<Type>& rOther)
{
    ASSERT( this != 0 && &rOther != 0 && this != &rOther );

    // 首先清除自己之前的对象并释放内存
    Clear();
    if( rOther.GetCount() == 0 ) 
    {
        return;
    }

    // 直接接过该数组的数据指针
    m_iCount = rOther.m_iCount;
    m_pArray = rOther.m_pArray;
    rOther.m_iCount = 0;
    rOther.m_pArray = 0;
}
//----------------------------------------------------------------------------

}

#endif

