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

namespace Swing{ namespace Tools{ namespace ManagedFramework{

//----------------------------------------------------------------------------
// Description:
// Author:Sun Che
// Date:20091219
//----------------------------------------------------------------------------
private ref class ManagedUtility sealed
{
internal:
    // Allocate a native heap buffer and fill it with the CLI string object's
    // content. You should call FreeNativeCharBuffer() function to deallocate 
    // the native heap buffer when you have finished with it. 
	// These two functions must be used in pairs.
    static const char* StringToNativeCharBuffer(String^ thString);
    static void FreeNativeCharBuffer(const char* acBuffer);

    // Do a shallow copy with a given SENode object, a node hierarchy is 
    // created an it only contains sub-node and sub-trimesh objects for now, 
    // all sub-trimesh objects share the VB and IB of the original objects.
    static SENode* CloneNode(SENode* pSrcNode);

    // Do a shallow copy with a given SETriMesh object, a new SETriMesh object 
    // is created an it shares the VB and IB of the original object.
    static SETriMesh* CloneTriMesh(SETriMesh* pSrcTriMesh);

    // Generate normals for all sub-mesh objects in the hierarchy.
    static void GenerateNormalsForAll(SENode* pNode);

    // Detach all effects for all sub-spatial objects in the hierarchy.
    static void DetachAllEffectsForAll(SENode* pNode);

    static void ModulateWithLightingEffectForAll(SENode* pNode);

    static void MaterialTextureConditioner(SENode* pNode);

    static void DisableLightingConditioner(SENode* pNode);

    static void ImageConditioner(SENode* pNode, SEImage* pImage);

    static void WallConditioner(SENode* pNode, SETextureTileL1Effect* pEffect);
};

}}}