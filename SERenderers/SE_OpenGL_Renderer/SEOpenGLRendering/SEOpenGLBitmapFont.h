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

#ifndef Swing_OpenGLBitmapFont_H
#define Swing_OpenGLBitmapFont_H

#include "SEOpenGLRendererLIB.h"

namespace Swing
{

class SE_RENDERER_API SEBitmapFontChar
{
public:
    SEBitmapFontChar(int iXOrigin, int iYOrigin, int iXSize, int iYSize,
        const unsigned char* aucBitmap)
    {
        XOrigin = iXOrigin;
        YOrigin = iYOrigin;
        XSize = iXSize;
        YSize = iYSize;
        Bitmap = aucBitmap;
    }

    int XOrigin, YOrigin, XSize, YSize;
    const unsigned char* Bitmap;
};

class SE_RENDERER_API SEBitmapFont
{
public:
    SEBitmapFont(const char* acName, int iCount,
        const SEBitmapFontChar* const* pChars)
    {
        Name = acName;
        Count = iCount;
        Chars = pChars;
    }

    const char* Name;
    int Count;
    const SEBitmapFontChar* const* Chars;
};

extern const SEBitmapFont g_Verdana_S16B0I0;

}

#endif
