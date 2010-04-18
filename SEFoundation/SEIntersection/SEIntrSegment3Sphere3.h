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

#ifndef Swing_IntrSegment3Sphere3_H
#define Swing_IntrSegment3Sphere3_H

#include "SEFoundationLIB.h"
#include "SEIntersector.h"
#include "SESegment3.h"
#include "SESphere3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20081220
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEIntrSegment3Sphere3f : public SEIntersector<float, 
    SEVector3f>
{
public:
    SEIntrSegment3Sphere3f(const SESegment3f& rSegment, const SESphere3f& 
        rSphere);

    // 对象访问.
    const SESegment3f& GetSegment(void) const;
    const SESphere3f& GetSphere(void) const;

    // test-intersection查询.
    virtual bool Test(void);

    // find-intersection查询.
    virtual bool Find(void);
    int GetCount(void) const;
    const SEVector3f& GetPoint(int i) const;
    float GetSegmentT(int i) const;

    // dynamic test-intersection查询.
    virtual bool Test(float fTMax, const SEVector3f& rVelocity0,
        const SEVector3f& rVelocity1);

    // dynamic find-intersection查询.
    virtual bool Find(float fTMax, const SEVector3f& rVelocity0,
        const SEVector3f& rVelocity1);

    float ZeroThreshold;  // default = SEMath<float>::ZERO_TOLERANCE

private:
    // 待检查对象.
    const SESegment3f* m_pSegment;
    const SESphere3f* m_pSphere;

    // 相交集相关信息.
    int m_iCount;
    SEVector3f m_aPoint[2];
    float m_afSegmentT[2];
};

}

#endif
