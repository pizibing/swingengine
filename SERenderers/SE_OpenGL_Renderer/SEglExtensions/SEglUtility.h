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

/*--------------------------------------------------------------------------*/
/* Swing Engine OpenGL Encapsulator, Version 1 */
/*--------------------------------------------------------------------------*/

#ifndef Swing_GLUtility_H
#define Swing_GLUtility_H

#include "SEglPlugin.h"

#ifdef WIN32
/* Microsoft Windows */
#define STDCALL __stdcall
#define EXTERN __declspec(dllimport)
#else
/* Macintosh, Linux */
#define STDCALL
#define EXTERN extern
#endif

/*
如果一个函数指针为空,则可以通过与之对应的ARB或EXT函数指针来覆盖它.
以下定义设置为1时则覆盖对应项,为0时不覆盖.
*/
#define SE_ARB_OVERRIDE  1
#define SE_EXT_OVERRIDE  1
#define SE_ATI_OVERRIDE  0
#define SE_HP_OVERRIDE   0
#define SE_IBM_OVERRIDE  0
#define SE_INGR_OVERRIDE 0
#define SE_MESA_OVERRIDE 0
#define SE_NV_OVERRIDE   0
#define SE_SGI_OVERRIDE  1
#define SE_SGIS_OVERRIDE 1
#define SE_SUN_OVERRIDE  0

