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

#ifndef Swing_Frustum3_H
#define Swing_Frustum3_H

#include "SEFoundationLIB.h"
#include "SEVector3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20090115
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEFrustum3f
{
public:
    // 规范正交截投体.设E为原点,R为右向量,U为上向量,D为方向向量.
    // 设r > 0且u > 0,分别为R轴和U轴方向的延展长度.
    // 设n和f为D轴方向的延展长度,且0 < n < f.
    // 近截投面(near plane)上的四角顶点表示为E + s0*r*R + s1*u*U + n*D,
    // 其中 |s0| = |s1| = 1(表示四种选择).
    // 远截投面(far plane)上的四角顶点表示为E + (f/n)*(s0*r*R + s1*u*U) + f*D,
    // 其中 |s0| = |s1| = 1(表示四种选择).

    // 默认值为: E = (0,0,0), R = (1,0,0), U = (0,1,0), D = (0,0,1),
    // RBound = 1, UBound = 1, DMin = 1, DMax = 2.
    SEFrustum3f(void);
    SEFrustum3f(const SEVector3f& rOrigin, const SEVector3f& rRVector,
        const SEVector3f& rUVector, const SEVector3f& rDVector,
        float fRBound, float fUBound, float fDMin, float fDMax);

    // 当RBound,UBound,Dmin,Dmax发生改变时,必须调用Update()函数.
    // DRatio,MTwoUF,MTwoRF将随之改变,因此应在Update()之后访问这三个变量.
    void Update(void);
    float GetDRatio(void) const;
    float GetMTwoUF(void) const;
    float GetMTwoRF(void) const;

    void ComputeVertices(SEVector3f aVertex[8]) const;

    SEVector3f Origin, RVector, UVector, DVector;
    float RBound, UBound, DMin, DMax;

protected:
    // 相关导出数据.
    float m_fDRatio, m_fMTwoUF, m_fMTwoRF;
};

}

#endif
