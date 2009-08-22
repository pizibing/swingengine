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

/*
OpenGL作为跨平台图形API,在各个具体平台上都有平台SDK的支持.
但针对具体平台,其平台SDK默认支持的OpenGL版本不尽相同.
例如,Microsoft Windows的Visual Studio.net 2003的gl.h,glu.h只支持到OpenGL 1.1,
其默认OpenGL库opengl32.lib,glu32.lib与之对应.
当需要使用高版本OpenGL库时,需要与之对应的gl.h,glu.h和gl.lib,glu.lib.
通常新版本的库文件由显示设备驱动所提供,在程序运行时刻动态替代旧有平台SDK的库实现.
由平台SDK提供新版本库的访问接口供应用程序调用.

我们把所需要的gl.h,glu.h信息提取封装,使渲染器程序调用OpenGL库函数时能通过编译,
从而实现平台SDK无关性.
OpenGL 1.1版的具体现实,我们通过静态链接的方式指定,从而使程序编译后能够成功链接.
高于OpenGL1.1版的具体实现,我们通过动态链接的方式指定,通过平台SDK提供的访问接口,
在程序运行时刻初始化阶段获取OpenGL库函数指针,从而使程序编译后不需静态链接.

OpenGL是基于C语言实现的具备扩展能力的多版本并存图形库,与DirectX的COM机制完全不同.

OpenGL Architecture Review Board,简称ARB,是OpenGL的官方架构评估组织,
不定期的对OpenGL做功能扩展,扩展实现的库函数和宏定义,以ARB后缀命名.
OpenGL EXT,是由2个或2个以上开发商达成共识后进行的OpenGL功能扩展,
扩展实现的库函数和宏定义,以EXT后缀命名.
我们跟踪OpenGL的最新版本,ARB扩展,EXT扩展,或某开发商发布的扩展.
相关信息发布位置:
http://www.opengl.org/registry/
*/

#ifndef Swing_GLExtensions_H
#define Swing_GLExtensions_H

#if defined(__gl_h_) || defined(__GL_H__)
#error gl.h included before SEglExtensions.h
#endif
#if defined(__glext_h_) || defined(__GLEXT_H_)
#error glext.h included before SEglExtensions.h
#endif
#if defined(__gl_ATI_h_)
#error glATI.h included before SEglExtensions.h
#endif
#define __gl_h_
#define __GL_H__
#define __glext_h_
#define __GLEXT_H_
#define __gl_ATI_h_

#ifdef WIN32
/* Microsoft Windows */
#ifdef SE_RENDERER_DLL_EXPORT
#define SE_EXTERN extern __declspec(dllexport)
#else
#ifdef SE_RENDERER_DLL_IMPORT
#define SE_EXTERN extern __declspec(dllimport)
#else
#define SE_EXTERN extern
#endif
#endif
#else
/* Macintosh, Linux */
#define SE_EXTERN extern
#endif