/*--------------------------------------------------------------------------*/
#define SE_GET_FUNCTION(glFunction)\
{ \
    const char* acString = #glFunction; \
    glFunction = \
        (P##glFunction)SE_GL_GetFunctionPointer(&acString[1]); \
}
/*--------------------------------------------------------------------------*/
#define SE_GET_FUNCTION_C(glFunction, suffix, allowOverride)\
{ \
    const char* acString = #glFunction#suffix; \
    glFunction##suffix = \
        (P##glFunction)SE_GL_GetFunctionPointer(&acString[1]); \
    if( allowOverride ) \
    { \
        if( !glFunction ) \
        { \
            glFunction = glFunction##suffix; \
        } \
    } \
}
/*--------------------------------------------------------------------------*/
#define SE_GET_FUNCTION_CA(glFunction, altglFunction, suffix, allowOverride)\
{ \
    const char* acString = #glFunction#suffix; \
    glFunction##suffix = \
        (P##glFunction)SE_GL_GetFunctionPointer(&acString[1]); \
    if( allowOverride ) \
    { \
        if( !altglFunction ) \
        { \
            altglFunction = glFunction##suffix; \
        } \
    } \
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* 已经存在的函数体所使用的宏封装,无返回值. */
/*--------------------------------------------------------------------------*/
#define SE_PRE_BODY_A0(f)\
SE_ENTER_FUNCTION(f); \
SE_NONNULL_FUNCTION(f); \
f(); \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_PRE_BODY_A1(f, a0)\
SE_ENTER_FUNCTION(f); \
SE_NONNULL_FUNCTION(f); \
f(a0); \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_PRE_BODY_A2(f, a0, a1)\
SE_ENTER_FUNCTION(f); \
SE_NONNULL_FUNCTION(f); \
f(a0, a1); \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_PRE_BODY_A3(f, a0, a1, a2)\
SE_ENTER_FUNCTION(f); \
SE_NONNULL_FUNCTION(f); \
f(a0, a1, a2); \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_PRE_BODY_A4(f, a0, a1, a2, a3)\
SE_ENTER_FUNCTION(f); \
SE_NONNULL_FUNCTION(f); \
f(a0, a1, a2, a3); \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_PRE_BODY_A5(f, a0, a1, a2, a3, a4)\
SE_ENTER_FUNCTION(f); \
SE_NONNULL_FUNCTION(f); \
f(a0, a1, a2, a3, a4); \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_PRE_BODY_A6(f, a0, a1, a2, a3, a4, a5)\
SE_ENTER_FUNCTION(f); \
SE_NONNULL_FUNCTION(f); \
f(a0, a1, a2, a3, a4, a5); \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_PRE_BODY_A7(f, a0, a1, a2, a3, a4, a5, a6)\
SE_ENTER_FUNCTION(f); \
SE_NONNULL_FUNCTION(f); \
f(a0, a1, a2, a3, a4, a5, a6); \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_PRE_BODY_A8(f, a0, a1, a2, a3, a4, a5, a6, a7)\
SE_ENTER_FUNCTION(f); \
SE_NONNULL_FUNCTION(f); \
f(a0, a1, a2, a3, a4, a5, a6, a7); \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_PRE_BODY_A9(f, a0, a1, a2, a3, a4, a5, a6, a7, a8)\
SE_ENTER_FUNCTION(f); \
SE_NONNULL_FUNCTION(f); \
f(a0, a1, a2, a3, a4, a5, a6, a7, a8); \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_PRE_BODY_A10(f, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9)\
SE_ENTER_FUNCTION(f); \
SE_NONNULL_FUNCTION(f); \
f(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9); \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* 已经存在的函数体所使用的宏封装,有返回值. */
/*--------------------------------------------------------------------------*/
#define SE_PRE_BODY_A0_RET(f, type)\
type tResult; \
SE_ENTER_FUNCTION(f); \
SE_NONNULL_FUNCTION(f); \
tResult = f(); \
SE_EXIT_FUNCTION(f); \
return tResult
/*--------------------------------------------------------------------------*/
#define SE_PRE_BODY_A1_RET(f, a0, type)\
type tResult; \
SE_ENTER_FUNCTION(f); \
SE_NONNULL_FUNCTION(f); \
tResult = f(a0); \
SE_EXIT_FUNCTION(f); \
return tResult
/*--------------------------------------------------------------------------*/
#define SE_PRE_BODY_A2_RET(f, a0, a1, type)\
type tResult; \
SE_ENTER_FUNCTION(f); \
SE_NONNULL_FUNCTION(f); \
tResult = f(a0, a1); \
SE_EXIT_FUNCTION(f); \
return tResult
/*--------------------------------------------------------------------------*/
#define SE_PRE_BODY_A3_RET(f, a0, a1, a2, type)\
type tResult; \
SE_ENTER_FUNCTION(f); \
SE_NONNULL_FUNCTION(f); \
tResult = f(a0, a1, a2); \
SE_EXIT_FUNCTION(f); \
return tResult
/*--------------------------------------------------------------------------*/
#define SE_PRE_BODY_A4_RET(f, a0, a1, a2, a3, type)\
type tResult; \
SE_ENTER_FUNCTION(f); \
SE_NONNULL_FUNCTION(f); \
tResult = f(a0, a1, a2, a3); \
SE_EXIT_FUNCTION(f); \
return tResult
/*--------------------------------------------------------------------------*/
#define SE_PRE_BODY_A5_RET(f, a0, a1, a2, a3, a4, type)\
type tResult; \
SE_ENTER_FUNCTION(f); \
SE_NONNULL_FUNCTION(f); \
tResult = f(a0, a1, a2, a3, a4); \
SE_EXIT_FUNCTION(f); \
return tResult
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* 函数体所使用的宏封装,无返回值. */
/*--------------------------------------------------------------------------*/
#define SE_BODY_A0(f)\
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    f(); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
} \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_BODY_A1(f, a0)\
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    f(a0); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
} \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_BODY_A2(f, a0, a1)\
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    f(a0, a1); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
} \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_BODY_A3(f, a0, a1, a2)\
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    f(a0, a1, a2); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
} \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_BODY_A4(f, a0, a1, a2, a3)\
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    f(a0, a1, a2, a3); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
} \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_BODY_A5(f, a0, a1, a2, a3, a4)\
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    f(a0, a1, a2, a3, a4); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
} \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_BODY_A6(f, a0, a1, a2, a3, a4, a5)\
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    f(a0, a1, a2, a3, a4, a5); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
} \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_BODY_A7(f, a0, a1, a2, a3, a4, a5, a6)\
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    f(a0, a1, a2, a3, a4, a5, a6); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
} \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_BODY_A8(f, a0, a1, a2, a3, a4, a5, a6, a7)\
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    f(a0, a1, a2, a3, a4, a5, a6, a7); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
} \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_BODY_A9(f, a0, a1, a2, a3, a4, a5, a6, a7, a8)\
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    f(a0, a1, a2, a3, a4, a5, a6, a7, a8); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
} \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_BODY_A10(f, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9)\
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    f(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
} \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/
#define SE_BODY_A11(f, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)\
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    f(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
} \
SE_EXIT_FUNCTION(f)
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* 函数体所使用的宏封装,有返回值. */
/*--------------------------------------------------------------------------*/
#define SE_BODY_A0_RET(f, type, nullretval)\
type tResult; \
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    tResult = f(); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
    tResult = nullretval; \
} \
SE_EXIT_FUNCTION(f); \
return tResult
/*--------------------------------------------------------------------------*/
#define SE_BODY_A1_RET(f, a0, type, nullretval)\
type tResult; \
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    tResult = f(a0); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
    tResult = nullretval; \
} \
SE_EXIT_FUNCTION(f); \
return tResult
/*--------------------------------------------------------------------------*/
#define SE_BODY_A2_RET(f, a0, a1, type, nullretval)\
type tResult; \
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    tResult = f(a0, a1); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
    tResult = nullretval; \
} \
SE_EXIT_FUNCTION(f); \
return tResult
/*--------------------------------------------------------------------------*/
#define SE_BODY_A3_RET(f, a0, a1, a2, type, nullretval)\
type tResult; \
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    tResult = f(a0, a1, a2); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
    tResult = nullretval; \
} \
SE_EXIT_FUNCTION(f); \
return tResult
/*--------------------------------------------------------------------------*/
#define SE_BODY_A4_RET(f, a0, a1, a2, a3, type, nullretval)\
type tResult; \
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    tResult = f(a0, a1, a2, a3); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
    tResult = nullretval; \
} \
SE_EXIT_FUNCTION(f); \
return tResult
/*--------------------------------------------------------------------------*/
#define SE_BODY_A5_RET(f, a0, a1, a2, a3, a4, type, nullretval)\
type tResult; \
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    tResult = f(a0, a1, a2, a3, a4); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
    tResult = nullretval; \
} \
SE_EXIT_FUNCTION(f); \
return tResult
/*--------------------------------------------------------------------------*/
#define SE_BODY_A6_RET(f, a0, a1, a2, a3, a4, a5, type, nullretval)\
type tResult; \
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    tResult = f(a0, a1, a2, a3, a4, a5); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
    tResult = nullretval; \
} \
SE_EXIT_FUNCTION(f); \
return tResult
/*--------------------------------------------------------------------------*/
#define SE_BODY_A7_RET(f, a0, a1, a2, a3, a4, a5, a6, type, nullretval)\
type tResult; \
SE_ENTER_FUNCTION(f); \
if( f ) \
{ \
    SE_NONNULL_FUNCTION(f); \
    tResult = f(a0, a1, a2, a3, a4, a5, a6); \
} \
else \
{ \
    SE_NULL_FUNCTION(f); \
    tResult = nullretval; \
} \
SE_EXIT_FUNCTION(f); \
return tResult
/*--------------------------------------------------------------------------*/

#ifdef __cplusplus
#include <cassert>
extern "C" {
#else
#include <assert.h>
#endif

#define SE_GL_VERSION_NONE  0
#define SE_GL_VERSION_1_1  11
#define SE_GL_VERSION_1_2  12
#define SE_GL_VERSION_1_3  13
#define SE_GL_VERSION_1_4  14
#define SE_GL_VERSION_1_5  15
#define SE_GL_VERSION_2_0  20
int SE_GL_GetVersion(void);
int SE_GL_SupportsExtension(const char* acExtension);

/* 这个函数在每个平台上都要有具体实现. */
void* SE_GL_GetFunctionPointer(const char*);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif
