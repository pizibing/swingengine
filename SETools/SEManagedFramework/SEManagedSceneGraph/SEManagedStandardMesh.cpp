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
#include "SEManagedStandardMesh.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedStandardMesh::ManagedStandardMesh(ManagedAttributes^ thAttr)
{
    SE_NULL_ARGUMENT_CHECK(thAttr, "thAttr");
    m_pStandardMesh = SE_NEW StandardMesh(*thAttr->GetNativeAttributes());
}
//---------------------------------------------------------------------------
ManagedStandardMesh::~ManagedStandardMesh()
{
    SE_DELETE m_pStandardMesh;
    m_pStandardMesh = 0;
}
//---------------------------------------------------------------------------
ManagedTriMesh^ ManagedStandardMesh::Box(float fXExtent, float fYExtent, 
    float fZExtent)
{
    SE_NULL_REFERENCE_CHECK(m_pStandardMesh, "Native pointer is null");
    TriMesh* pTriMesh = m_pStandardMesh->Box(fXExtent, fYExtent, fZExtent);

    return gcnew ManagedTriMesh(pTriMesh);
}
//---------------------------------------------------------------------------
StandardMesh* ManagedStandardMesh::GetNativeStandardMesh()
{
    return m_pStandardMesh;
}
//---------------------------------------------------------------------------