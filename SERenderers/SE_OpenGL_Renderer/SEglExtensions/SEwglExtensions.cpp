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

#include "SEwglExtensions.h"
#include "SEglUtility.h"

#if defined(_MSC_VER)
#pragma warning(disable:4127)
#endif

/*--------------------------------------------------------------------------*/
void* SE_GL_GetFunctionPointer(const char* acFunction)
{
    return (void*)wglGetProcAddress(acFunction);
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/***** ARB Extensions *****/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 04) WGL_ARB_buffer_region */
/*--------------------------------------------------------------------------*/
int SE_ExistsWglArbBufferRegion = 0;

typedef HANDLE (STDCALL* PswglCreateBufferRegionARB)(HDC, int, UINT);
typedef VOID (STDCALL* PswglDeleteBufferRegionARB)(HANDLE);
typedef BOOL (STDCALL* PswglSaveBufferRegionARB)(HANDLE, int, int, int, int);
typedef BOOL (STDCALL* PswglRestoreBufferRegionARB)(HANDLE, int, int, int,
    int, int, int);

static PswglCreateBufferRegionARB swglCreateBufferRegionARB = 0;
static PswglDeleteBufferRegionARB swglDeleteBufferRegionARB = 0;
static PswglSaveBufferRegionARB swglSaveBufferRegionARB = 0;
static PswglRestoreBufferRegionARB swglRestoreBufferRegionARB = 0;
/*--------------------------------------------------------------------------*/
HANDLE SE_wglCreateBufferRegionARB(HDC hDC, int iLayerPlane, UINT uiType)
{
    SE_BODY_A3_RET(swglCreateBufferRegionARB, hDC, iLayerPlane, uiType, 
        HANDLE, 0);
}
/*--------------------------------------------------------------------------*/
VOID SE_wglDeleteBufferRegionARB(HANDLE hRegion)
{
    SE_BODY_A1(swglDeleteBufferRegionARB, hRegion);
}
/*--------------------------------------------------------------------------*/
BOOL SE_wglSaveBufferRegionARB(HANDLE hRegion, int iX, int iY, int iWidth,
    int iHeight)
{
    SE_BODY_A5_RET(swglSaveBufferRegionARB, hRegion, iX, iY, iWidth, iHeight, 
        BOOL, FALSE);
}
/*--------------------------------------------------------------------------*/
BOOL SE_wglRestoreBufferRegionARB(HANDLE hRegion, int iX, int iY, int iWidth, 
    int iHeight, int iXSrc, int iYSrc)
{
    SE_BODY_A7_RET(swglRestoreBufferRegionARB, hRegion, iX, iY, iWidth, iHeight, 
        iXSrc, iYSrc, BOOL, FALSE);
}
/*--------------------------------------------------------------------------*/
void SE_InitWglArbBufferRegion()
{
    if( SE_GL_SupportsExtension("WGL_ARB_buffer_region") )
    {
        SE_ExistsWglArbBufferRegion = 1;

        SE_GET_FUNCTION(swglCreateBufferRegionARB);
        SE_GET_FUNCTION(swglDeleteBufferRegionARB);
        SE_GET_FUNCTION(swglSaveBufferRegionARB);
        SE_GET_FUNCTION(swglRestoreBufferRegionARB);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 05) WGL_ARB_multisample */
/*--------------------------------------------------------------------------*/
int SE_ExistsWglArbMultisample = 0;
/*--------------------------------------------------------------------------*/
void SE_InitWglArbMultisample()
{
    if( SE_GL_SupportsExtension("WGL_ARB_multisample") )
    {
        SE_ExistsWglArbMultisample = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 08) WGL_ARB_extensions_string */
/*--------------------------------------------------------------------------*/
int SE_ExistsWglArbExtensionsString = 0;

typedef const char* (STDCALL* PswglGetExtensionsStringARB)(HDC);

static PswglGetExtensionsStringARB swglGetExtensionsStringARB = 0;
/*--------------------------------------------------------------------------*/
const char* SE_wglGetExtensionsStringARB(HDC hDC)
{
    SE_BODY_A1_RET(swglGetExtensionsStringARB, hDC, const char*, 0);
}
/*--------------------------------------------------------------------------*/
void SE_InitWglArbExtensionsString()
{
    if( SE_GL_SupportsExtension("WGL_ARB_extensions_string") )
    {
        SE_ExistsWglArbExtensionsString = 1;

        SE_GET_FUNCTION(swglGetExtensionsStringARB);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 09) WGL_ARB_pixel_format */
/*--------------------------------------------------------------------------*/
int SE_ExistsWglArbPixelFormat = 0;

typedef BOOL (STDCALL* PswglGetPixelFormatAttribivARB)(HDC, int, int, UINT,
    const int*, int*);
typedef BOOL (STDCALL* PswglGetPixelFormatAttribfvARB)(HDC, int, int, UINT,
    const int*, FLOAT*);
typedef BOOL (STDCALL* PswglChoosePixelFormatARB)(HDC, const int*,
    const FLOAT*, UINT, int*, UINT*);

static PswglGetPixelFormatAttribivARB swglGetPixelFormatAttribivARB = 0;
static PswglGetPixelFormatAttribfvARB swglGetPixelFormatAttribfvARB = 0;
static PswglChoosePixelFormatARB swglChoosePixelFormatARB = 0;
/*--------------------------------------------------------------------------*/
BOOL SE_wglGetPixelFormatAttribivARB(HDC hDC, int iPixelFormat,
    int iLayerPlane, UINT uiNumAttributes, const int* aiAttribute,
    int* aiValue)
{
    SE_BODY_A6_RET(swglGetPixelFormatAttribivARB, hDC, iPixelFormat, iLayerPlane, 
        uiNumAttributes, aiAttribute, aiValue, BOOL, FALSE);
}
/*--------------------------------------------------------------------------*/
BOOL SE_wglGetPixelFormatAttribfvARB(HDC hDC, int iPixelFormat, 
    int iLayerPlane, UINT uiNumAttributes, const int* aiAttribute, 
    FLOAT* afValue)
{
    SE_BODY_A6_RET(swglGetPixelFormatAttribfvARB, hDC, iPixelFormat, iLayerPlane, 
        uiNumAttributes, aiAttribute, afValue, BOOL, FALSE);
}
/*--------------------------------------------------------------------------*/
BOOL SE_wglChoosePixelFormatARB(HDC hDC, const int* aiAttribIList, 
    const FLOAT* afAttribFList, UINT uiMaxFormats, int* aiFormat, 
    UINT* puiNumFormats)
{
    SE_BODY_A6_RET(swglChoosePixelFormatARB, hDC, aiAttribIList, afAttribFList, 
        uiMaxFormats, aiFormat, puiNumFormats, BOOL, FALSE);
}
/*--------------------------------------------------------------------------*/
void SE_InitWglArbPixelFormat()
{
    if( SE_GL_SupportsExtension("WGL_ARB_pixel_format") )
    {
        SE_ExistsWglArbPixelFormat = 1;

        SE_GET_FUNCTION(swglGetPixelFormatAttribivARB);
        SE_GET_FUNCTION(swglGetPixelFormatAttribfvARB);
        SE_GET_FUNCTION(swglChoosePixelFormatARB);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 10) WGL_ARB_make_current_read */
/*--------------------------------------------------------------------------*/
int SE_ExistsWglArbMakeCurrentRead = 0;

typedef BOOL (STDCALL* PswglMakeContextCurrentARB)(HDC, HDC, HGLRC);
typedef HDC (STDCALL* PswglGetCurrentReadDCARB)(void);

static PswglMakeContextCurrentARB swglMakeContextCurrentARB = 0;
static PswglGetCurrentReadDCARB swglGetCurrentReadDCARB = 0;
/*--------------------------------------------------------------------------*/
BOOL SE_wglMakeContextCurrentARB(HDC hDrawDC, HDC hReadDC, HGLRC hWindowRC)
{
    SE_BODY_A3_RET(swglMakeContextCurrentARB, hDrawDC, hReadDC, hWindowRC,
        BOOL, FALSE);
}
/*--------------------------------------------------------------------------*/
HDC SE_wglGetCurrentReadDCARB()
{
    SE_BODY_A0_RET(swglGetCurrentReadDCARB, HDC, 0);
}
/*--------------------------------------------------------------------------*/
void SE_InitWglArbMakeCurrentRead()
{
    if( SE_GL_SupportsExtension("WGL_ARB_make_current_read") )
    {
        SE_ExistsWglArbMakeCurrentRead = 1;

        SE_GET_FUNCTION(swglMakeContextCurrentARB);
        SE_GET_FUNCTION(swglGetCurrentReadDCARB);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 11) WGL_ARB_pbuffer */
/*--------------------------------------------------------------------------*/
int SE_ExistsWglArbPBuffer = 0;

typedef HPBUFFERARB (STDCALL* PswglCreatePbufferARB)(HDC, int, int, int,
    const int*);
typedef HDC (STDCALL* PswglGetPbufferDCARB)(HPBUFFERARB);
typedef int (STDCALL* PswglReleasePbufferDCARB)(HPBUFFERARB, HDC);
typedef BOOL (STDCALL* PswglDestroyPbufferARB)(HPBUFFERARB);
typedef BOOL (STDCALL* PswglQueryPbufferARB)(HPBUFFERARB, int, int*);

static PswglCreatePbufferARB swglCreatePbufferARB = 0;
static PswglGetPbufferDCARB swglGetPbufferDCARB = 0;
static PswglReleasePbufferDCARB swglReleasePbufferDCARB = 0;
static PswglDestroyPbufferARB swglDestroyPbufferARB = 0;
static PswglQueryPbufferARB swglQueryPbufferARB = 0;
/*--------------------------------------------------------------------------*/
HPBUFFERARB SE_wglCreatePbufferARB(HDC hDC, int iPixelFormat, int iWidth,
    int iHeight, const int* aiAttribList)
{
    SE_BODY_A5_RET(swglCreatePbufferARB, hDC, iPixelFormat, iWidth, iHeight,
        aiAttribList, HPBUFFERARB, 0);
}
/*--------------------------------------------------------------------------*/
HDC SE_wglGetPbufferDCARB(HPBUFFERARB hPBuffer)
{
    SE_BODY_A1_RET(swglGetPbufferDCARB, hPBuffer, HDC, 0);
}
/*--------------------------------------------------------------------------*/
int SE_wglReleasePbufferDCARB(HPBUFFERARB hPBuffer, HDC hDC)
{
    SE_BODY_A2_RET(swglReleasePbufferDCARB, hPBuffer, hDC, int, 0);
}
/*--------------------------------------------------------------------------*/
BOOL SE_wglDestroyPbufferARB(HPBUFFERARB hPBuffer)
{
    SE_BODY_A1_RET(swglDestroyPbufferARB, hPBuffer, BOOL, FALSE);
}
/*--------------------------------------------------------------------------*/
BOOL SE_wglQueryPbufferARB(HPBUFFERARB hPBuffer, int iAttribute,
    int* piValue)
{
    SE_BODY_A3_RET(swglQueryPbufferARB, hPBuffer, iAttribute, piValue, BOOL,
        FALSE);
}
/*--------------------------------------------------------------------------*/
void SE_InitWglArbPBuffer()
{
    if( SE_GL_SupportsExtension("WGL_ARB_pbuffer") )
    {
        SE_ExistsWglArbPBuffer = 1;

        SE_GET_FUNCTION(swglCreatePbufferARB);
        SE_GET_FUNCTION(swglGetPbufferDCARB);
        SE_GET_FUNCTION(swglReleasePbufferDCARB);
        SE_GET_FUNCTION(swglDestroyPbufferARB);
        SE_GET_FUNCTION(swglQueryPbufferARB);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 20) WGL_ARB_render_texture */
/*--------------------------------------------------------------------------*/
int SE_ExistsWglArbRenderTexture = 0;

typedef BOOL (STDCALL* PswglBindTexImageARB)(HPBUFFERARB, int);
typedef BOOL (STDCALL* PswglReleaseTexImageARB)(HPBUFFERARB, int);
typedef BOOL (STDCALL* PswglSetPbufferAttribARB)(HPBUFFERARB, const int*);

static PswglBindTexImageARB swglBindTexImageARB = 0;
static PswglReleaseTexImageARB swglReleaseTexImageARB = 0;
static PswglSetPbufferAttribARB swglSetPbufferAttribARB = 0;
/*--------------------------------------------------------------------------*/
BOOL SE_wglBindTexImageARB(HPBUFFERARB hPBuffer, int iBuffer)
{
    SE_BODY_A2_RET(swglBindTexImageARB, hPBuffer, iBuffer, BOOL, FALSE);
}
/*--------------------------------------------------------------------------*/
BOOL SE_wglReleaseTexImageARB(HPBUFFERARB hPBuffer, int iBuffer)
{
    SE_BODY_A2_RET(swglReleaseTexImageARB, hPBuffer, iBuffer, BOOL, FALSE);
}
/*--------------------------------------------------------------------------*/
BOOL SE_wglSetPbufferAttribARB(HPBUFFERARB hPBuffer, const int* aiAttribList)
{
    SE_BODY_A2_RET(swglSetPbufferAttribARB, hPBuffer, aiAttribList, BOOL, FALSE);
}
/*--------------------------------------------------------------------------*/
void SE_InitWglArbRenderTexture()
{
    if( SE_GL_SupportsExtension("WGL_ARB_render_texture") )
    {
        SE_ExistsWglArbRenderTexture = 1;

        SE_GET_FUNCTION(swglBindTexImageARB);
        SE_GET_FUNCTION(swglReleaseTexImageARB);
        SE_GET_FUNCTION(swglSetPbufferAttribARB);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 39) WGL_ARB_pixel_format_float */
/*--------------------------------------------------------------------------*/
int SE_ExistsWglArbPixelFormatFloat = 0;
/*--------------------------------------------------------------------------*/
void SE_InitWglArbPixelFormatFloat()
{
    if( SE_GL_SupportsExtension("WGL_ARB_pixel_format_float") )
    {
        SE_ExistsWglArbPixelFormatFloat = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/***** EXT Extensions *****/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 167) WGL_EXT_display_color_table */
/*--------------------------------------------------------------------------*/
int SE_ExistsWglExtDisplayColorTable = 0;

typedef GLboolean (STDCALL* PswglCreateDisplayColorTableEXT)(GLushort);
typedef GLboolean (STDCALL* PswglLoadDisplayColorTableEXT)(const GLushort*,
    GLuint);
typedef GLboolean (STDCALL* PswglBindDisplayColorTableEXT)(GLushort);
typedef VOID (STDCALL* PswglDestroyDisplayColorTableEXT)(GLushort);

static PswglCreateDisplayColorTableEXT swglCreateDisplayColorTableEXT = 0;
static PswglLoadDisplayColorTableEXT swglLoadDisplayColorTableEXT = 0;
static PswglBindDisplayColorTableEXT swglBindDisplayColorTableEXT = 0;
static PswglDestroyDisplayColorTableEXT swglDestroyDisplayColorTableEXT = 0;
/*--------------------------------------------------------------------------*/
GLboolean SE_wglCreateDisplayColorTableEXT(GLushort usID)
{
    SE_BODY_A1_RET(swglCreateDisplayColorTableEXT, usID, GLboolean, 0);
}
/*--------------------------------------------------------------------------*/
GLboolean SE_wglLoadDisplayColorTableEXT(const GLushort* ausTable, 
    GLuint uiLength)
{
    SE_BODY_A2_RET(swglLoadDisplayColorTableEXT, ausTable, uiLength, GLboolean, 
        0);
}
/*--------------------------------------------------------------------------*/
GLboolean SE_wglBindDisplayColorTableEXT(GLushort usID)
{
    SE_BODY_A1_RET(swglBindDisplayColorTableEXT, usID, GLboolean, 0);
}
/*--------------------------------------------------------------------------*/
VOID SE_wglDestroyDisplayColorTableEXT(GLushort usID)
{
    SE_BODY_A1(swglDestroyDisplayColorTableEXT, usID);
}
/*--------------------------------------------------------------------------*/
void SE_InitWglExtDisplayColorTable()
{
    if( SE_GL_SupportsExtension("WGL_EXT_display_color_table") )
    {
        SE_ExistsWglExtDisplayColorTable = 1;

        SE_GET_FUNCTION(swglCreateDisplayColorTableEXT);
        SE_GET_FUNCTION(swglLoadDisplayColorTableEXT);
        SE_GET_FUNCTION(swglBindDisplayColorTableEXT);
        SE_GET_FUNCTION(swglDestroyDisplayColorTableEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 168) WGL_EXT_extensions_string */
/*--------------------------------------------------------------------------*/
int SE_ExistsWglExtExtensionsString = 0;

typedef const char* (STDCALL* PswglGetExtensionsStringEXT)(void);

static PswglGetExtensionsStringEXT swglGetExtensionsStringEXT = 0;
/*--------------------------------------------------------------------------*/
const char* SE_wglGetExtensionsStringEXT ()
{
    SE_BODY_A0_RET(swglGetExtensionsStringEXT,const char*,0);
}
/*--------------------------------------------------------------------------*/
void SE_InitWglExtExtensionsString ()
{
    if(SE_GL_SupportsExtension("WGL_EXT_extensions_string"))
    {
        SE_ExistsWglExtExtensionsString = 1;
        SE_GET_FUNCTION(swglGetExtensionsStringEXT);
        if(SE_EXT_OVERRIDE && !swglGetExtensionsStringARB)
        {
            swglGetExtensionsStringARB =
                (PswglGetExtensionsStringARB)swglGetExtensionsStringEXT;
        }
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 169) WGL_EXT_make_current_read */
/*--------------------------------------------------------------------------*/
int SE_ExistsWglExtMakeCurrentRead = 0;

typedef BOOL (STDCALL* PswglMakeContextCurrentEXT)(HDC, HDC, HGLRC);
typedef HDC (STDCALL* PswglGetCurrentReadDCEXT)(void);

static PswglMakeContextCurrentEXT swglMakeContextCurrentEXT = 0;
static PswglGetCurrentReadDCEXT swglGetCurrentReadDCEXT = 0;
/*--------------------------------------------------------------------------*/
BOOL SE_wglMakeContextCurrentEXT(HDC hDrawDC, HDC hReadDC, HGLRC hWindowRC)
{
    SE_BODY_A3_RET(swglMakeContextCurrentEXT, hDrawDC, hReadDC, hWindowRC, BOOL,
        FALSE);
}
/*--------------------------------------------------------------------------*/
HDC SE_wglGetCurrentReadDCEXT()
{
    SE_BODY_A0_RET(swglGetCurrentReadDCEXT,HDC,0);
}
/*--------------------------------------------------------------------------*/
void SE_InitWglExtMakeCurrentRead()
{
    if( SE_GL_SupportsExtension("WGL_EXT_make_current_read") )
    {
        SE_ExistsWglExtMakeCurrentRead = 1;

        SE_GET_FUNCTION(swglMakeContextCurrentEXT);
        if( SE_EXT_OVERRIDE && !swglMakeContextCurrentARB )
        {
            swglMakeContextCurrentARB =
                (PswglMakeContextCurrentARB)swglMakeContextCurrentEXT;
        }

        SE_GET_FUNCTION(swglGetCurrentReadDCEXT);
        if( SE_EXT_OVERRIDE && !swglGetCurrentReadDCARB )
        {
            swglGetCurrentReadDCARB =
                (PswglGetCurrentReadDCARB)swglGetCurrentReadDCEXT;
        }
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 170) WGL_EXT_pixel_format */
/*--------------------------------------------------------------------------*/
int SE_ExistsWglExtPixelFormat = 0;

typedef BOOL (STDCALL* PswglGetPixelFormatAttribivEXT)(HDC, int, int, UINT,
    const int*, int*);
typedef BOOL (STDCALL* PswglGetPixelFormatAttribfvEXT)(HDC, int, int, UINT,
    const int*, FLOAT*);
typedef BOOL (STDCALL* PswglChoosePixelFormatEXT)(HDC, const int*,
    const FLOAT*, UINT, int*, UINT*);

static PswglGetPixelFormatAttribivEXT swglGetPixelFormatAttribivEXT = 0;
static PswglGetPixelFormatAttribfvEXT swglGetPixelFormatAttribfvEXT = 0;
static PswglChoosePixelFormatEXT swglChoosePixelFormatEXT = 0;
/*--------------------------------------------------------------------------*/
BOOL SE_wglGetPixelFormatAttribivEXT(HDC hDC, int iPixelFormat,
    int iLayerPlane, UINT uiNumAttributes, const int* aiAttribute,
    int* aiValue)
{
    SE_BODY_A6_RET(swglGetPixelFormatAttribivEXT, hDC, iPixelFormat, iLayerPlane, 
        uiNumAttributes, aiAttribute, aiValue, BOOL, FALSE);
}
/*--------------------------------------------------------------------------*/
BOOL SE_wglGetPixelFormatAttribfvEXT(HDC hDC, int iPixelFormat, 
    int iLayerPlane, UINT uiNumAttributes, const int* aiAttribute, 
    FLOAT* afValue)
{
    SE_BODY_A6_RET(swglGetPixelFormatAttribfvEXT, hDC, iPixelFormat, iLayerPlane, 
        uiNumAttributes, aiAttribute, afValue, BOOL, FALSE);
}
/*--------------------------------------------------------------------------*/
BOOL SE_wglChoosePixelFormatEXT(HDC hDC, const int* aiAttribIList, 
    const FLOAT* afAttribFList, UINT uiMaxFormats, int* aiFormat, 
    UINT* puiNumFormats)
{
    SE_BODY_A6_RET(swglChoosePixelFormatEXT, hDC, aiAttribIList, afAttribFList, 
        uiMaxFormats, aiFormat, puiNumFormats, BOOL, FALSE);
}
/*--------------------------------------------------------------------------*/
void SE_InitWglExtPixelFormat()
{
    if( SE_GL_SupportsExtension("WGL_EXT_pixel_format") )
    {
        SE_ExistsWglExtPixelFormat = 1;

        SE_GET_FUNCTION(swglGetPixelFormatAttribivEXT);
        if( SE_EXT_OVERRIDE && !swglGetPixelFormatAttribivARB )
        {
            swglGetPixelFormatAttribivARB =
                (PswglGetPixelFormatAttribivARB)swglGetPixelFormatAttribivEXT;
        }

        SE_GET_FUNCTION(swglGetPixelFormatAttribfvEXT);
        if( SE_EXT_OVERRIDE && !swglGetPixelFormatAttribfvARB )
        {
            swglGetPixelFormatAttribfvARB =
                (PswglGetPixelFormatAttribfvARB)swglGetPixelFormatAttribfvEXT;
        }

        SE_GET_FUNCTION(swglChoosePixelFormatEXT);
        if( SE_EXT_OVERRIDE && !swglChoosePixelFormatARB )
        {
            swglChoosePixelFormatARB =
                (PswglChoosePixelFormatARB)swglChoosePixelFormatEXT;
        }
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 171) WGL_EXT_pbuffer */
/*--------------------------------------------------------------------------*/
int SE_ExistsWglExtPBuffer = 0;

typedef HPBUFFEREXT (STDCALL* PswglCreatePbufferEXT)(HDC, int, int, int,
    const int*);
typedef HDC (STDCALL* PswglGetPbufferDCEXT)(HPBUFFEREXT);
typedef int (STDCALL* PswglReleasePbufferDCEXT)(HPBUFFEREXT, HDC);
typedef BOOL (STDCALL* PswglDestroyPbufferEXT)(HPBUFFEREXT);
typedef BOOL (STDCALL* PswglQueryPbufferEXT)(HPBUFFEREXT, int, int*);

static PswglCreatePbufferEXT swglCreatePbufferEXT = 0;
static PswglGetPbufferDCEXT swglGetPbufferDCEXT = 0;
static PswglReleasePbufferDCEXT swglReleasePbufferDCEXT = 0;
static PswglDestroyPbufferEXT swglDestroyPbufferEXT = 0;
static PswglQueryPbufferEXT swglQueryPbufferEXT = 0;
/*--------------------------------------------------------------------------*/
HPBUFFEREXT SE_wglCreatePbufferEXT(HDC hDC, int iPixelFormat, int iWidth, 
    int iHeight, const int* aiAttribList)
{
    SE_BODY_A5_RET(swglCreatePbufferEXT, hDC, iPixelFormat, iWidth, iHeight, 
        aiAttribList, HPBUFFEREXT, 0);
}
/*--------------------------------------------------------------------------*/
HDC SE_wglGetPbufferDCEXT(HPBUFFEREXT hPBuffer)
{
    SE_BODY_A1_RET(swglGetPbufferDCEXT, hPBuffer, HDC, 0);
}
/*--------------------------------------------------------------------------*/
int SE_wglReleasePbufferDCEXT(HPBUFFEREXT hPBuffer, HDC hDC)
{
    SE_BODY_A2_RET(swglReleasePbufferDCEXT, hPBuffer, hDC, int, 0);
}
/*--------------------------------------------------------------------------*/
BOOL SE_wglDestroyPbufferEXT(HPBUFFEREXT hPBuffer)
{
    SE_BODY_A1_RET(swglDestroyPbufferEXT, hPBuffer, BOOL, FALSE);
}
/*--------------------------------------------------------------------------*/
BOOL SE_wglQueryPbufferEXT(HPBUFFEREXT hPBuffer, int iAttribute, 
    int* piValue)
{
    SE_BODY_A3_RET(swglQueryPbufferEXT, hPBuffer, iAttribute, piValue, BOOL, 
        FALSE);
}
/*--------------------------------------------------------------------------*/
void SE_InitWglExtPBuffer()
{
    if( SE_GL_SupportsExtension("WGL_EXT_pbuffer") )
    {
        SE_ExistsWglExtPBuffer = 1;

        SE_GET_FUNCTION(swglCreatePbufferEXT);
        if( SE_EXT_OVERRIDE && !swglCreatePbufferARB )
        {
            swglCreatePbufferARB =
                (PswglCreatePbufferARB)swglCreatePbufferEXT;
        }

        SE_GET_FUNCTION(swglGetPbufferDCEXT);
        if( SE_EXT_OVERRIDE && !swglGetPbufferDCARB )
        {
            swglGetPbufferDCARB =
                (PswglGetPbufferDCARB)swglGetPbufferDCEXT;
        }

        SE_GET_FUNCTION(swglReleasePbufferDCEXT);
        if( SE_EXT_OVERRIDE && !swglReleasePbufferDCARB )
        {
            swglReleasePbufferDCARB =
                (PswglReleasePbufferDCARB)swglReleasePbufferDCEXT;
        }

        SE_GET_FUNCTION(swglDestroyPbufferEXT);
        if( SE_EXT_OVERRIDE && !swglDestroyPbufferARB )
        {
            swglDestroyPbufferARB =
                (PswglDestroyPbufferARB)swglDestroyPbufferEXT;
        }

        SE_GET_FUNCTION(swglQueryPbufferEXT);
        if( SE_EXT_OVERRIDE && !swglQueryPbufferARB )
        {
            swglQueryPbufferARB =
                (PswglQueryPbufferARB)swglQueryPbufferEXT;
        }
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 172) WGL_EXT_swap_control */
/*--------------------------------------------------------------------------*/
int SE_ExistsWglExtSwapControl = 0;

typedef BOOL (STDCALL* PswglSwapIntervalEXT)(int);
typedef int (STDCALL* PswglGetSwapIntervalEXT)(void);

static PswglSwapIntervalEXT swglSwapIntervalEXT = 0;
static PswglGetSwapIntervalEXT swglGetSwapIntervalEXT = 0;
/*--------------------------------------------------------------------------*/
BOOL SE_wglSwapIntervalEXT(int iInterval)
{
    SE_BODY_A1_RET(swglSwapIntervalEXT, iInterval, BOOL, FALSE);
}
/*--------------------------------------------------------------------------*/
int SE_wglGetSwapIntervalEXT()
{
    SE_BODY_A0_RET(swglGetSwapIntervalEXT, int, 0);
}
/*--------------------------------------------------------------------------*/
void SE_InitWglExtSwapControl()
{
    if( SE_GL_SupportsExtension("WGL_EXT_swap_control") )
    {
        SE_ExistsWglExtSwapControl = 1;

        SE_GET_FUNCTION(swglSwapIntervalEXT);
        SE_GET_FUNCTION(swglGetSwapIntervalEXT);
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 177) WGL_EXT_depth_float */
/*--------------------------------------------------------------------------*/
int SE_ExistsWglExtDepthFloat = 0;
/*--------------------------------------------------------------------------*/
void SE_InitWglExtDepthFloat()
{
    if( SE_GL_SupportsExtension("WGL_EXT_depth_float") )
    {
        SE_ExistsWglExtDepthFloat = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 209) WGL_EXT_multisample */
/*--------------------------------------------------------------------------*/
int SE_ExistsWglExtMultisample = 0;
/*--------------------------------------------------------------------------*/
void SE_InitWglExtMultisample()
{
    if( SE_GL_SupportsExtension("WGL_EXT_multisample") )
    {
        SE_ExistsWglExtMultisample = 1;
    }
}
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* WGL系统初始化 */
/*--------------------------------------------------------------------------*/
void SE_WGL_Initialize(const char* acInfoFile)
{
    SE_GL_Initialize(acInfoFile);

    SE_InitWglArbBufferRegion();
    SE_InitWglArbMultisample();
    SE_InitWglArbExtensionsString();
    SE_InitWglArbPixelFormat();
    SE_InitWglArbMakeCurrentRead();
    SE_InitWglArbPBuffer();
    SE_InitWglArbRenderTexture();
    SE_InitWglArbPixelFormatFloat();

    SE_InitWglExtDisplayColorTable();
    SE_InitWglExtExtensionsString();
    SE_InitWglExtMakeCurrentRead();
    SE_InitWglExtPixelFormat();
    SE_InitWglExtPBuffer();
    SE_InitWglExtSwapControl();
    SE_InitWglExtDepthFloat();
    SE_InitWglExtMultisample();
}
/*--------------------------------------------------------------------------*/
