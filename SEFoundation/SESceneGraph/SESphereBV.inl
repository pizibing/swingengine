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
inline int SphereBV::GetBVType() const
{
    return BoundingVolume::BV_SPHERE;
}
//----------------------------------------------------------------------------
inline void SphereBV::SetCenter(const Vector3f& rCenter)
{
    m_Sphere.Center = rCenter;
}
//----------------------------------------------------------------------------
inline void SphereBV::SetRadius(float fRadius)
{
    m_Sphere.Radius = fRadius;
}
//----------------------------------------------------------------------------
inline Vector3f SphereBV::GetCenter() const
{
    return m_Sphere.Center;
}
//----------------------------------------------------------------------------
inline float SphereBV::GetRadius() const
{
    return m_Sphere.Radius;
}
//----------------------------------------------------------------------------
inline Sphere3f& SphereBV::Sphere()
{
    return m_Sphere;
}
//----------------------------------------------------------------------------
inline const Sphere3f& SphereBV::GetSphere() const
{
    return m_Sphere;
}
//----------------------------------------------------------------------------