#include <cstddef>
extern "C"
{

/*--------------------------------------------------------------------------*/
/* OpenGL 1.1 */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsOpenGL11;

#define GL_ACCUM                                                    0x0100
#define GL_LOAD                                                     0x0101
#define GL_RETURN                                                   0x0102
#define GL_MULT                                                     0x0103
#define GL_ADD                                                      0x0104
#define GL_NEVER                                                    0x0200
#define GL_LESS                                                     0x0201
#define GL_EQUAL                                                    0x0202
#define GL_LEQUAL                                                   0x0203
#define GL_GREATER                                                  0x0204
#define GL_NOTEQUAL                                                 0x0205
#define GL_GEQUAL                                                   0x0206
#define GL_ALWAYS                                                   0x0207
#define GL_CURRENT_BIT                                              0x00000001
#define GL_POINT_BIT                                                0x00000002
#define GL_LINE_BIT                                                 0x00000004
#define GL_POLYGON_BIT                                              0x00000008
#define GL_POLYGON_STIPPLE_BIT                                      0x00000010
#define GL_PIXEL_MODE_BIT                                           0x00000020
#define GL_LIGHTING_BIT                                             0x00000040
#define GL_FOG_BIT                                                  0x00000080
#define GL_DEPTH_BUFFER_BIT                                         0x00000100
#define GL_ACCUM_BUFFER_BIT                                         0x00000200
#define GL_STENCIL_BUFFER_BIT                                       0x00000400
#define GL_VIEWPORT_BIT                                             0x00000800
#define GL_TRANSFORM_BIT                                            0x00001000
#define GL_ENABLE_BIT                                               0x00002000
#define GL_COLOR_BUFFER_BIT                                         0x00004000
#define GL_HINT_BIT                                                 0x00008000
#define GL_EVAL_BIT                                                 0x00010000
#define GL_LIST_BIT                                                 0x00020000
#define GL_TEXTURE_BIT                                              0x00040000
#define GL_SCISSOR_BIT                                              0x00080000
#define GL_ALL_ATTRIB_BITS                                          0x000fffff
#define GL_POINTS                                                   0x0000
#define GL_LINES                                                    0x0001
#define GL_LINE_LOOP                                                0x0002
#define GL_LINE_STRIP                                               0x0003
#define GL_TRIANGLES                                                0x0004
#define GL_TRIANGLE_STRIP                                           0x0005
#define GL_TRIANGLE_FAN                                             0x0006
#define GL_QUADS                                                    0x0007
#define GL_QUAD_STRIP                                               0x0008
#define GL_POLYGON                                                  0x0009
#define GL_ZERO                                                     0
#define GL_ONE                                                      1
#define GL_SRC_COLOR                                                0x0300
#define GL_ONE_MINUS_SRC_COLOR                                      0x0301
#define GL_SRC_ALPHA                                                0x0302
#define GL_ONE_MINUS_SRC_ALPHA                                      0x0303
#define GL_DST_ALPHA                                                0x0304
#define GL_ONE_MINUS_DST_ALPHA                                      0x0305
#define GL_DST_COLOR                                                0x0306
#define GL_ONE_MINUS_DST_COLOR                                      0x0307
#define GL_SRC_ALPHA_SATURATE                                       0x0308
#define GL_TRUE                                                     1
#define GL_FALSE                                                    0
#define GL_CLIP_PLANE0                                              0x3000
#define GL_CLIP_PLANE1                                              0x3001
#define GL_CLIP_PLANE2                                              0x3002
#define GL_CLIP_PLANE3                                              0x3003
#define GL_CLIP_PLANE4                                              0x3004
#define GL_CLIP_PLANE5                                              0x3005
#define GL_BYTE                                                     0x1400
#define GL_UNSIGNED_BYTE                                            0x1401
#define GL_SHORT                                                    0x1402
#define GL_UNSIGNED_SHORT                                           0x1403
#define GL_INT                                                      0x1404
#define GL_UNSIGNED_INT                                             0x1405
#define GL_FLOAT                                                    0x1406
#define GL_2_BYTES                                                  0x1407
#define GL_3_BYTES                                                  0x1408
#define GL_4_BYTES                                                  0x1409
#define GL_DOUBLE                                                   0x140A
#define GL_NONE                                                     0
#define GL_FRONT_LEFT                                               0x0400
#define GL_FRONT_RIGHT                                              0x0401
#define GL_BACK_LEFT                                                0x0402
#define GL_BACK_RIGHT                                               0x0403
#define GL_FRONT                                                    0x0404
#define GL_BACK                                                     0x0405
#define GL_LEFT                                                     0x0406
#define GL_RIGHT                                                    0x0407
#define GL_FRONT_AND_BACK                                           0x0408
#define GL_AUX0                                                     0x0409
#define GL_AUX1                                                     0x040A
#define GL_AUX2                                                     0x040B
#define GL_AUX3                                                     0x040C
#define GL_NO_ERROR                                                 0
#define GL_INVALID_ENUM                                             0x0500
#define GL_INVALID_VALUE                                            0x0501
#define GL_INVALID_OPERATION                                        0x0502
#define GL_STACK_OVERFLOW                                           0x0503
#define GL_STACK_UNDERFLOW                                          0x0504
#define GL_OUT_OF_MEMORY                                            0x0505
#define GL_2D                                                       0x0600
#define GL_3D                                                       0x0601
#define GL_3D_COLOR                                                 0x0602
#define GL_3D_COLOR_TEXTURE                                         0x0603
#define GL_4D_COLOR_TEXTURE                                         0x0604
#define GL_PASS_THROUGH_TOKEN                                       0x0700
#define GL_POINT_TOKEN                                              0x0701
#define GL_LINE_TOKEN                                               0x0702
#define GL_POLYGON_TOKEN                                            0x0703
#define GL_BITMAP_TOKEN                                             0x0704
#define GL_DRAW_PIXEL_TOKEN                                         0x0705
#define GL_COPY_PIXEL_TOKEN                                         0x0706
#define GL_LINE_RESET_TOKEN                                         0x0707
#define GL_EXP                                                      0x0800
#define GL_EXP2                                                     0x0801
#define GL_CW                                                       0x0900
#define GL_CCW                                                      0x0901
#define GL_COEFF                                                    0x0A00
#define GL_ORDER                                                    0x0A01
#define GL_DOMAIN                                                   0x0A02
#define GL_CURRENT_COLOR                                            0x0B00
#define GL_CURRENT_INDEX                                            0x0B01
#define GL_CURRENT_NORMAL                                           0x0B02
#define GL_CURRENT_TEXTURE_COORDS                                   0x0B03
#define GL_CURRENT_RASTER_COLOR                                     0x0B04
#define GL_CURRENT_RASTER_INDEX                                     0x0B05
#define GL_CURRENT_RASTER_TEXTURE_COORDS                            0x0B06
#define GL_CURRENT_RASTER_POSITION                                  0x0B07
#define GL_CURRENT_RASTER_POSITION_VALID                            0x0B08
#define GL_CURRENT_RASTER_DISTANCE                                  0x0B09
#define GL_POINT_SMOOTH                                             0x0B10
#define GL_POINT_SIZE                                               0x0B11
#define GL_POINT_SIZE_RANGE                                         0x0B12
#define GL_POINT_SIZE_GRANULARITY                                   0x0B13
#define GL_LINE_SMOOTH                                              0x0B20
#define GL_LINE_WIDTH                                               0x0B21
#define GL_LINE_WIDTH_RANGE                                         0x0B22
#define GL_LINE_WIDTH_GRANULARITY                                   0x0B23
#define GL_LINE_STIPPLE                                             0x0B24
#define GL_LINE_STIPPLE_PATTERN                                     0x0B25
#define GL_LINE_STIPPLE_REPEAT                                      0x0B26
#define GL_LIST_MODE                                                0x0B30
#define GL_MAX_LIST_NESTING                                         0x0B31
#define GL_LIST_BASE                                                0x0B32
#define GL_LIST_INDEX                                               0x0B33
#define GL_POLYGON_MODE                                             0x0B40
#define GL_POLYGON_SMOOTH                                           0x0B41
#define GL_POLYGON_STIPPLE                                          0x0B42
#define GL_EDGE_FLAG                                                0x0B43
#define GL_CULL_FACE                                                0x0B44
#define GL_CULL_FACE_MODE                                           0x0B45
#define GL_FRONT_FACE                                               0x0B46
#define GL_LIGHTING                                                 0x0B50
#define GL_LIGHT_MODEL_LOCAL_VIEWER                                 0x0B51
#define GL_LIGHT_MODEL_TWO_SIDE                                     0x0B52
#define GL_LIGHT_MODEL_AMBIENT                                      0x0B53
#define GL_SHADE_MODEL                                              0x0B54
#define GL_COLOR_MATERIAL_FACE                                      0x0B55
#define GL_COLOR_MATERIAL_PARAMETER                                 0x0B56
#define GL_COLOR_MATERIAL                                           0x0B57
#define GL_FOG                                                      0x0B60
#define GL_FOG_INDEX                                                0x0B61
#define GL_FOG_DENSITY                                              0x0B62
#define GL_FOG_START                                                0x0B63
#define GL_FOG_END                                                  0x0B64
#define GL_FOG_MODE                                                 0x0B65
#define GL_FOG_COLOR                                                0x0B66
#define GL_DEPTH_RANGE                                              0x0B70
#define GL_DEPTH_TEST                                               0x0B71
#define GL_DEPTH_WRITEMASK                                          0x0B72
#define GL_DEPTH_CLEAR_VALUE                                        0x0B73
#define GL_DEPTH_FUNC                                               0x0B74
#define GL_ACCUM_CLEAR_VALUE                                        0x0B80
#define GL_STENCIL_TEST                                             0x0B90
#define GL_STENCIL_CLEAR_VALUE                                      0x0B91
#define GL_STENCIL_FUNC                                             0x0B92
#define GL_STENCIL_VALUE_MASK                                       0x0B93
#define GL_STENCIL_FAIL                                             0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL                                  0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS                                  0x0B96
#define GL_STENCIL_REF                                              0x0B97
#define GL_STENCIL_WRITEMASK                                        0x0B98
#define GL_MATRIX_MODE                                              0x0BA0
#define GL_NORMALIZE                                                0x0BA1
#define GL_VIEWPORT                                                 0x0BA2
#define GL_MODELVIEW_STACK_DEPTH                                    0x0BA3
#define GL_PROJECTION_STACK_DEPTH                                   0x0BA4
#define GL_TEXTURE_STACK_DEPTH                                      0x0BA5
#define GL_MODELVIEW_MATRIX                                         0x0BA6
#define GL_PROJECTION_MATRIX                                        0x0BA7
#define GL_TEXTURE_MATRIX                                           0x0BA8
#define GL_ATTRIB_STACK_DEPTH                                       0x0BB0
#define GL_CLIENT_ATTRIB_STACK_DEPTH                                0x0BB1
#define GL_ALPHA_TEST                                               0x0BC0
#define GL_ALPHA_TEST_FUNC                                          0x0BC1
#define GL_ALPHA_TEST_REF                                           0x0BC2
#define GL_DITHER                                                   0x0BD0
#define GL_BLEND_DST                                                0x0BE0
#define GL_BLEND_SRC                                                0x0BE1
#define GL_BLEND                                                    0x0BE2
#define GL_LOGIC_OP_MODE                                            0x0BF0
#define GL_INDEX_LOGIC_OP                                           0x0BF1
#define GL_COLOR_LOGIC_OP                                           0x0BF2
#define GL_AUX_BUFFERS                                              0x0C00
#define GL_DRAW_BUFFER                                              0x0C01
#define GL_READ_BUFFER                                              0x0C02
#define GL_SCISSOR_BOX                                              0x0C10
#define GL_SCISSOR_TEST                                             0x0C11
#define GL_INDEX_CLEAR_VALUE                                        0x0C20
#define GL_INDEX_WRITEMASK                                          0x0C21
#define GL_COLOR_CLEAR_VALUE                                        0x0C22
#define GL_COLOR_WRITEMASK                                          0x0C23
#define GL_INDEX_MODE                                               0x0C30
#define GL_RGBA_MODE                                                0x0C31
#define GL_DOUBLEBUFFER                                             0x0C32
#define GL_STEREO                                                   0x0C33
#define GL_RENDER_MODE                                              0x0C40
#define GL_PERSPECTIVE_CORRECTION_HINT                              0x0C50
#define GL_POINT_SMOOTH_HINT                                        0x0C51
#define GL_LINE_SMOOTH_HINT                                         0x0C52
#define GL_POLYGON_SMOOTH_HINT                                      0x0C53
#define GL_FOG_HINT                                                 0x0C54
#define GL_TEXTURE_GEN_S                                            0x0C60
#define GL_TEXTURE_GEN_T                                            0x0C61
#define GL_TEXTURE_GEN_R                                            0x0C62
#define GL_TEXTURE_GEN_Q                                            0x0C63
#define GL_PIXEL_MAP_I_TO_I                                         0x0C70
#define GL_PIXEL_MAP_S_TO_S                                         0x0C71
#define GL_PIXEL_MAP_I_TO_R                                         0x0C72
#define GL_PIXEL_MAP_I_TO_G                                         0x0C73
#define GL_PIXEL_MAP_I_TO_B                                         0x0C74
#define GL_PIXEL_MAP_I_TO_A                                         0x0C75
#define GL_PIXEL_MAP_R_TO_R                                         0x0C76
#define GL_PIXEL_MAP_G_TO_G                                         0x0C77
#define GL_PIXEL_MAP_B_TO_B                                         0x0C78
#define GL_PIXEL_MAP_A_TO_A                                         0x0C79
#define GL_PIXEL_MAP_I_TO_I_SIZE                                    0x0CB0
#define GL_PIXEL_MAP_S_TO_S_SIZE                                    0x0CB1
#define GL_PIXEL_MAP_I_TO_R_SIZE                                    0x0CB2
#define GL_PIXEL_MAP_I_TO_G_SIZE                                    0x0CB3
#define GL_PIXEL_MAP_I_TO_B_SIZE                                    0x0CB4
#define GL_PIXEL_MAP_I_TO_A_SIZE                                    0x0CB5
#define GL_PIXEL_MAP_R_TO_R_SIZE                                    0x0CB6
#define GL_PIXEL_MAP_G_TO_G_SIZE                                    0x0CB7
#define GL_PIXEL_MAP_B_TO_B_SIZE                                    0x0CB8
#define GL_PIXEL_MAP_A_TO_A_SIZE                                    0x0CB9
#define GL_UNPACK_SWAP_BYTES                                        0x0CF0
#define GL_UNPACK_LSB_FIRST                                         0x0CF1
#define GL_UNPACK_ROW_LENGTH                                        0x0CF2
#define GL_UNPACK_SKIP_ROWS                                         0x0CF3
#define GL_UNPACK_SKIP_PIXELS                                       0x0CF4
#define GL_UNPACK_ALIGNMENT                                         0x0CF5
#define GL_PACK_SWAP_BYTES                                          0x0D00
#define GL_PACK_LSB_FIRST                                           0x0D01
#define GL_PACK_ROW_LENGTH                                          0x0D02
#define GL_PACK_SKIP_ROWS                                           0x0D03
#define GL_PACK_SKIP_PIXELS                                         0x0D04
#define GL_PACK_ALIGNMENT                                           0x0D05
#define GL_MAP_COLOR                                                0x0D10
#define GL_MAP_STENCIL                                              0x0D11
#define GL_INDEX_SHIFT                                              0x0D12
#define GL_INDEX_OFFSET                                             0x0D13
#define GL_RED_SCALE                                                0x0D14
#define GL_RED_BIAS                                                 0x0D15
#define GL_ZOOM_X                                                   0x0D16
#define GL_ZOOM_Y                                                   0x0D17
#define GL_GREEN_SCALE                                              0x0D18
#define GL_GREEN_BIAS                                               0x0D19
#define GL_BLUE_SCALE                                               0x0D1A
#define GL_BLUE_BIAS                                                0x0D1B
#define GL_ALPHA_SCALE                                              0x0D1C
#define GL_ALPHA_BIAS                                               0x0D1D
#define GL_DEPTH_SCALE                                              0x0D1E
#define GL_DEPTH_BIAS                                               0x0D1F
#define GL_MAX_EVAL_ORDER                                           0x0D30
#define GL_MAX_LIGHTS                                               0x0D31
#define GL_MAX_CLIP_PLANES                                          0x0D32
#define GL_MAX_TEXTURE_SIZE                                         0x0D33
#define GL_MAX_PIXEL_MAP_TABLE                                      0x0D34
#define GL_MAX_ATTRIB_STACK_DEPTH                                   0x0D35
#define GL_MAX_MODELVIEW_STACK_DEPTH                                0x0D36
#define GL_MAX_NAME_STACK_DEPTH                                     0x0D37
#define GL_MAX_PROJECTION_STACK_DEPTH                               0x0D38
#define GL_MAX_TEXTURE_STACK_DEPTH                                  0x0D39
#define GL_MAX_VIEWPORT_DIMS                                        0x0D3A
#define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH                            0x0D3B
#define GL_SUBPIXEL_BITS                                            0x0D50
#define GL_INDEX_BITS                                               0x0D51
#define GL_RED_BITS                                                 0x0D52
#define GL_GREEN_BITS                                               0x0D53
#define GL_BLUE_BITS                                                0x0D54
#define GL_ALPHA_BITS                                               0x0D55
#define GL_DEPTH_BITS                                               0x0D56
#define GL_STENCIL_BITS                                             0x0D57
#define GL_ACCUM_RED_BITS                                           0x0D58
#define GL_ACCUM_GREEN_BITS                                         0x0D59
#define GL_ACCUM_BLUE_BITS                                          0x0D5A
#define GL_ACCUM_ALPHA_BITS                                         0x0D5B
#define GL_NAME_STACK_DEPTH                                         0x0D70
#define GL_AUTO_NORMAL                                              0x0D80
#define GL_MAP1_COLOR_4                                             0x0D90
#define GL_MAP1_INDEX                                               0x0D91
#define GL_MAP1_NORMAL                                              0x0D92
#define GL_MAP1_TEXTURE_COORD_1                                     0x0D93
#define GL_MAP1_TEXTURE_COORD_2                                     0x0D94
#define GL_MAP1_TEXTURE_COORD_3                                     0x0D95
#define GL_MAP1_TEXTURE_COORD_4                                     0x0D96
#define GL_MAP1_VERTEX_3                                            0x0D97
#define GL_MAP1_VERTEX_4                                            0x0D98
#define GL_MAP2_COLOR_4                                             0x0DB0
#define GL_MAP2_INDEX                                               0x0DB1
#define GL_MAP2_NORMAL                                              0x0DB2
#define GL_MAP2_TEXTURE_COORD_1                                     0x0DB3
#define GL_MAP2_TEXTURE_COORD_2                                     0x0DB4
#define GL_MAP2_TEXTURE_COORD_3                                     0x0DB5
#define GL_MAP2_TEXTURE_COORD_4                                     0x0DB6
#define GL_MAP2_VERTEX_3                                            0x0DB7
#define GL_MAP2_VERTEX_4                                            0x0DB8
#define GL_MAP1_GRID_DOMAIN                                         0x0DD0
#define GL_MAP1_GRID_SEGMENTS                                       0x0DD1
#define GL_MAP2_GRID_DOMAIN                                         0x0DD2
#define GL_MAP2_GRID_SEGMENTS                                       0x0DD3
#define GL_TEXTURE_1D                                               0x0DE0
#define GL_TEXTURE_2D                                               0x0DE1
#define GL_FEEDBACK_BUFFER_POINTER                                  0x0DF0
#define GL_FEEDBACK_BUFFER_SIZE                                     0x0DF1
#define GL_FEEDBACK_BUFFER_TYPE                                     0x0DF2
#define GL_SELECTION_BUFFER_POINTER                                 0x0DF3
#define GL_SELECTION_BUFFER_SIZE                                    0x0DF4
#define GL_TEXTURE_WIDTH                                            0x1000
#define GL_TEXTURE_HEIGHT                                           0x1001
#define GL_TEXTURE_INTERNAL_FORMAT                                  0x1003
#define GL_TEXTURE_BORDER_COLOR                                     0x1004
#define GL_TEXTURE_BORDER                                           0x1005
#define GL_DONT_CARE                                                0x1100
#define GL_FASTEST                                                  0x1101
#define GL_NICEST                                                   0x1102
#define GL_LIGHT0                                                   0x4000
#define GL_LIGHT1                                                   0x4001
#define GL_LIGHT2                                                   0x4002
#define GL_LIGHT3                                                   0x4003
#define GL_LIGHT4                                                   0x4004
#define GL_LIGHT5                                                   0x4005
#define GL_LIGHT6                                                   0x4006
#define GL_LIGHT7                                                   0x4007
#define GL_AMBIENT                                                  0x1200
#define GL_DIFFUSE                                                  0x1201
#define GL_SPECULAR                                                 0x1202
#define GL_POSITION                                                 0x1203
#define GL_SPOT_DIRECTION                                           0x1204
#define GL_SPOT_EXPONENT                                            0x1205
#define GL_SPOT_CUTOFF                                              0x1206
#define GL_CONSTANT_ATTENUATION                                     0x1207
#define GL_LINEAR_ATTENUATION                                       0x1208
#define GL_QUADRATIC_ATTENUATION                                    0x1209
#define GL_COMPILE                                                  0x1300
#define GL_COMPILE_AND_EXECUTE                                      0x1301
#define GL_CLEAR                                                    0x1500
#define GL_AND                                                      0x1501
#define GL_AND_REVERSE                                              0x1502
#define GL_COPY                                                     0x1503
#define GL_AND_INVERTED                                             0x1504
#define GL_NOOP                                                     0x1505
#define GL_XOR                                                      0x1506
#define GL_OR                                                       0x1507
#define GL_NOR                                                      0x1508
#define GL_EQUIV                                                    0x1509
#define GL_INVERT                                                   0x150A
#define GL_OR_REVERSE                                               0x150B
#define GL_COPY_INVERTED                                            0x150C
#define GL_OR_INVERTED                                              0x150D
#define GL_NAND                                                     0x150E
#define GL_SET                                                      0x150F
#define GL_EMISSION                                                 0x1600
#define GL_SHININESS                                                0x1601
#define GL_AMBIENT_AND_DIFFUSE                                      0x1602
#define GL_COLOR_INDEXES                                            0x1603
#define GL_MODELVIEW                                                0x1700
#define GL_PROJECTION                                               0x1701
#define GL_TEXTURE                                                  0x1702
#define GL_COLOR                                                    0x1800
#define GL_DEPTH                                                    0x1801
#define GL_STENCIL                                                  0x1802
#define GL_COLOR_INDEX                                              0x1900
#define GL_STENCIL_INDEX                                            0x1901
#define GL_DEPTH_COMPONENT                                          0x1902
#define GL_RED                                                      0x1903
#define GL_GREEN                                                    0x1904
#define GL_BLUE                                                     0x1905
#define GL_ALPHA                                                    0x1906
#define GL_RGB                                                      0x1907
#define GL_RGBA                                                     0x1908
#define GL_LUMINANCE                                                0x1909
#define GL_LUMINANCE_ALPHA                                          0x190A
#define GL_BITMAP                                                   0x1A00
#define GL_POINT                                                    0x1B00
#define GL_LINE                                                     0x1B01
#define GL_FILL                                                     0x1B02
#define GL_RENDER                                                   0x1C00
#define GL_FEEDBACK                                                 0x1C01
#define GL_SELECT                                                   0x1C02
#define GL_FLAT                                                     0x1D00
#define GL_SMOOTH                                                   0x1D01
#define GL_KEEP                                                     0x1E00
#define GL_REPLACE                                                  0x1E01
#define GL_INCR                                                     0x1E02
#define GL_DECR                                                     0x1E03
#define GL_VENDOR                                                   0x1F00
#define GL_RENDERER                                                 0x1F01
#define GL_VERSION                                                  0x1F02
#define GL_EXTENSIONS                                               0x1F03
#define GL_S                                                        0x2000
#define GL_T                                                        0x2001
#define GL_R                                                        0x2002
#define GL_Q                                                        0x2003
#define GL_MODULATE                                                 0x2100
#define GL_DECAL                                                    0x2101
#define GL_TEXTURE_ENV_MODE                                         0x2200
#define GL_TEXTURE_ENV_COLOR                                        0x2201
#define GL_TEXTURE_ENV                                              0x2300
#define GL_EYE_LINEAR                                               0x2400
#define GL_OBJECT_LINEAR                                            0x2401
#define GL_SPHERE_MAP                                               0x2402
#define GL_TEXTURE_GEN_MODE                                         0x2500
#define GL_OBJECT_PLANE                                             0x2501
#define GL_EYE_PLANE                                                0x2502
#define GL_NEAREST                                                  0x2600
#define GL_LINEAR                                                   0x2601
#define GL_NEAREST_MIPMAP_NEAREST                                   0x2700
#define GL_LINEAR_MIPMAP_NEAREST                                    0x2701
#define GL_NEAREST_MIPMAP_LINEAR                                    0x2702
#define GL_LINEAR_MIPMAP_LINEAR                                     0x2703
#define GL_TEXTURE_MAG_FILTER                                       0x2800
#define GL_TEXTURE_MIN_FILTER                                       0x2801
#define GL_TEXTURE_WRAP_S                                           0x2802
#define GL_TEXTURE_WRAP_T                                           0x2803
#define GL_CLAMP                                                    0x2900
#define GL_REPEAT                                                   0x2901
#define GL_CLIENT_PIXEL_STORE_BIT                                   0x00000001
#define GL_CLIENT_VERTEX_ARRAY_BIT                                  0x00000002
#define GL_CLIENT_ALL_ATTRIB_BITS                                   0xffffffff
#define GL_POLYGON_OFFSET_FACTOR                                    0x8038
#define GL_POLYGON_OFFSET_UNITS                                     0x2A00
#define GL_POLYGON_OFFSET_POINT                                     0x2A01
#define GL_POLYGON_OFFSET_LINE                                      0x2A02
#define GL_POLYGON_OFFSET_FILL                                      0x8037
#define GL_ALPHA4                                                   0x803B
#define GL_ALPHA8                                                   0x803C
#define GL_ALPHA12                                                  0x803D
#define GL_ALPHA16                                                  0x803E
#define GL_LUMINANCE4                                               0x803F
#define GL_LUMINANCE8                                               0x8040
#define GL_LUMINANCE12                                              0x8041
#define GL_LUMINANCE16                                              0x8042
#define GL_LUMINANCE4_ALPHA4                                        0x8043
#define GL_LUMINANCE6_ALPHA2                                        0x8044
#define GL_LUMINANCE8_ALPHA8                                        0x8045
#define GL_LUMINANCE12_ALPHA4                                       0x8046
#define GL_LUMINANCE12_ALPHA12                                      0x8047
#define GL_LUMINANCE16_ALPHA16                                      0x8048
#define GL_INTENSITY                                                0x8049
#define GL_INTENSITY4                                               0x804A
#define GL_INTENSITY8                                               0x804B
#define GL_INTENSITY12                                              0x804C
#define GL_INTENSITY16                                              0x804D
#define GL_R3_G3_B2                                                 0x2A10
#define GL_RGB4                                                     0x804F
#define GL_RGB5                                                     0x8050
#define GL_RGB8                                                     0x8051
#define GL_RGB10                                                    0x8052
#define GL_RGB12                                                    0x8053
#define GL_RGB16                                                    0x8054
#define GL_RGBA2                                                    0x8055
#define GL_RGBA4                                                    0x8056
#define GL_RGB5_A1                                                  0x8057
#define GL_RGBA8                                                    0x8058
#define GL_RGB10_A2                                                 0x8059
#define GL_RGBA12                                                   0x805A
#define GL_RGBA16                                                   0x805B
#define GL_TEXTURE_RED_SIZE                                         0x805C
#define GL_TEXTURE_GREEN_SIZE                                       0x805D
#define GL_TEXTURE_BLUE_SIZE                                        0x805E
#define GL_TEXTURE_ALPHA_SIZE                                       0x805F
#define GL_TEXTURE_LUMINANCE_SIZE                                   0x8060
#define GL_TEXTURE_INTENSITY_SIZE                                   0x8061
#define GL_PROXY_TEXTURE_1D                                         0x8063
#define GL_PROXY_TEXTURE_2D                                         0x8064
#define GL_TEXTURE_PRIORITY                                         0x8066
#define GL_TEXTURE_RESIDENT                                         0x8067
#define GL_TEXTURE_BINDING_1D                                       0x8068
#define GL_TEXTURE_BINDING_2D                                       0x8069
#define GL_VERTEX_ARRAY                                             0x8074
#define GL_NORMAL_ARRAY                                             0x8075
#define GL_COLOR_ARRAY                                              0x8076
#define GL_INDEX_ARRAY                                              0x8077
#define GL_TEXTURE_COORD_ARRAY                                      0x8078
#define GL_EDGE_FLAG_ARRAY                                          0x8079
#define GL_VERTEX_ARRAY_SIZE                                        0x807A
#define GL_VERTEX_ARRAY_TYPE                                        0x807B
#define GL_VERTEX_ARRAY_STRIDE                                      0x807C
#define GL_NORMAL_ARRAY_TYPE                                        0x807E
#define GL_NORMAL_ARRAY_STRIDE                                      0x807F
#define GL_COLOR_ARRAY_SIZE                                         0x8081
#define GL_COLOR_ARRAY_TYPE                                         0x8082
#define GL_COLOR_ARRAY_STRIDE                                       0x8083
#define GL_INDEX_ARRAY_TYPE                                         0x8085
#define GL_INDEX_ARRAY_STRIDE                                       0x8086
#define GL_TEXTURE_COORD_ARRAY_SIZE                                 0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE                                 0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE                               0x808A
#define GL_EDGE_FLAG_ARRAY_STRIDE                                   0x808C
#define GL_VERTEX_ARRAY_POINTER                                     0x808E
#define GL_NORMAL_ARRAY_POINTER                                     0x808F
#define GL_COLOR_ARRAY_POINTER                                      0x8090
#define GL_INDEX_ARRAY_POINTER                                      0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER                              0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER                                  0x8093
#define GL_V2F                                                      0x2A20
#define GL_V3F                                                      0x2A21
#define GL_C4UB_V2F                                                 0x2A22
#define GL_C4UB_V3F                                                 0x2A23
#define GL_C3F_V3F                                                  0x2A24
#define GL_N3F_V3F                                                  0x2A25
#define GL_C4F_N3F_V3F                                              0x2A26
#define GL_T2F_V3F                                                  0x2A27
#define GL_T4F_V4F                                                  0x2A28
#define GL_T2F_C4UB_V3F                                             0x2A29
#define GL_T2F_C3F_V3F                                              0x2A2A
#define GL_T2F_N3F_V3F                                              0x2A2B
#define GL_T2F_C4F_N3F_V3F                                          0x2A2C
#define GL_T4F_C4F_N3F_V4F                                          0x2A2D
#define GL_LOGIC_OP                                                 0x0BF1
#define GL_TEXTURE_COMPONENTS                                       0x1003
#define GL_COLOR_INDEX1_EXT                                         0x80E2
#define GL_COLOR_INDEX2_EXT                                         0x80E3
#define GL_COLOR_INDEX4_EXT                                         0x80E4
#define GL_COLOR_INDEX8_EXT                                         0x80E5
#define GL_COLOR_INDEX12_EXT                                        0x80E6
#define GL_COLOR_INDEX16_EXT                                        0x80E7

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;

#define glAccum SE_glAccum
#define glAlphaFunc SE_glAlphaFunc
#define glAreTexturesResident SE_glAreTexturesResident
#define glArrayElement SE_glArrayElement
#define glBegin SE_glBegin
#define glBindTexture SE_glBindTexture
#define glBitmap SE_glBitmap
#define glBlendFunc SE_glBlendFunc
#define glCallList SE_glCallList
#define glCallLists SE_glCallLists
#define glClear SE_glClear
#define glClearAccum SE_glClearAccum
#define glClearColor SE_glClearColor
#define glClearDepth SE_glClearDepth
#define glClearIndex SE_glClearIndex
#define glClearStencil SE_glClearStencil
#define glClipPlane SE_glClipPlane
#define glColor3b SE_glColor3b
#define glColor3bv SE_glColor3bv
#define glColor3d SE_glColor3d
#define glColor3dv SE_glColor3dv
#define glColor3f SE_glColor3f
#define glColor3fv SE_glColor3fv
#define glColor3i SE_glColor3i
#define glColor3iv SE_glColor3iv
#define glColor3s SE_glColor3s
#define glColor3sv SE_glColor3sv
#define glColor3ub SE_glColor3ub
#define glColor3ubv SE_glColor3ubv
#define glColor3ui SE_glColor3ui
#define glColor3uiv SE_glColor3uiv
#define glColor3us SE_glColor3us
#define glColor3usv SE_glColor3usv
#define glColor4b SE_glColor4b
#define glColor4bv SE_glColor4bv
#define glColor4d SE_glColor4d
#define glColor4dv SE_glColor4dv
#define glColor4f SE_glColor4f
#define glColor4fv SE_glColor4fv
#define glColor4i SE_glColor4i
#define glColor4iv SE_glColor4iv
#define glColor4s SE_glColor4s
#define glColor4sv SE_glColor4sv
#define glColor4ub SE_glColor4ub
#define glColor4ubv SE_glColor4ubv
#define glColor4ui SE_glColor4ui
#define glColor4uiv SE_glColor4uiv
#define glColor4us SE_glColor4us
#define glColor4usv SE_glColor4usv
#define glColorMask SE_glColorMask
#define glColorMaterial SE_glColorMaterial
#define glColorPointer SE_glColorPointer
#define glCopyPixels SE_glCopyPixels
#define glCopyTexImage1D SE_glCopyTexImage1D
#define glCopyTexImage2D SE_glCopyTexImage2D
#define glCopyTexSubImage1D SE_glCopyTexSubImage1D
#define glCopyTexSubImage2D SE_glCopyTexSubImage2D
#define glCullFace SE_glCullFace
#define glDeleteLists SE_glDeleteLists
#define glDeleteTextures SE_glDeleteTextures
#define glDepthFunc SE_glDepthFunc
#define glDepthMask SE_glDepthMask
#define glDepthRange SE_glDepthRange
#define glDisable SE_glDisable
#define glDisableClientState SE_glDisableClientState
#define glDrawArrays SE_glDrawArrays
#define glDrawBuffer SE_glDrawBuffer
#define glDrawElements SE_glDrawElements
#define glDrawPixels SE_glDrawPixels
#define glEdgeFlag SE_glEdgeFlag
#define glEdgeFlagPointer SE_glEdgeFlagPointer
#define glEdgeFlagv SE_glEdgeFlagv
#define glEnable SE_glEnable
#define glEnableClientState SE_glEnableClientState
#define glEnd SE_glEnd
#define glEndList SE_glEndList
#define glEvalCoord1d SE_glEvalCoord1d
#define glEvalCoord1dv SE_glEvalCoord1dv
#define glEvalCoord1f SE_glEvalCoord1f
#define glEvalCoord1fv SE_glEvalCoord1fv
#define glEvalCoord2d SE_glEvalCoord2d
#define glEvalCoord2dv SE_glEvalCoord2dv
#define glEvalCoord2f SE_glEvalCoord2f
#define glEvalCoord2fv SE_glEvalCoord2fv
#define glEvalMesh1 SE_glEvalMesh1
#define glEvalMesh2 SE_glEvalMesh2
#define glEvalPoint1 SE_glEvalPoint1
#define glEvalPoint2 SE_glEvalPoint2
#define glFeedbackBuffer SE_glFeedbackBuffer
#define glFinish SE_glFinish
#define glFlush SE_glFlush
#define glFogf SE_glFogf
#define glFogfv SE_glFogfv
#define glFogi SE_glFogi
#define glFogiv SE_glFogiv
#define glFrontFace SE_glFrontFace
#define glFrustum SE_glFrustum
#define glGenLists SE_glGenLists
#define glGenTextures SE_glGenTextures
#define glGetBooleanv SE_glGetBooleanv
#define glGetClipPlane SE_glGetClipPlane
#define glGetDoublev SE_glGetDoublev
#define glGetError SE_glGetError
#define glGetFloatv SE_glGetFloatv
#define glGetIntegerv SE_glGetIntegerv
#define glGetLightfv SE_glGetLightfv
#define glGetLightiv SE_glGetLightiv
#define glGetMapdv SE_glGetMapdv
#define glGetMapfv SE_glGetMapfv
#define glGetMapiv SE_glGetMapiv
#define glGetMaterialfv SE_glGetMaterialfv
#define glGetMaterialiv SE_glGetMaterialiv
#define glGetPixelMapfv SE_glGetPixelMapfv
#define glGetPixelMapuiv SE_glGetPixelMapuiv
#define glGetPixelMapusv SE_glGetPixelMapusv
#define glGetPointerv SE_glGetPointerv
#define glGetPolygonStipple SE_glGetPolygonStipple
#define glGetString SE_glGetString
#define glGetTexEnvfv SE_glGetTexEnvfv
#define glGetTexEnviv SE_glGetTexEnviv
#define glGetTexGendv SE_glGetTexGendv
#define glGetTexGenfv SE_glGetTexGenfv
#define glGetTexGeniv SE_glGetTexGeniv
#define glGetTexImage SE_glGetTexImage
#define glGetTexLevelParameterfv SE_glGetTexLevelParameterfv
#define glGetTexLevelParameteriv SE_glGetTexLevelParameteriv
#define glGetTexParameterfv SE_glGetTexParameterfv
#define glGetTexParameteriv SE_glGetTexParameteriv
#define glHint SE_glHint
#define glIndexMask SE_glIndexMask
#define glIndexPointer SE_glIndexPointer
#define glIndexd SE_glIndexd
#define glIndexdv SE_glIndexdv
#define glIndexf SE_glIndexf
#define glIndexfv SE_glIndexfv
#define glIndexi SE_glIndexi
#define glIndexiv SE_glIndexiv
#define glIndexs SE_glIndexs
#define glIndexsv SE_glIndexsv
#define glIndexub SE_glIndexub
#define glIndexubv SE_glIndexubv
#define glInitNames SE_glInitNames
#define glInterleavedArrays SE_glInterleavedArrays
#define glIsEnabled SE_glIsEnabled
#define glIsList SE_glIsList
#define glIsTexture SE_glIsTexture
#define glLightModelf SE_glLightModelf
#define glLightModelfv SE_glLightModelfv
#define glLightModeli SE_glLightModeli
#define glLightModeliv SE_glLightModeliv
#define glLightf SE_glLightf
#define glLightfv SE_glLightfv
#define glLighti SE_glLighti
#define glLightiv SE_glLightiv
#define glLineStipple SE_glLineStipple
#define glLineWidth SE_glLineWidth
#define glListBase SE_glListBase
#define glLoadIdentity SE_glLoadIdentity
#define glLoadMatrixd SE_glLoadMatrixd
#define glLoadMatrixf SE_glLoadMatrixf
#define glLoadName SE_glLoadName
#define glLogicOp SE_glLogicOp
#define glMap1d SE_glMap1d
#define glMap1f SE_glMap1f
#define glMap2d SE_glMap2d
#define glMap2f SE_glMap2f
#define glMapGrid1d SE_glMapGrid1d
#define glMapGrid1f SE_glMapGrid1f
#define glMapGrid2d SE_glMapGrid2d
#define glMapGrid2f SE_glMapGrid2f
#define glMaterialf SE_glMaterialf
#define glMaterialfv SE_glMaterialfv
#define glMateriali SE_glMateriali
#define glMaterialiv SE_glMaterialiv
#define glMatrixMode SE_glMatrixMode
#define glMultMatrixd SE_glMultMatrixd
#define glMultMatrixf SE_glMultMatrixf
#define glNewList SE_glNewList
#define glNormal3b SE_glNormal3b
#define glNormal3bv SE_glNormal3bv
#define glNormal3d SE_glNormal3d
#define glNormal3dv SE_glNormal3dv
#define glNormal3f SE_glNormal3f
#define glNormal3fv SE_glNormal3fv
#define glNormal3i SE_glNormal3i
#define glNormal3iv SE_glNormal3iv
#define glNormal3s SE_glNormal3s
#define glNormal3sv SE_glNormal3sv
#define glNormalPointer SE_glNormalPointer
#define glOrtho SE_glOrtho
#define glPassThrough SE_glPassThrough
#define glPixelMapfv SE_glPixelMapfv
#define glPixelMapuiv SE_glPixelMapuiv
#define glPixelMapusv SE_glPixelMapusv
#define glPixelStoref SE_glPixelStoref
#define glPixelStorei SE_glPixelStorei
#define glPixelTransferf SE_glPixelTransferf
#define glPixelTransferi SE_glPixelTransferi
#define glPixelZoom SE_glPixelZoom
#define glPointSize SE_glPointSize
#define glPolygonMode SE_glPolygonMode
#define glPolygonOffset SE_glPolygonOffset
#define glPolygonStipple SE_glPolygonStipple
#define glPopAttrib SE_glPopAttrib
#define glPopClientAttrib SE_glPopClientAttrib
#define glPopMatrix SE_glPopMatrix
#define glPopName SE_glPopName
#define glPrioritizeTextures SE_glPrioritizeTextures
#define glPushAttrib SE_glPushAttrib
#define glPushClientAttrib SE_glPushClientAttrib
#define glPushMatrix SE_glPushMatrix
#define glPushName SE_glPushName
#define glRasterPos2d SE_glRasterPos2d
#define glRasterPos2dv SE_glRasterPos2dv
#define glRasterPos2f SE_glRasterPos2f
#define glRasterPos2fv SE_glRasterPos2fv
#define glRasterPos2i SE_glRasterPos2i
#define glRasterPos2iv SE_glRasterPos2iv
#define glRasterPos2s SE_glRasterPos2s
#define glRasterPos2sv SE_glRasterPos2sv
#define glRasterPos3d SE_glRasterPos3d
#define glRasterPos3dv SE_glRasterPos3dv
#define glRasterPos3f SE_glRasterPos3f
#define glRasterPos3fv SE_glRasterPos3fv
#define glRasterPos3i SE_glRasterPos3i
#define glRasterPos3iv SE_glRasterPos3iv
#define glRasterPos3s SE_glRasterPos3s
#define glRasterPos3sv SE_glRasterPos3sv
#define glRasterPos4d SE_glRasterPos4d
#define glRasterPos4dv SE_glRasterPos4dv
#define glRasterPos4f SE_glRasterPos4f
#define glRasterPos4fv SE_glRasterPos4fv
#define glRasterPos4i SE_glRasterPos4i
#define glRasterPos4iv SE_glRasterPos4iv
#define glRasterPos4s SE_glRasterPos4s
#define glRasterPos4sv SE_glRasterPos4sv
#define glReadBuffer SE_glReadBuffer
#define glReadPixels SE_glReadPixels
#define glRectd SE_glRectd
#define glRectdv SE_glRectdv
#define glRectf SE_glRectf
#define glRectfv SE_glRectfv
#define glRecti SE_glRecti
#define glRectiv SE_glRectiv
#define glRects SE_glRects
#define glRectsv SE_glRectsv
#define glRenderMode SE_glRenderMode
#define glRotated SE_glRotated
#define glRotatef SE_glRotatef
#define glScaled SE_glScaled
#define glScalef SE_glScalef
#define glScissor SE_glScissor
#define glSelectBuffer SE_glSelectBuffer
#define glShadeModel SE_glShadeModel
#define glStencilFunc SE_glStencilFunc
#define glStencilMask SE_glStencilMask
#define glStencilOp SE_glStencilOp
#define glTexCoord1d SE_glTexCoord1d
#define glTexCoord1dv SE_glTexCoord1dv
#define glTexCoord1f SE_glTexCoord1f
#define glTexCoord1fv SE_glTexCoord1fv
#define glTexCoord1i SE_glTexCoord1i
#define glTexCoord1iv SE_glTexCoord1iv
#define glTexCoord1s SE_glTexCoord1s
#define glTexCoord1sv SE_glTexCoord1sv
#define glTexCoord2d SE_glTexCoord2d
#define glTexCoord2dv SE_glTexCoord2dv
#define glTexCoord2f SE_glTexCoord2f
#define glTexCoord2fv SE_glTexCoord2fv
#define glTexCoord2i SE_glTexCoord2i
#define glTexCoord2iv SE_glTexCoord2iv
#define glTexCoord2s SE_glTexCoord2s
#define glTexCoord2sv SE_glTexCoord2sv
#define glTexCoord3d SE_glTexCoord3d
#define glTexCoord3dv SE_glTexCoord3dv
#define glTexCoord3f SE_glTexCoord3f
#define glTexCoord3fv SE_glTexCoord3fv
#define glTexCoord3i SE_glTexCoord3i
#define glTexCoord3iv SE_glTexCoord3iv
#define glTexCoord3s SE_glTexCoord3s
#define glTexCoord3sv SE_glTexCoord3sv
#define glTexCoord4d SE_glTexCoord4d
#define glTexCoord4dv SE_glTexCoord4dv
#define glTexCoord4f SE_glTexCoord4f
#define glTexCoord4fv SE_glTexCoord4fv
#define glTexCoord4i SE_glTexCoord4i
#define glTexCoord4iv SE_glTexCoord4iv
#define glTexCoord4s SE_glTexCoord4s
#define glTexCoord4sv SE_glTexCoord4sv
#define glTexCoordPointer SE_glTexCoordPointer
#define glTexEnvf SE_glTexEnvf
#define glTexEnvfv SE_glTexEnvfv
#define glTexEnvi SE_glTexEnvi
#define glTexEnviv SE_glTexEnviv
#define glTexGend SE_glTexGend
#define glTexGendv SE_glTexGendv
#define glTexGenf SE_glTexGenf
#define glTexGenfv SE_glTexGenfv
#define glTexGeni SE_glTexGeni
#define glTexGeniv SE_glTexGeniv
#define glTexImage1D SE_glTexImage1D
#define glTexImage2D SE_glTexImage2D
#define glTexParameterf SE_glTexParameterf
#define glTexParameterfv SE_glTexParameterfv
#define glTexParameteri SE_glTexParameteri
#define glTexParameteriv SE_glTexParameteriv
#define glTexSubImage1D SE_glTexSubImage1D
#define glTexSubImage2D SE_glTexSubImage2D
#define glTranslated SE_glTranslated
#define glTranslatef SE_glTranslatef
#define glVertex2d SE_glVertex2d
#define glVertex2dv SE_glVertex2dv
#define glVertex2f SE_glVertex2f
#define glVertex2fv SE_glVertex2fv
#define glVertex2i SE_glVertex2i
#define glVertex2iv SE_glVertex2iv
#define glVertex2s SE_glVertex2s
#define glVertex2sv SE_glVertex2sv
#define glVertex3d SE_glVertex3d
#define glVertex3dv SE_glVertex3dv
#define glVertex3f SE_glVertex3f
#define glVertex3fv SE_glVertex3fv
#define glVertex3i SE_glVertex3i
#define glVertex3iv SE_glVertex3iv
#define glVertex3s SE_glVertex3s
#define glVertex3sv SE_glVertex3sv
#define glVertex4d SE_glVertex4d
#define glVertex4dv SE_glVertex4dv
#define glVertex4f SE_glVertex4f
#define glVertex4fv SE_glVertex4fv
#define glVertex4i SE_glVertex4i
#define glVertex4iv SE_glVertex4iv
#define glVertex4s SE_glVertex4s
#define glVertex4sv SE_glVertex4sv
#define glVertexPointer SE_glVertexPointer
#define glViewport SE_glViewport

SE_EXTERN void SE_glAccum(GLenum eOperation, GLfloat fValue);
SE_EXTERN void SE_glAlphaFunc(GLenum eFunction, GLclampf fReference);
SE_EXTERN GLboolean SE_glAreTexturesResident(GLsizei iNumTextures,
    const GLuint* auiTextures, GLboolean* aucResidences);
SE_EXTERN void SE_glArrayElement(GLint i);
SE_EXTERN void SE_glBegin(GLenum eMode);
SE_EXTERN void SE_glBindTexture(GLenum eTarget, GLuint uiTexture);
SE_EXTERN void SE_glBitmap(GLsizei iWidth, GLsizei iHeight, GLfloat fXOrigin,
    GLfloat fYOrigin, GLfloat fXMove, GLfloat fYMove,
    const GLubyte* aucBitmap);
SE_EXTERN void SE_glBlendFunc(GLenum eSrcFunction, GLenum eDstFunction);
SE_EXTERN void SE_glCallList(GLuint uiList);
SE_EXTERN void SE_glCallLists(GLsizei iNumLists, GLenum eType,
    const GLvoid* pvLists);
SE_EXTERN void SE_glClear(GLbitfield uiMask);
SE_EXTERN void SE_glClearAccum(GLfloat fRed, GLfloat fGreen, GLfloat fBlue,
    GLfloat fAlpha);
SE_EXTERN void SE_glClearColor(GLclampf fRed, GLclampf fGreen, GLclampf fBlue,
    GLclampf fAlpha);
SE_EXTERN void SE_glClearDepth(GLclampd dDepth);
SE_EXTERN void SE_glClearIndex(GLfloat fIndex);
SE_EXTERN void SE_glClearStencil(GLint iStencil);
SE_EXTERN void SE_glClipPlane(GLenum ePlane, const GLdouble* adEquation);
SE_EXTERN void SE_glColor3b(GLbyte cRed, GLbyte cGreen, GLbyte cBlue);
SE_EXTERN void SE_glColor3bv(const GLbyte* acRGB);
SE_EXTERN void SE_glColor3d(GLdouble dRed, GLdouble dGreen, GLdouble dBlue);
SE_EXTERN void SE_glColor3dv(const GLdouble* adRGB);
SE_EXTERN void SE_glColor3f(GLfloat fRed, GLfloat fGreen, GLfloat fBlue);
SE_EXTERN void SE_glColor3fv(const GLfloat* afRGB);
SE_EXTERN void SE_glColor3i(GLint iRed, GLint iGreen, GLint iBlue);
SE_EXTERN void SE_glColor3iv(const GLint* aiRGB);
SE_EXTERN void SE_glColor3s(GLshort sRed, GLshort sGreen, GLshort sBlue);
SE_EXTERN void SE_glColor3sv(const GLshort* asRGB);
SE_EXTERN void SE_glColor3ub(GLubyte ucRed, GLubyte ucGreen, GLubyte ucBlue);
SE_EXTERN void SE_glColor3ubv(const GLubyte* aucRGB);
SE_EXTERN void SE_glColor3ui(GLuint uiRed, GLuint uiGreen, GLuint uiBlue);
SE_EXTERN void SE_glColor3uiv(const GLuint* auiRGB);
SE_EXTERN void SE_glColor3us(GLushort usRed, GLushort usGreen,
    GLushort usBlue);
SE_EXTERN void SE_glColor3usv(const GLushort* ausRGB);
SE_EXTERN void SE_glColor4b(GLbyte cRed, GLbyte cGreen, GLbyte cBlue,
    GLbyte cAlpha);
SE_EXTERN void SE_glColor4bv(const GLbyte* acRGBA);
SE_EXTERN void SE_glColor4d(GLdouble dRed, GLdouble dGreen, GLdouble dBlue,
    GLdouble dAlpha);
SE_EXTERN void SE_glColor4dv(const GLdouble* adRGBA);
SE_EXTERN void SE_glColor4f(GLfloat fRed, GLfloat fGreen, GLfloat fBlue,
    GLfloat fAlpha);
SE_EXTERN void SE_glColor4fv(const GLfloat* afRGBA);
SE_EXTERN void SE_glColor4i(GLint iRed, GLint iGreen, GLint iBlue,
    GLint iAlpha);
SE_EXTERN void SE_glColor4iv(const GLint* aiRGBA);
SE_EXTERN void SE_glColor4s(GLshort sRed, GLshort sGreen, GLshort sBlue,
    GLshort sAlpha);
SE_EXTERN void SE_glColor4sv(const GLshort* asRGBA);
SE_EXTERN void SE_glColor4ub(GLubyte ucRed, GLubyte ucGreen, GLubyte ucBlue,
    GLubyte ucAlpha);
SE_EXTERN void SE_glColor4ubv(const GLubyte* aucRGBA);
SE_EXTERN void SE_glColor4ui(GLuint uiRed, GLuint uiGreen, GLuint uiBlue,
    GLuint uiAlpha);
SE_EXTERN void SE_glColor4uiv(const GLuint* auiRGBA);
SE_EXTERN void SE_glColor4us(GLushort usRed, GLushort usGreen,
    GLushort usBlue, GLushort usAlpha);
SE_EXTERN void SE_glColor4usv(const GLushort* ausRGBA);
SE_EXTERN void SE_glColorMask(GLboolean ucRed, GLboolean ucGreen,
    GLboolean ucBlue, GLboolean ucAlpha);
SE_EXTERN void SE_glColorMaterial(GLenum eFace, GLenum eMode);
SE_EXTERN void SE_glColorPointer(GLint iSize, GLenum eType, GLsizei iStride,
    const GLvoid* pvPointer);
SE_EXTERN void SE_glCopyPixels(GLint iX, GLint iY, GLsizei iWidth,
    GLsizei iHeight, GLenum eType);
SE_EXTERN void SE_glCopyTexImage1D(GLenum eTarget, GLint iLevel,
    GLenum eInternalFormat, GLint iX, GLint iY, GLsizei iWidth,
    GLint iBorder);
SE_EXTERN void SE_glCopyTexImage2D(GLenum eTarget, GLint iLevel,
    GLenum eInternalFormat,  GLint iX, GLint iY, GLsizei iWidth,
    GLsizei iHeight, GLint iBorder);
SE_EXTERN void SE_glCopyTexSubImage1D(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLint iX, GLint iY, GLsizei iWidth);
SE_EXTERN void SE_glCopyTexSubImage2D(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLint iYOffset, GLint iX, GLint iY, GLsizei iWidth,
    GLsizei iHeight);
SE_EXTERN void SE_glCullFace(GLenum eMode);
SE_EXTERN void SE_glDeleteLists(GLuint uiList, GLsizei iRange);
SE_EXTERN void SE_glDeleteTextures(GLsizei iNumTextures,
    const GLuint* auiTextures);
SE_EXTERN void SE_glDepthFunc(GLenum eFunction);
SE_EXTERN void SE_glDepthMask(GLboolean ucMask);
SE_EXTERN void SE_glDepthRange(GLclampd dZNear, GLclampd dZFar);
SE_EXTERN void SE_glDisable(GLenum eCapability);
SE_EXTERN void SE_glDisableClientState(GLenum eArray);
SE_EXTERN void SE_glDrawArrays(GLenum eMode, GLint iFirst, GLsizei iCount);
SE_EXTERN void SE_glDrawBuffer(GLenum eMode);
SE_EXTERN void SE_glDrawElements(GLenum eMode, GLsizei iCount, GLenum eType,
    const GLvoid* pvIndices);
SE_EXTERN void SE_glDrawPixels(GLsizei iWidth, GLsizei iHeight,
    GLenum eFormat, GLenum eType, const GLvoid* pvPixels);
SE_EXTERN void SE_glEdgeFlag(GLboolean ucFlag);
SE_EXTERN void SE_glEdgeFlagPointer(GLsizei iStride, const GLvoid* pvPointer);
SE_EXTERN void SE_glEdgeFlagv(const GLboolean* pucFlag);
SE_EXTERN void SE_glEnable(GLenum eCapability);
SE_EXTERN void SE_glEnableClientState(GLenum eArray);
SE_EXTERN void SE_glEnd(void);
SE_EXTERN void SE_glEndList(void);
SE_EXTERN void SE_glEvalCoord1d(GLdouble dU);
SE_EXTERN void SE_glEvalCoord1dv(const GLdouble* pdU);
SE_EXTERN void SE_glEvalCoord1f(GLfloat fU);
SE_EXTERN void SE_glEvalCoord1fv(const GLfloat* pfU);
SE_EXTERN void SE_glEvalCoord2d(GLdouble dU, GLdouble dV);
SE_EXTERN void SE_glEvalCoord2dv(const GLdouble* adUV);
SE_EXTERN void SE_glEvalCoord2f(GLfloat fU, GLfloat fV);
SE_EXTERN void SE_glEvalCoord2fv(const GLfloat* afUV);
SE_EXTERN void SE_glEvalMesh1(GLenum eMode, GLint i1, GLint i2);
SE_EXTERN void SE_glEvalMesh2(GLenum eMode, GLint i1, GLint i2, GLint j1,
    GLint j2);
SE_EXTERN void SE_glEvalPoint1(GLint i);
SE_EXTERN void SE_glEvalPoint2(GLint i, GLint j);
SE_EXTERN void SE_glFeedbackBuffer(GLsizei iSize, GLenum eType,
    GLfloat* afBuffer);
SE_EXTERN void SE_glFinish(void);
SE_EXTERN void SE_glFlush(void);
SE_EXTERN void SE_glFogf(GLenum ePName, GLfloat fParam);
SE_EXTERN void SE_glFogfv(GLenum ePName, const GLfloat* afParam);
SE_EXTERN void SE_glFogi(GLenum ePName, GLint iParam);
SE_EXTERN void SE_glFogiv(GLenum ePName, const GLint* aiParam);
SE_EXTERN void SE_glFrontFace(GLenum eMode);
SE_EXTERN void SE_glFrustum(GLdouble dLeft, GLdouble dRight, GLdouble dBottom,
    GLdouble dTop, GLdouble dZNear, GLdouble dZFar);
SE_EXTERN GLuint SE_glGenLists(GLsizei iRange);
SE_EXTERN void SE_glGenTextures(GLsizei iNumTextures, GLuint* auiTexture);
SE_EXTERN void SE_glGetBooleanv(GLenum ePName, GLboolean* aucParam);
SE_EXTERN void SE_glGetClipPlane(GLenum ePlane, GLdouble* adEquation);
SE_EXTERN void SE_glGetDoublev(GLenum ePName, GLdouble* adParam);
SE_EXTERN GLenum SE_glGetError(void);
SE_EXTERN void SE_glGetFloatv(GLenum ePName, GLfloat* afParam);
SE_EXTERN void SE_glGetIntegerv(GLenum ePName, GLint* aiParam);
SE_EXTERN void SE_glGetLightfv(GLenum eLight, GLenum ePName,
    GLfloat* afParam);
SE_EXTERN void SE_glGetLightiv(GLenum eLight, GLenum ePName, GLint* aiParam);
SE_EXTERN void SE_glGetMapdv(GLenum eTarget, GLenum eQuery,
    GLdouble* adValue);
SE_EXTERN void SE_glGetMapfv(GLenum eTarget, GLenum eQuery, GLfloat* afValue);
SE_EXTERN void SE_glGetMapiv(GLenum eTarget, GLenum eQuery, GLint* aiValue);
SE_EXTERN void SE_glGetMaterialfv(GLenum eFace, GLenum ePName,
    GLfloat* afParam);
SE_EXTERN void SE_glGetMaterialiv(GLenum eFace, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glGetPixelMapfv(GLenum eMap, GLfloat* afValue);
SE_EXTERN void SE_glGetPixelMapuiv(GLenum eMap, GLuint* auiValue);
SE_EXTERN void SE_glGetPixelMapusv(GLenum eMap, GLushort* ausValue);
SE_EXTERN void SE_glGetPointerv(GLenum ePName, GLvoid** apvParam);
SE_EXTERN void SE_glGetPolygonStipple(GLubyte* aucPattern);
SE_EXTERN const GLubyte* SE_glGetString(GLenum eName);
SE_EXTERN void SE_glGetTexEnvfv(GLenum eTarget, GLenum ePName,
    GLfloat* afParam);
SE_EXTERN void SE_glGetTexEnviv(GLenum eTarget, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glGetTexGendv(GLenum eCoord, GLenum ePName,
    GLdouble* adParam);
SE_EXTERN void SE_glGetTexGenfv(GLenum eCoord, GLenum ePName,
    GLfloat* afParam);
SE_EXTERN void SE_glGetTexGeniv(GLenum eCoord, GLenum ePName, GLint* aiParam);
SE_EXTERN void SE_glGetTexImage(GLenum eTarget, GLint iLevel, GLenum eFormat,
    GLenum eType, GLvoid* pvPixels);
SE_EXTERN void SE_glGetTexLevelParameterfv(GLenum eTarget, GLint iLevel,
    GLenum ePName, GLfloat* afParam);
SE_EXTERN void SE_glGetTexLevelParameteriv(GLenum eTarget, GLint iLevel,
    GLenum ePName, GLint* aiParam);
SE_EXTERN void SE_glGetTexParameterfv(GLenum eTarget, GLenum ePName,
    GLfloat* afParam);
SE_EXTERN void SE_glGetTexParameteriv(GLenum eTarget, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glHint(GLenum eTarget, GLenum eMode);
SE_EXTERN void SE_glIndexMask(GLuint uiMask);
SE_EXTERN void SE_glIndexPointer(GLenum eType, GLsizei iStride,
    const GLvoid* pvPointer);
SE_EXTERN void SE_glIndexd(GLdouble dIndex);
SE_EXTERN void SE_glIndexdv(const GLdouble* pdIndex);
SE_EXTERN void SE_glIndexf(GLfloat fIndex);
SE_EXTERN void SE_glIndexfv(const GLfloat* pfIndex);
SE_EXTERN void SE_glIndexi(GLint iIndex);
SE_EXTERN void SE_glIndexiv(const GLint* piIndex);
SE_EXTERN void SE_glIndexs(GLshort sIndex);
SE_EXTERN void SE_glIndexsv(const GLshort* psIndex);
SE_EXTERN void SE_glIndexub(GLubyte ucIndex);
SE_EXTERN void SE_glIndexubv(const GLubyte* pucIndex);
SE_EXTERN void SE_glInitNames(void);
SE_EXTERN void SE_glInterleavedArrays(GLenum eFormat, GLsizei iStride,
    const GLvoid* pvPointer);
SE_EXTERN GLboolean SE_glIsEnabled(GLenum eCapability);
SE_EXTERN GLboolean SE_glIsList(GLuint uiList);
SE_EXTERN GLboolean SE_glIsTexture(GLuint uiTexture);
SE_EXTERN void SE_glLightModelf(GLenum ePName, GLfloat fParam);
SE_EXTERN void SE_glLightModelfv(GLenum ePName, const GLfloat* afParam);
SE_EXTERN void SE_glLightModeli(GLenum ePName, GLint iParam);
SE_EXTERN void SE_glLightModeliv(GLenum ePName, const GLint* aiParam);
SE_EXTERN void SE_glLightf(GLenum eLight, GLenum ePName, GLfloat fParam);
SE_EXTERN void SE_glLightfv(GLenum eLight, GLenum ePName,
    const GLfloat* afParam);
SE_EXTERN void SE_glLighti(GLenum eLight, GLenum ePName, GLint iParam);
SE_EXTERN void SE_glLightiv(GLenum eLight, GLenum ePName,
    const GLint* aiParam);
SE_EXTERN void SE_glLineStipple(GLint iFactor, GLushort usPattern);
SE_EXTERN void SE_glLineWidth(GLfloat fWidth);
SE_EXTERN void SE_glListBase(GLuint uiBase);
SE_EXTERN void SE_glLoadIdentity(void);
SE_EXTERN void SE_glLoadMatrixd(const GLdouble* adMatrix);
SE_EXTERN void SE_glLoadMatrixf(const GLfloat* afMatrix);
SE_EXTERN void SE_glLoadName(GLuint uiName);
SE_EXTERN void SE_glLogicOp(GLenum eOpCode);
SE_EXTERN void SE_glMap1d(GLenum eTarget, GLdouble dU1, GLdouble dU2,
    GLint iStride, GLint iOrder, const GLdouble* adPoints);
SE_EXTERN void SE_glMap1f(GLenum eTarget, GLfloat fU1, GLfloat fU2,
    GLint iStride, GLint iOrder, const GLfloat* afPoints);
SE_EXTERN void SE_glMap2d(GLenum eTarget, GLdouble dU1, GLdouble dU2,
    GLint iUStride, GLint iUOrder, GLdouble dV1, GLdouble dV2,
    GLint iVStride, GLint iVOrder, const GLdouble* adPoints);
SE_EXTERN void SE_glMap2f(GLenum eTarget, GLfloat fU1, GLfloat fU2,
    GLint iUStride, GLint iUOrder, GLfloat fV1, GLfloat fV2, GLint iVStride,
    GLint iVOrder, const GLfloat* afPoints);
SE_EXTERN void SE_glMapGrid1d(GLint iNumUPartitions, GLdouble dU1,
    GLdouble dU2);
SE_EXTERN void SE_glMapGrid1f(GLint iNumUPartitions, GLfloat fU1,
    GLfloat fU2);
SE_EXTERN void SE_glMapGrid2d(GLint iNumUPartitions, GLdouble dU1,
    GLdouble dU2, GLint iNumVPartitions, GLdouble dV1, GLdouble dV2);
SE_EXTERN void SE_glMapGrid2f(GLint iNumUPartitions, GLfloat fU1, GLfloat fU2,
    GLint iNumVPartitions, GLfloat fV1, GLfloat fV2);
SE_EXTERN void SE_glMaterialf(GLenum eFace, GLenum ePName, GLfloat fParam);
SE_EXTERN void SE_glMaterialfv(GLenum eFace, GLenum ePName,
    const GLfloat* afParam);
SE_EXTERN void SE_glMateriali(GLenum eFace, GLenum ePName, GLint iParam);
SE_EXTERN void SE_glMaterialiv(GLenum eFace, GLenum ePName,
    const GLint* aiParam);
SE_EXTERN void SE_glMatrixMode(GLenum eMode);
SE_EXTERN void SE_glMultMatrixd(const GLdouble* adMatrix);
SE_EXTERN void SE_glMultMatrixf(const GLfloat* afMatrix);
SE_EXTERN void SE_glNewList(GLuint uiList, GLenum eMode);
SE_EXTERN void SE_glNormal3b(GLbyte cX, GLbyte cY, GLbyte cZ);
SE_EXTERN void SE_glNormal3bv(const GLbyte* acXYZ);
SE_EXTERN void SE_glNormal3d(GLdouble dX, GLdouble dY, GLdouble dZ);
SE_EXTERN void SE_glNormal3dv(const GLdouble* adXYZ);
SE_EXTERN void SE_glNormal3f(GLfloat fX, GLfloat fY, GLfloat fZ);
SE_EXTERN void SE_glNormal3fv(const GLfloat* afXYZ);
SE_EXTERN void SE_glNormal3i(GLint iX, GLint iY, GLint iZ);
SE_EXTERN void SE_glNormal3iv(const GLint* aiXYZ);
SE_EXTERN void SE_glNormal3s(GLshort sX, GLshort sY, GLshort sZ);
SE_EXTERN void SE_glNormal3sv(const GLshort* asXYZ);
SE_EXTERN void SE_glNormalPointer(GLenum eType, GLsizei iStride,
    const GLvoid* pvPointer);
SE_EXTERN void SE_glOrtho(GLdouble dLeft, GLdouble dRight, GLdouble dBottom,
    GLdouble dTop, GLdouble dZNear, GLdouble dZFar);
SE_EXTERN void SE_glPassThrough(GLfloat fToken);
SE_EXTERN void SE_glPixelMapfv(GLenum eMap, GLsizei iSize,
    const GLfloat* afValue);
SE_EXTERN void SE_glPixelMapuiv(GLenum eMap, GLsizei iSize,
    const GLuint* auiValue);
SE_EXTERN void SE_glPixelMapusv(GLenum eMap, GLsizei iSize,
    const GLushort* ausValue);
SE_EXTERN void SE_glPixelStoref(GLenum ePName, GLfloat fParam);
SE_EXTERN void SE_glPixelStorei(GLenum ePName, GLint iParam);
SE_EXTERN void SE_glPixelTransferf(GLenum ePName, GLfloat fParam);
SE_EXTERN void SE_glPixelTransferi(GLenum ePName, GLint iParam);
SE_EXTERN void SE_glPixelZoom(GLfloat fXFactor, GLfloat fYFactor);
SE_EXTERN void SE_glPointSize(GLfloat fSize);
SE_EXTERN void SE_glPolygonMode(GLenum eFace, GLenum eMode);
SE_EXTERN void SE_glPolygonOffset(GLfloat fScale, GLfloat fBias);
SE_EXTERN void SE_glPolygonStipple(const GLubyte* aucPattern);
SE_EXTERN void SE_glPopAttrib(void);
SE_EXTERN void SE_glPopClientAttrib(void);
SE_EXTERN void SE_glPopMatrix(void);
SE_EXTERN void SE_glPopName(void);
SE_EXTERN void SE_glPrioritizeTextures(GLsizei iNumTextures,
    const GLuint* auiTextures, const GLclampf* afPriorities);
SE_EXTERN void SE_glPushAttrib(GLbitfield uiMask);
SE_EXTERN void SE_glPushClientAttrib(GLbitfield uiMask);
SE_EXTERN void SE_glPushMatrix(void);
SE_EXTERN void SE_glPushName(GLuint uiName);
SE_EXTERN void SE_glRasterPos2d(GLdouble dX, GLdouble dY);
SE_EXTERN void SE_glRasterPos2dv(const GLdouble* adXY);
SE_EXTERN void SE_glRasterPos2f(GLfloat fX, GLfloat fY);
SE_EXTERN void SE_glRasterPos2fv(const GLfloat* afXY);
SE_EXTERN void SE_glRasterPos2i(GLint iX, GLint iY);
SE_EXTERN void SE_glRasterPos2iv(const GLint* aiXY);
SE_EXTERN void SE_glRasterPos2s(GLshort sX, GLshort sY);
SE_EXTERN void SE_glRasterPos2sv(const GLshort* asXY);
SE_EXTERN void SE_glRasterPos3d(GLdouble dX, GLdouble dY, GLdouble dZ);
SE_EXTERN void SE_glRasterPos3dv(const GLdouble* adXYZ);
SE_EXTERN void SE_glRasterPos3f(GLfloat fX, GLfloat fY, GLfloat fZ);
SE_EXTERN void SE_glRasterPos3fv(const GLfloat* afXYZ);
SE_EXTERN void SE_glRasterPos3i(GLint iX, GLint iY, GLint iZ);
SE_EXTERN void SE_glRasterPos3iv(const GLint* aiXYZ);
SE_EXTERN void SE_glRasterPos3s(GLshort sX, GLshort sY, GLshort sZ);
SE_EXTERN void SE_glRasterPos3sv(const GLshort* asXYZ);
SE_EXTERN void SE_glRasterPos4d(GLdouble dX, GLdouble dY, GLdouble dZ,
    GLdouble dW);
SE_EXTERN void SE_glRasterPos4dv(const GLdouble* adXYZW);
SE_EXTERN void SE_glRasterPos4f(GLfloat fX, GLfloat fY, GLfloat fZ,
    GLfloat fW);
SE_EXTERN void SE_glRasterPos4fv(const GLfloat* afXYZW);
SE_EXTERN void SE_glRasterPos4i(int iX, int iY, int iZ, int iW);
SE_EXTERN void SE_glRasterPos4iv(const GLint* aiXYZW);
SE_EXTERN void SE_glRasterPos4s(GLshort sX, GLshort sY, GLshort sZ,
    GLshort sW);
SE_EXTERN void SE_glRasterPos4sv(const GLshort* asXYZW);
SE_EXTERN void SE_glReadBuffer(GLenum eMode);
SE_EXTERN void SE_glReadPixels(GLint iX, GLint iY, GLsizei iWidth,
    GLsizei iHeight, GLenum eFormat, GLenum eType, GLvoid* pvPixels);
SE_EXTERN void SE_glRectd(GLdouble dX1, GLdouble dY1, GLdouble dX2,
    GLdouble dY2);
SE_EXTERN void SE_glRectdv(const GLdouble* adX1Y1, const GLdouble* adX2Y2);
SE_EXTERN void SE_glRectf(GLfloat fX1, GLfloat fY1, GLfloat fX2, GLfloat fY2);
SE_EXTERN void SE_glRectfv(const GLfloat* afX1Y1, const GLfloat* afX2Y2);
SE_EXTERN void SE_glRecti(GLint iX1, GLint iY1, GLint iX2, GLint iY2);
SE_EXTERN void SE_glRectiv(const GLint* aiX1Y1, const GLint* aiX2Y2);
SE_EXTERN void SE_glRects(GLshort sX1, GLshort sY1, GLshort sX2, GLshort sY2);
SE_EXTERN void SE_glRectsv(const GLshort* asX1Y1, const GLshort* asX2Y2);
SE_EXTERN GLint SE_glRenderMode(GLenum eMode);
SE_EXTERN void SE_glRotated(GLdouble dAngle, GLdouble dX, GLdouble dY,
    GLdouble dZ);
SE_EXTERN void SE_glRotatef(GLfloat fAngle, GLfloat fX, GLfloat fY,
    GLfloat fZ);
SE_EXTERN void SE_glScaled(GLdouble dX, GLdouble dY, GLdouble dZ);
SE_EXTERN void SE_glScalef(GLfloat fAngle, GLfloat fX, GLfloat fY);
SE_EXTERN void SE_glScissor(GLint iX, GLint iY, GLsizei iWidth,
    GLsizei iHeight);
SE_EXTERN void SE_glSelectBuffer(GLsizei iSize, GLuint* auiBuffer);
SE_EXTERN void SE_glShadeModel(GLenum eMode);
SE_EXTERN void SE_glStencilFunc(GLenum eFunction, GLint iReference,
    GLuint uiMask);
SE_EXTERN void SE_glStencilMask(GLuint uiMask);
SE_EXTERN void SE_glStencilOp(GLenum eFail, GLenum eZFail, GLenum eZPass);
SE_EXTERN void SE_glTexCoord1d(GLdouble dS);
SE_EXTERN void SE_glTexCoord1dv(const GLdouble* pdS);
SE_EXTERN void SE_glTexCoord1f(GLfloat fS);
SE_EXTERN void SE_glTexCoord1fv(const GLfloat* pfS);
SE_EXTERN void SE_glTexCoord1i(GLint iS);
SE_EXTERN void SE_glTexCoord1iv(const GLint* piS);
SE_EXTERN void SE_glTexCoord1s(GLshort sS);
SE_EXTERN void SE_glTexCoord1sv(const GLshort* psS);
SE_EXTERN void SE_glTexCoord2d(GLdouble dS, GLdouble dT);
SE_EXTERN void SE_glTexCoord2dv(const GLdouble* asDT);
SE_EXTERN void SE_glTexCoord2f(GLfloat fS, GLfloat fT);
SE_EXTERN void SE_glTexCoord2fv(const GLfloat* afST);
SE_EXTERN void SE_glTexCoord2i(GLint iS, GLint iT);
SE_EXTERN void SE_glTexCoord2iv(const GLint* aiST);
SE_EXTERN void SE_glTexCoord2s(GLshort sS, GLshort sT);
SE_EXTERN void SE_glTexCoord2sv(const GLshort* asST);
SE_EXTERN void SE_glTexCoord3d(GLdouble dS, GLdouble dT, GLdouble dR);
SE_EXTERN void SE_glTexCoord3dv(const GLdouble* adSTR);
SE_EXTERN void SE_glTexCoord3f(GLfloat fS, GLfloat fT, GLfloat fR);
SE_EXTERN void SE_glTexCoord3fv(const GLfloat* afSTR);
SE_EXTERN void SE_glTexCoord3i(GLint iS, GLint iT, GLint iR);
SE_EXTERN void SE_glTexCoord3iv(const GLint* aiSTR);
SE_EXTERN void SE_glTexCoord3s(GLshort sS, GLshort sT, GLshort sR);
SE_EXTERN void SE_glTexCoord3sv(const GLshort* asSTR);
SE_EXTERN void SE_glTexCoord4d(GLdouble dS, GLdouble dT, GLdouble dR,
    GLdouble dQ);
SE_EXTERN void SE_glTexCoord4dv(const GLdouble* adSTRQ);
SE_EXTERN void SE_glTexCoord4f(GLfloat fS, GLfloat fT, GLfloat fR,
    GLfloat fQ);
SE_EXTERN void SE_glTexCoord4fv(const GLfloat* afSTRQ);
SE_EXTERN void SE_glTexCoord4i(GLint iS, GLint iT, GLint iR, GLint iQ);
SE_EXTERN void SE_glTexCoord4iv(const GLint* aiSTRQ);
SE_EXTERN void SE_glTexCoord4s(GLshort sS, GLshort sT, GLshort sR,
    GLshort sQ);
SE_EXTERN void SE_glTexCoord4sv(const GLshort* asSTRQ);
SE_EXTERN void SE_glTexCoordPointer(GLint iSize, GLenum eType,
    GLsizei iStride, const GLvoid* pvPointer);
SE_EXTERN void SE_glTexEnvf(GLenum eTarget, GLenum ePName, GLfloat fParam);
SE_EXTERN void SE_glTexEnvfv(GLenum eTarget, GLenum ePName,
    const GLfloat* afParam);
SE_EXTERN void SE_glTexEnvi(GLenum eTarget, GLenum ePName, GLint iParam);
SE_EXTERN void SE_glTexEnviv(GLenum eTarget, GLenum ePName,
    const GLint* aiParam);
SE_EXTERN void SE_glTexGend(GLenum eCoord, GLenum ePName, GLdouble dParam);
SE_EXTERN void SE_glTexGendv(GLenum eCoord, GLenum ePName,
    const GLdouble* adParam);
SE_EXTERN void SE_glTexGenf(GLenum eCoord, GLenum ePName, GLfloat fParam);
SE_EXTERN void SE_glTexGenfv(GLenum eCoord, GLenum ePName,
    const GLfloat* afParam);
SE_EXTERN void SE_glTexGeni(GLenum eCoord, GLenum ePName, GLint iParam);
SE_EXTERN void SE_glTexGeniv(GLenum eCoord, GLenum ePName,
    const GLint* aiParam);
SE_EXTERN void SE_glTexImage1D(GLenum eTarget, GLint iLevel,
    GLint iInternalFormat, GLsizei iWidth, GLint iBorder, GLenum eFormat,
    GLenum eType, const GLvoid* pvPixels);
SE_EXTERN void SE_glTexImage2D(GLenum eTarget, GLint iLevel,
    GLint iInternalFormat, GLsizei iWidth, GLsizei iHeight, GLint iBorder,
    GLenum eFormat, GLenum eType, const GLvoid* pvPixels);
SE_EXTERN void SE_glTexParameterf(GLenum eTarget, GLenum ePName,
    GLfloat fParam);
SE_EXTERN void SE_glTexParameterfv(GLenum eTarget, GLenum ePName,
    const GLfloat* afParam);
SE_EXTERN void SE_glTexParameteri(GLenum eTarget, GLenum ePName,
    GLint iParam);
SE_EXTERN void SE_glTexParameteriv(GLenum eTarget, GLenum ePName,
    const GLint* aiParam);
SE_EXTERN void SE_glTexSubImage1D(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLsizei iWidth, GLenum eFormat, GLenum eType,
    const GLvoid* pvPixels);
SE_EXTERN void SE_glTexSubImage2D(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLint iYOffset, GLsizei iWidth, GLsizei iHeight,
    GLenum eFormat, GLenum eType, const GLvoid* pvPixels);
SE_EXTERN void SE_glTranslated(GLdouble dX, GLdouble dY, GLdouble dZ);
SE_EXTERN void SE_glTranslatef(GLfloat fX, GLfloat fY, GLfloat fZ);
SE_EXTERN void SE_glVertex2d(GLdouble dX, GLdouble dY);
SE_EXTERN void SE_glVertex2dv(const GLdouble* adXY);
SE_EXTERN void SE_glVertex2f(GLfloat fX, GLfloat fY);
SE_EXTERN void SE_glVertex2fv(const GLfloat* afXY);
SE_EXTERN void SE_glVertex2i(GLint iX, GLint iY);
SE_EXTERN void SE_glVertex2iv(const GLint* aiXY);
SE_EXTERN void SE_glVertex2s(GLshort sX, GLshort sY);
SE_EXTERN void SE_glVertex2sv(const GLshort* asXY);
SE_EXTERN void SE_glVertex3d(GLdouble dX, GLdouble dY, GLdouble dZ);
SE_EXTERN void SE_glVertex3dv(const GLdouble* adXYZ);
SE_EXTERN void SE_glVertex3f(GLfloat fX, GLfloat fY, GLfloat fZ);
SE_EXTERN void SE_glVertex3fv(const GLfloat* afXYZ);
SE_EXTERN void SE_glVertex3i(GLint iX, GLint iY, GLint iZ);
SE_EXTERN void SE_glVertex3iv(const GLint* aiXYZ);
SE_EXTERN void SE_glVertex3s(GLshort sX, GLshort sY, GLshort sZ);
SE_EXTERN void SE_glVertex3sv(const GLshort* asXYZ);
SE_EXTERN void SE_glVertex4d(GLdouble dX, GLdouble dY, GLdouble dZ,
    GLdouble dW);
SE_EXTERN void SE_glVertex4dv(const GLdouble* adXYZW);
SE_EXTERN void SE_glVertex4f(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fW);
SE_EXTERN void SE_glVertex4fv(const GLfloat* afXYZW);
SE_EXTERN void SE_glVertex4i(GLint iX, GLint iY, GLint iZ, GLint iW);
SE_EXTERN void SE_glVertex4iv(const GLint* aiXYZW);
SE_EXTERN void SE_glVertex4s(GLshort sX, GLshort sY, GLshort sZ, GLshort sW);
SE_EXTERN void SE_glVertex4sv(const GLshort* asXYZW);
SE_EXTERN void SE_glVertexPointer(GLint iSize, GLenum eType, GLsizei iStride,
    const GLvoid* pvPointer);
SE_EXTERN void SE_glViewport(GLint iX, GLint iY, GLsizei iWidth, GLsizei iHeight);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* OpenGL 1.2 */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsOpenGL12;

#define GL_SMOOTH_POINT_SIZE_RANGE                                  0x0B12
#define GL_SMOOTH_POINT_SIZE_GRANULARITY                            0x0B13
#define GL_SMOOTH_LINE_WIDTH_RANGE                                  0x0B22
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY                            0x0B23
#define GL_UNSIGNED_BYTE_3_3_2                                      0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4                                   0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1                                   0x8034
#define GL_UNSIGNED_INT_8_8_8_8                                     0x8035
#define GL_UNSIGNED_INT_10_10_10_2                                  0x8036
#define GL_RESCALE_NORMAL                                           0x803A
#define GL_TEXTURE_BINDING_3D                                       0x806A
#define GL_PACK_SKIP_IMAGES                                         0x806B
#define GL_PACK_IMAGE_HEIGHT                                        0x806C
#define GL_UNPACK_SKIP_IMAGES                                       0x806D
#define GL_UNPACK_IMAGE_HEIGHT                                      0x806E
#define GL_TEXTURE_3D                                               0x806F
#define GL_PROXY_TEXTURE_3D                                         0x8070
#define GL_TEXTURE_DEPTH                                            0x8071
#define GL_TEXTURE_WRAP_R                                           0x8072
#define GL_MAX_3D_TEXTURE_SIZE                                      0x8073
#define GL_BGR                                                      0x80E0
#define GL_BGRA                                                     0x80E1
#define GL_MAX_ELEMENTS_VERTICES                                    0x80E8
#define GL_MAX_ELEMENTS_INDICES                                     0x80E9
#define GL_CLAMP_TO_EDGE                                            0x812F
#define GL_TEXTURE_MIN_LOD                                          0x813A
#define GL_TEXTURE_MAX_LOD                                          0x813B
#define GL_TEXTURE_BASE_LEVEL                                       0x813C
#define GL_TEXTURE_MAX_LEVEL                                        0x813D
#define GL_LIGHT_MODEL_COLOR_CONTROL                                0x81F8
#define GL_SINGLE_COLOR                                             0x81F9
#define GL_SEPARATE_SPECULAR_COLOR                                  0x81FA
#define GL_UNSIGNED_BYTE_2_3_3_REV                                  0x8362
#define GL_UNSIGNED_SHORT_5_6_5                                     0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV                                 0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4_REV                               0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV                               0x8366
#define GL_UNSIGNED_INT_8_8_8_8_REV                                 0x8367
#define GL_UNSIGNED_INT_2_10_10_10_REV                              0x8368
#define GL_ALIASED_POINT_SIZE_RANGE                                 0x846D
#define GL_ALIASED_LINE_WIDTH_RANGE                                 0x846E

#define glDrawRangeElements SE_glDrawRangeElements
#define glTexImage3D SE_glTexImage3D
#define glTexSubImage3D SE_glTexSubImage3D
#define glCopyTexSubImage3D SE_glCopyTexSubImage3D

SE_EXTERN void SE_glDrawRangeElements(GLenum eMode, GLuint uiStart,
    GLuint uiEnd, GLsizei iCount, GLenum eType, const GLvoid* pvIndices);
SE_EXTERN void SE_glTexImage3D(GLenum eTarget, GLint iLevel,
    GLint iInternalFormat, GLsizei iWidth, GLsizei iHeight, GLsizei iDepth,
    GLint iBorder, GLenum eFormat, GLenum eType, const GLvoid* pvData);
SE_EXTERN void SE_glTexSubImage3D(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLint iYOffset, GLint iZOffset, GLsizei iWidth,
    GLsizei iHeight, GLsizei iDepth, GLenum eFormat, GLenum eType,
    const GLvoid* pvData);
SE_EXTERN void SE_glCopyTexSubImage3D(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLint iYOffset, GLint iZOffset, GLint iX, GLint iY,
    GLsizei iWidth, GLsizei iHeight);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Imaging Subset (GL_ARB_imaging) */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbImaging;

#define GL_CONSTANT_COLOR                                           0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR                                 0x8002
#define GL_CONSTANT_ALPHA                                           0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA                                 0x8004
#define GL_BLEND_COLOR                                              0x8005
#define GL_FUNC_ADD                                                 0x8006
#define GL_MIN                                                      0x8007
#define GL_MAX                                                      0x8008
#define GL_BLEND_EQUATION                                           0x8009
#define GL_FUNC_SUBTRACT                                            0x800A
#define GL_FUNC_REVERSE_SUBTRACT                                    0x800B
#define GL_CONVOLUTION_1D                                           0x8010
#define GL_CONVOLUTION_2D                                           0x8011
#define GL_SEPARABLE_2D                                             0x8012
#define GL_CONVOLUTION_BORDER_MODE                                  0x8013
#define GL_CONVOLUTION_FILTER_SCALE                                 0x8014
#define GL_CONVOLUTION_FILTER_BIAS                                  0x8015
#define GL_REDUCE                                                   0x8016
#define GL_CONVOLUTION_FORMAT                                       0x8017
#define GL_CONVOLUTION_WIDTH                                        0x8018
#define GL_CONVOLUTION_HEIGHT                                       0x8019
#define GL_MAX_CONVOLUTION_WIDTH                                    0x801A
#define GL_MAX_CONVOLUTION_HEIGHT                                   0x801B
#define GL_POST_CONVOLUTION_RED_SCALE                               0x801C
#define GL_POST_CONVOLUTION_GREEN_SCALE                             0x801D
#define GL_POST_CONVOLUTION_BLUE_SCALE                              0x801E
#define GL_POST_CONVOLUTION_ALPHA_SCALE                             0x801F
#define GL_POST_CONVOLUTION_RED_BIAS                                0x8020
#define GL_POST_CONVOLUTION_GREEN_BIAS                              0x8021
#define GL_POST_CONVOLUTION_BLUE_BIAS                               0x8022
#define GL_POST_CONVOLUTION_ALPHA_BIAS                              0x8023
#define GL_HISTOGRAM                                                0x8024
#define GL_PROXY_HISTOGRAM                                          0x8025
#define GL_HISTOGRAM_WIDTH                                          0x8026
#define GL_HISTOGRAM_FORMAT                                         0x8027
#define GL_HISTOGRAM_RED_SIZE                                       0x8028
#define GL_HISTOGRAM_GREEN_SIZE                                     0x8029
#define GL_HISTOGRAM_BLUE_SIZE                                      0x802A
#define GL_HISTOGRAM_ALPHA_SIZE                                     0x802B
#define GL_HISTOGRAM_LUMINANCE_SIZE                                 0x802C
#define GL_HISTOGRAM_SINK                                           0x802D
#define GL_MINMAX                                                   0x802E
#define GL_MINMAX_FORMAT                                            0x802F
#define GL_MINMAX_SINK                                              0x8030
#define GL_TABLE_TOO_LARGE                                          0x8031
#define GL_COLOR_MATRIX                                             0x80B1
#define GL_COLOR_MATRIX_STACK_DEPTH                                 0x80B2
#define GL_MAX_COLOR_MATRIX_STACK_DEPTH                             0x80B3
#define GL_POST_COLOR_MATRIX_RED_SCALE                              0x80B4
#define GL_POST_COLOR_MATRIX_GREEN_SCALE                            0x80B5
#define GL_POST_COLOR_MATRIX_BLUE_SCALE                             0x80B6
#define GL_POST_COLOR_MATRIX_ALPHA_SCALE                            0x80B7
#define GL_POST_COLOR_MATRIX_RED_BIAS                               0x80B8
#define GL_POST_COLOR_MATRIX_GREEN_BIAS                             0x80B9
#define GL_POST_COLOR_MATRIX_BLUE_BIAS                              0x80BA
#define GL_POST_COLOR_MATRIX_ALPHA_BIAS                             0x80BB
#define GL_COLOR_TABLE                                              0x80D0
#define GL_POST_CONVOLUTION_COLOR_TABLE                             0x80D1
#define GL_POST_COLOR_MATRIX_COLOR_TABLE                            0x80D2
#define GL_PROXY_COLOR_TABLE                                        0x80D3
#define GL_PROXY_POST_CONVOLUTION_COLOR_TABLE                       0x80D4
#define GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE                      0x80D5
#define GL_COLOR_TABLE_SCALE                                        0x80D6
#define GL_COLOR_TABLE_BIAS                                         0x80D7
#define GL_COLOR_TABLE_FORMAT                                       0x80D8
#define GL_COLOR_TABLE_WIDTH                                        0x80D9
#define GL_COLOR_TABLE_RED_SIZE                                     0x80DA
#define GL_COLOR_TABLE_GREEN_SIZE                                   0x80DB
#define GL_COLOR_TABLE_BLUE_SIZE                                    0x80DC
#define GL_COLOR_TABLE_ALPHA_SIZE                                   0x80DD
#define GL_COLOR_TABLE_LUMINANCE_SIZE                               0x80DE
#define GL_COLOR_TABLE_INTENSITY_SIZE                               0x80DF
#define GL_CONSTANT_BORDER                                          0x8151
#define GL_REPLICATE_BORDER                                         0x8153
#define GL_CONVOLUTION_BORDER_COLOR                                 0x8154

#define glBlendColor SE_glBlendColor
#define glBlendEquation SE_glBlendEquation
#define glColorTable SE_glColorTable
#define glColorTableParameterfv SE_glColorTableParameterfv
#define glColorTableParameteriv SE_glColorTableParameteriv
#define glCopyColorTable SE_glCopyColorTable
#define glGetColorTable SE_glGetColorTable
#define glGetColorTableParameterfv SE_glGetColorTableParameterfv
#define glGetColorTableParameteriv SE_glGetColorTableParameteriv
#define glColorSubTable SE_glColorSubTable
#define glCopyColorSubTable SE_glCopyColorSubTable
#define glConvolutionFilter1D SE_glConvolutionFilter1D
#define glConvolutionFilter2D SE_glConvolutionFilter2D
#define glConvolutionParameterf SE_glConvolutionParameterf
#define glConvolutionParameterfv SE_glConvolutionParameterfv
#define glConvolutionParameteri SE_glConvolutionParameteri
#define glConvolutionParameteriv SE_glConvolutionParameteriv
#define glCopyConvolutionFilter1D SE_glCopyConvolutionFilter1D
#define glCopyConvolutionFilter2D SE_glCopyConvolutionFilter2D
#define glGetConvolutionFilter SE_glGetConvolutionFilter
#define glGetConvolutionParameterfv SE_glGetConvolutionParameterfv
#define glGetConvolutionParameteriv SE_glGetConvolutionParameteriv
#define glGetSeparableFilter SE_glGetSeparableFilter
#define glSeparableFilter2D SE_glSeparableFilter2D
#define glGetHistogram SE_glGetHistogram
#define glGetHistogramParameterfv SE_glGetHistogramParameterfv
#define glGetHistogramParameteriv SE_glGetHistogramParameteriv
#define glGetMinmax SE_glGetMinmax
#define glGetMinmaxParameterfv SE_glGetMinmaxParameterfv
#define glGetMinmaxParameteriv SE_glGetMinmaxParameteriv
#define glHistogram SE_glHistogram
#define glMinmax SE_glMinmax
#define glResetHistogram SE_glResetHistogram
#define glResetMinmax SE_glResetMinmax

SE_EXTERN void SE_glBlendColor(GLclampf fRed, GLclampf fGreen,
    GLclampf fBlue, GLclampf fAlpha);
SE_EXTERN void SE_glBlendEquation(GLenum eMode);
SE_EXTERN void SE_glColorTable(GLenum eTarget, GLenum eInternalFormat,
    GLsizei iWidth, GLenum eFormat, GLenum eType, const GLvoid* pvTable);
SE_EXTERN void SE_glColorTableParameterfv(GLenum eTarget, GLenum ePName,
    const GLfloat* afParam);
SE_EXTERN void SE_glColorTableParameteriv(GLenum eTarget, GLenum ePName,
    const GLint* aiParam);
SE_EXTERN void SE_glCopyColorTable(GLenum eTarget, GLenum eInternalFormat,
    GLint iX, GLint iY, GLsizei iWidth);
SE_EXTERN void SE_glGetColorTable(GLenum eTarget, GLenum eFormat,
    GLenum eType, GLvoid* pvTable);
SE_EXTERN void SE_glGetColorTableParameterfv(GLenum eTarget, GLenum ePName,
    GLfloat* afParam);
SE_EXTERN void SE_glGetColorTableParameteriv(GLenum eTarget, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glColorSubTable(GLenum eTarget, GLsizei iStart,
    GLsizei iCount, GLenum eFormat, GLenum eType, const GLvoid* pvData);
SE_EXTERN void SE_glCopyColorSubTable(GLenum eTarget, GLsizei iStart,
    GLint iX, GLint iY, GLsizei iWidth);
SE_EXTERN void SE_glConvolutionFilter1D(GLenum eTarget,
    GLenum eInternalFormat, GLsizei iWidth, GLenum eFormat, GLenum eType,
    const GLvoid* pvImage);
SE_EXTERN void SE_glConvolutionFilter2D(GLenum eTarget,
    GLenum eInternalFormat, GLsizei iWidth, GLsizei iHeight, GLenum eFormat,
    GLenum eType, const GLvoid* pvImage);
SE_EXTERN void SE_glConvolutionParameterf(GLenum eTarget, GLenum ePName,
    GLfloat fParam);
SE_EXTERN void SE_glConvolutionParameterfv(GLenum eTarget, GLenum ePName,
    const GLfloat* afParam);
SE_EXTERN void SE_glConvolutionParameteri(GLenum eTarget, GLenum ePName,
    GLint iParam);
SE_EXTERN void SE_glConvolutionParameteriv(GLenum eTarget, GLenum ePName,
    const GLint* aiParam);
SE_EXTERN void SE_glCopyConvolutionFilter1D(GLenum eTarget,
    GLenum eInternalFormat, GLint iX, GLint iY, GLsizei iWidth);
SE_EXTERN void SE_glCopyConvolutionFilter2D(GLenum eTarget,
    GLenum eInternalFormat, GLint iX, GLint iY, GLsizei iWidth,
    GLsizei iHeight);
SE_EXTERN void SE_glGetConvolutionFilter(GLenum eTarget, GLenum eFormat,
    GLenum eType, GLvoid* pvImage);
SE_EXTERN void SE_glGetConvolutionParameterfv(GLenum eTarget, GLenum ePName,
    GLfloat* afParam);
SE_EXTERN void SE_glGetConvolutionParameteriv(GLenum eTarget, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glGetSeparableFilter(GLenum eTarget, GLenum eFormat,
    GLenum eType, GLvoid* pvRow, GLvoid* pvColumn, GLvoid* pvSpan);
SE_EXTERN void SE_glSeparableFilter2D(GLenum eTarget, GLenum eInternalFormat,
    GLsizei iWidth, GLsizei iHeight, GLenum eFormat, GLenum eType,
    const GLvoid* pvRow, const GLvoid* pvColumn);
SE_EXTERN void SE_glGetHistogram(GLenum eTarget, GLboolean ucReset,
    GLenum eFormat, GLenum eType, GLvoid* pvValues);
SE_EXTERN void SE_glGetHistogramParameterfv(GLenum eTarget, GLenum ePName,
    GLfloat* afParam);
SE_EXTERN void SE_glGetHistogramParameteriv(GLenum eTarget, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glGetMinmax(GLenum eTarget, GLboolean ucReset,
    GLenum eFormat, GLenum eType, GLvoid* pvValues);
SE_EXTERN void SE_glGetMinmaxParameterfv(GLenum eTarget, GLenum ePName,
    GLfloat* afParam);
SE_EXTERN void SE_glGetMinmaxParameteriv(GLenum eTarget, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glHistogram(GLenum eTarget, GLsizei iWidth,
    GLenum eInternalFormat, GLboolean ucSink);
SE_EXTERN void SE_glMinmax(GLenum eTarget, GLenum eInternalFormat,
    GLboolean ucSink);
SE_EXTERN void SE_glResetHistogram(GLenum eTarget);
SE_EXTERN void SE_glResetMinmax(GLenum eTarget);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* OpenGL 1.3 */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsOpenGL13;

#define GL_TEXTURE0                                                 0x84C0
#define GL_TEXTURE1                                                 0x84C1
#define GL_TEXTURE2                                                 0x84C2
#define GL_TEXTURE3                                                 0x84C3
#define GL_TEXTURE4                                                 0x84C4
#define GL_TEXTURE5                                                 0x84C5
#define GL_TEXTURE6                                                 0x84C6
#define GL_TEXTURE7                                                 0x84C7
#define GL_TEXTURE8                                                 0x84C8
#define GL_TEXTURE9                                                 0x84C9
#define GL_TEXTURE10                                                0x84CA
#define GL_TEXTURE11                                                0x84CB
#define GL_TEXTURE12                                                0x84CC
#define GL_TEXTURE13                                                0x84CD
#define GL_TEXTURE14                                                0x84CE
#define GL_TEXTURE15                                                0x84CF
#define GL_TEXTURE16                                                0x84D0
#define GL_TEXTURE17                                                0x84D1
#define GL_TEXTURE18                                                0x84D2
#define GL_TEXTURE19                                                0x84D3
#define GL_TEXTURE20                                                0x84D4
#define GL_TEXTURE21                                                0x84D5
#define GL_TEXTURE22                                                0x84D6
#define GL_TEXTURE23                                                0x84D7
#define GL_TEXTURE24                                                0x84D8
#define GL_TEXTURE25                                                0x84D9
#define GL_TEXTURE26                                                0x84DA
#define GL_TEXTURE27                                                0x84DB
#define GL_TEXTURE28                                                0x84DC
#define GL_TEXTURE29                                                0x84DD
#define GL_TEXTURE30                                                0x84DE
#define GL_TEXTURE31                                                0x84DF
#define GL_ACTIVE_TEXTURE                                           0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE                                    0x84E1
#define GL_MAX_TEXTURE_UNITS                                        0x84E2
#define GL_TRANSPOSE_MODELVIEW_MATRIX                               0x84E3
#define GL_TRANSPOSE_PROJECTION_MATRIX                              0x84E4
#define GL_TRANSPOSE_TEXTURE_MATRIX                                 0x84E5
#define GL_TRANSPOSE_COLOR_MATRIX                                   0x84E6
#define GL_MULTISAMPLE                                              0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE                                 0x809E
#define GL_SAMPLE_ALPHA_TO_ONE                                      0x809F
#define GL_SAMPLE_COVERAGE                                          0x80A0
#define GL_SAMPLE_BUFFERS                                           0x80A8
#define GL_SAMPLES                                                  0x80A9
#define GL_SAMPLE_COVERAGE_VALUE                                    0x80AA
#define GL_SAMPLE_COVERAGE_INVERT                                   0x80AB
#define GL_MULTISAMPLE_BIT                                          0x20000000
#define GL_NORMAL_MAP                                               0x8511
#define GL_REFLECTION_MAP                                           0x8512
#define GL_TEXTURE_CUBE_MAP                                         0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP                                 0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X                              0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X                              0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y                              0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y                              0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z                              0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z                              0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP                                   0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE                                0x851C
#define GL_COMPRESSED_ALPHA                                         0x84E9
#define GL_COMPRESSED_LUMINANCE                                     0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA                               0x84EB
#define GL_COMPRESSED_INTENSITY                                     0x84EC
#define GL_COMPRESSED_RGB                                           0x84ED
#define GL_COMPRESSED_RGBA                                          0x84EE
#define GL_TEXTURE_COMPRESSION_HINT                                 0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE                            0x86A0
#define GL_TEXTURE_COMPRESSED                                       0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS                           0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS                               0x86A3
#define GL_CLAMP_TO_BORDER                                          0x812D
#define GL_COMBINE                                                  0x8570
#define GL_COMBINE_RGB                                              0x8571
#define GL_COMBINE_ALPHA                                            0x8572
#define GL_SOURCE0_RGB                                              0x8580
#define GL_SOURCE1_RGB                                              0x8581
#define GL_SOURCE2_RGB                                              0x8582
#define GL_SOURCE0_ALPHA                                            0x8588
#define GL_SOURCE1_ALPHA                                            0x8589
#define GL_SOURCE2_ALPHA                                            0x858A
#define GL_OPERAND0_RGB                                             0x8590
#define GL_OPERAND1_RGB                                             0x8591
#define GL_OPERAND2_RGB                                             0x8592
#define GL_OPERAND0_ALPHA                                           0x8598
#define GL_OPERAND1_ALPHA                                           0x8599
#define GL_OPERAND2_ALPHA                                           0x859A
#define GL_RGB_SCALE                                                0x8573
#define GL_ADD_SIGNED                                               0x8574
#define GL_INTERPOLATE                                              0x8575
#define GL_SUBTRACT                                                 0x84E7
#define GL_CONSTANT                                                 0x8576
#define GL_PRIMARY_COLOR                                            0x8577
#define GL_PREVIOUS                                                 0x8578
#define GL_DOT3_RGB                                                 0x86AE
#define GL_DOT3_RGBA                                                0x86AF

#define glActiveTexture SE_glActiveTexture
#define glClientActiveTexture SE_glClientActiveTexture
#define glMultiTexCoord1d SE_glMultiTexCoord1d
#define glMultiTexCoord1dv SE_glMultiTexCoord1dv
#define glMultiTexCoord1f SE_glMultiTexCoord1f
#define glMultiTexCoord1fv SE_glMultiTexCoord1fv
#define glMultiTexCoord1i SE_glMultiTexCoord1i
#define glMultiTexCoord1iv SE_glMultiTexCoord1iv
#define glMultiTexCoord1s SE_glMultiTexCoord1s
#define glMultiTexCoord1sv SE_glMultiTexCoord1sv
#define glMultiTexCoord2d SE_glMultiTexCoord2d
#define glMultiTexCoord2dv SE_glMultiTexCoord2dv
#define glMultiTexCoord2f SE_glMultiTexCoord2f
#define glMultiTexCoord2fv SE_glMultiTexCoord2fv
#define glMultiTexCoord2i SE_glMultiTexCoord2i
#define glMultiTexCoord2iv SE_glMultiTexCoord2iv
#define glMultiTexCoord2s SE_glMultiTexCoord2s
#define glMultiTexCoord2sv SE_glMultiTexCoord2sv
#define glMultiTexCoord3d SE_glMultiTexCoord3d
#define glMultiTexCoord3dv SE_glMultiTexCoord3dv
#define glMultiTexCoord3f SE_glMultiTexCoord3f
#define glMultiTexCoord3fv SE_glMultiTexCoord3fv
#define glMultiTexCoord3i SE_glMultiTexCoord3i
#define glMultiTexCoord3iv SE_glMultiTexCoord3iv
#define glMultiTexCoord3s SE_glMultiTexCoord3s
#define glMultiTexCoord3sv SE_glMultiTexCoord3sv
#define glMultiTexCoord4d SE_glMultiTexCoord4d
#define glMultiTexCoord4dv SE_glMultiTexCoord4dv
#define glMultiTexCoord4f SE_glMultiTexCoord4f
#define glMultiTexCoord4fv SE_glMultiTexCoord4fv
#define glMultiTexCoord4i SE_glMultiTexCoord4i
#define glMultiTexCoord4iv SE_glMultiTexCoord4iv
#define glMultiTexCoord4s SE_glMultiTexCoord4s
#define glMultiTexCoord4sv SE_glMultiTexCoord4sv
#define glLoadTransposeMatrixd SE_glLoadTransposeMatrixd
#define glLoadTransposeMatrixf SE_glLoadTransposeMatrixf
#define glMultTransposeMatrixd SE_glMultTransposeMatrixd
#define glMultTransposeMatrixf SE_glMultTransposeMatrixf
#define glSampleCoverage SE_glSampleCoverage
#define glCompressedTexImage1D SE_glCompressedTexImage1D
#define glCompressedTexImage2D SE_glCompressedTexImage2D
#define glCompressedTexImage3D SE_glCompressedTexImage3D
#define glCompressedTexSubImage1D SE_glCompressedTexSubImage1D
#define glCompressedTexSubImage2D SE_glCompressedTexSubImage2D
#define glCompressedTexSubImage3D SE_glCompressedTexSubImage3D
#define glGetCompressedTexImage SE_glGetCompressedTexImage

SE_EXTERN void SE_glActiveTexture(GLenum eTexture);
SE_EXTERN void SE_glClientActiveTexture(GLenum eTexture);
SE_EXTERN void SE_glMultiTexCoord1d(GLenum eTarget, GLdouble dS);
SE_EXTERN void SE_glMultiTexCoord1dv(GLenum eTarget, const GLdouble* pdS);
SE_EXTERN void SE_glMultiTexCoord1f(GLenum eTarget, GLfloat fS);
SE_EXTERN void SE_glMultiTexCoord1fv(GLenum eTarget, const GLfloat* pfS);
SE_EXTERN void SE_glMultiTexCoord1i(GLenum eTarget, GLint iS);
SE_EXTERN void SE_glMultiTexCoord1iv(GLenum eTarget, const GLint* piS);
SE_EXTERN void SE_glMultiTexCoord1s(GLenum eTarget, GLshort sS);
SE_EXTERN void SE_glMultiTexCoord1sv(GLenum eTarget, const GLshort* psS);
SE_EXTERN void SE_glMultiTexCoord2d(GLenum eTarget, GLdouble dS, GLdouble dT);
SE_EXTERN void SE_glMultiTexCoord2dv(GLenum eTarget, const GLdouble* asDT);
SE_EXTERN void SE_glMultiTexCoord2f(GLenum eTarget, GLfloat fS, GLfloat fT);
SE_EXTERN void SE_glMultiTexCoord2fv(GLenum eTarget, const GLfloat* afST);
SE_EXTERN void SE_glMultiTexCoord2i(GLenum eTarget, GLint iS, GLint iT);
SE_EXTERN void SE_glMultiTexCoord2iv(GLenum eTarget, const GLint* aiST);
SE_EXTERN void SE_glMultiTexCoord2s(GLenum eTarget, GLshort sS, GLshort sT);
SE_EXTERN void SE_glMultiTexCoord2sv(GLenum eTarget, const GLshort* asST);
SE_EXTERN void SE_glMultiTexCoord3d(GLenum eTarget, GLdouble dS, GLdouble dT,
    GLdouble dR);
SE_EXTERN void SE_glMultiTexCoord3dv(GLenum eTarget, const GLdouble* adSTR);
SE_EXTERN void SE_glMultiTexCoord3f(GLenum eTarget, GLfloat fS, GLfloat fT,
    GLfloat fR);
SE_EXTERN void SE_glMultiTexCoord3fv(GLenum eTarget, const GLfloat* afSTR);
SE_EXTERN void SE_glMultiTexCoord3i(GLenum eTarget, GLint iS, GLint iT,
    GLint iR);
SE_EXTERN void SE_glMultiTexCoord3iv(GLenum eTarget, const GLint* aiSTR);
SE_EXTERN void SE_glMultiTexCoord3s(GLenum eTarget, GLshort sS, GLshort sT,
    GLshort sR);
SE_EXTERN void SE_glMultiTexCoord3sv(GLenum eTarget, const GLshort* asSTR);
SE_EXTERN void SE_glMultiTexCoord4d(GLenum eTarget, GLdouble dS, GLdouble dT,
    GLdouble dR, GLdouble dQ);
SE_EXTERN void SE_glMultiTexCoord4dv(GLenum eTarget, const GLdouble* asSTRQ);
SE_EXTERN void SE_glMultiTexCoord4f(GLenum eTarget, GLfloat fS, GLfloat fT,
    GLfloat fR, GLfloat fQ);
SE_EXTERN void SE_glMultiTexCoord4fv(GLenum eTarget, const GLfloat* afSTRQ);
SE_EXTERN void SE_glMultiTexCoord4i(GLenum eTarget, GLint iS, GLint iT,
    GLint iR, GLint iQ);
SE_EXTERN void SE_glMultiTexCoord4iv(GLenum eTarget, const GLint* aiSTRQ);
SE_EXTERN void SE_glMultiTexCoord4s(GLenum eTarget, GLshort sS, GLshort sT,
    GLshort sR, GLshort sQ);
SE_EXTERN void SE_glMultiTexCoord4sv(GLenum eTarget, const GLshort* asSTRQ);
SE_EXTERN void SE_glLoadTransposeMatrixd(const GLdouble* adMatrix);
SE_EXTERN void SE_glLoadTransposeMatrixf(const GLfloat* afMatrix);
SE_EXTERN void SE_glMultTransposeMatrixd(const GLdouble* adMatrix);
SE_EXTERN void SE_glMultTransposeMatrixf(const GLfloat* afMatrix);
SE_EXTERN void SE_glSampleCoverage(GLclampf fValue, GLboolean ucInvert);
SE_EXTERN void SE_glCompressedTexImage1D(GLenum eTarget, GLint iLevel,
    GLenum eInternalFormat, GLsizei iWidth, GLint iBorder, GLsizei iImageSize,
    const GLvoid* pvData);
SE_EXTERN void SE_glCompressedTexImage2D(GLenum eTarget, GLint iLevel,
    GLenum eInternalFormat, GLsizei iWidth, GLsizei iHeight, GLint iBorder,
    GLsizei iImageSize, const GLvoid* pvData);
SE_EXTERN void SE_glCompressedTexImage3D(GLenum eTarget, GLint iLevel,
    GLenum eInternalFormat, GLsizei iWidth, GLsizei iHeight, GLsizei iDepth,
    GLint iBorder, GLsizei iImageSize, const GLvoid* pvData);
SE_EXTERN void SE_glCompressedTexSubImage1D(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLsizei iWidth, GLenum eFormat, GLsizei iImageSize,
    const GLvoid* pvData);
SE_EXTERN void SE_glCompressedTexSubImage2D(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLint iYOffset, GLsizei iWidth, GLsizei iHeight,
    GLenum eFormat, GLsizei iImageSize, const GLvoid* pvData);
SE_EXTERN void SE_glCompressedTexSubImage3D(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLint iYOffset, GLint iZOffset, GLsizei iWidth,
    GLsizei iHeight, GLsizei iDepth, GLenum eFormat, GLsizei iImageSize,
    const GLvoid* pvData);
SE_EXTERN void SE_glGetCompressedTexImage(GLenum eTarget, GLint iLevel,
    GLvoid* pvData);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* OpenGL 1.4 */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsOpenGL14;

#define GL_BLEND_DST_RGB                                            0x80C8
#define GL_BLEND_SRC_RGB                                            0x80C9
#define GL_BLEND_DST_ALPHA                                          0x80CA
#define GL_BLEND_SRC_ALPHA                                          0x80CB
#define GL_POINT_SIZE_MIN                                           0x8126
#define GL_POINT_SIZE_MAX                                           0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE                                0x8128
#define GL_POINT_DISTANCE_ATTENUATION                               0x8129
#define GL_GENERATE_MIPMAP                                          0x8191
#define GL_GENERATE_MIPMAP_HINT                                     0x8192
#define GL_DEPTH_COMPONENT16                                        0x81A5
#define GL_DEPTH_COMPONENT24                                        0x81A6
#define GL_DEPTH_COMPONENT32                                        0x81A7
#define GL_MIRRORED_REPEAT                                          0x8370
#define GL_FOG_COORDINATE_SOURCE                                    0x8450
#define GL_FOG_COORDINATE                                           0x8451
#define GL_FRAGMENT_DEPTH                                           0x8452
#define GL_CURRENT_FOG_COORDINATE                                   0x8453
#define GL_FOG_COORDINATE_ARRAY_TYPE                                0x8454
#define GL_FOG_COORDINATE_ARRAY_STRIDE                              0x8455
#define GL_FOG_COORDINATE_ARRAY_POINTER                             0x8456
#define GL_FOG_COORDINATE_ARRAY                                     0x8457
#define GL_COLOR_SUM                                                0x8458
#define GL_CURRENT_SECONDARY_COLOR                                  0x8459
#define GL_SECONDARY_COLOR_ARRAY_SIZE                               0x845A
#define GL_SECONDARY_COLOR_ARRAY_TYPE                               0x845B
#define GL_SECONDARY_COLOR_ARRAY_STRIDE                             0x845C
#define GL_SECONDARY_COLOR_ARRAY_POINTER                            0x845D
#define GL_SECONDARY_COLOR_ARRAY                                    0x845E
#define GL_MAX_TEXTURE_LOD_BIAS                                     0x84FD
#define GL_TEXTURE_FILTER_CONTROL                                   0x8500
#define GL_TEXTURE_LOD_BIAS                                         0x8501
#define GL_INCR_WRAP                                                0x8507
#define GL_DECR_WRAP                                                0x8508
#define GL_TEXTURE_DEPTH_SIZE                                       0x884A
#define GL_DEPTH_TEXTURE_MODE                                       0x884B
#define GL_TEXTURE_COMPARE_MODE                                     0x884C
#define GL_TEXTURE_COMPARE_FUNC                                     0x884D
#define GL_COMPARE_R_TO_TEXTURE                                     0x884E

#define glBlendFuncSeparate SE_glBlendFuncSeparate
#define glFogCoordd SE_glFogCoordd
#define glFogCoorddv SE_glFogCoorddv
#define glFogCoordf SE_glFogCoordf
#define glFogCoordfv SE_glFogCoordfv
#define glFogCoordPointer SE_glFogCoordPointer
#define glMultiDrawArrays SE_glMultiDrawArrays
#define glMultiDrawElements SE_glMultiDrawElements
#define glPointParameterf SE_glPointParameterf
#define glPointParameterfv SE_glPointParameterfv
#define glPointParameteri SE_glPointParameteri
#define glPointParameteriv SE_glPointParameteriv
#define glSecondaryColor3b SE_glSecondaryColor3b
#define glSecondaryColor3bv SE_glSecondaryColor3bv
#define glSecondaryColor3d SE_glSecondaryColor3d
#define glSecondaryColor3dv SE_glSecondaryColor3dv
#define glSecondaryColor3f SE_glSecondaryColor3f
#define glSecondaryColor3fv SE_glSecondaryColor3fv
#define glSecondaryColor3i SE_glSecondaryColor3i
#define glSecondaryColor3iv SE_glSecondaryColor3iv
#define glSecondaryColor3s SE_glSecondaryColor3s
#define glSecondaryColor3sv SE_glSecondaryColor3sv
#define glSecondaryColor3ub SE_glSecondaryColor3ub
#define glSecondaryColor3ubv SE_glSecondaryColor3ubv
#define glSecondaryColor3ui SE_glSecondaryColor3ui
#define glSecondaryColor3uiv SE_glSecondaryColor3uiv
#define glSecondaryColor3us SE_glSecondaryColor3us
#define glSecondaryColor3usv SE_glSecondaryColor3usv
#define glSecondaryColorPointer SE_glSecondaryColorPointer
#define glWindowPos2d SE_glWindowPos2d
#define glWindowPos2dv SE_glWindowPos2dv
#define glWindowPos2f SE_glWindowPos2f
#define glWindowPos2fv SE_glWindowPos2fv
#define glWindowPos2i SE_glWindowPos2i
#define glWindowPos2iv SE_glWindowPos2iv
#define glWindowPos2s SE_glWindowPos2s
#define glWindowPos2sv SE_glWindowPos2sv
#define glWindowPos3d SE_glWindowPos3d
#define glWindowPos3dv SE_glWindowPos3dv
#define glWindowPos3f SE_glWindowPos3f
#define glWindowPos3fv SE_glWindowPos3fv
#define glWindowPos3i SE_glWindowPos3i
#define glWindowPos3iv SE_glWindowPos3iv
#define glWindowPos3s SE_glWindowPos3s
#define glWindowPos3sv SE_glWindowPos3sv

SE_EXTERN void SE_glBlendFuncSeparate(GLenum eSrcFactorRGB,
    GLenum eDstFactorRGB, GLenum eSrcFactorA, GLenum eDstFactorA);
SE_EXTERN void SE_glFogCoordd(GLdouble dCoord);
SE_EXTERN void SE_glFogCoorddv(const GLdouble *adCoord);
SE_EXTERN void SE_glFogCoordf(GLfloat fCoord);
SE_EXTERN void SE_glFogCoordfv(const GLfloat *afCoord);
SE_EXTERN void SE_glFogCoordPointer(GLenum eType, GLsizei iStride,
    const GLvoid* pvPointer);
SE_EXTERN void SE_glMultiDrawArrays(GLenum eMode, GLint* aiFirst,
    GLsizei* aiCount, GLsizei iPrimitiveCount);
SE_EXTERN void SE_glMultiDrawElements(GLenum eMode, const GLsizei* aiCount,
    GLenum eType, const GLvoid** apvIndices, GLsizei iPrimitiveCount);
SE_EXTERN void SE_glPointParameterf(GLenum ePName, GLfloat fParam);
SE_EXTERN void SE_glPointParameterfv(GLenum ePName, const GLfloat* afParam);
SE_EXTERN void SE_glPointParameteri(GLenum ePName, int iParam);
SE_EXTERN void SE_glPointParameteriv(GLenum ePName, const int* aiParam);
SE_EXTERN void SE_glSecondaryColor3b(GLbyte cR, GLbyte cG, GLbyte cB);
SE_EXTERN void SE_glSecondaryColor3bv(const GLbyte* acRGB);
SE_EXTERN void SE_glSecondaryColor3d(GLdouble dR, GLdouble dG, GLdouble dB);
SE_EXTERN void SE_glSecondaryColor3dv(const GLdouble* adRGB);
SE_EXTERN void SE_glSecondaryColor3f(GLfloat fR, GLfloat fG, GLfloat fB);
SE_EXTERN void SE_glSecondaryColor3fv(const GLfloat* afRGB);
SE_EXTERN void SE_glSecondaryColor3i(GLint iR, GLint iG, GLint iB);
SE_EXTERN void SE_glSecondaryColor3iv(const GLint* aiRGB);
SE_EXTERN void SE_glSecondaryColor3s(GLshort sR, GLshort sG, GLshort sB);
SE_EXTERN void SE_glSecondaryColor3sv(const GLshort* asRGB);
SE_EXTERN void SE_glSecondaryColor3ub(GLubyte ucR, GLubyte ucG, GLubyte ucB);
SE_EXTERN void SE_glSecondaryColor3ubv(const GLubyte* aucRGB);
SE_EXTERN void SE_glSecondaryColor3ui(GLuint uiR, GLuint uiG, GLuint uiB);
SE_EXTERN void SE_glSecondaryColor3uiv(const GLuint* auiRGB);
SE_EXTERN void SE_glSecondaryColor3us(GLushort usR, GLushort usG,
    GLushort usB);
SE_EXTERN void SE_glSecondaryColor3usv(const GLushort* ausRGB);
SE_EXTERN void SE_glSecondaryColorPointer(GLint iSize, GLenum eType,
    GLsizei iStride, const GLvoid* pvPointer);
SE_EXTERN void SE_glWindowPos2d(GLdouble dX, GLdouble dY);
SE_EXTERN void SE_glWindowPos2dv(const GLdouble* adXY);
SE_EXTERN void SE_glWindowPos2f(GLfloat fX, GLfloat fY);
SE_EXTERN void SE_glWindowPos2fv(const GLfloat* afXY);
SE_EXTERN void SE_glWindowPos2i(GLint iX, GLint iY);
SE_EXTERN void SE_glWindowPos2iv(const GLint* aiXY);
SE_EXTERN void SE_glWindowPos2s(GLshort sX, GLshort sY);
SE_EXTERN void SE_glWindowPos2sv(const GLshort* asXY);
SE_EXTERN void SE_glWindowPos3d(GLdouble dX, GLdouble dY, GLdouble dZ);
SE_EXTERN void SE_glWindowPos3dv(const GLdouble* adXYZ);
SE_EXTERN void SE_glWindowPos3f(GLfloat fX, GLfloat fY, GLfloat fZ);
SE_EXTERN void SE_glWindowPos3fv(const GLfloat* afXYZ);
SE_EXTERN void SE_glWindowPos3i(GLint iX, GLint iY, GLint iZ);
SE_EXTERN void SE_glWindowPos3iv(const GLint* aiXYZ);
SE_EXTERN void SE_glWindowPos3s(GLshort sX, GLshort sY, GLshort sZ);
SE_EXTERN void SE_glWindowPos3sv(const GLshort* asXYZ);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* OpenGL 1.5 */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsOpenGL15;

#define GL_BUFFER_SIZE                                              0x8764
#define GL_BUFFER_USAGE                                             0x8765
#define GL_QUERY_COUNTER_BITS                                       0x8864
#define GL_CURRENT_QUERY                                            0x8865
#define GL_QUERY_RESULT                                             0x8866
#define GL_QUERY_RESULT_AVAILABLE                                   0x8867
#define GL_ARRAY_BUFFER                                             0x8892
#define GL_ELEMENT_ARRAY_BUFFER                                     0x8893
#define GL_ARRAY_BUFFER_BINDING                                     0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING                             0x8895
#define GL_VERTEX_ARRAY_BUFFER_BINDING                              0x8896
#define GL_NORMAL_ARRAY_BUFFER_BINDING                              0x8897
#define GL_COLOR_ARRAY_BUFFER_BINDING                               0x8898
#define GL_INDEX_ARRAY_BUFFER_BINDING                               0x8899
#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING                       0x889A
#define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING                           0x889B
#define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING                     0x889C
#define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING                      0x889D
#define GL_WEIGHT_ARRAY_BUFFER_BINDING                              0x889E
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING                       0x889F
#define GL_READ_ONLY                                                0x88B8
#define GL_WRITE_ONLY                                               0x88B9
#define GL_READ_WRITE                                               0x88BA
#define GL_BUFFER_ACCESS                                            0x88BB
#define GL_BUFFER_MAPPED                                            0x88BC
#define GL_BUFFER_MAP_POINTER                                       0x88BD
#define GL_STREAM_DRAW                                              0x88E0
#define GL_STREAM_READ                                              0x88E1
#define GL_STREAM_COPY                                              0x88E2
#define GL_STATIC_DRAW                                              0x88E4
#define GL_STATIC_READ                                              0x88E5
#define GL_STATIC_COPY                                              0x88E6
#define GL_DYNAMIC_DRAW                                             0x88E8
#define GL_DYNAMIC_READ                                             0x88E9
#define GL_DYNAMIC_COPY                                             0x88EA
#define GL_SAMPLES_PASSED                                           0x8914
#define GL_FOG_COORD_SRC                                            0x8450
#define GL_FOG_COORD                                                0x8451
#define GL_CURRENT_FOG_COORD                                        0x8453
#define GL_FOG_COORD_ARRAY_TYPE                                     0x8454
#define GL_FOG_COORD_ARRAY_STRIDE                                   0x8455
#define GL_FOG_COORD_ARRAY_POINTER                                  0x8456
#define GL_FOG_COORD_ARRAY                                          0x8457
#define GL_FOG_COORD_ARRAY_BUFFER_BINDING                           0x889D
#define GL_SRC0_RGB                                                 0x8580
#define GL_SRC1_RGB                                                 0x8581
#define GL_SRC2_RGB                                                 0x8582
#define GL_SRC0_ALPHA                                               0x8588
#define GL_SRC1_ALPHA                                               0x8589
#define GL_SRC2_ALPHA                                               0x858A

typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;

#define glGenQueries SE_glGenQueries
#define glDeleteQueries SE_glDeleteQueries
#define glIsQuery SE_glIsQuery
#define glBeginQuery SE_glBeginQuery
#define glEndQuery SE_glEndQuery
#define glGetQueryiv SE_glGetQueryiv
#define glGetQueryObjectiv SE_glGetQueryObjectiv
#define glGetQueryObjectuiv SE_glGetQueryObjectuiv
#define glBindBuffer SE_glBindBuffer
#define glDeleteBuffers SE_glDeleteBuffers
#define glGenBuffers SE_glGenBuffers
#define glIsBuffer SE_glIsBuffer
#define glBufferData SE_glBufferData
#define glBufferSubData SE_glBufferSubData
#define glGetBufferSubData SE_glGetBufferSubData
#define glMapBuffer SE_glMapBuffer
#define glUnmapBuffer SE_glUnmapBuffer
#define glGetBufferParameteriv SE_glGetBufferParameteriv
#define glGetBufferPointerv SE_glGetBufferPointerv

SE_EXTERN void SE_glGenQueries(GLsizei iNumQueries, GLuint* auiID);
SE_EXTERN void SE_glDeleteQueries(GLsizei iNumQueries, const GLuint* auiID);
GLboolean SE_glIsQuery(GLuint uiID);
SE_EXTERN void SE_glBeginQuery(GLenum eTarget, GLuint uiID);
SE_EXTERN void SE_glEndQuery(GLenum eTarget);
SE_EXTERN void SE_glGetQueryiv(GLenum eTarget, GLenum ePName, GLint* aiParam);
SE_EXTERN void SE_glGetQueryObjectiv(GLuint uiID, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glGetQueryObjectuiv(GLuint uiID, GLenum ePName,
    GLuint* auiParam);
SE_EXTERN void SE_glBindBuffer(GLenum eTarget, GLuint uiBuffer);
SE_EXTERN void SE_glDeleteBuffers(GLsizei iNumBuffers,
    const GLuint* auiBuffer);
SE_EXTERN void SE_glGenBuffers(GLsizei iNumBuffers, GLuint* auiBuffer);
SE_EXTERN GLboolean SE_glIsBuffer(GLuint uiBuffer);
SE_EXTERN void SE_glBufferData(GLenum eTarget, GLsizeiptr piSize,
    const GLvoid* pvData, GLenum eUsage);
SE_EXTERN void SE_glBufferSubData(GLenum eTarget, GLintptr piOffset,
    GLsizeiptr piSize, const GLvoid* pvData);
SE_EXTERN void SE_glGetBufferSubData(GLenum eTarget, GLintptr piOffset,
    GLsizeiptr piSize, GLvoid* pvData);
SE_EXTERN GLvoid* SE_glMapBuffer(GLenum eTarget, GLenum eAccess);
SE_EXTERN GLboolean SE_glUnmapBuffer(GLenum eTarget);
SE_EXTERN void SE_glGetBufferParameteriv(GLenum eTarget, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glGetBufferPointerv(GLenum eTarget, GLenum ePName,
    GLvoid** apvParam);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* OpenGL 2.0 */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsOpenGL20;

#define GL_BLEND_EQUATION_RGB                                       0x8009
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED                              0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE                                 0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE                               0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE                                 0x8625
#define GL_CURRENT_VERTEX_ATTRIB                                    0x8626
#define GL_VERTEX_PROGRAM_POINT_SIZE                                0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE                                  0x8643
#define GL_VERTEX_ATTRIB_ARRAY_POINTER                              0x8645
#define GL_STENCIL_BACK_FUNC                                        0x8800
#define GL_STENCIL_BACK_FAIL                                        0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL                             0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS                             0x8803
#define GL_MAX_DRAW_BUFFERS                                         0x8824
#define GL_DRAW_BUFFER0                                             0x8825
#define GL_DRAW_BUFFER1                                             0x8826
#define GL_DRAW_BUFFER2                                             0x8827
#define GL_DRAW_BUFFER3                                             0x8828
#define GL_DRAW_BUFFER4                                             0x8829
#define GL_DRAW_BUFFER5                                             0x882A
#define GL_DRAW_BUFFER6                                             0x882B
#define GL_DRAW_BUFFER7                                             0x882C
#define GL_DRAW_BUFFER8                                             0x882D
#define GL_DRAW_BUFFER9                                             0x882E
#define GL_DRAW_BUFFER10                                            0x882F
#define GL_DRAW_BUFFER11                                            0x8830
#define GL_DRAW_BUFFER12                                            0x8831
#define GL_DRAW_BUFFER13                                            0x8832
#define GL_DRAW_BUFFER14                                            0x8833
#define GL_DRAW_BUFFER15                                            0x8834
#define GL_BLEND_EQUATION_ALPHA                                     0x883D
#define GL_POINT_SPRITE                                             0x8861
#define GL_COORD_REPLACE                                            0x8862
#define GL_MAX_VERTEX_ATTRIBS                                       0x8869
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED                           0x886A
#define GL_MAX_TEXTURE_COORDS                                       0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS                                  0x8872
#define GL_FRAGMENT_SHADER                                          0x8B30
#define GL_VERTEX_SHADER                                            0x8B31
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS                          0x8B49
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS                            0x8B4A
#define GL_MAX_VARYING_FLOATS                                       0x8B4B
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS                           0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS                         0x8B4D
#define GL_SHADER_TYPE                                              0x8B4F
#define GL_FLOAT_VEC2                                               0x8B50
#define GL_FLOAT_VEC3                                               0x8B51
#define GL_FLOAT_VEC4                                               0x8B52
#define GL_INT_VEC2                                                 0x8B53
#define GL_INT_VEC3                                                 0x8B54
#define GL_INT_VEC4                                                 0x8B55
#define GL_BOOL                                                     0x8B56
#define GL_BOOL_VEC2                                                0x8B57
#define GL_BOOL_VEC3                                                0x8B58
#define GL_BOOL_VEC4                                                0x8B59
#define GL_FLOAT_MAT2                                               0x8B5A
#define GL_FLOAT_MAT3                                               0x8B5B
#define GL_FLOAT_MAT4                                               0x8B5C
#define GL_SAMPLER_1D                                               0x8B5D
#define GL_SAMPLER_2D                                               0x8B5E
#define GL_SAMPLER_3D                                               0x8B5F
#define GL_SAMPLER_CUBE                                             0x8B60
#define GL_SAMPLER_1D_SHADOW                                        0x8B61
#define GL_SAMPLER_2D_SHADOW                                        0x8B62
#define GL_DELETE_STATUS                                            0x8B80
#define GL_COMPILE_STATUS                                           0x8B81
#define GL_LINK_STATUS                                              0x8B82
#define GL_VALIDATE_STATUS                                          0x8B83
#define GL_INFO_LOG_LENGTH                                          0x8B84
#define GL_ATTACHED_SHADERS                                         0x8B85
#define GL_ACTIVE_UNIFORMS                                          0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH                                0x8B87
#define GL_SHADER_SOURCE_LENGTH                                     0x8B88
#define GL_ACTIVE_ATTRIBUTES                                        0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH                              0x8B8A
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT                          0x8B8B
#define GL_SHADING_LANGUAGE_VERSION                                 0x8B8C
#define GL_CURRENT_PROGRAM                                          0x8B8D
#define GL_POINT_SPRITE_COORD_ORIGIN                                0x8CA0
#define GL_LOWER_LEFT                                               0x8CA1
#define GL_UPPER_LEFT                                               0x8CA2
#define GL_STENCIL_BACK_REF                                         0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK                                  0x8CA4
#define GL_STENCIL_BACK_WRITEMASK                                   0x8CA5

typedef char GLchar;

#define glBlendEquationSeparate SE_glBlendEquationSeparate
#define glDrawBuffers SE_glDrawBuffers
#define glStencilOpSeparate SE_glStencilOpSeparate
#define glStencilFuncSeparate SE_glStencilFuncSeparate
#define glStencilMaskSeparate SE_glStencilMaskSeparate
#define glAttachShader SE_glAttachShader
#define glBindAttribLocation SE_glBindAttribLocation
#define glCompileShader SE_glCompileShader
#define glCreateProgram SE_glCreateProgram
#define glCreateShader SE_glCreateShader
#define glDeleteProgram SE_glDeleteProgram
#define glDeleteShader SE_glDeleteShader
#define glDetachShader SE_glDetachShader
#define glDisableVertexAttribArray SE_glDisableVertexAttribArray
#define glEnableVertexAttribArray SE_glEnableVertexAttribArray
#define glGetActiveAttrib SE_glGetActiveAttrib
#define glGetActiveUniform SE_glGetActiveUniform
#define glGetAttachedShaders SE_glGetAttachedShaders
#define glGetAttribLocation SE_glGetAttribLocation
#define glGetProgramiv SE_glGetProgramiv
#define glGetProgramInfoLog SE_glGetProgramInfoLog
#define glGetShaderiv SE_glGetShaderiv
#define glGetShaderInfoLog SE_glGetShaderInfoLog
#define glGetShaderSource SE_glGetShaderSource
#define glGetUniformLocation SE_glGetUniformLocation
#define glGetUniformfv SE_glGetUniformfv
#define glGetUniformiv SE_glGetUniformiv
#define glGetVertexAttribdv SE_glGetVertexAttribdv
#define glGetVertexAttribfv SE_glGetVertexAttribfv
#define glGetVertexAttribiv SE_glGetVertexAttribiv
#define glGetVertexAttribPointerv SE_glGetVertexAttribPointerv
#define glIsProgram SE_glIsProgram
#define glIsShader SE_glIsShader
#define glLinkProgram SE_glLinkProgram
#define glShaderSource SE_glShaderSource
#define glUseProgram SE_glUseProgram
#define glUniform1f SE_glUniform1f
#define glUniform2f SE_glUniform2f
#define glUniform3f SE_glUniform3f
#define glUniform4f SE_glUniform4f
#define glUniform1i SE_glUniform1i
#define glUniform2i SE_glUniform2i
#define glUniform3i SE_glUniform3i
#define glUniform4i SE_glUniform4i
#define glUniform1fv SE_glUniform1fv
#define glUniform2fv SE_glUniform2fv
#define glUniform3fv SE_glUniform3fv
#define glUniform4fv SE_glUniform4fv
#define glUniform1iv SE_glUniform1iv
#define glUniform2iv SE_glUniform2iv
#define glUniform3iv SE_glUniform3iv
#define glUniform4iv SE_glUniform4iv
#define glUniformMatrix2fv SE_glUniformMatrix2fv
#define glUniformMatrix3fv SE_glUniformMatrix3fv
#define glUniformMatrix4fv SE_glUniformMatrix4fv
#define glValidateProgram SE_glValidateProgram
#define glVertexAttrib1d SE_glVertexAttrib1d
#define glVertexAttrib1dv SE_glVertexAttrib1dv
#define glVertexAttrib1f SE_glVertexAttrib1f
#define glVertexAttrib1fv SE_glVertexAttrib1fv
#define glVertexAttrib1s SE_glVertexAttrib1s
#define glVertexAttrib1sv SE_glVertexAttrib1sv
#define glVertexAttrib2d SE_glVertexAttrib2d
#define glVertexAttrib2dv SE_glVertexAttrib2dv
#define glVertexAttrib2f SE_glVertexAttrib2f
#define glVertexAttrib2fv SE_glVertexAttrib2fv
#define glVertexAttrib2s SE_glVertexAttrib2s
#define glVertexAttrib2sv SE_glVertexAttrib2sv
#define glVertexAttrib3d SE_glVertexAttrib3d
#define glVertexAttrib3dv SE_glVertexAttrib3dv
#define glVertexAttrib3f SE_glVertexAttrib3f
#define glVertexAttrib3fv SE_glVertexAttrib3fv
#define glVertexAttrib3s SE_glVertexAttrib3s
#define glVertexAttrib3sv SE_glVertexAttrib3sv
#define glVertexAttrib4Nbv SE_glVertexAttrib4Nbv
#define glVertexAttrib4Niv SE_glVertexAttrib4Niv
#define glVertexAttrib4Nsv SE_glVertexAttrib4Nsv
#define glVertexAttrib4Nub SE_glVertexAttrib4Nub
#define glVertexAttrib4Nubv SE_glVertexAttrib4Nubv
#define glVertexAttrib4Nuiv SE_glVertexAttrib4Nuiv
#define glVertexAttrib4Nusv SE_glVertexAttrib4Nusv
#define glVertexAttrib4bv SE_glVertexAttrib4bv
#define glVertexAttrib4d SE_glVertexAttrib4d
#define glVertexAttrib4dv SE_glVertexAttrib4dv
#define glVertexAttrib4f SE_glVertexAttrib4f
#define glVertexAttrib4fv SE_glVertexAttrib4fv
#define glVertexAttrib4iv SE_glVertexAttrib4iv
#define glVertexAttrib4s SE_glVertexAttrib4s
#define glVertexAttrib4sv SE_glVertexAttrib4sv
#define glVertexAttrib4ubv SE_glVertexAttrib4ubv
#define glVertexAttrib4uiv SE_glVertexAttrib4uiv
#define glVertexAttrib4usv SE_glVertexAttrib4usv
#define glVertexAttribPointer SE_glVertexAttribPointer

SE_EXTERN void SE_glBlendEquationSeparate(GLenum eModeRGB, GLenum eModeAlpha);
SE_EXTERN void SE_glDrawBuffers(GLsizei iNumBuffers, const GLenum* aeBuffer);
SE_EXTERN void SE_glStencilOpSeparate(GLenum eFace, GLenum eSFail,
    GLenum eDPFail, GLenum eDPPass);
SE_EXTERN void SE_glStencilFuncSeparate(GLenum eFrontFunc, GLenum eBackFunc,
    GLint iReference, GLuint uiMask);
SE_EXTERN void SE_glStencilMaskSeparate(GLenum eFace, GLuint uiMask);
SE_EXTERN void SE_glAttachShader(GLuint uiProgram, GLuint uiShader);
SE_EXTERN void SE_glBindAttribLocation(GLuint uiProgram, GLuint uiIndex,
    const GLchar* acName);
SE_EXTERN void SE_glCompileShader(GLuint uiShader);
SE_EXTERN GLuint SE_glCreateProgram(void);
SE_EXTERN GLuint SE_glCreateShader(GLenum eType);
SE_EXTERN void SE_glDeleteProgram(GLuint uiProgram);
SE_EXTERN void SE_glDeleteShader(GLuint uiShader);
SE_EXTERN void SE_glDetachShader(GLuint uiProgram, GLuint uiShader);
SE_EXTERN void SE_glDisableVertexAttribArray(GLuint uiIndex);
SE_EXTERN void SE_glEnableVertexAttribArray(GLuint uiIndex);
SE_EXTERN void SE_glGetActiveAttrib(GLuint uiProgram, GLuint uiIndex,
    GLsizei iBufSize, GLsizei* piLength, GLint* piSize, GLenum* peType,
    GLchar* acName);
SE_EXTERN void SE_glGetActiveUniform(GLuint uiProgram, GLuint uiIndex,
    GLsizei iBufSize, GLsizei* piLength, GLint* piSize, GLenum* peType,
    GLchar* acName);
SE_EXTERN void SE_glGetAttachedShaders(GLuint uiProgram, GLsizei iMaxCount,
    GLsizei* aiCount, GLuint* aiObj);
SE_EXTERN GLint SE_glGetAttribLocation(GLuint uiProgram,
    const GLchar* acName);
SE_EXTERN void SE_glGetProgramiv(GLuint uiProgram, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glGetProgramInfoLog(GLuint uiProgram, GLsizei iBufSize,
    GLsizei* piLength, GLchar* acInfoLog);
SE_EXTERN void SE_glGetShaderiv(GLuint uiShader, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glGetShaderInfoLog(GLuint uiShader, GLsizei iBufSize,
    GLsizei* piLength, GLchar* acInfoLog);
SE_EXTERN void SE_glGetShaderSource(GLuint uiShader, GLsizei iBufSize,
    GLsizei* piLength, GLchar* acSource);
SE_EXTERN GLint SE_glGetUniformLocation(GLuint uiProgram,
    const GLchar* acName);
SE_EXTERN void SE_glGetUniformfv(GLuint uiProgram, GLint uiLocation,
    GLfloat* afParam);
SE_EXTERN void SE_glGetUniformiv(GLuint uiProgram, GLint uiLocation,
    GLint* aiParam);
SE_EXTERN void SE_glGetVertexAttribdv(GLuint uiIndex, GLenum ePName,
    GLdouble* adParam);
SE_EXTERN void SE_glGetVertexAttribfv(GLuint uiIndex, GLenum ePName,
    GLfloat* afParam);
SE_EXTERN void SE_glGetVertexAttribiv(GLuint uiIndex, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glGetVertexAttribPointerv(GLuint uiIndex, GLenum ePName,
    GLvoid** apvParam);
SE_EXTERN GLboolean SE_glIsProgram(GLuint uiProgram);
SE_EXTERN GLboolean SE_glIsShader(GLuint uiShader);
SE_EXTERN void SE_glLinkProgram(GLuint uiProgram);
SE_EXTERN void SE_glShaderSource(GLuint uiShader, GLsizei iCount,
    const GLchar** aacString, const GLint* piLength);
SE_EXTERN void SE_glUseProgram(GLuint uiProgram);
SE_EXTERN void SE_glUniform1f(GLint uiLocation, GLfloat fV0);
SE_EXTERN void SE_glUniform2f(GLint uiLocation, GLfloat fV0, GLfloat fV1);
SE_EXTERN void SE_glUniform3f(GLint uiLocation, GLfloat fV0, GLfloat fV1,
    GLfloat fV2);
SE_EXTERN void SE_glUniform4f(GLint uiLocation, GLfloat fV0, GLfloat fV1,
    GLfloat fV2, GLfloat fV3);
SE_EXTERN void SE_glUniform1i(GLint uiLocation, GLint iV0);
SE_EXTERN void SE_glUniform2i(GLint uiLocation, GLint iV0, GLint iV1);
SE_EXTERN void SE_glUniform3i(GLint uiLocation, GLint iV0, GLint iV1,
    GLint iV2);
SE_EXTERN void SE_glUniform4i(GLint uiLocation, GLint iV0, GLint iV1,
    GLint iV2, GLint iV3);
SE_EXTERN void SE_glUniform1fv(GLint uiLocation, GLsizei iCount,
    const GLfloat* afValue);
SE_EXTERN void SE_glUniform2fv(GLint uiLocation, GLsizei iCount,
    const GLfloat* afValue);
SE_EXTERN void SE_glUniform3fv(GLint uiLocation, GLsizei iCount,
    const GLfloat* afValue);
SE_EXTERN void SE_glUniform4fv(GLint uiLocation, GLsizei iCount,
    const GLfloat* afValue);
SE_EXTERN void SE_glUniform1iv(GLint uiLocation, GLsizei iCount,
    const GLint* aiValue);
SE_EXTERN void SE_glUniform2iv(GLint uiLocation, GLsizei iCount,
    const GLint* aiValue);
SE_EXTERN void SE_glUniform3iv(GLint uiLocation, GLsizei iCount,
    const GLint* aiValue);
SE_EXTERN void SE_glUniform4iv(GLint uiLocation, GLsizei iCount,
    const GLint* aiValue);
SE_EXTERN void SE_glUniformMatrix2fv(GLint uiLocation, GLsizei iCount,
    GLboolean ucTranspose, const GLfloat* afValue);
SE_EXTERN void SE_glUniformMatrix3fv(GLint uiLocation, GLsizei iCount,
    GLboolean ucTranspose, const GLfloat* afValue);
SE_EXTERN void SE_glUniformMatrix4fv(GLint uiLocation, GLsizei iCount,
    GLboolean ucTranspose, const GLfloat* afValue);
SE_EXTERN void SE_glValidateProgram(GLuint uiProgram);
SE_EXTERN void SE_glVertexAttrib1d(GLuint uiIndex, GLdouble dX);
SE_EXTERN void SE_glVertexAttrib1dv(GLuint uiIndex, const GLdouble* pdX);
SE_EXTERN void SE_glVertexAttrib1f(GLuint uiIndex, GLfloat fX);
SE_EXTERN void SE_glVertexAttrib1fv(GLuint uiIndex, const GLfloat* pfX);
SE_EXTERN void SE_glVertexAttrib1s(GLuint uiIndex, GLshort sX);
SE_EXTERN void SE_glVertexAttrib1sv(GLuint uiIndex, const GLshort* psX);
SE_EXTERN void SE_glVertexAttrib2d(GLuint uiIndex, GLdouble dX, GLdouble dY);
SE_EXTERN void SE_glVertexAttrib2dv(GLuint uiIndex, const GLdouble* adXY);
SE_EXTERN void SE_glVertexAttrib2f(GLuint uiIndex, GLfloat fX, GLfloat fY);
SE_EXTERN void SE_glVertexAttrib2fv(GLuint uiIndex, const GLfloat* afXY);
SE_EXTERN void SE_glVertexAttrib2s(GLuint uiIndex, GLshort sX, GLshort sY);
SE_EXTERN void SE_glVertexAttrib2sv(GLuint uiIndex, const GLshort* asXY);
SE_EXTERN void SE_glVertexAttrib3d(GLuint uiIndex, GLdouble dX, GLdouble dY,
    GLdouble dZ);
SE_EXTERN void SE_glVertexAttrib3dv(GLuint uiIndex, const GLdouble* adXYZ);
SE_EXTERN void SE_glVertexAttrib3f(GLuint uiIndex, GLfloat fX, GLfloat fY,
    GLfloat fZ);
SE_EXTERN void SE_glVertexAttrib3fv(GLuint uiIndex, const GLfloat* afXYZ);
SE_EXTERN void SE_glVertexAttrib3s(GLuint uiIndex, GLshort sX, GLshort sY,
    GLshort sZ);
SE_EXTERN void SE_glVertexAttrib3sv(GLuint uiIndex, const GLshort* asXYZ);
SE_EXTERN void SE_glVertexAttrib4Nbv(GLuint uiIndex, const GLbyte* acXYZW);
SE_EXTERN void SE_glVertexAttrib4Niv(GLuint uiIndex, const GLint* aiXYZW);
SE_EXTERN void SE_glVertexAttrib4Nsv(GLuint uiIndex, const GLshort* asXYZW);
SE_EXTERN void SE_glVertexAttrib4Nub(GLuint uiIndex, GLubyte ucX, GLubyte ucY,
    GLubyte ucZ, GLubyte ucW);
SE_EXTERN void SE_glVertexAttrib4Nubv(GLuint uiIndex, const GLubyte* aucXYZW);
SE_EXTERN void SE_glVertexAttrib4Nuiv(GLuint uiIndex, const GLuint* auiXYZW);
SE_EXTERN void SE_glVertexAttrib4Nusv(GLuint uiIndex,
    const GLushort* ausXYZW);
SE_EXTERN void SE_glVertexAttrib4bv(GLuint uiIndex, const GLbyte* acXYZW);
SE_EXTERN void SE_glVertexAttrib4d(GLuint uiIndex, GLdouble dX, GLdouble dY,
    GLdouble dZ, GLdouble dW);
SE_EXTERN void SE_glVertexAttrib4dv(GLuint uiIndex, const GLdouble* adXYZW);
SE_EXTERN void SE_glVertexAttrib4f(GLuint uiIndex, GLfloat fX, GLfloat fY,
    GLfloat fZ, GLfloat fW);
SE_EXTERN void SE_glVertexAttrib4fv(GLuint uiIndex, const GLfloat* afXYZW);
SE_EXTERN void SE_glVertexAttrib4iv(GLuint uiIndex, const GLint* aiXYZW);
SE_EXTERN void SE_glVertexAttrib4s(GLuint uiIndex, GLshort sX, GLshort sY,
    GLshort sZ, GLshort sW);
SE_EXTERN void SE_glVertexAttrib4sv(GLuint uiIndex, const GLshort* asXYZW);
SE_EXTERN void SE_glVertexAttrib4ubv(GLuint uiIndex, const GLubyte* aucXYZW);
SE_EXTERN void SE_glVertexAttrib4uiv(GLuint uiIndex, const GLuint* auiXYZW);
SE_EXTERN void SE_glVertexAttrib4usv(GLuint uiIndex, const GLushort* ausXYZW);
SE_EXTERN void SE_glVertexAttribPointer(GLuint uiIndex, GLint iSize,
    GLenum eType, GLboolean ucNormalized, GLsizei iStride,
    const GLvoid* pvPointer);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/***** ARB Extensions *****/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 01) GL_ARB_multitexture */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbMultitexture;

#define GL_TEXTURE0_ARB                                             0x84C0
#define GL_TEXTURE1_ARB                                             0x84C1
#define GL_TEXTURE2_ARB                                             0x84C2
#define GL_TEXTURE3_ARB                                             0x84C3
#define GL_TEXTURE4_ARB                                             0x84C4
#define GL_TEXTURE5_ARB                                             0x84C5
#define GL_TEXTURE6_ARB                                             0x84C6
#define GL_TEXTURE7_ARB                                             0x84C7
#define GL_TEXTURE8_ARB                                             0x84C8
#define GL_TEXTURE9_ARB                                             0x84C9
#define GL_TEXTURE10_ARB                                            0x84CA
#define GL_TEXTURE11_ARB                                            0x84CB
#define GL_TEXTURE12_ARB                                            0x84CC
#define GL_TEXTURE13_ARB                                            0x84CD
#define GL_TEXTURE14_ARB                                            0x84CE
#define GL_TEXTURE15_ARB                                            0x84CF
#define GL_TEXTURE16_ARB                                            0x84D0
#define GL_TEXTURE17_ARB                                            0x84D1
#define GL_TEXTURE18_ARB                                            0x84D2
#define GL_TEXTURE19_ARB                                            0x84D3
#define GL_TEXTURE20_ARB                                            0x84D4
#define GL_TEXTURE21_ARB                                            0x84D5
#define GL_TEXTURE22_ARB                                            0x84D6
#define GL_TEXTURE23_ARB                                            0x84D7
#define GL_TEXTURE24_ARB                                            0x84D8
#define GL_TEXTURE25_ARB                                            0x84D9
#define GL_TEXTURE26_ARB                                            0x84DA
#define GL_TEXTURE27_ARB                                            0x84DB
#define GL_TEXTURE28_ARB                                            0x84DC
#define GL_TEXTURE29_ARB                                            0x84DD
#define GL_TEXTURE30_ARB                                            0x84DE
#define GL_TEXTURE31_ARB                                            0x84DF
#define GL_ACTIVE_TEXTURE_ARB                                       0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE_ARB                                0x84E1
#define GL_MAX_TEXTURE_UNITS_ARB                                    0x84E2

#define glActiveTextureARB SE_glActiveTextureARB
#define glClientActiveTextureARB SE_glClientActiveTextureARB
#define glMultiTexCoord1dARB SE_glMultiTexCoord1dARB
#define glMultiTexCoord1dvARB SE_glMultiTexCoord1dvARB
#define glMultiTexCoord1fARB SE_glMultiTexCoord1fARB
#define glMultiTexCoord1fvARB SE_glMultiTexCoord1fvARB
#define glMultiTexCoord1iARB SE_glMultiTexCoord1iARB
#define glMultiTexCoord1ivARB SE_glMultiTexCoord1ivARB
#define glMultiTexCoord1sARB SE_glMultiTexCoord1sARB
#define glMultiTexCoord1svARB SE_glMultiTexCoord1svARB
#define glMultiTexCoord2dARB SE_glMultiTexCoord2dARB
#define glMultiTexCoord2dvARB SE_glMultiTexCoord2dvARB
#define glMultiTexCoord2fARB SE_glMultiTexCoord2fARB
#define glMultiTexCoord2fvARB SE_glMultiTexCoord2fvARB
#define glMultiTexCoord2iARB SE_glMultiTexCoord2iARB
#define glMultiTexCoord2ivARB SE_glMultiTexCoord2ivARB
#define glMultiTexCoord2sARB SE_glMultiTexCoord2sARB
#define glMultiTexCoord2svARB SE_glMultiTexCoord2svARB
#define glMultiTexCoord3dARB SE_glMultiTexCoord3dARB
#define glMultiTexCoord3dvARB SE_glMultiTexCoord3dvARB
#define glMultiTexCoord3fARB SE_glMultiTexCoord3fARB
#define glMultiTexCoord3fvARB SE_glMultiTexCoord3fvARB
#define glMultiTexCoord3iARB SE_glMultiTexCoord3iARB
#define glMultiTexCoord3ivARB SE_glMultiTexCoord3ivARB
#define glMultiTexCoord3sARB SE_glMultiTexCoord3sARB
#define glMultiTexCoord3svARB SE_glMultiTexCoord3svARB
#define glMultiTexCoord4dARB SE_glMultiTexCoord4dARB
#define glMultiTexCoord4dvARB SE_glMultiTexCoord4dvARB
#define glMultiTexCoord4fARB SE_glMultiTexCoord4fARB
#define glMultiTexCoord4fvARB SE_glMultiTexCoord4fvARB
#define glMultiTexCoord4iARB SE_glMultiTexCoord4iARB
#define glMultiTexCoord4ivARB SE_glMultiTexCoord4ivARB
#define glMultiTexCoord4sARB SE_glMultiTexCoord4sARB
#define glMultiTexCoord4svARB SE_glMultiTexCoord4svARB

SE_EXTERN void SE_glActiveTextureARB(GLenum eTexture);
SE_EXTERN void SE_glClientActiveTextureARB(GLenum eTexture);
SE_EXTERN void SE_glMultiTexCoord1dARB(GLenum eTarget, GLdouble dS);
SE_EXTERN void SE_glMultiTexCoord1dvARB(GLenum eTarget, const GLdouble* pdS);
SE_EXTERN void SE_glMultiTexCoord1fARB(GLenum eTarget, GLfloat fS);
SE_EXTERN void SE_glMultiTexCoord1fvARB(GLenum eTarget, const GLfloat* pfS);
SE_EXTERN void SE_glMultiTexCoord1iARB(GLenum eTarget, GLint iS);
SE_EXTERN void SE_glMultiTexCoord1ivARB(GLenum eTarget, const GLint* piS);
SE_EXTERN void SE_glMultiTexCoord1sARB(GLenum eTarget, GLshort sS);
SE_EXTERN void SE_glMultiTexCoord1svARB(GLenum eTarget, const GLshort* psS);
SE_EXTERN void SE_glMultiTexCoord2dARB(GLenum eTarget, GLdouble dS,
    GLdouble dT);
SE_EXTERN void SE_glMultiTexCoord2dvARB(GLenum eTarget, const GLdouble* asDT);
SE_EXTERN void SE_glMultiTexCoord2fARB(GLenum eTarget, GLfloat fS,
    GLfloat fT);
SE_EXTERN void SE_glMultiTexCoord2fvARB(GLenum eTarget, const GLfloat* afST);
SE_EXTERN void SE_glMultiTexCoord2iARB(GLenum eTarget, GLint iS, GLint iT);
SE_EXTERN void SE_glMultiTexCoord2ivARB(GLenum eTarget, const GLint* aiST);
SE_EXTERN void SE_glMultiTexCoord2sARB(GLenum eTarget, GLshort sS,
    GLshort sT);
SE_EXTERN void SE_glMultiTexCoord2svARB(GLenum eTarget, const GLshort* asST);
SE_EXTERN void SE_glMultiTexCoord3dARB(GLenum eTarget, GLdouble dS,
    GLdouble dT, GLdouble dR);
SE_EXTERN void SE_glMultiTexCoord3dvARB(GLenum eTarget,
    const GLdouble* adSTR);
SE_EXTERN void SE_glMultiTexCoord3fARB(GLenum eTarget, GLfloat fS, GLfloat fT,
    GLfloat fR);
SE_EXTERN void SE_glMultiTexCoord3fvARB(GLenum eTarget, const GLfloat* afSTR);
SE_EXTERN void SE_glMultiTexCoord3iARB(GLenum eTarget, GLint iS, GLint iT,
    GLint iR);
SE_EXTERN void SE_glMultiTexCoord3ivARB(GLenum eTarget, const GLint* aiSTR);
SE_EXTERN void SE_glMultiTexCoord3sARB(GLenum eTarget, GLshort sS, GLshort sT,
    GLshort sR);
SE_EXTERN void SE_glMultiTexCoord3svARB(GLenum eTarget, const GLshort* asSTR);
SE_EXTERN void SE_glMultiTexCoord4dARB(GLenum eTarget, GLdouble dS,
    GLdouble dT, GLdouble dR, GLdouble dQ);
SE_EXTERN void SE_glMultiTexCoord4dvARB(GLenum eTarget,
    const GLdouble* asSTRQ);
SE_EXTERN void SE_glMultiTexCoord4fARB(GLenum eTarget, GLfloat fS, GLfloat fT,
    GLfloat fR,GLfloat fQ);
SE_EXTERN void SE_glMultiTexCoord4fvARB(GLenum eTarget,
    const GLfloat* afSTRQ);
SE_EXTERN void SE_glMultiTexCoord4iARB(GLenum eTarget, GLint iS, GLint iT,
    GLint iR, GLint iQ);
SE_EXTERN void SE_glMultiTexCoord4ivARB(GLenum eTarget, const GLint* aiSTRQ);
SE_EXTERN void SE_glMultiTexCoord4sARB(GLenum eTarget, GLshort sS, GLshort sT,
    GLshort sR, GLshort sQ);
SE_EXTERN void SE_glMultiTexCoord4svARB(GLenum eTarget,
    const GLshort* asSTRQ);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 03) GL_ARB_transpose_matrix */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbTransposeMatrix;

#define GL_TRANSPOSE_MODELVIEW_MATRIX_ARB                           0x84E3
#define GL_TRANSPOSE_PROJECTION_MATRIX_ARB                          0x84E4
#define GL_TRANSPOSE_TEXTURE_MATRIX_ARB                             0x84E5
#define GL_TRANSPOSE_COLOR_MATRIX_ARB                               0x84E6

#define glLoadTransposeMatrixdARB SE_glLoadTransposeMatrixdARB
#define glLoadTransposeMatrixfARB SE_glLoadTransposeMatrixfARB
#define glMultTransposeMatrixdARB SE_glMultTransposeMatrixdARB
#define glMultTransposeMatrixfARB SE_glMultTransposeMatrixfARB

SE_EXTERN void SE_glLoadTransposeMatrixdARB(const GLdouble* adMatrix);
SE_EXTERN void SE_glLoadTransposeMatrixfARB(const GLfloat* afMatrix);
SE_EXTERN void SE_glMultTransposeMatrixdARB(const GLdouble* adMatrix);
SE_EXTERN void SE_glMultTransposeMatrixfARB(const GLfloat* afMatrix);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 05) GL_ARB_multisample */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbMultisample;

#define GL_MULTISAMPLE_ARB                                          0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE_ARB                             0x809E
#define GL_SAMPLE_ALPHA_TO_ONE_ARB                                  0x809F
#define GL_SAMPLE_COVERAGE_ARB                                      0x80A0
#define GL_SAMPLE_BUFFERS_ARB                                       0x80A8
#define GL_SAMPLES_ARB                                              0x80A9
#define GL_SAMPLE_COVERAGE_VALUE_ARB                                0x80AA
#define GL_SAMPLE_COVERAGE_INVERT_ARB                               0x80AB
#define GL_MULTISAMPLE_BIT_ARB                                      0x20000000

#define glSampleCoverageARB SE_glSampleCoverageARB

SE_EXTERN void SE_glSampleCoverageARB(GLclampf fValue, GLboolean ucInvert);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 06) GL_ARB_texture_env_add */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbTextureEnvAdd;
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 07) GL_ARB_texture_cube_map */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbTextureCubeMap;

#define GL_NORMAL_MAP_ARB                                           0x8511
#define GL_REFLECTION_MAP_ARB                                       0x8512
#define GL_TEXTURE_CUBE_MAP_ARB                                     0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_ARB                             0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB                          0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB                          0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB                          0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB                          0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB                          0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB                          0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARB                               0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB                            0x851C
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 12) GL_ARB_texture_compression */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbTextureCompression;

#define GL_COMPRESSED_ALPHA_ARB                                     0x84E9
#define GL_COMPRESSED_LUMINANCE_ARB                                 0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA_ARB                           0x84EB
#define GL_COMPRESSED_INTENSITY_ARB                                 0x84EC
#define GL_COMPRESSED_RGB_ARB                                       0x84ED
#define GL_COMPRESSED_RGBA_ARB                                      0x84EE
#define GL_TEXTURE_COMPRESSION_HINT_ARB                             0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB                        0x86A0
#define GL_TEXTURE_COMPRESSED_ARB                                   0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB                       0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS_ARB                           0x86A3

#define glCompressedTexImage1DARB SE_glCompressedTexImage1DARB
#define glCompressedTexImage2DARB SE_glCompressedTexImage2DARB
#define glCompressedTexImage3DARB SE_glCompressedTexImage3DARB
#define glCompressedTexSubImage1DARB SE_glCompressedTexSubImage1DARB
#define glCompressedTexSubImage2DARB SE_glCompressedTexSubImage2DARB
#define glCompressedTexSubImage3DARB SE_glCompressedTexSubImage3DARB
#define glGetCompressedTexImageARB SE_glGetCompressedTexImageARB

SE_EXTERN void SE_glCompressedTexImage1DARB(GLenum eTarget, GLint iLevel,
    GLenum eInternalFormat, GLsizei iWidth, GLint iBorder,
    GLsizei iImageSize, const GLvoid* pvData);
SE_EXTERN void SE_glCompressedTexImage2DARB(GLenum eTarget, GLint iLevel,
    GLenum eInternalFormat, GLsizei iWidth, GLsizei iHeight, GLint iBorder,
    GLsizei iImageSize, const GLvoid* pvData);
SE_EXTERN void SE_glCompressedTexImage3DARB(GLenum eTarget, GLint iLevel,
    GLenum eInternalFormat, GLsizei iWidth, GLsizei iHeight, GLsizei iDepth,
    GLint iBorder, GLsizei iImageSize, const GLvoid* pvData);
SE_EXTERN void SE_glCompressedTexSubImage1DARB(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLsizei iWidth, GLenum eFormat, GLsizei iImageSize,
    const GLvoid* pvData);
SE_EXTERN void SE_glCompressedTexSubImage2DARB(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLint iYOffset, GLsizei iWidth, GLsizei iHeight,
    GLenum eFormat, GLsizei iImageSize, const GLvoid* pvData);
SE_EXTERN void SE_glCompressedTexSubImage3DARB(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLint iYOffset, GLint iZOffset, GLsizei iWidth,
    GLsizei iHeight, GLsizei iDepth, GLenum eFormat, GLsizei iImageSize,
    const GLvoid* pvData);
SE_EXTERN void SE_glGetCompressedTexImageARB(GLenum eTarget, GLint iLevel,
    GLvoid* pvData);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 13) GL_ARB_texture_border_clamp */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbTextureBorderClamp;

#define GL_CLAMP_TO_BORDER_ARB                                      0x812D
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 14) GL_ARB_point_parameters */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbPointParameters;

#define GL_POINT_SIZE_MIN_ARB                                       0x8126
#define GL_POINT_SIZE_MAX_ARB                                       0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_ARB                            0x8128
#define GL_POINT_DISTANCE_ATTENUATION_ARB                           0x8129

#define glPointParameterfARB SE_glPointParameterfARB
#define glPointParameterfvARB SE_glPointParameterfvARB

SE_EXTERN void SE_glPointParameterfARB(GLenum ePName, GLfloat fParam);
SE_EXTERN void SE_glPointParameterfvARB(GLenum ePName,
    const GLfloat* afParam);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 15) GL_ARB_vertex_blend */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbVertexBlend;

#define GL_MAX_VERTEX_UNITS_ARB                                     0x86A4
#define GL_ACTIVE_VERTEX_UNITS_ARB                                  0x86A5
#define GL_WEIGHT_SUM_UNITY_ARB                                     0x86A6
#define GL_VERTEX_BLEND_ARB                                         0x86A7
#define GL_CURRENT_WEIGHT_ARB                                       0x86A8
#define GL_WEIGHT_ARRAY_TYPE_ARB                                    0x86A9
#define GL_WEIGHT_ARRAY_STRIDE_ARB                                  0x86AA
#define GL_WEIGHT_ARRAY_SIZE_ARB                                    0x86AB
#define GL_WEIGHT_ARRAY_POINTER_ARB                                 0x86AC
#define GL_WEIGHT_ARRAY_ARB                                         0x86AD
#define GL_MODELVIEW0_ARB                                           0x1700
#define GL_MODELVIEW1_ARB                                           0x850A
#define GL_MODELVIEW2_ARB                                           0x8722
#define GL_MODELVIEW3_ARB                                           0x8723
#define GL_MODELVIEW4_ARB                                           0x8724
#define GL_MODELVIEW5_ARB                                           0x8725
#define GL_MODELVIEW6_ARB                                           0x8726
#define GL_MODELVIEW7_ARB                                           0x8727
#define GL_MODELVIEW8_ARB                                           0x8728
#define GL_MODELVIEW9_ARB                                           0x8729
#define GL_MODELVIEW10_ARB                                          0x872A
#define GL_MODELVIEW11_ARB                                          0x872B
#define GL_MODELVIEW12_ARB                                          0x872C
#define GL_MODELVIEW13_ARB                                          0x872D
#define GL_MODELVIEW14_ARB                                          0x872E
#define GL_MODELVIEW15_ARB                                          0x872F
#define GL_MODELVIEW16_ARB                                          0x8730
#define GL_MODELVIEW17_ARB                                          0x8731
#define GL_MODELVIEW18_ARB                                          0x8732
#define GL_MODELVIEW19_ARB                                          0x8733
#define GL_MODELVIEW20_ARB                                          0x8734
#define GL_MODELVIEW21_ARB                                          0x8735
#define GL_MODELVIEW22_ARB                                          0x8736
#define GL_MODELVIEW23_ARB                                          0x8737
#define GL_MODELVIEW24_ARB                                          0x8738
#define GL_MODELVIEW25_ARB                                          0x8739
#define GL_MODELVIEW26_ARB                                          0x873A
#define GL_MODELVIEW27_ARB                                          0x873B
#define GL_MODELVIEW28_ARB                                          0x873C
#define GL_MODELVIEW29_ARB                                          0x873D
#define GL_MODELVIEW30_ARB                                          0x873E
#define GL_MODELVIEW31_ARB                                          0x873F

#define glWeightbvARB SE_glWeightbvARB
#define glWeightsvARB SE_glWeightsvARB
#define glWeightivARB SE_glWeightivARB
#define glWeightfvARB SE_glWeightfvARB
#define glWeightdvARB SE_glWeightdvARB
#define glWeightubvARB SE_glWeightubvARB
#define glWeightusvARB SE_glWeightusvARB
#define glWeightuivARB SE_glWeightuivARB
#define glWeightPointerARB SE_glWeightPointerARB
#define glVertexBlendARB SE_glVertexBlendARB

SE_EXTERN void SE_glWeightbvARB(GLint iSize, const GLbyte* acWeight);
SE_EXTERN void SE_glWeightsvARB(GLint iSize, const GLshort* asWeight);
SE_EXTERN void SE_glWeightivARB(GLint iSize, const GLint* aiWeight);
SE_EXTERN void SE_glWeightfvARB(GLint iSize, const GLfloat* afWeight);
SE_EXTERN void SE_glWeightdvARB(GLint iSize, const GLdouble* adWeight);
SE_EXTERN void SE_glWeightubvARB(GLint iSize, const GLubyte* aucWeight);
SE_EXTERN void SE_glWeightusvARB(GLint iSize, const GLushort* ausWeight);
SE_EXTERN void SE_glWeightuivARB(GLint iSize, const GLuint* auiWeight);
SE_EXTERN void SE_glWeightPointerARB(GLint iSize, GLenum eType,
    GLsizei iStride, const GLvoid* pvPointer);
SE_EXTERN void SE_glVertexBlendARB(GLint iCount);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 16) GL_ARB_matrix_palette */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbMatrixPalette;

#define GL_MATRIX_PALETTE_ARB                                       0x8840
#define GL_MAX_MATRIX_PALETTE_STACK_DEPTH_ARB                       0x8841
#define GL_MAX_PALETTE_MATRICES_ARB                                 0x8842
#define GL_CURRENT_PALETTE_MATRIX_ARB                               0x8843
#define GL_MATRIX_INDEX_ARRAY_ARB                                   0x8844
#define GL_CURRENT_MATRIX_INDEX_ARB                                 0x8845
#define GL_MATRIX_INDEX_ARRAY_SIZE_ARB                              0x8846
#define GL_MATRIX_INDEX_ARRAY_TYPE_ARB                              0x8847
#define GL_MATRIX_INDEX_ARRAY_STRIDE_ARB                            0x8848
#define GL_MATRIX_INDEX_ARRAY_POINTER_ARB                           0x8849

#define glCurrentPaletteMatrixARB SE_glCurrentPaletteMatrixARB
#define glMatrixIndexubvARB SE_glMatrixIndexubvARB
#define glMatrixIndexusvARB SE_glMatrixIndexusvARB
#define glMatrixIndexuivARB SE_glMatrixIndexuivARB
#define glMatrixIndexPointerARB SE_glMatrixIndexPointerARB

SE_EXTERN void SE_glCurrentPaletteMatrixARB(GLint iIndex);
SE_EXTERN void SE_glMatrixIndexubvARB(GLint iSize, const GLubyte* aucIndex);
SE_EXTERN void SE_glMatrixIndexusvARB(GLint iSize, const GLushort* ausIndex);
SE_EXTERN void SE_glMatrixIndexuivARB(GLint iSize, const GLuint* auiIndex);
SE_EXTERN void SE_glMatrixIndexPointerARB(GLint iSize, GLenum eType,
    GLsizei iStride, const GLvoid* pvPointer);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 17) GL_ARB_texture_env_combine */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbTextureEnvCombine;

#define GL_SUBTRACT_ARB                                             0x84E7
#define GL_COMBINE_ARB                                              0x8570
#define GL_COMBINE_RGB_ARB                                          0x8571
#define GL_COMBINE_ALPHA_ARB                                        0x8572
#define GL_RGB_SCALE_ARB                                            0x8573
#define GL_ADD_SIGNED_ARB                                           0x8574
#define GL_INTERPOLATE_ARB                                          0x8575
#define GL_CONSTANT_ARB                                             0x8576
#define GL_PRIMARY_COLOR_ARB                                        0x8577
#define GL_PREVIOUS_ARB                                             0x8578
#define GL_SOURCE0_RGB_ARB                                          0x8580
#define GL_SOURCE1_RGB_ARB                                          0x8581
#define GL_SOURCE2_RGB_ARB                                          0x8582
#define GL_SOURCE0_ALPHA_ARB                                        0x8588
#define GL_SOURCE1_ALPHA_ARB                                        0x8589
#define GL_SOURCE2_ALPHA_ARB                                        0x858A
#define GL_OPERAND0_RGB_ARB                                         0x8590
#define GL_OPERAND1_RGB_ARB                                         0x8591
#define GL_OPERAND2_RGB_ARB                                         0x8592
#define GL_OPERAND0_ALPHA_ARB                                       0x8598
#define GL_OPERAND1_ALPHA_ARB                                       0x8599
#define GL_OPERAND2_ALPHA_ARB                                       0x859A
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 18) GL_ARB_texture_env_crossbar */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbTextureEnvCrossbar;
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 19) GL_ARB_texture_env_dot3 */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbTextureEnvDot3;

