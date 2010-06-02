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

#ifndef Swing_BMFontTypes_H
#define Swing_BMFontTypes_H

namespace Swing
{

struct SE_GUI_API SEBMFontCharInfo
{
    unsigned int   ID;
    unsigned short X;
    unsigned short Y;
    unsigned short Width;
    unsigned short Height;
    short          XOffset;
    short          YOffset;
    unsigned char  XAdvance;
    unsigned char  Page;
    unsigned char  Chnl;
};

struct SE_GUI_API SEBMFontInfoBlock
{ 
    unsigned short FontSize;
    unsigned char  Reserved:4;
    unsigned char  Bold    :1;
    unsigned char  Italic  :1;
    unsigned char  Unicode :1;
    unsigned char  Smooth  :1;
    unsigned char  CharSet;
    unsigned short StretchH;
    unsigned char  Aa;
    unsigned char  PaddingUp;
    unsigned char  PaddingRight;
    unsigned char  PaddingDown;
    unsigned char  PaddingLeft;
    unsigned char  SpacingHoriz;
    unsigned char  SpacingVert;
    unsigned char  Outline;  // Added with version 2
    char           FontName[1];
};

struct SE_GUI_API SEBMFontCommonBlock
{
    unsigned short LineHeight;
    unsigned short Base;
    unsigned short ScaleW;
    unsigned short ScaleH;
    unsigned short Pages;
    unsigned char  Packed  :1;
    unsigned char  Reserved:7;
    unsigned char  AlphaChnl;
    unsigned char  RedChnl;
    unsigned char  GreenChnl;
    unsigned char  BlueChnl;
};

struct SE_GUI_API SEBMFontKerningPair
{
    unsigned short First;
    unsigned short Second;
    short          Amount;
};

}

#endif