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

#pragma once

#pragma unmanaged

#include "SwingFoundation.h"
#include "SwingDX9Renderer.h"

#pragma managed

// Managed Math
#include "SEManagedMath.h"
#include "SEManagedColorRGB.h"
#include "SEManagedColorRGBA.h"
#include "SEManagedVector2.h"
#include "SEManagedVector3.h"
#include "SEManagedMatrix3.h"
#include "SEManagedQuaternion.h"
#include "SEManagedRay3.h"

// Managed Rendering
#include "SEINativeGlobalState.h"
#include "SEManagedCamera.h"
#include "SEManagedRenderer.h"
#include "SEManagedAlphaState.h"
#include "SEManagedCullState.h"
#include "SEManagedMaterialState.h"
#include "SEManagedPolygonOffsetState.h"
#include "SEManagedStencilState.h"
#include "SEManagedWireframeState.h"
#include "SEManagedZBufferState.h"
#include "SEManagedLight.h"

// Managed Scene Graph
#include "SEINativeSpatial.h"
#include "SEINativeNode.h"
#include "SEINativeGeometry.h"
#include "SEManagedCuller.h"
#include "SEManagedAttributes.h"
#include "SEManagedStandardMesh.h"
#include "SEManagedNode.h"
#include "SEManagedTriMesh.h"
#include "SEManagedWidget.h"

// Managed Effects
#include "SEINativeEffect.h"
#include "SEINativeShaderEffect.h"
#include "SEManagedDefaultShaderEffect.h"
#include "SEManagedTextureEffect.h"

// Managed Object System
#include "SEINativeObject.h"
#include "SEManagedStream.h"

// Managed System
#include "SEManagedSystem.h"

#include "SEManagedMCR.h"
#include "SEManagedEngine.h"
#include "SEManagedObjectFactory.h"

using namespace System;
