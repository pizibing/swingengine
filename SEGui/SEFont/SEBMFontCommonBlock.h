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

#ifndef Swing_BMFontCommonBlock_H
#define Swing_BMFontCommonBlock_H

#include "SEGuiLIB.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:This class holds information common to all characters.
// Author:Sun Che
// Date:20100603
//----------------------------------------------------------------------------
class SE_GUI_API SEBMFontCommonBlock
{
    // lineHeight : This is the distance in pixels between each line of text. 
    // base       : The number of pixels from the absolute top of the line to 
    //              the base of the characters. 
    // scaleW     : The width of the texture, normally used to scale the x pos 
    //              of the character image. 
    // scaleH     : The height of the texture, normally used to scale the y 
    //              pos of the character image. 
    // pages      : The number of texture pages included in the font. 
    // packed     : Set to 1 if the monochrome characters have been packed 
    //              into each of the texture channels. In this case alphaChnl 
    //              describes what is stored in each channel. 
    // alphaChnl  : Set to 0 if the channel holds the glyph data, 1 if it 
    //              holds the outline, 2 if it holds the glyph and the outline,
    //              3 if its set to zero, and 4 if its set to one. 
    // redChnl    : Set to 0 if the channel holds the glyph data, 1 if it 
    //              holds the outline, 2 if it holds the glyph and the outline,
    //              3 if its set to zero, and 4 if its set to one. 
    // greenChnl  : Set to 0 if the channel holds the glyph data, 1 if it
    //              holds the outline, 2 if it holds the glyph and the outline,
    //              3 if its set to zero, and 4 if its set to one. 
    // blueChnl   : Set to 0 if the channel holds the glyph data, 1 if it 
    //              holds the outline, 2 if it holds the glyph and the outline,
    //              3 if its set to zero, and 4 if its set to one. 

public:
    SEBMFontCommonBlock(void);
    ~SEBMFontCommonBlock(void);

    unsigned short LineHeight;
    unsigned short Base;
    unsigned short ScaleW;
    unsigned short ScaleH;
    unsigned short Pages;
    unsigned char  BitField; // bits 0-6: reserved, bit 7: packed
    unsigned char  AlphaChnl;
    unsigned char  RedChnl;
    unsigned char  GreenChnl;
    unsigned char  BlueChnl;
};

}

#endif
