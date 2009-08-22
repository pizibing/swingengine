#ifndef Swing_DynamicStackArray_CPP
#define Swing_DynamicStackArray_CPP

#include "SEDynamicStackArray.h"
#include "SEDynamicArray.cpp"

namespace Swing
{

//----------------------------------------------------------------------------
template<class Type>
INDEX DynamicStackArray<Type>::GetCount() const 
{
    ASSERT( this != 0 );

    return m_iUsed;
}
//----------------------------------------------------------------------------
template<class Type>
INDEX DynamicStackArray<Type>::Index(Type* pObject) 
{
    ASSERT( this != 0 );

    INDEX i = DynamicArray<Type>::Index(pObject);
    ASSERTMSG(i<m_iUsed, "DynamicStackArray<>::Index(): Not a member of this array!");
	
    return i;
}
//----------------------------------------------------------------------------
template<class Type>
Type** DynamicStackArray<Type>::GetArrayOfPointers()
{
	return m_Pointers;
}
//----------------------------------------------------------------------------
template<class Type>
DynamicStackArray<Type>& DynamicStackArray<Type>::operator=(DynamicStackArray<Type>& rOriginal)
{
    ASSERT( this != 0 );
    ASSERT( &rOriginal != 0 );
    ASSERT( this != &rOriginal );

    DynamicArray<Type>::operator=(rOriginal);
    m_iUsed = rOriginal.m_iUsed;

    return *this;
}
//----------------------------------------------------------------------------

}

#endif

