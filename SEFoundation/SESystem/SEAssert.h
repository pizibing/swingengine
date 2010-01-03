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

#ifndef Swing_Assert_H
#define Swing_Assert_H

#ifdef NDEBUG

//----------------------------------------------------------------------------
#define SE_ASSERT(ignore) \
((void)0)
//----------------------------------------------------------------------------

#else

//----------------------------------------------------------------------------
// Microsoft Windows 2000/XP platform
//----------------------------------------------------------------------------
#if defined(_WIN32)

//----------------------------------------------------------------------------
#define SE_SAFEBREAKPOINT \
try \
{ \
    _asm \
    { \
        int 3 \
    }; \
} \
catch(...) \
{ \
    ; \
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Macintosh OS X platform
//----------------------------------------------------------------------------
#elif defined(__APPLE__)

#define SE_SAFEBREAKPOINT ((void)0)

//----------------------------------------------------------------------------
// Linux platform
//----------------------------------------------------------------------------
#else

#define SE_SAFEBREAKPOINT ((void)0)

#endif

//----------------------------------------------------------------------------
#define SE_ASSERT(expr) \
if( !(expr) ) \
{ \
    FILE* pFile = System::SE_Fopen("Assert.txt", "at"); \
    System::SE_Fprintf(pFile, "SwingEngine assert:\n"); \
    System::SE_Fprintf(pFile, "File: %s\n", __FILE__); \
    System::SE_Fprintf(pFile, "Line: %d\n", __LINE__); \
    System::SE_Fprintf(pFile, "Function: %s\n", __FUNCTION__); \
    System::SE_Fclose(pFile); \
    SE_SAFEBREAKPOINT; \
    assert(expr); \
}
//----------------------------------------------------------------------------

#endif

#endif

