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

#ifndef Swing_PolygonOffsetState_H
#define Swing_PolygonOffsetState_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEGlobalState.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 说明:
// 作者:Sun Che
// 时间:20080701
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEPolygonOffsetState : public SEGlobalState
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;
    SE_DECLARE_INITIALIZE;
    SE_DECLARE_TERMINATE;

public:
    virtual StateType GetStateType(void) const { return POLYGONOFFSET; }

    SEPolygonOffsetState(void);
    virtual ~SEPolygonOffsetState(void);

    // 针对各种多边形渲染填充模式(fill, line, point),设置是否允许offset.
    bool FillEnabled;   // default: false
    bool LineEnabled;   // default: false
    bool PointEnabled;  // default: false

    // offset = Scale*dZ + Bias*r.
    // 其中dZ是相对于多边形屏幕空间区域的深度改变值,
    // r是最小resolvable depth difference.
    // 这些值为负时,多边形距离眼睛更近.
    float Scale;  // default: 0.0
    float Bias;   // default: 0.0
};

typedef SESmartPointer<SEPolygonOffsetState> SEPolygonOffsetStatePtr;

}

#endif
