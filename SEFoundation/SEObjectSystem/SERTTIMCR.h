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

#ifndef Swing_RTTIMCR_H
#define Swing_RTTIMCR_H

//----------------------------------------------------------------------------
#define SE_DECLARE_RTTI \
public: \
    static const SERTTI TYPE; \
    virtual const SERTTI& GetType(void) const { return TYPE; }
//----------------------------------------------------------------------------
#define SE_DECLARE_TEMPLATE_RTTI \
public: \
    SE_FOUNDATION_API static const SERTTI TYPE; \
    virtual const SERTTI& GetType(void) const { return TYPE; }
//----------------------------------------------------------------------------
#define SE_IMPLEMENT_RTTI(nsname, classname, baseclassname) \
    const SERTTI classname::TYPE(#nsname"."#classname, &baseclassname::TYPE)
//----------------------------------------------------------------------------
#define SE_IMPLEMENT_TEMPLATE_RTTI(nsname, classname, baseclassname) \
    template <> \
    const SERTTI classname::TYPE(#nsname"."#classname, &baseclassname::TYPE)
//----------------------------------------------------------------------------

#endif
