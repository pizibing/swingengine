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
#include "SEEffect.h"
#include "SEGeometry.h"
#include "SERenderer.h"
#include "SEUnculledSet.h"

using namespace Swing;

SE_IMPLEMENT_RTTI(Swing, SEEffect, SEAdvancedObject);
SE_IMPLEMENT_STREAM(SEEffect);
SE_IMPLEMENT_DEFAULT_STREAM(SEEffect, SEAdvancedObject);
SE_IMPLEMENT_DEFAULT_NAME_ID(SEEffect, SEAdvancedObject);

//SE_REGISTER_STREAM(SEEffect);

//----------------------------------------------------------------------------
SEEffect::SEEffect()
{
}
//----------------------------------------------------------------------------
SEEffect::~SEEffect()
{
}
//----------------------------------------------------------------------------
void SEEffect::Draw(SERenderer* pRenderer, SESpatial*, int iMin, int iMax, 
    SEUnculledObject* pVisibleSet)
{
    // global effect的默认渲染函数.
    // 实际上,只是将该effect作为local effect临时添加给每个待渲染geometry对象.
    for( int i = iMin; i <= iMax; i++ )
    {
        if( pVisibleSet[i].IsRenderable() )
        {
            SEGeometry* pGeometry = (SEGeometry*)pVisibleSet[i].Object;
            pGeometry->AttachEffect(this);
            pRenderer->Draw(pGeometry);
            pGeometry->DetachEffect(this);
        }
    }
}
//----------------------------------------------------------------------------
void SEEffect::OnUpdateData(void*)
{
}
//----------------------------------------------------------------------------
void SEEffect::LoadResources(SERenderer*, SEGeometry*)
{
}
//----------------------------------------------------------------------------
void SEEffect::ReleaseResources(SERenderer*, SEGeometry*)
{
}
//----------------------------------------------------------------------------
