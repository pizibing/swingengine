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
inline int StringTree::GetStringCount() const
{
    return (int)m_Strings.size();
}
//----------------------------------------------------------------------------
inline void StringTree::SetString(int i, char* pString)
{
    SE_ASSERT( 0 <= i && i < (int)m_Strings.size() );

    m_Strings[i] = pString;
}
//----------------------------------------------------------------------------
inline char* StringTree::GetString(int i)
{
    SE_ASSERT( 0 <= i && i < (int)m_Strings.size() );

    return m_Strings[i];
}
//----------------------------------------------------------------------------
inline void StringTree::Append(char* pString)
{
    m_Strings.push_back(pString);
}
//----------------------------------------------------------------------------
inline int StringTree::GetChildCount() const
{
    return (int)m_Children.size();
}
//----------------------------------------------------------------------------
inline void StringTree::SetChild(int i, StringTree* pChild)
{
    SE_ASSERT( 0 <= i && i < (int)m_Strings.size() );

    m_Children[i] = pChild;
}
//----------------------------------------------------------------------------
inline StringTree* StringTree::GetChild(int i)
{
    SE_ASSERT( 0 <= i && i < (int)m_Children.size() );

    return m_Children[i];
}
//----------------------------------------------------------------------------
inline void StringTree::Append(StringTree* pChild)
{
    m_Children.push_back(pChild);
}
//----------------------------------------------------------------------------
template <class T>
StringTree* Format(const char* pTitle, int iCount, const T* pValue)
{
    StringTree* pTree = SE_NEW StringTree;
    pTree->Append(Format(pTitle));

    pTree->Append(Format("count =", iCount));
    for( int i = 0; i < iCount; i++ )
    {
        const size_t uiSize = 256;
        char pPrefix[uiSize];
        System::SE_Sprintf(pPrefix, uiSize, "%d: ", i);
        T TempData = pValue[i];
        pTree->Append(Format(pPrefix, TempData));
    }

    return pTree;
}
//----------------------------------------------------------------------------
