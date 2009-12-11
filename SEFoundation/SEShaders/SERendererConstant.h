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

#ifndef Swing_RendererConstant_H
#define Swing_RendererConstant_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEMain.h"
#include "SEStringHashTable.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:渲染器常量类
// 说明:shader程序中的全局数值量,
//      主要指渲染器管线所需的各种T&L数据.
// 作者:Sun Che
// 时间:20080623
//----------------------------------------------------------------------------
class SE_FOUNDATION_API RendererConstant
{
    SE_DECLARE_INITIALIZE;
    SE_DECLARE_TERMINATE;

public:
    enum Type
    {
        W_MATRIX,                          // 4x4 model-to-world matrix
        V_MATRIX,                          // 4x4 world-to-view matrix
        P_MATRIX,                          // 4x4 view-to-clip matrix
        WV_MATRIX,                         // 4x4 model-to-view matrix
        VP_MATRIX,                         // 4x4 world-to-clip matrix
        WVP_MATRIX,                        // 4x4 model-to-clip matrix
        W_MATRIX_TRANSPOSE,                // 4x4 trans model-to-world
        V_MATRIX_TRANSPOSE,                // 4x4 trans world-to-view
        P_MATRIX_TRANSPOSE,                // 4x4 trans view-to-clip
        WV_MATRIX_TRANSPOSE,               // 4x4 trans model-to-view
        VP_MATRIX_TRANSPOSE,               // 4x4 trans world-to-clip
        WVP_MATRIX_TRANSPOSE,              // 4x4 trans model-to-clip
        W_MATRIX_INVERSE,                  // 4x4 inv model-to-world
        V_MATRIX_INVERSE,                  // 4x4 inv world-to-view
        P_MATRIX_INVERSE,                  // 4x4 inv view-to-clip
        WV_MATRIX_INVERSE,                 // 4x4 inv model-to-view
        VP_MATRIX_INVERSE,                 // 4x4 inv world-to-clip
        WVP_MATRIX_INVERSE,                // 4x4 inv model-to-clip
        W_MATRIX_INVERSE_TRANSPOSE,        // 4x4 inv-trans model-to-world
        V_MATRIX_INVERSE_TRANSPOSE,        // 4x4 inv-trans world-to-view
        P_MATRIX_INVERSE_TRANSPOSE,        // 4x4 inv-trans view-to-clip
        WV_MATRIX_INVERSE_TRANSPOSE,       // 4x4 inv-trans model-to-view
        VP_MATRIX_INVERSE_TRANSPOSE,       // 4x4 inv-trans world-to-clip
        WVP_MATRIX_INVERSE_TRANSPOSE,      // 4x4 inv-trans model-to-clip

        MATERIAL_EMISSIVE,                 // (r,g,b)
        MATERIAL_AMBIENT,                  // (r,g,b)
        MATERIAL_DIFFUSE,                  // (r,g,b;alpha)
        MATERIAL_SPECULAR,                 // (r,g,b;shininess)

        CAMERA_MODEL_POSITION,             // (x,y,z,1)
        CAMERA_MODEL_RIGHT,                // (x,y,z,0)
        CAMERA_MODEL_UP,                   // (x,y,z,0)
        CAMERA_MODEL_DIRECTION,            // (x,y,z,0)

        CAMERA_WORLD_POSITION,             // (x,y,z,1)
        CAMERA_WORLD_RIGHT,                // (x,y,z,0)
        CAMERA_WORLD_UP,                   // (x,y,z,0)
        CAMERA_WORLD_DIRECTION,            // (x,y,z,0)

        PROJECTOR_MODEL_POSITION,          // (x,y,z,1)
        PROJECTOR_MODEL_RIGHT,             // (x,y,z,0)
        PROJECTOR_MODEL_UP,                // (x,y,z,0)
        PROJECTOR_MODEL_DIRECTION,         // (x,y,z,0)

        PROJECTOR_WORLD_POSITION,          // (x,y,z,1)
        PROJECTOR_WORLD_RIGHT,             // (x,y,z,0)
        PROJECTOR_WORLD_UP,                // (x,y,z,0)
        PROJECTOR_WORLD_DIRECTION,         // (x,y,z,0)

        PROJECTOR_MATRIX,                  // 4x4 world-to-clip matrix

