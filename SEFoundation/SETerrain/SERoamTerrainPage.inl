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
inline int SERoamTerrainPage::GetSize(void) const
{
    return m_iSize;
}
//----------------------------------------------------------------------------
inline const unsigned short* SERoamTerrainPage::GetHeights(void) const
{
    return m_ausHeight;
}
//----------------------------------------------------------------------------
inline const SEVector2f& SERoamTerrainPage::GetOrigin(void) const
{
    return m_Origin;
}
//----------------------------------------------------------------------------
inline float SERoamTerrainPage::GetMinElevation(void) const
{
    return m_fMinElevation;
}
//----------------------------------------------------------------------------
inline float SERoamTerrainPage::GetMaxElevation(void) const
{
    return m_fMaxElevation;
}
//----------------------------------------------------------------------------
inline float SERoamTerrainPage::GetSpacing(void) const
{
    return m_fSpacing;
}
//----------------------------------------------------------------------------
inline float& SERoamTerrainPage::UVBias()
{
    return m_fUVBias;
}
//----------------------------------------------------------------------------
inline int SERoamTerrainPage::GetNextTriNode() const
{ 
    return m_iNextTriNode;
}
//----------------------------------------------------------------------------
inline void SERoamTerrainPage::SetNextTriNode(int iNextNode) 
{ 
    m_iNextTriNode = iNextNode; 
}
//----------------------------------------------------------------------------
inline void SERoamTerrainPage::SetPageGrid(int iRow, int iCol, 
    SERoamTerrain* pTerrain)
{
    m_iRow = iRow;
    m_iCol = iCol;
    m_pTerrain = pTerrain;
}
//----------------------------------------------------------------------------
inline float SERoamTerrainPage::GetX(int iX) const
{
    return m_Origin.X + m_fSpacing*float(iX);
}
//----------------------------------------------------------------------------
inline float SERoamTerrainPage::GetZ(int iZ) const
{
    return m_Origin.Y + m_fSpacing*float(iZ);
}
//----------------------------------------------------------------------------
inline float SERoamTerrainPage::GetHeight(int iIndex) const
{
    return m_fMinElevation + m_fMultiplier*float(m_ausHeight[iIndex]);
}
//----------------------------------------------------------------------------
inline float SERoamTerrainPage::GetTextureCoordinate(int iIndex) const
{
    return m_fTextureSpacing * float(iIndex);
}
//----------------------------------------------------------------------------