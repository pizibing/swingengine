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

#ifndef Swing_FoundationHead_H
#define Swing_FoundationHead_H

// Foundation Register
#include "SEFoundationRegister.h"

// Math
#include "SEMath.h"
#include "SEMatrix2.h"
#include "SEMatrix3.h"
#include "SEMatrix4.h"
#include "SEMatrixMN.h"
#include "SEVector2.h"
#include "SEVector3.h"
#include "SEVector4.h"
#include "SEVectorN.h"
#include "SEQuaternion.h"
#include "SEPlane3.h"
#include "SESphere3.h"
#include "SEBox2.h"
#include "SEBox3.h"
#include "SELine2.h"
#include "SELine3.h"
#include "SERay2.h"
#include "SERay3.h"
#include "SEColorRGB.h"
#include "SEColorRGBA.h"
#include "SEBitHacks.h"
#include "SELinComp.h"
#include "SETriangle2.h"
#include "SETriangle3.h"
#include "SEPolyhedron3.h"
#include "SEConvexPolyhedron3.h"
#include "SEMapper2.h"
#include "SEMapper3.h"
#include "SESegment2.h"
#include "SESegment3.h"
#include "SERectangle3.h"
#include "SEFrustum3.h"

// System
#include "SECommand.h"
#include "SEPlatforms.h"
#include "SESystem.h"
#include "SEAssert.h"
#include "SEMemory.h"

// Base
#include "SEHashTable.h"
#include "SEHashSet.h"
#include "SEStringHashTable.h"
#include "SEString.h"

// Scene Graph
#include "SETransformation.h"
#include "SEBoundingVolume.h"
#include "SEAttributes.h"
#include "SEVertexBuffer.h"
#include "SEIndexBuffer.h"
#include "SEBoxBV.h"
#include "SESphereBV.h"
#include "SEUnculledObject.h"
#include "SEUnculledSet.h"
#include "SECuller.h"
#include "SESpatial.h"
#include "SENode.h"
#include "SEGeometry.h"
#include "SETriMesh.h"
#include "SEPolyline.h"
#include "SEPolypoint.h"
#include "SEStandardMesh.h"
#include "SECameraNode.h"
#include "SELightNode.h"
#include "SEParticles.h"

// Object System
#include "SESmartPointer.h"
#include "SERTTI.h"
#include "SEObject.h"
#include "SEStringTree.h"
#include "SEMain.h"
#include "SEStreamVersion.h"
#include "SEStream.h"
#include "SEImageVersion.h"

// Containment
#include "SEContSphere3.h"
#include "SEContBox3.h"

// Intersection
#include "SEIntersector.h"
#include "SEIntersector1.h"
#include "SEIntrLine3Sphere3.h"
#include "SEIntrRay3Sphere3.h"
#include "SEIntrSegment3Sphere3.h"
#include "SEIntrRay3Triangle3.h"
#include "SEIntrSphere3Sphere3.h"
#include "SEIntrTriangle2Triangle2.h"
#include "SEIntrTriangle3Triangle3.h"
#include "SEIntrLine3Box3.h"
#include "SEIntrRay3Box3.h"
#include "SEIntrSegment3Box3.h"
#include "SEIntrBox3Box3.h"

// Approximation
#include "SEApprGaussPointsFit3.h"
#include "SEApprLineFit3.h"

// Numerical Analysis
#include "SEEigen.h"

// Rendering
#include "SEBindable.h"
#include "SERenderer.h"
#include "SEImage.h"
#include "SETexture.h"
#include "SEGlobalState.h"
#include "SEAlphaState.h"
#include "SEMaterialState.h"
#include "SEWireframeState.h"
#include "SEZbufferState.h"
#include "SEStencilState.h"
#include "SECullState.h"
#include "SEPolygonOffsetState.h"
#include "SEFrameBuffer.h"
#include "SELight.h"
#include "SECamera.h"
#include "SERenderStateBlock.h"

// Shared Arrays
#include "SESharedArray.h"
#include "SEIntArray.h"
#include "SEFloatArray.h"
#include "SEDoubleArray.h"
#include "SEVector2Array.h"
#include "SEVector3Array.h"
#include "SEVector4Array.h"
#include "SEMatrix2Array.h"
#include "SEMatrix3Array.h"
#include "SEMatrix4Array.h"
#include "SEColorRGBArray.h"
#include "SEColorRGBAArray.h"
#include "SEPlaneArray.h"
#include "SEQuaternionArray.h"

// Controllers
#include "SEController.h"
#include "SEKeyFrameController.h"
#include "SESkinController.h"
#include "SEParticleController.h"

