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

#ifndef Swing_Max8UnimaterialMesh_H
#define Swing_Max8UnimaterialMesh_H

#include "SEVector3.h"
#include "SEVector2.h"
#include "SEColorRGB.h"
#include "SEMaterialState.h"
#include "SETexture.h"
#include "SETriMesh.h"
#include "SEVertexBuffer.h"
#include "SEIndexBuffer.h"
#include "SEDefaultShaderEffect.h"
#include "SEMaterialEffect.h"
#include "SEMaterialTextureEffect.h"
#include "SETextureEffect.h"

//----------------------------------------------------------------------------
// 名称:Max8UnimaterialMesh类
// 说明:使用单一材质的网格.
// 作者:Sun Che
// 时间:20080817
//----------------------------------------------------------------------------
class Max8UnimaterialMesh
{
public:
    Max8UnimaterialMesh(void);
    int& VCount(void);
    Swing::Vector3f*& Vertex(void);
    Swing::Vector3f*& Normal(void);
    int& CCount(void);
    Swing::ColorRGB*& Color(void);
    int& TCount(void);
    Swing::Vector2f*& Texture(void);
    int& FCount(void);
    int*& Face(void);
    int*& CFace(void);
    int*& TFace(void);
    Swing::MaterialStatePtr& MState(void);
    Swing::TexturePtr& TState(void);

    // 每个Max顶点可以有多组UVW坐标.
    // Swing Engine导出器只支持每个顶点一组UV坐标(忽略W分量).
    // 因此任何具备N组UVW坐标的Max顶点都会被拆分复制为N个Swing Engine顶点,
    // 每个带有其中一组UV坐标.
    void DuplicateGeometry(void);
    Swing::TriMesh* ToTriMesh(void);

    class VertexAttr
    {
    public:
        VertexAttr(void);
        bool operator == (const VertexAttr& rAttr) const;
        bool operator < (const VertexAttr& rAttr) const;
        int V, C, T;
    };

private:
    int m_iVCount;
    Swing::Vector3f* m_aVertex;
    Swing::Vector3f* m_aNormal;

    int m_iCCount;
    Swing::ColorRGB* m_aColor;

    int m_iTCount;
    Swing::Vector2f* m_aTexture;

    int m_iFCount;
    int* m_aiFace;
    int* m_aiCFace;
    int* m_aiTFace;

    Swing::MaterialStatePtr m_spSEMaterialState;
    Swing::TexturePtr m_spTState;
};

#endif




