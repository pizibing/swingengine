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

#ifndef Swing_Box2_H
#define Swing_Box2_H

#include "SEFoundationLIB.h"
#include "SEVector2.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:2维OBB类
// 说明:oriented bounding box
// 作者:Sun Che
// 时间:20090113
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEBox2f
{
public:
    SEBox2f(void);
    SEBox2f(const SEVector2f& rCenter, const SEVector2f* aAxis,
        const float* afExtent);
    SEBox2f(const SEVector2f& rCenter, const SEVector2f& rAxis0,
        const SEVector2f& rAxis1, float fExtent0, float fExtent1);

    void ComputeVertices(SEVector2f aVertex[4]) const;

    SEVector2f Center;  // 盒子中心
    SEVector2f Axis[2];  // 规范正交基
    float Extent[2];  // 半长,半宽,均非负
};

}

#endif