        LIGHT0_MODEL_POSITION,             // (x,y,z,1)
        LIGHT0_MODEL_DIRECTION,            // (x,y,z,0)
        LIGHT0_WORLD_POSITION,             // (x,y,z,1)
        LIGHT0_WORLD_DIRECTION,            // (x,y,z,0)
        LIGHT0_AMBIENT,                    // (r,g,b,a)
        LIGHT0_DIFFUSE,                    // (r,g,b,a)
        LIGHT0_SPECULAR,                   // (r,g,b,a)
        LIGHT0_SPOTCUTOFF,                 // (angle,cos,sin,exponent)
        LIGHT0_ATTENUATION,                // (const,lin,quad,intensity)

        LIGHT1_MODEL_POSITION,             // (x,y,z,1)
        LIGHT1_MODEL_DIRECTION,            // (x,y,z,0)
        LIGHT1_WORLD_POSITION,             // (x,y,z,1)
        LIGHT1_WORLD_DIRECTION,            // (x,y,z,0)
        LIGHT1_AMBIENT,                    // (r,g,b,a)
        LIGHT1_DIFFUSE,                    // (r,g,b,a)
        LIGHT1_SPECULAR,                   // (r,g,b,a)
        LIGHT1_SPOTCUTOFF,                 // (angle,cos,sin,exponent)
        LIGHT1_ATTENUATION,                // (const,lin,quad,intensity)

        LIGHT2_MODEL_POSITION,             // (x,y,z,1)
        LIGHT2_MODEL_DIRECTION,            // (x,y,z,0)
        LIGHT2_WORLD_POSITION,             // (x,y,z,1)
        LIGHT2_WORLD_DIRECTION,            // (x,y,z,0)
        LIGHT2_AMBIENT,                    // (r,g,b,a)
        LIGHT2_DIFFUSE,                    // (r,g,b,a)
        LIGHT2_SPECULAR,                   // (r,g,b,a)
        LIGHT2_SPOTCUTOFF,                 // (angle,cos,sin,exponent)
        LIGHT2_ATTENUATION,                // (const,lin,quad,intensity)

        LIGHT3_MODEL_POSITION,             // (x,y,z,1)
        LIGHT3_MODEL_DIRECTION,            // (x,y,z,0)
        LIGHT3_WORLD_POSITION,             // (x,y,z,1)
        LIGHT3_WORLD_DIRECTION,            // (x,y,z,0)
        LIGHT3_AMBIENT,                    // (r,g,b,a)
        LIGHT3_DIFFUSE,                    // (r,g,b,a)
        LIGHT3_SPECULAR,                   // (r,g,b,a)
        LIGHT3_SPOTCUTOFF,                 // (angle,cos,sin,exponent)
        LIGHT3_ATTENUATION,                // (const,lin,quad,intensity)

        LIGHT4_MODEL_POSITION,             // (x,y,z,1)
        LIGHT4_MODEL_DIRECTION,            // (x,y,z,0)
        LIGHT4_WORLD_POSITION,             // (x,y,z,1)
        LIGHT4_WORLD_DIRECTION,            // (x,y,z,0)
        LIGHT4_AMBIENT,                    // (r,g,b,a)
        LIGHT4_DIFFUSE,                    // (r,g,b,a)
        LIGHT4_SPECULAR,                   // (r,g,b,a)
        LIGHT4_SPOTCUTOFF,                 // (angle,cos,sin,exponent)
        LIGHT4_ATTENUATION,                // (const,lin,quad,intensity)

        LIGHT5_MODEL_POSITION,             // (x,y,z,1)
        LIGHT5_MODEL_DIRECTION,            // (x,y,z,0)
        LIGHT5_WORLD_POSITION,             // (x,y,z,1)
        LIGHT5_WORLD_DIRECTION,            // (x,y,z,0)
        LIGHT5_AMBIENT,                    // (r,g,b,a)
        LIGHT5_DIFFUSE,                    // (r,g,b,a)
        LIGHT5_SPECULAR,                   // (r,g,b,a)
        LIGHT5_SPOTCUTOFF,                 // (angle,cos,sin,exponent)
        LIGHT5_ATTENUATION,                // (const,lin,quad,intensity)

        LIGHT6_MODEL_POSITION,             // (x,y,z,1)
        LIGHT6_MODEL_DIRECTION,            // (x,y,z,0)
        LIGHT6_WORLD_POSITION,             // (x,y,z,1)
        LIGHT6_WORLD_DIRECTION,            // (x,y,z,0)
        LIGHT6_AMBIENT,                    // (r,g,b,a)
        LIGHT6_DIFFUSE,                    // (r,g,b,a)
        LIGHT6_SPECULAR,                   // (r,g,b,a)
        LIGHT6_SPOTCUTOFF,                 // (angle,cos,sin,exponent)
        LIGHT6_ATTENUATION,                // (const,lin,quad,intensity)

