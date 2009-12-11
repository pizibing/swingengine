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

#ifndef Swing_ToolsUtility_H
#define Swing_ToolsUtility_H

// DirectX9 headers.
#include <d3d9.h>
#include <d3dx9tex.h>

// 避免非Unicode文件中的无法表示字符警告.
#pragma warning(disable:4819)

// COLLADA headers.
#include "dae.h"
#include "dae/daeSIDResolver.h"
#include "dae/domAny.h"
#include "dom/domCOLLADA.h"
#include "dom/domConstants.h"
#include "dom/domElements.h"
#include "dom/domProfile_COMMON.h"

typedef domCamera::domOptics DomCameraOptics;
typedef DomCameraOptics::domTechnique_common DomCameraOpticsTechCommon;
typedef DomCameraOpticsTechCommon::domPerspective DomCameraPerspective;
typedef DomCameraOpticsTechCommon::domOrthographic DomCameraOrthographic;

#endif
