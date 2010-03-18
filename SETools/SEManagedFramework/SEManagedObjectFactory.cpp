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
    Spatial* pSpatial)
{
    if( !pSpatial )
    {
        return nullptr;
    }

    const Swing::RTTI& rType = pSpatial->GetType();
    if( rType.IsExactly(Node::TYPE) )
    {
        return gcnew ManagedNode((Node*)pSpatial);
    }
    else if( rType.IsExactly(TriMesh::TYPE) )
    {
        return gcnew ManagedTriMesh((TriMesh*)pSpatial);
    }

    return nullptr;
}
//---------------------------------------------------------------------------
INativeEffect^ ManagedObjectFactory::CreateEffectDerivedObject(
    Effect* pEffect)
{
    if( !pEffect )
    {
        return nullptr;
    }

    const Swing::RTTI& rType = pEffect->GetType();
    if( rType.IsExactly(DefaultShaderEffect::TYPE) )
    {
        return gcnew ManagedDefaultShaderEffect(
            (DefaultShaderEffect*)pEffect); 
    }
    else if( rType.IsExactly(TextureEffect::TYPE) )
    {
        return gcnew ManagedTextureEffect((TextureEffect*)pEffect);
    }
    else if( rType.IsExactly(TextureTileEffect::TYPE) )
    {
        return gcnew ManagedTextureTileEffect((TextureTileEffect*)pEffect);
    }
    else if( rType.IsExactly(TextureTileL1Effect::TYPE) )
    {
        return gcnew ManagedTextureTileL1Effect(
            (TextureTileL1Effect*)pEffect);
    }

    return nullptr;
}
//---------------------------------------------------------------------------
INativeGlobalState^ ManagedObjectFactory::CreateGlobalStateObject(
    GlobalState* pState)
{
    if( !pState )
    {
        return nullptr;
    }

    GlobalState::StateType eType = pState->GetStateType();
    switch( eType )
    {
    case GlobalState::ALPHA:
        return gcnew ManagedAlphaState((AlphaState*)pState);
        break;

    case GlobalState::CULL:
        return gcnew ManagedCullState((CullState*)pState);
        break;

    case GlobalState::MATERIAL:
        return gcnew ManagedMaterialState((MaterialState*)pState);
        break;

    case GlobalState::POLYGONOFFSET:
        return gcnew ManagedPolygonOffsetState((PolygonOffsetState*)pState);
        break;

    case GlobalState::STENCIL:
        return gcnew ManagedStencilState((StencilState*)pState);
        break;

    case GlobalState::WIREFRAME:
        return gcnew ManagedWireframeState((WireframeState*)pState);
        break;

    case GlobalState::ZBUFFER:
        return gcnew ManagedZBufferState((ZBufferState*)pState);
        break;

    default:
        return nullptr;
        break;
    }
}
//---------------------------------------------------------------------------