#ifndef Swing_DynamicStackArray_H
#define Swing_DynamicStackArray_H

#include "SEDynamicArray.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:动态堆栈数组类
// 说明:参考自Serious Engine
// 作者:Sun Che
// 时间:20070617
//----------------------------------------------------------------------------
template<class Type>
class DynamicStackArray : public DynamicArray<Type> 
{
public:
    DynamicStackArray(void);
    virtual ~DynamicStackArray(void);

public:
    inline void SetAllocationStep(INDEX iStep);
    inline void Clear(void);

    // Push只增加堆栈使用计数,并没有立刻压入新对象,需要程序稍后手动压入新对象,
    // example:Push() = Type,没有参数传递,直接访问数组赋值,效率较高
    inline Type& Push(void);
    inline Type* Push(INDEX iCount);
    // 弹出所有对象
    inline void PopAll(void);

    inline Type& operator [] (INDEX iObject);
    inline const Type& operator [] (INDEX iObject) const;

	INDEX GetCount(void) const;
	INDEX Index(Type* pObject);
	// 获取对象指针数组,用于对指针数组排序
	Type** GetArrayOfPointers(void);

	DynamicStackArray<Type>& operator = (DynamicStackArray<Type> &rOriginal);

protected:
    INDEX m_iUsed;            // 当前对象数量
    INDEX m_iAllocationStep;  // 堆栈溢出时新分配的内存数量
};

#include "SEDynamicStackArray.inl"

}

#endif

