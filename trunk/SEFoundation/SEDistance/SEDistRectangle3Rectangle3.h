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

#ifndef Swing_DistRectangle3Rectangle3_H
#define Swing_DistRectangle3Rectangle3_H

#include "SEFoundationLIB.h"
#include "SEDistance.h"
#include "SERectangle3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// ����:DistRectangle3Rectangle3f��
// ˵��:
// ����:Sun Che
// ʱ��:20090119
//----------------------------------------------------------------------------
class SE_FOUNDATION_API DistRectangle3Rectangle3f
    : public Distance<float, Vector3f>
{
public:
    DistRectangle3Rectangle3f(const Rectangle3f& rRectangle0,
        const Rectangle3f& rRectangle1);

    // �������.
    const Rectangle3f& GetRectangle0(void) const;
    const Rectangle3f& GetRectangle1(void) const;

    // static distance��ѯ.
    virtual float Get(void);
    virtual float GetSquared(void);

    // ����dynamic distance��ѯ��convex function����.
    virtual float Get(float fT, const Vector3f& rVelocity0,
        const Vector3f& rVelocity1);
    virtual float GetSquared(float fT, const Vector3f& rVelocity0,
        const Vector3f& rVelocity1);

private:
    const Rectangle3f* m_pRectangle0;
    const Rectangle3f* m_pRectangle1;
};

}

#endif