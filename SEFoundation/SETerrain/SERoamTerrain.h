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

#ifndef Swing_RoamTerrain_H
#define Swing_RoamTerrain_H

#include "SEFoundationLIB.h"
#include "SENode.h"
#include "SECuller.h"
#include "SERoamTerrainPage.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:ROAM地形对象类
// 说明:管理RoamTerrainPage类,RoamTerrain对象构成一个完整地形,
//      注意相邻的RoamTerrainPage之间需要进行缝合,
//      否则衔接处将可能产生T-junction.
// 作者:Sun Che
// 时间:20080104
//----------------------------------------------------------------------------
class SE_FOUNDATION_API RoamTerrain : public Node
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    RoamTerrain(const char* acHeightName, const char* acImageName,
        const Attributes& rAttr, Camera* pCamera, float fUVBias,
        SEColorRGBA* pBorderColor);

    virtual ~RoamTerrain(void);

    inline int GetRowCount(void) const;
    inline int GetColCount(void) const;
    inline int GetSize(void) const;
    inline float GetMinElevation(void) const;
    inline float GetMaxElevation(void) const;
    inline float GetSpacing(void) const;
    inline float& UVBias(void);
    inline SEColorRGBA& BorderColor(void);
    inline void SetCamera(Camera* pCamera);

    inline int GetPoolSize(void) const;
    inline int GetPatchSize(void) const;
    inline int GetSplitLevel(void) const;
    inline int GetVarianceLevel(void) const;

    void SetLod(bool bLod);
    inline bool GetLod(void) const;

    // page管理.
    RoamTerrainPage* GetPage(int iRow, int iCol);
    RoamTerrainPage* GetCurrentPage(float fX, float fZ) const;
    float GetHeight(float fX, float fZ) const;

    // 允许一个page被替换掉.
    // 代码把旧有page解除缝合,装载一个新page并重新缝合.
    // 然后返回旧有page,从而允许应用程序cache旧有page,并在短期内重新使用它.
    RoamTerrainPagePtr ReplacePage(int iRow, int iCol, const char* acHeightName,
        const char* acHeightSuffix, const char* acImageName,
        const char* acImageSuffix);

    RoamTerrainPagePtr ReplacePage(int iRow, int iCol, RoamTerrainPage* pNewPage);

    // LOD入口函数.
    void Simplify(Culler& rCuller);

protected:
    // streaming support
    RoamTerrain(void);

    void LoadHeader(const char* acHeightName);
    void LoadPage(int iRow, int iCol, const char* acHeightName,
        const char* acHeightSuffix, const char* acImageName,
        const char* acImageSuffix);

    // page所用VB的attribute.
    Attributes m_Attr;

    // page信息.
    int m_iRows, m_iCols;
    int m_iSize;
    float m_fMinElevation, m_fMaxElevation, m_fSpacing;
    std::vector<std::vector<RoamTerrainPagePtr> > m_Pages;

    // ROAM相关page信息.
    int m_iPoolSize;
    int m_iPatchSize;
    int m_iSplitLevel;
    int m_iVarianceLevel; // 最小为2

    // LOD状态.
    bool m_bLod;

    // 包含camera的当前page.
    int m_iCameraRow, m_iCameraCol;
    SESmartPointer<Camera> m_spCamera;

    // texture参数.
    float m_fUVBias;
    SEColorRGBA m_BorderColor;
};

typedef SESmartPointer<RoamTerrain> RoamTerrainPtr;
#include "SERoamTerrain.inl"

}

#endif