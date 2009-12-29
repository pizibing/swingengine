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
#include "SEManagedAttributes.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedAttributes::ManagedAttributes()
{
    // Create the native attributes.
    m_pAttributes = SE_NEW Attributes;
}
//---------------------------------------------------------------------------
ManagedAttributes::~ManagedAttributes()
{
    SE_DELETE m_pAttributes;
    m_pAttributes = 0;
}
//---------------------------------------------------------------------------
void ManagedAttributes::SetPositionChannels(int iPChannels)
{
    m_pAttributes->SetPositionChannels(iPChannels);
}
//---------------------------------------------------------------------------
void ManagedAttributes::SetNormalChannels(int iNChannels)
{
    m_pAttributes->SetNormalChannels(iNChannels);
}
//---------------------------------------------------------------------------
void ManagedAttributes::SetColorChannels(int iUnit, int iCChannels)
{
    m_pAttributes->SetColorChannels(iUnit, iCChannels);
}
//---------------------------------------------------------------------------
void ManagedAttributes::SetTCoordChannels(int iUnit, int iTChannels)
{
    m_pAttributes->SetTCoordChannels(iUnit, iTChannels);
}
//---------------------------------------------------------------------------
Attributes* ManagedAttributes::GetNativeAttributes()
{
    return m_pAttributes;
}
//---------------------------------------------------------------------------