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

#ifndef Swing_BillBoardNode_H
#define Swing_BillBoardNode_H

#include "SEFoundationLIB.h"
#include "SENode.h"
#include "SECamera.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 说明:
// 作者:Sun Che
// 时间:20090603
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEBillboardNode : public SENode
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    // billboard的模型空间up轴(0,1,0)被用来当作billboard的旋转轴.

    SEBillboardNode(SECamera* pCamera = 0);
    virtual ~SEBillboardNode(void);

    // billboard当前所对齐的camera.
    inline void AlignTo(SECamera* pCamera);

protected:
    // geometric updates
    virtual void UpdateWorldData(double dAppTime);

    SESmartPointer<SECamera> m_spCamera;
};

typedef SESmartPointer<SEBillboardNode> SEBillboardNodePtr;

#include "SEBillboardNode.inl"

}

#endif
