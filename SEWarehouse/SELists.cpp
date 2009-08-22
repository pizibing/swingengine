#include "SELists.h"


//----------------------------------------------------------------------------
bool ListNode::IsValid() const
{
    ASSERT( this != 0 );
    ASSERT( (pPredecessor == 0 && pSuccessor == 0) || (pPredecessor != 0 && pSuccessor != 0) );

    // 或者前后都不相连,或者前后都相连且前后节点都指向自己,只有这两种情况返回true
	return (pPredecessor == 0 && pSuccessor == 0) ||
           (pPredecessor->pSuccessor == this) && (pSuccessor->pPredecessor == this);
}
//----------------------------------------------------------------------------
bool ListNode::IsLinked() const
{
    ASSERT( IsValid() );

    return pPredecessor != 0;
}
//----------------------------------------------------------------------------
void ListNode::Remove()
{
    ASSERT( IsLinked() );

    ListNode& next = *pSuccessor;
    ListNode& prev = *pPredecessor;
  
    ASSERT( next.IsTailMarker() || next.IsLinked() );
    ASSERT( prev.IsHeadMarker() || prev.IsLinked() );

    next.pPredecessor = &prev;
    prev.pSuccessor = &next;

    pSuccessor = 0;
    pPredecessor = 0;
}
//----------------------------------------------------------------------------
void ListNode::AddAfter(ListNode& rNode)
{
    ASSERT( IsLinked() && !rNode.IsLinked() );

    ListNode& succ = IterationSucc();
    ListNode& pred = *this;

    succ.pPredecessor = &rNode;
    pred.pSuccessor = &rNode;
    rNode.pSuccessor = &succ;
    rNode.pPredecessor = &pred;
}
//----------------------------------------------------------------------------
void ListNode::AddBefore(ListNode &rNode)
{
    ASSERT( IsLinked() && !rNode.IsLinked() );

    ListNode &succ = *this;
    ListNode &pred = IterationPred();

    succ.pPredecessor = &rNode;
    pred.pSuccessor = &rNode;
    rNode.pSuccessor = &succ;
    rNode.pPredecessor = &pred;
}
//----------------------------------------------------------------------------
ListHead& ListNode::GetListHead()
{
    ListNode* pNode = this;

    while( pNode->pPredecessor != 0 ) 
	{
        pNode = pNode->pPredecessor;
    }

    return *(ListHead*)pNode;
}
//----------------------------------------------------------------------------
void ListHead::Clear()
{
    ASSERT( this != 0 );
  
    pHead = (ListNode*)&(pNULL);
    pNULL = (ListNode*)0;
    pTail = (ListNode*)&(pHead);
}
//----------------------------------------------------------------------------
bool ListHead::IsValid() const
{
    ASSERT( this != 0 );
    ASSERT( pNULL == 0 );
    ASSERT( (pHead == (ListNode*)&pNULL) && (pTail == (ListNode*)&pHead)
         ||  pTail->IsValid() && pHead->IsValid() );
  
    return true;
}
//----------------------------------------------------------------------------
bool ListHead::IsEmpty() const
{
    ASSERT( IsValid() );
  
    return( pHead == (ListNode*)&pNULL );
}
//----------------------------------------------------------------------------
void ListHead::AddHead(ListNode& rNode)
{
    ASSERT( IsValid() && !rNode.IsLinked() );

    ListNode &first = *pHead;

    pHead = &rNode;
    rNode.pSuccessor = &first;
    rNode.pPredecessor = first.pPredecessor;
    first.pPredecessor = &rNode;
}
//----------------------------------------------------------------------------
void ListHead::AddTail(ListNode& rNode)
{
    ASSERT( IsValid() && !rNode.IsLinked() );
  
    ListNode &last = *pTail;

    pTail = &rNode;
    rNode.pSuccessor = last.pSuccessor;
    rNode.pPredecessor = &last;
    last.pSuccessor = &rNode;
}
//----------------------------------------------------------------------------
void ListHead::RemoveHead()
{
    ASSERT( !IsEmpty() );

    pHead->Remove();
}
//----------------------------------------------------------------------------
void ListHead::RemoveTail()
{
    ASSERT( !IsEmpty() );
  
    pTail->Remove();
}
//----------------------------------------------------------------------------
void ListHead::RemoveAll()
{
    for( ListIter<ListNode, 0> iter(*this), iternext;
         iternext = iter, iternext.IsPastEnd() || (iternext.MoveToNext(),1), !iter.IsPastEnd();
         iter = iternext ) 
    {
        iter->Remove();
    }
}
//----------------------------------------------------------------------------
void ListHead::MoveList(ListHead& rHead)
{
    ASSERT( IsValid() && rHead.IsValid() );

    if( rHead.IsEmpty() ) 
    {
        return;
    }

    ListNode& rOtherFirstNode = *rHead.pHead;
    ListNode& rOtherLastNode = *rHead.pTail;

    ListNode& rThisLastNode = *pTail;

    rOtherLastNode.pSuccessor = rThisLastNode.pSuccessor;
    rThisLastNode.pSuccessor = &rOtherFirstNode;
    rOtherFirstNode.pPredecessor = &rThisLastNode;
    pTail = &rOtherLastNode;

    rHead.Clear();
}
//----------------------------------------------------------------------------
INDEX ListHead::Count() const
{
    INDEX slCount = 0;

    for( ListIter<ListNode, 0> iter(*this); !iter.IsPastEnd(); iter.MoveToNext() ) 
    {
        slCount++;
    }

    return slCount;
}
//----------------------------------------------------------------------------
void ListHead::Sort(int (*pCompare)(const void *p0, const void *p1), int iNodeOffset)
{
    INDEX slCount = Count();

    if( slCount == 0 ) 
        return;

    ULONG* pPointers = new ULONG[slCount];

    INDEX i = 0;
    for( ListIter<int, 0> iter(*this); !iter.IsPastEnd(); iter.MoveToNext() ) 
    {
        pPointers[i] = ((ULONG)&*iter) - iNodeOffset;
        i++;
    }

    qsort(pPointers, slCount, sizeof(SLONG), pCompare);

    ListHead tempHead;

    for( INDEX i = 0; i < slCount; i++ )
    {
        ULONG ul = pPointers[i];
        // 获取该node
        ListNode* pNode = (ListNode*)(ul + iNodeOffset);
        // 从原来的list中移除
        pNode->Remove();
        // 加入到新list中
        tempHead.AddTail(*pNode);
    }

    delete[] pPointers;

    MoveList(tempHead);
}
//----------------------------------------------------------------------------