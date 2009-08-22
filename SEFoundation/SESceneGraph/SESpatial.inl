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
inline void Spatial::SetParent(Spatial* pParent)
{
    m_pParent = pParent;
}
//----------------------------------------------------------------------------
inline Spatial* Spatial::GetParent()
{
    return m_pParent;
}
//----------------------------------------------------------------------------
inline int Spatial::GetGlobalStateCount() const
{
    return (int)m_GlobalStates.size();
}
//----------------------------------------------------------------------------
inline GlobalState* Spatial::GetGlobalState(int i) const
{
    SE_ASSERT( 0 <= i && i < (int)m_GlobalStates.size() );

    return m_GlobalStates[i];
}
//----------------------------------------------------------------------------
inline void Spatial::DetachAllGlobalStates()
{
    m_GlobalStates.clear();
}
//----------------------------------------------------------------------------
inline int Spatial::GetLightCount() const
{
    return (int)m_Lights.size();
}
//----------------------------------------------------------------------------
inline Light* Spatial::GetLight(int i) const
{
    SE_ASSERT( 0 <= i && i < (int)m_Lights.size() );

    return StaticCast<Light>(m_Lights[i]);
}
//----------------------------------------------------------------------------
inline void Spatial::DetachAllLights()
{
    m_Lights.clear();
}
//----------------------------------------------------------------------------
inline int Spatial::GetEffectCount() const
{
    return (int)m_Effects.size();
}
//----------------------------------------------------------------------------
inline Effect* Spatial::GetEffect(int i) const
{
    SE_ASSERT( 0 <= i && i < (int)m_Effects.size() );

    return StaticCast<Effect>(m_Effects[i]);
}
//----------------------------------------------------------------------------
inline void Spatial::DetachAllEffects()
{
    m_Effects.clear();
}
//----------------------------------------------------------------------------
inline void Spatial::SetStartEffect(int i)
{
    SE_ASSERT( 0 <= i && i < (int)m_Effects.size() );

    m_iStartEffect = i;
}
//----------------------------------------------------------------------------
inline int Spatial::GetStartEffect() const
{
    return m_iStartEffect;
}
//----------------------------------------------------------------------------
