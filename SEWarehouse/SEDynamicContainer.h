#ifndef Swing_DynamicContainer_H
#define Swing_DynamicContainer_H

#include "SESystem.h"
#include "SEStaticStackArray.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:动态容器类
// 说明:这个容器类保存着其他类对象的指针,注意派生自StaticStackArray<Type *>
//----------------------------------------------------------------------------
template<class Type>
class DynamicContainer : public StaticStackArray<Type *> 
{
public:
#if CHECKARRAYLOCKING
	INDEX m_iLockCt;          // lock counter for getting indices
#endif

	/* Get index of an object from it's pointer without locking. */
	INDEX GetIndex(Type *ptMember);

public:
	DynamicContainer(void);
	DynamicContainer(DynamicContainer<Type> &coOriginal);
	virtual ~DynamicContainer(void);

public:
	// 添加一个对象到容器
	void Add(Type *ptNewObject);
	// 从容器移走一个对象
	void Remove(Type *ptOldObject);
	// 清空容器
	void Clear(void);
	// 指定对象是否在容器中
	BOOL IsMember(Type *ptOldObject);

	// 根据索引返回对象指针
	Type *Pointer(INDEX iObject);
	const Type *Pointer(INDEX iObject) const;
	inline Type &operator[](INDEX iObject) { return *Pointer(iObject); };
	inline const Type &operator[](INDEX iObject) const { return *Pointer(iObject); };
	DynamicContainer<Type> &operator=(DynamicContainer<Type> &coOriginal);
	// 从另一个容器中把所有对象移动过来
	void MoveContainer(DynamicContainer<Type> &coOther);

	/* Lock for getting indices. */
	void Lock(void);
	/* Unlock after getting indices. */
	void Unlock(void);
	// 根据对象指针返回其索引
	INDEX Index(Type *ptObject);
	// 获取容器中第一个对象(调用时容器必须至少有一个对象)
	Type &GetFirst(void);
};

//--------------------------------------------------------------------------------------
// 名称:动态容器迭代器类
// 说明:
//--------------------------------------------------------------------------------------
template<class Type>
class DynamicContainerIterator 
{
private:
	INDEX dci_Index;               // 当前对象索引
	DynamicContainer<Type> &dci_Array;   // 被迭代的动态容器的引用

public:
	inline DynamicContainerIterator(DynamicContainer<Type> &da);
	inline ~DynamicContainerIterator(void);

public:
	// 只能向后迭代
	inline void MoveToNext(void);
	inline BOOL IsPastEnd(void);

	// 获取当前对象
	Type &Current(void) { return *dci_Array.Pointer(dci_Index); }
	Type &operator*(void) { return *dci_Array.Pointer(dci_Index); }
	operator Type *(void) { return dci_Array.Pointer(dci_Index); }
	Type *operator->(void) { return dci_Array.Pointer(dci_Index); }
};

}

#endif

