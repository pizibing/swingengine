#ifndef Swing_Lists_H
#define Swing_Lists_H

#include "SESystem.h"

//----------------------------------------------------------------------------
// 名称:双向链表节点类
// 说明:参考自Serious Engine
// 作者:Sun Che
// 时间:20070603
//----------------------------------------------------------------------------
class SE_FOUNDATION_API ListNode 
{
public:
    ListNode* pSuccessor;
    ListNode* pPredecessor;

    bool IsValid(void) const;

public:
    inline ListNode(void);
    inline ListNode(const ListNode& rNode);
    inline ~ListNode(void);
  
public:
    inline ListNode &operator = (const ListNode& rNode);
    // 检查当前节点是否被连入list,自己指向前驱与后继,且前驱与后继均指向自己
    bool IsLinked(void) const;
    void AddAfter(ListNode& rNode);
    void AddBefore(ListNode& rNode);
    // 从list中移除自己
    void Remove(void);

    inline bool IsHeadMarker(void) const;
    inline bool IsTailMarker(void) const;
    inline bool IsHead(void) const;
    inline bool IsTail(void) const;

    // 获取当前节点的后继节点
    inline ListNode& GetSucc(void) const;
    // 获取当前节点的前驱节点
    inline ListNode& GetPred(void) const;

    // 向后迭代
    inline ListNode& IterationSucc(void) const;
    // 向前迭代
    inline ListNode& IterationPred(void) const;
    // 在迭代过程中在当前节点之前插入node
    inline void IterationInsertBefore(ListNode& rNode);
    // 在迭代过程中在当前节点之后插入node
    inline void IterationInsertAfter(ListNode& rNode);

    // 找到当前节点所在list的list head
    ListHead& GetListHead(void);
};

//----------------------------------------------------------------------------
// 名称:双向链表表头类
// 说明:参考自Serious Engine
// 作者:Sun Che
// 时间:20070603
//----------------------------------------------------------------------------
class SE_FOUNDATION_API ListHead 
{
public:
    // 前2个指针的内存空间用作这个list的head marker,
    // 后2个指针的内存空间用作这个list的tail marker,
    // 空list时,head marker的pSuccessor(pHead)指向&pNULL,即指向tail marker,
    // 空list时,tail marker的pPredecessor(pTail)指向&pHead,即指向head marker,
    // head marker的pPredecessor(pNULL)始终为NULL,tail marker的pSuccessor(pNULL)始终为NULL.
    ListNode* pHead; // 指向第一个节点(head节点)
    ListNode* pNULL; // 既是head marker的前驱指针,又是tail marker的后继指针
    ListNode* pTail; // 指向最后一个节点(tail节点)

     // 或者是空list,或者是包含至少一个有效节点的list
    bool IsValid(void) const;
    // 构建空List,
    // 构建结果:0<-head marker-><-tail marker->0
    void Clear(void);

public:
    inline ListHead(void);
    inline ListHead(const ListHead& rHead);

public:
    inline void operator = (const ListHead& rHead);
  
    inline ListNode& GetHead(void) const;
    inline ListNode& GetTail(void) const;
    inline ListNode& GetIterationHead(void) const;
    inline ListNode& GetIterationTail(void) const;

    void AddHead(ListNode& rNode);
    void AddTail(ListNode& rNode);
    void RemoveHead(void);
    void RemoveTail(void);
    void RemoveAll(void);

    bool IsEmpty(void) const;
    // 把另一个list的所有元素move进来
    void MoveList(ListHead& rHead);
    INDEX Count(void) const;
    void Sort(int (*pCompare)(const void *p0, const void *p1), int iNodeOffset);
};

