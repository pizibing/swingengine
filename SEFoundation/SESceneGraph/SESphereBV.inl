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
inline int SESphereBV::GetBVType() const
{
    return SEBoundingVolume::BV_SPHERE;
}
//----------------------------------------------------------------------------
inline void SESphereBV::SetCenter(const SEVector3f& rCenter)
{
    m_Sphere.Center = rCenter;
}
//----------------------------------------------------------------------------
inline void SESphereBV::SetRadius(float fRadius)
{
    m_Sphere.Radius = fRadius;
}
//----------------------------------------------------------------------------
inline SEVector3f SESphereBV::GetCenter() const
{
    return m_Sphere.Center;
}
//----------------------------------------------------------------------------
inline float SESphereBV::GetRadius() const
{
    return m_Sphere.Radius;
}
//----------------------------------------------------------------------------
inline SESphere3f& SESphereBV::Sphere()
{
    return m_Sphere;
}
//----------------------------------------------------------------------------
inline const SESphere3f& SESphereBV::GetSphere() const
{
    return m_Sphere;
}
//----------------------------------------------------------------------------
