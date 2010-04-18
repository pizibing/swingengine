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
inline void SECuller::SetCamera(const SECamera* pCamera)
{
    m_pCamera = pCamera;
}
//----------------------------------------------------------------------------
inline const SECamera* SECuller::GetCamera() const
{
    return m_pCamera;
}
//----------------------------------------------------------------------------
inline const float* SECuller::GetFrustum() const
{
    return m_Frustum;
}
//----------------------------------------------------------------------------
inline SEUnculledSet& SECuller::GetVisibleSet()
{
    return m_VisibleSet;
}
//----------------------------------------------------------------------------
inline SEUnculledSet& SECuller::GetAudibleSet()
{
    return m_AudibleSet;
}
//----------------------------------------------------------------------------
inline void SECuller::Insert(SESpatial* pObject, SEEffect* pGlobalEffect,
    bool bIsAudible)
{
    if( !bIsAudible )
    {
        m_VisibleSet.Insert(pObject, pGlobalEffect);
    }
    else
    {
        m_AudibleSet.Insert(pObject, pGlobalEffect);
    }
}
//----------------------------------------------------------------------------
inline int SECuller::GetPlaneCount() const
{
    return m_iPlaneCount;
}
//----------------------------------------------------------------------------
inline const SEPlane3f* SECuller::GetPlanes() const
{
    return m_aPlane;
}
//----------------------------------------------------------------------------
inline void SECuller::SetPlaneState(unsigned int uiPlaneState)
{
    m_uiPlaneState = uiPlaneState;
}
//----------------------------------------------------------------------------
inline unsigned int SECuller::GetPlaneState() const
{
    return m_uiPlaneState;
}
//----------------------------------------------------------------------------
inline void SECuller::PushPlane(const SEPlane3f& rPlane)
{
    if( m_iPlaneCount < US_MAX_PLANE_COUNT )
    {
        m_aPlane[m_iPlaneCount++] = rPlane;
    }
}
//----------------------------------------------------------------------------
inline void SECuller::PopPlane()
{
    if( m_iPlaneCount > SECamera::VF_COUNT )
    {
        // 截投体平面不能被弹出
        m_iPlaneCount--;
    }
}
//----------------------------------------------------------------------------
