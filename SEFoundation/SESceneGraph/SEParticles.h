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

#ifndef Swing_Particles_H
#define Swing_Particles_H

#include "SEFoundationLIB.h"
#include "SETriMesh.h"
#include "SEFloatArray.h"

namespace Swing
{

class SECamera;
class SECuller;

// particle's billboard quad.
//
//  1 --------- 2
//    | \     |
//    |   \   |
//    |     \ |
//  0 --------- 3

//----------------------------------------------------------------------------
// Description:基于动态刷新VB的particle system.
// Author:Sun Che
// Date:20090602
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEParticles : public SETriMesh
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    SEParticles(const SEAttributes& rAttr, SEVector3fArray* pLocations,
        SEFloatArray* pSizes);
    virtual ~SEParticles(void);

    // 数据成员.
    SEVector3fArrayPtr Locations;
    SEFloatArrayPtr Sizes;
    float SizeAdjust;

    void SetActiveCount(int iActiveCount);
    inline int GetActiveCount(void) const;

protected:
    SEParticles(void);

    // 所有粒子都是朝向camera的广告牌.
    void GenerateParticles(const SECamera* pCamera);

    // culling.
    virtual void GetUnculledSet(SECuller& rCuller, bool bNoCull);

    // 允许用户指定少于实际最大数量的粒子数用于draw.
    int m_iActiveCount;
};

typedef SESmartPointer<SEParticles> SEParticlesPtr;

#include "SEParticles.inl"

}

#endif
