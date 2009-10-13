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
// ����:IntrRay3Box3f��
// ˵��:
// ����:Sun Che
// ʱ��:20081230
//----------------------------------------------------------------------------
class SE_FOUNDATION_API IntrRay3Box3f
    : public Intersector<float, Vector3f>
{
public:
    IntrRay3Box3f(const Ray3f& rRay, const Box3f& rBox);

    // �������.
    const Ray3f& GetRay(void) const;
    const Box3f& GetBox(void) const;

    // static intersection��ѯ.
    virtual bool Test(void);
    virtual bool Find(void);

    // �ཻ����.
    int GetCount(void) const;
    const Vector3f& GetPoint(int i) const;

private:
    // ������Ƿ��ཻ�Ķ���.
    const Ray3f* m_pRay;
    const Box3f* m_pBox;

    // �ཻ�������Ϣ.
    int m_iCount;
    Vector3f m_aPoint[2];
};

}

#endif