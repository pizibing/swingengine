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
inline void SESpatial::SetParent(SESpatial* pParent)
{
    m_pParent = pParent;
}
//----------------------------------------------------------------------------
inline SESpatial* SESpatial::GetParent()
{
    return m_pParent;
}
//----------------------------------------------------------------------------
inline int SESpatial::GetGlobalStateCount() const
{
    return (int)m_GlobalStates.size();
}
//----------------------------------------------------------------------------
inline SEGlobalState* SESpatial::GetGlobalState(int i) const
{
    SE_ASSERT( 0 <= i && i < (int)m_GlobalStates.size() );

    return m_GlobalStates[i];
}
//----------------------------------------------------------------------------
inline void SESpatial::DetachAllGlobalStates()
{
    m_GlobalStates.clear();
}
//----------------------------------------------------------------------------
inline int SESpatial::GetLightCount() const
{
    return (int)m_Lights.size();
}
//----------------------------------------------------------------------------
inline SELight* SESpatial::GetLight(int i) const
{
    SE_ASSERT( 0 <= i && i < (int)m_Lights.size() );

    return StaticCast<SELight>(m_Lights[i]);
}
//----------------------------------------------------------------------------
inline void SESpatial::DetachAllLights()
{
    m_Lights.clear();
}
//----------------------------------------------------------------------------
inline int SESpatial::GetEffectCount() const
{
    return (int)m_Effects.size();
}
//----------------------------------------------------------------------------
inline SEEffect* SESpatial::GetEffect(int i) const
{
    SE_ASSERT( 0 <= i && i < (int)m_Effects.size() );

    return StaticCast<SEEffect>(m_Effects[i]);
}
//----------------------------------------------------------------------------
inline void SESpatial::DetachAllEffects()
{
    m_Effects.clear();
}
//----------------------------------------------------------------------------
inline void SESpatial::SetStartEffect(int i)
{
    SE_ASSERT( 0 <= i && i < (int)m_Effects.size() );

    m_iStartEffect = i;
}
//----------------------------------------------------------------------------
inline int SESpatial::GetStartEffect() const
{
    return m_iStartEffect;
}
//----------------------------------------------------------------------------
