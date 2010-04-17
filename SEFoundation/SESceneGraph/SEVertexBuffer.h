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

#ifndef Swing_VertexBuffer_H
#define Swing_VertexBuffer_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEObject.h"
#include "SEAttributes.h"
#include "SEBindable.h"
#include "SEColorRGB.h"
#include "SEColorRGBA.h"
#include "SEVector2.h"
#include "SEVector3.h"
#include "SEVector4.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:顶点缓冲区类
// 说明:VB原始数据保存在系统内存中,
//      在显存中可以存在多个该VB的实例,由具体图形API负责创建,
//      每个显存实例都是该VB数据的子集,供某effect使用.
// 作者:Sun Che
// 时间:20080319
//----------------------------------------------------------------------------
class SE_FOUNDATION_API VertexBuffer : public SEObject, public Bindable
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    VertexBuffer(const Attributes& rAttributes, int iVertexCount);
    VertexBuffer(const VertexBuffer* pVBuffer);
    virtual ~VertexBuffer(void);

    // 获取缓冲区的顶点格式.
    inline const Attributes& GetAttributes(void) const;

    // 返回每个顶点大小,单位是"float",
    // 字节数大小用GetVertexSize()*sizeof(float)获得.
    inline int GetVertexSize(void) const;

    // 获取缓冲区的顶点个数
    inline int GetVertexCount(void) const;

    // 访问positions.
    float* PositionTuple(int i);
    const float* PositionTuple(int i) const;

    // 访问normals.
    float* NormalTuple(int i);
    const float* NormalTuple(int i) const;

    // 访问colors.
    float* ColorTuple(int iUnit, int i);
    const float* ColorTuple(int iUnit, int i) const;

    // 访问texture coordinates.
    float* TCoordTuple(int iUnit, int i);
    const float* TCoordTuple(int iUnit, int i) const;

    // 直接访问顶点缓冲区数据,channel count是float元素总数,
    // 缓冲区总字节数为GetChannelCount()*sizeof(float).
    inline int GetChannelCount(void) const;
    inline float* GetData(void);
    inline const float* GetData(void) const;

    // 没有范围检测,用户必须确保所要访问的顶点属性存在且不超过channel范围.
    Vector3f& Position3(int i);
    Vector3f Position3(int i) const;
    Vector3f& Normal3(int i);
    Vector3f Normal3(int i) const;
    ColorRGB& Color3(int iUnit, int i);
    ColorRGB Color3(int iUnit, int i) const;
    ColorRGBA& Color4(int iUnit, int i);
    ColorRGBA Color4(int iUnit, int i) const;
    float& TCoord1(int iUnit, int i);
    float TCoord1(int iUnit, int i) const;
    SEVector2f& TCoord2(int iUnit, int i);
    SEVector2f TCoord2(int iUnit, int i) const;
    Vector3f& TCoord3(int iUnit, int i);
    Vector3f TCoord3(int iUnit, int i) const;
    Vector4f& TCoord4(int iUnit, int i);
    Vector4f TCoord4(int iUnit, int i) const;

    // 用来根据当前VB创建一个与vertex program inputs兼容的数组数据,
    // rCompatible保存该兼容数组,如果rCompatible传入空指针,则此函数动态为其分配内存,
    // 调用者有责任删除该内存,也可以传入非空指针,前提是你已经知道该数据区大小.
    //
    // bPackARGB目前针对DirectX9,因为DirectX9需要ARGB(8-bit,共32-bit)颜色通道,
    // 而不是OpenGL的[0,1]区间浮点值颜色通道(32-bit,共128-bit),
    // DirectX10也支持[0,1]区间浮点值颜色通道(32-bit,共128-bit).
    // 因此bPackARGB为true时为DirectX9,否则为OpenGL/DirectX10/software renderers,
    // 如果今后还需要支持其他格式,则扩展此标志为多状态标志.
    void BuildCompatibleArray(const Attributes& rIAttributes, bool bPackARGB,
        int& rChannels, float*& rCompatible) const;

    // 用户可能想设置顶点的"active count",使用此函数来设置,
    // 函数没有改变实际数据存储,只是设置m_iVertexCount,
    // 用户有责任保存实际顶点数目,并在一系列操作完成后恢复实际顶点数目,
    // active count不能超过实际顶点数目.
    inline void SetVertexCount(int iVCount);

private:
    // streaming support
    VertexBuffer(void);

    // 顶点属性.
    Attributes m_Attributes;

    // 每个顶点大小,单位是"float".
    int m_iVertexSize;

    // 顶点数.
    int m_iVertexCount;

    // 顶点缓冲区数据.
    int m_iChannelCount;  // = m_iVertexCount*m_iVertexSize
    float* m_pChannel;
};

typedef SESmartPointer<VertexBuffer> VertexBufferPtr;

#include "SEVertexBuffer.inl"

}

#endif
