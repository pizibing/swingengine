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
#include "SEColorRGBA.h"

using namespace Swing;

const ColorRGBA ColorRGBA::SE_RGBA_BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const ColorRGBA ColorRGBA::SE_RGBA_WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const ColorRGBA ColorRGBA::SE_RGBA_RED(1.0f, 0.0f, 0.0f, 1.0f);
const ColorRGBA ColorRGBA::SE_RGBA_GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const ColorRGBA ColorRGBA::SE_RGBA_BLUE(0.0f, 0.0f, 1.0f, 1.0f);
const ColorRGBA ColorRGBA::SE_RGBA_INVALID(-1.0f, -1.0f, -1.0f, -1.0f);

//----------------------------------------------------------------------------
ColorRGBA::ColorRGBA()
{
    m_fData[0] = 0.0f;
    m_fData[1] = 0.0f;
    m_fData[2] = 0.0f;
    m_fData[3] = 0.0f;
}
//----------------------------------------------------------------------------
ColorRGBA::ColorRGBA(float fR, float fG, float fB, float fA)
{
    m_fData[0] = fR;
    m_fData[1] = fG;
    m_fData[2] = fB;
    m_fData[3] = fA;
}
//----------------------------------------------------------------------------
ColorRGBA::ColorRGBA(const float* pData)
{
    m_fData[0] = pData[0];
    m_fData[1] = pData[1];
    m_fData[2] = pData[2];
    m_fData[3] = pData[3];
}
//----------------------------------------------------------------------------
ColorRGBA::ColorRGBA(const ColorRGBA& rColor)
{
    m_fData[0] = rColor.m_fData[0];
    m_fData[1] = rColor.m_fData[1];
    m_fData[2] = rColor.m_fData[2];
    m_fData[3] = rColor.m_fData[3];
}
//----------------------------------------------------------------------------
ColorRGBA& ColorRGBA::operator=(const ColorRGBA& rColor)
{
    m_fData[0] = rColor.m_fData[0];
    m_fData[1] = rColor.m_fData[1];
    m_fData[2] = rColor.m_fData[2];
    m_fData[3] = rColor.m_fData[3];

    return *this;
}
//----------------------------------------------------------------------------
bool ColorRGBA::operator==(const ColorRGBA& rColor) const
{
    return
        m_fData[0] == rColor.m_fData[0] &&
        m_fData[1] == rColor.m_fData[1] &&
        m_fData[2] == rColor.m_fData[2] &&
        m_fData[3] == rColor.m_fData[3];
}
//----------------------------------------------------------------------------
bool ColorRGBA::operator!=(const ColorRGBA& rColor) const
{
    return
        m_fData[0] != rColor.m_fData[0] ||
        m_fData[1] != rColor.m_fData[1] ||
        m_fData[2] != rColor.m_fData[2] ||
        m_fData[3] != rColor.m_fData[3];
}
//----------------------------------------------------------------------------
bool ColorRGBA::operator<(const ColorRGBA& rColor) const
{
    return CompareData(rColor) < 0;
}
//----------------------------------------------------------------------------
bool ColorRGBA::operator<=(const ColorRGBA& rColor) const
{
    return CompareData(rColor) <= 0;
}
//----------------------------------------------------------------------------
bool ColorRGBA::operator>(const ColorRGBA& rColor) const
{
    return CompareData(rColor) > 0;
}
//----------------------------------------------------------------------------
bool ColorRGBA::operator>=(const ColorRGBA& rColor) const
{
    return CompareData(rColor) >= 0;
}
//----------------------------------------------------------------------------
ColorRGBA ColorRGBA::operator+(const ColorRGBA& rColor) const
{
    return ColorRGBA(
        m_fData[0] + rColor.m_fData[0],
        m_fData[1] + rColor.m_fData[1],
        m_fData[2] + rColor.m_fData[2],
        m_fData[3] + rColor.m_fData[3]);
}
//----------------------------------------------------------------------------
ColorRGBA ColorRGBA::operator-(const ColorRGBA& rColor) const
{
    return ColorRGBA(
        m_fData[0] - rColor.m_fData[0],
        m_fData[1] - rColor.m_fData[1],
        m_fData[2] - rColor.m_fData[2],
        m_fData[3] - rColor.m_fData[3]);
}
//----------------------------------------------------------------------------
ColorRGBA ColorRGBA::operator*(const ColorRGBA& rColor) const
{
    return ColorRGBA(
        m_fData[0] * rColor.m_fData[0],
        m_fData[1] * rColor.m_fData[1],
        m_fData[2] * rColor.m_fData[2],
        m_fData[3] * rColor.m_fData[3]);
}
//----------------------------------------------------------------------------
ColorRGBA ColorRGBA::operator*(float fScalar) const
{
    return ColorRGBA(
        fScalar * m_fData[0],
        fScalar * m_fData[1],
        fScalar * m_fData[2],
        fScalar * m_fData[3]);
}
//----------------------------------------------------------------------------
ColorRGBA Swing::operator*(float fScalar, const ColorRGBA& rColor)
{
    return ColorRGBA(
        fScalar * rColor.m_fData[0],
        fScalar * rColor.m_fData[1],
        fScalar * rColor.m_fData[2],
        fScalar * rColor.m_fData[3]);
}
//----------------------------------------------------------------------------
ColorRGBA& ColorRGBA::operator+=(const ColorRGBA& rColor)
{
    m_fData[0] += rColor.m_fData[0];
    m_fData[1] += rColor.m_fData[1];
    m_fData[2] += rColor.m_fData[2];
    m_fData[3] += rColor.m_fData[3];

    return *this;
}
//----------------------------------------------------------------------------
ColorRGBA& ColorRGBA::operator-=(const ColorRGBA& rColor)
{
    m_fData[0] -= rColor.m_fData[0];
    m_fData[1] -= rColor.m_fData[1];
    m_fData[2] -= rColor.m_fData[2];
    m_fData[3] -= rColor.m_fData[3];

    return *this;
}
//----------------------------------------------------------------------------
ColorRGBA& ColorRGBA::operator*=(const ColorRGBA& rColor)
{
    m_fData[0] *= rColor.m_fData[0];
    m_fData[1] *= rColor.m_fData[1];
    m_fData[2] *= rColor.m_fData[2];
    m_fData[3] *= rColor.m_fData[3];

    return *this;
}
//----------------------------------------------------------------------------
ColorRGBA& ColorRGBA::operator*=(float fScalar)
{
    m_fData[0] *= fScalar;
    m_fData[1] *= fScalar;
    m_fData[2] *= fScalar;
    m_fData[3] *= fScalar;

    return *this;
}
//----------------------------------------------------------------------------
void ColorRGBA::Clamp()
{
    for( int i = 0; i < 4; i++ )
    {
        if( m_fData[i] > 1.0f )
        {
            m_fData[i] = 1.0f;
        }
        else if( m_fData[i] < 0.0f )
        {
            m_fData[i] = 0.0f;
        }
    }
}
//----------------------------------------------------------------------------
void ColorRGBA::ScaleByMax()
{
    // 找到最大RGB值
    float fMax = m_fData[0];
    if( m_fData[1] > fMax )
    {
        fMax = m_fData[1];
    }
    if( m_fData[2] > fMax )
    {
        fMax = m_fData[2];
    }

    if( fMax > 1.0f )
    {
        float fInvMax = 1.0f/fMax;
        for( int i = 0; i < 3; i++ )
        {
            m_fData[i] *= fInvMax;
        }
    }

    // 裁剪A值到[0,1]区间
    if( m_fData[3] > 1.0f )
    {
        m_fData[3] = 1.0f;
    }
    else if( m_fData[3] < 0.0f )
    {
        m_fData[3] = 0.0f;
    }
}
//----------------------------------------------------------------------------
