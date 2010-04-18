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

#ifndef Swing_DistSegment3Segment3_H
#define Swing_DistSegment3Segment3_H

#include "SEFoundationLIB.h"
#include "SEDistance.h"
#include "SESegment3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20090119
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEDistSegment3Segment3f : public SEDistance<float, 
    SEVector3f>
{
public:
    SEDistSegment3Segment3f(const SESegment3f& rSegment0,
        const SESegment3f& rSegment1);

    // 对象访问.
    const SESegment3f& GetSegment0(void) const;
    const SESegment3f& GetSegment1(void) const;

    // static distance查询.
    virtual float Get(void);
    virtual float GetSquared(void);

    // 用于dynamic distance查询的convex function计算.
    virtual float Get(float fT, const SEVector3f& rVelocity0,
        const SEVector3f& rVelocity1);
    virtual float GetSquared(float fT, const SEVector3f& rVelocity0,
        const SEVector3f& rVelocity1);

    // 最近点相关信息.
    float GetSegment0Parameter(void) const;
    float GetSegment1Parameter(void) const;

private:
    const SESegment3f* m_pSegment0;
    const SESegment3f* m_pSegment1;

    // 最近点相关信息.
    float m_fSegment0Parameter;  // closest0 = seg0.origin+param*seg0.direction
    float m_fSegment1Parameter;  // closest1 = seg1.origin+param*seg1.direction
};

}

#endif