#define GL_DOT3_RGB_ARB                                             0x86AE
#define GL_DOT3_RGBA_ARB                                            0x86AF
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 21) GL_ARB_texture_mirrored_repeat */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbTextureMirroredRepeat;

#define GL_MIRRORED_REPEAT_ARB                                      0x8370
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 22) GL_ARB_depth_texture */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbDepthTexture;

#define GL_DEPTH_COMPONENT16_ARB                                    0x81A5
#define GL_DEPTH_COMPONENT24_ARB                                    0x81A6
#define GL_DEPTH_COMPONENT32_ARB                                    0x81A7
#define GL_TEXTURE_DEPTH_SIZE_ARB                                   0x884A
#define GL_DEPTH_TEXTURE_MODE_ARB                                   0x884B
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 23) GL_ARB_shadow */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbShadow;

#define GL_TEXTURE_COMPARE_MODE_ARB                                 0x884C
#define GL_TEXTURE_COMPARE_FUNC_ARB                                 0x884D
#define GL_COMPARE_R_TO_TEXTURE_ARB                                 0x884E
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 24) GL_ARB_shadow_ambient */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbShadowAmbient;

#define GL_TEXTURE_COMPARE_FAIL_VALUE_ARB                           0x80BF
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 25) GL_ARB_window_pos */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbWindowPos;

