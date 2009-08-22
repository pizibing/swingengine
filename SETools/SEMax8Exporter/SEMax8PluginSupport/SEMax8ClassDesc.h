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

#ifndef Swing_Max8ClassDesc_H
#define Swing_Max8ClassDesc_H

#include "max.h"
#include "iparamb2.h"

//----------------------------------------------------------------------------
// 名称:Max8ClassDesc类
// 说明:
// 作者:Sun Che
// 时间:20080814
//----------------------------------------------------------------------------
class Max8ClassDesc : public ClassDesc2
{
public:
    Max8ClassDesc(void);

    virtual int IsPublic(void);
    virtual void* Create(BOOL bLoading = FALSE);
    virtual const TCHAR* ClassName(void);
    virtual SClass_ID SuperClassID(void);
    virtual Class_ID ClassID(void);
    virtual const TCHAR* Category(void);
    virtual const TCHAR* InternalName(void);
    virtual HINSTANCE HInstance(void);

    static Class_ID ID;
    static Max8ClassDesc TheDescription;
};

#endif



