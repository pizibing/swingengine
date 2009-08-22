#ifndef Swing_LinearAllocator_CPP
#define Swing_LinearAllocator_CPP
#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include "SELinearAllocator.h"

namespace Swing
{

class LABlockInfo
{
public:
  ListNode bi_lnNode;
  INDEX bi_ctObjects;   // number of objects in this block
  void *bi_pvMemory;    // start of block memory
  void *bi_pvEnd;       // end of block memory
};

// default constructor
template <class Type>
LinearAllocator<Type>::LinearAllocator(void)
{
  la_ctAllocationStep = 256;
  la_ctObjects = 0;
  la_ctFree = 0;
  la_ptNextFree = NULL;
}

// copy constructor
template <class Type>
LinearAllocator<Type>::LinearAllocator(LinearAllocator<Type> &laOriginal)
{
  ASSERT(FALSE);
}

// destructor -- frees all memory
template <class Type>
LinearAllocator<Type>::~LinearAllocator(void)
{
  Clear();
}

// destroy all objects, and reset the allocator to initial (empty) state
template <class Type>
void LinearAllocator<Type>::Clear(void)
{
  FORDELETELIST(LABlockInfo, bi_lnNode, la_lhBlocks, itBlock) {
  // for all memory blocks
    // free memory used by block (this doesn't call destructors - see note above!)
    delete[] (Type *)itBlock->bi_pvMemory;
    // free memory used by block info
    delete &itBlock.Current();
  }
  la_ctObjects = 0;
  la_ctFree = 0;
  la_ptNextFree = NULL;
}


/* Set how many elements to allocate when stack overflows. */
template <class Type>
inline void LinearAllocator<Type>::SetAllocationStep(INDEX ctStep)
{
  la_ctAllocationStep = ctStep;
}


// allocate a new memory block
template <class Type>
void LinearAllocator<Type>::AllocBlock(INDEX iCount)
{
  ASSERT(this!=NULL && iCount>0);
  //ASSERT(la_ctFree==0);
  Type *ptBlock;
  LABlockInfo *pbi;

  // allocate the memory and call constructors for all members
  ptBlock = new Type[iCount];     // call vector constructor, for better performance
  // allocate the block info
  pbi = new LABlockInfo;
  // add the block to list
  la_lhBlocks.AddTail(pbi->bi_lnNode);
  // remember block memory and size
  pbi->bi_pvMemory = ptBlock;
  pbi->bi_pvEnd = ptBlock+iCount;
  pbi->bi_ctObjects = iCount;

  // count total number of allocated objects
  la_ctObjects+=iCount;
  // set up to get new objects from here
  la_ctFree = iCount;
  la_ptNextFree = ptBlock;
}

// allocate a new object
template <class Type>
inline Type &LinearAllocator<Type>::Append(void)
{
  if (la_ctFree == 0) {
    // allocate a new memory block
    AllocBlock(la_ctAllocationStep);
  }
  Type *ptNew = la_ptNextFree;
  la_ctFree--;
  la_ptNextFree++;
  return *ptNew;
}
template <class Type>
inline Type *LinearAllocator<Type>::Append(INDEX ct)
{
  // if not enough space in current block
  if (la_ctFree < ct) {
    // allocate an entirely new memory block of exact that size
    AllocBlock(ct);
    // use it entirely
    Type *ptNew = la_ptNextFree;
    la_ctFree=0;
    la_ptNextFree=NULL;
    return ptNew;
  // if there is enough space in current block
  } else {
    // use the space
    Type *ptNew = la_ptNextFree;
    la_ctFree-=ct;
    la_ptNextFree+=ct;
    return ptNew;
  }
}
// free all objects but keep allocated space and relinearize it
template <class Type>
inline void LinearAllocator<Type>::Reset(void)
{
  // if there is no block allocated
  if (la_lhBlocks.IsEmpty()) {
    // do nothing
    return;

  // if there is only one block allocated
  } else if (&la_lhBlocks.GetHead()==&la_lhBlocks.GetTail()) {
    // just restart at the beginning
    la_ctFree = la_ctObjects;
    la_ptNextFree = (Type*) (LIST_HEAD(la_lhBlocks, LABlockInfo, bi_lnNode)->bi_pvMemory);

  // if there is more than one block allocated
  } else {
    // remember how much objects were used and allocation step
    INDEX ctObjectsOld = la_ctObjects;
    INDEX ctAllocationStepOld = la_ctAllocationStep;
    // free all blocks
    Clear();
    // restore the allocation step
    la_ctAllocationStep = ctAllocationStepOld;
    // allocate only one linear block
    AllocBlock(ctObjectsOld);
  }
}

// make 'for' construct for walking all objects in a linear allocator
#define FOREACHINLINEARALLOCATOR(allocator, type, pt) \
FOREACHINLIST(LABlockInfo, bi_lnNode, allocator.la_lhBlocks, pt##itBlock) { \
    for(type *pt = (type *)pt##itBlock->bi_pvMemory; pt<(type *)pt##itBlock->bi_pvEnd; pt++)

}

#endif