#define glWindowPos2dARB SE_glWindowPos2dARB
#define glWindowPos2dvARB SE_glWindowPos2dvARB
#define glWindowPos2fARB SE_glWindowPos2fARB
#define glWindowPos2fvARB SE_glWindowPos2fvARB
#define glWindowPos2iARB SE_glWindowPos2iARB
#define glWindowPos2ivARB SE_glWindowPos2ivARB
#define glWindowPos2sARB SE_glWindowPos2sARB
#define glWindowPos2svARB SE_glWindowPos2svARB
#define glWindowPos3dARB SE_glWindowPos3dARB
#define glWindowPos3dvARB SE_glWindowPos3dvARB
#define glWindowPos3fARB SE_glWindowPos3fARB
#define glWindowPos3fvARB SE_glWindowPos3fvARB
#define glWindowPos3iARB SE_glWindowPos3iARB
#define glWindowPos3ivARB SE_glWindowPos3ivARB
#define glWindowPos3sARB SE_glWindowPos3sARB
#define glWindowPos3svARB SE_glWindowPos3svARB

SE_EXTERN void SE_glWindowPos2dARB(GLdouble dX, GLdouble dY);
SE_EXTERN void SE_glWindowPos2dvARB(const GLdouble* adXY);
SE_EXTERN void SE_glWindowPos2fARB(GLfloat fX, GLfloat fY);
SE_EXTERN void SE_glWindowPos2fvARB(const GLfloat* afXY);
SE_EXTERN void SE_glWindowPos2iARB(GLint iX, GLint iY);
SE_EXTERN void SE_glWindowPos2ivARB(const GLint* aiXY);
SE_EXTERN void SE_glWindowPos2sARB(GLshort sX, GLshort sY);
SE_EXTERN void SE_glWindowPos2svARB(const GLshort* asXY);
SE_EXTERN void SE_glWindowPos3dARB(GLdouble dX, GLdouble dY, GLdouble dZ);
SE_EXTERN void SE_glWindowPos3dvARB(const GLdouble* adXYZ);
SE_EXTERN void SE_glWindowPos3fARB(GLfloat fX, GLfloat fY, GLfloat fZ);
SE_EXTERN void SE_glWindowPos3fvARB(const GLfloat* afXYZ);
SE_EXTERN void SE_glWindowPos3iARB(GLint iX, GLint iY, GLint iZ);
SE_EXTERN void SE_glWindowPos3ivARB(const GLint* aiXYZ);
SE_EXTERN void SE_glWindowPos3sARB(GLshort sX, GLshort sY, GLshort sZ);
SE_EXTERN void SE_glWindowPos3svARB(const GLshort* asXYZ);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 26) GL_ARB_vertex_program */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbVertexProgram;

