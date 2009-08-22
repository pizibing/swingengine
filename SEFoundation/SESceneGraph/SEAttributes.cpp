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

#include "SEFoundationPCH.h"
#include "SEAttributes.h"

using namespace Swing;

//----------------------------------------------------------------------------
Attributes::Attributes()
{
    m_iChannelCount = 0;
    m_iPositionOffset = -1;
    m_iPositionChannels = 0;
    m_iNormalOffset = -1;
    m_iNormalChannels = 0;
}
//----------------------------------------------------------------------------
Attributes::~Attributes()
{
}
//----------------------------------------------------------------------------
void Attributes::SetPositionChannels(int iPChannels)
{
    SE_ASSERT( 0 <= iPChannels && iPChannels <= 4 );

    m_iPositionChannels = iPChannels;
    UpdateOffsets();
}
//----------------------------------------------------------------------------
void Attributes::SetNormalChannels(int iNChannels)
{
    SE_ASSERT( 0 <= iNChannels && iNChannels <= 4 );

    m_iNormalChannels = iNChannels;
    UpdateOffsets();
}
//----------------------------------------------------------------------------
void Attributes::SetColorChannels(int iUnit, int iCChannels)
{
    SE_ASSERT( 0 <= iUnit && 0 <= iCChannels && iCChannels <= 4 );

    int iMaxUnits = (int)m_ColorChannels.size();
    if( iUnit >= iMaxUnits )
    {
        m_ColorChannels.resize(iUnit+1);
    }

    m_ColorChannels[iUnit] = iCChannels;
    UpdateOffsets();
}
//----------------------------------------------------------------------------
void Attributes::SetTCoordChannels(int iUnit, int iTChannels)
{
    SE_ASSERT( 0 <= iUnit && 0 <= iTChannels && iTChannels <= 4 );

    int iMaxUnits = (int)m_TCoordChannels.size();
    if( iUnit >= iMaxUnits )
    {
        m_TCoordChannels.resize(iUnit+1);
    }

    m_TCoordChannels[iUnit] = iTChannels;
    UpdateOffsets();
}
//----------------------------------------------------------------------------
int Attributes::GetColorOffset(int iUnit) const
{
    if( 0 <= iUnit && iUnit < (int)m_ColorOffset.size() )
    {
        return m_ColorOffset[iUnit];
    }
    return -1;
}
//----------------------------------------------------------------------------
int Attributes::GetColorChannels(int iUnit) const
{
    if( 0 <= iUnit && iUnit < (int)m_ColorChannels.size() )
    {
        return m_ColorChannels[iUnit];
    }
    return 0;
}
//----------------------------------------------------------------------------
bool Attributes::HasColor(int iUnit) const
{
    if( 0 <= iUnit && iUnit < (int)m_ColorChannels.size() )
    {
        return m_ColorChannels[iUnit] > 0;
    }
    return false;
}
//----------------------------------------------------------------------------
int Attributes::GetTCoordOffset(int iUnit) const
{
    if( 0 <= iUnit && iUnit < (int)m_TCoordOffset.size() )
    {
        return m_TCoordOffset[iUnit];
    }
    return -1;
}
//----------------------------------------------------------------------------
int Attributes::GetTCoordChannels(int iUnit) const
{
    if( 0 <= iUnit && iUnit < (int)m_TCoordChannels.size() )
    {
        return m_TCoordChannels[iUnit];
    }
    return 0;
}
//----------------------------------------------------------------------------
bool Attributes::HasTCoord(int iUnit) const
{
    if( 0 <= iUnit && iUnit < (int)m_TCoordChannels.size() )
    {
        return m_TCoordChannels[iUnit] > 0;
    }
    return false;
}
//----------------------------------------------------------------------------
bool Attributes::Matches(const Attributes& rAttributes, bool bIncludeP,
    bool bIncludeN, bool bIncludeC, bool bIncludeT) const
{
    int i;

    if( bIncludeP )
    {
        if( m_iPositionChannels != rAttributes.m_iPositionChannels )
        {
            return false;
        }
    }

    if( bIncludeN )
    {
        if( m_iNormalChannels != rAttributes.m_iNormalChannels )
        {
            return false;
        }
    }

    if( bIncludeC )
    {
        if( m_ColorChannels.size() != rAttributes.m_ColorChannels.size() )
        {
            return false;
        }
        for( i = 0; i < (int)m_ColorChannels.size(); i++ )
        {
            if( m_ColorChannels[i] != rAttributes.m_ColorChannels[i] )
            {
                return false;
            }
        }
    }

    if( bIncludeT )
    {
        if( m_TCoordChannels.size() != rAttributes.m_TCoordChannels.size() )
        {
            return false;
        }
        for( i = 0; i < (int)m_TCoordChannels.size(); i++ )
        {
            if( m_TCoordChannels[i] != rAttributes.m_TCoordChannels[i] )
            {
                return false;
            }
        }
    }

    return true;
}
//----------------------------------------------------------------------------
bool Attributes::operator==(const Attributes& rAttributes) const
{
    // 所有值必须都相等
    int i;

    if( rAttributes.m_iPositionChannels != m_iPositionChannels )
    {
        return false;
    }

    if( rAttributes.m_iNormalChannels != m_iNormalChannels )
    {
        return false;
    }

    if( rAttributes.m_ColorChannels.size() != m_ColorChannels.size() )
    {
        return false;
    }
    for( i = 0; i < (int)m_ColorChannels.size(); i++ )
    {
        if( rAttributes.m_ColorChannels[i] != m_ColorChannels[i] )
        {
            return false;
        }
    }

    if( rAttributes.m_TCoordChannels.size() != m_TCoordChannels.size() )
    {
        return false;
    }
    for( i = 0; i < (int)m_TCoordChannels.size(); i++ )
    {
        if( rAttributes.m_TCoordChannels[i] != m_TCoordChannels[i] )
        {
            return false;
        }
    }

    return true;
}
//----------------------------------------------------------------------------
bool Attributes::operator!=(const Attributes& rAttributes) const
{
    return !operator==(rAttributes);
}
//----------------------------------------------------------------------------
void Attributes::UpdateOffsets()
{
    m_iChannelCount = 0;
    m_iPositionOffset = -1;
    m_iNormalOffset = -1;
    m_ColorOffset.resize(m_ColorChannels.size());
    m_TCoordOffset.resize(m_TCoordChannels.size());

    if( m_iPositionChannels > 0 )
    {
        m_iPositionOffset = m_iChannelCount;
        m_iChannelCount += m_iPositionChannels;
    }

    if( m_iNormalChannels > 0 )
    {
        m_iNormalOffset = m_iChannelCount;
        m_iChannelCount += m_iNormalChannels;
    }

    int i;
    for( i = 0; i < (int)m_ColorChannels.size(); i++ )
    {
        if( m_ColorChannels[i] > 0 )
        {
            m_ColorOffset[i] = m_iChannelCount;
            m_iChannelCount += m_ColorChannels[i];
        }
    }

    for( i = 0; i < (int)m_TCoordChannels.size(); i++ )
    {
        if( m_TCoordChannels[i] > 0 )
        {
            m_TCoordOffset[i] = m_iChannelCount;
            m_iChannelCount += m_TCoordChannels[i];
        }
    }
}
//----------------------------------------------------------------------------