        LIGHT7_MODEL_POSITION,             // (x,y,z,1)
        LIGHT7_MODEL_DIRECTION,            // (x,y,z,0)
        LIGHT7_WORLD_POSITION,             // (x,y,z,1)
        LIGHT7_WORLD_DIRECTION,            // (x,y,z,0)
        LIGHT7_AMBIENT,                    // (r,g,b,a)
        LIGHT7_DIFFUSE,                    // (r,g,b,a)
        LIGHT7_SPECULAR,                   // (r,g,b,a)
        LIGHT7_SPOTCUTOFF,                 // (angle,cos,sin,exponent)
        LIGHT7_ATTENUATION,                // (const,lin,quad,intensity)

        LIGHT_ARRAY0_MODEL_POSITION,       // (x,y,z,1)
        LIGHT_ARRAY0_MODEL_DIRECTION,      // (x,y,z,0)
        LIGHT_ARRAY0_WORLD_POSITION,       // (x,y,z,1)
        LIGHT_ARRAY0_WORLD_DIRECTION,      // (x,y,z,0)
        LIGHT_ARRAY0_AMBIENT,              // (r,g,b,a)
        LIGHT_ARRAY0_DIFFUSE,              // (r,g,b,a)
        LIGHT_ARRAY0_SPECULAR,             // (r,g,b,a)
        LIGHT_ARRAY0_SPOTCUTOFF,           // (angle,cos,sin,exponent)
        LIGHT_ARRAY0_ATTENUATION,          // (const,lin,quad,intensity)

        LIGHT_ARRAY1_MODEL_POSITION,       // (x,y,z,1)
        LIGHT_ARRAY1_MODEL_DIRECTION,      // (x,y,z,0)
        LIGHT_ARRAY1_WORLD_POSITION,       // (x,y,z,1)
        LIGHT_ARRAY1_WORLD_DIRECTION,      // (x,y,z,0)
        LIGHT_ARRAY1_AMBIENT,              // (r,g,b,a)
        LIGHT_ARRAY1_DIFFUSE,              // (r,g,b,a)
        LIGHT_ARRAY1_SPECULAR,             // (r,g,b,a)
        LIGHT_ARRAY1_SPOTCUTOFF,           // (angle,cos,sin,exponent)
        LIGHT_ARRAY1_ATTENUATION,          // (const,lin,quad,intensity)

        LIGHT_ARRAY2_MODEL_POSITION,       // (x,y,z,1)
        LIGHT_ARRAY2_MODEL_DIRECTION,      // (x,y,z,0)
        LIGHT_ARRAY2_WORLD_POSITION,       // (x,y,z,1)
        LIGHT_ARRAY2_WORLD_DIRECTION,      // (x,y,z,0)
        LIGHT_ARRAY2_AMBIENT,              // (r,g,b,a)
        LIGHT_ARRAY2_DIFFUSE,              // (r,g,b,a)
        LIGHT_ARRAY2_SPECULAR,             // (r,g,b,a)
        LIGHT_ARRAY2_SPOTCUTOFF,           // (angle,cos,sin,exponent)
        LIGHT_ARRAY2_ATTENUATION,          // (const,lin,quad,intensity)

        LIGHT_ARRAY3_MODEL_POSITION,       // (x,y,z,1)
        LIGHT_ARRAY3_MODEL_DIRECTION,      // (x,y,z,0)
        LIGHT_ARRAY3_WORLD_POSITION,       // (x,y,z,1)
        LIGHT_ARRAY3_WORLD_DIRECTION,      // (x,y,z,0)
        LIGHT_ARRAY3_AMBIENT,              // (r,g,b,a)
        LIGHT_ARRAY3_DIFFUSE,              // (r,g,b,a)
        LIGHT_ARRAY3_SPECULAR,             // (r,g,b,a)
        LIGHT_ARRAY3_SPOTCUTOFF,           // (angle,cos,sin,exponent)
        LIGHT_ARRAY3_ATTENUATION,          // (const,lin,quad,intensity)

