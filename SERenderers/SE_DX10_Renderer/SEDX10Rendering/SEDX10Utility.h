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

#ifndef Swing_DX10Utility_H
#define Swing_DX10Utility_H

#include "SEDX10RendererLIB.h"

//#ifdef _DEBUG
//#define D3D_DEBUG_INFO
//#endif

#include <d3d10_1.h>
#include <d3d10.h>
#include <d3dx10tex.h>
#include <dxerr.h>

#include <Cg/Cg.h>
#include <Cg/cgD3D10.h>

//----------------------------------------------------------------------------
#define SE_DX10_SAFE_RELEASE(p) \
{ \
    if( p ) \
    { \
        (p)->Release(); \
        (p) = 0; \
    } \
}
//----------------------------------------------------------------------------
#define SE_DX10_SAFE_DELETE(p) \
{ \
    if( p ) \
    { \
        delete (p); \
        (p) = 0; \
    } \
}
//----------------------------------------------------------------------------
#define SE_DX10_SAFE_DELETE_ARRAY(p) \
{ \
    if( p ) \
    { \
        delete[] (p); \
        (p) = 0; \
    } \
}
//----------------------------------------------------------------------------
#ifdef _DEBUG
#define SE_DX10_DEBUG_CG_PROGRAM \
{ \
    CGerror tempError; \
    cgGetLastErrorString(&tempError); \
    SE_ASSERT( tempError == CG_NO_ERROR ); \
}
#else
#define SE_DX10_DEBUG_CG_PROGRAM
#endif
//----------------------------------------------------------------------------

#endif
