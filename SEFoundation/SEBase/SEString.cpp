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
#include "SEString.h"

using namespace Swing;

//----------------------------------------------------------------------------
String::String(const char* pText)
{
    // 用户必须确保pText以空字符结尾.

    if( pText )
    {
        m_iLength = (int)strlen(pText);
        size_t uiSize = (size_t)(m_iLength + 1);
        m_pText = SE_NEW char[uiSize];
        System::SE_Strcpy(m_pText, uiSize, pText);
    }
    else
    {
        m_iLength = 0;
        m_pText = SE_NEW char[1];
        m_pText[0] = 0;
    }
}
//----------------------------------------------------------------------------
String::String(int iLength, const char* pText)
{
    if( iLength < 0 || (iLength > 0 && !pText) )
    {
        SE_ASSERT( !(iLength < 0 || (iLength > 0 && !pText)) );
        iLength = 0;
    }

#ifdef _DEBUG
    // 确保pText有制定数量的非空字符.
    if( iLength > 0 )
    {
        int i;
        for( i = 0; i < iLength; i++ )
        {
            if( pText[i] == 0 )
                break;
        }
        SE_ASSERT( i == iLength );
    }
#endif

    m_iLength = iLength;
    if( m_iLength > 0 )
    {
        size_t uiSize = (size_t)(m_iLength + 1);
        m_pText = SE_NEW char[uiSize];
        // 严格拷贝指定数量的字符,支持pText没有空字符结尾时的情况.
        memcpy(m_pText, pText, m_iLength*sizeof(char));
        m_pText[m_iLength] = 0;
    }
    else
    {
        m_pText = SE_NEW char[1];
        m_pText[0] = 0;
    }
}
//----------------------------------------------------------------------------
String::String(const String& rString)
{
    m_pText = 0;
    *this = rString;
}
//----------------------------------------------------------------------------
String::~String()
{
    SE_DELETE[] m_pText;
}
//----------------------------------------------------------------------------
char String::operator[](int i) const
{
    SE_ASSERT( 0 <= i && i < m_iLength );

    return m_pText[i];
}
//----------------------------------------------------------------------------
char& String::operator[](int i)
{
    SE_ASSERT( 0 <= i && i < m_iLength );

    return m_pText[i];
}
//----------------------------------------------------------------------------
String& String::operator=(const String& rString)
{
    m_iLength = rString.m_iLength;
    SE_DELETE[] m_pText;
    size_t uiSize = (size_t)(m_iLength + 1);
    m_pText = SE_NEW char[uiSize];
    System::SE_Strcpy(m_pText, uiSize, rString.m_pText);
    return *this;
}
//----------------------------------------------------------------------------
String& String::operator+=(const String& rString)
{
    size_t uiSize = (size_t)(m_iLength + rString.m_iLength + 1);
    char* pNew = SE_NEW char[uiSize];
    System::SE_Strcpy(pNew, (size_t)(m_iLength + 1), m_pText);
    SE_DELETE[] m_pText;
    m_pText = System::SE_Strcat(pNew, uiSize, rString.m_pText);
    m_iLength = (int)(uiSize - 1);
    return *this;
}
//----------------------------------------------------------------------------
String String::operator+(const String& rString)
{
    size_t uiSize = (size_t)(m_iLength + rString.m_iLength + 1);
    char* pNew = SE_NEW char[uiSize];
    System::SE_Strcpy(pNew, (size_t)(m_iLength + 1), m_pText);
    System::SE_Strcat(pNew, uiSize, rString.m_pText);
    String TempData((int)(uiSize - 1), pNew);
    SE_DELETE[] pNew;
    return TempData;
}
//----------------------------------------------------------------------------
bool String::operator==(const String& rString) const
{
    return m_iLength == rString.m_iLength
        && memcmp(m_pText, rString.m_pText, m_iLength) == 0;
}
//----------------------------------------------------------------------------
bool String::operator!=(const String& rString) const
{
    return m_iLength != rString.m_iLength
        || memcmp(m_pText, rString.m_pText, m_iLength) != 0;
}
//----------------------------------------------------------------------------
bool String::operator<(const String& rString) const
{
    return m_iLength == rString.m_iLength
        && CompareData(rString) < 0;
}
//----------------------------------------------------------------------------
bool String::operator<=(const String& rString) const
{
    return m_iLength == rString.m_iLength
        && CompareData(rString) <= 0;
}
//----------------------------------------------------------------------------
bool String::operator>(const String& rString) const
{
    return m_iLength == rString.m_iLength
        && CompareData(rString) > 0;
}
//----------------------------------------------------------------------------
bool String::operator>=(const String& rString) const
{
    return m_iLength == rString.m_iLength
        && CompareData(rString) >= 0;
}
//----------------------------------------------------------------------------
String::operator unsigned int() const
{
    unsigned int uiKey = 0;
    for( int i = 0; i < m_iLength; i++ )
        uiKey += (uiKey << 5) + m_pText[i];

    return uiKey;
}
//----------------------------------------------------------------------------
String String::ToUpper() const
{
    String TempData(*this);
    for( int i = 0; i < m_iLength; i++ )
        TempData.m_pText[i] = (char)toupper(m_pText[i]);

    return TempData;
}
//----------------------------------------------------------------------------
String String::ToLower() const
{
    String TempData(*this);
    for( int i = 0; i < m_iLength; i++ )
        TempData.m_pText[i] = (char)tolower(m_pText[i]);

    return TempData;
}
//----------------------------------------------------------------------------

