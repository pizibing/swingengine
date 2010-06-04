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

#ifndef Swing_DistLine3Box3_H
#define Swing_DistLine3Box3_H

#include "SEFoundationLIB.h"
#include "SEDistance.h"
#include "SELine3.h"
#include "SEBox3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20090113
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEDistLine3Box3f : public SEDistance<float, 
    SEVector3f>
{
public:
    SEDistLine3Box3f(const SELine3f& rLine, const SEBox3f& rBox);

    // �������.
    const SELine3f& GetLine(void) const;
    const SEBox3f& GetBox(void) const;

    // static distance��ѯ.
    virtual float Get(void);
    virtual float GetSquared(void);

    // ����dynamic distance��ѯ��convex function����.
    virtual float Get(float fT, const SEVector3f& rVelocity0,
        const SEVector3f& rVelocity1);
    virtual float GetSquared(float fT, const SEVector3f& rVelocity0,
        const SEVector3f& rVelocity1);

    // ��������㴦��ֱ�߲���.
    // ray-box��segment-box��distance����Ҳʹ���������.
    float GetLineParameter(void) const;

private:
    void Face(int i0, int i1, int i2, SEVector3f& rPnt,
        const SEVector3f& rDir, const SEVector3f& rPmE,
        float& rfSqrDistance);

    void CaseNoZeros(SEVector3f& rPnt, const SEVector3f& rDir,
        float& rfSqrDistance);

    void Case0(int i0, int i1, int i2, SEVector3f& rPnt,
        const SEVector3f& rDir, float& rfSqrDistance);

    void Case00(int i0, int i1, int i2, SEVector3f& rPnt,
        const SEVector3f& rDir, float& rfSqrDistance);

    void Case000(SEVector3f& rPnt, float& rfSqrDistance);

    const SELine3f* m_pLine;
    const SEBox3f* m_pBox;
    float m_fLParam;
};

}

#endif