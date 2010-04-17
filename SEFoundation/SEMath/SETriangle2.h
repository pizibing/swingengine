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

#ifndef Swing_Triangle2_H
#define Swing_Triangle2_H

#include "SEFoundationLIB.h"
#include "SEVector2.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:二维空间三角形类
// 说明:
// 作者:Sun Che
// 时间:20081223
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Triangle2f
{
public:
    Triangle2f(void);  // 未初始化
    Triangle2f(const SEVector2f& rV0, const SEVector2f& rV1, const SEVector2f& rV2);
    Triangle2f(const SEVector2f aV[3]);

    // 三角形到点Q的距离.
    float GetDistance(const SEVector2f& rQ) const;

    SEVector2f V[3];
};

}

#endif
