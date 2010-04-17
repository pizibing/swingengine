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

#ifndef Swing_IntrTriangle3Triangle3_H
#define Swing_IntrTriangle3Triangle3_H

#include "SEFoundationLIB.h"
#include "SEIntersector.h"
#include "SETriangle3.h"
#include "SELine3.h"
#include "SEPlane3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 名称:IntrTriangle3Triangle3f类
// 说明:
// 作者:Sun Che
// 时间:20081223
//----------------------------------------------------------------------------
class SE_FOUNDATION_API IntrTriangle3Triangle3f
    : public Intersector<float, SEVector3f>
{
public:
    IntrTriangle3Triangle3f(const SETriangle3f& rTriangle0,
        const SETriangle3f& rTriangle1);

    // object access
    const SETriangle3f& GetTriangle0(void) const;
    const SETriangle3f& GetTriangle1(void) const;

    bool ReportCoplanarIntersections;  // default 'true'

    // static queries
    virtual bool Test(void);
    virtual bool Find(void);

    // dynamic queries
    virtual bool Test(float fTMax, const SEVector3f& rVelocity0,
        const SEVector3f& rVelocity1);
    virtual bool Find(float fTMax, const SEVector3f& rVelocity0,
        const SEVector3f& rVelocity1);

    // information about the intersection set
    int GetCount(void) const;
    const SEVector3f& GetPoint(int i) const;

private:
    static void ProjectOntoAxis(const SETriangle3f& rTri,
        const SEVector3f& rAxis, float& rfMin, float& rfMax);

    static void TrianglePlaneRelations(const SETriangle3f& rTriangle,
        const SEPlane3f& rPlane, float afDistance[3], int aiSign[3],
        int& riPositive, int& riNegative, int& riZero);

    static void GetInterval(const SETriangle3f& rTriangle,
        const SELine3f& rLine, const float afDistance[3],
        const int aiSign[3], float afParam[2]);

    bool GetCoplanarIntersection(const SEPlane3f& rPlane,
        const SETriangle3f& rTri0, const SETriangle3f& rTri1);

    static bool TestOverlap(float fTMax, float fSpeed, float fUMin, 
        float fUMax, float fVMin, float fVMax, float& rfTFirst, 
        float& rfTLast);

    bool TestOverlap(const SEVector3f& rAxis, float fTMax,
        const SEVector3f& rVelocity, float& rfTFirst, float& rfTLast);

    enum ProjectionMap
    {
        M2, M11,                // lines
        M3, M21, M12, M111,     // triangles
        M44, M2_2, M1_1         // boxes
    };

    enum ContactSide
    {
        CS_LEFT,
        CS_RIGHT,
        CS_NONE
    };

    class SE_FOUNDATION_API Configuration
    {
    public:
        ProjectionMap Map;  // how vertices map to the projection interval
        int Index[8];       // the sorted indices of the vertices
        float Min, Max;      // the interval is [min,max]
    };

    static void ProjectOntoAxis(const SETriangle3f& rTri,
        const SEVector3f& rAxis, Configuration& rCfg);

    bool FindOverlap(float fTMax, float fSpeed, const Configuration& rUC, 
        const Configuration& rVC, ContactSide& reSide, Configuration& rTUC, 
        Configuration& rTVC, float& rfTFirst, float& rfTLast);

    bool FindOverlap(const SEVector3f& rAxis, float fTMax,
        const SEVector3f& rVelocity, ContactSide& reSide,
        Configuration& rTCfg0, Configuration& rTCfg1, float& rfTFirst,
        float& rfTLast);

    void FindContactSet(const SETriangle3f& rTri0,
        const SETriangle3f& rTri1, ContactSide& reSide,
        Configuration& rCfg0, Configuration& rCfg1);

    void GetEdgeEdgeIntersection(const SEVector3f& rU0,
        const SEVector3f& rU1, const SEVector3f& rV0,
        const SEVector3f& rV1);

    // the objects to intersect
    const SETriangle3f* m_pTriangle0;
    const SETriangle3f* m_pTriangle1;

    // information about the intersection set
    int m_iCount;
    SEVector3f m_aPoint[6];
};

}

#endif
