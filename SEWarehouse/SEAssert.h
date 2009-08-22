#ifndef Swing_Assert_H
#define Swing_Assert_H

// 用我们的SE_ASSERT宏,仿照微软<assert.h>从dll引入_assert

/* From VisualC 7.1 assert.h: Define _CRTIMP */
#ifndef _CRTIMP
#ifdef  _DLL
#define _CRTIMP __declspec(dllimport)
#else   /* ndef _DLL */
#define _CRTIMP
#endif  /* _DLL */
#endif  /* _CRTIMP */
/* End: Define _CRTIMP */

/* Define __cdecl for non-Microsoft compilers */
#if ( !defined(_MSC_VER) && !defined(__cdecl) )
#define __cdecl
#endif

#ifdef _MSC_VER

// 如果是C++程序.
#ifdef __cplusplus
// 按照C编译器的方式编译和连接_assert函数.
extern "C" {
#endif
// _CRTIMP是__attribute__((dllimport)) 
// __attribute__可以为函数声明赋属性值,其目的是让编译程序可以优化处理.
// 关键字__attribute__可以为函数(function attribute),
// 变量(variable attribute)和结构成员(type attribute)赋属性.
_CRTIMP void __cdecl _assert(const char *, const char *, unsigned);

#ifdef __cplusplus
}
#endif

#endif

#ifdef NDEBUG

// release时全部失效.
#define SE_ASSERT(__ignore) ((void)0)
#define SE_ASSERTMSG(__ignore1, __ignore2) ((void)0)
#define SE_ASSERTALWAYS(__ignore) ((void)0)
#define SE_BREAKPOINT ((void)0)
#define SE_SAFEBREAKPOINT ((void)0)
#define SE_IFDEBUG(__ignore) ((void)0)
#define SE_DEBUGSTRING(__ignore) ("")

#else

// debug模式用户断点宏,强制程序中断,可跳过.
#ifdef _MSC_VER
#define SE_SAFEBREAKPOINT try { _asm { int 3 }; } catch(...) {;}
#else
#define SE_SAFEBREAKPOINT ((void)0)
#endif

//----------------------------------------------------------------------------
// debug模式用户断点宏,强制程序中断,不可跳过.
#define SE_BREAKPOINT \
if( 1 ) \
{ \
    SE_SAFEBREAKPOINT; \
    _assert("hard-coded breakpoint", __FILE__, __LINE__); \
}
//----------------------------------------------------------------------------
// CT DEBUG macro,表达式只在debug模式下执行.
#define SE_IFDEBUG(expr) \
expr
//----------------------------------------------------------------------------
// 我们用这个宏代替原来的assert(exp).
#define SE_ASSERT(expr) \
if( !(expr) ) \
{ \
    SE_SAFEBREAKPOINT; \
    _assert(#expr, __FILE__, __LINE__); \
}
//----------------------------------------------------------------------------
// 无条件assert.
#define SE_ASSERTALWAYS(msg) \
if( 1 ) \
{ \
    SE_SAFEBREAKPOINT; \
    _assert(msg, __FILE__, __LINE__); \
}
//----------------------------------------------------------------------------
// 我们用这个宏代替原来的assert(exp),并且可以自定义显示内容.
#define SE_ASSERTMSG(expr, msg) \
if( !(expr) ) \
{ \
    SE_SAFEBREAKPOINT; \
    _assert(msg, __FILE__, __LINE__); \
}
//----------------------------------------------------------------------------
#define SE_DEBUGSTRING(str) (str)
#endif

#endif

