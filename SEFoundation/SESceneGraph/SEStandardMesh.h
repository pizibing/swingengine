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

#ifndef Swing_StandardMesh_H
#define Swing_StandardMesh_H

#include "SEFoundationLIB.h"
#include "SETriMesh.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:StandardMesh类
// 说明:	
// 作者:Sun Che
// 时间:20081015
//----------------------------------------------------------------------------
class SE_FOUNDATION_API StandardMesh
{
public:
    StandardMesh(const Attributes& rAttr, bool bInside = false,
        const Transformation* pXFrm = 0);
    ~StandardMesh(void);

    void SetTransformation(const Transformation& rXFrm);
    const Transformation& GetTransformation(void) const;

    // 各种标准网格mesh. 
    // 每个mesh以(0,0,0)为中心,up-axis为(0,0,-1).其他axes为(1,0,0)和(0,1,0).
    // 应用程序可以对mesh进行变换.

    TriMesh* Rectangle(int iXSamples, int iYSamples, float fXExtent,
        float fYExtent);

    TriMesh* Disk(int iShellSamples, int iRadialSamples, float fRadius);

    TriMesh* Box(float fXExtent, float fYExtent, float fZExtent);

    TriMesh* Cylinder(int iAxisSamples, int iRadialSamples, float fRadius,
        float fHeight, bool bOpen);

    TriMesh* Sphere(int iZSamples, int iRadialSamples, float fRadius);

    TriMesh* Torus(int iCircleSamples, int iRadialSamples,
        float fOuterRadius, float fInnerRadius);

    TriMesh* Cone(int iRadialSamples, float fRadius, float fHeight);

    // 各种platonic多面体, 内接在一个以(0,0,0)为中心的单位球中.
    TriMesh* Tetrahedron(void);  // 四面体
    TriMesh* Hexahedron(void);   // 六面体
    TriMesh* Octahedron(void);   // 八面体
    TriMesh* Dodecahedron(void); // 十二面体
    TriMesh* Icosahedron(void);  // 二十面体

private:
    void CreatePlatonicNormals(VertexBuffer* pVBuffer);
    void CreatePlatonicUVs(VertexBuffer* pVBuffer);
    void ReverseTriangleOrder(int iTCount, int* aiIndex);
    void TransformData(VertexBuffer* pVBuffer);

    Attributes m_Attr;
    Transformation m_XFrm;
    bool m_bInside;
    VertexBuffer* m_pVBuffer;
    IndexBuffer* m_pIBuffer;
};

}

#endif
