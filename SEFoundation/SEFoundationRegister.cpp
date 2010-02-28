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
    SE_REGISTER_STREAM(Object);
    SE_INVOKE_STREAM(Object);

    // Scene Graph
    SE_REGISTER_STREAM(BoundingVolume);
    SE_REGISTER_STREAM(BoxBV);
    SE_REGISTER_STREAM(Geometry);
    SE_REGISTER_STREAM(IndexBuffer);
    SE_REGISTER_STREAM(Node);
    SE_REGISTER_STREAM(Polyline);
    SE_REGISTER_STREAM(Polypoint);
    SE_REGISTER_STREAM(Spatial);
    SE_REGISTER_STREAM(SphereBV);
    SE_REGISTER_STREAM(TriMesh);
    SE_REGISTER_STREAM(VertexBuffer);
    SE_REGISTER_STREAM(CameraNode);
    SE_REGISTER_STREAM(LightNode);
    SE_REGISTER_STREAM(Particles);
    SE_INVOKE_STREAM(BoundingVolume);
    SE_INVOKE_STREAM(BoxBV);
    SE_INVOKE_STREAM(Geometry);
    SE_INVOKE_STREAM(IndexBuffer);
    SE_INVOKE_STREAM(Node);
    SE_INVOKE_STREAM(Polyline);
    SE_INVOKE_STREAM(Polypoint);
    SE_INVOKE_STREAM(Spatial);
    SE_INVOKE_STREAM(SphereBV);
    SE_INVOKE_STREAM(TriMesh);
    SE_INVOKE_STREAM(VertexBuffer);
    SE_INVOKE_STREAM(CameraNode);
    SE_INVOKE_STREAM(LightNode);
    SE_INVOKE_STREAM(Particles);

    // Rendering
    SE_REGISTER_STREAM(AlphaState);
    SE_REGISTER_STREAM(Camera);
    SE_REGISTER_STREAM(CullState);
    SE_REGISTER_STREAM(GlobalState);
    SE_REGISTER_STREAM(Image);
    SE_REGISTER_STREAM(Light);
    SE_REGISTER_STREAM(MaterialState);
    SE_REGISTER_STREAM(PolygonOffsetState);
    SE_REGISTER_STREAM(StencilState);
    SE_REGISTER_STREAM(Texture);
    SE_REGISTER_STREAM(WireframeState);
    SE_REGISTER_STREAM(ZBufferState);
    SE_REGISTER_STREAM(RenderStateBlock);
    SE_INVOKE_STREAM(AlphaState);
    SE_INVOKE_STREAM(Camera);
    SE_INVOKE_STREAM(CullState);
    SE_INVOKE_STREAM(GlobalState);
    SE_INVOKE_STREAM(Image);
    SE_INVOKE_STREAM(Light);
    SE_INVOKE_STREAM(MaterialState);
    SE_INVOKE_STREAM(PolygonOffsetState);
    SE_INVOKE_STREAM(StencilState);
    SE_INVOKE_STREAM(Texture);
    SE_INVOKE_STREAM(WireframeState);
    SE_INVOKE_STREAM(ZBufferState);
    SE_INVOKE_STREAM(RenderStateBlock);

    SE_REGISTER_INITIALIZE(AlphaState);
    SE_REGISTER_INITIALIZE(CullState);
    SE_REGISTER_INITIALIZE(MaterialState);
    SE_REGISTER_INITIALIZE(PolygonOffsetState);
    SE_REGISTER_INITIALIZE(StencilState);
    SE_REGISTER_INITIALIZE(WireframeState);
    SE_REGISTER_INITIALIZE(ZBufferState);
    SE_INVOKE_INITIALIZE(AlphaState);
    SE_INVOKE_INITIALIZE(CullState);
    SE_INVOKE_INITIALIZE(MaterialState);
    SE_INVOKE_INITIALIZE(PolygonOffsetState);
    SE_INVOKE_INITIALIZE(StencilState);
    SE_INVOKE_INITIALIZE(WireframeState);
    SE_INVOKE_INITIALIZE(ZBufferState);

    SE_REGISTER_TERMINATE(AlphaState);
    SE_REGISTER_TERMINATE(CullState);
    SE_REGISTER_TERMINATE(MaterialState);
    SE_REGISTER_TERMINATE(PolygonOffsetState);
    SE_REGISTER_TERMINATE(StencilState);
    SE_REGISTER_TERMINATE(WireframeState);
    SE_REGISTER_TERMINATE(ZBufferState);
    SE_INVOKE_TERMINATE(AlphaState);
    SE_INVOKE_TERMINATE(CullState);
    SE_INVOKE_TERMINATE(MaterialState);
    SE_INVOKE_TERMINATE(PolygonOffsetState);
    SE_INVOKE_TERMINATE(StencilState);
    SE_INVOKE_TERMINATE(WireframeState);
    SE_INVOKE_TERMINATE(ZBufferState);

    // Shared Arrays
    SE_REGISTER_STREAM(ColorRGBAArray);
    SE_REGISTER_STREAM(ColorRGBArray);
    SE_REGISTER_STREAM(DoubleArray);
    SE_REGISTER_STREAM(FloatArray);
    SE_REGISTER_STREAM(IntArray);
    SE_REGISTER_STREAM(Matrix2fArray);
    SE_REGISTER_STREAM(Matrix3fArray);
    SE_REGISTER_STREAM(Matrix4fArray);
    SE_REGISTER_STREAM(Plane3fArray);
    SE_REGISTER_STREAM(QuaternionfArray);
    SE_REGISTER_STREAM(Vector2fArray);
    SE_REGISTER_STREAM(Vector3fArray);
    SE_REGISTER_STREAM(Vector4fArray);
    SE_INVOKE_STREAM(ColorRGBAArray);
    SE_INVOKE_STREAM(ColorRGBArray);
    SE_INVOKE_STREAM(DoubleArray);
    SE_INVOKE_STREAM(FloatArray);
    SE_INVOKE_STREAM(IntArray);
    SE_INVOKE_STREAM(Matrix2fArray);
    SE_INVOKE_STREAM(Matrix3fArray);
    SE_INVOKE_STREAM(Matrix4fArray);
    SE_INVOKE_STREAM(Plane3fArray);
    SE_INVOKE_STREAM(QuaternionfArray);
    SE_INVOKE_STREAM(Vector2fArray);
    SE_INVOKE_STREAM(Vector3fArray);
    SE_INVOKE_STREAM(Vector4fArray);

    // Controllers
    SE_REGISTER_STREAM(Controller);
    SE_REGISTER_STREAM(KeyframeController);
    SE_REGISTER_STREAM(SkinController);
    SE_REGISTER_STREAM(ParticleController);
    SE_INVOKE_STREAM(Controller);
    SE_INVOKE_STREAM(KeyframeController);
    SE_INVOKE_STREAM(SkinController);
    SE_INVOKE_STREAM(ParticleController);

    // Shaders
    SE_REGISTER_STREAM(PixelProgram);
    SE_REGISTER_STREAM(PixelShader);
    SE_REGISTER_STREAM(Program);
    SE_REGISTER_STREAM(Shader);
    SE_REGISTER_STREAM(VertexProgram);
    SE_REGISTER_STREAM(VertexShader);
    SE_REGISTER_STREAM(InterfaceDescriptor);
    SE_REGISTER_STREAM(DescriptorItem);
    SE_REGISTER_STREAM(GeometryProgram);
    SE_REGISTER_STREAM(GeometryShader);
    SE_INVOKE_STREAM(PixelProgram);
    SE_INVOKE_STREAM(PixelShader);
    SE_INVOKE_STREAM(Program);
    SE_INVOKE_STREAM(Shader);
    SE_INVOKE_STREAM(VertexProgram);
    SE_INVOKE_STREAM(VertexShader);
    SE_INVOKE_STREAM(InterfaceDescriptor);
    SE_INVOKE_STREAM(DescriptorItem);
    SE_INVOKE_STREAM(GeometryProgram);
    SE_INVOKE_STREAM(GeometryShader);

    SE_REGISTER_INITIALIZE(RendererConstant);
    SE_INVOKE_INITIALIZE(RendererConstant);

    SE_REGISTER_TERMINATE(RendererConstant);
    SE_INVOKE_TERMINATE(RendererConstant);

    // Effects
    SE_REGISTER_STREAM(DefaultShaderEffect);
    SE_REGISTER_STREAM(Effect);
    SE_REGISTER_STREAM(LightingEffect);
    SE_REGISTER_STREAM(ShaderEffect);
    SE_REGISTER_STREAM(TextureEffect);
    SE_REGISTER_STREAM(MultitextureEffect);
    SE_REGISTER_STREAM(MaterialEffect);
    SE_REGISTER_STREAM(MaterialTextureEffect);
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
    SE_INVOKE_STREAM(DefaultShaderEffect);
    SE_INVOKE_STREAM(Effect);
    SE_INVOKE_STREAM(LightingEffect);
    SE_INVOKE_STREAM(ShaderEffect);
    SE_INVOKE_STREAM(TextureEffect);
    SE_INVOKE_STREAM(MultitextureEffect);
    SE_INVOKE_STREAM(MaterialEffect);
    SE_INVOKE_STREAM(MaterialTextureEffect);
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

    // Terrain
    SE_REGISTER_STREAM(Terrain);
    SE_REGISTER_STREAM(TerrainPage);
    SE_REGISTER_STREAM(RoamTerrain);
    SE_REGISTER_STREAM(RoamTerrainPage);
    SE_INVOKE_STREAM(Terrain);
    SE_INVOKE_STREAM(TerrainPage);
    SE_INVOKE_STREAM(RoamTerrain);
    SE_INVOKE_STREAM(RoamTerrainPage);

    // Collision
    SE_REGISTER_INITIALIZE(BoxBVTree);
    SE_REGISTER_INITIALIZE(SphereBVTree);
    SE_INVOKE_INITIALIZE(BoxBVTree);
    SE_INVOKE_INITIALIZE(SphereBVTree);

    // Detail
    SE_REGISTER_STREAM(BillboardNode);
    SE_INVOKE_STREAM(BillboardNode);
}
//----------------------------------------------------------------------------