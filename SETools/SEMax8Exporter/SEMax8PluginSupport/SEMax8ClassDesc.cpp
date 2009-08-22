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

#include "SEMax8ClassDesc.h"
#include "SEMax8Exporter.h"
#include "resource.h"
#include "SEMax8SceneExport.h"

Class_ID Max8ClassDesc::ID(0x554dbc9c, 0x8f17519);
Max8ClassDesc Max8ClassDesc::TheDescription;

//----------------------------------------------------------------------------
Max8ClassDesc::Max8ClassDesc()
{
}
//----------------------------------------------------------------------------
int Max8ClassDesc::IsPublic() 
{ 
    return TRUE; 
}
//----------------------------------------------------------------------------
void* Max8ClassDesc::Create(BOOL) 
{ 
    return new Max8SceneExport; 
}
//----------------------------------------------------------------------------
const TCHAR* Max8ClassDesc::ClassName() 
{ 
    return Max8Exporter::ThePlugin.GetResourceString(IDS_CLASS_NAME); 
}
//----------------------------------------------------------------------------
SClass_ID Max8ClassDesc::SuperClassID() 
{ 
    return SCENE_EXPORT_CLASS_ID; 
}
//----------------------------------------------------------------------------
Class_ID Max8ClassDesc:: ClassID() 
{ 
    return ID;
}
//----------------------------------------------------------------------------
const TCHAR* Max8ClassDesc::Category()
{ 
    return Max8Exporter::ThePlugin.GetResourceString(IDS_CATEGORY); 
}
//----------------------------------------------------------------------------
const TCHAR* Max8ClassDesc::InternalName() 
{ 
    return Max8Exporter::ThePlugin.GetResourceString(IDS_INTERNALNAME); 
}
//----------------------------------------------------------------------------
HINSTANCE Max8ClassDesc::HInstance() 
{ 
    return Max8Exporter::ThePlugin.GetInstance(); 
}
//----------------------------------------------------------------------------



