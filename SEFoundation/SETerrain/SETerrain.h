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

#ifndef Swing_Terrain_H
#define Swing_Terrain_H

#include "SEFoundationLIB.h"
#include "SENode.h"
#include "SETerrainPage.h"

namespace Swing
{

class Camera;

//----------------------------------------------------------------------------
// 名称:Terrain类
// 说明:没有进行LOD.	
// 作者:Sun Che
// 时间:20081014
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Terrain : public Node
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    Terrain(const char* acHeightName, const char* acImageName,
        const Attributes& rAttr, Camera* pCamera, float fUVBias,
        ColorRGBA* pBorderColor);

    virtual ~Terrain(void);

    int GetRowCount(void) const;
    int GetColCount(void) const;
    int GetSize(void) const;
    float GetMinElevation(void) const;
    float GetMaxElevation(void) const;
    float GetSpacing(void) const;
    float& UVBias(void);
    ColorRGBA& BorderColor(void);
    void SetCamera(Camera* pCamera);

    // page管理.
    TerrainPage* GetPage(int iRow, int iCol);
    TerrainPage* GetCurrentPage(float fX, float fZ) const;
    float GetHeight(float fX, float fZ) const;

    // 允许一个page被替换掉.
    // 代码装载一个新page.
    // 然后返回旧有page,从而允许应用程序cache旧有page,并在短期内重新使用它.
    TerrainPagePtr ReplacePage(int iRow, int iCol, const char* acHeightName,
        const char* acHeightSuffix, const char* acImageName,
        const char* acImageSuffix);

    TerrainPagePtr ReplacePage(int iRow, int iCol, TerrainPage* pNewPage);

    // 更新terrain pages的active set.
    void OnCameraMotion(void);

protected:
    // streaming support
    Terrain(void);

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
    TerrainPagePtr** m_aaspPage;  // 第1维是row,第2维是col

    // 包含camera的当前page.
    int m_iCameraRow, m_iCameraCol;
    SmartPointer<Camera> m_spCamera;

    // texture参数.
    float m_fUVBias;
    ColorRGBA m_BorderColor;
};

typedef SmartPointer<Terrain> TerrainPtr;
#include "SETerrain.inl"

}

#endif
