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

#ifndef Swing_TerrainPage_H
#define Swing_TerrainPage_H

#include "SEFoundationLIB.h"
#include "SETriMesh.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 说明:
// 作者:Sun Che
// 时间:20081014
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SETerrainPage : public SETriMesh
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    // size = 2^p + 1, p <= 7 (size = 3, 5, 9, 17, 33, 65, 129)
    SETerrainPage(const SEAttributes& rAttr, int iSize,
        unsigned short* ausHeight, const SEVector2f& rOrigin,
        float fMinElevation, float fMaxElevation, float fSpacing,
        float fUVBias);

    virtual ~SETerrainPage(void);

    // 高度图访问.
    inline int GetSize(void) const;
    inline const unsigned short* GetHeights(void) const;
    inline const SEVector2f& GetOrigin(void) const;
    inline float GetMinElevation(void) const;
    inline float GetMaxElevation(void) const;
    inline float GetSpacing(void) const;

    // 获取高度.
    // 如果不在page中,则返回INFINITY.
    float GetHeight(float fX, float fZ) const;

    // page的顶点纹理坐标可以从VB中获取.
    // bias从该函数获取.
    inline float& UVBias(void);

protected:
    // streaming support
    SETerrainPage(void);
    void InitializeDerivedData(void);

    // tessellation.
    inline float GetX(int iX) const;
    inline float GetZ(int iZ) const;
    inline float GetHeight(int iIndex) const;
    inline float GetTextureCoordinate(int iIndex) const;

    // 高度图相关数据.
    int m_iSize, m_iSizeM1;
    unsigned short* m_ausHeight;
    SEVector2f m_Origin;
    float m_fMinElevation, m_fMaxElevation, m_fSpacing;
    float m_fInvSpacing, m_fTextureSpacing, m_fMultiplier;

    // 纹理坐标的bias.
    float m_fUVBias;
};

typedef SESmartPointer<SETerrainPage> SETerrainPagePtr;
#include "SETerrainPage.inl"

}

#endif
