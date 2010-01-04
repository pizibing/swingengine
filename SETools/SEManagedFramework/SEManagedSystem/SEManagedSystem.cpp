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
#include "SEManagedSystem.h"

using namespace Swing::Tools::ManagedFramework;
using namespace System::Runtime::InteropServices;

//---------------------------------------------------------------------------
String^ ManagedSystem::GetPath(String^ thFileName, Mode eMode)
{
    SE_NULL_ARGUMENT_CHECK(thFileName, "thFileName");

    // Native heap resource is allocated here.
    IntPtr pFileName = Marshal::StringToHGlobalAnsi(thFileName);

    using Swing::System;  // Avoid namespace conflict.
    const char* acPath = System::SE_GetPath((const char*)(void*)pFileName, 
        (int)eMode);

    // We've done with the native resource allocated by Marshal, free it.
    Marshal::FreeHGlobal(pFileName);

    if( !acPath )
    {
        return nullptr;
    }

    return gcnew String(acPath);
}
//---------------------------------------------------------------------------
bool ManagedSystem::InsertDirectory(String^ thDirectory)
{
    SE_NULL_ARGUMENT_CHECK(thDirectory, "thDirectory");

    // Native heap resource is allocated here.
    IntPtr pDirectory = Marshal::StringToHGlobalAnsi(thDirectory);

    using Swing::System;  // Avoid namespace conflict.
    bool bRes = System::SE_InsertDirectory((const char*)(void*)pDirectory);

    // We've done with the native resource allocated by Marshal, free it.
    Marshal::FreeHGlobal(pDirectory);

    return bRes;
}
//---------------------------------------------------------------------------