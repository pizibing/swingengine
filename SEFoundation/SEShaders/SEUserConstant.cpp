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
#include "SEUserConstant.h"

using namespace Swing;

float UserConstant::ms_afDefaultData[16] = 
{
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f
};

UserConstant::ReleaseID UserConstant::OnReleaseID = 0;
UserConstant::CopyID UserConstant::OnCopyID = 0;

//----------------------------------------------------------------------------
UserConstant::UserConstant(const std::string& rName, void* pID, int iDataCount)
    :
    m_Name(rName)
{
    SE_ASSERT( pID );
    SE_ASSERT( iDataCount > 0 && iDataCount <= 16 );

    m_pID = pID;
    m_iDataCount = iDataCount;

    // 稍后在创建shader effect时,用户可以为此变量指定实际数据存储位置.
    m_pData = (float*)&ms_afDefaultData[0];

    Active = true;
}
//----------------------------------------------------------------------------
UserConstant::UserConstant(const UserConstant& rUC)
{
    m_Name = rUC.m_Name;
    m_iDataCount = rUC.m_iDataCount;
    m_pData = rUC.m_pData;

    if( OnCopyID )
    {
        OnCopyID(rUC.m_pID, &m_pID);
    }
    else
    {
        m_pID = rUC.m_pID;
    }

    Active = true;
}
//----------------------------------------------------------------------------
UserConstant::~UserConstant()
{
    // 注意m_pData只索引数据,不在这里释放.

    if( OnReleaseID )
    {
        OnReleaseID(m_pID);
    }
}
//----------------------------------------------------------------------------
void UserConstant::SetDataSource(float* pData)
{
    SE_ASSERT( pData );

    m_pData = pData;
}
//----------------------------------------------------------------------------
