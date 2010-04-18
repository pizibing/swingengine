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
#include "SEFoundationRegister.h"

// Object System
#include "SEObject.h"
// Scene Graph
#include "SEBoundingVolume.h"
#include "SEBoxBV.h"
#include "SEGeometry.h"
#include "SEIndexBuffer.h"
#include "SENode.h"
#include "SEPolyline.h"
#include "SEPolypoint.h"
#include "SESpatial.h"
#include "SESphereBV.h"
#include "SETriMesh.h"
#include "SEVertexBuffer.h"
#include "SECameraNode.h"
#include "SELightNode.h"
#include "SEParticles.h"
// Rendering
#include "SEAlphaState.h"
#include "SECamera.h"
#include "SECullState.h"
#include "SEGlobalState.h"
#include "SEImage.h"
#include "SELight.h"
#include "SEMaterialState.h"
#include "SEPolygonOffsetState.h"
#include "SEStencilState.h"
#include "SETexture.h"
#include "SEWireframeState.h"
#include "SEZBufferState.h"
#include "SERenderStateBlock.h"
// Shared Arrays
#include "SEColorRGBAArray.h"
#include "SEColorRGBArray.h"
#include "SEDoubleArray.h"
#include "SEFloatArray.h"
#include "SEIntArray.h"
#include "SEMatrix2Array.h"
#include "SEMatrix3Array.h"
#include "SEMatrix4Array.h"
#include "SEPlaneArray.h"
#include "SEQuaternionArray.h"
#include "SEVector2Array.h"
#include "SEVector3Array.h"
#include "SEVector4Array.h"
// Controllers
#include "SEController.h"
#include "SEKeyFrameController.h"
#include "SESkinController.h"
#include "SEParticleController.h"
// Shaders
#include "SEPixelProgram.h"
#include "SEPixelShader.h"
#include "SEProgram.h"
#include "SEShader.h"
#include "SEVertexProgram.h"
#include "SEVertexShader.h"
#include "SERendererConstant.h"
#include "SEInterfaceDescriptor.h"
#include "SEDescriptorItem.h"
#include "SEGeometryProgram.h"
#include "SEGeometryShader.h"
// Effects
#include "SEDefaultShaderEffect.h"
#include "SEEffect.h"
#include "SELightingEffect.h"
#include "SEShaderEffect.h"
#include "SETextureEffect.h"
#include "SEMultitextureEffect.h"
#include "SEMaterialEffect.h"
#include "SEMaterialTextureEffect.h"
#include "SEMaterialTextureL1Effect.h"
#include "SEMaterialTexture2L1Effect.h"
#include "SEVertexColor3Effect.h"
#include "SESkinEffect.h"
#include "SESkinDefaultEffect.h"
#include "SESkinMaterialEffect.h"
#include "SESkinMaterialTextureEffect.h"
#include "SESkinMaterialTextureL1Effect.h"
#include "SESkinMaterialTexture2L1Effect.h"
#include "SETerrainEffect.h"
#include "SEBumpMapL1Effect.h"
#include "SEParallaxMapL1Effect.h"
#include "SEShadowMapEffect.h"
#include "SEVertexTextureEffect.h"
#include "SEDefaultMRT3Effect.h"
#include "SEGaussianBlurHEffect.h"
#include "SEGaussianBlurVEffect.h"
#include "SECombineEffect.h"
#include "SEColorNormalDepthEffect.h"
#include "SEScreenSpaceAOEffect.h"
#include "SEScreenSpaceAOBlurEffect.h"
#include "SETextureTileEffect.h"
#include "SETextureTileL1Effect.h"
// Terrain
#include "SETerrain.h"
#include "SETerrainPage.h"
#include "SERoamTerrain.h"
#include "SERoamTerrainPage.h"
// Collision
#include "SEBoxBVTree.h"
#include "SESphereBVTree.h"
// Detail
#include "SEBillboardNode.h"

using namespace Swing;

