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

#include "SEManagedFrameworkPCH.h"
#include "SEManagedObjectFactory.h"

#include "SEManagedNode.h"
#include "SEManagedLightNode.h"
#include "SEManagedCameraNode.h"

#include "SEManagedDefaultShaderEffect.h"
#include "SEManagedTextureEffect.h"
#include "SEManagedTextureTileEffect.h"
#include "SEManagedTextureTileL1Effect.h"

#include "SEManagedAlphaState.h"
#include "SEManagedCullState.h"
#include "SEManagedMaterialState.h"
#include "SEManagedPolygonOffsetState.h"
#include "SEManagedStencilState.h"
#include "SEManagedWireframeState.h"
#include "SEManagedZBufferState.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
INativeSpatial^ ManagedObjectFactory::CreateSpatialDerivedObject(
    SESpatial* pSpatial)
{
    if( !pSpatial )
    {
        return nullptr;
    }

    const Swing::SERTTI& rType = pSpatial->GetType();
    if( rType.IsExactly(SENode::TYPE) )
    {
        return gcnew ManagedNode((SENode*)pSpatial);
    }
    else if( rType.IsExactly(SETriMesh::TYPE) )
    {
        return gcnew ManagedTriMesh((SETriMesh*)pSpatial);
    }

    return nullptr;
}
//---------------------------------------------------------------------------
INativeEffect^ ManagedObjectFactory::CreateEffectDerivedObject(
    SEEffect* pEffect)
{
    if( !pEffect )
    {
        return nullptr;
    }

    const Swing::SERTTI& rType = pEffect->GetType();
    if( rType.IsExactly(SEDefaultShaderEffect::TYPE) )
    {
        return gcnew ManagedDefaultShaderEffect(
            (SEDefaultShaderEffect*)pEffect); 
    }
    else if( rType.IsExactly(SETextureEffect::TYPE) )
    {
        return gcnew ManagedTextureEffect((SETextureEffect*)pEffect);
    }
    else if( rType.IsExactly(SETextureTileEffect::TYPE) )
    {
        return gcnew ManagedTextureTileEffect((SETextureTileEffect*)pEffect);
    }
    else if( rType.IsExactly(SETextureTileL1Effect::TYPE) )
    {
        return gcnew ManagedTextureTileL1Effect(
            (SETextureTileL1Effect*)pEffect);
    }

    return nullptr;
}
//---------------------------------------------------------------------------
INativeGlobalState^ ManagedObjectFactory::CreateGlobalStateObject(
    SEGlobalState* pState)
{
    if( !pState )
    {
        return nullptr;
    }

    SEGlobalState::StateType eType = pState->GetStateType();
    switch( eType )
    {
    case SEGlobalState::ALPHA:
        return gcnew ManagedAlphaState((SEAlphaState*)pState);
        break;

    case SEGlobalState::CULL:
        return gcnew ManagedCullState((SECullState*)pState);
        break;

    case SEGlobalState::MATERIAL:
        return gcnew ManagedMaterialState((SEMaterialState*)pState);
        break;

    case SEGlobalState::POLYGONOFFSET:
        return gcnew ManagedPolygonOffsetState((SEPolygonOffsetState*)pState);
        break;

    case SEGlobalState::STENCIL:
        return gcnew ManagedStencilState((SEStencilState*)pState);
        break;

    case SEGlobalState::WIREFRAME:
        return gcnew ManagedWireframeState((SEWireframeState*)pState);
        break;

    case SEGlobalState::ZBUFFER:
        return gcnew ManagedZBufferState((SEZBufferState*)pState);
        break;

    default:
        return nullptr;
        break;
    }
}
//---------------------------------------------------------------------------