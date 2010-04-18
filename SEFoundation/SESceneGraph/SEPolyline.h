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

#ifndef Swing_Polyline_H
#define Swing_Polyline_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEGeometry.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20080808
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEPolyline : public SEGeometry
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    SEPolyline(SEVertexBuffer* pVBuffer, bool bClosed, bool bContiguous);
    virtual ~SEPolyline(void);

    void SetActiveCount(int iActiveCount);
    inline int GetActiveCount(void) const;

    void SetClosed(bool bClosed);
    inline bool GetClosed(void) const;

    void SetContiguous(bool bContiguous);
    inline bool GetContiguous(void) const;

protected:
    SEPolyline(void);
    void SetGeometryType(void);

    // 允许应用程序指定少于实际顶点数的顶点子集用于渲染.
    int m_iActiveCount;

    // 线段的开放与闭合,连续与断开.
    bool m_bClosed, m_bContiguous;
};

typedef SESmartPointer<SEPolyline> SEPolylinePtr;

#include "SEPolyline.inl"

}

#endif
