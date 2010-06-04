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

#ifndef Swing_DistRay3Rectangle3_H
#define Swing_DistRay3Rectangle3_H

#include "SEFoundationLIB.h"
#include "SEDistance.h"
#include "SERectangle3.h"
#include "SERay3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20090117
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEDistRay3Rectangle3f : public SEDistance<float, 
    SEVector3f>
{
public:
    SEDistRay3Rectangle3f(const SERay3f& rRay, const SERectangle3f& 
        rRectangle);

    // �������.
    const SERay3f& GetRay(void) const;
    const SERectangle3f& GetRectangle(void) const;

    // static distance��ѯ.
    virtual float Get(void);
    virtual float GetSquared(void);

    // ����dynamic distance��ѯ��convex function����.
    virtual float Get(float fT, const SEVector3f& rVelocity0,
        const SEVector3f& rVelocity1);
    virtual float GetSquared(float fT, const SEVector3f& rVelocity0,
        const SEVector3f& rVelocity1);

    // ����������Ϣ.
    float GetRayParameter(void) const;
    float GetRectangleCoordinate(int i) const;

private:
    const SERay3f* m_pRay;
    const SERectangle3f* m_pRectangle;

    // ����������Ϣ.
    float m_fRayParameter;   // closest0 = ray.origin+param*ray.direction
    float m_afRectCoord[2];  // closest1 = rect.center+param0*rect.dir0+
                            //            param1*rect.dir1
};

}

#endif