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

#ifndef Swing_WglExtensions_H
#define Swing_WglExtensions_H

#include "SEglExtensions.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>

extern "C"
{

/*--------------------------------------------------------------------------*/
/***** ARB Extensions *****/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 04) WGL_ARB_buffer_region */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsWglArbBufferRegion;

#define WGL_FRONT_COLOR_BUFFER_BIT_ARB                              0x00000001
#define WGL_BACK_COLOR_BUFFER_BIT_ARB                               0x00000002
#define WGL_DEPTH_BUFFER_BIT_ARB                                    0x00000004
#define WGL_STENCIL_BUFFER_BIT_ARB                                  0x00000008

#define wglCreateBufferRegionARB SE_wglCreateBufferRegionARB
#define wglDeleteBufferRegionARB SE_wglDeleteBufferRegionARB
#define wglSaveBufferRegionARB SE_wglSaveBufferRegionARB
#define wglRestoreBufferRegionARB SE_wglRestoreBufferRegionARB

HANDLE SE_wglCreateBufferRegionARB(HDC hDC, int iLayerPlane, UINT uiType);
SE_EXTERN VOID SE_wglDeleteBufferRegionARB(HANDLE hRegion);
SE_EXTERN BOOL SE_wglSaveBufferRegionARB(HANDLE hRegion, int iX, int iY,
    int iWidth, int iHeight);
SE_EXTERN BOOL SE_wglRestoreBufferRegionARB(HANDLE hRegion, int iX, int iY,
    int iWidth, int iHeight, int iXSrc, int iYSrc);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 05) WGL_ARB_multisample */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsWglArbMultisample;

#define WGL_SAMPLE_BUFFERS_ARB                                      0x2041
#define WGL_SAMPLES_ARB                                             0x2042
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 08) WGL_ARB_extensions_string */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsWglArbExtensionsString;

#define wglGetExtensionsStringARB SE_wglGetExtensionsStringARB

SE_EXTERN const char* SE_wglGetExtensionsStringARB(HDC hDC);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 09) WGL_ARB_pixel_format */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsWglArbPixelFormat;

#define WGL_NUMBER_PIXEL_FORMATS_ARB                                0x2000
#define WGL_DRAW_TO_WINDOW_ARB                                      0x2001
#define WGL_DRAW_TO_BITMAP_ARB                                      0x2002
#define WGL_ACCELERATION_ARB                                        0x2003
#define WGL_NEED_PALETTE_ARB                                        0x2004
#define WGL_NEED_SYSTEM_PALETTE_ARB                                 0x2005
#define WGL_SWAP_LAYER_BUFFERS_ARB                                  0x2006
#define WGL_SWAP_METHOD_ARB                                         0x2007
#define WGL_NUMBER_OVERLAYS_ARB                                     0x2008
#define WGL_NUMBER_UNDERLAYS_ARB                                    0x2009
#define WGL_TRANSPARENT_ARB                                         0x200A
#define WGL_TRANSPARENT_RED_VALUE_ARB                               0x2037
#define WGL_TRANSPARENT_GREEN_VALUE_ARB                             0x2038
#define WGL_TRANSPARENT_BLUE_VALUE_ARB                              0x2039
#define WGL_TRANSPARENT_ALPHA_VALUE_ARB                             0x203A
#define WGL_TRANSPARENT_INDEX_VALUE_ARB                             0x203B
#define WGL_SHARE_DEPTH_ARB                                         0x200C
#define WGL_SHARE_STENCIL_ARB                                       0x200D
#define WGL_SHARE_ACCUM_ARB                                         0x200E
#define WGL_SUPPORT_GDI_ARB                                         0x200F
#define WGL_SUPPORT_OPENGL_ARB                                      0x2010
#define WGL_DOUBLE_BUFFER_ARB                                       0x2011
#define WGL_STEREO_ARB                                              0x2012
#define WGL_PIXEL_TYPE_ARB                                          0x2013
#define WGL_COLOR_BITS_ARB                                          0x2014
#define WGL_RED_BITS_ARB                                            0x2015
#define WGL_RED_SHIFT_ARB                                           0x2016
#define WGL_GREEN_BITS_ARB                                          0x2017
#define WGL_GREEN_SHIFT_ARB                                         0x2018
#define WGL_BLUE_BITS_ARB                                           0x2019
#define WGL_BLUE_SHIFT_ARB                                          0x201A
#define WGL_ALPHA_BITS_ARB                                          0x201B
#define WGL_ALPHA_SHIFT_ARB                                         0x201C
#define WGL_ACCUM_BITS_ARB                                          0x201D
#define WGL_ACCUM_RED_BITS_ARB                                      0x201E
#define WGL_ACCUM_GREEN_BITS_ARB                                    0x201F
#define WGL_ACCUM_BLUE_BITS_ARB                                     0x2020
#define WGL_ACCUM_ALPHA_BITS_ARB                                    0x2021
#define WGL_DEPTH_BITS_ARB                                          0x2022
#define WGL_STENCIL_BITS_ARB                                        0x2023
#define WGL_AUX_BUFFERS_ARB                                         0x2024
#define WGL_NO_ACCELERATION_ARB                                     0x2025
#define WGL_GENERIC_ACCELERATION_ARB                                0x2026
#define WGL_FULL_ACCELERATION_ARB                                   0x2027
#define WGL_SWAP_EXCHANGE_ARB                                       0x2028
#define WGL_SWAP_COPY_ARB                                           0x2029
#define WGL_SWAP_UNDEFINED_ARB                                      0x202A
#define WGL_TYPE_RGBA_ARB                                           0x202B
#define WGL_TYPE_COLORINDEX_ARB                                     0x202C

