#ifndef Swing_LinearAllocator_H
#define Swing_LinearAllocator_H
#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include "SESystem.h"
#include "SELists.h"

namespace Swing
{

// 线性方式动态分配器类
template<class Type>
class LinearAllocator 
{
// implementation:
public:
  ListHead la_lhBlocks;      // list of allocated memory blocks
  INDEX la_ctAllocationStep;  // number of objects allocated
  INDEX la_ctObjects;         // number of objects allocated
  INDEX la_ctFree;            // number of free objects in current block
  Type *la_ptNextFree;        // pointer to next free object

  // allocate a new memory block
  void AllocBlock(INDEX iCount);

// interface:
public:
  // default constructor
  LinearAllocator(void);
  // copy constructor
  LinearAllocator(LinearAllocator<Type> &laOriginal);
  // destructor -- frees all memory
  ~LinearAllocator(void);
  // destroy all objects, and reset the allocator to initial (empty) state
  void Clear(void);

  /* Set how many elements to allocate when stack overflows. */
  inline void SetAllocationStep(INDEX ctStep);

  // allocate a new object
  inline Type &Append(void);
  inline Type *Append(INDEX ct);
  // free all objects but keep allocated space and relinearize it
  inline void Reset(void);
// these are just for compatibility with DynamicStackArray<>:
  inline Type &Push(void) { return Append(); };
  inline Type *Push(INDEX ct) { return Append(ct); };
  inline void PopAll(void) { Reset(); };
};

}

#endif