#define GL_COLOR_SUM_ARB                                            0x8458
#define GL_VERTEX_PROGRAM_ARB                                       0x8620
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB                          0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE_ARB                             0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE_ARB                           0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE_ARB                             0x8625
#define GL_CURRENT_VERTEX_ATTRIB_ARB                                0x8626
#define GL_PROGRAM_LENGTH_ARB                                       0x8627
#define GL_PROGRAM_STRING_ARB                                       0x8628
#define GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB                       0x862E
#define GL_MAX_PROGRAM_MATRICES_ARB                                 0x862F
#define GL_CURRENT_MATRIX_STACK_DEPTH_ARB                           0x8640
#define GL_CURRENT_MATRIX_ARB                                       0x8641
#define GL_VERTEX_PROGRAM_POINT_SIZE_ARB                            0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE_ARB                              0x8643
#define GL_VERTEX_ATTRIB_ARRAY_POINTER_ARB                          0x8645
#define GL_PROGRAM_ERROR_POSITION_ARB                               0x864B
#define GL_PROGRAM_BINDING_ARB                                      0x8677
#define GL_MAX_VERTEX_ATTRIBS_ARB                                   0x8869
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED_ARB                       0x886A
#define GL_PROGRAM_ERROR_STRING_ARB                                 0x8874
#define GL_PROGRAM_FORMAT_ASCII_ARB                                 0x8875
#define GL_PROGRAM_FORMAT_ARB                                       0x8876
#define GL_PROGRAM_INSTRUCTIONS_ARB                                 0x88A0
#define GL_MAX_PROGRAM_INSTRUCTIONS_ARB                             0x88A1
#define GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB                          0x88A2
#define GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB                      0x88A3
#define GL_PROGRAM_TEMPORARIES_ARB                                  0x88A4
#define GL_MAX_PROGRAM_TEMPORARIES_ARB                              0x88A5
#define GL_PROGRAM_NATIVE_TEMPORARIES_ARB                           0x88A6
#define GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB                       0x88A7
#define GL_PROGRAM_PARAMETERS_ARB                                   0x88A8
#define GL_MAX_PROGRAM_PARAMETERS_ARB                               0x88A9
#define GL_PROGRAM_NATIVE_PARAMETERS_ARB                            0x88AA
#define GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB                        0x88AB
#define GL_PROGRAM_ATTRIBS_ARB                                      0x88AC
#define GL_MAX_PROGRAM_ATTRIBS_ARB                                  0x88AD
#define GL_PROGRAM_NATIVE_ATTRIBS_ARB                               0x88AE
#define GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB                           0x88AF
#define GL_PROGRAM_ADDRESS_REGISTERS_ARB                            0x88B0
#define GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB                        0x88B1
#define GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB                     0x88B2
#define GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB                 0x88B3
#define GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB                         0x88B4
#define GL_MAX_PROGRAM_ENV_PARAMETERS_ARB                           0x88B5
#define GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB                          0x88B6
#define GL_TRANSPOSE_CURRENT_MATRIX_ARB                             0x88B7
#define GL_MATRIX0_ARB                                              0x88C0
#define GL_MATRIX1_ARB                                              0x88C1
#define GL_MATRIX2_ARB                                              0x88C2
#define GL_MATRIX3_ARB                                              0x88C3
#define GL_MATRIX4_ARB                                              0x88C4
#define GL_MATRIX5_ARB                                              0x88C5
#define GL_MATRIX6_ARB                                              0x88C6
#define GL_MATRIX7_ARB                                              0x88C7
#define GL_MATRIX8_ARB                                              0x88C8
#define GL_MATRIX9_ARB                                              0x88C9
#define GL_MATRIX10_ARB                                             0x88CA
#define GL_MATRIX11_ARB                                             0x88CB
#define GL_MATRIX12_ARB                                             0x88CC
#define GL_MATRIX13_ARB                                             0x88CD
#define GL_MATRIX14_ARB                                             0x88CE
#define GL_MATRIX15_ARB                                             0x88CF
#define GL_MATRIX16_ARB                                             0x88D0
#define GL_MATRIX17_ARB                                             0x88D1
#define GL_MATRIX18_ARB                                             0x88D2
#define GL_MATRIX19_ARB                                             0x88D3
#define GL_MATRIX20_ARB                                             0x88D4
#define GL_MATRIX21_ARB                                             0x88D5
#define GL_MATRIX22_ARB                                             0x88D6
#define GL_MATRIX23_ARB                                             0x88D7
#define GL_MATRIX24_ARB                                             0x88D8
#define GL_MATRIX25_ARB                                             0x88D9
#define GL_MATRIX26_ARB                                             0x88DA
#define GL_MATRIX27_ARB                                             0x88DB
#define GL_MATRIX28_ARB                                             0x88DC
#define GL_MATRIX29_ARB                                             0x88DD
#define GL_MATRIX30_ARB                                             0x88DE
#define GL_MATRIX31_ARB                                             0x88DF