#define wglGetPixelFormatAttribivARB SE_wglGetPixelFormatAttribivARB
#define wglGetPixelFormatAttribfvARB SE_wglGetPixelFormatAttribfvARB
#define wglChoosePixelFormatARB SE_wglChoosePixelFormatARB

SE_EXTERN BOOL SE_wglGetPixelFormatAttribivARB(HDC hDC, int iPixelFormat,
    int iLayerPlane, UINT uiNumAttributes, const int* aiAttribute,
    int* aiValue);
SE_EXTERN BOOL SE_wglGetPixelFormatAttribfvARB(HDC hDC, int iPixelFormat,
    int iLayerPlane, UINT uiNumAttributes, const int* aiAttribute,
    FLOAT* afValue);
SE_EXTERN BOOL SE_wglChoosePixelFormatARB(HDC hDC, const int* aiAttribIList,
    const FLOAT* afAttribFList, UINT uiMaxFormats, int* aiFormat,
    UINT* puiNumFormats);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 10) WGL_ARB_make_current_read */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsWglArbMakeCurrentRead;

#define ERROR_INVALID_PIXEL_TYPE_ARB                                0x2043
#define ERROR_INCOMPATIBLE_DEVICE_CONTEXTS_ARB                      0x2054

#define wglMakeContextCurrentARB SE_wglMakeContextCurrentARB
#define wglGetCurrentReadDCARB SE_wglGetCurrentReadDCARB

SE_EXTERN BOOL SE_wglMakeContextCurrentARB(HDC hDrawDC, HDC hReadDC,
    HGLRC hWindowRC);
SE_EXTERN HDC SE_wglGetCurrentReadDCARB(void);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 11) WGL_ARB_pbuffer */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsWglArbPBuffer;

#define WGL_DRAW_TO_PBUFFER_ARB                                     0x202D
#define WGL_MAX_PBUFFER_PIXELS_ARB                                  0x202E
#define WGL_MAX_PBUFFER_WIDTH_ARB                                   0x202F
#define WGL_MAX_PBUFFER_HEIGHT_ARB                                  0x2030
#define WGL_PBUFFER_LARGEST_ARB                                     0x2033
#define WGL_PBUFFER_WIDTH_ARB                                       0x2034
#define WGL_PBUFFER_HEIGHT_ARB                                      0x2035
#define WGL_PBUFFER_LOST_ARB                                        0x2036
DECLARE_HANDLE(HPBUFFERARB);

#define wglCreatePbufferARB SE_wglCreatePbufferARB
#define wglGetPbufferDCARB SE_wglGetPbufferDCARB
#define wglReleasePbufferDCARB SE_wglReleasePbufferDCARB
#define wglDestroyPbufferARB SE_wglDestroyPbufferARB
#define wglQueryPbufferARB SE_wglQueryPbufferARB

