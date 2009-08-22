// Swing Engine Version 1 Source Code 
// Most of techniques in the engine are mainly based on David Eberly's
// Wild Magic 4 open-source code.The author of Swing Engine learned a lot
// from Eberly's experience of architecture and algorithm.
// Several sub-systems are totally new,and others are re-implimented or
// re-organized based on Wild Magic 4's sub-systems.
// Copyright (c) 2007-2010.  All Rights Reserved
//
// Eberly's permission:
// Geometric Tools, Inc.
// http://www.geometrictools.com
// Copyright (c) 1998-2006.  All Rights Reserved
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or (at
// your option) any later version.  The license is available for reading at
// the location:
// http://www.gnu.org/copyleft/lgpl.html

#ifndef Swing_Platforms_H
#define Swing_Platforms_H

//----------------------------------------------------------------------------
// Microsoft Windows 2000/XP platform
//----------------------------------------------------------------------------
#if defined(_WIN32)

#define SE_ALIGN1 __declspec(align(1))
#define SE_ALIGN2 __declspec(align(2))
#define SE_ALIGN4 __declspec(align(4))
#define SE_ALIGN8 __declspec(align(8))
#define SE_ALIGN16 __declspec(align(16))

#if defined(_MSC_VER)
// _MSC_VER 是 VC编译器内定义的一个宏
// 1200 VC6.0
// 1201 EVC4.2
// 1300 VC2002
// 1310 VC2003
// 1400 VC2005
#if _MSC_VER < 1300
#define SE_USING_VC6
#elif _MSC_VER < 1310
#define SE_USING_VC70
#elif _MSC_VER < 1400
#define SE_USING_VC71
#else
#define SE_USING_VC80
#endif 

// 使用SE_ASSERT( false )时,该宏展开后,可能产生条件表达式为常量的情况,
// 避免这个编译器4级警告.
#pragma warning(disable:4127)

// 声明类成员无名称struct时,避免这个编译器4级警告.
#pragma warning(disable:4201)

// The use of SE_FOUNDATION_ITEM to export an entire class generates warnings
// when member data and functions involving templates or inlines occur.  To
// avoid the warning, SE_FOUNDATION_ITEM can be applied only to those items
// that really need to be exported.
#pragma warning(disable:4251)

typedef __int64 SE_Int64;

#endif
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Macintosh OS X platform
//----------------------------------------------------------------------------
#elif defined(__APPLE__)

#define SE_ALIGN1
#define SE_ALIGN2
#define SE_ALIGN4
#define SE_ALIGN8
#define SE_ALIGN16

#if defined(__BIG_ENDIAN__)
#define SE_BIG_ENDIAN
#else
#define SE_LITTLE_ENDIAN
#endif

#include <stdint.h>
typedef int64_t SE_Int64;
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Linux platform
//----------------------------------------------------------------------------
#else

#define SE_ALIGN1
#define SE_ALIGN2
#define SE_ALIGN4
#define SE_ALIGN8
#define SE_ALIGN16

#include <stdint.h>
typedef int64_t SE_Int64;

#endif
//----------------------------------------------------------------------------

#endif
