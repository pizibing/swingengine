#ifndef Swing_StaticStackArray_H
#define Swing_StaticStackArray_H

#include "SESystem.h"
#include "SEStaticArray.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:静态堆栈数组类
// 说明:
//----------------------------------------------------------------------------
template<class Type>
class StaticStackArray : public StaticArray<Type> 
{
public:
	INDEX sa_UsedCount;         // 当前使用数量
	INDEX sa_ctAllocationStep;  // 堆栈溢出时新分配的内存大小

public:
	StaticStackArray(void);
	virtual ~StaticStackArray(void);

public:

	inline void SetAllocationStep(INDEX ctStep);
	inline void Append(INDEX iCount);
	// 释放内存,恢复初始空状态
	inline void Delete(void);
	// 调用Delete释放内存,恢复初始空状态
	inline void Clear(void);

	// 在堆栈顶部压入新对象
	// Push只增加堆栈使用计数,并没有立刻压入新对象,需要程序稍后手动压入新对象,
	// example:Push() = Type,没有参数传递,直接访问数组赋值,效率较高
	inline Type &Push(void);
	inline Type *Push(INDEX ct);
	// 从堆栈顶部弹出一个对象,保留堆栈内存
	inline Type &Pop(void);
	// 弹出比iNewTop索引值高的所有对象,保留堆栈内存
	inline void PopUntil(INDEX iNewTop);
	// 弹出所有对象,但保留堆栈内存
	inline void PopAll(void);

	inline Type &operator[](INDEX iObject);
	inline const Type &operator[](INDEX iObject) const;
	INDEX Count(void) const;
	INDEX Index(Type *ptObject);
	void MoveArray(StaticStackArray<Type> &arOther);

	StaticStackArray<Type> &operator=(const StaticStackArray<Type> &arOriginal);
};

}

#endif

