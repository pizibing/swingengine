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

#ifndef Swing_FrameBuffer_H
#define Swing_FrameBuffer_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"

namespace Swing
{

class SERenderer;
class SETexture;

//----------------------------------------------------------------------------
// Description:封装渲染目标有关的操作,
//      支持渲染到纹理.
// Author:Sun Che
// Date:20080702
// 更新时间:20090306
// 更新说明:从只支持单一渲染目标,到改为支持多渲染目标(MRT).
//     多渲染目标的数量不能超过当前渲染器能力所允许的最大数量.
//     传入的用作渲染目标的纹理指针数组应由调用者在动态内存中创建,
//     frame buffer负责释放该数组.
//
//     每个纹理需要有同样的纹理尺寸和像素深度,
//     即,允许具有同样像素位宽的不同像素类型的纹理同时使用.
//     DirectX9和OpenGL2都按照该标准要求MRT.
//
//     frame buffer对象支持多个对象嵌套调用,即:
//
//        SEFrameBuffer A,B;
//        A.Enable();
//        rendering code...
//            B.Enable();
//            rendering code...
//            B.Disable();
//        rendering code...
//        A.Disable();
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEFrameBuffer
{
public:
    // 支持MRT后,framebuffer的具体格式由每个target纹理决定,这个枚举没有意义了.
    enum FormatType
    {
        FT_FORMAT_NONE,
        FT_FORMAT_RGB,
        FT_FORMAT_RGBA,
        FT_FORMAT_R32,
        FT_FORMAT_RGBA16,
        FT_FORMAT_RGBA32,
        FT_FORMAT_DEPTH
    };

    enum DepthType
    {
        DT_DEPTH_NONE,
        DT_DEPTH_8,
        DT_DEPTH_16,
        DT_DEPTH_24,
        DT_DEPTH_32
    };

    enum StencilType
    {
        ST_STENCIL_NONE,
        ST_STENCIL_8
    };

    enum BufferingType
    {
        BT_BUFFERED_SINGLE,
        BT_BUFFERED_DOUBLE
    };

    enum MultisamplingType
    {
        MT_SAMPLING_NONE,
        MT_SAMPLING_2,
        MT_SAMPLING_4,
        MT_SAMPLING_8
    };

    // 虚基类,SEFrameBuffer::Create和SEFrameBuffer::Destroy构成工厂函数,
    // 输入纹理apTargets必须是一组SAMPLER_2D目标,frame buffer是一组2D数据区,
    // 用户有责任确保传入的纹理数组中的每个纹理对象都具有相同的width,height,
    // 以及纹理类型,纹理格式.
    // 传入的纹理指针数组必须是由调用者动态创建的,由SEFrameBuffer负责删除.
    static SEFrameBuffer* Create(FormatType eFormat, DepthType eDepth,
        StencilType eStencil, BufferingType eBuffering,
        MultisamplingType eMultisampling, SERenderer* pRenderer,
        int iTCount, SETexture** apTargets);

    static void Destroy(SEFrameBuffer* pBuffer);

    SEFrameBuffer(FormatType eFormat, DepthType eDepth, StencilType eStencil,
        BufferingType eBuffering, MultisamplingType eSampling,
        SERenderer* pRenderer, int iTCount, SETexture** apTargets);

    virtual ~SEFrameBuffer(void);

    inline FormatType GetFormatType(void) const;
    inline DepthType GetDepthType(void) const;
    inline StencilType GetStencilType(void) const;
    inline BufferingType GetBufferingType(void) const;
    inline MultisamplingType GetMultisamplingType(void) const;
    inline SERenderer* GetRenderer(void);
    inline int GetCount(void) const;
    inline SETexture* GetTarget(int i);

    virtual void Enable(void) = 0;   // 由具体渲染器派生类实现
    virtual void Disable(void) = 0;  // 由具体渲染器派生类实现

    // 把指定target的数据从frame buffer复制到texture的系统内存中.
    virtual void CopyToTexture(int i) = 0;  // 由具体渲染器派生类实现

protected:
    // 支持MRT后,framebuffer的具体格式由每个target纹理决定,m_eFormat没有意义了.
    FormatType m_eFormat;
    DepthType m_eDepth;
    StencilType m_eStencil;
    BufferingType m_eBuffering;
    MultisamplingType m_eMultisampling;
    SERenderer* m_pRenderer;   // 当前渲染器

    int m_iCount;
    SETexture** m_apTargets;

    // frame buffer工厂函数声明,每个派生类实现一个Creator和Destroyer,
    // 并且把函数指针赋给以下静态数组成员
    typedef SEFrameBuffer* (*Creator)(FormatType, DepthType, StencilType,
        BufferingType, MultisamplingType, SERenderer*, int, SETexture**);
    typedef void (*Destroyer)(SEFrameBuffer*);

    static Creator ms_aoCreator[];
    static Destroyer ms_aoDestroyer[];
};

#include "SEFrameBuffer.inl"

}

#endif