SE_EXTERN HPBUFFERARB SE_wglCreatePbufferARB(HDC hDC, int iPixelFormat,
    int iWidth, int iHeight, const int* aiAttribList);
SE_EXTERN HDC SE_wglGetPbufferDCARB(HPBUFFERARB hPBuffer);
SE_EXTERN int SE_wglReleasePbufferDCARB(HPBUFFERARB hPBuffer, HDC hDC);
SE_EXTERN BOOL SE_wglDestroyPbufferARB(HPBUFFERARB hPBuffer);
SE_EXTERN BOOL SE_wglQueryPbufferARB(HPBUFFERARB hPBuffer, int iAttribute,
    int* piValue);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 20) WGL_ARB_render_texture */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsWglArbRenderTexture;

#define WGL_BIND_TO_TEXTURE_RGB_ARB                                 0x2070
#define WGL_BIND_TO_TEXTURE_RGBA_ARB                                0x2071
#define WGL_TEXTURE_FORMAT_ARB                                      0x2072
#define WGL_TEXTURE_TARGET_ARB                                      0x2073
#define WGL_MIPMAP_TEXTURE_ARB                                      0x2074
#define WGL_TEXTURE_RGB_ARB                                         0x2075
#define WGL_TEXTURE_RGBA_ARB                                        0x2076
#define WGL_NO_TEXTURE_ARB                                          0x2077
#define WGL_TEXTURE_CUBE_MAP_ARB                                    0x2078
#define WGL_TEXTURE_1D_ARB                                          0x2079
#define WGL_TEXTURE_2D_ARB                                          0x207A
#define WGL_MIPMAP_LEVEL_ARB                                        0x207B
#define WGL_CUBE_MAP_FACE_ARB                                       0x207C
#define WGL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB                         0x207D
#define WGL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB                         0x207E
#define WGL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB                         0x207F
#define WGL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB                         0x2080
#define WGL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB                         0x2081
#define WGL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB                         0x2082
#define WGL_FRONT_LEFT_ARB                                          0x2083
#define WGL_FRONT_RIGHT_ARB                                         0x2084
#define WGL_BACK_LEFT_ARB                                           0x2085
#define WGL_BACK_RIGHT_ARB                                          0x2086
#define WGL_AUX0_ARB                                                0x2087
#define WGL_AUX1_ARB                                                0x2088
#define WGL_AUX2_ARB                                                0x2089
#define WGL_AUX3_ARB                                                0x208A
#define WGL_AUX4_ARB                                                0x208B
#define WGL_AUX5_ARB                                                0x208C
#define WGL_AUX6_ARB                                                0x208D
#define WGL_AUX7_ARB                                                0x208E
#define WGL_AUX8_ARB                                                0x208F
#define WGL_AUX9_ARB                                                0x2090

#define wglBindTexImageARB SE_wglBindTexImageARB
#define wglReleaseTexImageARB SE_wglReleaseTexImageARB
#define wglSetPbufferAttribARB SE_wglSetPbufferAttribARB

SE_EXTERN BOOL SE_wglBindTexImageARB(HPBUFFERARB hPBuffer, int iBuffer);
SE_EXTERN BOOL SE_wglReleaseTexImageARB(HPBUFFERARB hPBuffer, int iBuffer);
SE_EXTERN BOOL SE_wglSetPbufferAttribARB(HPBUFFERARB hPBuffer,
    const int* aiAttribList);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 39) WGL_ARB_pixel_format_float */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsWglArbPixelFormatFloat;

#define WGL_TYPE_RGBA_FLOAT_ARB                                     0x21A0
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/***** EXT Extensions *****/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 167) WGL_EXT_display_color_table */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsWglExtDisplayColorTable;

#define wglCreateDisplayColorTableEXT SE_wglCreateDisplayColorTableEXT
#define wglLoadDisplayColorTableEXT SE_wglLoadDisplayColorTableEXT
#define wglBindDisplayColorTableEXT SE_wglBindDisplayColorTableEXT
#define wglDestroyDisplayColorTableEXT SE_wglDestroyDisplayColorTableEXT

