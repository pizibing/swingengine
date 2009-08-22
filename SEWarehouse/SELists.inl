//----------------------------------------------------------------------------
inline ListNode::ListNode()
{
    pSuccessor = 0;
    pPredecessor = 0;
}
//----------------------------------------------------------------------------
inline ListNode::ListNode(const ListNode& rNode)
{
    (void)rNode;

    pSuccessor = 0;
    pPredecessor = 0;
}
//----------------------------------------------------------------------------
inline ListNode::~ListNode()
{
    if( IsLinked() ) 
    {
        Remove();
    }
}
//----------------------------------------------------------------------------
inline ListNode& ListNode::operator=(const ListNode& rNode)
{
    (void)rNode;

    pSuccessor = 0;
    pPredecessor = 0;
    
    return *this;
}
//----------------------------------------------------------------------------
inline ListNode& ListNode::GetSucc() const
{
    // 不允许获取到tail marker
    ASSERT( IsLinked() && pSuccessor->IsLinked() );

    return *pSuccessor;
}
//----------------------------------------------------------------------------
inline ListNode& ListNode::GetPred() const
{
    // 不允许获取到head marker
    ASSERT( IsLinked() && pPredecessor->IsLinked() );

    return *pPredecessor;
}
//----------------------------------------------------------------------------
inline ListNode& ListNode::IterationSucc() const
{
    // 允许迭代到tail marker
    ASSERT( pSuccessor->IsTailMarker() || pSuccessor->IsLinked() );
  
    return *pSuccessor;
}
//----------------------------------------------------------------------------
inline ListNode& ListNode::IterationPred() const
{
    // 允许迭代到head marker
    ASSERT( pPredecessor->IsHeadMarker() || pPredecessor->IsLinked() );
    
    return *pPredecessor;
}
//----------------------------------------------------------------------------
inline void ListNode::IterationInsertAfter(ListNode& rNode)
{
    ASSERT( !rNode.IsLinked() );
    ASSERT( pSuccessor->IsTailMarker() || pSuccessor->IsLinked() );
  
    pSuccessor->pPredecessor = &rNode;
    rNode.pSuccessor = pSuccessor;
    rNode.pPredecessor = this;
    pSuccessor = &rNode;
}
//----------------------------------------------------------------------------
inline void ListNode::IterationInsertBefore(ListNode& rNode)
{
    ASSERT( !rNode.IsLinked() );
    ASSERT( pPredecessor->IsHeadMarker() || pPredecessor->IsLinked() );
  
    pPredecessor->pSuccessor = &rNode;
    rNode.pPredecessor = pPredecessor;
    rNode.pSuccessor = this;
    pPredecessor = &rNode;
}
//----------------------------------------------------------------------------
inline bool ListNode::IsHeadMarker() const
{
    if( pPredecessor == 0 ) 
    {
        return true;
    } 
    else 
    {
        ASSERT( IsLinked() );
        return false;
    }
}
//----------------------------------------------------------------------------
inline bool ListNode::IsTailMarker() const
{
    if( pSuccessor == 0 ) 
    {
        return true;
    } 
    else 
    {
        ASSERT( IsLinked() );
        return false;
    }
}
//----------------------------------------------------------------------------
inline bool ListNode::IsHead() const
{
    ASSERT( IsLinked() );

    // head的前驱是head marker
    return pPredecessor->pPredecessor == 0;
}
//----------------------------------------------------------------------------
inline bool ListNode::IsTail() const
{
    ASSERT( IsLinked() );

    // tail的后继是tail marker
    return pSuccessor->pSuccessor == 0;
}
//----------------------------------------------------------------------------
inline ListHead::ListHead() 
{ 
    Clear(); 
}
//----------------------------------------------------------------------------
inline ListHead::ListHead(const ListHead& rHead) 
{
    ASSERTALWAYS("Don't copy list heads!");
}
//----------------------------------------------------------------------------
inline void ListHead::operator=(const ListHead& rHead) 
{
    ASSERTALWAYS("Don't copy list heads!");
}
//----------------------------------------------------------------------------
inline ListNode& ListHead::GetHead() const
{
    ASSERT( IsValid() && pHead->IsLinked() );
  
    return *pHead;
}
//----------------------------------------------------------------------------
inline ListNode& ListHead::GetTail() const
{
    ASSERT( IsValid() && pTail->IsLinked() );
  
    return *pTail;
}
//----------------------------------------------------------------------------
inline ListNode& ListHead::GetIterationHead() const
{
    // 允许迭代到tail marker
    ASSERT( IsValid() && (pHead->IsTailMarker() || pHead->IsLinked()) );
  
    return *pHead;
}
//----------------------------------------------------------------------------
inline ListNode& ListHead::GetIterationTail() const
{
    // 允许迭代到head marker
    ASSERT( IsValid() && (pTail->IsHeadMarker() || pTail->IsLinked()) );
  
    return *pTail;
}
//----------------------------------------------------------------------------