//----------------------------------------------------------------------------
// 名称:双向链表迭代器类
// 说明:参考自Serious Engine
// 作者:Sun Che
// 时间:20070603
//----------------------------------------------------------------------------
template<class Base, int iOffset>
class ListIter 
{
public:
    ListIter(void){ m_pCurrentNode = 0; }
    // 指向head(非空list)或者tail marker(空list)
    ListIter(const ListHead& rHead){ m_pCurrentNode = &rHead.GetIterationHead(); }
    // 指向传入的node
    ListIter(ListNode& lnNode){ ASSERT( rNode.IsLinked() ); m_pCurrentNode = &rNode; }

public:
    // 指向head marker
    void Reset(const ListHead& rHead){ m_pCurrentNode = &rHead.IterationHead(); }
    // 向后继迭代
    void MoveToNext(void){ m_pCurrentNode = &m_pCurrentNode->IterationSucc(); }
    // 向前驱迭代
    void MoveToPrev(void){ m_pCurrentNode = &m_pCurrentNode->IterationPred(); }
    // 是否到达tail marker
    bool IsPastEnd(void){ return m_pCurrentNode->IsTailMarker(); }

    // 在当前指向节点之后插入节点
    inline void InsertAfterCurrent(ListNode& rNode){ m_pCurrentNode->IterationInsertAfter(rNode); }
    // 在当前指向节点之前插入节点
    inline void InsertBeforeCurrent(ListNode& rNode){ m_pCurrentNode->IterationInsertBefore(rNode); }

    // 获取当前指向的元素
    Base& Current(void){ return *((Base*)((UBYTE*)m_pCurrentNode - iOffset)); }
    Base& operator* (void){ return *((Base*)((UBYTE*)m_pCurrentNode - iOffset)); }
    operator Base* (void){ return ((Base*)((UBYTE*)m_pCurrentNode - iOffset)); }
    Base* operator -> (void){ return ((Base*)((UBYTE*)m_pCurrentNode - iOffset)); }

private:
    ListNode* m_pCurrentNode;
};

#include "SELists.inl"

// offsetof求出m在s中的字节偏移量
//#define offsetof(s,m)	(size_t)&(((s *)0)->m)

// 构建用于baseclass的迭代器
#define LISTITER(baseclass, member) ListIter<baseclass, offsetof(baseclass, member)>

// 正向迭代list
#define FOREACHINLIST(baseclass, member, head, iter) \
  for( LISTITER(baseclass, member) iter(head); !iter.IsPastEnd(); iter.MoveToNext() )

// 逆向迭代list
#define FOREACHINLIST_R(baseclass, member, head, iter) \
  for( LISTITER(baseclass, member) iter(head.IterationTail()); \
   !iter->member.IsHeadMarker(); iter.MoveToPrev() )

// 正向迭代删除list
#define FORDELETELIST(baseclass, member, head, iter)		  \
   for( LISTITER(baseclass, member) iter(head), iter##next;	  \
   iter##next=iter, iter##next.IsPastEnd() || (iter##next.MoveToNext(),1), !iter.IsPastEnd(); \
     iter = iter##next)

// 逆向迭代删除list
#define FORDELETELIST_R(baseclass, member, head, iter)		  \
   for( LISTITER(baseclass, member) iter(head.IterationTail()), iter##prev;	  \
   iter##prev=iter, iter##prev->member.IsHeadMarker() || (iter##prev.MoveToPrev(),1), !iter->member.IsHeadMarker(); \
     iter = iter##prev)

#define LIST_HEAD(listhead, baseclass, member) \
  ( (baseclass *) ( ((UBYTE *)(&(listhead).GetHead())) - offsetof(baseclass, member) ) )

#define LIST_TAIL(listhead, baseclass, member) \
  ( (baseclass *) ( ((UBYTE *)(&(listhead).GetTail())) - offsetof(baseclass, member) ) )

#define LIST_PRED(element, baseclass, member) \
  ( (baseclass *) ( ((UBYTE *)(&(element).member.GetPred())) - offsetof(baseclass, member) ) )

#define LIST_SUCC(element, baseclass, member) \
  ( (baseclass *) ( ((UBYTE *)(&(element).member.GetSucc())) - offsetof(baseclass, member) ) )


#endif