SE_EXTERN GLboolean SE_wglCreateDisplayColorTableEXT(GLushort usID);
SE_EXTERN GLboolean SE_wglLoadDisplayColorTableEXT(const GLushort* ausTable,
    GLuint uiLength);
SE_EXTERN GLboolean SE_wglBindDisplayColorTableEXT(GLushort usID);
SE_EXTERN VOID SE_wglDestroyDisplayColorTableEXT(GLushort usID);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 168) WGL_EXT_extensions_string */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsWglExtExtensionsString;

#define wglGetExtensionsStringEXT SE_wglGetExtensionsStringEXT

SE_EXTERN const char* SE_wglGetExtensionsStringEXT(void);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 169) WGL_EXT_make_current_read */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsWglExtMakeCurrentRead;

#define ERROR_INVALID_PIXEL_TYPE_EXT                                0x2043

#define wglMakeContextCurrentEXT SE_wglMakeContextCurrentEXT
#define wglGetCurrentReadDCEXT SE_wglGetCurrentReadDCEXT

SE_EXTERN BOOL SE_wglMakeContextCurrentEXT(HDC hDrawDC, HDC hReadDC,
    HGLRC hWindowRC);
SE_EXTERN HDC SE_wglGetCurrentReadDCEXT(void);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 170) WGL_EXT_pixel_format */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsWglExtPixelFormat;

#define WGL_NUMBER_PIXEL_FORMATS_EXT                                0x2000
#define WGL_DRAW_TO_WINDOW_EXT                                      0x2001
#define WGL_DRAW_TO_BITMAP_EXT                                      0x2002
#define WGL_ACCELERATION_EXT                                        0x2003
#define WGL_NEED_PALETTE_EXT                                        0x2004
#define WGL_NEED_SYSTEM_PALETTE_EXT                                 0x2005
#define WGL_SWAP_LAYER_BUFFERS_EXT                                  0x2006
#define WGL_SWAP_METHOD_EXT                                         0x2007
#define WGL_NUMBER_OVERLAYS_EXT                                     0x2008
#define WGL_NUMBER_UNDERLAYS_EXT                                    0x2009
#define WGL_TRANSPARENT_EXT                                         0x200A
#define WGL_TRANSPARENT_VALUE_EXT                                   0x200B
#define WGL_SHARE_DEPTH_EXT                                         0x200C
#define WGL_SHARE_STENCIL_EXT                                       0x200D
#define WGL_SHARE_ACCUM_EXT                                         0x200E
#define WGL_SUPPORT_GDI_EXT                                         0x200F
#define WGL_SUPPORT_OPENGL_EXT                                      0x2010
#define WGL_DOUBLE_BUFFER_EXT                                       0x2011
#define WGL_STEREO_EXT                                              0x2012
#define WGL_PIXEL_TYPE_EXT                                          0x2013
#define WGL_COLOR_BITS_EXT                                          0x2014
#define WGL_RED_BITS_EXT                                            0x2015
#define WGL_RED_SHIFT_EXT                                           0x2016
#define WGL_GREEN_BITS_EXT                                          0x2017
#define WGL_GREEN_SHIFT_EXT                                         0x2018
#define WGL_BLUE_BITS_EXT                                           0x2019
#define WGL_BLUE_SHIFT_EXT                                          0x201A
#define WGL_ALPHA_BITS_EXT                                          0x201B
#define WGL_ALPHA_SHIFT_EXT                                         0x201C
#define WGL_ACCUM_BITS_EXT                                          0x201D
#define WGL_ACCUM_RED_BITS_EXT                                      0x201E
#define WGL_ACCUM_GREEN_BITS_EXT                                    0x201F
#define WGL_ACCUM_BLUE_BITS_EXT                                     0x2020
#define WGL_ACCUM_ALPHA_BITS_EXT                                    0x2021
#define WGL_DEPTH_BITS_EXT                                          0x2022
#define WGL_STENCIL_BITS_EXT                                        0x2023
#define WGL_AUX_BUFFERS_EXT                                         0x2024
#define WGL_NO_ACCELERATION_EXT                                     0x2025
#define WGL_GENERIC_ACCELERATION_EXT                                0x2026
#define WGL_FULL_ACCELERATION_EXT                                   0x2027
#define WGL_SWAP_EXCHANGE_EXT                                       0x2028
#define WGL_SWAP_COPY_EXT                                           0x2029
#define WGL_SWAP_UNDEFINED_EXT                                      0x202A
#define WGL_TYPE_RGBA_EXT                                           0x202B
#define WGL_TYPE_COLORINDEX_EXT                                     0x202C

