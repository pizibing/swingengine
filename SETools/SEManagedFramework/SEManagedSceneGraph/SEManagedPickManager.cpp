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

#include "SEManagedFrameworkPCH.h"
#include "SEManagedPickManager.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedPickManager::ManagedPickManager()
{
    m_pPickResults = SE_NEW SESpatial::PickArray;
}
//---------------------------------------------------------------------------
ManagedPickManager::~ManagedPickManager()
{
    SE_DELETE m_pPickResults;
    m_pPickResults = 0;
}
//---------------------------------------------------------------------------
void ManagedPickManager::DoPick(ManagedRay3f^ thRay, 
    INativeSpatial^ thSpatial)
{
    SE_NULL_ARGUMENT_CHECK(thRay, "thRay");
    SE_NULL_ARGUMENT_CHECK(thSpatial, "thSpatial");
    
    SERay3f tempRay;
    thRay->ToRay3f(tempRay);
    SESpatial* pSpatial = thSpatial->GetNativeSpatial();

    SE_NULL_REFERENCE_CHECK(m_pPickResults, "Native pointer is null");
    m_pPickResults->clear();
    SETriMesh::ResetPickRecordPool();

    SE_NULL_REFERENCE_CHECK(pSpatial, "Native pointer is null");
    pSpatial->DoPick(tempRay, *m_pPickResults);
}
//---------------------------------------------------------------------------
ManagedTriMesh^ ManagedPickManager::GetClosestTriMesh()
{
    SE_NULL_REFERENCE_CHECK(m_pPickResults, "Native pointer is null");
    if( m_pPickResults->size() > 0 )
    {
        SESpatial::SEPickRecord* pClosest = SESpatial::GetClosest(
            *m_pPickResults);
        SESpatial* pIObject = pClosest->IObject;

        SETriMesh* pPickedMesh = DynamicCast<SETriMesh>(pIObject);
        if( pPickedMesh )
        {
            return gcnew ManagedTriMesh(pPickedMesh);
        }
    }

    return nullptr;
}
//---------------------------------------------------------------------------