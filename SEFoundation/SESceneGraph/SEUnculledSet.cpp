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
#include "SEUnculledSet.h"

using namespace Swing;

//----------------------------------------------------------------------------
UnculledSet::UnculledSet(int iMaxCount, int iGrowBy)
{
    m_pUnculled = 0;
    Resize(iMaxCount, iGrowBy);
}
//----------------------------------------------------------------------------
UnculledSet::~UnculledSet()
{
    SE_DELETE[] m_pUnculled;
}
//----------------------------------------------------------------------------
void UnculledSet::Insert(Spatial* pObject, Effect* pGlobalEffect)
{
    if( ++m_iCount > m_iMaxCount )
    {
        int iNewMaxCount = m_iMaxCount + m_iGrowBy;
        UnculledObject* pNewVisible = SE_NEW UnculledObject[iNewMaxCount];
        size_t uiSize = m_iCount * sizeof(UnculledObject);
        SESystem::SE_Memcpy(pNewVisible, uiSize, m_pUnculled, uiSize);
        SE_DELETE[] m_pUnculled;
        m_pUnculled = pNewVisible;
        m_iMaxCount = iNewMaxCount;
    }

    int iIndex = m_iCount-1;
    m_pUnculled[iIndex].SEObject = pObject;
    m_pUnculled[iIndex].GlobalEffect = pGlobalEffect;
}
//----------------------------------------------------------------------------
void UnculledSet::Resize(int iMaxCount, int iGrowBy)
{
    if( iMaxCount > 0 )
    {
        m_iMaxCount = iMaxCount;
    }
    else
    {
        m_iMaxCount = US_DEFAULT_MAX_COUNT;
    }

    if( iGrowBy > 0 )
    {
        m_iGrowBy = iGrowBy;
    }
    else
    {
        m_iGrowBy = US_DEFAULT_GROWBY;
    }

    SE_DELETE[] m_pUnculled;
    m_iCount = 0;
    m_pUnculled = SE_NEW UnculledObject[m_iMaxCount];
}
//----------------------------------------------------------------------------
