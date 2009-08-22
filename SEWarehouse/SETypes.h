#pragma once
#ifndef Swing_Types_H
#define Swing_Types_H

typedef signed __int64     SQUAD;
typedef signed long  int   SLONG;
typedef signed short int   SWORD;
typedef signed char	       SBYTE;
typedef signed int         SINT;

typedef unsigned __int64   UQUAD;
typedef unsigned long  int ULONG;
typedef unsigned short int UWORD;
typedef unsigned char      UBYTE;
typedef unsigned int       UINT;


#define MAX_SLONG ((SLONG)0x7FFFFFFFL)
#define MAX_SWORD ((UWORD)0x7FFF)
#define MAX_SBYTE ((SBYTE)0x7F)

#define MIN_SLONG ((SLONG)0x80000000L)
#define MIN_SWORD ((SWORD)0x8000)
#define MIN_SBYTE ((SBYTE)0x80)

#define MIN_ULONG ((ULONG)0x00000000L)
#define MIN_UWORD ((UWORD)0x0000)
#define MIN_UBYTE ((UBYTE)0x00)

#define MAX_ULONG ((ULONG)0xFFFFFFFFL)
#define MAX_UWORD ((UWORD)0xFFFF)
#define MAX_UBYTE ((UBYTE)0xFF)

#define MAX_FLOAT  (+3E38f)
#define MIN_FLOAT  (-3E38f)
#define MAX_DOUBLE (+1E308)
#define MIN_DOUBLE (-1E308)

typedef int BOOL;		        // this is for TRUE/FALSE
typedef long int RESULT;		// for error codes
typedef long int INDEX;     // for indexed values and quantities

#define FALSE 0
#define TRUE  1

#define NONE 0
#define NOTHING ((void) 0)
#define FOREVERDO for(;;)

#define DECLARE_NOCOPYING(classname)        \
  classname(const classname &c);            \
  classname &operator=(const classname &c); 
#define IMPLEMENT_NOCOPYING(classname)      \
  classname::classname(const classname &c) { ASSERT(FALSE); };            \
  classname &classname::operator=(const classname &c){ ASSERT(FALSE); return *this; }; 

// standard angles
#define ANGLE_0    (  0.0f)
#define ANGLE_90   ( 90.0f)
#define ANGLE_180  (180.0f)
#define ANGLE_270  (270.0f)
#define ANGLE_360  (360.0f)

// you need <stddef.h> for this!
#define structptr(structure, member, ptr) \
( (struct structure *) ( ((UBYTE *)(ptr)) - \
 offsetof(struct structure, member)) )

// standard types

// simple types
typedef SLONG  PIX;    // pixel coordinates
typedef SLONG  TEX;    // texel coordinates
typedef SLONG  MEX;    // texels in mip-level 0
typedef float  FLOAT;
typedef double DOUBLE;
typedef float  ANGLE;
typedef float  TIME;
typedef FLOAT  RANGE;
typedef ULONG  COLOR;  // color is always in 32 bit true-color format

// macros for windows/croteam true color conversion
#define CLRF_CLR(clr) ( ((clr & 0xff000000) >> 24) | \
                        ((clr & 0x00ff0000) >>  8) | \
                        ((clr & 0x0000ff00) <<  8))
#define CLR_CLRF(clrref) ( ((clrref & 0x000000ff) << 24) | \
                           ((clrref & 0x0000ff00) <<  8) | \
                           ((clrref & 0x00ff0000) >>  8))

// z-buffer depth constants
#define ZBUF_FRONT (0.0f)
#define ZBUF_BACK  (1.0f)

// alpha factor constants
#define CT_OPAQUE      MAX_UBYTE
#define CT_TRANSPARENT MIN_UBYTE

// line types (masks)
#define _FULL_	   0xFFFFFFFF
#define _SYMMET16_ 0xFF88FF88
#define _SYMMET32_ 0xFFFF0180
#define _POINT_    0xAAAAAAAA

#define _DOT2_	   0xCCCCCCCC
#define _DOT4_	   0xF0F0F0F0
#define _DOT8_	   0xFF00FF00
#define _DOT16_    0xFFFF0000

#define _TY31_	   0xEEEEEEEE
#define _TY62_	   0xFCFCFCFC
#define _TY124_    0xFFF0FFF0
#define _TY13_	   0x88888888
#define _TY26_	   0xC0C0C0C0
#define _TY412_    0xF000F000

// some mexels constants
#define MAX_MEX_LOG2 10
#define MIN_MEX_LOG2  0
#define MAX_MEX     (1L<<MAX_MEX_LOG2)
#define MIN_MEX     (1L<<MIN_MEX_LOG2)

// macro for converting mexels to meters
#define METERS_MEX(mex)    ((FLOAT)(((FLOAT)mex)/MAX_MEX))
#define MEX_METERS(meters) ((MEX)(meters*MAX_MEX))

#define ARRAYCOUNT(array) (sizeof(array)/sizeof((array)[0]))

inline DOUBLE FLOATtoDOUBLE(const FLOAT f)  { return DOUBLE(f); }
inline FLOAT  DOUBLEtoFLOAT(const DOUBLE d) { return FLOAT(d);  }

inline DOUBLE UpperLimit(DOUBLE x) { return MAX_DOUBLE; }
inline DOUBLE LowerLimit(DOUBLE x) { return MIN_DOUBLE; }
inline FLOAT  UpperLimit(FLOAT x)  { return MAX_FLOAT;  }
inline FLOAT  LowerLimit(FLOAT x)  { return MIN_FLOAT;  }
inline SLONG  UpperLimit(SLONG x)  { return MAX_SLONG;  }
inline SLONG  LowerLimit(SLONG x)  { return MIN_SLONG;  }
inline SWORD  UpperLimit(SWORD x)  { return MAX_SWORD;  }
inline SWORD  LowerLimit(SWORD x)  { return MIN_SWORD;  }

// class predeclarations
class ListHead;
class ListNode;

// template class predeclarations
template<class Type, int iOffset> class ListIter;
template<class Type> class DynamicArray;
template<class Type> class DynamicStackArray;
template<class Type> class DynamicArrayIterator;
template<class Type> class StaticArray;
template<class Type> class StaticStackArray;
template<class Type> class StaticArrayIterator;
template<class Type> class LinearAllocator;
template<class Type> class DynamicContainer;

// vectors


// planes


// axis-aligned bounding boxes


// oriented bounding boxes


// matrices


// quaternions


// BSP types

// general clearing functions
template<class cType>
inline void Clear(cType &t) { t.cType::Clear(); };

// specific clearing functions for built-in types
inline void Clear(signed long int sli) {};
inline void Clear(unsigned long int uli) {};
inline void Clear(int i) {};
inline void Clear(float i) {};
inline void Clear(double i) {};
inline void Clear(void *pv) {};

#define SYMBOLLOCATOR(symbol)

#endif 

