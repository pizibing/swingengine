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

#pragma once

#ifdef NDEBUG

//----------------------------------------------------------------------------
#define SE_NULL_ARGUMENT_CHECK(ignore0, ignore1) \
((void)0)
//----------------------------------------------------------------------------
#define SE_NULL_REFERENCE_CHECK(ignore0, ignore1) \
((void)0)
//----------------------------------------------------------------------------

#else

//----------------------------------------------------------------------------
#define SE_NULL_ARGUMENT_CHECK(arg, msg) \
if( !(arg) ) \
{ \
    throw gcnew ArgumentNullException(msg); \
}
//----------------------------------------------------------------------------
#define SE_NULL_REFERENCE_CHECK(ref, msg) \
if( !(ref) ) \
{ \
    throw gcnew NullReferenceException(msg); \
}
//----------------------------------------------------------------------------

#endif