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

#ifndef Swing_BoxBVTree_H
#define Swing_BoxBVTree_H

#include "SEFoundationLIB.h"
#include "SEBoundingVolumeTree.h"
#include "SEBoxBV.h"

namespace Swing
{

//----------------------------------------------------------------------------
// 说明:
// 作者:Sun Che
// 时间:20081223
//----------------------------------------------------------------------------
class SE_FOUNDATION_API SEBoxBVTree : public SEBoundingVolumeTree
{
    SE_DECLARE_INITIALIZE;

public:
    SEBoxBVTree(const SETriMesh* pMesh, int iMaxTrisPerLeaf = 1,
        bool bStoreInteriorTris = false);

protected:
    static SEBoundingVolume* CreateModelBound(const SETriMesh* pMesh, int i0,
        int i1, int* aiISplit, SELine3f& rLine);

    static SEBoundingVolume* CreateWorldBound(void);
};

}

#endif
