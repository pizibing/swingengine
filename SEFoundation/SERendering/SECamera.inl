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
inline SEVector3f SECamera::GetLocation() const
{
    return m_Location;
}
//----------------------------------------------------------------------------
inline SEVector3f SECamera::GetRVector() const
{
    return m_RVector;
}
//----------------------------------------------------------------------------
inline SEVector3f SECamera::GetUVector() const
{
    return m_UVector;
}
//----------------------------------------------------------------------------
inline SEVector3f SECamera::GetDVector() const
{
    return m_DVector;
}
//----------------------------------------------------------------------------
inline const float* SECamera::GetFrustum() const
{
    return m_Frustum;
}
//----------------------------------------------------------------------------
inline float SECamera::GetDMin() const
{
    return m_Frustum[VF_DMIN];
}
//----------------------------------------------------------------------------
inline float SECamera::GetDMax() const
{
    return m_Frustum[VF_DMAX];
}
//----------------------------------------------------------------------------
inline float SECamera::GetUMin() const
{
    return m_Frustum[VF_UMIN];
}
//----------------------------------------------------------------------------
inline float SECamera::GetUMax() const
{
    return m_Frustum[VF_UMAX];
}
//----------------------------------------------------------------------------
inline float SECamera::GetRMin() const
{
    return m_Frustum[VF_RMIN];
}
//----------------------------------------------------------------------------
inline float SECamera::GetRMax() const
{
    return m_Frustum[VF_RMAX];
}
//----------------------------------------------------------------------------
inline bool SECamera::IsPerspective() const
{
    return m_bPerspective;
}
//----------------------------------------------------------------------------