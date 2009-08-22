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

/*--------------------------------------------------------------------------*/
/* Swing Engine OpenGL Encapsulator, Version 1 */
/*--------------------------------------------------------------------------*/

#ifndef Swing_GLPlugIn_H
#define Swing_GLPlugIn_H

/*
默认情况下,每次OpenGL函数调用没有任何额外语义发生.
如果有必要的话,移除SEglPlugin.h,并加入新文件SEglPlugin.c实现额外语义.
比如用于生成report-log或用于profiling.
*/

#define SE_ENTER_FUNCTION(glFunction)
#define SE_NONNULL_FUNCTION(glFunction)
#define SE_NULL_FUNCTION(glFunction)
#define SE_EXIT_FUNCTION(glFunction)

#endif
