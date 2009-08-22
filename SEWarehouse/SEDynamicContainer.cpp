#pragma once
#ifndef Swing_DynamicContainer_CPP
#define Swing_DynamicContainer_CPP

#include "SEDynamicContainer.h"
#include "SEStaticStackArray.cpp"

namespace Swing
{

// iterate whole dynamic container
/* NOTE: The iterator defined by this macro must be destroyed before adding/removing
 * elements in the container. To do so, embed the for loop in additional curly braces.
 */
#define FOREACHINDYNAMICCONTAINER(container, type, iter) \
  for(DynamicContainerIterator<type> iter(container); !iter.IsPastEnd(); iter.MoveToNext() )

template<class Type>
DynamicContainer<Type>::DynamicContainer(void) 
{
#if CHECKARRAYLOCKING
	// not locked
	dc_LockCt = 0;
#endif
}

template<class Type>
DynamicContainer<Type>::DynamicContainer(DynamicContainer<Type> &dcOriginal)
{
#if CHECKARRAYLOCKING
	// not locked
	dc_LockCt = 0;
#endif

	(*this) = dcOriginal;
}

template<class Type>
DynamicContainer<Type>::~DynamicContainer(void) 
{
	Clear();
}

template<class Type>
void DynamicContainer<Type>::Clear(void) 
{
	ASSERT(this!=NULL);
	
	// 手动删除所有对象
	for(INDEX i = 0; i<Count(); i++ )
		delete sa_Array[i];

	// 删除对象指针数组
	StaticStackArray<Type *>::Clear();
}

template<class Type>
void DynamicContainer<Type>::Add(Type *ptNewObject)
{
	Push() = ptNewObject;
}

template<class Type>
void DynamicContainer<Type>::Remove(Type *ptOldObject)
{
	ASSERT(this!=NULL);

#if CHECKARRAYLOCKING
	// check that not locked for indices
	ASSERT(dc_LockCt == 0);
#endif

	// 获取该对象索引
	INDEX iMember = GetIndex(ptOldObject);
	// 把当前最后一个对象的指针移动到该位置,并减少堆栈当前使用计数
	sa_Array[iMember]=sa_Array[Count()-1];
	Pop();
}

template<class Type>
BOOL DynamicContainer<Type>::IsMember(Type *ptOldObject)
{
	ASSERT(this!=NULL);

	// 检查所有对象指针,很慢
	for (INDEX iMember=0; iMember<Count(); iMember++) 
	{
		if(sa_Array[iMember] == ptOldObject) 
		{
			return TRUE;
		}
	}

	return FALSE;
}

template<class Type>
Type *DynamicContainer<Type>::Pointer(INDEX iMember) 
{
	ASSERT(this!=NULL);
	// 检查数组越界
	ASSERT(iMember>=0 && iMember<Count());

#if CHECKARRAYLOCKING
	// check that locked for indices
	ASSERT(dc_LockCt>0);
#endif

	return sa_Array[iMember];
}

template<class Type>
const Type *DynamicContainer<Type>::Pointer(INDEX iMember) const 
{
	ASSERT(this!=NULL);
	// 检查数组越界
	ASSERT(iMember>=0 && iMember<Count());

#if CHECKARRAYLOCKING
	// check that locked for indices
	ASSERT(dc_LockCt>0);
#endif

	return sa_Array[iMember];
}

template<class Type>
void DynamicContainer<Type>::Lock(void) 
{
	ASSERT(this!=NULL);

#if CHECKARRAYLOCKING
	ASSERT(dc_LockCt>=0);
	// increment lock counter
	dc_LockCt++;
#endif
}

template<class Type>
void DynamicContainer<Type>::Unlock(void) 
{
	ASSERT(this!=NULL);

#if CHECKARRAYLOCKING
	dc_LockCt--;
	ASSERT(dc_LockCt>=0);
#endif
}

template<class Type>
INDEX DynamicContainer<Type>::Index(Type *ptMember) 
{
	ASSERT(this!=NULL);

  // check that locked for indices
#if CHECKARRAYLOCKING
	ASSERT(dc_LockCt>0);
#endif

	return GetIndex(ptMember);
}

template<class Type>
INDEX DynamicContainer<Type>::GetIndex(Type *ptMember) 
{
	ASSERT(this!=NULL);

	// 检查所有对象指针,很慢
	for (INDEX iMember=0; iMember<Count(); iMember++) 
	{
		if(sa_Array[iMember]==ptMember) 
		{
			return iMember;
		}
	}

	ASSERTALWAYS("DynamicContainer<Type><>::Index(): Not a member of this container!");
	return 0;
}

template<class Type>
Type &DynamicContainer<Type>::GetFirst(void)
{
	ASSERT(Count()>=1);

	return *sa_Array[0];
}

template<class Type>
DynamicContainer<Type> &DynamicContainer<Type>::operator=(DynamicContainer<Type> &coOriginal)
{
	StaticStackArray<Type *>::operator=(coOriginal);
	
	return *this;
}

template<class Type>
void DynamicContainer<Type>::MoveContainer(DynamicContainer<Type> &coOther)
{
	ASSERT(this!=NULL && &coOther!=NULL);
  
	// check that not locked for indices
#if CHECKARRAYLOCKING
	ASSERT(dc_LockCt==0 && coOther.dc_LockCt==0);
#endif
	StaticStackArray<Type*>::MoveArray(coOther);
}

template<class Type>
inline DynamicContainerIterator<Type>::DynamicContainerIterator(DynamicContainer<Type> &da) : dci_Array(da) 
{
	// lock indices
	dci_Array.Lock();
	dci_Index = 0;
}

template<class Type>
inline DynamicContainerIterator<Type>::~DynamicContainerIterator(void) 
{
	// unlock indices
	dci_Array.Unlock();
	dci_Index = -1;
}

template<class Type>
inline void DynamicContainerIterator<Type>::MoveToNext(void) 
{
	ASSERT(this!=NULL);
	dci_Index++;
}

template<class Type>
inline BOOL DynamicContainerIterator<Type>::IsPastEnd(void) 
{
	ASSERT(this!=NULL);
	return dci_Index>=dci_Array.Count();
}

}

#endif