#define glBindProgramARB SE_glBindProgramARB
#define glDeleteProgramsARB SE_glDeleteProgramsARB
#define glDisableVertexAttribArrayARB SE_glDisableVertexAttribArrayARB
#define glEnableVertexAttribArrayARB SE_glEnableVertexAttribArrayARB
#define glGenProgramsARB SE_glGenProgramsARB
#define glGetProgramivARB SE_glGetProgramivARB
#define glGetProgramEnvParameterdvARB SE_glGetProgramEnvParameterdvARB
#define glGetProgramEnvParameterfvARB SE_glGetProgramEnvParameterfvARB
#define glGetProgramLocalParameterdvARB SE_glGetProgramLocalParameterdvARB
#define glGetProgramLocalParameterfvARB SE_glGetProgramLocalParameterfvARB
#define glGetProgramStringARB SE_glGetProgramStringARB
#define glGetVertexAttribdvARB SE_glGetVertexAttribdvARB
#define glGetVertexAttribfvARB SE_glGetVertexAttribfvARB
#define glGetVertexAttribivARB SE_glGetVertexAttribivARB
#define glGetVertexAttribPointervARB SE_glGetVertexAttribPointervARB
#define glIsProgramARB SE_glIsProgramARB
#define glProgramEnvParameter4dARB SE_glProgramEnvParameter4dARB
#define glProgramEnvParameter4dvARB SE_glProgramEnvParameter4dvARB
#define glProgramEnvParameter4fARB SE_glProgramEnvParameter4fARB
#define glProgramEnvParameter4fvARB SE_glProgramEnvParameter4fvARB
#define glProgramLocalParameter4dARB SE_glProgramLocalParameter4dARB
#define glProgramLocalParameter4dvARB SE_glProgramLocalParameter4dvARB
#define glProgramLocalParameter4fARB SE_glProgramLocalParameter4fARB
#define glProgramLocalParameter4fvARB SE_glProgramLocalParameter4fvARB
#define glProgramStringARB SE_glProgramStringARB
#define glVertexAttrib1dARB SE_glVertexAttrib1dARB
#define glVertexAttrib1dvARB SE_glVertexAttrib1dvARB
#define glVertexAttrib1fARB SE_glVertexAttrib1fARB
#define glVertexAttrib1fvARB SE_glVertexAttrib1fvARB
#define glVertexAttrib1sARB SE_glVertexAttrib1sARB
#define glVertexAttrib1svARB SE_glVertexAttrib1svARB
#define glVertexAttrib2dARB SE_glVertexAttrib2dARB
#define glVertexAttrib2dvARB SE_glVertexAttrib2dvARB
#define glVertexAttrib2fARB SE_glVertexAttrib2fARB
#define glVertexAttrib2fvARB SE_glVertexAttrib2fvARB
#define glVertexAttrib2sARB SE_glVertexAttrib2sARB
#define glVertexAttrib2svARB SE_glVertexAttrib2svARB
#define glVertexAttrib3dARB SE_glVertexAttrib3dARB
#define glVertexAttrib3dvARB SE_glVertexAttrib3dvARB
#define glVertexAttrib3fARB SE_glVertexAttrib3fARB
#define glVertexAttrib3fvARB SE_glVertexAttrib3fvARB
#define glVertexAttrib3sARB SE_glVertexAttrib3sARB
#define glVertexAttrib3svARB SE_glVertexAttrib3svARB
#define glVertexAttrib4NbvARB SE_glVertexAttrib4NbvARB
#define glVertexAttrib4NivARB SE_glVertexAttrib4NivARB
#define glVertexAttrib4NsvARB SE_glVertexAttrib4NsvARB
#define glVertexAttrib4NubARB SE_glVertexAttrib4NubARB
#define glVertexAttrib4NubvARB SE_glVertexAttrib4NubvARB
#define glVertexAttrib4NuivARB SE_glVertexAttrib4NuivARB
#define glVertexAttrib4NusvARB SE_glVertexAttrib4NusvARB
#define glVertexAttrib4bvARB SE_glVertexAttrib4bvARB
#define glVertexAttrib4dARB SE_glVertexAttrib4dARB
#define glVertexAttrib4dvARB SE_glVertexAttrib4dvARB
#define glVertexAttrib4fARB SE_glVertexAttrib4fARB
#define glVertexAttrib4fvARB SE_glVertexAttrib4fvARB
#define glVertexAttrib4ivARB SE_glVertexAttrib4ivARB
#define glVertexAttrib4sARB SE_glVertexAttrib4sARB
#define glVertexAttrib4svARB SE_glVertexAttrib4svARB
#define glVertexAttrib4ubvARB SE_glVertexAttrib4ubvARB
#define glVertexAttrib4uivARB SE_glVertexAttrib4uivARB
#define glVertexAttrib4usvARB SE_glVertexAttrib4usvARB
#define glVertexAttribPointerARB SE_glVertexAttribPointerARB

SE_EXTERN void SE_glBindProgramARB(GLenum eTarget, GLuint uiProgram);
SE_EXTERN void SE_glDeleteProgramsARB(GLsizei iNumPrograms,
    const GLuint* auiPrograms);
SE_EXTERN void SE_glDisableVertexAttribArrayARB(GLuint uiIndex);
SE_EXTERN void SE_glEnableVertexAttribArrayARB(GLuint uiIndex);
SE_EXTERN void SE_glGenProgramsARB(GLsizei iNumPrograms, GLuint* auiPrograms);
SE_EXTERN void SE_glGetProgramivARB(GLenum eTarget, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glGetProgramEnvParameterdvARB(GLenum eTarget,
    GLuint uiIndex, GLdouble* adParam);
SE_EXTERN void SE_glGetProgramEnvParameterfvARB(GLenum eTarget,
    GLuint uiIndex, GLfloat* afParam);
SE_EXTERN void SE_glGetProgramLocalParameterdvARB(GLenum eTarget,
    GLuint uiIndex, GLdouble* adParam);
SE_EXTERN void SE_glGetProgramLocalParameterfvARB(GLenum eTarget,
    GLuint uiIndex, GLfloat* afParam);
SE_EXTERN void SE_glGetProgramStringARB(GLenum eTarget, GLenum ePName,
    GLvoid* pvString);
SE_EXTERN void SE_glGetVertexAttribdvARB(GLuint uiIndex, GLenum ePName,
    GLdouble* adParam);
SE_EXTERN void SE_glGetVertexAttribfvARB(GLuint uiIndex, GLenum ePName,
    GLfloat* afParam);
SE_EXTERN void SE_glGetVertexAttribivARB(GLuint uiIndex, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glGetVertexAttribPointervARB(GLuint uiIndex, GLenum ePName,
    GLvoid** apvPointer);
SE_EXTERN GLboolean SE_glIsProgramARB(GLuint uiProgram);
SE_EXTERN void SE_glProgramEnvParameter4dARB(GLenum eTarget, GLuint uiIndex,
    GLdouble dX, GLdouble dY, GLdouble dZ, GLdouble dW);
SE_EXTERN void SE_glProgramEnvParameter4dvARB(GLenum eTarget, GLuint uiIndex,
    const GLdouble* adXYZW);
SE_EXTERN void SE_glProgramEnvParameter4fARB(GLenum eTarget, GLuint uiIndex,
    GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fW);
SE_EXTERN void SE_glProgramEnvParameter4fvARB(GLenum eTarget, GLuint uiIndex,
    const GLfloat* afXYZW);
SE_EXTERN void SE_glProgramLocalParameter4dARB(GLenum eTarget, GLuint uiIndex,
    GLdouble dX, GLdouble dY, GLdouble dZ, GLdouble dW);
SE_EXTERN void SE_glProgramLocalParameter4dvARB(GLenum eTarget,
    GLuint uiIndex, const GLdouble* adXYZW);
SE_EXTERN void SE_glProgramLocalParameter4fARB(GLenum eTarget, GLuint uiIndex,
    GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fW);
SE_EXTERN void SE_glProgramLocalParameter4fvARB(GLenum eTarget,
    GLuint uiIndex, const GLfloat* afXYZW);
SE_EXTERN void SE_glProgramStringARB(GLenum eTarget, GLenum eFormat,
    GLsizei iLength, const GLvoid* pvString);
SE_EXTERN void SE_glVertexAttrib1dARB(GLuint uiIndex, GLdouble dX);
SE_EXTERN void SE_glVertexAttrib1dvARB(GLuint uiIndex, const GLdouble* pdX);
SE_EXTERN void SE_glVertexAttrib1fARB(GLuint uiIndex, GLfloat fX);
SE_EXTERN void SE_glVertexAttrib1fvARB(GLuint uiIndex, const GLfloat* pfX);
SE_EXTERN void SE_glVertexAttrib1sARB(GLuint uiIndex, GLshort sX);
SE_EXTERN void SE_glVertexAttrib1svARB(GLuint uiIndex, const GLshort* psX);
SE_EXTERN void SE_glVertexAttrib2dARB(GLuint uiIndex, GLdouble dX,
    GLdouble dY);
SE_EXTERN void SE_glVertexAttrib2dvARB(GLuint uiIndex, const GLdouble* adXY);
SE_EXTERN void SE_glVertexAttrib2fARB(GLuint uiIndex, GLfloat fX, GLfloat fY);
SE_EXTERN void SE_glVertexAttrib2fvARB(GLuint uiIndex, const GLfloat* afXY);
SE_EXTERN void SE_glVertexAttrib2sARB(GLuint uiIndex, GLshort sX, GLshort sY);
SE_EXTERN void SE_glVertexAttrib2svARB(GLuint uiIndex, const GLshort* asXY);
SE_EXTERN void SE_glVertexAttrib3dARB(GLuint uiIndex, GLdouble dX,
    GLdouble dY, GLdouble dZ);
SE_EXTERN void SE_glVertexAttrib3dvARB(GLuint uiIndex, const GLdouble* adXYZ);
SE_EXTERN void SE_glVertexAttrib3fARB(GLuint uiIndex, GLfloat fX, GLfloat fY,
    GLfloat fZ);
SE_EXTERN void SE_glVertexAttrib3fvARB(GLuint uiIndex, const GLfloat* afXYZ);
SE_EXTERN void SE_glVertexAttrib3sARB(GLuint uiIndex, GLshort sX, GLshort sY,
    GLshort sZ);
SE_EXTERN void SE_glVertexAttrib3svARB(GLuint uiIndex, const GLshort* asXYZ);
SE_EXTERN void SE_glVertexAttrib4NbvARB(GLuint uiIndex, const GLbyte* acXYZW);
SE_EXTERN void SE_glVertexAttrib4NivARB(GLuint uiIndex, const GLint* aiXYZW);
SE_EXTERN void SE_glVertexAttrib4NsvARB(GLuint uiIndex,
    const GLshort* asXYZW);
SE_EXTERN void SE_glVertexAttrib4NubARB(GLuint uiIndex, GLubyte ucX,
    GLubyte ucY, GLubyte ucZ, GLubyte ucW);
SE_EXTERN void SE_glVertexAttrib4NubvARB(GLuint uiIndex,
    const GLubyte* aucXYZW);
SE_EXTERN void SE_glVertexAttrib4NuivARB(GLuint uiIndex,
    const GLuint* auiXYZW);
SE_EXTERN void SE_glVertexAttrib4NusvARB(GLuint uiIndex,
    const GLushort* ausXYZW);
SE_EXTERN void SE_glVertexAttrib4bvARB(GLuint uiIndex, const GLbyte* acXYZW);
SE_EXTERN void SE_glVertexAttrib4dARB(GLuint uiIndex, GLdouble dX,
    GLdouble dY, GLdouble dZ, GLdouble dW);
SE_EXTERN void SE_glVertexAttrib4dvARB(GLuint uiIndex,
    const GLdouble* adXYZW);
SE_EXTERN void SE_glVertexAttrib4fARB(GLuint uiIndex, GLfloat fX, GLfloat fY,
    GLfloat fZ, GLfloat fW);
SE_EXTERN void SE_glVertexAttrib4fvARB(GLuint uiIndex, const GLfloat* afXYZW);
SE_EXTERN void SE_glVertexAttrib4ivARB(GLuint uiIndex, const GLint* aiXYZW);
SE_EXTERN void SE_glVertexAttrib4sARB(GLuint uiIndex, GLshort sX, GLshort sY,
    GLshort sZ, GLshort sW);
SE_EXTERN void SE_glVertexAttrib4svARB(GLuint uiIndex, const GLshort* asXYZW);
SE_EXTERN void SE_glVertexAttrib4ubvARB(GLuint uiIndex,
    const GLubyte* aucXYZW);
SE_EXTERN void SE_glVertexAttrib4uivARB(GLuint uiIndex,
    const GLuint* auiXYZW);
SE_EXTERN void SE_glVertexAttrib4usvARB(GLuint uiIndex,
    const GLushort* ausXYZW);
SE_EXTERN void SE_glVertexAttribPointerARB(GLuint uiIndex, GLint iSize,
    GLenum eType, GLboolean ucNormalized, GLsizei iStride,
    const GLvoid* pvPointer);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 27) GL_ARB_fragment_program */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbFragmentProgram;

#define GL_FRAGMENT_PROGRAM_ARB                                     0x8804
#define GL_PROGRAM_ALU_INSTRUCTIONS_ARB                             0x8805
#define GL_PROGRAM_TEX_INSTRUCTIONS_ARB                             0x8806
#define GL_PROGRAM_TEX_INDIRECTIONS_ARB                             0x8807
#define GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB                      0x8808
#define GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB                      0x8809
#define GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB                      0x880A
#define GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB                         0x880B
#define GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB                         0x880C
#define GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB                         0x880D
#define GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB                  0x880E
#define GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB                  0x880F
#define GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB                  0x8810
#define GL_MAX_TEXTURE_COORDS_ARB                                   0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS_ARB                              0x8872
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 28) GL_ARB_vertex_buffer_object */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbVertexBufferObject;

#define GL_BUFFER_SIZE_ARB                                          0x8764
#define GL_BUFFER_USAGE_ARB                                         0x8765
#define GL_ARRAY_BUFFER_ARB                                         0x8892
#define GL_ELEMENT_ARRAY_BUFFER_ARB                                 0x8893
#define GL_ARRAY_BUFFER_BINDING_ARB                                 0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB                         0x8895
#define GL_VERTEX_ARRAY_BUFFER_BINDING_ARB                          0x8896
#define GL_NORMAL_ARRAY_BUFFER_BINDING_ARB                          0x8897
#define GL_COLOR_ARRAY_BUFFER_BINDING_ARB                           0x8898
#define GL_INDEX_ARRAY_BUFFER_BINDING_ARB                           0x8899
#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB                   0x889A
#define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB                       0x889B
#define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB                 0x889C
#define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB                  0x889D
#define GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB                          0x889E
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING_ARB                   0x889F
#define GL_READ_ONLY_ARB                                            0x88B8
#define GL_WRITE_ONLY_ARB                                           0x88B9
#define GL_READ_WRITE_ARB                                           0x88BA
#define GL_BUFFER_ACCESS_ARB                                        0x88BB
#define GL_BUFFER_MAPPED_ARB                                        0x88BC
#define GL_BUFFER_MAP_POINTER_ARB                                   0x88BD
#define GL_STREAM_DRAW_ARB                                          0x88E0
#define GL_STREAM_READ_ARB                                          0x88E1
#define GL_STREAM_COPY_ARB                                          0x88E2
#define GL_STATIC_DRAW_ARB                                          0x88E4
#define GL_STATIC_READ_ARB                                          0x88E5
#define GL_STATIC_COPY_ARB                                          0x88E6
#define GL_DYNAMIC_DRAW_ARB                                         0x88E8
#define GL_DYNAMIC_READ_ARB                                         0x88E9
#define GL_DYNAMIC_COPY_ARB                                         0x88EA

typedef ptrdiff_t GLintptrARB;
typedef ptrdiff_t GLsizeiptrARB;

#define glBindBufferARB SE_glBindBufferARB
#define glDeleteBuffersARB SE_glDeleteBuffersARB
#define glGenBuffersARB SE_glGenBuffersARB
#define glIsBufferARB SE_glIsBufferARB
#define glBufferDataARB SE_glBufferDataARB
#define glBufferSubDataARB SE_glBufferSubDataARB
#define glGetBufferSubDataARB SE_glGetBufferSubDataARB
#define glMapBufferARB SE_glMapBufferARB
#define glUnmapBufferARB SE_glUnmapBufferARB
#define glGetBufferParameterivARB SE_glGetBufferParameterivARB
#define glGetBufferPointervARB SE_glGetBufferPointervARB

SE_EXTERN void SE_glBindBufferARB(GLenum eTarget, GLuint uiBuffer);
SE_EXTERN void SE_glDeleteBuffersARB(GLsizei iNumBuffers,
    const GLuint* auiBuffer);
SE_EXTERN void SE_glGenBuffersARB(GLsizei iNumBuffers, GLuint* auiBuffer);
SE_EXTERN GLboolean SE_glIsBufferARB(GLuint uiBuffer);
SE_EXTERN void SE_glBufferDataARB(GLenum eTarget, GLsizeiptrARB piSize,
    const GLvoid* pvData, GLenum eUsage);
SE_EXTERN void SE_glBufferSubDataARB(GLenum eTarget, GLintptrARB piOffset,
    GLsizeiptrARB piSize, const GLvoid* pvData);
SE_EXTERN void SE_glGetBufferSubDataARB(GLenum eTarget, GLintptrARB piOffset,
    GLsizeiptrARB piSize, GLvoid* pvData);
SE_EXTERN GLvoid* SE_glMapBufferARB(GLenum eTarget, GLenum eAccess);
SE_EXTERN GLboolean SE_glUnmapBufferARB(GLenum eTarget);
SE_EXTERN void SE_glGetBufferParameterivARB(GLenum eTarget, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glGetBufferPointervARB(GLenum eTarget, GLenum ePName,
    GLvoid** apvParam);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 29) GL_ARB_occlusion_query */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbOcclusionQuery;

#define GL_QUERY_COUNTER_BITS_ARB                                   0x8864
#define GL_CURRENT_QUERY_ARB                                        0x8865
#define GL_QUERY_RESULT_ARB                                         0x8866
#define GL_QUERY_RESULT_AVAILABLE_ARB                               0x8867
#define GL_SAMPLES_PASSED_ARB                                       0x8914

#define glGenQueriesARB SE_glGenQueriesARB
#define glDeleteQueriesARB SE_glDeleteQueriesARB
#define glIsQueryARB SE_glIsQueryARB
#define glBeginQueryARB SE_glBeginQueryARB
#define glEndQueryARB SE_glEndQueryARB
#define glGetQueryivARB SE_glGetQueryivARB
#define glGetQueryObjectivARB SE_glGetQueryObjectivARB
#define glGetQueryObjectuivARB SE_glGetQueryObjectuivARB

SE_EXTERN void SE_glGenQueriesARB(GLsizei iNumQueries, GLuint* auiID);
SE_EXTERN void SE_glDeleteQueriesARB(GLsizei iNumQueries,
    const GLuint* auiID);
SE_EXTERN GLboolean SE_glIsQueryARB(GLuint uiID);
SE_EXTERN void SE_glBeginQueryARB(GLenum eTarget, GLuint uiID);
SE_EXTERN void SE_glEndQueryARB(GLenum eTarget);
SE_EXTERN void SE_glGetQueryivARB(GLenum eTarget, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glGetQueryObjectivARB(GLuint uiID, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glGetQueryObjectuivARB(GLuint uiID, GLenum ePName,
    GLuint* auiParam);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 29) GL_ARB_shader_objects */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbShaderObjects;

#define GL_PROGRAM_OBJECT_ARB                                       0x8B40
#define GL_SHADER_OBJECT_ARB                                        0x8B48
#define GL_OBJECT_TYPE_ARB                                          0x8B4E
#define GL_OBJECT_SUBTYPE_ARB                                       0x8B4F
#define GL_FLOAT_VEC2_ARB                                           0x8B50
#define GL_FLOAT_VEC3_ARB                                           0x8B51
#define GL_FLOAT_VEC4_ARB                                           0x8B52
#define GL_INT_VEC2_ARB                                             0x8B53
#define GL_INT_VEC3_ARB                                             0x8B54
#define GL_INT_VEC4_ARB                                             0x8B55
#define GL_BOOL_ARB                                                 0x8B56
#define GL_BOOL_VEC2_ARB                                            0x8B57
#define GL_BOOL_VEC3_ARB                                            0x8B58
#define GL_BOOL_VEC4_ARB                                            0x8B59
#define GL_FLOAT_MAT2_ARB                                           0x8B5A
#define GL_FLOAT_MAT3_ARB                                           0x8B5B
#define GL_FLOAT_MAT4_ARB                                           0x8B5C
#define GL_SAMPLER_1D_ARB                                           0x8B5D
#define GL_SAMPLER_2D_ARB                                           0x8B5E
#define GL_SAMPLER_3D_ARB                                           0x8B5F
#define GL_SAMPLER_CUBE_ARB                                         0x8B60
#define GL_SAMPLER_1D_SHADOW_ARB                                    0x8B61
#define GL_SAMPLER_2D_SHADOW_ARB                                    0x8B62
#define GL_SAMPLER_2D_RECT_ARB                                      0x8B63
#define GL_SAMPLER_2D_RECT_SHADOW_ARB                               0x8B64
#define GL_OBJECT_DELETE_STATUS_ARB                                 0x8B80
#define GL_OBJECT_COMPILE_STATUS_ARB                                0x8B81
#define GL_OBJECT_LINK_STATUS_ARB                                   0x8B82
#define GL_OBJECT_VALIDATE_STATUS_ARB                               0x8B83
#define GL_OBJECT_INFO_LOG_LENGTH_ARB                               0x8B84
#define GL_OBJECT_ATTACHED_OBJECTS_ARB                              0x8B85
#define GL_OBJECT_ACTIVE_UNIFORMS_ARB                               0x8B86
#define GL_OBJECT_ACTIVE_UNIFORM_MAX_LENGTH_ARB                     0x8B87
#define GL_OBJECT_SHADER_SOURCE_LENGTH_ARB                          0x8B88

typedef char GLcharARB;
typedef unsigned int GLhandleARB;

#define glAttachObjectARB SE_glAttachObjectARB
#define glCompileShaderARB SE_glCompileShaderARB
#define glCreateProgramObjectARB SE_glCreateProgramObjectARB
#define glCreateShaderObjectARB SE_glCreateShaderObjectARB
#define glDeleteObjectARB SE_glDeleteObjectARB
#define glDetachObjectARB SE_glDetachObjectARB
#define glGetActiveUniformARB SE_glGetActiveUniformARB
#define glGetAttachedObjectsARB SE_glGetAttachedObjectsARB
#define glGetHandleARB SE_glGetHandleARB
#define glGetInfoLogARB SE_glGetInfoLogARB
#define glGetObjectParameterfvARB SE_glGetObjectParameterfvARB
#define glGetObjectParameterivARB SE_glGetObjectParameterivARB
#define glGetShaderSourceARB SE_glGetShaderSourceARB
#define glGetUniformfvARB SE_glGetUniformfvARB
#define glGetUniformivARB SE_glGetUniformivARB
#define glGetUniformLocationARB SE_glGetUniformLocationARB
#define glLinkProgramARB SE_glLinkProgramARB
#define glShaderSourceARB SE_glShaderSourceARB
#define glUniform1fARB SE_glUniform1fARB
#define glUniform2fARB SE_glUniform2fARB
#define glUniform3fARB SE_glUniform3fARB
#define glUniform4fARB SE_glUniform4fARB
#define glUniform1iARB SE_glUniform1iARB
#define glUniform2iARB SE_glUniform2iARB
#define glUniform3iARB SE_glUniform3iARB
#define glUniform4iARB SE_glUniform4iARB
#define glUniform1fvARB SE_glUniform1fvARB
#define glUniform2fvARB SE_glUniform2fvARB
#define glUniform3fvARB SE_glUniform3fvARB
#define glUniform4fvARB SE_glUniform4fvARB
#define glUniform1ivARB SE_glUniform1ivARB
#define glUniform2ivARB SE_glUniform2ivARB
#define glUniform3ivARB SE_glUniform3ivARB
#define glUniform4ivARB SE_glUniform4ivARB
#define glUniformMatrix2fvARB SE_glUniformMatrix2fvARB
#define glUniformMatrix3fvARB SE_glUniformMatrix3fvARB
#define glUniformMatrix4fvARB SE_glUniformMatrix4fvARB
#define glUseProgramObjectARB SE_glUseProgramObjectARB
#define glValidateProgramARB SE_glValidateProgramARB

SE_EXTERN void SE_glAttachObjectARB(GLhandleARB uiContainer,
    GLhandleARB uiObject);
SE_EXTERN void SE_glCompileShaderARB(GLhandleARB uiShader);
SE_EXTERN GLhandleARB SE_glCreateProgramObjectARB(void);
SE_EXTERN GLhandleARB SE_glCreateShaderObjectARB(GLenum eType);
SE_EXTERN void SE_glDeleteObjectARB(GLhandleARB uiObject);
SE_EXTERN void SE_glDetachObjectARB(GLhandleARB uiContainer,
    GLhandleARB uiObject);
SE_EXTERN void SE_glGetActiveUniformARB(GLhandleARB uiProgram, GLuint uiIndex,
    GLsizei iMaxLength, GLsizei* piLength, GLint* piSize, GLenum* peType,
    GLcharARB* acName);
SE_EXTERN void SE_glGetAttachedObjectsARB(GLhandleARB uiContainer,
    GLsizei iMaxCount, GLsizei* aiCount, GLhandleARB* auiObject);
SE_EXTERN GLhandleARB SE_glGetHandleARB(GLenum ePName);
SE_EXTERN void SE_glGetInfoLogARB(GLhandleARB uiObject, GLsizei iMaxLength,
    GLsizei* piLength, GLcharARB* acInfoLog);
SE_EXTERN void SE_glGetObjectParameterfvARB(GLhandleARB uiObject,
    GLenum ePName, GLfloat* afParam);
SE_EXTERN void SE_glGetObjectParameterivARB(GLhandleARB uiObject,
    GLenum ePName, GLint* aiParam);
SE_EXTERN void SE_glGetShaderSourceARB(GLhandleARB uiObject,
    GLsizei iMaxLength, GLsizei* piLength, GLcharARB* acSource);
SE_EXTERN GLint SE_glGetUniformLocationARB(GLhandleARB uiProgram,
    const GLcharARB* acName);
SE_EXTERN void SE_glGetUniformfvARB(GLhandleARB uiProgram, GLint iLocation,
    GLfloat* afParam);
SE_EXTERN void SE_glGetUniformivARB(GLhandleARB uiProgram, GLint iLocation,
    GLint* aiParam);
SE_EXTERN void SE_glLinkProgramARB(GLhandleARB uiProgram);
SE_EXTERN void SE_glShaderSourceARB(GLhandleARB uiShader, GLsizei iCount,
    const GLcharARB** aacString, const GLint* aiLength);
SE_EXTERN void SE_glUniform1fARB(GLint iLocation, GLfloat fV0);
SE_EXTERN void SE_glUniform2fARB(GLint iLocation, GLfloat fV0, GLfloat fV1);
SE_EXTERN void SE_glUniform3fARB(GLint iLocation, GLfloat fV0, GLfloat fV1,
    GLfloat fV2);
SE_EXTERN void SE_glUniform4fARB(GLint iLocation, GLfloat fV0, GLfloat fV1,
    GLfloat fV2, GLfloat fV3);
SE_EXTERN void SE_glUniform1iARB(GLint iLocation, GLint iV0);
SE_EXTERN void SE_glUniform2iARB(GLint iLocation, GLint iV0, GLint iV1);
SE_EXTERN void SE_glUniform3iARB(GLint iLocation, GLint iV0, GLint iV1,
    GLint iV2);
SE_EXTERN void SE_glUniform4iARB(GLint iLocation, GLint iV0, GLint iV1,
    GLint iV2, GLint iV3);
SE_EXTERN void SE_glUniform1fvARB(GLint iLocation, GLsizei iCount,
    const GLfloat* afValue);
SE_EXTERN void SE_glUniform2fvARB(GLint iLocation, GLsizei iCount,
    const GLfloat* afValue);
SE_EXTERN void SE_glUniform3fvARB(GLint iLocation, GLsizei iCount,
    const GLfloat* afValue);
SE_EXTERN void SE_glUniform4fvARB(GLint iLocation, GLsizei iCount,
    const GLfloat* afValue);
SE_EXTERN void SE_glUniform1ivARB(GLint iLocation, GLsizei iCount,
    const GLint* aiValue);
SE_EXTERN void SE_glUniform2ivARB(GLint iLocation, GLsizei iCount,
    const GLint* aiValue);
SE_EXTERN void SE_glUniform3ivARB(GLint iLocation, GLsizei iCount,
    const GLint* aiValue);
SE_EXTERN void SE_glUniform4ivARB(GLint iLocation, GLsizei iCount,
    const GLint* aiValue);
SE_EXTERN void SE_glUniformMatrix2fvARB(GLint iLocation, GLsizei iCount,
    GLboolean ucTranspose, const GLfloat* afValue);
SE_EXTERN void SE_glUniformMatrix3fvARB(GLint iLocation, GLsizei iCount,
    GLboolean ucTranspose, const GLfloat* afValue);
SE_EXTERN void SE_glUniformMatrix4fvARB(GLint iLocation, GLsizei iCount,
    GLboolean ucTranspose, const GLfloat* afValue);
SE_EXTERN void SE_glUseProgramObjectARB(GLhandleARB uiProgram);
SE_EXTERN void SE_glValidateProgramARB(GLhandleARB uiProgram);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 31) GL_ARB_vertex_shader */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbVertexShader;

#define GL_VERTEX_SHADER_ARB                                        0x8B31
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS_ARB                        0x8B4A
#define GL_MAX_VARYING_FLOATS_ARB                                   0x8B4B
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS_ARB                       0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB                     0x8B4D
#define GL_OBJECT_ACTIVE_ATTRIBUTES_ARB                             0x8B89
#define GL_OBJECT_ACTIVE_ATTRIBUTE_MAX_LENGTH_ARB                   0x8B8A