        LIGHT_ARRAY4_MODEL_POSITION,       // (x,y,z,1)
        LIGHT_ARRAY4_MODEL_DIRECTION,      // (x,y,z,0)
        LIGHT_ARRAY4_WORLD_POSITION,       // (x,y,z,1)
        LIGHT_ARRAY4_WORLD_DIRECTION,      // (x,y,z,0)
        LIGHT_ARRAY4_AMBIENT,              // (r,g,b,a)
        LIGHT_ARRAY4_DIFFUSE,              // (r,g,b,a)
        LIGHT_ARRAY4_SPECULAR,             // (r,g,b,a)
        LIGHT_ARRAY4_SPOTCUTOFF,           // (angle,cos,sin,exponent)
        LIGHT_ARRAY4_ATTENUATION,          // (const,lin,quad,intensity)

        LIGHT_ARRAY5_MODEL_POSITION,       // (x,y,z,1)
        LIGHT_ARRAY5_MODEL_DIRECTION,      // (x,y,z,0)
        LIGHT_ARRAY5_WORLD_POSITION,       // (x,y,z,1)
        LIGHT_ARRAY5_WORLD_DIRECTION,      // (x,y,z,0)
        LIGHT_ARRAY5_AMBIENT,              // (r,g,b,a)
        LIGHT_ARRAY5_DIFFUSE,              // (r,g,b,a)
        LIGHT_ARRAY5_SPECULAR,             // (r,g,b,a)
        LIGHT_ARRAY5_SPOTCUTOFF,           // (angle,cos,sin,exponent)
        LIGHT_ARRAY5_ATTENUATION,          // (const,lin,quad,intensity)

        LIGHT_ARRAY6_MODEL_POSITION,       // (x,y,z,1)
        LIGHT_ARRAY6_MODEL_DIRECTION,      // (x,y,z,0)
        LIGHT_ARRAY6_WORLD_POSITION,       // (x,y,z,1)
        LIGHT_ARRAY6_WORLD_DIRECTION,      // (x,y,z,0)
        LIGHT_ARRAY6_AMBIENT,              // (r,g,b,a)
        LIGHT_ARRAY6_DIFFUSE,              // (r,g,b,a)
        LIGHT_ARRAY6_SPECULAR,             // (r,g,b,a)
        LIGHT_ARRAY6_SPOTCUTOFF,           // (angle,cos,sin,exponent)
        LIGHT_ARRAY6_ATTENUATION,          // (const,lin,quad,intensity)

        LIGHT_ARRAY7_MODEL_POSITION,       // (x,y,z,1)
        LIGHT_ARRAY7_MODEL_DIRECTION,      // (x,y,z,0)
        LIGHT_ARRAY7_WORLD_POSITION,       // (x,y,z,1)
        LIGHT_ARRAY7_WORLD_DIRECTION,      // (x,y,z,0)
        LIGHT_ARRAY7_AMBIENT,              // (r,g,b,a)
        LIGHT_ARRAY7_DIFFUSE,              // (r,g,b,a)
        LIGHT_ARRAY7_SPECULAR,             // (r,g,b,a)
        LIGHT_ARRAY7_SPOTCUTOFF,           // (angle,cos,sin,exponent)
        LIGHT_ARRAY7_ATTENUATION,          // (const,lin,quad,intensity)

        LIGHT_COUNT,                       // Count of lights currently used

        MAX_TYPES
    };

    RendererConstant(Type eType, void* pID, int iDataCount);
    RendererConstant(const RendererConstant& rRC);
    ~RendererConstant(void);

    // 成员访问,renderer使用他们给图形API传递数据.
    inline Type GetType(void) const;
    inline void* GetID(void) const;
    inline int GetDataCount(void) const;
    inline float* GetData(void) const;

    // 枚举值和字符串之间的映射.
    static const std::string& GetName(Type eType);
    static Type GetType(const std::string& rName);

    // 如果用户实现了自定义数据,则应实现自定义数据的释放过程.
    typedef void (*ReleaseID)(void*);
    static ReleaseID OnReleaseID;

    // 如果用户实现了自定义数据,则应实现自定义数据的拷贝过程.
    // 从而允许拷贝构造函数正确拷贝用户自定义数据.
    typedef void (*CopyID)(void*, void**);
    static CopyID OnCopyID;

private:
    Type m_eType;
    void* m_pID;
    int m_iDataCount;
    float m_afData[16];     // 最大数据存储,避免动态分配

    // 根据类型查找该渲染器常量的名字.
    static std::string ms_StringMap[MAX_TYPES+1];

    // 根据名字查找该渲染器常量的类型.
    static StringHashTable<Type>* ms_pTypeMap;
};

#include "SERendererConstant.inl"

}

#endif
