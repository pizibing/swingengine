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

#ifndef Swing_IVector2_H
#define Swing_IVector2_H

#include "SEFoundationLIB.h"
#include "SETIVector.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:IVector2类
// 说明:
// 作者:Sun Che
// 时间:20081202
//----------------------------------------------------------------------------
class SEIVector2 : public SETIVector<2>
{
public:
    // construction
    SEIVector2(void);
    SEIVector2(const SEIVector2& rV);
    SEIVector2(const SETIVector<2>& rV);
    SEIVector2(const SE_Int64& riX,  const SE_Int64& riY);

    // member access
    SE_Int64 X(void) const;
    SE_Int64& X(void);
    SE_Int64 Y(void) const;
    SE_Int64& Y(void);

    // assignment
    SEIVector2& operator = (const SEIVector2& rV);
    SEIVector2& operator = (const SETIVector<2>& rV);

    // returns Dot(this, V)
    SE_Int64 Dot(const SEIVector2& rV) const;

    // returns (y, -x)
    SEIVector2 Perp(void) const;

    // returns Cross((x, y, 0), (V.x, V.y, 0)) = x*V.y - y*V.x
    SE_Int64 DotPerp(const SEIVector2& rV) const;

protected:
    using SETIVector<2>::m_aiTuple;
};

#include "SEIVector2.inl"

}

#endif
