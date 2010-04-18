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

#ifndef Swing_Box3_H
#define Swing_Box3_H

#include "SEFoundationLIB.h"
#include "SEVector3.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:oriented bounding box
// Author:Sun Che
// Date:20070705
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEBox3f
{
public:
    SEBox3f(void);
    SEBox3f(const SEVector3f& rCenter, const SEVector3f* aAxis, 
        const float* afExtent);
    SEBox3f(const SEVector3f& rCenter, const SEVector3f& rAxis0, 
        const SEVector3f& rAxis1, const SEVector3f& rAxis2, float fExtent0, 
        float fExtent1, float fExtent2);

    void ComputeVertices(SEVector3f aVertex[8]) const;

    SEVector3f Center;  // 盒子中心
    SEVector3f Axis[3];  // 规范正交基
    float Extent[3];  // 半长,半宽,半高,均非负
};

}

#endif