#define glBindAttribLocationARB SE_glBindAttribLocationARB
#define glGetActiveAttribARB SE_glGetActiveAttribARB
#define glGetAttribLocationARB SE_glGetAttribLocationARB

SE_EXTERN void SE_glBindAttribLocationARB(GLhandleARB uiProgram,
    GLuint uiIndex, const GLcharARB* acName);
SE_EXTERN void SE_glGetActiveAttribARB(GLhandleARB uiProgram, GLuint uiIndex,
    GLsizei iMaxLength, GLsizei* piLength, GLint* piSize, GLenum* peType,
    GLcharARB* acName);
SE_EXTERN GLint SE_glGetAttribLocationARB(GLhandleARB uiProgram,
    const GLcharARB* acName);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 32) GL_ARB_fragment_shader */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbFragmentShader;

#define GL_FRAGMENT_SHADER_ARB                                      0x8B30
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS_ARB                      0x8B49
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT_ARB                      0x8B8B
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 33) GL_ARB_shading_language_100 */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbShadingLanguage100;

#define GL_SHADING_LANGUAGE_VERSION_ARB                             0x8B8C
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 34) GL_ARB_texture_non_power_of_two */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbTextureNonpowerOfTwo;
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 35) GL_ARB_point_sprite */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbPointSprite;

#define GL_POINT_SPRITE_ARB                                         0x8861
#define GL_COORD_REPLACE_ARB                                        0x8862
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 36) GL_ARB_fragment_program_shadow */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbFragmentProgramShadow;
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 37) GL_ARB_draw_buffers */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbDrawBuffers;

#define GL_MAX_DRAW_BUFFERS_ARB                                     0x8824
#define GL_DRAW_BUFFER0_ARB                                         0x8825
#define GL_DRAW_BUFFER1_ARB                                         0x8826
#define GL_DRAW_BUFFER2_ARB                                         0x8827
#define GL_DRAW_BUFFER3_ARB                                         0x8828
#define GL_DRAW_BUFFER4_ARB                                         0x8829
#define GL_DRAW_BUFFER5_ARB                                         0x882A
#define GL_DRAW_BUFFER6_ARB                                         0x882B
#define GL_DRAW_BUFFER7_ARB                                         0x882C
#define GL_DRAW_BUFFER8_ARB                                         0x882D
#define GL_DRAW_BUFFER9_ARB                                         0x882E
#define GL_DRAW_BUFFER10_ARB                                        0x882F
#define GL_DRAW_BUFFER11_ARB                                        0x8830
#define GL_DRAW_BUFFER12_ARB                                        0x8831
#define GL_DRAW_BUFFER13_ARB                                        0x8832
#define GL_DRAW_BUFFER14_ARB                                        0x8833
#define GL_DRAW_BUFFER15_ARB                                        0x8834

#define glDrawBuffersARB SE_glDrawBuffersARB

SE_EXTERN void SE_glDrawBuffersARB(GLsizei iNumBuffers,
    const GLenum* aeBuffer);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 38) GL_ARB_texture_rectangle */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbTextureRectangle;

#define GL_TEXTURE_RECTANGLE_ARB                                    0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE_ARB                            0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE_ARB                              0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_ARB                           0x84F8
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 39) GL_ARB_color_buffer_float */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbColorBufferFloat;

#define GL_RGBA_FLOAT_MODE_ARB                                      0x8820
#define GL_CLAMP_VERTEX_COLOR_ARB                                   0x891A
#define GL_CLAMP_FRAGMENT_COLOR_ARB                                 0x891B
#define GL_CLAMP_READ_COLOR_ARB                                     0x891C
#define GL_FIXED_ONLY_ARB                                           0x891D

#define glClampColorARB SE_glClampColorARB

SE_EXTERN void SE_glClampColorARB(GLenum eTarget, GLenum eClamp);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 40) GL_ARB_half_float_pixel */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbHalfFloatPixel;

#define GL_HALF_FLOAT_ARB                                           0x140B
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 41) GL_ARB_texture_float */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbTextureFloat;

#define GL_TEXTURE_RED_TYPE_ARB                                     0x8C10
#define GL_TEXTURE_GREEN_TYPE_ARB                                   0x8C11
#define GL_TEXTURE_BLUE_TYPE_ARB                                    0x8C12
#define GL_TEXTURE_ALPHA_TYPE_ARB                                   0x8C13
#define GL_TEXTURE_LUMINANCE_TYPE_ARB                               0x8C14
#define GL_TEXTURE_INTENSITY_TYPE_ARB                               0x8C15
#define GL_TEXTURE_DEPTH_TYPE_ARB                                   0x8C16
#define GL_UNSIGNED_NORMALIZED_ARB                                  0x8C17
#define GL_RGBA32F_ARB                                              0x8814
#define GL_RGB32F_ARB                                               0x8815
#define GL_ALPHA32F_ARB                                             0x8816
#define GL_INTENSITY32F_ARB                                         0x8817
#define GL_LUMINANCE32F_ARB                                         0x8818
#define GL_LUMINANCE_ALPHA32F_ARB                                   0x8819
#define GL_RGBA16F_ARB                                              0x881A
#define GL_RGB16F_ARB                                               0x881B
#define GL_ALPHA16F_ARB                                             0x881C
#define GL_INTENSITY16F_ARB                                         0x881D
#define GL_LUMINANCE16F_ARB                                         0x881E
#define GL_LUMINANCE_ALPHA16F_ARB                                   0x881F
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (ARB 42) GL_ARB_pixel_buffer_object */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlArbPixelBufferObject;

#define GL_PIXEL_PACK_BUFFER_ARB                                    0x88EB
#define GL_PIXEL_UNPACK_BUFFER_ARB                                  0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING_ARB                            0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING_ARB                          0x88EF
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/***** EXT Extensions *****/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 001) GL_EXT_abgr */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtABGR;

#define GL_ABGR_EXT                                                 0x8000
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 002) GL_EXT_blend_color */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtBlendColor;

#define GL_CONSTANT_COLOR_EXT                                       0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR_EXT                             0x8002
#define GL_CONSTANT_ALPHA_EXT                                       0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA_EXT                             0x8004
#define GL_BLEND_COLOR_EXT                                          0x8005

#define glBlendColorEXT SE_glBlendColorEXT

SE_EXTERN void SE_glBlendColorEXT(GLclampf fRed, GLclampf fGreen,
    GLclampf fBlue, GLclampf fAlpha);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 003) GL_EXT_polygon_offset */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtPolygonOffset;

#define GL_POLYGON_OFFSET_EXT                                       0x8037
#define GL_POLYGON_OFFSET_FACTOR_EXT                                0x8038
#define GL_POLYGON_OFFSET_BIAS_EXT                                  0x8039

#define glPolygonOffsetEXT SE_glPolygonOffsetEXT

SE_EXTERN void SE_glPolygonOffsetEXT(GLfloat fScale, GLfloat fBias);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 004) GL_EXT_texture */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtTexture;

#define GL_ALPHA4_EXT                                               0x803B
#define GL_ALPHA8_EXT                                               0x803C
#define GL_ALPHA12_EXT                                              0x803D
#define GL_ALPHA16_EXT                                              0x803E
#define GL_LUMINANCE4_EXT                                           0x803F
#define GL_LUMINANCE8_EXT                                           0x8040
#define GL_LUMINANCE12_EXT                                          0x8041
#define GL_LUMINANCE16_EXT                                          0x8042
#define GL_LUMINANCE4_ALPHA4_EXT                                    0x8043
#define GL_LUMINANCE6_ALPHA2_EXT                                    0x8044
#define GL_LUMINANCE8_ALPHA8_EXT                                    0x8045
#define GL_LUMINANCE12_ALPHA4_EXT                                   0x8046
#define GL_LUMINANCE12_ALPHA12_EXT                                  0x8047
#define GL_LUMINANCE16_ALPHA16_EXT                                  0x8048
#define GL_INTENSITY_EXT                                            0x8049
#define GL_INTENSITY4_EXT                                           0x804A
#define GL_INTENSITY8_EXT                                           0x804B
#define GL_INTENSITY12_EXT                                          0x804C
#define GL_INTENSITY16_EXT                                          0x804D
#define GL_RGB2_EXT                                                 0x804E
#define GL_RGB4_EXT                                                 0x804F
#define GL_RGB5_EXT                                                 0x8050
#define GL_RGB8_EXT                                                 0x8051
#define GL_RGB10_EXT                                                0x8052
#define GL_RGB12_EXT                                                0x8053
#define GL_RGB16_EXT                                                0x8054
#define GL_RGBA2_EXT                                                0x8055
#define GL_RGBA4_EXT                                                0x8056
#define GL_RGB5_A1_EXT                                              0x8057
#define GL_RGBA8_EXT                                                0x8058
#define GL_RGB10_A2_EXT                                             0x8059
#define GL_RGBA12_EXT                                               0x805A
#define GL_RGBA16_EXT                                               0x805B
#define GL_TEXTURE_RED_SIZE_EXT                                     0x805C
#define GL_TEXTURE_GREEN_SIZE_EXT                                   0x805D
#define GL_TEXTURE_BLUE_SIZE_EXT                                    0x805E
#define GL_TEXTURE_ALPHA_SIZE_EXT                                   0x805F
#define GL_TEXTURE_LUMINANCE_SIZE_EXT                               0x8060
#define GL_TEXTURE_INTENSITY_SIZE_EXT                               0x8061
#define GL_REPLACE_EXT                                              0x8062
#define GL_PROXY_TEXTURE_1D_EXT                                     0x8063
#define GL_PROXY_TEXTURE_2D_EXT                                     0x8064
#define GL_TEXTURE_TOO_LARGE_EXT                                    0x8065
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 006) GL_EXT_texture3D */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtTexture3D;

#define GL_PACK_SKIP_IMAGES_EXT                                     0x806B
#define GL_PACK_IMAGE_HEIGHT_EXT                                    0x806C
#define GL_UNPACK_SKIP_IMAGES_EXT                                   0x806D
#define GL_UNPACK_IMAGE_HEIGHT_EXT                                  0x806E
#define GL_TEXTURE_3D_EXT                                           0x806F
#define GL_PROXY_TEXTURE_3D_EXT                                     0x8070
#define GL_TEXTURE_DEPTH_EXT                                        0x8071
#define GL_TEXTURE_WRAP_R_EXT                                       0x8072
#define GL_MAX_3D_TEXTURE_SIZE_EXT                                  0x8073

#define glTexImage3DEXT SE_glTexImage3DEXT
#define glTexSubImage3DEXT SE_glTexSubImage3DEXT

SE_EXTERN void SE_glTexImage3DEXT(GLenum eTarget, GLint iLevel,
    GLint iInternalFormat, GLsizei iWidth, GLsizei iHeight, GLsizei iDepth,
    GLint iBorder, GLenum eFormat, GLenum eType, const GLvoid* pvData);
SE_EXTERN void SE_glTexSubImage3DEXT(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLint iYOffset, GLint iZOffset, GLsizei iWidth,
    GLsizei iHeight, GLsizei iDepth, GLenum eFormat, GLenum eType,
    const GLvoid* pvData);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 009) GL_EXT_subtexture */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtSubtexture;

#define glTexSubImage1DEXT SE_glTexSubImage1DEXT
#define glTexSubImage2DEXT SE_glTexSubImage2DEXT

SE_EXTERN void SE_glTexSubImage1DEXT(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLsizei iWidth, GLenum eFormat, GLenum eType,
    const GLvoid* pvData);
SE_EXTERN void SE_glTexSubImage2DEXT(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLint iYOffset, GLsizei iWidth, GLsizei iHeight,
    GLenum eFormat, GLenum eType, const GLvoid* pvData);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 010) GL_EXT_copy_texture */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtCopyTexture;

#define glCopyTexImage1DEXT SE_glCopyTexImage1DEXT
#define glCopyTexImage2DEXT SE_glCopyTexImage2DEXT
#define glCopyTexSubImage1DEXT SE_glCopyTexSubImage1DEXT
#define glCopyTexSubImage2DEXT SE_glCopyTexSubImage2DEXT
#define glCopyTexSubImage3DEXT SE_glCopyTexSubImage3DEXT

SE_EXTERN void SE_glCopyTexImage1DEXT(GLenum eTarget, GLint iLevel,
    GLenum eInternalFormat, GLint iX, GLint iY, GLsizei iWidth,
    GLint iBorder);
SE_EXTERN void SE_glCopyTexImage2DEXT(GLenum eTarget, GLint iLevel,
    GLenum eInternalFormat, GLint iX, GLint iY, GLsizei iWidth,
    GLsizei iHeight, GLint iBorder);
SE_EXTERN void SE_glCopyTexSubImage1DEXT(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLint iX, GLint iY, GLsizei iWidth);
SE_EXTERN void SE_glCopyTexSubImage2DEXT(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLint iYOffset, GLint iX, GLint iY, GLsizei iWidth,
    GLsizei iHeight);
SE_EXTERN void SE_glCopyTexSubImage3DEXT(GLenum eTarget, GLint iLevel,
    GLint iXOffset, GLint iYOffset, GLint iZOffset, GLint iX, GLint iY,
    GLsizei iWidth, GLsizei iHeight);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 011) GL_EXT_histogram */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtHistogram;

#define GL_HISTOGRAM_EXT                                            0x8024
#define GL_PROXY_HISTOGRAM_EXT                                      0x8025
#define GL_HISTOGRAM_WIDTH_EXT                                      0x8026
#define GL_HISTOGRAM_FORMAT_EXT                                     0x8027
#define GL_HISTOGRAM_RED_SIZE_EXT                                   0x8028
#define GL_HISTOGRAM_GREEN_SIZE_EXT                                 0x8029
#define GL_HISTOGRAM_BLUE_SIZE_EXT                                  0x802A
#define GL_HISTOGRAM_ALPHA_SIZE_EXT                                 0x802B
#define GL_HISTOGRAM_LUMINANCE_SIZE_EXT                             0x802C
#define GL_HISTOGRAM_SINK_EXT                                       0x802D
#define GL_MINMAX_EXT                                               0x802E
#define GL_MINMAX_FORMAT_EXT                                        0x802F
#define GL_MINMAX_SINK_EXT                                          0x8030
#define GL_TABLE_TOO_LARGE_EXT                                      0x8031

#define glGetHistogramEXT SE_glGetHistogramEXT
#define glGetHistogramParameterfvEXT SE_glGetHistogramParameterfvEXT
#define glGetHistogramParameterivEXT SE_glGetHistogramParameterivEXT
#define glGetMinmaxEXT SE_glGetMinmaxEXT
#define glGetMinmaxParameterfvEXT SE_glGetMinmaxParameterfvEXT
#define glGetMinmaxParameterivEXT SE_glGetMinmaxParameterivEXT
#define glHistogramEXT SE_glHistogramEXT
#define glMinmaxEXT SE_glMinmaxEXT
#define glResetHistogramEXT SE_glResetHistogramEXT
#define glResetMinmaxEXT SE_glResetMinmaxEXT

SE_EXTERN void SE_glGetHistogramEXT(GLenum eTarget, GLboolean ucReset,
    GLenum eFormat, GLenum eType, GLvoid* pvValues);
SE_EXTERN void SE_glGetHistogramParameterfvEXT(GLenum eTarget, GLenum ePName,
    GLfloat* afParam);
SE_EXTERN void SE_glGetHistogramParameterivEXT(GLenum eTarget, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glGetMinmaxEXT(GLenum eTarget, GLboolean ucReset,
    GLenum eFormat, GLenum eType, GLvoid* pvValues);
SE_EXTERN void SE_glGetMinmaxParameterfvEXT(GLenum eTarget, GLenum ePName,
    GLfloat* afParam);
SE_EXTERN void SE_glGetMinmaxParameterivEXT(GLenum eTarget, GLenum ePName,
    GLint* aiParam);
SE_EXTERN void SE_glHistogramEXT(GLenum eTarget, GLsizei iWidth,
    GLenum eInternalFormat, GLboolean ucSink);
SE_EXTERN void SE_glMinmaxEXT(GLenum eTarget, GLenum eInternalFormat,
    GLboolean ucSink);
SE_EXTERN void SE_glResetHistogramEXT(GLenum eTarget);
SE_EXTERN void SE_glResetMinmaxEXT(GLenum eTarget);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 012) GL_EXT_convolution */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtConvolution;

#define GL_CONVOLUTION_1D_EXT                                       0x8010
#define GL_CONVOLUTION_2D_EXT                                       0x8011
#define GL_SEPARABLE_2D_EXT                                         0x8012
#define GL_CONVOLUTION_BORDER_MODE_EXT                              0x8013
#define GL_CONVOLUTION_FILTER_SCALE_EXT                             0x8014
#define GL_CONVOLUTION_FILTER_BIAS_EXT                              0x8015
#define GL_REDUCE_EXT                                               0x8016
#define GL_CONVOLUTION_FORMAT_EXT                                   0x8017
#define GL_CONVOLUTION_WIDTH_EXT                                    0x8018
#define GL_CONVOLUTION_HEIGHT_EXT                                   0x8019
#define GL_MAX_CONVOLUTION_WIDTH_EXT                                0x801A
#define GL_MAX_CONVOLUTION_HEIGHT_EXT                               0x801B
#define GL_POST_CONVOLUTION_RED_SCALE_EXT                           0x801C
#define GL_POST_CONVOLUTION_GREEN_SCALE_EXT                         0x801D
#define GL_POST_CONVOLUTION_BLUE_SCALE_EXT                          0x801E
#define GL_POST_CONVOLUTION_ALPHA_SCALE_EXT                         0x801F
#define GL_POST_CONVOLUTION_RED_BIAS_EXT                            0x8020
#define GL_POST_CONVOLUTION_GREEN_BIAS_EXT                          0x8021
#define GL_POST_CONVOLUTION_BLUE_BIAS_EXT                           0x8022
#define GL_POST_CONVOLUTION_ALPHA_BIAS_EXT                          0x8023

#define glConvolutionFilter1DEXT SE_glConvolutionFilter1DEXT
#define glConvolutionFilter2DEXT SE_glConvolutionFilter2DEXT
#define glConvolutionParameterfEXT SE_glConvolutionParameterfEXT
#define glConvolutionParameterfvEXT SE_glConvolutionParameterfvEXT
#define glConvolutionParameteriEXT SE_glConvolutionParameteriEXT
#define glConvolutionParameterivEXT SE_glConvolutionParameterivEXT
#define glCopyConvolutionFilter1DEXT SE_glCopyConvolutionFilter1DEXT
#define glCopyConvolutionFilter2DEXT SE_glCopyConvolutionFilter2DEXT
#define glGetConvolutionFilterEXT SE_glGetConvolutionFilterEXT
#define glGetConvolutionParameterfvEXT SE_glGetConvolutionParameterfvEXT
#define glGetConvolutionParameterivEXT SE_glGetConvolutionParameterivEXT
#define glGetSeparableFilterEXT SE_glGetSeparableFilterEXT
#define glSeparableFilter2DEXT SE_glSeparableFilter2DEXT

SE_EXTERN void SE_glConvolutionFilter1DEXT(GLenum eTarget,
    GLenum eInternalFormat, GLsizei iWidth, GLenum eFormat, GLenum eType,
    const GLvoid* pvImage);
SE_EXTERN void SE_glConvolutionFilter2DEXT(GLenum eTarget,
    GLenum eInternalFormat, GLsizei iWidth, GLsizei iHeight, GLenum eFormat,
    GLenum eType, const GLvoid* pvImage);
SE_EXTERN void SE_glConvolutionParameterfEXT(GLenum eTarget, GLenum ePName,
    GLfloat fParam);
SE_EXTERN void SE_glConvolutionParameterfvEXT(GLenum eTarget, GLenum ePName,
    const GLfloat* afParam);
SE_EXTERN void SE_glConvolutionParameteriEXT(GLenum eTarget, GLenum ePName,
    GLint iParam);
SE_EXTERN void SE_glConvolutionParameterivEXT(GLenum eTarget, GLenum ePName,
    const GLint* aiParam);
SE_EXTERN void SE_glCopyConvolutionFilter1DEXT(GLenum eTarget,
    GLenum eInternalFormat, GLint iX, GLint iY, GLsizei iWidth);
SE_EXTERN void SE_glCopyConvolutionFilter2DEXT(GLenum eTarget,
    GLenum eInternalFormat, GLint iX, GLint iY, GLsizei iWidth,
    GLsizei iHeight);
SE_EXTERN void SE_glGetConvolutionFilterEXT(GLenum eTarget, GLenum eFormat,
    GLenum eType, GLvoid* pvImage);
SE_EXTERN void SE_glGetConvolutionParameterfvEXT(GLenum eTarget,
    GLenum ePName, GLfloat* afParam);
SE_EXTERN void SE_glGetConvolutionParameterivEXT(GLenum eTarget,
    GLenum ePName, GLint* aiParam);
SE_EXTERN void SE_glGetSeparableFilterEXT(GLenum eTarget, GLenum eFormat,
    GLenum eType, GLvoid* pvRow, GLvoid* pvColumn, GLvoid* pvSpan);
SE_EXTERN void SE_glSeparableFilter2DEXT(GLenum eTarget,
    GLenum eInternalFormat, GLsizei iWidth, GLsizei iHeight, GLenum eFormat,
    GLenum eType, const GLvoid* pvRow, const GLvoid* pvColumn);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 018) GL_EXT_cmyka */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtCMYKA;

#define GL_CMYK_EXT                                                 0x800C
#define GL_CMYKA_EXT                                                0x800D
#define GL_PACK_CMYK_HINT_EXT                                       0x800E
#define GL_UNPACK_CMYK_HINT_EXT                                     0x800F
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 020) GL_EXT_texture3D */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtTextureObject;

#define GL_TEXTURE_PRIORITY_EXT                                     0x8066
#define GL_TEXTURE_RESIDENT_EXT                                     0x8067
#define GL_TEXTURE_1D_BINDING_EXT                                   0x8068
#define GL_TEXTURE_2D_BINDING_EXT                                   0x8069
#define GL_TEXTURE_3D_BINDING_EXT                                   0x806A

#define glAreTexturesResidentEXT SE_glAreTexturesResidentEXT
#define glBindTextureEXT SE_glBindTextureEXT
#define glDeleteTexturesEXT SE_glDeleteTexturesEXT
#define glGenTexturesEXT SE_glGenTexturesEXT
#define glIsTextureEXT SE_glIsTextureEXT
#define glPrioritizeTexturesEXT SE_glPrioritizeTexturesEXT

SE_EXTERN GLboolean SE_glAreTexturesResidentEXT(GLsizei iNumTextures,
    const GLuint* auiTextures, GLboolean* aucResidences);
SE_EXTERN void SE_glBindTextureEXT(GLenum eTarget, GLuint uiTexture);
SE_EXTERN void SE_glDeleteTexturesEXT(GLsizei iNumTextures,
    const GLuint* auiTextures);
SE_EXTERN void SE_glGenTexturesEXT(GLsizei iNumTextures, GLuint* auiTexture);
SE_EXTERN GLboolean SE_glIsTextureEXT(GLuint uiTexture);
SE_EXTERN void SE_glPrioritizeTexturesEXT(GLsizei iNumTextures,
    const GLuint* auiTextures, const GLclampf* afPriorities);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 023) GL_EXT_packed_pixels */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtPackedPixels;

#define GL_UNSIGNED_BYTE_3_3_2_EXT                                  0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4_EXT                               0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1_EXT                               0x8034
#define GL_UNSIGNED_INT_8_8_8_8_EXT                                 0x8035
#define GL_UNSIGNED_INT_10_10_10_2_EXT                              0x8036
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 027) GL_EXT_rescale_normal */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtRescaleNormal;

#define GL_RESCALE_NORMAL_EXT                                       0x803A
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 030) GL_EXT_vertex_array */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtVertexArray;

#define GL_VERTEX_ARRAY_EXT                                         0x8074
#define GL_NORMAL_ARRAY_EXT                                         0x8075
#define GL_COLOR_ARRAY_EXT                                          0x8076
#define GL_INDEX_ARRAY_EXT                                          0x8077
#define GL_TEXTURE_COORD_ARRAY_EXT                                  0x8078
#define GL_EDGE_FLAG_ARRAY_EXT                                      0x8079
#define GL_VERTEX_ARRAY_SIZE_EXT                                    0x807A
#define GL_VERTEX_ARRAY_TYPE_EXT                                    0x807B
#define GL_VERTEX_ARRAY_STRIDE_EXT                                  0x807C
#define GL_VERTEX_ARRAY_COUNT_EXT                                   0x807D
#define GL_NORMAL_ARRAY_TYPE_EXT                                    0x807E
#define GL_NORMAL_ARRAY_STRIDE_EXT                                  0x807F
#define GL_NORMAL_ARRAY_COUNT_EXT                                   0x8080
#define GL_COLOR_ARRAY_SIZE_EXT                                     0x8081
#define GL_COLOR_ARRAY_TYPE_EXT                                     0x8082
#define GL_COLOR_ARRAY_STRIDE_EXT                                   0x8083
#define GL_COLOR_ARRAY_COUNT_EXT                                    0x8084
#define GL_INDEX_ARRAY_TYPE_EXT                                     0x8085
#define GL_INDEX_ARRAY_STRIDE_EXT                                   0x8086
#define GL_INDEX_ARRAY_COUNT_EXT                                    0x8087
#define GL_TEXTURE_COORD_ARRAY_SIZE_EXT                             0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE_EXT                             0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE_EXT                           0x808A
#define GL_TEXTURE_COORD_ARRAY_COUNT_EXT                            0x808B
#define GL_EDGE_FLAG_ARRAY_STRIDE_EXT                               0x808C
#define GL_EDGE_FLAG_ARRAY_COUNT_EXT                                0x808D
#define GL_VERTEX_ARRAY_POINTER_EXT                                 0x808E
#define GL_NORMAL_ARRAY_POINTER_EXT                                 0x808F
#define GL_COLOR_ARRAY_POINTER_EXT                                  0x8090
#define GL_INDEX_ARRAY_POINTER_EXT                                  0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER_EXT                          0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER_EXT                              0x8093

#define glArrayElementEXT SE_glArrayElementEXT
#define glColorPointerEXT SE_glColorPointerEXT
#define glDrawArraysEXT SE_glDrawArraysEXT
#define glEdgeFlagPointerEXT SE_glEdgeFlagPointerEXT
#define glGetPointervEXT SE_glGetPointervEXT
#define glIndexPointerEXT SE_glIndexPointerEXT
#define glNormalPointerEXT SE_glNormalPointerEXT
#define glTexCoordPointerEXT SE_glTexCoordPointerEXT
#define glVertexPointerEXT SE_glVertexPointerEXT

SE_EXTERN void SE_glArrayElementEXT(GLint i);
SE_EXTERN void SE_glColorPointerEXT(GLint iSize, GLenum eType,
    GLsizei iStride, GLsizei iCount, const GLvoid* pvPointer);
SE_EXTERN void SE_glDrawArraysEXT(GLenum eMode, GLint iFirst, GLsizei iCount);
SE_EXTERN void SE_glEdgeFlagPointerEXT(GLsizei iStride, GLsizei iCount,
    const GLboolean* pvPointer);
SE_EXTERN void SE_glGetPointervEXT(GLenum ePName, GLvoid** apvParam);
SE_EXTERN void SE_glIndexPointerEXT(GLenum eType, GLsizei iStride,
    GLsizei iCount, const GLvoid* pvPointer);
SE_EXTERN void SE_glNormalPointerEXT(GLenum eType, GLsizei iStride,
    GLsizei iCount, const GLvoid* pvPointer);
SE_EXTERN void SE_glTexCoordPointerEXT(GLint iSize, GLenum eType,
    GLsizei iStride, GLsizei iCount, const GLvoid* pvPointer);
SE_EXTERN void SE_glVertexPointerEXT(GLint iSize, GLenum eType,
    GLsizei iStride, GLsizei iCount, const GLvoid* pvPointer);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 031) GL_EXT_misc_attribute */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtMiscAttribute;

/*
The specification document mentions
    GL_MISC_BIT_EXT
but has no value assigned to it.
*/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 037) GL_EXT_blend_minmax */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtBlendMinMax;

#define GL_FUNC_ADD_EXT                                             0x8006
#define GL_MIN_EXT                                                  0x8007
#define GL_MAX_EXT                                                  0x8008
#define GL_BLEND_EQUATION_EXT                                       0x8009

#define glBlendEquationEXT SE_glBlendEquationEXT

SE_EXTERN void SE_glBlendEquationEXT(GLenum eMode);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 038) GL_EXT_blend_subtract */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtBlendSubtract;

#define GL_FUNC_SUBTRACT_EXT                                        0x800A
#define GL_FUNC_REVERSE_SUBTRACT_EXT                                0x800B
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 039) GL_EXT_blend_logic_op */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtBlendLogicOp;
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 054) GL_EXT_point_parameters */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtPointParameters;

#define GL_POINT_SIZE_MIN_EXT                                       0x8126
#define GL_POINT_SIZE_MAX_EXT                                       0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_EXT                            0x8128
#define GL_DISTANCE_ATTENUATION_EXT                                 0x8129

#define glPointParameterfEXT SE_glPointParameterfEXT
#define glPointParameterfvEXT SE_glPointParameterfvEXT

SE_EXTERN void SE_glPointParameterfEXT(GLenum ePName, GLfloat fParam);
SE_EXTERN void SE_glPointParameterfvEXT(GLenum ePName,
    const GLfloat* afParam);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 074) GL_EXT_color_subtable */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtColorSubtable;

#define glColorSubTableEXT SE_glColorSubTableEXT
#define glCopyColorSubTableEXT SE_glCopyColorSubTableEXT

SE_EXTERN void SE_glColorSubTable(GLenum eTarget, GLsizei iStart,
    GLsizei iCount, GLenum eFormat, GLenum eType, const GLvoid* pvData);
SE_EXTERN void SE_glCopyColorSubTable(GLenum eTarget, GLsizei iStart,
    GLint iX, GLint iY, GLsizei iWidth);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 078) GL_EXT_paletted_texture */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtPalettedTexture;

#define GL_COLOR_INDEX1_EXT                                         0x80E2
#define GL_COLOR_INDEX2_EXT                                         0x80E3
#define GL_COLOR_INDEX4_EXT                                         0x80E4
#define GL_COLOR_INDEX8_EXT                                         0x80E5
#define GL_COLOR_INDEX12_EXT                                        0x80E6
#define GL_COLOR_INDEX16_EXT                                        0x80E7
#define GL_TEXTURE_INDEX_SIZE_EXT                                   0x80ED

#define glColorTableEXT SE_glColorTableEXT
#define glGetColorTableEXT SE_glGetColorTableEXT
#define glGetColorTableParameterfvEXT SE_glGetColorTableParameterfvEXT
#define glGetColorTableParameterivEXT SE_glGetColorTableParameterivEXT

SE_EXTERN void SE_glColorTableEXT(GLenum eTarget, GLenum eInternalFormat,
    GLsizei iWidth, GLenum eFormat, GLenum eType, const GLvoid* pvTable);
SE_EXTERN void SE_glGetColorTableEXT(GLenum eTarget, GLenum eFormat,
    GLenum eType, GLvoid* pvTable);
SE_EXTERN void SE_glGetColorTableParameterfvEXT(GLenum eTarget, GLenum ePName,
    GLfloat* afParam);
SE_EXTERN void SE_glGetColorTableParameterivEXT(GLenum eTarget, GLenum ePName,
    GLint* aiParam);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 079) GL_EXT_clip_volume_hint */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtClipVolumeHint;

#define GL_CLIP_VOLUME_CLIPPING_HINT_EXT                            0x80F0
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 093) GL_EXT_index_texture */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtIndexTexture;
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 094) GL_EXT_index_material */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtIndexMaterial;

#define GL_INDEX_MATERIAL_EXT                                       0x81B8
#define GL_INDEX_MATERIAL_PARAMETER_EXT                             0x81B9
#define GL_INDEX_MATERIAL_FACE_EXT                                  0x81BA

#define glIndexMaterialEXT SE_glIndexMaterialEXT

SE_EXTERN void SE_glIndexMaterialEXT(GLenum eFace, GLenum eMode);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 095) GL_EXT_index_func */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtIndexFunc;

#define GL_INDEX_TEST_EXT                                           0x81B5
#define GL_INDEX_TEST_FUNC_EXT                                      0x81B6
#define GL_INDEX_TEST_REF_EXT                                       0x81B7

#define glIndexFuncEXT SE_glIndexFuncEXT

SE_EXTERN void SE_glIndexFuncEXT(GLenum eFunction, GLclampf fReference);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 096) GL_EXT_index_array_formats */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtIndexArrayFormats;

#define GL_IUI_V2F_EXT                                              0x81AD
#define GL_IUI_V3F_EXT                                              0x81AE
#define GL_IUI_N3F_V2F_EXT                                          0x81AF
#define GL_IUI_N3F_V3F_EXT                                          0x81B0
#define GL_T2F_IUI_V2F_EXT                                          0x81B1
#define GL_T2F_IUI_V3F_EXT                                          0x81B2
#define GL_T2F_IUI_N3F_V2F_EXT                                      0x81B3
#define GL_T2F_IUI_N3F_V3F_EXT                                      0x81B4
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 097) GL_EXT_compiled_vertex_array */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtCompiledVertexArray;

#define GL_ARRAY_ELEMENT_LOCK_FIRST_EXT                             0x81A8
#define GL_ARRAY_ELEMENT_LOCK_COUNT_EXT                             0x81A9

#define glLockArraysEXT SE_glLockArraysEXT
#define glUnlockArraysEXT SE_glUnlockArraysEXT

SE_EXTERN void SE_glLockArraysEXT(GLint iFirst, GLsizei iCount);
SE_EXTERN void SE_glUnlockArraysEXT(void);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 098) GL_EXT_cull_vertex */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtCullVertex;

#define GL_CULL_VERTEX_EXT                                          0x81AA
#define GL_CULL_VERTEX_EYE_POSITION_EXT                             0x81AB
#define GL_CULL_VERTEX_OBJECT_POSITION_EXT                          0x81AC

#define glCullParameterdvEXT SE_glCullParameterdvEXT
#define glCullParameterfvEXT SE_glCullParameterfvEXT

SE_EXTERN void SE_glCullParameterdvEXT(GLenum ePName, GLdouble* adParam);
SE_EXTERN void SE_glCullParameterfvEXT(GLenum ePName, GLfloat* afParam);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 112) GL_EXT_draw_range_elements */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtDrawRangeElements;

#define GL_MAX_ELEMENTS_VERTICES_EXT                                0x80E8
#define GL_MAX_ELEMENTS_INDICES_EXT                                 0x80E9

#define glDrawRangeElementsEXT SE_glDrawRangeElementsEXT

SE_EXTERN void SE_glDrawRangeElementsEXT(GLenum eMode, GLuint uiStart,
    GLuint uiEnd, GLsizei iCount, GLenum eType, const GLvoid* pvIndices);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 117) GL_EXT_light_texture */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtLightTexture;

#define GL_FRAGMENT_MATERIAL_EXT                                    0x8349
#define GL_FRAGMENT_NORMAL_EXT                                      0x834A
#define GL_FRAGMENT_COLOR_EXT                                       0x834C
#define GL_ATTENUATION_EXT                                          0x834D
#define GL_SHADOW_ATTENUATION_EXT                                   0x834E
#define GL_TEXTURE_APPLICATION_MODE_EXT                             0x834F
#define GL_TEXTURE_LIGHT_EXT                                        0x8350
#define GL_TEXTURE_MATERIAL_FACE_EXT                                0x8351
#define GL_TEXTURE_MATERIAL_PARAMETER_EXT                           0x8352

#define glApplyTextureEXT SE_glApplyTextureEXT
#define glTextureLightEXT SE_glTextureLightEXT
#define glTextureMaterialEXT SE_glTextureMaterialEXT

