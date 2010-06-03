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
//
//----------------------------------------------------------------------------
// AngelCode Tool Box Library
// Copyright (c) 2007-2008 Andreas Jonsson
//
// This software is provided 'as-is', without any express or implied 
// warranty. In no event will the authors be held liable for any 
// damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any 
// purpose, including commercial applications, and to alter it and 
// redistribute it freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you 
//    must not claim that you wrote the original software. If you use
//    this software in a product, an acknowledgment in the product 
//    documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and 
//    must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source 
//    distribution.
//
// Andreas Jonsson
// andreas@angelcode.com
//----------------------------------------------------------------------------

#include "SEGuiPCH.h"
#include "SEBMFontCommonBlock.h"

using namespace Swing;

//----------------------------------------------------------------------------
SEBMFontCommonBlock::SEBMFontCommonBlock()
{
    LineHeight = 0;
    Base = 0;
    ScaleW = 0;
    ScaleH = 0;
    Pages = 0;
    BitField = 0;
    RedChnl = 0;
    GreenChnl = 0;
    BlueChnl = 0;
}
//----------------------------------------------------------------------------
SEBMFontCommonBlock::~SEBMFontCommonBlock()
{
}
//----------------------------------------------------------------------------