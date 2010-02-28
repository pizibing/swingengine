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
#include "SEManagedImage.h"

using namespace Swing;
using namespace Swing::Tools::ManagedFramework;

//---------------------------------------------------------------------------
ManagedImage::ManagedImage()
{
}
//---------------------------------------------------------------------------
ManagedImage::ManagedImage(Image* pImage)
{
    m_pspImage = SE_NEW ImagePtr;
    (*m_pspImage) = pImage;
}
//---------------------------------------------------------------------------
ManagedImage::~ManagedImage()
{
    SE_DELETE m_pspImage;
    m_pspImage = 0;
}
//---------------------------------------------------------------------------
void ManagedImage::SetName(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");
    SE_NULL_REFERENCE_CHECK(m_pspImage, "Native pointer is null");

    const char* acName = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acName);
    ManagedUtility::FreeNativeCharBuffer(acName);
    (*m_pspImage)->SetName(tempName);
}
//---------------------------------------------------------------------------
String^ ManagedImage::GetName()
{
    SE_NULL_REFERENCE_CHECK(m_pspImage, "Native pointer is null");
    return gcnew String((*m_pspImage)->GetName().c_str());
}
//---------------------------------------------------------------------------
int ManagedImage::GetNativeReferences()
{
    SE_NULL_REFERENCE_CHECK(m_pspImage, "Native pointer is null");
    return (*m_pspImage)->GetReferences();
}
//---------------------------------------------------------------------------
Image* ManagedImage::GetNativeImage()
{
    SE_NULL_REFERENCE_CHECK(m_pspImage, "Native pointer is null");
    return (Image*)(*m_pspImage);
}
//---------------------------------------------------------------------------
ManagedImage^ ManagedImage::Find(String^ thName)
{
    SE_NULL_ARGUMENT_CHECK(thName, "thName");

    const char* acName = ManagedUtility::StringToNativeCharBuffer(thName);
    std::string tempName(acName);
    ManagedUtility::FreeNativeCharBuffer(acName);
    Image* pImage = ImageCatalog::GetActive()->Find(tempName);
    return gcnew ManagedImage(pImage);
}
//---------------------------------------------------------------------------