#define wglGetPixelFormatAttribivEXT SE_wglGetPixelFormatAttribivEXT
#define wglGetPixelFormatAttribfvEXT SE_wglGetPixelFormatAttribfvEXT
#define wglChoosePixelFormatEXT SE_wglChoosePixelFormatEXT

SE_EXTERN BOOL SE_wglGetPixelFormatAttribivEXT(HDC hDC, int iPixelFormat,
    int iLayerPlane, UINT uiNumAttributes, const int* aiAttribute,
    int* aiValue);
SE_EXTERN BOOL SE_wglGetPixelFormatAttribfvEXT(HDC hDC, int iPixelFormat,
    int iLayerPlane, UINT uiNumAttributes, const int* aiAttribute,
    FLOAT* afValue);
SE_EXTERN BOOL SE_wglChoosePixelFormatEXT(HDC hDC, const int* aiAttribIList,
    const FLOAT* afAttribFList, UINT uiMaxFormats, int* aiFormat,
    UINT* puiNumFormats);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 171) WGL_EXT_pbuffer */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsWglExtPBuffer;

#define WGL_DRAW_TO_PBUFFER_EXT                                     0x202D
#define WGL_MAX_PBUFFER_PIXELS_EXT                                  0x202E
#define WGL_MAX_PBUFFER_WIDTH_EXT                                   0x202F
#define WGL_MAX_PBUFFER_HEIGHT_EXT                                  0x2030
#define WGL_OPTIMAL_PBUFFER_WIDTH_EXT                               0x2031
#define WGL_OPTIMAL_PBUFFER_HEIGHT_EXT                              0x2032
#define WGL_PBUFFER_LARGEST_EXT                                     0x2033
#define WGL_PBUFFER_WIDTH_EXT                                       0x2034
#define WGL_PBUFFER_HEIGHT_EXT                                      0x2035
DECLARE_HANDLE(HPBUFFEREXT);

#define wglCreatePbufferEXT SE_wglCreatePbufferEXT
#define wglGetPbufferDCEXT SE_wglGetPbufferDCEXT
#define wglReleasePbufferDCEXT SE_wglReleasePbufferDCEXT
#define wglDestroyPbufferEXT SE_wglDestroyPbufferEXT
#define wglQueryPbufferEXT SE_wglQueryPbufferEXT

SE_EXTERN HPBUFFEREXT SE_wglCreatePbufferEXT(HDC hDC, int iPixelFormat,
    int iWidth, int iHeight, const int* aiAttribList);
SE_EXTERN HDC SE_wglGetPbufferDCEXT(HPBUFFEREXT hPBuffer);
SE_EXTERN int SE_wglReleasePbufferDCEXT(HPBUFFEREXT hPBuffer, HDC hDC);
SE_EXTERN BOOL SE_wglDestroyPbufferEXT(HPBUFFEREXT hPBuffer);
SE_EXTERN BOOL SE_wglQueryPbufferEXT(HPBUFFEREXT hPBuffer, int iAttribute,
    int* piValue);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 172) WGL_EXT_swap_control */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsWglExtSwapControl;

#define wglSwapIntervalEXT SE_wglSwapIntervalEXT
#define wglGetSwapIntervalEXT SE_wglGetSwapIntervalEXT

SE_EXTERN BOOL SE_wglSwapIntervalEXT(int iInterval);
SE_EXTERN int SE_wglGetSwapIntervalEXT(void);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 177) WGL_EXT_depth_float */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsWglExtDepthFloat;

#define WGL_DEPTH_FLOAT_EXT                                         0x2040
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 209) WGL_EXT_multisample */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsWglExtMultisample;

#define WGL_SAMPLE_BUFFERS_EXT                                      0x2041
#define WGL_SAMPLES_EXT                                             0x2042
/*--------------------------------------------------------------------------*/

SE_EXTERN void SE_WGL_Initialize(const char* acInfoFile);

}

#endif
