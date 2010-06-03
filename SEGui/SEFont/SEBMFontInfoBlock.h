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

#ifndef Swing_BMFontInfoBlock_H
#define Swing_BMFontInfoBlock_H

#include "SEGuiLIB.h"

namespace Swing
{

//----------------------------------------------------------------------------
// Description:This class holds information on how the font was generated.
// Author:Sun Che
// Date:20100603
//----------------------------------------------------------------------------
class SE_GUI_API SEBMFontInfoBlock
{ 
    // face     : This is the name of the true type font. 
    // size     : The size of the true type font. 
    // bold     : The font is bold. 
    // italic   : The font is italic. 
    // charset  : The name of the OEM charset used (when not unicode). 
    // unicode  : Set to 1 if it is the unicode charset. 
    // stretchH : The font height stretch in percentage. 100% means no stretch. 
    // smooth   : Set to 1 if smoothing was turned on. 
    // aa       : The supersampling level used. 1 means no supersampling was 
    //            used. 
    // padding  : The padding for each character (up, right, down, left). 
    // spacing  : The spacing for each character (horizontal, vertical). 
    // outline  : The outline thickness for the characters. 

public:
    SEBMFontInfoBlock(void);
    ~SEBMFontInfoBlock(void);

    unsigned short FontSize;
    unsigned char  BitField;
    unsigned char  CharSet;
    unsigned short StretchH;
    unsigned char  AA;
    unsigned char  PaddingUp;
    unsigned char  PaddingRight;
    unsigned char  PaddingDown;
    unsigned char  PaddingLeft;
    unsigned char  SpacingHoriz;
    unsigned char  SpacingVert;
    unsigned char  Outline;
    char*          acFontName;
};

}

#endif
