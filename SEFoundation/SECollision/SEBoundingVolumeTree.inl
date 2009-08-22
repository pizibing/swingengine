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

//----------------------------------------------------------------------------
inline const TriMesh* BoundingVolumeTree::GetMesh() const
{
    return m_pMesh;
}
//----------------------------------------------------------------------------
inline const BoundingVolume* BoundingVolumeTree::GetWorldBound() const
{
    return m_spWorldBound;
}
//----------------------------------------------------------------------------
inline int BoundingVolumeTree::GetTriangleCount() const
{
    return m_iTriangleCount;
}
//----------------------------------------------------------------------------
inline int BoundingVolumeTree::GetTriangle(int i) const
{
    return m_aiTriangle[i];
}
//----------------------------------------------------------------------------
inline const int* BoundingVolumeTree::GetTriangles() const
{
    return m_aiTriangle;
}
//----------------------------------------------------------------------------
inline BoundingVolumeTree* BoundingVolumeTree::GetLChild()
{
    return m_pLChild;
}
//----------------------------------------------------------------------------
inline BoundingVolumeTree* BoundingVolumeTree::GetRChild()
{
    return m_pRChild;
}
//----------------------------------------------------------------------------
inline bool BoundingVolumeTree::IsInteriorNode() const
{
    return m_pLChild || m_pRChild;
}
//----------------------------------------------------------------------------
inline bool BoundingVolumeTree::IsLeafNode() const
{
    return !m_pLChild && !m_pRChild;
}
//----------------------------------------------------------------------------
