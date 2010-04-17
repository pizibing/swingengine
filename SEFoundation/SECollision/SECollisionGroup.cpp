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
#include "SECollisionGroup.h"
#include "SECollisionRecord.h"

using namespace Swing;

//----------------------------------------------------------------------------
SECollisionGroup::SECollisionGroup()
{
}
//----------------------------------------------------------------------------
SECollisionGroup::~SECollisionGroup()
{
    for( int i = 0; i < (int)m_Record.size(); i++ )
    {
        SE_DELETE m_Record[i];
    }
}
//----------------------------------------------------------------------------
bool SECollisionGroup::Add(SECollisionRecord* pRecord)
{
    for( int i = 0; i < (int)m_Record.size(); i++ )
    {
        if( pRecord == m_Record[i] )
        {
            return false;
        }
    }

    m_Record.push_back(pRecord);

    return true;
}
//----------------------------------------------------------------------------
bool SECollisionGroup::Remove(SECollisionRecord* pRecord)
{
    std::vector<SECollisionRecord*>::iterator tempIter = m_Record.begin();
    for( /**/; tempIter != m_Record.end(); tempIter++ )
    {
        if( pRecord == *tempIter )
        {
            m_Record.erase(tempIter);
            SE_DELETE pRecord;

            return true;
        }
    }

    return false;
}
//----------------------------------------------------------------------------
void SECollisionGroup::TestIntersection()
{
    // 所有对象被假设为静止状态,成对进行比较.
    for( int i0 = 0; i0 < (int)m_Record.size(); i0++ )
    {
        SECollisionRecord* pRecord0 = m_Record[i0];
        for( int i1 = i0 + 1; i1 < (int)m_Record.size(); i1++ )
        {
            SECollisionRecord* pRecord1 = m_Record[i1];
            pRecord0->TestIntersection(*pRecord1);
        }
    }
}
//----------------------------------------------------------------------------
void SECollisionGroup::FindIntersection()
{
    // 所有对象被假设为静止状态,成对进行比较.
    for( int i0 = 0; i0 < (int)m_Record.size(); i0++ )
    {
        SECollisionRecord* pRecord0 = m_Record[i0];
        for( int i1 = i0 + 1; i1 < (int)m_Record.size(); i1++ )
        {
            SECollisionRecord* pRecord1 = m_Record[i1];
            pRecord0->FindIntersection(*pRecord1);
        }
    }
}
//----------------------------------------------------------------------------
void SECollisionGroup::TestIntersection(float fTMax)
{
    // 所有对象被假设为运动状态,成对进行比较.
    for( int i0 = 0; i0 < (int)m_Record.size(); i0++ )
    {
        SECollisionRecord* pRecord0 = m_Record[i0];
        for( int i1 = i0 + 1; i1 < (int)m_Record.size(); i1++ )
        {
            SECollisionRecord* pRecord1 = m_Record[i1];
            if( pRecord0->GetVelocity() || pRecord1->GetVelocity() )
                pRecord0->TestIntersection(fTMax, *pRecord1);
        }
    }
}
//----------------------------------------------------------------------------
void SECollisionGroup::FindIntersection(float fTMax)
{
    // 所有对象被假设为运动状态,成对进行比较.
    for( int i0 = 0; i0 < (int)m_Record.size(); i0++ )
    {
        SECollisionRecord* pRecord0 = m_Record[i0];
        for( int i1 = i0 + 1; i1 < (int)m_Record.size(); i1++ )
        {
            SECollisionRecord* pRecord1 = m_Record[i1];
            if( pRecord0->GetVelocity() || pRecord1->GetVelocity() )
                pRecord0->FindIntersection(fTMax, *pRecord1);
        }
    }
}
//----------------------------------------------------------------------------