//----------------------------------------------------------------------------
void Swing::SE_Foundation_Register()
{
    // Object System
    SE_REGISTER_STREAM(SEObject);
    SE_INVOKE_STREAM(SEObject);

    // Scene Graph
    SE_REGISTER_STREAM(SEBoundingVolume);
    SE_REGISTER_STREAM(SEBoxBV);
    SE_REGISTER_STREAM(SEGeometry);
    SE_REGISTER_STREAM(SEIndexBuffer);
    SE_REGISTER_STREAM(SENode);
    SE_REGISTER_STREAM(SEPolyline);
    SE_REGISTER_STREAM(SEPolypoint);
    SE_REGISTER_STREAM(SESpatial);
    SE_REGISTER_STREAM(SESphereBV);
    SE_REGISTER_STREAM(SETriMesh);
    SE_REGISTER_STREAM(SEVertexBuffer);
    SE_REGISTER_STREAM(SECameraNode);
    SE_REGISTER_STREAM(SELightNode);
    SE_REGISTER_STREAM(SEParticles);
    SE_INVOKE_STREAM(SEBoundingVolume);
    SE_INVOKE_STREAM(SEBoxBV);
    SE_INVOKE_STREAM(SEGeometry);
    SE_INVOKE_STREAM(SEIndexBuffer);
    SE_INVOKE_STREAM(SENode);
    SE_INVOKE_STREAM(SEPolyline);
    SE_INVOKE_STREAM(SEPolypoint);
    SE_INVOKE_STREAM(SESpatial);
    SE_INVOKE_STREAM(SESphereBV);
    SE_INVOKE_STREAM(SETriMesh);
    SE_INVOKE_STREAM(SEVertexBuffer);
    SE_INVOKE_STREAM(SECameraNode);
    SE_INVOKE_STREAM(SELightNode);
    SE_INVOKE_STREAM(SEParticles);

    // Rendering
    SE_REGISTER_STREAM(SEAlphaState);
    SE_REGISTER_STREAM(SECamera);
    SE_REGISTER_STREAM(SECullState);
    SE_REGISTER_STREAM(SEGlobalState);
    SE_REGISTER_STREAM(SEImage);
    SE_REGISTER_STREAM(SELight);
    SE_REGISTER_STREAM(SEMaterialState);
    SE_REGISTER_STREAM(SEPolygonOffsetState);
    SE_REGISTER_STREAM(SEStencilState);
    SE_REGISTER_STREAM(SETexture);
    SE_REGISTER_STREAM(SEWireframeState);
    SE_REGISTER_STREAM(SEZBufferState);
    SE_REGISTER_STREAM(SERenderStateBlock);
    SE_INVOKE_STREAM(SEAlphaState);
    SE_INVOKE_STREAM(SECamera);
    SE_INVOKE_STREAM(SECullState);
    SE_INVOKE_STREAM(SEGlobalState);
    SE_INVOKE_STREAM(SEImage);
    SE_INVOKE_STREAM(SELight);
    SE_INVOKE_STREAM(SEMaterialState);
    SE_INVOKE_STREAM(SEPolygonOffsetState);
    SE_INVOKE_STREAM(SEStencilState);
    SE_INVOKE_STREAM(SETexture);
    SE_INVOKE_STREAM(SEWireframeState);
    SE_INVOKE_STREAM(SEZBufferState);
    SE_INVOKE_STREAM(SERenderStateBlock);

    SE_REGISTER_INITIALIZE(SEAlphaState);
    SE_REGISTER_INITIALIZE(SECullState);
    SE_REGISTER_INITIALIZE(SEMaterialState);
    SE_REGISTER_INITIALIZE(SEPolygonOffsetState);
    SE_REGISTER_INITIALIZE(SEStencilState);
    SE_REGISTER_INITIALIZE(SEWireframeState);
    SE_REGISTER_INITIALIZE(SEZBufferState);
    SE_INVOKE_INITIALIZE(SEAlphaState);
    SE_INVOKE_INITIALIZE(SECullState);
    SE_INVOKE_INITIALIZE(SEMaterialState);
    SE_INVOKE_INITIALIZE(SEPolygonOffsetState);
    SE_INVOKE_INITIALIZE(SEStencilState);
    SE_INVOKE_INITIALIZE(SEWireframeState);
    SE_INVOKE_INITIALIZE(SEZBufferState);

    SE_REGISTER_TERMINATE(SEAlphaState);
    SE_REGISTER_TERMINATE(SECullState);
    SE_REGISTER_TERMINATE(SEMaterialState);
    SE_REGISTER_TERMINATE(SEPolygonOffsetState);
    SE_REGISTER_TERMINATE(SEStencilState);
    SE_REGISTER_TERMINATE(SEWireframeState);
    SE_REGISTER_TERMINATE(SEZBufferState);
    SE_INVOKE_TERMINATE(SEAlphaState);
    SE_INVOKE_TERMINATE(SECullState);
    SE_INVOKE_TERMINATE(SEMaterialState);
    SE_INVOKE_TERMINATE(SEPolygonOffsetState);
    SE_INVOKE_TERMINATE(SEStencilState);
    SE_INVOKE_TERMINATE(SEWireframeState);
    SE_INVOKE_TERMINATE(SEZBufferState);

    // Shared Arrays
    SE_REGISTER_STREAM(SEColorRGBAArray);
    SE_REGISTER_STREAM(SEColorRGBArray);
    SE_REGISTER_STREAM(SEDoubleArray);
    SE_REGISTER_STREAM(SEFloatArray);
    SE_REGISTER_STREAM(SEIntArray);
    SE_REGISTER_STREAM(SEMatrix2fArray);
    SE_REGISTER_STREAM(SEMatrix3fArray);
    SE_REGISTER_STREAM(SEMatrix4fArray);
    SE_REGISTER_STREAM(SEPlane3fArray);
    SE_REGISTER_STREAM(SEQuaternionfArray);
    SE_REGISTER_STREAM(SEVector2fArray);
    SE_REGISTER_STREAM(SEVector3fArray);
    SE_REGISTER_STREAM(SEVector4fArray);
    SE_INVOKE_STREAM(SEColorRGBAArray);
    SE_INVOKE_STREAM(SEColorRGBArray);
    SE_INVOKE_STREAM(SEDoubleArray);
    SE_INVOKE_STREAM(SEFloatArray);
    SE_INVOKE_STREAM(SEIntArray);
    SE_INVOKE_STREAM(SEMatrix2fArray);
    SE_INVOKE_STREAM(SEMatrix3fArray);
    SE_INVOKE_STREAM(SEMatrix4fArray);
    SE_INVOKE_STREAM(SEPlane3fArray);
    SE_INVOKE_STREAM(SEQuaternionfArray);
    SE_INVOKE_STREAM(SEVector2fArray);
    SE_INVOKE_STREAM(SEVector3fArray);
    SE_INVOKE_STREAM(SEVector4fArray);

    // Controllers
    SE_REGISTER_STREAM(SEController);
    SE_REGISTER_STREAM(SEKeyframeController);
    SE_REGISTER_STREAM(SESkinController);
    SE_REGISTER_STREAM(SEParticleController);
    SE_INVOKE_STREAM(SEController);
    SE_INVOKE_STREAM(SEKeyframeController);
    SE_INVOKE_STREAM(SESkinController);
    SE_INVOKE_STREAM(SEParticleController);

    // Shaders
    SE_REGISTER_STREAM(SEPixelProgram);
    SE_REGISTER_STREAM(SEPixelShader);
    SE_REGISTER_STREAM(SEProgram);
    SE_REGISTER_STREAM(SEShader);
    SE_REGISTER_STREAM(SEVertexProgram);
    SE_REGISTER_STREAM(SEVertexShader);
    SE_REGISTER_STREAM(SEInterfaceDescriptor);
    SE_REGISTER_STREAM(SEDescriptorItem);
    SE_REGISTER_STREAM(SEGeometryProgram);
    SE_REGISTER_STREAM(SEGeometryShader);
    SE_INVOKE_STREAM(SEPixelProgram);
    SE_INVOKE_STREAM(SEPixelShader);
    SE_INVOKE_STREAM(SEProgram);
    SE_INVOKE_STREAM(SEShader);
    SE_INVOKE_STREAM(SEVertexProgram);
    SE_INVOKE_STREAM(SEVertexShader);
    SE_INVOKE_STREAM(SEInterfaceDescriptor);
    SE_INVOKE_STREAM(SEDescriptorItem);
    SE_INVOKE_STREAM(SEGeometryProgram);
    SE_INVOKE_STREAM(SEGeometryShader);

    SE_REGISTER_INITIALIZE(SERendererConstant);
    SE_INVOKE_INITIALIZE(SERendererConstant);

    SE_REGISTER_TERMINATE(SERendererConstant);
    SE_INVOKE_TERMINATE(SERendererConstant);

    // Effects
    SE_REGISTER_STREAM(DefaultShaderEffect);
    SE_REGISTER_STREAM(Effect);
    SE_REGISTER_STREAM(LightingEffect);
    SE_REGISTER_STREAM(ShaderEffect);
    SE_REGISTER_STREAM(TextureEffect);
    SE_REGISTER_STREAM(MultitextureEffect);
    SE_REGISTER_STREAM(MaterialEffect);
    SE_REGISTER_STREAM(MaterialTextureEffect);
    SE_REGISTER_STREAM(MaterialTextureL1Effect);
    SE_REGISTER_STREAM(MaterialTexture2L1Effect);
    SE_REGISTER_STREAM(VertexColor3Effect);
    SE_REGISTER_STREAM(SkinEffect);
    SE_REGISTER_STREAM(SkinDefaultEffect);
    SE_REGISTER_STREAM(SkinMaterialEffect);
    SE_REGISTER_STREAM(SkinMaterialTextureEffect);
    SE_REGISTER_STREAM(SkinMaterialTextureL1Effect);
    SE_REGISTER_STREAM(SkinMaterialTexture2L1Effect);
    SE_REGISTER_STREAM(TerrainEffect);
    SE_REGISTER_STREAM(BumpMapL1Effect);
    SE_REGISTER_STREAM(ParallaxMapL1Effect);
    SE_REGISTER_STREAM(ShadowMapEffect);
    SE_REGISTER_STREAM(VertexTextureEffect);
    SE_REGISTER_STREAM(DefaultMRT3Effect);
    SE_REGISTER_STREAM(GaussianBlurHEffect);
    SE_REGISTER_STREAM(GaussianBlurVEffect);
    SE_REGISTER_STREAM(CombineEffect);
    SE_REGISTER_STREAM(ColorNormalDepthEffect);
    SE_REGISTER_STREAM(ScreenSpaceAOEffect);
    SE_REGISTER_STREAM(ScreenSpaceAOBlurEffect);
    SE_REGISTER_STREAM(TextureTileEffect);
    SE_REGISTER_STREAM(TextureTileL1Effect);
    SE_INVOKE_STREAM(DefaultShaderEffect);
    SE_INVOKE_STREAM(Effect);
    SE_INVOKE_STREAM(LightingEffect);
    SE_INVOKE_STREAM(ShaderEffect);
    SE_INVOKE_STREAM(TextureEffect);
    SE_INVOKE_STREAM(MultitextureEffect);
    SE_INVOKE_STREAM(MaterialEffect);
    SE_INVOKE_STREAM(MaterialTextureEffect);
    SE_INVOKE_STREAM(MaterialTextureL1Effect);
    SE_INVOKE_STREAM(MaterialTexture2L1Effect);
    SE_INVOKE_STREAM(VertexColor3Effect);
    SE_INVOKE_STREAM(SkinEffect);
    SE_INVOKE_STREAM(SkinDefaultEffect);
    SE_INVOKE_STREAM(SkinMaterialEffect);
    SE_INVOKE_STREAM(SkinMaterialTextureEffect);
    SE_INVOKE_STREAM(SkinMaterialTextureL1Effect);
    SE_INVOKE_STREAM(SkinMaterialTexture2L1Effect);
    SE_INVOKE_STREAM(TerrainEffect);
    SE_INVOKE_STREAM(BumpMapL1Effect);
    SE_INVOKE_STREAM(ParallaxMapL1Effect);
    SE_INVOKE_STREAM(ShadowMapEffect);
    SE_INVOKE_STREAM(VertexTextureEffect);
    SE_INVOKE_STREAM(DefaultMRT3Effect);
    SE_INVOKE_STREAM(GaussianBlurHEffect);
    SE_INVOKE_STREAM(GaussianBlurVEffect);
    SE_INVOKE_STREAM(CombineEffect);
    SE_INVOKE_STREAM(ColorNormalDepthEffect);
    SE_INVOKE_STREAM(ScreenSpaceAOEffect);
    SE_INVOKE_STREAM(ScreenSpaceAOBlurEffect);
    SE_INVOKE_STREAM(TextureTileEffect);
    SE_INVOKE_STREAM(TextureTileL1Effect);

    SE_REGISTER_INITIALIZE(SkinEffect);
    SE_INVOKE_INITIALIZE(SkinEffect);

    SE_REGISTER_TERMINATE(SkinEffect);
    SE_INVOKE_TERMINATE(SkinEffect);

    // Terrain
    SE_REGISTER_STREAM(SETerrain);
    SE_REGISTER_STREAM(SETerrainPage);
    SE_REGISTER_STREAM(SERoamTerrain);
    SE_REGISTER_STREAM(SERoamTerrainPage);
    SE_INVOKE_STREAM(SETerrain);
    SE_INVOKE_STREAM(SETerrainPage);
    SE_INVOKE_STREAM(SERoamTerrain);
    SE_INVOKE_STREAM(SERoamTerrainPage);

    // Collision
    SE_REGISTER_INITIALIZE(SEBoxBVTree);
    SE_REGISTER_INITIALIZE(SESphereBVTree);
    SE_INVOKE_INITIALIZE(SEBoxBVTree);
    SE_INVOKE_INITIALIZE(SESphereBVTree);

    // Detail
    SE_REGISTER_STREAM(SEBillboardNode);
    SE_INVOKE_STREAM(SEBillboardNode);
}
//----------------------------------------------------------------------------