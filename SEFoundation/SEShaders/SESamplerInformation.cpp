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
#include "SESamplerInformation.h"

using namespace Swing;

SamplerInformation::ReleaseID SamplerInformation::OnReleaseID = 0;
SamplerInformation::CopyID SamplerInformation::OnCopyID = 0;

//----------------------------------------------------------------------------
SamplerInformation::SamplerInformation(const std::string& rName, Type eType,
    void* pID)
    :
    m_Name(rName)
{
    SE_ASSERT( pID );

    m_eType = eType;
    m_pID = pID;

    switch( m_eType )
    {
    case SAMPLER_1D:
        m_iDimension = 1;
        break;
    case SAMPLER_2D:
        m_iDimension = 2;
        break;
    case SAMPLER_3D:
        m_iDimension = 3;
        break;
    case SAMPLER_CUBE:
        m_iDimension = 2;
        break;
    case SAMPLER_PROJ:
        m_iDimension = 2;
        break;
    default:
        SE_ASSERT( false );
        m_iDimension = 0;
        break;
    }
}
//----------------------------------------------------------------------------
SamplerInformation::SamplerInformation(const SamplerInformation& rSI)
{
    m_Name = rSI.m_Name;
    m_eType = rSI.m_eType;
    m_iDimension = rSI.m_iDimension;

    if( OnCopyID )
    {
        OnCopyID(rSI.m_pID, &m_pID);
    }
    else
    {
        m_pID = rSI.m_pID;
    }
}
//----------------------------------------------------------------------------
SamplerInformation::~SamplerInformation()
{
    if( OnReleaseID )
    {
        OnReleaseID(m_pID);
    }
}
//----------------------------------------------------------------------------