SE_EXTERN void SE_glApplyTextureEXT(GLenum eMode);
SE_EXTERN void SE_glTextureLightEXT(GLenum ePName);
SE_EXTERN void SE_glTextureMaterialEXT(GLenum eFace, GLenum eMode);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 129) GL_EXT_bgra */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtBGRA;

#define GL_BGR_EXT                                                  0x80E0
#define GL_BGRA_EXT                                                 0x80E1
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 138) GL_EXT_pixel_transform */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtPixelTransform;

#define GL_PIXEL_TRANSFORM_2D_EXT                                   0x8330
#define GL_PIXEL_MAG_FILTER_EXT                                     0x8331
#define GL_PIXEL_MIN_FILTER_EXT                                     0x8332
#define GL_PIXEL_CUBIC_WEIGHT_EXT                                   0x8333
#define GL_CUBIC_EXT                                                0x8334
#define GL_AVERAGE_EXT                                              0x8335
#define GL_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT                       0x8336
#define GL_MAX_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT                   0x8337
#define GL_PIXEL_TRANSFORM_2D_MATRIX_EXT                            0x8338

#define glPixelTransformParameteriEXT SE_glPixelTransformParameteriEXT
#define glPixelTransformParameterfEXT SE_glPixelTransformParameterfEXT
#define glPixelTransformParameterivEXT SE_glPixelTransformParameterivEXT
#define glPixelTransformParameterfvEXT SE_glPixelTransformParameterfvEXT

SE_EXTERN void SE_glPixelTransformParameteriEXT(GLenum eTarget, GLenum ePName,
    GLint iParam);
SE_EXTERN void SE_glPixelTransformParameterfEXT(GLenum eTarget, GLenum ePName,
    GLfloat fParam);
SE_EXTERN void SE_glPixelTransformParameterivEXT(GLenum eTarget,
    GLenum ePName, const GLint* aiParam);
SE_EXTERN void SE_glPixelTransformParameterfvEXT(GLenum eTarget,
    GLenum ePName, const GLfloat* afParam);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 139) GL_EXT_pixel_transform_color_table */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtPixelTransformColorTable;

/*
The specification document mentions
    GL_PIXEL_TRANSFORM_COLOR_TABLE_EXT
    GL_PROXY_PIXEL_TRANSFORM_COLOR_TABLE_EXT
but has no values assigned to them.
*/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 141) GL_EXT_shared_texture_palette */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtSharedTexturePalette;

#define GL_SHARED_TEXTURE_PALETTE_EXT                               0x81FB
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 144) GL_EXT_separate_specular_color */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtSeparateSpecularColor;

#define GL_LIGHT_MODEL_COLOR_CONTROL_EXT                            0x81F8
#define GL_SINGLE_COLOR_EXT                                         0x81F9
#define GL_SEPARATE_SPECULAR_COLOR_EXT                              0x81FA
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 145) GL_EXT_secondary_color */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtSecondaryColor;

#define GL_COLOR_SUM_EXT                                            0x8458
#define GL_CURRENT_SECONDARY_COLOR_EXT                              0x8459
#define GL_SECONDARY_COLOR_ARRAY_SIZE_EXT                           0x845A
#define GL_SECONDARY_COLOR_ARRAY_TYPE_EXT                           0x845B
#define GL_SECONDARY_COLOR_ARRAY_STRIDE_EXT                         0x845C
#define GL_SECONDARY_COLOR_ARRAY_POINTER_EXT                        0x845D
#define GL_SECONDARY_COLOR_ARRAY_EXT                                0x845E

#define glSecondaryColor3bEXT SE_glSecondaryColor3bEXT
#define glSecondaryColor3bvEXT SE_glSecondaryColor3bvEXT
#define glSecondaryColor3dEXT SE_glSecondaryColor3dEXT
#define glSecondaryColor3dvEXT SE_glSecondaryColor3dvEXT
#define glSecondaryColor3fEXT SE_glSecondaryColor3fEXT
#define glSecondaryColor3fvEXT SE_glSecondaryColor3fvEXT
#define glSecondaryColor3iEXT SE_glSecondaryColor3iEXT
#define glSecondaryColor3ivEXT SE_glSecondaryColor3ivEXT
#define glSecondaryColor3sEXT SE_glSecondaryColor3sEXT
#define glSecondaryColor3svEXT SE_glSecondaryColor3svEXT
#define glSecondaryColor3ubEXT SE_glSecondaryColor3ubEXT
#define glSecondaryColor3ubvEXT SE_glSecondaryColor3ubvEXT
#define glSecondaryColor3uiEXT SE_glSecondaryColor3uiEXT
#define glSecondaryColor3uivEXT SE_glSecondaryColor3uivEXT
#define glSecondaryColor3usEXT SE_glSecondaryColor3usEXT
#define glSecondaryColor3usvEXT SE_glSecondaryColor3usvEXT
#define glSecondaryColorPointerEXT SE_glSecondaryColorPointerEXT

SE_EXTERN void SE_glSecondaryColor3bEXT(GLbyte cR, GLbyte cG, GLbyte cB);
SE_EXTERN void SE_glSecondaryColor3bvEXT(const GLbyte* acRGB);
SE_EXTERN void SE_glSecondaryColor3dEXT(GLdouble dR, GLdouble dG,
    GLdouble dB);
SE_EXTERN void SE_glSecondaryColor3dvEXT(const GLdouble* adRGB);
SE_EXTERN void SE_glSecondaryColor3fEXT(GLfloat fR, GLfloat fG, GLfloat fB);
SE_EXTERN void SE_glSecondaryColor3fvEXT(const GLfloat* afRGB);
SE_EXTERN void SE_glSecondaryColor3iEXT(GLint iR, GLint iG, GLint iB);
SE_EXTERN void SE_glSecondaryColor3ivEXT(const GLint* aiRGB);
SE_EXTERN void SE_glSecondaryColor3sEXT(GLshort sR, GLshort sG, GLshort sB);
SE_EXTERN void SE_glSecondaryColor3svEXT(const GLshort* asRGB);
SE_EXTERN void SE_glSecondaryColor3ubEXT(GLubyte ucR, GLubyte ucG,
    GLubyte ucB);
SE_EXTERN void SE_glSecondaryColor3ubvEXT(const GLubyte* aucRGB);
SE_EXTERN void SE_glSecondaryColor3uiEXT(GLuint uiR, GLuint uiG, GLuint uiB);
SE_EXTERN void SE_glSecondaryColor3uivEXT(const GLuint* auiRGB);
SE_EXTERN void SE_glSecondaryColor3usEXT(GLushort usR, GLushort usG,
    GLushort usB);
SE_EXTERN void SE_glSecondaryColor3usvEXT(const GLushort* ausRGB);
SE_EXTERN void SE_glSecondaryColorPointerEXT(GLint iSize, GLenum eType,
    GLsizei iStride, const GLvoid* pvPointer);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 147) GL_EXT_texture_perturb_normal */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtTexturePerturbNormal;

#define GL_PERTURB_EXT                    0x85AE
#define GL_TEXTURE_NORMAL_EXT             0x85AF

#define glTextureNormalEXT SE_glTextureNormalEXT

SE_EXTERN void SE_glTextureNormalEXT(GLenum eMode);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 148) GL_EXT_multi_draw_arrays */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtMultidrawArrays;

#define glMultiDrawArraysEXT SE_glMultiDrawArraysEXT
#define glMultiDrawElementsEXT SE_glMultiDrawElementsEXT

SE_EXTERN void SE_glMultiDrawArraysEXT(GLenum eMode, GLint* aiFirst,
    GLsizei* aiCount, GLsizei iPrimitiveCount);
SE_EXTERN void SE_glMultiDrawElementsEXT(GLenum eMode, const GLsizei* aiCount,
    GLenum eType, const GLvoid** apvIndices, GLsizei iPrimitiveCount);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 149) GL_EXT_fog_coord */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtFogCoord;

#define GL_FOG_COORDINATE_SOURCE_EXT                                0x8450
#define GL_FOG_COORDINATE_EXT                                       0x8451
#define GL_FRAGMENT_DEPTH_EXT                                       0x8452
#define GL_CURRENT_FOG_COORDINATE_EXT                               0x8453
#define GL_FOG_COORDINATE_ARRAY_TYPE_EXT                            0x8454
#define GL_FOG_COORDINATE_ARRAY_STRIDE_EXT                          0x8455
#define GL_FOG_COORDINATE_ARRAY_POINTER_EXT                         0x8456
#define GL_FOG_COORDINATE_ARRAY_EXT                                 0x8457

#define glFogCoorddEXT SE_glFogCoorddEXT
#define glFogCoorddvEXT SE_glFogCoorddvEXT
#define glFogCoordfEXT SE_glFogCoordfEXT
#define glFogCoordfvEXT SE_glFogCoordfvEXT
#define glFogCoordPointerEXT SE_glFogCoordPointerEXT

SE_EXTERN void SE_glFogCoorddEXT(GLdouble dCoord);
SE_EXTERN void SE_glFogCoorddvEXT(const GLdouble *adCoord);
SE_EXTERN void SE_glFogCoordfEXT(GLfloat fCoord);
SE_EXTERN void SE_glFogCoordfvEXT(const GLfloat *afCoord);
SE_EXTERN void SE_glFogCoordPointerEXT(GLenum eType, GLsizei iStride,
    const GLvoid* pvPointer);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 156) GL_EXT_coordinate_frame */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtCoordinateFrame;

#define GL_TANGENT_ARRAY_EXT                                        0x8439
#define GL_BINORMAL_ARRAY_EXT                                       0x843A
#define GL_CURRENT_TANGENT_EXT                                      0x843B
#define GL_CURRENT_BINORMAL_EXT                                     0x843C
#define GL_TANGENT_ARRAY_TYPE_EXT                                   0x843E
#define GL_TANGENT_ARRAY_STRIDE_EXT                                 0x843F
#define GL_BINORMAL_ARRAY_TYPE_EXT                                  0x8440
#define GL_BINORMAL_ARRAY_STRIDE_EXT                                0x8441
#define GL_TANGENT_ARRAY_POINTER_EXT                                0x8442
#define GL_BINORMAL_ARRAY_POINTER_EXT                               0x8443
#define GL_MAP1_TANGENT_EXT                                         0x8444
#define GL_MAP2_TANGENT_EXT                                         0x8445
#define GL_MAP1_BINORMAL_EXT                                        0x8446
#define GL_MAP2_BINORMAL_EXT                                        0x8447

#define glTangent3bEXT SE_glTangent3bEXT
#define glTangent3bvEXT SE_glTangent3bvEXT
#define glTangent3dEXT SE_glTangent3dEXT
#define glTangent3dvEXT SE_glTangent3dvEXT
#define glTangent3fEXT SE_glTangent3fEXT
#define glTangent3fvEXT SE_glTangent3fvEXT
#define glTangent3iEXT SE_glTangent3iEXT
#define glTangent3ivEXT SE_glTangent3ivEXT
#define glTangent3sEXT SE_glTangent3sEXT
#define glTangent3svEXT SE_glTangent3svEXT
#define glBinormal3bEXT SE_glBinormal3bEXT
#define glBinormal3bvEXT SE_glBinormal3bvEXT
#define glBinormal3dEXT SE_glBinormal3dEXT
#define glBinormal3dvEXT SE_glBinormal3dvEXT
#define glBinormal3fEXT SE_glBinormal3fEXT
#define glBinormal3fvEXT SE_glBinormal3fvEXT
#define glBinormal3iEXT SE_glBinormal3iEXT
#define glBinormal3ivEXT SE_glBinormal3ivEXT
#define glBinormal3sEXT SE_glBinormal3sEXT
#define glBinormal3svEXT SE_glBinormal3svEXT
#define glTangentPointerEXT SE_glTangentPointerEXT
#define glBinormalPointerEXT SE_glBinormalPointerEXT

SE_EXTERN void SE_glTangent3bEXT(GLbyte cX, GLbyte cY, GLbyte cZ);
SE_EXTERN void SE_glTangent3bvEXT(const GLbyte* acXYZ);
SE_EXTERN void SE_glTangent3dEXT(GLdouble dX, GLdouble dY, GLdouble dZ);
SE_EXTERN void SE_glTangent3dvEXT(const GLdouble* adXYZ);
SE_EXTERN void SE_glTangent3fEXT(GLfloat fX, GLfloat fY, GLfloat fZ);
SE_EXTERN void SE_glTangent3fvEXT(const GLfloat* afXYZ);
SE_EXTERN void SE_glTangent3iEXT(GLint iX, GLint iY, GLint iZ);
SE_EXTERN void SE_glTangent3ivEXT(const GLint* aiXYZ);
SE_EXTERN void SE_glTangent3sEXT(GLshort sX, GLshort sY, GLshort sZ);
SE_EXTERN void SE_glTangent3svEXT(const GLshort* asXYZ);
SE_EXTERN void SE_glBinormal3bEXT(GLbyte cX, GLbyte cY, GLbyte cZ);
SE_EXTERN void SE_glBinormal3bvEXT(const GLbyte* acXYZ);
SE_EXTERN void SE_glBinormal3dEXT(GLdouble dX, GLdouble dY, GLdouble dZ);
SE_EXTERN void SE_glBinormal3dvEXT(const GLdouble* adXYZ);
SE_EXTERN void SE_glBinormal3fEXT(GLfloat fX, GLfloat fY, GLfloat fZ);
SE_EXTERN void SE_glBinormal3fvEXT(const GLfloat* afXYZ);
SE_EXTERN void SE_glBinormal3iEXT(GLint iX, GLint iY, GLint iZ);
SE_EXTERN void SE_glBinormal3ivEXT(const GLint* aiXYZ);
SE_EXTERN void SE_glBinormal3sEXT(GLshort sX, GLshort sY, GLshort sZ);
SE_EXTERN void SE_glBinormal3svEXT(const GLshort* asXYZ);
SE_EXTERN void SE_glTangentPointerEXT(GLenum eType, GLsizei iStride,
    const GLvoid* pvPointer);
SE_EXTERN void SE_glBinormalPointerEXT(GLenum eType, GLsizei iStride,
    const GLvoid* pvPointer);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 158) GL_EXT_texture_env_combine */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtTextureEnvCombine;

#define GL_COMBINE_EXT                                              0x8570
#define GL_COMBINE_RGB_EXT                                          0x8571
#define GL_COMBINE_ALPHA_EXT                                        0x8572
#define GL_RGB_SCALE_EXT                                            0x8573
#define GL_ADD_SIGNED_EXT                                           0x8574
#define GL_INTERPOLATE_EXT                                          0x8575
#define GL_CONSTANT_EXT                                             0x8576
#define GL_PRIMARY_COLOR_EXT                                        0x8577
#define GL_PREVIOUS_EXT                                             0x8578
#define GL_SOURCE0_RGB_EXT                                          0x8580
#define GL_SOURCE1_RGB_EXT                                          0x8581
#define GL_SOURCE2_RGB_EXT                                          0x8582
#define GL_SOURCE0_ALPHA_EXT                                        0x8588
#define GL_SOURCE1_ALPHA_EXT                                        0x8589
#define GL_SOURCE2_ALPHA_EXT                                        0x858A
#define GL_OPERAND0_RGB_EXT                                         0x8590
#define GL_OPERAND1_RGB_EXT                                         0x8591
#define GL_OPERAND2_RGB_EXT                                         0x8592
#define GL_OPERAND0_ALPHA_EXT                                       0x8598
#define GL_OPERAND1_ALPHA_EXT                                       0x8599
#define GL_OPERAND2_ALPHA_EXT                                       0x859A
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 173) GL_EXT_blend_func_separate */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtBlendFuncSeparate;

#define GL_BLEND_DST_RGB_EXT                                        0x80C8
#define GL_BLEND_SRC_RGB_EXT                                        0x80C9
#define GL_BLEND_DST_ALPHA_EXT                                      0x80CA
#define GL_BLEND_SRC_ALPHA_EXT                                      0x80CB

#define glBlendFuncSeparateEXT SE_glBlendFuncSeparateEXT

SE_EXTERN void SE_glBlendFuncSeparateEXT(GLenum eSrcFactorRGB,
    GLenum eDstFactorRGB, GLenum eSrcFactorA, GLenum eDstFactorA);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 176) GL_EXT_stencil_wrap */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtStencilWrap;

#define GL_INCR_WRAP_EXT                                            0x8507
#define GL_DECR_WRAP_EXT                                            0x8508
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 178) GL_EXT_422_pixels */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExt422Pixels;

#define GL_422_EXT                                                  0x80CC
#define GL_422_REV_EXT                                              0x80CD
#define GL_422_AVERAGE_EXT                                          0x80CE
#define GL_422_REV_AVERAGE_EXT                                      0x80CF
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 185) GL_EXT_texture_env_add */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtTextureEnvAdd;
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 186) GL_EXT_texture_lod_bias */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtTextureLodBias;

#define GL_MAX_TEXTURE_LOD_BIAS_EXT                                 0x84FD
#define GL_TEXTURE_FILTER_CONTROL_EXT                               0x8500
#define GL_TEXTURE_LOD_BIAS_EXT                                     0x8501
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 187) GL_EXT_texture_filter_anisotropic */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtTextureFilterAnisotropic;

#define GL_TEXTURE_MAX_ANISOTROPY_EXT                               0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT                           0x84FF
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 188) GL_EXT_vertex_weighting */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtVertexWeighting;

#define GL_MODELVIEW0_STACK_DEPTH_EXT                               0x0BA3
#define GL_MODELVIEW1_STACK_DEPTH_EXT                               0x8502
#define GL_MODELVIEW0_MATRIX_EXT                                    0x0BA6
#define GL_MODELVIEW1_MATRIX_EXT                                    0x8506
#define GL_VERTEX_WEIGHTING_EXT                                     0x8509
#define GL_MODELVIEW0_EXT                                           0x1700
#define GL_MODELVIEW1_EXT                                           0x850A
#define GL_CURRENT_VERTEX_WEIGHT_EXT                                0x850B
#define GL_VERTEX_WEIGHT_ARRAY_EXT                                  0x850C
#define GL_VERTEX_WEIGHT_ARRAY_SIZE_EXT                             0x850D
#define GL_VERTEX_WEIGHT_ARRAY_TYPE_EXT                             0x850E
#define GL_VERTEX_WEIGHT_ARRAY_STRIDE_EXT                           0x850F
#define GL_VERTEX_WEIGHT_ARRAY_POINTER_EXT                          0x8510

#define glVertexWeightfEXT SE_glVertexWeightfEXT
#define glVertexWeightfvEXT SE_glVertexWeightfvEXT
#define glVertexWeightPointerEXT SE_glVertexWeightPointerEXT

SE_EXTERN void SE_glVertexWeightfEXT(GLfloat fWeight);
SE_EXTERN void SE_glVertexWeightfvEXT(const GLfloat* afWeight);
SE_EXTERN void SE_glVertexWeightPointerEXT(GLsizei iSize, GLenum eType,
    GLsizei iStride, const GLvoid* pvPointer);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 198) GL_EXT_texture_compression_s3tc */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtTextureCompressionS3TC;

#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT                             0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT                            0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT                            0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT                            0x83F3
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 209) GL_EXT_multisample */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtMultisample;

#define GL_MULTISAMPLE_EXT                                          0x809D
#define GL_SAMPLE_ALPHA_TO_MASK_EXT                                 0x809E
#define GL_SAMPLE_ALPHA_TO_ONE_EXT                                  0x809F
#define GL_SAMPLE_MASK_EXT                                          0x80A0
#define GL_1PASS_EXT                                                0x80A1
#define GL_2PASS_0_EXT                                              0x80A2
#define GL_2PASS_1_EXT                                              0x80A3
#define GL_4PASS_0_EXT                                              0x80A4
#define GL_4PASS_1_EXT                                              0x80A5
#define GL_4PASS_2_EXT                                              0x80A6
#define GL_4PASS_3_EXT                                              0x80A7
#define GL_SAMPLE_BUFFERS_EXT                                       0x80A8
#define GL_SAMPLES_EXT                                              0x80A9
#define GL_SAMPLE_MASK_VALUE_EXT                                    0x80AA
#define GL_SAMPLE_MASK_INVERT_EXT                                   0x80AB
#define GL_SAMPLE_PATTERN_EXT                                       0x80AC
#define GL_MULTISAMPLE_BIT_EXT                                      0x20000000

#define glSampleMaskEXT SE_glSampleMaskEXT
#define glSamplePatternEXT SE_glSamplePatternEXT

SE_EXTERN void SE_glSampleMaskEXT(GLclampf fValue, GLboolean ucInvert);
SE_EXTERN void SE_glSamplePatternEXT(GLenum ePattern);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 220) GL_EXT_texture_env_dot3 */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtTextureEnvDot3;

#define GL_DOT3_RGB_EXT                                             0x8740
#define GL_DOT3_RGBA_EXT                                            0x8741
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 267) GL_EXT_shadow_funcs */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtShadowFuncs;
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 268) GL_EXT_stencil_two_side */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtStencilTwoSide;

#define GL_STENCIL_TEST_TWO_SIDE_EXT                                0x8910
#define GL_ACTIVE_STENCIL_FACE_EXT                                  0x8911

#define glActiveStencilFaceEXT SE_glActiveStencilFaceEXT

SE_EXTERN void SE_glActiveStencilFaceEXT(GLenum eFace);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 297) GL_EXT_depth_bounds_test */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtDepthBoundsTest;

#define GL_DEPTH_BOUNDS_TEST_EXT                                    0x8890
#define GL_DEPTH_BOUNDS_EXT                                         0x8891

#define glDepthBoundsEXT SE_glDepthBoundsEXT

SE_EXTERN void SE_glDepthBoundsEXT(GLclampd dMin, GLclampd dMax);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 298) GL_EXT_texture_mirror_clamp */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtTextureMirrorClamp;

#define GL_MIRROR_CLAMP_EXT                                         0x8742
#define GL_MIRROR_CLAMP_TO_EDGE_EXT                                 0x8743
#define GL_MIRROR_CLAMP_TO_BORDER_EXT                               0x8912
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 299) GL_EXT_blend_equation_separate */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtBlendEquationSeparate;

#define GL_BLEND_EQUATION_RGB_EXT                                   0x8009
#define GL_BLEND_EQUATION_ALPHA_EXT                                 0x883D

#define glBlendEquationSeparateEXT SE_glBlendEquationSeparateEXT

SE_EXTERN void SE_glBlendEquationSeparateEXT(GLenum eModeRGB,
    GLenum eModeAlpha);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 302) GL_EXT_pixel_buffer_object */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtPixelBufferObject;

#define GL_PIXEL_PACK_BUFFER_EXT                                    0x88EB
#define GL_PIXEL_UNPACK_BUFFER_EXT                                  0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING_EXT                            0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING_EXT                          0x88EF
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 304) GL_NV_fragment_program2 */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlNvFragmentProgram2;

#define GL_MAX_PROGRAM_EXEC_INSTRUCTIONS_NV                         0x88F4
#define GL_MAX_PROGRAM_CALL_DEPTH_NV                                0x88F5
#define GL_MAX_PROGRAM_IF_DEPTH_NV                                  0x88F6
#define GL_MAX_PROGRAM_LOOP_DEPTH_NV                                0x88F7
#define GL_MAX_PROGRAM_LOOP_COUNT_NV                                0x88F8
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 306) GL_NV_vertex_program3 */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlNvVertexProgram3;
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 309) GL_EXT_texture_compression_dxt1 */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtTextureCompressionDXT1;
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 310) GL_EXT_framebuffer_object */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtFrameBufferObject;

#define GL_INVALID_FRAMEBUFFER_OPERATION_EXT                        0x0506
#define GL_MAX_RENDERBUFFER_SIZE_EXT                                0x84E8
#define GL_FRAMEBUFFER_BINDING_EXT                                  0x8CA6
#define GL_RENDERBUFFER_BINDING_EXT                                 0x8CA7
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT                   0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT                   0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT                 0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_EXT         0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT            0x8CD4
#define GL_FRAMEBUFFER_COMPLETE_EXT                                 0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENTS_EXT                   0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT            0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT          0x8CD8
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT                    0x8CD9
#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT                       0x8CDA
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT                   0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT                   0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED_EXT                              0x8CDD
#define GL_FRAMEBUFFER_STATUS_ERROR_EXT                             0x8CDE
#define GL_MAX_COLOR_ATTACHMENTS_EXT                                0x8CDF
#define GL_COLOR_ATTACHMENT0_EXT                                    0x8CE0
#define GL_COLOR_ATTACHMENT1_EXT                                    0x8CE1
#define GL_COLOR_ATTACHMENT2_EXT                                    0x8CE2
#define GL_COLOR_ATTACHMENT3_EXT                                    0x8CE3
#define GL_COLOR_ATTACHMENT4_EXT                                    0x8CE4
#define GL_COLOR_ATTACHMENT5_EXT                                    0x8CE5
#define GL_COLOR_ATTACHMENT6_EXT                                    0x8CE6
#define GL_COLOR_ATTACHMENT7_EXT                                    0x8CE7
#define GL_COLOR_ATTACHMENT8_EXT                                    0x8CE8
#define GL_COLOR_ATTACHMENT9_EXT                                    0x8CE9
#define GL_COLOR_ATTACHMENT10_EXT                                   0x8CEA
#define GL_COLOR_ATTACHMENT11_EXT                                   0x8CEB
#define GL_COLOR_ATTACHMENT12_EXT                                   0x8CEC
#define GL_COLOR_ATTACHMENT13_EXT                                   0x8CED
#define GL_COLOR_ATTACHMENT14_EXT                                   0x8CEE
#define GL_COLOR_ATTACHMENT15_EXT                                   0x8CEF
#define GL_DEPTH_ATTACHMENT_EXT                                     0x8D00
#define GL_STENCIL_ATTACHMENT_EXT                                   0x8D20
#define GL_FRAMEBUFFER_EXT                                          0x8D40
#define GL_RENDERBUFFER_EXT                                         0x8D41
#define GL_RENDERBUFFER_WIDTH_EXT                                   0x8D42
#define GL_RENDERBUFFER_HEIGHT_EXT                                  0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT_EXT                         0x8D44
#define GL_STENCIL_INDEX_EXT                                        0x8D45
#define GL_STENCIL_INDEX1_EXT                                       0x8D46
#define GL_STENCIL_INDEX4_EXT                                       0x8D47
#define GL_STENCIL_INDEX8_EXT                                       0x8D48
#define GL_STENCIL_INDEX16_EXT                                      0x8D49

#define glIsRenderbufferEXT SE_glIsRenderbufferEXT
#define glBindRenderbufferEXT SE_glBindRenderbufferEXT
#define glDeleteRenderbuffersEXT SE_glDeleteRenderbuffersEXT
#define glGenRenderbuffersEXT SE_glGenRenderbuffersEXT
#define glRenderbufferStorageEXT SE_glRenderbufferStorageEXT
#define glGetRenderbufferParameterivEXT SE_glGetRenderbufferParameterivEXT
#define glIsFramebufferEXT SE_glIsFramebufferEXT
#define glBindFramebufferEXT SE_glBindFramebufferEXT
#define glDeleteFramebuffersEXT SE_glDeleteFramebuffersEXT
#define glGenFramebuffersEXT SE_glGenFramebuffersEXT
#define glCheckFramebufferStatusEXT SE_glCheckFramebufferStatusEXT
#define glFramebufferTexture1DEXT SE_glFramebufferTexture1DEXT
#define glFramebufferTexture2DEXT SE_glFramebufferTexture2DEXT
#define glFramebufferTexture3DEXT SE_glFramebufferTexture3DEXT
#define glFramebufferRenderbufferEXT SE_glFramebufferRenderbufferEXT
#define glGetFramebufferAttachmentParameterivEXT\
    SE_glGetFramebufferAttachmentParameterivEXT
#define glGenerateMipmapEXT SE_glGenerateMipmapEXT

SE_EXTERN GLboolean SE_glIsRenderbufferEXT(GLuint uiRenderBuffer);
SE_EXTERN void SE_glBindRenderbufferEXT(GLenum eTarget,
    GLuint uiRenderBuffer);
SE_EXTERN void SE_glDeleteRenderbuffersEXT(GLsizei iNumBuffers,
    const GLuint* auiRenderBuffer);
SE_EXTERN void SE_glGenRenderbuffersEXT(GLsizei iNumBuffers,
    GLuint* auiRenderBuffer);
SE_EXTERN void SE_glRenderbufferStorageEXT(GLenum eTarget,
    GLenum eInternalFormat, GLsizei iWidth, GLsizei iHeight);
SE_EXTERN void SE_glGetRenderbufferParameterivEXT(GLenum eTarget,
    GLenum ePName, GLint* aiParam);
SE_EXTERN GLboolean SE_glIsFramebufferEXT(GLuint uiFrameBuffer);
SE_EXTERN void SE_glBindFramebufferEXT(GLenum eTarget, GLuint uiFrameBuffer);
SE_EXTERN void SE_glDeleteFramebuffersEXT(GLsizei iNumBuffers,
    const GLuint* auiFrameBuffer);
SE_EXTERN void SE_glGenFramebuffersEXT(GLsizei iNumBuffers,
    GLuint* auiFrameBuffer);
SE_EXTERN GLenum SE_glCheckFramebufferStatusEXT(GLenum eTarget);
SE_EXTERN void SE_glFramebufferTexture1DEXT(GLenum eTarget,
    GLenum eAttachment, GLenum eTextureTarget, GLuint uiTexture,
    GLint iLevel);
SE_EXTERN void SE_glFramebufferTexture2DEXT(GLenum eTarget,
    GLenum eAttachment, GLenum eTextureTarget, GLuint uiTexture,
    GLint iLevel);
SE_EXTERN void SE_glFramebufferTexture3DEXT(GLenum eTarget,
    GLenum eAttachment, GLenum eTextureTarget, GLuint uiTexture, GLint iLevel,
    GLint iZOffset);
SE_EXTERN void SE_glFramebufferRenderbufferEXT(GLenum eTarget,
    GLenum eAttachment, GLenum eRenderBufferTarget, GLuint uiRenderBuffer);
SE_EXTERN void SE_glGetFramebufferAttachmentParameterivEXT(GLenum eTarget,
    GLenum eAttachment, GLenum ePName, GLint* aiParam);
SE_EXTERN void SE_glGenerateMipmapEXT(GLenum eTarget);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 312) GL_EXT_packed_depth_stencil */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtPackedDepthStencil;

#define GL_DEPTH_STENCIL_EXT                                        0x84F9
#define GL_UNSIGNED_INT_24_8_EXT                                    0x84FA
#define GL_DEPTH24_STENCIL8_EXT                                     0x88F0
#define GL_TEXTURE_STENCIL_SIZE_EXT                                 0x88F1
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 314) GL_EXT_stencil_clear_tag */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtStencilClearTag;

/*
The specification file mentions the information here but none of the tokens
or functions were found in the file glext.h (version 29).  I suppose it is
possible that glext.h is not current relative to the extensions posted at the
OpenGL extension registry.
*/

#define GL_STENCIL_TAG_BITS_EXT                                     0x88F2
#define GL_STENCIL_CLEAR_TAG_VALUE_EXT                              0x88F3

#define glStencilClearTagEXT SE_glStencilClearTagEXT

SE_EXTERN void SE_glStencilClearTagEXT(GLsizei iStencilTagBits,
    GLuint uiStencilClearTag);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 315) GL_EXT_texture_sRGB */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtTextureSRGB;

#define GL_SRGB_EXT                                                 0x8C40
#define GL_SRGB8_EXT                                                0x8C41
#define GL_SRGB_ALPHA_EXT                                           0x8C42
#define GL_SRGB8_ALPHA8_EXT                                         0x8C43
#define GL_SLUMINANCE_ALPHA_EXT                                     0x8C44
#define GL_SLUMINANCE8_ALPHA8_EXT                                   0x8C45
#define GL_SLUMINANCE_EXT                                           0x8C46
#define GL_SLUMINANCE8_EXT                                          0x8C47
#define GL_COMPRESSED_SRGB_EXT                                      0x8C48
#define GL_COMPRESSED_SRGB_ALPHA_EXT                                0x8C49
#define GL_COMPRESSED_SLUMINANCE_EXT                                0x8C4A
#define GL_COMPRESSED_SLUMINANCE_ALPHA_EXT                          0x8C4B
#define GL_COMPRESSED_SRGB_S3TC_DXT1_EXT                            0x8C4C
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT                      0x8C4D
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT                      0x8C4E
#define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT                      0x8C4F
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 316) GL_EXT_framebuffer_blit */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtFrameBufferBlit;

/*
The specification file mentions the information here but none of the tokens
or functions were found in the file glext.h (version 29).  I suppose it is
possible that glext.h is not current relative to the extensions posted at the
OpenGL extension registry.
*/

#define GL_READ_FRAMEBUFFER_EXT                                     0x8CA8
#define GL_DRAW_FRAMEBUFFER_EXT                                     0x8CA9
#define GL_DRAW_FRAMEBUFFER_BINDING_EXT                             0x8CA6
#define GL_READ_FRAMEBUFFER_BINDING_EXT                             0x8CAA

#define glBlitFramebufferEXT SE_glBlitFramebufferEXT

SE_EXTERN void SE_glBlitFramebufferEXT(GLint iSrcX0, GLint iSrcY0,
    GLint iSrcX1, GLint iSrcY1, GLint iDstX0, GLint iDstY0, GLint iDstX1,
    GLint iDstY1, GLbitfield uiMask, GLenum eFilter);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* (EXT 317) GL_EXT_framebuffer_multisample */
/*--------------------------------------------------------------------------*/
SE_EXTERN int SE_ExistsGlExtFrameBufferMultisample;

/*
The specification file mentions the information here but none of the tokens
or functions were found in the file glext.h (version 29).  I suppose it is
possible that glext.h is not current relative to the extensions posted at the
OpenGL extension registry.
*/

#define GL_RENDERBUFFER_SAMPLES_EXT                                 0x8CAB

#define glRenderbufferStorageMultisampleEXT\
    SE_glRenderbufferStorageMultisampleEXT

SE_EXTERN void SE_glRenderbufferStorageMultisampleEXT(GLenum eTarget,
    GLsizei iSamples, GLenum eInternalFormat, GLsizei iWidth,
    GLsizei iHeight);
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* GLU */
/*--------------------------------------------------------------------------*/
#ifdef WIN32
/* Microsoft Windows */

#ifndef APIENTRY
#define SE_DEFINED_APIENTRY
#define APIENTRY __stdcall
#endif

#ifndef CALLBACK
#define SE_DEFINED_CALLBACK
#define CALLBACK __stdcall
#endif

#ifndef GLAPI
#define SE_DEFINED_GLAPI
#define GLAPI extern
#endif

#else
/* Macintosh, Linux */
#define APIENTRY
#define CALLBACK
#endif

#ifdef __APPLE__
#include <OpenGL/glu.h> /* Macintosh中glu.h不需要APIENTRY, CALLBACK */
#else
#include <GL/glu.h> /* Microsoft Windows中glu.h需要APIENTRY, CALLBACK */
#endif

#ifdef SE_DEFINED_APIENTRY
#undef APIENTRY
#endif

#ifdef SE_DEFINED_CALLBACK
#undef CALLBACK
#endif

#ifdef SE_DEFINED_GLAPI
#undef GLAPI
#endif
/*--------------------------------------------------------------------------*/

SE_EXTERN const char* SE_GL_GetVendorString(void);
SE_EXTERN const char* SE_GL_GetRendererString(void);
SE_EXTERN const char* SE_GL_GetVersionString(void);
SE_EXTERN const char* SE_GL_GetExtensionString(void);
SE_EXTERN void SE_GL_Initialize(const char* acInfoFile);

}  /* extern "C" */

#endif
