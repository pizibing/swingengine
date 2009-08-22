#ifndef Swing_DynamicMinHeap_H
#define Swing_DynamicMinHeap_H

#include "SESystem.h"
#include "SEDynamicArray.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:动态最小堆类
// 说明:m_HeapArray数组中的元素满足完全二叉树的存储顺序:
//      ki <= k2i + 1(ki的左孩子) 且 ki <= k2i + 2(ki的右孩子)
//      二叉树的最后一个非叶子节点在: ki = (m_iCurrentSize - 2) / 2
//      ki节点的父亲节点kp = (ki - 1) / 2
// 作者:Sun Che
// 时间:20070609
//----------------------------------------------------------------------------
template <class Type>
class DynamicMinHeap
{
public:
    DynamicMinHeap(void);
    // 用初始数组元素构建堆,O(n*log(n))
    DynamicMinHeap(DynamicArray<Type>& rDA, int iUsed, 
                   int (*pCompare)(const void* p0, const void* p1) = 0,
                   void (*pOperation)(void* pObject, int iIndex) = 0);
    ~DynamicMinHeap(void);

public:
    inline void SetAllocationStep(int iStep);
    inline void Clear(void);

    DynamicMinHeap<Type>& operator = (const DynamicMinHeap<Type>& rOther);

    // 在堆尾部追加,之后调整堆,O(log(n))
    inline void Insert(const Type& rSrcObject);
    // 移走堆中元素,之后调整堆,O(log(n))
    inline void Remove(int iPos, Type& rDesObject);
    // 设置堆中元素,之后调整堆,O(log(n))
    inline void        Set(int iPos, const Type& rSrcObject);
	inline const Type& Get(int iPos) const;

    inline int GetCount(void) const;

    // 用户指定的比较函数
    int (*UserCompareFunction)(const void* p1, const void* p2);
    // 用户指定的对象操作函数,在堆调整时调用,iIndex是对象调整后的位置
    void (*UserOperationFunction)(void* pObject, int iIndex);

private:
	DynamicArray<Type> m_HeapArray;
	int                m_iUsed;
    int                m_iAllocationStep;

    int CompareFunction(const void* p1, const void* p2);

	void AdjustDownward(int iStart, int iEnd);
	void AdjustUpward(int iStart);
};

#include "SEDynamicMinHeap.inl"

}

#endif