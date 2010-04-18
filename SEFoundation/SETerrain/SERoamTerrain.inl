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
inline int SERoamTerrain::GetRowCount() const
{
    return m_iRows;
}
//----------------------------------------------------------------------------
inline int SERoamTerrain::GetColCount() const
{
    return m_iCols;
}
//----------------------------------------------------------------------------
inline int SERoamTerrain::GetSize() const
{
    return m_iSize;
}
//----------------------------------------------------------------------------
inline float SERoamTerrain::GetMinElevation() const
{
    return m_fMinElevation;
}
//----------------------------------------------------------------------------
inline float SERoamTerrain::GetMaxElevation() const
{
    return m_fMaxElevation;
}
//----------------------------------------------------------------------------
inline float SERoamTerrain::GetSpacing() const
{
    return m_fSpacing;
}
//----------------------------------------------------------------------------
inline float& SERoamTerrain::UVBias()
{
    return m_fUVBias;
}
//----------------------------------------------------------------------------
inline SEColorRGBA& SERoamTerrain::BorderColor()
{
    return m_BorderColor;
}
//----------------------------------------------------------------------------
inline int SERoamTerrain::GetPoolSize(void) const
{
    return m_iPoolSize;
}
//----------------------------------------------------------------------------
inline int SERoamTerrain::GetPatchSize(void) const
{
    return m_iPatchSize;
}
//----------------------------------------------------------------------------
inline int SERoamTerrain::GetSplitLevel(void) const
{
    return m_iSplitLevel;
}
//----------------------------------------------------------------------------
inline int SERoamTerrain::GetVarianceLevel(void) const
{
    return m_iVarianceLevel;
}
//----------------------------------------------------------------------------
inline bool SERoamTerrain::GetLod() const
{
    return m_bLod;
}
//----------------------------------------------------------------------------
inline void SERoamTerrain::SetCamera(SECamera* pCamera)
{
    m_spCamera = pCamera;
}
//----------------------------------------------------------------------------