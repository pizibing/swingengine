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

#ifndef Swing_Effect_H
#define Swing_Effect_H

#include "SEFoundationLIB.h"
#include "SEPlatforms.h"
#include "SEObject.h"

namespace Swing
{

class Spatial;
class Geometry;
class Renderer;
class UnculledObject;

//----------------------------------------------------------------------------
// 名称:effect基类
// 说明:
// 作者:Sun Che
// 时间:20080702
//----------------------------------------------------------------------------
class SE_FOUNDATION_API Effect : public SEObject
{
    SE_DECLARE_RTTI;
    SE_DECLARE_NAME_ID;
    SE_DECLARE_STREAM;

public:
    // 虚基类
    virtual ~Effect(void);

    // 重载这个函数从而可获得effect派生类的自定义渲染行为.
    // 默认情况下是依次渲染pVisibleSet中的geometry对象.
    virtual void Draw(Renderer* pRenderer, Spatial* pGlobalObject,
        int iMin, int iMax, UnculledObject* pVisibleSet);

    // 重载这个函数从而可以更新effect派生类所需的自定义数据.
    virtual void OnUpdateData(void* pUserData);

    // 重载这些函数从而可获得effect派生类的自定义资源装载.
    // 默认情况下什么都不做.
    // 这些函数被Renderer::LoadResources和Renderer::ReleaseResources调用,
    // 用于geometry和effect对象.
    virtual void LoadResources(Renderer* pRenderer, Geometry* pGeometry);
    virtual void ReleaseResources(Renderer* pRenderer, Geometry* pGeometry);

protected:
    Effect(void);
};

typedef SESmartPointer<Effect> EffectPtr;

}

#endif