// Shaders
#include "SERendererConstant.h"
#include "SEUserConstant.h"
#include "SESamplerInformation.h"
#include "SEProgram.h"
#include "SEVertexProgram.h"
#include "SEVertexProgramCatalog.h"
#include "SEPixelProgram.h"
#include "SEPixelProgramCatalog.h"
#include "SEImageCatalog.h"
#include "SEShader.h"
#include "SEVertexShader.h"
#include "SEPixelShader.h"
#include "SEInterfaceDescriptor.h"
#include "SEDescriptorItem.h"
#include "SEGeometryProgram.h"
#include "SEGeometryProgramCatalog.h"
#include "SEGeometryShader.h"

// Effects
#include "SEEffect.h"
#include "SEShaderEffect.h"
#include "SELightingEffect.h"
#include "SEDefaultShaderEffect.h"
#include "SETextureEffect.h"
#include "SEMultitextureEffect.h"
#include "SEMaterialEffect.h"
#include "SEMaterialTextureEffect.h"
#include "SEVertexColor3Effect.h"
#include "SESkinEffect.h"
#include "SESkinDefaultEffect.h"
#include "SESkinMaterialEffect.h"
#include "SESkinMaterialTextureEffect.h"
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

// Terrain
#include "SETerrain.h"
#include "SETerrainPage.h"
#include "SERoamTerrain.h"
#include "SERoamTerrainPage.h"
#include "SERoamTerrainPatch.h"
#include "SERoamTriTreeNode.h"

// Meshes
#include "SEBasicMesh.h"
#include "SEEdgeKey.h"

// Computational Geometry:  Convex Hull
#include "SEConvexHull.h"
#include "SEConvexHull1.h"
#include "SEConvexHull2.h"
#include "SEConvexHull3.h"
#include "SEHullEdge2.h"
#include "SEHullTriangle3.h"

// Computational Geometry:  Delaunay

// Computational Geometry:  Query
#include "SEQuery.h"
#include "SEQuery2.h"
#include "SEQuery2Filtered.h"
#include "SEQuery2Int64.h"
#include "SEQuery2TInteger.h"
#include "SEQuery2TRational.h"
#include "SEQuery3.h"
#include "SEQuery3Filtered.h"
#include "SEQuery3Int64.h"
#include "SEQuery3TInteger.h"
#include "SEQuery3TRational.h"

// Computational Geometry:  Rational Arithmetic
#include "SEIVector2.h"
#include "SEIVector3.h"
#include "SERVector2.h"
#include "SERVector3.h"
#include "SETInteger.h"
#include "SETIVector.h"
#include "SETRational.h"
#include "SETRVector.h"

// Computational Geometry:  Triangulate

// Collision
#include "SEBoundingVolumeTree.h"
#include "SEBoxBVTree.h"
#include "SECollisionGroup.h"
#include "SECollisionRecord.h"
#include "SESphereBVTree.h"

// Distance
#include "SEDistance.h"
#include "SEDistLine2Line2.h"
#include "SEDistLine2Ray2.h"
#include "SEDistLine2Segment2.h"
#include "SEDistLine3Box3.h"
#include "SEDistLine3Line3.h"
#include "SEDistLine3Ray3.h"
#include "SEDistLine3Segment3.h"
#include "SEDistLine3Rectangle3.h"
#include "SEDistLine3Triangle3.h"
#include "SEDistRay2Ray2.h"
#include "SEDistRay2Segment2.h"
#include "SEDistRay3Box3.h"
#include "SEDistRay3Ray3.h"
#include "SEDistRay3Segment3.h"
#include "SEDistRay3Rectangle3.h"
#include "SEDistRay3Triangle3.h"
#include "SEDistRectangle3Rectangle3.h"
#include "SEDistSegment2Segment2.h"
#include "SEDistSegment3Box3.h"
#include "SEDistSegment3Rectangle3.h"
#include "SEDistSegment3Segment3.h"
#include "SEDistSegment3Triangle3.h"
#include "SEDistTriangle3Rectangle3.h"
#include "SEDistTriangle3Triangle3.h"
#include "SEDistVector2Box2.h"
#include "SEDistVector2Line2.h"
#include "SEDistVector2Ray2.h"
#include "SEDistVector2Segment2.h"
#include "SEDistVector3Box3.h"
#include "SEDistVector3Frustum3.h"
#include "SEDistVector3Line3.h"
#include "SEDistVector3Plane3.h"
#include "SEDistVector3Ray3.h"
#include "SEDistVector3Segment3.h"
#include "SEDistVector3Rectangle3.h"
#include "SEDistVector3Triangle3.h"

// Detail
#include "SEBillboardNode.h"

#endif