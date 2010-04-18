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
#include "SEBindable.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEBindable::SEBindable()
{
}
//----------------------------------------------------------------------------
SEBindable::~SEBindable()
{
}
//----------------------------------------------------------------------------
int SEBindable::GetInfoCount() const
{
    return (int)m_InfoArray.size();
}
//----------------------------------------------------------------------------
SEResourceIdentifier* SEBindable::GetIdentifier(SERenderer* pUser) const
{
    for( int i = 0; i < (int)m_InfoArray.size(); i++ )
    {
        const Info& rInfo = m_InfoArray[i];
        if( rInfo.User == pUser )
        {
            return rInfo.ID;
        }
    }

    // 资源还没有和该renderer绑定
    return 0;
}
//----------------------------------------------------------------------------
SEResourceIdentifier* SEBindable::GetIdentifier(int i, SERenderer* pUser) 
    const
{
    if( 0 <= i && i < (int)m_InfoArray.size() )
    {
        const Info& rInfo = m_InfoArray[i];
        if( rInfo.User == pUser )
        {
            return rInfo.ID;
        }
    }

    // 资源还没有和该renderer绑定
    return 0;
}
//----------------------------------------------------------------------------
void SEBindable::Release()
{
    while( m_InfoArray.size() > 0 )
    {
        Info& rInfo = m_InfoArray[0];
        (rInfo.User->*rInfo.Release)(this);
    }
}
//----------------------------------------------------------------------------
void SEBindable::OnLoad(SERenderer* pUser, SERenderer::ReleaseFunction 
    oRelease, SEResourceIdentifier* pID)
{
    Info TempData;
    TempData.User = pUser;
    TempData.Release = oRelease;
    TempData.ID = pID;
    m_InfoArray.push_back(TempData);
}
//----------------------------------------------------------------------------
void SEBindable::OnRelease(SERenderer* pUser, SEResourceIdentifier* pID)
{
    int iCount = (int)m_InfoArray.size();
    for( int i = 0; i < iCount; i++ )
    {
        const Info& rInfo = m_InfoArray[i];
        if( rInfo.User == pUser && rInfo.ID == pID )
        {
            // 如果必要则用数组最后元素覆盖当前元素
            if( i < --iCount )
            {
                m_InfoArray[i] = m_InfoArray[iCount];
            }

            // 删除最后元素
            m_InfoArray.pop_back();

            return;
        }
    }
}
//----------------------------------------------------------------------------
