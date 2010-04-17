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

#ifndef Swing_IntrTriangle2Triangle2_H
#define Swing_IntrTriangle2Triangle2_H

#include "SEFoundationLIB.h"
#include "SEIntersector.h"
#include "SEIntersector1.h"
#include "SETriangle2.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:IntrTriangle2Triangle2f类
// 说明:
// 作者:Sun Che
// 时间:20081223
//----------------------------------------------------------------------------
class SE_FOUNDATION_API IntrTriangle2Triangle2f
    : public Intersector<float, SEVector2f>
{
public:
    IntrTriangle2Triangle2f(const Triangle2f& rTriangle0,
        const Triangle2f& rTriangle1);

    // object access
    const Triangle2f& GetTriangle0(void) const;
    const Triangle2f& GetTriangle1(void) const;

    // static queries
    virtual bool Test(void);
    virtual bool Find(void);

    // dynamic queries
    virtual bool Test(float fTMax, const SEVector2f& rVelocity0,
        const SEVector2f& rVelocity1);
    virtual bool Find(float fTMax, const SEVector2f& rVelocity0,
        const SEVector2f& rVelocity1);

    // information about the intersection set
    int GetCount(void) const;
    const SEVector2f& GetPoint(int i) const;

private:
    static int OnWhichSide(const SEVector2f aV[3],
        const SEVector2f& rP, const SEVector2f& rD);

    static void ClipConvexPolygonAgainstLine(const SEVector2f& rN,
        float fC, int& riCount, SEVector2f aV[6]);

    enum ProjectionMap
    {
        M21,  // 2 vertices map to min, 1 vertex maps to max
        M12,  // 1 vertex maps to min, 2 vertices map to max
        M11   // 1 vertex maps to min, 1 vertex maps to max
    };

    class Configuration
    {
    public:
        ProjectionMap Map;  // how vertices map to the projection interval
        int Index[3];       // the sorted indices of the vertices
        float Min, Max;      // the interval is [min,max]
    };

    void ComputeTwo(Configuration& rCfg, const SEVector2f aV[3],
        const SEVector2f& rD, int iI0, int iI1, int iI2);

    void ComputeThree(Configuration& rCfg, const SEVector2f aV[3],
        const SEVector2f& rD, const SEVector2f& rP);

    static bool NoIntersect(const Configuration& rCfg0,
        const Configuration& rCfg1, float fTMax, float fSpeed, int& riSide,
        Configuration& rTCfg0, Configuration& rTCfg1, float& rfTFirst,
        float& rfTLast);

    static void GetIntersection(const Configuration& rCfg0,
        const Configuration& rCfg1, int iSide, const SEVector2f aV0[3],
        const SEVector2f aV1[3], int& riCount, SEVector2f aVertex[6]);

    // the objects to intersect
    const Triangle2f* m_pTriangle0;
    const Triangle2f* m_pTriangle1;

    // information about the intersection set
    int m_iCount;
    SEVector2f m_aPoint[6];
};

}

#endif
