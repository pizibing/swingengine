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

#ifndef Swing_Attributes_H
#define Swing_Attributes_H

#include "SEFoundationLIB.h"
#include "SESystem.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:属性类
// 说明:用于指定VB顶点格式时类似于FVF,此外还用于指定shader input output参数属性,
//      offset为指定数据在VertexBuffer中的float个数偏移量
// 作者:Sun Che
// 时间:20080312
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Attributes
{
public:
    Attributes(void);
    ~Attributes(void);

    // 当前支持的顶点属性:
    //    p  = position
    //         3或4个分量 (xyz,xyzw)
    //    n  = normal vector
    //         3或4个分量 (xyz,xyzw)
    //    ci = color
    //         1至4个分量 (r,rg,rgb,rgba)
    //    ti = texture coordinate
    //         1至4个分量 (s,st,str,strq)
    // 所有属性的内部组织顺序:
    // p, n, c0, c1, ..., t0, t1, ...

    void SetPositionChannels(int iPChannels);
    void SetNormalChannels(int iNChannels);
    void SetColorChannels(int iUnit, int iCChannels);
    void SetTCoordChannels(int iUnit, int iTChannels);

    // 获取所有属性的float通道总数
    inline int GetChannelCount(void) const;

    // 访问position信息
    inline int GetPositionOffset(void) const;
    inline int GetPositionChannels(void) const;
    inline bool HasPosition(void) const;

    // 访问normal信息
    inline int GetNormalOffset(void) const;
    inline int GetNormalChannels(void) const;
    inline bool HasNormal(void) const;

    // 访问color信息
    inline int GetMaxColors(void) const; // 几组color
    int GetColorOffset(int iUnit) const;
    int GetColorChannels(int iUnit) const;
    bool HasColor(int iUnit) const;

    // 访问texture coordinate信息.
    inline int GetMaxTCoords(void) const; // 几组texture coord
    int GetTCoordOffset(int iUnit) const;
    int GetTCoordChannels(int iUnit) const;
    bool HasTCoord(int iUnit) const;

    // 对vertex program outputs和pixel program inputs进行比较
    bool Matches(const Attributes& rAttributes, bool bIncludeP, bool bIncludeN,
        bool bIncludeC, bool bIncludeT) const;

    // 对vertex buffer的vertex format和vertex program input的vertex format进行比较
    bool operator == (const Attributes& rAttributes) const;
    bool operator != (const Attributes& rAttributes) const;

private:
    void UpdateOffsets(void);

    // 所有属性的float通道总数
    int m_iChannelCount;

    // positions
    int m_iPositionOffset;
    int m_iPositionChannels;

    // normals
    int m_iNormalOffset;
    int m_iNormalChannels;

    // colors
    std::vector<int> m_ColorOffset;
    std::vector<int> m_ColorChannels;

    // texture coordinates
    std::vector<int> m_TCoordOffset;
    std::vector<int> m_TCoordChannels;
};

#include "SEAttributes.inl"

}

#endif
