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

#ifndef Swing_IntrRay3Box3_H
#define Swing_IntrRay3Box3_H

#include "SEFoundationLIB.h"
#include "SEIntersector.h"
#include "SERay3.h"
#include "SEIntrLine3Box3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20081230
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEIntrRay3Box3f : public SEIntersector<float, 
    SEVector3f>
{
public:
    SEIntrRay3Box3f(const SERay3f& rRay, const SEBox3f& rBox);

    // 对象访问.
    const SERay3f& GetRay(void) const;
    const SEBox3f& GetBox(void) const;

    // static intersection查询.
    virtual bool Test(void);
    virtual bool Find(void);

    // 相交集合.
    int GetCount(void) const;
    const SEVector3f& GetPoint(int i) const;

private:
    // 待检查是否相交的对象.
    const SERay3f* m_pRay;
    const SEBox3f* m_pBox;

    // 相交集相关信息.
    int m_iCount;
    SEVector3f m_aPoint[2];
};

}

#endif
