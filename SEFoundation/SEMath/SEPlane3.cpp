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

#include "SEFoundationPCH.h"
#include "SEPlane3.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEPlane3f::SEPlane3f()
{
}
//----------------------------------------------------------------------------
SEPlane3f::SEPlane3f(const SEPlane3f& rPlane)
    : Normal(rPlane.Normal)
{
    Constant = rPlane.Constant;
}
//----------------------------------------------------------------------------
SEPlane3f::SEPlane3f(const SEVector3f& rNormal, float fConstant)
    : Normal(rNormal)
{
    Constant = fConstant;
}
//----------------------------------------------------------------------------
SEPlane3f::SEPlane3f(const SEVector3f& rNormal, const SEVector3f& rP0)
    : Normal(rNormal)
{
    Constant = rNormal.Dot(rP0);
}
//----------------------------------------------------------------------------
SEPlane3f::SEPlane3f(const SEVector3f& rP0, const SEVector3f& rP1, const 
    SEVector3f& rP2)
{
    SEVector3f Vec1 = rP1 - rP0;
    SEVector3f Vec2 = rP2 - rP0;
    Normal = Vec1.Cross(Vec2);
    Normal.Normalize();
    Constant = Normal.Dot(rP0);
}
//----------------------------------------------------------------------------
SEPlane3f& SEPlane3f::operator=(const SEPlane3f& rPlane)
{
    Normal = rPlane.Normal;
    Constant = rPlane.Constant;
    
    return *this;
}
//----------------------------------------------------------------------------